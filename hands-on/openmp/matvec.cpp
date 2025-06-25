#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

#include <omp.h>


void matvec(int n, int nrhs, const double* mat, const double* b, double* x)
{
    for (int i = 0; i < n * nrhs; i++) {
        x[i] = 0.0;
    }
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            for (int r = 0; r < nrhs; r++) {
                // x(row, r) += mat(row, col) * b(col, r)
                x[row * nrhs + r] += mat[row * n + col] * b[col * nrhs + r];
            }
        }
    }
}


void par_matvec(int n, int nrhs, const double* mat, const double* b, double* x)
{
#pragma omp parallel for
    for (int i = 0; i < n * nrhs; i++) {
        x[i] = 0.0;
    }

#pragma omp parallel for
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            for (int r = 0; r < nrhs; r++) {
                x[row * nrhs + r] += mat[row * n + col] * b[col * nrhs + r];
            }
        }
    }
}

int main()
{
    int n = 10000;
    int nrhs = 2;
    std::vector<double> mat(n * n, 5.0);
    std::vector<double> b(n * nrhs, 2.0);
    std::vector<double> x(n * nrhs, 0.0);

    matvec(n, nrhs, mat.data(), b.data(), x.data());
    for (const auto& val : x) {
        assert(val == n * 10);
    }

    par_matvec(n, nrhs, mat.data(), b.data(), x.data());
    // we do tricky check here.
    // it does not work for random generation
    for (const auto& val : x) {
        assert(val == n * 10);
    }
    // TODO: Benchmark with different matrix sizes, number of threads and number
    // of rhs

    int warmup = 2;
    int rep = 10;
    {
        for (int i = 0; i < warmup; i++) {
            matvec(n, nrhs, mat.data(), b.data(), x.data());
        }
        const auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < rep; i++) {
            matvec(n, nrhs, mat.data(), b.data(), x.data());
        }
        const auto end = std::chrono::steady_clock::now();
        const std::chrono::duration<double> diff = end - start;
        std::cout << "seq: " << diff.count() << " s." << std::endl;
    }

    {
        for (int i = 0; i < warmup; i++) {
            par_matvec(n, nrhs, mat.data(), b.data(), x.data());
        }
        const auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < rep; i++) {
            par_matvec(n, nrhs, mat.data(), b.data(), x.data());
        }
        const auto end = std::chrono::steady_clock::now();
        const std::chrono::duration<double> diff = end - start;
        std::cout << "par: " << diff.count() << " s." << std::endl;
    }
}
