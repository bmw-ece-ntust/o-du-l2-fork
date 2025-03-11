# Trace:UL init transfer

Start Date: 2024/09/30
Summary: The project involves transferring initial UL RRC messages and analyzing their configuration and encoding for effective communication within the system.
Status: Done
Assign: 陳奕全
Finish Date: 2024/10/14
SUM: 🗓️ Days Spent to Complete: 14

# Status

![image.png](image.png)

| Item | Status |
| --- | --- |
| DU Initializing | ✅ |
| F1 setup request | ✅ |
| F1 Setup response | ✅ |
| P5 config.request | ✅ |
| P5 config.response | ✅ |
| DU configuration Update | ✅ |
| DU configurationUpdate ACK | ✅ |
| P5 start.request | ✅ |
| P5 start.response | ✅ |
| MIB | ✅ |
| SIB1 | ✅ |
| MSG1 (Preamble) | ✅ |
| MSG2 (RAR) | ✅ |
| MSG3 (RRC request) | ✅ |
| F1AP: Initial UL RRC transfer transfer | ✅ |
| F1AP: DL RRC message transfer | ✅ |
| MSG4 (RRC response) | ⌛ |
| UL RRC transfer | ❌ |
| F1AP: Authentication request | ❌ |
| DL RRC transfer | ❌ |
|  |  |

![image.png](image%2035.png)

![image.png](image%2036.png)

![image.png](image%2037.png)

## What is difference between with OAI and OSC+OAI

|  | OAI CU + OAI DU | OAI CU + OSC DU |
| --- | --- | --- |
| **RNTI** | **e088** | **0064** |
| **payload_size** | 6 | 6 |
| **RRCSetup Encoded** | **1093 bits (137 bytes)** | **821 bits (103 bytes)** |
|  |  | duToCuRrcContainer->size = encBufSize +33;

RRCSetup Encoded 1093 bits (137 bytes) |

OAI

![image.png](image%2038.png)

OSC

![image.png](image%2039.png)

![image.png](image%2040.png)

```c
uint8_t **BuildAndSendInitialRrcMsgTransfer**(uint32_t gnbDuUeF1apId, uint16_t crnti,uint16_t rrcContSize, uint8_t *rrcContainer)

{
```

### Fill MSG4 DL data

![image.png](image%2041.png)

**duProcUlCcchInd**

```c
   DU_LOG("\nERROR  --> UL_RRC ulCcchIndInfo->ulCcchMsgLen:%d\n", ulCcchIndInfo->ulCcchMsgLen);

   ret = (BuildAndSendInitialRrcMsgTransfer(gnbDuUeF1apId, ulCcchIndInfo->crnti, ulCcchIndInfo->ulCcchMsgLen,
	    ulCcchIndInfo->ulCcchMsg));
```

```
 九  30 13:13:13 [0m<DL-CCCH-Message>
 九  30 13:13:13     <message>
 九  30 13:13:13         <c1>
 九  30 13:13:13             <rrcSetup>
 九  30 13:13:13                 <rrc-TransactionIdentifier>1</rrc-TransactionIdentifier>
 九  30 13:13:13                 <criticalExtensions>
 九  30 13:13:13                     <rrcSetup>
 九  30 13:13:13                         <radioBearerConfig>
 九  30 13:13:13                             <srb-ToAddModList>
 九  30 13:13:13                                 <SRB-ToAddMod>
 九  30 13:13:13                                     <srb-Identity>1</srb-Identity>
 九  30 13:13:13                                 </SRB-ToAddMod>
 九  30 13:13:13                             </srb-ToAddModList>
 九  30 13:13:13                         </radioBearerConfig>
 九  30 13:13:13                         <masterCellGroup>
 九  30 13:13:13                             5C 00 B0 01 11 7A EC 70 10 61 F0 00 7C 02 04 68 
 九  30 13:13:13                             3C 08 00 04 12 09 81 95 00 81 FF FF 00 00 00 01 
 九  30 13:13:13                             00 00 37 14 42 00 00 80 16 50 00 04 82 00 00 44 
 九  30 13:13:13                             09 34 0D 54 93 50 00 04 00 80 80 01 00 1A 02 00 
 九  30 13:13:13                             27 6C 92 30 1D C0 76 78 9A BC D0 00 00 29 A1 00 
 九  30 13:13:13                             20 00 25 80 C2 0C 02 C9 C1 82 1C 00 31 28 1C 00 
 九  30 13:13:13                             00 20 5E F4 01 00 01 00 00 06 40 01 40 03 2A 0A 
 九  30 13:13:13                             00 C4 40 15 00 00 00 00 01 42 00 80 00 14 50 80 
 九  30 13:13:13                             80 02 C6 00
 九  30 13:13:13                         </masterCellGroup>
 九  30 13:13:13                     </rrcSetup>
 九  30 13:13:13                 </criticalExtensions>
 九  30 13:13:13             </rrcSetup>
 九  30 13:13:13         </c1>
 九  30 13:13:13     </message>
 九  30 13:13:13 </DL-CCCH-Message>
```

