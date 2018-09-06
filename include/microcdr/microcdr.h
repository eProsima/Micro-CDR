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

#ifndef _MICROCDR_MICRO_CDR_H_
#define _MICROCDR_MICRO_CDR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <microcdr/common.h>
#include <microcdr/types/basics.h>
#include <microcdr/types/array.h>
#include <microcdr/types/sequence.h>

#include <stddef.h>

microcdr_DllAPI void init_micro_buffer        (MicroBuffer* buffer, uint8_t* data, const uint32_t size);
microcdr_DllAPI void init_micro_buffer_offset (MicroBuffer* buffer, uint8_t* data, const uint32_t size, uint32_t offset);
microcdr_DllAPI void reset_micro_buffer       (MicroBuffer* buffer);
microcdr_DllAPI void reset_micro_buffer_offset(MicroBuffer* buffer, const uint32_t offset);

microcdr_DllAPI MicroState get_micro_state(MicroBuffer* buffer);
microcdr_DllAPI void restore_micro_state  (MicroBuffer* buffer, const MicroState state);

microcdr_DllAPI void align_to(MicroBuffer* buffer, const uint32_t size);
microcdr_DllAPI uint32_t get_alignment(uint32_t current_alignment, const uint32_t data_size);

microcdr_DllAPI size_t micro_buffer_size(const MicroBuffer* buffer);
microcdr_DllAPI size_t micro_buffer_length(const MicroBuffer* buffer);
microcdr_DllAPI size_t micro_buffer_remaining(const MicroBuffer* buffer);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_MICRO_CDR_H_
