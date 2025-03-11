# Use another(mouse07410) asn.1 compiler (asn1c)

Start Date: 2024/10/29
Summary: Replacing the ASN.1 compiler from OSC's Nokia fork to mouse07410's version due to lack of progress and implementing necessary structural changes.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/29
SUM: 🗓️ Days Spent to Complete: 0

<aside>
⚠️

Due to Nokia's lack of progress in fixing asn1c for several months, and no response to multiple weekly email inquiries about the progress, I have decided to restart the process of replacing the ans.1 compiler, switching from OSC's Nokia fork version to mouse07410's fork version, which is currently being used by OAI, and reorganizing the entire folder structure to replace the file structure

</aside>

## Environment Setup

First, I need to ensure that all ASN.1 folders in OSC match those in the i-release source code.

```diff
git clone https://github.com/dong881/OSC-DU.git
git checkout 9d13bb38
git checkout -B TryUseOAIasn1c
```

- Next, rebuild the ASN.1 files in the `RRC`, `E2AP`, and `F1AP` folders using the same asn1c compiler that OAI is currently using.
    
    [BUILD_LOG-RRC(ERROR)](BUILD_LOG-RRC(ERROR).txt)
    
    [reBuildRRC.log](reBuildRRC.log)
    
    [reBuildF1AP.log](reBuildF1AP.log)
    
    <aside>
    ⚠️
    
    Encountered issues: [**ASN.1 file build: unknown type name**](ASN%201%20file%20build%20unknown%20type%20name%201221009831438027a679c6b997f60b5b.md) 
    
    </aside>
    

Therefore, before making any changes, I will revert the previous SIB1-related modifications while keeping the subsequent RA modifications to maintain the current state

