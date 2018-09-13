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
#define PI 3.1415926535897932384626433832795028

static Endianness endianness = BIG_ENDIANNESS;

TEST(Serialization, Bool)
{
    bool input = true;
    bool output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_bool(&writer, input));
    EXPECT_TRUE(deserialize_bool(&reader, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Char)
{
    char input = 'A';
    char output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_char(&writer, input));
    EXPECT_TRUE(deserialize_char(&reader, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Int8)
{
    int8_t input = 0x09;
    int8_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_int8_t(&writer, input));
    EXPECT_TRUE(deserialize_int8_t(&reader, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Uint8)
{
    uint8_t input = 0x09;
    uint8_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_uint8_t(&writer, input));
    EXPECT_TRUE(deserialize_uint8_t(&reader, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Int16)
{
    int16_t input = 0x0A0B;
    int16_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_int16_t(&writer, endianness, input));
    EXPECT_TRUE(deserialize_endian_int16_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Uint16)
{
    uint16_t input = 0x0A0B;
    uint16_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_uint16_t(&writer, endianness, input));
    EXPECT_TRUE(deserialize_endian_uint16_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Int32)
{
    int32_t input = 0x0C0D0E0F;
    int32_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_int32_t(&writer, endianness, input));
    EXPECT_TRUE(deserialize_endian_int32_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Uint32)
{
    uint32_t input = 0x0C0D0E0F;
    uint32_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_uint32_t(&writer, endianness, input));
    EXPECT_TRUE(deserialize_endian_uint32_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Int64)
{
    int64_t input = 0x0102030405060708L;
    int64_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_int64_t(&writer, endianness, input));
    EXPECT_TRUE(deserialize_endian_int64_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Uint64)
{
    uint64_t input = 0x0102030405060708L;
    uint64_t output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_uint64_t(&writer, endianness, input));
    EXPECT_TRUE(deserialize_endian_uint64_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Float)
{
    float input = static_cast<float>(PI);
    float output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_float(&writer, endianness, input));
    EXPECT_TRUE(deserialize_endian_float(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}

TEST(Serialization, Double)
{
    double input = PI;
    double output;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_double(&writer, endianness, input));
    EXPECT_TRUE(deserialize_endian_double(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(input, output);
}
