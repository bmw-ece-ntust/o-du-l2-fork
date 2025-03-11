# Fix ASN.1 solution

Start Date: 2024/07/26
Summary: Fixing the ASN.1 solution involving updates to F1AP and E1AP compile files and addressing issues in the OSC source code.
Status: padding
Assign: Ming 咚咚 [銘鴻]

- List all of HARD code F1AP and E1AP compile files

```c
hpe@hpe-ProLiant-DL380-Gen10:~/mwnl-odu-at-oai-based-on-scf$ git show --name-only --oneline bedda0d6
bedda0d6 [Match SIB1] Fix the issue where the PLMN in SIB1 cannot be decoded.(E2AP and F1AP change name)
l2/src/codec_utils/E2AP/GlobalENB-ID.c
l2/src/codec_utils/E2AP/GlobalENB-ID.h
l2/src/codec_utils/E2AP/GlobalRIC-ID.c
l2/src/codec_utils/E2AP/GlobalRIC-ID.h
l2/src/codec_utils/E2AP/GlobalenGNB-ID.c
l2/src/codec_utils/E2AP/GlobalenGNB-ID.h
l2/src/codec_utils/E2AP/GlobalgNB-ID.c
l2/src/codec_utils/E2AP/GlobalgNB-ID.h
l2/src/codec_utils/E2AP/GlobalngeNB-ID.c
l2/src/codec_utils/E2AP/GlobalngeNB-ID.h
l2/src/codec_utils/E2AP/Makefile.am.libasncodec
l2/src/codec_utils/E2AP/PLMN-IdentityE2AP.c
l2/src/codec_utils/E2AP/PLMN-IdentityE2AP.h
l2/src/codec_utils/F1AP/AvailablePLMNList-Item.c
l2/src/codec_utils/F1AP/AvailablePLMNList-Item.h
l2/src/codec_utils/F1AP/ExtendedAvailablePLMN-Item.c
l2/src/codec_utils/F1AP/ExtendedAvailablePLMN-Item.h
l2/src/codec_utils/F1AP/ExtendedServedPLMNs-Item.c
l2/src/codec_utils/F1AP/ExtendedServedPLMNs-Item.h
l2/src/codec_utils/F1AP/Makefile.am.libasncodec
l2/src/codec_utils/F1AP/NRCGI.c
l2/src/codec_utils/F1AP/NRCGI.h
l2/src/codec_utils/F1AP/PLMN-IdentityF1AP.c
l2/src/codec_utils/F1AP/PLMN-IdentityF1AP.h
l2/src/codec_utils/F1AP/ProtocolIE-Field.c
l2/src/codec_utils/F1AP/ProtocolIE-Field.h
l2/src/codec_utils/F1AP/ServedPLMNs-Item.c
l2/src/codec_utils/F1AP/ServedPLMNs-Item.h
```

- List all of modify OSC source code files:

```c
hpe@hpe-ProLiant-DL380-Gen10:~/mwnl-odu-at-oai-based-on-scf$ git show --name-only --oneline 3f63ee8f
3f63ee8f [Match SIB1] Because of the version update, a substantial modification of the original makefile and OSC source code's variable names is required to ensure successful compilation.
l2/build/common/asn_rrc.mak
l2/build/common/cu_stub.mak
l2/build/common/du_app.mak
l2/build/odu/makefile
l2/src/cu_stub/cu_f1ap_msg_hdl.c
l2/src/du_app/du_cell_mgr.c
l2/src/du_app/du_cfg.c
l2/src/du_app/du_f1ap_conversions.c
l2/src/du_app/du_f1ap_conversions.h
l2/src/du_app/du_f1ap_msg_hdl.c
l2/src/du_app/du_sys_info_hdl.c
```

# RRC

```c
sudo rm /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/codec_utils/RRC/*
sudo asn1c -pdu=all -fcompound-names -fno-include-deps -findirect-choice -gen-PER -D /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/codec_utils/RRC/ /home/hpe/openairinterface5g/openair2/RRC/NR/MESSAGES/ASN.1/nr-rrc-15.3.0.asn1
/*Install OAI ASN.1 compile  https://github.com/mouse07410/asn1c */
/home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/codec_utils/RRC
cd /opt/asn1c/bin
sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp /home/hpe/openairinterface5g/openair2/RRC/NR/MESSAGES/ASN.1/nr-rrc-17.3.0.asn1
```

### For original solution

```bash
hpe@hpe-ProLiant-DL380-Gen10:~/o-du-l2$ git show oai_nFAPI 889d0e77 --name-only | grep 'du_app'
src/du_app/du_cell_mgr.c
src/du_app/du_cfg.c
src/du_app/du_f1ap_conversions.c
src/du_app/du_f1ap_conversions.h
src/du_app/du_f1ap_msg_hdl.c
src/du_app/du_sys_info_hdl.c

hpe@hpe-ProLiant-DL380-Gen10:~/o-du-l2$ git show 889d0e77 src/du_app/du_cell_mgr.c
```

## RRC for OSC

```bash
cd /opt/asn1c/bin
sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp ./osc-rrc-17.3.0.asn1
find ./ -type f -name "*Rrc.h"
sudo rm ~/o-du-l2/src/codec_utils/RRC/*
sudo cp ./temp/* ~/o-du-l2/src/codec_utils/RRC/
```

