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

#include <ucdr/common.h>

// -------------------------------------------------------------------
//                   PUBLIC SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

UCDRDLLAPI bool ucdr_serialize_char(ucdrBuffer* ub, const char value);
UCDRDLLAPI bool ucdr_serialize_bool(ucdrBuffer* ub, const bool value);
UCDRDLLAPI bool ucdr_serialize_uint8_t(ucdrBuffer* ub, const uint8_t value);
UCDRDLLAPI bool ucdr_serialize_uint16_t(ucdrBuffer* ub, const uint16_t value);
UCDRDLLAPI bool ucdr_serialize_uint32_t(ucdrBuffer* ub, const uint32_t value);
UCDRDLLAPI bool ucdr_serialize_uint64_t(ucdrBuffer* ub, const uint64_t value);
UCDRDLLAPI bool ucdr_serialize_int8_t(ucdrBuffer* ub, const int8_t value);
UCDRDLLAPI bool ucdr_serialize_int16_t(ucdrBuffer* ub, const int16_t value);
UCDRDLLAPI bool ucdr_serialize_int32_t(ucdrBuffer* ub, const int32_t value);
UCDRDLLAPI bool ucdr_serialize_int64_t(ucdrBuffer* ub, const int64_t value);
UCDRDLLAPI bool ucdr_serialize_float(ucdrBuffer* ub, const float value);
UCDRDLLAPI bool ucdr_serialize_double(ucdrBuffer* ub, const double value);

UCDRDLLAPI bool ucdr_deserialize_char(ucdrBuffer* ub, char* value);
UCDRDLLAPI bool ucdr_deserialize_bool(ucdrBuffer* ub, bool* value);
UCDRDLLAPI bool ucdr_deserialize_uint8_t(ucdrBuffer* ub, uint8_t* value);
UCDRDLLAPI bool ucdr_deserialize_uint16_t(ucdrBuffer* ub, uint16_t* value);
UCDRDLLAPI bool ucdr_deserialize_uint32_t(ucdrBuffer* ub, uint32_t* value);
UCDRDLLAPI bool ucdr_deserialize_uint64_t(ucdrBuffer* ub, uint64_t* value);
UCDRDLLAPI bool ucdr_deserialize_int8_t(ucdrBuffer* ub, int8_t* value);
UCDRDLLAPI bool ucdr_deserialize_int16_t(ucdrBuffer* ub, int16_t* value);
UCDRDLLAPI bool ucdr_deserialize_int32_t(ucdrBuffer* ub, int32_t* value);
UCDRDLLAPI bool ucdr_deserialize_int64_t(ucdrBuffer* ub, int64_t* value);
UCDRDLLAPI bool ucdr_deserialize_float(ucdrBuffer* ub, float* value);
UCDRDLLAPI bool ucdr_deserialize_double(ucdrBuffer* ub, double* value);

UCDRDLLAPI bool ucdr_serialize_endian_uint16_t(ucdrBuffer* ub, ucdrEndianness endianness, const uint16_t value);
UCDRDLLAPI bool ucdr_serialize_endian_uint32_t(ucdrBuffer* ub, ucdrEndianness endianness, const uint32_t value);
UCDRDLLAPI bool ucdr_serialize_endian_uint64_t(ucdrBuffer* ub, ucdrEndianness endianness, const uint64_t value);
UCDRDLLAPI bool ucdr_serialize_endian_int16_t(ucdrBuffer* ub, ucdrEndianness endianness, const int16_t value);
UCDRDLLAPI bool ucdr_serialize_endian_int32_t(ucdrBuffer* ub, ucdrEndianness endianness, const int32_t value);
UCDRDLLAPI bool ucdr_serialize_endian_int64_t(ucdrBuffer* ub, ucdrEndianness endianness, const int64_t value);
UCDRDLLAPI bool ucdr_serialize_endian_float(ucdrBuffer* ub, ucdrEndianness endianness, const float value);
UCDRDLLAPI bool ucdr_serialize_endian_double(ucdrBuffer* ub, ucdrEndianness endianness, const double value);

UCDRDLLAPI bool ucdr_deserialize_endian_uint16_t(ucdrBuffer* ub, ucdrEndianness endianness, uint16_t* value);
UCDRDLLAPI bool ucdr_deserialize_endian_uint32_t(ucdrBuffer* ub, ucdrEndianness endianness, uint32_t *value);
UCDRDLLAPI bool ucdr_deserialize_endian_uint64_t(ucdrBuffer* ub, ucdrEndianness endianness, uint64_t* value);
UCDRDLLAPI bool ucdr_deserialize_endian_int16_t(ucdrBuffer* ub, ucdrEndianness endianness, int16_t* value);
UCDRDLLAPI bool ucdr_deserialize_endian_int32_t(ucdrBuffer* ub, ucdrEndianness endianness, int32_t* value);
UCDRDLLAPI bool ucdr_deserialize_endian_int64_t(ucdrBuffer* ub, ucdrEndianness endianness, int64_t* value);
UCDRDLLAPI bool ucdr_deserialize_endian_float(ucdrBuffer* ub, ucdrEndianness endianness, float* value);
UCDRDLLAPI bool ucdr_deserialize_endian_double(ucdrBuffer* ub, ucdrEndianness endianness, double* value);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_BASIC_H_
