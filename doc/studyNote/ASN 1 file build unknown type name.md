# ASN.1 file build: unknown type name

Start Date: 2024/10/17
Summary: Resolving "unknown type name" errors in ASN.1 file builds by verifying include paths, file orders, and type definitions.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: ASN.1, OSC Integration
Finish Date: 2025/01/17
SUM: 🗓️ Days Spent to Complete: 92

<aside>
🖇️

Solution:

Follow the steps in [How to Fix OSC asn1c Issues](How%20to%20Fix%20OSC%20asn1c%20Issues%20176100983143804bb9f3fd6a511b919c.md) to resolve this issue

</aside>

### 1. Encountered Issues

After rebuilding all ASN.1-related files and removing multiple files in the `common` folder, I encountered "unknown type name" errors while building OSC source code. However, I've checked all the necessary conditions:

- makefile
- gcc -I config has correct paths
- head files are in the correct paths
- The struct is already defined
- [Managing Circular Dependencies in C/C++ Header Files](Managing%20Circular%20Dependencies%20in%20C%20C++%20Header%20Fil%2012810098314380e4a3f1f891e44df280.md)

### 2. LOG Records

```bash
-e Compiling [31m[1m /home/hpe/o-du-l2/src/codec_utils/F1AP/DRX-Config.c [m
-e Compiling [31m[1m /home/hpe/o-du-l2/src/codec_utils/F1AP/DRXConfigurationIndicator.c [m
In file included from /home/hpe/o-du-l2/src/codec_utils/F1AP/NR-Mode-Info.h:60,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/Served-Cell-Information.h:20,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/GNB-DU-Served-Cells-Item.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h:24,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Container.h:484,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.c:8:
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:22:9: error: unknown type name ‘F1AP_PDU_ExtIEs_t’
   22 | typedef F1AP_PDU_ExtIEs_t  ProtocolIE_SingleContainer_4590P0_t;
      |         ^~~~~~~~~~~~~~~~~
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:23:9: error: unknown type name ‘ResetType_ExtIEs_t’
   23 | typedef ResetType_ExtIEs_t  ProtocolIE_SingleContainer_4590P1_t;
      |         ^~~~~~~~~~~~~~~~~~
```

### 3. Solutions and Analysis

1. **Confirm include paths**: Ensure that your compilation system can find the definition of `F1AP_PDU_ExtIEs_t`. Check the `Makefile` or compilation commands to make sure the file containing the `F1AP_PDU_ExtIEs_t` definition is included in the compilation path.
2. **File order and dependencies**: Verify if the file inclusion order is correct. If the definition of `F1AP_PDU_ExtIEs_t` is in other files, ensure it is correctly included before it is depended upon.
3. **Duplicate definitions or other type conflicts**: Check for situations where `F1AP_PDU_ExtIEs_t` might be defined multiple times or for conflicts with identically named types, possibly from other files or packages.

<aside>
💡

I will use the following steps to verify the file paths, file locations, and definitions:

</aside>

### 1. **Use the `gcc` `E` option to view preprocessing results**

Preprocessing is the first step of compilation, which expands all `#include` files. You can use it to confirm whether the files correctly include the header files you need.

Command :

```bash
gcc -E -I/home/hpe/o-du-l2/src/codec_utils/F1AP /home/hpe/o-du-l2/src/codec_utils/E2AP/ProtocolIE-Field.c -o ~/preprocessed_output.i
```

[preprocessed_output.i](preprocessed_output.i)

```jsx
typedef struct F1AP_PDU_ExtIEs {
 ProtocolIE_ID_t id;
 Criticality_t criticality;
 struct F1AP_PDU_ExtIEs__value {
  F1AP_PDU_ExtIEs__value_PR present;
  union F1AP_PDU_ExtIEs__value_u {
  } choice;

  asn_struct_ctx_t _asn_ctx;
 } value;

 asn_struct_ctx_t _asn_ctx;
} F1AP_PDU_ExtIEs_t;
```

<aside>
💡

Confirm that the definition of `F1AP_PDU_ExtIEs_t` has been expanded

</aside>

---

### 2. **Confirm file existence in include paths**

Use the following command to confirm whether the file is in the specified include path:

Command example:

