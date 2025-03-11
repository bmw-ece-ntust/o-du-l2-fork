# Refactor Development Code for SIB1 ASN.1 in Preparation for New Nokia asn1c Integration

Start Date: 2024/11/13
Summary: Refactoring development code for SIB1 ASN.1 in preparation for integrating the new Nokia asn1c version.
Status: padding
Assign: Ming 咚咚 [銘鴻]

- [x]  Compile the OSC-provided ASN.1 definition file using mouse asn1c compiler through manual command line input → [(mouse asn1c) command line](Refactor%20Development%20Code%20for%20SIB1%20ASN%201%20in%20Prepar%2013d1009831438065ad24d2d8167e4721.md)
- [ ]  Compile the OSC-provided ASN.1 definition file using the mouse asn1c compiler through OAI's automatic CMake compilation, then copy all files to the OSC project → [(mouse asn1c) CMakefile](Refactor%20Development%20Code%20for%20SIB1%20ASN%201%20in%20Prepar%2013d1009831438065ad24d2d8167e4721.md)

# (mouse asn1c) command line

<aside>
💡

Refactor the current development code and commit, removing previous manual fixes for `SIB1` ASN.1 but retaining all integrated development features, in preparation for replacing with the new Nokia `asn1c` version.

</aside>

- [x]  Refactor the current development code and commit:
    - [x]  Remove previous manual fixes for `SIB1` ASN.1
    - [x]  check commit `9d13bb384381778749c0854fb9842c71355b328e` execute status
    - [x]  Prepare the code for integration with the new Nokia `asn1c` version

### In the Old Development Folder `mwnl-odu-at-oai-based-on-scf`

- add new branch `RemoveFixedSIB1asn1` to prepare for code refactoring and integration with new Nokia asn1c version

### Switch to new Git clone of OSC source folder `o-du-l2`

- add new branch`moveFromOldDevelop`to prepare for migrating code from old development repository
- add new branch`FixASN1_afterGetSouceFile_base_moveFromOldDevelop`to fix ASN.1 issues after obtaining source files, based on code migrated from old development

### After compiling the OSC-provided ASN definition file using OAI's mouse asn1c compiler

- `/home/hpe/o-du-l2/src/codec_utils/RRC/NULL.h:30:1: error: unknown type name ‘asn_struct_copy_f’; did you mean ‘asn_struct_compare_f’?`
    
    [(build)NULL unkonw type name.log]((build)NULL_unkonw_type_name.log)
    
- Modify makefile (`build/common/du_app.mak`) oder

```diff
diff --git a/build/common/du_app.mak b/build/common/du_app.mak
index dc03e4f6..d853e6dc 100644
--- a/build/common/du_app.mak
+++ b/build/common/du_app.mak
@@ -36,9 +36,9 @@ lib: $(LIB_DIR)/libduapp.a
 include $(COM_BUILD_DIR)/compile.mak
 
 I_OPTS+=-I$(ROOT_DIR)/src/mt
-I_OPTS+=-I$(ROOT_DIR)/src/codec_utils/common
 I_OPTS+=-I$(ROOT_DIR)/src/codec_utils/F1AP
 I_OPTS+=-I$(ROOT_DIR)/src/codec_utils/RRC
+I_OPTS+=-I$(ROOT_DIR)/src/codec_utils/common
 I_OPTS+=-I$(ROOT_DIR)/src/codec_utils/E2AP
 I_OPTS+=-I$(ROOT_DIR)/src/codec_utils/E2SM_KPM
```

- **`multiple definition` and `undefined reference`**
    
    [BuildOsc_multiple definition_undefined reference.log](BuildOsc_multiple_definition_undefined_reference.log)
    

- Finish re-compile `RRC` ,`F1AP` ,`E2AP`
    
    [BuildOsc_FinishF1APE2APRRC.log](BuildOsc_FinishF1APE2APRRC.log)
    

### Manually delete problematic asn1c compiled files (typically in the OSC original COMMON folder)

