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
#include "../common_internals.h"
#include "basic_internals.h"

#include <string.h>


// -------------------------------------------------------------------
//                INTERNAL SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------

bool serialize_byte_1(MicroBuffer* mb, const uint8_t* byte)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_buffer(mb, data_size))
    {
        *mb->iterator = *byte;

        mb->iterator += data_size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool serialize_byte_2(MicroBuffer* mb, const Endianness endianness, const uint16_t* bytes)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *mb->iterator = *(bytes_pointer + 1);
            *(mb->iterator + 1) = *bytes_pointer;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool serialize_byte_4(MicroBuffer* mb, const Endianness endianness, const uint32_t* bytes)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *mb->iterator = *(bytes_pointer + 3);
            *(mb->iterator + 1) = *(bytes_pointer + 2);
            *(mb->iterator + 2) = *(bytes_pointer + 1);
            *(mb->iterator + 3) = *bytes_pointer;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool serialize_byte_8(MicroBuffer* mb, const Endianness endianness, const uint64_t* bytes)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *mb->iterator = *(bytes_pointer + 7);
            *(mb->iterator + 1) = *(bytes_pointer + 6);
            *(mb->iterator + 2) = *(bytes_pointer + 5);
            *(mb->iterator + 3) = *(bytes_pointer + 4);
            *(mb->iterator + 4) = *(bytes_pointer + 3);
            *(mb->iterator + 5) = *(bytes_pointer + 2);
            *(mb->iterator + 6) = *(bytes_pointer + 1);
            *(mb->iterator + 7) = *bytes_pointer;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool deserialize_byte_1(MicroBuffer* mb, uint8_t* byte)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_buffer(mb, data_size))
    {
        *byte = *mb->iterator;

        mb->iterator += data_size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool deserialize_byte_2(MicroBuffer* mb, const Endianness endianness, uint16_t* bytes)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, mb->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(mb->iterator + 1);
            *(bytes_pointer + 1) = *mb->iterator ;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool deserialize_byte_4(MicroBuffer* mb, const Endianness endianness, uint32_t* bytes)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, mb->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(mb->iterator + 3);
            *(bytes_pointer + 1) = *(mb->iterator + 2);
            *(bytes_pointer + 2) = *(mb->iterator + 1);
            *(bytes_pointer + 3) = *mb->iterator;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

bool deserialize_byte_8(MicroBuffer* mb, const Endianness endianness, uint64_t* bytes)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, mb->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(mb->iterator + 7);
            *(bytes_pointer + 1) = *(mb->iterator + 6);
            *(bytes_pointer + 2) = *(mb->iterator + 5);
            *(bytes_pointer + 3) = *(mb->iterator + 4);
            *(bytes_pointer + 4) = *(mb->iterator + 3);
            *(bytes_pointer + 5) = *(mb->iterator + 2);
            *(bytes_pointer + 6) = *(mb->iterator + 1);
            *(bytes_pointer + 7) = *mb->iterator;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
    }
    return !mb->error;
}

// -------------------------------------------------------------------
//                  PUBLIC SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------

bool serialize_char(MicroBuffer* mb, const char value)
{
    return serialize_byte_1(mb, (uint8_t*)&value);
}

bool serialize_bool(MicroBuffer* mb, const bool value)
{
    return serialize_byte_1(mb, (uint8_t*)&value);
}

bool serialize_uint8_t(MicroBuffer* mb, const uint8_t value)
{
    return serialize_byte_1(mb, &value);
}

bool serialize_uint16_t(MicroBuffer* mb, const uint16_t value)
{
    return serialize_byte_2(mb, mb->endianness, &value);
}

bool serialize_uint32_t(MicroBuffer* mb, const uint32_t value)
{
    return serialize_byte_4(mb, mb->endianness, &value);
}

bool serialize_uint64_t(MicroBuffer* mb, const uint64_t value)
{
    return serialize_byte_8(mb, mb->endianness, &value);
}

bool serialize_int8_t(MicroBuffer* mb, const int8_t value)
{
    return serialize_byte_1(mb, (uint8_t*)&value);
}

bool serialize_int16_t(MicroBuffer* mb, const int16_t value)
{
    return serialize_byte_2(mb, mb->endianness, (uint16_t*)&value);
}

bool serialize_int32_t(MicroBuffer* mb, const int32_t value)
{
    return serialize_byte_4(mb, mb->endianness, (uint32_t*)&value);
}

bool serialize_int64_t(MicroBuffer* mb, const int64_t value)
{
    return serialize_byte_8(mb, mb->endianness, (uint64_t*)&value);
}

bool serialize_float(MicroBuffer* mb, const float value)
{
    return serialize_byte_4(mb, mb->endianness, (uint32_t*)&value);
}

bool serialize_double(MicroBuffer* mb, const double value)
{
    return serialize_byte_8(mb, mb->endianness, (uint64_t*)&value);
}

