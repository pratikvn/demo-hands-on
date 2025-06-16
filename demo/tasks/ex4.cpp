#include <omp.h>

#include <stdio.h>


int main()
{
    int x = 0, y = 0;

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task depend(inout : x)
            {
                x = 5;
                printf("hello world:%d\n", x);
            }

#pragma omp task depend(inout : y)
            {
                y = 7;
                printf("hello also here:%d\n", y);
            }

#pragma omp task depend(in : x)
            {
                x++;
                printf("hello again:%d\n", x);
            }
        }
    }
    return 0;
}
