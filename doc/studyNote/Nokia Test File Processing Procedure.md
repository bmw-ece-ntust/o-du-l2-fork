# Nokia Test File Processing Procedure

Start Date: 2024/10/30
Summary: Processing Nokia test files to verify the generation and compilation of APER files and report any differences.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/30
SUM: 🗓️ Days Spent to Complete: 0

[testRRC.tar.gz](testRRC.tar.gz)

TODO List:

- Put the attached file into a new directory
- Run the following commands:
    
    ```diff
    tar xzf testRRC.tar.gz
    cd RRC
    ./maketest.sh
    ```
    
- Check the results:
    - Verify if C files are generated
    - Confirm if the test program is compiled
    - Check if APER files are generated in the APER directory
    - Compare the resulting APER files with those in the NokiaAPER directory
- Report the results:
    - If the last line is "Making diff", it means there is no difference
    - If there are differences, send the APER files to Erick

Note: This test has been done for a few XML values but can be extended easily.

```diff
Making diff
Binary files NokiaAPER/BWP_DownlinkCommon-2.aper and APER/BWP_DownlinkCommon-2.aper differ
Binary files NokiaAPER/DownlinkConfigCommon-2.aper and APER/DownlinkConfigCommon-2.aper differ
Binary files NokiaAPER/PDCCH_ConfigCommon-3.aper and APER/PDCCH_ConfigCommon-3.aper diffe
```

[BWP_DownlinkCommon-2.aper](BWP_DownlinkCommon-2.aper)

[DownlinkConfigCommon-2.aper](DownlinkConfigCommon-2.aper)

[PDCCH_ConfigCommon-3.aper](PDCCH_ConfigCommon-3.aper)

[APER.tar.gz](APER.tar.gz)

Following your steps, the final log shows differences in three APER files, as attached in the folder.
Do I need to add any additional test files, such as replacing certain files or extended XML files?