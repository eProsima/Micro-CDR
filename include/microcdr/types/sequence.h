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

#ifndef _MICROCDR_TYPES_SEQUENCE_H_
#define _MICROCDR_TYPES_SEQUENCE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <microcdr/common.h>

// -------------------------------------------------------------------
//                   PUBLIC SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

MCDLLAPI bool mc_serialize_sequence_char(mcBuffer* mb, const char* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_bool(mcBuffer* mb, const bool* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_uint8_t(mcBuffer* mb, const uint8_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_uint16_t(mcBuffer* mb, const uint16_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_uint32_t(mcBuffer* mb, const uint32_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_uint64_t(mcBuffer* mb, const uint64_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_int8_t(mcBuffer* mb, const int8_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_int16_t(mcBuffer* mb, const int16_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_int32_t(mcBuffer* mb, const int32_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_int64_t(mcBuffer* mb, const int64_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_float(mcBuffer* mb, const float* array, const uint32_t size);
MCDLLAPI bool mc_serialize_sequence_double(mcBuffer* mb, const double* array, const uint32_t size);

MCDLLAPI bool mc_deserialize_sequence_char(mcBuffer* mb, char* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_bool(mcBuffer* mb, bool* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_uint8_t(mcBuffer* mb, uint8_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_uint16_t(mcBuffer* mb, uint16_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_uint32_t(mcBuffer* mb, uint32_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_uint64_t(mcBuffer* mb, uint64_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_int8_t(mcBuffer* mb, int8_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_int16_t(mcBuffer* mb, int16_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_int32_t(mcBuffer* mb, int32_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_int64_t(mcBuffer* mb, int64_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_float(mcBuffer* mb, float* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_sequence_double(mcBuffer* mb, double* array, const uint32_t array_capacity, uint32_t* size);

MCDLLAPI bool mc_serialize_endian_sequence_char(mcBuffer* mb, mcEndianness endianness, const char* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_bool(mcBuffer* mb, mcEndianness endianness, const bool* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_uint8_t(mcBuffer* mb, mcEndianness endianness, const uint8_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_uint16_t(mcBuffer* mb, mcEndianness endianness, const uint16_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_uint32_t(mcBuffer* mb, mcEndianness endianness, const uint32_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_uint64_t(mcBuffer* mb, mcEndianness endianness, const uint64_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_int8_t(mcBuffer* mb, mcEndianness endianness, const int8_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_int16_t(mcBuffer* mb, mcEndianness endianness, const int16_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_int32_t(mcBuffer* mb, mcEndianness endianness, const int32_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_int64_t(mcBuffer* mb, mcEndianness endianness, const int64_t* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_float(mcBuffer* mb, mcEndianness endianness, const float* array, const uint32_t size);
MCDLLAPI bool mc_serialize_endian_sequence_double(mcBuffer* mb, mcEndianness endianness, const double* array, const uint32_t size);

MCDLLAPI bool mc_deserialize_endian_sequence_char(mcBuffer* mb, mcEndianness endianness, char* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_bool(mcBuffer* mb, mcEndianness endianness, bool* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_uint8_t(mcBuffer* mb, mcEndianness endianness, uint8_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_uint16_t(mcBuffer* mb, mcEndianness endianness, uint16_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_uint32_t(mcBuffer* mb, mcEndianness endianness, uint32_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_uint64_t(mcBuffer* mb, mcEndianness endianness, uint64_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_int8_t(mcBuffer* mb, mcEndianness endianness, int8_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_int16_t(mcBuffer* mb, mcEndianness endianness, int16_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_int32_t(mcBuffer* mb, mcEndianness endianness, int32_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_int64_t(mcBuffer* mb, mcEndianness endianness, int64_t* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_float(mcBuffer* mb, mcEndianness endianness, float* array, const uint32_t array_capacity, uint32_t* size);
MCDLLAPI bool mc_deserialize_endian_sequence_double(mcBuffer* mb, mcEndianness endianness, double* array, const uint32_t array_capacity, uint32_t* size);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_SEQUENCE_H_
