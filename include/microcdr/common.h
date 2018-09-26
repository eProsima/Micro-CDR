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

#include <microcdr/dll.h>
#include <microcdr/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum Endianness {
    BIG_ENDIANNESS,
    LITTLE_ENDIANNESS

} Endianness;

typedef struct mcMicroBuffer
{
    uint8_t *init;
    uint8_t *final;
    uint8_t *iterator;

    Endianness endianness;
    uint32_t last_data_size;

    bool error;

} mcMicroBuffer;

MCDLLAPI extern const Endianness MACHINE_ENDIANNESS;

// ------------------------------------------------
//              Main library functions
// ------------------------------------------------
MCDLLAPI void init_micro_buffer               (mcMicroBuffer* mb, uint8_t* data, const uint32_t size);
MCDLLAPI void init_micro_buffer_offset        (mcMicroBuffer* mb, uint8_t* data, const uint32_t size, uint32_t offset);
MCDLLAPI void init_micro_buffer_offset_endian (mcMicroBuffer* mb, uint8_t* data, const uint32_t size, uint32_t offset, Endianness endianness);
MCDLLAPI void copy_micro_buffer               (mcMicroBuffer* mb_dest, const mcMicroBuffer* mb_source);

MCDLLAPI void reset_micro_buffer        (mcMicroBuffer* mb);
MCDLLAPI void reset_micro_buffer_offset (mcMicroBuffer* mb, const uint32_t offset);

MCDLLAPI void     align_to            (mcMicroBuffer* mb, const uint32_t alignment);
MCDLLAPI uint32_t get_alignment       (uint32_t buffer_position, const uint32_t data_size); //change name
MCDLLAPI uint32_t get_alignment_offset(const mcMicroBuffer* mb, const uint32_t data_size); //change name

MCDLLAPI size_t     micro_buffer_size      (const mcMicroBuffer* mb);
MCDLLAPI size_t     micro_buffer_length    (const mcMicroBuffer* mb);
MCDLLAPI size_t     micro_buffer_remaining (const mcMicroBuffer* mb);
MCDLLAPI Endianness micro_buffer_endianness(const mcMicroBuffer* mb);
MCDLLAPI bool       micro_buffer_has_error (const mcMicroBuffer* mb);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_COMMON_H_
