// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT

#include <iostream>
#include <vector>

#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // TODO: Using a ping pong (using MPI_Send and MPI_Recv), measure the
    // bandwidth of a system.
    MPI_Finalize();
}
