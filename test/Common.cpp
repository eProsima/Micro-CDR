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

#include <gtest/gtest.h>
#include <ucdr/microcdr.h>

extern "C"
{
#include <c/common.c>
}

#include <cstring>

class CommonTest : public ::testing::Test
{
public:
    CommonTest()
    {
        ucdr_init_stream(&us, buffer, sizeof(buffer));
    }

public:
    ucdrStream us;
    uint8_t buffer[66 + UCDR_BUFFER_INFO_SIZE];
};

TEST_F(CommonTest, InitStream)
{
    EXPECT_EQ(us.offset, 0);
    EXPECT_EQ(us.size, sizeof(buffer));
    EXPECT_EQ(us.iterator, buffer);
    EXPECT_EQ(us.endianness, UCDR_MACHINE_ENDIANNESS);
    EXPECT_EQ(us.error, false);

    EXPECT_EQ(us.buffer_info.origin, 0);
    EXPECT_EQ(us.buffer_info.data, buffer);
    EXPECT_EQ(us.buffer_info.size, sizeof(buffer));
    EXPECT_EQ(us.buffer_info.next, reinterpret_cast<void*>(NULL));
    EXPECT_EQ(us.buffer_info.prev, reinterpret_cast<void*>(NULL));
}

TEST_F(CommonTest, InitStreamOffset)
{
    ucdr_init_stream_offset(&us, buffer, sizeof(buffer), 11);

    EXPECT_EQ(us.offset, 11);
    EXPECT_EQ(us.size, sizeof(buffer));
    EXPECT_EQ(us.iterator, buffer + 11);
    EXPECT_EQ(us.endianness, UCDR_MACHINE_ENDIANNESS);
    EXPECT_EQ(us.error, false);

    EXPECT_EQ(us.buffer_info.origin, 11);
    EXPECT_EQ(us.buffer_info.data, buffer);
    EXPECT_EQ(us.buffer_info.size, sizeof(buffer));
    EXPECT_EQ(us.buffer_info.next, reinterpret_cast<void*>(NULL));
    EXPECT_EQ(us.buffer_info.prev, reinterpret_cast<void*>(NULL));
}

TEST_F(CommonTest, InitStreamBigEndian)
{
    ucdr_init_stream_offset_endian(&us, buffer, sizeof(buffer), 11, UCDR_BIG_ENDIANNESS);

    EXPECT_EQ(us.offset, 11);
    EXPECT_EQ(us.size, sizeof(buffer));
    EXPECT_EQ(us.iterator, buffer + 11);
    EXPECT_EQ(us.endianness, UCDR_BIG_ENDIANNESS);
    EXPECT_EQ(us.error, false);

    EXPECT_EQ(us.buffer_info.origin, 11);
    EXPECT_EQ(us.buffer_info.data, buffer);
    EXPECT_EQ(us.buffer_info.size, sizeof(buffer));
    EXPECT_EQ(us.buffer_info.next, reinterpret_cast<void*>(NULL));
    EXPECT_EQ(us.buffer_info.prev, reinterpret_cast<void*>(NULL));
}

TEST_F(CommonTest, InitStreamLittleEndian)
{
    ucdr_init_stream_offset_endian(&us, buffer, sizeof(buffer), 11, UCDR_LITTLE_ENDIANNESS);

    EXPECT_EQ(us.offset, 11);
    EXPECT_EQ(us.size, sizeof(buffer));
    EXPECT_EQ(us.iterator, buffer + 11);
    EXPECT_EQ(us.endianness, UCDR_LITTLE_ENDIANNESS);
    EXPECT_EQ(us.error, false);

    EXPECT_EQ(us.buffer_info.next, reinterpret_cast<void*>(NULL));
    EXPECT_EQ(us.buffer_info.prev, reinterpret_cast<void*>(NULL));
}

TEST_F(CommonTest, InitBufferInfo)
{
    ucdr_init_buffer_info(&us.buffer_info, 0, us.iterator, us.size);

    EXPECT_EQ(us.buffer_info.size, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);

    ucdrBufferInfo binfo;
    memcpy(&binfo, us.buffer_info.data + us.buffer_info.size, UCDR_BUFFER_INFO_SIZE);

    EXPECT_EQ(us.buffer_info.origin, binfo.origin);
    EXPECT_EQ(us.buffer_info.size, binfo.size);
    EXPECT_EQ(us.buffer_info.data, binfo.data);
    EXPECT_EQ(us.buffer_info.next, binfo.next);
    EXPECT_EQ(us.buffer_info.prev, binfo.prev);
}

