# Compare OSC DU send MSG4

Start Date: 2024/09/24
Summary: Comparison of OSC DU send MSG4, detailing changes in parameters and code functionality for PDCCH and PDSCH.
Status: Done
Assign: Ming 咚咚 [銘鴻]

### When PNF send compare table → [Compare OAI PNF recieve MSG4](Compare%20OAI%20PNF%20recieve%20MSG4%2012110098314381c180f1e4809fbc4292.md)

### When UE recieve compare table → [Compare OAI UE receive MSG4](Compare%20OAI%20UE%20receive%20MSG4%2012110098314381d690cdc975187a879a.md)

<aside>
💡

✅ means OSC has been revised to match the OAI config settings.

</aside>

## DL_TTI for PDCCH

```c
     -> Function: OAI_OSC_fillPdcchPdu()
     
      dlTtiReqPdu->PDUType = PDCCH_PDU_TYPE;
      dlTtiReqPdu->pdcch_pdu.pdcch_pdu_rel15.BWPSize = bwp->freqAlloc.numPrb;
      dlTtiReqPdu->pdcch_pdu.pdcch_pdu_rel15.BWPStart = bwp->freqAlloc.startPrb;
      dlTtiReqPdu->pdcch_pdu.pdcch_pdu_rel15.SubcarrierSpacing = bwp->subcarrierSpacing; 
      dlTtiReqPdu->pdcch_pdu.pdcch_pdu_rel15.CyclicPrefix = bwp->cyclicPrefix; 
```

| Parameter | OAI Value | OSC Value |
| --- | --- | --- |
| `BWPSize` | 48 | 48 |
| `BWPStart` | 27 | 27 |
| `SubcarrierSpacing` | 1 | 1 |
| `CyclicPrefix` | 0 | 0 |
| `StartSymbolIndex` | 0 | 0 |
| `DurationSymbols` | 1 | 1 |
| `FreqDomainResource[0]` | 255 | 0  ✅ |
| `FreqDomainResource[1]` | 0 | 31  ✅ |
| `FreqDomainResource[2]` | 0 | 224  ✅ |
| `FreqDomainResource[3]` | 0 | 0 |
| `FreqDomainResource[4]` | 0 | 0 |
| `FreqDomainResource[5]` | 0 | 0 |
| `CceRegMappingType` | 1 | 1 |
| `RegBundleSize` | 6 | 6 |
| `InterleaverSize` | 2 | 2 |
| `CoreSetType` | 0 | 0 |
| `ShiftIndex` | 1 | 1 |
| `precoderGranularity` | 0 | 0 |
| `numDlDci` | 1 | 1 |
| `dci_pdu[0].RNTI` | 21665 | 100 |
| `dci_pdu[0].ScramblingId` | 1 | 1 |
| `dci_pdu[0].ScramblingRNTI` | 0 | 0 |
| `dci_pdu[0].CceIndex` → [Question: CCEindex](Question%20CCEindex%201211009831438160a24dfdbbd409a76e.md)  | 0 | 4 |
| `dci_pdu[0].AggregationLevel` | 4 | 4 |
| `dci_pdu[0].precodingAndBeamforming.num_prgs` | 0 | 0 |
| `dci_pdu[0].precodingAndBeamforming.prg_size` | 0 | 0 |
| `dci_pdu[0].precodingAndBeamforming.dig_bf_interfaces` | 0 | 0 |
| `dci_pdu[0].beta_PDCCH_1_0` | 0 | 0 |
| `dci_pdu[0].powerControlOffsetSS` | 1 | 0  ✅ |
| `dci_pdu[0].PayloadSizeBits` | 39 | 28  ✅ |

### DCI Payload

- OSC DU HIgh source code

```jsx
-> Function: schDlRsrcAllocDlMsg()

   pdcch->numDlDci = 1;
   pdcch->dci.rnti = ueCb.crnti;
   pdcch->dci.scramblingId = cell->cellCfg.phyCellId;
   pdcch->dci.scramblingRnti = 0;
   pdcch->dci.cceIndex = 0; /* 0-3 for UL and 4-7 for DL */
   pdcch->dci.aggregLevel = 4;
```

