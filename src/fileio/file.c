#include "file.h"

FILEIO_API pfile_t *
FileIO_New(const char *_Name)
{
    pfile_t *f = MALLOC(sizeof(pfile_t));
    f->fptr = fopen(_Name, "r");
    assert(!!f->fptr);
    f->state = true;

    return f;
}

FILEIO_API pfile_t *
FileIO_New_withMode(const char *_Name, int _Mode)
{
    pfile_t *f = MALLOC(sizeof(pfile_t));
    f->mode = _Mode;
    char md[8];
    int i = 0;

    if (_Mode & FMODE_APPEND)
        md[i++] = 'a';
    if (_Mode & FMODE_BINARY)
        md[i++] = 'b';
    if (_Mode & FMODE_READ)
        if (_Mode & FMODE_WRITE ||
            _Mode & FMODE_APPEND)
            md[i++] = '+';
        else
            md[i++] = 'r';
    if (_Mode & FMODE_WRITE)
        if (_Mode & FMODE_READ)
            md[i++] = '+';
        else
            md[i++] = 'w';

    md[i++] = '\0';
    f->fname = _Name;

    f->fptr = fopen(_Name, md);
    assert(!!f->fptr);

    f->state = true;

    return f;
}

FILEIO_API pfile_t *
FileIO_New_withModeString(
    const char *_Name, const char *_Mode)
{
    pfile_t *f = MALLOC(sizeof(pfile_t));
    // f->fptr = fopen(_Name, _Mode);
    f->fname = _Name;
    assert(!!f->fptr);
    f->state = true;
    int ml = strlen(_Mode);
    f->mode = 0;

    for (size_t i = 0; i < ml; i++)
    {
        switch (_Mode[i])
        {
        case 'r':
        {
            if (!f->mode)
                f->mode = FMODE_READ;
            else
                f->mode |= FMODE_READ;
        }
        break;
        case 'w':
        {
            if (!f->mode)
                f->mode = FMODE_WRITE;
            else
                f->mode |= FMODE_WRITE;
        }
        break;
        case 'a':
        {
            if (!f->mode)
                f->mode = FMODE_APPEND;
            else
                f->mode |= FMODE_APPEND;
        }
        break;
        case 'b':
        {
            if (!f->mode)
                f->mode = FMODE_BINARY;
            else
                f->mode |= FMODE_BINARY;
        }
        break;
        case '+':
        {
            assert(!!f->mode);

            if (f->mode & FMODE_READ)
                f->mode |= FMODE_WRITE;
            else if (f->mode & FMODE_WRITE ||
                     f->mode & FMODE_APPEND)
                f->mode |= FMODE_READ;
        }
        break;

        default:
            break;
        }
    }

    return f;
}

FILEIO_API char *
FileIO_ReadWholeFile(pfile_t *fptr)
{
    assert(fptr->state);
    assert(fptr->mode & FMODE_READ);

    char *res = MALLOC(sizeof(char));
    char r;
    int rlen = 0;

    while ((r = fgetc(fptr->fptr)) != EOF)
    {
        if (rlen)
            res = REALLOC(res, (rlen + 1) * sizeof(char));
        res[rlen++] = r;
    }

    if (rlen)
        res = REALLOC(res, (rlen + 1) * sizeof(char));
    res[rlen++] = '\0';

    return res;
}

FILEIO_API void
FileIO_Write(pfile_t *fptr, const char *text)
{
    assert(fptr->mode & FMODE_WRITE);

    fprintf(fptr->fptr, text);
}

FILEIO_API void
FileIO_Append(pfile_t *fptr, const char *text)
{
    assert(fptr->mode & FMODE_APPEND);

    fprintf(fptr->fptr, text);
}

FILEIO_API void
FileIO_Close(pfile_t *_File)
{
    if (!_File->state)
        return;

    _File->state = false;
    fclose(_File->fptr);
}