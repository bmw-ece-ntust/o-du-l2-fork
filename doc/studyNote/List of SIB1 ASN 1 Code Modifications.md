# List of SIB1 ASN.1 Code Modifications

Start Date: 2024/12/09
Summary: Summary of modifications and improvements made to SIB1 ASN.1 code, including parameter adjustments, structural enhancements, bug fixes, and new feature integrations.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/12/17
SUM: 🗓️ Days Spent to Complete: 8

### **1. Parameter Adjustments in SIB1**

Several commits addressed parameter adjustments in SIB1 to align with specific requirements or comparisons with OAI:

- **Fix PUSCH-TimeDomainResourceAllocation (remove hard-coded K2):**
    
    Removed hardcoded values for `K2` in PUSCH-TimeDomainResourceAllocation. Retained the original number (2) and used OSC TX_Data to get SIB1.
    
    [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/944fe6908e6fe8ec656a61e95a8072f18de195a2)
    
- **Adjustments to PRACH parameters:**
    - Adjusted `PRACH_FREQ_START` [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/6aae675158df3b72b9a36bc095253611f8e3d972)
    - Tweaked `PRACH_PREAMBLE_RCVD_TGT_PWR` [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/9fb5f06cb1d810f3578cf669fe77a49df696953e)
- **Updates to other SIB1 fields:**
    - Added `PUCCH_P0_NOMINAL` [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/2857d594efcf57ce0f59e75087e4c777c358a797)
    - Added `RSRP_THRESHOLD_SSB` [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/b79d59846ad3863ce017e0fdd16d4f94cd78c7dc)
    - Set `CB_PREAMBLE_PER_SSB` [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/caebee329520554bac0aa60b2722bce66718e3f5)

---

### **2. Structural and Functional Improvements**

Efforts to improve code structure and functionality for better SIB1 processing:

- **Fix PLMN Decoding Issues:**
    
    Resolved the issue where the PLMN in SIB1 could not be decoded.
    
    [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/bedda0d63c831a51d0e688725139dcab25135617)
    
- **Refactor and Streamline C Code:**
    - Deleted outdated source code and replaced it with a macro-based approach.[Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/5a2cfb425bac8b517f6a2df3cba4d4ac9f450034)
    - Streamlined C code macros for better efficiency.[Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/061faf1f6afdf300d8838858dcef6a3b469b91ab)
- **Upgrade ASN.1 RRC Version:**
    
    Upgraded ASN.1 RRC version from 15_3 to 17.3.0 and updated folder naming accordingly.
    
    [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/9a1c5f5fe6cf494887b86b79fe7b59d75eb28f34)
    
- **Reverted Deletions of Critical Elements:**
    
    Restored `connEstFailureControl` and `SI Scheduling Info` after determining their necessity.
    
    [Commit Links](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/bb22895f4f3d3af13a4932cac1fea3c0a7d090d7), [Link 2](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/6fbd8ab58755baa0d5759bd56358f9fbb5a48abd)
    

---

### **3. Bug Fixes**

Addressed specific bugs and incorrect implementations:

- **Corrected Field Names and Search Spaces:**
    
    Fixed incorrect field names in `CellAccessRelatedInfo` and search spaces in PUCCH and PDCCH setups.
    
    [Commit Links](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/5b2a2cbbcc27361dc98d4ef9edd377146679fd04), [Link 2](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/030cd6de1aa416e0124c9850f2dab140062fd1c1)
    
- **PDSCH Time Domain Allocation List Fix:**
    
    Temporarily modified the SLIV and ensured the PDSCH retained its original number (2).
    
    [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/ea109a68dea7e5300adcae1274c7961594bcb98b)
    

---

### **4. Reverted Changes for Compatibility**

Reverted several previous modifications based on further analysis and compatibility concerns:

- **Restored Deletions:**
    - Restored `searchSpaceOtherSystemInformation` in `pdcchSetup`.[Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/6cd30857213e90415f61f756912a3b6eea56818e)
    - Reverted changes to `nFPAI integration`.[Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/7f34f58808face3e8faa75afee6bb0a94bd215b7)

---

### **5. New Feature Integrations**

Integrated new features and made updates inspired by OAI comparisons:

- **Added searchSpaceType:**
    
    Added `searchSpaceType` to improve alignment with OAI's SIB1 structure.
    
    [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/45539ae5324a7aff42994582e26fe6da5568723f)
    
- **PUCCH Hopping Integration:**
    
    Introduced PUCCH hopping mechanism.
    
    [Commit Link](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/58124e958b2e50fd321debf085f687e2262e8919)
    

---

# Detailed List of Commits

