/* 
 * guess4.c - a C version of our simple bash demo program guess1
 *  (we move the function to the bottom, so main() stays at top.)
 * David Kotz, March 2019
 */

#include <stdio.h>
#include <stdlib.h>

/* function prototype *declaration*; the function is *defined* below */
int askGuess(const int low, const int high);

/* ***************** main ********************** */
int
main()
{
  const int answer = 31;
  int guess;

  printf("I'm thinking of a number between 1-100.\n");
  guess = askGuess(1, 100);

  while (guess != answer) {
    if (guess > answer) {
      printf("too high!\n");
    } else {
      printf("too low!\n");
    }
    guess = askGuess(1, 100);
  }

  printf("Correct!\n");
  return 0;  // exit status
}


/* ***************** askGuess ********************** */
/*
 * Ask the user to guess, and return the guess.
 *  where [low-high] is the range of numbers in which they should guess.
 */
int
askGuess(const int low, const int high)
{
  int guess;

  printf("Guess my number (between %d and %d): ", low, high);
  scanf("%d", &guess);

  return guess;
}

