# Notes on Ankit Response Regarding RRCSetupRequest & CellGroupConfig

Start Date: 2025/02/21
Summary: Investigating RRC setup and message transfer issues in OSC DU High, focusing on initial UL RRC message transfer and DL RRC message handling.
Status: In progress
Assign: Ming 咚咚 [銘鴻]
Tags: mail

```bash
Subject: Questions Regarding OSC DU High Handling of RRC Setup and DL RRC Message Transfer

Dear Ankit and Team,

In my current integration environment (OAI CU + OSC DU High + OAI Layer1 + OAI UE), after replacing Nokia asn1c with mouse07410 asn1c in OSC, I have successfully enabled DU and UE to encode/decode SIB1 and RRCSetup messages without modifying the compiler results.

Recently, I have been investigating the RRC setup initiated by the UE after receiving MSG4. I have two questions regarding cellGroupConfig in OSC DU High that I would like to clarify with you:
	1.	Handling of Initial UL RRC Message Transfer in OSC DU High
When OSC DU High receives an RRC Setup Request from the UE, it needs to send an Initial UL RRC Message Transfer to O-CU. However, I noticed that OSC DU High does not package pucch_Config->schedulingRequestResourceToAddModList into the Initial UL RRC Message Transfer structure.
Based on my trace analysis, I found that the function responsible for this process in OSC is:
Function: BuildAndSendInitialRrcMsgTransfer()
Path: o-du-l2/src/du_app/du_f1ap_msg_hdl.c
The issue seems to be that in BuildAndSendInitialRrcMsgTransfer(), both crnti and gnbDuUeF1apId objects (duCb.actvCellLst[cellIdx]->ueCb[ueIdx].crnti) are null, making it impossible to determine the reference.
As a result, in BuildBWPUlDedPucchCfg(), the condition if(schReqDb && (schReqDb->schedAddModListCount != 0)) is not met, preventing BuildPucchSchReqAddModList() from executing. This leads to OSC DU High failing to package pucch_Config->schedulingRequestResourceToAddModList into cellGroupConfig, and consequently, not including it in the Initial UL RRC Message Transfer to O-CU.
This ultimately causes an error in OAI UE, where it detects the missing configuration.
	2.	Handling of DL RRC Message Transfer in OSC DU High
The first point was a bug report; now I would like to clarify another doubt.
Based on my trace analysis, after OSC DU receives DL RRC Message Transfer from O-CU, it executes the function:
Function: duBuildAndSendUeCreateReqToMac()
Path: o-du-l2/src/du_app/du_ue_mgr.c
This function is called in duCreateUeCb(), and the input value DuUeCfg *ueCfgDb is set to NULL. This confirms that in updateDuMacUeCfg(), the system executes fillDefaultxxx_() instead of passing the actual data received from CU to OSC MAC.
Furthermore, I have observed that this data is not transmitted to the UE.
I would like to understand how DL RRC Message Transfer data is passed from O-CU through OSC DU High to DU Low and ultimately to the UE.

I appreciate your time and look forward to your insights.

Best regards,
Ming
```

[(split2&6) OAI CU + OSC DU High + OAI Layer1 + OAI UE.pcap]((split26)_OAI_CU__OSC_DU_High__OAI_Layer1__OAI_UE.pcap)

[(split2&6) OAI CU + OAI DU High + OAI Layer1 + OAI UE.pcap]((split26)_OAI_CU__OAI_DU_High__OAI_Layer1__OAI_UE.pcap)

```css
Dear Ankit,
Please find attached the requested PCAP trace files for both scenarios:
(OAI CU + OSC DU High + OAI Layer1 + OAI UE)
(OAI CU + OAI DU High + OAI Layer1 + OAI UE)
Due to the file size, I have recorded only SCTP and UDP traffic, but I believe this should be sufficient. I have verified using Wireshark that all F1AP and nFAPI messages are visible in the captures.
Additionally, I would like to clarify an issue related to the Initial UL RRC Message Transfer.
According to 38.331, schedulingRequestResourceToAddModList is a required parameter:
schedulingRequestResourceToAddModList   SEQUENCE (SIZE (1..maxNrofSR-Resources)) OF SchedulingRequestResourceConfig  
This means that at least one element must be present in the list. If this parameter is missing, the UE will not be able to configure its scheduling request resources properly, leading to setup failures.
Currently, OSC DU High does not include schedulingRequestResourceToAddModList in the Initial UL RRC Message Transfer. As a result, OAI UE detects the missing configuration and fails.
Could you confirm whether this is a known issue, and if there are any plans to address it?
Lastly, I will share the updated code base after the changes related to ASN.1 shortly.
Looking forward to your response.
```

