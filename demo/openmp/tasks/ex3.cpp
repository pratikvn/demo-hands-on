#include <omp.h>

#include <stdio.h>


int main()
{
    int x = 0, y = 0;

#pragma omp parallel
    {
        {
#pragma omp task depend(inout : x)
            {
                x = 5;
                printf("hello world:%d\n", x);
            }


#pragma omp task depend(in : x)
            {
                x++;
                printf("hello again:%d\n", x);
            }

#pragma omp task depend(in : y)
            {
                x++;
                printf("hello again:%d\n", y);
            }
        }
    }
    return 0;
}
