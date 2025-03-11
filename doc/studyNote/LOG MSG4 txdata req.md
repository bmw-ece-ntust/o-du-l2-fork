# LOG:MSG4 txdata.req

Start Date: 2024/09/19
Summary: Developing and analyzing MSG4 transmission data structures and handling in a communication system.
Status: Done
Assign: 陳奕全

dlMsgAlloc struct

```cpp

typedef struct dlMsgSchedInfo
{
   uint16_t        crnti;
   uint8_t         dciFormatId;
   uint8_t         harqProcNum;
   bool            vrbPrbMapping;
   uint8_t         dlAssignIdx;
   uint8_t         pucchTpc;
   uint8_t         pucchResInd;
   uint8_t         harqFeedbackInd;
   uint16_t        dlMsgPduLen;
   uint8_t         *dlMsgPdu;
   FreqDomainAlloc freqAlloc;
   TimeDomainAlloc timeAlloc;
   uint8_t         numOfTbs;
   TransportBlock  transportBlock[2];
   BwpCfg          bwp;
   PdcchCfg        *dlMsgPdcchCfg;
   PdschCfg        *dlMsgPdschCfg;
}DlMsgSchInfo;
```

**fillMsg4DlData**

dlCcchMsg

```
 九  19 14:17:37 ==========MSG4 or dedicate message=========
 九  19 14:17:37 
 九  19 14:17:37 crnti: 100
 九  19 14:17:37 dciFormatId: 1
 九  19 14:17:37 harqProcNum: 0
 九  19 14:17:37 vrbPrbMapping: 0
 九  19 14:17:37 dlAssignIdx: 0
 九  19 14:17:37 pucchTpc: 0
 九  19 14:17:37 pucchResInd: 0
 九  19 14:17:37 harqFeedbackInd: 0
 九  19 14:17:37 dlMsgPduLen: 113
 九  19 14:17:37 dlMsgPdu address: 0x7ef821e06610
 九  19 14:17:37 numOfTbs: 0
 九  19 14:17:37 TransportBlock[0].tbSize: 0
 九  19 14:17:37 TransportBlock[1].tbSize: 0
 九  19 14:17:37 ===============================
```

---

 OAI

**prepare_dl_pdus**

```
 九  19 15:37:51 [0m=====MSG4 or DEDicate message======
 九  19 15:37:51 rnti: 51180
 九  19 15:37:51 SubcarrierSpacing: 1
 九  19 15:37:51 CyclicPrefix: 0
 九  19 15:37:51 NrOfCodewords: 1
 九  19 15:37:51 targetCodeRate[0]: 1200
 九  19 15:37:51 qamModOrder[0]: 2
 九  19 15:37:51 mcsIndex[0]: 0
 九  19 15:37:51 mcsTable[0]: 0
 九  19 15:37:51 rvIndex[0]: 0
 九  19 15:37:51 dataScramblingId: 1
 九  19 15:37:51 nrOfLayers: 1
 九  19 15:37:51 transmissionScheme: 0
 九  19 15:37:51 refPoint: 0
 九  19 15:37:51 dmrsConfigType: 0
 九  19 15:37:51 dlDmrsScramblingId: 1
 九  19 15:37:51 SCID: 0
 九  19 15:37:51 numDmrsCdmGrpsNoData: 2
 九  19 15:37:51 dmrsPorts: 1
 九  19 15:37:51 resourceAlloc: 1
 九  19 15:37:51 rbStart: 0
 九  19 15:37:51 rbSize: 42
 九  19 15:37:51 VRBtoPRBMapping: 0
 九  19 15:37:51 StartSymbolIndex: 1
 九  19 15:37:51 NrOfSymbols: 13
 九  19 15:37:51 dlDmrsSymbPos: 2180
 九  19 15:37:51 ===============================
```

transmissionScheme

| item | OSC+OAI | Whole OAI |
| --- | --- | --- |
| **crnti / rnti** | 100 | 51180 |
| **dciFormatId** | 1 | - |
| **harqProcNum** | 0 | - |
| **vrbPrbMapping** | 0 | 0 |
| **dlAssignIdx** | 0 | - |
| **pucchTpc** | 0 | - |
| **pucchResInd** | 0 | - |
| **harqFeedbackInd** | 0 | - |
| **dlMsgPduLen** | 113 | - |
| **dlMsgPdu address** | 0x7ef821e06610 | - |
| **numOfTbs** | 0 | - |
| **TransportBlock[0].tbSize** | 0 | - |
| **TransportBlock[1].tbSize** | 0 | - |
|  |  |  |
|  |  |  |
|  |  |  |
|  |  |  |

MSG4 PDSCH PDU table

