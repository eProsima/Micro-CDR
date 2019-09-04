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

#include "common_internal.h"

#include <string.h>

#define UCDR_BUFFER_INFO_SIZE sizeof(ucdrBufferInfo)

// -------------------------------------------------------------------
//                       PUBLIC IMPLEMENTATION
// -------------------------------------------------------------------
void ucdr_init_stream(
        ucdrStream* us,
        uint8_t* buffer,
        size_t size)
{
    ucdr_init_stream_offset(us, buffer, size, 0u);
}

void ucdr_init_stream_offset(
        ucdrStream* us,
        uint8_t* buffer,
        size_t size,
        size_t offset)
{
    ucdr_init_stream_offset_endian(us, buffer, size, offset, UCDR_MACHINE_ENDIANNESS);
}

void ucdr_init_stream_offset_endian(
        ucdrStream* us,
        uint8_t* buffer,
        size_t size,
        size_t offset,
        ucdrEndianness endianness)
{
    us->offset = offset;
    us->origin = offset;
    us->iterator = buffer + offset;
    us->size = size;
    us->endianness = endianness;
    us->error = false;

    us->buffer_info.origin = 0;
    us->buffer_info.size = size;
    us->buffer_info.data = buffer;
    us->buffer_info.next = NULL;
    us->buffer_info.prev = NULL;
}

bool ucdr_append_buffer(
        ucdrStream* us,
        uint8_t* data,
        size_t size)
{
    bool rv = false;
    if (ucdr_init_list(us))
    {
        ucdrBufferInfo prev_binfo = us->buffer_info;
        while (ucdr_next_buffer_info(&prev_binfo))
        {}

        ucdrBufferInfo next_binfo;
        if (ucdr_init_buffer_info(&next_binfo, prev_binfo.origin + prev_binfo.size, data, size))
        {
            us->size += next_binfo.size;
            ucdr_link_buffers(&prev_binfo, &next_binfo);
            memcpy(&us->buffer_info, us->buffer_info.data + us->buffer_info.size, UCDR_BUFFER_INFO_SIZE);
            rv = true;
        }
    }
    return rv;
}

void ucdr_reset_stream(
        ucdrStream* us)
{
    us->offset = us->origin;
    us->error = false;

    while (ucdr_prev_buffer_info(&us->buffer_info))
    {}
    us->iterator = us->buffer_info.data;
}

size_t ucdr_size(
        const ucdrStream* us)
{
    return us->size;
}

size_t ucdr_used_size(
        const ucdrStream* us)
{
    return us->offset;
}

size_t ucdr_remaining_size(
        const ucdrStream* us)
{
    return us->size - us->offset;
}

ucdrEndianness ucdr_endianness(
        const ucdrStream* us)
{
    return us->endianness;
}

bool ucdr_has_error(
        const ucdrStream* us)
{
    return us->error;
}

bool ucdr_copy_stream(
        ucdrStream* us_dst,
        const ucdrStream* us_src)
{
    bool rv = false;
    size_t remaining_size = us_src->offset - us_src->origin;

    if (us_dst->size >= remaining_size)
    {
        rv = true;

        ucdrStream us_tmp = *us_src;

        ucdr_reset_stream(us_dst);
        ucdr_reset_stream(&us_tmp);

        do
        {
            size_t avsize_dst_buffer = us_dst->buffer_info.size - (us_dst->offset - us_dst->buffer_info.origin);
            size_t avsize_tmp_buffer = us_tmp.buffer_info.size - (us_tmp.offset - us_tmp.buffer_info.origin);

            if (remaining_size <= avsize_dst_buffer && remaining_size <= avsize_tmp_buffer)
            {
                memcpy(us_dst->iterator, us_tmp.iterator, remaining_size);
                us_dst->iterator += remaining_size;
                remaining_size = 0;
            }
            else
            {
                size_t copied_size = 0;
                bool promote_dst = false;
                bool promote_tmp = false;

                if (avsize_dst_buffer < avsize_tmp_buffer)
                {
                    copied_size = avsize_dst_buffer;
                    promote_dst = true;
                }
                else if (avsize_dst_buffer > avsize_tmp_buffer)
                {
                    copied_size = avsize_tmp_buffer;
                    promote_tmp = true;
                }
                else
                {
                    copied_size = avsize_dst_buffer;
                    promote_dst = true;
                    promote_tmp = true;
                }

                memcpy(us_dst->iterator, us_tmp.iterator, copied_size);
                us_dst->iterator += copied_size;
                us_dst->offset += copied_size;
                us_tmp.iterator += copied_size;
                us_tmp.offset += copied_size;
                remaining_size -= copied_size;

                if (promote_dst)
                {
                    ucdr_next_buffer_info(&us_dst->buffer_info);
                    us_dst->iterator = us_dst->buffer_info.data;
                }

                if (promote_tmp)
                {
                    ucdr_next_buffer_info(&us_tmp.buffer_info);
                    us_tmp.iterator = us_tmp.buffer_info.data;
                }
            }
        } while(remaining_size > 0);
    }

    return rv;
}

