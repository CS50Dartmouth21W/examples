/* 
 * sizeof - demonstrating the difference between sizeof() and strlen()
 * 
 * The sizeof() operator in C returns the size, in bytes, of the type
 * or variable inside the parentheses.  Because C does not have a built-in
 * notion of "strings", sizeof(string) does not return what you expect.
 * In C a string is represented as a char*, i.e., a pointer to the first
 * character of the string.  The sizeof(char*) is just the size of a pointer.
 * If you really want to know the amount of memory needed to store the string,
 * you need to compute its length. Remember that there's a null character 
 * after the string, so the true size of string 's' is strlen(s)+1.
 * 
 * Note that sizeof() and strlen() return a number of type size_t, which is
 * actually an unsigned long int. Thus we must print with %lu format.
 *
 * David Kotz, April 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int i = 42;
  float f = 3.14159;
  char c = 'A';
  char *s = "hello world!";

  printf("i = [%d], size %lu bytes\n", i, sizeof(i));
  printf("f = [%f], size %lu bytes\n", f, sizeof(f));
  printf("c = [%c], size %lu bytes\n", c, sizeof(c));
  printf("s = [%s], size %lu bytes, len %lu chars\n", s, sizeof(s), strlen(s));
  printf("sizeof(s)=%lu, sizeof(char*)=%lu, strlen(s)=%lu\n", 
         sizeof(s), sizeof(char*), strlen(s));
  return 0;
}
