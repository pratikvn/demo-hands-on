#include <iostream>
#include <vector>

#include <omp.h>


void matvec(int n, int nrhs, const double* mat, const double* b, double* x)
{
    
}


int main()
{
    int n = 100;
    int nrhs = 2;
    std::vector<double> mat(n * n, 5.0);
    std::vector<double> b(n * nrhs, 2.0);
    std::vector<double> x(n * nrhs, 0.0);

    matvec(n, nrhs, mat.data(), b.data(), x.data());

    // TODO: Verify result.
    // TODO: Benchmark with different matrix sizes, number of threads and number
    // of rhs
}
