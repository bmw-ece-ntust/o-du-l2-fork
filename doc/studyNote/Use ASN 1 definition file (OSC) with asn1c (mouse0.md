# Use ASN.1 definition file (OSC) with asn1c (mouse07410)

Start Date: 2025/01/09
Summary: Resolving OSC's ASN.1 compiler issues by replacing the existing compiler with mouse asn1c and automating the recompilation and organization of ASN.1 definitions.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2025/01/17
SUM: 🗓️ Days Spent to Complete: 8

<aside>
💡

The current conclusion is that to resolve OSC's ASN.1 compiler issue, we need to replace Nokia's provided compiler with the mouse asn.1 compiler currently used by OAI. 

</aside>

One point to note is

asn1c generates files for both F1AP and COMMON modules. When following OAI's method of adding prefixes to files, the COMMON files are compiled without prefixes. OSC's project combines all files—F1AP, E2AP, and COMMON—into one separate file. Therefore, during recompilation, we must carefully identify the COMMON files and extract them without prefixes, since OSC's project doesn't use them.

Common Files List

```bash
❯ ls /home/hpe/o-du-l2/src/codec_utils/common
ANY_aper.c             asn_constant.h      BOOLEAN.c                  constr_SEQUENCE_OF_xer.c  INTEGER.h                OBJECT_IDENTIFIER_print.c  per_opentype.h
ANY.c                  asn_internal.c      BOOLEAN.h                  constr_SEQUENCE_print.c   INTEGER_print.c          OBJECT_IDENTIFIER_rfill.c  per_support.c
ANY.h                  asn_internal.h      BOOLEAN_print.c            constr_SEQUENCE_rfill.c   INTEGER_rfill.c          OBJECT_IDENTIFIER_xer.c    per_support.h
ANY_uper.c             asn_ioc.h           BOOLEAN_rfill.c            constr_SEQUENCE_uper.c    INTEGER_uper.c           OCTET_STRING_aper.c        PrintableString.c
ANY_xer.c              asn_random_fill.c   BOOLEAN_uper.c             constr_SEQUENCE_xer.c     INTEGER_xer.c            OCTET_STRING.c             PrintableString.h
aper_decoder.c         asn_random_fill.h   BOOLEAN_xer.c              constr_SET_OF_aper.c      Makefile.am.libasncodec  OCTET_STRING.h             uper_decoder.c
aper_decoder.h         asn_SEQUENCE_OF.c   constraints.c              constr_SET_OF.c           NativeEnumerated_aper.c  OCTET_STRING_print.c       uper_decoder.h
aper_encoder.c         asn_SEQUENCE_OF.h   constraints.h              constr_SET_OF.h           NativeEnumerated.c       OCTET_STRING_rfill.c       uper_encoder.c
aper_encoder.h         asn_SET_OF.c        constr_CHOICE_aper.c       constr_SET_OF_print.c     NativeEnumerated.h       OCTET_STRING_uper.c        uper_encoder.h
aper_opentype.c        asn_SET_OF.h        constr_CHOICE.c            constr_SET_OF_rfill.c     NativeEnumerated_uper.c  OCTET_STRING_xer.c         uper_opentype.c
aper_opentype.h        asn_system.h        constr_CHOICE.h            constr_SET_OF_uper.c      NativeEnumerated_xer.c   odu_common_codec.c         uper_opentype.h
aper_support.c         ber_tlv_length.c    constr_CHOICE_print.c      constr_SET_OF_xer.c       NativeInteger_aper.c     odu_common_codec.h         uper_support.c
aper_support.h         ber_tlv_length.h    constr_CHOICE_rfill.c      constr_TYPE.c             NativeInteger.c          OPEN_TYPE_aper.c           uper_support.h
asn_application.c      ber_tlv_tag.c       constr_CHOICE_uper.c       constr_TYPE.h             NativeInteger.h          OPEN_TYPE.c                xer_decoder.c
asn_application.h      ber_tlv_tag.h       constr_CHOICE_xer.c        ENUMERATED_aper.c         NativeInteger_print.c    OPEN_TYPE.h                xer_decoder.h
asn_bit_data.c         BIT_STRING.c        constr_SEQUENCE_aper.c     ENUMERATED.c              NativeInteger_rfill.c    OPEN_TYPE_uper.c           xer_encoder.c
asn_bit_data.h         BIT_STRING.h        constr_SEQUENCE.c          ENUMERATED.h              NativeInteger_uper.c     OPEN_TYPE_xer.c            xer_encoder.h
asn_codecs.h           BIT_STRING_print.c  constr_SEQUENCE.h          ENUMERATED_uper.c         NativeInteger_xer.c      per_decoder.c              xer_support.c
asn_codecs_prim.c      BIT_STRING_rfill.c  constr_SEQUENCE_OF_aper.c  GraphicString.c           ObjectDescriptor.c       per_decoder.h              xer_support.h
asn_codecs_prim.h      BIT_STRING_uper.c   constr_SEQUENCE_OF.c       GraphicString.h           ObjectDescriptor.h       per_encoder.c
asn_codecs_prim_xer.c  BIT_STRING_xer.c    constr_SEQUENCE_OF.h       INTEGER_aper.c            OBJECT_IDENTIFIER.c      per_encoder.h
asn_config.h           BOOLEAN_aper.c      constr_SEQUENCE_OF_uper.c  INTEGER.c                 OBJECT_IDENTIFIER.h      per_opentype.c
```

I have implemented a simple process to recompile OSC's ASN.1 definitions using mouse asn1c. The process determines whether files belong in the common folder based on their content and moves them to either the common folder or their respective module folders (such as E2AP, F1AP, RRC). To automate this process, I created a script that handles the file organization. To use it, refer to the script at the top of each file and replace DIR_NAME and all file paths with your own paths.

[https://github.com/dong881/NTUST-script/blob/one-click/Tools/Pick-commonFiles.sh](https://github.com/dong881/NTUST-script/blob/one-click/Tools/Pick-commonFiles.sh)

<aside>

Key ASN.1 file directories:

</aside>

- COMMON → [OSC common  ASN.1 file](OSC%20common%20ASN%201%20file%2012110098314381598f71f038b9794b83.md)
- RRC → [OSC RRC ASN.1 file](OSC%20RRC%20ASN%201%20file%20121100983143816c86a6e7063521baf1.md)
- F1AP → [OSC F1AP ASN.1 file](OSC%20F1AP%20ASN%201%20file%201211009831438070bb80c050fcf47cdf.md)
- E2AP → [OSC E2AP ASN.1 file](OSC%20E2AP%20ASN%201%20file%2012110098314380ebbef6c4d726bd0894.md)
    
    <aside>
    ⚠️
    
    Please note that I repeatedly recompiled and verified the updates to ensure there were no issues. Following the compilation order (RRC → E2AP → E2SM_KPM → F1AP) when overwriting the common folder helps resolve some unexpected problems.
    
    </aside>
    

At this point, you should be able to successfully compile all the codec_utils code, meaning there are no issues with any of the files compiled by asn1c. The next challenge is to address the compatibility issues in the OSC source code caused by using a different asn1c compiler. Moving forward, our modifications will focus on adjusting OSC's modified ASN.1 definitions and their native source code—we will absolutely not modify the asn1c-compiled files as a solution.

After recompilation, we will use a script to delete unnecessary encoding files (DER, BER, OER, and JER related files) from the COMMON folder since they are not used in the original definition.

```bash
rm -f {ber_,oer_,jer_}* *_{jer,ber,oer}.*(N)
```

The following files should not be deleted (they are required):

- ber_tlv_length.c
- ber_tlv_length.h
- ber_tlv_tag.c
- ber_tlv_tag.h

Suggested git commit message:

```bash
codec: Cleanup unnecessary encoding files and reorganize COMMON

- Remove unused DER/BER/OER/JER related files from COMMON folder
- Move UPER-specific files to RRC folder
- Retain essential BER TLV files
- Optimize codec structure for better maintainability
```

Alternatively, you can directly apply the patch

[0001-Cleanup-unnecessary-encoding-files-and-reorganize-CO.patch](0001-Cleanup-unnecessary-encoding-files-and-reorganize-CO.patch)

```bash
git apply --reject --whitespace=fix ~/0001-Cleanup-unnecessary-encoding-files-and-reorganize-CO.patch
```

[Ming-Fixed-du_f1ap_msg_hdl.patch](Ming-Fixed-du_f1ap_msg_hdl.patch)

```bash
git apply --reject --whitespace=fix ~/Ming-Fixed-all-compilerERROR.patch
```

### Insights from Robert

[Ask Robert](Ask%20Robert%2017810098314380a29e47f308dbc12958.md)

# Modification Patches

---

[RRC-asn1c_mouse07410.patch](RRC-asn1c_mouse07410.patch)

[F1AP-asn1c_mouse07410.patch](F1AP-asn1c_mouse07410.patch)

[E2SM_KPM-asn1c_mouse07410.patch](E2SM_KPM-asn1c_mouse07410.patch)

[E2AP-asn1c_mouse07410.patch](E2AP-asn1c_mouse07410.patch)

[CleanStep.patch](CleanStep.patch)

[Fix-Handle-F1AP_ProtocolExtensionContainerUsage.patch](Fix-Handle-F1AP_ProtocolExtensionContainerUsage.patch)