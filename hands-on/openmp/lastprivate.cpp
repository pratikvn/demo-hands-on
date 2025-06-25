#include <iostream>
#include <omp.h>

int main() {
    int x = 0;
    #pragma omp parallel for lastprivate(x)
    for (int i = 0; i < 15; i++) {
        x = i;
    }
    std::cout << x << std::endl;

    #pragma omp parallel sections lastprivate(x)
    {
        #pragma omp section 
        x = 1;
        
        #pragma omp section
        x = 2;

        #pragma omp section
        x = 4;
    }
    std::cout << x << std::endl;
}