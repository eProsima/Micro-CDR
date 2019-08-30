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
#include <c/common_internal.h>

void check_iterator(ucdrStream& us)
{
    ucdrBufferInfo binfo = us.buffer_info;
    while (ucdr_prev_buffer_info(&binfo))
    {}

    uint8_t* iterator = binfo.data;
    size_t remainding_size = us.offset;
    do
    {
        if (remainding_size <= binfo.size)
        {
            iterator += remainding_size;
            remainding_size = 0;
        }
        else
        {
            ucdr_next_buffer_info(&binfo);
            iterator = binfo.data;
            remainding_size -= binfo.size;
        }

    } while(remainding_size > 0);

    EXPECT_EQ(us.iterator, iterator);
}

class BasicFragmentation : public BasicSerialization
{
public:
    BasicFragmentation()
    {
        std::memset(buffer2, 0, BUFFER_LENGTH);
        ucdr_append_buffer(&writer, buffer2, sizeof(buffer2));
        ucdr_append_buffer(&writer, buffer3, sizeof(buffer3));
        ucdr_append_buffer(&reader, buffer2, sizeof(buffer2));
        ucdr_append_buffer(&reader, buffer3, sizeof(buffer3));
        for(int i = 0; i < BUFFER_LENGTH - int(sizeof(ucdrBufferInfo) + 1); ++i)
        {
            uint8_t_serialization();
        }
    }

protected:
    uint8_t buffer2[sizeof(ucdrBufferInfo) + 1];
    uint8_t buffer3[BUFFER_LENGTH];
};

TEST_F(BasicFragmentation, Bool)
{
    bool_serialization();
    check_iterator(writer);
    check_iterator(reader);
}

TEST_F(BasicFragmentation, Char)
{
    char_serialization();
    check_iterator(writer);
    check_iterator(reader);
}

TEST_F(BasicFragmentation, Int8)
{
    int8_t_serialization();
    check_iterator(writer);
    check_iterator(reader);
}

TEST_F(BasicFragmentation, Uint8)
{
    uint8_t_serialization();
    check_iterator(writer);
    check_iterator(reader);
}

TEST_F(BasicFragmentation, Int16)
{
    int16_t_serialization();
    check_iterator(writer);
    check_iterator(reader);
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

