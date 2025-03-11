# OSC can’t send RAR

Start Date: 2024/07/08
Summary: Resolving the issue of OSC DU High not sending RAR after receiving it, focusing on system instability and code adjustments.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全
Tags: OSC Integration problem

[https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Eurecom.drawio#Uhttps://drive.google.com/uc?id=1W_o7Se11USgVPska8-t5i0JgpRSCQf4h&export=download](https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Eurecom.drawio#Uhttps://drive.google.com/uc?id=1W_o7Se11USgVPska8-t5i0JgpRSCQf4h&export=download)

**Currently, SIB1 can be successfully transmitted, and PNF can send RACH.indication to VNF, but OSC DU High does not send RAR back after receiving it, so it needs to be resolved and the problem needs to be identified**

**Possible reasons:**

**Due to the current system instability, sometimes when running, unexpected ERRORs regarding F1AP and E2AP may appear, which could be due to changes in the code caused by upgrading the ASN.1 version, but it does not cause serious impact. The unstable situation cannot be resolved temporarily and cannot be addressed, and it is not a high priority, so it is postponed**

**The code comments provide a clear description, making it easier to understand**

```c
/* Current slot + k2 should be either UL or FLEXI slot.
                * If slot is FLEXI then check all the symbols of that slot,
                * it should not contain any DL or FLEXI slot */
```

```c
  /* Check for K2 for MSG3 */
		/* Current slot + k2 should be either UL or FLEXI slot.
		 * If slot is FLEXI then check all the symbols of that slot,
		 * it should not contain any DL or FLEXI slot */
```

- need to check git commit

```bash
0e96a38 [temp] After VNF get queue call function to process Indication message (need to be comfirm again)
a2f2a38 For OAI add UL delta 1 slot
40f84e3 For OAI use rootseqlen 139 instead of 839
d233c2c For OAI, we don't need to send ULtti and ULdci if no DLtti pdu
47e3a36 Re-order pack config.request tlvs
```

- cherrypick

```bash
db4b7c4      Send ul_tti、ul_dci only if has dl_tti PDUs
2259f78 (upstream/Fixed-SIB1, origin/Fixed-SIB1) Remove some unused logs
feed85b Update make help (add nFAPI)
6ea89f5 match_crc_rx_pdu free and NULL is better
!! 452e43b Revise process CRC、RACH、UCI、RX indication function
fb589bb CRC.indication unqueue and match_crc_rx_pdu
aff785b Add new function match_crc_rx_pdu (Copy from OAI)
e440777 1. Add new functions remove RX、CRC PDU function 2. Add new function RX、CRC.indicaiton has rnti
d964682 Add new function crc_sfn_slot_matcher for crc.indication

```

**Current suspected issues:**

**Previous git commits need to be organized, including reverts and some unnecessary commits**

**The code related to the TDD Table transmission process through nFAPI may have issues**

- TDD Table

```
 七  09 20:17:51 [NTUST] TDD Table
 七  09 20:17:51 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  09 20:17:51 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  09 20:17:51 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  09 20:17:51 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  09 20:17:51 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  09 20:17:51 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  09 20:17:51 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  09 20:17:51 0 0 0 0 0 0 2 2 2 2 1 1 1 1 
 七  09 20:17:51 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
 七  09 20:17:51 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
```

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| D | D | D | D | D | D | D | F | U | U |

**slotIdx  → Downlink and (slotIdx + 6 + 3) mod 10  → Uplink**

**Therefore, it will only find slotIdx = 0**

**msg3K2InfoTbl->k2TimingInfo[slotIdx].numK2**

**→ 3 0 0 0 0 0 0 1 0 0 3 0 0 0 0 0 0 1 0 0**

**fill Initial UL BWP**

**SIB1 transmits one version, and OSC internally uses another version, so it needs to be adjusted to make the two data consistent**

```c
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.numTimeDomRsrcAlloc = 2;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[0].k2 = PUSCH_K2_CFG1;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[0].mappingType = 
      PUSCH_MAPPING_TYPE_A;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[0].startSymbol = 
      PUSCH_START_SYMBOL;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[0].symbolLength =
      PUSCH_LENGTH_SYMBOL;

   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[1].k2 = PUSCH_K2_CFG2;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[1].mappingType = 
      PUSCH_MAPPING_TYPE_A;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[1].startSymbol = 
      PUSCH_START_SYMBOL;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[1].symbolLength =
      PUSCH_LENGTH_SYMBOL;
```

```c
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.numTimeDomRsrcAlloc = 4;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[0].k2 = PUSCH_K2_CFG1;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[0].mappingType = PUSCH_TimeDomainResourceAllocation__mappingType_typeB;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[0].startSymbol = PUSCH_START_SYMBOL_CFG1;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[0].symbolLength = PUSCH_LENGTH_SYMBOL_CFG1;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[1].k2 = PUSCH_K2_CFG2;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[1].mappingType = PUSCH_TimeDomainResourceAllocation__mappingType_typeB;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[1].startSymbol = PUSCH_START_SYMBOL_CFG2;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[1].symbolLength = PUSCH_LENGTH_SYMBOL_CFG2;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[2].k2 = PUSCH_K2_CFG3;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[2].mappingType = PUSCH_TimeDomainResourceAllocation__mappingType_typeB;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[2].startSymbol = PUSCH_START_SYMBOL;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[2].symbolLength = PUSCH_LENGTH_SYMBOL;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[3].k2 = PUSCH_K2_CFG4;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[3].mappingType = PUSCH_TimeDomainResourceAllocation__mappingType_typeB;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[3].startSymbol = PUSCH_START_SYMBOL;
   duCfgParam.macCellCfg.cellCfg.initialUlBwp.puschCommon.timeDomRsrcAllocList[3].symbolLength = PUSCH_LENGTH_SYMBOL;

```

- **PDSCH has the same problem:**

**Therefore, the solution is to refer to the start and length settings in OAI and set them in the OSC parameters**

![Untitled](Untitled%2043.png)

```c
/* MACRO Ddefine for PDSCH Configuration */
#define NUM_TIME_DOM_RSRC_ALLOC 2
#define PDSCH_K0_CFG1  0
#define PDSCH_K0_CFG2  1
/* ======== small cell integration ======== */
#ifdef NFAPI
#define PDSCH_START_SYMBOL  1
#define PDSCH_LENGTH_SYMBOL 13
#define PDSCH_START_SYMBOL_2  1
#define PDSCH_LENGTH_SYMBOL_2 12
#define PDSCH_START_SYMBOL_3  1
#define PDSCH_LENGTH_SYMBOL_3 5
#else
#define PDSCH_START_SYMBOL  3
#define PDSCH_LENGTH_SYMBOL 11
#endif
/* ======================================== */
```

- TEST the following commit log will work
    - UE will send RA
    - PNF will send RACH.indication (power will auto get higher than 540)
    - OSC VNF can’t sned RAR → **ERROR  --> SCH : schFillRar()**
    
    ```bash
    hpe@hpe-ProLiant-DL380-Gen10:~/mwnl-odu-at-oai-based-on-scf$ git log --oneline 
    e20e4ea (HEAD) Revert "Revert "For OAI add UL delta 1 slot""
    c3dd190 [Match SIB1] PDSCH numTimeDomRsrcAlloc need 4
    0548b43 Revert "For OAI add UL delta 1 slot"
    d16714f Revert "For OAI, we don't need to send ULtti and ULdci if no DLtti pdu"
    a31e441 Revert "Re-order pack config.request tlvs"
    944fe69 (origin/UpdatedANS1-forSIB1, UpdatedANS1-forSIB1) [Match SIB1] Fix PUSCH-TimeDomainResourceAllocation (remove hard code K2)
    ```
    
    - also the same result
    
    ```bash
    hpe@hpe-ProLiant-DL380-Gen10:~/mwnl-odu-at-oai-based-on-scf$ git log --oneline 
    ed758fb (HEAD -> FixRAR) [Match SIB1] PDSCH numTimeDomRsrcAlloc need 4
    8492285 Send ul_tti、ul_dci only if has dl_tti PDUs
    e9d8675 Remove some unused logs
    1acd113 Update make help (add nFAPI)
    51090a7 match_crc_rx_pdu free and NULL is better
    ed5e359 Revise process CRC、RACH、UCI、RX indication function
    b3b762d CRC.indication unqueue and match_crc_rx_pdu
    0d6bef6 Add new function match_crc_rx_pdu (Copy from OAI)
    7a4cbf1 1. Add new functions remove RX、CRC PDU function 2. Add new function RX、CRC.indicaiton has rnti
    7314800 Add new function crc_sfn_slot_matcher for crc.indication
    af22b32 Revert "[temp] After VNF get queue call function to process Indication message (need to be comfirm again)"
    0548b43 Revert "For OAI add UL delta 1 slot"
    d16714f Revert "For OAI, we don't need to send ULtti and ULdci if no DLtti pdu"
    a31e441 Revert "Re-order pack config.request tlvs"
    944fe69 (origin/UpdatedANS1-forSIB1, UpdatedANS1-forSIB1) [Match SIB1] Fix PUSCH-TimeDomainResourceAllocation (remove hard code K2)
    ```
    
    ```bash
    #define ADD_DELTA_TO_TIME(crntTime, toFill, incr, numOfSlot) 
    ```
    
    - 發現OSC如果用原生參數K2 = 4,5 可以成功顯示LOG sent RAR，但是OAI UE沒辦法收到
    - OAI K2 = 6,6,6,7 list中有四個item
        - Unit TEST：
        - 已經測試OSC採用OAI相同參數 6 6 6 7 無法work
        - 測試OSC採用 4 5 6 7 能夠成功分配準備fill RAR 但是會莫名中斷
        - 測試OAI VNF + PNF 如果採用K2 = 4,5 是否能work → 可以work
            - K2 = 4, 7 → work
            - K2 = 4, 5 → work
        - 測試OSC只傳送 4 5 是否能work → 不能work UE會直接解不開SIB1 (**Got NACK on NR-BCCH-DL-SCH-Message (SIB1)**)
            
            ```bash
             七  12 16:23:54 [0m[PHY]   [SCHED][UE] Check absolute frequency DL 3619200000.000000, UL 3619200000.000000 (RF card 0, oai_exit 0, channel 0, rx_num_channels 1)
             七  12 16:23:54 [0m[93m[NR_PHY]   Starting sync detection
             七  12 16:23:54 [0m[PHY]   [UE thread Synch] Running Initial Synch 
             七  12 16:23:54 [0m[PHY]   [UE] nr_synchro_time: Sync source (nid2) = 0, Peak found at pos 219600, val = 8706702226 (99 dB power over signal avg 58 dB), ffo 0.000000
             七  12 16:23:54 [0m[PHY]   PSS execution duration 85518 microseconds 
             七  12 16:23:54 [0m[93m[NR_PHY]   SSS detected, PCI: 0, ffo_pss 0.000000 (0 Hz), ffo_sss 0.000590 (17 Hz),  ffo_pss+ffo_sss 0.000590 (17 Hz), nid1: 0, nid2: 0
             七  12 16:23:54 [0m[PHY]   [UE0] Initial sync: pbch decoded sucessfully, ssb index 0
             七  12 16:23:54 [0m[PHY]   [UE0] In synch, rx_offset 215040 samples
             七  12 16:23:54 [0m[PHY]   [UE 0] Measured Carrier Frequency offset 0 Hz
             七  12 16:23:54 [0m[32m[PHY]   Initial sync successful
             七  12 16:23:54 [0m[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
             七  12 16:23:54 [0m[PHY]   Got synch: hw_slot_offset 14, carrier off 0 Hz, rxgain 0.000000 (DL 3619200000.000000 Hz, UL 3619200000.000000 Hz)
             七  12 16:23:54 [0m[32m[PHY]   UE synchronized! decoded_frame_rx=32 UE->init_sync_frame=1 trashed_frames=8
             七  12 16:23:54 [0m[PHY]   Resynchronizing RX by 215040 samples
             七  12 16:23:54 [0m[1;31m[NR_MAC]   Got NACK on NR-BCCH-DL-SCH-Message (SIB1)
             七  12 16:23:54 [0m[1;31m[NR_MAC]   Got NACK on NR-BCCH-DL-SCH-Message (SIB1)
            ```
            
        
        OAI have 4 K2 (**pusch-TimeDomainAllocationList**)
        
        **<k2>6</k2>**
        
        **<k2>6</k2>**
        
        **<k2>6</k2>**
        
        **<k2>7</k2>**
        
        - **UL TDA index 0 is basic slot configuration starting in symbol 0 til the last but one symbol**
        - **UL TDA index 1 in case of SRS**
        - **UL TDA index 2 for mixed slot (TDD)**
        - **UL TDA index 3 for msg3 in the mixed slot (TDD)**
    
- 根據LOG整理出以下表格

![Untitled](Untitled%2044.png)

- K2 = [6,6,6,7]

```bash
msg3K2InfoTbl->k2TimingInfo[slotIdx].numK2
3 0 0 0 0 0 0 1 0 0 3 0 0 0 0 0 0 1 0 0 
```

- 修改為K2 = [4,5,6,7]

```
msg3K2InfoTbl->k2TimingInfo[slotIdx].numK2
2 2 1 0 0 0 0 1 0 0 2 2 1 0 0 0 0 1 0 0 
```

經過調整K2以及避免UL_TTI連續傳送後已經可以執行RAR Sent了
但是目前OAI UE 沒辦法正確收到並decode，首先比較OAI VNF + PNF nFAPI LOG

```
 七  17 02:45:03 [32m[NR_RRC]   SIB1 decoded
 七  17 02:45:03 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 七  17 02:45:03 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 七  17 02:45:04 [0m[NR_PHY]   ============================================
 七  17 02:45:04 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
 七  17 02:45:04 [0m[NR_PHY]   ============================================
 七  17 02:45:05 [0m[NR_PHY]   ============================================
 七  17 02:45:05 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
 七  17 02:45:05 [0m[NR_PHY]   ============================================
 七  17 02:45:06 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 七  17 02:45:06 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 七  17 02:45:06 [0m[NR_MAC]   Initialization of 4-step contention-based random access procedure
 七  17 02:45:06 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
 七  17 02:45:06 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 12, first_nonzero_root_idx 0
 七  17 02:45:06 [0m(184.0) Trying DCI candidate 0 of 1 number of candidates, CCE 0 (0), L 4, length 39, format 0
 七  17 02:45:06 (184.0) Decoded crc ffff does not match rnti 10b for DCI format 0
```

```
juil. 16 16:55:38 [32m[NR_RRC]   SIB1 decoded
juil. 16 16:55:38 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
juil. 16 16:55:38 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
juil. 16 16:55:38 [0m[NR_PHY]   ============================================
juil. 16 16:55:38 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
juil. 16 16:55:38 [0m[NR_PHY]   ============================================
juil. 16 16:55:38 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
juil. 16 16:55:38 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
juil. 16 16:55:38 [0m[NR_MAC]   Initialization of 4-step contention-based random access procedure
juil. 16 16:55:38 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
juil. 16 16:55:38 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 9, first_nonzero_root_idx 0
juil. 16 16:55:38 [0m[PHY]   [UE  0] AbsSubFrame 184.7: DCI 1 of 1 total DCIs found --> rnti 10b : format 0
juil. 16 16:55:38 [0m[1;31m[NR_MAC]   Trying to process acknack for an inactive harq process (0)
juil. 16 16:55:38 [0m[NR_MAC]   [UE 0][RAPROC][RA-RNTI 0005] Got BI RAR subPDU 267 ms
juil. 16 16:55:38 [0m[NR_MAC]   [UE 0][RAPROC][RA-RNTI 010b] Got RAPID RAR subPDU
juil. 16 16:55:38 [0m[32m[NR_MAC]   [UE 0][RAPROC][184.7] Found RAR with the intended RAPID 36
juil. 16 16:55:38 [0m[93m[MAC]   received TA command 31
juil. 16 16:55:38 [0m[PHY]   RAR-Msg2 decoded
juil. 16 16:55:38 [0m[32m[NR_MAC]   [RAPROC][184.17] RA-Msg3 transmitted
```

### 目前問題：

- 沒有 [UE  0] AbsSubFrame 184.7: DCI 1 of 1 total DCIs found --> rnti 10b : format 0

```c
int nr_ue_pdcch_procedures(PHY_VARS_NR_UE *ue,
                           const UE_nr_rxtx_proc_t *proc,
                           int32_t pdcch_est_size,
                           c16_t pdcch_dl_ch_estimates[][pdcch_est_size],
                           nr_phy_data_t *phy_data,
                           int n_ss,
                           c16_t rxdataF[][ue->frame_parms.samples_per_slot_wCP])
{
  int frame_rx = proc->frame_rx;
  int nr_slot_rx = proc->nr_slot_rx;
  NR_UE_PDCCH_CONFIG *phy_pdcch_config = &phy_data->phy_pdcch_config;

  fapi_nr_dl_config_dci_dl_pdu_rel15_t *rel15 = &phy_pdcch_config->pdcch_config[n_ss];

  start_meas(&ue->dlsch_rx_pdcch_stats);

  /// PDCCH/DCI e-sequence (input to rate matching).
  int32_t pdcch_e_rx_size = NR_MAX_PDCCH_SIZE;
  c16_t pdcch_e_rx[pdcch_e_rx_size];

  nr_rx_pdcch(ue, proc, pdcch_est_size, pdcch_dl_ch_estimates, pdcch_e_rx, rel15, rxdataF);

  fapi_nr_dci_indication_t dci_ind;
  nr_dci_decoding_procedure(ue, proc, pdcch_e_rx, &dci_ind, rel15);

  for (int i = 0; i < dci_ind.number_of_dcis; i++) {
    LOG_I(PHY,
          "[UE  %d] AbsSubFrame %d.%d: DCI %i of %d total DCIs found --> rnti %x : format %d\n",
          ue->Mod_id,
          frame_rx % 1024,
          nr_slot_rx,
          i + 1,
          dci_ind.number_of_dcis,
          dci_ind.dci_list[i].rnti,
          dci_ind.dci_list[i].dci_format);
  }
```

- 在(184/0)的時候會有**n_ss<phy_pdcch_config->nb_search_space**

```
 七  17 20:28:33 [0m[PHY]    ------ --> PDCCH ChannelComp/LLR Frame.slot 183.17 ------  
 七  17 20:28:33 [0m[NR_PHY]   n_ss<phy_pdcch_config->nb_search_space:0
 七  17 20:28:33 [0m[PHY]   [UE 0] Frame 183, nr_slot_rx 17: found 0 DCIs
 七  17 20:28:33 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
 七  17 20:28:33 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 13, first_nonzero_root_idx 0
 七  17 20:28:33 [0m[PHY]    ****** start RX-Chain for Frame.Slot 184.0 ******  
 七  17 20:28:33 [0m[PHY]    ------  PBCH ChannelComp/LLR: frame.slot 184.0 ------  
 七  17 20:28:33 [0m[PHY]    ------  Decode MIB: frame.slot 184.0 ------  
 七  17 20:28:33 [0m[PHY]   start adjust sync slot = 0 no timing 0
 七  17 20:28:33 [0m[PHY]   Doing N0 measurements in pbch_pdcch_processing
 七  17 20:28:33 [0m[PHY]    ------ --> PDCCH ChannelComp/LLR Frame.slot 184.0 ------  
 七  17 20:28:33 [0m[NR_PHY]   n_ss<phy_pdcch_config->nb_search_space:1
 七  17 20:28:33 [0m[PHY]   (184/0)nr_ue_pdcch_procedures
 七  17 20:28:33 [0m(184.0) Trying DCI candidate 0 of 1 number of candidates, CCE 0 (0), L 4, length 39, format 0
 七  17 20:28:33 (184.0) Decoded crc ffff does not match rnti 10b for DCI format 0
 七  17 20:28:33 [PHY]   [UE 0] Frame 184, nr_slot_rx 0: found 0 DCIs
 七  17 20:28:33 [0m[PHY]    ****** start RX-Chain for Frame.Slot 184.1 ******  
 七  17 20:28:33 [0m[PHY]    ------ --> PDCCH ChannelComp/LLR Frame.slot 184.1 ------  
 七  17 20:28:33 [0m[NR_PHY]   n_ss<phy_pdcch_config->nb_search_space:1
 七  17 20:28:33 [0m[PHY]   (184/1)nr_ue_pdcch_procedures
```

目前根據 [RNTI about RandomAccess](RNTI%20about%20RandomAccess%20121100983143819487b9ce48feb89f4a.md) 整理得到結論是OSC DU High沒有拿到t_id，因此算不出RA_RNTI，因此RAR送出去UE也無法decode

- put queue 之前填入資料有問題

```c
      // rach_ind->pdu_list[i].phy_cell_id = ind->pdu_list[i].phy_cell_id;
      // rach_ind->pdu_list[i].slot_index = ind->pdu_list[i].slot_index;
      // rach_ind->pdu_list[i].avg_rssi = ind->pdu_list[i].avg_rssi;
      // rach_ind->pdu_list[i].avg_snr = ind->pdu_list[i].avg_snr;
      // rach_ind->pdu_list[i].num_preamble = ind->pdu_list[i].num_preamble;
      // rach_ind->pdu_list[i].freq_index = ind->pdu_list[i].freq_index;
      // rach_ind->pdu_list[i].symbol_index = ind->pdu_list[i].symbol_index;
      rach_ind->pdu_list[i] = ind->pdu_list[i];
```

- UE sim LDPC

```c
  NR_DL_UE_HARQ_t *dl_harq0 = NULL;

  if ((pdu_type !=  FAPI_NR_RX_PDU_TYPE_SSB) && dlsch0) {
    int t=WS_C_RNTI;
    if (pdu_type == FAPI_NR_RX_PDU_TYPE_RAR)
      t=WS_RA_RNTI;
    if  (pdu_type == FAPI_NR_RX_PDU_TYPE_SIB)
      t=WS_SI_RNTI;
    dl_harq0 = &ue->dl_harq_processes[0][dlsch0->dlsch_config.harq_process_nbr];
    trace_NRpdu(DIRECTION_DOWNLINK,
		b,
		dlsch0->dlsch_config.TBS / 8,
		t,
		dlsch0->rnti,
		proc->frame_rx,
		proc->nr_slot_rx,
		0,0);
  }
  switch (pdu_type){
    case FAPI_NR_RX_PDU_TYPE_SIB:
    case FAPI_NR_RX_PDU_TYPE_RAR:
    case FAPI_NR_RX_PDU_TYPE_DLSCH:
      if(dlsch0) {
        LOG_I(PHY,"dl_harq0->ack:%d\n",dl_harq0->ack);
        dl_harq0 = &ue->dl_harq_processes[0][dlsch0->dlsch_config.harq_process_nbr];
        rx_ind->rx_indication_body[n_pdus - 1].pdsch_pdu.harq_pid = dlsch0->dlsch_config.harq_process_nbr;
        rx_ind->rx_indication_body[n_pdus - 1].pdsch_pdu.ack_nack = dl_harq0->ack;
```

- 目前可以顯示RAR decode但是UE還是無法拿來用，經過與OAI VNF+PNF的LOG結果比較得知UE沒有顯示Got RAPID RAR subPDU的LOG，需要進一步確認：

```
juil. 18 11:57:06 [0m[PHY]   [UE  0] AbsSubFrame 168.7: DCI 1 of 1 total DCIs found --> rnti 10b : format 0
juil. 18 11:57:06 [0m[PHY]   [UE 0] nr_slot_rx 7, harq_pid 0 (1), BWP start 27, rb_start 0, nb_rb 8, symbol_start 1, nb_symbols 5, DMRS mask 4, Nl 1
juil. 18 11:57:06 [0m[PHY]   dl_harq0->ack:1
juil. 18 11:57:06 [0m[1;31m[NR_MAC]   Trying to process acknack for an inactive harq process (0)
juil. 18 11:57:06 [0m[NR_MAC]   [UE 0][RAPROC][RA-RNTI 0005] Got BI RAR subPDU 267 ms
juil. 18 11:57:06 [0m[NR_MAC]   [UE 0][RAPROC][RA-RNTI 010b] Got RAPID RAR subPDU
juil. 18 11:57:06 [0m[32m[NR_MAC]   [UE 0][RAPROC][168.7] Found RAR with the intended RAPID 26
juil. 18 11:57:06 [0m[93m[MAC]   received TA command 31
juil. 18 11:57:06 [0m[PHY]   RAR-Msg2 decoded
```

```
 七  19 16:52:38 [0m[NR_MAC]   Initialization of 4-step contention-based random access procedure
 七  19 16:52:38 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
 七  19 16:52:38 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 10, first_nonzero_root_idx 0
 七  19 16:52:38 [0m(184.12) Received dci indication (rnti 10b,dci format 0,n_CCE 0,payloadSize 39,payload 1502000000)
 七  19 16:52:38 [PHY]   [UE  0] AbsSubFrame 184.12: DCI 1 of 1 total DCIs found --> rnti 10b : format 0
 七  19 16:52:38 [0m[PHY]   [UE 0] nr_slot_rx 12, harq_pid 0 (1), BWP start 27, rb_start 0, nb_rb 8, symbol_start 1, nb_symbols 5, DMRS mask 4, Nl 1
 七  19 16:52:38 [0m[PHY]   dl_harq0->ack:0
 七  19 16:52:38 [0m[1;31m[NR_MAC]   Trying to process acknack for an inactive harq process (0)
 七  19 16:52:38 [0m[93m[PHY]   Received a RAR-Msg2 but LDPC decode failed
```

```
 七  18 19:02:59 [PHY]   [UE  0] AbsSubFrame 184.12: DCI 1 of 1 total DCIs found --> rnti 10b : format 0
 七  18 19:02:59 [0m[PHY]   [UE 0] nr_slot_rx 12, harq_pid 0 (1), BWP start 27, rb_start 0, nb_rb 8, symbol_start 1, nb_symbols 5, DMRS mask 4, Nl 1
 七  18 19:02:59 [0m[PHY]   dl_harq0->ack:1
 七  18 19:02:59 [0m[1;31m[NR_MAC]   Trying to process acknack for an inactive harq process (0)
 七  18 19:02:59 [0m[NR_MAC]   [UE 0][RAPROC][RA-RNTI 0005] Got BI RAR subPDU 267 ms
 七  18 19:02:59 [0m[PHY]   RAR-Msg2 decoded
```

可以從code 看出rarh->T == 1有問題

```c
    if (rarh->T == 1) {
      n_subPDUs++;
      LOG_I(NR_MAC, "[UE %d][RAPROC][RA-RNTI %04x] Got RAPID RAR subPDU\n", mac->ue_id, rnti);
    } else {
      ra->RA_backoff_indicator = table_7_2_1[((NR_RA_HEADER_BI *)rarh)->BI];
      ra->RA_BI_found = 1;
      LOG_I(NR_MAC, "[UE %d][RAPROC][RA-RNTI %04x] Got BI RAR subPDU %d ms\n", mac->ue_id, ra->RA_backoff_indicator, rnti);
      
```

- 檢查結構: The Type field is a flag indicating whether the MAC subheader contains a Random Access Preamble ID or a Backoff Indicator (0, BI) (1, RAPID)

```c
//* RAR MAC subheader // TS 38.321 ch. 6.1.5, 6.2.2 *//
// - E: The Extension field is a flag indicating if the MAC subPDU including this MAC subheader is the last MAC subPDU or not in the MAC PDU
// - T: The Type field is a flag indicating whether the MAC subheader contains a Random Access Preamble ID or a Backoff Indicator (0, BI) (1, RAPID)
// - R: Reserved bit, set to "0"
// - BI: The Backoff Indicator field identifies the overload condition in the cell.
// - RAPID: The Random Access Preamble IDentifier field identifies the transmitted Random Access Preamble

/*!\brief RAR MAC subheader with RAPID */
typedef struct {
  uint8_t RAPID: 6;
  uint8_t T: 1;
  uint8_t E: 1;
} __attribute__ ((__packed__)) NR_RA_HEADER_RAPID;
```

目前根據 [RAR PDU](RAR%20PDU%20121100983143813f9531d126bef7e972.md) 研究的結果，可以整理以下流程

- OSC SCH 會排RAR並且建立填入RAR PDU
- nFAPI slot.indication收到後的下一個slot若SCH已有排好的PDU 則會觸發填入RAR資訊
    - DL_TTI.request 會填入RAR版本的 PDCCH PDU , PDSCH PDU
    - TX_Data.request 會填入RAR版本的 RAR PDU
- 根據目前UE LOG可以解開DCI 但是MSG2 decode 失敗可以推測DL_TTI應該沒有問題，應該先解決TX_DATA 根據[RAR PDU](RAR%20PDU%20121100983143813f9531d126bef7e972.md) 比較表調整參數讓OSC 和OAI相同

- 目前檢查到OSC 送出RAR 但是UE 僅收到DCI (被包在DL_TTI內傳送) 並沒有收到RAR PDU (被包在TX_DATA內傳送)
    - 先檢查TX_DATA是否有成功送到L1 → 有成功送出接收
    - 在檢查為甚麼UE拿不到RAR PDU

Currently, OSC DU is able to send RAR to OAI PNF, and the UE sim can receive the DCI and decode the DCI to know the RA-RNTI.

```c
(184.12) Received dci indication (rnti 10b, dci format 0, n_CCE 0, payloadSize 39, payload 1502000000)
[UE 0] AbsSubFrame 184.12: DCI 1 of 1 total DCIs found --> rnti 10b: format 0
[UE 0] nr_slot_rx 12, harq_pid 0 (1), BWP start 27, rb_start 0, nb_rb 8, symbol_start 1, nb_symbols 5, DMRS mask 4, Nl 1
Comparing the differences in the OAI VNF+PNF logs, it is found that Got RAPID RAR subPDU cannot be obtained, and after printing the RAR PDU received by the UE, it is found that p_b is still empty after nr_dlsch_decoding, and the UE has not received it.
```

Therefore, summarizing the current situation as I see it:
DL_TTI PDCCH PDSCH (DCI) have all been successfully transmitted (because the DCI payload has been received)
TX_Data has only been successfully transmitted to the PNF, but the part from PNF to the UE sim has not been successful (because I checked the PNF log and saw that TX_Data unpacked and received the complete information successfully).

I would like to ask, based on your experience, where do you think the problem might be?
(Which RAR-related parameters do you think are most likely affecting the decode (nr_dlsch_decoding) results?)

- following Robert suggest check nr_generate_pdsch function
    - rbsize is different!
    - Found hard code and fixed it!!!

```
 七  22 16:36:26 [0m[NR_MAC]   Initialization of 4-step contention-based random access procedure
 七  22 16:36:26 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
 七  22 16:36:26 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 8, first_nonzero_root_idx 0
 七  22 16:36:26 [0m(184.12) Received dci indication (rnti 10b,dci format 0,n_CCE 0,payloadSize 39,payload 1502000000)
 七  22 16:36:26 [PHY]   [UE  0] AbsSubFrame 184.12: DCI 1 of 1 total DCIs found --> rnti 10b : format 0
 七  22 16:36:26 [0m[PHY]   [UE 0] nr_slot_rx 12, harq_pid 0 (1), BWP start 27, rb_start 0, nb_rb 8, symbol_start 1, nb_symbols 5, DMRS mask 4, Nl 1
 七  22 16:36:26 [0m[PHY]   AbsSubframe 184.12 Start LDPC Decoder for CW0 [harq_pid 0] ? 1 
 七  22 16:36:26 [0m[PHY]   AbsSubframe 184.12 Start LDPC Decoder for CW1 [harq_pid 0] ? 0 
 七  22 16:36:26 [0m[PHY]   num_rb8
 七  22 16:36:26 [0m[PHY]   nbDecode:1
 七  22 16:36:26 [0m[PHY]   b_size:5280
 七  22 16:36:26 [0m[PHY]   dlsch decoding, ret = 8
 七  22 16:36:26 [0m
 七  22 16:36:26  decoding [RAR PDU]
 七  22 16:36:26 62 0 0 2e 60 16 0 64 3f 0 0 f5 ad 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  22 16:36:26 END [RAR PDU]
 七  22 16:36:26 [PHY]   dl_harq0->ack:1
 七  22 16:36:26 [0m
 七  22 16:36:26 [RAR PDU]
 七  22 16:36:26 62 0 0 2e 60 16 0 64 3f 0 0 f5 ad 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  22 16:36:26 END [RAR PDU]
 七  22 16:36:26 [1;31m[NR_MAC]   Trying to process acknack for an inactive harq process (0)
 七  22 16:36:26 [0m
 七  22 16:36:26 [RAR PDU]
 七  22 16:36:26 62 0 0 2e 60 16 0 64 3f 0 0 f5 ad 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 七  22 16:36:26 END [RAR PDU]
 七  22 16:36:26 [NR_MAC]   [UE 0][RAPROC][RA-RNTI 010b] Got RAPID RAR subPDU
 七  22 16:36:26 [0m[32m[NR_MAC]   [UE 0][RAPROC][184.12] Found RAR with the intended RAPID 34
 七  22 16:36:26 [0m[93m[MAC]   received TA command 31
 七  22 16:36:26 [0m[PHY]   RAR-Msg2 decoded
 七  22 16:36:26 [0m[32m[NR_MAC]   [RAPROC][184.19] RA-Msg3 transmitted
 七  22 16:36:26 [0m[1;31m[PHY]   [UE 0] frame 186, nr_slot_rx 0, Error decoding PBCH!
 七  22 16:36:26 [0m[1;31m[PHY]   [UE 0] frame 188, nr_slot_rx 0, Error decoding PBCH!
 七  22 16:36:26 [0m[1;31m[PHY]   [UE 0] frame 190, nr_slot_rx 0, Error decoding PBCH!
 七  22 16:36:26 [0m[1;31m[PHY]   [UE 0] frame 192, nr_slot_rx 0, Error decoding PBCH!
```

```
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