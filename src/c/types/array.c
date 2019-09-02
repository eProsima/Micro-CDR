// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include "../common_internal.h"

#include <string.h>

static void ucdr_array_to_buffer(
        ucdrStream* us,
        const uint8_t* array,
        size_t size);

static void ucdr_buffer_to_array(
        ucdrStream* us,
        uint8_t* array,
        size_t size);

// -------------------------------------------------------------------
//                         SERIALIZE MACROS
// -------------------------------------------------------------------
void ucdr_array_to_buffer(
        ucdrStream* us,
        const uint8_t* array,
        size_t size)
{
    size_t remaining_size = size;
    do
    {
        size_t buffer_available_size = ucdr_buffer_remaining_size(us);
        if (remaining_size <= buffer_available_size)
        {
            memcpy(us->iterator, array + (size - remaining_size), remaining_size);
            ucdr_advance_stream(us, size);
            remaining_size = 0;
        }
        else
        {
            memcpy(us->iterator, array + (size - remaining_size), buffer_available_size);
            ucdr_promote_buffer(us);
            remaining_size -= buffer_available_size;
        }

    } while (remaining_size > 0);
}

void ucdr_buffer_to_array(
        ucdrStream* us,
        uint8_t* array,
        size_t size)
{
    size_t remaining_size = size;
    do
    {
        size_t buffer_available_size = ucdr_buffer_remaining_size(us);
        if (remaining_size <= buffer_available_size)
        {
            memcpy(array + (size - remaining_size), us->iterator, remaining_size);
            ucdr_advance_stream(us, size);
            remaining_size = 0;
        }
        else
        {
            memcpy(array + (size - remaining_size), us->iterator, buffer_available_size);
            ucdr_promote_buffer(us);
            remaining_size -= buffer_available_size;
        }

    } while (remaining_size > 0);
}

#define UCDR_SERIALIZE_ARRAY_BYTE_1(TYPE, ENDIAN) \
    (void)ENDIAN; \
    if (ucdr_enough_space(us, size)) \
    { \
        ucdr_array_to_buffer(us, (uint8_t*)array, size); \
    } \
    else \
    { \
        us->error = true; \
    } \

#define UCDR_SERIALIZE_ARRAY_BYTE_N(TYPE, TYPE_SIZE, ENDIAN) \
    if (ucdr_enough_space(us, size * TYPE_SIZE)) \
    { \
        if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
        { \
            ucdr_array_to_buffer(us, (uint8_t*)array, size * TYPE_SIZE); \
        } \
        else \
        { \
            for(uint32_t i = 0; i < size; ++i) \
            { \
                ucdr_serialize_endian_ ## TYPE(us, ENDIAN, *(array + i)); \
            } \
        } \
    } \
    else \
    { \
        us->error = true; \
    } \

#define UCDR_SERIALIZE_ARRAY_BYTE_2(TYPE, ENDIAN) UCDR_SERIALIZE_ARRAY_BYTE_N(TYPE, 2, ENDIAN)
#define UCDR_SERIALIZE_ARRAY_BYTE_4(TYPE, ENDIAN) UCDR_SERIALIZE_ARRAY_BYTE_N(TYPE, 4, ENDIAN)
#define UCDR_SERIALIZE_ARRAY_BYTE_8(TYPE, ENDIAN) UCDR_SERIALIZE_ARRAY_BYTE_N(TYPE, 8, ENDIAN)

#define UCDR_SERIALIZE_ARRAY_DEFINITION(SUFFIX, TYPE, TYPE_SIZE) \
    bool ucdr_serialize_array ## SUFFIX(ucdrStream* us, const TYPE* array, size_t size) \
    { \
        if (!us->error) \
        { \
            UCDR_SERIALIZE_ARRAY_BYTE_ ## TYPE_SIZE(TYPE, us->endianness) \
        } \
        return !us->error; \
    } \
    bool ucdr_serialize_endian_array ## SUFFIX(ucdrStream* us, const ucdrEndianness endianness, const TYPE* array, size_t size) \
    { \
        if (!us->error) \
        { \
            UCDR_SERIALIZE_ARRAY_BYTE_ ## TYPE_SIZE(TYPE, endianness) \
        } \
        return !us->error; \
    } \

