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

#include <microcdr/types/array.h>

#include "../common_internals.h"
#include "array_internals.h"
#include "basic_internals.h"

#include <string.h>

// -------------------------------------------------------------------
//                INTERNAL SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------

bool serialize_array_byte_1(mcMicroBuffer* mb, const uint8_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_buffer(mb, size))
    {
        memcpy(mb->iterator, array, size);

        mb->iterator += size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool serialize_array_byte_2(mcMicroBuffer* mb, const Endianness endianness, const uint16_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint16_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;
        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, array, array_size);

            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_2(mb, endianness, array + i);
            }
        }
    }
    return !mb->error;
}

bool serialize_array_byte_4(mcMicroBuffer* mb, const Endianness endianness, const uint32_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint32_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, array, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_4(mb, endianness, array + i);
            }
        }
    }
    return !mb->error;
}

bool serialize_array_byte_8(mcMicroBuffer* mb, const Endianness endianness, const uint64_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint64_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, array, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_8(mb, endianness, array + i);
            }
        }
    }
    return !mb->error;
}

bool mc_deserialize_array_byte_1(mcMicroBuffer* mb, uint8_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_buffer(mb, size))
    {
        memcpy(array, mb->iterator, size);

        mb->iterator += size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool mc_deserialize_array_byte_2(mcMicroBuffer* mb, const Endianness endianness, uint16_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint16_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, mb->iterator, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                mc_deserialize_byte_2(mb, endianness, array + i);
            }
        }
    }
    return !mb->error;
}

bool mc_deserialize_array_byte_4(mcMicroBuffer* mb, const Endianness endianness, uint32_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint32_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, mb->iterator, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                mc_deserialize_byte_4(mb, endianness, array + i);
            }
        }
    }
    return !mb->error;
}

bool mc_deserialize_array_byte_8(mcMicroBuffer* mb, const Endianness endianness, uint64_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint64_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, mb->iterator, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                mc_deserialize_byte_8(mb, endianness, array + i);
            }
        }
    }
    return !mb->error;
}

// -------------------------------------------------------------------
//              PUBLIC SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------

bool serialize_array_char(mcMicroBuffer* mb, const char* array, const uint32_t size)
{
    return serialize_array_byte_1(mb, (uint8_t*)array, size);
}

bool serialize_array_bool(mcMicroBuffer* mb, const bool* array, const uint32_t size)
{
    return serialize_array_byte_1(mb, (uint8_t*)array, size);
}

bool serialize_array_uint8_t(mcMicroBuffer* mb, const uint8_t* array, const uint32_t size)
{
    return serialize_array_byte_1(mb, array, size);
}

bool serialize_array_uint16_t(mcMicroBuffer* mb, const uint16_t* array, const uint32_t size)
{
    return serialize_array_byte_2(mb, mb->endianness, array, size);
}

bool serialize_array_uint32_t(mcMicroBuffer* mb, const uint32_t* array, const uint32_t size)
{
    return serialize_array_byte_4(mb, mb->endianness, array, size);
}

bool serialize_array_uint64_t(mcMicroBuffer* mb, const uint64_t* array, const uint32_t size)
{
    return serialize_array_byte_8(mb, mb->endianness, array, size);
}

bool serialize_array_int8_t(mcMicroBuffer* mb, const int8_t* array, const uint32_t size)
{
    return serialize_array_byte_1(mb, (uint8_t*)array, size);
}

bool serialize_array_int16_t(mcMicroBuffer* mb, const int16_t* array, const uint32_t size)
{
    return serialize_array_byte_2(mb, mb->endianness, (uint16_t*)array, size);
}

bool serialize_array_int32_t(mcMicroBuffer* mb, const int32_t* array, const uint32_t size)
{
    return serialize_array_byte_4(mb, mb->endianness, (uint32_t*)array, size);
}

bool serialize_array_int64_t(mcMicroBuffer* mb, const int64_t* array, const uint32_t size)
{
    return serialize_array_byte_8(mb, mb->endianness, (uint64_t*)array, size);
}

bool serialize_array_float(mcMicroBuffer* mb, const float* array, const uint32_t size)
{
    return serialize_array_byte_4(mb, mb->endianness, (uint32_t*)array, size);
}

bool serialize_array_double(mcMicroBuffer* mb, const double* array, const uint32_t size)
{
    return serialize_array_byte_8(mb, mb->endianness, (uint64_t*)array, size);
}

bool mc_deserialize_array_char(mcMicroBuffer* mb, char* array, const uint32_t size)
{
    return mc_deserialize_array_byte_1(mb, (uint8_t*)array, size);
}

bool mc_deserialize_array_bool(mcMicroBuffer* mb, bool* array, const uint32_t size)
{
    return mc_deserialize_array_byte_1(mb, (uint8_t*)array, size);
}

