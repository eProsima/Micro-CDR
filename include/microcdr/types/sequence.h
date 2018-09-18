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

microcdr_DllAPI bool serialize_sequence_char(MicroBuffer* mb, const char* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_bool(MicroBuffer* mb, const bool* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_uint8_t(MicroBuffer* mb, const uint8_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_uint16_t(MicroBuffer* mb, const uint16_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_uint32_t(MicroBuffer* mb, const uint32_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_uint64_t(MicroBuffer* mb, const uint64_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_int8_t(MicroBuffer* mb, const int8_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_int16_t(MicroBuffer* mb, const int16_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_int32_t(MicroBuffer* mb, const int32_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_int64_t(MicroBuffer* mb, const int64_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_float(MicroBuffer* mb, const float* array, const uint32_t size);
microcdr_DllAPI bool serialize_sequence_double(MicroBuffer* mb, const double* array, const uint32_t size);

microcdr_DllAPI bool deserialize_sequence_char(MicroBuffer* mb, char* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_bool(MicroBuffer* mb, bool* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_uint8_t(MicroBuffer* mb, uint8_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_uint16_t(MicroBuffer* mb, uint16_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_uint32_t(MicroBuffer* mb, uint32_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_uint64_t(MicroBuffer* mb, uint64_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_int8_t(MicroBuffer* mb, int8_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_int16_t(MicroBuffer* mb, int16_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_int32_t(MicroBuffer* mb, int32_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_int64_t(MicroBuffer* mb, int64_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_float(MicroBuffer* mb, float* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_sequence_double(MicroBuffer* mb, double* array, uint32_t* size, const uint32_t max_size);

microcdr_DllAPI bool serialize_endian_sequence_char(MicroBuffer* mb, Endianness endianness, const char* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_bool(MicroBuffer* mb, Endianness endianness, const bool* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_uint8_t(MicroBuffer* mb, Endianness endianness, const uint8_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_uint16_t(MicroBuffer* mb, Endianness endianness, const uint16_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_uint32_t(MicroBuffer* mb, Endianness endianness, const uint32_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_uint64_t(MicroBuffer* mb, Endianness endianness, const uint64_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_int8_t(MicroBuffer* mb, Endianness endianness, const int8_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_int16_t(MicroBuffer* mb, Endianness endianness, const int16_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_int32_t(MicroBuffer* mb, Endianness endianness, const int32_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_int64_t(MicroBuffer* mb, Endianness endianness, const int64_t* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_float(MicroBuffer* mb, Endianness endianness, const float* array, const uint32_t size);
microcdr_DllAPI bool serialize_endian_sequence_double(MicroBuffer* mb, Endianness endianness, const double* array, const uint32_t size);

microcdr_DllAPI bool deserialize_endian_sequence_char(MicroBuffer* mb, Endianness endianness, char* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_bool(MicroBuffer* mb, Endianness endianness, bool* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_uint8_t(MicroBuffer* mb, Endianness endianness, uint8_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_uint16_t(MicroBuffer* mb, Endianness endianness, uint16_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_uint32_t(MicroBuffer* mb, Endianness endianness, uint32_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_uint64_t(MicroBuffer* mb, Endianness endianness, uint64_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_int8_t(MicroBuffer* mb, Endianness endianness, int8_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_int16_t(MicroBuffer* mb, Endianness endianness, int16_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_int32_t(MicroBuffer* mb, Endianness endianness, int32_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_int64_t(MicroBuffer* mb, Endianness endianness, int64_t* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_float(MicroBuffer* mb, Endianness endianness, float* array, uint32_t* size, const uint32_t max_size);
microcdr_DllAPI bool deserialize_endian_sequence_double(MicroBuffer* mb, Endianness endianness, double* array, uint32_t* size, const uint32_t max_size);


#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_SEQUENCE_H_
