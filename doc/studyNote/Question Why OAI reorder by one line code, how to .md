# Question: Why OAI reorder by one line code, how to do it?

Start Date: 2024/05/13
Summary: Reordering OAI using a one-line code to extract the highest 8 bits from a uint32_t integer in Little Endian format.
Status: Done
Assign: Ming 咚咚 [銘鴻]

```c
    // get MIB every 8 frames
    if(((slotP == 0) && (frameP & 7) == 0) ||
       gNB->first_MIB) {
      int mib_sdu_length = encode_mib(cc->mib, frameP, cc->MIB_pdu, sizeof(cc->MIB_pdu));

      // flag to avoid sending an empty MIB in the first frames of execution since gNB doesn't get at the beginning in frame 0 slot 0
      gNB->first_MIB = false;

      LOG_D(MAC,
            "[gNB %d] Frame %d : MIB->BCH  CC_id %d, Received %d bytes\n",
            module_idP,
            frameP,
            CC_id,
            mib_sdu_length);
    }

    uint32_t mib_pdu = (*(uint32_t *)cc->MIB_pdu) & ((1 << 24) - 1);
```

<aside>
🗣 [Question: Why `OAI` reorder by one line code, how to do it?](Question%20Why%20OAI%20reorder%20by%20one%20line%20code,%20how%20to%20%20121100983143818397a3c4ea0d65ee73.md) 
`uint32_t mib_pdu = (*(uint32_t *)cc->MIB_pdu) & ((1 << 24) - 1);`

</aside>

### C Code Explanation:

The line of code `uint32_t mib_pdu = (*(uint32_t *)cc->MIB_pdu) & ((1 << 24) - 1);` aims to extract the highest 8 bits from the memory location pointed to by `cc->MIB_pdu`, treating it as a `uint32_t` integer, and setting all other bits to zero. This is achieved through bitwise AND and left bit shifting operations.

Breaking down the code:

1. `(uint32_t *)cc->MIB_pdu`: This portion casts the pointer `cc->MIB_pdu` to a `uint32_t` pointer and then dereferences it, obtaining the `uint32_t` integer value stored at that memory address.
2. `((1 << 24) - 1)`: This segment creates a 32-bit integer with only the highest 8 bits set to 1 and all other bits set to 0. It does so by left shifting 1 by 24 bits and then subtracting 1.
3. `&`: This is the bitwise AND operator, used to perform bitwise AND operations between two binary values.

Thus, the entire line of code aims to read a `uint32_t` integer value from the memory location pointed to by `cc->MIB_pdu` and retain only its highest 8 bits, setting all other bits to zero.

### Little Endian:

In the context of the C code provided, Little Endian refers to the byte ordering scheme used in the system. In Little Endian systems, such as x86-based architectures, the least significant byte (LSB) of a multi-byte data type is stored at the lowest memory address, while the most significant byte (MSB) is stored at the highest memory address.

For example, if `cc->MIB_pdu` contains `[0xAB, 0xCD, 0xEF]` in memory, in a Little Endian system, it would be interpreted as `0xEFCDAB00` when treated as a 32-bit integer. This byte ordering can lead to the reversal of index order when accessing multi-byte data types in memory, which is why the index order appears reversed when extracting the highest 8 bits in the provided code snippet.

![Untitled](Untitled%2070.png)

```
[MAC]   cc->MIB_pdu (%x) [0] [1] [2] [3]: 1 6 6 64
[MAC]   (*(uint32_t *)cc->MIB_pdu): 0x64060601
[MAC]   (*(uint32_t *)cc->MIB_pdu) & ((1 << 24) - 1): 0x60601
[MAC]   uint32_t mib_pdu: 0x60601
```