```
 九  30 16:07:26     <initiatingMessage>
 九  30 16:07:26         <procedureCode>11</procedureCode>
 九  30 16:07:26         <criticality><ignore/></criticality>
 九  30 16:07:26         <value>
 九  30 16:07:26             <InitialULRRCMessageTransfer>
 九  30 16:07:26                 <protocolIEs>
 九  30 16:07:26                     <InitialULRRCMessageTransferIEs>
 九  30 16:07:26                         <id>41</id>
 九  30 16:07:26                         <criticality><reject/></criticality>
 九  30 16:07:26                         <value>
 九  30 16:07:26                             <GNB-DU-UE-F1AP-ID>1</GNB-DU-UE-F1AP-ID>
 九  30 16:07:26                         </value>
 九  30 16:07:26                     </InitialULRRCMessageTransferIEs>
 九  30 16:07:26                     <InitialULRRCMessageTransferIEs>
 九  30 16:07:26                         <id>111</id>
 九  30 16:07:26                         <criticality><reject/></criticality>
 九  30 16:07:26                         <value>
 九  30 16:07:26                             <NRCGI>
 九  30 16:07:26                                 <pLMN-Identity>00 F1 10</pLMN-Identity>
 九  30 16:07:26                                 <nRCellIdentity>
 九  30 16:07:26                                     000000000000000000000000000000000001
 九  30 16:07:26                                 </nRCellIdentity>
 九  30 16:07:26                             </NRCGI>
 九  30 16:07:26                         </value>
 九  30 16:07:26                     </InitialULRRCMessageTransferIEs>
 九  30 16:07:26                     <InitialULRRCMessageTransferIEs>
 九  30 16:07:26                         <id>95</id>
 九  30 16:07:26                         <criticality><reject/></criticality>
 九  30 16:07:26                         <value>
 九  30 16:07:26                             <C-RNTI>100</C-RNTI>
 九  30 16:07:26                         </value>
 九  30 16:07:26                     </InitialULRRCMessageTransferIEs>
 九  30 16:07:26                     <InitialULRRCMessageTransferIEs>
 九  30 16:07:26                         <id>50</id>
 九  30 16:07:26                         <criticality><reject/></criticality>
 九  30 16:07:26                         <value>
 九  30 16:07:26                             <RRCContainer>1A 40 A6 FE DE 26</RRCContainer>
 九  30 16:07:26                         </value>
 九  30 16:07:26                     </InitialULRRCMessageTransferIEs>
 九  30 16:07:26                     <InitialULRRCMessageTransferIEs>
 九  30 16:07:26                         <id>128</id>
 九  30 16:07:26                         <criticality><reject/></criticality>
 九  30 16:07:26                         <value>
 九  30 16:07:26                             <DUtoCURRCContainer>
 九  30 16:07:26                                 5C 00 B0 01 10 0A EC 81 D0 61 EA 00 7C 22 A0 95 
 九  30 16:07:26                                 07 B8 C0 20 7A 98 04 B2 03 2A 00 22 00 F0 00 00 
 九  30 16:07:26                                 00 07 00 01 0D C2 10 80 03 F8 8C 90 81 01 20 31 
 九  30 16:07:26                                 80 73 04 E4 00 4C D5 50 20 20 02 00 02 00 20 00 
 九  30 16:07:26                                 22 24 4A A1 10 00 32 42 00 01 63 10 A6 31 4E 50 
 九  30 16:07:26                                 20 20 08 04 00 08 00 00 00 00 00 00 01 80 50 07 
 九  30 16:07:26                                 02 2A 00
 九  30 16:07:26                             </DUtoCURRCContainer>
 九  30 16:07:26                         </value>
 九  30 16:07:26                     </InitialULRRCMessageTransferIEs>
 九  30 16:07:26                 </protocolIEs>
 九  30 16:07:26             </InitialULRRCMessageTransfer>
 九  30 16:07:26         </value>
 九  30 16:07:26     </initiatingMessage>
 九  30 16:07:26 </F1AP-PDU>
 九  30 16:07:26 
```

