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

#include <ucdr/microcdr.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define BUFFER_LENGTH   128
#define STRING_MAX      256

int main()
{
    // Data buffer
    uint8_t buffer1[BUFFER_LENGTH];
    uint8_t buffer2[BUFFER_LENGTH];

    // Structs for handle the stream.
    ucdrStream writer;
    ucdrStream reader;

    // Initialize the MicroStream for working with an user-managed buffer.
    ucdr_init_stream(&writer, buffer1, sizeof(buffer1));
    ucdr_init_stream(&reader, buffer1, sizeof(buffer1));

    // Append a buffer to the writer and the reader
    ucdr_append_buffer(&writer, buffer2, sizeof(buffer2));
    ucdr_append_buffer(&reader, buffer2, sizeof(buffer2));

    // Serialize data
    printf("Serializing...\n");
    char input[STRING_MAX] = {0};
    memset(&input, 'a', BUFFER_LENGTH + 1);
    ucdr_serialize_string(&writer, input);
    printf("\n");

    // Deserialize data
    printf("Deserializing...\n");
    char output[STRING_MAX];
    ucdr_deserialize_string(&reader, output, STRING_MAX);
    printf("\n");

    printf("Input: %s\n", input);
    printf("Output: %s\n", output);

    return 0;
}
