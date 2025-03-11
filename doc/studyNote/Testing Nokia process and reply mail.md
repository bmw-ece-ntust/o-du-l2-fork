# Testing Nokia process and reply mail

Start Date: 2024/11/01
Summary: Testing the Nokia process and analyzing the differences in compiled binaries between the Nokia and Mouse asn1c implementations.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: mail
Finish Date: 2024/11/01
SUM: 🗓️ Days Spent to Complete: 0

[workaroundRRC.tar](workaroundRRC.tar)

Hello

Can you extract the tar file at the same place as you have extracted the previous one ?

It contains

- a modified version of the SearchSpace.c file.
- a shell script to be able to do a test taking into account the modified file.

Then type

```bash
cd RRC
./justTest.sh
```

Then you may compare with diff the files into the APER directory for the Nokia asn1c and the APER directory for the OAI or Mouse asn1c.

It should be the same.

Please send me the result.

Best regards,

Erick Bizouarn

[APER.tar](APER.tar)

[result.log](result.log)

```bash
#!/bin/bash

cp Src/test_RRC.c .
cp Src/testRRC.mk .
cp Src/rrc_15_3.asn1 .

asn1c -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-OER rrc_15_3.asn1

make -f testRRC.mk

for i in `ls XER`
do
    baseName=`echo $i | cut -d "." -f 1`
    typeName=`echo $i | cut -d "-" -f 1`
    ./test_RRC $typeName XER/${baseName}.xml APER/${baseName}.aper
done

echo "Making diff"
diff -r NokiaAPER APER

```

```bash
#!/bin/bash

rm *.o
make -f testRRC.mk

for i in `ls XER`
do
    baseName=`echo $i | cut -d "." -f 1`
    typeName=`echo $i | cut -d "-" -f 1`
    ./test_RRC $typeName XER/${baseName}.xml APER/${baseName}.aper
done

echo "Making diff"
diff -r NokiaAPER APER

```

```bash
#!/bin/bash

cp Src/test_RRC.c .
cp Src/testRRC.mk .
cp Src/rrc_15_3.asn1 .

asn1c -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-OER rrc_15_3.asn1

make -f testRRC.mk

for i in `ls XER`
do
    baseName=`echo $i | cut -d "." -f 1`
    typeName=`echo $i | cut -d "-" -f 1`
    ./test_RRC $typeName XER/${baseName}.xml APER/${baseName}.aper
done

diff -r NokiaAPER APER

```

## I made some modifications

```bash
diff --git a/RRC/makeTest.sh b/RRC/makeTest.sh
index 817e26a..7d5f174 100755
--- a/RRC/makeTest.sh
+++ b/RRC/makeTest.sh
@@ -4,7 +4,11 @@ cp Src/test_RRC.c .
 cp Src/testRRC.mk .
 cp Src/rrc_15_3.asn1 .
 
-asn1c -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-OER rrc_15_3.asn1
+echo "Nokia asn1c"
+asn1c -h
+echo "Mouse asn1c"
+/opt/asn1c/bin/asn1c -h
+/opt/asn1c/bin/asn1c -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice rrc_15_3.asn1
 
 make -f testRRC.mk
```

[https://github.com/dong881/Nokia-Test-asn1c](https://github.com/dong881/Nokia-Test-asn1c)

[justTest.log](justTest.log)

[makeTest.log](makeTest.log)

[APER.tar.gz](APER.tar%201.gz)

[APER.tar.gz](APER.tar%202.gz)

I recently re-evaluated the script and discovered an issue that seems to stem from comparing the Nokia asn1c provided by you with another Nokia asn1c file, which inherently yields no differences. I’ve since modified the script to ensure it runs with the Mouse asn1c, as intended. Please find attached the modified patch file, **MouseAsn1c.patch**, for your reference.

Following the steps you provided, I ran the test again and identified three compiled binary differences:

1. `NokiaAPER/BWP_DownlinkCommon-2.aper` and `APER/BWP_DownlinkCommon-2.aper`
2. `NokiaAPER/DownlinkConfigCommon-2.aper` and `APER/DownlinkConfigCommon-2.aper`
3. `NokiaAPER/PDCCH_ConfigCommon-3.aper` and `APER/PDCCH_ConfigCommon-3.aper`

Attached are the script execution log and the **APER** folder for further examination.