# Invalid CCCH message

Start Date: 2024/09/30
Summary: Investigating and troubleshooting the invalid CCCH message issue in the communication between OSC DU and OAI systems.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/13
SUM: 🗓️ Days Spent to Complete: 13

<aside>
✅

Solution: TBS and RB size in OSC and OAI implementations do not match, so MSG4 information is not fully transmitted correctly. → [Compute TBS and PRB](Compute%20TBS%20and%20PRB%20121100983143819aa2b2c12155d157f8.md) 

</aside>

# Trace Message Flow

The message needs to be sent from `OSC DU` to `OAI Layer1` and `OAI UE`.

I will check each part to ensure the message is processed correctly.

|  | 🔗 Note Link |
| --- | --- |
| OAI CU relate | [Compare CU Logs](Compare%20CU%20Logs%201211009831438112a179dbddf976f6cf.md)  |
| OSC DU send message4 | [Compare OSC DU send MSG4](Compare%20OSC%20DU%20send%20MSG4%201211009831438147a50bd917d4b0a91d.md)  |
| OAI PNF recieve message4 and processed  | [Compare OAI PNF recieve MSG4](Compare%20OAI%20PNF%20recieve%20MSG4%2012110098314381c180f1e4809fbc4292.md)  |
| OAI UE recieve message4 and processed  | [Compare OAI UE receive MSG4](Compare%20OAI%20UE%20receive%20MSG4%2012110098314381d690cdc975187a879a.md)  |

![image.png](image.png)

It successfully received the PDSCH message from PNF and from OSC DU High, but the CCCH message is invalid.

```
 十  08 19:31:37 [0m[PHY]   Copying DLSCH PDU to UE PHY
 十  08 19:31:37 [0m[PHY]   current_harq_pid = 0
 十  08 19:31:37 [0m[PHY]   Updating harq_status for harq_id 0, ack/nak 1
 十  08 19:31:37 [0m[NR_MAC]   ul config in slot 18
 十  08 19:31:37 [0m[MAC]   In [185.15] Handling DLSCH PDU type 3
 十  08 19:31:37 [0m[MAC]   pduP: 0x75e6e1dde3c0, pdu_len: 40
 十  08 19:31:37 [0m[MAC]   [185.15]: processing PDU 0 (with length 40) of 1 total number of PDUs...
 十  08 19:31:37 [0m[MAC]   [UE] LCID 0, PDU length 40
 十  08 19:31:37 [0m[1;31m[NR_MAC]   Invalid CCCH message!, pdu_len: 40
 十  08 19:31:37 [0m[PHY]   Copying pucch pdu to UE PHY
 十  08 19:31:37 [0m[1;31m[PHY]   [UE 0] frame 188, nr_slot_rx 0, Error decoding PBCH!
 十  08 19:31:37 [0m[1;31m[PHY]   [UE 0] frame 190, nr_slot_rx 0, Error decoding PBCH!
 十  08 19:31:37 [0m[1;31m[PHY]   [UE 0] frame 192, nr_slot_rx 0, Error decoding PBCH!
 十  08 19:31:37 [0m[NR_PHY]   ============================================
 十  08 19:31:37 [0m[NR_PHY]   Harq round stats for Downlink: 3/0/0
 十  08 19:31:37 [0m[NR_PHY]   ============================================
```

- Compare with OAI VNF + OAI PNF + OAI UE Logs

```
 十  08 19:32:12 [0m[PHY]   Copying DLSCH PDU to UE PHY
 十  08 19:32:12 [0m[PHY]   current_harq_pid = 0
 十  08 19:32:12 [0m[PHY]   Updating harq_status for harq_id 0, ack/nak 1
 十  08 19:32:12 [0m[NR_MAC]   ul config in slot 18
 十  08 19:32:12 [0m[MAC]   In [185.12] Handling DLSCH PDU type 3
 十  08 19:32:12 [0m[MAC]   pduP: 0x7382473dc2c0, pdu_len: 149
 十  08 19:32:12 [0m[MAC]   [185.12]: processing PDU 0 (with length 149) of 1 total number of PDUs...
 十  08 19:32:12 [0m[MAC]   [UE] LCID 62, PDU length 149
 十  08 19:32:12 [0m[MAC]   [UE 0]Frame 185 Contention resolution identity: 0x18b385b57606 Terminating RA procedure
 十  08 19:32:12 [0m[32m[MAC]   [UE 0][185.12][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
 十  08 19:32:12 [0m[MAC]   [UE] LCID 0, PDU length 142
 十  08 19:32:12 [0m[MAC]   [UE] LCID 63, PDU length 3
 十  08 19:32:12 [0m[NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
 十  08 19:32:12 [0m[RLC]   Added srb 1 to UE 0
 十  08 19:32:12 [0m[MAC]   Applying CellGroupConfig from gNodeB
 十  08 19:32:12 [0m[NR_RRC]   State = NR_RRC_CONNECTED
 十  08 19:32:12 [0m[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
 十  08 19:32:12 [0m[NR_MAC]   ul config in slot 17
```

| DL_SCH_LCID_CON_RES_ID
MAC_LCID_LONG_BSR | 0x3E (62) | Contention resolution fixed subheader and MAC CE |
| --- | --- | --- |
| UL_SCH_LCID_CCCH1
MAC_LCID_CCCH | 0x0 (0) |  |
| UL_SCH_LCID_PADDING
MAC_LCID_PADDING | 0x3F (63) |  |

