# Responding to Robert's email about the F1AP Version and CellGroupConfig Debugging Tasks.

Start Date: 2024/11/05
Summary: Addressing F1AP version identification and debugging CellGroupConfig issues based on Robert's feedback and applying a patch for further analysis.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: mail
Finish Date: 2024/11/13
SUM: 🗓️ Days Spent to Complete: 8

[cellgroupconfig.patch](cellgroupconfig.patch)

[Mail content](Mail%20content%20135100983143809194f9c3d7db2b4fe1.md)

### Summary of Original Description

1. **F1AP Version Issue**: Ming cannot determine the exact F1AP version used from the build logs alone and plans to follow up with further inquiries.
2. **CellGroupConfig Decoding Issue**: There is a segmentation fault in `nr_update_sr` due to a `NULL` `pucch_Config`, indicating potential initialization or memory management issues. Ming has provided the UE logs and backtrace for reference.

### Key Points in Robert’s Response

- **F1AP Version Identification**: Robert suggests checking the F1 Setup Request in the OAI output, as it should print the RRC version received from the DU if OSC O-DU-high fills it correctly.
- **CellGroupConfig Decoding Issue**: Robert confirms that `pucch_Config` being `NULL` likely causes the segmentation fault. He requests that Ming print the received `CellGroupConfig` to verify if/what the PUCCH configuration contains. Robert has provided a patch for this.

### Action Items

1. **F1AP Version Check**:
    - Verify if the F1 Setup Request message IE for the RRC version is visible in the OAI output.
    - Confirm that OSC O-DU-high is correctly filling this field.
        
        [F1SetupResponse](F1SetupResponse%2013510098314380559821f028d198231a.md)
        
    - Find RRC version

```bash
<RRC-Version>
    <latest-RRC-Version>
        000
    </latest-RRC-Version>
    <iE-Extensions>
        <RRC-Version-ExtIEs>
            <id>199</id>
            <criticality><ignore/></criticality>
            <extensionValue>
                <Latest-RRC-Version-Enhanced>11 03 00</Latest-RRC-Version-Enhanced>
            </extensionValue>
        </RRC-Version-ExtIEs>
    </iE-Extensions>
</RRC-Version>
```

```bash
    <RRC-Version>
      <latest-RRC-Version>
          000
      </latest-RRC-Version>
      <iE-Extensions>
          <RRC-Version-ExtIEs>
              <id>199</id>
              <criticality><ignore/></criticality>
              <extensionValue>
                  <OCTET STRING (SIZE(3))>11 03 00</OCTET STRING (SIZE(3))>
              </extensionValue>
          </RRC-Version-ExtIEs>
      </iE-Extensions>
  </RRC-Version>
```

1. **CellGroupConfig Debugging**:
    - Apply Robert's patch to print the `CellGroupConfig` upon receipt.
    - Examine the output to identify the PUCCH configuration details and check for any initialization or memory management issues related to `pucch_Config`.
    1. **Action Items**:
        - Verify F1AP version:
            - Check the F1 Setup Request message IE for the RRC version in the OAI output.
            - Confirm that OSC O-DU-high is correctly filling this field.
            - Analyze the RRC version information found in the F1SetupResponse (11.3.0).
        - Debug CellGroupConfig:
            - Apply Robert's patch to print the `CellGroupConfig` upon receipt.
            
            [UE cellgroupconfig with OSC DU High](UE%20cellgroupconfig%20with%20OSC%20DU%20High%2013d1009831438019be29c874586b68bd.md)
            
            [cellgroupconfig in OAI UE](cellgroupconfig%20in%20OAI%20UE%2013d10098314380c893e2cc9d3e5193eb.md)
            
            - Examine the output for PUCCH configuration details.
            - Check for initialization or memory management issues related to `pucch_Config`.
        - Follow up:
            - Report findings on F1AP version to Robert.
            - Share results of CellGroupConfig debugging, including any PUCCH configuration issues found.
    
    [CellGroupConfig.xml](CellGroupConfig.xml)
    
    [OAIsplit2-CellGroupConfig.xml](OAIsplit2-CellGroupConfig.xml)
    

---

## My reply

```bash
Hi,

Following your instructions, I indeed found the version in the `F1AP-PDU F1SetupResponse`:
With OSC DU High RRC version
```
<RRC-Version>
    <latest-RRC-Version>
        000
    </latest-RRC-Version>
    <iE-Extensions>
        <RRC-Version-ExtIEs>
            <id>199</id>
            <criticality><ignore/></criticality>
            <extensionValue>
                <Latest-RRC-Version-Enhanced>11 03 00</Latest-RRC-Version-Enhanced>
            </extensionValue>
        </RRC-Version-ExtIEs>
    </iE-Extensions>
</RRC-Version>
```
With OAI VNF RRC version
```
    <RRC-Version>
      <latest-RRC-Version>
          000
      </latest-RRC-Version>
      <iE-Extensions>
          <RRC-Version-ExtIEs>
              <id>199</id>
              <criticality><ignore/></criticality>
              <extensionValue>
                  <OCTET STRING (SIZE(3))>11 03 00</OCTET STRING (SIZE(3))>
              </extensionValue>
          </RRC-Version-ExtIEs>
      </iE-Extensions>
  </RRC-Version>
```

I also compared this with the OAI CU/DU split setup, and the version number is the same.

Additionally, I applied the patch file you provided to print out the `CellGroupConfig`. I found there are quite a few differences; the content generated by the OSC DU build is significantly lacking.

By the way, Nokia mentioned they will release a fixed version of asn1c this week. My next step is to replace it with the new version to test whether SIB1 encodes/decodes successfully and to see if the current pucch_Config issue is caused by asn1c.

Best regards,

銘鴻  Ming
```

---

## Robert reply

<aside>
💡

Yes there is a big chunk missing. I think that's not right.

</aside>