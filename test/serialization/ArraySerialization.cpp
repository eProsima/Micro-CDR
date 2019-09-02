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

#include "ArraySerialization.hpp"

INSTANTIATE_TEST_CASE_P(Parametrized, ArraySerialization,
        ::testing::Combine(::testing::Values(0, 11), ::testing::Values(UCDR_BIG_ENDIANNESS, UCDR_LITTLE_ENDIANNESS)));

TEST_P(ArraySerialization, Bool)
{
    bool_array_serialization();
}

TEST_P(ArraySerialization, Char)
{
    char_array_serialization();
}

TEST_P(ArraySerialization, Int8)
{
    int8_t_array_serialization();
}

TEST_P(ArraySerialization, Uint8)
{
    uint8_t_array_serialization();
}

TEST_P(ArraySerialization, Int16)
{
    int16_t_array_serialization();
}

TEST_P(ArraySerialization, Uint16)
{
    uint16_t_array_serialization();
}

TEST_P(ArraySerialization, Int32)
{
    int32_t_array_serialization();
}

TEST_P(ArraySerialization, Uint32)
{
    uint32_t_array_serialization();
}

TEST_P(ArraySerialization, Int64)
{
    int64_t_array_serialization();
}

TEST_P(ArraySerialization, Uint64)
{
    uint64_t_array_serialization();
}

TEST_P(ArraySerialization, Float)
{
    float_array_serialization();
}

TEST_P(ArraySerialization, Double)
{
    double_array_serialization();
}
