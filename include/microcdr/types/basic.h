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

microcdr_DllAPI bool serialize_char(MicroBuffer* mb, const char value);
microcdr_DllAPI bool serialize_bool(MicroBuffer* mb, const bool value);
microcdr_DllAPI bool serialize_uint8_t(MicroBuffer* mb, const uint8_t value);
microcdr_DllAPI bool serialize_uint16_t(MicroBuffer* mb, const uint16_t value);
microcdr_DllAPI bool serialize_uint32_t(MicroBuffer* mb, const uint32_t value);
microcdr_DllAPI bool serialize_uint64_t(MicroBuffer* mb, const uint64_t value);
microcdr_DllAPI bool serialize_int8_t(MicroBuffer* mb, const int8_t value);
microcdr_DllAPI bool serialize_int16_t(MicroBuffer* mb, const int16_t value);
microcdr_DllAPI bool serialize_int32_t(MicroBuffer* mb, const int32_t value);
microcdr_DllAPI bool serialize_int64_t(MicroBuffer* mb, const int64_t value);
microcdr_DllAPI bool serialize_float(MicroBuffer* mb, const float value);
microcdr_DllAPI bool serialize_double(MicroBuffer* mb, const double value);

microcdr_DllAPI bool deserialize_char(MicroBuffer* mb, char* value);
microcdr_DllAPI bool deserialize_bool(MicroBuffer* mb, bool* value);
microcdr_DllAPI bool deserialize_uint8_t(MicroBuffer* mb, uint8_t* value);
microcdr_DllAPI bool deserialize_uint16_t(MicroBuffer* mb, uint16_t* value);
microcdr_DllAPI bool deserialize_uint32_t(MicroBuffer* mb, uint32_t* value);
microcdr_DllAPI bool deserialize_uint64_t(MicroBuffer* mb, uint64_t* value);
microcdr_DllAPI bool deserialize_int8_t(MicroBuffer* mb, int8_t* value);
microcdr_DllAPI bool deserialize_int16_t(MicroBuffer* mb, int16_t* value);
microcdr_DllAPI bool deserialize_int32_t(MicroBuffer* mb, int32_t* value);
microcdr_DllAPI bool deserialize_int64_t(MicroBuffer* mb, int64_t* value);
microcdr_DllAPI bool deserialize_float(MicroBuffer* mb, float* value);
microcdr_DllAPI bool deserialize_double(MicroBuffer* mb, double* value);

microcdr_DllAPI bool serialize_endian_uint16_t(MicroBuffer* mb, Endianness endianness, const uint16_t value);
microcdr_DllAPI bool serialize_endian_uint32_t(MicroBuffer* mb, Endianness endianness, const uint32_t value);
microcdr_DllAPI bool serialize_endian_uint64_t(MicroBuffer* mb, Endianness endianness, const uint64_t value);
microcdr_DllAPI bool serialize_endian_int16_t(MicroBuffer* mb, Endianness endianness, const int16_t value);
microcdr_DllAPI bool serialize_endian_int32_t(MicroBuffer* mb, Endianness endianness, const int32_t value);
microcdr_DllAPI bool serialize_endian_int64_t(MicroBuffer* mb, Endianness endianness, const int64_t value);
microcdr_DllAPI bool serialize_endian_float(MicroBuffer* mb, Endianness endianness, const float value);
microcdr_DllAPI bool serialize_endian_double(MicroBuffer* mb, Endianness endianness, const double value);

microcdr_DllAPI bool deserialize_endian_uint16_t(MicroBuffer* mb, Endianness endianness, uint16_t* value);
microcdr_DllAPI bool deserialize_endian_uint32_t(MicroBuffer* mb, Endianness endianness, uint32_t *value);
microcdr_DllAPI bool deserialize_endian_uint64_t(MicroBuffer* mb, Endianness endianness, uint64_t* value);
microcdr_DllAPI bool deserialize_endian_int16_t(MicroBuffer* mb, Endianness endianness, int16_t* value);
microcdr_DllAPI bool deserialize_endian_int32_t(MicroBuffer* mb, Endianness endianness, int32_t* value);
microcdr_DllAPI bool deserialize_endian_int64_t(MicroBuffer* mb, Endianness endianness, int64_t* value);
microcdr_DllAPI bool deserialize_endian_float(MicroBuffer* mb, Endianness endianness, float* value);
microcdr_DllAPI bool deserialize_endian_double(MicroBuffer* mb, Endianness endianness, double* value);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_BASIC_H_
