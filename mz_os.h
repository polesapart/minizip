/* mz_os.h -- System functions
   Version 2.7.5, November 13, 2018
   part of the MiniZip project

   Copyright (C) 2010-2018 Nathan Moinvaziri
     https://github.com/nmoinvaz/minizip

   This program is distributed under the terms of the same license as zlib.
   See the accompanying LICENSE file for the full text of the license.
*/

#ifndef MZ_OS_H
#define MZ_OS_H

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/

#if defined(__APPLE__)
#define MZ_VERSION_MADEBY_HOST_SYSTEM (MZ_HOST_SYSTEM_OSX_DARWIN)
#elif defined(unix)
#define MZ_VERSION_MADEBY_HOST_SYSTEM (MZ_HOST_SYSTEM_UNIX)
#elif defined(_WIN32)
#define MZ_VERSION_MADEBY_HOST_SYSTEM (MZ_HOST_SYSTEM_WINDOWS_NTFS)
#endif

#ifdef HAVE_LZMA
#define MZ_VERSION_MADEBY_ZIP_VERSION (63)
#elif HAVE_AES
#define MZ_VERSION_MADEBY_ZIP_VERSION (51)
#elif HAVE_BZIP2
#define MZ_VERSION_MADEBY_ZIP_VERSION (46)
#else
#define MZ_VERSION_MADEBY_ZIP_VERSION (45)
#endif

#define MZ_VERSION_MADEBY             ((MZ_VERSION_MADEBY_HOST_SYSTEM << 8) | \
                                       (MZ_VERSION_MADEBY_ZIP_VERSION))

/***************************************************************************/

#if defined(_WIN32)
struct dirent {
    char d_name[256];
};
typedef void* DIR;
#else
#include <dirent.h>
#endif

/***************************************************************************/
// Shared functions

int32_t mz_path_combine(char *path, const char *join, int32_t max_path);
// Combines two paths

int32_t mz_path_compare_wc(const char *path, const char *wildcard, uint8_t ignore_case);
// Compare two paths with wildcard

int32_t mz_path_resolve(const char *path, char *target, int32_t max_target);
// Resolves path

int32_t mz_path_remove_filename(char *path);
// Remove the filename from a path

int32_t mz_path_get_filename(const char *path, const char **filename);
// Get the filename from a path

int32_t mz_dir_make(const char *path);
// Creates a directory recursively

int32_t mz_file_get_crc(const char *path, uint32_t *result_crc);
// Gets the crc32 hash of a file

/***************************************************************************/
// Platform specific functions

wchar_t *mz_os_unicode_string_create(const char *string, int32_t encoding);
// Create unicode string from a utf8 string

void     mz_os_unicode_string_delete(wchar_t **string);
// Delete a unicode string that was created

uint8_t *mz_os_utf8_string_create(const char *string, int32_t encoding);
// Create a utf8 string from a string with another encoding

void     mz_os_utf8_string_delete(uint8_t **string);
// Delete a utf8 string that was created

int32_t  mz_os_rand(uint8_t *buf, int32_t size);
// Random number generator (not cryptographically secure)

int32_t  mz_os_rename(const char *source_path, const char *target_path);
// Rename a file

int32_t  mz_os_delete(const char *path);
// Delete an existing file 

int32_t  mz_os_file_exists(const char *path);
// Check to see if a file exists

int64_t  mz_os_get_file_size(const char *path);
// Gets the length of a file

int32_t  mz_os_get_file_date(const char *path, time_t *modified_date, time_t *accessed_date, time_t *creation_date);
// Gets a file's modified, access, and creation dates if supported

int32_t  mz_os_set_file_date(const char *path, time_t modified_date, time_t accessed_date, time_t creation_date);
// Sets a file's modified, access, and creation dates if supported

int32_t  mz_os_get_file_attribs(const char *path, uint32_t *attributes);
// Gets a file's attributes

int32_t  mz_os_set_file_attribs(const char *path, uint32_t attributes);
// Sets a file's attributes

int32_t  mz_os_make_dir(const char *path);
// Recursively creates a directory

DIR*     mz_os_open_dir(const char *path);
// Opens a directory for listing
struct
dirent*  mz_os_read_dir(DIR *dir);
// Reads a directory listing entry

int32_t  mz_os_close_dir(DIR *dir);
// Closes a directory that has been opened for listing

int32_t  mz_os_is_dir(const char *path);
// Checks to see if path is a directory

uint64_t mz_os_ms_time(void);
// Gets the time in milliseconds

/***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
