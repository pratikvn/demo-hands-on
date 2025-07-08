// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT
//
// This file is part of KaMPI.ng.
//
// Copyright 2022 The KaMPI.ng Authors
//
// KaMPI.ng is free software : you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option) any
// later version. KaMPI.ng is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
// General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with KaMPI.ng.  If not, see <https://www.gnu.org/licenses/>.


#include <iostream>
#include <numeric>
#include <vector>

#include "kamping/collectives/barrier.hpp"
#include "kamping/collectives/bcast.hpp"
#include "kamping/communicator.hpp"
#include "kamping/environment.hpp"
#include "kamping/named_parameters.hpp"

using namespace ::kamping;

template <typename T>
void print_vector(std::vector<T>& vec)
{
    for (auto& i : vec) std::cout << i << ',';
    std::cout << std::endl;
}

int main()
{
    using namespace kamping;

    kamping::Environment e;
    kamping::Communicator comm;

    std::vector<size_t> values;
    values.resize(4);
    std::iota(values.begin(), values.end(), comm.rank());
    if (comm.rank() == 2) {
        std::cout << "Rank: " << comm.rank() << "\n";
        print_vector(values);
    }

    comm.bcast(send_recv_buf(values), send_recv_count(4), root(1));

    if (comm.rank() == 2) {
        std::cout << "After broadcast, rank: " << comm.rank() << "\n";
        print_vector(values);
    }
}
