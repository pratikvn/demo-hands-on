#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

#include <omp.h>


void reduction(int n, const double* val, double* result)
{
    *result = 0.0;
    for (int i = 0; i < n; i++) {
        *result += val[i];
    }
}

void atomic_reduction(int n, const double* val, double* result)
{
    *result = 0.0;
    // get partial sum for each thread
#pragma omp parallel
    {
        double temp = 0.0;
#pragma omp for
        for (int i = 0; i < n; i++) {
            temp += val[i];
        }
        // write the result to global memory
#pragma omp atomic
        *result += temp;
    }
}

void omp_reduction(int n, const double* val, double* result)
{
    *result = 0.0;
    double sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++) {
        sum += val[i];
    }
    *result = sum;
}

void critical_reduction(int n, const double* val, double* result)
{
    *result = 0.0;
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
#pragma omp critical
        *result = *result + val[i];
        // read *result
        // operate *result + val[i]
        // write to *result
    }
}

void task_reduction(int n, const double* val, double* result)
{
    *result = 0;
#pragma omp parallel
    {
#pragma omp single
        {
            for (int i = 0; i < n; i++) {
// input val[i], *result
// output *result
#pragma omp task depend(inout : *result)
                *result += val[i];
            }
        }
    }
}


int main()
{
    int n = 100000;
    std::vector<double> x(n, 1.0);
    double result = 0.0;

    reduction(n, x.data(), &result);
    // verify result = n * 1.0;
    // if you use assert, you should avoid -DNDEBUG in compile
    // cmake -DCMAKE_CXX_FLAGS_RELEASE=-O3 (default is -O3 -DNDEBUG)
    assert(result == n);
    atomic_reduction(n, x.data(), &result);
    // verify result = n * 1.0;
    assert(result == n);
    critical_reduction(n, x.data(), &result);
    // verify result = n * 1.0;
    assert(result == n);
    omp_reduction(n, x.data(), &result);
    // verify result = n * 1.0;
    assert(result == n);
    task_reduction(n, x.data(), &result);
    // verify result = n * 1.0;
    assert(result == n);
    // TODO: Benchmark with different sizes, number of threads and
    // different implementation
    int warmup = 2;
    int rep = 10;
    auto timing = [&](auto f, auto name) {
        for (int i = 0; i < warmup; i++) {
            f(n, x.data(), &result);
        }
        // we mesure all iterations together
        const auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < rep; i++) {
            f(n, x.data(), &result);
        }
        const auto end = std::chrono::steady_clock::now();
        const std::chrono::duration<double> diff = end - start;
        std::cout << name << ": " << diff.count() << " s for " << rep << " run."
                  << std::endl;
    };
    timing(reduction, "seq");
    timing(atomic_reduction, "omp atomic");
    timing(critical_reduction, "omp critical");
    timing(omp_reduction, "omp native");
    timing(task_reduction, "omp task");
}
