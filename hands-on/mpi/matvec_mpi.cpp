
// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT

#include <iostream>
#include <vector>

#include <mpi.h>

// TODO: Include necessary headers

#include "matrix.hpp"

void local_matvec(const Matrix<double>* mat, const Matrix<double>* b,
                  Matrix<double>* x)
{
    // TODO: Implement local matrix vector product
}

bool verify_result(const std::vector<double>& x1, const std::vector<double>& x2)
{
    if (x1.size() != x2.size()) {
        return false;
    }
    for (int i = 0; i < x1.size(); i++) {
        if (x1[i] != x2[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    using namespace kamping;

    kamping::Environment e;
    Communicator comm;

    int n = 10 * comm.size();

    int local_n = n / comm.size();
    constexpr double m_val = 10.0;
    constexpr double b_val = 4.0;

    std::vector<double> mat_data(local_n * n, m_val);
    std::vector<double> x_data(local_n, 3.0);
    std::vector<double> b_data(local_n, b_val);

    // Distribute data by rows, for example, if n=10 and you have 5
    // ranks, then each row performs a mat vec for 2 rows.

    // TODO: What needs to be communicated? And what does each rank need to
    // compute?

    std::vector<double> serial_x(local_n, m_val * b_val * n);
    if (verify_result(serial_x, x_data)) {
        std::cout << "Rank: " << comm.rank() << ", Result correct!\n";
    } else {
        std::cout << "Rank: " << comm.rank() << ", Result NOT correct!\n";
    }
}
