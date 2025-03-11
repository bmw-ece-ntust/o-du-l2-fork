# OSC F1AP ASN.1 file

Start Date: 2024/10/16
Summary: Migration and compilation of F1AP ASN.1 files using different ASN1C versions to resolve compatibility issues.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2025/01/09
SUM: 🗓️ Days Spent to Complete: 85

Use the following command to rebuild the RRC ASN.1 files

- Clone the `NTUST-script` repository into the `home` directory → https://github.com/dong881/NTUST-script
- Install mouse07410 version of asn1c → [Installation Guide for ASN.1 Compiler (mouse07410)](Installation%20Guide%20for%20ASN%201%20Compiler%20(mouse07410)%2017e10098314380d0a8dbd26bcbc32e42.md)
- Have the `o-du-l2` project source code in the `home` directory → https://github.com/o-ran-sc/o-du-l2

This command can be executed from any directory

```bash
sudo rm -rf ~/o-du-l2/src/codec_utils/F1AP/* && sudo /opt/asn1c/bin/asn1c -pdu=all -fcompound-names -gen-APER -no-gen-BER -no-gen-JER -no-gen-OER -gen-UPER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ~/o-du-l2/src/codec_utils/F1AP ~/NTUST-script/CONFIG/F1.asn1 &&  ~/NTUST-script/Tools/Pick-commonFiles.sh F1AP
```

<aside>
💡

If you only need to compile F1AP, you can stop reading here. The remaining content contains my unorganized notes about investigating Nokia ASN1c issues and comparing them with mouse07410's version. While I plan to reorganize these notes eventually, we have already completed the migration to mouse07410's asn1c, so I won't be revising this section soon.

</aside>

---

# Main script

- Rebuild ANS1 file for F1AP by mouse’s ASN1C

```bash
cd /opt/asn1c/bin
sudo rm -r /home/hpe/o-du-l2/src/codec_utils/F1AP
sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp /home/hpe/NTUST-script/CONFIG/F1.asn1
mkdir /home/hpe/o-du-l2/src/codec_utils/F1AP
sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/F1AP

cd /opt/asn1c/bin
sudo rm -r /home/hpe/o-du-l2/src/codec_utils/F1AP/*
sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /home/hpe/o-du-l2/src/codec_utils/F1AP/ /home/hpe/NTUST-script/CONFIG/F1.asn1

#### one line command
cd /opt/asn1c/bin && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/F1AP/* && sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /home/hpe/o-du-l2/src/codec_utils/F1AP/ /home/hpe/NTUST-script/CONFIG/F1.asn1

#### auto execute script
cd /opt/asn1c/bin && sudo ./asn1c -pdu=all -fcompound-names -gen-APER -no-gen-BER -no-gen-JER -no-gen-OER -gen-UPER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ./temp /home/hpe/NTUST-script/CONFIG/F1.asn1 && mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP && cd /home/hpe/o-du-l2/src/codec_utils/ && sudo rm /home/hpe/o-du-l2/src/codec_utils/F1AP/* && ./pick.sh && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP && ~/Build-OSC-script.sh

cd /opt/asn1c/bin && sudo ./asn1c -pdu=all -fcompound-names -gen-APER -no-gen-BER -no-gen-JER -no-gen-OER -gen-UPER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ./temp /home/hpe/openairinterface5g/openair2/F1AP/MESSAGES/ASN1/R16.3.1/38473-g31.asn && mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP && cd /home/hpe/o-du-l2/src/codec_utils/ && sudo rm /home/hpe/o-du-l2/src/codec_utils/F1AP/* && ./pick.sh && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP && ~/Build-OSC-script.sh
```

```bash
cd /opt/asn1c/bin && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/F1AP/* && sudo ASN1C_PREFIX=F1AP_  ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /home/hpe/o-du-l2/src/codec_utils/F1AP/ /home/hpe/NTUST-script/CONFIG/F1.asn1
```

Build together

```bash
cd /opt/asn1c/bin && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/ALL/* && sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /home/hpe/o-du-l2/src/codec_utils/ALL/ /home/hpe/NTUST-script/CONFIG/*.asn1
```

