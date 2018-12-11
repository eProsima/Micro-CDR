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
#include "basic_internals.h"

#include <string.h>


// -------------------------------------------------------------------
//                INTERNAL SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------

bool ucdr_serialize_byte_1(ucdrBuffer* ub, const uint8_t* byte)
{
    const uint32_t data_size = 1;

    if(ucdr_check_final_buffer_behavior(ub, data_size))
    {
        *ub->iterator = *byte;

        ub->iterator += data_size;
        ub->last_data_size = data_size;
    }
    return !ub->error;
}

bool ucdr_serialize_byte_2(ucdrBuffer* ub, const ucdrEndianness endianness, const uint16_t* bytes)
{
    const uint32_t data_size = 2;

    ub->iterator += ucdr_buffer_alignment(ub, data_size);

    if(ucdr_check_final_buffer_behavior(ub, data_size))
    {
        if(UCDR_MACHINE_ENDIANNESS == endianness)
        {
            memcpy(ub->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *ub->iterator = *(bytes_pointer + 1);
            *(ub->iterator + 1) = *bytes_pointer;
        }

        ub->iterator += data_size;
        ub->last_data_size = data_size;
    }
    return !ub->error;
}

bool ucdr_serialize_byte_4(ucdrBuffer* ub, const ucdrEndianness endianness, const uint32_t* bytes)
{
    const uint32_t data_size = 4;

    ub->iterator += ucdr_buffer_alignment(ub, data_size);

    if(ucdr_check_final_buffer_behavior(ub, data_size))
    {
        if(UCDR_MACHINE_ENDIANNESS == endianness)
        {
            memcpy(ub->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *ub->iterator = *(bytes_pointer + 3);
            *(ub->iterator + 1) = *(bytes_pointer + 2);
            *(ub->iterator + 2) = *(bytes_pointer + 1);
            *(ub->iterator + 3) = *bytes_pointer;
        }

        ub->iterator += data_size;
        ub->last_data_size = data_size;
    }
    return !ub->error;
}

bool ucdr_serialize_byte_8(ucdrBuffer* ub, const ucdrEndianness endianness, const uint64_t* bytes)
{
    const uint32_t data_size = 8;

    ub->iterator += ucdr_buffer_alignment(ub, data_size);

    if(ucdr_check_final_buffer_behavior(ub, data_size))
    {
        if(UCDR_MACHINE_ENDIANNESS == endianness)
        {
            memcpy(ub->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *ub->iterator = *(bytes_pointer + 7);
            *(ub->iterator + 1) = *(bytes_pointer + 6);
            *(ub->iterator + 2) = *(bytes_pointer + 5);
            *(ub->iterator + 3) = *(bytes_pointer + 4);
            *(ub->iterator + 4) = *(bytes_pointer + 3);
            *(ub->iterator + 5) = *(bytes_pointer + 2);
            *(ub->iterator + 6) = *(bytes_pointer + 1);
            *(ub->iterator + 7) = *bytes_pointer;
        }

        ub->iterator += data_size;
        ub->last_data_size = data_size;
    }
    return !ub->error;
}

bool ucdr_deserialize_byte_1(ucdrBuffer* ub, uint8_t* byte)
{
    const uint32_t data_size = 1;

    if(ucdr_check_final_buffer_behavior(ub, data_size))
    {
        *byte = *ub->iterator;

        ub->iterator += data_size;
        ub->last_data_size = data_size;
    }
    return !ub->error;
}

bool ucdr_deserialize_byte_2(ucdrBuffer* ub, const ucdrEndianness endianness, uint16_t* bytes)
{
    const uint32_t data_size = 2;

    ub->iterator += ucdr_buffer_alignment(ub, data_size);

    if(ucdr_check_final_buffer_behavior(ub, data_size))
    {
        if(UCDR_MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, ub->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(ub->iterator + 1);
            *(bytes_pointer + 1) = *ub->iterator ;
        }

        ub->iterator += data_size;
        ub->last_data_size = data_size;
    }
    return !ub->error;
}

bool ucdr_deserialize_byte_4(ucdrBuffer* ub, const ucdrEndianness endianness, uint32_t* bytes)
{
    const uint32_t data_size = 4;

    ub->iterator += ucdr_buffer_alignment(ub, data_size);

    if(ucdr_check_final_buffer_behavior(ub, data_size))
    {
        if(UCDR_MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, ub->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(ub->iterator + 3);
            *(bytes_pointer + 1) = *(ub->iterator + 2);
            *(bytes_pointer + 2) = *(ub->iterator + 1);
            *(bytes_pointer + 3) = *ub->iterator;
        }

        ub->iterator += data_size;
        ub->last_data_size = data_size;
    }
    return !ub->error;
}

bool ucdr_deserialize_byte_8(ucdrBuffer* ub, const ucdrEndianness endianness, uint64_t* bytes)
{
    const uint32_t data_size = 8;

    ub->iterator += ucdr_buffer_alignment(ub, data_size);

    if(ucdr_check_final_buffer_behavior(ub, data_size))
    {
        if(UCDR_MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, ub->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(ub->iterator + 7);
            *(bytes_pointer + 1) = *(ub->iterator + 6);
            *(bytes_pointer + 2) = *(ub->iterator + 5);
            *(bytes_pointer + 3) = *(ub->iterator + 4);
            *(bytes_pointer + 4) = *(ub->iterator + 3);
            *(bytes_pointer + 5) = *(ub->iterator + 2);
            *(bytes_pointer + 6) = *(ub->iterator + 1);
            *(bytes_pointer + 7) = *ub->iterator;
        }

        ub->iterator += data_size;
        ub->last_data_size = data_size;
    }
    return !ub->error;
}

// -------------------------------------------------------------------
//                  PUBLIC SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------

bool ucdr_serialize_char(ucdrBuffer* ub, const char value)
{
    return ucdr_serialize_byte_1(ub, (uint8_t*)&value);
}

bool ucdr_serialize_bool(ucdrBuffer* ub, const bool value)
{
    return ucdr_serialize_byte_1(ub, (uint8_t*)&value);
}

bool ucdr_serialize_uint8_t(ucdrBuffer* ub, const uint8_t value)
{
    return ucdr_serialize_byte_1(ub, &value);
}

bool ucdr_serialize_uint16_t(ucdrBuffer* ub, const uint16_t value)
{
    return ucdr_serialize_byte_2(ub, ub->endianness, &value);
}

bool ucdr_serialize_uint32_t(ucdrBuffer* ub, const uint32_t value)
{
    return ucdr_serialize_byte_4(ub, ub->endianness, &value);
}

bool ucdr_serialize_uint64_t(ucdrBuffer* ub, const uint64_t value)
{
    return ucdr_serialize_byte_8(ub, ub->endianness, &value);
}

bool ucdr_serialize_int8_t(ucdrBuffer* ub, const int8_t value)
{
    return ucdr_serialize_byte_1(ub, (uint8_t*)&value);
}

bool ucdr_serialize_int16_t(ucdrBuffer* ub, const int16_t value)
{
    return ucdr_serialize_byte_2(ub, ub->endianness, (uint16_t*)&value);
}

bool ucdr_serialize_int32_t(ucdrBuffer* ub, const int32_t value)
{
    return ucdr_serialize_byte_4(ub, ub->endianness, (uint32_t*)&value);
}

bool ucdr_serialize_int64_t(ucdrBuffer* ub, const int64_t value)
{
    return ucdr_serialize_byte_8(ub, ub->endianness, (uint64_t*)&value);
}

bool ucdr_serialize_float(ucdrBuffer* ub, const float value)
{
    return ucdr_serialize_byte_4(ub, ub->endianness, (uint32_t*)&value);
}

bool ucdr_serialize_double(ucdrBuffer* ub, const double value)
{
    return ucdr_serialize_byte_8(ub, ub->endianness, (uint64_t*)&value);
}

bool ucdr_deserialize_char(ucdrBuffer* ub, char* value)
{
    return ucdr_deserialize_byte_1(ub, (uint8_t*)value);
}

bool ucdr_deserialize_bool(ucdrBuffer* ub, bool* value)
{
    return ucdr_deserialize_byte_1(ub, (uint8_t*)value);
}

bool ucdr_deserialize_uint8_t(ucdrBuffer* ub, uint8_t* value)
{
    return ucdr_deserialize_byte_1(ub, value);
}

bool ucdr_deserialize_uint16_t(ucdrBuffer* ub, uint16_t* value)
{
    return ucdr_deserialize_byte_2(ub, ub->endianness, value);
}

bool ucdr_deserialize_uint32_t(ucdrBuffer* ub, uint32_t* value)
{
    return ucdr_deserialize_byte_4(ub, ub->endianness, value);
}

bool ucdr_deserialize_uint64_t(ucdrBuffer* ub, uint64_t* value)
{
    return ucdr_deserialize_byte_8(ub, ub->endianness, value);
}

bool ucdr_deserialize_int8_t(ucdrBuffer* ub, int8_t* value)
{
    return ucdr_deserialize_byte_1(ub, (uint8_t*)value);
}

bool ucdr_deserialize_int16_t(ucdrBuffer* ub, int16_t* value)
{
    return ucdr_deserialize_byte_2(ub, ub->endianness, (uint16_t*)value);
}

bool ucdr_deserialize_int32_t(ucdrBuffer* ub, int32_t* value)
{
    return ucdr_deserialize_byte_4(ub, ub->endianness, (uint32_t*)value);
}

bool ucdr_deserialize_int64_t(ucdrBuffer* ub, int64_t* value)
{
    return ucdr_deserialize_byte_8(ub, ub->endianness, (uint64_t*)value);
}

bool ucdr_deserialize_float(ucdrBuffer* ub, float* value)
{
    return ucdr_deserialize_byte_4(ub, ub->endianness, (uint32_t*)value);
}

bool ucdr_deserialize_double(ucdrBuffer* ub, double* value)
{
    return ucdr_deserialize_byte_8(ub, ub->endianness, (uint64_t*)value);
}

bool ucdr_serialize_endian_uint16_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint16_t value)
{
    return ucdr_serialize_byte_2(ub, endianness, &value);
}

bool ucdr_serialize_endian_uint32_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint32_t value)
{
    return ucdr_serialize_byte_4(ub, endianness, &value);
}

bool ucdr_serialize_endian_uint64_t(ucdrBuffer* ub, const ucdrEndianness endianness, const uint64_t value)
{
    return ucdr_serialize_byte_8(ub, endianness, &value);
}

bool ucdr_serialize_endian_int16_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int16_t value)
{
    return ucdr_serialize_byte_2(ub, endianness, (uint16_t*)&value);
}

