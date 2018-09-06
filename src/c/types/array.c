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

#include <microcdr/types/basics.h>
#include <microcdr/types/array.h>

#include <string.h>

// -------------------------------------------------------------------
//              INTERNAL SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------

bool serialize_array_byte_1(MicroBuffer* buffer, const uint8_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_size(buffer, size))
    {
        memcpy(buffer->iterator, array, size);

        buffer->iterator += size;
        buffer->last_data_size = data_size;
        return true;
    }
    buffer->error = BUFFER_NOK;
    return false;
}

bool serialize_array_byte_2(MicroBuffer* buffer, const Endianness endianness, const uint16_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint16_t));

    if(check_size(buffer, alignment + array_size))
    {
        buffer->iterator += alignment;
        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(buffer->iterator, array, array_size);

            buffer->iterator += array_size;
            buffer->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_2(buffer, endianness, array + i);
            }
        }
        return true;
    }
    buffer->error = BUFFER_NOK;
    return false;
}

bool serialize_array_byte_4(MicroBuffer* buffer, const Endianness endianness, const uint32_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint32_t));

    if(check_size(buffer, alignment + array_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(buffer->iterator, array, array_size);
            buffer->iterator += array_size;
            buffer->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_4(buffer, endianness, array + i);
            }
        }
        return true;
    }
    buffer->error = BUFFER_NOK;
    return false;
}

bool serialize_array_byte_8(MicroBuffer* buffer, const Endianness endianness, const uint64_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint64_t));

    if(check_size(buffer, alignment + array_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(buffer->iterator, array, array_size);
            buffer->iterator += array_size;
            buffer->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_8(buffer, endianness, array + i);
            }
        }
        return true;
    }
    buffer->error = BUFFER_NOK;
    return false;
}

bool deserialize_array_byte_1(MicroBuffer* buffer, uint8_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_size(buffer, size))
    {
        memcpy(array, buffer->iterator, size);

        buffer->iterator += size;
        buffer->last_data_size = data_size;
        return true;
    }
    buffer->error = BUFFER_NOK;
    return false;
}

bool deserialize_array_byte_2(MicroBuffer* buffer, const Endianness endianness, uint16_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint16_t));

    if(check_size(buffer, alignment + array_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, buffer->iterator, array_size);
            buffer->iterator += array_size;
            buffer->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                deserialize_byte_2(buffer, endianness, array + i);
            }
        }
        return true;
    }
    buffer->error = BUFFER_NOK;
    return false;
}

bool deserialize_array_byte_4(MicroBuffer* buffer, const Endianness endianness, uint32_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint32_t));

    if(check_size(buffer, alignment + array_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, buffer->iterator, array_size);
            buffer->iterator += array_size;
            buffer->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                deserialize_byte_4(buffer, endianness, array + i);
            }
        }
        return true;
    }
    buffer->error = BUFFER_NOK;
    return false;
}

bool deserialize_array_byte_8(MicroBuffer* buffer, const Endianness endianness, uint64_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint64_t));

    if(check_size(buffer, alignment + array_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, buffer->iterator, array_size);
            buffer->iterator += array_size;
            buffer->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                deserialize_byte_8(buffer, endianness, array + i);
            }
        }
        return true;
    }
    buffer->error = BUFFER_NOK;
    return false;
}

// -------------------------------------------------------------------
//              PUBLIC SERIALIZATION IMPLEMENTATIONS
// -------------------------------------------------------------------

bool serialize_array_char(MicroBuffer* buffer, const char* array, const uint32_t size)
{
    return serialize_array_byte_1(buffer, (uint8_t*)array, size);
}

bool serialize_array_bool(MicroBuffer* buffer, const bool* array, const uint32_t size)
{
    return serialize_array_byte_1(buffer, (uint8_t*)array, size);
}

bool serialize_array_uint8_t(MicroBuffer* buffer, const uint8_t* array, const uint32_t size)
{
    return serialize_array_byte_1(buffer, array, size);
}