Build for temp folder

```bash
cd /opt/asn1c/bin && sudo mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP/ && sudo c /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP/ /home/hpe/NTUST-script/CONFIG/F1.asn1
```

Build for F1AP v16.3.1

```bash
cd /opt/asn1c/bin && sudo mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP/ && sudo ./asn1c -pdu=all -fcompound-names -gen-APER -no-gen-BER -no-gen-JER -no-gen-OER -gen-UPER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D /home/hpe/o-du-l2/src/codec_utils/Temp_F1AP/ /home/hpe/openairinterface5g/openair2/F1AP/MESSAGES/ASN1/R16.3.1/38473-g31.asn
```

Get only file name command

```bash
find . -type f -name "*.c" | sed 's|^\./||' | sort
```

## Spec Link

- ETSI TS 138 473 V17.3.0 (2023-01)
- 5G; NG-RAN; F1 Application Protocol (F1AP) (3GPP TS 38.473 version 17.3.0 Release 17)
    
    https://www.etsi.org/deliver/etsi_ts/138400_138499/138473/17.03.00_60/ts_138473v170300p.pdf
    
    https://portal.etsi.org/webapp/workprogram/Report_WorkItem.asp?WKI_ID=67825
    
- ETSI TS 138 473 V16.3.1 (2020-11)
- 5G; NG-RAN; F1 Application Protocol (F1AP) (3GPP TS 38.473 version 16.3.1 Release 16)
    
    https://portal.etsi.org/webapp/workprogram/Report_WorkItem.asp?WKI_ID=61964
    
    https://www.etsi.org/deliver/etsi_ts/138400_138499/138473/16.03.01_60/ts_138473v160301p.pdf
    

# Main issues (forward declaration issue)

Compilation Issue in F1AP ASN.1 Files:

- Problem Description:
    - Need to use F1AP_PDU_ExtIEs_t structure in compilation
    - Structure is defined in ProtocolIE-Field code
    - During recursive file inclusion:
        - ProtocolIE-SingleContainer requires F1AP_PDU_ExtIEs_t structure
        - But F1AP_PDU_ExtIEs_t definition hasn't been processed yet
- Result:
    - Compiler fails due to undefined structure reference
    - Compilation process stops with error

![image.png](image%201.png)

```bash
In file included from /home/hpe/o-du-l2/src/codec_utils/F1AP/NR-Mode-Info.h:60,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/Served-Cell-Information.h:20,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/GNB-DU-Served-Cells-Item.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h:24,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-Container.h:484,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/GNBCUConfigurationUpdateAcknowledge.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/F1AP/GNBCUConfigurationUpdateAcknowledge.c:8:
/home/hpe/o-du-l2/src/codec_utils/F1AP/ProtocolIE-SingleContainer.h:22:9: error: unknown type name ‘F1AP_PDU_ExtIEs_t’
   22 | typedef F1AP_PDU_ExtIEs_t  ProtocolIE_SingleContainer_4590P0_t;
      |         ^~~~~~~~~~~~~~~~~
```

## Including **"Potential-SpCell-Item.h"** causes an error that appears to create an infinite include loop

in file `o-du-l2/src/codec_utils/F1AP/ProtocolIE-Field.h`

In `ProtocolIE-Field.h`, the `#include "GNB-DU-Served-Cells-Item.h"` must come after **`typedef struct F1AP_PDU_ExtIEs` , otherwise `ProtocolIE-SingleContainer.h` cannot find `F1AP_PDU_ExtIEs_t`**

![image.png](image%202.png)

<aside>
💡

Solution:

After comparing with OAI's ASN1C output, I found the key difference:

In OAI's version of `NR-Mode-Info.h`, there is no callback to `ProtocolIE-SingleContainer`

Not yet resolved.

Next step: I plan to use OAI's F1AP version to rebuild for OSC to avoid such inconsistencies. I want to keep everything as identical as possible to ensure smooth integration.

</aside>

![image.png](image%203.png)

