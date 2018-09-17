// Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "serialization/BasicSerialization.hpp"

class Alignment : public BasicSerialization,
                  public ::testing::WithParamInterface<int>
{
public:

    Alignment()
    {
        for(int i = 0; i < GetParam(); ++i)
        {
            uint8_t_serialization();
        }
    }

    void check_alignment(int alignment)
    {
        EXPECT_EQ(static_cast<int>(micro_buffer_length(&writer)) % alignment, 0);
        EXPECT_EQ(static_cast<int>(micro_buffer_length(&reader)) % alignment, 0);
    }

    virtual ~Alignment()
    {
    }
};

INSTANTIATE_TEST_CASE_P(Offset_0_to_16, Alignment, ::testing::Range(0, 17), ::testing::PrintToStringParamName());

TEST_P(Alignment, Block_8)
{
    uint64_t_serialization();
    check_alignment(8);
}

TEST_P(Alignment, Block_4)
{
    uint32_t_serialization();
    check_alignment(4);
}

TEST_P(Alignment, Block_2)
{
    uint16_t_serialization();
    check_alignment(2);
}

TEST_P(Alignment, Block_1)
{
    uint8_t_serialization();
    check_alignment(1);
}
