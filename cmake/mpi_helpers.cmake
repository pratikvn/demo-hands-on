# SPDX-FileCopyrightText: © 2025 pratik nayak
# SPDX-License-Identifier: MIT

find_package(MPI 3.0 REQUIRED)
find_package(OpenMP 3.0 REQUIRED)

function(add_mpi_executable target_name)
  add_executable("${target_name}" "${target_name}.cpp")
  target_link_libraries(${target_name} PRIVATE MPI::MPI_CXX)
endfunction()

function(add_mpi_omp_executable target_name)
  add_executable("${target_name}" "${target_name}.cpp")
  target_link_libraries(${target_name} PRIVATE MPI::MPI_CXX OpenMP::OpenMP_CXX)
endfunction()