```bash
#include "GNB-DU-Served-Cells-Item.h"
#include "Served-Cells-To-Add-Item.h"
#include "Served-Cells-To-Modify-Item.h"
#include "Served-Cells-To-Delete-Item.h"
#include "Cells-Status-Item.h"
#include "Dedicated-SIDelivery-NeededUE-Item.h"
#include "Cells-to-be-Deactivated-List-Item.h"
#include "GNB-CU-TNL-Association-To-Add-Item.h"
#include "GNB-CU-TNL-Association-To-Remove-Item.h"
#include "GNB-CU-TNL-Association-To-Update-Item.h"
#include "Cells-to-be-Barred-Item.h"
#include "Protected-EUTRA-Resources-Item.h"
#include "Cells-Failed-to-be-Activated-List-Item.h"
#include "GNB-CU-TNL-Association-Setup-Item.h"
#include "GNB-CU-TNL-Association-Failed-To-Setup-Item.h"
#include "Candidate-SpCell-Item.h"
#include "SCell-ToBeSetup-Item.h"
#include "SRBs-ToBeSetup-Item.h"
#include "DRBs-ToBeSetup-Item.h"
#include "DRBs-Setup-Item.h"
#include "SRBs-FailedToBeSetup-Item.h"
#include "DRBs-FailedToBeSetup-Item.h"
#include "SCell-FailedtoSetup-Item.h"
#include "SRBs-Setup-Item.h"
#include "Potential-SpCell-Item.h"
#include "SCell-ToBeSetupMod-Item.h"
#include "SCell-ToBeRemoved-Item.h"
#include "SRBs-ToBeSetupMod-Item.h"
#include "DRBs-ToBeSetupMod-Item.h"
#include "DRBs-ToBeModified-Item.h"
#include "SRBs-ToBeReleased-Item.h"
#include "DRBs-ToBeReleased-Item.h"
#include "DRBs-SetupMod-Item.h"
#include "DRBs-Modified-Item.h"
#include "SRBs-SetupMod-Item.h"
#include "SRBs-Modified-Item.h"
#include "DRBs-FailedToBeModified-Item.h"
#include "SRBs-FailedToBeSetupMod-Item.h"
#include "DRBs-FailedToBeSetupMod-Item.h"
#include "SCell-FailedtoSetupMod-Item.h"
#include "Associated-SCell-Item.h"
#include "DRBs-Required-ToBeModified-Item.h"
#include "DRBs-Required-ToBeReleased-Item.h"
#include "SRBs-Required-ToBeReleased-Item.h"
#include "DRBs-ModifiedConf-Item.h"
#include "Cells-To-Be-Broadcast-Item.h"
#include "Cells-Broadcast-Completed-Item.h"
#include "Broadcast-To-Be-Cancelled-Item.h"
#include "Cells-Broadcast-Cancelled-Item.h"
#include "DRB-Activity-Item.h"
#include "PagingCell-Item.h"
#include "DRB-Notify-Item.h"
#include "NR-CGI-List-For-Restart-Item.h"
#include "PWS-Failed-NR-CGI-Item.h"
#include "DRB-Information.h"
#include "TransactionID.h"
#include "Cause.h"
#include "ResetType.h"
#include "UE-associatedLogicalF1-ConnectionListResAck.h"
#include "CriticalityDiagnostics.h"
#include "GNB-CU-UE-F1AP-ID.h"
#include "GNB-DU-UE-F1AP-ID.h"
#include "GNB-DU-ID.h"
#include "GNB-DU-Name.h"
#include "GNB-DU-Served-Cells-List.h"
#include "RRC-Version.h"
#include "GNB-CU-Name.h"
#include "Cells-to-be-Activated-List.h"
#include "TimeToWait.h"
#include "Served-Cells-To-Add-List.h"
#include "Served-Cells-To-Modify-List.h"
#include "Served-Cells-To-Delete-List.h"
#include "Cells-Status-List.h"
#include "Dedicated-SIDelivery-NeededUE-List.h"
#include "Cells-to-be-Deactivated-List.h"
#include "GNB-CU-TNL-Association-To-Add-List.h"
#include "GNB-CU-TNL-Association-To-Remove-List.h"
#include "GNB-CU-TNL-Association-To-Update-List.h"
#include "Cells-to-be-Barred-List.h"
#include "Protected-EUTRA-Resources-List.h"
#include "Cells-Failed-to-be-Activated-List.h"
#include "GNB-CU-TNL-Association-Setup-List.h"
#include "GNB-CU-TNL-Association-Failed-To-Setup-List.h"
#include "RequestType.h"
#include "EUTRA-NR-CellResourceCoordinationReq-Container.h"
#include "IgnoreResourceCoordinationContainer.h"
#include "EUTRA-NR-CellResourceCoordinationReqAck-Container.h"
#include "NRCGI.h"
#include "ServCellIndex.h"
#include "CellULConfigured.h"
#include "CUtoDURRCInformation.h"
#include "Candidate-SpCell-List.h"
#include "DRXCycle.h"
#include "ResourceCoordinationTransferContainer.h"
#include "SCell-ToBeSetup-List.h"
#include "SRBs-ToBeSetup-List.h"
#include "DRBs-ToBeSetup-List.h"
#include "InactivityMonitoringRequest.h"
#include "RAT-FrequencyPriorityInformation.h"
#include "RRCContainer.h"
#include "MaskedIMEISV.h"
#include "PLMN-Identity.h"
#include "BitRate.h"
#include "RRCDeliveryStatusRequest.h"
#include "ResourceCoordinationTransferInformation.h"
#include "ServingCellMO.h"
#include "DUtoCURRCInformation.h"
#include "C-RNTI.h"
#include "FullConfiguration.h"
#include "DRBs-Setup-List.h"
#include "SRBs-FailedToBeSetup-List.h"
#include "DRBs-FailedToBeSetup-List.h"
#include "SCell-FailedtoSetup-List.h"
#include "InactivityMonitoringResponse.h"
#include "SRBs-Setup-List.h"
#include "Potential-SpCell-List.h"
#include "SRBID.h"
#include "ExecuteDuplication.h"
#include "TransmissionActionIndicator.h"
#include "RRCReconfigurationCompleteIndicator.h"
#include "SCell-ToBeSetupMod-List.h"
#include "SCell-ToBeRemoved-List.h"
#include "SRBs-ToBeSetupMod-List.h"
#include "DRBs-ToBeSetupMod-List.h"
#include "DRBs-ToBeModified-List.h"
#include "SRBs-ToBeReleased-List.h"
#include "DRBs-ToBeReleased-List.h"
#include "DRXConfigurationIndicator.h"
#include "RLCFailureIndication.h"
#include "UplinkTxDirectCurrentListInformation.h"
#include "GNB-DUConfigurationQuery.h"
#include "NeedforGap.h"
#include "DRBs-SetupMod-List.h"
#include "DRBs-Modified-List.h"
#include "SRBs-FailedToBeSetupMod-List.h"
#include "DRBs-FailedToBeSetupMod-List.h"
#include "SCell-FailedtoSetupMod-List.h"
#include "DRBs-FailedToBeModified-List.h"
#include "Associated-SCell-List.h"
#include "SRBs-SetupMod-List.h"
#include "SRBs-Modified-List.h"
#include "DRBs-Required-ToBeModified-List.h"
#include "SRBs-Required-ToBeReleased-List.h"
#include "DRBs-Required-ToBeReleased-List.h"
#include "DRBs-ModifiedConf-List.h"
#include "PWSSystemInformation.h"
#include "RepetitionPeriod.h"
#include "NumberofBroadcastRequest.h"
#include "Cells-To-Be-Broadcast-List.h"
#include "Cells-Broadcast-Completed-List.h"
#include "Broadcast-To-Be-Cancelled-List.h"
#include "Cancel-all-Warning-Messages-Indicator.h"
#include "Cells-Broadcast-Cancelled-List.h"
#include "DRB-Activity-List.h"
#include "DUtoCURRCContainer.h"
#include "SULAccessIndication.h"
#include "SItype-List.h"
#include "UEIdentityIndexValue.h"
#include "PagingIdentity.h"
#include "PagingDRX.h"
#include "PagingPriority.h"
#include "PagingCell-list.h"
#include "PagingOrigin.h"
#include "DRB-Notify-List.h"
#include "NR-CGI-List-For-Restart-List.h"
#include "PWS-Failed-NR-CGI-List.h"
#include "GNBDUOverloadInformation.h"
#include "RRCDeliveryStatus.h"
```

