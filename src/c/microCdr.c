#include <microcdr/microCdr.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <microcdr/microBuffer.h>

#include <stdint.h>

#include <stdio.h>
#include <setjmp.h>

void initMicroCDR(struct microCDR* m_microCDR, struct microBuffer* m_microBuffer)
{
    m_microCDR->m_microBuffer = m_microBuffer;
    m_microCDR->m_iterator = 0;
    int32_t local_i = 1;
    char* local_c = (char*) &local_i;
    char endia = (*local_c);
    if (endia == '1')
    {
        m_microCDR->m_endianness = LITTLE_ENDIANNESS;
    }
    else
    {
        m_microCDR->m_endianness = BIG_ENDIANNESS;
    }
    m_microCDR->m_swapBytes = NCDR_FALSE;
    m_microCDR->m_currentPosition = m_microBuffer->m_buffer;
    m_microCDR->m_alignPosition = m_microBuffer->m_buffer;
    m_microCDR->m_buffer = m_microBuffer->m_buffer;
    m_microCDR->m_lastDataSize = 0;
}

void resetStaticMicroCDRForSerialize(struct microCDR* m_microCDR)
{
    m_microCDR->m_iterator = 0;
    m_microCDR->m_currentPosition = m_microCDR->m_buffer;
    m_microCDR->m_alignPosition = m_microCDR->m_buffer;
    m_microCDR->m_lastDataSize = 0;
    m_microCDR->m_microBuffer->m_serializedBuffer = 0;
}

void resetStaticMicroCDRForDeserialize(struct microCDR* m_microCDR)
{
    m_microCDR->m_iterator = 0;
    m_microCDR->m_currentPosition = m_microCDR->m_buffer;
    m_microCDR->m_alignPosition = m_microCDR->m_buffer;
    m_microCDR->m_lastDataSize = 0;
    m_microCDR->m_microBuffer->m_serializedBuffer = m_microCDR->m_microBuffer->m_bufferSize;
}

void newMicroCDR(struct microCDR** m_cdrBuffer, struct microBuffer* m_microBuffer)
{
    *m_cdrBuffer = malloc(sizeof(microCDR));
    initMicroCDR(*m_cdrBuffer, m_microBuffer);
}

void initDeserializedAlignedBuffer(char* buffer, uint32_t bufferSize, struct microBuffer* m_microBuffer)
{
    m_microBuffer->m_bufferSize = bufferSize;
    m_microBuffer->m_internalBuffer = '0';
    m_microBuffer->m_serializedBuffer = bufferSize;
    m_microBuffer->m_buffer = buffer;
    m_microBuffer->m_alingData = NCDR_TRUE;
}

void newDeserializedAlignedBuffer(char* buffer, uint32_t bufferSize, struct microBuffer** m_microBuffer)
{
    *m_microBuffer = malloc(sizeof(microBuffer));
    initDeserializedAlignedBuffer(buffer, bufferSize, *m_microBuffer);
}

void initDeserializedNonAlignedBuffer(char* buffer, uint32_t bufferSize, struct microBuffer* m_microBuffer)
{
    m_microBuffer->m_bufferSize = bufferSize;
    m_microBuffer->m_internalBuffer = '0';
    m_microBuffer->m_serializedBuffer = bufferSize;
    m_microBuffer->m_buffer = buffer;
    m_microBuffer->m_alingData = NCDR_FALSE;
}

void newDeserializedNonAlignedBuffer(char* buffer, uint32_t bufferSize, struct microBuffer** m_microBuffer)
{
    *m_microBuffer = malloc(sizeof(microBuffer));
    initDeserializedNonAlignedBuffer(buffer, bufferSize, *m_microBuffer);
}

void newDynamicAlignedBuffer(struct microBuffer** m_microBuffer)
{
    *m_microBuffer = malloc(sizeof(microBuffer));
    (*m_microBuffer)->m_buffer = malloc(MICROCDR_INIT_BUF_LENGTH);
    (*m_microBuffer)->m_bufferSize = MICROCDR_INIT_BUF_LENGTH;
    (*m_microBuffer)->m_internalBuffer = '1';
    (*m_microBuffer)->m_serializedBuffer = 0;
    (*m_microBuffer)->m_alingData = NCDR_TRUE;
}

void initStaticAlignedBuffer(char* buffer, uint32_t bufferSize, struct microBuffer* m_microBuffer)
{
    m_microBuffer->m_bufferSize = bufferSize;
    m_microBuffer->m_internalBuffer = '0';
    m_microBuffer->m_serializedBuffer = 0;
    m_microBuffer->m_buffer = buffer;
    m_microBuffer->m_alingData = NCDR_TRUE;
}

void newStaticAlignedBuffer(char* buffer, uint32_t bufferSize, struct microBuffer** m_microBuffer)
{
    *m_microBuffer = malloc(sizeof(microBuffer));
    initStaticAlignedBuffer(buffer, bufferSize, *m_microBuffer);
}

void newDynamicNonAlignedBuffer(struct microBuffer** m_microBuffer)
{
    *m_microBuffer = malloc(sizeof(microBuffer));
    (*m_microBuffer)->m_buffer = malloc(MICROCDR_INIT_BUF_LENGTH);
    (*m_microBuffer)->m_bufferSize = MICROCDR_INIT_BUF_LENGTH;
    (*m_microBuffer)->m_internalBuffer = '1';
    (*m_microBuffer)->m_serializedBuffer = 0;
    (*m_microBuffer)->m_alingData = NCDR_FALSE;
}

void initStaticNonAlignedBuffer(char* buffer, uint32_t bufferSize, struct microBuffer* m_microBuffer)
{
    m_microBuffer->m_bufferSize = bufferSize;
    m_microBuffer->m_internalBuffer = '0';
    m_microBuffer->m_serializedBuffer = 0;
    m_microBuffer->m_buffer = buffer;
    m_microBuffer->m_alingData = NCDR_FALSE;
}

void newStaticNonAlignedBuffer(char* buffer, uint32_t bufferSize, struct microBuffer** m_microBuffer)
{
    *m_microBuffer = malloc(sizeof(microBuffer));
    initStaticNonAlignedBuffer(buffer, bufferSize, *m_microBuffer);
}

void destroyBuffer(struct microBuffer* m_cdrBuffer)
{
    if (m_cdrBuffer->m_internalBuffer == '1')
    {
        free(m_cdrBuffer->m_buffer);
    }
    free(m_cdrBuffer);
}

void mallocCdr(void** point_t, uint32_t size)
{
    *point_t = malloc(size);
}

void freeCdr(void** point_t)
{
    free(*point_t);
}

void resetAlignment(struct microCDR* m_cdrBuffer)
{
    m_cdrBuffer->m_alignPosition = m_cdrBuffer->m_currentPosition;
}

uint32_t alignment(uint32_t dataSize, struct microCDR* m_cdrBuffer)
{
    uint8_t alingData = m_cdrBuffer->m_microBuffer->m_alingData;
    if (alingData == NCDR_TRUE)
    {
        return dataSize > m_cdrBuffer->m_lastDataSize ?
               (dataSize - ((m_cdrBuffer->m_currentPosition - m_cdrBuffer->m_alignPosition) % dataSize)) & (dataSize - 1) :
               0;
    }
    else
    {
        return 0;
    }
}

void makeAlign(uint32_t align, struct microCDR* m_cdrBuffer)
{
    if (m_cdrBuffer->m_microBuffer->m_alingData == NCDR_TRUE)
    {
        m_cdrBuffer->m_currentPosition += align;
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += align;
        m_cdrBuffer->m_iterator += align;
    }
}

