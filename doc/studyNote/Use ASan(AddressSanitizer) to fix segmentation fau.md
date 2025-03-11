# Use ASan(AddressSanitizer) to fix segmentation faults

Start Date: 2024/09/25
Summary: Fix segmentation faults in the OSC DU High execution by using AddressSanitizer to identify and resolve heap buffer overflows during memory allocation.
Status: Done
Assign: Ming 咚咚 [銘鴻]

# Problem Definition

<aside>
💡

When executing OSC DU High, a segmentation fault often occurs during memory allocation (DU_ALLOC).

**Fix:** Refer to the document on [**Fix: E2AP Blockage During E2 Setup Request Build**](Fix%20E2AP%20Blockage%20During%20E2%20Setup%20Request%20Build%201211009831438136b428fa8de1a96aad.md) for resolution.

</aside>

## ASan（AddressSanitizer）

How to use: [**Debugging Intermittent Memory Issues in C Code**](Debugging%20Intermittent%20Memory%20Issues%20in%20C%20Code%2012110098314381e8af07d2e1cc058382.md) 

```jsx
</BCCH-DL-SCH-Message>

encbufSize: 87
64      ffffff80        a       2       8       0       ffffff80        40      0       0       40      0       0       0       6       ffffff90        ffffff84        ffffffd0        56 00       26      ffffff96        70      ffffffcb        35      ffffffde      1       ffffffb8        20      10      0       0       40      40      0       20      ffffffd2        14 dffffff87        21      ffffffd3        30      0       8       0       0       ffffff9a        72      73      ffffff86        59      ffffff95    18      ffffff80        6       ffffffb5    33      5f      72      70      12      4e      71      2a      63      5b      ffffffc6        ffffffa9        ffffff8d        52      5c      2e      0       50      ffffffe1   ffffffd0 8       2c      7       60      12      23      37      ffffffb1        c

[DU UTILS] --> Gen Buffer
[DU UTILS] --> Gen Buffer
[DU UTILS] --> Gen Buffer
[DU UTILS] --> Gen Buffer
[DU UTILS] --> Gen Buffer
=================================================================
==229442==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x603000000120 at pc 0x714fa5067f3d bp 0x7fffe9dfd860 sp 0x7fffe9dfd008
WRITE of size 200 at 0x603000000120 thread T0
    #0 0x714fa5067f3c in __interceptor_memset ../../../../src/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:762
    #1 0x64a06c791cc5 in BuildMibPdu /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_sys_info_hdl.c:190
    #2 0x64a06c6bb60a in readMacCfg /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_cfg.c:243
    #3 0x64a06c6c1f3e in readCfg /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_cfg.c:1222
    #4 0x64a06c6c40c9 in duReadCfg /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_cfg.c:1415
    #5 0x64a06c77fcc2 in tst /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_mgr_main.c:782
    #6 0x64a06ca17a71 in SInit /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/ss_gen.c:650
    #7 0x64a06c85dfd0 in main /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:1014
    #8 0x714fa4829d8f  (/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)
    #9 0x714fa4829e3f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x29e3f)
    #10 0x64a06c32c764 in _start (/home/hpe/mwnl-odu-at-oai-based-on-scf/l2/bin/odu/odu+0xb11764)

0x603000000120 is located 0 bytes to the right of 32-byte region [0x603000000100,0x603000000120)
allocated by thread T0 here:
    #0 0x714fa510dc3e in __interceptor_realloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:163
    #1 0x64a06c61c7ee in asn_set_add /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/codec_utils/common/asn_SET_OF.c:27
    #2 0x64a06c7931ea in BuildPlmnList /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_sys_info_hdl.c:457
    #3 0x64a06c79edd2 in BuildSib1Msg /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_sys_info_hdl.c:2500
    #4 0x64a06c6c1c3c in readCfg /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_cfg.c:1208
    #5 0x64a06c6c40c9 in duReadCfg /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_cfg.c:1415
    #6 0x64a06c77fcc2 in tst /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_mgr_main.c:782
    #7 0x64a06ca17a71 in SInit /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/ss_gen.c:650
    #8 0x64a06c85dfd0 in main /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:1014
    #9 0x714fa4829d8f  (/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)

SUMMARY: AddressSanitizer: heap-buffer-overflow ../../../../src/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:762 in __interceptor_memset
Shadow bytes around the buggy address:
  0x0c067fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c067fff8000: fa fa 00 00 00 fa fa fa 00 00 04 fa fa fa 00 00
  0x0c067fff8010: 04 fa fa fa 00 00 04 fa fa fa 00 00 04 fa fa fa
=>0x0c067fff8020: 00 00 00 00[fa]fa 00 00 00 00 fa fa 00 00 00 00
  0x0c067fff8030: fa fa 00 00 00 00 fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8060: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c067fff8070: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==229442==ABORTING
```

