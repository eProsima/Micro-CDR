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

#include "../common_internal.h"

#include <string.h>

// -------------------------------------------------------------------
//                    SERIALIZE MACROS
// -------------------------------------------------------------------
#define UCDR_SERIALIZE_BYTE_1(TYPE, ENDIAN) \
    (void)ENDIAN; \
    if (ucdr_enough_space(us, 1)) \
    { \
        bool serialized = false; \
        do \
        { \
            if (1 <= ucdr_buffer_remaining_size(us)) \
            { \
                *us->iterator = (uint8_t)value; \
                ucdr_advance_stream(us, 1); \
                serialized = true; \
            } \
            else \
            { \
                ucdr_promote_buffer(us); \
            } \
        } while (!serialized); \
    } \
    else \
    { \
        us->error = true; \
    } \

#define UCDR_SERIALIZE_BYTE_N(TYPE, SIZE, ENDIAN) \
    if(ucdr_enough_space(us, SIZE)) \
    { \
        if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
        { \
            size_t remaining_size = SIZE; \
            do \
            { \
                size_t buffer_available_size = ucdr_buffer_remaining_size(us); \
                if (remaining_size <= buffer_available_size) \
                { \
                    memcpy(us->iterator, (uint8_t*)&value + (SIZE - remaining_size), remaining_size); \
                    ucdr_advance_stream(us, remaining_size); \
                    remaining_size = 0; \
                } \
                else \
                { \
                    memcpy(us->iterator, (uint8_t*)&value + (SIZE - remaining_size), buffer_available_size); \
                    ucdr_promote_buffer(us); \
                    remaining_size -= buffer_available_size; \
                } \
            } while (remaining_size > 0); \
        } \
        else \
        { \
            const uint8_t* bytes_pointer = (uint8_t*)&value; \
            size_t remaining_size = SIZE; \
            do \
            { \
                size_t buffer_available_size = ucdr_buffer_remaining_size(us); \
                if (remaining_size <= buffer_available_size) \
                { \
                    for (size_t i = (SIZE - remaining_size); i < SIZE; ++i) \
                    { \
                        *(us->iterator + i) = *(bytes_pointer + SIZE - i - 1); \
                    } \
                    ucdr_advance_stream(us, remaining_size); \
                    remaining_size = 0; \
                } \
                else \
                { \
                    for (size_t i = (SIZE - remaining_size); i < (SIZE - remaining_size) + buffer_available_size; ++i) \
                    { \
                        *(us->iterator + i) = *(bytes_pointer + SIZE - i - 1); \
                    } \
                    ucdr_promote_buffer(us); \
                    remaining_size -= buffer_available_size; \
                } \
            } while (remaining_size > 0); \
        } \
    } \
    else \
    { \
        us->error = true; \
    } \

#define UCDR_SERIALIZE_BYTE_2(TYPE, ENDIAN) UCDR_SERIALIZE_BYTE_N(TYPE, 2, ENDIAN)
#define UCDR_SERIALIZE_BYTE_4(TYPE, ENDIAN) UCDR_SERIALIZE_BYTE_N(TYPE, 4, ENDIAN)
#define UCDR_SERIALIZE_BYTE_8(TYPE, ENDIAN) UCDR_SERIALIZE_BYTE_N(TYPE, 8, ENDIAN)

#define UCDR_BASIC_TYPE_SERIALIZE_DEFINITION(SUFFIX, TYPE, SIZE) \
    bool ucdr_serialize ## SUFFIX(ucdrStream* us, TYPE value) \
    { \
        if (!us->error) \
        { \
            UCDR_SERIALIZE_BYTE_ ## SIZE(TYPE, us->endianness) \
        } \
        return !us->error; \
    } \
    bool ucdr_serialize_endian ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, TYPE value) \
    { \
        if (!us->error) \
        { \
            UCDR_SERIALIZE_BYTE_ ## SIZE(TYPE, endianness) \
        } \
        return !us->error; \
    }

// -------------------------------------------------------------------
//                    DESERIALIZE MACROS
// -------------------------------------------------------------------
#define UCDR_DESERIALIZE_BYTE_1(TYPE, ENDIAN) \
    (void)ENDIAN; \
    if(ucdr_enough_space(us, 1)) \
    { \
        bool serialized = false; \
        do \
        { \
            if (1 <= ucdr_buffer_remaining_size(us)) \
            { \
                *value = (TYPE)*us->iterator; \
                ucdr_advance_stream(us, 1); \
                serialized = true; \
            } \
            else \
            { \
                ucdr_promote_buffer(us); \
            } \
        } while (!serialized); \
    } \
    else \
    { \
        us->error = true; \
    } \

