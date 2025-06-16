# SPDX-FileCopyrightText: © 2025 pratik nayak
# SPDX-License-Identifier: MIT

find_package(OpenMP 3.0 REQUIRED)
find_package(Threads REQUIRED)

function(add_omp_executable target_name)
  add_executable("${target_name}" "${target_name}.cpp")
  target_link_libraries(${target_name} PUBLIC Threads::Threads)
  target_link_libraries(${target_name} PRIVATE "${OpenMP_CXX_LIBRARIES}")
  target_include_directories(${target_name} PRIVATE "${OpenMP_CXX_INCLUDE_DIRS}")
  # We first separate the arguments, otherwise, the target_compile_options adds it as a string
  # and the compiler is unhappy with the quotation marks.
  separate_arguments(OpenMP_SEP_FLAGS NATIVE_COMMAND "${OpenMP_CXX_FLAGS}")
  target_compile_options(${target_name} PRIVATE "${OpenMP_SEP_FLAGS}")
endfunction()