```c
      -> Function: OAI_OSC_fillDlMsgDlDciPdu()
      
      
      /* Packing DCI format fields */
      fillDlDciPayload(dlDciPtr->Payload, &bytePos, &bitPos,\
            dciFormatId, dciFormatIdSize);
      fillDlDciPayload(dlDciPtr->Payload, &bytePos, &bitPos,\
            freqDomResAssign, freqDomResAssignSize);
```

```c
      /* Size(in bits) of each field in DCI format 1_0 */
      uint8_t dciFormatIdSize    = 1;
      uint8_t freqDomResAssignSize = 0;
      uint8_t timeDomResAssignSize = 4;
      uint8_t VRB2PRBMapSize       = 1;
      uint8_t modNCodSchemeSize    = 5;
      uint8_t ndiSize              = 1;
      uint8_t redundancyVerSize    = 2;
      uint8_t harqProcessNumSize   = 4;
      uint8_t dlAssignmentIdxSize  = 2;
      uint8_t pucchTpcSize         = 2;
      uint8_t pucchResoIndSize     = 3;
      uint8_t harqFeedbackIndSize  = 3;
```

- OAI VNF Source code

```c
  dci_payload.format_indicator = 1;
  dci_payload.time_domain_assignment.val = time_domain_assignment;
  dci_payload.vrb_to_prb_mapping.val = 0;
  dci_payload.mcs = pdsch_pdu_rel15->mcsIndex[0];
  dci_payload.tb_scaling = tb_scaling;
  dci_payload.rv = pdsch_pdu_rel15->rvIndex[0];
  dci_payload.harq_pid = current_harq_pid;
  dci_payload.ndi = ndi;
  dci_payload.dai[0].val = pucch ? (pucch->dai_c-1) & 3 : 0;
  dci_payload.tpc = tpc; // TPC for PUCCH: table 7.2.1-1 in 38.213
  dci_payload.pucch_resource_indicator = delta_PRI; // This is delta_PRI from 9.2.1 in 38.213
	  dci_payload.pdsch_to_harq_feedback_timing_indicator.val = pucch ? pucch->timing_indicator : 0;

```

```c
case TYPE_TC_RNTI_:
        pos = 1;
        // indicating a DL DCI format 1bit
        LOG_I(NR_MAC, "DCI1_0 (size %d): Format indicator %d (%d bits) N_RB_BWP %d => %d (0x%lx)\n", dci_size, dci_pdu_rel15->format_indicator, 1, N_RB, dci_size - pos, *dci_pdu);
        *dci_pdu |= ((uint64_t)dci_pdu_rel15->format_indicator & 1) << (dci_size - pos++);
        // Freq domain assignment 0-16 bit
        fsize = (int)ceil(log2((N_RB * (N_RB + 1)) >> 1));
        for (int i = 0; i < fsize; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->frequency_domain_assignment.val >> (fsize - i - 1)) & 1) << (dci_size - pos++);
        // Time domain assignment 4 bit
        for (int i = 0; i < 4; i++) {
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->time_domain_assignment.val >> (3 - i)) & 1) << (dci_size - pos++);
          LOG_I(NR_MAC, "Time domain assignment bit %d: %d (0x%lx)\n", i, ((dci_pdu_rel15->time_domain_assignment.val >> (3 - i)) & 1), *dci_pdu);
        }
        // VRB to PRB mapping 1 bit
        *dci_pdu |= ((uint64_t)dci_pdu_rel15->vrb_to_prb_mapping.val & 1) << (dci_size - pos++);
        // MCS 5bit  //bit over 32, so dci_pdu ++
        for (int i = 0; i < 5; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->mcs >> (4 - i)) & 1) << (dci_size - pos++);
        // New data indicator 1bit
        *dci_pdu |= ((uint64_t)dci_pdu_rel15->ndi & 1) << (dci_size - pos++);
        // Redundancy version  2bit
        for (int i = 0; i < 2; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->rv >> (1 - i)) & 1) << (dci_size - pos++);
        // HARQ process number  4bit
        for (int i = 0; i < 4; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->harq_pid >> (3 - i)) & 1) << (dci_size - pos++);
        // Downlink assignment index – 2 bits
        for (int i = 0; i < 2; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->dai[0].val >> (1 - i)) & 1) << (dci_size - pos++);
        // TPC command for scheduled PUCCH – 2 bits
        for (int i = 0; i < 2; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->tpc >> (1 - i)) & 1) << (dci_size - pos++);
        // PUCCH resource indicator – 3 bits
        for (int i = 0; i < 3; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->pucch_resource_indicator >> (2 - i)) & 1) << (dci_size - pos++);
        // PDSCH-to-HARQ_feedback timing indicator – 3 bits
        for (int i = 0; i < 3; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->pdsch_to_harq_feedback_timing_indicator.val >> (2 - i)) & 1) << (dci_size - pos++);

```

