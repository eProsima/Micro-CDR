# eProsima microCDR

<a href="http://www.eprosima.com"><img src="https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcSd0PDlVz1U_7MgdTe0FRIWD0Jc9_YH-gGi0ZpLkr-qgCI6ZEoJZ5GBqQ" align="left" hspace="8" vspace="2" width="100" height="100" ></a>

*eProsima MicroCDR* is a *C* library implementing the *CDR* standard serialization methods.
This library is focused on embedded and resource-limited systems.

*MicroCDR* uses a static buffer, and allow to serialize and deserialize in both, big endianness and little endianness.

## Usage examples
This is a code example showing the serialization and deserialization of a string.
As *MicroCDR* uses a static buffer, that means the user has to provide a defined buffer and its size during the *MicroBuffer* creation.

```c
    #include <microcdr/microcdr.h>
    #include <stdio.h>

    #define BUFFER_LENGTH 256

    int main(int argc, char** args)
    {
        // Data buffer
        uint8_t buffer[BUFFER_LENGTH];

        // Structs for handle the buffer.
        MicroBuffer writer;
        MicroBuffer reader;

        // Initialize the MicroBuffers for working with an user-managed buffer.
        init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
        init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

        // Serialize data
        char input[16] = "Hello MicroCDR!"; //16 characters
        serialize_array_char(&writer, input, 16);

        // Deserialize data
        char output[16];
        deserialize_array_char(&reader, output, 16);

        printf("Input: %s\n", input);
        printf("Output: %s\n", output);

        return 0;
    }
```

## API functions

```c
void init_micro_buffer        (MicroBuffer* mb, uint8_t* data, const uint32_t size);
void init_micro_buffer_offset (MicroBuffer* mb, uint8_t* data, const uint32_t size, uint32_t offset);
```
Initialize a `MicroBuffer` structure, the main struct of *MicroCDR*.
- `mb`: the `MicroBuffer` struct
- `data`: the buffer that the `MicroBuffer` will use.
- `size`: the size of the buffer that the `MicroBuffer` will use.
- `offset`: where the serialization/deserialization will start.
Initially, the serialization/deserialization starts at the beginning of the buffer.

---

```c
void reset_micro_buffer       (MicroBuffer* mb);
void reset_micro_buffer_offset(MicroBuffer* mb, const uint32_t offset);
```
Reset the `MicroBuffer` as the same state that it was created.
- `mb`: the `MicroBuffer` struct
- `offset`: where the serialization/deserialization will start.
Initially, the serialization/deserialization starts at the beginning of the buffer.

---

```c
void align_to         (MicroBuffer* mb, const uint32_t alignment);
```
Align the MicroBuffer to an `alignment` position.
After call this function, the serialization pointer will be moved only if the current `MicroBuffer` was not aligment to the passed value.

- `mb`: the `MicroBuffer` struct
- `alignment`: the alignment value used.

---

```c
uint32_t get_alignment(uint32_t buffer_position, const uint32_t data_size);
```
Returns the aligment necessary to serialize/deserialize a type with `data_size` size.

- `buffer_position`: the current serialization/deserialization position of the `MicroBuffer`. (Typically  `mb->iterator - mb->init`).
- `data_size`: the bytes of the data that you are asking for.

---

```c
size_t micro_buffer_size(const MicroBuffer* mb);
```
Returns the memory size of the buffer.
- `mb`: the `MicroBuffer` struct

---

```c
size_t micro_buffer_length(const MicroBuffer* mb);
```
Returns the size of the serialized/deserialized data.
- `mb`: the `MicroBuffer` struct

---

```c
size_t micro_buffer_remaining(const MicroBuffer* mb);
```
Returns the remaining size for the serializing/deserializing.
- `mb`: the `MicroBuffer` struct


### Serialization/deserialization functions
Adding to this, there is a big set of functions for deserialize and deserialize different kind of types:
- Basics: `bool`, `char`, `int8_t`, `uint8_t`,`int16_t`, `uint16_t`,`int32_t`, `uint32_t`,`int64_t`, `uint64_t`,`float`, `double`.
- Arrays: Any fixed size of basics types.
- Sequence: Similar to arrays, but the information about the size is serialized along with the data.

### Endianness
*MicroCDR* supports little and big endianness.
The configuration can be done by cmake with the cmake `__BIG_ENDIAN__` variable.
A `0` value implies that the serialization will performed into a little endian machine, and `1` into a big endian machine.

The default endianness serialization can be choosen by setting the `endianness` parameter of a `MicroBuffer`  to `BIG_ENDIANNESS` or `LITTLE_ENDIANNESS`.
Also, there are a functions that allow to force an endianness in their serialization/deserialization.
These functions contains the name `endiannness` in their signature.

## Serialization/deserialization list
The avaialble modes of serialization/deserializations in *MicroCDR* are shown in the following table.


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