---

## Issues list

<aside>
💡

Here are the variables I can modify to address the current issues:

Available options:

- OSC asn1 definition file (F1AP v17.3.0)
- OAI asn1 definition file (F1AP v16.3.1)
- OSC's asn1 compiler (Nokia)
- OAI's asn1 compiler (mouse)
- OAI's Cmake script for automatic compilation

Attempted solution: 

- [x]  Use OAI's ASN1C compiler (mouse) to build OAI's F1AP v16.3.1 ASN.1 definition file
- Result: No Error, this is OAI original options
- [x]  Use OSC's ASN1C compiler (Nokia) to build OSC's F1AP v17.3.0 ASN.1 definition file
- Result: Encountered error - [unknown type name](OSC%20F1AP%20ASN%201%20file%201211009831438070bb80c050fcf47cdf.md), this is OSC original options
- [x]  Use OAI's ASN1C compiler (mouse) to build OSC's F1AP v17.3.0 ASN.1 definition file
- Result: Encountered error - [unknown type name](OSC%20F1AP%20ASN%201%20file%201211009831438070bb80c050fcf47cdf.md)
- [x]  Use OAI's ASN1C compiler (mouse) to compile OSC's F1AP v17.3.0 and RRC v17.3.0 ASN.1 definition files together. (compile together)
- Result: Encountered error - [unknown type name](OSC%20F1AP%20ASN%201%20file%201211009831438070bb80c050fcf47cdf.md)
- [x]  Use OAI's ASN1C compiler (mouse) to compile OSC's F1AP v17.3.0 using OAI's CMake script for automatic compilation
- The .cmake file needs to be manually rewritten for each different ASN.1 version (verify with Robert → [About the .cmake File Generation](Responding%20to%20Robert%20MIB%20Decoding%20Issue%2014c10098314380b29129fa178d328dd4.md))
- Result: Encountered error - [No such file](OSC%20F1AP%20ASN%201%20file%201211009831438070bb80c050fcf47cdf.md)
- [x]  Use OAI's ASN1C compiler (mouse) to compile OSC's F1AP v17.3.0 using OAI's CMake script for automatic compilation and replace the ./COMMON directory files
- Result: [replacing the ./COMMON directory files results in compilation errors](OSC%20F1AP%20ASN%201%20file%201211009831438070bb80c050fcf47cdf.md)
</aside>