## **Potential issues discovered after tracing the code:**

TBS and RB size in OSC and OAI implementations do not match, so MSG4 information is not fully transmitted correctly. 

More detail in: [Compute TBS and PRB](Compute%20TBS%20and%20PRB%20121100983143819aa2b2c12155d157f8.md) 

[https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=BxmrTluOHl3hw8C2wvRX#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=BxmrTluOHl3hw8C2wvRX#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)

### Debug initially cared a lot about the PDU size being consistent, but later found that this did not cause any issues.

The length of the same message in the CU split logs is inconsistent, which may lead to `Invalid CCCH message` errors when the DU sends it to the UE for decoding.

```jsx
[NR_RRC]   RRCSetup Encoded 821 bits (103 bytes)
```

```jsx
[NR_RRC]   RRCSetup Encoded 1093 bits (137 bytes)
```

### Solution: Trace Tony’s OAI CU split Logs→ [Compare CU Logs](Compare%20CU%20Logs%201211009831438112a179dbddf976f6cf.md)

**Current Situation:**

The UE successfully received the MSG4 DCI but failed to decode MSG4, leading to an `Invalid CCCH message`. Tracing back, I found that the data is forwarded from the CU after DU High checks the RNTI, and initially, I suspected an issue with the CU's data segmentation. I asked Senior Sheryl to update the CU to the latest development version, but the problem persists.

Now, I suspect the issue might lie in the UL RRC message transfer payload that DU High sends to the CU after receiving MSG3. This suspicion arises because the payload for MSG3 between OAI VNF and OAI PNF is the same, but the DL RRC message transfer payload from the CU to DU High differs in length compared to OAI VNF + PNF.

From DU High’s perspective, receiving MSG3 involves the CRC indication and RX_DATA indication. Thus, to resolve this, we need to first verify how OSC DU processes and sends data to the CU (initial UL RRC Message Transfer) after receiving these indications. The issue likely traces back to the message sent by OSC DU, and by comparing the logs between OAI VNF + PNF, we can review the code surrounding the encoding and decoding processes to pinpoint the error.

### Note:

To summarize the current situation, we should first verify how the OSC DU processes and sends data to the CU (initial UL RRC Message Transfer) after receiving the CRC indication and `RX_Data` indication. This is because the UE decodes MSG4 and gets an `Invalid CCCH message`, which can be traced back to the PDU Payload sent by `TX_Data`. Further tracing leads to the DL RRC Message Transfer sent by the CU. Assuming there are no issues with the OAI CU, the problem lies with the message sent by the OSC DU (initial UL RRC Message Transfer). The solution could be to compare the logs of OAI VNF + PNF and review and trace the related code before and after encoding and decoding.

## Trace OSC pack PDU source code

<aside>
💡

In function: **macMuxPdu()**

path: mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/mac_mux.c

</aside>

### Calculate PDU size

| MAC_LCID_CRI | 7 Bytes |
| --- | --- |
| MAC_LCID_CCCH | 2 Bytes + dlData->pduInfo[pduIdx].pduLen |
| MAC_LCID_PADDING | 1 Bytes |

compare table

This is from CU to DU PDU LEN

|  | OAI | OSC |
| --- | --- | --- |
| dlData->pduInfo[pduIdx].pduLen | 137 | 103 |

### Pack MAC_LCID_CRI

```c
            case MAC_LCID_CRI:
               {
                  /* Packing fields into MAC PDU R/R/LCID */
                  /* 2 + 6 + 48 = 56 */
                  printf("[Start] bytePos = %d, bitPos = %d\n", bytePos, bitPos);
                  packBytes(macPdu, &bytePos, &bitPos, RBit, (RBitSize * 2));
                  packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
                  memcpy(&macPdu[bytePos], macCeData->macCe[pduIdx].macCeValue,\
                        MAX_CRI_SIZE);
                  bytePos += MAX_CRI_SIZE;
                  break;
               }
```

### Pack MAC_LCID_CCCH

```c
         case MAC_LCID_CCCH:
         case MAC_LCID_MIN ... MAC_LCID_MAX :
            {
               lenField = dlData->pduInfo[pduIdx].pduLen;
               printf("lenField = %d\n", lenField);
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
               /* 1 + 1 + 6 + 8 + lenField*8 = lenField*8 + 16 */
               packBytes(macPdu, &bytePos, &bitPos, RBit, RBitSize);
               packBytes(macPdu, &bytePos, &bitPos, FBit, FBitSize);
               packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
               packBytes(macPdu, &bytePos, &bitPos, lenField, lenFieldSize);
               memcpy(&macPdu[bytePos], dlData->pduInfo[pduIdx].dlPdu, lenField);
               bytePos += lenField;
               break;
            }
```

### Pack MAC_LCID_PADDING

```c
      /* padding remaining bytes */
      /* 2 + 6 = 8*/
      RBitSize = 2;
      lcid = MAC_LCID_PADDING;
      packBytes(macPdu, &bytePos, &bitPos, RBit, RBitSize);
      packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
      printf("[end]bytePos = %d, bitPos = %d\n\n", bytePos, bitPos);
```