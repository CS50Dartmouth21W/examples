/* 
 * guess6.c - a C version of our simple bash demo program guess1
 *  (we use readline() to improve input checking)
 * 
 * usage: guess6 [max]
 *  where 'max' is the maximum number of the range for guesses,
 *  and if not supplied, max=100 is the default.
 *
 * David Kotz, March 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "readline.h" // informs C about functions in readline.c file.

/* function prototype *declaration*; the function is *defined* below */
int askGuess(const int low, const int high);
int pickAnswer(const int high);
bool str2int(const char string[], int *number);

/* ***************** main ********************** */
int
main(const int argc, const char *argv[])
{
  int answer; // the secret number to guess
  int guess;  // the user's guess
  int max;    // we'll pick a number in [1..max]

  // interpret arguments
  if (argc == 1) {
    // no arguments (other than the command) - use default value
    max = 100;
  } else if (argc == 2) {
    // one argument - should be the max
    if (!str2int(argv[1], &max) || max < 2 || max > 100) {
      printf("usage: %s [max]; your max is out of range\n", argv[0]);
      exit(1);
    }
  } else {
    // too many arguments
    printf("usage: %s [max]\n", argv[0]);
    exit(2);
  }

  answer = pickAnswer(max);

  printf("I'm thinking of a number between 1-%d.\n", max);
  guess = askGuess(1, max);

  while (guess != 0 && guess != answer) {
    if (guess < 0) {
      printf("invalid number!\n");
    } else if (guess > answer) {
      printf("too high!\n");
    } else {
      printf("too low!\n");
    }
    guess = askGuess(1, max);
  }

  if (guess == answer)
    printf("Correct!\n");
  else
    printf("The answer was %d\n", answer);

  return 0;  // exit status
}

/* ***************** pickAnswer ********************** */
/*
 * Return a random number between 1 and max, inclusive.
 * Assumes high > 0.
 */
int
pickAnswer(const int high)
{
  // seed the random-number sequence using current time
  srand(time(NULL));

  // pick a large random number and map into range [1..high]
  return (rand() % high + 1);
}

/* ***************** askGuess ********************** */
/*
 * Ask the user to guess, and return the guess.
 *  where [low-high] is the range of numbers in which they should guess.
 * Handles many forms of input error.
 */
int
askGuess(const int low, const int high)
{
  const int bufsize = 20;     // the buffer size
  char inputline[bufsize];    // the buffer for user input
  int guess;                  // user's guess

  printf("Guess my number (between %d and %d, or 0 to give up): ", low, high);

  // use readline() to read a whole line, or as much as fits into our buffer
  // if it returns false, the line was too long, or an EOF occurred. 
  if (!readline(inputline, bufsize)) {
    if (feof(stdin)) {    // end of file
      printf("EOF\n");
      return 0;
    } else {      // error in input
      return -1;
    }
  }

  // now they can type 'quit' or '0' to exit.
  if (strcmp(inputline, "quit") == 0) {
    return 0;
  }
  
  if (!str2int(inputline, &guess)) {
    printf("Hey! bad integer.\n");
    return -1;
  }
  
  if (guess == 0) {
    return 0;
  }

  if (guess < 1 || guess > high) {
    printf("Hey! %d is out of range [1..%d].\n", guess, high);
    return -1;
  }

  return guess;
}

/* ***************** str2int ********************** */
/*
 * Convert a string to an integer, returning that integer.
 * Returns true if successful, or false if any error. 
 * It is an error if there is any additional character beyond the integer.
 * Assumes number is a valid pointer.
 */
bool str2int(const char string[], int *number)
{
  // The following is one of my favorite tricks.
  // We use sscanf() to parse a number, expecting there to be no following
  // character ... but if there is, the input is invalid.
  // For example, 1234x will be invalid, as would 12.34 or just x.
  char nextchar;
  return (sscanf(string, "%d%c", number, &nextchar) == 1);
}
