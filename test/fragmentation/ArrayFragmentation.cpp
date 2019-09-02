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

#include "../serialization/ArraySerialization.hpp"

#define OFFSET 16

class ArrayFragmentation : public ArraySerialization
{
public:
    ArrayFragmentation()
    {
        std::memset(buffer2, 0, BUFFER_LENGTH);
        ucdr_append_buffer(&writer, buffer2, sizeof(buffer2));
        ucdr_append_buffer(&writer, buffer3, sizeof(buffer3));
        ucdr_append_buffer(&reader, buffer2, sizeof(buffer2));
        ucdr_append_buffer(&reader, buffer3, sizeof(buffer3));
        for(int i = 0; i < BUFFER_LENGTH - OFFSET; ++i)
        {
            uint8_t_serialization();
        }
    }

    ~ArrayFragmentation()
    {
        check_iterator(writer);
        check_iterator(reader);
    }

protected:
    uint8_t buffer2[sizeof(ucdrBufferInfo) + 1];
    uint8_t buffer3[BUFFER_LENGTH];
};

TEST_F(ArrayFragmentation, Bool)
{
    bool_array_serialization();
}

TEST_F(ArrayFragmentation, Char)
{
    char_array_serialization();
}

TEST_F(ArrayFragmentation, Int8)
{
    int8_t_array_serialization();
}

TEST_F(ArrayFragmentation, Uint8)
{
    uint8_t_array_serialization();
}

TEST_F(ArrayFragmentation, Int16)
{
    int16_t_array_serialization();
}

TEST_F(ArrayFragmentation, Uint16)
{
    uint16_t_array_serialization();
}

TEST_F(ArrayFragmentation, Int32)
{
    int32_t_array_serialization();
}

TEST_F(ArrayFragmentation, Uint32)
{
    uint32_t_array_serialization();
}

TEST_F(ArrayFragmentation, Int64)
{
    int64_t_array_serialization();
}

TEST_F(ArrayFragmentation, Uint64)
{
    uint64_t_array_serialization();
}

TEST_F(ArrayFragmentation, Float)
{
    float_array_serialization();
}

TEST_F(ArrayFragmentation, Double)
{
    double_array_serialization();
}