| Member | OSC |  |
| --- | --- | --- |
| pduBitmap | 0 
(PTRS and CBG params excluded) |  |
| rnti | cell->raCb[ueId-1].tcrnti
100 |  |
| pduIndex | 0 |  |
| numCodewords | 1 | 1 |
| codeword[cwCount].targetCodeRate | 308 | 1200 |
| codeword[cwCount].qamModOrder | 2 | 2 |
| codeword[cwCount].mcsIndex | mcs
  (configured to 4)
5 | 0 |
| codeword[cwCount].mcsTable | 0 (not 256 QAM) | 0 |
| codeword[cwCount].rvIndex | If not retransmission: 0, else (pdsch->codeword[cwCount].rvIndex + 1) & 0x03
0 | 0 |
| codeword[cwCount].tbSize | tbSize
  (Calculated TB size)
145 | - |
| dataScramblingId | cell->cellCfg.phyCellId 
1 | 1 |
| numLayers | 1 | - |
| transmissionScheme | 0 | 0 |
| refPoint | 0 | 0 |
| dmrs.dlDmrsSymbPos | DL_DMRS_SYMBOL_POS
4 | 2180 |
| dmrs.dmrsConfigType | 0 (Type-1) | 0 |
| dmrs.dlDmrsScramblingId | cell->cellCfg.phyCellId | 1 |
| dmrs.scid | 0 | 0 |
| dmrs.numDmrsCdmGrpsNoData | 1 | 2 |
| dmrs.dmrsPorts | 0 | 1 |
| dmrs.mappingType | DMRS_MAP_TYPE_A
  (Type-A) 
**1** |  |
| dmrs.nrOfDmrsSymbols | NUM_DMRS_SYMBOLS 
1 |  |
| dmrs.dmrsAddPos | DMRS_ADDITIONAL_POS
0 |  |
| pdschTimeAlloc.startSymb | pdschStartSymbol 
1 |  |
| pdschTimeAlloc.numSymb | pdschNumSymbols 
5 |  |
| pdschFreqAlloc.resourceAllocType | 1 (RAT Type-1 RIV format) |  |
| pdschFreqAlloc.startPrb | MAX_NUM_RB
240 |  |
| pdschFreqAlloc.numPrb | schCalcNumPrb(tbSize, mcs,
  pdschNumSymbols)
33 |  |
| pdschFreqAlloc.vrbPrbMapping | 0 (non-interleaved) |  |
| beamPdschInfo.numPrgs | 1 |  |
| beamPdschInfo.prgSize | 1 |  |
| beamPdschInfo.digBfInterfaces | 0 |  |
| beamPdschInfo.prg[0].pmIdx | 0 |  |
| beamPdschInfo.prg[0].beamIdx[0] | 0 |  |
| txPdschPower.powerControlOffset | 0 |  |
| txPdschPower.powerControlOffsetSS | 0 |  |

OSC OAI_OSC_fillDlMsgTxDataReq