TEST_F(CommonTest, UpdateBufferInfo)
{
    ucdrBufferInfo init_binfo;
    ucdr_init_buffer_info(&init_binfo, 0, us.iterator, us.size);
    init_binfo.origin = 11;

    ucdrBufferInfo copy_binfo;
    memcpy(&copy_binfo, init_binfo.data + init_binfo.size, UCDR_BUFFER_INFO_SIZE);

    EXPECT_NE(init_binfo.origin, copy_binfo.origin);

    ucdr_update_buffer_info(&init_binfo);
    memcpy(&copy_binfo, init_binfo.data + init_binfo.size, UCDR_BUFFER_INFO_SIZE);

    EXPECT_EQ(init_binfo.origin, copy_binfo.origin);
}

TEST_F(CommonTest, InitList)
{
    EXPECT_TRUE(ucdr_init_list(&us));
    EXPECT_EQ(us.size, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);
}

TEST_F(CommonTest, LinkBuffers)
{
    uint8_t buffer1[sizeof(buffer)];
    uint8_t buffer2[sizeof(buffer)];

    ucdrBufferInfo prev_buffer;
    ucdrBufferInfo next_buffer;

    ucdr_init_buffer_info(&prev_buffer, 11, buffer1, sizeof(buffer1));
    ucdr_init_buffer_info(&next_buffer, 12, buffer2, sizeof(buffer2));

    ucdr_link_buffers(&prev_buffer, &next_buffer);
    EXPECT_EQ(prev_buffer.next, next_buffer.data + next_buffer.size);
    EXPECT_EQ(next_buffer.prev, prev_buffer.data + prev_buffer.size);

    memcpy(&prev_buffer, prev_buffer.data + prev_buffer.size, UCDR_BUFFER_INFO_SIZE);
    memcpy(&next_buffer, next_buffer.data + next_buffer.size, UCDR_BUFFER_INFO_SIZE);
    EXPECT_EQ(prev_buffer.next, next_buffer.data + next_buffer.size);
    EXPECT_EQ(next_buffer.prev, prev_buffer.data + prev_buffer.size);
}

TEST_F(CommonTest, NextBufferInfo)
{
    uint8_t buffer1[sizeof(buffer)];
    uint8_t buffer2[sizeof(buffer)];

    ucdrBufferInfo prev_buffer;
    ucdrBufferInfo next_buffer;

    ucdr_init_buffer_info(&prev_buffer, 0, buffer1, sizeof(buffer1));
    ucdr_init_buffer_info(&next_buffer, 0, buffer2, sizeof(buffer2));

    ucdr_link_buffers(&prev_buffer, &next_buffer);
    EXPECT_TRUE(ucdr_next_buffer_info(&prev_buffer));
    EXPECT_EQ(prev_buffer.origin, prev_buffer.origin);
    EXPECT_EQ(prev_buffer.data, prev_buffer.data);
    EXPECT_EQ(prev_buffer.size, prev_buffer.size);
    EXPECT_EQ(prev_buffer.next, prev_buffer.next);
    EXPECT_EQ(prev_buffer.prev, prev_buffer.prev);
    EXPECT_FALSE(ucdr_next_buffer_info(&prev_buffer));
}

TEST_F(CommonTest, PrevBufferInfo)
{
    uint8_t buffer1[sizeof(buffer)];
    uint8_t buffer2[sizeof(buffer)];

    ucdrBufferInfo prev_buffer;
    ucdrBufferInfo next_buffer;

    ucdr_init_buffer_info(&prev_buffer, 0, buffer1, sizeof(buffer1));
    ucdr_init_buffer_info(&next_buffer, 0, buffer2, sizeof(buffer2));

    ucdr_link_buffers(&prev_buffer, &next_buffer);
    EXPECT_TRUE(ucdr_prev_buffer_info(&next_buffer));
    EXPECT_EQ(prev_buffer.origin, prev_buffer.origin);
    EXPECT_EQ(prev_buffer.data, prev_buffer.data);
    EXPECT_EQ(prev_buffer.size, prev_buffer.size);
    EXPECT_EQ(prev_buffer.next, prev_buffer.next);
    EXPECT_EQ(prev_buffer.prev, prev_buffer.prev);
    EXPECT_FALSE(ucdr_prev_buffer_info(&next_buffer));
}

