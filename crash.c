/* 
 * crash.c - a program that dereferences NULL and dumps core.
 * 
 * David Kotz, April 2019
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int *x = NULL;

  *x = 42;

  return 0;
}
