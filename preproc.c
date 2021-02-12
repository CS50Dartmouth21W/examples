#include <stdio.h>
#include <math.h>


#define ABS(x) (x<0?-x:x)

int main()
{
    int i=1, j=0, k=-1;

    printf( "i = %d, ABS(i)= %d\n", i, ABS(i));
    printf( "j = %d, ABS(j)= %d\n", j, ABS(j));
    printf( "k = %d, ABS(k)= %d\n", k, ABS(k));


#if 0
    printf( "whatever you do, don't execute this! %f\n", (f/(f-f)));
#endif

    return 0;
}