```bash
find <include path> -name 'ProtocolIE-Field.h'
```

**Steps:**

- Replace `<include path>` with the `I` include path you set.
- Check the output to confirm whether `ProtocolIE-Field.h` or related files defining `ProtocolIE-Field.h` exist.

```jsx
hpe@hpe-ProLiant-DL380-Gen10:~$ find ~/o-du-l2/src/codec_utils/F1AP/ -name 'Protoco
lIE-Field.h'
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h
```

### 3. **Create a simple test file to verify if the type is available**

Create a simple C file, manually include the relevant header files, and try to compile.

Example C file (`test_F1AP.c`):

```c
#include "ProtocolIE-SingleContainer.h"  // Include your header file

int main() {
    F1AP_PDU_ExtIEs_t test_struct;
    printf("123\n");
    return 0;
}
```

Compilation test:

```bash
gcc -I<include path> test_F1AP.c -o test_F1AP
```

**Steps:**

- Replace `<include path>` with `/home/hpe/o-du-l2/src/codec_utils/F1AP`.
- Check if the compilation result is correct, with no errors.

```jsx
hpe@hpe-ProLiant-DL380-Gen10:~$ gcc -I/home/hpe/o-du-l2/src/codec_utils/F1AP test_F1AP.c -o test_F1AP
hpe@hpe-ProLiant-DL380-Gen10:~$ ./test_F1AP 
123
hpe@hpe-ProLiant-DL380-Gen10:~$ 
```

### 4. Unit test for error file

```jsx
hpe@hpe-ProLiant-DL380-Gen10:~$ gcc -I/home/hpe/o-du-l2/src/codec_utils/F1AP /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.c -o test_F1AP
In file included from /home/hpe/o-du-l2/src/codec_utils/F1AP/NR-Mode-Info.h:60,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/Served-Cell-Information.h:20,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/GNB-DU-Served-Cells-Item.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h:24,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Container.h:484,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.c:8:
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:22:9: error: unknown type name ‘F1AP_PDU_ExtIEs_t’
   22 | typedef F1AP_PDU_ExtIEs_t  ProtocolIE_SingleContainer_4590P0_t;
      |         ^~~~~~~~~~~~~~~~~
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:23:9: error: unknown type name ‘ResetType_ExtIEs_t’
   23 | typedef ResetType_ExtIEs_t  ProtocolIE_SingleContainer_4590P1_t;
      |         ^~~~~~~~~~~~~~~~~~
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:24:9: error: unknown type name ‘UE_associatedLogicalF1_ConnectionItemRes_t’
   24 | typedef UE_associatedLogicalF1_ConnectionItemRes_t  ProtocolIE_SingleContainer_4590P2_t;
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:25:9: error: unknown type name ‘UE_associatedLogicalF1_ConnectionItemResAck_t’
   25 | typedef UE_associatedLogicalF1_ConnectionItemResAck_t  ProtocolIE_SingleContainer_4590P3_t;
```

I find C code header file compilation confusing, so I've created a new note to better understand it.

[Managing Circular Dependencies in C/C++ Header Files](Managing%20Circular%20Dependencies%20in%20C%20C++%20Header%20Fil%2012810098314380e4a3f1f891e44df280.md) 

**ProtocolIE-Container.c** will first include **ProtocolIE-Field.h**

Then **ProtocolIE-SingleContainer.h will also want to include ProtocolIE-Field.h again**

However, this would cause duplicate definitions of the same structures, so header files are usually designed with protection mechanisms to prevent repeated declarations after the second time.
This protection mechanism causes **ProtocolIE-SingleContainer.h to be unable to use the structures defined in ProtocolIE-Field.h, resulting in the compiler throwing errors**

```jsx
In file included from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Container.h:484,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.c:8:
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h:11:9: note: #pragma message: Including
```

```
In file included from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/NR-Mode-Info.h:60,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/Served-Cell-Information.h:20,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/GNB-DU-Served-Cells-Item.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h:25,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Container.h:484,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.c:8:
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h:3164:9: note: #pragma message: Including
```

