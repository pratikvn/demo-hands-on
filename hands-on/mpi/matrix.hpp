// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT

#pragma once

template <typename ValueType>
struct Matrix {
    Matrix(int n, ValueType* dataptr)
        : nrows{n}, ncols{n}, stride{n}, data{dataptr}
    {}

    Matrix(int nr, int nc, int str, ValueType* dataptr)
        : nrows{nr}, ncols{nc}, stride{str}, data{dataptr}
    {}

    inline ValueType& at(int row, int col) { return data[row * stride + col]; }

    inline ValueType& at(int row, int col) const
    {
        return data[row * stride + col];
    }

    inline int num_elems() { return nrows * stride; }

    int nrows;
    int ncols;
    int stride;
    ValueType* data;
};