# Buffer recoder

OSC:DUtoCURRCContainer

```c
#original
5C 00 B0 01 10 0A EC 81 D0 61 EA 00 7C 22 A0 95 
07 B8 C0 20 7A 98 04 B2 03 2A 00 22 00 F0 00 00 
00 07 00 01 0D C2 10 80 03 F8 8C 90 81 01 20 31 
80 73 04 E4 00 4C D5 50 20 20 02 00 02 00 20 00 
22 24 4A A1 10 00 32 42 00 01 63 10 A6 31 4E 50 
20 20 08 04 00 08 00 00 00 00 00 00 01 80 50 07 
02 2A 00
```

```c
#Ming revised S1b1
5C 00 B0 01 10 0A EC 81 D0 61 EA 00 7C 22 A0 95 
07 B8 C0 20 7A 98 04 B2 03 2A 00 20 00 F0 00 00 
00 07 00 01 0D C1 00 80 00 02 04 90 81 01 20 31 
80 73 04 E4 00 4C D5 50 20 20 02 00 02 00 20 00 
22 24 4A A1 10 00 32 42 00 01 63 10 A6 31 4E 50 
20 20 08 04 00 08 00 00 00 00 00 00 01 80 50 07 
02 2A 00
```

```c
#elarge
5C 00 B0 01 10 0A EC 81 D0 61 EA 00 7C 22 A0 95 
07 B8 C0 20 7A 98 04 B2 03 2A 00 20 00 F0 00 00 
00 07 00 01 0D C1 00 80 00 02 04 90 81 01 20 31 
80 73 04 E4 00 4C D5 50 20 20 02 00 02 00 20 00 
22 24 4A A1 10 00 32 42 00 01 63 10 A6 31 4E 50 
20 20 08 04 00 08 00 00 00 00 00 00 01 80 50 07 
02 2A 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00
```

```c
#Hardcode
5C 00 B0 01 11 7A EC 70 10 61 F0 00 7C 02 04 68 
3C 08 00 04 12 09 81 95 00 81 FF FF 00 00 00 01 
00 00 37 14 42 00 00 80 16 50 00 04 82 00 00 44 
09 34 0D 54 93 50 00 04 00 80 80 01 00 1A 02 00 
27 6C 92 30 1D C0 76 78 9A BC D0 00 00 29 A1 00 
20 00 25 80 C2 0C 02 C9 C1 82 1C 00 31 28 1C 00 
00 20 5E F4 01 00 01 00 00 06 40 01 40 03 2A 0A 
00 C4 40 15 00 00 00 00 01 42 00 80 00 14 50 80 
80 02 C6 00
```

```c
5c	0	ffffffb0	1	10	a	ffffffec	ffffff81	ffffffd0	61	ffffffea	0	7c	22	ffffffa0	ffffff95	7	ffffffb8	ffffffc0	20	7a	ffffff98	4	ffffffb2	3	2a	0	20	0	fffffff0	0	0	0	7	0	1	d	ffffffc1	0	ffffff80	0	2	4	ffffff90	ffffff81	1	20	31	ffffff80	73	4	ffffffe4	0	4c	ffffffd5	50	20	20	2	0	2	0	20	0	22	24	4a	ffffffa1	10	0	32	42	0	1	63	10	ffffffa6	31	4e	50	20	20	8	4	0	8	0	0	0	0	0	0	1	ffffff80	50	7	2	2a	0
```

OAI

```c
5C 00 B0 01 11 7A EC 70 10 61 F0 00 7C 02 04 68 
3C 08 00 04 12 09 81 95 00 81 FF FF 00 00 00 01 
00 00 37 14 42 00 00 80 16 50 00 04 82 00 00 44 
09 34 0D 54 93 50 00 04 00 80 80 01 00 1A 02 00 
27 6C 92 30 1D C0 76 78 9A BC D0 00 00 29 A1 00 
20 00 25 80 C2 0C 02 C9 C1 82 1C 00 31 28 1C 00 
00 20 5E F4 01 00 01 00 00 06 40 01 40 03 2A 0A 
00 C4 40 15 00 00 00 00 01 42 00 80 00 14 50 80 
80 02 C6 00
```