bool ucdr_align(
        ucdrStream* us,
        size_t type_size)
{
    size_t alignment = ucdr_alignment(us->offset, type_size);
    bool rv = alignment <= ucdr_remaining_size(us);

    if ((0 != alignment) && rv)
    {
        do
        {
            size_t buffer_available_size = us->buffer_info.size - (us->offset - us->buffer_info.origin);
            if (alignment < buffer_available_size)
            {
                ucdr_advance_stream(us, alignment);
                alignment = 0;
            }
            else
            {
                ucdr_promote_buffer(us);
                alignment -= buffer_available_size;
            }
        } while(alignment > 0);
    }

    return rv;
}

// -------------------------------------------------------------------
//                       INTERNAL UTIL IMPLEMENTATION
// -------------------------------------------------------------------
bool ucdr_init_buffer_info(
        ucdrBufferInfo* binfo,
        size_t origin,
        uint8_t* data,
        size_t size)
{
    bool rv = false;
    if (UCDR_BUFFER_INFO_SIZE <= size)
    {
        binfo->origin = origin;
        binfo->data = data;
        binfo->size = size - UCDR_BUFFER_INFO_SIZE;
        binfo->next = NULL;
        binfo->prev = NULL;
        memcpy(binfo->data + binfo->size, binfo, UCDR_BUFFER_INFO_SIZE);
        rv = true;
    }
    return rv;
}

bool ucdr_init_list(
        ucdrStream* us)
{
    if ((NULL != us->buffer_info.next) || (NULL != us->buffer_info.prev))
    {
        return true;
    }

    bool rv = false;
    if (ucdr_init_buffer_info(&us->buffer_info, 0u, us->iterator - us->offset, us->size))
    {
        us->size = us->buffer_info.size;
        rv = true;
    }
    return rv;
}

void ucdr_update_buffer_info(
        ucdrBufferInfo* binfo)
{
    memcpy(binfo->data + binfo->size, binfo, UCDR_BUFFER_INFO_SIZE);
}

void ucdr_link_buffers(
        ucdrBufferInfo* prev_binfo,
        ucdrBufferInfo* next_binfo)
{
    prev_binfo->next = next_binfo->data + next_binfo->size;
    next_binfo->prev = prev_binfo->data + prev_binfo->size;
    ucdr_update_buffer_info(prev_binfo);
    ucdr_update_buffer_info(next_binfo);
}

bool ucdr_next_buffer_info(
        ucdrBufferInfo* binfo)
{
    if (NULL != binfo->next)
    {
        memcpy(binfo, binfo->next, UCDR_BUFFER_INFO_SIZE);
        return true;
    }
    return false;
}

bool ucdr_prev_buffer_info(
        ucdrBufferInfo* binfo)
{
    if (NULL != binfo->prev)
    {
        memcpy(binfo, binfo->prev, UCDR_BUFFER_INFO_SIZE);
        return true;
    }
    return false;
}

size_t ucdr_alignment(
        size_t offset,
        size_t data_size)
{
    return ((data_size - (offset % data_size)) & (data_size - 1));
}

bool ucdr_enough_space(
        const ucdrStream* us,
        size_t bytes)
{
    return (us->size - us->offset) >= bytes;
}

size_t ucdr_buffer_remaining_size(
        const ucdrStream* us)
{
    return us->buffer_info.size - (us->offset - us->buffer_info.origin);
}

void ucdr_advance_stream(
        ucdrStream* us,
        size_t size)
{
    us->offset += size;
    us->iterator += size;
}

bool ucdr_promote_buffer(
        ucdrStream* us)
{
    bool rv = false;
    if (ucdr_next_buffer_info(&us->buffer_info))
    {
        us->offset = us->buffer_info.origin;
        us->iterator = us->buffer_info.data;
        rv = true;
    }
    return rv;
}
