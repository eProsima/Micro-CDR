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
#include <microcdr/serialization.h>

#include <string.h>

// -------------------------------------------------------------------
//                  PUBLIC SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------

bool serialize_char(MicroBuffer* buffer, const char value)
{
    return serialize_byte_1(buffer, (uint8_t*)&value);
}

bool serialize_bool(MicroBuffer* buffer, const bool value)
{
    return serialize_byte_1(buffer, (uint8_t*)&value);
}

bool serialize_uint8_t(MicroBuffer* buffer, const uint8_t value)
{
    return serialize_byte_1(buffer, &value);
}

bool serialize_uint16_t(MicroBuffer* buffer, const uint16_t value)
{
    return serialize_byte_2(buffer, buffer->endianness, &value);
}

bool serialize_uint32_t(MicroBuffer* buffer, const uint32_t value)
{
    return serialize_byte_4(buffer, buffer->endianness, &value);
}

bool serialize_uint64_t(MicroBuffer* buffer, const uint64_t value)
{
    return serialize_byte_8(buffer, buffer->endianness, &value);
}

bool serialize_int8_t(MicroBuffer* buffer, const int8_t value)
{
    return serialize_byte_1(buffer, (uint8_t*)&value);
}

bool serialize_int16_t(MicroBuffer* buffer, const int16_t value)
{
    return serialize_byte_2(buffer, buffer->endianness, (uint16_t*)&value);
}

bool serialize_int32_t(MicroBuffer* buffer, const int32_t value)
{
    return serialize_byte_4(buffer, buffer->endianness, (uint32_t*)&value);
}

bool serialize_int64_t(MicroBuffer* buffer, const int64_t value)
{
    return serialize_byte_8(buffer, buffer->endianness, (uint64_t*)&value);
}

bool serialize_float(MicroBuffer* buffer, const float value)
{
    return serialize_byte_4(buffer, buffer->endianness, (uint32_t*)&value);
}

bool serialize_double(MicroBuffer* buffer, const double value)
{
    return serialize_byte_8(buffer, buffer->endianness, (uint64_t*)&value);
}

bool deserialize_char(MicroBuffer* buffer, char* value)
{
    return deserialize_byte_1(buffer, (uint8_t*)value);
}

bool deserialize_bool(MicroBuffer* buffer, bool* value)
{
    return deserialize_byte_1(buffer, (uint8_t*)value);
}

bool deserialize_uint8_t(MicroBuffer* buffer, uint8_t* value)
{
    return deserialize_byte_1(buffer, value);
}

bool deserialize_uint16_t(MicroBuffer* buffer, uint16_t* value)
{
    return deserialize_byte_2(buffer, buffer->endianness, value);
}

bool deserialize_uint32_t(MicroBuffer* buffer, uint32_t* value)
{
    return deserialize_byte_4(buffer, buffer->endianness, value);
}

bool deserialize_uint64_t(MicroBuffer* buffer, uint64_t* value)
{
    return deserialize_byte_8(buffer, buffer->endianness, value);
}

bool deserialize_int8_t(MicroBuffer* buffer, int8_t* value)
{
    return deserialize_byte_1(buffer, (uint8_t*)value);
}

bool deserialize_int16_t(MicroBuffer* buffer, int16_t* value)
{
    return deserialize_byte_2(buffer, buffer->endianness, (uint16_t*)value);
}

bool deserialize_int32_t(MicroBuffer* buffer, int32_t* value)
{
    return deserialize_byte_4(buffer, buffer->endianness, (uint32_t*)value);
}

bool deserialize_int64_t(MicroBuffer* buffer, int64_t* value)
{
    return deserialize_byte_8(buffer, buffer->endianness, (uint64_t*)value);
}

bool deserialize_float(MicroBuffer* buffer, float* value)
{
    return deserialize_byte_4(buffer, buffer->endianness, (uint32_t*)value);
}

bool deserialize_double(MicroBuffer* buffer, double* value)
{
    return deserialize_byte_8(buffer, buffer->endianness, (uint64_t*)value);
}

bool serialize_endian_uint16_t(MicroBuffer* buffer, const Endianness endianness, const uint16_t value)
{
    return serialize_byte_2(buffer, endianness, &value);
}

bool serialize_endian_uint32_t(MicroBuffer* buffer, const Endianness endianness, const uint32_t value)
{
    return serialize_byte_4(buffer, endianness, &value);
}

bool serialize_endian_uint64_t(MicroBuffer* buffer, const Endianness endianness, const uint64_t value)
{
    return serialize_byte_8(buffer, endianness, &value);
}

bool serialize_endian_int16_t(MicroBuffer* buffer, const Endianness endianness, const int16_t value)
{
    return serialize_byte_2(buffer, endianness, (uint16_t*)&value);
}

bool serialize_endian_int32_t(MicroBuffer* buffer, const Endianness endianness, const int32_t value)
{
    return serialize_byte_4(buffer, endianness, (uint32_t*)&value);
}

bool serialize_endian_int64_t(MicroBuffer* buffer, const Endianness endianness, const int64_t value)
{
    return serialize_byte_8(buffer, endianness, (uint64_t*)&value);
}

bool serialize_endian_float(MicroBuffer* buffer, const Endianness endianness, const float value)
{
    return serialize_byte_4(buffer, endianness, (uint32_t*)&value);
}

bool serialize_endian_double(MicroBuffer* buffer, const Endianness endianness, const double value)
{
    return serialize_byte_8(buffer, endianness, (uint64_t*)&value);
}

bool deserialize_endian_uint16_t(MicroBuffer* buffer, const Endianness endianness, uint16_t* value)
{
    return deserialize_byte_2(buffer, endianness, value);
}

bool deserialize_endian_uint32_t(MicroBuffer* buffer, const Endianness endianness, uint32_t* value)
{
    return deserialize_byte_4(buffer, endianness, value);
}

bool deserialize_endian_uint64_t(MicroBuffer* buffer, const Endianness endianness, uint64_t* value)
{
    return deserialize_byte_8(buffer, endianness, value);
}

bool deserialize_endian_int16_t(MicroBuffer* buffer, const Endianness endianness, int16_t* value)
{
    return deserialize_byte_2(buffer, endianness, (uint16_t*)value);
}

bool deserialize_endian_int32_t(MicroBuffer* buffer, const Endianness endianness, int32_t* value)
{
    return deserialize_byte_4(buffer, endianness, (uint32_t*)value);
}

bool deserialize_endian_int64_t(MicroBuffer* buffer, const Endianness endianness, int64_t* value)
{
    return deserialize_byte_8(buffer, endianness, (uint64_t*)value);
}

bool deserialize_endian_float(MicroBuffer* buffer, const Endianness endianness, float* value)
{
    return deserialize_byte_4(buffer, endianness, (uint32_t*)value);
}

bool deserialize_endian_double(MicroBuffer* buffer, const Endianness endianness, double* value)
{
    return deserialize_byte_8(buffer, endianness, (uint64_t*)value);
}