---

OSC: DL RRCContainer

```c
#origin
28 40 03 1A E0 05 80 08 80 57 64 0E 83 0F 50 03 
E1 15 04 A8 3D C6 01 03 D4 C0 25 90 19 50 01 10 
07 80 00 00 00 38 00 08 6E 10 84 00 1F C4 64 84 
08 09 01 8C 03 98 27 20 02 66 AA 81 01 00 10 00 
10 01 00 01 11 22 55 08 80 01 92 10 00 0B 18 85 
31 8A 72 81 01 00 40 20 00 40 00 00 00 00 00 00 
0C 02 80 38 11 50 00
```

```c
#Ming revised SIB1
28 40 03 1A E0 05 80 08 80 57 64 0E 83 0F 50 03 
E1 15 04 A8 3D C6 01 03 D4 C0 25 90 19 50 01 00 
07 80 00 00 00 38 00 08 6E 08 04 00 00 10 24 84 
08 09 01 8C 03 98 27 20 02 66 AA 81 01 00 10 00 
10 01 00 01 11 22 55 08 80 01 92 10 00 0B 18 85 
31 8A 72 81 01 00 40 20 00 40 00 00 00 00 00 00 
0C 02 80 38 11 50 00
```

```c
#enlarge
28 40 04 04 22 E0 05 80 08 80 57 64 0E 83 0F 50 
03 E1 15 04 A8 3D C6 01 03 D4 C0 25 90 19 50 01 
00 07 80 00 00 00 38 00 08 6E 08 04 00 00 10 24 
84 08 09 01 8C 03 98 27 20 02 66 AA 81 01 00 10 
00 10 01 00 01 11 22 55 08 80 01 92 10 00 0B 18 
85 31 8A 72 81 01 00 40 20 00 40 00 00 00 00 00 
00 0C 02 80 38 11 50 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00
```

```c
#Hardcode
28 40 04 04 22 E0 05 80 08 8B D7 63 80 83 0F 80 
03 E0 10 23 41 E0 40 00 20 90 4C 0C A8 04 0F FF 
F8 00 00 00 08 00 01 B8 A2 10 00 04 00 B2 80 00 
24 10 00 02 20 49 A0 6A A4 9A 80 00 20 04 04 00 
08 00 D0 10 01 3B 64 91 80 EE 03 B3 C4 D5 E6 80 
00 01 4D 08 01 00 01 2C 06 10 60 16 4E 0C 10 E0 
01 89 40 E0 00 01 02 F7 A0 08 00 08 00 00 32 00 
0A 00 19 50 50 06 22 00 A8 00 00 00 00 0A 10 04 
00 00 A2 84 04 00 16 30 00
```

OAI

https://www.marben-products.com/cgi-bin/asn1tools/free-online-asn1-decoder.pl

[NR_RRC]   RRCSetup Encoded 1093 bits (137 bytes)

VS

RRCSetup Encoded 821 bits (103 bytes)

```
 九  30 16:55:26 [0m[1;31m[SCTP]   Received data from peer with unsollicited PPID 0, expecting 62
 九  30 16:55:26 [0m[34m[F1AP]   CU Task Received SCTP_DATA_IND for instance 0: sending SCTP message via assoc_id 0
 九  30 16:55:26 [0m[34m[F1AP]   Calling handler with instance 0
 九  30 16:55:26 [0m[34m[F1AP]   CU_handle_INITIAL_UL_RRC_MESSAGE_TRANSFER
 九  30 16:55:26 [0m[NR_RRC]   Decoding CCCH: RNTI 0064, payload_size 6
 九  30 16:55:26 [0m[NR_RRC]   Created new UE context: CU UE ID 1 DU UE ID 1 (rnti: 0064, random ue id 1c1fcd8d0b000000)
 九  30 16:55:26 [0m[RRC]   activate SRB 1 of UE 1
 九  30 16:55:26 [0m[NR_RRC]   rrc_gNB_generate_RRCSetup for RNTI 0064
 九  30 16:55:26 [0m[NR_RRC]   RRCSetup Encoded 821 bits (103 bytes)
 九  30 16:55:26 [0m[34m[F1AP]   CU Task Received F1AP_DL_RRC_MESSAGE for instance 0: sending SCTP message via assoc_id 5491
 九  30 16:55:26 [0m[34m[F1AP]   CU send DL_RRC_MESSAGE_TRANSFER 
```

