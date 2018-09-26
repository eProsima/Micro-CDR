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

#ifndef _MICROCDR_TYPES_ARRAY_H_
#define _MICROCDR_TYPES_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <microcdr/common.h>

// -------------------------------------------------------------------
//                   PUBLIC SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

MCDLLAPI bool mc_serialize_array_char(mcBuffer* mb, const char* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_bool(mcBuffer* mb, const bool* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_uint8_t(mcBuffer* mb, const uint8_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_uint16_t(mcBuffer* mb, const uint16_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_uint32_t(mcBuffer* mb, const uint32_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_uint64_t(mcBuffer* mb, const uint64_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_int8_t(mcBuffer* mb, const int8_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_int16_t(mcBuffer* mb, const int16_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_int32_t(mcBuffer* mb, const int32_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_int64_t(mcBuffer* mb, const int64_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_float(mcBuffer* mb, const float* array, const uint32_t size);
MCDLLAPI bool mc_serialize_array_double(mcBuffer* mb, const double* array, const uint32_t size);

MCDLLAPI bool mc_deserialize_array_char(mcBuffer* mb, char* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_bool(mcBuffer* mb, bool* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_uint8_t(mcBuffer* mb, uint8_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_uint16_t(mcBuffer* mb, uint16_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_uint32_t(mcBuffer* mb, uint32_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_uint64_t(mcBuffer* mb, uint64_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_int8_t(mcBuffer* mb, int8_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_int16_t(mcBuffer* mb, int16_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_int32_t(mcBuffer* mb, int32_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_int64_t(mcBuffer* mb, int64_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_float(mcBuffer* mb, float* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_double(mcBuffer* mb, double* array, const uint32_t size);

MCDLLAPI bool mc_serialize_endian_array_uint16_t(mcBuffer* mb, mrEndianness endianness, const uint16_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_array_uint32_t(mcBuffer* mb, mrEndianness endianness, const uint32_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_array_uint64_t(mcBuffer* mb, mrEndianness endianness, const uint64_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_array_int16_t(mcBuffer* mb, mrEndianness endianness, const int16_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_array_int32_t(mcBuffer* mb, mrEndianness endianness, const int32_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_array_int64_t(mcBuffer* mb, mrEndianness endianness, const int64_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_array_float(mcBuffer* mb, mrEndianness endianness, const float* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_array_double(mcBuffer* mb, mrEndianness endianness, const double* array, const uint32_t size);

MCDLLAPI bool mc_deserialize_endian_array_uint16_t(mcBuffer* mb, mrEndianness endianness, uint16_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_uint32_t(mcBuffer* mb, mrEndianness endianness, uint32_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_uint64_t(mcBuffer* mb, mrEndianness endianness, uint64_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_int16_t(mcBuffer* mb, mrEndianness endianness, int16_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_int32_t(mcBuffer* mb, mrEndianness endianness, int32_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_int64_t(mcBuffer* mb, mrEndianness endianness, int64_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_float(mcBuffer* mb, mrEndianness endianness, float* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_double(mcBuffer* mb, mrEndianness endianness, double* array, const uint32_t size);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_ARRAY_H_