[E2SM_KPM-asn1c_mouse07410.patch](E2SM_KPM-asn1c_mouse07410%201.patch)

[F1AP-asn1c_mouse07410.patch](F1AP-asn1c_mouse07410%201.patch)

[E2AP-asn1c_mouse07410.patch](E2AP-asn1c_mouse07410%201.patch)

[CleanStep.patch](CleanStep%201.patch)

[RRC-asn1c_mouse07410.patch](RRC-asn1c_mouse07410%201.patch)

[Fix-Handle-F1AP_ProtocolExtensionContainerUsage.patch](Fix-Handle-F1AP_ProtocolExtensionContainerUsage%201.patch)

```css
Dear Ankit,
I have generated patch files for all the modifications related to ASN.1c, including differences after compilation. You can refer to them for details. At the beginning of each patch file, I have described the commit and included the command I used on the mouse07410 ASN.1 compiler. The .asn1 files I used were the ones previously provided to me.
Summary of Fixes
After testing, I found that Nokia’s issue with not updating their ASN.1c can be resolved under the following two conditions:
Replacing it with the mouse07410 version of ASN.1c currently used by OAI.
Using the rrc_15_3.asn1, F1.asn1, and E2APV0300.asn1 files provided by OSC for compilation.
Handling Common Folder Issues
I also implemented a script to address issues that appeared in the common folder during the process.
I created a simple workflow to recompile OSC’s ASN.1 definitions using mouse ASN.1c. The script determines whether files should be placed in the common folder based on their content and then moves them accordingly to either the common folder or their respective module folders (such as E2AP, F1AP, or RRC).
To use this script, modify DIR_NAME and update the file paths accordingly.
#!/bin/bash

DIR_NAME="$1"
TARGET_DIR="/home/hpe/o-du-l2/src/codec_utils/$DIR_NAME"
CCOMMON_DIR="/home/hpe/o-du-l2/src/codec_utils/common"

for file in "$TARGET_DIR"/*; do
    if ! head -n 2 "$file" | grep -q 'Generated by asn1c-' && [[ "$file" == *.c || "$file" == *.h ]]; then
        sudo mv "$file" "$CCOMMON_DIR/"
        echo "Moved $(basename "$file") to common directory"
    fi
done
Additionally, after recompilation, another script is used to remove unnecessary encoding files (DER, BER, OER, and JER related files) from the common folder since they are not required in the original definition.
rm -f {ber_,oer_,jer_}* *_{jer,ber,oer}.*(N)
The following files should not be deleted as they are required:
ber_tlv_length.c
ber_tlv_length.h
ber_tlv_tag.c
ber_tlv_tag.h
Suggested Git Commit Message:
codec: Cleanup unnecessary encoding files and reorganize COMMON

- Remove unused DER/BER/OER/JER related files from COMMON folder
- Move UPER-specific files to RRC folder
- Retain essential BER TLV files
Fix for F1AP Structure Usage
After replacing ASN.1c, I encountered an issue with F1AP structure usage. You can refer to Fix-Handle-F1AP_ProtocolExtensionContainerUsage.patch for details.
Issue: Compilation error related to .asn1 files using struct F1AP_ProtocolExtensionContainer.
Error Message: "dereferencing pointer to incomplete type 'struct F1AP_ProtocolExtensionContainer'".
Root Cause: The structure should only be accessed via pointers, not directly.
I manually adjusted the OSC source code to properly reference this structure. Fortunately, only this file had the issue, and after fixing it, everything builds and executes successfully.
With these changes, I was able to properly encode/decode SIB1, and resolve all the ASN.1-related issues I previously encountered.
Let me know if you have any questions or if anything needs further clarification.

Best regards,

Ming
National Taiwan University of Science and Technology (NTUST)
```