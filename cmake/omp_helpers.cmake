# SPDX-FileCopyrightText: © 2025 pratik nayak
# SPDX-License-Identifier: MIT

find_package(OpenMP 3.0 REQUIRED)

function(add_omp_executable target_name)
  add_executable("${target_name}" "${target_name}.cpp")
  target_link_libraries(${target_name} PRIVATE OpenMP::OpenMP_CXX)
endfunction()
