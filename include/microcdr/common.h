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
#include <stddef.h>

typedef enum Endianness {
    BIG_ENDIANNESS,
    LITTLE_ENDIANNESS

} Endianness;

typedef struct MicroBuffer
{
    uint8_t *init;
    uint8_t *final;
    uint8_t *iterator;

    Endianness endianness;
    uint32_t last_data_size;

    bool error;

} MicroBuffer;

typedef struct MicroState
{
    uint8_t *position;
    uint32_t last_data_size;

    bool error;

} MicroState;


microcdr_DllAPI extern const Endianness MACHINE_ENDIANNESS;

// ------------------------------------------------
//              Main library functions
// ------------------------------------------------
microcdr_DllAPI void init_micro_buffer        (MicroBuffer* mb, uint8_t* data, const uint32_t size);
microcdr_DllAPI void init_micro_buffer_offset (MicroBuffer* mb, uint8_t* data, const uint32_t size, uint32_t offset);
microcdr_DllAPI void reset_micro_buffer       (MicroBuffer* mb);
microcdr_DllAPI void reset_micro_buffer_offset(MicroBuffer* mb, const uint32_t offset);

microcdr_DllAPI void align_to(MicroBuffer* mb, const uint32_t alignment);
microcdr_DllAPI uint32_t get_alignment(uint32_t buffer_position, const uint32_t data_size); // Deprecated?
microcdr_DllAPI uint32_t get_alignment_offset(MicroBuffer* mb, const uint32_t data_size); //Mix with get_alignment

microcdr_DllAPI size_t micro_buffer_size(const MicroBuffer* mb);
microcdr_DllAPI size_t micro_buffer_length(const MicroBuffer* mb);
microcdr_DllAPI size_t micro_buffer_remaining(const MicroBuffer* mb);

// ------------------------------------------------
//               MicroState Utility
// ------------------------------------------------
microcdr_DllAPI MicroState get_micro_state(MicroBuffer* mb);
microcdr_DllAPI void restore_micro_state  (MicroBuffer* mb, const MicroState state);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_COMMON_H_
