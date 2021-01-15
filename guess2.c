/* 
 * guess2.c - a C version of our simple bash demo program guess1
 *  (we guide the user toward an answer.)
 * David Kotz, March 2019
 */

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
    if (guess > answer) {
      printf("too high!\n");
    } else {
      printf("too low!\n");
    }
    printf("Guess my number: ");
    scanf("%d", &guess);
  }

  printf("Correct!\n");
  return 0;  // exit status
}


