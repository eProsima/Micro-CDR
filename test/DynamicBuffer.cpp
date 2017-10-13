#include <gtest/gtest.h>
#include <microcdr/microcdr.h>

#define INITIAL_BUFFER_LENGTH 1
#define ARRAY_LENGTH 4
#define ELEMENTS 1024

TEST(resize_dynamic_buffer, Bool)
{
    bool input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_bool(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Char)
{
    char input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_char(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Uint8)
{
    uint8_t input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_uint8_t(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Int16)
{
    int16_t input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_int16_t(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Uint16)
{
    uint16_t input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_uint16_t(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Int32)
{
    int32_t input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_int32_t(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Uint32)
{
    uint32_t input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_uint32_t(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Int64)
{
    int64_t input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_int64_t(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Uint64)
{
    uint64_t input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_uint64_t(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Float)
{
    float input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_float(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Double)
{
    double input = 0;

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_double(&writer, input);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, ArrayBool)
{
    bool input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_bool(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, ArrayChar)
{
    char input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_char(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, ArrayUint8)
{
    uint8_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_uint8_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Arrayint16)
{
    int16_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_int16_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, ArrayUint16)
{
    uint16_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_uint16_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Arrayint32)
{
    int32_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_int32_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, ArrayUint32)
{
    uint32_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_uint32_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Arrayint64)
{
    int64_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_int64_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, ArrayUint64)
{
    uint64_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_uint64_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}


TEST(resize_dynamic_buffer, ArrayFloat)
{
    float input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_float(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, ArrayDouble)
{
    double input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_array_double(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, SequenceBool)
{
    bool input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_bool(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, SequenceChar)
{
    char input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_char(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, SequenceUint8)
{
    uint8_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_uint8_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Sequenceint16)
{
    int16_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_int16_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, SequenceUint16)
{
    uint16_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_uint16_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Sequenceint32)
{
    int32_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_int32_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, SequenceUint32)
{
    uint32_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_uint32_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, Sequenceint64)
{
    int64_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_int64_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, SequenceUint64)
{
    uint64_t input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_uint64_t(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}


TEST(resize_dynamic_buffer, SequenceFloat)
{
    float input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_float(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(resize_dynamic_buffer, SequenceDouble)
{
    double input[ARRAY_LENGTH] = {};

    MicroBuffer writer;

    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < ELEMENTS; i++)
    {
        serialize_sequence_double(&writer, input, ARRAY_LENGTH);
        ASSERT_LE(i * sizeof(input), writer.iterator - writer.init);
    }

    free_internal_buffer(&writer);
}

TEST(dynamic_buffer_integrity, Test)
{
    MicroBuffer writer;
    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    for(uint32_t i = 0; i < 256; i++)
        serialize_uint8_t(&writer, i);


    MicroBuffer reader;
    init_external_buffer(&reader, writer.init, writer.final - writer.init);

    uint8_t output;
    for(uint32_t i = 0; i < 256; i++)
    {
        deserialize_uint8_t(&reader, &output);
        EXPECT_EQ(i, output);
    }

    free_internal_buffer(&writer);
}