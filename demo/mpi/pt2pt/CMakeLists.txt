# SPDX-FileCopyrightText: © 2025 pratik nayak
# SPDX-License-Identifier: MIT

include(${PROJECT_SOURCE_DIR}/cmake/mpi_helpers.cmake)

add_mpi_executable(send_recv)
add_mpi_executable(ping_pong)
add_mpi_executable(non_blocking_recv)