- DCI 1_0 Payload compare table

|  | OAI | OSC |
| --- | --- | --- |
| **coresetSize (BWPSize)** | 48 | 48 |
| **rbStart** | 0 | 240  ✅ |
| **rbSize** | 42 | 33  ✅⚠️ → 28 |
|  |  |  |
| dciFormatId | 1 | 1 |
| freqDomResAssign | 383 | — ✅ UE decode 1055 |
| (f_size) freqDomResAssignSize | 11 | 11 |
| (**time_alloc**) timeDomResAssign | 0 | 255  ✅ |
| **(vrb_to_prb_mapping)** VRB2PRBMap | 0 | 0 |
| (mcs) modNCodScheme | 0 | 5  ✅ |
| ndi : New data indicator | 0 | 0 |
| **(rv)** redundancyVer | 0 | 0 |
| **(harq_pid)** harqProcessNum | 0 | 0 |
| **(dai)** dlAssignmentIdx | 0 | 0 |
| **(tpc)** pucchTpc | 0 | 0 |
| **(pucch_resource_indicator)** pucchResoInd | 0 | 0 |
| (**pdsch_to_harq_feedback_timing_indicator**) harqFeedbackInd | 6 | 0  ✅ ⚠️→ 2 |
- MSG4 DCI Payload (PDCCH)   ✅

```
 九  24 23:59:58 [0m1727193598.175508 [PHY]   dci_pdu[0].Payload[0]: 6
 九  24 23:59:58 [0m1727193598.175509 [PHY]   dci_pdu[0].Payload[1]: 0
 九  24 23:59:58 [0m1727193598.175510 [PHY]   dci_pdu[0].Payload[2]: 0
 九  24 23:59:58 [0m1727193598.175511 [PHY]   dci_pdu[0].Payload[3]: 248
 九  24 23:59:58 [0m1727193598.175511 [PHY]   dci_pdu[0].Payload[4]: 75
```

```
 九  24 23:50:20 [0m[PHY]   dci_pdu[0].Payload[2]: 138
 九  24 23:50:20 [0m[PHY]   dci_pdu[0].Payload[3]: 135
 九  24 23:50:20 [0m[PHY]   dci_pdu[0].Payload[4]: 86
```

## DL_TTI for PDSCH

```c
   -> Function: schDlRsrcAllocMsg4()
   
   /* fill the PDSCH PDU */
   uint8_t cwCount = 0;
   pdsch->pduBitmap = 0; /* PTRS and CBG params are excluded */
   pdsch->rnti = cell->raCb[ueId-1].tcrnti;
```

```bash
   -> Function: schDlRsrcAllocMsg4()	
   pdsch->pdschTimeAlloc.startSymb = pdschStartSymbol; 
   pdsch->pdschTimeAlloc.numSymb = pdschNumSymbols;
```

