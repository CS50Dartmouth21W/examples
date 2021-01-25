/* 
 * freadline.h - a utility function to safely read one line of input
 * Safely read a line of input into `buf` (with room for `len` chars).
 *
 * David Kotz, April 2016, 2017, 2019
 */

#ifndef __FREADLINE_H__
#define __FREADLINE_H__

#include <stdio.h>
#include <stdbool.h>

/* freadline - Safely read a line of file into `buf`.
 * 
 * We assume:
 *   Caller provides valid buffer `buf` with room for `len>0` characters.
 *   Caller provides open file `fp`.
 * We return
 *   `buf` filled with reading characters from file `fp` until newline or EOF.
 * We guarantee:
 *   we won't over-run the end of the buffer;
 *   null-terminated string in the buffer;
 *   no newline in the buffer.
 * We return:
 *   true if success and false if EOF or any error.
 * Notes:
 *   If the user enters more than len-1 characters, that is considered an error.
 *   If end-of-file is reached before newline, that is considered an error.
 *   If an error occurs, buf may have been written but should be untrusted.
 */
extern bool freadline(FILE *fp, char *buf, const int len);

#endif //  __FREADLINE_H__
