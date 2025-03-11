# RAR PDU

Start Date: 2024/07/18
Summary: Development and implementation of the Random Access Response Protocol Data Unit (RAR PDU) for 5G communication systems.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 Reference:
[https://blog.csdn.net/m0_45416816/article/details/99690204](https://blog.csdn.net/m0_45416816/article/details/99690204)
https://blog.csdn.net/dear_father/article/details/107793162K

</aside>

![{5615C426-1079-4C46-B938-08410A69534B}.png](5615C426-1079-4C46-B938-08410A69534B.png)

![{3678BEE1-8E0A-4D67-89F3-70B8A5F40CC2}.png](3678BEE1-8E0A-4D67-89F3-70B8A5F40CC2.png)

![{ADC092FC-5C85-4703-8189-891818207D87}.png](ADC092FC-5C85-4703-8189-891818207D87.png)

![{836ACCE5-FC08-45D1-8118-331BDD09CBF1}.png](836ACCE5-FC08-45D1-8118-331BDD09CBF1.png)

![Untitled](Untitled%2040.png)

## **RA_backoff_indicator**

![Untitled](Untitled%2041.png)

## RAR PDU

```c
/////////////////////////////////////
//    Random Access Response PDU   //
//         TS 38.213 ch 8.2        //
//        TS 38.321 ch 6.2.3       //
/////////////////////////////////////
//| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |// bit-wise
//| E | T |       R A P I D       |//
//| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |//
//| R |           T A             |//
//|       T A         |  UL grant |//
//|            UL grant           |//
//|            UL grant           |//
//|            UL grant           |//
//|         T C - R N T I         |//
//|         T C - R N T I         |//
/////////////////////////////////////
```

### UL grant

```c
/////////////////////////////////////
//       UL grant  (27 bits)       //
/////////////////////////////////////
//| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |// bit-wise
//|-------------------|FHF|F_alloc|//
//|        Freq allocation        |//
//|    F_alloc    |Time allocation|//
//|      MCS      |     TPC   |CSI|//
/////////////////////////////////////
```

- OAI Implement

```c
static void nr_fill_rar(uint8_t Mod_idP, NR_RA_t *ra, uint8_t *dlsch_buffer, nfapi_nr_pusch_pdu_t *pusch_pdu)
{
  LOG_D(NR_MAC, "[gNB] Generate RAR MAC PDU frame %d slot %d preamble index %u TA command %d \n", ra->Msg2_frame, ra-> Msg2_slot, ra->preamble_index, ra->timing_offset);
  NR_RA_HEADER_BI *rarbi = (NR_RA_HEADER_BI *) dlsch_buffer;
  NR_RA_HEADER_RAPID *rarh = (NR_RA_HEADER_RAPID *) (dlsch_buffer + 1);
  NR_MAC_RAR *rar = (NR_MAC_RAR *) (dlsch_buffer + 2);
  unsigned char csi_req = 0, tpc_command;

  tpc_command = 3; // this is 0 dB

  /// E/T/R/R/BI subheader ///
  // E = 1, MAC PDU includes another MAC sub-PDU (RAPID)
  // T = 0, Back-off indicator subheader
  // R = 2, Reserved
  // BI = 0, 5ms
  rarbi->E = 1;
  rarbi->T = 0;
  rarbi->R = 0;
  rarbi->BI = 0;

  /// E/T/RAPID subheader ///
  // E = 0, one only RAR, first and last
  // T = 1, RAPID
  rarh->E = 0;
  rarh->T = 1;
  rarh->RAPID = ra->preamble_index;
```

- OSC IMplement

```c
void fillRarPdu(RarInfo *rarInfo)
{
   uint8_t   *rarPdu = rarInfo->rarPdu;
   uint8_t   bitPos = 0;
   uint16_t  bytePos= 0, bwpSize = 0, rbStart = 0, rbLen = 0;
   uint8_t   numHopInfoBitsInFreqAlloc = 0;
   uint8_t   actualFreqRsrcAllocSize = 0;

   /* RAR subheader fields */
   uint8_t   EBit = 0;
   uint8_t   TBit = 0;

   /* RAR payload fields */
   uint8_t   RBit = 0;
   uint16_t  msg3FreqResource = 0;
   uint8_t   paddingLcid = 63;
   DU_LOG("\nSTART of fillRarPdu\n");

   /* Considering 2 bytes of padding in RAR PDU. 
    * 1st byte is MAC sub-header for padding
    * 2nd byte contains padding bits
    */
   uint8_t   paddingSize = 8;

   /* Fill RAR pdu fields */
   EBit = 0;
   TBit = 1;
   RBit = 0;

   rarInfo->rarPduLen = RAR_PAYLOAD_SIZE;

   /* Initialize buffer */
   for(bytePos = 0; bytePos < rarInfo->rarPduLen; bytePos++)
      rarPdu[bytePos] = 0;

   bytePos = 0;
   bitPos = 7;

   /* Packing fields into RAR PDU */
   packBytes(rarPdu, &bytePos, &bitPos, EBit, E_BIT_SIZE); 
   packBytes(rarPdu, &bytePos, &bitPos, TBit, T_BIT_SIZE);
   packBytes(rarPdu, &bytePos, &bitPos, rarInfo->RAPID, RAPID_SIZE);
   packBytes(rarPdu, &bytePos, &bitPos, RBit, R_BIT_SIZE);
   packBytes(rarPdu, &bytePos, &bitPos, rarInfo->ta, TIMING_ADVANCE_SIZE);
   DU_LOG("Packing fields into RAR PDU\n");
   /* Packing MSG3 UL Grant in RAR */
   packBytes(rarPdu, &bytePos, &bitPos, rarInfo->ulGrant.freqHopFlag, FREQ_HOP_FLAG_SIZE);
```

- OSC is same with 3GPP spec
- Next step I want to print out all of RAR PDU in OAI(VNF) and OSC DU

```c
/* As per spec 38.321, sections 6.1.5 and 6.2.3, 
RAR PDU is 8 bytes long and 2 bytes of padding */
RAR PDU: -> 
5B 00 00 2D 00 56 00 64 3F 00 
52 00 00 2D 00 16 00 64 3F 00 
10 62 00 00 2D 00 16 00 64 00 // add BI subheader remove padding of 2 bytes
10 44 00 00 2D 00 16 00 64 00 

02 0A 80 64

10 5B 00 00 2D 00 16 00 64 00 
->  5b10 16002d 64
80 48 00 00 2D 00 16 00 64 00 
->  4880 16002d 64 
80 7A 00 00 2E 60 16 00 64 00 
80 58 00 00 2E 63 16 00 64 00 

// PNF
4d80 16632e 64 90060000 56d084 70962600 1de35cb 1020b8 404000 d14d220 30d32187 800 8673729a 80189559 5f33b506 4e127072 db622a71 4c8fa6c6 50002e9c 2c08d0e1 23126007 cb137
```

```c
/////////////////////////////////////
//    Random Access Response PDU   //
//         TS 38.213 ch 8.2        //
//        TS 38.321 ch 6.2.3       //
/////////////////////////////////////
//| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |// bit-wise
//| E | T |       R A P I D       |//
//| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |//
//| R |           T A             |//
//|       T A         |  UL grant |//
//|            UL grant           |//
//|            UL grant           |//
//|            UL grant           |//
//|         T C - R N T I         |//
//|         T C - R N T I         |//
/////////////////////////////////////
//       UL grant  (27 bits)       //
/////////////////////////////////////
//| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |// bit-wise
//|-------------------|FHF|F_alloc|//
//|        Freq allocation        |//
//|    F_alloc    |Time allocation|//
//|      MCS      |     TPC   |CSI|//
/////////////////////////////////////
```

| 0 E | 1 T | 0 | 1 | 1 | 0 | 1 | 1 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 0 R | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 FHF | 0 | 0 |
| 0 | 0 | 1 | 0 | 1 | 1 | 0 | 1 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 1 | 0 | 1 | 0 | 1 | 1 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 1 | 1 | 0 | 0 | 1 | 0 | 0 |

### OAI Value

```
juil. 18 16:25:32 [0m1721312732.170962 [NR_MAC]   rarh->E = 0x0
juil. 18 16:25:32 [0m1721312732.170963 [NR_MAC]   rarh->T = 0x1
juil. 18 16:25:32 [0m1721312732.170964 [NR_MAC]   rarh->RAPID = 0x24 (36)
juil. 18 16:25:32 [0m1721312732.170965 [NR_MAC]   rar->R = 0x0
juil. 18 16:25:32 [0m1721312732.170965 [NR_MAC]   rar->TA1 = 0x0
juil. 18 16:25:32 [0m1721312732.170966 [NR_MAC]   rar->TA2 = 0x0
juil. 18 16:25:32 [0m1721312732.170967 [NR_MAC]   rar->UL_GRANT_1 = 0x0
juil. 18 16:25:32 [0m1721312732.170967 [NR_MAC]   rar->UL_GRANT_2 = 0x2e
juil. 18 16:25:32 [0m1721312732.170968 [NR_MAC]   rar->UL_GRANT_3 = 0x63
juil. 18 16:25:32 [0m1721312732.170969 [NR_MAC]   rar->UL_GRANT_4 = 0x16
juil. 18 16:25:32 [0m1721312732.170969 [NR_MAC]   rar->TCRNTI_1 = 0x39
juil. 18 16:25:32 [0m1721312732.170970 [NR_MAC]   rar->TCRNTI_2 = 0x3c
```

```c
0x80 0x2e 0xc7 0xf1 0x84 0x0 0xcb 0xb8 0x0 0x40 0x40 0x10 0x40 0x48 0x87 0x20 0xc9 0x54 0xd4 0xc0 0xa9 0x9a 0xb8 0x40 0x80 0xc4
80 2e 35 f1 84 0 cb b8 0 40 40 10 40 48 87 20 c9 54 d4 c0 a9 9a b8 40 80 c4

juil. 19 11:48:46 Fill RAR [RAR PDU]
juil. 19 11:48:46 80 4a 0 0 2e 63 16 b9 bd 0 40 2 f1 85 3a 90 84 d0 56 0 0 26 96 70 cb 35 fe 5 b8 20 10 0 0 40 41 b8 40 10 0 0 40 41 b8 60 10 0 0 40 40 0 61 3 48 50 36 1c 87 4c c0 0 20 0 2 69 
juil. 19 11:48:46 END [RAR PDU]
juil. 19 11:48:46 
juil. 19 11:48:46 After nr_fill_rar [RAR PDU]
juil. 19 11:48:46 80 4a 0 0 2e 63 16 b9 bd 0 40 2 f1 85 3a 90 84 d0 56 0 0 26 96 70 cb 35 fe 5 b8 20 10 0 0 40 41 b8 40 10 0 0 40 41 b8 60 10 0 0 40 40 0 61 3 48 50 36 1c 87 4c c0 0 20 0 2 69 
juil. 19 11:48:46 END [RAR PDU]
juil. 19 11:48:46 
juil. 19 11:48:46 [RAR PDU]
juil. 19 11:48:46 4a80 b916632e 24000bd 903a85f1 56d084 70962600 5fe35cb 1020b8 b8414000 1040 60b84140 40000010 3610040 1c365048 c04c87 69020020 6619cec9 1a006254 c97dcdd4 c63949c0 1a6f8da9 70323d9a 874301b8 1db02040 de8c4880 30c4 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
juil. 19 11:48:46 END [RAR PDU]

// RAPID = 0x20
80 60 0 0 2e 63 16 fd 47 0 40 2 f1 85 3a 90 84 d0 56 0 0 26 96 70 cb 35 fe 5 b8 20 10 0 0 40 41 b8 40 10 0 0 40 41 b8 60 10 0 0 40 40 0 61 3 48 50 36 1c 87 4c c0 0 20 0 2 69 c9 ce 19 66 54 62 0 1a d4 cd 7d c9 c0 49 39 c6 a9 8d 6f 1a 9a 3d 32 70 b8 1 43 87 40 20 b0 1d 80 48 8c de c4 30 0 0 0 0 0 0 0 0 
4301b8 1db02040 de8c4880 30c4 0 0 0 0 0 0 0 

//PNF 

juil. 19 15:48:34  decoding [RAR PDU]
juil. 19 15:48:34 7a80 d016632e 24000d5 903a85f1 56d084 70962600 5fe35cb 1020b8 b8414000 1040 60b84140 40000010 3610040 1c365048 c04c87 69020020 6619cec9 1a006254 c97dcdd4 c63949c0 1a6f8da9 70323d9a 874301b8 1db02040 de8c4880 30c4 
```

| param | OAI value | OAI two times vales (caheck random value) | OAI three times vales (caheck random value) | OSC value |
| --- | --- | --- | --- | --- |
| rarh->E | 0x0 | 0x0 | 0x0 | 0x0 |
| rarh->T | 0x1 | 0x1 | 0x1 | 0x1 |
| rarh->RAPID | 0x24 | 0x9 | 0x1e | 0x1B |
| rar->R | 0x0 | 0x0 | 0x0 | 0x0 |
| rar->TA1 | 0x0 | 0x0 | 0x0 | 0x0 |
| rar->TA2 | 0x0 | 0x0 | 0x0 | 0x0 |
| rar->UL_GRANT_1 | 0x0 | 0x0 | 0x0 | 0x0 |
| rar->UL_GRANT_2 | 0x2e | 0x2e | 0x2e | 0x2d |
| rar->UL_GRANT_3 | 0x63 | 0x60 | 0x63 | 0x00 |
| rar->UL_GRANT_4 | 0x16 | 0x6 | 0x16 | 0x56 |
| rar->TCRNTI_1 | 0x39 | 0xfe | 0x77 | 0x0 |
| rar->TCRNTI_2 | 0x3c | 0xaa | 0x9e | 0x64 |

## UL grant

|  | OAI value | OSC value |
| --- | --- | --- |
| 9o0ooFoo9HF | 0 | 0 |
| Freq allocation | 742 | 720 |
| Time allocation | 3 | 0 |
| MCS | 1 | 1 |
| TPC | 3 | 3 |
| CSI | 0 | 0 |

## OSC modify config path

```c
      /* Fill RAR info */
      DU_LOG("\nINFO  -->  Fill RAR info..\n");
      dciSlotAlloc->raRnti = cell->raReq[ueId-1]->raRnti;
      dciSlotAlloc->rarInfo.tcrnti = cell->raReq[ueId-1]->rachInd->crnti;
      dciSlotAlloc->rarInfo.RAPID = cell->raReq[ueId-1]->rachInd->preambleIdx;
      dciSlotAlloc->rarInfo.ta = cell->raReq[ueId-1]->rachInd->timingAdv;
      printf("dciSlotAlloc->raRnti:%d\n",dciSlotAlloc->raRnti);
      printf("dciSlotAlloc->rarInfo.tcrnti:%d\n",dciSlotAlloc->rarInfo.tcrnti);
      printf("dciSlotAlloc->rarInfo.RAPID:%d\n",dciSlotAlloc->rarInfo.RAPID);
      printf("dciSlotAlloc->rarInfo.ta:%d\n",dciSlotAlloc->rarInfo.ta);
```

### OAI set TCRNTI

```c
    rnti_t trial = 0;
    do {
      // 3GPP TS 38.321 version 15.13.0 Section 7.1 Table 7.1-1: RNTI values
      while (trial < 1 || trial > 0xffef)
        trial = (taus() % 0xffef) + 1;
      exist_connected_ue = find_nr_UE(&nr_mac->UE_info, trial) != NULL;
      exist_in_pending_ra_ue = find_nr_RA_rnti(cc->ra, sizeofArray(cc->ra), ra->rnti) != NULL;
      loop++;
    } while (loop < 100 && (exist_connected_ue || exist_in_pending_ra_ue) );
    if (loop == 100) {
      LOG_E(NR_MAC, "initialisation random access: no more available RNTIs for new UE\n");
      NR_SCHED_UNLOCK(&nr_mac->sched_lock);
      return;
    }
    ra->rnti = trial;
```

### OSC set TCRNTI

```c
#define ODU_START_CRNTI   100
#define ODU_END_CRNTI     500
```

```c
      /* Calculate CRNTI from UE Index */
      GET_CRNTI(crnti, ueIdx+1);
      printf("\n[GET_CRNTI] CRNTI: %d\n", crnti);
```

```c
#define GET_CRNTI( _crnti, _ueId)          \
{                                          \
   _crnti = _ueId + ODU_START_CRNTI - 1;  \
}
```

→ OSC hard code TCRNTI is 100 (because ueid is 1)

## OAI RAPID

- It is random number in every execute times, random by hardware.

## OAI TA

```bash
[MAC]   received TA command 31
```

```c
    // TA command
    NR_UL_TIME_ALIGNMENT_t *ul_time_alignment = &mac->ul_time_alignment;
    const int ta = rar->TA2 + (rar->TA1 << 5);
    ul_time_alignment->ta_command = ta;
    ul_time_alignment->ta_apply = rar_ta;

    LOG_W(MAC, "received TA command %d\n", 31 + ta);
```

- I think OAI set UEsim force hardcode advance 31
- OAI acuctully send TA is 0.