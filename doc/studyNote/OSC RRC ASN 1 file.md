# OSC RRC ASN.1 file

Start Date: 2024/10/16
Summary: The project involves rebuilding RRC ASN.1 files for the OSC initiative using specified commands and modified files.
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
sudo rm -rf ~/o-du-l2/src/codec_utils/RRC/* && sudo /opt/asn1c/bin/asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ~/o-du-l2/src/codec_utils/RRC ~/NTUST-script/CONFIG/rrc_15_3.asn1 &&  ~/NTUST-script/Tools/Pick-commonFiles.sh RRC
```

OSC will arbitrarily modify the .asn1 file (therefore, if you want to use it in the OSC project's du_app, you must use their modified .asn1 file)

![image.png](image%2046.png)

The left side shows the .asn1 file provided by OAI and the spec, while the right side shows the one provided by OSC

## Appendix

- Rebuild ANS1 file for RRC

```bash
cd /opt/asn1c/bin
sudo rm -r /home/hpe/o-du-l2/src/codec_utils/RRC
sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp /home/hpe/NTUST-script/CONFIG/rrc_15_3.asn1
mkdir /home/hpe/o-du-l2/src/codec_utils/RRC
sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/RRC

####### one-line command
cd /opt/asn1c/bin && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/RRC && sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp /home/hpe/NTUST-script/CONFIG/rrc_15_3.asn1 && mkdir /home/hpe/o-du-l2/src/codec_utils/RRC && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/RRC

####### Build from OAI defintion files
cd /opt/asn1c/bin && sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp /home/hpe/openairinterface5g/openair2/RRC/NR/MESSAGES/ASN.1/nr-rrc-17.3.0.asn1 && mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_RRC && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/Temp_RRC && cd /home/hpe/o-du-l2/src/codec_utils/Temp_RRC 

####### Auto execut script
cd /opt/asn1c/bin && sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp /home/hpe/NTUST-script/CONFIG/rrc_15_3.asn1 && mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_RRC && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/Temp_RRC && cd /home/hpe/o-du-l2/src/codec_utils/ && sudo rm /home/hpe/o-du-l2/src/codec_utils/RRC/* && ./pick.sh && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/Temp_RRC

```