bool mc_deserialize_array_uint8_t(mcMicroBuffer* mb, uint8_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_1(mb, array, size);
}

bool mc_deserialize_array_uint16_t(mcMicroBuffer* mb, uint16_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_2(mb, mb->endianness, array, size);
}

bool mc_deserialize_array_uint32_t(mcMicroBuffer* mb, uint32_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_4(mb, mb->endianness, array, size);
}

bool mc_deserialize_array_uint64_t(mcMicroBuffer* mb, uint64_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_8(mb, mb->endianness, array, size);
}

bool mc_deserialize_array_int8_t(mcMicroBuffer* mb, int8_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_1(mb, (uint8_t*)array, size);
}

bool mc_deserialize_array_int16_t(mcMicroBuffer* mb, int16_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_2(mb, mb->endianness, (uint16_t*)array, size);
}

bool mc_deserialize_array_int32_t(mcMicroBuffer* mb, int32_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_4(mb, mb->endianness, (uint32_t*)array, size);
}

bool mc_deserialize_array_int64_t(mcMicroBuffer* mb, int64_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_8(mb, mb->endianness, (uint64_t*)array, size);
}

bool mc_deserialize_array_float(mcMicroBuffer* mb, float* array, const uint32_t size)
{
    return mc_deserialize_array_byte_4(mb, mb->endianness, (uint32_t*)array, size);
}

bool mc_deserialize_array_double(mcMicroBuffer* mb, double* array, const uint32_t size)
{
    return mc_deserialize_array_byte_8(mb, mb->endianness, (uint64_t*)array, size);
}

bool serialize_endian_array_uint16_t(mcMicroBuffer* mb, const Endianness endianness, const uint16_t* array, const uint32_t size)
{
    return serialize_array_byte_2(mb, endianness, array, size);
}

bool serialize_endian_array_uint32_t(mcMicroBuffer* mb, const Endianness endianness, const uint32_t* array, const uint32_t size)
{
    return serialize_array_byte_4(mb, endianness, array, size);
}

bool serialize_endian_array_uint64_t(mcMicroBuffer* mb, const Endianness endianness, const uint64_t* array, const uint32_t size)
{
    return serialize_array_byte_8(mb, endianness, array, size);
}

bool serialize_endian_array_int16_t(mcMicroBuffer* mb, const Endianness endianness, const int16_t* array, const uint32_t size)
{
    return serialize_array_byte_2(mb, endianness, (uint16_t*)array, size);
}

bool serialize_endian_array_int32_t(mcMicroBuffer* mb, const Endianness endianness, const int32_t* array, const uint32_t size)
{
    return serialize_array_byte_4(mb, endianness, (uint32_t*)array, size);
}

bool serialize_endian_array_int64_t(mcMicroBuffer* mb, const Endianness endianness, const int64_t* array, const uint32_t size)
{
    return serialize_array_byte_8(mb, endianness, (uint64_t*)array, size);
}

bool serialize_endian_array_float(mcMicroBuffer* mb, const Endianness endianness, const float* array, const uint32_t size)
{
    return serialize_array_byte_4(mb, endianness, (uint32_t*)array, size);
}

bool serialize_endian_array_double(mcMicroBuffer* mb, const Endianness endianness, const double* array, const uint32_t size)
{
    return serialize_array_byte_8(mb, endianness, (uint64_t*)array, size);
}

bool mc_deserialize_endian_array_uint16_t(mcMicroBuffer* mb, const Endianness endianness, uint16_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_2(mb, endianness, array, size);
}

bool mc_deserialize_endian_array_uint32_t(mcMicroBuffer* mb, const Endianness endianness, uint32_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_4(mb, endianness, array, size);
}

bool mc_deserialize_endian_array_uint64_t(mcMicroBuffer* mb, const Endianness endianness, uint64_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_8(mb, endianness, array, size);
}

bool mc_deserialize_endian_array_int16_t(mcMicroBuffer* mb, const Endianness endianness, int16_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_2(mb, endianness, (uint16_t*)array, size);
}

bool mc_deserialize_endian_array_int32_t(mcMicroBuffer* mb, const Endianness endianness, int32_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_4(mb, endianness, (uint32_t*)array, size);
}

bool mc_deserialize_endian_array_int64_t(mcMicroBuffer* mb, const Endianness endianness, int64_t* array, const uint32_t size)
{
    return mc_deserialize_array_byte_8(mb, endianness, (uint64_t*)array, size);
}

bool mc_deserialize_endian_array_float(mcMicroBuffer* mb, const Endianness endianness, float* array, const uint32_t size)
{
    return mc_deserialize_array_byte_4(mb, endianness, (uint32_t*)array, size);
}

bool mc_deserialize_endian_array_double(mcMicroBuffer* mb, const Endianness endianness, double* array, const uint32_t size)
{
    return mc_deserialize_array_byte_8(mb, endianness, (uint64_t*)array, size);
}

