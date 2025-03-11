# Fix OSC can’t get MSG3

Start Date: 2024/07/22
Summary: Resolved the issue of OSC not receiving and processing MSG3 correctly, leading to CRC errors and data mismatches, by aligning configurations and fixing parameter discrepancies.
Status: Done
Assign: Ming 咚咚 [銘鴻]

### Problem Summary

**Issue**: OSC DU was unable to properly receive and process MSG3 from the UE , leading to CRC errors and mismatched data between OSC DU and OAI PNF. This caused MSG4 processing to fail as the necessary flags and indicators were not set correctly.

```c
 七  19 04:45:13 [0m[32m[NR_MAC]   [UE 0][RAPROC][184.10] Found RAR with the intended RAPID 22
 七  19 04:45:13 [0m[93m[MAC]   received TA command 31
 七  19 04:45:13 [0m[PHY]   RAR-Msg2 decoded
 七  19 04:45:13 [0m[32m[NR_MAC]   [RAPROC][184.19] RA-Msg3 transmitted
 七  19 04:45:13 [0m[MAC]   [UE 0]Frame 186 Contention resolution identity: 0x1d12e57ff186 Terminating RA procedure
 七  19 04:45:13 [0m[32m[MAC]   [UE 0][186.1][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
 七  19 04:45:13 [0m[NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
 七  19 04:45:13 [0m[RLC]   Added srb 1 to UE 0
 七  19 04:45:13 [0m[MAC]   Applying CellGroupConfig from gNodeB
 七  19 04:45:13 [0m[NR_RRC]   State = NR_RRC_CONNECTED
 七  19 04:45:13 [0m[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
 七  19 04:45:13 [0m[NR_PHY]   ============================================
 七  19 04:45:13 [0m[NR_PHY]   Harq round stats for Downlink: 4/0/0
 七  19 04:45:13 [0m[NR_PHY]   ============================================
```

### Key Investigation Points

1. **MSG4 Scheduling Issue**:
    - The `msg4recvd` flag was not set, indicating that the process to schedule and transmit MSG4 was not being triggered correctly.
    - Investigation revealed that the flag is set within the `SchProcDlRlcBoInfo` function, meaning the issue stemmed from not receiving a proper MSG4 command from the CU.
2. **MSG3 Reception and Comparison**:
    - **CRC Indication**: OSC received CRC indications, but the data compared with OAI's output was significantly different.
        - **tb_crc_status**: OAI reported `0` (success), whereas OSC reported `1` (failure).
        - Other parameters such as `ul_cqi` and `rssi` also differed between OAI and OSC.
    
    ```c
     七  24 05:19:54 [0m[PHY]   crc_valid:1
     七  24 05:19:54 [0m[PHY]   condition1:1
     七  24 05:19:54 [0m[PHY]   condition2:0
     七  24 05:19:54 [0m[PHY]   [gNB 0] ULSCH: Setting NAK for SFN/SF 184/19 (pid 0, ndi 1, status 1, round 0, RV 0, prb_start 0, prb_size 8, TBS 7) r 0
     七  24 05:19:54 [0m[PHY]   ULSCH 0 in error
    ```
    
    ```c
        // When the number of code blocks is 1 (C = 1) and ulsch_harq->processedSegments = 1, we can assume a good TB because of the
        // CRC check made by the LDPC for early termination, so, no need to perform CRC check twice for a single code block
        bool crc_valid = true;
        if (ulsch_harq->C > 1) {
          crc_valid = check_crc(ulsch_harq->b, lenWithCrc(1, rdata->A), crcType(1, rdata->A));
        }
        LOG_I(PHY,"crc_valid:%d\n",crc_valid);
        LOG_I(PHY,"condition1:%d\n",check_abort(&ulsch_harq->abort_decode));
        LOG_I(PHY,"condition2:%d\n",gNB->pusch_vars[rdata->ulsch_id].DTX);
        if (crc_valid && !check_abort(&ulsch_harq->abort_decode) && !gNB->pusch_vars[rdata->ulsch_id].DTX) {
    ```
    
    - **RX_DATA Indication**: Similar discrepancies were observed in the `pdu_length`, `ul_cqi`, and `rssi` values.
    - Root cause: Incorrect handling of CRC checks and RX data in OSC, requiring corrections in how these values were populated.
3. **PUCCH Comparison** (though MSG3 doesn't use PUCCH):
    - Compared parameters between OAI and OSC, such as `pusch_identity` and other uplink parameters, showing clear mismatches in settings.

### Solutions Implemented

1. **Fixing CRC Status and RX Data**:
    - Modified the OSC code to correct the handling of `tb_crc_status` and `RX_DATA`. This involved fixing how `nr_postDecode` and `nr_fill_indication` were processed, ensuring that CRC and data indications matched between OSC and OAI.
2. **Adjusting OSC Parameters to Match OAI**:
    - Added missing parameters in the OSC UL_TTI request, specifically setting the `pusch_identity` to the correct value based on the current UL slot information.
    - Aligned `physCellId` in OSC DU with OAI PNF, ensuring the `NR_PCI` was correctly set to `1` for transmission, matching the physical cell ID used by OAI.
3. **Final Adjustments**:
    - Compared and corrected further discrepancies between OAI and OSC configurations, including MCS (Modulation and Coding Scheme) values and other physical layer parameters such as `ul_dmrs_symb_pos`, `transform_precoding`, and `tb_size`.
    - Confirmed successful reception of MSG3, proper packing of CRC and RX data indications, and resolution of mismatches between the variables used by OSC DU and OAI PNF.
    

### Outcome

The issue was resolved by aligning the configurations and fixing parameter mismatches, allowing OSC DU to successfully receive MSG3, handle CRC and RX data correctly, and proceed with subsequent message transmissions (MSG4 and beyond). The `phy_cell_id` was properly set and matched between P5 (config request) and P7 (RACH indication), leading to successful communication between the UE and the network.

```c
#define NR_PCI 1
```

### Git commit

---

# Reference

## CRC in SCF FAPI spec

![Untitled](Untitled.png)

![Untitled](Untitled%201.png)

## CRC indication

| param | OAI value | OSC value |
| --- | --- | --- |
| handle | 0 | 100 |
| rnti | 13377 | 100 |
| harq_id | 0 | 0 |
| tb_crc_status | 0 | 1 |
| num_cb | 0 | 0 |
| ul_cqi | 230 | 128 |
| timing_advance | 31 | 31 |
| rssi | 860 | 0 |

### RX_DATA indication

| param | OAI value | OSC value |
| --- | --- | --- |
| handle | 0 | 100 |
| rnti | 13377 | 100 |
| harq_id | 0 | 0 |
| pdu_length | 7 | 0 |
| ul_cqi | 230 | 128 |
| timing_advance | 31 | 31 |
| rssi | 860 | 0 |

## compareC MSC

|  | OAI | OSC |
| --- | --- | --- |
| [MSG2] PDSCH MCS | 0 | 0 |
| [MSG3] PUSCH MCS | 1 | 1 |
| PDCCH DL DCI .mcs | 0 | 0 |
| PUSCH RAR .mcs | 1 | 1 |

# compare PUSCH

|  | OAI | OSC |
| --- | --- | --- |
| pusch_pdu->ul_dmrs_symb_pos | 1057 | 1024 |
| transform_precoding | 1 | 0 |
| ul_dmrs_scrambling_id | 1 | 0 |
| pusch_identity | 1 | 1 |
| pusch_data.tb_size | 28 | 7 |
| num_dmrs | 3 | 1 |