| Parameter | **OAI Value** | OSC Value |
| --- | --- | --- |
| `pduBitmap` | 0 | 0 |
| `rnti` | 12071 | 100 |
| `pduIndex` | 0 | 0 |
| `BWPSize` | 48 | 48 |
| `BWPStart` | 27 | 27 |
| `SubcarrierSpacing` | 1 | 1 |
| `CyclicPrefix` | 0 | 0 |
| `NrOfCodewords` | 1 | 1 |
| `targetCodeRate[0]` | 1200 | 308  ✅ |
| `qamModOrder[0]` | 2 | 2 |
| `mcsIndex[0]` | 0 | 5  ✅ |
| `mcsTable[0]` | 0 | 0 |
| `rvIndex[0]` | 0 | 0 |
| `TBSize[0]` | 149 | 145  ✅ → 116 |
| `dataScramblingId` | 1 | 1 |
| `nrOfLayers` | 1 | 1 |
| `transmissionScheme` | 0 | 0 |
| `refPoint` | 0 | 0 |
| `dlDmrsSymbPos` | 2180 | 4  ✅ |
| `dmrsConfigType` | 0 | 0 |
| `dlDmrsScramblingId` | 1 | 1 |
| `SCID` | 0 | 0 |
| `numDmrsCdmGrpsNoData` | 2 | 1  ✅ |
| `dmrsPorts` | 1 | 0  ✅ |
| `resourceAlloc` | 1 | 1 |
| `rbBitmap` | 0 | 0 |
| `rbStart` | 0 | 0 |
| `rbSize` | 42 | 33  ✅⚠️ → 28 |
| `VRBtoPRBMapping` | 0 | 0 |
| `StartSymbolIndex` | 1 | 1 |
| `NrOfSymbols` | 13 | 5 ⚠️✅ |
| `num_prgs` | 1 | 1 |
| `prg_size` | 275 | 1  ✅ |
| `dig_bf_interfaces` | 1 | 0  ✅ |
| `pm_idx[0]` | 0 | 0 |
| `powerControlOffset` | 0 | 8 (OAI Hardcode)  ✅ |
| `powerControlOffsetSS` | 0 | 1 (OAI Hardcode)  ✅ |
| `ldpcBaseGraph` | 2 | 2 |
| `tbSizeLbrmBytes` | 92200 | 0 ✅ |

<aside>
⚠️

`NrOfSymbols` can't be modified because MSG3 can only be transmitted in this symbol set.

</aside>

## TX_Data

| Parameter | OAI value | OSC value |
| --- | --- | --- |
| **PDU_length** | 161 | 145 |
| Payload | The following log | all value is zero   ✅ |

```
 九  26 00:57:40  decoding [MSG4 PDU]
 九  26 00:57:40 [0m1727283460.976651 [PHY]   20a8064 
 九  26 00:57:40 [0m1727283460.976652 [PHY]   40250409 
 九  26 00:57:40 [0m1727283460.976653 [PHY]   2400000 
 九  26 00:57:40 [0m1727283460.976654 [PHY]   903a85f1 
 九  26 00:57:40 [0m1727283460.976655 [PHY]   56d084 
 九  26 00:57:40 [0m1727283460.976655 [PHY]   70962600 
 九  26 00:57:40 [0m1727283460.976656 [PHY]   5fe35cb 
 九  26 00:57:40 [0m1727283460.976657 [PHY]   1020b8 
 九  26 00:57:40 [0m1727283460.976658 [PHY]   b8414000 
 九  26 00:57:40 [0m1727283460.976658 [PHY]   1040 
 九  26 00:57:40 [0m1727283460.976659 [PHY]   60b84140 
 九  26 00:57:40 [0m1727283460.976660 [PHY]   40000010 
 九  26 00:57:40 [0m1727283460.976661 [PHY]   3610040 
 九  26 00:57:40 [0m1727283460.976662 [PHY]   1c365048 
 九  26 00:57:40 [0m1727283460.976662 [PHY]   c04c87 
 九  26 00:57:40 [0m1727283460.976663 [PHY]   69020020 
 九  26 00:57:40 [0m1727283460.976664 [PHY]   6619cec9 
 九  26 00:57:40 [0m1727283460.976665 [PHY]   1a006254 
 九  26 00:57:40 [0m1727283460.976665 [PHY]   c97dcdd4 
 九  26 00:57:40 [0m1727283460.976666 [PHY]   c63949c0 
 九  26 00:57:40 [0m1727283460.976667 [PHY]   1a6f8da9 
 九  26 00:57:40 [0m1727283460.976668 [PHY]   70323d9a 
 九  26 00:57:40 [0m1727283460.976668 [PHY]   874301b8 
 九  26 00:57:40 [0m1727283460.976669 [PHY]   1db02040 
 九  26 00:57:40 [0m1727283460.976670 [PHY]   de8c4880 
 九  26 00:57:40 [0m1727283460.976671 [PHY]   30c4 
 九  26 00:57:40 [0m1727283460.976671 [PHY]   0 
```

