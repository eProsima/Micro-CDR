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

#include "../serialization/BasicSerialization.hpp"

class BasicFragmentation : public BasicSerialization
{
public:
    BasicFragmentation()
    {
        std::memset(buffer2, 0, BUFFER_LENGTH);
        ucdr_append_buffer(&writer, buffer2, BUFFER_LENGTH);
        ucdr_append_buffer(&reader, buffer2, BUFFER_LENGTH);
        for(int i = 0; i < BUFFER_LENGTH - int(sizeof(ucdrBufferInfo) + 1); ++i)
        {
            uint8_t_serialization();
        }
    }

protected:
    uint8_t buffer2[BUFFER_LENGTH];
};

TEST_F(BasicFragmentation, Bool)
{
    bool_serialization();
}

TEST_F(BasicFragmentation, Char)
{
    char_serialization();
}

TEST_F(BasicFragmentation, Int8)
{
    int8_t_serialization();
}

TEST_F(BasicFragmentation, Uint8)
{
    uint8_t_serialization();
}

TEST_F(BasicFragmentation, Int16)
{
    int16_t_serialization();
}

TEST_F(BasicFragmentation, Uint16)
{
    uint16_t_serialization();
}

TEST_F(BasicFragmentation, Int32)
{
    int32_t_serialization();
}

TEST_F(BasicFragmentation, Uint32)
{
    uint32_t_serialization();
}

TEST_F(BasicFragmentation, Int64)
{
    int64_t_serialization();
}

TEST_F(BasicFragmentation, Uint64)
{
    uint64_t_serialization();
}

TEST_F(BasicFragmentation, Float)
{
    float_serialization();
}

TEST_F(BasicFragmentation, Double)
{
    double_serialization();
}

