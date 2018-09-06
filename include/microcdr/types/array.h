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

#include <stdint.h>
#include <stdbool.h>

microcdr_DllAPI bool serialize_array_char(MicroBuffer* buffer, const char* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_bool(MicroBuffer* buffer, const bool* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_uint8_t(MicroBuffer* buffer, const uint8_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_uint16_t(MicroBuffer* buffer, const uint16_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_uint32_t(MicroBuffer* buffer, const uint32_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_uint64_t(MicroBuffer* buffer, const uint64_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_int8_t(MicroBuffer* buffer, const int8_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_int16_t(MicroBuffer* buffer, const int16_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_int32_t(MicroBuffer* buffer, const int32_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_int64_t(MicroBuffer* buffer, const int64_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_float(MicroBuffer* buffer, const float* array, const uint32_t size);
microcdr_DllAPI bool serialize_array_double(MicroBuffer* buffer, const double* array, const uint32_t size);

microcdr_DllAPI bool deserialize_array_char(MicroBuffer* buffer, char* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_bool(MicroBuffer* buffer, bool* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_uint8_t(MicroBuffer* buffer, uint8_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_uint16_t(MicroBuffer* buffer, uint16_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_uint32_t(MicroBuffer* buffer, uint32_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_uint64_t(MicroBuffer* buffer, uint64_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_int8_t(MicroBuffer* buffer, int8_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_int16_t(MicroBuffer* buffer, int16_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_int32_t(MicroBuffer* buffer, int32_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_int64_t(MicroBuffer* buffer, int64_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_float(MicroBuffer* buffer, float* array, const uint32_t size);
microcdr_DllAPI bool deserialize_array_double(MicroBuffer* buffer, double* array, const uint32_t size);


microcdr_DllAPI bool serialize_endian_array_uint16_t(MicroBuffer* buffer, Endianness endianness, const uint16_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_array_uint32_t(MicroBuffer* buffer, Endianness endianness, const uint32_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_array_uint64_t(MicroBuffer* buffer, Endianness endianness, const uint64_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_array_int16_t(MicroBuffer* buffer, Endianness endianness, const int16_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_array_int32_t(MicroBuffer* buffer, Endianness endianness, const int32_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_array_int64_t(MicroBuffer* buffer, Endianness endianness, const int64_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_array_float(MicroBuffer* buffer, Endianness endianness, const float* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_array_double(MicroBuffer* buffer, Endianness endianness, const double* array, const uint32_t size);

microcdr_DllAPI bool deserialize_endian_array_uint16_t(MicroBuffer* buffer, Endianness endianness, uint16_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_endian_array_uint32_t(MicroBuffer* buffer, Endianness endianness, uint32_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_endian_array_uint64_t(MicroBuffer* buffer, Endianness endianness, uint64_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_endian_array_int16_t(MicroBuffer* buffer, Endianness endianness, int16_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_endian_array_int32_t(MicroBuffer* buffer, Endianness endianness, int32_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_endian_array_int64_t(MicroBuffer* buffer, Endianness endianness, int64_t* array, const uint32_t size);
microcdr_DllAPI bool deserialize_endian_array_float(MicroBuffer* buffer, Endianness endianness, float* array, const uint32_t size);
microcdr_DllAPI bool deserialize_endian_array_double(MicroBuffer* buffer, Endianness endianness, double* array, const uint32_t size);


#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_ARRAY_H_
