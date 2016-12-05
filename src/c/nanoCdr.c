#include <nanocdr/nanoCdr.h>
#include <stdlib.h>
#include <string.h>
#include <nanocdr/nanoBuffer.h>

#include <stdint.h>

#include <stdio.h>

void newDynamicBuffer()
{
	m_cdrBuffer = malloc(sizeof(nanoBuffer));

	m_cdrBuffer->m_bufferSize = 0;
	m_cdrBuffer->m_internalBuffer = '1';
	m_cdrBuffer->m_iterator = 0;
 	m_cdrBuffer->m_serializedBuffer = 0;

	int32_t local_i = 1;
	char *local_c = (char*)&local_i;
	char endia = (*local_c);
	if(endia == '1')
	{
		m_endianness = LITTLE_ENDIANNESS;
	}
	else
	{
		m_endianness = BIG_ENDIANNESS;
	}
	m_swapBytes = FALSE;
}


void newStaticBuffer (char * buffer, uint32_t bufferSize)
{
	m_cdrBuffer = malloc(sizeof(nanoBuffer));

	m_cdrBuffer->m_bufferSize = bufferSize;
	m_cdrBuffer->m_internalBuffer = '0';
	m_cdrBuffer->m_iterator = 0;
	m_cdrBuffer->m_serializedBuffer = 0;
	m_cdrBuffer->m_buffer = buffer;

	int32_t local_i = 1;
	char *local_c = (char*)&local_i;
	char endia = (*local_c);
	if(endia == '1')
	{
		m_endianness = LITTLE_ENDIANNESS;
	}
	else
	{
		m_endianness = BIG_ENDIANNESS;
	}
	m_swapBytes = FALSE;
}


void destroyBuffer()
{
	if(m_cdrBuffer->m_internalBuffer == '1')
	{
		free(m_cdrBuffer->m_buffer);
	}
	free(m_cdrBuffer);
}

void mallocCdr (void ** point_t, uint32_t size)
{
	*point_t = malloc(size);
}

void freeCdr (void ** point_t)
{
	free(*point_t);
}

void resetAlignment()
{
		m_cdrBuffer->m_alignPosition = m_cdrBuffer->m_currentPosition;
}

uint32_t getSerializedDataLength()
{
	return m_cdrBuffer->m_serializedBuffer;
}

char * getBufferPointer()
{
	return m_cdrBuffer->m_buffer;
}

char * getCurrentPosition()
{
		return m_cdrBuffer->m_currentPosition;
}

void changeEndianness (Endianness endianness)
{
	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
		m_endianness = endianness;
	}
}

int8_t resize(uint32_t  minSizeInc)
{
    if(m_cdrBuffer->m_internalBuffer == '1')
    {
        if(m_cdrBuffer->m_bufferSize == 0)
        {
           	m_cdrBuffer->m_bufferSize = minSizeInc;
						m_cdrBuffer->m_buffer = (char*)malloc(m_cdrBuffer->m_bufferSize);
						return 0;
        }
        else
        {
					uint32_t freeSpace = (uint32_t)(m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);

					if(freeSpace < minSizeInc)
					{
						int32_t sizeInc = minSizeInc - freeSpace;
	          m_cdrBuffer->m_bufferSize += sizeInc;
        	  m_cdrBuffer->m_buffer = (char*)realloc(m_cdrBuffer->m_buffer, m_cdrBuffer->m_bufferSize);
            return 0;
					}
        }
    }
    return -1;
}

void reset ()
{
	m_cdrBuffer->m_serializedBuffer = 0;
}

int8_t jump (uint16_t bytes)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	if(freeSpace > bytes || resize(bytes) == 0)
	{
		m_cdrBuffer->m_serializedBuffer += bytes;
	}
	else
	{
			result = -1;
	}
	return result;
}


int8_t serializeChar (const char char_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t needed = sizeof(char);

	if((resize(needed) == 0) || free >= needed)
	{
		memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&char_t, needed);
		m_cdrBuffer->m_serializedBuffer +=needed;
		m_cdrBuffer->m_currentPosition += needed;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t serializeUnsignedChar (const unsigned char uchar_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t needed = sizeof(unsigned char);

	if((resize(needed) == 0) || free >= needed)
	{
		memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&uchar_t, needed);
		m_cdrBuffer->m_serializedBuffer +=needed;
		m_cdrBuffer->m_currentPosition += needed;
	}
	else
	{
		result = -1;
	}

	return result;
}