bool deserialize_char(MicroBuffer* mb, char* value)
{
    return deserialize_byte_1(mb, (uint8_t*)value);
}

bool deserialize_bool(MicroBuffer* mb, bool* value)
{
    return deserialize_byte_1(mb, (uint8_t*)value);
}

bool deserialize_uint8_t(MicroBuffer* mb, uint8_t* value)
{
    return deserialize_byte_1(mb, value);
}

bool deserialize_uint16_t(MicroBuffer* mb, uint16_t* value)
{
    return deserialize_byte_2(mb, mb->endianness, value);
}

bool deserialize_uint32_t(MicroBuffer* mb, uint32_t* value)
{
    return deserialize_byte_4(mb, mb->endianness, value);
}

bool deserialize_uint64_t(MicroBuffer* mb, uint64_t* value)
{
    return deserialize_byte_8(mb, mb->endianness, value);
}

bool deserialize_int8_t(MicroBuffer* mb, int8_t* value)
{
    return deserialize_byte_1(mb, (uint8_t*)value);
}

bool deserialize_int16_t(MicroBuffer* mb, int16_t* value)
{
    return deserialize_byte_2(mb, mb->endianness, (uint16_t*)value);
}

bool deserialize_int32_t(MicroBuffer* mb, int32_t* value)
{
    return deserialize_byte_4(mb, mb->endianness, (uint32_t*)value);
}

bool deserialize_int64_t(MicroBuffer* mb, int64_t* value)
{
    return deserialize_byte_8(mb, mb->endianness, (uint64_t*)value);
}

bool deserialize_float(MicroBuffer* mb, float* value)
{
    return deserialize_byte_4(mb, mb->endianness, (uint32_t*)value);
}

bool deserialize_double(MicroBuffer* mb, double* value)
{
    return deserialize_byte_8(mb, mb->endianness, (uint64_t*)value);
}

bool serialize_endian_uint16_t(MicroBuffer* mb, const Endianness endianness, const uint16_t value)
{
    return serialize_byte_2(mb, endianness, &value);
}

bool serialize_endian_uint32_t(MicroBuffer* mb, const Endianness endianness, const uint32_t value)
{
    return serialize_byte_4(mb, endianness, &value);
}

bool serialize_endian_uint64_t(MicroBuffer* mb, const Endianness endianness, const uint64_t value)
{
    return serialize_byte_8(mb, endianness, &value);
}

bool serialize_endian_int16_t(MicroBuffer* mb, const Endianness endianness, const int16_t value)
{
    return serialize_byte_2(mb, endianness, (uint16_t*)&value);
}

bool serialize_endian_int32_t(MicroBuffer* mb, const Endianness endianness, const int32_t value)
{
    return serialize_byte_4(mb, endianness, (uint32_t*)&value);
}

bool serialize_endian_int64_t(MicroBuffer* mb, const Endianness endianness, const int64_t value)
{
    return serialize_byte_8(mb, endianness, (uint64_t*)&value);
}

bool serialize_endian_float(MicroBuffer* mb, const Endianness endianness, const float value)
{
    return serialize_byte_4(mb, endianness, (uint32_t*)&value);
}

bool serialize_endian_double(MicroBuffer* mb, const Endianness endianness, const double value)
{
    return serialize_byte_8(mb, endianness, (uint64_t*)&value);
}

bool deserialize_endian_uint16_t(MicroBuffer* mb, const Endianness endianness, uint16_t* value)
{
    return deserialize_byte_2(mb, endianness, value);
}

bool deserialize_endian_uint32_t(MicroBuffer* mb, const Endianness endianness, uint32_t* value)
{
    return deserialize_byte_4(mb, endianness, value);
}

bool deserialize_endian_uint64_t(MicroBuffer* mb, const Endianness endianness, uint64_t* value)
{
    return deserialize_byte_8(mb, endianness, value);
}

bool deserialize_endian_int16_t(MicroBuffer* mb, const Endianness endianness, int16_t* value)
{
    return deserialize_byte_2(mb, endianness, (uint16_t*)value);
}

bool deserialize_endian_int32_t(MicroBuffer* mb, const Endianness endianness, int32_t* value)
{
    return deserialize_byte_4(mb, endianness, (uint32_t*)value);
}

bool deserialize_endian_int64_t(MicroBuffer* mb, const Endianness endianness, int64_t* value)
{
    return deserialize_byte_8(mb, endianness, (uint64_t*)value);
}

bool deserialize_endian_float(MicroBuffer* mb, const Endianness endianness, float* value)
{
    return deserialize_byte_4(mb, endianness, (uint32_t*)value);
}

bool deserialize_endian_double(MicroBuffer* mb, const Endianness endianness, double* value)
{
    return deserialize_byte_8(mb, endianness, (uint64_t*)value);
}

