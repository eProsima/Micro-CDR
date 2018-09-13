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

TEST(Serialization, SequenceChar)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    char input[ARRAY_LENGTH];
    std::fill_n(input, sequence_size, 'A');
    char output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_sequence_char(&writer, input, sequence_size));
    EXPECT_TRUE(deserialize_sequence_char(&reader, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceBool)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    bool input[ARRAY_LENGTH];
    std::fill_n(input, sequence_size, true);
    bool output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_sequence_bool(&writer, input, sequence_size));
    EXPECT_TRUE(deserialize_sequence_bool(&reader, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceInt8)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    int8_t input[ARRAY_LENGTH];
    std::fill_n(input, sequence_size, 0x09);
    int8_t output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_sequence_int8_t(&writer, input, sequence_size));
    EXPECT_TRUE(deserialize_sequence_int8_t(&reader, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceUint8)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    uint8_t input[ARRAY_LENGTH];
    std::fill_n(input, sequence_size, 0x09);
    uint8_t output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_sequence_uint8_t(&writer, input, sequence_size));
    EXPECT_TRUE(deserialize_sequence_uint8_t(&reader, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceInt16)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    int16_t input[ARRAY_LENGTH];
    std::fill_n(input, sequence_size, 0x0A0B);
    int16_t output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_sequence_int16_t(&writer, endianness, input, sequence_size));
    EXPECT_TRUE(deserialize_endian_sequence_int16_t(&reader, endianness, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceUint16)
{
    uint16_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0A0B);
    uint16_t output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_sequence_uint16_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_endian_sequence_uint16_t(&reader, endianness, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(ARRAY_LENGTH, outputSize);
    for (uint32_t i = 0; i < ARRAY_LENGTH; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceInt32)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    int32_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0A0B0C0D);
    int32_t output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_sequence_int32_t(&writer, endianness, input, sequence_size));
    EXPECT_TRUE(deserialize_endian_sequence_int32_t(&reader, endianness, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceUint32)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    uint32_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0A0B0C0D);
    uint32_t output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_sequence_uint32_t(&writer, endianness, input, sequence_size));
    EXPECT_TRUE(deserialize_endian_sequence_uint32_t(&reader, endianness, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceInt64)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    int64_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0102030405060708L);
    int64_t output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_sequence_int64_t(&writer, endianness, input, sequence_size));
    EXPECT_TRUE(deserialize_endian_sequence_int64_t(&reader, endianness, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceUint64)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    uint64_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0102030405060708L);
    uint64_t output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_sequence_uint64_t(&writer, endianness, input, sequence_size));
    EXPECT_TRUE(deserialize_endian_sequence_uint64_t(&reader, endianness, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceFloat)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    float input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, static_cast<float>(PI));
    float output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_sequence_float(&writer, endianness, input, sequence_size));
    EXPECT_TRUE(deserialize_endian_sequence_float(&reader, endianness, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);
    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(Serialization, SequenceDouble)
{
    uint32_t sequence_size = ARRAY_LENGTH / 2;
    double input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, PI);
    double output[ARRAY_LENGTH];
    uint32_t outputSize = 0;
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_endian_sequence_double(&writer, endianness, input, sequence_size));
    EXPECT_TRUE(deserialize_endian_sequence_double(&reader, endianness, output, &outputSize));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    EXPECT_EQ(sequence_size, outputSize);

    for (uint32_t i = 0; i < sequence_size; i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}
