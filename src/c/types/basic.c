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
#include "../common_internals.h"

#include <string.h>

// -------------------------------------------------------------------
//                    SERIALIZE MACROS
// -------------------------------------------------------------------
#define UCDR_SERIALIZE_BYTE_1(TYPE, ENDIAN) \
    (void)ENDIAN; \
    if(ucdr_check_final_buffer_behavior(ub, (uint32_t)1)) \
    { \
        *ub->iterator = (uint8_t)value; \
        ub->iterator += (uint32_t)1; \
        ub->last_data_size = (uint32_t)1; \
    } \
    return !ub->error;

#define UCDR_SERIALIZE_BYTE_2_CORE() \
    uint8_t* bytes_pointer = (uint8_t*)&value; \
    *ub->iterator = *(bytes_pointer + 1); \
    *(ub->iterator + 1) = *bytes_pointer;

#define UCDR_SERIALIZE_BYTE_4_CORE() \
    uint8_t* bytes_pointer = (uint8_t*)&value; \
    *ub->iterator = *(bytes_pointer + 3); \
    *(ub->iterator + 1) = *(bytes_pointer + 2); \
    *(ub->iterator + 2) = *(bytes_pointer + 1); \
    *(ub->iterator + 3) = *bytes_pointer;

#define UCDR_SERIALIZE_BYTE_8_CORE() \
    uint8_t* bytes_pointer = (uint8_t*)&value; \
    *ub->iterator = *(bytes_pointer + 7); \
    *(ub->iterator + 1) = *(bytes_pointer + 6); \
    *(ub->iterator + 2) = *(bytes_pointer + 5); \
    *(ub->iterator + 3) = *(bytes_pointer + 4); \
    *(ub->iterator + 4) = *(bytes_pointer + 3); \
    *(ub->iterator + 5) = *(bytes_pointer + 2); \
    *(ub->iterator + 6) = *(bytes_pointer + 1); \
    *(ub->iterator + 7) = *bytes_pointer;

#define UCDR_SERIALIZE_BYTE_N(TYPE, SIZE, ENDIAN) \
    ub->iterator += ucdr_buffer_alignment(ub, (uint32_t)SIZE); \
    if(ucdr_check_final_buffer_behavior(ub, alignment + (uint32_t)SIZE)) \
    { \
        if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
        { \
            memcpy(ub->iterator, (void*)&value, (size_t)SIZE); \
        } \
        else \
        { \
            UCDR_SERIALIZE_BYTE_ ## SIZE ## _CORE() \
        } \
        ub->iterator += (uint32_t)SIZE; \
        ub->last_data_size = (uint32_t)SIZE; \
    } \
    return !ub->error;

#define UCDR_SERIALIZE_BYTE_2(TYPE, ENDIAN) UCDR_SERIALIZE_BYTE_N(TYPE, 2, ENDIAN)
#define UCDR_SERIALIZE_BYTE_4(TYPE, ENDIAN) UCDR_SERIALIZE_BYTE_N(TYPE, 4, ENDIAN)
#define UCDR_SERIALIZE_BYTE_8(TYPE, ENDIAN) UCDR_SERIALIZE_BYTE_N(TYPE, 8, ENDIAN)

#define UCDR_BASIC_TYPE_SERIALIZE_DEFINITION(TYPE, SIZE) \
    bool ucdr_serialize_ ## TYPE(ucdrBuffer* ub, const TYPE value) \
    { \
        UCDR_SERIALIZE_BYTE_ ## SIZE(TYPE, ub->endianness) \
    } \
    bool ucdr_serialize_endian_ ## TYPE(ucdrBuffer* ub, const ucdrEndianness endianness, const TYPE value) \
    { \
        UCDR_SERIALIZE_BYTE_ ## SIZE(TYPE, endianness) \
    }

// -------------------------------------------------------------------
//                    DESERIALIZE MACROS
// -------------------------------------------------------------------
#define UCDR_DESERIALIZE_BYTE_1(TYPE, ENDIAN) \
    (void)ENDIAN; \
    if(ucdr_check_final_buffer_behavior(ub, (uint32_t)1)) \
    { \
        *value = (TYPE)*ub->iterator; \
        ub->iterator += (uint32_t)1; \
        ub->last_data_size = (uint32_t)1; \
    } \
    return !ub->error;

#define UCDR_DESERIALIZE_BYTE_2_CORE() \
    uint8_t* bytes_pointer = (uint8_t*)value; \
    *bytes_pointer = *(ub->iterator + 1); \
    *(bytes_pointer + 1) = *ub->iterator ; \

