#include "parser.h"

JIT_API jit_const_t *
Jit_Parser_Const_New(int type, ...)
{
    va_list va;
    va_start(va, type);

    jit_const_t *nc = MALLOC(sizeof(jit_const_t));

    switch (nc->type = type)
    {
    case JIT_EXPR_CONSTANT_FLOAT:
        nc->v.Float.val = va_arg(va, float);
        break;
    case JIT_EXPR_CONSTANT_INT:
        nc->v.Integer.val = va_arg(va, int);
        break;
    case JIT_EXPR_CONSTANT_VARIABLE:
        nc->v.Variable.val = va_arg(va, char *);
        nc->v.Variable.isdtype = va_arg(va, bool);
        break;
    case JIT_EXPR_CONSTANT_STRING:
        nc->v.String.val = va_arg(va, char *);
        break;

    default:
        break;
    }

    va_end(va);

    return nc;
}

JIT_API jit_expr_t *
Jit_Parser_Expr_New(int type, ...)
{
    va_list va;
    va_start(va, type);

    jit_expr_t *ep = MALLOC(sizeof(jit_expr_t));

    switch (ep->type)
    {
    case JIT_EXPR_CONSTANT:
        ep->v.constant.val = va_arg(va, jit_const_t *);
        break;
    case JIT_EXPR_FUNC_CALL:
        ep->v.func_call.name = va_arg(va, jit_const_t *);
        ep->v.func_call.args = va_arg(va, jit_const_t *);
        ep->v.func_call.arg_count = va_arg(va, int);
        break;

    default:
        break;
    }

    va_end(va);

    return ep;
}

JIT_API jit_stmt_t *
Jit_Parser_Stmt_New(int type, ...)
{
    va_list va;
    va_start(va, type);

    jit_stmt_t *st = MALLOC(sizeof(jit_stmt_t));

    switch (st->type = type)
    {
    case JIT_STMT_RETURN:
        st->v.ret_stmt.expr = va_arg(va, jit_expr_t *);
        break;
    case JIT_STMT_FUN_DECL:
        st->v.func_decl.name = va_arg(va, char *);
        st->v.func_decl.args = va_arg(va, jit_expr_t *);
        st->v.func_decl.ret_type = va_arg(va, jit_expr_t *);
        st->v.func_decl.body = va_arg(va, jit_stmt_t *);
        st->v.func_decl.arg_count = va_arg(va, int);
        st->v.func_decl.body = va_arg(va, int);
        break;

    default:
        break;
    }

    va_end(va);
    return st;
}

JIT_API jit_const_t *
Jit_Parser_Empty_Const_New(void)
{
    jit_const_t *ct = MALLOC(sizeof(jit_const_t));
    return ct;
}

JIT_API jit_expr_t *
Jit_Parser_Empty_Expr_New(void)
{
    jit_expr_t *exp = MALLOC(sizeof(jit_expr_t));
    return exp;
}

JIT_API jit_stmt_t *
Jit_Parser_Empty_Stmt_New(void)
{
    jit_stmt_t *st = MALLOC(sizeof(jit_stmt_t));
    return st;
}

JIT_API jit_module_t *
Jit_Parser_Module_New(
    char *name,
    jit_stmt_t *body,
    int body_count)
{
    jit_module_t *md = MALLOC(sizeof(jit_module_t));
    md->name = name;
    md->body = !!body ? body: MALLOC(sizeof(jit_stmt_t));
    md->body_count = body_count;
    md->emt = Emit_Emitter_New(name, "main");
    
    emit_file_top(md->emt);

    md->meta._pragma._once = false;
    md->meta._macros = MALLOC(sizeof(md->meta._st_sz1));
    md->meta.macro_count = 0;

    return md;
}

JIT_API int 
Jit_Parser_ParseAST(jit_module_t *mod)
{
    for (size_t i = 0; i < mod->body_count; i++)
    {
        jit_stmt_t st = mod->body[i];

        switch (st.type)
        {
        case JIT_STMT_FUN_DECL:
        {
            emit_label_instruction(mod->emt, st.v.func_decl.name);
            jit_stmt_t *pres = mod->body;
            int pc = mod->body_count;

            mod->body = st.v.func_decl.body;
            mod->body_count = st.v.func_decl.body_count;

            Jit_Parser_ParseAST(mod);

            mod->body = pres;
            mod->body_count = pc;
        }
            break;
        
        default:
            break;
        }
    }

    return 0;
}