```c
   printf("=========MSG4 TXdata:=======\n");~~Create a wireguard VPN~~
   printf("pduBitmap: %d\n", pdschCfg->pduBitmap);
   printf("rnti: %d\n", pdschCfg->rnti);
   printf("pduIndex: %d\n", pdschCfg->pduIndex);
   printf("numCodewords: %d\n", pdschCfg->numCodewords);

   for(int cwCount = 0; cwCount < pdschCfg->numCodewords; cwCount++)
   {
      printf("codeword[%d].targetCodeRate: %d\n", cwCount, pdschCfg->codeword[cwCount].targetCodeRate);
      printf("codeword[%d].qamModOrder: %d\n", cwCount, pdschCfg->codeword[cwCount].qamModOrder);
      printf("codeword[%d].mcsIndex: %d\n", cwCount, pdschCfg->codeword[cwCount].mcsIndex);
      printf("codeword[%d].mcsTable: %d\n", cwCount, pdschCfg->codeword[cwCount].mcsTable);
      printf("codeword[%d].rvIndex: %d\n", cwCount, pdschCfg->codeword[cwCount].rvIndex);
      printf("codeword[%d].tbSize: %d\n", cwCount, pdschCfg->codeword[cwCount].tbSize);
   }

   printf("dataScramblingId: %d\n", pdschCfg->dataScramblingId);
   printf("numLayers: %d\n", pdschCfg->numLayers);
   printf("transmissionScheme: %d\n", pdschCfg->transmissionScheme);
   printf("refPoint: %d\n", pdschCfg->refPoint);

   /* DMRS fields */
   printf("dmrs.dlDmrsSymbPos: %d\n", pdschCfg->dmrs.dlDmrsSymbPos);
   printf("dmrs.dmrsConfigType: %d\n", pdschCfg->dmrs.dmrsConfigType);
   printf("dmrs.dlDmrsScramblingId: %d\n", pdschCfg->dmrs.dlDmrsScramblingId);
   printf("dmrs.scid: %d\n", pdschCfg->dmrs.scid);
   printf("dmrs.numDmrsCdmGrpsNoData: %d\n", pdschCfg->dmrs.numDmrsCdmGrpsNoData);
   printf("dmrs.dmrsPorts: %d\n", pdschCfg->dmrs.dmrsPorts);
   printf("dmrs.mappingType: %d\n", pdschCfg->dmrs.mappingType);
   printf("dmrs.nrOfDmrsSymbols: %d\n", pdschCfg->dmrs.nrOfDmrsSymbols);
   printf("dmrs.dmrsAddPos: %d\n", pdschCfg->dmrs.dmrsAddPos);

   /* Time and frequency allocation */
   printf("pdschTimeAlloc.startSymb: %d\n", pdschCfg->pdschTimeAlloc.startSymb);
   printf("pdschTimeAlloc.numSymb: %d\n", pdschCfg->pdschTimeAlloc.numSymb);

   printf("pdschFreqAlloc.resourceAllocType: %d\n", pdschCfg->pdschFreqAlloc.resourceAllocType);
   printf("pdschFreqAlloc.startPrb: %d\n", pdschCfg->pdschFreqAlloc.startPrb);
   printf("pdschFreqAlloc.numPrb: %d\n", pdschCfg->pdschFreqAlloc.numPrb);
   printf("pdschFreqAlloc.vrbPrbMapping: %d\n", pdschCfg->pdschFreqAlloc.vrbPrbMapping);

   /* Beam information */
   printf("beamPdschInfo.numPrgs: %d\n", pdschCfg->beamPdschInfo.numPrgs);
   printf("beamPdschInfo.prgSize: %d\n", pdschCfg->beamPdschInfo.prgSize);
   printf("beamPdschInfo.digBfInterfaces: %d\n", pdschCfg->beamPdschInfo.digBfInterfaces);
   printf("beamPdschInfo.prg[0].pmIdx: %d\n", pdschCfg->beamPdschInfo.prg[0].pmIdx);
   printf("beamPdschInfo.prg[0].beamIdx[0]: %d\n", pdschCfg->beamPdschInfo.prg[0].beamIdx[0]);

   /* Transmission power */
   printf("txPdschPower.powerControlOffset: %d\n", pdschCfg->txPdschPower.powerControlOffset);
   printf("txPdschPower.powerControlOffsetSS: %d\n", pdschCfg->txPdschPower.powerControlOffsetSS);

   printf("============================\n\n\n\n\n\n");
```

```
//OSC
 九  24 23:50:20 =========MSG4 TXdata:=======
 九  24 23:50:20 pduBitmap: 0
 九  24 23:50:20 rnti: 100
 九  24 23:50:20 pduIndex: 0
 九  24 23:50:20 numCodewords: 1
 九  24 23:50:20 codeword[0].targetCodeRate: 308
 九  24 23:50:20 codeword[0].qamModOrder: 2
 九  24 23:50:20 codeword[0].mcsIndex: 5
 九  24 23:50:20 codeword[0].mcsTable: 0
 九  24 23:50:20 codeword[0].rvIndex: 0
 九  24 23:50:20 codeword[0].tbSize: 145
 九  24 23:50:20 dataScramblingId: 1
 九  24 23:50:20 numLayers: 1
 九  24 23:50:20 transmissionScheme: 0
 九  24 23:50:20 refPoint: 0
 九  24 23:50:20 dmrs.dlDmrsSymbPos: 4
 九  24 23:50:20 dmrs.dmrsConfigType: 0
 九  24 23:50:20 dmrs.dlDmrsScramblingId: 1
 九  24 23:50:20 dmrs.scid: 0
 九  24 23:50:20 dmrs.numDmrsCdmGrpsNoData: 1
 九  24 23:50:20 dmrs.dmrsPorts: 0
 九  24 23:50:20 dmrs.mappingType: 1
 九  24 23:50:20 dmrs.nrOfDmrsSymbols: 1
 九  24 23:50:20 dmrs.dmrsAddPos: 0
 九  24 23:50:20 pdschTimeAlloc.startSymb: 1
 九  24 23:50:20 pdschTimeAlloc.numSymb: 5
 九  24 23:50:20 pdschFreqAlloc.resourceAllocType: 1
 九  24 23:50:20 pdschFreqAlloc.startPrb: 240
 九  24 23:50:20 pdschFreqAlloc.numPrb: 33
 九  24 23:50:20 pdschFreqAlloc.vrbPrbMapping: 0
 九  24 23:50:20 beamPdschInfo.numPrgs: 1
 九  24 23:50:20 beamPdschInfo.prgSize: 1
 九  24 23:50:20 beamPdschInfo.digBfInterfaces: 0
 九  24 23:50:20 beamPdschInfo.prg[0].pmIdx: 0
 九  24 23:50:20 beamPdschInfo.prg[0].beamIdx[0]: 0
 九  24 23:50:20 txPdschPower.powerControlOffset: 0
 九  24 23:50:20 txPdschPower.powerControlOffsetSS: 0
 九  24 23:50:20 ============================
 九  24 23:50:20 
 九  24 23:50:20 
```

