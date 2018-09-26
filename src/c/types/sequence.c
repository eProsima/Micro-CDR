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

#include <microcdr/types/basic.h>
#include <microcdr/types/array.h>
#include <microcdr/types/sequence.h>

#include "array_internals.h"
#include "sequence_internals.h"

// -------------------------------------------------------------------
//                INTERNAL UTIL IMPLEMENTATION
// -------------------------------------------------------------------
static inline void deserialize_sequence_header(mcBuffer* mb, mcEndianness endianness, uint32_t capacity, uint32_t* size)
{
    mc_deserialize_endian_uint32_t(mb, endianness, size);
    if(*size > capacity)
    {
        mb->error = true;
    }
}

// -------------------------------------------------------------------
//                INTERNAL SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------
bool serialize_sequence_byte_1(mcBuffer* mb, mcEndianness endianness, const uint8_t* array, const uint32_t size)
{
    mc_serialize_endian_uint32_t(mb, endianness, size);
    return serialize_array_byte_1(mb, array, size);
}

bool serialize_sequence_byte_2(mcBuffer* mb, mcEndianness endianness, const uint16_t* array, const uint32_t size)
{
    mc_serialize_endian_uint32_t(mb, endianness, size);
    return serialize_array_byte_2(mb, endianness, array, size);
}

bool serialize_sequence_byte_4(mcBuffer* mb, mcEndianness endianness, const uint32_t* array, const uint32_t size)
{
    mc_serialize_endian_uint32_t(mb, endianness, size);
    return serialize_array_byte_4(mb, endianness, array, size);
}

bool serialize_sequence_byte_8(mcBuffer* mb, mcEndianness endianness, const uint64_t* array, const uint32_t size)
{
    mc_serialize_endian_uint32_t(mb, endianness, size);
    return serialize_array_byte_8(mb, endianness, array, size);
}

bool deserialize_sequence_byte_1(mcBuffer* mb, mcEndianness endianness, uint8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    deserialize_sequence_header(mb, endianness, array_capacity, size);
    return deserialize_array_byte_1(mb, array, *size);
}

bool deserialize_sequence_byte_2(mcBuffer* mb, mcEndianness endianness, uint16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    deserialize_sequence_header(mb, endianness, array_capacity, size);
    return deserialize_array_byte_2(mb, endianness, array, *size);
}

bool deserialize_sequence_byte_4(mcBuffer* mb, mcEndianness endianness, uint32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    deserialize_sequence_header(mb, endianness, array_capacity, size);
    return deserialize_array_byte_4(mb, endianness, array, *size);
}

bool deserialize_sequence_byte_8(mcBuffer* mb, mcEndianness endianness, uint64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    deserialize_sequence_header(mb, endianness, array_capacity, size);
    return deserialize_array_byte_8(mb, endianness, array, *size);
}

// -------------------------------------------------------------------
//              PUBLIC SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------

bool mc_serialize_sequence_char(mcBuffer* mb, const char* array, const uint32_t size)
{
    return serialize_sequence_byte_1(mb, mb->endianness, (uint8_t*)array, size);
}

bool mc_serialize_sequence_bool(mcBuffer* mb, const bool* array, const uint32_t size)
{
    return serialize_sequence_byte_1(mb, mb->endianness, (uint8_t*)array, size);
}

bool mc_serialize_sequence_uint8_t(mcBuffer* mb, const uint8_t* array, const uint32_t size)
{
    return serialize_sequence_byte_1(mb, mb->endianness, (uint8_t*)array, size);
}

bool mc_serialize_sequence_uint16_t(mcBuffer* mb, const uint16_t* array, const uint32_t size)
{
    return serialize_sequence_byte_2(mb, mb->endianness, (uint16_t*)array, size);
}

bool mc_serialize_sequence_uint32_t(mcBuffer* mb, const uint32_t* array, const uint32_t size)
{
    return serialize_sequence_byte_4(mb, mb->endianness, (uint32_t*)array, size);
}

bool mc_serialize_sequence_uint64_t(mcBuffer* mb, const uint64_t* array, const uint32_t size)
{
    return serialize_sequence_byte_8(mb, mb->endianness, (uint64_t*)array, size);
}

bool mc_serialize_sequence_int8_t(mcBuffer* mb, const int8_t* array, const uint32_t size)
{
    return serialize_sequence_byte_1(mb, mb->endianness, (uint8_t*)array, size);
}

bool mc_serialize_sequence_int16_t(mcBuffer* mb, const int16_t* array, const uint32_t size)
{
    return serialize_sequence_byte_2(mb, mb->endianness, (uint16_t*)array, size);
}

bool mc_serialize_sequence_int32_t(mcBuffer* mb, const int32_t* array, const uint32_t size)
{
    return serialize_sequence_byte_4(mb, mb->endianness, (uint32_t*)array, size);
}

bool mc_serialize_sequence_int64_t(mcBuffer* mb, const int64_t* array, const uint32_t size)
{
    return serialize_sequence_byte_8(mb, mb->endianness, (uint64_t*)array, size);
}

bool mc_serialize_sequence_float(mcBuffer* mb, const float* array, const uint32_t size)
{
    return serialize_sequence_byte_4(mb, mb->endianness, (uint32_t*)array, size);
}

bool mc_serialize_sequence_double(mcBuffer* mb, const double* array, const uint32_t size)
{
    return serialize_sequence_byte_8(mb, mb->endianness, (uint64_t*)array, size);
}

