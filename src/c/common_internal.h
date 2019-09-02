// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#ifndef SRC_COMMON_INTERNAL_H_
#define SRC_COMMON_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ucdr/microcdr.h>

// -------------------------------------------------------------------
//                     INTERNAL UTIL FUNCTIONS
// -------------------------------------------------------------------
bool ucdr_init_buffer_info(
        ucdrBufferInfo* binfo,
        size_t origin,
        uint8_t* data,
        size_t size);

bool ucdr_init_list(
        ucdrStream* us);

void ucdr_update_buffer_info(
        ucdrBufferInfo* binfo);

void ucdr_link_buffers(
        ucdrBufferInfo* prev_binfo,
        ucdrBufferInfo* next_binfo);

bool ucdr_next_buffer_info(
        ucdrBufferInfo* binfo);

bool ucdr_prev_buffer_info(
        ucdrBufferInfo* binfo);

size_t ucdr_alignment(
        size_t offset,
        size_t data_size);

bool ucdr_enough_space(
        const ucdrStream* us,
        size_t bytes);

size_t ucdr_buffer_remaining_size(
        const ucdrStream* us);

void ucdr_advance_stream(
        ucdrStream* us,
        size_t size);

bool ucdr_promote_buffer(
        ucdrStream* us);

#ifdef __cplusplus
}
#endif

#endif // SRC_COMMON_INTERNAL_H_
