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
#include <algorithm>

#define BUFFER_LENGTH 1024
#define ARRAY_LENGTH 4u
#define PI 3.1415926535897932384626433832795028

static Endianness endianness = BIG_ENDIANNESS;

TEST(Serialization, ArrayBool)
{
    bool input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, true);
    bool output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_array_bool(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_bool(&reader, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayChar)
{
    char input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 'A');
    char output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_array_char(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_char(&reader, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayInt8)
{
    int8_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x09);
    int8_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_array_int8_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_int8_t(&reader, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayUint8)
{
    uint8_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x09);
    uint8_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_array_uint8_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_uint8_t(&reader, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayInt16)
{
    int16_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0A0B);
    int16_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_array_int16_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_array_int16_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayUint16)
{
    uint16_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0A0B);
    uint16_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_array_uint16_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_array_uint16_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayInt32)
{
    int32_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0C0D0E0F);
    int32_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_array_int32_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_array_int32_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayUint32)
{
    uint32_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0C0D0E0F);
    uint32_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_array_uint32_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_array_uint32_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayInt64)
{
    int64_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0102030405060708L);
    int64_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_array_int64_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_array_int64_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayUint64)
{
    uint64_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0102030405060708L);
    uint64_t output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_array_uint64_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_array_uint64_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayFloat)
{
    float input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, static_cast<float>(PI));
    float output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_array_float(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_array_float(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, ArrayDouble)
{
    double input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, PI);
    double output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_array_double(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_array_double(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}