- **#pragma message("Including ProtocolIE-Field.h") → Trigger by `ProtocolIE-Container.h`**
- **#pragma message("SingleContainer want to include ProtocolIE-Field")**
- **#pragma message("Including ProtocolIE-Field.h Finish")**
- **#pragma message("SingleContainer include finish") → Failed to use `F1AP_PDU_ExtIEs_t` struct**
- **#pragma message("Defined F1AP_PDU_ExtIEs_t") →** until here the structure was defined
- **#pragma message("Including ProtocolIE-Field.h Finish")**

## Compiling OAI Source Code for Unit Testing

```jsx
gcc  -I/home/hpe/openairinterface5g/cmake_targets/ran_build/build/openair2/F1AP/MESSAGES /home/hpe/openairinterface5g/cmake_targets/ran_build/build/openair2/F1AP/MESSAGES/F1AP_DLRRCMessageTransfer.c -o test_F1AP &> ./UnitLOG.log
```

```
/usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o: in function `_start':
(.text+0x1b): undefined reference to `main'
/usr/bin/ld: /tmp/cc2T5ljG.o:(.data.rel+0x18): undefined reference to `asn_DEF_F1AP_ProtocolIE_Container_10659P32'
/usr/bin/ld: /tmp/cc2T5ljG.o:(.data.rel+0x70): undefined reference to `asn_OP_SEQUENCE'
/usr/bin/ld: /tmp/cc2T5ljG.o:(.data.rel+0xa0): undefined reference to `SEQUENCE_constraint'
collect2: error: ld returned 1 exit status

```

## Compare OAI and OSC Structure Definitions and Use the Same Compiler

Compiler used by OAI:

### ProtocolIE-Field.h

```diff
hpe@hpe-ProLiant-DL380-Gen10:~/o-du-l2$ git diff o-ran-sc/i-release -- src/codec_utils/F1AP/ProtocolIE-Field.h
diff --git a/src/codec_utils/F1AP/ProtocolIE-Field.h b/src/codec_utils/F1AP/ProtocolIE-Field.h
index 65e2abaf..89d070bf 100644
--- a/src/codec_utils/F1AP/ProtocolIE-Field.h
+++ b/src/codec_utils/F1AP/ProtocolIE-Field.h
@@ -1,8 +1,8 @@
 /*
  * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
  * From ASN.1 module "F1AP-Containers"
- *     found in "../F1.asn1"
- *     `asn1c -D ../F1_output/ -fcompound-names -fno-include-deps -findirect-choice -gen-PER`
+ *     found in "/home/hpe/NTUST-script/CONFIG/F1.asn1"
+ *     `asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp`
  */
 
 #ifndef        _ProtocolIE_Field_H_
@@ -642,6 +642,7 @@ typedef enum UEContextReleaseCommandIEs__value_PR {
        UEContextReleaseCommandIEs__value_PR_Cause,
        UEContextReleaseCommandIEs__value_PR_RRCContainer,
        UEContextReleaseCommandIEs__value_PR_SRBID,
+       UEContextReleaseCommandIEs__value_PR_GNB_DU_UE_F1AP_ID_1,
        UEContextReleaseCommandIEs__value_PR_ExecuteDuplication,
        UEContextReleaseCommandIEs__value_PR_RRCDeliveryStatusRequest
 } UEContextReleaseCommandIEs__value_PR;