bool serialize_array_uint16_t(MicroBuffer* buffer, const uint16_t* array, const uint32_t size)
{
    return serialize_array_byte_2(buffer, buffer->endianness, array, size);
}

bool serialize_array_uint32_t(MicroBuffer* buffer, const uint32_t* array, const uint32_t size)
{
    return serialize_array_byte_4(buffer, buffer->endianness, array, size);
}

bool serialize_array_uint64_t(MicroBuffer* buffer, const uint64_t* array, const uint32_t size)
{
    return serialize_array_byte_8(buffer, buffer->endianness, array, size);
}

bool serialize_array_int8_t(MicroBuffer* buffer, const int8_t* array, const uint32_t size)
{
    return serialize_array_byte_1(buffer, (uint8_t*)array, size);
}

bool serialize_array_int16_t(MicroBuffer* buffer, const int16_t* array, const uint32_t size)
{
    return serialize_array_byte_2(buffer, buffer->endianness, (uint16_t*)array, size);
}

bool serialize_array_int32_t(MicroBuffer* buffer, const int32_t* array, const uint32_t size)
{
    return serialize_array_byte_4(buffer, buffer->endianness, (uint32_t*)array, size);
}

bool serialize_array_int64_t(MicroBuffer* buffer, const int64_t* array, const uint32_t size)
{
    return serialize_array_byte_8(buffer, buffer->endianness, (uint64_t*)array, size);
}

bool serialize_array_float(MicroBuffer* buffer, const float* array, const uint32_t size)
{
    return serialize_array_byte_4(buffer, buffer->endianness, (uint32_t*)array, size);
}

bool serialize_array_double(MicroBuffer* buffer, const double* array, const uint32_t size)
{
    return serialize_array_byte_8(buffer, buffer->endianness, (uint64_t*)array, size);
}

bool deserialize_array_char(MicroBuffer* buffer, char* array, const uint32_t size)
{
    return deserialize_array_byte_1(buffer, (uint8_t*)array, size);
}

bool deserialize_array_bool(MicroBuffer* buffer, bool* array, const uint32_t size)
{
    return deserialize_array_byte_1(buffer, (uint8_t*)array, size);
}

bool deserialize_array_uint8_t(MicroBuffer* buffer, uint8_t* array, const uint32_t size)
{
    return deserialize_array_byte_1(buffer, array, size);
}

bool deserialize_array_uint16_t(MicroBuffer* buffer, uint16_t* array, const uint32_t size)
{
    return deserialize_array_byte_2(buffer, buffer->endianness, array, size);
}

bool deserialize_array_uint32_t(MicroBuffer* buffer, uint32_t* array, const uint32_t size)
{
    return deserialize_array_byte_4(buffer, buffer->endianness, array, size);
}

bool deserialize_array_uint64_t(MicroBuffer* buffer, uint64_t* array, const uint32_t size)
{
    return deserialize_array_byte_8(buffer, buffer->endianness, array, size);
}

bool deserialize_array_int8_t(MicroBuffer* buffer, int8_t* array, const uint32_t size)
{
    return deserialize_array_byte_1(buffer, (uint8_t*)array, size);
}

bool deserialize_array_int16_t(MicroBuffer* buffer, int16_t* array, const uint32_t size)
{
    return deserialize_array_byte_2(buffer, buffer->endianness, (uint16_t*)array, size);
}

bool deserialize_array_int32_t(MicroBuffer* buffer, int32_t* array, const uint32_t size)
{
    return deserialize_array_byte_4(buffer, buffer->endianness, (uint32_t*)array, size);
}

bool deserialize_array_int64_t(MicroBuffer* buffer, int64_t* array, const uint32_t size)
{
    return deserialize_array_byte_8(buffer, buffer->endianness, (uint64_t*)array, size);
}