```c
hpe@hpe-ProLiant-DL380-Gen10:/opt/asn1c/bin/temp$ find ./ -type f -name "*Rrc.h"
./MeasGapConfigRrc.h
./CellGroupConfigRrc.h
./SCellIndexRrc.h
./MeasConfigRrc.h
./DRX-ConfigRrc.h
./PagingRrc.h
./ServCellIndexRrc.h
./CG-ConfigInfoRrc.h
./MeasurementTimingConfigurationRrc.h
./HandoverPreparationInformationRrc.h
./UEAssistanceInformationRrc.h
```

## issues

```bash
In file included from /home/hpe/o-du-l2/src/codec_utils/RRC/PCCH-Config.h:17,
                 from /home/hpe/o-du-l2/src/du_app//du_f1ap_conversions.h:32,
                 from /home/hpe/o-du-l2/src/du_app//du_f1ap_conversions.c:24:
/home/hpe/o-du-l2/src/codec_utils/RRC/NULL.h:30:1: error: unknown type name ‘asn_struct_copy_f’; did you mean ‘asn_struct_compare_f’?
   30 | asn_struct_copy_f    NULL_copy;
      | ^~~~~~~~~~~~~~~~~
      | asn_struct_compare_f
```

### solution → change order in makefile for du_app (RRC should be first)

```bash
I_OPTS+=-I$(ROOT_DIR)/src/codec_utils/RRC
I_OPTS+=-I$(ROOT_DIR)/src/codec_utils/common
```

# F1AP

```c
sudo rm /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/codec_utils/F1AP/*
sudo asn1c -pdu=all -fcompound-names -fno-include-deps -findirect-choice -gen-PER -D /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/codec_utils/RRC/ /home/hpe/openairinterface5g/openair2/RRC/NR/MESSAGES/ASN.1/nr-rrc-15.3.0.asn1
/*Install OAI ASN.1 compile  https://github.com/mouse07410/asn1c */
/home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/codec_utils/RRC
cd /opt/asn1c/bin
mkdir temp
sudo ./asn1c -gen-APER -no-gen-BER -no-gen-JER -no-gen-OER -gen-UPER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ./temp /home/hpe/openairinterface5g/openair2/F1AP/MESSAGES/ASN1/R16.3.1/38473-g31.asn
sudo ./asn1c -gen-APER -no-gen-BER -no-gen-JER -no-gen-OER -gen-UPER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ./temp /home/hpe/openairinterface5g/openair2/F1AP/MESSAGES/ASN1/R15.1.1/F1AP-IEs.asn

rm /home/hpe/o-du-l2/src/codec_utils/F1AP
cp ./temp/* /home/hpe/o-du-l2/src/codec_utils/F1AP
```

```c
src/cu_stub/cu_f1ap_msg_hdl.c
src/du_app/du_cell_mgr.c
src/du_app/du_cfg.c
src/du_app/du_f1ap_conversions.c
src/du_app/du_f1ap_conversions.h
src/du_app/du_f1ap_msg_hdl.c
src/du_app/du_sys_info_hdl.c
```

```
    src/codec_utils/F1AP/CellGroupConfig.c \\
    src/codec_utils/F1AP/CellGroupConfig.h \\
    src/codec_utils/F1AP/DRX-Config.c \\
    src/codec_utils/F1AP/DRX-Config.h \\
    src/codec_utils/F1AP/MeasurementTimingConfiguration.c \\
    src/codec_utils/F1AP/MeasurementTimingConfiguration.h \\
    src/codec_utils/F1AP/PLMN-Identity.c \\
    src/codec_utils/F1AP/PLMN-Identity.h \\
    src/codec_utils/F1AP/Paging.c \\
    src/codec_utils/F1AP/Paging.h \\
    src/codec_utils/F1AP/UE-CapabilityRAT-ContainerList.c \\
    src/codec_utils/F1AP/UE-CapabilityRAT-ContainerList.h

```

```c
hpe@hpe-ProLiant-DL380-Gen10:~/o-du-l2$ git diff --name-only 
src/codec_utils/E2AP/GlobalENB-ID.c
src/codec_utils/E2AP/GlobalENB-ID.h
src/codec_utils/E2AP/GlobalRIC-ID.c
src/codec_utils/E2AP/GlobalRIC-ID.h
src/codec_utils/E2AP/GlobalenGNB-ID.c
src/codec_utils/E2AP/GlobalenGNB-ID.h
src/codec_utils/E2AP/GlobalgNB-ID.c
src/codec_utils/E2AP/GlobalgNB-ID.h
src/codec_utils/E2AP/GlobalngeNB-ID.c
src/codec_utils/E2AP/GlobalngeNB-ID.h
src/codec_utils/E2AP/Makefile.am.libasncodec
src/codec_utils/E2AP/PLMN-Identity.c
src/codec_utils/E2AP/PLMN-Identity.h
```

# Find original OSC source code .*Rrc.h

```c
hpe@hpe-ProLiant-DL380-Gen10:~/o-du-l2$ find /home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC -type f -name "*Rrc.h"
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/MeasGapConfigRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/CellGroupConfigRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/SCellIndexRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/MeasConfigRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/DRX-ConfigRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/PagingRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/ServCellIndexRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/CG-ConfigInfoRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/MeasurementTimingConfigurationRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/HandoverPreparationInformationRrc.h
/home/hpe/Original-OSC/o-du-l2/src/codec_utils/RRC/UEAssistanceInformationRrc.h
```