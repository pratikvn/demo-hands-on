// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT

#include <iostream>
#include <vector>

#include <mpi.h>

#include "helpers.hpp"
#include "kamping/checking_casts.hpp"
#include "kamping/collectives/allgather.hpp"
#include "kamping/communicator.hpp"
#include "kamping/data_buffer.hpp"
#include "kamping/environment.hpp"
#include "kamping/named_parameters.hpp"
#include "matrix.hpp"

void local_matvec(const Matrix<double>* mat, const Matrix<double>* b,
                  Matrix<double>* x)
{
    for (int i = 0; i < mat->nrows; i++) {
        x->at(i, 0) = 0.0;
        for (int j = 0; j < mat->ncols; j++) {
            x->at(i, 0) += mat->at(i, j) * b->at(j, 0);
        }
    }
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

    auto b_gathered = comm.allgather(send_buf(b_data));
    // print_result_on_root(b_gathered, comm);

    auto mat = Matrix<double>(local_n, n, n, mat_data.data());
    auto x = Matrix<double>(local_n, 1, 1, x_data.data());
    auto b = Matrix<double>(n, 1, 1, b_gathered.data());

    local_matvec(&mat, &b, &x);

    std::vector<double> serial_x(local_n, m_val * b_val * n);
    if (verify_result(serial_x, x_data)) {
        std::cout << "Rank: " << comm.rank() << ", Result correct!\n";
    } else {
        std::cout << "Rank: " << comm.rank() << ", Result NOT correct!\n";
    }
}