```
 九  26 10:29:44  decoding [MSG4 PDU]
 九  26 10:29:44 [0m[PHY]   69e81d3e 
 九  26 10:29:44 [0m[PHY]   60dc6 
 九  26 10:29:44 [0m[PHY]   3402889 
 九  26 10:29:44 [0m[PHY]   8005e01a 
 九  26 10:29:44 [0m[PHY]   64578008 
 九  26 10:29:44 [0m[PHY]   500f830e 
 九  26 10:29:44 [0m[PHY]   415e103 
 九  26 10:29:44 [0m[PHY]   1c63da8 
 九  26 10:29:44 [0m[PHY]   25c0d403 
 九  26 10:29:44 [0m[PHY]   1501990 
 九  26 10:29:44 [0m[PHY]   800710 
 九  26 10:29:44 [0m[PHY]   380000 
 九  26 10:29:44 [0m[PHY]   84106e08 
 九  26 10:29:44 [0m[PHY]   64c41f00 
 九  26 10:29:44 [0m[PHY]   1090884 
 九  26 10:29:44 [0m[PHY]   2798038c 
 九  26 10:29:44 [0m[PHY]   aa660220 
 九  26 10:29:44 [0m[PHY]   10000181 
 九  26 10:29:44 [0m[PHY]   11000 
 九  26 10:29:44 [0m[PHY]   55221101 
 九  26 10:29:44 [0m[PHY]   92018008 
 九  26 10:29:44 [0m[PHY]   180b0010 
 九  26 10:29:44 [0m[PHY]   728a3185 
 九  26 10:29:44 [0m[PHY]   40000181 
 九  26 10:29:44 [0m[PHY]   400020 
 九  26 10:29:44 [0m[PHY]   0 
 九  26 10:29:44 [0m[PHY]   80020c00 
 九  26 10:29:44 [0m[PHY]   501138 
```

```c
               /* Packing fields into MAC PDU R/F/LCID/L */
               packBytes(macPdu, &bytePos, &bitPos, RBit, RBitSize);
               packBytes(macPdu, &bytePos, &bitPos, FBit, FBitSize);
               packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
               packBytes(macPdu, &bytePos, &bitPos, lenField, lenFieldSize);
```

### MSG4 PDU

```cpp
//  For both DL/UL-SCH
//  Except:
//   - UL/DL-SCH: fixed-size MAC CE(known by LCID)
//   - UL/DL-SCH: padding
//   - UL-SCH:    MSG3 48-bits
//  |0|1|2|3|4|5|6|7|  bit-wise
//  |R|F|   LCID    |
//  |       L       |
//  |0|1|2|3|4|5|6|7|  bit-wise
//  |R|F|   LCID    |
//  |       L       |
//  |       L       |

//  For both DL/UL-SCH
//  For:
//   - UL/DL-SCH: fixed-size MAC CE(known by LCID)
//   - UL/DL-SCH: padding, for single/multiple 1-oct padding CE(s)
//   - UL-SCH:    MSG3 48-bits
//  |0|1|2|3|4|5|6|7|  bit-wise
//  |R|R|   LCID    |
//  LCID: The Logical Channel ID field identifies the logical channel instance of the corresponding MAC SDU or the type of the corresponding MAC CE or padding as described in Tables 6.2.1-1 and 6.2.1-2 for the DL-SCH and UL-SCH respectively. There is one LCID field per MAC subheader. The LCID field size is 6 bits;
//  L: The Length field indicates the length of the corresponding MAC SDU or variable-sized MAC CE in bytes. There is one L field per MAC subheader except for subheaders corresponding to fixed-sized MAC CEs and padding. The size of the L field is indicated by the F field;
//  F: lenght of L is 0:8 or 1:16 bits wide
//  R: Reserved bit, set to zero.
```

```c
-> Function: macMuxPdu()
		
                  /* Packing fields into MAC PDU R/R/LCID */
                  packBytes(macPdu, &bytePos, &bitPos, RBit, (RBitSize * 2));
                  packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
```

### MSG4 PDU

|  | OAI value | OSC value |
| --- | --- | --- |
| RBit | 0 | 0 |
| FBit | 0 | 0 |
| lcid | 0 | 0 |
| lenField | 137 | 103  ✅ |

### OSC

```c
void fillMsg4DlData(MacDlData *dlData, uint16_t msg4PduLen, uint8_t *msg4Pdu)
{
   dlData->pduInfo[dlData->numPdu].lcId = MAC_LCID_CCCH;
   dlData->pduInfo[dlData->numPdu].pduLen = msg4PduLen;
   memcpy(dlData->pduInfo[dlData->numPdu].dlPdu, msg4Pdu, msg4PduLen);
   dlData->numPdu++;
}
```

