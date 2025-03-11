# Ask Robert

## Key Points Summary:

- **Issue:** Compilation error with .asn1 files regarding `struct F1AP_ProtocolExtensionContainer`
- **Error Message:** "dereferencing pointer to incomplete type 'struct F1AP_ProtocolExtensionContainer'"
- **Code Structure:**
    - Only suffixed versions of the container exist (e.g., `F1AP_ProtocolExtensionContainer_10696P121`)
    - No direct definition of base `F1AP_ProtocolExtensionContainer` found
- **Robert's Response:**
    - Robert also believes that this type cannot be used directly and must be cast to suffixed versions
    - Should only use pointers to this type, not the entire structure

# My Question

I am currently trying to compile using the .asn1 files provided by OSC, and I’ve encountered an issue. Specifically, the `gcc` compiler throws the following error:`error: dereferencing pointer to incomplete type 'struct F1AP_ProtocolExtensionContainer'.`I thought maybe I could find a solution in OAI since they use the same struct, soI’ve been tracing the code in OAI but, like the compiler, I can’t seem to figure out this part. Here's what I’ve found so far:

1. **Where the structure is used**

For example:

```
 struct F1AP_ProtocolExtensionContainer *iE_Extensions; /* OPTIONAL */
```

Found in:`openairinterface5g/cmake_targets/ran_build/build/openair2/F1AP/MESSAGES/F1AP_GNB-DU-Served-Cells-Item.h`.

**2. What I discovered in the generated files**I searched for the definition of `F1AP_ProtocolExtensionContainer` but could only find definitions for structures like `F1AP_ProtocolExtensionContainer_<suffix>` (e.g., `F1AP_ProtocolExtensionContainer_10696P121`).

Found in:`openairinterface5g/cmake_targets/ran_build/build/openair2/F1AP/MESSAGES/F1AP_ProtocolExtensionContainer.h`.Example:

```
typedef struct F1AP_ProtocolExtensionContainer_10696P121 {
    A_SEQUENCE_OF(struct F1AP_GNB_DU_Served_Cells_ItemExtIEs) list;
    asn_struct_ctx_t _asn_ctx;
} F1AP_ProtocolExtensionContainer_10696P121_t;

```

**3.  The confusion**While we know that the code works, I couldn’t find any direct definition of `F1AP_ProtocolExtensionContainer`. It seems like the generated files only define the suffixed versions (e.g., `F1AP_ProtocolExtensionContainer_10696P121`).Would you happen to have any insights into this? Perhaps there’s an implicit mechanism or mapping I’m missing? Any advice or pointers would be greatly appreciated.

# Reply from Robert

Robert Schmidt

[今天下午 5:02](https://openairinterface.slack.com/archives/D06MS6VMKQS/p1736758939031349?thread_ts=1736609486.733119&cid=D06MS6VMKQS)

I have never fully understood how this works. In OAI, you cannot use this type directly, you always have to cast it to one of this suffixed version. But also, we always only use a pointer to this type! the error message  that you seem to have sèems to imply that you have the entire structure, but again, you should only have a pointer!

# Reply from Open AI

https://chatgpt.com/share/67878068-d004-8003-a794-14532bc177ed