```bash
hpe@hpe-ProLiant-DL380-Gen10:~/o-du-l2$ git status --short | grep '^ D' | awk '{print $2}'
src/codec_utils/F1AP/OBJECT_IDENTIFIER.c
src/codec_utils/RRC/Makefile.am.asn1convert
src/codec_utils/RRC/pdu_collection.c
src/codec_utils/common/BIT_STRING.c
src/codec_utils/common/BOOLEAN.c
src/codec_utils/common/INTEGER.c
src/codec_utils/common/NativeEnumerated.c
src/codec_utils/common/NativeInteger.c
src/codec_utils/common/OCTET_STRING.c
src/codec_utils/common/OPEN_TYPE.c
src/codec_utils/common/asn_codecs_prim.c
src/codec_utils/common/constr_CHOICE.c
src/codec_utils/common/constr_SEQUENCE.c
src/codec_utils/common/constr_SEQUENCE_OF.c
src/codec_utils/common/constr_SET_OF.c
src/codec_utils/common/per_decoder.c
src/codec_utils/common/per_encoder.c
src/codec_utils/common/per_opentype.c
src/codec_utils/common/per_support.c
```

```bash
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/ANY.o:(.data.rel+0x18): undefined reference to `OCTET_STRING_decode_ber'
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/ANY.o:(.data.rel+0x20): undefined reference to `OCTET_STRING_encode_der'
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/NULL.o:(.data.rel+0x18): undefined reference to `BOOLEAN_decode_ber'
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/NativeReal.o: in function `NativeReal_encode_der':
/home/hpe/o-du-l2/src/codec_utils/E2SM_KPM/NativeReal.c:191: undefined reference to `der_encode_primitive'
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/PrintableString.o:(.data.rel+0x18): undefined reference to `OCTET_STRING_decode_ber'
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/PrintableString.o:(.data.rel+0x20): undefined reference to `OCTET_STRING_encode_der'
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/REAL.o:(.data.rel+0x18): undefined reference to `ber_decode_primitive'
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/REAL.o:(.data.rel+0x20): undefined reference to `der_encode_primitive'
collect2: error: ld returned 1 exit status
make: *** [makefile:235: link_du] Error 1

```

## Added Debug Logging for OSC Build Failures

```makefile
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/asn_common.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)echo "Building asn_common components..."
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/asn_f1ap.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)echo "Building asn_f1ap components..."
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/asn_e2ap.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)echo "Building asn_e2ap components..."
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/asn_e2ap_kpm.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)echo "Building asn_e2ap_kpm components..."
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/asn_rrc.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)echo "Building asn_rrc components..."
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/du_app.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)echo "Building du_app components..."
```

[BuildOsc.log](BuildOsc.log)

<aside>
⚠️

The issue occurs in Building F1AP components...
Running make command to build E2AP files using specified directories and compiler settings

</aside>

```diff
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:22:9: error: unknown type name ‘F1AP_PDU_ExtIEs_t’
   22 | typedef F1AP_PDU_ExtIEs_t  ProtocolIE_SingleContainer_4590P0_t;
      |         ^~~~~~~~~~~~~~~~~
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:23:9: error: unknown type name ‘ResetType_ExtIEs_t’
   23 | typedef ResetType_ExtIEs_t  ProtocolIE_SingleContainer_4590P1_t;
      |         ^~~~~~~~~~~~~~~~~~
```

```diff
In file included from /home/hpe/o-du-l2/src/codec_utils/F1AP/NR-Mode-Info.h:60,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/Served-Cell-Information.h:20,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/GNB-DU-Served-Cells-Item.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h:24,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Container.h:484,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/DLRRCMessageTransfer.c:8:
```

![image.png](image%2092.png)

<aside>
⚠️

The files compiled by OAI have different includes. In `ProtocolIE-Container.h`, it does not include **`ProtocolIE-Field.h`** , therefore it will not cause an infinite loop

</aside>

# (mouse asn1c) CMakefile

- [ ]  Find where OAI uses ASN.1 definitions
- [ ]  Copy OSC-provided ASN.1 definition file to OAI project folder
- [ ]  Compile OAI project
- [ ]  Copy all the compile files back to OSC project
- [ ]  Compile OSC project
- [ ]  Modify OSC source code files (excluding compiled files) as needed
- [ ]  (Optional) Learn how OAI implements CMake build system and adapt similar methods for OSC

## Find where OAI uses ASN.1 definitions

### RRC

```bash
set(NR_RRC_VERSION 17 3 0)
make_version(NR_RRC_cc ${NR_RRC_VERSION})
string(REPLACE ";" "." NR_RRC_RELEASE "${NR_RRC_VERSION}")

