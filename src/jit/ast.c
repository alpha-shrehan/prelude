#include "ast.h"
#include "parser.h"

size_t _parse_args(jit_stmt_t *, struct _jit_token_str *, int);
size_t _eval_size(struct _jit_token_str *, int);
void _append_stmt_tomod(jit_module_t *, jit_stmt_t);
void _get_stmt_block_body(struct _jit_token_str *, int *, struct _jit_token_str *, int);

struct
{
    char *type;
    size_t size;
} DSIZES[] = {
    {"int", sizeof(int)},
    {"char", sizeof(char)},
    {"bool", sizeof(int)},
    {NULL, 0}};

JIT_API int
Jit_Parser_Make_AST(
    jit_module_t *mod,
    struct _jit_lexer_ctx_str *toks)
{
    for (size_t i = 0; i < toks->tok_count; i++)
    {
        struct _jit_token_str ctok = toks->toks[i];

        switch (ctok.type)
        {
        case JIT_TOKEN_IDENTIFIER:
        {
            char *dval = ctok.v.Identifier.val;

            if (ctok.v.Identifier.reserved_token)
            {
                if (!strcmp(dval, "decl"))
                {
                    jit_stmt_t st;
                    st.type = JIT_STMT_FUN_DECL;
                    st.v.func_decl.name = toks->toks[i + 1].v.Identifier.val;
                    st.v.func_decl.arg_count = 0;
                    st.v.func_decl.args = MALLOC(sizeof(jit_expr_t));

                    int nd = _parse_args(&st, toks->toks, i + 2) + 1; // -> operator

                    st.v.func_decl.ret_type = Jit_Parser_Empty_Expr_New();
                    st.v.func_decl.ret_type->type = JIT_EXPR_CONSTANT;

                    struct _jit_token_str *sztok = MALLOC(sizeof(struct _jit_token_str));
                    int tsz = 0, gb = 0;

                    for (size_t j = nd + 1; i < toks->tok_count; i++)
                    {
                        struct _jit_token_str _t = toks->toks[j];

                        if (_t.type == JIT_TOKEN_OPERATOR)
                        {
                            if (!strcmp(_t.v.Operator.val, "{") && gb)
                                gb++;
                            if (!strcmp(_t.v.Operator.val, "{") && !gb)
                                break;
                            if (!strcmp(_t.v.Operator.val, "}"))
                                gb--;
                        }

                        if (tsz)
                            sztok = REALLOC(sztok, (tsz + 1) * sizeof(struct _jit_token_str));

                        sztok[tsz++] = _t;
                    }

                    st.v.func_decl.ret_type->size = _eval_size(sztok, tsz);

                    jit_const_t *ct = Jit_Parser_Empty_Const_New();
                    ct->type = JIT_EXPR_CONSTANT_TYPE;
                    ct->v.Type.custom = false;
                    ct->v.Type.val = toks->toks[nd + 1].v.Identifier.val;

                    st.v.func_decl.ret_type->v.constant.val = ct;

                    struct _jit_token_str *body_toks = MALLOC(sizeof(struct _jit_token_str));
                    int bt_count = 0;

                    struct _jit_token_str *tcpy = toks->toks + nd + 2;

                    while ((*tcpy).type == JIT_TOKEN_NEWLINE)
                        tcpy++;

                    _get_stmt_block_body(body_toks, &bt_count, tcpy, toks->tok_count - nd - 3);

                    jit_module_t *dummy = Jit_Parser_Module_New(NULL, NULL, 0);

                    struct _jit_lexer_ctx_str *lex_tk = MALLOC(sizeof(struct _jit_lexer_ctx_str));
                    lex_tk->cpos = 0;
                    lex_tk->raw = "";
                    lex_tk->tok_count = bt_count;
                    lex_tk->tok_limit = bt_count;
                    lex_tk->toks = body_toks;

                    Jit_Parser_Make_AST(dummy, lex_tk);

                    st.v.func_decl.body = dummy->body;
                    st.v.func_decl.body_count = dummy->body_count;

                    _append_stmt_tomod(mod, st);

                    FREE(dummy->meta._macros);
                    FREE(dummy);
                    FREE(lex_tk);
                    FREE(sztok);
                }
            }
        }
        break;

        default:
            break;
        }
    }
}

