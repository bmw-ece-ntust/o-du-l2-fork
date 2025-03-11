# OAI PNF can’t send RACH.indication

Start Date: 2024/07/05
Summary: Investigating the issue of OAI PNF being unable to send RACH indications, including logs and project details.
Status: Reject
Assign: Ming 咚咚 [銘鴻]

```
juil. 05 11:08:08 [32m[NR_RRC]   SIB1 decoded
juil. 05 11:08:08 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
juil. 05 11:08:08 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
juil. 05 11:08:08 [0m[PHY]   (1)commonSearchSpaceList->list.count:1
juil. 05 11:08:08 [0m[PHY]   Success get_common_search_space
juil. 05 11:08:08 [0m[NR_PHY]   ============================================
juil. 05 11:08:08 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
juil. 05 11:08:08 [0m[NR_PHY]   ============================================
juil. 05 11:08:08 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
juil. 05 11:08:08 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
juil. 05 11:08:08 [0m[NR_MAC]   Initialization of 4-step contention-based random access procedure
juil. 05 11:08:08 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
juil. 05 11:08:08 [0m[MAC]   Msg1_transmitted
juil. 05 11:08:08 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 13, first_nonzero_root_idx 0
juil. 05 11:08:08 [0m[PHY]   In nr_ue_prach_procedures: [UE 0][RAPROC][183.19]: Generated PRACH Msg1 (TX power PRACH -72 dBm, digital power 42 dBW (amp 512)
juil. 05 11:08:08 [0m[PHY]   [UE  0] AbsSubFrame 184.7: DCI 1 of 1 total DCIs found --> rnti 10b : format 0
juil. 05 11:08:08 [0m[NR_MAC]   Received dci indication (rnti 10b, dci format 0, n_CCE 0, payloadSize 39, payload 1502000000)
juil. 05 11:08:08 [0m[MAC]   nr_ue_process_dci_dl_10()
juil. 05 11:08:08 [0m[PHY]    ------ --> PDSCH ChannelComp/LLR Frame.slot 184.7 ------  
juil. 05 11:08:08 [0m[PHY]   dlsch[0].rnti_type= 5
juil. 05 11:08:08 [0m[1;31m[NR_MAC]   Trying to process acknack for an inactive harq process (0)
juil. 05 11:08:08 [0m[NR_MAC]   [UE 0][RAPROC][RA-RNTI 0005] Got BI RAR subPDU 267 ms
juil. 05 11:08:08 [0m[NR_MAC]   [UE 0][RAPROC][RA-RNTI 010b] Got RAPID RAR subPDU
juil. 05 11:08:08 [0m[32m[NR_MAC]   [UE 0][RAPROC][184.7] Found RAR with the intended RAPID 54
juil. 05 11:08:08 [0m[93m[MAC]   received TA command 31
juil. 05 11:08:08 [0m[PHY]   RAR-Msg2 decoded
juil. 05 11:08:08 [0m[32m[NR_MAC]   [RAPROC][184.17] RA-Msg3 transmitted
juil. 05 11:08:08 [0munpaired:1
```

```
 七  05 17:05:43 [32m[NR_RRC]   SIB1 decoded
 七  05 17:05:43 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 七  05 17:05:43 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 七  05 17:05:43 [0m[PHY]   (1)commonSearchSpaceList->list.count:1
 七  05 17:05:43 [0m[PHY]   Success get_common_search_space
 七  05 17:05:44 [0m[NR_PHY]   ============================================
 七  05 17:05:44 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
 七  05 17:05:44 [0m[NR_PHY]   ============================================
 七  05 17:05:44 [0m[NR_PHY]   ============================================
 七  05 17:05:44 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
 七  05 17:05:44 [0m[NR_PHY]   ============================================
 七  05 17:05:45 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 七  05 17:05:45 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 七  05 17:05:45 [0m[NR_MAC]   Initialization of 4-step contention-based random access procedure
 七  05 17:05:45 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
 七  05 17:05:45 [0m[MAC]   Msg1_transmitted
 七  05 17:05:45 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 0, first_nonzero_root_idx 0
 七  05 17:05:45 [0m[PHY]   In nr_ue_prach_procedures: [UE 0][RAPROC][183.19]: Generated PRACH Msg1 (TX power PRACH -72 dBm, digital power 42 dBW (amp 512)
 七  05 17:05:45 [0m[NR_PHY]   ============================================
 七  05 17:05:45 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
 七  05 17:05:45 [0m[NR_PHY]   ============================================
 七  05 17:05:45 [0m[93m[MAC]   [UE 0][194:7] RAR reception failed 
 七  05 17:05:45 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 195, Slot 19, Symbol 0, Fdm 0
 七  05 17:05:45 [0m[MAC]   Msg1_transmitted
```