if(NR_RRC_RELEASE VERSION_EQUAL "16.4.1")
  include(ASN.1/nr-rrc-16.4.1.cmake)
elseif(NR_RRC_RELEASE VERSION_EQUAL "17.3.0")
  include(ASN.1/nr-rrc-17.3.0.cmake)
else()
  message(FATAL_ERROR "unknown NR_RRC_RELEASE ${NR_RRC_RELEASE}")
endif()

add_custom_command(OUTPUT ${nr_rrc_source} ${nr_rrc_headers}
  COMMAND ASN1C_PREFIX=NR_ ${ASN1C_EXEC} -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${NR_RRC_GRAMMAR}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${NR_RRC_GRAMMAR}
  COMMENT "Generating NR RRC source file from ${CMAKE_CURRENT_SOURCE_DIR}/${NR_RRC_GRAMMAR}"
)
```

### F1AP

```bash
set(F1AP_VERSION 16 3 1)
make_version(F1AP_cc ${F1AP_VERSION})
string(REPLACE ";" "." F1AP_RELEASE "${F1AP_VERSION}")

if(F1AP_RELEASE VERSION_EQUAL "16.3.1")
  include(ASN1/f1ap-16.3.1.cmake)
else()
  message(FATAL_ERROR "unknown F1AP_RELEASE ${F1AP_RELEASE}")
endif()

add_custom_command(OUTPUT ${f1ap_source} ${f1ap_headers}
  COMMAND ASN1C_PREFIX=F1AP_ ${ASN1C_EXEC} -gen-APER -no-gen-BER -no-gen-JER -no-gen-OER -gen-UPER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${F1AP_GRAMMAR}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${F1AP_GRAMMAR}
  COMMENT "Generating F1AP source files from ${CMAKE_CURRENT_SOURCE_DIR}/${F1AP_GRAMMAR}"
)
```

### E2AP

```bash
if(E2AP_VERSION STREQUAL "E2AP_V1")
  add_library(e2ap_ran_func_obj OBJECT 
              flexric/src/lib/e2ap/v1_01/e2ap_types/common/e2ap_ran_function.c )
  add_library(e2ap_plmn_obj OBJECT 
              flexric/src/lib/e2ap/v1_01/e2ap_types/common/e2ap_plmn.c )
  add_library(e2ap_global_node_id_obj OBJECT 
              flexric/src/lib/e2ap/v1_01/e2ap_types/common/e2ap_global_node_id.c )
elseif(E2AP_VERSION STREQUAL "E2AP_V2")
  add_library(e2ap_ran_func_obj OBJECT 
              flexric/src/lib/e2ap/v2_03/e2ap_types/common/e2ap_ran_function.c )
  add_library(e2ap_plmn_obj OBJECT 
              flexric/src/lib/e2ap/v2_03/e2ap_types/common/e2ap_plmn.c )
  add_library(e2ap_global_node_id_obj OBJECT 
              flexric/src/lib/e2ap/v2_03/e2ap_types/common/e2ap_global_node_id.c )
elseif(E2AP_VERSION STREQUAL "E2AP_V3")
  add_library(e2ap_ran_func_obj OBJECT 
              flexric/src/lib/e2ap/v3_01/e2ap_types/common/e2ap_ran_function.c )
  add_library(e2ap_plmn_obj OBJECT 
              flexric/src/lib/e2ap/v3_01/e2ap_types/common/e2ap_plmn.c )
  add_library(e2ap_global_node_id_obj OBJECT 
              flexric/src/lib/e2ap/v3_01/e2ap_types/common/e2ap_global_node_id.c )
else()
  message(FATAL_ERROR "E2AP Unknown version selected")
endif()

```

<aside>
⚠️

I am blocked because I don't have a .cmake file for the OSC ASN.1 definition file. It might need to be created manually.

</aside>

[nr-rrc-17.3.0.cmake](nr-rrc-17.3.0.cmake)