#define UCDR_DESERIALIZE_BYTE_4_CORE() \
    uint8_t* bytes_pointer = (uint8_t*)value; \
    *bytes_pointer = *(ub->iterator + 3); \
    *(bytes_pointer + 1) = *(ub->iterator + 2); \
    *(bytes_pointer + 2) = *(ub->iterator + 1); \
    *(bytes_pointer + 3) = *ub->iterator;

#define UCDR_DESERIALIZE_BYTE_8_CORE() \
    uint8_t* bytes_pointer = (uint8_t*)value; \
    *bytes_pointer = *(ub->iterator + 7); \
    *(bytes_pointer + 1) = *(ub->iterator + 6); \
    *(bytes_pointer + 2) = *(ub->iterator + 5); \
    *(bytes_pointer + 3) = *(ub->iterator + 4); \
    *(bytes_pointer + 4) = *(ub->iterator + 3); \
    *(bytes_pointer + 5) = *(ub->iterator + 2); \
    *(bytes_pointer + 6) = *(ub->iterator + 1); \
    *(bytes_pointer + 7) = *ub->iterator;

#define UCDR_DESERIALIZE_BYTE_N(TYPE, SIZE, ENDIAN) \
    ub->iterator += ucdr_buffer_alignment(ub, (uint32_t)SIZE); \
    if(ucdr_check_final_buffer_behavior(ub, alignment + (uint32_t)SIZE)) \
    { \
        ub->iterator += alignment; \
        if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
        { \
            memcpy((void*)value, ub->iterator, (size_t)SIZE); \
        } \
        else \
        { \
            UCDR_DESERIALIZE_BYTE_ ## SIZE ## _CORE() \
        } \
        ub->iterator += (uint32_t)SIZE; \
        ub->last_data_size = (uint32_t)SIZE; \
    } \
    return !ub->error;

#define UCDR_DESERIALIZE_BYTE_2(TYPE, ENDIAN) UCDR_DESERIALIZE_BYTE_N(TYPE, 2, ENDIAN)
#define UCDR_DESERIALIZE_BYTE_4(TYPE, ENDIAN) UCDR_DESERIALIZE_BYTE_N(TYPE, 4, ENDIAN)
#define UCDR_DESERIALIZE_BYTE_8(TYPE, ENDIAN) UCDR_DESERIALIZE_BYTE_N(TYPE, 8, ENDIAN)

#define UCDR_BASIC_TYPE_DESERIALIZE_DEFINITION(TYPE, SIZE) \
    bool ucdr_deserialize_ ## TYPE(ucdrBuffer* ub, TYPE* value) \
    { \
        UCDR_DESERIALIZE_BYTE_ ## SIZE(TYPE, ub->endianness) \
    } \
    bool ucdr_deserialize_endian_ ## TYPE(ucdrBuffer* ub, const ucdrEndianness endianness, TYPE* value) \
    { \
        UCDR_DESERIALIZE_BYTE_ ## SIZE(TYPE, endianness) \
    }

// -------------------------------------------------------------------
//                         DEFINITION MACRO
// -------------------------------------------------------------------
#define UCDR_BASIC_TYPE_DEFINITIONS(TYPE, SIZE) \
    UCDR_BASIC_TYPE_SERIALIZE_DEFINITION(TYPE, SIZE) \
    UCDR_BASIC_TYPE_DESERIALIZE_DEFINITION(TYPE, SIZE) \

// -------------------------------------------------------------------
//              PUBLIC DE-SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------
UCDR_BASIC_TYPE_DEFINITIONS(char, 1)
UCDR_BASIC_TYPE_DEFINITIONS(bool, 1)
UCDR_BASIC_TYPE_DEFINITIONS(uint8_t, 1)
UCDR_BASIC_TYPE_DEFINITIONS(uint16_t, 2)
UCDR_BASIC_TYPE_DEFINITIONS(uint32_t, 4)
UCDR_BASIC_TYPE_DEFINITIONS(uint64_t, 8)
UCDR_BASIC_TYPE_DEFINITIONS(int8_t, 1)
UCDR_BASIC_TYPE_DEFINITIONS(int16_t, 2)
UCDR_BASIC_TYPE_DEFINITIONS(int32_t, 4)
UCDR_BASIC_TYPE_DEFINITIONS(int64_t, 8)
UCDR_BASIC_TYPE_DEFINITIONS(float, 4)
UCDR_BASIC_TYPE_DEFINITIONS(double, 8)
