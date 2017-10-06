#include <microcdr/microcdr.h>
#include <stdio.h>

#define BUFFER_LENGTH 256

uint8_t buffer[BUFFER_LENGTH];

int main(int argc, char** args)
{
    // Structs for handle the buffer.
    MicroBuffer writer;
    MicroBuffer reader;

    // Initialize the MicroBuffers for working with an user-managed buffer.
    init_external_buffer(&writer, buffer, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer, BUFFER_LENGTH);

    // Serialize data
    char input[16] = "Hello microCDR!"; //16 characters
    serialize_array_char(&writer, input, 16);

    // Deserialize data
    char output[16];
    deserialize_array_char(&reader, output, 16);

    printf("Input: %s\n", input);
    printf("Output: %s\n", output);

    return 0;
}