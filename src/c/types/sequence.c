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

#include <ucdr/types/basic.h>
#include <ucdr/types/array.h>
#include <ucdr/types/sequence.h>

#include "array_internals.h"
#include "sequence_internals.h"

// -------------------------------------------------------------------
//                INTERNAL UTIL IMPLEMENTATION
// -------------------------------------------------------------------
static inline void ucdr_deserialize_sequence_header(ucdrBuffer* ub, ucdrEndianness endianness, uint32_t capacity, uint32_t* size)
{
    ucdr_deserialize_endian_uint32_t(ub, endianness, size);
    if(*size > capacity)
    {
        ub->error = true;
    }
}

// -------------------------------------------------------------------
//                INTERNAL SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------
bool ucdr_serialize_sequence_byte_1(ucdrBuffer* ub, ucdrEndianness endianness, const uint8_t* array, const uint32_t size)
{
    ucdr_serialize_endian_uint32_t(ub, endianness, size);
    return ucdr_serialize_array_byte_1(ub, array, size);
}

bool ucdr_serialize_sequence_byte_2(ucdrBuffer* ub, ucdrEndianness endianness, const uint16_t* array, const uint32_t size)
{
    ucdr_serialize_endian_uint32_t(ub, endianness, size);
    return ucdr_serialize_array_byte_2(ub, endianness, array, size);
}

bool ucdr_serialize_sequence_byte_4(ucdrBuffer* ub, ucdrEndianness endianness, const uint32_t* array, const uint32_t size)
{
    ucdr_serialize_endian_uint32_t(ub, endianness, size);
    return ucdr_serialize_array_byte_4(ub, endianness, array, size);
}

bool ucdr_serialize_sequence_byte_8(ucdrBuffer* ub, ucdrEndianness endianness, const uint64_t* array, const uint32_t size)
{
    ucdr_serialize_endian_uint32_t(ub, endianness, size);
    return ucdr_serialize_array_byte_8(ub, endianness, array, size);
}

bool ucdr_deserialize_sequence_byte_1(ucdrBuffer* ub, ucdrEndianness endianness, uint8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    ucdr_deserialize_sequence_header(ub, endianness, array_capacity, size);
    return ucdr_deserialize_array_byte_1(ub, array, *size);
}

bool ucdr_deserialize_sequence_byte_2(ucdrBuffer* ub, ucdrEndianness endianness, uint16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    ucdr_deserialize_sequence_header(ub, endianness, array_capacity, size);
    return ucdr_deserialize_array_byte_2(ub, endianness, array, *size);
}

bool ucdr_deserialize_sequence_byte_4(ucdrBuffer* ub, ucdrEndianness endianness, uint32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    ucdr_deserialize_sequence_header(ub, endianness, array_capacity, size);
    return ucdr_deserialize_array_byte_4(ub, endianness, array, *size);
}

bool ucdr_deserialize_sequence_byte_8(ucdrBuffer* ub, ucdrEndianness endianness, uint64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    ucdr_deserialize_sequence_header(ub, endianness, array_capacity, size);
    return ucdr_deserialize_array_byte_8(ub, endianness, array, *size);
}

// -------------------------------------------------------------------
//              PUBLIC SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------

bool ucdr_serialize_sequence_char(ucdrBuffer* ub, const char* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_1(ub, ub->endianness, (uint8_t*)array, size);
}

bool ucdr_serialize_sequence_bool(ucdrBuffer* ub, const bool* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_1(ub, ub->endianness, (uint8_t*)array, size);
}

bool ucdr_serialize_sequence_uint8_t(ucdrBuffer* ub, const uint8_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_1(ub, ub->endianness, (uint8_t*)array, size);
}

bool ucdr_serialize_sequence_uint16_t(ucdrBuffer* ub, const uint16_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_2(ub, ub->endianness, (uint16_t*)array, size);
}

