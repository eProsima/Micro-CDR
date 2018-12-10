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

#include "../common_internals.h"
#include "array_internals.h"
#include "basic_internals.h"

#include <string.h>

static void ucdr_array_to_buffer(ucdrBuffer* ub, const uint8_t* array, const uint32_t size, const uint32_t data_size);
static void ucdr_buffer_to_array(ucdrBuffer* ub, uint8_t* array, const uint32_t size, const uint32_t data_size);

// -------------------------------------------------------------------
//                INTERNAL SERIALIZATION IMPLEMENTATION
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

bool ucdr_serialize_array_byte_1(ucdrBuffer* ub, const uint8_t* array, const uint32_t size)
{
    ucdr_array_to_buffer(ub, array, size, 1);
    return !ub->error;
}

bool ucdr_serialize_array_byte_2(ucdrBuffer* ub, const ucdrEndianness endianness, const uint16_t* array, const uint32_t size)
{
    ub->iterator += ucdr_buffer_alignment(ub, 2);

    if(UCDR_MACHINE_ENDIANNESS == endianness)
    {
        ucdr_array_to_buffer(ub, (uint8_t*)array, size * 2, 2);
    }
    else
    {
        for(uint32_t i = 0; i < size; i++)
        {
            ucdr_serialize_byte_2(ub, endianness, array + i);
        }
    }

    return !ub->error;
}

bool ucdr_serialize_array_byte_4(ucdrBuffer* ub, const ucdrEndianness endianness, const uint32_t* array, const uint32_t size)
{
    ub->iterator += ucdr_buffer_alignment(ub, 4);

    if(UCDR_MACHINE_ENDIANNESS == endianness)
    {
        ucdr_array_to_buffer(ub, (uint8_t*)array, size * 4, 4);
    }
    else
    {
        for(uint32_t i = 0; i < size; i++)
        {
            ucdr_serialize_byte_4(ub, endianness, array + i);
        }
    }

    return !ub->error;
}

bool ucdr_serialize_array_byte_8(ucdrBuffer* ub, const ucdrEndianness endianness, const uint64_t* array, const uint32_t size)
{
    ub->iterator += ucdr_buffer_alignment(ub, 8);

    if(UCDR_MACHINE_ENDIANNESS == endianness)
    {
        ucdr_array_to_buffer(ub, (uint8_t*)array, size * 8, 8);
    }
    else
    {
        for(uint32_t i = 0; i < size; i++)
        {
            ucdr_serialize_byte_8(ub, endianness, array + i);
        }
    }
    return !ub->error;
}

bool ucdr_deserialize_array_byte_1(ucdrBuffer* ub, uint8_t* array, const uint32_t size)
{
    ucdr_buffer_to_array(ub, array, size, 1);
    return !ub->error;
}

bool ucdr_deserialize_array_byte_2(ucdrBuffer* ub, const ucdrEndianness endianness, uint16_t* array, const uint32_t size)
{
    ub->iterator += ucdr_buffer_alignment(ub, 2);

    if(UCDR_MACHINE_ENDIANNESS == endianness)
    {
        ucdr_buffer_to_array(ub, (uint8_t*)array, size * 2, 2);
    }
    else
    {
        for(uint32_t i = 0; i < size; i++)
        {
            ucdr_deserialize_byte_2(ub, endianness, array + i);
        }
    }

    return !ub->error;
}

bool ucdr_deserialize_array_byte_4(ucdrBuffer* ub, const ucdrEndianness endianness, uint32_t* array, const uint32_t size)
{
    ub->iterator += ucdr_buffer_alignment(ub, 4);

    if(UCDR_MACHINE_ENDIANNESS == endianness)
    {
        ucdr_buffer_to_array(ub, (uint8_t*)array, size * 4, 4);
    }
    else
    {
        for(uint32_t i = 0; i < size; i++)
        {
            ucdr_deserialize_byte_4(ub, endianness, array + i);
        }
    }

    return !ub->error;
}

bool ucdr_deserialize_array_byte_8(ucdrBuffer* ub, const ucdrEndianness endianness, uint64_t* array, const uint32_t size)
{
    ub->iterator += ucdr_buffer_alignment(ub, 8);

    if(UCDR_MACHINE_ENDIANNESS == endianness)
    {
        ucdr_buffer_to_array(ub, (uint8_t*)array, size * 8, 8);
    }
    else
    {
        for(uint32_t i = 0; i < size; i++)
        {
            ucdr_deserialize_byte_8(ub, endianness, array + i);
        }
    }

    return !ub->error;
}

// -------------------------------------------------------------------
//              PUBLIC SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------

bool ucdr_serialize_array_char(ucdrBuffer* ub, const char* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_1(ub, (uint8_t*)array, size);
}

bool ucdr_serialize_array_bool(ucdrBuffer* ub, const bool* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_1(ub, (uint8_t*)array, size);
}

bool ucdr_serialize_array_uint8_t(ucdrBuffer* ub, const uint8_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_1(ub, array, size);
}

bool ucdr_serialize_array_uint16_t(ucdrBuffer* ub, const uint16_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_2(ub, ub->endianness, array, size);
}

