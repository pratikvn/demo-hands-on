// SPDX-FileCopyrightText: © 2025 pratik nayak
// SPDX-License-Identifier: MIT

// This file is part of KaMPIng.
//
// Copyright 2022 The KaMPIng Authors
//
// KaMPIng is free software : you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option) any
// later version. KaMPIng is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with KaMPIng.  If not, see <https://www.gnu.org/licenses/>.

#include "kamping/collectives/alltoall.hpp"

#include <iostream>
#include <numeric>
#include <vector>

#include <mpi.h>

#include "helpers.hpp"
#include "kamping/checking_casts.hpp"
#include "kamping/communicator.hpp"
#include "kamping/data_buffer.hpp"
#include "kamping/environment.hpp"
#include "kamping/named_parameters.hpp"

int main()
{
    using namespace kamping;

    kamping::Environment e;
    Communicator comm;

    std::vector<int> input(2 * comm.size(), comm.rank_signed());
    print_result_on_root(input, comm);
    std::vector<int> output;

    {  // Basic alltoall example. Automatically deduce the send/recv counts and
       // allocate a receive buffer.
        output = comm.alltoall(send_buf(input));
        print_result_on_root(output, comm);
    }
    return 0;
}
