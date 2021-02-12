#include <stdio.h>


int main()
{
  /* :? as an operator */
  int i = 1, j=2, k=3;
  int e;

  printf( "i %c j\n", (i<j?'<':'>'));

  printf( "k %c j\n", (k<j?'<':'>'));

  e = ( (i<j)&(j<k)) ? 0 : 1;

  return ( e);
}