bool ucdr_serialize_array_uint32_t(ucdrBuffer* ub, const uint32_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_4(ub, ub->endianness, array, size);
}

bool ucdr_serialize_array_uint64_t(ucdrBuffer* ub, const uint64_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_8(ub, ub->endianness, array, size);
}

bool ucdr_serialize_array_int8_t(ucdrBuffer* ub, const int8_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_1(ub, (uint8_t*)array, size);
}

bool ucdr_serialize_array_int16_t(ucdrBuffer* ub, const int16_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_2(ub, ub->endianness, (uint16_t*)array, size);
}

bool ucdr_serialize_array_int32_t(ucdrBuffer* ub, const int32_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_4(ub, ub->endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_array_int64_t(ucdrBuffer* ub, const int64_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_8(ub, ub->endianness, (uint64_t*)array, size);
}

bool ucdr_serialize_array_float(ucdrBuffer* ub, const float* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_4(ub, ub->endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_array_double(ucdrBuffer* ub, const double* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_8(ub, ub->endianness, (uint64_t*)array, size);
}

bool ucdr_deserialize_array_char(ucdrBuffer* ub, char* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_1(ub, (uint8_t*)array, size);
}

bool ucdr_deserialize_array_bool(ucdrBuffer* ub, bool* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_1(ub, (uint8_t*)array, size);
}

bool ucdr_deserialize_array_uint8_t(ucdrBuffer* ub, uint8_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_1(ub, array, size);
}

bool ucdr_deserialize_array_uint16_t(ucdrBuffer* ub, uint16_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_2(ub, ub->endianness, array, size);
}

bool ucdr_deserialize_array_uint32_t(ucdrBuffer* ub, uint32_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_4(ub, ub->endianness, array, size);
}

bool ucdr_deserialize_array_uint64_t(ucdrBuffer* ub, uint64_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_8(ub, ub->endianness, array, size);
}

bool ucdr_deserialize_array_int8_t(ucdrBuffer* ub, int8_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_1(ub, (uint8_t*)array, size);
}

bool ucdr_deserialize_array_int16_t(ucdrBuffer* ub, int16_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_2(ub, ub->endianness, (uint16_t*)array, size);
}

bool ucdr_deserialize_array_int32_t(ucdrBuffer* ub, int32_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_4(ub, ub->endianness, (uint32_t*)array, size);
}

bool ucdr_deserialize_array_int64_t(ucdrBuffer* ub, int64_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_8(ub, ub->endianness, (uint64_t*)array, size);
}

bool ucdr_deserialize_array_float(ucdrBuffer* ub, float* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_4(ub, ub->endianness, (uint32_t*)array, size);
}

bool ucdr_deserialize_array_double(ucdrBuffer* ub, double* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_8(ub, ub->endianness, (uint64_t*)array, size);
}

bool ucdr_serialize_endian_array_uint16_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint16_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_2(ub, endianness, array, size);
}

bool ucdr_serialize_endian_array_uint32_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint32_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_4(ub, endianness, array, size);
}

bool ucdr_serialize_endian_array_uint64_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint64_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_8(ub, endianness, array, size);
}

bool ucdr_serialize_endian_array_int16_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int16_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_2(ub, endianness, (uint16_t*)array, size);
}

bool ucdr_serialize_endian_array_int32_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int32_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_4(ub, endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_endian_array_int64_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int64_t* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_8(ub, endianness, (uint64_t*)array, size);
}

bool ucdr_serialize_endian_array_float(ucdrBuffer* ub, const ucdrEndianness endianness, const float* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_4(ub, endianness, (uint32_t*)array, size);
}

bool ucdr_serialize_endian_array_double(ucdrBuffer* ub, const ucdrEndianness endianness, const double* array, const uint32_t size)
{
    return ucdr_serialize_array_byte_8(ub, endianness, (uint64_t*)array, size);
}

bool ucdr_deserialize_endian_array_uint16_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint16_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_2(ub, endianness, array, size);
}

bool ucdr_deserialize_endian_array_uint32_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint32_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_4(ub, endianness, array, size);
}

bool ucdr_deserialize_endian_array_uint64_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint64_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_8(ub, endianness, array, size);
}

bool ucdr_deserialize_endian_array_int16_t(ucdrBuffer* ub, const ucdrEndianness endianness, int16_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_2(ub, endianness, (uint16_t*)array, size);
}

bool ucdr_deserialize_endian_array_int32_t(ucdrBuffer* ub, const ucdrEndianness endianness, int32_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_4(ub, endianness, (uint32_t*)array, size);
}

bool ucdr_deserialize_endian_array_int64_t(ucdrBuffer* ub, const ucdrEndianness endianness, int64_t* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_8(ub, endianness, (uint64_t*)array, size);
}

bool ucdr_deserialize_endian_array_float(ucdrBuffer* ub, const ucdrEndianness endianness, float* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_4(ub, endianness, (uint32_t*)array, size);
}

bool ucdr_deserialize_endian_array_double(ucdrBuffer* ub, const ucdrEndianness endianness, double* array, const uint32_t size)
{
    return ucdr_deserialize_array_byte_8(ub, endianness, (uint64_t*)array, size);
}

