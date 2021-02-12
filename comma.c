#include <stdio.h>
#include <math.h>

int main()
{
  /* comma as an operator */
  int n = (5, 10); /* 10 is assigned to n*/

  double f = (sqrt(4.0), sqrt(9.0));   /* sqrt(4) is called (evaluated) first */
                                       /* followed by sqrt(9). */
                                       /* The returned value of sqrt(9) is then */
                                       /* assigned to f */

  printf( "f = %f, n = %d\n", f, n);

  return 0;
}
