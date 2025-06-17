#include <iostream>
#include <vector>

#include <omp.h>


void reduction(int n, const double* val, double* result) {}


int main()
{
    int n = 100;
    std::vector<double> x(n, 1.0);
    double result = 0.0;

    reduction(n, x.data(), &result);

    // TODO: Verify result.
    // TODO: Benchmark with different matrix sizes, number of threads and
    // different implementation
}
