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

#ifndef _MICROCDR_TYPES_BASIC_H_
#define _MICROCDR_TYPES_BASIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <microcdr/common.h>

// -------------------------------------------------------------------
//                   PUBLIC SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

MCDLLAPI bool serialize_char(mcMicroBuffer* mb, const char value);
MCDLLAPI bool serialize_bool(mcMicroBuffer* mb, const bool value);
MCDLLAPI bool serialize_uint8_t(mcMicroBuffer* mb, const uint8_t value);
MCDLLAPI bool serialize_uint16_t(mcMicroBuffer* mb, const uint16_t value);
MCDLLAPI bool serialize_uint32_t(mcMicroBuffer* mb, const uint32_t value);
MCDLLAPI bool serialize_uint64_t(mcMicroBuffer* mb, const uint64_t value);
MCDLLAPI bool serialize_int8_t(mcMicroBuffer* mb, const int8_t value);
MCDLLAPI bool serialize_int16_t(mcMicroBuffer* mb, const int16_t value);
MCDLLAPI bool serialize_int32_t(mcMicroBuffer* mb, const int32_t value);
MCDLLAPI bool serialize_int64_t(mcMicroBuffer* mb, const int64_t value);
MCDLLAPI bool serialize_float(mcMicroBuffer* mb, const float value);
MCDLLAPI bool serialize_double(mcMicroBuffer* mb, const double value);

MCDLLAPI bool deserialize_char(mcMicroBuffer* mb, char* value);
MCDLLAPI bool deserialize_bool(mcMicroBuffer* mb, bool* value);
MCDLLAPI bool deserialize_uint8_t(mcMicroBuffer* mb, uint8_t* value);
MCDLLAPI bool deserialize_uint16_t(mcMicroBuffer* mb, uint16_t* value);
MCDLLAPI bool deserialize_uint32_t(mcMicroBuffer* mb, uint32_t* value);
MCDLLAPI bool deserialize_uint64_t(mcMicroBuffer* mb, uint64_t* value);
MCDLLAPI bool deserialize_int8_t(mcMicroBuffer* mb, int8_t* value);
MCDLLAPI bool deserialize_int16_t(mcMicroBuffer* mb, int16_t* value);
MCDLLAPI bool deserialize_int32_t(mcMicroBuffer* mb, int32_t* value);
MCDLLAPI bool deserialize_int64_t(mcMicroBuffer* mb, int64_t* value);
MCDLLAPI bool deserialize_float(mcMicroBuffer* mb, float* value);
MCDLLAPI bool deserialize_double(mcMicroBuffer* mb, double* value);

MCDLLAPI bool serialize_endian_uint16_t(mcMicroBuffer* mb, Endianness endianness, const uint16_t value);
MCDLLAPI bool serialize_endian_uint32_t(mcMicroBuffer* mb, Endianness endianness, const uint32_t value);
MCDLLAPI bool serialize_endian_uint64_t(mcMicroBuffer* mb, Endianness endianness, const uint64_t value);
MCDLLAPI bool serialize_endian_int16_t(mcMicroBuffer* mb, Endianness endianness, const int16_t value);
MCDLLAPI bool serialize_endian_int32_t(mcMicroBuffer* mb, Endianness endianness, const int32_t value);
MCDLLAPI bool serialize_endian_int64_t(mcMicroBuffer* mb, Endianness endianness, const int64_t value);
MCDLLAPI bool serialize_endian_float(mcMicroBuffer* mb, Endianness endianness, const float value);
MCDLLAPI bool serialize_endian_double(mcMicroBuffer* mb, Endianness endianness, const double value);

MCDLLAPI bool deserialize_endian_uint16_t(mcMicroBuffer* mb, Endianness endianness, uint16_t* value);
MCDLLAPI bool deserialize_endian_uint32_t(mcMicroBuffer* mb, Endianness endianness, uint32_t *value);
MCDLLAPI bool deserialize_endian_uint64_t(mcMicroBuffer* mb, Endianness endianness, uint64_t* value);
MCDLLAPI bool deserialize_endian_int16_t(mcMicroBuffer* mb, Endianness endianness, int16_t* value);
MCDLLAPI bool deserialize_endian_int32_t(mcMicroBuffer* mb, Endianness endianness, int32_t* value);
MCDLLAPI bool deserialize_endian_int64_t(mcMicroBuffer* mb, Endianness endianness, int64_t* value);
MCDLLAPI bool deserialize_endian_float(mcMicroBuffer* mb, Endianness endianness, float* value);
MCDLLAPI bool deserialize_endian_double(mcMicroBuffer* mb, Endianness endianness, double* value);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_BASIC_H_
