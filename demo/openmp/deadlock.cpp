#include <iostream>
#include <thread>
#include <chrono>

#include <omp.h>

int main()
{
    using namespace std::chrono_literals;
    int x = 0;
    int y = 0;
    // the following gives a deadlock example
    // one is waiting for x == 1, and then assign 1 to y
    // the other is waiting for y == 1, and then assign 1 to x
#pragma omp parallel
#pragma omp sections
    {
        #pragma omp section
        {
            while (x != 1) {
                // just reduce the checking frequency
                std::this_thread::sleep_for(500ms);
                std::cout << "waiting for x == 1" << std::endl;
            }
            y = 1;
        }

        #pragma omp section
        {
            while (y != 1) {
                // just reduce the checking frequency
                std::this_thread::sleep_for(500ms);
                std::cout << "waiting for y == 1" << std::endl;
            }
            x = 1;
        }
    }
}
