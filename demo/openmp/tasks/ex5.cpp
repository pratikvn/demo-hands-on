#include <chrono>
#include <thread>

#include <omp.h>

#include <stdio.h>


int main()
{
    using namespace std::chrono_literals;
    int x = 0, y = 0;

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task depend(in : x)
            {
                int a = x;
                std::this_thread::sleep_for(1000ms);
                printf("hello world:%d\n", a);
            }

#pragma omp task depend(in : x)
            {
                printf("hello world again:%d\n", x);
            }

            // it will need to wait the depend(in: x)
#pragma omp task depend(out : x)
            {
                x++;
                printf("hello again:%d\n", x);
            }
        }
    }
    return 0;
}
