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

#include <ucdr/types/array.h>
#include <ucdr/types/basic.h>
#include "../common_internals.h"

#include <string.h>

static void ucdr_array_to_buffer(ucdrBuffer* ub, const uint8_t* array, const uint32_t size, const uint32_t data_size);
static void ucdr_buffer_to_array(ucdrBuffer* ub, uint8_t* array, const uint32_t size, const uint32_t data_size);

// -------------------------------------------------------------------
//                         SERIALIZE MACROS
// -------------------------------------------------------------------
void ucdr_array_to_buffer(ucdrBuffer* ub, const uint8_t* array, const uint32_t size, const uint32_t data_size)
{
    if(ucdr_check_buffer_available_for(ub, size))
    {
        memcpy(ub->iterator, array, size);
        ub->iterator += size;
    }
    else
    {
        uint32_t remaining_size = size;
        uint32_t serialization_size;
        while(0 < (serialization_size = ucdr_check_final_buffer_behavior_array(ub, remaining_size, data_size)))
        {
            memcpy(ub->iterator, array + (size - remaining_size), serialization_size);
            remaining_size -= serialization_size;
            ub->iterator += serialization_size;
        }
    }
    ub->last_data_size = data_size;
}

void ucdr_buffer_to_array(ucdrBuffer* ub, uint8_t* array, const uint32_t size, const uint32_t data_size)
{
    if(ucdr_check_buffer_available_for(ub, size))
    {
        memcpy(array, ub->iterator, size);
        ub->iterator += size;
    }
    else
    {
        uint32_t remaining_size = size;
        uint32_t deserialization_size;
        while(0 < (deserialization_size = ucdr_check_final_buffer_behavior_array(ub, remaining_size, data_size)))
        {
            memcpy(array + (size - remaining_size), ub->iterator, deserialization_size);
            remaining_size -= deserialization_size;
            ub->iterator += deserialization_size;
        }
    }
    ub->last_data_size = data_size;
}

#define UCDR_SERIALIZE_ARRAY_BYTE_1(TYPE, ENDIAN) \
    (void)ENDIAN; \
    ucdr_array_to_buffer(ub, (uint8_t*)array, size, 1); \
    return !ub->error;

#define UCDR_SERIALIZE_ARRAY_BYTE_N(TYPE, BASE_TYPE, SIZE, ENDIAN) \
    ub->iterator += ucdr_buffer_alignment(ub, (uint32_t)SIZE); \
    if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
    { \
        ucdr_array_to_buffer(ub, (uint8_t*)array, size * SIZE, SIZE); \
    } \
    else \
    { \
        for(uint32_t i = 0; i < size; ++i) \
        { \
            ucdr_serialize_endian_ ## TYPE(ub, ENDIAN, *(array + i)); \
        } \
    } \
    return !ub->error;

#define UCDR_SERIALIZE_ARRAY_BYTE_2(TYPE, ENDIAN) UCDR_SERIALIZE_ARRAY_BYTE_N(TYPE, uint16_t, 2, ENDIAN)
#define UCDR_SERIALIZE_ARRAY_BYTE_4(TYPE, ENDIAN) UCDR_SERIALIZE_ARRAY_BYTE_N(TYPE, uint32_t, 4, ENDIAN)
#define UCDR_SERIALIZE_ARRAY_BYTE_8(TYPE, ENDIAN) UCDR_SERIALIZE_ARRAY_BYTE_N(TYPE, uint64_t, 8, ENDIAN)

#define UCDR_SERIALIZE_ARRAY_DEFINITION(TYPE, SIZE) \
    bool ucdr_serialize_array_ ## TYPE (ucdrBuffer* ub, const TYPE * array, const uint32_t size) \
    { \
        UCDR_SERIALIZE_ARRAY_BYTE_ ## SIZE (TYPE, ub->endianness) \
    } \
    bool ucdr_serialize_endian_array_ ## TYPE (ucdrBuffer* ub, const ucdrEndianness endianness, const TYPE * array, const uint32_t size) \
    { \
        UCDR_SERIALIZE_ARRAY_BYTE_ ## SIZE (TYPE, endianness) \
    } \

// -------------------------------------------------------------------
//                         DESERIALIZE MACROS
// -------------------------------------------------------------------
#define UCDR_DESERIALIZE_ARRAY_BYTE_1(TYPE, ENDIAN) \
    (void)ENDIAN; \
    ucdr_buffer_to_array(ub, array, size, 1); \
    return !ub->error;

#define UCDR_DESERIALIZE_ARRAY_BYTE_N(TYPE, BASE_TYPE, SIZE, ENDIAN) \
    ub->iterator += ucdr_buffer_alignment(ub, (uint32_t)SIZE); \
    if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
    { \
        ucdr_buffer_to_array(ub, (uint8_t*)array, size * SIZE, SIZE); \
    } \
    else \
    { \
        for(uint32_t i = 0; i < size; i++) \
        { \
            ucdr_deserialize_endian_ ## TYPE(ub, ENDIAN, array + i); \
        } \
    } \
    return !ub->error;

#define UCDR_DESERIALIZE_ARRAY_BYTE_2(TYPE, ENDIAN) UCDR_DESERIALIZE_ARRAY_BYTE_N(TYPE, 2, ENDIAN)
#define UCDR_DESERIALIZE_ARRAY_BYTE_4(TYPE, ENDIAN) UCDR_DESERIALIZE_ARRAY_BYTE_N(TYPE, 4, ENDIAN)
#define UCDR_DESERIALIZE_ARRAY_BYTE_8(TYPE, ENDIAN) UCDR_DESERIALIZE_ARRAY_BYTE_N(TYPE, 8, ENDIAN)

#define UCDR_DESERIALIZE_ARRAY_DEFINITION(TYPE, SIZE) \
    bool ucdr_deserialize_array_ ## TYPE(ucdrBuffer* ub, TYPE * array, const uint32_t size) \
    { \
        UCDR_DESERIALIZE_ARRAY_BYTE_ ## SIZE (TYPE, ub->endianness) \
    } \
    bool ucdr_deserialize_endian_array_ ## TYPE(ucdrBuffer* ub, const ucdrEndianness endianness, TYPE * array, const uint32_t size) \
    { \
        UCDR_DESERIALIZE_ARRAY_BYTE_ ## SIZE(TYPE, endianness) \
    }

// -------------------------------------------------------------------
//                         DEFINITION MACRO
// -------------------------------------------------------------------
#define UCDR_ARRAY_DEFINITIONS(TYPE, SIZE) \
    UCDR_SERIALIZE_ARRAY_DEFINITION(TYPE, SIZE) \
    UCDR_DESERIALIZE_ARRAY_DEFINITION(TYPE, SIZE) \

// -------------------------------------------------------------------
//              PUBLIC SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------
UCDR_ARRAY_DEFINITIONS(char, 1)
UCDR_ARRAY_DEFINITIONS(bool, 1)
UCDR_ARRAY_DEFINITIONS(uint8_t, 1)
UCDR_ARRAY_DEFINITIONS(uint16_t, 2)
UCDR_ARRAY_DEFINITIONS(uint32_t, 4)
UCDR_ARRAY_DEFINITIONS(uint64_t, 8)
UCDR_ARRAY_DEFINITIONS(int8_t, 1)
UCDR_ARRAY_DEFINITIONS(int16_t, 2)
UCDR_ARRAY_DEFINITIONS(int32_t, 4)
UCDR_ARRAY_DEFINITIONS(int64_t, 8)
UCDR_ARRAY_DEFINITIONS(float, 4)
UCDR_ARRAY_DEFINITIONS(double, 8)
