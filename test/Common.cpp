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
#include <c/common.c>

class CommonTest : public ::testing::Test
{
public:
    CommonTest()
    {
        ucdr_init_stream(&us, buffer, sizeof(buffer));
    }

public:
    ucdrStream us;
    uint8_t buffer[UINT8_MAX];
};

TEST_F(CommonTest, InitStream)
{
    EXPECT_EQ(us.offset, 0);
    EXPECT_EQ(us.size, sizeof(buffer));
    EXPECT_EQ(us.iterator, buffer);
    EXPECT_EQ(us.endianness, UCDR_MACHINE_ENDIANNESS);
    EXPECT_EQ(us.error, false);

    EXPECT_EQ(us.buffer_info.next, reinterpret_cast<void*>(NULL));
    EXPECT_EQ(us.buffer_info.prev, reinterpret_cast<void*>(NULL));
}

TEST_F(CommonTest, InitStreamOffset)
{
    ucdr_init_stream_offset(&us, buffer, sizeof(buffer), 11);

    EXPECT_EQ(us.offset, 11);
    EXPECT_EQ(us.size, sizeof(buffer));
    EXPECT_EQ(us.iterator, buffer);
    EXPECT_EQ(us.endianness, UCDR_MACHINE_ENDIANNESS);
    EXPECT_EQ(us.error, false);

    EXPECT_EQ(us.buffer_info.next, reinterpret_cast<void*>(NULL));
    EXPECT_EQ(us.buffer_info.prev, reinterpret_cast<void*>(NULL));
}

TEST_F(CommonTest, InitStreamBigEndian)
{
    ucdr_init_stream_offset_endian(&us, buffer, sizeof(buffer), 11, UCDR_BIG_ENDIANNESS);

    EXPECT_EQ(us.offset, 11);
    EXPECT_EQ(us.size, sizeof(buffer));
    EXPECT_EQ(us.iterator, buffer);
    EXPECT_EQ(us.endianness, UCDR_BIG_ENDIANNESS);
    EXPECT_EQ(us.error, false);

    EXPECT_EQ(us.buffer_info.next, reinterpret_cast<void*>(NULL));
    EXPECT_EQ(us.buffer_info.prev, reinterpret_cast<void*>(NULL));
}

TEST_F(CommonTest, InitStreamLittleEndian)
{
    ucdr_init_stream_offset_endian(&us, buffer, sizeof(buffer), 11, UCDR_LITTLE_ENDIANNESS);

    EXPECT_EQ(us.offset, 11);
    EXPECT_EQ(us.size, sizeof(buffer));
    EXPECT_EQ(us.iterator, buffer);
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

int main(int args, char** argv)
{
    ::testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}
