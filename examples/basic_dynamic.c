#include <microcdr/microcdr.h>
#include <stdio.h>

#define BUFFER_LENGTH 256
#define INITIAL_BUFFER_LENGTH 8

uint8_t buffer[BUFFER_LENGTH];

int main(int argc, char** args)
{
    // Structs for handle the buffer.
    MicroBuffer writer;
    MicroBuffer reader;

    // The writer will be managed dynamically by the library.
    init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

    // Serialize data
    char input[16] = "Hello microCDR!"; //16 characters
    serialize_array_char(&writer, input, 16);


    // The reader will read from the writer-managed buffer.
    init_external_buffer(&reader, writer.init, writer.final - writer.init);

    // Deserialize data
    char output[16];
    deserialize_array_char(&reader, output, 16);

    // Free internal buffer of the writer.
    free_internal_buffer(&writer);

    printf("Input: %s\n", input);
    printf("Output: %s\n", output);

    return 0;
}