bool ucdr_serialize_endian_int32_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int32_t value)
{
    return ucdr_serialize_byte_4(ub, endianness, (uint32_t*)&value);
}

bool ucdr_serialize_endian_int64_t(ucdrBuffer* ub, const ucdrEndianness endianness, const int64_t value)
{
    return ucdr_serialize_byte_8(ub, endianness, (uint64_t*)&value);
}

bool ucdr_serialize_endian_float(ucdrBuffer* ub, const ucdrEndianness endianness, const float value)
{
    return ucdr_serialize_byte_4(ub, endianness, (uint32_t*)&value);
}

bool ucdr_serialize_endian_double(ucdrBuffer* ub, const ucdrEndianness endianness, const double value)
{
    return ucdr_serialize_byte_8(ub, endianness, (uint64_t*)&value);
}

bool ucdr_deserialize_endian_uint16_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint16_t* value)
{
    return ucdr_deserialize_byte_2(ub, endianness, value);
}

bool ucdr_deserialize_endian_uint32_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint32_t* value)
{
    return ucdr_deserialize_byte_4(ub, endianness, value);
}

bool ucdr_deserialize_endian_uint64_t(ucdrBuffer* ub, const ucdrEndianness endianness, uint64_t* value)
{
    return ucdr_deserialize_byte_8(ub, endianness, value);
}

bool ucdr_deserialize_endian_int16_t(ucdrBuffer* ub, const ucdrEndianness endianness, int16_t* value)
{
    return ucdr_deserialize_byte_2(ub, endianness, (uint16_t*)value);
}

bool ucdr_deserialize_endian_int32_t(ucdrBuffer* ub, const ucdrEndianness endianness, int32_t* value)
{
    return ucdr_deserialize_byte_4(ub, endianness, (uint32_t*)value);
}

bool ucdr_deserialize_endian_int64_t(ucdrBuffer* ub, const ucdrEndianness endianness, int64_t* value)
{
    return ucdr_deserialize_byte_8(ub, endianness, (uint64_t*)value);
}

bool ucdr_deserialize_endian_float(ucdrBuffer* ub, const ucdrEndianness endianness, float* value)
{
    return ucdr_deserialize_byte_4(ub, endianness, (uint32_t*)value);
}

bool ucdr_deserialize_endian_double(ucdrBuffer* ub, const ucdrEndianness endianness, double* value)
{
    return ucdr_deserialize_byte_8(ub, endianness, (uint64_t*)value);
}