### OAI

```c
NR_MAC_SUBHEADER_SHORT: R=0, F=0, LCID=0, L=137
```

## LCID defined in OAI

```cpp
//  38.321 ch6.2.1, 38.331
#define DL_SCH_LCID_CCCH                           0x00
#define DL_SCH_LCID_DCCH                           0x01
#define DL_SCH_LCID_DCCH1                          0x02
#define DL_SCH_LCID_DTCH                           0x04
#define DL_SCH_LCID_RECOMMENDED_BITRATE            0x2F
#define DL_SCH_LCID_SP_ZP_CSI_RS_RES_SET_ACT       0x30
#define DL_SCH_LCID_PUCCH_SPATIAL_RELATION_ACT     0x31
#define DL_SCH_LCID_SP_SRS_ACTIVATION              0x32
#define DL_SCH_LCID_SP_CSI_REP_PUCCH_ACT           0x33
#define DL_SCH_LCID_TCI_STATE_IND_UE_SPEC_PDCCH    0x34
#define DL_SCH_LCID_TCI_STATE_ACT_UE_SPEC_PDSCH    0x35
#define DL_SCH_LCID_APERIODIC_CSI_TRI_STATE_SUBSEL 0x36
#define DL_SCH_LCID_SP_CSI_RS_CSI_IM_RES_SET_ACT   0X37
#define DL_SCH_LCID_DUPLICATION_ACT                0X38
#define DL_SCH_LCID_SCell_ACT_4_OCT                0X39
#define DL_SCH_LCID_SCell_ACT_1_OCT                0X3A
#define DL_SCH_LCID_L_DRX                          0x3B
#define DL_SCH_LCID_DRX                            0x3C
#define DL_SCH_LCID_TA_COMMAND                     0x3D
#define DL_SCH_LCID_CON_RES_ID                     0x3E
#define DL_SCH_LCID_PADDING                        0x3F

#define UL_SCH_LCID_CCCH1                          0x00
#define UL_SCH_LCID_SRB1                           0x01
#define UL_SCH_LCID_SRB2                           0x02
#define UL_SCH_LCID_SRB3                           0x03
#define UL_SCH_LCID_DTCH                           0x04
#define UL_SCH_LCID_CCCH                           0x34
#define UL_SCH_LCID_RECOMMENDED_BITRATE_QUERY      0x35
#define UL_SCH_LCID_MULTI_ENTRY_PHR_4_OCT          0x36
#define UL_SCH_LCID_CONFIGURED_GRANT_CONFIRMATION  0x37
#define UL_SCH_LCID_MULTI_ENTRY_PHR_1_OCT          0x38
#define UL_SCH_LCID_SINGLE_ENTRY_PHR               0x39
#define UL_SCH_LCID_C_RNTI                         0x3A
#define UL_SCH_LCID_S_TRUNCATED_BSR                0x3B
#define UL_SCH_LCID_L_TRUNCATED_BSR                0x3C
#define UL_SCH_LCID_S_BSR                          0x3D
#define UL_SCH_LCID_L_BSR                          0x3E
#define UL_SCH_LCID_PADDING                        0x3F
```

## LCID defined in OSC

```c
#define MAC_LCID_CCCH              0
#define MAC_LCID_MIN               1
#define MAC_LCID_MAX               32
#define MAC_LCID_RESERVED_MIN      33
#define MAC_LCID_RESERVED_MAX      51
#define MAC_LCID_CCCH_48BIT        52
#define MAC_LCID_BIT_RATE_QUERY    53
#define MAC_LCID_MULT_PHR_FOUR_OCT 54
#define MAC_LCID_CFG_GRANT_CFM     55
#define MAC_LCID_MULT_PHR_ONE_OCT  56
#define MAC_LCID_SINGLE_PHR        57
#define MAC_LCID_CRNTI             58
#define MAC_LCID_SHORT_TRUNC_BSR   59
#define MAC_LCID_LONG_TRUNC_BSR    60
#define MAC_LCID_SHORT_BSR         61
#define MAC_LCID_LONG_BSR          62
#define [MAC_LCID_CRI](https://www.notion.so/Main-Page-12110098314381cc92f0d3a5e80580f0?pvs=21)               62
#define MAC_LCID_PADDING           63
```