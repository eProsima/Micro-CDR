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
//                    SERIALIZE MACROS
// -------------------------------------------------------------------
#define UCDR_SEQUENCE_SERIALIZE_DEFINITION(TYPE, SIZE) \
    bool ucdr_serialize_sequence_ ## TYPE(ucdrBuffer* ub, const TYPE* array, const uint32_t size) \
    { \
        ucdr_serialize_endian_uint32_t(ub, ub->endianness, size); \
        return ucdr_serialize_endian_array_ ## TYPE(ub, ub->endianness, array, size); \
    } \
    bool ucdr_serialize_endian_sequence_ ## TYPE(ucdrBuffer* ub, const ucdrEndianness endianness, const TYPE* array, const uint32_t size) \
    { \
        ucdr_serialize_endian_uint32_t(ub, endianness, size); \
        return ucdr_serialize_endian_array_ ## TYPE(ub, endianness, array, size); \
    } \

// -------------------------------------------------------------------
//                    DESERIALIZE MACROS
// -------------------------------------------------------------------
#define UCDR_SEQUENCE_DESERIALIZE_DEFINITION(TYPE, SIZE) \
    bool ucdr_deserialize_sequence_ ## TYPE(ucdrBuffer* ub, TYPE* array, const uint32_t array_capacity, uint32_t* size) \
    { \
        ucdr_deserialize_sequence_header(ub, ub->endianness, array_capacity, size); \
        return ucdr_deserialize_endian_array_ ## TYPE(ub, ub->endianness, array, *size); \
    } \
    bool ucdr_deserialize_endian_sequence_ ## TYPE(ucdrBuffer* ub, const ucdrEndianness endianness, TYPE* array, const uint32_t array_capacity, uint32_t* size) \
    { \
        ucdr_deserialize_sequence_header(ub, endianness, array_capacity, size); \
        return ucdr_deserialize_endian_array_ ## TYPE(ub, endianness, array, *size); \
    } \

// -------------------------------------------------------------------
//                         DEFINITION MACRO
// -------------------------------------------------------------------
#define UCDR_SEQUENCE_DEFINITIONS(TYPE, SIZE) \
    UCDR_SEQUENCE_SERIALIZE_DEFINITION(TYPE, SIZE) \
    UCDR_SEQUENCE_DESERIALIZE_DEFINITION(TYPE, SIZE) \

// -------------------------------------------------------------------
//              PUBLIC DE-SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------
UCDR_SEQUENCE_DEFINITIONS(char, 1)
UCDR_SEQUENCE_DEFINITIONS(bool, 1)
UCDR_SEQUENCE_DEFINITIONS(uint8_t, 1)
UCDR_SEQUENCE_DEFINITIONS(uint16_t, 2)
UCDR_SEQUENCE_DEFINITIONS(uint32_t, 4)
UCDR_SEQUENCE_DEFINITIONS(uint64_t, 8)
UCDR_SEQUENCE_DEFINITIONS(int8_t, 1)
UCDR_SEQUENCE_DEFINITIONS(int16_t, 2)
UCDR_SEQUENCE_DEFINITIONS(int32_t, 4)
UCDR_SEQUENCE_DEFINITIONS(int64_t, 8)
UCDR_SEQUENCE_DEFINITIONS(float, 4)
UCDR_SEQUENCE_DEFINITIONS(double, 8)