int8_t serializeSignedChar (const signed char schar_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t needed = sizeof(signed char);

	if((resize(needed) == 0) || free >= needed)
	{
		memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&schar_t, needed);
		m_cdrBuffer->m_serializedBuffer +=needed;
		m_cdrBuffer->m_currentPosition += needed;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t serializeString (const char * string_t, const uint32_t length)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t needed = sizeof(length) + length + 1;

	if((resize(needed) == 0) || free >= needed)
	{
		result = serializeUnsignedInt(length + 1);
		if(result < 0) return result;

		memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, string_t, length + 1);
		m_cdrBuffer->m_serializedBuffer += (length + 1);
		m_cdrBuffer->m_currentPosition += (length + 1);

	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t serializeStringEndianness (const char * string_t, const uint32_t length, Endianness endianness)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t needed = sizeof(length) + length + 1;

	if((resize(needed) == 0) || free >= needed)
	{
		result = serializeUnsignedIntEndianness(length + 1, endianness);
		if(result < 0) return result;

		memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, string_t, length + 1);
		m_cdrBuffer->m_serializedBuffer += (length + 1);
		m_cdrBuffer->m_currentPosition += (length + 1);

	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t deserializeChar(char * char_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	if(unread >= 1)
	{
		memcpy(char_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, 1);
		m_cdrBuffer->m_iterator += 1;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t deserializeUnsignedChar(unsigned char * uchar_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	if(unread >= 1)
	{
		memcpy(uchar_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, 1);
		m_cdrBuffer->m_iterator += 1;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t deserializeSignedChar(signed char * schar_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	if(unread >= 1)
	{
		memcpy(schar_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, 1);
		m_cdrBuffer->m_iterator += 1;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t deserializeString (char ** string, uint32_t * strlen)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeInt = sizeof(int32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(strlen);

		if(result < 0) return -1;

		unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

		if(unread >= *strlen)
		{

			*string = malloc(*strlen);
			memcpy(*string, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, *strlen);
			m_cdrBuffer->m_iterator += *strlen;
			*strlen -= 1;
		}
		else
		{
			return -1;
		}
	}
	return result;
}

int8_t deserializeStringEndianness (char ** string, uint32_t * strlen, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeInt = sizeof(int32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(strlen, endianness);

		if(result < 0) return -1;

		unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

		if(unread >= *strlen)
		{

			*string = malloc(*strlen);
			memcpy(*string, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, *strlen);
			m_cdrBuffer->m_iterator += *strlen;
			*strlen -= 1;
		}
		else
		{
			return -1;
		}
	}
	return result;
}

int8_t serializeShort (const int16_t short_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeShort = sizeof(int16_t);

	if((resize(sizeShort) == 0) || free >= sizeShort)
	{
		if(m_swapBytes == TRUE)
		{
			char * short_c = (char *)&short_t;
			m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer] = short_c[1];
			m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + 1] = short_c[0];
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&short_t, sizeShort);
		}

		m_cdrBuffer->m_serializedBuffer +=sizeShort;
		m_cdrBuffer->m_currentPosition += sizeShort;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t serializeShortEndianness (const int16_t short_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeShort (short_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeShort (short_t);
	}
	return result;
}

int8_t serializeUnsignedShort (const uint16_t ushort_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeShort = sizeof(uint16_t);
	uint16_t i = 0;

	if((resize(sizeShort) == 0) || free >= sizeShort)
	{
		if(m_swapBytes == TRUE)
		{
			char * short_c = (char *)&ushort_t;
			for (i = 0; i < sizeShort; i++)
			{
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = short_c[sizeShort - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&ushort_t, sizeShort);
		}
		m_cdrBuffer->m_serializedBuffer +=sizeShort;
		m_cdrBuffer->m_currentPosition += sizeShort;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t serializeUnsignedShortEndianness (const uint16_t ushort_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeUnsignedShort (ushort_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeUnsignedShort (ushort_t);
	}
	return result;
}

int8_t serializeInt (const int32_t int_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(int32_t);
	uint16_t i = 0;

	if((resize(sizeInt) == 0) || free >= sizeInt)
	{
		if(m_swapBytes == TRUE)
		{
			char * int_c = (char *)&int_t;
			for (i = 0; i < sizeInt; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = int_c[sizeInt - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&int_t, sizeInt);
		}

		m_cdrBuffer->m_serializedBuffer +=sizeInt;
		m_cdrBuffer->m_currentPosition += sizeInt;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t serializeIntEndianness (const int32_t int_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeInt (int_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeInt (int_t);
	}
	return result;
}

int8_t serializeUnsignedInt (const uint32_t uint_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(uint32_t);
	uint16_t i = 0;

	if((resize(sizeInt) == 0) || free >= sizeInt)
	{
		if(m_swapBytes == TRUE)
		{
			char * int_c = (char *)&uint_t;
			for (i = 0; i < sizeInt; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = int_c[sizeInt - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&uint_t, sizeInt);
		}

		m_cdrBuffer->m_serializedBuffer +=sizeInt;
		m_cdrBuffer->m_currentPosition += sizeInt;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t serializeUnsignedIntEndianness (const uint32_t uint_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeUnsignedInt (uint_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeUnsignedInt (uint_t);
	}
	return result;
}

int8_t serializeLong (const int64_t long_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(int64_t);
	uint16_t i = 0;

	if((resize(sizeLong) == 0) || free >= sizeLong)
	{
		if(m_swapBytes == TRUE)
		{
			char * long_c = (char *)&long_t;
			for (i = 0; i < sizeLong; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = long_c[sizeLong - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&long_t, sizeLong);
		}
		m_cdrBuffer->m_serializedBuffer +=sizeLong;
		m_cdrBuffer->m_currentPosition += sizeLong;

	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t serializeLongEndianness (const int64_t long_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeLong (long_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeLong (long_t);
	}
	return result;
}


int8_t serializeUnsignedLong (const uint64_t ulong_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(int64_t);
	uint16_t i = 0;

	if((resize(sizeLong) == 0) || free >= sizeLong)
	{
		if(m_swapBytes == TRUE)
		{
			char * long_c = (char *)&ulong_t;
			for (i = 0; i < sizeLong; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = long_c[sizeLong - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&ulong_t, sizeLong);
		}
		m_cdrBuffer->m_serializedBuffer +=sizeLong;
		m_cdrBuffer->m_currentPosition += sizeLong;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t serializeUnsignedLongEndianness (const uint64_t ulong_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeUnsignedLong (ulong_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeUnsignedLong (ulong_t);
	}
	return result;
}

int8_t serializeLongLong (const long long longlong_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(long long);
	uint16_t i = 0;

	if((resize(sizeLong) == 0) || free >= sizeLong)
	{
		if(m_swapBytes == TRUE)
		{
			char * long_c = (char *)&longlong_t;
			for (i = 0; i < sizeLong; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = long_c[sizeLong - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&longlong_t, sizeLong);
		}
		m_cdrBuffer->m_serializedBuffer +=sizeLong;
		m_cdrBuffer->m_currentPosition += sizeLong;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t serializeLongLongEndianness (const long long longlong_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeLongLong (longlong_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeLongLong (longlong_t);
	}
	return result;
}

int8_t serializeUnsignedLongLong (const unsigned long long ulonglong_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(unsigned long long);
	uint16_t i = 0;

	if((resize(sizeLong) == 0) || free >= sizeLong)
	{
		if(m_swapBytes == TRUE)
		{
			char * long_c = (char *)&ulonglong_t;
			for (i = 0; i < sizeLong; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = long_c[sizeLong - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&ulonglong_t, sizeLong);
		}
		m_cdrBuffer->m_serializedBuffer +=sizeLong;
		m_cdrBuffer->m_currentPosition += sizeLong;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t serializeUnsignedLongLongEndianness (const unsigned long long ulonglong_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeUnsignedLongLong(ulonglong_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeUnsignedLongLong(ulonglong_t);
	}
	return result;
}

int8_t serializeFloat (const float float_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeFloat = sizeof(float);
	uint16_t i = 0;

	if((resize(sizeFloat) == 0) || free >= sizeFloat)
	{
		if(m_swapBytes == TRUE)
		{
			char * float_c = (char *)&float_t;

			for (i = 0; i < sizeFloat; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = float_c[sizeFloat - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&float_t, sizeFloat);
		}

		m_cdrBuffer->m_serializedBuffer +=sizeFloat;
		m_cdrBuffer->m_currentPosition += sizeFloat;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t serializeFloatEndianness (const float float_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeFloat(float_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeFloat(float_t);
	}
	return result;
}

int8_t serializeDouble (const double double_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(double);
	uint16_t i = 0;

	if((resize(sizeDouble) == 0) || free >= sizeDouble)
	{
		if(m_swapBytes == TRUE)
		{
			char * double_c = (char *)&double_t;
			for (i = 0; i < sizeDouble; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = double_c[sizeDouble - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&double_t, sizeDouble);
		}

		m_cdrBuffer->m_serializedBuffer +=sizeDouble;
		m_cdrBuffer->m_currentPosition += sizeDouble;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t serializeDoubleEndianness (const double double_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeDouble(double_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeDouble(double_t);
	}
	return result;
}

int8_t serializeLongDouble (const long double longdouble_t)
{
	int8_t result = 0;

	uint32_t free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(long double);
	uint16_t i = 0;

	if((resize(sizeDouble) == 0) || free >= sizeDouble)
	{
		if(m_swapBytes == TRUE)
		{
			char * double_c = (char *)&longdouble_t;
			for (i = 0; i < sizeDouble; i++){
				m_cdrBuffer->m_buffer[m_cdrBuffer->m_serializedBuffer + i] = double_c[sizeDouble - i - 1];
			}
		}
		else
		{
			memcpy(m_cdrBuffer->m_buffer + m_cdrBuffer->m_serializedBuffer, (char *)&longdouble_t, sizeDouble);
		}

		m_cdrBuffer->m_serializedBuffer +=sizeDouble;
		m_cdrBuffer->m_currentPosition += sizeDouble;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t serializeLongDoubleEndianness (const long double longdouble_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = serializeLongDouble(longdouble_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = serializeLongDouble(longdouble_t);
	}
	return result;
}

int8_t deserializeShort(int16_t * short_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeShort = sizeof(int16_t);
	uint32_t i;

	if(unread >= sizeShort)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(short_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeShort);
		}
		else
		{
			char * short_c = (char *)short_t;
			for(i = 0; i < sizeShort; i++)
			{
				short_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeShort - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeShort;
		m_cdrBuffer->m_currentPosition -= sizeShort;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeShortEndianness (int16_t * short_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeShort(short_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeShort(short_t);
	}
	return result;
}

int8_t deserializeUnsignedShort(uint16_t * ushort_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeShort = sizeof(uint16_t);
	uint32_t i;

	if(unread >= sizeShort)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(ushort_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeShort);
		}
		else
		{
			char * short_c = (char *)ushort_t;
			for(i = 0; i < sizeShort; i++)
			{
				short_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeShort - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeShort;
		m_cdrBuffer->m_currentPosition -= sizeShort;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeUnsignedShortEndianness (uint16_t * ushort_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeUnsignedShort(ushort_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeUnsignedShort(ushort_t);
	}
	return result;
}

int8_t deserializeInt(int32_t * int_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeInt = sizeof(int32_t);
	uint32_t i;

	if(unread >= sizeInt)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(int_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeInt);
		}
		else
		{
			char * int_c = (char *)int_t;
			for(i = 0; i < sizeInt; i++)
			{
				int_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeInt - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeInt;
		m_cdrBuffer->m_currentPosition -= sizeInt;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeIntEndianness (int32_t * int_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeInt(int_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeInt(int_t);
	}
	return result;
}

int8_t deserializeUnsignedInt(uint32_t * int_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeInt = sizeof(uint32_t);
	uint32_t i;

	if(unread >= sizeInt)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(int_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeInt);
		}
		else
		{
			char * int_c = (char *)int_t;
			for(i = 0; i < sizeInt; i++)
			{
				int_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeInt - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeInt;
		m_cdrBuffer->m_currentPosition -= sizeInt;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeUnsignedIntEndianness (uint32_t * uint_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeUnsignedInt(uint_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeUnsignedInt(uint_t);
	}
	return result;
}


int8_t deserializeLong(int64_t * long_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeLong = sizeof(int64_t);
	uint32_t i;

	if(unread >= sizeLong)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(long_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeLong);
		}
		else
		{
			char * long_c = (char *)long_t;
			for(i = 0; i < sizeLong; i++)
			{
				long_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeLong - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeLong;
		m_cdrBuffer->m_currentPosition -= sizeLong;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeLongEndianness (int64_t * long_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeLong(long_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeLong(long_t);
	}
	return result;
}

int8_t deserializeUnsignedLong(uint64_t * ulong_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeLong = sizeof(uint64_t);
	uint32_t i;

	if(unread >= sizeLong)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(ulong_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeLong);
		}
		else
		{
			char * long_c = (char *)ulong_t;
			for(i = 0; i < sizeLong; i++)
			{
				long_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeLong - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeLong;
		m_cdrBuffer->m_currentPosition -= sizeLong;
	}
	else
	{
		result = -1;
	}

	return result;
}

int8_t deserializeUnsignedLongEndianness (uint64_t * ulong_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeUnsignedLong(ulong_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeUnsignedLong(ulong_t);
	}
	return result;
}

int8_t deserializeLongLong(long long * longlong_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeLong = sizeof(long long);
	uint32_t i;

	if(unread >= sizeLong)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(longlong_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeLong);
		}
		else
		{
			char * long_c = (char *)longlong_t;
			for(i = 0; i < sizeLong; i++)
			{
				long_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeLong - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeLong;
		m_cdrBuffer->m_currentPosition -= sizeLong;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeLongLongEndianness (long long * longlong_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeLongLong(longlong_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeLongLong(longlong_t);
	}
	return result;
}

int8_t deserializeUnsignedLongLong(unsigned long long * long_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeLong = sizeof(unsigned long long);
	uint32_t i;

	if(unread >= sizeLong)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(long_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeLong);
		}
		else
		{
			char * long_c = (char *)long_t;
			for(i = 0; i < sizeLong; i++)
			{
				long_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeLong - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeLong;
		m_cdrBuffer->m_currentPosition -= sizeLong;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeUnsignedLongLongEndianness (unsigned long long * ulonglong_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeUnsignedLongLong(ulonglong_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeUnsignedLongLong(ulonglong_t);
	}
	return result;
}

int8_t deserializeFloat(float * float_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeFloat = sizeof(float);
	uint32_t i;

	if(unread >= sizeFloat)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(float_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeFloat);
		}
		else
		{
			char * float_c = (char *)float_t;
			for(i = 0; i < sizeFloat; i++)
			{
				float_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeFloat - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeFloat;
		m_cdrBuffer->m_currentPosition -= sizeFloat;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeFloatEndianness (float * float_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeFloat(float_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeFloat(float_t);
	}
	return result;
}

int8_t deserializeDouble(double * double_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeDouble = sizeof(double);

	uint16_t i;

	if(unread >= sizeDouble)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(double_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeDouble);
		}
		else
		{
			char * double_c = (char *)double_t;
			for(i = 0; i < sizeDouble; i++)
			{
				double_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeDouble - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeDouble;
		m_cdrBuffer->m_currentPosition -= sizeDouble;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeDoubleEndianness (double * double_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeDouble(double_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeDouble(double_t);
	}
	return result;
}

int8_t deserializeLongDouble(long double * longdouble_t)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint16_t sizeDouble = sizeof(long double);

	uint16_t i;

	if(unread >= sizeDouble)
	{
		if(m_swapBytes == FALSE)
		{
			memcpy(longdouble_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, sizeDouble);
		}
		else
		{
			char * double_c = (char *)longdouble_t;
			for(i = 0; i < sizeDouble; i++)
			{
				double_c[i] = m_cdrBuffer->m_buffer[m_cdrBuffer->m_iterator + (sizeDouble - 1 - i)];
			}
		}
		m_cdrBuffer->m_iterator += sizeDouble;
		m_cdrBuffer->m_currentPosition -= sizeDouble;
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeLongDoubleEndianness (long double * longdouble_t, Endianness endianness)
{
	int8_t result = 0;

	if(endianness != m_endianness)
	{
		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }

		result = deserializeLongDouble(longdouble_t);

		if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
		else { m_swapBytes = TRUE; }
	}
	else
	{
		result = deserializeLongDouble(longdouble_t);
	}
	return result;
}

 int8_t serializeStringSequence (const char ** string_t, const uint32_t numElements)
 {
 	int8_t result = 0;
 	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
 	uint32_t totalSpace = sizeof(uint32_t);

	uint32_t i = 0;
	for (i = 0; i < numElements; i++){
		totalSpace += (uint32_t)strlen(string_t[i]);
		totalSpace += 1;
		totalSpace += sizeof(uint32_t);
	}

 	if((resize(totalSpace) == 0) || totalSpace <= freeSpace)
 	{
 		result = serializeUnsignedInt(numElements);
 		if(result < 0) return -1;
 		result = serializeStringArray(string_t, numElements);
 	}
 	return result;
 }

 int8_t serializeStringSequenceEndianness (const char ** string_t, const uint32_t numElements, Endianness endianness)
 {
	 int8_t result = 0;
  	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  	uint32_t totalSpace = sizeof(uint32_t);

 	uint32_t i = 0;
 	for (i = 0; i < numElements; i++){
 		totalSpace += (uint32_t)strlen(string_t[i]);
 		totalSpace += 1;
 		totalSpace += sizeof(uint32_t);
 	}

  	if((resize(totalSpace) == 0) || totalSpace <= freeSpace)
  	{
  		result = serializeUnsignedIntEndianness(numElements, endianness);
  		if(result < 0) return -1;
  		result = serializeStringArrayEndianness(string_t, numElements, endianness);
  	}
  	return result;
 }

 int8_t serializeStringArray (const char ** string_t, const uint32_t numElements)
 {
 	int8_t result = 0;
 	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);

	uint32_t i = 0;
	uint32_t totalSpace = 0;
	for (i = 0; i < numElements; i++){
		totalSpace += (uint32_t)strlen(string_t[i]);
		totalSpace += 1;
		totalSpace += sizeof(uint32_t);
	}

 	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
 	{
 		for(i = 0; i < numElements; i++)
 		{
 			result = serializeString(string_t[i], (uint32_t)strlen(string_t[i]));
 			if(result < 0) return -1;
 		}
 	}
 	return result;
 }

 int8_t serializeStringArrayEndianness (const char ** string_t, const uint32_t numElements, Endianness endianness)
 {
	 int8_t result = 0;
  	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);

 	uint32_t i = 0;
 	uint32_t totalSpace = 0;
 	for (i = 0; i < numElements; i++){
 		totalSpace += (uint32_t)strlen(string_t[i]);
 		totalSpace += 1;
 		totalSpace += sizeof(uint32_t);
 	}

  	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  	{
  		for(i = 0; i < numElements; i++)
  		{
  			result = serializeStringEndianness(string_t[i], (uint32_t)strlen(string_t[i]), endianness);
  			if(result < 0) return -1;
  		}
  	}
  	return result;
 }

int8_t serializeCharSequence (const char * char_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t totalSpace = sizeof(uint32_t) + numElements;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeCharArray(char_t, numElements);
	}
	return result;
}

int8_t serializeCharSequenceEndianness (const char * char_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
  uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  uint32_t totalSpace = sizeof(uint32_t) + numElements;

  if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  {
 	 result = serializeUnsignedIntEndianness(numElements, endianness);
 	 if(result < 0) return -1;
 	 result = serializeCharArray(char_t, numElements);
  }
  return result;
}

int8_t serializeCharArray (const char * char_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t totalSpace = numElements;
	uint32_t i = 0;
	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeChar(char_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeUnsignedCharSequence (const unsigned char * uchar_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t totalSpace = sizeof(uint32_t) + numElements;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedCharArray(uchar_t, numElements);
	}
	return result;
}

int8_t serializeUnsignedCharSequenceEndianness (const unsigned char * uchar_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
  uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  uint32_t totalSpace = sizeof(uint32_t) + numElements;

  if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  {
 	 result = serializeUnsignedIntEndianness(numElements, endianness);
 	 if(result < 0) return -1;
 	 result = serializeUnsignedCharArray(uchar_t, numElements);
  }
  return result;
}

int8_t serializeUnsignedCharArray (const unsigned char * uchar_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t totalSpace = numElements;
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedChar(uchar_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeSignedCharSequence (const signed char * schar_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t totalSpace = sizeof(uint32_t) + numElements;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeSignedCharArray(schar_t, numElements);
	}
	return result;
}

int8_t serializeSignedCharSequenceEndianness (const signed char * schar_t, const uint32_t numElements, Endianness endianness)
{
 int8_t result = 0;

 if(endianness != m_endianness)
 {
	 if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
	 else { m_swapBytes = TRUE; }

	 result = serializeSignedCharSequence(schar_t, numElements);

	 if(m_swapBytes == TRUE) { m_swapBytes = FALSE; }
	 else { m_swapBytes = TRUE; }
 }
 else
 {
	 result = serializeSignedCharSequence(schar_t, numElements);
 }
 return result;
}

int8_t serializeSignedCharArray (const signed char * schar_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint32_t totalSpace = numElements;
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeSignedChar(schar_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeShortSequence (const int16_t * short_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeShort = sizeof(int16_t);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeShort);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeShortArray(short_t, numElements);
	}
	return result;
}

int8_t serializeShortSequenceEndianness (const int16_t * short_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
  uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  uint16_t sizeShort = sizeof(int16_t);
  uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeShort);

  if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  {
 	 result = serializeUnsignedIntEndianness(numElements, endianness);
 	 if(result < 0) return -1;
 	 result = serializeShortArrayEndianness(short_t, numElements, endianness);
  }
  return result;
}

int8_t serializeShortArray (const int16_t * short_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeShort = sizeof(int16_t);
	uint32_t totalSpace = (numElements * sizeShort);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeShort(short_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeShortArrayEndianness (const int16_t * short_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
  uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  uint16_t sizeShort = sizeof(int16_t);
  uint32_t totalSpace = (numElements * sizeShort);
  uint32_t i = 0;

  if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  {
 	 for(i = 0; i < numElements; i++)
 	 {
 		 result = serializeShortEndianness(short_t[i], endianness);
 		 if(result < 0) return -1;
 	 }
  }
  return result;
}

int8_t serializeUnsignedShortSequence (const uint16_t * ushort_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeShort = sizeof(uint16_t);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeShort);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedShortArray(ushort_t, numElements);
	}
	return result;
}

int8_t serializeUnsignedShortSequenceEndianness (const uint16_t * ushort_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeShort = sizeof(uint16_t);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeShort);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeUnsignedShortArrayEndianness(ushort_t, numElements, endianness);
	}
	return result;
}

int8_t serializeUnsignedShortArray (const uint16_t * ushort_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeShort = sizeof(uint16_t);
	uint32_t totalSpace = (numElements * sizeShort);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedShort(ushort_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeUnsignedShortArrayEndianness (const uint16_t * ushort_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeShort = sizeof(uint16_t);
	uint32_t totalSpace = (numElements * sizeShort);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedShortEndianness(ushort_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeIntSequence (const int32_t * int_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(int32_t);
	uint32_t totalSpace = sizeInt + (numElements * sizeInt);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeIntArray(int_t, numElements);
	}
	return result;
}

int8_t serializeIntSequenceEndianness (const int32_t * int_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(int32_t);
	uint32_t totalSpace = sizeInt + (numElements * sizeInt);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeIntArrayEndianness(int_t, numElements, endianness);
	}
	return result;
}

int8_t serializeIntArray (const int32_t * int_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(int32_t);
	uint32_t totalSpace = (numElements * sizeInt);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeInt(int_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeIntArrayEndianness (const int32_t * int_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(int32_t);
	uint32_t totalSpace = (numElements * sizeInt);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeIntEndianness(int_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeUnsignedIntSequence (const uint32_t * uint_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(uint32_t);
	uint32_t totalSpace = sizeInt + (numElements * sizeInt);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedIntArray(uint_t, numElements);
	}
	return result;
}

int8_t serializeUnsignedIntSequenceEndianness (const uint32_t * uint_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(uint32_t);
	uint32_t totalSpace = sizeInt + (numElements * sizeInt);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeUnsignedIntArrayEndianness(uint_t, numElements, endianness);
	}
	return result;
}

int8_t serializeUnsignedIntArray (const uint32_t * uint_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(uint32_t);
	uint32_t totalSpace = (numElements * sizeInt);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedInt(uint_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeUnsignedIntArrayEndianness (const uint32_t * uint_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeInt = sizeof(uint32_t);
	uint32_t totalSpace = (numElements * sizeInt);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedIntEndianness(uint_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeLongSequence (const int64_t * long_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(int64_t);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeLongArray(long_t, numElements);
	}
	return result;
}

int8_t serializeLongSequenceEndianness (const int64_t * long_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(int64_t);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeLongArrayEndianness(long_t, numElements, endianness);
	}
	return result;
}

int8_t serializeLongArray (const int64_t * long_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(int64_t);
	uint32_t totalSpace = (numElements * sizeLong);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeLong(long_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeLongArrayEndianness (const int64_t * long_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(int64_t);
	uint32_t totalSpace = (numElements * sizeLong);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeLongEndianness(long_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeUnsignedLongSequence (const uint64_t * ulong_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(uint64_t);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedLongArray(ulong_t, numElements);
	}
	return result;
}

int8_t serializeUnsignedLongSequenceEndianness (const uint64_t * ulong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(uint64_t);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeUnsignedLongArrayEndianness(ulong_t, numElements, endianness);
	}
	return result;
}

int8_t serializeUnsignedLongArray (const uint64_t * ulong_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(uint64_t);
	uint32_t totalSpace = (numElements * sizeLong);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedLong(ulong_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeUnsignedLongArrayEndianness (const uint64_t * ulong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(uint64_t);
	uint32_t totalSpace = (numElements * sizeLong);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedLongEndianness(ulong_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeLongLongSequence (const long long * longlong_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(long long);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeLongLongArray(longlong_t, numElements);
	}
	return result;
}

int8_t serializeLongLongSequenceEndianness (const long long * longlong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(long long);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeLongLongArrayEndianness(longlong_t, numElements, endianness);
	}
	return result;
}

int8_t serializeLongLongArray (const long long * longlong_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(long long);
	uint32_t totalSpace = (numElements * sizeLong);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeLongLong(longlong_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeLongLongArrayEndianness (const long long * longlong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(long long);
	uint32_t totalSpace = (numElements * sizeLong);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeLongLongEndianness(longlong_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeUnsignedLongLongSequence (const unsigned long long * ulonglong_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(unsigned long long);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedLongLongArray(ulonglong_t, numElements);
	}
	return result;
}

int8_t serializeUnsignedLongLongSequenceEndianness (const unsigned long long * ulonglong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(unsigned long long);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeUnsignedLongLongArrayEndianness(ulonglong_t, numElements, endianness);
	}
	return result;
}

int8_t serializeUnsignedLongLongArray (const unsigned long long * ulonglong_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(unsigned long long);
	uint32_t totalSpace = (numElements * sizeLong);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedLongLong(ulonglong_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeUnsignedLongLongArrayEndianness (const unsigned long long * ulonglong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeLong = sizeof(unsigned long long);
	uint32_t totalSpace = (numElements * sizeLong);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeUnsignedLongLongEndianness(ulonglong_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeFloatSequence (const float * float_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeFloat = sizeof(float);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeFloat);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeFloatArray(float_t, numElements);
	}
	return result;
}

int8_t serializeFloatSequenceEndianness (const float * float_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeFloat = sizeof(float);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeFloat);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeFloatArrayEndianness(float_t, numElements, endianness);
	}
	return result;
}

int8_t serializeFloatArray (const float * float_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeFloat = sizeof(float);
	uint32_t totalSpace = (numElements * sizeFloat);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeFloat(float_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeFloatArrayEndianness (const float * float_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeFloat = sizeof(float);
	uint32_t totalSpace = (numElements * sizeFloat);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeFloatEndianness(float_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeDoubleSequence (const double * double_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(double);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeDouble);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeDoubleArray(double_t, numElements);
	}
	return result;
}

int8_t serializeDoubleSequenceEndianness (const double * double_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(double);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeDouble);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeDoubleArrayEndianness(double_t, numElements, endianness);
	}
	return result;
}

int8_t serializeDoubleArray (const double * double_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(double);
	uint32_t totalSpace = (numElements * sizeDouble);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeDouble(double_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeDoubleArrayEndianness (const double * double_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(double);
	uint32_t totalSpace = (numElements * sizeDouble);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeDoubleEndianness(double_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeLongDoubleSequence (const long double * longdouble_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(long double);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeDouble);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeLongDoubleArray(longdouble_t, numElements);
	}
	return result;
}

int8_t serializeLongDoubleSequenceEndianness (const long double * longdouble_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(long double);
	uint32_t totalSpace = sizeof(uint32_t) + (numElements * sizeDouble);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeLongDoubleArrayEndianness(longdouble_t, numElements, endianness);
	}
	return result;
}

int8_t serializeLongDoubleArray (const long double * longdouble_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(long double);
	uint32_t totalSpace = (numElements * sizeDouble);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeLongDouble(longdouble_t[i]);
			if(result < 0) return -1;
		}
	}
	return result;
}

int8_t serializeLongDoubleArrayEndianness (const long double * longdouble_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	uint16_t sizeDouble = sizeof(long double);
	uint32_t totalSpace = (numElements * sizeDouble);
	uint32_t i = 0;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		for(i = 0; i < numElements; i++)
		{
			result = serializeLongDoubleEndianness(longdouble_t[i], endianness);
			if(result < 0) return -1;
		}
	}
	return result;
}

//DESERIALIZE CHAR

int8_t deserializeStringSequence(char *** string_t, uint32_t * numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		char ** swap = malloc(*numElements * sizeof(char *));
		result = deserializeStringArray(&swap, *numElements);
		*string_t = malloc(*numElements * sizeof(char *));
		memcpy(*string_t, swap, (*numElements * sizeof(char *)));
		free(swap);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeStringSequenceEndianness(char *** string_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		char ** swap = malloc(*numElements * sizeof(char *));
		result = deserializeStringArrayEndianness(&swap, *numElements, endianness);
		*string_t = malloc(*numElements * sizeof(char *));
		memcpy(*string_t, swap, (*numElements * sizeof(char *)));
		free(swap);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeStringArray (char *** string_t, const uint32_t numElements)
{
	int8_t result = 0;

	char ** swap = malloc(numElements * sizeof(char * ));
	*string_t = malloc(numElements * sizeof(char *));

	uint32_t i = 0;
	uint32_t length = 0;
	for (i = 0; i < numElements; i++)
	{
		result = deserializeString(&swap[i], &length);
		if(result < 0) return -1;
	}
	memcpy(*string_t, swap, (numElements * sizeof(char *)));
	free(swap);
	return result;
}

int8_t deserializeStringArrayEndianness (char *** string_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	char ** swap = malloc(numElements * sizeof(char * ));
	*string_t = malloc(numElements * sizeof(char *));

	uint32_t i = 0;
	uint32_t length = 0;
	for (i = 0; i < numElements; i++)
	{
		result = deserializeStringEndianness(&swap[i], &length, endianness);
		if(result < 0) return -1;
	}
	memcpy(*string_t, swap, (numElements * sizeof(char *)));
	free(swap);
	return result;
}

int8_t deserializeCharSequence (char ** char_t, uint32_t * numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeCharArray(char_t, *numElements);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeCharSequenceEndianness (char ** char_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeCharArray(char_t, *numElements);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeCharArray (char ** char_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t totalSpace = numElements;
	if(unread >= totalSpace)
	{
		*char_t = malloc(totalSpace);
		memcpy(*char_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, totalSpace);
		m_cdrBuffer->m_iterator += totalSpace;
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedCharSequence (unsigned char ** uchar_t, uint32_t * numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeUnsignedCharArray(uchar_t, *numElements);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeUnsignedCharSequenceEndianness (unsigned char ** uchar_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeUnsignedCharArray(uchar_t, *numElements);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeUnsignedCharArray (unsigned char ** uchar_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t totalSpace = numElements;
	if(unread >= totalSpace)
	{
		*uchar_t = malloc(totalSpace);
		memcpy(*uchar_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, totalSpace);
		m_cdrBuffer->m_iterator += totalSpace;
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeSignedCharSequence (signed char ** schar_t, uint32_t * numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeSignedCharArray(schar_t, *numElements);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeSignedCharSequenceEndianness (signed char ** schar_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeSignedCharArray(schar_t, *numElements);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeSignedCharArray (signed char ** char_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t totalSpace = numElements;
	if(unread >= totalSpace)
	{
		*char_t = malloc(totalSpace);
		memcpy(*char_t, m_cdrBuffer->m_buffer + m_cdrBuffer->m_iterator, totalSpace);
		m_cdrBuffer->m_iterator += totalSpace;
	}
	else
	{
		return -1;
	}
	return result;
}

//DESERIALIZE SHORT

int8_t deserializeShortSequence (int16_t ** short_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeShortArray(short_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeShortSequenceEndianness (int16_t ** short_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeShortArrayEndianness(short_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeShortArray (int16_t ** short_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeShort = sizeof(int16_t);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t totalSpace = numElements * sizeShort;
	if(unread >= totalSpace)
	{
		*short_t = malloc(totalSpace);
		int16_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeShort(&swap[i]);
		}
		memcpy(*short_t, swap, totalSpace);
		free(swap);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeShortArrayEndianness (int16_t ** short_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeShort = sizeof(int16_t);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t totalSpace = numElements * sizeShort;
	if(unread >= totalSpace)
	{
		*short_t = malloc(totalSpace);
		int16_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeShortEndianness(&swap[i], endianness);
		}
		memcpy(*short_t, swap, totalSpace);
		free(swap);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedShortSequence (uint16_t ** ushort_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeUnsignedShortArray(ushort_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedShortSequenceEndianness (uint16_t ** ushort_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeUnsignedShortArrayEndianness(ushort_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedShortArray (uint16_t ** ushort_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeShort = sizeof(int16_t);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t totalSpace = numElements * sizeShort;
	if(unread >= totalSpace)
	{
		*ushort_t = malloc(totalSpace);
		uint16_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeUnsignedShort(&swap[i]);
		}
		memcpy(*ushort_t, swap, totalSpace);
		free(swap);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedShortArrayEndianness (uint16_t ** ushort_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeShort = sizeof(int16_t);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t totalSpace = numElements * sizeShort;
	if(unread >= totalSpace)
	{
		*ushort_t = malloc(totalSpace);
		uint16_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeUnsignedShortEndianness(&swap[i], endianness);
		}
		memcpy(*ushort_t, swap, totalSpace);
		free(swap);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeIntSequence (int32_t ** int_t, uint32_t * numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeIntArray(int_t, *numElements);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeIntSequenceEndianness (int32_t ** int_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeIntArrayEndianness(int_t, *numElements, endianness);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeIntArray (int32_t ** int_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeInt;
	if(unread >= totalSpace)
	{
		*int_t = malloc(totalSpace);
		int32_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeInt(&swap[i]);
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

int8_t deserializeIntArrayEndianness (int32_t ** int_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeInt;
	if(unread >= totalSpace)
	{
		*int_t = malloc(totalSpace);
		int32_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeIntEndianness(&swap[i], endianness);
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

int8_t deserializeUnsignedIntSequence (uint32_t ** uint_t, uint32_t * numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeUnsignedIntArray(uint_t, *numElements);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeUnsignedIntSequenceEndianness (uint32_t ** int_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeUnsignedIntArrayEndianness(int_t, *numElements, endianness);
	}
	else
	{
		result = -1;
	}
	return result;
}

int8_t deserializeUnsignedIntArray (uint32_t ** uint_t, const uint32_t numElements)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeInt;
	if(unread >= totalSpace)
	{
		*uint_t = malloc(totalSpace);
		uint32_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeUnsignedInt(&swap[i]);
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

int8_t deserializeUnsignedIntArrayEndianness (uint32_t ** uint_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;
	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeInt;
	if(unread >= totalSpace)
	{
		*uint_t = malloc(totalSpace);
		uint32_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeUnsignedIntEndianness(&swap[i], endianness);
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

int8_t deserializeLongSequence (int64_t ** long_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeLongArray(long_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeLongSequenceEndianness (int64_t ** long_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeLongArrayEndianness(long_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeLongArray (int64_t ** long_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeLong = sizeof(int64_t);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*long_t = malloc(totalSpace);
		int64_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeLong(&swap[i]);
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

int8_t deserializeLongArrayEndianness (int64_t ** long_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeLong = sizeof(int64_t);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*long_t = malloc(totalSpace);
		int64_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeLongEndianness(&swap[i], endianness);
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

int8_t deserializeUnsignedLongSequence (uint64_t ** ulong_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeUnsignedLongArray(ulong_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedLongSequenceEndianness (uint64_t ** ulong_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeUnsignedLongArrayEndianness(ulong_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedLongArray (uint64_t ** ulong_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeLong = sizeof(uint64_t);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*ulong_t = malloc(totalSpace);
		uint64_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeUnsignedLong(&swap[i]);
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

int8_t deserializeUnsignedLongArrayEndianness (uint64_t ** ulong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeLong = sizeof(uint64_t);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*ulong_t = malloc(totalSpace);
		uint64_t * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeUnsignedLongEndianness(&swap[i], endianness);
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

int8_t deserializeLongLongSequence (long long ** longlong_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeLongLongArray(longlong_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeLongLongSequenceEndianness (long long ** longlong_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeLongLongArrayEndianness(longlong_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeLongLongArray (long long ** longlong_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeLong = sizeof(long long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*longlong_t = malloc(totalSpace);
		long long * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeLongLong(&swap[i]);
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

int8_t deserializeLongLongArrayEndianness (long long ** longlong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeLong = sizeof(long long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*longlong_t = malloc(totalSpace);
		long long * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeLongLongEndianness(&swap[i], endianness);
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

int8_t deserializeUnsignedLongLongSequence (unsigned long long ** ulonglong_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeUnsignedLongLongArray(ulonglong_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedLongLongSequenceEndianness (unsigned long long ** ulonglong_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeUnsignedLongLongArrayEndianness(ulonglong_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeUnsignedLongLongArray (unsigned long long ** ulonglong_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeLong = sizeof(unsigned long long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*ulonglong_t = malloc(totalSpace);
		unsigned long long * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeUnsignedLongLong(&swap[i]);
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

int8_t deserializeUnsignedLongLongArrayEndianness (unsigned long long ** ulonglong_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeLong = sizeof(unsigned long long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*ulonglong_t = malloc(totalSpace);
		unsigned long long * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeUnsignedLongLongEndianness(&swap[i], endianness);
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

int8_t deserializeFloatSequence (float ** float_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeFloatArray(float_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeFloatSequenceEndianness (float ** float_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeFloatArrayEndianness(float_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeFloatArray (float ** float_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeFloat = sizeof(float);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeFloat;
	if(unread >= totalSpace)
	{
		*float_t = malloc(totalSpace);
		float * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeFloat(&swap[i]);
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

int8_t deserializeFloatArrayEndianness (float ** float_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeFloat = sizeof(float);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeFloat;
	if(unread >= totalSpace)
	{
		*float_t = malloc(totalSpace);
		float * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeFloatEndianness(&swap[i], endianness);
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

int8_t deserializeDoubleSequence (double ** double_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeDoubleArray(double_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeDoubleSequenceEndianness (double ** double_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeDoubleArrayEndianness(double_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeDoubleArray (double ** double_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeDouble = sizeof(double);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeDouble;
	if(unread >= totalSpace)
	{
		*double_t = malloc(totalSpace);
		double * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeDouble(&swap[i]);
		}
		memcpy(*double_t, swap, totalSpace);
		free(swap);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeDoubleArrayEndianness (double ** double_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeDouble = sizeof(double);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeDouble;
	if(unread >= totalSpace)
	{
		*double_t = malloc(totalSpace);
		double * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeDoubleEndianness(&swap[i], endianness);
		}
		memcpy(*double_t, swap, totalSpace);
		free(swap);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeLongDoubleSequence (long double ** longdouble_t, uint32_t * numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = deserializeLongDoubleArray(longdouble_t, *numElements);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeLongDoubleSequenceEndianness (long double ** longdouble_t, uint32_t * numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeInt = sizeof(uint32_t);

	if(unread >= sizeInt)
	{
		result = deserializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = deserializeLongDoubleArrayEndianness(longdouble_t, *numElements, endianness);
	}
	else
	{
		return -1;
	}
	return result;
}

int8_t deserializeLongDoubleArray (long double ** longdouble_t, const uint32_t numElements)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeDouble = sizeof(long double);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeDouble;
	if(unread >= totalSpace)
	{
		*longdouble_t = malloc(totalSpace);
		long double * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeLongDouble(&swap[i]);
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

int8_t deserializeLongDoubleArrayEndianness (long double ** longdouble_t, const uint32_t numElements, Endianness endianness)
{
	int8_t result = 0;

	uint32_t unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	uint32_t sizeDouble = sizeof(long double);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	uint32_t totalSpace = numElements * sizeDouble;
	if(unread >= totalSpace)
	{
		*longdouble_t = malloc(totalSpace);
		long double * swap = malloc(totalSpace);
		uint32_t i = 0;
		for (i = 0; i < numElements; i++)
		{
			deserializeLongDoubleEndianness(&swap[i], endianness);
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