commit 944fe6908e6fe8ec656a61e95a8072f18de195a2 (origin/UpdatedANS1-forSIB1, UpdatedANS1-forSIB1)
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 7 23:06:49 2024 +0800

```
[Match SIB1] Fix PUSCH-TimeDomainResourceAllocation (remove hard code K2)
```

commit 58124e958b2e50fd321debf085f687e2262e8919
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 14 17:30:49 2024 +0800

```
[Match SIB1] Add PUCCH Hopping I
```

commit acf6e359f8b3a1a2552492c1e0a23733e17beb1a

Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jul 5 16:22:01 2024 +0800

```
[Match SIB1] Fix issue with PLMN decoding in SIB1
```

commit bbb166466531c13aa3a5ae2ff2cb8a0ea5f31a10
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jul 5 16:35:41 2024 +0800

```
[Match SIB1] Revert Delete the connEstFailureControl and SI Scheduling Info.
```

commit 9902c727db73eff512ca1371f50e2650951dad8f
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jul 5 16:34:21 2024 +0800

```
[Match SIB1] Remove and comment on the SIB1 encode/decode unit test.
```

commit 5a2cfb425bac8b517f6a2df3cba4d4ac9f450034
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jul 5 16:32:58 2024 +0800

```
[Match SIB1] Delete the old source code and revise it with a new approach using macros
```

commit 061faf1f6afdf300d8838858dcef6a3b469b91ab
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jul 5 16:29:26 2024 +0800

```
[Match SIB1] Streamline C code macr
```

commit bedda0d63c831a51d0e688725139dcab25135617
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jul 5 16:25:34 2024 +0800

```
[Match SIB1] Fix the issue where the PLMN in SIB1 cannot be decoded.(E2AP and F1AP change name)
```

commit 3f63ee8f7586761ba31b261715ad639d0566d930
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jul 2 17:31:00 2024 +0800

```
[Match SIB1] Because of the version update, a substantial modification of the original makefile and OSC source code's variable names is required to ensure successful compilation.
```

commit 9a1c5f5fe6cf494887b86b79fe7b59d75eb28f34
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 28 17:34:48 2024 +0800

```
[Match SIB1] Upgrade ASN.1 RRC version 15_3->17.3.0 (and change Folder name)

```

commit 45539ae5324a7aff42994582e26fe6da5568723f
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 28 17:11:28 2024 +0800

```
[Match SIB1] Add searchSpaceType (based on the comparison with OAI SIB1)

```

commit 6fbd8ab58755baa0d5759bd56358f9fbb5a48abd
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Wed Jun 19 15:49:48 2024 +0800

```
Revert "[Match SIB1] Delete the connEstFailureControl (based on the comparison with OAI SIB1)"

This reverts commit 3dc44ac715e5e6d2a966ca088757552733a03eb6.

```

commit bb22895f4f3d3af13a4932cac1fea3c0a7d090d7
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Wed Jun 19 15:49:23 2024 +0800

```
Revert "[Match SIB1] Delete the SI Scheduling Info (based on the comparison with OAI SIB1)"

This reverts commit cfc2489a82450868efd018376b957751b740c9f5.

```

commit cfc2489a82450868efd018376b957751b740c9f5
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 22:31:32 2024 +0800

```
[Match SIB1] Delete the SI Scheduling Info (based on the comparison with OAI SIB1)

```

commit 3dc44ac715e5e6d2a966ca088757552733a03eb6
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 22:31:03 2024 +0800

```
[Match SIB1] Delete the connEstFailureControl (based on the comparison with OAI SIB1)

```

commit d4102b5b3a299a2360c11251193e4a823479d6ec
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 22:30:38 2024 +0800

```
[Match SIB1] Delete the cellSelectionInfo (based on the comparison with OAI SIB1)

```

commit 85e1cb5efbfde7c6f2e043252d7c46a8484ae221
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 22:29:06 2024 +0800

```
[Match SIB1] Delete the Total number of RA preambles (based on the comparison with OAI SIB1)

```

commit 3dd50e93fa1715518cb3ced54bee7b77a185fa06
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 22:28:43 2024 +0800

```
[Match SIB1] Delete the K0 (based on the comparison with OAI SIB1)

```

commit be8be418fac075d1a1094c24ae8733b9583f5583
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 22:28:10 2024 +0800

```
[Match SIB1] Delete the RANAC (based on the comparison with OAI SIB1)

```

commit 7f34f58808face3e8faa75afee6bb0a94bd215b7
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 22:00:31 2024 +0800

