# SPDX-FileCopyrightText: © 2025 pratik nayak
# SPDX-License-Identifier: MIT

add_subdirectory(basics)
add_subdirectory(tasks)


include(${PROJECT_SOURCE_DIR}/cmake/omp_helpers.cmake)

add_omp_executable(deadlock)
