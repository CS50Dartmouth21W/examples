/*
 * atoi - read an integer from each argument,
 *        and print them to stdout.  catch errors.
 *
 * usage: atoi [integer]...
 *
 * David Kotz, April 2017
 */

#include <stdio.h>
#include <stdlib.h>

int main(const int argc, char *argv[])
{
  int status = 0;

  for (int i = 1; i < argc; i++) {
    int number;         // the number converted from argv[1]
    char excess;        // any excess chars after the number
    
    // if the argument is valid, sscanf should extract exactly one thing.
    if (sscanf(argv[i], "%d%c", &number, &excess) == 1) {
      printf("argument %d: %d\n", i, number);
    } else {
      fprintf(stderr, "argument %d: '%s' is not a valid integer\n", 
	      i, argv[i]);
      status++;
    }
  }

  exit(status);
}
