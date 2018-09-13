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
#define ARRAY_LENGTH 255

TEST(Serialization, String)
{
    char input[ARRAY_LENGTH];
    strcpy(input, "This is a message test");
    char output[ARRAY_LENGTH];
    uint8_t buffer[BUFFER_LENGTH] = {0};

    MicroBuffer writer;
    MicroBuffer reader;

    init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
    init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

    EXPECT_TRUE(serialize_string(&writer, input));
    EXPECT_TRUE(deserialize_string(&reader, output));

    EXPECT_EQ(writer.error, BUFFER_OK);
    EXPECT_EQ(reader.error, BUFFER_OK);

    for (uint32_t i = 0; i < strlen(input); i++)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}
