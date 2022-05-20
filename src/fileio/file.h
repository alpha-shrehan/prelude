#pragma once

#include "Header.h"
#include "../memory/pmemory.h"

/**
 * @brief File structure for fileio API.
 * @param fptr File pointer.
 * @param state State of file.
 */
struct _fl_str
{
    const char *fname;
    FILE *fptr;
    bool state;
    int mode;
};

enum _FileModeEnum
{
    FMODE_READ = 1 << 1,
    FMODE_WRITE = 1 << 2,
    FMODE_APPEND = 1 << 3,
    FMODE_BINARY = 1 << 4
};

typedef struct _fl_str pfile_t;

#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     * @brief Creates a new file object.
     * Default mode is read.
     * @param _Name Name of file
     * @return FILEIO_API*
     */
    FILEIO_API pfile_t *FileIO_New(const char *);

    /**
     * @brief Creates a new file object with custom modes.
     * @param _Name name of file.
     * @param _Mode Mode of file.
     * @return FILEIO_API* 
     */
    FILEIO_API pfile_t *FileIO_New_withMode(const char *, int);

    /**
     * @brief Creates a new file object with custom mode as string.
     * @param _Name name of file.
     * @param _Mode Mode of file.
     * @return FILEIO_API* 
     */
    FILEIO_API pfile_t *FileIO_New_withModeString(const char *, const char *);

    /**
     * @brief Read whole file and return as dynamic pointer.
     * @param fptr File pointer
     * @return FILEIO_API* 
     */
    FILEIO_API char *FileIO_ReadWholeFile(pfile_t *);

    /**
     * @brief Write to file
     * @param fptr File pointer
     * @param text Text to write
     * @return FILEIO_API* 
     */
    FILEIO_API void FileIO_Write(pfile_t *, const char *);

    /**
     * @brief Append to file
     * @param fptr File pointer
     * @param text Text to write
     * @return FILEIO_API* 
     */
    FILEIO_API void FileIO_Append(pfile_t *, const char *);

    /**
     * @brief Close a filestream.
     * @param _File file object.
     * @return FILEIO_API
     */
    FILEIO_API void FileIO_Close(pfile_t *);

#if defined(__cplusplus)
}
#endif
