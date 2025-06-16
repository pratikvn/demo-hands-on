#include <omp.h>

#include <stdio.h>


int main()
{
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            printf("hello world\n");


#pragma omp task
            printf("hello again\n");
        }
    }
    return 0;
}
