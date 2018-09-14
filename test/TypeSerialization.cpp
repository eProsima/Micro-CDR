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
#include <cstring>

#define SEQUENCE_LENGTH 16
#define ARRAY_LENGTH 32
#define BUFFER_LENGTH  321024
#define PI 3.141592653589793238462

class TypeSerialization : public testing::Test
{
public:
    TypeSerialization()
    {
        std::memset(buffer, 0, BUFFER_LENGTH);
        init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
        init_micro_buffer(&reader, buffer, BUFFER_LENGTH);
    }

    virtual ~TypeSerialization()
    {
        EXPECT_FALSE(writer.error);
        EXPECT_FALSE(reader.error);
    }

protected:
    MicroBuffer writer;
    MicroBuffer reader;
    uint8_t buffer[BUFFER_LENGTH];
};

class TypeSeqSerialization : public TypeSerialization
{
public:
    TypeSeqSerialization() { }

    virtual ~TypeSeqSerialization()
    {
        EXPECT_EQ(output_size, SEQUENCE_LENGTH);
    }

protected:
    uint32_t output_size = 0;
};


TEST_F(TypeSerialization, Bool)
{
    bool input = true;
    bool output;

    EXPECT_TRUE(serialize_bool(&writer, input));
    EXPECT_TRUE(deserialize_bool(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Char)
{
    char input = 'A';
    char output;

    EXPECT_TRUE(serialize_char(&writer, input));
    EXPECT_TRUE(deserialize_char(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Int8)
{
    int8_t input = 0x09;
    int8_t output;

    EXPECT_TRUE(serialize_int8_t(&writer, input));
    EXPECT_TRUE(deserialize_int8_t(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Uint8)
{
    uint8_t input = 0x09;
    uint8_t output;

    EXPECT_TRUE(serialize_uint8_t(&writer, input));
    EXPECT_TRUE(deserialize_uint8_t(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Int16)
{
    int16_t input = 0x0A0B;
    int16_t output;

    EXPECT_TRUE(serialize_int16_t(&writer, input));
    EXPECT_TRUE(deserialize_int16_t(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Uint16)
{
    uint16_t input = 0x0A0B;
    uint16_t output;

    EXPECT_TRUE(serialize_uint16_t(&writer, input));
    EXPECT_TRUE(deserialize_uint16_t(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Int32)
{
    int32_t input = 0x0C0D0E0F;
    int32_t output;

    EXPECT_TRUE(serialize_int32_t(&writer, input));
    EXPECT_TRUE(deserialize_int32_t(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Uint32)
{
    uint32_t input = 0x0C0D0E0F;
    uint32_t output;

    EXPECT_TRUE(serialize_uint32_t(&writer, input));
    EXPECT_TRUE(deserialize_uint32_t(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Int64)
{
    int64_t input = 0x0102030405060708L;
    int64_t output;

    EXPECT_TRUE(serialize_int64_t(&writer, input));
    EXPECT_TRUE(deserialize_int64_t(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Uint64)
{
    uint64_t input = 0x0102030405060708L;
    uint64_t output;

    EXPECT_TRUE(serialize_uint64_t(&writer, input));
    EXPECT_TRUE(deserialize_uint64_t(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Float)
{
    float input = static_cast<float>(PI);
    float output;

    EXPECT_TRUE(serialize_float(&writer, input));
    EXPECT_TRUE(deserialize_float(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, Double)
{
    double input = PI;
    double output;

    EXPECT_TRUE(serialize_double(&writer, input));
    EXPECT_TRUE(deserialize_double(&reader, &output));

    EXPECT_EQ(input, output);
}

TEST_F(TypeSerialization, String)
{
    char input[ARRAY_LENGTH] = "This is a message test";
    char output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_string(&writer, input));
    EXPECT_TRUE(deserialize_string(&reader, output));

    EXPECT_STREQ(input, output);
}

TEST_F(TypeSerialization, ArrayBool)
{
    bool input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, true);
    bool output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_bool(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_bool(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayChar)
{
    char input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 'A');
    char output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_char(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_char(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayInt8)
{
    int8_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x09);
    int8_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_int8_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_int8_t(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayUint8)
{
    uint8_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x09);
    uint8_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_uint8_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_uint8_t(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayInt16)
{
    int16_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0A0B);
    int16_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_int16_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_int16_t(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayUint16)
{
    uint16_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0A0B);
    uint16_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_uint16_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_uint16_t(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayInt32)
{
    int32_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0C0D0E0F);
    int32_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_int32_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_int32_t(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayUint32)
{
    uint32_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0C0D0E0F);
    uint32_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_uint32_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_uint32_t(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayInt64)
{
    int64_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0102030405060708L);
    int64_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_int64_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_int64_t(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayUint64)
{
    uint64_t input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, 0x0102030405060708L);
    uint64_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_uint64_t(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_uint64_t(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayFloat)
{
    float input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, static_cast<float>(PI));
    float output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_float(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_float(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSerialization, ArrayDouble)
{
    double input[ARRAY_LENGTH];
    std::fill_n(input, ARRAY_LENGTH, PI);
    double output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_array_double(&writer, input, ARRAY_LENGTH));
    EXPECT_TRUE(deserialize_array_double(&reader, output, ARRAY_LENGTH));

    EXPECT_TRUE(0 == std::memcmp(input, output, ARRAY_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceChar)
{
    char input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 'A');
    char output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_char(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_char(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceBool)
{
    bool input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, true);
    bool output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_bool(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_bool(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceInt8)
{
    int8_t input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 0x09);
    int8_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_int8_t(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_int8_t(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceUint8)
{
    uint8_t input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 0x09);
    uint8_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_uint8_t(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_uint8_t(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceInt16)
{
    int16_t input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 0x0A0B);
    int16_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_int16_t(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_int16_t(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceUint16)
{
    uint16_t input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 0x0A0B);
    uint16_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_uint16_t(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_uint16_t(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceInt32)
{
    int32_t input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 0x0A0B0C0D);
    int32_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_int32_t(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_int32_t(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceUint32)
{
    uint32_t input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 0x0A0B0C0D);
    uint32_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_uint32_t(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_uint32_t(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceInt64)
{
    int64_t input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 0x0102030405060708L);
    int64_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_int64_t(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_int64_t(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceUint64)
{
    uint64_t input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, 0x0102030405060708L);
    uint64_t output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_uint64_t(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_uint64_t(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceFloat)
{
    float input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, static_cast<float>(PI));
    float output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_float(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_float(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

TEST_F(TypeSeqSerialization, SequenceDouble)
{
    double input[ARRAY_LENGTH];
    std::fill_n(input, SEQUENCE_LENGTH, PI);
    double output[ARRAY_LENGTH];

    EXPECT_TRUE(serialize_sequence_double(&writer, input, SEQUENCE_LENGTH));
    EXPECT_TRUE(deserialize_sequence_double(&reader, output, &output_size));

    EXPECT_TRUE(0 == std::memcmp(input, output, SEQUENCE_LENGTH));
}

