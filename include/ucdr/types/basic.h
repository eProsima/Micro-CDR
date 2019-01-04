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
//                         DECLARATION MACROS
// -------------------------------------------------------------------
#define UCDR_BASIC_TYPE_SERIALIZE_DECLARATION(SUFFIX, TYPE) \
    UCDRDLLAPI bool ucdr_serialize ## SUFFIX(ucdrBuffer* ub, const TYPE value); \
    UCDRDLLAPI bool ucdr_serialize_endian ## SUFFIX(ucdrBuffer* ub, ucdrEndianness endianness, const TYPE value); \

#define UCDR_BASIC_TYPE_DESERIALIZE_DECLARATION(SUFFIX, TYPE) \
    UCDRDLLAPI bool ucdr_deserialize ## SUFFIX(ucdrBuffer* ub, TYPE* value); \
    UCDRDLLAPI bool ucdr_deserialize_endian ## SUFFIX(ucdrBuffer* ub, ucdrEndianness endianness, TYPE* value); \

#define UCDR_BASIC_TYPE_DECLARATIONS(SUFFIX, TYPE) \
    UCDR_BASIC_TYPE_SERIALIZE_DECLARATION(SUFFIX, TYPE) \
    UCDR_BASIC_TYPE_DESERIALIZE_DECLARATION(SUFFIX, TYPE) \

// -------------------------------------------------------------------
//              PUBLIC DE-SERIALIZATION DECLARATIONS
// -------------------------------------------------------------------
UCDR_BASIC_TYPE_DECLARATIONS(_char, char)
UCDR_BASIC_TYPE_DECLARATIONS(_bool, bool)
UCDR_BASIC_TYPE_DECLARATIONS(_uint8_t, uint8_t)
UCDR_BASIC_TYPE_DECLARATIONS(_uint16_t, uint16_t)
UCDR_BASIC_TYPE_DECLARATIONS(_uint32_t, uint32_t)
UCDR_BASIC_TYPE_DECLARATIONS(_uint64_t, uint64_t)
UCDR_BASIC_TYPE_DECLARATIONS(_int8_t, int8_t)
UCDR_BASIC_TYPE_DECLARATIONS(_int16_t, int16_t)
UCDR_BASIC_TYPE_DECLARATIONS(_int32_t, int32_t)
UCDR_BASIC_TYPE_DECLARATIONS(_int64_t, int64_t)
UCDR_BASIC_TYPE_DECLARATIONS(_float, float)
UCDR_BASIC_TYPE_DECLARATIONS(_double, double)

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_BASIC_H_
