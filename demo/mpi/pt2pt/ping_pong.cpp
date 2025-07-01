// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT

#include <iostream>

#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank;
    constexpr int message_size = 1024;
    constexpr int ping = 0;
    constexpr int pong = 1;
    float buffer[message_size];
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Ping: Send message from Rank 0 to 1, and receive same message again
    // (pong) from rank 1.
    if (rank == 0) {
        MPI_Send(buffer, message_size, MPI_FLOAT, 1, ping, MPI_COMM_WORLD);
        MPI_Recv(buffer, message_size, MPI_FLOAT, 1, pong, MPI_COMM_WORLD,
                 &status);
    }
    if (rank == 1) {
        MPI_Recv(buffer, message_size, MPI_FLOAT, 0, ping, MPI_COMM_WORLD,
                 &status);
        MPI_Send(buffer, message_size, MPI_FLOAT, 0, pong, MPI_COMM_WORLD);
    }
    std::cout << "Rank: " << rank << ", Pinged and Ponged." << std::endl;

    MPI_Finalize();
    return 0;
}
