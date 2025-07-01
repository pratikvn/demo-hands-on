// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT

#include <iostream>

#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, size;
    int value = 5;
    MPI_Status status;
    MPI_Request request;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        std::cout << "Only allowed to run on two processes\n";
        MPI_Finalize();
        exit(1);
    }
    if (rank == 0) {
        value = 42;
    }

    std::cout << "Before send, Rank: " << rank << ", Value: " << value
              << std::endl;

    if (rank == 1) {
        MPI_Irecv(&value, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &request);
    }
    if (rank == 0) {
        MPI_Send(&value, 1, MPI_INT, 1, 123, MPI_COMM_WORLD);
    }

    if (rank == 1) {
        MPI_Wait(&request, &status);
    }
    std::cout << "Rank: " << rank << ", Value: " << value << std::endl;

    MPI_Finalize();
    return 0;
}