@@ -787,6 +788,7 @@ typedef enum DLRRCMessageTransferIEs__value_PR {
        DLRRCMessageTransferIEs__value_PR_NOTHING,      /* No components present */
        DLRRCMessageTransferIEs__value_PR_GNB_CU_UE_F1AP_ID,
        DLRRCMessageTransferIEs__value_PR_GNB_DU_UE_F1AP_ID,
+       DLRRCMessageTransferIEs__value_PR_GNB_DU_UE_F1AP_ID_1,
        DLRRCMessageTransferIEs__value_PR_SRBID,
        DLRRCMessageTransferIEs__value_PR_ExecuteDuplication,
        DLRRCMessageTransferIEs__value_PR_RRCContainer,
@@ -2340,6 +2342,7 @@ typedef struct UEContextReleaseCommandIEs {
                        Cause_t  Cause;
                        RRCContainer_t   RRCContainer;
                        SRBID_t  SRBID;
+                       GNB_DU_UE_F1AP_ID_t      GNB_DU_UE_F1AP_ID_1;
                        ExecuteDuplication_t     ExecuteDuplication;
                        RRCDeliveryStatusRequest_t       RRCDeliveryStatusRequest;
                } choice;
@@ -2653,6 +2656,7 @@ typedef struct DLRRCMessageTransferIEs {
                union DLRRCMessageTransferIEs__value_u {
                        GNB_CU_UE_F1AP_ID_t      GNB_CU_UE_F1AP_ID;
                        GNB_DU_UE_F1AP_ID_t      GNB_DU_UE_F1AP_ID;
+                       GNB_DU_UE_F1AP_ID_t      GNB_DU_UE_F1AP_ID_1;
                        SRBID_t  SRBID;
                        ExecuteDuplication_t     ExecuteDuplication;
                        RRCContainer_t   RRCContainer;
```

### ProtocolIE-SingleContainer.h

```diff
hpe@hpe-ProLiant-DL380-Gen10:~/o-du-l2$ git diff o-ran-sc/i-release -- src/codec_utils/F1AP/ProtocolIE-SingleContainer.h
diff --git a/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h b/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h
index fa21bc0d..0f34dd85 100644
--- a/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h
+++ b/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h
@@ -1,8 +1,8 @@
 /*
  * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
  * From ASN.1 module "F1AP-Containers"
- *     found in "../F1.asn1"
- *     `asn1c -D ../F1_output/ -fcompound-names -fno-include-deps -findirect-choice -gen-PER`
+ *     found in "/home/hpe/NTUST-script/CONFIG/F1.asn1"
+ *     `asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp`
  */
 
 #ifndef        _ProtocolIE_SingleContainer_H_
@@ -95,12 +95,8 @@ extern asn_TYPE_descriptor_t asn_DEF_ProtocolIE_SingleContainer_4590P0;
 asn_struct_free_f ProtocolIE_SingleContainer_4590P0_free;
 asn_struct_print_f ProtocolIE_SingleContainer_4590P0_print;
 asn_constr_check_f ProtocolIE_SingleContainer_4590P0_constraint;
-ber_type_decoder_f ProtocolIE_SingleContainer_4590P0_decode_ber;
-der_type_encoder_f ProtocolIE_SingleContainer_4590P0_encode_der;
 xer_type_decoder_f ProtocolIE_SingleContainer_4590P0_decode_xer;
 xer_type_encoder_f ProtocolIE_SingleContainer_4590P0_encode_xer;
-oer_type_decoder_f ProtocolIE_SingleContainer_4590P0_decode_oer;
-oer_type_encoder_f ProtocolIE_SingleContainer_4590P0_encode_oer;
 per_type_decoder_f ProtocolIE_SingleContainer_4590P0_decode_uper;
 per_type_encoder_f ProtocolIE_SingleContainer_4590P0_encode_uper;
 per_type_decoder_f ProtocolIE_SingleContainer_4590P0_decode_aper;
@@ -109,12 +105,8 @@ extern asn_TYPE_descriptor_t asn_DEF_ProtocolIE_SingleContainer_4590P1;
 asn_struct_free_f ProtocolIE_SingleContainer_4590P1_free;
 asn_struct_print_f ProtocolIE_SingleContainer_4590P1_print;
 asn_constr_check_f ProtocolIE_SingleContainer_4590P1_constraint;
-ber_type_decoder_f ProtocolIE_SingleContainer_4590P1_decode_ber;
-der_type_encoder_f ProtocolIE_SingleContainer_4590P1_encode_der;
 xer_type_decoder_f ProtocolIE_SingleContainer_4590P1_decode_xer;
 xer_type_encoder_f ProtocolIE_SingleContainer_4590P1_encode_xer;
-oer_type_decoder_f ProtocolIE_SingleContainer_4590P1_decode_oer;
-oer_type_encoder_f ProtocolIE_SingleContainer_4590P1_encode_oer;
 per_type_decoder_f ProtocolIE_SingleContainer_4590P1_decode_uper;
 per_type_encoder_f ProtocolIE_SingleContainer_4590P1_encode_uper;
 per_type_decoder_f ProtocolIE_SingleContainer_4590P1_decode_aper;
```