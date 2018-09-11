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

#ifndef _MICROCDR_COMMON_H_
#define _MICROCDR_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <microcdr/microcdr_dll.h>
#include <microcdr/config.h.in>

#include <stdint.h>
#include <stdbool.h>

typedef enum Endianness {
    BIG_ENDIANNESS,
    LITTLE_ENDIANNESS

} Endianness;

typedef enum BufferError {
    BUFFER_OK,
    BUFFER_NOK

} BufferError;

typedef struct MicroState
{
    uint8_t *position;
    uint32_t last_data_size;

    BufferError error;

} MicroState;

typedef struct MicroBuffer
{
    uint8_t *init;
    uint8_t *final;
    uint8_t *iterator;

    Endianness endianness;
    uint32_t last_data_size;

    BufferError error;

} MicroBuffer;

microcdr_DllAPI extern const Endianness MACHINE_ENDIANNESS;

uint32_t get_alignment_offset(MicroBuffer* buffer, const uint32_t data_size);
bool check_size(MicroBuffer* buffer, const uint32_t bytes);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_COMMON_H_