TEST_F(CommonTest, Alignment)
{
    EXPECT_EQ(ucdr_alignment(1, 1), 0);
    EXPECT_EQ(ucdr_alignment(1, 2), 1);
    EXPECT_EQ(ucdr_alignment(1, 4), 3);
    EXPECT_EQ(ucdr_alignment(1, 8), 7);
}

TEST_F(CommonTest, AppendBuffer)
{
    uint8_t buffer1[sizeof(buffer)];
    uint8_t buffer2[sizeof(buffer)];

    ucdr_append_buffer(&us, buffer1, sizeof(buffer1));
    EXPECT_EQ(us.size, 2 * (sizeof(buffer) - UCDR_BUFFER_INFO_SIZE));

    ucdr_append_buffer(&us, buffer2, sizeof(buffer2));
    EXPECT_EQ(us.size, 3 * (sizeof(buffer) - UCDR_BUFFER_INFO_SIZE));

    ucdrBufferInfo binfo = us.buffer_info;
    EXPECT_EQ(binfo.data, buffer);
    EXPECT_EQ(binfo.size, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);

    EXPECT_TRUE(ucdr_next_buffer_info(&binfo));
    EXPECT_EQ(binfo.data, buffer1);
    EXPECT_EQ(binfo.size, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);
    EXPECT_EQ(binfo.origin, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);

    EXPECT_TRUE(ucdr_next_buffer_info(&binfo));
    EXPECT_EQ(binfo.data, buffer2);
    EXPECT_EQ(binfo.size, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);
    EXPECT_EQ(binfo.origin, 2 * (sizeof(buffer) - UCDR_BUFFER_INFO_SIZE));

    EXPECT_FALSE(ucdr_next_buffer_info(&binfo));

    EXPECT_TRUE(ucdr_prev_buffer_info(&binfo));
    EXPECT_EQ(binfo.data, buffer1);
    EXPECT_EQ(binfo.size, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);

    EXPECT_TRUE(ucdr_prev_buffer_info(&binfo));
    EXPECT_EQ(binfo.data, buffer);
    EXPECT_EQ(binfo.size, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);

    EXPECT_FALSE(ucdr_prev_buffer_info(&binfo));
}

TEST_F(CommonTest, ResetStream)
{
    ++us.offset;
    ++us.iterator;

    ucdr_reset_stream(&us);
    EXPECT_EQ(us.offset, 0);
    EXPECT_EQ(us.iterator, buffer);

    uint8_t buffer1[sizeof(buffer)];
    ucdr_append_buffer(&us, buffer1, sizeof(buffer1));
    ucdr_next_buffer_info(&us.buffer_info);
    us.iterator = us.buffer_info.data;
    us.offset = sizeof(buffer1) - UCDR_BUFFER_INFO_SIZE;

    ucdr_reset_stream(&us);
    EXPECT_EQ(us.offset, 0);
    EXPECT_EQ(us.iterator, buffer);
}

TEST_F(CommonTest, Size)
{
    EXPECT_EQ(ucdr_size(&us), us.size);
}

TEST_F(CommonTest, UsedSize)
{
    us.offset = 2;
    EXPECT_EQ(ucdr_used_size(&us), us.offset);
}

TEST_F(CommonTest, RemaningSize)
{
    us.offset = 2;
    EXPECT_EQ(ucdr_remaining_size(&us), us.size - us.offset);
}

