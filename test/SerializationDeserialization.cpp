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

TEST(serialization_deserialization, Bool)
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

TEST(serialization_deserialization, Char)
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

TEST(serialization_deserialization, Uint8)
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

TEST(serialization_deserialization, Int16)
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

TEST(serialization_deserialization, Uint16)
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

TEST(serialization_deserialization, Int32)
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

TEST(serialization_deserialization, Uint32)
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

TEST(serialization_deserialization, Int64)
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

TEST(serialization_deserialization, Uint64)
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

TEST(serialization_deserialization, Float)
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

TEST(serialization_deserialization, Double)
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

TEST(serialization_deserialization, ArrayBool)
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

TEST(serialization_deserialization, ArrayChar)
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

TEST(serialization_deserialization, ArrayUint8)
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

TEST(serialization_deserialization, ArrayInt16)
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

TEST(serialization_deserialization, ArrayUint16)
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

TEST(serialization_deserialization, ArrayInt32)
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

TEST(serialization_deserialization, ArrayUint32)
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

TEST(serialization_deserialization, ArrayInt64)
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

TEST(serialization_deserialization, ArrayUint64)
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

TEST(serialization_deserialization, ArrayFloat)
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

TEST(serialization_deserialization, ArrayDouble)
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

TEST(serialization_deserialization, SequenceChar)
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

TEST(serialization_deserialization, SequenceBool)
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

TEST(serialization_deserialization, SequenceUint8)
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

TEST(serialization_deserialization, SequenceInt16)
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

TEST(serialization_deserialization, SequenceUint16)
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

TEST(serialization_deserialization, SequenceInt32)
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

TEST(serialization_deserialization, SequenceUint32)
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

TEST(serialization_deserialization, SequenceInt64)
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

TEST(serialization_deserialization, SequenceUint64)
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

TEST(serialization_deserialization, SequenceFloat)
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

TEST(serialization_deserialization, SequenceDouble)
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
