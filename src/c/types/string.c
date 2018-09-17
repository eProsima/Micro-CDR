
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

#include <microcdr/types/string.h>
#include <microcdr/types/sequence.h>

#include <string.h>

// -------------------------------------------------------------------
//              PUBLIC SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------

bool serialize_string(MicroBuffer* buffer, const char* string)
{
    return serialize_sequence_char(buffer, string, (uint32_t)strlen(string) + 1);
}

bool deserialize_string(MicroBuffer* buffer, char* string)
{
    uint32_t length;
    return deserialize_sequence_char(buffer, string, &length);
}

bool serialize_endian_string(MicroBuffer* buffer, Endianness endianness, const char* string)
{
    return serialize_endian_sequence_char(buffer, endianness, string, (uint32_t)strlen(string) + 1);
}

bool deserialize_endian_string(MicroBuffer* buffer, Endianness endianness, char* string)
{
    uint32_t length;
    return deserialize_endian_sequence_char(buffer, endianness, string, &length);
}