### AddressSanitizer Output Analysis

The log you provided from AddressSanitizer highlights a **heap buffer overflow** during the execution of your program. Here’s a breakdown of the analysis based on the error:

### **Key Findings:**

1. **Heap Buffer Overflow**:
The main issue is a **heap-buffer-overflow** in `memset`. The program is writing beyond the bounds of an allocated memory region:
    
    ```
    ERROR: AddressSanitizer: heap-buffer-overflow on address 0x603000000120 at pc 0x714fa5067f3d bp 0x7fffe9dfd860 sp 0x7fffe9dfd008
    WRITE of size 200 at 0x603000000120
    
    ```
    
    - The overflow happens in `__interceptor_memset`, which is part of AddressSanitizer’s intercepted memory functions. It appears when calling `memset` in the function `BuildMibPdu`.
    - The address `0x603000000120` is **0 bytes beyond** the allocated 32-byte region (`[0x603000000100, 0x603000000120)`), meaning the write operation extends outside of the allocated block.
2. **Offending Functions**:
The trace shows the sequence of function calls leading to the error:
    - `BuildMibPdu` at `du_sys_info_hdl.c:190` seems to be the primary location where the buffer overflow is triggered. This is where `memset` is being used to clear or initialize a buffer.
    - The problem arises when trying to write 200 bytes to a memory region that was only allocated 32 bytes.

### **What Happened:**

The program is attempting to write more data than was allocated for the buffer. Specifically, `memset` is trying to clear or initialize 200 bytes, but the allocated buffer is only 32 bytes long. This results in writing beyond the memory boundaries and causes the **heap buffer overflow**.

### **Backtrace Breakdown**:

1. **BuildMibPdu**:
    - The first function in the trace, located in `du_sys_info_hdl.c:190`, is responsible for building the MIB PDU. The issue likely lies in this function where the memory is allocated and managed incorrectly, leading to an overflow during `memset`.
2. **asn_set_add** in `asn_SET_OF.c:27`:
    - This function handles ASN.1 encoding, and it’s possible that during this process, memory is incorrectly sized or reallocated, causing the problem later in `BuildMibPdu`.
3. **BuildSib1Msg**:
    - This function is responsible for building the SIB1 message, which is closely related to MIB. The incorrect memory handling might have originated here or propagated from other parts of the system.

### **Steps to Fix**:

1. **Check Memory Allocation**:
    - In the `BuildMibPdu` function, carefully check the memory allocation for buffers. Ensure that the size of the allocated memory is sufficient for the amount of data being written by `memset`. Specifically, for any `memset` operation writing 200 bytes, ensure that at least 200 bytes have been allocated.
2. **Inspect Buffer Usage**:
    - Trace the flow of the buffer starting from allocation. Make sure the buffer is not being reused or incorrectly resized, especially in related functions like `BuildSib1Msg` or `asn_set_add`.
3. **Use Dynamic Bounds Checking**:
    - You can use AddressSanitizer with bounds checking enabled (`fsanitize=bounds`) to catch more such errors during buffer usage.
4. **Fix Overwrites**:
    - Review all buffer-handling code in the functions mentioned (`BuildMibPdu`, `BuildSib1Msg`, `asn_set_add`) and ensure the logic properly respects allocated sizes before performing any write operations.

### **Conclusion**:

The error is caused by writing beyond the allocated memory size in the `BuildMibPdu` function. Carefully check the memory allocation and ensure that the buffer is large enough for any `memset` or data write operations. By correcting the memory management in the code, you should be able to resolve this heap buffer overflow issue.