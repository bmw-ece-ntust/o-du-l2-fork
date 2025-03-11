# Use Valgrind to fix segmentation faults

Start Date: 2024/09/25
Summary: Fix segmentation faults in the OSC DU High project using Valgrind to analyze memory allocation issues.
Status: Done
Assign: Ming 咚咚 [銘鴻]

# Problem Definition

<aside>
💡

When executing OSC DU High, a segmentation fault often occurs during memory allocation (DU_ALLOC).

**Fix:** Refer to the document on [E2AP Blockage During E2 Setup Request Build](Fix%20E2AP%20Blockage%20During%20E2%20Setup%20Request%20Build%201211009831438136b428fa8de1a96aad.md) for resolution.

</aside>

## Valgrind

How to use: [**Debugging Intermittent Memory Issues in C Code**](Debugging%20Intermittent%20Memory%20Issues%20in%20C%20Code%2012110098314381e8af07d2e1cc058382.md) 

```jsx
==213745== Memcheck, a memory error detector
==213745== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==213745== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==213745== Command: ./du
==213745== 
==213772== 
==213772== HEAP SUMMARY:
==213772==     in use at exit: 67,804 bytes in 732 blocks
==213772==   total heap usage: 1,264 allocs, 532 frees, 308,399 bytes allocated
==213772== 
==213772== LEAK SUMMARY:
==213772==    definitely lost: 0 bytes in 0 blocks
==213772==    indirectly lost: 0 bytes in 0 blocks
==213772==      possibly lost: 0 bytes in 0 blocks
==213772==    still reachable: 67,804 bytes in 732 blocks
==213772==         suppressed: 0 bytes in 0 blocks
==213772== Reachable blocks (those to which a pointer was found) are not shown.
==213772== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==213772== 
==213772== For lists of detected and suppressed errors, rerun with: -s
==213772== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```jsx
./du: line 5: 213778 Segmentation fault      sudo ./odu
==213745== 
==213745== HEAP SUMMARY:
==213745==     in use at exit: 151,933 bytes in 753 blocks
==213745==   total heap usage: 1,786 allocs, 1,033 frees, 216,383 bytes allocated
==213745== 
==213745== LEAK SUMMARY:
==213745==    definitely lost: 0 bytes in 0 blocks
==213745==    indirectly lost: 0 bytes in 0 blocks
==213745==      possibly lost: 0 bytes in 0 blocks
==213745==    still reachable: 151,933 bytes in 753 blocks
==213745==         suppressed: 0 bytes in 0 blocks
==213745== Reachable blocks (those to which a pointer was found) are not shown.
==213745== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==213745== 
==213745== For lists of detected and suppressed errors, rerun with: -s
==213745== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

<aside>
✅

**Memory Leaks:**

- **No definite memory leaks** are present (meaning no memory that is fully lost).
- **Reachable memory** might indicate that some memory remains allocated but is still referenced when the program terminates. This might be okay, as it could be global/static allocations or memory the program hasn't explicitly freed but was accessible.
</aside>

### Valgrind Output Analysis

Your Valgrind report indicates no **definite** or **indirect memory leaks**, but there is a **segmentation fault** during the execution of `odu` that needs further investigation. Let's break down the report step by step:

### **Key Findings:**

1. **Heap Summary:**
    - **First run (`./du`)**:
        - **67,804 bytes** in **732 blocks** are still reachable but not freed.
        - No memory leaks (definitely or indirectly lost).
        - Valgrind suggests using `-leak-check=full --show-leak-kinds=all` to display reachable blocks in detail, but they are not necessarily memory leaks.
    - **Second run (`sudo ./odu`)**:
        - **151,933 bytes** in **753 blocks** still reachable.
        - Similarly, no leaks are indicated, but some memory remains reachable at the end.
2. **Memory Leaks:**
    - **No definite memory leaks** are present (meaning no memory that is fully lost).
    - **Reachable memory** might indicate that some memory remains allocated but is still referenced when the program terminates. This might be okay, as it could be global/static allocations or memory the program hasn't explicitly freed but was accessible.
3. **Segmentation Fault:**
    - The key issue is the segmentation fault:
        
        ```bash
        ./du: line 5: 213778 Segmentation fault      sudo ./odu
        
        ```
        
    - This error happens during the execution of `sudo ./odu`, not captured directly by Valgrind in terms of memory violations.
    - Valgrind doesn’t report any memory errors in its memory check, so the segmentation fault might be unrelated to memory leaks but could stem from:
        - **Invalid memory access** (e.g., accessing freed memory or an out-of-bounds access).
        - **Threading issues** (e.g., race conditions).

---

### Conclusion:

- **No definite memory leaks** are shown, but **reachable memory** indicates that some allocations were not freed. These may or may not be problematic.
- The **segmentation fault** is the main issue and could be due to invalid memory access, race conditions, or another type of undefined behavior.
- To resolve the issue:
    - Use `gdb` or Valgrind to track the exact location of the segmentation fault.
    - Use AddressSanitizer (ASan) to catch potential memory corruption or out-of-bounds access.