- OAI and OSC use different .asn1 file to build F1AP ASN.1 struct
    
    [F1.asn1](F1.asn1)
    
    [38473-g31.asn](38473-g31.asn)
    

OAI includes more detailed descriptions in its .asn1 file, though the underlying structure matches OSC's and follows the same specification.

![OSC → left hand side. OAI → right hand side](image%204.png)

OSC → left hand side. OAI → right hand side

<aside>
💡

I found the reason: they use different versions of F1AP

</aside>

OAI uses ETSI TS 138 473 **V16.3.1** (2020-11)

- 5G; NG-RAN; F1 Application Protocol (F1AP) (3GPP TS 38.473 version 16.3.1 Release 16)

while OSC uses ETSI TS 138 473 **V17.3.0** (2023-01)

- 5G; NG-RAN; F1 Application Protocol (F1AP) (3GPP TS 38.473 version 17.3.0 Release 17)

## Current Compilation Errors

I am encountering a compilation error while manually using gcc to build asn.1 files. The issue arises from a missing type definition for F1AP_PDU_ExtIEs_t and ResetType_ExtIEs_t in the file ProtocolIE-SingleContainer.h. However, the type F1AP_PDU_ExtIEs_t is correctly defined in ProtocolIE-Field.h.

I verified this by using `grep`, which shows that only one instance of the `#ifndef` guard (`_ProtocolIE_Field_H_`) exists in `ProtocolIE-Field.h`. This indicates that the header file is included correctly and should provide the necessary type definition.

