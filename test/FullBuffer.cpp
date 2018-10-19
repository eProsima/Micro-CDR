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

class FullBuffer : public BasicSerialization
{
public:
    FullBuffer()
    {
    }

    void fill_buffer_except(int gap)
    {
        for(int i = 0; i < BUFFER_LENGTH - gap; ++i)
        {
            uint8_t_serialization();
        }

        writer_it = writer.iterator;
        reader_it = reader.iterator;
    }

    void try_block_1()
    {
        uint8_t input = 0xAA;
        uint8_t output = 0;

        EXPECT_FALSE(ucdr_serialize_uint8_t(&writer, input));
        EXPECT_FALSE(ucdr_deserialize_uint8_t(&reader, &output));
    }

    void try_block_2()
    {
        uint16_t input = 0xAABB;
        uint16_t output = 0;

        EXPECT_FALSE(ucdr_serialize_uint16_t(&writer, input));
        EXPECT_FALSE(ucdr_deserialize_uint16_t(&reader, &output));
    }

    void try_block_4()
    {
        uint32_t input = 0xAABBCCDD;
        uint32_t output = 0;

        EXPECT_FALSE(ucdr_serialize_uint32_t(&writer, input));
        EXPECT_FALSE(ucdr_deserialize_uint32_t(&reader, &output));
    }

    void try_block_8()
    {
        uint64_t input = 0x0123456789ABCDEF;
        uint64_t output = 0;

        EXPECT_FALSE(ucdr_serialize_uint64_t(&writer, input));
        EXPECT_FALSE(ucdr_deserialize_uint64_t(&reader, &output));
    }

    ~FullBuffer()
    {
        EXPECT_EQ(writer_it, writer.iterator);
        EXPECT_EQ(reader_it, reader.iterator);
        EXPECT_TRUE(writer.error);
        EXPECT_TRUE(reader.error);

        // To satisfy the base destructor
        writer.error = false;
        reader.error = false;
    }

private:
    uint8_t* writer_it;
    uint8_t* reader_it;
};

TEST_F(FullBuffer, Block_8)
{
    fill_buffer_except(7);
    try_block_8();
    try_block_1();
}

TEST_F(FullBuffer, Block_4)
{
    fill_buffer_except(3);
    try_block_4();
    try_block_1();
}

TEST_F(FullBuffer, Block_2)
{
    fill_buffer_except(1);
    try_block_2();
    try_block_1();
}

TEST_F(FullBuffer, Block_1)
{
    fill_buffer_except(0);
    try_block_1();
}
