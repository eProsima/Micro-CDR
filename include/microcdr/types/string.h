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

#ifndef _MICROCDR_TYPES_STRING_H_
#define _MICROCDR_TYPES_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <microcdr/common.h>

#include <stdint.h>
#include <stdbool.h>

// -------------------------------------------------------------------
//                   PUBLIC SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

MCDLLAPI bool mc_serialize_string(mcMicroBuffer* mb, const char* string);
MCDLLAPI bool mc_deserialize_string(mcMicroBuffer* mb, char* string, const uint32_t string_capacity);

MCDLLAPI bool mc_serialize_endian_string(mcMicroBuffer* mb, mrEndianness endianness, const char* string);
MCDLLAPI bool mc_deserialize_endian_string(mcMicroBuffer* mb, mrEndianness endianness, char* string, const uint32_t string_capacity);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_TYPES_STRING_H_