#define UCDR_DESERIALIZE_BYTE_N(TYPE, SIZE, ENDIAN) \
    if(ucdr_enough_space(us, SIZE)) \
    { \
        if(UCDR_MACHINE_ENDIANNESS == ENDIAN) \
        { \
            size_t remaining_size = SIZE; \
            do \
            { \
                size_t buffer_available_size = ucdr_buffer_remaining_size(us); \
                if (remaining_size <= buffer_available_size) \
                { \
                    memcpy((uint8_t*)value + (SIZE - remaining_size), us->iterator, remaining_size); \
                    ucdr_advance_stream(us, remaining_size); \
                    remaining_size = 0; \
                } \
                else \
                { \
                    memcpy((uint8_t*)value + (SIZE - remaining_size), us->iterator, buffer_available_size); \
                    ucdr_promote_buffer(us); \
                    remaining_size -= buffer_available_size; \
                } \
            } while (remaining_size > 0); \
        } \
        else \
        { \
            uint8_t* bytes_pointer = (uint8_t*)value; \
            size_t remaining_size = SIZE; \
            do \
            { \
                size_t buffer_available_size = ucdr_buffer_remaining_size(us); \
                if (remaining_size <= buffer_available_size) \
                { \
                    for (size_t i = (SIZE - remaining_size); i < SIZE; ++i) \
                    { \
                        *(bytes_pointer + i) = *(us->iterator + SIZE - i - 1); \
                    } \
                    ucdr_advance_stream(us, remaining_size); \
                    remaining_size = 0; \
                } \
                else \
                { \
                    for (size_t i = (SIZE - remaining_size); i < (SIZE - remaining_size) + buffer_available_size; ++i) \
                    { \
                        *(bytes_pointer + i) = *(us->iterator + SIZE - i - 1); \
                    } \
                    ucdr_promote_buffer(us); \
                    remaining_size -= buffer_available_size; \
                } \
            } while (remaining_size > 0); \
        } \
    } \
    return !us->error;

#define UCDR_DESERIALIZE_BYTE_2(TYPE, ENDIAN) UCDR_DESERIALIZE_BYTE_N(TYPE, 2, ENDIAN)
#define UCDR_DESERIALIZE_BYTE_4(TYPE, ENDIAN) UCDR_DESERIALIZE_BYTE_N(TYPE, 4, ENDIAN)
#define UCDR_DESERIALIZE_BYTE_8(TYPE, ENDIAN) UCDR_DESERIALIZE_BYTE_N(TYPE, 8, ENDIAN)

#define UCDR_BASIC_TYPE_DESERIALIZE_DEFINITION(SUFFIX, TYPE, SIZE) \
    bool ucdr_deserialize ## SUFFIX(ucdrStream* us, TYPE* value) \
    { \
        if (!us->error) \
        { \
            UCDR_DESERIALIZE_BYTE_ ## SIZE(TYPE, us->endianness) \
        } \
        return !us->error; \
    } \
    bool ucdr_deserialize_endian ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, TYPE* value) \
    { \
        if (!us->error) \
        { \
            UCDR_DESERIALIZE_BYTE_ ## SIZE(TYPE, endianness) \
        } \
        return !us->error; \
    }

// -------------------------------------------------------------------
//                         DEFINITION MACRO
// -------------------------------------------------------------------
#define UCDR_BASIC_TYPE_DEFINITIONS(SUFFIX, TYPE, SIZE) \
    UCDR_BASIC_TYPE_SERIALIZE_DEFINITION(SUFFIX, TYPE, SIZE) \
    UCDR_BASIC_TYPE_DESERIALIZE_DEFINITION(SUFFIX, TYPE, SIZE) \

// -------------------------------------------------------------------
//              PUBLIC DE-SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------
UCDR_BASIC_TYPE_DEFINITIONS(_char, char, 1)
UCDR_BASIC_TYPE_DEFINITIONS(_bool, bool, 1)
UCDR_BASIC_TYPE_DEFINITIONS(_uint8_t, uint8_t, 1)
UCDR_BASIC_TYPE_DEFINITIONS(_uint16_t, uint16_t, 2)
UCDR_BASIC_TYPE_DEFINITIONS(_uint32_t, uint32_t, 4)
UCDR_BASIC_TYPE_DEFINITIONS(_uint64_t, uint64_t, 8)
UCDR_BASIC_TYPE_DEFINITIONS(_int8_t, int8_t, 1)
UCDR_BASIC_TYPE_DEFINITIONS(_int16_t, int16_t, 2)
UCDR_BASIC_TYPE_DEFINITIONS(_int32_t, int32_t, 4)
UCDR_BASIC_TYPE_DEFINITIONS(_int64_t, int64_t, 8)
UCDR_BASIC_TYPE_DEFINITIONS(_float, float, 4)
UCDR_BASIC_TYPE_DEFINITIONS(_double, double, 8)
