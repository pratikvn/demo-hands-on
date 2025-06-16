// SPDX - FileCopyrightText : © 2025 pratik nayak
// SPDX - License - Identifier : MIT

#include <iostream>

#include <omp.h>

int main()
{
    int Z = 0;
    omp_set_num_threads(5);
#pragma omp parallel private(Z)
    {
        int ID = 0;
        Z = 0;
        ID = omp_get_thread_num();
        Z = Z + ID;
        std::cout << "Hello from: " << ID << ": " << Z << std::endl;
    }
}