```
 九  30 16:52:26 [0m1727686346.551148 [RLC]   Activated srb0 for UE 20075
 九  30 16:52:26 [0m1727686346.551154 [RLC]   Added srb 1 to UE 20075
 九  30 16:52:26 [0m1727686346.551231 [NR_MAC]   Activating scheduling RA-Msg4 for TC_RNTI 0x4e6b (state WAIT_Msg3)
 九  30 16:52:26 [0m[93m1727686346.551234 [NR_MAC]   Unexpected ULSCH HARQ PID 0 (have -1) for RNTI 0x4e6b (ignore this warning for RA)
 九  30 16:52:26 [0m1727686346.551244 [MAC]   VNF SFN/Slot 185.9 
 九  30 16:52:26 [0m1727686346.551241 [NR_RRC]   Decoding CCCH: RNTI 4e6b, payload_size 6
 九  30 16:52:26 [0m1727686346.551491 [NR_RRC]   Created new UE context: CU UE ID 1 DU UE ID 20075 (rnti: 4e6b, random ue id 32c0bff357000000)
 九  30 16:52:26 [0m1727686346.551494 [RRC]   activate SRB 1 of UE 1
 九  30 16:52:26 [0m1727686346.551498 [NR_RRC]   rrc_gNB_generate_RRCSetup for RNTI 4e6b
  九  30 16:52:26 1727686346.551524 [NR_RRC]   RRCSetup Encoded 1093 bits (137 bytes)

```

odu how to generate the Initial UL RRC message transfer

```c
 *    Function : **BuildAndSendInitialRrcMsgTransfer** 
 *
 *    Functionality: Constructs the Initial UL RRC Message Transfer and sends
 *                   it to the CU through SCTP.
 *
```

**fillMsg4DlData**

```c
	 macCb.macCell[cellIdx]->macRaCb[ueIdx].msg4PduLen = dlCcchIndInfo->dlCcchMsgLen;
```

rrcMsgSize

---

After tracing I think we need to revise `unpackRxData` in odu, because of all of RX and CRC configurations are match as OAI, rrcMsgSize still difference.

```
uint8_t unpackRxData(uint16_t cellId, SlotTimingInfo slotInfo, RxDataIndPdu *rxDataIndPdu)
{
```

<aside>
💡

OAI pack pdu code is :

```
static int nr_process_mac_pdu(instance_t module_idP,

prepare_initial_ul_rrc_message

**mac_rlc_data_ind**
```

</aside>

```c
void mac_rlc_data_ind(const module_id_t  module_idP,
                      const uint16_t ue_id,
                      const eNB_index_t eNB_index,
                      const frame_t frameP,
                      const eNB_flag_t enb_flagP,
                      const MBMS_flag_t MBMS_flagP,
                      const logical_chan_id_t channel_idP,
                      char *buffer_pP,
                      const tb_size_t tb_sizeP,
                      num_tb_t num_tbP,
                      crc_t *crcs_pP)
{
  if (module_idP != 0 || eNB_index != 0 || /*enb_flagP != 1 ||*/ MBMS_flagP != 0) {
    LOG_E(RLC, "%s:%d:%s: fatal\n", __FILE__, __LINE__, __FUNCTION__);
    exit(1);
  }

  if (enb_flagP)
    T(T_ENB_RLC_MAC_UL, T_INT(module_idP), T_INT(ue_id),
      T_INT(channel_idP), T_INT(tb_sizeP));

  nr_rlc_manager_lock(nr_rlc_ue_manager);
  nr_rlc_ue_t *ue = nr_rlc_manager_get_ue(nr_rlc_ue_manager, ue_id);

  if(ue == NULL)
    LOG_I(RLC, "RLC instance for the given UE was not found \n");

  nr_rlc_entity_t *rb = get_rlc_entity_from_lcid(ue, channel_idP);

  if (rb != NULL) {
    LOG_D(RLC, "RB found! (channel ID %d) \n", channel_idP);
    rb->set_time(rb, nr_rlc_current_time);
    rb->recv_pdu(rb, buffer_pP, tb_sizeP);
  } else {
    LOG_E(RLC, "Fatal: no RB found (channel ID %d UE ID %d)\n", channel_idP, ue_id);
    // exit(1);
  }

  nr_rlc_manager_unlock(nr_rlc_ue_manager);
}

```

