# eProsima Micro CDR

[![Releases](https://img.shields.io/github/release/eProsima/Micro-CDR.svg)](https://github.com/eProsima/Micro-CDR/releases)
[![License](https://img.shields.io/github/license/eProsima/Micro-CDR.svg)](https://github.com/eProsima/Micro-CDR/blob/master/LICENSE)
[![Issues](https://img.shields.io/github/issues/eProsima/Micro-CDR.svg)](https://github.com/eProsima/Micro-CDR/issues)
[![Forks](https://img.shields.io/github/forks/eProsima/Micro-CDR.svg)](https://github.com/eProsima/Micro-CDR/network/members)
[![Stars](https://img.shields.io/github/stars/eProsima/Micro-CDR.svg)](https://github.com/eProsima/Micro-CDR/stargazers)

<a href="http://www.eprosima.com"><img src="https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcSd0PDlVz1U_7MgdTe0FRIWD0Jc9_YH-gGi0ZpLkr-qgCI6ZEoJZ5GBqQ" align="left" hspace="8" vspace="2" width="100" height="100" ></a>

*eProsima MicroCDR* is a *C* library implementing the *CDR* standard serialization methods.
This library is focused on embedded and resource-limited systems.

*MicroCDR* uses static buffers, and allow serializing and deserializing in both, big endianness and little endianness.

The main structure of *MicroCDR* is the `ucdrStream`.
It represents a XCDR byte stream where data is de/serialized acording to the XTYPES standard.
This structure is composed by a seft-contained linked list of raw static buffers, that is,
these buffers are used to de/serialize the data, as well as to keep the information of the linked list.

## Usage examples
This is a code example showing the serialization and deserialization of a string.
As *MicroCDR* uses a static buffer, that means the user has to provide a defined buffer and its size during the *ucdrBuffer* creation.

```c
    #include <ucdr/microcdr.h>
    #include <stdio.h>

    #define BUFFER_LENGTH 256

    int main()
    {
        // Data buffer
        uint8_t buffer[BUFFER_LENGTH];

        // Structs for handle the stream.
        ucdrStream writer;
        ucdrStream reader;

        // Initialize the MicroBuffers for working with a user-managed buffer.
        ucdr_init_stream(&writer, buffer, sizeof(buffer));
        ucdr_init_stream(&reader, buffer, sizeof(buffer));

        // Serialize data
        char input[16] = "Hello MicroCDR!"; //16 characters
        ucdr_serialize_array_char(&writer, input, 16);

        // Deserialize data
        char output[16];
        ucdr_deserialize_array_char(&reader, output, 16);

        printf("Input: %s\n", input);
        printf("Output: %s\n", output);

        return 0;
    }
```

## API functions

```c
void ucdr_init_stream(
        ucdrStream* us,
        uint8_t* buffer,
        size_t size);
```
Initializes a ucdrStream from a buffer.
 * `us`: a pointer to the ucdrStream to be initialized.
 * `buffer`: the buffer which will be associated with the ucdrStream.
 * `size`: the size of the buffer.


---

```c
void ucdr_init_stream_offset(
        ucdrStream* us,
        uint8_t* data,
        size_t size,
        size_t offset);
```
Initializes a ucdrStream from a buffer with a offset.
 * `us`: a pointer to the ucdrStream to initialize.
 * `data`: the buffer which will be associated with the ucdrStream.
 * `size`: the size of the buffer.
 * `offset`: the initial offset of the ucdrStream.

---

```c
void ucdr_init_stream_offset_endian(
        ucdrStream* us,
        uint8_t* data,
        size_t size,
        size_t offset,
        ucdrEndianness endianness);
```
Initializes a ucdrStream from a buffer with an offset and an endianness.
 * `us`: a pointer to the ucdrStream to initialize.
 * `buffer`: a pointer to the buffer which will be associated with the ucdrStream.
 * `size`: the size of the buffer.
 * `offset`: the initial offset of the ucdrStream.
 * `endianness`: the endianness of the ucdrStream.

---

```c
bool ucdr_append_buffer(
        ucdrStream* us,
        uint8_t* data,
        size_t size);
```
Appends a buffer to the ucdrStream. Multiple buffer can be linked forming a doubly linked list of buffers.
 * `us`: a pointer to the ucdrStream to which the buffer will be linked.
 * `data`: a pointer to the buffer to be linked.
 * `size`: the size of the buffer.

Returns true in case of successful buffer linking, and false in other case.

---

```c
void ucdr_reset_stream(
        ucdrStream* us);
```
Resets a ucdrStream.
 * `us`: a pointer to the ucdrStream to reset.

---

```c
size_t ucdr_size(
        const ucdrStream* us);
```
Computes the total size of the ucdrStream, that is, the sum of the linked buffers' effective size.
 * `us`: a pointer to the ucdrStream.

Returns the total size of the ucdrStream.

---

```c
size_t ucdr_used_size(
        const ucdrStream* us);
```
Computes the used size of the ucdrStream.
 * `us`: a pointer to the ucdrStream.

Returns the used size of the ucdrStream.

---

```c
size_t ucdr_remaining_size(
        const ucdrStream* us);
```
Computes the remaining size of the ucdrStream.
 * `us`: a pointer to the ucdrStream.

Returns the total size of the ucdrStream.

---

```c
ucdrEndianness ucdr_endianness(
        const ucdrStream* us);
```
Returns the endianness of the ucdrStream.

 * `us`: a pointer to the ucdrStream.

---

```c
bool ucdr_has_error(
        const ucdrStream* us);
```
Indicates whether the ucdrStream has an error.
 * `us`: a pointer to the ucdrStream.

Returns the error state of the ucdrStream.

---

```c
bool ucdr_copy_stream(
        ucdrStream* us_dest,
        const ucdrStream* us_src);
```
Copies the de/serialized data of a ucdrStream into a new one.
 * `us_dest`: a pointer to the ucdrStream to copy to.
 * `us_source`: a pointer to the ucdrStream to copy from.

Returns true in case of success copy and false in other case.

---

```c
bool ucdr_align(
        ucdrStream* us,
        size_t alignment_size);
```
Advances the XCDR stream to achieve a desired alignment.
 * `us`: a pointer to the ucdrStream to align.
 * `type_size`: size of the type to be aligned.
Returns true in case of success alignment, and false in other case.

### Serialization/deserialization functions
Adding to this, there is a big set of functions for deserialize and deserialize different kind of types:
- Basics: `bool`, `char`, `int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, `int64_t`, `uint64_t`, `float`, `double`.
```c
ucdr_serialize_<type>           (ucdrStream* us, <type> value);
ucdr_serialize_endian_<type>    (ucdrStream* us, ucdrEndianness endianness, <type> value);
ucdr_deserialize_<type>         (ucdrStream* us, <type>* value); 
ucdr_deserialize_endian_<type>  (ucdrStream* us, ucdrEndianness endianness, <type>* value);
```

- Arrays: any fixed size of basics types.
```c
ucdr_serialize_array_<type>           (ucdrStream* us, const <type>* array, size_t size);
ucdr_serialize_endian_array_<type>    (ucdrStream* us, ucdrEndianness endianness, const <type>* array, size_t size);
ucdr_deserialize_array_<type>         (ucdrStream* us, <type>* array, size_t size); 
ucdr_deserialize_endian_array_<type>  (ucdrStream* us, ucdrEndianness endianness, <type>* array, size_t size);
```

- Sequences: similar to arrays, but the information about the size is serialized along with the data.
```c
ucdr_serialize_sequence_<type>           (ucdrStream* us, const <type>* sequence, uint32_t length);
ucdr_serialize_endian_sequence_<type>    (ucdrStream* us, ucdrEndianness endianness, const <type>* sequence, uint32_t length);
ucdr_deserialize_sequence_<type>         (ucdrStream* us, <type>* sequence, size_t sequence_capacity, uint32_t* length); 
ucdr_deserialize_endian_sequence_<type>  (ucdrStream* us, ucdrEndianness endianness, <type>* sequence, size_t array_capacity, uint32_t* length);
```

- Strings: wrapper of char sequence, but easily to use.
```c
ucdr_serialize_string           (ucdrStream* us, const char* string);
ucdr_serialize_endian_string    (ucdrStream* us, ucdrEndianness endianness, const char* string);
ucdr_deserialize_string         (ucdrStream* us, char* string, size_t string_capacity);
ucdr_deserialize_endian_string  (ucdrStream* us, ucdrEndianness endianness, char* string, size_t string_capacity);
```

### Endianness
*MicroCDR* supports little and big endianness.
The **machine endianness** can be set by the cmake variable: `CONFIG_BIG_ENDIANNESS`.
By default, if this varible is `OFF` which means that the machine endianness is little endianness.

The `ucdrStream` endianness can be set by the `endianness` parameter of the structure to `UCDR_BIG_ENDIANNESS` or `UCDR_LITTLE_ENDIANNESS`.
Also, there are functions that allow to force an endianness independiently of the `ucdrStream` endianness in their serialization/deserialization.
These functions contain the name `endianness` in their signature.

### Error
All serialization/deserialization functions return a boolean indicating the result of their operations.
When a serialization/deserialization could not be possible (the type can not be serialized, or the capacity of the destination buffer is not enough),
a status error is setted into the `ucdrStream`.
If a `ucdrStream` has an error state, the next serialization/deserialization operations will not works and will return `false` in their execution.
A buffer marked with an error can be used, but any serialization/deserialization operation over it will not produce any effect.

If is kwown that an operation can fail over a `ucdrStream`, and its necessary to continue with the serialization/deserialization if it happens,
the `ucdrStream` state can be saved using the `ucdr_copy_buffer` function.
After the application of the wrong serialization/deserialization, only the `ucdrStream` that performed the operation will have a dirty state.

## Serialization/deserialization list
The available modes of serialization/deserializations in *MicroCDR* are shown in the following table.

| Type                 | Endianness |
| -------------------- | ---------- |
| bool                 |            |
| char                 |            |
| int8                 |            |
| uint8                |            |
| int16                |            |
| int16                | endianness |
| uint16               |            |
| uint16               | endianness |
| int32                |            |
| int32                | endianness |
| uint32               |            |
| uint32               | endianness |
| int64                |            |
| int64                | endianness |
| uint64               |            |
| uint64               | endianness |
| float                |            |
| float                | endianness |
| double               |            |
| double               | endianness |
| string               |            |
| string               | endianness |
| bool array           |            |
| char array           |            |
| int8 array           |            |
| uint8 array          |            |
| int16 array          |            |
| int16 array          | endianness |
| uint16 array         |            |
| uint16 array         | endianness |
| int32 array          |            |
| int32 array          | endianness |
| uint32 array         |            |
| uint32 array         | endianness |
| int64 array          |            |
| int64 array          | endianness |
| uint64 array         |            |
| uint64 array         | endianness |
| float array          |            |
| float array          | endianness |
| double array         |            |
| double array         | endianness |
| bool sequence        |            |
| bool sequence        | endianness |
| char sequence        |            |
| char sequence        | endianness |
| int8 sequence        |            |
| int8 sequence        | endianness |
| uint8 sequence       |            |
| uint8 sequence       | endianness |
| int16 sequence       |            |
| int16 sequence       | endianness |
| uint16 sequence      |            |
| uint16 sequence      | endianness |
| int32 sequence       |            |
| int32 sequence       | endianness |
| uint32 sequence      |            |
| uint32 sequence      | endianness |
| int64 sequence       |            |
| int64 sequence       | endianness |
| uint64 sequence      |            |
| uint64 sequence      | endianness |
| float sequence       |            |
| float sequence       | endianness |
| double sequence      |            |
| double sequence      | endianness |

## Additional features
### Endianness
*MicroCDR* supports little and big endianness.
The configuration can be done by cmake with the cmake `__BIG_ENDIAN__` variable.
A `0` value implies that the serialization will be performed into a little endian machine, and `1` into a big endian machine.

The default endianness serialization can be choosen by setting the `endianness` parameter of a `ucdrBuffer`  to `UCDR_BIG_ENDIANNESS` or `UCDR_LITTLE_ENDIANNESS`.
Also, there are functions that allow to force an endianness in their serialization/deserialization.
These functions contain the name `endiannness` in their signature.

### Error
All serialization/deserialization functions return a boolean indicating the result of their operations.
When a serialization/deserialization could not be possible (the type can not be serialized, or the capacity of the destination buffer is not enough),
a status error is setted into the `ucdrBuffer`.
If a `ucdrBuffer` has an error state, the next serialization/deserialization operations will not work and will return `false` in their execution.
A buffer marked with an error can be used, but any serialization/deserialization operation over it will not produce any effect.

If is kwown that an operation can fail over a `ucdrBuffer`, and its necessary to continue with the serialization/deserialization if it happens,
the `ucdrBuffer` state can be saved using the `ucdr_copy_buffer` function.
After the application of the wrong serialization/deserialization, only the `ucdrBuffer` that performed the operation will have a dirty state.