```
Revert "[Match Sib1] Develop a new case for OAI nFPAI integration (need to be comfirm)"

This reverts commit c4ce2c82c538b697b021c5c433d29057df832b72.

```

commit c4ce2c82c538b697b021c5c433d29057df832b72
Author: Richard-yq [a2311496a@gmail.com](mailto:a2311496a@gmail.com)
Date:   Fri Jun 14 22:40:13 2024 +0800

```
[Match Sib1] Develop a new case for OAI nFPAI integration (need to be comfirm)

```

commit 22ac827197294ddb26515fdc97949a0d2f1c6eed
Author: Richard-yq [a2311496a@gmail.com](mailto:a2311496a@gmail.com)
Date:   Fri Jun 14 22:41:04 2024 +0800

```
[Match Sib1] msg1_FrequencyStart

```

commit 6cd30857213e90415f61f756912a3b6eea56818e
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 20:30:41 2024 +0800

```
Revert "[Match SIB1] Add searchSpaceOtherSystemInformation in pdcchSetup"

This reverts commit 38996479ce3504bfbd31de851501d1562e9f6b42.

```

commit 0e0a448b64f225711d0460561aca5dd3f2c87434
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 17:05:02 2024 +0800

```
Remove duplicate define

```

commit 2857d594efcf57ce0f59e75087e4c777c358a797
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 17:02:48 2024 +0800

```
[Match SIB1]  PUCCH_P0_NOMINAL

```

commit b79d59846ad3863ce017e0fdd16d4f94cd78c7dc
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 17:01:58 2024 +0800

```
[Match SIB1]  RSRP_THRESHOLD_SSB

```

commit 9fb5f06cb1d810f3578cf669fe77a49df696953e
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 17:01:29 2024 +0800

```
[Match SIB1]  PRACH_PREAMBLE_RCVD_TGT_PWR

```

commit caebee329520554bac0aa60b2722bce66718e3f5
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 17:00:37 2024 +0800

```
[Match SIB1]  CB_PREAMBLE_PER_SSB

```

commit 6aae675158df3b72b9a36bc095253611f8e3d972
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 16:59:40 2024 +0800

```
[Match SIB1]  PRACH_FREQ_START

```

commit ec3686b2cf76b0d1cf7d3c313581ca0cedbb631e
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 16:58:18 2024 +0800

```
[Match SIB1]  UL_P_MAX

```

commit 23a6efba006b7c69cfb377770ced0cf6b0891343
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 16:56:19 2024 +0800

```
[Match SIB1]  RACH raRspWindow

```

commit ec4b8f40ac9e01203e3b01dee35bed8fd13023ef
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 16:55:19 2024 +0800

```
[Match SIB1]  PCCH pageFrameOffset,

```

commit 4d9b941524a56ef8bcd6a2b0066adf493a59de97
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 16:54:13 2024 +0800

```
[Match SIB1]  PDCCH numCandAggLvl8

```

commit ea109a68dea7e5300adcae1274c7961594bcb98b
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 14 17:11:23 2024 +0800

```
[Match SIB1] Fix PDSCH-TimeDomainAllocationList (temp modify- force give sliv)

PDSCH need to keep original number: 2

```

commit 38996479ce3504bfbd31de851501d1562e9f6b42
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 20:29:04 2024 +0800

```
[Match SIB1] Add searchSpaceOtherSystemInformation in pdcchSetup

```

commit 030cd6de1aa416e0124c9850f2dab140062fd1c1
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Tue Jun 18 20:28:15 2024 +0800

```
[Match SIB1] Fix PUCCH searchSpaceSIB1, pagingSearchSpace, ra-SearchSpace

```

commit 5b2a2cbbcc27361dc98d4ef9edd377146679fd04
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 14 17:29:30 2024 +0800

```
[Match SIB1] Fix incorrect field name in CellAccessRelatedInfo struct

```

commit a591e0d874642c45df3673e568800f3993ab6e3a
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 7 23:06:49 2024 +0800

```
[Match SIB1] Fix PUSCH-TimeDomainResourceAllocation (remove hard code K2)

[Match SIB1]  PUSCH need to keep original number:2 It could use OSC TX_Data to get SIB1

```

commit 2921a0772250b62f7111a1abf0dcb043c89138a6
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 7 22:52:22 2024 +0800

```
[Match SIB1] Fix ssb-PositionsInBurst inOneGroup

```

commit 4fabd8335b362147bf1d589d76314d47f5fafffd
Author: dong881 [joe888joejoe@gmail.com](mailto:joe888joejoe@gmail.com)
Date:   Fri Jun 7 17:32:40 2024 +0800

```
[Match SIB1] Fix trackAreaCode

```