```c
      MAC_ALLOC(pdu->pduData,pdu->pduLength);
      memcpy(pdu->pduData, **nfapiRxDataInd**->pdu_list[pduIdx].pdu, pdu->pduLength);
```

1. `SCF_procRxDataInd` memory copy pduData from nFAPI RX pdu

![{91DB3A0D-AA9F-4920-BA31-A4F988C25545}.png](91DB3A0D-AA9F-4920-BA31-A4F988C25545.png)

1. `OAI_OSC_nfapiMacRxDataInd` invoke unpackRxData to unpack pduData

![{BEA6CBE7-D293-4503-8970-A9A2A596DC65}.png](BEA6CBE7-D293-4503-8970-A9A2A596DC65.png)

3. `rxDataPdu = rxDataIndPdu->pduData;` `unpackRxData`  memory copy rxDataPdu and invoke `macProcUlCcchInd`

![{3E97670A-9F5E-4DF2-973A-47CDBD3B30F8}.png](3E97670A-9F5E-4DF2-973A-47CDBD3B30F8.png)

4.  `rxDataPdu`is `rrcContainer`

![{1B50D2B7-91F6-471F-847A-D9D4EEBBAA80}.png](1B50D2B7-91F6-471F-847A-D9D4EEBBAA80.png)

[Compare:RX_data content](Compare%20RX_data%20content%20121100983143810885dde61db26108b2.md)

---

# BuildAndSendInitialRrcMsgTransfer

![{327D9C2C-ECE4-4472-80B6-EC4978B890CB}.png](327D9C2C-ECE4-4472-80B6-EC4978B890CB.png)

```c
      printf("=============RRCContainer===========\n");
      printf("RRCContainer size %d\n", rrcContSize);
      printf("====================================\n");
```

```
 十  03 12:56:34 =============RRCContainer===========
 十  03 12:56:34 RRCContainer size 6
 十  03 12:56:34 ====================================
```

<aside>
👀

I think the major issue in `DUtoCURRCContainer`

- **BuildCellGroupConfigRrc**
    - BuildRlcBearerToAddModList
        - **BuildRlcConfig**
        - **BuildMacLCConfig**
        - **BuildRlcConfig**
            - **BuildRlcConfigAm**
            - **BuildRlcConfigUmBiDir**
            - **BuildRlcConfigUmUniDirUl**
            - **BuildRlcConfigUmUniDirDl**
        - **BuildMacLCConfig**
    - BuildMacCellGrpCfg
        - **BuildSchedulingReqConfig**
        - **BuildBsrConfig**
        - **BuildTagConfig**
        - **BuildPhrConfig**
    - BuildPhyCellGrpCfg
    - BuildSpCellCfg
        - **BuildRecfgWithSync**
        - **BuildSpCellCfgDed**
            - **BuildInitialDlBWP**
                - **BuildBWPDlDedPdcchCfg**
                    - **BuildControlRSetToAddModList**
                    - **BuildSearchSpcToAddModList**
                - **BuildBWPDlDedPdschCfg**
                    - **BuildDMRSDLPdschMapTypeA**
                    - **BuildPdschTimeDomAllocList**
                    - **BuildPdschPrbBundlingType**
            - **BuildDlBwpToAddModList**
            - **BuildUlCfg**
                - **BuildInitialUlBWP**
                    - **BuildBWPUlDedPucchCfg**
                        - **BuildPucchRsrcSetAddModList**
                        - **BuildPucchRsrcAddModList**
                        - **BuildPucchFormat**
                    - **BuildBWPUlDedPuschCfg**
                        - **BuildDMRSULPuschMapTypeA**
                        - **BuildPuschTimeDomAllocList**
                    - **BuildBWPUlDedSrsCfg**
                        - **BuildSrsRsrcSetAddModList**
                        - **BuildSrsRsrcAddModList**
                - **BuildPuschSrvCellCfg**
            - **BuildPdschSrvCellCfg**
            
</aside>

<aside>
💡

If I modify `CellGroupConfigRrc encBufSize`, the RRCSetup encoded bits will change. This demonstrates that we need to modify `BuildCellGroupConfigRrc` in the ODU to match OAI.

</aside>

## ~~OAI~~

