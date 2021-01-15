/* 
 * guess1.c - a C version of our simple bash demo program guess1
 *  (simple replacement for the bash program)
 * David Kotz, March 2019
 */

// This is a one-line comment; modern syntax
/* This is another one-line comment; traditional syntax */

#include <stdio.h>
#include <stdlib.h>

int
main()
{
  const int answer = 31;
  int guess;

  printf("I'm thinking of a number between 1-100.\n");
  printf("Guess my number: ");
  scanf("%d", &guess);

  while (guess != answer) {
    printf("Wrong! try again\n");
    printf("Guess my number: ");
    scanf("%d", &guess);
  }

  printf("Correct!\n");
  return 0;  // exit status
}