[https://github.com/dong881/OSC-DU/commit/6e91e1cc6eccffb734e294f333744ef11f72788e](https://github.com/dong881/OSC-DU/commit/6e91e1cc6eccffb734e294f333744ef11f72788e)

```markdown
十二 24 11:59:22 [0m[PHY]   Resynchronizing RX by 215040 samples
十二 24 11:59:23 [0m[1;31m[NR_RRC]   [UE 0] Failed to decode BCCH_DLSCH_MESSAGE (0 bits)
十二 24 11:59:23 [0m[NR_RRC]      Received bytes:
十二 24 11:59:23 64 80 0a 02 08 00 c0 40 00 00 04 00 00 00 00 69 08 4d 05 60 00 02 69 67 0c b3 5d e0 1b 82 01 00 00 04 04 00 04 1a 42 81 b0 e4 3a 66 00 01 00 00 13 4e 4e 70 cb 32 a3 10 00 d6 a6 6b ee 4e 02 49 ce 25 4c 6b 78 d5 31 aa 4b 85 c0 0a 1c 3a 01 05 80 ec 02 44 66 f6 21 80 [0m
十二 24 11:59:23 [NR_PHY]   ============================================
十二 24 11:59:23 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
十二 24 11:59:23 [0m[NR_PHY]   ============================================
```

<aside>
💡

New idea pending implementation

I believe there's an alternative approach to address this error log.

Previously, I didn't have the OSC ASN.1 definition structure, so I modified the OSC source code. Now, I think I can attempt to revise the OSC definition structure to resolve the issue.

</aside>

- List compiler issues
    
    I have tried this method but found that it fails to compile due to file conflicts and duplicate declarations. I believe the main issue is that OSC has designed a common folder, or rather Nokia's asn1c has designed an asn.1 common folder, while mouse asn1c does not have one. Therefore, I want to reference the cmake build structure that OAI is currently using, perhaps implementing it more comprehensively. I had already inquired with Robert about the detailed steps a few weeks ago → [Responding to Robert: MIB Decoding Issue](Responding%20to%20Robert%20MIB%20Decoding%20Issue%2014c10098314380b29129fa178d328dd4.md) 
    
    - [OSC asn1c .cmake File Generation](OSC%20asn1c%20cmake%20File%20Generation%2014d100983143805fb970eb6975364058.md)

Next, I will identify potential solutions to the problem, evaluate them, and proceed with implementing the most promising approach

Branch : `ImplementCmake_base_moveFromOldDevelop`

```markdown
git checkout -B ImplementCmake_base_moveFromOldDevelop
```

- I may need to remove some files from the OSC ASN.1 `common` folder to avoid multiple definition issues.
    - OAI does not have a `common` folder, so I want to match their structure and behavior.
    
    ```bash
    ~/openairinterface5g/cmake_targets/ran_build/build/openair2$ ls
    CMakeFiles  cmake_install.cmake  E1AP  F1AP  LAYER2  M2AP  RRC  X2AP  XNAP
    ```
    
    ### OSC common folder:
    
    ```bash
    hpe@hpe-ProLiant-DL380-Gen10:~/o-du-l2/src/codec_utils/common$ tree .
    .
    ├── ANY.c
    ├── ANY.h
    ├── asn_application.c
    ├── asn_application.h
    ├── asn_bit_data.c
    ├── asn_bit_data.h
    ├── asn_codecs.h
    ├── asn_codecs_prim.c
    ├── asn_codecs_prim.h
    ├── asn_constant.h
    ├── asn_internal.c
    ├── asn_internal.h
    ├── asn_ioc.h
    ├── asn_random_fill.c
    ├── asn_random_fill.h
    ├── asn_SEQUENCE_OF.c
    ├── asn_SEQUENCE_OF.h
    ├── asn_SET_OF.c
    ├── asn_SET_OF.h
    ├── asn_system.h
    ├── ber_decoder.c
    ├── ber_decoder.h
    ├── ber_tlv_length.c
    ├── ber_tlv_length.h
    ├── ber_tlv_tag.c
    ├── ber_tlv_tag.h
    ├── BIT_STRING.c
    ├── BIT_STRING.h
    ├── BIT_STRING_oer.c
    ├── BOOLEAN.c
    ├── BOOLEAN.h
    ├── constraints.c
    ├── constraints.h
    ├── constr_CHOICE.c
    ├── constr_CHOICE.h
    ├── constr_CHOICE_oer.c
    ├── constr_SEQUENCE.c
    ├── constr_SEQUENCE.h
    ├── constr_SEQUENCE_oer.c
    ├── constr_SEQUENCE_OF.c
    ├── constr_SEQUENCE_OF.h
    ├── constr_SET_OF.c
    ├── constr_SET_OF.h
    ├── constr_SET_OF_oer.c
    ├── constr_TYPE.c
    ├── constr_TYPE.h
    ├── der_encoder.c
    ├── der_encoder.h
    ├── INTEGER.c
    ├── INTEGER.h
    ├── INTEGER_oer.c
    ├── NativeEnumerated.c
    ├── NativeEnumerated.h
    ├── NativeEnumerated_oer.c
    ├── NativeInteger.c
    ├── NativeInteger.h
    ├── NativeInteger_oer.c
    ├── OCTET_STRING.c
    ├── OCTET_STRING.h
    ├── OCTET_STRING_oer.c
    ├── odu_common_codec.c
    ├── odu_common_codec.h
    ├── oer_decoder.c
    ├── oer_decoder.h
    ├── oer_encoder.c
    ├── oer_encoder.h
    ├── oer_support.c
    ├── oer_support.h
    ├── OPEN_TYPE.c
    ├── OPEN_TYPE.h
    ├── OPEN_TYPE_oer.c
    ├── per_decoder.c
    ├── per_decoder.h
    ├── per_encoder.c
    ├── per_encoder.h
    ├── per_opentype.c
    ├── per_opentype.h
    ├── per_support.c
    ├── per_support.h
    ├── xer_decoder.c
    ├── xer_decoder.h
    ├── xer_encoder.c
    ├── xer_encoder.h
    ├── xer_support.c
    └── xer_support.h
    
    0 directories, 85 files
    ```
    
    - However, this approach would require extensive modifications to the original OSC-DU source code, making it a costly solution.
- Replicate OAI asn1c behavior → [OSC asn1c .cmake File Generation](OSC%20asn1c%20cmake%20File%20Generation%2014d100983143805fb970eb6975364058.md)
- Compile and document remaining issues