bool deserialize_array_float(MicroBuffer* buffer, float* array, const uint32_t size)
{
    return deserialize_array_byte_4(buffer, buffer->endianness, (uint32_t*)array, size);
}

bool deserialize_array_double(MicroBuffer* buffer, double* array, const uint32_t size)
{
    return deserialize_array_byte_8(buffer, buffer->endianness, (uint64_t*)array, size);
}

bool serialize_endian_array_uint16_t(MicroBuffer* buffer, const Endianness endianness, const uint16_t* array, const uint32_t size)
{
    return serialize_array_byte_2(buffer, endianness, array, size);
}

bool serialize_endian_array_uint32_t(MicroBuffer* buffer, const Endianness endianness, const uint32_t* array, const uint32_t size)
{
    return serialize_array_byte_4(buffer, endianness, array, size);
}

bool serialize_endian_array_uint64_t(MicroBuffer* buffer, const Endianness endianness, const uint64_t* array, const uint32_t size)
{
    return serialize_array_byte_8(buffer, endianness, array, size);
}

bool serialize_endian_array_int16_t(MicroBuffer* buffer, const Endianness endianness, const int16_t* array, const uint32_t size)
{
    return serialize_array_byte_2(buffer, endianness, (uint16_t*)array, size);
}

bool serialize_endian_array_int32_t(MicroBuffer* buffer, const Endianness endianness, const int32_t* array, const uint32_t size)
{
    return serialize_array_byte_4(buffer, endianness, (uint32_t*)array, size);
}

bool serialize_endian_array_int64_t(MicroBuffer* buffer, const Endianness endianness, const int64_t* array, const uint32_t size)
{
    return serialize_array_byte_8(buffer, endianness, (uint64_t*)array, size);
}

bool serialize_endian_array_float(MicroBuffer* buffer, const Endianness endianness, const float* array, const uint32_t size)
{
    return serialize_array_byte_4(buffer, endianness, (uint32_t*)array, size);
}

bool serialize_endian_array_double(MicroBuffer* buffer, const Endianness endianness, const double* array, const uint32_t size)
{
    return serialize_array_byte_8(buffer, endianness, (uint64_t*)array, size);
}

bool deserialize_endian_array_uint16_t(MicroBuffer* buffer, const Endianness endianness, uint16_t* array, const uint32_t size)
{
    return deserialize_array_byte_2(buffer, endianness, array, size);
}

bool deserialize_endian_array_uint32_t(MicroBuffer* buffer, const Endianness endianness, uint32_t* array, const uint32_t size)
{
    return deserialize_array_byte_4(buffer, endianness, array, size);
}

bool deserialize_endian_array_uint64_t(MicroBuffer* buffer, const Endianness endianness, uint64_t* array, const uint32_t size)
{
    return deserialize_array_byte_8(buffer, endianness, array, size);
}

bool deserialize_endian_array_int16_t(MicroBuffer* buffer, const Endianness endianness, int16_t* array, const uint32_t size)
{
    return deserialize_array_byte_2(buffer, endianness, (uint16_t*)array, size);
}

bool deserialize_endian_array_int32_t(MicroBuffer* buffer, const Endianness endianness, int32_t* array, const uint32_t size)
{
    return deserialize_array_byte_4(buffer, endianness, (uint32_t*)array, size);
}

bool deserialize_endian_array_int64_t(MicroBuffer* buffer, const Endianness endianness, int64_t* array, const uint32_t size)
{
    return deserialize_array_byte_8(buffer, endianness, (uint64_t*)array, size);
}

bool deserialize_endian_array_float(MicroBuffer* buffer, const Endianness endianness, float* array, const uint32_t size)
{
    return deserialize_array_byte_4(buffer, endianness, (uint32_t*)array, size);
}

bool deserialize_endian_array_double(MicroBuffer* buffer, const Endianness endianness, double* array, const uint32_t size)
{
    return deserialize_array_byte_8(buffer, endianness, (uint64_t*)array, size);
}