Despite this, the compiler cannot resolve the type, suggesting one of the following issues:

1. The `#ifndef` or `#define` guard in `ProtocolIE-Field.h` may be incorrectly defined or misinterpreted.
2. The `ProtocolIE-Field.h` file might not actually be included in `ProtocolIE-SingleContainer.h` or included after its use.
3. There might be an issue with the build process or header inclusion order, leading to the file not being recognized by the compiler.

### unknown type name

```bash
In file included from /home/hpe/o-du-l2/src/codec_utils/ALL/NR-Mode-Info.h:60,
                 from /home/hpe/o-du-l2/src/codec_utils/ALL/Served-Cell-Information.h:20,
                 from /home/hpe/o-du-l2/src/codec_utils/ALL/GNB-DU-Served-Cells-Item.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/ALL/ProtocolIE-Field.h:24,
                 from /home/hpe/o-du-l2/src/codec_utils/ALL/ProtocolIE-Container.h:484,
                 from /home/hpe/o-du-l2/src/codec_utils/ALL/DLRRCMessageTransfer.h:15,
                 from /home/hpe/o-du-l2/src/codec_utils/ALL/DLRRCMessageTransfer.c:8:
/home/hpe/o-du-l2/src/codec_utils/ALL/ProtocolIE-SingleContainer.h:22:9: error: unknown type name ‘F1AP_PDU_ExtIEs_t’
   22 | typedef F1AP_PDU_ExtIEs_t  ProtocolIE_SingleContainer_4590P0_t;
      |         ^~~~~~~~~~~~~~~~~
/home/hpe/o-du-l2/src/codec_utils/ALL/ProtocolIE-SingleContainer.h:23:9: error: unknown type name ‘ResetType_ExtIEs_t’
   23 | typedef ResetType_ExtIEs_t  ProtocolIE_SingleContainer_4590P1_t;
      |         ^~~~~~~~~~~~~~~~~~
/home/hpe/o-du-l2/src/codec_utils/ALL/ProtocolIE-SingleContainer.h:24:9: error: unknown type name ‘UE_associatedLogicalF1_ConnectionItemRes_t’
   24 | typedef UE_associatedLogicalF1_ConnectionItemRes_t  ProtocolIE_SingleContainer_4590P2_t;
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

### Search for ProtocolIE-Field Files in O-DU L2 Source Code

```bash
❯ grep -ron "ProtocolIE-Field.h" /home/hpe/o-du-l2/src/
❯ grep -ron "ProtocolIE-Field.c" /home/hpe/o-du-l2/src/
```

Files containing ProtocolIE-Field.h:

- Message handling files:
    - du_app/du_f1ap_msg_hdl.c:154
    - cu_stub/cu_f1ap_msg_hdl.c:24
- Codec utility header files:
    - codec_utils/ALL/ProtocolIE-Container.h:484
    - codec_utils/ALL/ProtocolIE-SingleContainerE2.h:15
    - codec_utils/ALL/ProtocolIE-Field.c:8
    - codec_utils/ALL/ProtocolIE-SingleContainer.h:15
    - codec_utils/ALL/ProtocolIE-ContainerE2.h:462
- Make files:
    - codec_utils/ALL/Makefile.am.libasncodec:1438, 1817 (.h files)
    - codec_utils/ALL/Makefile.am.libasncodec:190, 569 (.c files)

- Rebuild ANS1 file for F1AP by Nokia’s ASN1C

```jsx

