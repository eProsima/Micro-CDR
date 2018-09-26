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

#ifndef _SRC_TYPES_BASIC_INTERNALS_H_
#define _SRC_TYPES_BASIC_INTERNALS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <microcdr/common.h>

// -------------------------------------------------------------------
//                  INTERNAL SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------
bool serialize_byte_1(mcMicroBuffer* buffer, const uint8_t* byte);
bool serialize_byte_2(mcMicroBuffer* buffer, Endianness endianness, const uint16_t* bytes);
bool serialize_byte_4(mcMicroBuffer* buffer, Endianness endianness, const uint32_t* bytes);
bool serialize_byte_8(mcMicroBuffer* buffer, Endianness endianness, const uint64_t* bytes);

bool deserialize_byte_1(mcMicroBuffer* buffer, uint8_t* byte);
bool deserialize_byte_2(mcMicroBuffer* buffer, Endianness endianness, uint16_t* bytes);
bool deserialize_byte_4(mcMicroBuffer* buffer, Endianness endianness, uint32_t* bytes);
bool deserialize_byte_8(mcMicroBuffer* buffer, Endianness endianness, uint64_t* bytes);

#ifdef __cplusplus
}
#endif

#endif //_SRC_TYPES_BASIC_INTERNALS_H_