uint32_t getSerializedDataLength(struct microCDR* m_cdrBuffer)
{
    return m_cdrBuffer->m_microBuffer->m_serializedBuffer;
}

char* getBufferPointer(struct microCDR* m_cdrBuffer)
{
    return m_cdrBuffer->m_microBuffer->m_buffer;
}

char* getCurrentPosition(struct microCDR* m_cdrBuffer)
{
    return m_cdrBuffer->m_currentPosition;
}

void changeEndianness(Endianness endianness, struct microCDR* m_cdrBuffer)
{
    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
        m_cdrBuffer->m_endianness = endianness;
    }
}

void updateCurrentPosition(struct microCDR* m_cdrBuffer)
{
    if (m_cdrBuffer->m_buffer != m_cdrBuffer->m_microBuffer->m_buffer)
    {
        m_cdrBuffer->m_currentPosition = m_cdrBuffer->m_microBuffer->m_buffer;
        m_cdrBuffer->m_buffer = m_cdrBuffer->m_microBuffer->m_buffer;
        m_cdrBuffer->m_currentPosition += m_cdrBuffer->m_iterator;
    }
}

int8_t resize(uint32_t minSizeInc, struct microCDR* m_cdrBuffer)
{
    if (m_cdrBuffer->m_microBuffer->m_internalBuffer == '1')
    {
        if (m_cdrBuffer->m_microBuffer->m_bufferSize == 0)
        {
            m_cdrBuffer->m_microBuffer->m_bufferSize = MICROCDR_INIT_BUF_LENGTH;
            m_cdrBuffer->m_microBuffer->m_buffer = (char*) malloc(m_cdrBuffer->m_microBuffer->m_bufferSize);
            m_cdrBuffer->m_currentPosition = m_cdrBuffer->m_microBuffer->m_buffer;
            m_cdrBuffer->m_alignPosition = m_cdrBuffer->m_microBuffer->m_buffer;
            m_cdrBuffer->m_currentPosition += m_cdrBuffer->m_microBuffer->m_serializedBuffer;
            return 0;
        }
        else
        {
            uint32_t freeSpace = (uint32_t)(m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
            if (freeSpace < minSizeInc)
            {
                //int32_t sizeInc = minSizeInc - freeSpace;
                if (minSizeInc < MICROCDR_INIT_BUF_LENGTH)
                {
                    m_cdrBuffer->m_microBuffer->m_bufferSize += MICROCDR_INIT_BUF_LENGTH;
                    m_cdrBuffer->m_microBuffer->m_buffer = (char*) realloc(m_cdrBuffer->m_microBuffer->m_buffer, m_cdrBuffer->m_microBuffer->m_bufferSize);
                    m_cdrBuffer->m_currentPosition = m_cdrBuffer->m_microBuffer->m_buffer;
                    m_cdrBuffer->m_alignPosition = m_cdrBuffer->m_microBuffer->m_buffer;
                    m_cdrBuffer->m_currentPosition += m_cdrBuffer->m_microBuffer->m_serializedBuffer;
                }
                else
                {
                    m_cdrBuffer->m_microBuffer->m_bufferSize += minSizeInc;
                    m_cdrBuffer->m_microBuffer->m_buffer = (char*) realloc(m_cdrBuffer->m_microBuffer->m_buffer, m_cdrBuffer->m_microBuffer->m_bufferSize);
                    m_cdrBuffer->m_currentPosition = m_cdrBuffer->m_microBuffer->m_buffer;
                    m_cdrBuffer->m_alignPosition = m_cdrBuffer->m_microBuffer->m_buffer;
                    m_cdrBuffer->m_currentPosition += m_cdrBuffer->m_microBuffer->m_serializedBuffer;
                }

                return 0;
            }
        }
    }
    return -1;
}

void reset(struct microCDR* m_cdrBuffer)
{
    m_cdrBuffer->m_microBuffer->m_serializedBuffer = 0;
    m_cdrBuffer->m_currentPosition = m_cdrBuffer->m_microBuffer->m_buffer;
    m_cdrBuffer->m_alignPosition = m_cdrBuffer->m_microBuffer->m_buffer;
}

int8_t jump(uint16_t bytes, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    if (freeSpace > bytes || resize(bytes, m_cdrBuffer) == 0)
    {
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += bytes;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t serializeChar(const char char_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    size_t align = 0;
    align = alignment(sizeof(char), m_cdrBuffer);
    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t needed = sizeof(char) + align;

    if ((resize(needed, m_cdrBuffer) == 0) || free >= needed)
    {
        // Save last datasize.
        m_cdrBuffer->m_lastDataSize = sizeof(char_t);
        // Align.
        makeAlign(align, m_cdrBuffer);

        memcpy(m_cdrBuffer->m_currentPosition, (char*) &char_t, sizeof(char));
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeof(char);
        m_cdrBuffer->m_currentPosition += sizeof(char);

    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeUnsignedChar(const unsigned char uchar_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    size_t align = 0;
    align = alignment(sizeof(char), m_cdrBuffer);
    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t needed = sizeof(char) + align;

    if ((resize(needed, m_cdrBuffer) == 0) || free >= needed)
    {
        // Save last datasize.
        m_cdrBuffer->m_lastDataSize = sizeof(uchar_t);
        // Align.
        makeAlign(align, m_cdrBuffer);

        memcpy(m_cdrBuffer->m_currentPosition, (char*) &uchar_t, sizeof(char));
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeof(char);
        m_cdrBuffer->m_currentPosition += sizeof(char);
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeSignedChar(const signed char schar_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    size_t align = 0;
    align = alignment(sizeof(char), m_cdrBuffer);
    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t needed = sizeof(char) + align;

    if ((resize(needed, m_cdrBuffer) == 0) || free >= needed)
    {
        // Save last datasize.
        m_cdrBuffer->m_lastDataSize = sizeof(schar_t);
        // Align.
        makeAlign(align, m_cdrBuffer);

        memcpy(m_cdrBuffer->m_currentPosition, (char*) &schar_t, sizeof(char));
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeof(char);
        m_cdrBuffer->m_currentPosition += sizeof(char);
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeBool(const bool bool_t, struct microCDR* m_cdrBuffer)
{
    char value = 0;
    int8_t result = 0;
    size_t align = 0;
    align = alignment(sizeof(char), m_cdrBuffer);
    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t needed = sizeof(char) + align;

    if ((resize(needed, m_cdrBuffer) == 0) || free >= needed)
    {
        // Save last datasize.
        m_cdrBuffer->m_lastDataSize = sizeof(char);
        // Align.
        makeAlign(align, m_cdrBuffer);

        if (bool_t)
        {
            value = 1;
        }
        memcpy(m_cdrBuffer->m_currentPosition, (char*) &value, sizeof(char));
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeof(char);
        m_cdrBuffer->m_currentPosition += sizeof(char);

    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeString(const char* string_t, const uint32_t length, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t needed = sizeof(length) + length + 1;
    size_t align = 0;
    align = alignment(sizeof(length), m_cdrBuffer);

    if ((resize(needed + align, m_cdrBuffer) == 0) || free >= (needed + align))
    {
        result = serializeUnsignedInt(length + 1, m_cdrBuffer);
        if (result < 0)
        {
            return result;
        }
        memcpy(m_cdrBuffer->m_currentPosition, string_t, length + 1);
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += (length + 1);
        m_cdrBuffer->m_currentPosition += (length + 1);
        m_cdrBuffer->m_lastDataSize = sizeof(uint8_t);
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeStringEndianness(const char* string_t, const uint32_t length, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t needed = sizeof(length) + length + 1;

    if ((resize(needed, m_cdrBuffer) == 0) || free >= needed)
    {
        result = serializeUnsignedIntEndianness(length + 1, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return result;
        }
        memcpy(m_cdrBuffer->m_currentPosition, string_t, length + 1);
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += (length + 1);
        m_cdrBuffer->m_currentPosition += (length + 1);
        m_cdrBuffer->m_lastDataSize = sizeof(uint8_t);
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t deserializeChar(char* char_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    size_t align = 0;
    align = alignment(sizeof(char), m_cdrBuffer);
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    if ((unread - align) >= 1)
    {
        makeAlign(align, m_cdrBuffer);
        memcpy(char_t, m_cdrBuffer->m_currentPosition, 1);
        m_cdrBuffer->m_iterator += 1;
        m_cdrBuffer->m_currentPosition += 1;
        m_cdrBuffer->m_lastDataSize = sizeof(uint8_t);

    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t deserializeUnsignedChar(unsigned char* uchar_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    size_t align = 0;
    align = alignment(sizeof(char), m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    if ((unread - align) >= 1)
    {
        makeAlign(align, m_cdrBuffer);
        memcpy(uchar_t, m_cdrBuffer->m_currentPosition, 1);
        m_cdrBuffer->m_currentPosition += 1;
        m_cdrBuffer->m_iterator += 1;
        m_cdrBuffer->m_lastDataSize = sizeof(uint8_t);
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t deserializeSignedChar(signed char* schar_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    size_t align = 0;
    align = alignment(sizeof(char), m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    if ((unread - align) >= 1)
    {
        makeAlign(align, m_cdrBuffer);
        memcpy(schar_t, m_cdrBuffer->m_currentPosition, 1);
        m_cdrBuffer->m_iterator += 1;
        m_cdrBuffer->m_currentPosition += 1;
        m_cdrBuffer->m_lastDataSize = sizeof(uint8_t);
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t deserializeBool(bool* bool_t, struct microCDR* m_cdrBuffer)
{
    char value = 0;
    int8_t result = 0;
    size_t align = 0;
    align = alignment(sizeof(char), m_cdrBuffer);
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    if ((unread - align) >= 1)
    {
        makeAlign(align, m_cdrBuffer);
        memcpy(&value, m_cdrBuffer->m_currentPosition, 1);
        m_cdrBuffer->m_iterator += 1;
        m_cdrBuffer->m_currentPosition += 1;
        m_cdrBuffer->m_lastDataSize = sizeof(char);

        if (0 == value)
        {
            *bool_t = false;
        }
        else if (1 == value)
        {
            *bool_t = true;
        }
        else
        {
            result = -1;
        }
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t deserializeString(char** string, uint32_t* strlen, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    size_t align = 0;
    align = alignment(sizeof(int32_t), m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeInt = sizeof(int32_t);

    if ((unread - align) >= sizeInt)
    {
        result = deserializeUnsignedInt(strlen, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

        if (unread >= *strlen)
        {
            *string = malloc(*strlen);
            memcpy(*string, m_cdrBuffer->m_currentPosition, *strlen);
            m_cdrBuffer->m_currentPosition += *strlen;
            m_cdrBuffer->m_iterator += *strlen;
            *strlen -= 1;
            m_cdrBuffer->m_lastDataSize = sizeof(uint8_t);
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeStringEndianness(char** string, uint32_t* strlen, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    size_t align = 0;
    align = alignment(sizeof(int32_t), m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeInt = sizeof(int32_t);

    if ((unread - align) >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(strlen, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }

        unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

        if (unread >= *strlen)
        {

            *string = malloc(*strlen);
            memcpy(*string, m_cdrBuffer->m_currentPosition, *strlen);
            m_cdrBuffer->m_currentPosition += *strlen;
            m_cdrBuffer->m_iterator += *strlen;
            *strlen -= 1;

            m_cdrBuffer->m_lastDataSize = sizeof(uint8_t);
        }
        else
        {
            return -1;
        }
    }
    return result;
}

int8_t serializeShort(const int16_t short_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(int16_t);

    size_t align = 0;
    align = alignment(sizeShort, m_cdrBuffer);

    if ((resize(sizeShort + align, m_cdrBuffer) == 0) || free >= (sizeShort + align))
    {
        // Save last datasize.
        m_cdrBuffer->m_lastDataSize = sizeShort;
        // Align.
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* short_c = (char*) &short_t;
            m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer] = short_c[1];
            m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + 1] = short_c[0];
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &short_t, sizeShort);
        }

        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeShort;
        m_cdrBuffer->m_currentPosition += sizeShort;
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeShortEndianness(const int16_t short_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeShort(short_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeShort(short_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedShort(const uint16_t ushort_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(uint16_t);
    uint16_t i = 0;

    size_t align = 0;
    align = alignment(sizeShort, m_cdrBuffer);

    if ((resize(sizeShort + align, m_cdrBuffer) == 0) || free >= (sizeShort + align))
    {
        // Save last datasize.
        m_cdrBuffer->m_lastDataSize = sizeShort;
        // Align.
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* short_c = (char*) &ushort_t;
            for (i = 0; i < sizeShort; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] =
                        short_c[sizeShort - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &ushort_t, sizeShort);
        }
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeShort;
        m_cdrBuffer->m_currentPosition += sizeShort;
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeUnsignedShortEndianness(const uint16_t ushort_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeUnsignedShort(ushort_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeUnsignedShort(ushort_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeInt(const int32_t int_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(int32_t);
    uint16_t i = 0;

    size_t align = 0;
    align = alignment(sizeInt, m_cdrBuffer);

    if ((resize(sizeInt + align, m_cdrBuffer) == 0) || free >= (sizeInt + align))
    {
        m_cdrBuffer->m_lastDataSize = sizeInt;
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* int_c = (char*) &int_t;
            for (i = 0; i < sizeInt; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] = int_c[sizeInt
                        - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &int_t, sizeInt);
        }

        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeInt;
        m_cdrBuffer->m_currentPosition += sizeInt;
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeIntEndianness(const int32_t int_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeInt(int_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeInt(int_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedInt(const uint32_t uint_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(uint32_t);
    uint16_t i = 0;

    uint32_t align = alignment(sizeInt, m_cdrBuffer);

    if ((resize(sizeInt + align, m_cdrBuffer) == 0) || free >= (sizeInt + align))
    {
        m_cdrBuffer->m_lastDataSize = sizeInt;
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* int_c = (char*) &uint_t;
            for (i = 0; i < sizeInt; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] = int_c[sizeInt
                        - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &uint_t, sizeInt);
        }

        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeInt;
        m_cdrBuffer->m_currentPosition += sizeInt;
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeUnsignedIntEndianness(const uint32_t uint_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeUnsignedInt(uint_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeUnsignedInt(uint_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLong(const int64_t long_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(int64_t);
    uint16_t i = 0;

    uint32_t align = alignment(sizeLong, m_cdrBuffer);

    if ((resize(sizeLong + align, m_cdrBuffer) == 0) || free >= (sizeLong + align))
    {

        m_cdrBuffer->m_lastDataSize = sizeLong;

        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* long_c = (char*) &long_t;
            for (i = 0; i < sizeLong; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] =
                        long_c[sizeLong - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &long_t, sizeLong);
        }
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeLong;
        m_cdrBuffer->m_currentPosition += sizeLong;

    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t serializeLongEndianness(const int64_t long_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeLong(long_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeLong(long_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedLong(const uint64_t ulong_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(int64_t);
    uint16_t i = 0;

    uint32_t align = alignment(sizeLong, m_cdrBuffer);

    if ((resize(sizeLong + align, m_cdrBuffer) == 0) || free >= (sizeLong + align))
    {
        m_cdrBuffer->m_lastDataSize = sizeLong;
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* long_c = (char*) &ulong_t;
            for (i = 0; i < sizeLong; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] =
                        long_c[sizeLong - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &ulong_t, sizeLong);
        }
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeLong;
        m_cdrBuffer->m_currentPosition += sizeLong;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t serializeUnsignedLongEndianness(const uint64_t ulong_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeUnsignedLong(ulong_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeUnsignedLong(ulong_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLongLong(const long long longlong_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(long long);
    uint16_t i = 0;

    uint32_t align = alignment(sizeLong, m_cdrBuffer);

    if ((resize(sizeLong + align, m_cdrBuffer) == 0) || free >= (sizeLong + align))
    {

        m_cdrBuffer->m_lastDataSize = sizeLong;
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* long_c = (char*) &longlong_t;
            for (i = 0; i < sizeLong; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] =
                        long_c[sizeLong - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &longlong_t, sizeLong);
        }
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeLong;
        m_cdrBuffer->m_currentPosition += sizeLong;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t serializeLongLongEndianness(const long long longlong_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeLongLong(longlong_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeLongLong(longlong_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedLongLong(const unsigned long long ulonglong_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(unsigned long long);
    uint16_t i = 0;

    uint32_t align = alignment(sizeLong, m_cdrBuffer);

    if ((resize(sizeLong + align, m_cdrBuffer) == 0) || free >= (sizeLong + align))
    {
        m_cdrBuffer->m_lastDataSize = sizeLong;
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* long_c = (char*) &ulonglong_t;
            for (i = 0; i < sizeLong; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] =
                        long_c[sizeLong - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &ulonglong_t, sizeLong);
        }
        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeLong;
        m_cdrBuffer->m_currentPosition += sizeLong;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t serializeUnsignedLongLongEndianness(const unsigned long long ulonglong_t, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeUnsignedLongLong(ulonglong_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeUnsignedLongLong(ulonglong_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeFloat(const float float_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeFloat = sizeof(float);
    uint16_t i = 0;

    uint32_t align = alignment(sizeFloat, m_cdrBuffer);

    if ((resize(sizeFloat + align, m_cdrBuffer) == 0) || free >= (sizeFloat + align))
    {
        m_cdrBuffer->m_lastDataSize = sizeFloat;
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* float_c = (char*) &float_t;

            for (i = 0; i < sizeFloat; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] =
                        float_c[sizeFloat - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &float_t, sizeFloat);
        }

        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeFloat;
        m_cdrBuffer->m_currentPosition += sizeFloat;
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t serializeFloatEndianness(const float float_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeFloat(float_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeFloat(float_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeDouble(const double m_double_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(double);
    uint16_t i = 0;

    uint32_t align = alignment(sizeDouble, m_cdrBuffer);

    if ((resize(sizeDouble + align, m_cdrBuffer) == 0) || free >= (sizeDouble + align))
    {

        m_cdrBuffer->m_lastDataSize = sizeDouble;
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* double_c = (char*) &m_double_t;
            for (i = 0; i < sizeDouble; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] =
                        double_c[sizeDouble - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &m_double_t, sizeDouble);
        }

        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeDouble;
        m_cdrBuffer->m_currentPosition += sizeDouble;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t serializeDoubleEndianness(const double m_double_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeDouble(m_double_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeDouble(m_double_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLongDouble(const long double longdouble_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    uint32_t free = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(long double);
    uint16_t i = 0;

    uint32_t align = alignment(sizeDouble, m_cdrBuffer);

    if ((resize(sizeDouble + align, m_cdrBuffer) == 0) || free >= (sizeDouble + align))
    {
        m_cdrBuffer->m_lastDataSize = sizeDouble;
        makeAlign(align, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            char* double_c = (char*) &longdouble_t;
            for (i = 0; i < sizeDouble; i++)
            {
                m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_microBuffer->m_serializedBuffer + i] =
                        double_c[sizeDouble - i - 1];
            }
        }
        else
        {
            memcpy(m_cdrBuffer->m_currentPosition, (char*) &longdouble_t, sizeDouble);
        }

        m_cdrBuffer->m_microBuffer->m_serializedBuffer += sizeDouble;
        m_cdrBuffer->m_currentPosition += sizeDouble;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t serializeLongDoubleEndianness(const long double longdouble_t, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeLongDouble(longdouble_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeLongDouble(longdouble_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeShort(int16_t* short_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeShort = sizeof(int16_t);
    uint32_t align = alignment(sizeShort, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeShort)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(short_t, m_cdrBuffer->m_currentPosition, sizeShort);
        }
        else
        {
            char* short_c = (char*) short_t;
            for (i = 0; i < sizeShort; i++)
            {
                short_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeShort - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeShort;
        m_cdrBuffer->m_currentPosition += sizeShort;
        m_cdrBuffer->m_lastDataSize = sizeShort;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeShortEndianness(int16_t* short_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeShort(short_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeShort(short_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeUnsignedShort(uint16_t* ushort_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeShort = sizeof(uint16_t);
    uint32_t align = alignment(sizeShort, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeShort)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(ushort_t, m_cdrBuffer->m_currentPosition, sizeShort);
        }
        else
        {
            char* short_c = (char*) ushort_t;
            for (i = 0; i < sizeShort; i++)
            {
                short_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeShort - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeShort;
        m_cdrBuffer->m_currentPosition += sizeShort;
        m_cdrBuffer->m_lastDataSize = sizeShort;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeUnsignedShortEndianness(uint16_t* ushort_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeUnsignedShort(ushort_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeUnsignedShort(ushort_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeInt(int32_t* int_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeInt = sizeof(int32_t);
    uint32_t align = alignment(sizeInt, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeInt)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(int_t, m_cdrBuffer->m_currentPosition, sizeInt);
        }
        else
        {
            char* int_c = (char*) int_t;
            for (i = 0; i < sizeInt; i++)
            {
                int_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeInt - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeInt;
        m_cdrBuffer->m_currentPosition += sizeInt;
        m_cdrBuffer->m_lastDataSize = sizeInt;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeIntEndianness(int32_t* int_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeInt(int_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeInt(int_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeUnsignedInt(uint32_t* int_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeInt = sizeof(uint32_t);
    uint32_t align = alignment(sizeInt, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeInt)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(int_t, m_cdrBuffer->m_currentPosition, sizeInt);
        }
        else
        {
            char* int_c = (char*) int_t;
            for (i = 0; i < sizeInt; i++)
            {
                int_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeInt - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeInt;
        m_cdrBuffer->m_currentPosition += sizeInt;
        m_cdrBuffer->m_lastDataSize = sizeInt;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeUnsignedIntEndianness(uint32_t* uint_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeUnsignedInt(uint_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeUnsignedInt(uint_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeLong(int64_t* long_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeLong = sizeof(int64_t);
    uint32_t align = alignment(sizeLong, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeLong)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(long_t, m_cdrBuffer->m_currentPosition, sizeLong);
        }
        else
        {
            char* long_c = (char*) long_t;
            for (i = 0; i < sizeLong; i++)
            {
                long_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeLong - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeLong;
        m_cdrBuffer->m_currentPosition += sizeLong;
        m_cdrBuffer->m_lastDataSize = sizeLong;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeLongEndianness(int64_t* long_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeLong(long_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeLong(long_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeUnsignedLong(uint64_t* ulong_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeLong = sizeof(uint64_t);
    uint32_t align = alignment(sizeLong, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeLong)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(ulong_t, m_cdrBuffer->m_currentPosition, sizeLong);
        }
        else
        {
            char* long_c = (char*) ulong_t;
            for (i = 0; i < sizeLong; i++)
            {
                long_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeLong - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeLong;
        m_cdrBuffer->m_currentPosition += sizeLong;
        m_cdrBuffer->m_lastDataSize = sizeLong;
    }
    else
    {
        result = -1;
    }

    return result;
}

int8_t deserializeUnsignedLongEndianness(uint64_t* ulong_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeUnsignedLong(ulong_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeUnsignedLong(ulong_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeLongLong(long long* longlong_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeLong = sizeof(long long);
    uint32_t align = alignment(sizeLong, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeLong)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(longlong_t, m_cdrBuffer->m_currentPosition, sizeLong);
        }
        else
        {
            char* long_c = (char*) longlong_t;
            for (i = 0; i < sizeLong; i++)
            {
                long_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeLong - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeLong;
        m_cdrBuffer->m_currentPosition += sizeLong;
        m_cdrBuffer->m_lastDataSize = sizeLong;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeLongLongEndianness(long long* longlong_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeLongLong(longlong_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeLongLong(longlong_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeUnsignedLongLong(unsigned long long* long_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeLong = sizeof(unsigned long long);
    uint32_t align = alignment(sizeLong, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeLong)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(long_t, m_cdrBuffer->m_currentPosition, sizeLong);
        }
        else
        {
            char* long_c = (char*) long_t;
            for (i = 0; i < sizeLong; i++)
            {
                long_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeLong - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeLong;
        m_cdrBuffer->m_currentPosition += sizeLong;
        m_cdrBuffer->m_lastDataSize = sizeLong;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeUnsignedLongLongEndianness(unsigned long long* ulonglong_t, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeUnsignedLongLong(ulonglong_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeUnsignedLongLong(ulonglong_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeFloat(float* float_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeFloat = sizeof(float);
    uint32_t align = alignment(sizeFloat, m_cdrBuffer);
    uint32_t i;

    if ((unread - align) >= sizeFloat)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(float_t, m_cdrBuffer->m_currentPosition, sizeFloat);
        }
        else
        {
            char* float_c = (char*) float_t;
            for (i = 0; i < sizeFloat; i++)
            {
                float_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeFloat - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeFloat;
        m_cdrBuffer->m_currentPosition += sizeFloat;
        m_cdrBuffer->m_lastDataSize = sizeFloat;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeFloatEndianness(float* float_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeFloat(float_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeFloat(float_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeDouble(double* m_double_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeDouble = sizeof(double);
    uint32_t align = alignment(sizeDouble, m_cdrBuffer);
    uint16_t i;

    if ((unread - align) >= sizeDouble)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(m_double_t, m_cdrBuffer->m_currentPosition, sizeDouble);
        }
        else
        {
            char* double_c = (char*) m_double_t;
            for (i = 0; i < sizeDouble; i++)
            {
                double_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeDouble - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeDouble;
        m_cdrBuffer->m_currentPosition += sizeDouble;
        m_cdrBuffer->m_lastDataSize = sizeDouble;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeDoubleEndianness(double* m_double_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeDouble(m_double_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeDouble(m_double_t, m_cdrBuffer);
    }
    return result;
}

int8_t deserializeLongDouble(long double* longdouble_t, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint16_t sizeDouble = sizeof(long double);
    uint32_t align = alignment(sizeDouble, m_cdrBuffer);
    uint16_t i;

    if ((unread - align) >= sizeDouble)
    {
        makeAlign(align, m_cdrBuffer);
        if (m_cdrBuffer->m_swapBytes == NCDR_FALSE)
        {
            memcpy(longdouble_t, m_cdrBuffer->m_currentPosition, sizeDouble);
        }
        else
        {
            char* double_c = (char*) longdouble_t;
            for (i = 0; i < sizeDouble; i++)
            {
                double_c[i] = m_cdrBuffer->m_microBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeDouble - 1 - i)];
            }
        }
        m_cdrBuffer->m_iterator += sizeDouble;
        m_cdrBuffer->m_currentPosition += sizeDouble;
        m_cdrBuffer->m_lastDataSize = sizeDouble;
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeLongDoubleEndianness(long double* longdouble_t, Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = deserializeLongDouble(longdouble_t, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = deserializeLongDouble(longdouble_t, m_cdrBuffer);
    }
    return result;
}

int8_t serializeStringSequence(const char** string_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = sizeof(uint32_t);

    uint32_t i = 0;
    for (i = 0; i < numElements; i++)
    {
        totalSpace += (uint32_t) strlen(string_t[i]);
        totalSpace += 1;
        totalSpace += sizeof(uint32_t);
    }

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeStringArray(string_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeStringSequenceEndianness(const char** string_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = sizeof(uint32_t);

    uint32_t i = 0;
    for (i = 0; i < numElements; i++)
    {
        totalSpace += (uint32_t) strlen(string_t[i]);
        totalSpace += 1;
        totalSpace += sizeof(uint32_t);
    }

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeStringArrayEndianness(string_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeStringArray(const char** string_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);

    uint32_t i = 0;
    uint32_t totalSpace = 0;
    for (i = 0; i < numElements; i++)
    {
        totalSpace += (uint32_t) strlen(string_t[i]);
        totalSpace += 1;
        totalSpace += sizeof(uint32_t);
    }

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeString(string_t[i], (uint32_t) strlen(string_t[i]), m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeStringArrayEndianness(const char** string_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);

    uint32_t i = 0;
    uint32_t totalSpace = 0;
    for (i = 0; i < numElements; i++)
    {
        totalSpace += (uint32_t) strlen(string_t[i]);
        totalSpace += 1;
        totalSpace += sizeof(uint32_t);
    }

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeStringEndianness(string_t[i], (uint32_t) strlen(string_t[i]), endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeCharSequence(const char* char_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = sizeof(uint32_t) + numElements;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeCharArray(char_t, numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    return result;
}

int8_t serializeCharSequenceEndianness(const char* char_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = sizeof(uint32_t) + numElements;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeCharArray(char_t, numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    return result;
}

int8_t serializeCharArray(const char* char_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = numElements;
    uint32_t i = 0;
    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeChar(char_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
            m_cdrBuffer->m_lastDataSize = sizeof(char);
        }
    }
    return result;
}

int8_t serializeUnsignedCharSequence(const unsigned char* uchar_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = sizeof(uint32_t) + numElements;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedCharArray(uchar_t, numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(unsigned char);
    }
    return result;
}

int8_t serializeUnsignedCharSequenceEndianness(const unsigned char* uchar_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = sizeof(uint32_t) + numElements;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedCharArray(uchar_t, numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(unsigned char);
    }
    return result;
}

int8_t serializeUnsignedCharArray(const unsigned char* uchar_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = numElements;
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedChar(uchar_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
            m_cdrBuffer->m_lastDataSize = sizeof(unsigned char);
        }
    }
    return result;
}

int8_t serializeSignedCharSequence(const signed char* schar_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = sizeof(uint32_t) + numElements;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeSignedCharArray(schar_t, numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(signed char);
    }
    return result;
}

int8_t serializeSignedCharSequenceEndianness(const signed char* schar_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    if (endianness != m_cdrBuffer->m_endianness)
    {
        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }

        result = serializeSignedCharSequence(schar_t, numElements, m_cdrBuffer);

        if (m_cdrBuffer->m_swapBytes == NCDR_TRUE)
        {
            m_cdrBuffer->m_swapBytes = NCDR_FALSE;
        }
        else
        {
            m_cdrBuffer->m_swapBytes = NCDR_TRUE;
        }
    }
    else
    {
        result = serializeSignedCharSequence(schar_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeSignedCharArray(const signed char* schar_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = numElements;
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeSignedChar(schar_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
            m_cdrBuffer->m_lastDataSize = sizeof(signed char);
        }
    }
    return result;
}

int8_t serializeBoolArray(const bool* bool_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint32_t totalSpace = numElements;
    uint32_t i = 0;
    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeBool(bool_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
            m_cdrBuffer->m_lastDataSize = sizeof(char);
        }
    }
    return result;
}

int8_t serializeShortSequence(const int16_t* short_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(int16_t);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeShort);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeShortArray(short_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeShortSequenceEndianness(const int16_t* short_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(int16_t);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeShort);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeShortArrayEndianness(short_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeShortArray(const int16_t* short_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(int16_t);
    uint32_t totalSpace = (numElements * sizeShort);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeShort(short_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeShortArrayEndianness(const int16_t* short_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(int16_t);
    uint32_t totalSpace = (numElements * sizeShort);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeShortEndianness(short_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeUnsignedShortSequence(const uint16_t* ushort_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(uint16_t);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeShort);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedShortArray(ushort_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedShortSequenceEndianness(const uint16_t* ushort_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(uint16_t);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeShort);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedShortArrayEndianness(ushort_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedShortArray(const uint16_t* ushort_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(uint16_t);
    uint32_t totalSpace = (numElements * sizeShort);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedShort(ushort_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeUnsignedShortArrayEndianness(const uint16_t* ushort_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeShort = sizeof(uint16_t);
    uint32_t totalSpace = (numElements * sizeShort);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedShortEndianness(ushort_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeIntSequence(const int32_t* int_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(int32_t);
    uint32_t totalSpace = sizeInt + (numElements * sizeInt);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeIntArray(int_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeIntSequenceEndianness(const int32_t* int_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(int32_t);
    uint32_t totalSpace = sizeInt + (numElements * sizeInt);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeIntArrayEndianness(int_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeIntArray(const int32_t* int_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(int32_t);
    uint32_t totalSpace = (numElements * sizeInt);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeInt(int_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeIntArrayEndianness(const int32_t* int_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(int32_t);
    uint32_t totalSpace = (numElements * sizeInt);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeIntEndianness(int_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeUnsignedIntSequence(const uint32_t* uint_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(uint32_t);
    uint32_t totalSpace = sizeInt + (numElements * sizeInt);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedIntArray(uint_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedIntSequenceEndianness(const uint32_t* uint_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(uint32_t);
    uint32_t totalSpace = sizeInt + (numElements * sizeInt);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedIntArrayEndianness(uint_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedIntArray(const uint32_t* uint_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(uint32_t);
    uint32_t totalSpace = (numElements * sizeInt);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedInt(uint_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeUnsignedIntArrayEndianness(const uint32_t* uint_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeInt = sizeof(uint32_t);
    uint32_t totalSpace = (numElements * sizeInt);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedIntEndianness(uint_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeLongSequence(const int64_t* long_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(int64_t);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeLongArray(long_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLongSequenceEndianness(const int64_t* long_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(int64_t);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeLongArrayEndianness(long_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLongArray(const int64_t* long_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(int64_t);
    uint32_t totalSpace = (numElements * sizeLong);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeLong(long_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeLongArrayEndianness(const int64_t* long_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(int64_t);
    uint32_t totalSpace = (numElements * sizeLong);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeLongEndianness(long_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeUnsignedLongSequence(const uint64_t* ulong_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(uint64_t);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedLongArray(ulong_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedLongSequenceEndianness(const uint64_t* ulong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(uint64_t);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedLongArrayEndianness(ulong_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedLongArray(const uint64_t* ulong_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(uint64_t);
    uint32_t totalSpace = (numElements * sizeLong);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedLong(ulong_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeUnsignedLongArrayEndianness(const uint64_t* ulong_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(uint64_t);
    uint32_t totalSpace = (numElements * sizeLong);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedLongEndianness(ulong_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeLongLongSequence(const long long* longlong_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(long long);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeLongLongArray(longlong_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLongLongSequenceEndianness(const long long* longlong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(long long);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeLongLongArrayEndianness(longlong_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLongLongArray(const long long* longlong_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(long long);
    uint32_t totalSpace = (numElements * sizeLong);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeLongLong(longlong_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeLongLongArrayEndianness(const long long* longlong_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(long long);
    uint32_t totalSpace = (numElements * sizeLong);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeLongLongEndianness(longlong_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeUnsignedLongLongSequence(const unsigned long long* ulonglong_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(unsigned long long);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedLongLongArray(ulonglong_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedLongLongSequenceEndianness(const unsigned long long* ulonglong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(unsigned long long);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeUnsignedLongLongArrayEndianness(ulonglong_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeUnsignedLongLongArray(const unsigned long long* ulonglong_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(unsigned long long);
    uint32_t totalSpace = (numElements * sizeLong);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedLongLong(ulonglong_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeUnsignedLongLongArrayEndianness(const unsigned long long* ulonglong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeLong = sizeof(unsigned long long);
    uint32_t totalSpace = (numElements * sizeLong);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeUnsignedLongLongEndianness(ulonglong_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeFloatSequence(const float* float_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeFloat = sizeof(float);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeFloat);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeFloatArray(float_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeFloatSequenceEndianness(const float* float_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeFloat = sizeof(float);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeFloat);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeFloatArrayEndianness(float_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeFloatArray(const float* float_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeFloat = sizeof(float);
    uint32_t totalSpace = (numElements * sizeFloat);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeFloat(float_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeFloatArrayEndianness(const float* float_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeFloat = sizeof(float);
    uint32_t totalSpace = (numElements * sizeFloat);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeFloatEndianness(float_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeDoubleSequence(const double* m_double_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(double);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeDouble);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeDoubleArray(m_double_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeDoubleSequenceEndianness(const double* m_double_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(double);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeDouble);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeDoubleArrayEndianness(m_double_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeDoubleArray(const double* m_double_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(double);
    uint32_t totalSpace = (numElements * sizeDouble);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeDouble(m_double_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeDoubleArrayEndianness(const double* m_double_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(double);
    uint32_t totalSpace = (numElements * sizeDouble);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeDoubleEndianness(m_double_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeLongDoubleSequence(const long double* longdouble_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(long double);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeDouble);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeLongDoubleArray(longdouble_t, numElements, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLongDoubleSequenceEndianness(const long double* longdouble_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(long double);
    uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeDouble);

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        result = serializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = serializeLongDoubleArrayEndianness(longdouble_t, numElements, endianness, m_cdrBuffer);
    }
    return result;
}

int8_t serializeLongDoubleArray(const long double* longdouble_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(long double);
    uint32_t totalSpace = (numElements * sizeDouble);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeLongDouble(longdouble_t[i], m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

int8_t serializeLongDoubleArrayEndianness(const long double* longdouble_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    uint32_t freeSpace = (m_cdrBuffer->m_microBuffer->m_bufferSize - m_cdrBuffer->m_microBuffer->m_serializedBuffer);
    uint16_t sizeDouble = sizeof(long double);
    uint32_t totalSpace = (numElements * sizeDouble);
    uint32_t i = 0;

    if ((resize(totalSpace, m_cdrBuffer) == 0) || totalSpace <= freeSpace)
    {
        for (i = 0; i < numElements; i++)
        {
            result = serializeLongDoubleEndianness(longdouble_t[i], endianness, m_cdrBuffer);
            if (result < 0)
            {
                return -1;
            }
        }
    }
    return result;
}

//DESERIALIZE CHAR

int8_t deserializeStringSequence(char*** string_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    //uint32_t i;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        char** swap; // = malloc(*numElements * sizeof(char*));

        result = deserializeStringArray(&swap, *numElements, m_cdrBuffer);

        *string_t = malloc(*numElements * sizeof(char*));
        memcpy(*string_t, swap, (*numElements * sizeof(char*)));

        /*for(i = 0; i < *numElements;i++)
         {
         free(swap[i]);
         }*/

        free(swap);

        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeStringSequenceEndianness(char*** string_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    //uint32_t i;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        char** swap; // = malloc(*numElements * sizeof(char*));
        result = deserializeStringArrayEndianness(&swap, *numElements, endianness, m_cdrBuffer);

        *string_t = malloc(*numElements * sizeof(char*));
        memcpy(*string_t, swap, (*numElements * sizeof(char*)));

        /*for(i = 0; i < *numElements;i++)
         {
         free(swap[i]);
         }*/

        free(swap);
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeStringArray(char*** string_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    char** swap = malloc(numElements * sizeof(char*));
    *string_t = malloc(numElements * sizeof(char*));

    uint32_t i = 0;
    uint32_t length = 0;
    for (i = 0; i < numElements; i++)
    {
        result = deserializeString(&swap[i], &length, m_cdrBuffer);
        if (result < 0)
        {
            free(swap);
            return -1;
        }
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    memcpy(*string_t, swap, (numElements * sizeof(char*)));

    /*for(i = 0; i < numElements;i++)
     {
     free(swap[i]);
     }*/

    free(swap);
    return result;
}

int8_t deserializeStringArrayEndianness(char*** string_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    char** swap = malloc(numElements * sizeof(char*));
    *string_t = malloc(numElements * sizeof(char*));

    uint32_t i = 0;
    uint32_t length = 0;
    for (i = 0; i < numElements; i++)
    {
        result = deserializeStringEndianness(&swap[i], &length, endianness, m_cdrBuffer);
        if (result < 0)
        {
            free(swap);
            return -1;
        }
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    memcpy(*string_t, swap, (numElements * sizeof(char*)));

    free(swap);
    return result;
}

int8_t deserializeCharSequence(char** char_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeCharArray(char_t, *numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeCharSequenceEndianness(char** char_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeCharArray(char_t, *numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeCharArray(char** char_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t totalSpace = numElements;
    if (unread >= totalSpace)
    {
        *char_t = malloc(totalSpace);
        memcpy(*char_t, m_cdrBuffer->m_currentPosition, totalSpace);
        m_cdrBuffer->m_iterator += totalSpace;
        m_cdrBuffer->m_currentPosition += totalSpace;
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedCharSequence(unsigned char** uchar_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedCharArray(uchar_t, *numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(unsigned char);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeUnsignedCharSequenceEndianness(unsigned char** uchar_t, uint32_t* numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedCharArray(uchar_t, *numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(unsigned char);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeUnsignedCharArray(unsigned char** uchar_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t totalSpace = numElements;
    if (unread >= totalSpace)
    {
        *uchar_t = malloc(totalSpace);
        memcpy(*uchar_t, m_cdrBuffer->m_currentPosition, totalSpace);
        m_cdrBuffer->m_iterator += totalSpace;
        m_cdrBuffer->m_currentPosition += totalSpace;
        m_cdrBuffer->m_lastDataSize = sizeof(unsigned char);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeSignedCharSequence(signed char** schar_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeSignedCharArray(schar_t, *numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(signed char);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeSignedCharSequenceEndianness(signed char** schar_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeSignedCharArray(schar_t, *numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(signed char);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeSignedCharArray(signed char** char_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t totalSpace = numElements;
    if (unread >= totalSpace)
    {
        *char_t = malloc(totalSpace);
        memcpy(*char_t, m_cdrBuffer->m_currentPosition, totalSpace);
        m_cdrBuffer->m_iterator += totalSpace;
        m_cdrBuffer->m_currentPosition += totalSpace;
        m_cdrBuffer->m_lastDataSize = sizeof(signed char);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeBoolArray(bool** bool_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeBool = sizeof(bool);
    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t totalSpace = numElements;
    uint32_t boolArraySpace = numElements * sizeBool;
    if (unread >= totalSpace)
    {
        *bool_t = malloc(boolArraySpace);
        bool* swap = malloc(boolArraySpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeBool(&swap[i], m_cdrBuffer);
        }
        memcpy(*bool_t, swap, boolArraySpace);
        free(swap);
        m_cdrBuffer->m_iterator += totalSpace;
        m_cdrBuffer->m_currentPosition += totalSpace;
        m_cdrBuffer->m_lastDataSize = sizeof(char);
    }
    else
    {
        return -1;
    }
    return result;
}

//DESERIALIZE SHORT

int8_t deserializeShortSequence(int16_t** short_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeShortArray(short_t, *numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(int16_t);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeShortSequenceEndianness(int16_t** short_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeShortArrayEndianness(short_t, *numElements, endianness, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(int16_t);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeShortArray(int16_t** short_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeShort = sizeof(int16_t);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t totalSpace = numElements * sizeShort;
    if (unread >= totalSpace)
    {
        *short_t = malloc(totalSpace);
        int16_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeShort(&swap[i], m_cdrBuffer);
        }
        memcpy(*short_t, swap, totalSpace);
        free(swap);
        m_cdrBuffer->m_lastDataSize = sizeof(int16_t);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeShortArrayEndianness(int16_t** short_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeShort = sizeof(int16_t);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t totalSpace = numElements * sizeShort;
    if (unread >= totalSpace)
    {
        *short_t = malloc(totalSpace);
        int16_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeShortEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*short_t, swap, totalSpace);
        free(swap);
        m_cdrBuffer->m_lastDataSize = sizeof(int16_t);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedShortSequence(uint16_t** ushort_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedShortArray(ushort_t, *numElements, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(uint16_t);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedShortSequenceEndianness(uint16_t** ushort_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedShortArrayEndianness(ushort_t, *numElements, endianness, m_cdrBuffer);
        m_cdrBuffer->m_lastDataSize = sizeof(uint16_t);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedShortArray(uint16_t** ushort_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeShort = sizeof(int16_t);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t totalSpace = numElements * sizeShort;
    if (unread >= totalSpace)
    {
        *ushort_t = malloc(totalSpace);
        uint16_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeUnsignedShort(&swap[i], m_cdrBuffer);
        }
        memcpy(*ushort_t, swap, totalSpace);
        free(swap);
        m_cdrBuffer->m_lastDataSize = sizeof(uint16_t);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedShortArrayEndianness(uint16_t** ushort_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeShort = sizeof(int16_t);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t totalSpace = numElements * sizeShort;
    if (unread >= totalSpace)
    {
        *ushort_t = malloc(totalSpace);
        uint16_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeUnsignedShortEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*ushort_t, swap, totalSpace);
        free(swap);
        m_cdrBuffer->m_lastDataSize = sizeof(uint16_t);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeIntSequence(int32_t** int_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeIntArray(int_t, *numElements, m_cdrBuffer);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeIntSequenceEndianness(int32_t** int_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeIntArrayEndianness(int_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeIntArray(int32_t** int_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeInt;
    if (unread >= totalSpace)
    {
        *int_t = malloc(totalSpace);
        int32_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeInt(&swap[i], m_cdrBuffer);
        }
        memcpy(*int_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeIntArrayEndianness(int32_t** int_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeInt;
    if (unread >= totalSpace)
    {
        *int_t = malloc(totalSpace);
        int32_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeIntEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*int_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedIntSequence(uint32_t** uint_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedIntArray(uint_t, *numElements, m_cdrBuffer);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeUnsignedIntSequenceEndianness(uint32_t** int_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedIntArrayEndianness(int_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        result = -1;
    }
    return result;
}

int8_t deserializeUnsignedIntArray(uint32_t** uint_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeInt;
    if (unread >= totalSpace)
    {
        *uint_t = malloc(totalSpace);
        uint32_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeUnsignedInt(&swap[i], m_cdrBuffer);
        }
        memcpy(*uint_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedIntArrayEndianness(uint32_t** uint_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;
    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);
    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeInt;
    if (unread >= totalSpace)
    {
        *uint_t = malloc(totalSpace);
        uint32_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeUnsignedIntEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*uint_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongSequence(int64_t** long_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeLongArray(long_t, *numElements, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongSequenceEndianness(int64_t** long_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeLongArrayEndianness(long_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongArray(int64_t** long_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeLong = sizeof(int64_t);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeLong;
    if (unread >= totalSpace)
    {
        *long_t = malloc(totalSpace);
        int64_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeLong(&swap[i], m_cdrBuffer);
        }
        memcpy(*long_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongArrayEndianness(int64_t** long_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeLong = sizeof(int64_t);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeLong;
    if (unread >= totalSpace)
    {
        *long_t = malloc(totalSpace);
        int64_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeLongEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*long_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedLongSequence(uint64_t** ulong_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedLongArray(ulong_t, *numElements, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedLongSequenceEndianness(uint64_t** ulong_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedLongArrayEndianness(ulong_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedLongArray(uint64_t** ulong_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeLong = sizeof(uint64_t);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeLong;
    if (unread >= totalSpace)
    {
        *ulong_t = malloc(totalSpace);
        uint64_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeUnsignedLong(&swap[i], m_cdrBuffer);
        }
        memcpy(*ulong_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedLongArrayEndianness(uint64_t** ulong_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeLong = sizeof(uint64_t);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeLong;
    if (unread >= totalSpace)
    {
        *ulong_t = malloc(totalSpace);
        uint64_t* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeUnsignedLongEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*ulong_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongLongSequence(long long** longlong_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeLongLongArray(longlong_t, *numElements, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongLongSequenceEndianness(long long** longlong_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeLongLongArrayEndianness(longlong_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongLongArray(long long** longlong_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);

    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeLong = sizeof(long long);

    uint32_t totalSpace = numElements * sizeLong;
    if (unread >= totalSpace)
    {
        *longlong_t = malloc(totalSpace);
        long long* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeLongLong(&swap[i], m_cdrBuffer);
        }
        memcpy(*longlong_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongLongArrayEndianness(long long** longlong_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeLong = sizeof(long long);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeLong;
    if (unread >= totalSpace)
    {
        *longlong_t = malloc(totalSpace);
        long long* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeLongLongEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*longlong_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedLongLongSequence(unsigned long long** ulonglong_t, uint32_t* numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedLongLongArray(ulonglong_t, *numElements, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedLongLongSequenceEndianness(unsigned long long** ulonglong_t, uint32_t* numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeUnsignedLongLongArrayEndianness(ulonglong_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedLongLongArray(unsigned long long** ulonglong_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeLong = sizeof(unsigned long long);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeLong;
    if (unread >= totalSpace)
    {
        *ulonglong_t = malloc(totalSpace);
        unsigned long long* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeUnsignedLongLong(&swap[i], m_cdrBuffer);
        }
        memcpy(*ulonglong_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeUnsignedLongLongArrayEndianness(unsigned long long** ulonglong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeLong = sizeof(unsigned long long);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeLong;
    if (unread >= totalSpace)
    {
        *ulonglong_t = malloc(totalSpace);
        unsigned long long* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeUnsignedLongLongEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*ulonglong_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeFloatSequence(float** float_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeFloatArray(float_t, *numElements, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeFloatSequenceEndianness(float** float_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeFloatArrayEndianness(float_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeFloatArray(float** float_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeFloat = sizeof(float);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeFloat;
    if (unread >= totalSpace)
    {
        *float_t = malloc(totalSpace);
        float* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeFloat(&swap[i], m_cdrBuffer);
        }
        memcpy(*float_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeFloatArrayEndianness(float** float_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeFloat = sizeof(float);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeFloat;
    if (unread >= totalSpace)
    {
        *float_t = malloc(totalSpace);
        float* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeFloatEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*float_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeDoubleSequence(double** m_double_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeDoubleArray(m_double_t, *numElements, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeDoubleSequenceEndianness(double** m_double_t, uint32_t* numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeDoubleArrayEndianness(m_double_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeDoubleArray(double** m_double_t, const uint32_t numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeDouble = sizeof(double);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeDouble;
    if (unread >= totalSpace)
    {
        *m_double_t = malloc(totalSpace);
        double* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeDouble(&swap[i], m_cdrBuffer);
        }
        memcpy(*m_double_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeDoubleArrayEndianness(double** m_double_t, const uint32_t numElements, Endianness endianness,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeDouble = sizeof(double);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeDouble;
    if (unread >= totalSpace)
    {
        *m_double_t = malloc(totalSpace);
        double* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeDoubleEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*m_double_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongDoubleSequence(long double** longdouble_t, uint32_t* numElements, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedInt(numElements, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeLongDoubleArray(longdouble_t, *numElements, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongDoubleSequenceEndianness(long double** longdouble_t, uint32_t* numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeInt = sizeof(uint32_t);

    if (unread >= sizeInt)
    {
        result = deserializeUnsignedIntEndianness(numElements, endianness, m_cdrBuffer);
        if (result < 0)
        {
            return -1;
        }
        result = deserializeLongDoubleArrayEndianness(longdouble_t, *numElements, endianness, m_cdrBuffer);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongDoubleArray(long double** longdouble_t, const uint32_t numElements,
        struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeDouble = sizeof(long double);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeDouble;
    if (unread >= totalSpace)
    {
        *longdouble_t = malloc(totalSpace);
        long double* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeLongDouble(&swap[i], m_cdrBuffer);
        }
        memcpy(*longdouble_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}

int8_t deserializeLongDoubleArrayEndianness(long double** longdouble_t, const uint32_t numElements,
        Endianness endianness, struct microCDR* m_cdrBuffer)
{
    int8_t result = 0;

    updateCurrentPosition(m_cdrBuffer);
    uint32_t unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
    uint32_t sizeDouble = sizeof(long double);

    unread = m_cdrBuffer->m_microBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

    uint32_t totalSpace = numElements * sizeDouble;
    if (unread >= totalSpace)
    {
        *longdouble_t = malloc(totalSpace);
        long double* swap = malloc(totalSpace);
        uint32_t i = 0;
        for (i = 0; i < numElements; i++)
        {
            deserializeLongDoubleEndianness(&swap[i], endianness, m_cdrBuffer);
        }
        memcpy(*longdouble_t, swap, totalSpace);
        free(swap);
    }
    else
    {
        return -1;
    }
    return result;
}
