#include <nanocdr/nanoCdr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main (int argc, const char* argv[])
{
	printf("----> Create a Dynamic Buffer\n");

/*
	unsigned int sizeBuffer = 487;
	char * buffer;
	mallocCdr((void *)&buffer, sizeBuffer);
	newStaticBuffer(buffer, sizeBuffer);
*/

	newDynamicBuffer();

	//changeEndianness(LITTLE_ENDIANNESS);

	printf("\nSERIALIZE basic\n\n");

	char char_in = 'b';
	printf("----> char: %c\n", char_in);
	serializeChar(char_in);

	unsigned char uchar_in = 'b';
	printf("----> uchar: %c\n", uchar_in);
	serializeChar(uchar_in);

	signed char schar_in = 'b';
	printf("----> schar: %c\n", schar_in);
	serializeChar(schar_in);

	char string_in[25] = "En un lugar de la mancha";
	printf("----> string: %s .\n", string_in);
	serializeString(string_in, strlen(string_in));

	short short_in = -256;
	printf("----> short: %d\n", short_in);
	serializeShort(short_in);

	unsigned short ushort_in = 256;
	printf("----> ushort: %d\n", ushort_in);
	serializeUnsignedShort(ushort_in);

	int int_in = -2549;
	printf("----> int: %d\n", int_in);
	serializeInt(int_in);

	unsigned uint_in = 2549;
	printf("----> uint: %d\n", uint_in);
	serializeUnsignedInt(uint_in);

	long long_in = -25564852;
	printf("----> long: %ld\n", long_in);
	serializeLong(long_in);

	unsigned long ulong_in = 25564852;
	printf("----> ulong: %ld\n", ulong_in);
	serializeUnsignedLong(ulong_in);

	long long longlong_in = -25564852;
	printf("----> long long: %lld\n", longlong_in);
	serializeLong(longlong_in);

	unsigned long long ulonglong_in = 25564852;
	printf("----> ulonglong: %lld\n", ulonglong_in);
	serializeUnsignedLongLong(ulonglong_in);

	float float_in = 256.25;
	printf("----> float: %f\n", float_in);
	serializeFloat(float_in);

	double double_in = 125256.25;
	printf("----> double: %lf\n", double_in);
	serializeDouble(double_in);

	long double longdouble_in = 125256.25;
	printf("----> long double: %LF\n", longdouble_in);
	serializeLongDouble(longdouble_in);

	printf("\nSERIALIZE Sequences\n\n");

	char *a[2];
	a[0] = "en un lugar de la mancha";
	a[1] = "en un lugar de la mancha";
	printf("----> stringSequence\n");
	serializeStringSequence(a,2);

	char SequenceChar[10] = {'a','b','c','d','e','f','h','j','u','p'};
	printf("----> charSequence\n");
	serializeCharSequence(SequenceChar, 10);

	unsigned char SequenceUChar[10] = {'a','b','c','d','e','f','h','j','u','p'};
	printf("----> uCharSequence\n");
	serializeUnsignedCharSequence(SequenceUChar, 10);

	signed char SequenceSChar[10] = {'a','b','c','d','e','f','h','j','u','p'};
	printf("----> sCharSequence\n");
	serializeSignedCharSequence(SequenceSChar, 10);

	short SequenceShort[10] = {1,2,3,4,5,6,-7,8,9,-10};
	printf("----> shortSequence\n");
	serializeShortSequence(SequenceShort, 10);

	unsigned short SequenceUShort[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("----> ushortSequence\n");
	serializeUnsignedShortSequence(SequenceUShort, 10);

	int SequenceInt[10] = {1,2,3,4,5,6,-7,8,9,-10};
	printf("----> intSequence\n");
	serializeIntSequence(SequenceInt, 10);

	unsigned int SequenceUInt[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("----> uintSequence\n");
	serializeUnsignedIntSequence(SequenceUInt, 10);

	long SequenceLong[10] = {1,2,3,4,5,-6,7,8,9,-10};
	printf("----> longSequence\n");
	serializeLongSequence(SequenceLong, 10);

	unsigned long SequenceULong[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("----> ulongSequence\n");
	serializeUnsignedLongSequence(SequenceULong, 10);

	long long SequenceLongLong[10] = {1,2,3,4,5,-6,7,8,9,-10};
	printf("----> longlongSequence\n");
	serializeLongLongSequence(SequenceLongLong, 10);

	unsigned long long SequenceULongLong[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("----> ulonglongSequence\n");
	serializeUnsignedLongLongSequence(SequenceULongLong, 10);

	float SequenceFloat[10] = {1.0,2.0,3.0,4.0,5.0,6.0,-7.0,8.0,9.0,-10.0};
	printf("----> floatSequence\n");
	serializeFloatSequence(SequenceFloat, 10);

	double SequenceDouble[10] = {1.0,2.0,3.0,4.0,5.0,6.0,-0.7,8.0,9.0,-10.0};
	printf("----> doubleSequence\n");
	serializeDoubleSequence(SequenceDouble, 10);

	long double SequenceLongDouble[10] = {1.0,2.0,3.0,4.0,5.0,6.0,-0.7,8.0,9.0,-10.0};
	printf("----> longdoubleSequence\n");
	serializeLongDoubleSequence(SequenceLongDouble, 10);

	printf("\nSERIALIZED DATA: %d\n\n", getSerializedDataLength());

	printf("DESERIALIZE basics\n");

	char char_out;
	deserializeChar(&char_out);
	printf("<---- char: %c\n", char_out);

	unsigned char uchar_out;
	deserializeUnsignedChar(&uchar_out);
	printf("<---- uchar: %c\n", uchar_out);

	signed char schar_out;
	deserializeSignedChar(&schar_out);
	printf("<---- schar: %c\n", schar_out);

	char * string_out;
	unsigned int string_length;
	deserializeString(&string_out, &string_length);
	printf("<---- string %s . strlen %d\n", string_out, string_length);

	short short_out;
	deserializeShort(&short_out);
	printf("<---- short: %d\n", short_out);

	unsigned short ushort_out;
	deserializeUnsignedShort(&ushort_out);
	printf("<---- ushort: %d\n", ushort_out);

	int int_out;
	deserializeInt(&int_out);
	printf("<---- int: %d\n", int_out);

	unsigned uint_out;
	deserializeUnsignedInt(&uint_out);
	printf("<---- uint: %d\n", uint_out);

	long long_out;
	deserializeLong(&long_out);
	printf("<---- long: %ld\n", long_out);

	unsigned long ulong_out;
	deserializeUnsignedLong(&ulong_out);
	printf("<---- ulong: %ld\n", ulong_out);

	long long longlong_out;
	deserializeLongLong(&longlong_out);
	printf("<---- long long: %lld\n", longlong_out);

	unsigned long long ulonglong_out;
	deserializeUnsignedLongLong(&ulonglong_out);
	printf("<---- ulong: %lld\n", ulonglong_out);

	float float_out;
	deserializeFloat(&float_out);
	printf("<---- float: %f\n", float_out);

	double double_out;
	deserializeDouble(&double_out);
	printf("<---- double: %lf\n", double_out);

	long double longdouble_out;
	deserializeLongDouble(&longdouble_out);
	printf("<---- long double: %LF\n", longdouble_out);

	printf("DESERIALIZE Sequence\n");

	char ** a_out;
	printf("<---- stringSequence\n");
	//unsigned int length1;
	unsigned int length;
	deserializeStringSequence(&a_out, &length);
	//deserializeString(&a_out[0],&length1);
	//deserializeString(&a_out[1],&length2);
	printf("<---- %s\n", a_out[0]);
	printf("<---- %s\n", a_out[1]);

	//printf("<---- %s\n", a_out[1]);

	free(a_out[0]);
	free(a_out[1]);
	free(a_out);


	char * charSequence_out;
	unsigned int charSequence_length;
	deserializeCharSequence(&charSequence_out, &charSequence_length);
	printf("<---- charSequence\n");

	unsigned char * ucharSequence_out;
	unsigned int ucharSequence_length;
	deserializeUnsignedCharSequence(&ucharSequence_out, &ucharSequence_length);
	printf("<---- ucharSequence\n");

	signed char * scharSequence_out;
	unsigned int scharSequence_length;
	deserializeSignedCharSequence(&scharSequence_out, &scharSequence_length);
	printf("<---- scharSequence\n");

	short * shortSequence_out;
	unsigned int shortSequence_length;
	deserializeShortSequence(&shortSequence_out, &shortSequence_length);
	printf("<---- shortSequence\n");

	unsigned short * uShortSequence_out;
	unsigned int uShortSequence_length;
	deserializeUnsignedShortSequence(&uShortSequence_out, &uShortSequence_length);
	printf("<---- uShortSequence\n");

	int * intSequence_out;
	unsigned int intSequence_length;
	deserializeIntSequence(&intSequence_out, &intSequence_length);
	printf("<---- intSequence\n");

	unsigned int * uIntSequence_out;
	unsigned int uIntSequence_length;
	deserializeUnsignedIntSequence(&uIntSequence_out, &uIntSequence_length);
	printf("<---- intSequence\n");

	long * longSequence_out;
	unsigned int longSequence_length;
	deserializeLongSequence(&longSequence_out, &longSequence_length);
	printf("<---- longSequence\n");

	unsigned long * uLongSequence_out;
	unsigned int uLongSequence_length;
	deserializeUnsignedLongSequence(&uLongSequence_out, &uLongSequence_length);
	printf("<---- uLongSequence\n");

	long long * longlongSequence_out;
	unsigned int longlongSequence_length;
	deserializeLongLongSequence(&longlongSequence_out, &longlongSequence_length);
	printf("<---- longlongSequence\n");

	unsigned long long * uLongLongSequence_out;
	unsigned int uLongLongSequence_length;
	deserializeUnsignedLongLongSequence(&uLongLongSequence_out, &uLongLongSequence_length);
	printf("<---- uLongLongSequence\n");

	float * floatSequence_out;
	unsigned int floatSequence_length;
	deserializeFloatSequence(&floatSequence_out, &floatSequence_length);
	printf("<---- floatSequence\n");

	double * doubleSequence_out;
	unsigned int doubleSequence_length;
	deserializeDoubleSequence(&doubleSequence_out, &doubleSequence_length);
	printf("<---- doubleSequence\n");

	long double * longdoubleSequence_out;
	unsigned int longdoubleSequence_length;
	deserializeLongDoubleSequence(&longdoubleSequence_out, &longdoubleSequence_length);
	printf("<---- longdoubleSequence\n");

	printf("Cheking results....\n\n\n");

	if(char_in == char_out) printf("Char \t OK\n");
	else printf("Char \t FAIL\n");

	if(uchar_in == uchar_out) printf("UChar \t OK\n");
	else printf("UChar \t FAIL\n");

	if(schar_in == schar_out) printf("SChar \t OK\n");
	else printf("SChar \t FAIL\n");

	if(string_length == strlen(string_in))
	{
		printf("Strlen \t OK\n");
		if(strcmp(string_in, string_out) == 0) printf("String \t OK\n");
		else printf("String \t FAIL\n");
	}
	else
	{
		printf("Strlen \t FAIL\n");
	}

	if(short_in == short_out) printf("Short \t OK\n");
	else printf("Short \t FAIL\n");

	if(ushort_in == ushort_out) printf("UShort \t OK\n");
	else printf("UShort \t FAIL\n");

	if(int_in == int_out) printf("Int \t OK\n");
	else printf("Int \t FAIL\n");

	if(uint_in == uint_out) printf("UInt \t OK\n");
	else printf("UInt \t FAIL\n");

	if(long_in == long_out) printf("Long \t OK\n");
	else printf("Long \t FAIL\n");

	if(ulong_in == ulong_out) printf("ULong \t OK\n");
	else printf("ULong \t FAIL\n");

	if(longlong_in == longlong_out) printf("LongLong \t OK\n");
	else printf("LongLong \t FAIL\n");

	if(ulonglong_in == ulonglong_out) printf("ULongLong \t OK\n");
	else printf("ULongLong \t FAIL\n");

	if(float_in == float_out) printf("Float \t OK\n");
	else printf("Float \t FAIL\n");

	if(double_in == double_out) printf("Double \t OK\n");
	else printf("Double \t FAIL\n");

	if(longdouble_in == longdouble_out) printf("LongDouble \t OK\n");
	else printf("LongDouble \t FAIL\n");

	printf("\n");

	if(charSequence_length == 10)
	{
		printf("Char Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceChar[i] != charSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("Char Sequence Content \t OK\n");
		else printf("Char Sequence Content \t FAIL\n");
	}else
	{
		printf("Char Sequence Length \t FAIL\n");
	}

printf("\n");

	if(ucharSequence_length == 10)
	{
		printf("UChar Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceUChar[i] != ucharSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("UChar Sequence Content \t OK\n");
		else printf("UChar Sequence Content \t FAIL\n");
	}else
	{
		printf("UChar Sequence Length \t FAIL\n");
	}

	if(scharSequence_length == 10)
	{
		printf("SChar Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceSChar[i] != scharSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("SChar Sequence Content \t OK\n");
		else printf("SChar Sequence Content \t FAIL\n");
	}else
	{
		printf("SChar Sequence Length \t FAIL\n");
	}

	printf("\n");

	if(shortSequence_length == 10)
	{
		printf("Short Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceShort[i] != shortSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("Short Sequence Content \t OK\n");
		else printf("Short Sequence Content \t FAIL\n");
	}else
	{
		printf("Short Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(uShortSequence_length == 10)
	{
		printf("UShort Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceUShort[i] != uShortSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("UShort Sequence Content \t OK\n");
		else printf("UShort Sequence Content \t FAIL\n");
	}else
	{
		printf("UShort Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(intSequence_length == 10)
	{
		printf("Int Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceInt[i] != intSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("Int Sequence Content \t OK\n");
		else printf("Int Sequence Content \t FAIL\n");
	}else
	{
		printf("Int Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(uIntSequence_length == 10)
	{
		printf("UInt Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceUInt[i] != uIntSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("UInt Sequence Content \t OK\n");
		else printf("UInt Sequence Content \t FAIL\n");
	}else
	{
		printf("UInt Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(longSequence_length == 10)
	{
		printf("Long Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceLong[i] != longSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("Long Sequence Content \t OK\n");
		else printf("Long Sequence Content \t FAIL\n");
	}else
	{
		printf("Long Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(uLongSequence_length == 10)
	{
		printf("ULong Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceULong[i] != uLongSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("ULong Sequence Content \t OK\n");
		else printf("ULong Sequence Content \t FAIL\n");
	}else
	{
		printf("ULong Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(longlongSequence_length == 10)
	{
		printf("Long Long Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceLongLong[i] != longlongSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("Long Long Sequence Content \t OK\n");
		else printf("Long Long Sequence Content \t FAIL\n");
	}else
	{
		printf("Long Long Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(floatSequence_length == 10)
	{
		printf("Float Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceFloat[i] != floatSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("Float Sequence Content \t OK\n");
		else printf("Float Sequence Content \t FAIL\n");
	}else
	{
		printf("Float Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(doubleSequence_length == 10)
	{
		printf("Double Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceDouble[i] != doubleSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("Double Sequence Content \t OK\n");
		else printf("Double Sequence Content \t FAIL\n");
	}else
	{
		printf("Double Sequence Length \t FAIL\n");
	}
	printf("\n");

	if(longdoubleSequence_length == 10)
	{
		printf("Long Double Sequence Length \t OK\n");
		int i = 0;
		short result = 0;
		for(i = 0; i < 10;i++)
		{
			if(SequenceLongDouble[i] != longdoubleSequence_out[i])
				result = -1;
		}
		if(result == 0) printf("Long Double Sequence Content \t OK\n");
		else printf("Long Double Sequence Content \t FAIL\n");
	}else
	{
		printf("Long Double Sequence Length \t FAIL\n");
	}

	printf("\n");

	freeCdr((void *)&string_out);
	freeCdr((void *)&charSequence_out);
	freeCdr((void *)&scharSequence_out);
	freeCdr((void *)&ucharSequence_out);
	freeCdr((void *)&shortSequence_out);
	freeCdr((void *)&uShortSequence_out);
	freeCdr((void *)&intSequence_out);
	freeCdr((void *)&uIntSequence_out);
	freeCdr((void *)&longSequence_out);
	freeCdr((void *)&uLongSequence_out);
	freeCdr((void *)&floatSequence_out);
	freeCdr((void *)&doubleSequence_out);
	freeCdr((void *)&longlongSequence_out);
	freeCdr((void *)&uLongLongSequence_out);
	freeCdr((void *)&longdoubleSequence_out);

	printf("\n\n----> Destroy the Dynamic Buffer\n");
	//freeCdr((void *)&buffer);
	destroyBuffer();
}
