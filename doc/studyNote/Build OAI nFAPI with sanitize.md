# Build OAI nFAPI with sanitize

Start Date: 2024/05/13
Summary: Building the OAI nFAPI with AddressSanitizer to detect and resolve memory errors during execution.
Status: Reject
Assign: Ming 咚咚 [銘鴻]

**AddressSanitizer** is a runtime memory error detector designed to find such issues in C and C++ programs. It instruments the code during compilation to track memory allocations and deallocations, and it detects errors when the program is executed.

To do this, you would typically compile your program with specific compiler flags that enable **AddressSanitizer**, like **`-fsanitize=address`** in GCC or Clang. Then, you'd run your program as usual, and if there are any memory errors, AddressSanitizer will report them along with the stack trace and other relevant information to help you debug the issues.

<aside>
🗣 Robert is encountering execution problems after cherry-picking our branch commit and has suggested building with an address sanitizer before trying again.

</aside>

OAI Build:

```bash
sudo ./build_oai -c --ninja --nrUE --gNB --sanitize
```

## In `./build_oai` script file

```bash
--sanitize
  Shortcut for usage of --sanitize-address --sanitize-undefined
--sanitize-address | -fsanitize=address
  Enable the address sanitizer on all targets
--sanitize-undefined | -fsanitize=undefined
  Enable the undefined behavior sanitizer on all targets
--sanitize-memory | -fsanitize=memory
  Enable the memory sanitizer on all targets. Requires clang, and is
  incompatible with ASan/UBSan. To build, issue:
  CC=/usr/bin/clang CXX=/usr/bin/clang++ ./build_oai ... --sanitize-memory
--sanitize-thread | -fsanitize=thread
  Enable the thread sanitizer on all targets
```

## add patch

In `openairinterface5g/CMakeLists.txt` add config **`-fno-omit-frame-pointer`** 

```c
diff --git a/CMakeLists.txt b/CMakeLists.txt
index 5854dae3d5..1bf379d206 100644
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -158,7 +158,7 @@ endif()
 # add autotools definitions that were maybe used!
 add_definitions("-DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_FCNTL_H=1 -DHAVE_ARPA_INET_H=1 -DHAVE_SYS_TIME_H=1 -DHAVE_SYS_SOCKET_H=1 -DHAVE_STRERROR=1 -DHAVE_SOCKET=1 -DHAVE_MEMSET=1 -DHAVE_GETTIMEOFDAY=1 -DHAVE_STDLIB_H=1 -DHAVE_MALLOC=1 -DHAVE_LIBSCTP")
 
-set(commonOpts "-pipe -fPIC -Wall -fno-strict-aliasing")
+set(commonOpts "-pipe -fPIC -Wall -fno-strict-aliasing -fno-omit-frame-pointer")
 # GNU C/C++ Compiler might throw many warnings without packed-bitfield-compat, see man page
 # also, we need -rdynamic to incorporate all symbols in shared objects, again, see man page
 if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
```

- Log will show error:

**AddressSanitizer:DEADLYSIGNAL**