**OSC:
fillMsg4Pdu**

Here odu fill the MSG4 PDU into dlMsgPdu

```c
   //TX_data OAI_OSC_fillDlMsgTxDataReq
   memcpy(dlMsgPayload, dlMsgSchInfo->dlMsgPdu, dlMsgSchInfo->dlMsgPduLen);
```

```c
	//MAC buildAndSendMuxPdu           
            fillMsg4Pdu(currTimingInfo.cellId, currDlSlot->dlInfo.dlMsgAlloc[ueIdx]);
```

```c
 //MAC fillMsg4Pdu
   /* storing msg4 Pdu in macDlSlot */
   if(hqProcCb->tbInfo[0].tb)
   {
      msg4SchInfo->dlMsgPduLen = msg4TxPduLen;
      MAC_ALLOC(msg4SchInfo->dlMsgPdu, msg4SchInfo->dlMsgPduLen);
      if(msg4SchInfo->dlMsgPdu != NULLP)
      {
         memcpy(msg4SchInfo->dlMsgPdu, hqProcCb->tbInfo[0].tb, \
               msg4SchInfo->dlMsgPduLen);
      }
   }
```

What’s `hqProcCb`

```c
   hqProcCb = &macCb.macCell[cellIdx]->macRaCb[ueIdx].msg4HqInfo;
```

Which function pack MSG4 txdata：**macMuxPdu**

![image.png](image%2074.png)

LCID:0

```cpp

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
#define MAC_LCID_CRI               62
#define MAC_LCID_PADDING           63
```

```c
            {
               lenField = dlData->pduInfo[pduIdx].pduLen;
               if(dlData->pduInfo[pduIdx].pduLen > 255)
               {
                  FBit = 1;
                  lenFieldSize = 16;

               }
               else
               {
                  FBit = 0;
                  lenFieldSize = 8;
               }
               /* Packing fields into MAC PDU R/F/LCID/L */
               packBytes(macPdu, &bytePos, &bitPos, RBit, RBitSize);
               packBytes(macPdu, &bytePos, &bitPos, FBit, FBitSize);
               packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
               packBytes(macPdu, &bytePos, &bitPos, lenField, lenFieldSize);
               memcpy(&macPdu[bytePos], dlData->pduInfo[pduIdx].dlPdu, lenField);
               bytePos += lenField;
               break;
            }
```

/* Packing fields into MAC PDU R/F/LCID/L */

| Item | OSC | OAI NR_MAC_SUBHEADER_SHORT |
| --- | --- | --- |
| RBit | 0 | 0 |
| FBit | 0 | 0 |
| lcid | 0 | 0 |
| lenField | 137 | 137 |

MSG4 MAC CE (Control Element)
UE Contention Resolution Identity of 4-step RA

![image.png](image%2075.png)

UE Contention Resolution Identity (48 bits) : Contain UL CCCH SDU, such as RRCSetupRequest (if UL CCCH SDU is longer than 48 bits, this field contains the first 48 bits of the UL CCCH SDU) (38.321)

```cpp
typedef struct {
  uint8_t LCID: 6;    // octet 1 [5:0]
  uint8_t F: 1;       // octet 1 [6]
  uint8_t R: 1;       // octet 1 [7]
  uint8_t L: 8;       // octet 2 [7:0]
} __attribute__ ((__packed__)) NR_MAC_SUBHEADER_SHORT;

typedef struct {
  uint8_t LCID: 6;
  uint8_t F: 1;
  uint8_t R: 1;
  uint16_t L: 16;
} __attribute__ ((__packed__)) NR_MAC_SUBHEADER_LONG;
```

## OAI:

**nr_generate_Msg4**

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

OAI

```
 九  26 12:55:53 [0m1727326553.334683 [NR_MAC]   MSG4 PDU
 九  26 12:55:53 
 九  26 12:55:53 
 九  26 12:55:53 
 九  26 12:55:53 [0m1727326553.334684 [NR_MAC]   NR_MAC_SUBHEADER_SHORT: R=0, F=0, LCID=0, L=137
```

---

---

## Issue found

OSC original source code rewrite `redundancyVer` two times in `fillDlMsgDlDciPdu` so I think I need to revise this bug.

![image.png](image%2076.png)

Remove one `redundancyVer`