bool ucdr_serialize_sequence_uint32_t(ucdrBuffer* ub, const uint32_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_4(ub, ub->endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_sequence_uint64_t(ucdrBuffer* ub, const uint64_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_8(ub, ub->endianness, (uint64_t*)array, size);
}

bool ucdr_serialize_sequence_int8_t(ucdrBuffer* ub, const int8_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_1(ub, ub->endianness, (uint8_t*)array, size);
}

bool ucdr_serialize_sequence_int16_t(ucdrBuffer* ub, const int16_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_2(ub, ub->endianness, (uint16_t*)array, size);
}

bool ucdr_serialize_sequence_int32_t(ucdrBuffer* ub, const int32_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_4(ub, ub->endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_sequence_int64_t(ucdrBuffer* ub, const int64_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_8(ub, ub->endianness, (uint64_t*)array, size);
}

bool ucdr_serialize_sequence_float(ucdrBuffer* ub, const float* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_4(ub, ub->endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_sequence_double(ucdrBuffer* ub, const double* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_8(ub, ub->endianness, (uint64_t*)array, size);
}

bool ucdr_deserialize_sequence_char(ucdrBuffer* ub, char* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_1(ub, ub->endianness, (uint8_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_bool(ucdrBuffer* ub, bool* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_1(ub, ub->endianness, (uint8_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_uint8_t(ucdrBuffer* ub, uint8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_1(ub, ub->endianness, (uint8_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_uint16_t(ucdrBuffer* ub, uint16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_2(ub, ub->endianness, (uint16_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_uint32_t(ucdrBuffer* ub, uint32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_4(ub, ub->endianness, (uint32_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_uint64_t(ucdrBuffer* ub, uint64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_8(ub, ub->endianness, (uint64_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_int8_t(ucdrBuffer* ub, int8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_1(ub, ub->endianness, (uint8_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_int16_t(ucdrBuffer* ub, int16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_2(ub, ub->endianness, (uint16_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_int32_t(ucdrBuffer* ub, int32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_4(ub, ub->endianness, (uint32_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_int64_t(ucdrBuffer* ub, int64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_8(ub, ub->endianness, (uint64_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_float(ucdrBuffer* ub, float* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_4(ub, ub->endianness, (uint32_t*)array, array_capacity, size);
}

bool ucdr_deserialize_sequence_double(ucdrBuffer* ub, double* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_8(ub, ub->endianness, (uint64_t*)array, array_capacity, size);
}

bool ucdr_serialize_endian_sequence_char(ucdrBuffer* ub, const ucdrEndianness endianness, const char* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_1(ub, endianness, (uint8_t*)array, size);
}

bool ucdr_serialize_endian_sequence_bool(ucdrBuffer* ub, const ucdrEndianness endianness, const bool* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_1(ub, endianness, (uint8_t*)array, size);
}

bool ucdr_serialize_endian_sequence_uint8_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint8_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_1(ub, endianness, (uint8_t*)array, size);
}

bool ucdr_serialize_endian_sequence_uint16_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint16_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_2(ub, endianness, (uint16_t*)array, size);
}

bool ucdr_serialize_endian_sequence_uint32_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint32_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_4(ub, endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_endian_sequence_uint64_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint64_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_8(ub, endianness, (uint64_t*)array, size);
}

bool ucdr_serialize_endian_sequence_int8_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int8_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_1(ub, endianness, (uint8_t*)array, size);
}

bool ucdr_serialize_endian_sequence_int16_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int16_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_2(ub, endianness, (uint16_t*)array, size);
}

bool ucdr_serialize_endian_sequence_int32_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int32_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_4(ub, endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_endian_sequence_int64_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int64_t* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_8(ub, endianness, (uint64_t*)array, size);
}

bool ucdr_serialize_endian_sequence_float(ucdrBuffer* ub, const ucdrEndianness endianness, const float* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_4(ub, endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_endian_sequence_double(ucdrBuffer* ub, const ucdrEndianness endianness, const double* array, const uint32_t size)
{
    return ucdr_serialize_sequence_byte_8(ub, endianness, (uint64_t*)array, size);
}

bool ucdr_deserialize_endian_sequence_char(ucdrBuffer* ub, const ucdrEndianness endianness, char* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_1(ub, endianness, (uint8_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_bool(ucdrBuffer* ub, const ucdrEndianness endianness, bool* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_1(ub, endianness, (uint8_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_uint8_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_1(ub, endianness, (uint8_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_uint16_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_2(ub, endianness, (uint16_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_uint32_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_4(ub, endianness, (uint32_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_uint64_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_8(ub, endianness, (uint64_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_int8_t(ucdrBuffer* ub, const ucdrEndianness endianness, int8_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_1(ub, endianness, (uint8_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_int16_t(ucdrBuffer* ub, const ucdrEndianness endianness, int16_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_2(ub, endianness, (uint16_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_int32_t(ucdrBuffer* ub, const ucdrEndianness endianness, int32_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_4(ub, endianness, (uint32_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_int64_t(ucdrBuffer* ub, const ucdrEndianness endianness, int64_t* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_8(ub, endianness, (uint64_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_float(ucdrBuffer* ub, const ucdrEndianness endianness, float* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_4(ub, endianness, (uint32_t*)array, array_capacity, size);
}

bool ucdr_deserialize_endian_sequence_double(ucdrBuffer* ub, const ucdrEndianness endianness, double* array, const uint32_t array_capacity, uint32_t* size)
{
    return ucdr_deserialize_sequence_byte_8(ub, endianness, (uint64_t*)array, array_capacity, size);
}

