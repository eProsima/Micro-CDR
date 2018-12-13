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

#include <ucdr/common.h>

// -------------------------------------------------------------------
//                         DECLARATION MACROS
// -------------------------------------------------------------------
#define UCDR_ARRAY_SERIALIZE_DECLARATION(TYPE) \
    UCDRDLLAPI bool ucdr_serialize_array_ ## TYPE(ucdrBuffer* ub, const TYPE* array, const uint32_t size); \
    UCDRDLLAPI bool ucdr_serialize_endian_array_ ## TYPE(ucdrBuffer* ub, ucdrEndianness endianness, const TYPE* array, const uint32_t size); \

#define UCDR_ARRAY_DESERIALIZE_DECLARATION(TYPE) \
    UCDRDLLAPI bool ucdr_deserialize_array_ ## TYPE(ucdrBuffer* ub, TYPE* array, const uint32_t size); \
    UCDRDLLAPI bool ucdr_deserialize_endian_array_ ## TYPE(ucdrBuffer* ub, ucdrEndianness endianness, TYPE* array, const uint32_t size); \

#define UCDR_ARRAY_DECLARATIONS(TYPE) \
    UCDR_ARRAY_SERIALIZE_DECLARATION(TYPE) \
    UCDR_ARRAY_DESERIALIZE_DECLARATION(TYPE) \

// -------------------------------------------------------------------
//              PUBLIC DE-SERIALIZATION DECLARATIONS
// -------------------------------------------------------------------
UCDR_ARRAY_DECLARATIONS(char)
UCDR_ARRAY_DECLARATIONS(bool)
UCDR_ARRAY_DECLARATIONS(uint8_t)
UCDR_ARRAY_DECLARATIONS(uint16_t)
UCDR_ARRAY_DECLARATIONS(uint32_t)
UCDR_ARRAY_DECLARATIONS(uint64_t)
UCDR_ARRAY_DECLARATIONS(int8_t)
UCDR_ARRAY_DECLARATIONS(int16_t)
UCDR_ARRAY_DECLARATIONS(int32_t)
UCDR_ARRAY_DECLARATIONS(int64_t)
UCDR_ARRAY_DECLARATIONS(float)
UCDR_ARRAY_DECLARATIONS(double)

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_ARRAY_H_