sudo rm -r /home/hpe/o-du-l2/src/codec_utils/F1AP/*
asn1c -D /home/hpe/o-du-l2/src/codec_utils/F1AP -fcompound-names -fno-include-deps -findirect-choice -gen-PER
```

[compileASN1.log](compileASN1.log)

Trace ASN.1 struct tree

| asn_DEF_F1AP_PDU |
| --- |
| asn_MBR_F1AP_PDU_1 |
| asn_DEF_InitiatingMessage |
| asn_MBR_InitiatingMessage_1 |
| asn_DEF_value_4 |
| asn_MBR_value_4 |
| asn_DEF_InitialULRRCMessageTransfer |
| asn_MBR_InitialULRRCMessageTransfer_1 |
| asn_DEF_ProtocolIE_Container_4587P31 |
| asn_MBR_ProtocolIE_Container_4587P31_63 |
| asn_DEF_InitialULRRCMessageTransferIEs |
| asn_MBR_InitialULRRCMessageTransferIEs_405 |
| asn_DEF_value_408 |
| asn_MBR_value_408 |
| asn_DEF_DUtoCURRCContainer |

### No such file

I'm encountering a compilation error. The specific error states:

```
cc: error: /home/hpe/openairinterface5g/cmake_targets/ran_build/build/openair2/F1AP/MESSAGES/AllocationAndRetentionPriority.c: No such file or directory
cc: fatal error: no input files
compilation terminated.
```

The source file, `AllocationAndRetentionPriority.c`, is missing, and I suspect it should be generated from the `.asn` definitions provided. Below are the relevant `.asn` definitions:

### ASN.1 Definitions:

### AllocationAndRetentionPriority

```
AllocationAndRetentionPriority ::= SEQUENCE {
   priorityLevel           PriorityLevel,
   pre-emptionCapability   Pre-emptionCapability,
   pre-emptionVulnerability Pre-emptionVulnerability,
   iE-Extensions           ProtocolExtensionContainer { {AllocationAndRetentionPriority-ExtIEs} } OPTIONAL,
   ...
}

AllocationAndRetentionPriority-ExtIEs F1AP-PROTOCOL-EXTENSION ::= {
   ...
}

```

### EUTRANQoS

```
EUTRANQoS ::= SEQUENCE {
   qCI                        QCI,
   allocationAndRetentionPriority AllocationAndRetentionPriority,
   gbrQosInformation          GBR-QosInformation OPTIONAL,
   iE-Extensions              ProtocolExtensionContainer { { EUTRANQoS-ExtIEs} } OPTIONAL,
   ...
}

```

### replacing the ./COMMON directory files results in compilation errors

```bash
-e Compiling [31m[1m /home/hpe/o-du-l2/src/codec_utils/common/constr_SET_OF.c [m
-e Compiling [31m[1m /home/hpe/o-du-l2/src/codec_utils/common/constr_SET_OF_oer.c [m
/home/hpe/o-du-l2/src/codec_utils/common/ber_decoder.c: In function ‘ber_decode’:
/home/hpe/o-du-l2/src/codec_utils/common/ber_decoder.c:54:9: error: too many arguments to function ‘type_descriptor->op->ber_decoder’
   54 |  return type_descriptor->op->ber_decoder(opt_codec_ctx, type_descriptor,
   
   -----
   
   
   /home/hpe/o-du-l2/src/codec_utils/common/constr_SEQUENCE_oer.c:540:62: error: ‘asn_encoding_constraints_t’ {aka ‘struct asn_encoding_constraints_s’} has no member named ‘oer_constraints’; did you mean ‘per_constraints’?
  540 |                         elm->type, elm->encoding_constraints.oer_constraints,
      |                                                              ^~~~~~~~~~~~~~~
      |                                                              per_constraints
make[1]: *** [/home/hpe/o-du-l2/build/odu/../common/compile.mak:83: /home/hpe/o-du-l2/build/odu/obj/odu/constr_SET_OF_oer.o] Error 1
make[1]: *** [/home/hpe/o-du-l2/build/odu/../common/compile.mak:83: /home/hpe/o-du-l2/build/odu/obj/odu/constr_SEQUENCE_oer.o] Error 1
make[1]: Leaving directory '/home/hpe/o-du-l2/build/odu'
make: *** [makefile:213: du] Error 2

```

<aside>
💡

Solution: Delete BER, OER, and JER related files from the COMMON folder since they are not used in the original definition.

</aside>

```bash
#include "Served-Cells-To-Add-Item.h"

```

# Summary

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

# Study…

## Understand the compilation process from struct definition file to header file

<aside>
💡

Trace in OSC i-release `o-du-l2` source code

</aside>

### pdcch-ConfigCommon struct definition

```jsx
-- TAG-PDCCH-CONFIGCOMMON-START

PDCCH-ConfigCommon ::=              SEQUENCE {
    controlResourceSetZero              ControlResourceSetZero                                  OPTIONAL,   -- Cond InitialBWP-Only
    commonControlResourceSet            ControlResourceSet                                      OPTIONAL,   -- Need R
    searchSpaceZero                     SearchSpaceZero                                         OPTIONAL,   -- Cond InitialBWP-Only
    commonSearchSpaceList               SEQUENCE (SIZE(1..4)) OF SearchSpace                    OPTIONAL,   -- Need R
    searchSpaceSIB1                     SearchSpaceId                                           OPTIONAL,   -- Need S
    searchSpaceOtherSystemInformation   SearchSpaceId                                           OPTIONAL,   -- Need S
    pagingSearchSpace                   SearchSpaceId                                           OPTIONAL,   -- Need S
    ra-SearchSpace                      SearchSpaceId                                           OPTIONAL,   -- Need S
    ...
}

-- TAG-PDCCH-CONFIGCOMMON-STOP
```

### pdcch-ConfigCommon head file

```cpp
/* PDCCH-ConfigCommon */
typedef struct PDCCH_ConfigCommon {
	ControlResourceSetZero_t	*controlResourceSetZero;	/* OPTIONAL */
	struct ControlResourceSet	*commonControlResourceSet;	/* OPTIONAL */
	SearchSpaceZero_t	*searchSpaceZero;	/* OPTIONAL */
	struct PDCCH_ConfigCommon__commonSearchSpaceList {
		A_SEQUENCE_OF(struct SearchSpace) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *commonSearchSpaceList;
	SearchSpaceId_t	*searchSpaceSIB1;	/* OPTIONAL */
	SearchSpaceId_t	*searchSpaceOtherSystemInformation;	/* OPTIONAL */
	SearchSpaceId_t	*pagingSearchSpace;	/* OPTIONAL */
	SearchSpaceId_t	*ra_SearchSpace;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDCCH_ConfigCommon_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PDCCH_ConfigCommon;
extern asn_SEQUENCE_specifics_t asn_SPC_PDCCH_ConfigCommon_specs_1;
extern asn_TYPE_member_t asn_MBR_PDCCH_ConfigCommon_1[8];
```

```c
/* Forward declarations */
struct PDCCH_ConfigCommon;
struct PDSCH_ConfigCommon;

/* BWP-DownlinkCommon */
typedef struct BWP_DownlinkCommon {
	BWP_t	 genericParameters;
	struct BWP_DownlinkCommon__pdcch_ConfigCommon {
		BWP_DownlinkCommon__pdcch_ConfigCommon_PR present;
		union BWP_DownlinkCommon__pdcch_ConfigCommon_u {
			NULL_t	 release;
			struct PDCCH_ConfigCommon	*setup;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *pdcch_ConfigCommon;
	struct BWP_DownlinkCommon__pdsch_ConfigCommon {
		BWP_DownlinkCommon__pdsch_ConfigCommon_PR present;
		union BWP_DownlinkCommon__pdsch_ConfigCommon_u {
			NULL_t	 release;
			struct PDSCH_ConfigCommon	*setup;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *pdsch_ConfigCommon;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} BWP_DownlinkCommon_t;
```

## Where to Use the Struct

```c
   /* PDCCH Config Common */
   DU_ALLOC(bwp->pdcch_ConfigCommon, sizeof(struct BWP_DownlinkCommon__pdcch_ConfigCommon));
   if(!bwp->pdcch_ConfigCommon)
   {
      DU_LOG("\nERROR  -->  DU APP : DL BWP memory allocation failed");
      return RFAILED;
   }
   if((BuildPdcchCfgCommon(bwp->pdcch_ConfigCommon)) != ROK)
   {
      DU_LOG("\nERROR  -->  DU APP : Failed to fill PDCCH config common in BuildBwpDlCommon()");
      return RFAILED;
   }
```

## Discovered

Discovered that the tony_cu_du code has modified the files after asn1c compilation, and we are currently encountering the same issue

![image.png](image%205.png)