**~~rrc_gNB_process_initial_ul_rrc_message~~**

**~~send_initial_ul_rrc_message~~**

<aside>
💡

I used hard-code in **BuildCellGroupConfigRrc buffer, but msg4 still can’t decode in UE**

</aside>

![image.png](image%2042.png)

```c
      DU_LOG("\nDEBUG   -->  F1AP : Before uper_encode encBufSize:%d\n",encBufSize);
      encRetVal = uper_encode(&asn_DEF_CellGroupConfig, 0, &cellGrpCfg, PrepFinalEncBuf, encBuf);
      DU_LOG("\nDEBUG   -->  F1AP : After uper_encode encBufSize:%d\n",encBufSize);
```

![image.png](image%2043.png)

## Original osc table

| **Parameter** | **Value** |
| --- | --- |
| ULTTI nPDUs | 0 |
| cellGroupId | 0 |
| logicalChannelIdentity | 1 |
| srb-Identity | 1 |
| sn-FieldLength (UL-AM-RLC) | size12 |
| t-PollRetransmit (UL-AM-RLC) | ms45 |
| pollPDU (UL-AM-RLC) | p4 |
| pollByte (UL-AM-RLC) | infinity |
| maxRetxThreshold (UL-AM-RLC) | t8 |
| sn-FieldLength (DL-AM-RLC) | size12 |
| t-Reassembly (DL-AM-RLC) | ms40 |
| t-StatusProhibit (DL-AM-RLC) | ms35 |
| priority (UL-SpecificParameters) | 1 |
| prioritisedBitRate | infinity |
| bucketSizeDuration | ms150 |
| logicalChannelGroup | 0 |
| schedulingRequestID | 0 |
| logicalChannelSR-Mask | false |
| logicalChannelSR-DelayTimerApplied | false |
| schedulingRequestId | 0 |
| sr-ProhibitTimer | ms32 |
| sr-TransMax | n16 |
| periodicBSR-Timer | sf10 |
| retxBSR-Timer | precoderGranularitysf320 |
| tag-Id | 0 |
| timeAlignmentTimer | infinity |
| phr-PeriodicTimer | infinity |
| phr-ProhibitTimer | sf0 |
| phr-Tx-PowerFactorChange | infinity |
| multiplePHR | false |
| dummy | false |
| phr-Type2OtherCell | false |
| phr-ModeOtherCG | real |
| skipUplinkTxDynamic | false |
| p-NR-FR1 | 0 |
| pdsch-HARQ-ACK-Codebook | dynamic |
| servCellIndex | 0 |
| rlmInSyncOutOfSyncThreshold | n1 |
| controlResourceSetId | 0 |
| frequencyDomainResources | 000000000111100000000000000000000000000000000 |
| duration | 2 |
| precoderGranularity | allContiguousRBs |
| pdcch-DMRS-ScramblingID | 1 |
| searchSpaceId | 1 |
| controlResourceSetId | 0 |
| monitoringSymbolsWithinSlot | 10000000000000 |
| nrofCandidates aggregationLevel1 | n0 |
| nrofCandidates aggregationLevel2 | n0 |
| nrofCandidates aggregationLevel4 | n1 |
| nrofCandidates aggregationLevel8 | n0 |
| nrofCandidates aggregationLevel16 | n0 |
| dci-Formats | formats0-0-And-1-0 |
| dmrs-AdditionalPosition | <pos0/> |
| resourceAllocation | <resourceAllocationType1/> |
| k0 | 0, 1 |
| startSymbolAndLength | 57 |
| rbg-Size | <config1/> |
| maxNrofCodeWordsScheduledByDCI | <n1/> |
| dataScramblingIdentityPUSCH | 1 |
| dmrs-AdditionalPosition | <pos0/> |
| resourceAllocation | <resourceAllocationType1/> |
| k2 | 4, 6 |
| startSymbolAndLength | 41 |
| transformPrecoder | <disabled/> |
| srs-ResourceSetId | 1 |
| aperiodicSRS-ResourceTrigger | 1 |
| nrofSRS-Ports | <port1/> |
| freqDomainPosition | 0 |
| resourceType | <aperiodic/> |
| maxMIMO-Layers | 1 |
| processingType2Enabled | <false/> |
| nrofHARQ-ProcessesForPDSCH | <n16/> |

<aside>
💡

There many parameter defined in `l2/src/du_app/du_cfg.h`

</aside>