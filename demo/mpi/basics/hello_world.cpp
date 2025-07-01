// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT

#include <iostream>

#include <mpi.h>

int main(int argc, char* argv[])
{
    int my_rank;
    int size;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the calling process
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Get the total number of ranks (processes)
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print hello only from rank 0.
    if (my_rank == 0) {
        std::cout << "Hello world!\n";
    }

    // Each process prints its own id.
    std::cout << "Hello from process " << my_rank << " out of " << size
              << std::endl;

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