TEST_F(CommonTest, CopyStream)
{
    uint8_t buffer1_obj[127];
    uint8_t buffer2_obj[256];
    uint8_t buffer3_obj[128];
    std::memset(buffer1_obj, 11, sizeof(buffer1_obj));
    std::memset(buffer2_obj, 11, sizeof(buffer2_obj));
    std::memset(buffer3_obj, 11, sizeof(buffer3_obj));

    uint8_t buffer1_dst[127] = {0};
    uint8_t buffer2_dst[256] = {0};
    uint8_t buffer3_dst[128] = {0};

    ucdrStream us_dst;
    ucdr_init_stream(&us_dst, buffer1_dst, sizeof(buffer1_dst));
    ucdr_append_buffer(&us_dst, buffer2_dst, sizeof(buffer2_dst));
    ucdr_append_buffer(&us_dst, buffer3_dst, sizeof(buffer3_dst));

    uint8_t buffer1_src[128];
    uint8_t buffer2_src[256];
    uint8_t buffer3_src[127];
    std::memset(buffer1_src, 11, sizeof(buffer1_src));
    std::memset(buffer2_src, 11, sizeof(buffer2_src));
    std::memset(buffer3_src, 11, sizeof(buffer3_src));

    ucdrStream us_src;
    ucdr_init_stream(&us_src, buffer1_src, sizeof(buffer1_src));
    ucdr_append_buffer(&us_src, buffer2_src, sizeof(buffer2_src));
    ucdr_append_buffer(&us_src, buffer3_src, sizeof(buffer3_src));

    us_src.offset = us_src.size;

    EXPECT_TRUE(ucdr_copy_stream(&us_dst, &us_src));
    EXPECT_EQ(std::memcmp(buffer1_dst, buffer1_obj, sizeof(buffer1_dst) - UCDR_BUFFER_INFO_SIZE), 0);
    EXPECT_EQ(std::memcmp(buffer2_dst, buffer2_obj, sizeof(buffer2_dst) - UCDR_BUFFER_INFO_SIZE), 0);
    EXPECT_EQ(std::memcmp(buffer3_dst, buffer3_obj, sizeof(buffer3_dst) - UCDR_BUFFER_INFO_SIZE), 0);

    std::memset(buffer1_dst, 0, sizeof(buffer1_dst));
    ucdr_init_stream(&us_dst, buffer1_dst, sizeof(buffer1_dst));
    ucdr_init_stream(&us_src, buffer1_src, sizeof(buffer1_src));

    us_src.offset = us_src.size;
    EXPECT_FALSE(ucdr_copy_stream(&us_dst, &us_src));

    us_src.offset = us_dst.size;
    EXPECT_TRUE(ucdr_copy_stream(&us_dst, &us_src));
    EXPECT_EQ(std::memcmp(buffer1_dst, buffer1_src, us_src.offset), 0);
}

TEST_F(CommonTest, Align)
{
    uint8_t buffer1[sizeof(buffer) + 1];
    ucdr_append_buffer(&us, buffer1, sizeof(buffer1));
    us.offset = sizeof(buffer) - UCDR_BUFFER_INFO_SIZE - 1;
    us.iterator = us.buffer_info.data + sizeof(buffer) - UCDR_BUFFER_INFO_SIZE - 1;

    EXPECT_TRUE(ucdr_align(&us, 1));
    EXPECT_EQ(us.offset, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE - 1);
    EXPECT_EQ(us.iterator, us.buffer_info.data + sizeof(buffer) - UCDR_BUFFER_INFO_SIZE - 1);

    EXPECT_TRUE(ucdr_align(&us, 2));
    EXPECT_EQ(us.offset, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE);
    EXPECT_EQ(us.iterator, us.buffer_info.data);

    ucdr_prev_buffer_info(&us.buffer_info);
    us.offset = sizeof(buffer) - UCDR_BUFFER_INFO_SIZE - 1;
    us.iterator = us.buffer_info.data + sizeof(buffer) - UCDR_BUFFER_INFO_SIZE - 1;
    EXPECT_TRUE(ucdr_align(&us, 4));
    EXPECT_EQ(us.offset, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE + 2);
    EXPECT_EQ(us.iterator, us.buffer_info.data + 2);

    ucdr_prev_buffer_info(&us.buffer_info);
    us.offset = sizeof(buffer) - UCDR_BUFFER_INFO_SIZE - 1;
    us.iterator = us.buffer_info.data + sizeof(buffer) - UCDR_BUFFER_INFO_SIZE - 1;
    EXPECT_TRUE(ucdr_align(&us, 8));
    EXPECT_EQ(us.offset, sizeof(buffer) - UCDR_BUFFER_INFO_SIZE + 6);
    EXPECT_EQ(us.iterator, us.buffer_info.data + 6);

    us.offset = us.size;
    us.iterator = us.buffer_info.data + us.buffer_info.size;
    EXPECT_TRUE(ucdr_align(&us, 1));

    us.offset = us.size;
    us.iterator = us.buffer_info.data + us.buffer_info.size;
    EXPECT_FALSE(ucdr_align(&us, 2));
}

int main(int args, char** argv)
{
    ::testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}
