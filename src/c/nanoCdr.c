#include <nanocdr/nanoCdr.h>
#include <stdlib.h>
#include <string.h>
#include <nanocdr/nanoBuffer.h>

#include <stdio.h>

void newDynamicBuffer()
{
	m_cdrBuffer = malloc(sizeof(nanoBuffer));

	m_cdrBuffer->m_bufferSize = 0;
	m_cdrBuffer->m_internalBuffer = '1';
	m_cdrBuffer->m_iterator = 0;
 	m_cdrBuffer->m_serializedBuffer = 0;

	int local_i = 1;
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


void newStaticBuffer (char * buffer, unsigned int bufferSize)
{
	m_cdrBuffer = malloc(sizeof(nanoBuffer));

	m_cdrBuffer->m_bufferSize = bufferSize;
	m_cdrBuffer->m_internalBuffer = '0';
	m_cdrBuffer->m_iterator = 0;
	m_cdrBuffer->m_serializedBuffer = 0;
	m_cdrBuffer->m_buffer = buffer;

	int local_i = 1;
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

void mallocCdr (void ** point_t, unsigned int size)
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

unsigned int getSerializedDataLength()
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

short resize(unsigned int  minSizeInc)
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
					unsigned int freeSpace = (unsigned int)(m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);

					if(freeSpace < minSizeInc)
					{
						int sizeInc = minSizeInc - freeSpace;
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

short jump (unsigned short bytes)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
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


short serializeChar (const char char_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int needed = sizeof(char);

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

short serializeUnsignedChar (const unsigned char uchar_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int needed = sizeof(unsigned char);

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


short serializeSignedChar (const signed char schar_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int needed = sizeof(signed char);

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

short serializeString (const char * string_t, const unsigned int length)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int needed = sizeof(length) + length + 1;

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

short serializeStringEndianness (const char * string_t, const unsigned int length, Endianness endianness)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int needed = sizeof(length) + length + 1;

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

short deserializeChar(char * char_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

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

short deserializeUnsignedChar(unsigned char * uchar_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

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

short deserializeSignedChar(signed char * schar_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

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

short deserializeString (char ** string, unsigned int * strlen)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeInt = sizeof(int);

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

short deserializeStringEndianness (char ** string, unsigned int * strlen, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeInt = sizeof(int);

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

short serializeShort (const short short_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeShort = sizeof(short);

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

short serializeShortEndianness (const short short_t, Endianness endianness)
{
	short result = 0;

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

short serializeUnsignedShort (const unsigned short ushort_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeShort = sizeof(unsigned short);
	unsigned short i = 0;

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

short serializeUnsignedShortEndianness (const unsigned short ushort_t, Endianness endianness)
{
	short result = 0;

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

short serializeInt (const int int_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(int);
	unsigned short i = 0;

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

short serializeIntEndianness (const int int_t, Endianness endianness)
{
	short result = 0;

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

short serializeUnsignedInt (const unsigned int uint_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(unsigned int);
	unsigned short i = 0;

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

short serializeUnsignedIntEndianness (const unsigned int uint_t, Endianness endianness)
{
	short result = 0;

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

short serializeLong (const long long_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long);
	unsigned short i = 0;

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

short serializeLongEndianness (const long long_t, Endianness endianness)
{
	short result = 0;

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


short serializeUnsignedLong (const unsigned long ulong_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long);
	unsigned short i = 0;

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

short serializeUnsignedLongEndianness (const unsigned long ulong_t, Endianness endianness)
{
	short result = 0;

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

short serializeLongLong (const long long longlong_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long long);
	unsigned short i = 0;

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

short serializeLongLongEndianness (const long long longlong_t, Endianness endianness)
{
	short result = 0;

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

short serializeUnsignedLongLong (const unsigned long long ulonglong_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long long);
	unsigned short i = 0;

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

short serializeUnsignedLongLongEndianness (const unsigned long long ulonglong_t, Endianness endianness)
{
	short result = 0;

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

short serializeFloat (const float float_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeFloat = sizeof(float);
	unsigned short i = 0;

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

short serializeFloatEndianness (const float float_t, Endianness endianness)
{
	short result = 0;

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

short serializeDouble (const double double_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(double);
	unsigned short i = 0;

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

short serializeDoubleEndianness (const double double_t, Endianness endianness)
{
	short result = 0;

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

short serializeLongDouble (const long double longdouble_t)
{
	short result = 0;

	unsigned int free = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(long double);
	unsigned short i = 0;

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

short serializeLongDoubleEndianness (const long double longdouble_t, Endianness endianness)
{
	short result = 0;

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

short deserializeShort(short * short_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeShort = sizeof(short);
	unsigned int i;

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

short deserializeShortEndianness (short * short_t, Endianness endianness)
{
	short result = 0;

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

short deserializeUnsignedShort(unsigned short * ushort_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeShort = sizeof(unsigned short);
	unsigned int i;

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

short deserializeUnsignedShortEndianness (unsigned short * ushort_t, Endianness endianness)
{
	short result = 0;

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

short deserializeInt(int * int_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeInt = sizeof(int);
	unsigned int i;

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

short deserializeIntEndianness (int * int_t, Endianness endianness)
{
	short result = 0;

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

short deserializeUnsignedInt(unsigned int * int_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeInt = sizeof(unsigned int);
	unsigned int i;

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

short deserializeUnsignedIntEndianness (unsigned int * uint_t, Endianness endianness)
{
	short result = 0;

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


short deserializeLong(long * long_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeLong = sizeof(long);
	unsigned int i;

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

short deserializeLongEndianness (long * long_t, Endianness endianness)
{
	short result = 0;

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

short deserializeUnsignedLong(unsigned long * ulong_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeLong = sizeof(unsigned long);
	unsigned int i;

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

short deserializeUnsignedLongEndianness (unsigned long * ulong_t, Endianness endianness)
{
	short result = 0;

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

short deserializeLongLong(long long * longlong_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeLong = sizeof(long long);
	unsigned int i;

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

short deserializeLongLongEndianness (long long * longlong_t, Endianness endianness)
{
	short result = 0;

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

short deserializeUnsignedLongLong(unsigned long long * long_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeLong = sizeof(unsigned long long);
	unsigned int i;

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

short deserializeUnsignedLongLongEndianness (unsigned long long * ulonglong_t, Endianness endianness)
{
	short result = 0;

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

short deserializeFloat(float * float_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeFloat = sizeof(float);
	unsigned int i;

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

short deserializeFloatEndianness (float * float_t, Endianness endianness)
{
	short result = 0;

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

short deserializeDouble(double * double_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeDouble = sizeof(double);

	unsigned short i;

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

short deserializeDoubleEndianness (double * double_t, Endianness endianness)
{
	short result = 0;

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

short deserializeLongDouble(long double * longdouble_t)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned short sizeDouble = sizeof(long double);

	unsigned short i;

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

short deserializeLongDoubleEndianness (long double * longdouble_t, Endianness endianness)
{
	short result = 0;

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

 short serializeStringSequence (const char ** string_t, const unsigned int numElements)
 {
 	short result = 0;
 	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
 	unsigned int totalSpace = sizeof(unsigned int);

	unsigned int i = 0;
	for (i = 0; i < numElements; i++){
		totalSpace += (unsigned int)strlen(string_t[i]);
		totalSpace += 1;
		totalSpace += sizeof(unsigned int);
	}

 	if((resize(totalSpace) == 0) || totalSpace <= freeSpace)
 	{
 		result = serializeUnsignedInt(numElements);
 		if(result < 0) return -1;
 		result = serializeStringArray(string_t, numElements);
 	}
 	return result;
 }

 short serializeStringSequenceEndianness (const char ** string_t, const unsigned int numElements, Endianness endianness)
 {
	 short result = 0;
  	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  	unsigned int totalSpace = sizeof(unsigned int);

 	unsigned int i = 0;
 	for (i = 0; i < numElements; i++){
 		totalSpace += strlen(string_t[i]);
 		totalSpace += 1;
 		totalSpace += sizeof(unsigned int);
 	}

  	if((resize(totalSpace) == 0) || totalSpace <= freeSpace)
  	{
  		result = serializeUnsignedIntEndianness(numElements, endianness);
  		if(result < 0) return -1;
  		result = serializeStringArrayEndianness(string_t, numElements, endianness);
  	}
  	return result;
 }

 short serializeStringArray (const char ** string_t, const unsigned int numElements)
 {
 	short result = 0;
 	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);

	unsigned int i = 0;
	unsigned int totalSpace = 0;
	for (i = 0; i < numElements; i++){
		totalSpace += (unsigned int)strlen(string_t[i]);
		totalSpace += 1;
		totalSpace += sizeof(unsigned int);
	}

 	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
 	{
 		for(i = 0; i < numElements; i++)
 		{
 			result = serializeString(string_t[i], (unsigned int)strlen(string_t[i]));
 			if(result < 0) return -1;
 		}
 	}
 	return result;
 }

 short serializeStringArrayEndianness (const char ** string_t, const unsigned int numElements, Endianness endianness)
 {
	 short result = 0;
  	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);

 	unsigned int i = 0;
 	unsigned int totalSpace = 0;
 	for (i = 0; i < numElements; i++){
 		totalSpace += (unsigned int)strlen(string_t[i]);
 		totalSpace += 1;
 		totalSpace += sizeof(unsigned int);
 	}

  	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  	{
  		for(i = 0; i < numElements; i++)
  		{
  			result = serializeStringEndianness(string_t[i], (unsigned int)strlen(string_t[i]), endianness);
  			if(result < 0) return -1;
  		}
  	}
  	return result;
 }

short serializeCharSequence (const char * char_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int totalSpace = sizeof(unsigned int) + numElements;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeCharArray(char_t, numElements);
	}
	return result;
}

short serializeCharSequenceEndianness (const char * char_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
  unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  unsigned int totalSpace = sizeof(unsigned int) + numElements;

  if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  {
 	 result = serializeUnsignedIntEndianness(numElements, endianness);
 	 if(result < 0) return -1;
 	 result = serializeCharArray(char_t, numElements);
  }
  return result;
}

short serializeCharArray (const char * char_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int totalSpace = numElements;
	unsigned int i = 0;
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

short serializeUnsignedCharSequence (const unsigned char * uchar_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int totalSpace = sizeof(unsigned int) + numElements;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedCharArray(uchar_t, numElements);
	}
	return result;
}

short serializeUnsignedCharSequenceEndianness (const unsigned char * uchar_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
  unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  unsigned int totalSpace = sizeof(unsigned int) + numElements;

  if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  {
 	 result = serializeUnsignedIntEndianness(numElements, endianness);
 	 if(result < 0) return -1;
 	 result = serializeUnsignedCharArray(uchar_t, numElements);
  }
  return result;
}

short serializeUnsignedCharArray (const unsigned char * uchar_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int totalSpace = numElements;
	unsigned int i = 0;

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

short serializeSignedCharSequence (const signed char * schar_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int totalSpace = sizeof(unsigned int) + numElements;

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeSignedCharArray(schar_t, numElements);
	}
	return result;
}

short serializeSignedCharSequenceEndianness (const signed char * schar_t, const unsigned int numElements, Endianness endianness)
{
 short result = 0;

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

short serializeSignedCharArray (const signed char * schar_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned int totalSpace = numElements;
	unsigned int i = 0;

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

short serializeShortSequence (const short * short_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeShort = sizeof(short);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeShort);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeShortArray(short_t, numElements);
	}
	return result;
}

short serializeShortSequenceEndianness (const short * short_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
  unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  unsigned short sizeShort = sizeof(short);
  unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeShort);

  if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
  {
 	 result = serializeUnsignedIntEndianness(numElements, endianness);
 	 if(result < 0) return -1;
 	 result = serializeShortArrayEndianness(short_t, numElements, endianness);
  }
  return result;
}

short serializeShortArray (const short * short_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeShort = sizeof(short);
	unsigned int totalSpace = (numElements * sizeShort);
	unsigned int i = 0;

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

short serializeShortArrayEndianness (const short * short_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
  unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
  unsigned short sizeShort = sizeof(short);
  unsigned int totalSpace = (numElements * sizeShort);
  unsigned int i = 0;

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

short serializeUnsignedShortSequence (const unsigned short * ushort_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeShort = sizeof(unsigned short);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeShort);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedShortArray(ushort_t, numElements);
	}
	return result;
}

short serializeUnsignedShortSequenceEndianness (const unsigned short * ushort_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeShort = sizeof(unsigned short);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeShort);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeUnsignedShortArrayEndianness(ushort_t, numElements, endianness);
	}
	return result;
}

short serializeUnsignedShortArray (const unsigned short * ushort_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeShort = sizeof(unsigned short);
	unsigned int totalSpace = (numElements * sizeShort);
	unsigned int i = 0;

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

short serializeUnsignedShortArrayEndianness (const unsigned short * ushort_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeShort = sizeof(unsigned short);
	unsigned int totalSpace = (numElements * sizeShort);
	unsigned int i = 0;

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

short serializeIntSequence (const int * int_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(int);
	unsigned int totalSpace = sizeInt + (numElements * sizeInt);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeIntArray(int_t, numElements);
	}
	return result;
}

short serializeIntSequenceEndianness (const int * int_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(int);
	unsigned int totalSpace = sizeInt + (numElements * sizeInt);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeIntArrayEndianness(int_t, numElements, endianness);
	}
	return result;
}

short serializeIntArray (const int * int_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(int);
	unsigned int totalSpace = (numElements * sizeInt);
	unsigned int i = 0;

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

short serializeIntArrayEndianness (const int * int_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(int);
	unsigned int totalSpace = (numElements * sizeInt);
	unsigned int i = 0;

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

short serializeUnsignedIntSequence (const unsigned int * uint_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(unsigned int);
	unsigned int totalSpace = sizeInt + (numElements * sizeInt);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedIntArray(uint_t, numElements);
	}
	return result;
}

short serializeUnsignedIntSequenceEndianness (const unsigned int * uint_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(unsigned int);
	unsigned int totalSpace = sizeInt + (numElements * sizeInt);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeUnsignedIntArrayEndianness(uint_t, numElements, endianness);
	}
	return result;
}

short serializeUnsignedIntArray (const unsigned int * uint_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(unsigned int);
	unsigned int totalSpace = (numElements * sizeInt);
	unsigned int i = 0;

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

short serializeUnsignedIntArrayEndianness (const unsigned int * uint_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeInt = sizeof(unsigned int);
	unsigned int totalSpace = (numElements * sizeInt);
	unsigned int i = 0;

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

short serializeLongSequence (const long * long_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeLongArray(long_t, numElements);
	}
	return result;
}

short serializeLongSequenceEndianness (const long * long_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeLongArrayEndianness(long_t, numElements, endianness);
	}
	return result;
}

short serializeLongArray (const long * long_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long);
	unsigned int totalSpace = (numElements * sizeLong);
	unsigned int i = 0;

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

short serializeLongArrayEndianness (const long * long_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long);
	unsigned int totalSpace = (numElements * sizeLong);
	unsigned int i = 0;

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

short serializeUnsignedLongSequence (const unsigned long * ulong_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedLongArray(ulong_t, numElements);
	}
	return result;
}

short serializeUnsignedLongSequenceEndianness (const unsigned long * ulong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeUnsignedLongArrayEndianness(ulong_t, numElements, endianness);
	}
	return result;
}

short serializeUnsignedLongArray (const unsigned long * ulong_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long);
	unsigned int totalSpace = (numElements * sizeLong);
	unsigned int i = 0;

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

short serializeUnsignedLongArrayEndianness (const unsigned long * ulong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long);
	unsigned int totalSpace = (numElements * sizeLong);
	unsigned int i = 0;

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

short serializeLongLongSequence (const long long * longlong_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long long);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeLongLongArray(longlong_t, numElements);
	}
	return result;
}

short serializeLongLongSequenceEndianness (const long long * longlong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long long);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeLongLongArrayEndianness(longlong_t, numElements, endianness);
	}
	return result;
}

short serializeLongLongArray (const long long * longlong_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long long);
	unsigned int totalSpace = (numElements * sizeLong);
	unsigned int i = 0;

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

short serializeLongLongArrayEndianness (const long long * longlong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(long long);
	unsigned int totalSpace = (numElements * sizeLong);
	unsigned int i = 0;

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

short serializeUnsignedLongLongSequence (const unsigned long long * ulonglong_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long long);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeUnsignedLongLongArray(ulonglong_t, numElements);
	}
	return result;
}

short serializeUnsignedLongLongSequenceEndianness (const unsigned long long * ulonglong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long long);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeLong);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeUnsignedLongLongArrayEndianness(ulonglong_t, numElements, endianness);
	}
	return result;
}

short serializeUnsignedLongLongArray (const unsigned long long * ulonglong_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long long);
	unsigned int totalSpace = (numElements * sizeLong);
	unsigned int i = 0;

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

short serializeUnsignedLongLongArrayEndianness (const unsigned long long * ulonglong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeLong = sizeof(unsigned long long);
	unsigned int totalSpace = (numElements * sizeLong);
	unsigned int i = 0;

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

short serializeFloatSequence (const float * float_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeFloat = sizeof(float);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeFloat);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeFloatArray(float_t, numElements);
	}
	return result;
}

short serializeFloatSequenceEndianness (const float * float_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeFloat = sizeof(float);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeFloat);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeFloatArrayEndianness(float_t, numElements, endianness);
	}
	return result;
}

short serializeFloatArray (const float * float_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeFloat = sizeof(float);
	unsigned int totalSpace = (numElements * sizeFloat);
	unsigned int i = 0;

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

short serializeFloatArrayEndianness (const float * float_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeFloat = sizeof(float);
	unsigned int totalSpace = (numElements * sizeFloat);
	unsigned int i = 0;

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

short serializeDoubleSequence (const double * double_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(double);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeDouble);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeDoubleArray(double_t, numElements);
	}
	return result;
}

short serializeDoubleSequenceEndianness (const double * double_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(double);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeDouble);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeDoubleArrayEndianness(double_t, numElements, endianness);
	}
	return result;
}

short serializeDoubleArray (const double * double_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(double);
	unsigned int totalSpace = (numElements * sizeDouble);
	unsigned int i = 0;

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

short serializeDoubleArrayEndianness (const double * double_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(double);
	unsigned int totalSpace = (numElements * sizeDouble);
	unsigned int i = 0;

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

short serializeLongDoubleSequence (const long double * longdouble_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(long double);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeDouble);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedInt(numElements);
		if(result < 0) return -1;
		result = serializeLongDoubleArray(longdouble_t, numElements);
	}
	return result;
}

short serializeLongDoubleSequenceEndianness (const long double * longdouble_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(long double);
	unsigned int totalSpace = sizeof(unsigned int) + (numElements * sizeDouble);

	if( (resize(totalSpace) == 0) || totalSpace <= freeSpace)
	{
		result = serializeUnsignedIntEndianness(numElements, endianness);
		if(result < 0) return -1;
		result = serializeLongDoubleArrayEndianness(longdouble_t, numElements, endianness);
	}
	return result;
}

short serializeLongDoubleArray (const long double * longdouble_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(long double);
	unsigned int totalSpace = (numElements * sizeDouble);
	unsigned int i = 0;

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

short serializeLongDoubleArrayEndianness (const long double * longdouble_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int freeSpace = (m_cdrBuffer->m_bufferSize - m_cdrBuffer->m_serializedBuffer);
	unsigned short sizeDouble = sizeof(long double);
	unsigned int totalSpace = (numElements * sizeDouble);
	unsigned int i = 0;

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

short deserializeStringSequence(char *** string_t, unsigned int * numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeStringSequenceEndianness(char *** string_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeStringArray (char *** string_t, const unsigned int numElements)
{
	short result = 0;

	char ** swap = malloc(numElements * sizeof(char * ));
	*string_t = malloc(numElements * sizeof(char *));

	unsigned int i = 0;
	unsigned int length = 0;
	for (i = 0; i < numElements; i++)
	{
		result = deserializeString(&swap[i], &length);
		if(result < 0) return -1;
	}
	memcpy(*string_t, swap, (numElements * sizeof(char *)));
	free(swap);
	return result;
}

short deserializeStringArrayEndianness (char *** string_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	char ** swap = malloc(numElements * sizeof(char * ));
	*string_t = malloc(numElements * sizeof(char *));

	unsigned int i = 0;
	unsigned int length = 0;
	for (i = 0; i < numElements; i++)
	{
		result = deserializeStringEndianness(&swap[i], &length, endianness);
		if(result < 0) return -1;
	}
	memcpy(*string_t, swap, (numElements * sizeof(char *)));
	free(swap);
	return result;
}

short deserializeCharSequence (char ** char_t, unsigned int * numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeCharSequenceEndianness (char ** char_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeCharArray (char ** char_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int totalSpace = numElements;
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

short deserializeUnsignedCharSequence (unsigned char ** uchar_t, unsigned int * numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeUnsignedCharSequenceEndianness (unsigned char ** uchar_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeUnsignedCharArray (unsigned char ** uchar_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int totalSpace = numElements;
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

short deserializeSignedCharSequence (signed char ** schar_t, unsigned int * numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeSignedCharSequenceEndianness (signed char ** schar_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeSignedCharArray (signed char ** char_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int totalSpace = numElements;
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

short deserializeShortSequence (short ** short_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeShortSequenceEndianness (short ** short_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeShortArray (short ** short_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeShort = sizeof(short);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int totalSpace = numElements * sizeShort;
	if(unread >= totalSpace)
	{
		*short_t = malloc(totalSpace);
		short * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeShortArrayEndianness (short ** short_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeShort = sizeof(short);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int totalSpace = numElements * sizeShort;
	if(unread >= totalSpace)
	{
		*short_t = malloc(totalSpace);
		short * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeUnsignedShortSequence (unsigned short ** ushort_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeUnsignedShortSequenceEndianness (unsigned short ** ushort_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeUnsignedShortArray (unsigned short ** ushort_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeShort = sizeof(short);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int totalSpace = numElements * sizeShort;
	if(unread >= totalSpace)
	{
		*ushort_t = malloc(totalSpace);
		unsigned short * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeUnsignedShortArrayEndianness (unsigned short ** ushort_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeShort = sizeof(short);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int totalSpace = numElements * sizeShort;
	if(unread >= totalSpace)
	{
		*ushort_t = malloc(totalSpace);
		unsigned short * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeIntSequence (int ** int_t, unsigned int * numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeIntSequenceEndianness (int ** int_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeIntArray (int ** int_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeInt;
	if(unread >= totalSpace)
	{
		*int_t = malloc(totalSpace);
		int * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeIntArrayEndianness (int ** int_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeInt;
	if(unread >= totalSpace)
	{
		*int_t = malloc(totalSpace);
		int * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeUnsignedIntSequence (unsigned int ** uint_t, unsigned int * numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeUnsignedIntSequenceEndianness (unsigned int ** int_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
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

short deserializeUnsignedIntArray (unsigned int ** uint_t, const unsigned int numElements)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeInt;
	if(unread >= totalSpace)
	{
		*uint_t = malloc(totalSpace);
		unsigned int * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeUnsignedIntArrayEndianness (unsigned int ** uint_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;
	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);
	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeInt;
	if(unread >= totalSpace)
	{
		*uint_t = malloc(totalSpace);
		unsigned int * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeLongSequence (long ** long_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeLongSequenceEndianness (long ** long_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeLongArray (long ** long_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeLong = sizeof(long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*long_t = malloc(totalSpace);
		long * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeLongArrayEndianness (long ** long_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeLong = sizeof(long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*long_t = malloc(totalSpace);
		long * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeUnsignedLongSequence (unsigned long ** ulong_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeUnsignedLongSequenceEndianness (unsigned long ** ulong_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeUnsignedLongArray (unsigned long ** ulong_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeLong = sizeof(unsigned long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*ulong_t = malloc(totalSpace);
		unsigned long * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeUnsignedLongArrayEndianness (unsigned long ** ulong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeLong = sizeof(unsigned long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*ulong_t = malloc(totalSpace);
		unsigned long * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeLongLongSequence (long long ** longlong_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeLongLongSequenceEndianness (long long ** longlong_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeLongLongArray (long long ** longlong_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeLong = sizeof(long long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*longlong_t = malloc(totalSpace);
		long long * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeLongLongArrayEndianness (long long ** longlong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeLong = sizeof(long long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*longlong_t = malloc(totalSpace);
		long long * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeUnsignedLongLongSequence (unsigned long long ** ulonglong_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeUnsignedLongLongSequenceEndianness (unsigned long long ** ulonglong_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeUnsignedLongLongArray (unsigned long long ** ulonglong_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeLong = sizeof(unsigned long long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*ulonglong_t = malloc(totalSpace);
		unsigned long long * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeUnsignedLongLongArrayEndianness (unsigned long long ** ulonglong_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeLong = sizeof(unsigned long long);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeLong;
	if(unread >= totalSpace)
	{
		*ulonglong_t = malloc(totalSpace);
		unsigned long long * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeFloatSequence (float ** float_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeFloatSequenceEndianness (float ** float_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeFloatArray (float ** float_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeFloat = sizeof(float);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeFloat;
	if(unread >= totalSpace)
	{
		*float_t = malloc(totalSpace);
		float * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeFloatArrayEndianness (float ** float_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeFloat = sizeof(float);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeFloat;
	if(unread >= totalSpace)
	{
		*float_t = malloc(totalSpace);
		float * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeDoubleSequence (double ** double_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeDoubleSequenceEndianness (double ** double_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeDoubleArray (double ** double_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeDouble = sizeof(double);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeDouble;
	if(unread >= totalSpace)
	{
		*double_t = malloc(totalSpace);
		double * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeDoubleArrayEndianness (double ** double_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeDouble = sizeof(double);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeDouble;
	if(unread >= totalSpace)
	{
		*double_t = malloc(totalSpace);
		double * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeLongDoubleSequence (long double ** longdouble_t, unsigned int * numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeLongDoubleSequenceEndianness (long double ** longdouble_t, unsigned int * numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeInt = sizeof(unsigned int);

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

short deserializeLongDoubleArray (long double ** longdouble_t, const unsigned int numElements)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeDouble = sizeof(long double);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeDouble;
	if(unread >= totalSpace)
	{
		*longdouble_t = malloc(totalSpace);
		long double * swap = malloc(totalSpace);
		unsigned int i = 0;
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

short deserializeLongDoubleArrayEndianness (long double ** longdouble_t, const unsigned int numElements, Endianness endianness)
{
	short result = 0;

	unsigned int unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;
	unsigned int sizeDouble = sizeof(long double);

	unread = m_cdrBuffer->m_serializedBuffer - m_cdrBuffer->m_iterator;

	unsigned int totalSpace = numElements * sizeDouble;
	if(unread >= totalSpace)
	{
		*longdouble_t = malloc(totalSpace);
		long double * swap = malloc(totalSpace);
		unsigned int i = 0;
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
