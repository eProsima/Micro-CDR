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

#define BUFFER_LENGTH_KO 0
#define ARRAY_LENGTH 4
#define PI 3.1415926535897932384626433832795028

static Endianness endianness = BIG_ENDIANNESS;

TEST(buffer_error, BoolKO)
{
    bool input = true;
    bool output;
    uint8_t *buffer = NULL;

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH_KO);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH_KO);

    EXPECT_FALSE(serialize_bool(&writer, input));
    EXPECT_FALSE(deserialize_bool(&reader, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, CharKO)
{
    char input = 'A';
    char output;
    uint8_t *buffer = NULL;

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH_KO);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH_KO);

    EXPECT_FALSE(serialize_char(&writer, input));
    EXPECT_FALSE(deserialize_char(&reader, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, Uint8KO)
{
    uint8_t input = 0x09;
    uint8_t output;
    uint8_t *buffer = NULL;

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH_KO);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH_KO);

    EXPECT_FALSE(serialize_uint8_t(&writer, input));
    EXPECT_FALSE(deserialize_uint8_t(&reader, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, Int16KO)
{
    int16_t input = 0x0A0B;
    int16_t output;
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_int16_t(&writer, endianness, input));
    EXPECT_FALSE(deserialize_endian_int16_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, Uint16KO)
{
    uint16_t input = 0x0A0B;
    uint16_t output;
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_uint16_t(&writer, endianness, input));
    EXPECT_FALSE(deserialize_endian_uint16_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, Int32KO)
{
    int32_t input = 0x0C0D0E0F;
    int32_t output;
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_int32_t(&writer, endianness, input));
    EXPECT_FALSE(deserialize_endian_int32_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, Uint32KO)
{
    uint32_t input = 0x0C0D0E0F;
    uint32_t output;
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_uint32_t(&writer, endianness, input));
    EXPECT_FALSE(deserialize_endian_uint32_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, Int64KO)
{
    int64_t input = 0x0102030405060708;
    int64_t output;
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_int64_t(&writer, endianness, input));
    EXPECT_FALSE(deserialize_endian_int64_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, Uint64KO)
{
    uint64_t input = 0x0102030405060708;
    uint64_t output;
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_uint64_t(&writer, endianness, input));
    EXPECT_FALSE(deserialize_endian_uint64_t(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, FloatKO)
{
    float input = static_cast<float>(PI);
    float output;
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_float(&writer, endianness, input));
    EXPECT_FALSE(deserialize_endian_float(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, DoubleKO)
{
    double input = PI;
    double output;
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_double(&writer, endianness, input));
    EXPECT_FALSE(deserialize_endian_double(&reader, endianness, &output));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayBoolKO)
{
    bool input[ARRAY_LENGTH] = {true};
    bool output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_array_bool(&writer, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_array_bool(&reader, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayCharKO)
{
    char input[ARRAY_LENGTH] = {'A'};
    char output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_array_char(&writer, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_array_char(&reader, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayUint8KO)
{
    uint8_t input[ARRAY_LENGTH] = {0x09};
    uint8_t output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_array_uint8_t(&writer, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_array_uint8_t(&reader, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayInt16KO)
{
    int16_t input[ARRAY_LENGTH] = {0x0A0B};
    int16_t output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_array_int16_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_endian_array_int16_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayUint16KO)
{
    uint16_t input[ARRAY_LENGTH] = {0x0A0B};
    uint16_t output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_array_uint16_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_endian_array_uint16_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayInt32KO)
{
    int32_t input[ARRAY_LENGTH] = {0x0C0D0E0F};
    int32_t output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_array_int32_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_endian_array_int32_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayUint32KO)
{
    uint32_t input[ARRAY_LENGTH] = {0x0C0D0E0F};
    uint32_t output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_array_uint32_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_endian_array_uint32_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayInt64KO)
{
    int64_t input[ARRAY_LENGTH] = {0x0102030405060708};
    int64_t output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_array_int64_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_endian_array_int64_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayUint64KO)
{
    uint64_t input[ARRAY_LENGTH] = {0x0102030405060708};
    uint64_t output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_array_uint64_t(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_endian_array_uint64_t(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayFloatKO)
{
    float input[ARRAY_LENGTH] = {static_cast<float>(PI)};
    float output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_array_float(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_endian_array_float(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

TEST(buffer_error, ArrayDoubleKO)
{
    double input[ARRAY_LENGTH] = {PI};
    double output[ARRAY_LENGTH];
    uint8_t buffer[sizeof(output) / 2] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, sizeof(output) / 2);
    init_micro_buffer(&reader, buffer, sizeof(output) / 2);

    EXPECT_FALSE(serialize_endian_array_double(&writer, endianness, input, ARRAY_LENGTH));
    EXPECT_FALSE(deserialize_endian_array_double(&reader, endianness, output, ARRAY_LENGTH));

    EXPECT_EQ(writer.error, BUFFER_NOK);
    EXPECT_EQ(reader.error, BUFFER_NOK);
}

