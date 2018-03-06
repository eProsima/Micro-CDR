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

TEST(alignment_2, Offset_0)
{
    uint16_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint16_t(&writer, 0);

    deserialize_uint16_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 2);
    EXPECT_EQ(reader.iterator - reader.init, 2);
}

TEST(alignment_2, Offset_1)
{
    uint8_t offset;
    uint16_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint16_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint16_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 4);
    EXPECT_EQ(reader.iterator - reader.init, 4);
}

TEST(alignment_2, Offset_2)
{
    uint8_t offset;
    uint16_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint16_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint16_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 4);
    EXPECT_EQ(reader.iterator - reader.init, 4);
}

TEST(alignment_2, Offset_3)
{
    uint8_t offset;
    uint16_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint16_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint16_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 6);
    EXPECT_EQ(reader.iterator - reader.init, 6);
}

TEST(alignment_4, Offset_0)
{
    uint32_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint32_t(&writer, 0);

    deserialize_uint32_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 4);
    EXPECT_EQ(reader.iterator - reader.init, 4);
}

TEST(alignment_4, Offset_1)
{
    uint8_t offset;
    uint32_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint32_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint32_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 8);
    EXPECT_EQ(reader.iterator - reader.init, 8);
}

TEST(alignment_4, Offset_2)
{
    uint8_t offset;
    uint32_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint32_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint32_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 8);
    EXPECT_EQ(reader.iterator - reader.init, 8);
}

TEST(alignment_4, Offset_3)
{
    uint8_t offset;
    uint32_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint32_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint32_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 8);
    EXPECT_EQ(reader.iterator - reader.init, 8);
}

TEST(alignment_4, Offset_4)
{
    uint8_t offset;
    uint32_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint32_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint32_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 8);
    EXPECT_EQ(reader.iterator - reader.init, 8);
}

TEST(alignment_4, Offset_5)
{
    uint8_t offset;
    uint32_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint32_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint32_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 12);
    EXPECT_EQ(reader.iterator - reader.init, 12);
}

TEST(alignment_8, Offset_0)
{
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint64_t(&writer, 0);

    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 8);
    EXPECT_EQ(reader.iterator - reader.init, 8);
}

TEST(alignment_8, Offset_1)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 16);
    EXPECT_EQ(reader.iterator - reader.init, 16);
}

TEST(alignment_8, Offset_2)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 16);
    EXPECT_EQ(reader.iterator - reader.init, 16);
}

TEST(alignment_8, Offset_3)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 16);
    EXPECT_EQ(reader.iterator - reader.init, 16);
}

TEST(alignment_8, Offset_4)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 16);
    EXPECT_EQ(reader.iterator - reader.init, 16);
}

TEST(alignment_8, Offset_5)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 16);
    EXPECT_EQ(reader.iterator - reader.init, 16);
}

TEST(alignment_8, Offset_6)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 16);
    EXPECT_EQ(reader.iterator - reader.init, 16);
}

TEST(alignment_8, Offset_7)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 16);
    EXPECT_EQ(reader.iterator - reader.init, 16);
}

TEST(alignment_8, Offset_8)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 16);
    EXPECT_EQ(reader.iterator - reader.init, 16);
}

TEST(alignment_8, Offset_9)
{
    uint8_t offset;
    uint64_t data;
    uint8_t buffer[BUFFER_LENGTH];

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint8_t(&writer, 0);
    serialize_uint64_t(&writer, 0);

    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint8_t(&reader, &offset);
    deserialize_uint64_t(&reader, &data);

    EXPECT_EQ(writer.iterator - writer.init, 24);
    EXPECT_EQ(reader.iterator - reader.init, 24);
}
