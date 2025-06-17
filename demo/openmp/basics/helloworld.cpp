// SPDX - FileCopyrightText : © 2025 pratik nayak
// SPDX - License - Identifier : MIT

#include <iostream>

#include <omp.h>

int main()
{
#pragma omp parallel num_threads(5)
    {
        int ID = 0;
        ID = omp_get_thread_num();
        std::cout << "Hello from: " << ID << std::endl;
    }
}
