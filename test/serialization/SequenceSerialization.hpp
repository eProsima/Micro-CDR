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

#ifndef _SEQUENCE_SERIALIZATION_HPP_
#define _SEQUENCE_SERIALIZATION_HPP_

#include "ArraySerialization.hpp"

#define SEQUENCE_LENGTH 16

class SequenceSerialization : public ArraySerialization
{
public:

    SequenceSerialization()
    {
    }

    virtual ~SequenceSerialization()
    {
        EXPECT_EQ(output_size, SEQUENCE_LENGTH);
    }

    void bool_sequence_serialization()
    {
        bool input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, true);
        bool output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_bool(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_bool(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void char_sequence_serialization()
    {
        char input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 'A');
        char output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_char(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_char(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void int8_t_sequence_serialization()
    {
        int8_t input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 0x09);
        int8_t output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_int8_t(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_int8_t(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void uint8_t_sequence_serialization()
    {
        uint8_t input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 0x09);
        uint8_t output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_uint8_t(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_uint8_t(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void int16_t_sequence_serialization()
    {
        int16_t input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 0x0A0B);
        int16_t output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_int16_t(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_int16_t(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void uint16_t_sequence_serialization()
    {
        uint16_t input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 0x0A0B);
        uint16_t output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_uint16_t(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_uint16_t(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void int32_t_sequence_serialization()
    {
        int32_t input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 0x0A0B0C0D);
        int32_t output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_int32_t(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_int32_t(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void uint32_t_sequence_serialization()
    {
        uint32_t input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 0x0A0B0C0D);
        uint32_t output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_uint32_t(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_uint32_t(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void int64_t_sequence_serialization()
    {
        int64_t input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 0x0102030405060708L);
        int64_t output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_int64_t(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_int64_t(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void uint64_t_sequence_serialization()
    {
        uint64_t input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 0x0102030405060708L);
        uint64_t output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_uint64_t(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_uint64_t(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void float_sequence_serialization()
    {
        float input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 3.141592653589793238462f);
        float output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_float(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_float(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

    void double_sequence_serialization()
    {
        double input[ARRAY_LENGTH];
        std::fill_n(input, SEQUENCE_LENGTH, 3.141592653589793238462);
        double output[ARRAY_LENGTH];

        EXPECT_TRUE(serialize_sequence_double(&writer, input, SEQUENCE_LENGTH));
        EXPECT_TRUE(deserialize_sequence_double(&reader, output, &output_size));

        EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
    }

protected:
    uint32_t output_size = 0;
};

#endif //_SEQUENCE_SERIALIZATION_HPP_