bool mc_deserialize_sequence_char(mcBuffer* mb, char* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_1(mb, mb->endianness, (uint8_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_bool(mcBuffer* mb, bool* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_1(mb, mb->endianness, (uint8_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_uint8_t(mcBuffer* mb, uint8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_1(mb, mb->endianness, (uint8_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_uint16_t(mcBuffer* mb, uint16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_2(mb, mb->endianness, (uint16_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_uint32_t(mcBuffer* mb, uint32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_4(mb, mb->endianness, (uint32_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_uint64_t(mcBuffer* mb, uint64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_8(mb, mb->endianness, (uint64_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_int8_t(mcBuffer* mb, int8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_1(mb, mb->endianness, (uint8_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_int16_t(mcBuffer* mb, int16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_2(mb, mb->endianness, (uint16_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_int32_t(mcBuffer* mb, int32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_4(mb, mb->endianness, (uint32_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_int64_t(mcBuffer* mb, int64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_8(mb, mb->endianness, (uint64_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_float(mcBuffer* mb, float* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_4(mb, mb->endianness, (uint32_t*)array, array_capacity, size);
}

bool mc_deserialize_sequence_double(mcBuffer* mb, double* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_8(mb, mb->endianness, (uint64_t*)array, array_capacity, size);
}

bool mc_serialize_endian_sequence_char(mcBuffer* mb, const mcEndianness endianness, const char* array, const uint32_t size)
{
    return serialize_sequence_byte_1(mb, endianness, (uint8_t*)array, size);
}

bool mc_serialize_endian_sequence_bool(mcBuffer* mb, const mcEndianness endianness, const bool* array, const uint32_t size)
{
    return serialize_sequence_byte_1(mb, endianness, (uint8_t*)array, size);
}

bool mc_serialize_endian_sequence_uint8_t(mcBuffer* mb, const mcEndianness endianness, const uint8_t* array, const uint32_t size)
{
    return serialize_sequence_byte_1(mb, endianness, (uint8_t*)array, size);
}

bool mc_serialize_endian_sequence_uint16_t(mcBuffer* mb, const mcEndianness endianness, const uint16_t* array, const uint32_t size)
{
    return serialize_sequence_byte_2(mb, endianness, (uint16_t*)array, size);
}

bool mc_serialize_endian_sequence_uint32_t(mcBuffer* mb, const mcEndianness endianness, const uint32_t* array, const uint32_t size)
{
    return serialize_sequence_byte_4(mb, endianness, (uint32_t*)array, size);
}

bool mc_serialize_endian_sequence_uint64_t(mcBuffer* mb, const mcEndianness endianness, const uint64_t* array, const uint32_t size)
{
    return serialize_sequence_byte_8(mb, endianness, (uint64_t*)array, size);
}

bool mc_serialize_endian_sequence_int8_t(mcBuffer* mb, const mcEndianness endianness, const int8_t* array, const uint32_t size)
{
    return serialize_sequence_byte_1(mb, endianness, (uint8_t*)array, size);
}

bool mc_serialize_endian_sequence_int16_t(mcBuffer* mb, const mcEndianness endianness, const int16_t* array, const uint32_t size)
{
    return serialize_sequence_byte_2(mb, endianness, (uint16_t*)array, size);
}

bool mc_serialize_endian_sequence_int32_t(mcBuffer* mb, const mcEndianness endianness, const int32_t* array, const uint32_t size)
{
    return serialize_sequence_byte_4(mb, endianness, (uint32_t*)array, size);
}

bool mc_serialize_endian_sequence_int64_t(mcBuffer* mb, const mcEndianness endianness, const int64_t* array, const uint32_t size)
{
    return serialize_sequence_byte_8(mb, endianness, (uint64_t*)array, size);
}

bool mc_serialize_endian_sequence_float(mcBuffer* mb, const mcEndianness endianness, const float* array, const uint32_t size)
{
    return serialize_sequence_byte_4(mb, endianness, (uint32_t*)array, size);
}

bool mc_serialize_endian_sequence_double(mcBuffer* mb, const mcEndianness endianness, const double* array, const uint32_t size)
{
    return serialize_sequence_byte_8(mb, endianness, (uint64_t*)array, size);
}

bool mc_deserialize_endian_sequence_char(mcBuffer* mb, const mcEndianness endianness, char* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_1(mb, endianness, (uint8_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_bool(mcBuffer* mb, const mcEndianness endianness, bool* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_1(mb, endianness, (uint8_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_uint8_t(mcBuffer* mb, const mcEndianness endianness, uint8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_1(mb, endianness, (uint8_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_uint16_t(mcBuffer* mb, const mcEndianness endianness, uint16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_2(mb, endianness, (uint16_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_uint32_t(mcBuffer* mb, const mcEndianness endianness, uint32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_4(mb, endianness, (uint32_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_uint64_t(mcBuffer* mb, const mcEndianness endianness, uint64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_8(mb, endianness, (uint64_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_int8_t(mcBuffer* mb, const mcEndianness endianness, int8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_1(mb, endianness, (uint8_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_int16_t(mcBuffer* mb, const mcEndianness endianness, int16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_2(mb, endianness, (uint16_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_int32_t(mcBuffer* mb, const mcEndianness endianness, int32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_4(mb, endianness, (uint32_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_int64_t(mcBuffer* mb, const mcEndianness endianness, int64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_8(mb, endianness, (uint64_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_float(mcBuffer* mb, const mcEndianness endianness, float* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_4(mb, endianness, (uint32_t*)array, array_capacity, size);
}

bool mc_deserialize_endian_sequence_double(mcBuffer* mb, const mcEndianness endianness, double* array, const uint32_t array_capacity, uint32_t* size)
{
    return deserialize_sequence_byte_8(mb, endianness, (uint64_t*)array, array_capacity, size);
}

