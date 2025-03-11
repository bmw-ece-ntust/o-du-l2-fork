# Reply to Robert's email to clarify the issue he raised

Start Date: 2024/10/30
Summary: Clarifying issues with the ASN.1 compiler and testing SIB1 and F1AP encoding based on Robert's feedback.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: mail
Finish Date: 2024/10/30
SUM: 🗓️ Days Spent to Complete: 0

- [ ]  [Use another(mouse07410) asn.1 compiler (asn1c)](Use%20another(mouse07410)%20asn%201%20compiler%20(asn1c)%2012e1009831438015baa3f32e16b207e0.md)
- I know the ASN.1 version is not the issue
- Currently, Nokia has requested that I provide a diff comparison to help them fix asn1c. Additionally, they have also sent a test file, hoping that I can test it and report back to them for repair. I am currently working on this.
- However, in OSC they need to get the entire community to agree before making changes, so Ankit currently believes the best solution is to wait for Nokia to fix the compiler. If I want to replace asn1c ourselves, it would be limited to internal testing. Of course, I have tried it, but I still encountered some problems, which I will briefly describe:
    - Currently, while waiting for Nokia to fix the compiler, I have some ideas I want to try to solve the problem on my own. From my previous tests, I know that if we want to try using mouse07410's asn1c to encode SIB1 in OSC, we need to modify the OSC source code, because I have found dozens of variable name mismatches that cause problems when compiling the OSC code
    - However, in the current state where I can encode/decode after making modifications, there are still issues with the ASN1 of the F1AP struct. Therefore, I have also rebuilt F1AP and E2AP using mouse07410's asn1c, but encountered error logs in the compiler (**unknown type name**) [**ASN.1 file build: unknown type name**](ASN%201%20file%20build%20unknown%20type%20name%201221009831438027a679c6b997f60b5b.md) Please refer to the log below

```jsx
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

I have completely run out of ideas for this problem, but my next step is to start with SIB1, beginning with modifying the struct definition, and attempt internal testing to fix SIB1 and F1AP ASN1 encoding

Additionally, this is the latest UE log, and by comparing the differences with OAI Layer2, I have confirmed that there is indeed a problem with the CellGroupConfig

[OAI UE Logs (OAI CU + OSC DU High + OAI Layer1 + OAI UE)](OAI_UE_Logs_(OAI_CU__OSC_DU_High__OAI_Layer1__OAI_UE).txt)

[OAI UE Logs (OAI CU + OAI Layer2 + OAI Layer1 + OAI UE)](OAI_UE_Logs_(OAI_CU__OAI_Layer2__OAI_Layer1__OAI_UE).txt)

Summary of Robert’s feedback, organized by topic and retaining the original content:

**1. Decoding Failures in Wireshark for SIB1 Messages**

Robert suggests that although Wireshark is not always the definitive reference, it’s worth addressing this issue. Since OAI DU’s SIB1 messages decode correctly in Wireshark (and many commercial UEs can decode them), it indicates a potential issue with Nokia’s ASN1C compiler. Robert advises either fixing the Nokia compiler or switching to a different ASN1C compiler, like the one used by OAI and Open5GS ([mouse07410/asn1c](https://github.com/mouse07410/asn1c)).

**2. Decoding Failures in Wireshark for F1 Messages**

This issue appears to mirror the problem with SIB1 messages. Robert’s suggestion remains consistent: try switching to the alternative asn1c compiler if Nokia’s implementation continues to fail.

**3. Version Discrepancies Between OSC and OAI ASN.1 Files**

Robert notes that 3GPP ASN.1 files are designed to be backward-compatible. Therefore, the version differences alone (OSC’s 3GPP Release 15 vs. OAI’s Release 17) shouldn’t cause issues. He asks whether the OAI CU is able to decode these messages correctly. If it can, but fails when attempting to decode CellGroupConfig, that may indicate a bug. This topic may require further analysis to determine if downgrading the OAI RRC to Release 16 or 15 is feasible. However, some features, like NTN support, would need to be removed.

**4. Diff Files for Identifying Compiler-Related Issues**

Robert expresses uncertainty about how the diff files (Diff_RRC_OAIOSC and Diff_name-status) will help identify specific issues. He reiterates that switching to another asn1c compiler could be the most straightforward solution, as Mikel had encountered similar problems and resolved them by switching compilers.

**5. Further Information Needed**

Finally, Robert inquires whether there are any specific error logs or crashes related to these issues, as these details could provide additional insights into the root cause.