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

MCDLLAPI bool serialize_array_char(mcMicroBuffer* mb, const char* array, const uint32_t size);
MCDLLAPI bool serialize_array_bool(mcMicroBuffer* mb, const bool* array, const uint32_t size);
MCDLLAPI bool serialize_array_uint8_t(mcMicroBuffer* mb, const uint8_t* array, const uint32_t size);
MCDLLAPI bool serialize_array_uint16_t(mcMicroBuffer* mb, const uint16_t* array, const uint32_t size);
MCDLLAPI bool serialize_array_uint32_t(mcMicroBuffer* mb, const uint32_t* array, const uint32_t size);
MCDLLAPI bool serialize_array_uint64_t(mcMicroBuffer* mb, const uint64_t* array, const uint32_t size);
MCDLLAPI bool serialize_array_int8_t(mcMicroBuffer* mb, const int8_t* array, const uint32_t size);
MCDLLAPI bool serialize_array_int16_t(mcMicroBuffer* mb, const int16_t* array, const uint32_t size);
MCDLLAPI bool serialize_array_int32_t(mcMicroBuffer* mb, const int32_t* array, const uint32_t size);
MCDLLAPI bool serialize_array_int64_t(mcMicroBuffer* mb, const int64_t* array, const uint32_t size);
MCDLLAPI bool serialize_array_float(mcMicroBuffer* mb, const float* array, const uint32_t size);
MCDLLAPI bool serialize_array_double(mcMicroBuffer* mb, const double* array, const uint32_t size);

MCDLLAPI bool mc_deserialize_array_char(mcMicroBuffer* mb, char* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_bool(mcMicroBuffer* mb, bool* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_uint8_t(mcMicroBuffer* mb, uint8_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_uint16_t(mcMicroBuffer* mb, uint16_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_uint32_t(mcMicroBuffer* mb, uint32_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_uint64_t(mcMicroBuffer* mb, uint64_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_int8_t(mcMicroBuffer* mb, int8_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_int16_t(mcMicroBuffer* mb, int16_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_int32_t(mcMicroBuffer* mb, int32_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_int64_t(mcMicroBuffer* mb, int64_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_float(mcMicroBuffer* mb, float* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_array_double(mcMicroBuffer* mb, double* array, const uint32_t size);

MCDLLAPI bool serialize_endian_array_uint16_t(mcMicroBuffer* mb, Endianness endianness, const uint16_t* array, const uint32_t size);
MCDLLAPI bool serialize_endian_array_uint32_t(mcMicroBuffer* mb, Endianness endianness, const uint32_t* array, const uint32_t size);
MCDLLAPI bool serialize_endian_array_uint64_t(mcMicroBuffer* mb, Endianness endianness, const uint64_t* array, const uint32_t size);
MCDLLAPI bool serialize_endian_array_int16_t(mcMicroBuffer* mb, Endianness endianness, const int16_t* array, const uint32_t size);
MCDLLAPI bool serialize_endian_array_int32_t(mcMicroBuffer* mb, Endianness endianness, const int32_t* array, const uint32_t size);
MCDLLAPI bool serialize_endian_array_int64_t(mcMicroBuffer* mb, Endianness endianness, const int64_t* array, const uint32_t size);
MCDLLAPI bool serialize_endian_array_float(mcMicroBuffer* mb, Endianness endianness, const float* array, const uint32_t size);
MCDLLAPI bool serialize_endian_array_double(mcMicroBuffer* mb, Endianness endianness, const double* array, const uint32_t size);

MCDLLAPI bool mc_deserialize_endian_array_uint16_t(mcMicroBuffer* mb, Endianness endianness, uint16_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_uint32_t(mcMicroBuffer* mb, Endianness endianness, uint32_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_uint64_t(mcMicroBuffer* mb, Endianness endianness, uint64_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_int16_t(mcMicroBuffer* mb, Endianness endianness, int16_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_int32_t(mcMicroBuffer* mb, Endianness endianness, int32_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_int64_t(mcMicroBuffer* mb, Endianness endianness, int64_t* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_float(mcMicroBuffer* mb, Endianness endianness, float* array, const uint32_t size);
MCDLLAPI bool mc_deserialize_endian_array_double(mcMicroBuffer* mb, Endianness endianness, double* array, const uint32_t size);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_ARRAY_H_