size_t _parse_args(jit_stmt_t *dest,
                   struct _jit_token_str *toks,
                   int idx)
{
    int gb = 0;

    size_t i;
    for (i = ++idx;; i++)
    {
        if (toks[i].type == JIT_TOKEN_OPERATOR &&
            !strcmp(toks[i].v.Operator.val, ")") &&
            !gb)
            break;

        struct _jit_token_str t = toks[i];

        if (t.type == JIT_TOKEN_OPERATOR &&
            !strcmp(t.v.Operator.val, ","))
            continue;

        if (dest->v.func_decl.arg_count)
            dest->v.func_decl.args = REALLOC(
                dest->v.func_decl.args,
                (dest->v.func_decl.arg_count + 1) *
                    sizeof(struct _jit_expr_str));

        jit_expr_t *exp = Jit_Parser_Empty_Expr_New();
        exp->type = JIT_EXPR_CONSTANT;

        jit_const_t *cnst = Jit_Parser_Empty_Const_New();
        cnst->type = JIT_EXPR_CONSTANT_TYPE;
        cnst->v.Type.custom = false;
        cnst->v.Type.val = t.v.Identifier.val;

        struct _jit_token_str *sz_arr = MALLOC(sizeof(struct _jit_token_str));
        int sz_acount = 0;

        for (size_t j = i + 2;; j++)
        {
            struct _jit_token_str u = toks[j];

            if (u.type == JIT_TOKEN_OPERATOR)
            {
                if (!strcmp(u.v.Operator.val, "("))
                    gb++;
                if ((!strcmp(u.v.Operator.val, ")") ||
                     !strcmp(u.v.Operator.val, ",")) &&
                    !gb)
                {
                    i = j - 1;
                    break;
                }
                if (!strcmp(u.v.Operator.val, ")") && gb)
                    gb--;
            }

            if (sz_acount)
                sz_arr = REALLOC(sz_arr, (sz_acount + 1) * sizeof(struct _jit_token_str));

            sz_arr[sz_acount++] = u;
        }

        size_t fsz = _eval_size(sz_arr, sz_acount);
        exp->size = fsz;
        exp->v.constant.val = cnst;

        dest->v.func_decl.args[dest->v.func_decl.arg_count++] = *exp;

        FREE(sz_arr);
    }

    return i;
}

size_t _eval_size(
    struct _jit_token_str *toks,
    int count)
{
    if (count == 1)
    {
        for (size_t i = 0; DSIZES[i].size; i++)
            if (!strcmp(DSIZES[i].type, (*toks).v.Identifier.val))
                return DSIZES[i].size;
    }

    return DEFAULT_TYPE_SIZE;
}

void _append_stmt_tomod(
    jit_module_t *mod,
    jit_stmt_t st)
{
    if (mod->body_count)
        mod->body = REALLOC(
            mod->body,
            (mod->body_count + 1) * sizeof(jit_stmt_t));

    mod->body[mod->body_count++] = st;
}

void _get_stmt_block_body(
    struct _jit_token_str *st,
    int *stsz_ptr,
    struct _jit_token_str *toks,
    int tok_count)
{
    assert(toks[0].type == JIT_TOKEN_OPERATOR &&
           !strcmp(toks[0].v.Operator.val, "{"));

    int gb = 0;

    for (size_t i = 1; i < tok_count; i++)
    {
        struct _jit_token_str t = toks[i];

        if (t.type == JIT_TOKEN_OPERATOR)
        {
            if (!strcmp(t.v.Operator.val, "{"))
                gb++;
            if (!strcmp(t.v.Operator.val, "}") && !gb)
                break;
            if (!strcmp(t.v.Operator.val, "}") && gb)
                gb--;
        }

        if (*stsz_ptr)
            st = REALLOC(st, ((*stsz_ptr) + 1) * sizeof(struct _jit_token_str));

        st[(*stsz_ptr)++] = t;
    }
}