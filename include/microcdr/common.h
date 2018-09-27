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

typedef enum mcEndianness {
    MC_BIG_ENDIANNESS,
    MC_LITTLE_ENDIANNESS

} mcEndianness;

typedef struct mcBuffer
{
    uint8_t *init;
    uint8_t *final;
    uint8_t *iterator;

    mcEndianness endianness;
    uint32_t last_data_size;

    bool error;

} mcBuffer;

MCDLLAPI extern const mcEndianness MC_MACHINE_ENDIANNESS;

// ------------------------------------------------
//              Main library functions
// ------------------------------------------------
MCDLLAPI void mc_init_buffer               (mcBuffer* mb, uint8_t* data, const uint32_t size);
MCDLLAPI void mc_init_buffer_offset        (mcBuffer* mb, uint8_t* data, const uint32_t size, uint32_t offset);
MCDLLAPI void mc_init_buffer_offset_endian (mcBuffer* mb, uint8_t* data, const uint32_t size, uint32_t offset, mcEndianness endianness);
MCDLLAPI void mc_copy_buffer               (mcBuffer* mb_dest, const mcBuffer* mb_source);

MCDLLAPI void mc_reset_buffer        (mcBuffer* mb);
MCDLLAPI void mc_reset_buffer_offset (mcBuffer* mb, const uint32_t offset);

MCDLLAPI void     mc_align_to              (mcBuffer* mb, const uint32_t alignment);
MCDLLAPI uint32_t mc_alignment             (uint32_t buffer_position, const uint32_t data_size);
MCDLLAPI uint32_t mc_buffer_alignment(const mcBuffer* mb, const uint32_t data_size);

MCDLLAPI size_t     mc_buffer_size      (const mcBuffer* mb);
MCDLLAPI size_t     mc_buffer_length    (const mcBuffer* mb);
MCDLLAPI size_t     mc_buffer_remaining (const mcBuffer* mb);
MCDLLAPI mcEndianness mc_buffer_endianness(const mcBuffer* mb);
MCDLLAPI bool       mc_buffer_has_error (const mcBuffer* mb);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_COMMON_H_
