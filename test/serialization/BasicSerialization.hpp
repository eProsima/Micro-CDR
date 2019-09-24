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

#ifndef BASIC_SERIALIZATION_HPP_
#define BASIC_SERIALIZATION_HPP_

#include <gtest/gtest.h>

#include <ucdr/microcdr.h>
#include <c/common_internal.h>

#include <algorithm>
#include <cstring>

#define BUFFER_LENGTH 1024

inline void check_iterator(ucdrStream& us)
{
    ucdrBufferInfo binfo;
    if (NULL == us.initial_buffer_info)
    {
        binfo = us.buffer_info;
    }
    else
    {
        memcpy(&binfo, us.initial_buffer_info, sizeof(ucdrBufferInfo));
    }

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
            remainding_size -= binfo.size;
            ucdr_next_buffer_info(&binfo);
            iterator = binfo.data;
        }

    } while(remainding_size > 0);

    EXPECT_EQ(us.iterator, iterator);
}

class BasicSerialization : public ::testing::TestWithParam<std::tuple<size_t, ucdrEndianness>>
{
public:

    BasicSerialization()
    {
        std::memset(buffer, 0, sizeof(buffer));
        ucdr_init_stream_offset_endian(&writer, buffer, sizeof(buffer), std::get<0>(GetParam()), std::get<1>(GetParam()));
        ucdr_init_stream_offset_endian(&reader, buffer, sizeof(buffer), std::get<0>(GetParam()), std::get<1>(GetParam()));
    }

    virtual ~BasicSerialization()
    {
        EXPECT_EQ(writer.iterator, reader.iterator);
        EXPECT_FALSE(writer.error);
        EXPECT_FALSE(reader.error);
    }

    void bool_serialization()
    {
        bool input = true;
        bool output = 0;

        EXPECT_TRUE(ucdr_serialize_bool(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_bool(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void char_serialization()
    {
        char input = 'A';
        char output = 0;

        EXPECT_TRUE(ucdr_serialize_char(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_char(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void int8_t_serialization()
    {
        int8_t input = 0x09;
        int8_t output = 0;

        EXPECT_TRUE(ucdr_serialize_int8_t(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_int8_t(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void uint8_t_serialization()
    {
        uint8_t input = 0x09;
        uint8_t output = 0;

        EXPECT_TRUE(ucdr_serialize_uint8_t(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_uint8_t(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void int16_t_serialization()
    {
        int16_t input = 0x0A0B;
        int16_t output = 0;

        EXPECT_TRUE(ucdr_serialize_int16_t(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_int16_t(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void uint16_t_serialization()
    {
        uint16_t input = 0x0A0B;
        uint16_t output = 0;

        EXPECT_TRUE(ucdr_serialize_uint16_t(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_uint16_t(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void int32_t_serialization()
    {
        int32_t input = 0x0C0D0E0F;
        int32_t output = 0;

        EXPECT_TRUE(ucdr_serialize_int32_t(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_int32_t(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void uint32_t_serialization()
    {
        uint32_t input = 0x0C0D0E0F;
        uint32_t output = 0;

        EXPECT_TRUE(ucdr_serialize_uint32_t(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_uint32_t(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void int64_t_serialization()
    {
        int64_t input = 0x0102030405060708L;
        int64_t output = 0;

        EXPECT_TRUE(ucdr_serialize_int64_t(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_int64_t(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void uint64_t_serialization()
    {
        uint64_t input = 0x0102030405060708L;
        uint64_t output = 0;

        EXPECT_TRUE(ucdr_serialize_uint64_t(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_uint64_t(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void float_serialization()
    {
        float input  = 3.141592653589793238462f;
        float output = 0;

        EXPECT_TRUE(ucdr_serialize_float(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_float(&reader, &output));

        EXPECT_EQ(input, output);
    }

    void double_serialization()
    {
        double input  = 3.141592653589793238462;
        double output = 0;

        EXPECT_TRUE(ucdr_serialize_double(&writer, input));
        EXPECT_TRUE(ucdr_deserialize_double(&reader, &output));

        EXPECT_EQ(input, output);
    }

protected:
    ucdrStream writer;
    ucdrStream reader;
    uint8_t buffer[BUFFER_LENGTH];
};

#endif // BASIC_SERIALIZATION_HPP_
