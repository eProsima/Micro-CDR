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

MCDLLAPI bool mc_serialize_char(mcBuffer* mb, const char value);
MCDLLAPI bool mc_serialize_bool(mcBuffer* mb, const bool value);
MCDLLAPI bool mc_serialize_uint8_t(mcBuffer* mb, const uint8_t value);
MCDLLAPI bool mc_serialize_uint16_t(mcBuffer* mb, const uint16_t value);
MCDLLAPI bool mc_serialize_uint32_t(mcBuffer* mb, const uint32_t value);
MCDLLAPI bool mc_serialize_uint64_t(mcBuffer* mb, const uint64_t value);
MCDLLAPI bool mc_serialize_int8_t(mcBuffer* mb, const int8_t value);
MCDLLAPI bool mc_serialize_int16_t(mcBuffer* mb, const int16_t value);
MCDLLAPI bool mc_serialize_int32_t(mcBuffer* mb, const int32_t value);
MCDLLAPI bool mc_serialize_int64_t(mcBuffer* mb, const int64_t value);
MCDLLAPI bool mc_serialize_float(mcBuffer* mb, const float value);
MCDLLAPI bool mc_serialize_double(mcBuffer* mb, const double value);

MCDLLAPI bool mc_deserialize_char(mcBuffer* mb, char* value);
MCDLLAPI bool mc_deserialize_bool(mcBuffer* mb, bool* value);
MCDLLAPI bool mc_deserialize_uint8_t(mcBuffer* mb, uint8_t* value);
MCDLLAPI bool mc_deserialize_uint16_t(mcBuffer* mb, uint16_t* value);
MCDLLAPI bool mc_deserialize_uint32_t(mcBuffer* mb, uint32_t* value);
MCDLLAPI bool mc_deserialize_uint64_t(mcBuffer* mb, uint64_t* value);
MCDLLAPI bool mc_deserialize_int8_t(mcBuffer* mb, int8_t* value);
MCDLLAPI bool mc_deserialize_int16_t(mcBuffer* mb, int16_t* value);
MCDLLAPI bool mc_deserialize_int32_t(mcBuffer* mb, int32_t* value);
MCDLLAPI bool mc_deserialize_int64_t(mcBuffer* mb, int64_t* value);
MCDLLAPI bool mc_deserialize_float(mcBuffer* mb, float* value);
MCDLLAPI bool mc_deserialize_double(mcBuffer* mb, double* value);

MCDLLAPI bool mc_serialize_endian_uint16_t(mcBuffer* mb, mcEndianness endianness, const uint16_t value);
MCDLLAPI bool mc_serialize_endian_uint32_t(mcBuffer* mb, mcEndianness endianness, const uint32_t value);
MCDLLAPI bool mc_serialize_endian_uint64_t(mcBuffer* mb, mcEndianness endianness, const uint64_t value);
MCDLLAPI bool mc_serialize_endian_int16_t(mcBuffer* mb, mcEndianness endianness, const int16_t value);
MCDLLAPI bool mc_serialize_endian_int32_t(mcBuffer* mb, mcEndianness endianness, const int32_t value);
MCDLLAPI bool mc_serialize_endian_int64_t(mcBuffer* mb, mcEndianness endianness, const int64_t value);
MCDLLAPI bool mc_serialize_endian_float(mcBuffer* mb, mcEndianness endianness, const float value);
MCDLLAPI bool mc_serialize_endian_double(mcBuffer* mb, mcEndianness endianness, const double value);

MCDLLAPI bool mc_deserialize_endian_uint16_t(mcBuffer* mb, mcEndianness endianness, uint16_t* value);
MCDLLAPI bool mc_deserialize_endian_uint32_t(mcBuffer* mb, mcEndianness endianness, uint32_t *value);
MCDLLAPI bool mc_deserialize_endian_uint64_t(mcBuffer* mb, mcEndianness endianness, uint64_t* value);
MCDLLAPI bool mc_deserialize_endian_int16_t(mcBuffer* mb, mcEndianness endianness, int16_t* value);
MCDLLAPI bool mc_deserialize_endian_int32_t(mcBuffer* mb, mcEndianness endianness, int32_t* value);
MCDLLAPI bool mc_deserialize_endian_int64_t(mcBuffer* mb, mcEndianness endianness, int64_t* value);
MCDLLAPI bool mc_deserialize_endian_float(mcBuffer* mb, mcEndianness endianness, float* value);
MCDLLAPI bool mc_deserialize_endian_double(mcBuffer* mb, mcEndianness endianness, double* value);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_BASIC_H_
