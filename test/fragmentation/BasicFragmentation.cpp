// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include "../serialization/BasicSerialization.hpp"
#include <c/common_internal.h>

class BasicFragmentation : public BasicSerialization
{
public:
    BasicFragmentation()
    {
        std::memset(buffer2, 0, sizeof(buffer2));
        std::memset(buffer3, 0, sizeof(buffer3));
        std::memset(buffer4, 0, sizeof(buffer4));
        std::memset(buffer5, 0, sizeof(buffer5));

        ucdr_append_buffer(&writer, buffer2, sizeof(buffer2));
        ucdr_append_buffer(&writer, buffer3, sizeof(buffer3));
        ucdr_append_buffer(&writer, buffer4, sizeof(buffer4));
        ucdr_append_buffer(&writer, buffer5, sizeof(buffer5));

        ucdr_append_buffer(&reader, buffer2, sizeof(buffer2));
        ucdr_append_buffer(&reader, buffer3, sizeof(buffer3));
        ucdr_append_buffer(&reader, buffer4, sizeof(buffer4));
        ucdr_append_buffer(&reader, buffer5, sizeof(buffer5));

        for(int i = 0; i < BUFFER_LENGTH - int(sizeof(ucdrBufferInfo)); ++i)
        {
            uint8_t_serialization();
        }
    }

    ~BasicFragmentation()
    {
        check_iterator(writer);
        check_iterator(reader);
    }

protected:
    uint8_t buffer2[sizeof(ucdrBufferInfo)];
    uint8_t buffer3[sizeof(ucdrBufferInfo) + 1];
    uint8_t buffer4[sizeof(ucdrBufferInfo) + 2];
    uint8_t buffer5[BUFFER_LENGTH];
};

INSTANTIATE_TEST_CASE_P(Parametrized, BasicFragmentation,
        ::testing::Combine(::testing::Values(0, 11), ::testing::Values(UCDR_BIG_ENDIANNESS, UCDR_LITTLE_ENDIANNESS)));

TEST_P(BasicFragmentation, Bool)
{
    bool_serialization();
}

TEST_P(BasicFragmentation, Char)
{
    char_serialization();
}

TEST_P(BasicFragmentation, Int8)
{
    int8_t_serialization();
}

TEST_P(BasicFragmentation, Uint8)
{
    uint8_t_serialization();
}

TEST_P(BasicFragmentation, Int16)
{
    int16_t_serialization();
}

TEST_P(BasicFragmentation, Uint16)
{
    uint16_t_serialization();
}

TEST_P(BasicFragmentation, Int32)
{
    int32_t_serialization();
}

TEST_P(BasicFragmentation, Uint32)
{
    uint32_t_serialization();
}

TEST_P(BasicFragmentation, Int64)
{
    int64_t_serialization();
}

TEST_P(BasicFragmentation, Uint64)
{
    uint64_t_serialization();
}

TEST_P(BasicFragmentation, Float)
{
    float_serialization();
}

TEST_P(BasicFragmentation, Double)
{
    double_serialization();
}

