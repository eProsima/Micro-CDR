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

#include <gtest/gtest.h>
#include <microcdr/microcdr.h>

#define BUFFER_LENGTH 1024
#define ARRAY_LENGTH 4
#define PI 3.1415926535897932384626433832795028L

Endianness endianness = BIG_ENDIANNESS;

TEST(serialization_deserialization, Bool)
{
    bool input = true;
    bool output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_bool(&writer, input);
    deserialize_bool(&reader, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Char)
{
    char input = 'A';
    char output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_char(&writer, input);
    deserialize_char(&reader, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Uint8)
{
    uint8_t input = 0x09;
    uint8_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, input);
    deserialize_uint8_t(&reader, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Int16)
{
    int16_t input = 0x0A0B;
    int16_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_int16_t(&writer, endianness, input);
    deserialize_endian_int16_t(&reader, endianness, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Uint16)
{
    uint16_t input = 0x0A0B;
    uint16_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_uint16_t(&writer, endianness, input);
    deserialize_endian_uint16_t(&reader, endianness, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Int32)
{
    int32_t input = 0x0C0D0E0F;
    int32_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_int32_t(&writer, endianness, input);
    deserialize_endian_int32_t(&reader, endianness, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Uint32)
{
    uint32_t input = 0x0C0D0E0F;
    uint32_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_uint32_t(&writer, endianness, input);
    deserialize_endian_uint32_t(&reader, endianness, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Int64)
{
    int64_t input = 0x0102030405060708;
    int64_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_int64_t(&writer, endianness, input);
    deserialize_endian_int64_t(&reader, endianness, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Uint64)
{
    uint64_t input = 0x0102030405060708;
    uint64_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_uint64_t(&writer, endianness, input);
    deserialize_endian_uint64_t(&reader, endianness, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Float)
{
    float input = PI;
    float output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_float(&writer, endianness, input);
    deserialize_endian_float(&reader, endianness, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, Double)
{
    double input = PI;
    double output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_double(&writer, endianness, input);
    deserialize_endian_double(&reader, endianness, &output);

    EXPECT_EQ(input, output);
}

TEST(serialization_deserialization, ArrayBool)
{
    bool input[ARRAY_LENGTH] = {true};
    bool output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_array_bool(&writer, input, ARRAY_LENGTH);
    deserialize_array_bool(&reader, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayChar)
{
    char input[ARRAY_LENGTH] = {'A'};
    char output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_array_char(&writer, input, ARRAY_LENGTH);
    deserialize_array_char(&reader, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayUint8)
{
    uint8_t input[ARRAY_LENGTH] = {0x09};
    uint8_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_array_uint8_t(&writer, input, ARRAY_LENGTH);
    deserialize_array_uint8_t(&reader, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayInt16)
{
    int16_t input[ARRAY_LENGTH] = {0x0A0B};
    int16_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_array_int16_t(&writer, endianness, input, ARRAY_LENGTH);
    deserialize_endian_array_int16_t(&reader, endianness, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayUint16)
{
    uint16_t input[ARRAY_LENGTH] = {0x0A0B};
    uint16_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_array_uint16_t(&writer, endianness, input, ARRAY_LENGTH);
    deserialize_endian_array_uint16_t(&reader, endianness, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayInt32)
{
    int32_t input[ARRAY_LENGTH] = {0x0C0D0E0F};
    int32_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_array_int32_t(&writer, endianness, input, ARRAY_LENGTH);
    deserialize_endian_array_int32_t(&reader, endianness, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayUint32)
{
    uint32_t input[ARRAY_LENGTH] = {0x0C0D0E0F};
    uint32_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_array_uint32_t(&writer, endianness, input, ARRAY_LENGTH);
    deserialize_endian_array_uint32_t(&reader, endianness, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayInt64)
{
    int64_t input[ARRAY_LENGTH] = {0x0102030405060708};
    int64_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_array_int64_t(&writer, endianness, input, ARRAY_LENGTH);
    deserialize_endian_array_int64_t(&reader, endianness, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayUint64)
{
    uint64_t input[ARRAY_LENGTH] = {0x0102030405060708};
    uint64_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_array_uint64_t(&writer, endianness, input, ARRAY_LENGTH);
    deserialize_endian_array_uint64_t(&reader, endianness, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayFloat)
{
    float input[ARRAY_LENGTH] = {PI};
    float output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_array_float(&writer, endianness, input, ARRAY_LENGTH);
    deserialize_endian_array_float(&reader, endianness, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(serialization_deserialization, ArrayDouble)
{
    double input[ARRAY_LENGTH] = {PI};
    double output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_endian_array_double(&writer, endianness, input, ARRAY_LENGTH);
    deserialize_endian_array_double(&reader, endianness, output, ARRAY_LENGTH);

    for(uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}