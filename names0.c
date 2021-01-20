/* 
 * names0.c - read in a list of names from stdin
 *   (two-dimensional array; each row is still a pointer)
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: numbered list of names, one per line
 * 
 * David Kotz, April 2016, 2017, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* function prototypes */
bool readline(char *buf, const int len);

/* ***************** main ********************** */
int
main()
{
  const int maxNames = 100;  // maximum number of names
  const int maxLength = 50;  // maximum length of a name (minus 2)
  char names[maxNames][maxLength];
  int n = 0;         // number of names read

  // read the list of names
  for (n = 0; n < maxNames && !feof(stdin); ) {
    if (readline(names[n], maxLength)) {
      n++; // only increment if no error
    }
  }

  printf("%d names\n", n);
  // print the list of names
  for (int i = 0; i < n; i++) {
    printf("%d: %s\n", i, names[i]);
  }
}

/* ***************** readline ********************** */
/* readline - Safely read a line of stdin into `buf`.
 * 
 * We assume:
 *   Caller provides valid buffer `buf` with room for `len>0` characters.
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
bool 
readline(char *buf, const int len) 
{
  int pos = 0;          // where in the buffer do we place next char?

  // fill the buffer from stdin until buf is full, until EOF, or until newline
  while ( !feof(stdin) && pos < len-1 ) {
    // read and store a character
    char c = getchar();
    if (c == '\n') {
      // end of line: terminate buf and return
      buf[pos++] = '\0';
      return true;
    } else {
      // add char to the buffer
      buf[pos++] = c;
    }
  }
  // terminate buffer
  buf[pos++] = '\0';

  // error: file ended or buffer filled before newline discovered.

  // strip characters until end of file or newline is finally reached
  while ( !feof(stdin) && getchar() != '\n' ) {
    ; // discard the rest of characters on input line
  }

  return false;
}
