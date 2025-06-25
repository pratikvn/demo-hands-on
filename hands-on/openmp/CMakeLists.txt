# SPDX-FileCopyrightText: © 2025 pratik nayak
# SPDX-License-Identifier: MIT

include(${PROJECT_SOURCE_DIR}/cmake/omp_helpers.cmake)

add_omp_executable(matvec)
add_omp_executable(reduction)
add_omp_executable(lastprivate)