// -------------------------------------------------------------------
//                         DESERIALIZE MACROS
// -------------------------------------------------------------------
#define UCDR_DESERIALIZE_ARRAY_BYTE_1(TYPE, ENDIAN) \
    (void)ENDIAN; \
    if (ucdr_enough_space(us, size)) \
    { \
        ucdr_buffer_to_array(us, (uint8_t*)array, size); \
    } \
    else \
    { \
        us->error = true; \
    } \

#define UCDR_DESERIALIZE_ARRAY_BYTE_N(TYPE, TYPE_SIZE, ENDIAN) \
    if (ucdr_enough_space(us, size * TYPE_SIZE)) \
    { \
        if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
        { \
            ucdr_buffer_to_array(us, (uint8_t*)array, size * TYPE_SIZE); \
        } \
        else \
        { \
            for(uint32_t i = 0; i < size; ++i) \
            { \
                ucdr_deserialize_endian_ ## TYPE(us, ENDIAN, array + i); \
            } \
        } \
    } \
    else \
    { \
        us->error = true; \
    } \

#define UCDR_DESERIALIZE_ARRAY_BYTE_2(TYPE, ENDIAN) UCDR_DESERIALIZE_ARRAY_BYTE_N(TYPE, 2, ENDIAN)
#define UCDR_DESERIALIZE_ARRAY_BYTE_4(TYPE, ENDIAN) UCDR_DESERIALIZE_ARRAY_BYTE_N(TYPE, 4, ENDIAN)
#define UCDR_DESERIALIZE_ARRAY_BYTE_8(TYPE, ENDIAN) UCDR_DESERIALIZE_ARRAY_BYTE_N(TYPE, 8, ENDIAN)

#define UCDR_DESERIALIZE_ARRAY_DEFINITION(SUFFIX, TYPE, TYPE_SIZE) \
    bool ucdr_deserialize_array ## SUFFIX(ucdrStream* us, TYPE* array, size_t size) \
    { \
        if (!us->error) \
        { \
            UCDR_DESERIALIZE_ARRAY_BYTE_ ## TYPE_SIZE(TYPE, us->endianness) \
        } \
        return !us->error; \
    } \
    bool ucdr_deserialize_endian_array ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, TYPE* array, size_t size) \
    { \
        if (!us->error) \
        { \
            UCDR_DESERIALIZE_ARRAY_BYTE_ ## TYPE_SIZE(TYPE, endianness) \
        } \
        return !us->error; \
    }

// -------------------------------------------------------------------
//                         DEFINITION MACRO
// -------------------------------------------------------------------
#define UCDR_ARRAY_DEFINITIONS(SUFFIX, TYPE, TYPE_SIZE) \
    UCDR_SERIALIZE_ARRAY_DEFINITION(SUFFIX, TYPE, TYPE_SIZE) \
    UCDR_DESERIALIZE_ARRAY_DEFINITION(SUFFIX, TYPE, TYPE_SIZE) \

// -------------------------------------------------------------------
//              PUBLIC SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------
UCDR_ARRAY_DEFINITIONS(_char, char, 1)
UCDR_ARRAY_DEFINITIONS(_bool, bool, 1)
UCDR_ARRAY_DEFINITIONS(_uint8_t, uint8_t, 1)
UCDR_ARRAY_DEFINITIONS(_uint16_t, uint16_t, 2)
UCDR_ARRAY_DEFINITIONS(_uint32_t, uint32_t, 4)
UCDR_ARRAY_DEFINITIONS(_uint64_t, uint64_t, 8)
UCDR_ARRAY_DEFINITIONS(_int8_t, int8_t, 1)
UCDR_ARRAY_DEFINITIONS(_int16_t, int16_t, 2)
UCDR_ARRAY_DEFINITIONS(_int32_t, int32_t, 4)
UCDR_ARRAY_DEFINITIONS(_int64_t, int64_t, 8)
UCDR_ARRAY_DEFINITIONS(_float, float, 4)
UCDR_ARRAY_DEFINITIONS(_double, double, 8)
