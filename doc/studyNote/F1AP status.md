# F1AP status

Start Date: 2024/09/05
Summary: The project focuses on implementing the F1AP procedure in a telecommunications context, involving user research, data analysis, and troubleshooting issues related to message transfers.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡

After OSC DU High get MSG3 (`RX_data` and `CRC` indication)
OSC starting F1AP procdure

</aside>

![image.png](image%2020.png)

<aside>
💡

Reference:
https://www.etsi.org/deliver/etsi_TS/138400_138499/138473/15.03.00_60/ts_138473v150300p.pdf

https://hackmd.io/@sheryl0625/H1fDsvgoC

</aside>

![image.png](image.png)

- **<CellGroupConfig>**
- **F1AP : Created APER encoded buffer for DuToCuRrcContainer**
- **<initiatingMessage>**
    - **InitialULRRCMessageTransfer**
    - **DLRRCMessageTransfer**

![image.png](image%2021.png)

![image.png](image%2022.png)

- **DU_APP : DL RRC message transfer Recevied**
- **DU APP : Building and Sending DL CCCH Ind to MAC**
- **DU_APP: Sending UE create request to RLC UL**
- **MAC: SCH UeConfigRsp for CRNTI[100] is success in MacProcSchUeCfgRsp()**

# Wireshark

| Time | Source | Destination | Protocol | Length | Info |
| --- | --- | --- | --- | --- | --- |
| 14.21644 | 192.168.130.81 | 192.168.130.83 | F1AP/NR RRC | 214 | `InitialULRRCMessageTransfer`, RRC Setup Request[Malformed Packet] |
| 14.216775 | 192.168.130.83 | 192.168.130.81 | F1AP/NR RRC | 218 | SACK (Ack=2, Arwnd=67108864) , `DLRRCMessageTransfer`, RRC Setup[Malformed Packet] |

|  | value |
| --- | --- |
| **Frame Number** | 4427 |
| **Frame Size** | 218 bytes on wire (1744 bits), 218 bytes captured (1744 bits) |
| **Ethernet Source** | 00:00:00_00:00:00 (00:00:00:00:00:00) |
| **Ethernet Destination** | 00:00:00_00:00:00 (00:00:00:00:00:00) |
| **IP Source** | 192.168.130.83 |
| **IP Destination** | 192.168.130.81 |
| **SCTP Source Port** | 38472 |
| **SCTP Destination Port** | 38472 |
| **F1AP Procedure** | DLRRCMessageTransfer |
| **F1AP ProtocolIEs** | 5 items |
| **gNB-CU-UE-F1AP-ID** | 100 |
| **gNB-DU-UE-F1AP-ID** | 1 |
| **SRBID** | 0 |
| **ExecuteDuplication** | true |
| **RRCContainer** | 2840031ae00580088057640e830f5003e11504a83dc60103d4c025901950011007800000003800086e1084001fc4648408090... |
| **RRC Protocol** | NR Radio Resource Control (RRC) |
| **DL-CCCH-Message** | c1 -> rrcSetup |
| **RRC Setup** |  |
| **RRC Transaction Identifier** | 1 |
| **Radio Bearer Config** |  |
| **SRB-ToAddMod List** | 1 item |
| **SRB-ToAddMod Identity** | 1 |
| **MasterCellGroup** | 5c00b001100aec81d061ea007c22a09507b8c0207a9804b2032a002200f00000000700010dc2108003f88c9081012031807304... |
| **RLC Bearer Config** | AM mode (uplink and downlink) |
| **UL Specific Parameters** | Priority: 1, Logical Channel Group: 0, Scheduling Request ID: 0 |
| **SchedulingRequestConfig** | 1 item |
| **PeriodicBSR Timer** | sf10 |
| **Retransmission BSR Timer** | sf320 |
| **TAG Config** | tag-Id: 0, Time Alignment Timer: infinity |
| **PHR Config** | phr-PeriodicTimer: infinity, phr-ProhibitTimer: sf0, multiplePHR: False |
| **Physical Cell Group Config** | p-NR-FR1: 0 dBm |
| **Downlink BWP To Release List** | BWP-Id: 6 (size constraint issue: value too big) |
| **BWP Inactivity Timer** | ms50 |
| **Uplink Config** | powerBoostPi2BPSK: True, powerBoostQPSK: False |
| **Encoding Error** | Possible encoding error: open type length less than dissected bits (Open type length 0, decoded 1) |
| **Malformed Packet Warning** | Possible encoding error in NR RRC |

|  | value |
| --- | --- |
| **Frame Number** | 4426 |
| **Frame Size** | 214 bytes on wire (1712 bits), 214 bytes captured (1712 bits) |
| **Ethernet Source** | 00:00:00_00:00:00 (00:00:00:00:00:00) |
| **Ethernet Destination** | 00:00:00_00:00:00 (00:00:00:00:00:00) |
| **IP Source** | 192.168.130.81 |
| **IP Destination** | 192.168.130.83 |
| **SCTP Source Port** | 38472 |
| **SCTP Destination Port** | 38472 |
| **F1AP Procedure** | InitialULRRCMessageTransfer |
| **F1AP ProtocolIEs** | 5 items |
| **gNB-DU-UE-F1AP-ID** | 1 |
| **NRCGI** |  |
| **PLMN Identity** | 00f110 (MCC: 001, MNC: 01) |
| **NR Cell Identity** | 0000000010 (decimal value: 1) |
| **C-RNTI** | 100 |
| **RRCContainer** | 128bb8a7cd66 |
| **RRC Protocol** | NR Radio Resource Control (RRC) |
| **UL-CCCH-Message** | c1 -> rrcSetupRequest |
| **RRC Setup Request** |  |
| **UE Identity** | Random Value: 28bb8a7cd6 (decimal value: 87472553579) |
| **Establishment Cause** | mo-Signalling |
| **DUtoCURRCContainer** | 5c00b001100aec81d061ea007c22a09507b8c0207a9804b2032a002200f00000000700010dc2108003f88c9081012031807304... |
| **Cell Group Config** |  |
| **RLC Bearer Config** | AM mode (uplink and downlink) |
| **UL Specific Parameters** | Priority: 1, Logical Channel Group: 0, Scheduling Request ID: 0 |
| **SchedulingRequestConfig** | 1 item |
| **PeriodicBSR Timer** | sf10 |
| **Retransmission BSR Timer** | sf320 |
| **TAG Config** | tag-Id: 0, Time Alignment Timer: infinity |
| **PHR Config** | phr-PeriodicTimer: infinity, phr-ProhibitTimer: sf0, multiplePHR: False |
| **Physical Cell Group Config** | p-NR-FR1: 0 dBm |
| **Downlink BWP To Release List** | BWP-Id: 6 |
| **BWP Inactivity Timer** | ms50 |
| **Uplink Config** | powerBoostPi2BPSK: True, powerBoostQPSK: False |
| **Encoding Error** | Possible encoding error: open type length less than dissected bits (Open type length 0, decoded 1) |
| **Malformed Packet Warning** | Possible encoding error in F1AP |

# Issues

If I attempt to set the RACH indication only once, it will not send an F1AP message.

Next, I need to verify whether the following original log is correct.

```
 九  05 21:39:24 INFO  ->  The current Timing Info : sfn : 184, slot : 8
 九  05 21:39:24 
 九  05 21:39:24 INFO  ->  The DL TTI Timing Info : sfn : 184, slot : 10
 九  05 21:39:24 
 九  05 21:39:24 [DEBUG] -->  dlTtiReq->dl_tti_request_body.nPDUs:0
 九  05 21:39:24 [DEBUG]	UL_INFO.rach_ind.number_of_pdus 1
 九  05 21:39:24 SCF_procRachInd
 九  05 21:39:24 
 九  05 21:39:24 INFO  -->  MAC : Received RACH indication from OAI PHY
 九  05 21:39:24 INFO  -->  SCH : Received Rach indication
 九  05 21:39:24 [SchProcRachInd] Adding UE Id to list of pending UEs to be scheduled
 九  05 21:39:24 
 九  05 21:39:24 [NTUST] have a p7 message.
 九  05 21:39:24 [NTUST] header.message_id:130
 九  05 21:39:24 INFO   --> VNF SFN/Slot 184.9 
```

| **unpackRxData** |
| --- |
| **case MAC_LCID_CCCH_48BIT : case MAC_LCID_CCCH :** |
| **macProcUlCcchInd** |
| **MacDuAppUlCcchInd** |
| **duHandleUlCcchInd** |
| **duProcUlCcchInd** |
| **BuildAndSendInitialRrcMsgTransfer** |
- After trace F1AP setup request relate source code, I insight the code flow is when OSC get RX_Data, then unpack rx_data function will trigger OSC Du send F1AP setup request.
- But if I revise source code to let OSC don’t repeat get the same RACH indication (because Layer 1 only send one time before 4-step Random access, but OSC DU log show it still unpack the same RACH indication for 23 times ), it can’t get RX_data indication!

# Current revise

- ~~set number to zero~~

```jsx
nfapiRachInd->number_of_pdus = 0;
```

- Else-if → if

```c
      /* If DL-Msg PDCCH/PDSCH is scheduled for a UE at this slot, fill 
       * specific interface structure to send to MAC */
      if(cell->schDlSlotInfo[dlSchedInfo.schSlotValue.dlMsgTime.slot]->dlMsgAlloc[ueIdx] != NULLP)
      {
```

- Remove **Process `Paging Msg`**

```c
   // schProcDlPageAlloc(cell, *slotInd, schInst);
```

- Remove **`pageAllocInfo` in `calcDlTtiReqPduCount`**
- Remove **`pageAllocInfo` in `calcTxDataReqPduCount`**

```c
   // if(dlSlot->pageAllocInfo)
   // {
   //    /* PDCCH and PDSCH PDU is filled */
   //    count += 2;
   // }
```

- Remove **`OAI_OSC_fillPageTxDataReq`**

```c
         // if(dlSlot->pageAllocInfo != NULLP)
         // {
         //    printf("\nDEBUG  -->  Page Alloc Info\n");
         //    TODO:OAI_OSC_fillPageTxDataReq done
         //    OAI_OSC_fillPageTxDataReq(txDataReq->pdu_list, pduIndex, dlSlot->pageAllocInfo);
         //    pduIndex++;
         //    txDataReq->Number_of_PDUs++;
         //    MAC_FREE(dlSlot->pageAllocInfo->pageDlSch.dlPagePdu, sizeof(dlSlot->pageAllocInfo->pageDlSch.dlPagePduLen));
         //    MAC_FREE(dlSlot->pageAllocInfo,sizeof(DlPageAlloc));
         // }
```

- Remove page message part in **`OAI_OSC_fillDlTtiReq`**

```c
/*
         //TODO: ADD Paging done
         if(currDlSlot->pageAllocInfo != NULLP)
         {
            // Filling DL Paging Alloc param
            if(numPduEncoded != nPdu)
            {
               rntiType = P_RNTI_TYPE;
               //TODO:OAI_OSC_fillPagePdcchPdu done
               OAI_OSC_fillPagePdcchPdu(&dlTtiReq->dl_tti_request_body.dl_tti_pdu_list[numPduEncoded], \
                                 currDlSlot->pageAllocInfo, &macCellCfg);
               numPduEncoded++;
               //TODO:OAI_OSC_fillPagePdschPdu done
               OAI_OSC_fillPagePdschPdu(&dlTtiReq->dl_tti_request_body.dl_tti_pdu_list[numPduEncoded], \
                                 currDlSlot->pageAllocInfo, pduIndex, &macCellCfg);
               dlTtiReq->dl_tti_request_body.PduIdx[pduIndex][0] = pduIndex;
               pduIndex++;
               numPduEncoded++;
            }
            DU_LOG("\033[1;34m");
            DU_LOG("\nDEBUG  -->  LWR_MAC: PAGE sent...");
            DU_LOG("\033[0m");
         }*/
```

![image.png](image%2023.png)

# Need to check

- What is Mux PDU for Msg4

```c
   /* Mux Pdu for Msg4 */
   buildAndSendMuxPdu(slotInd);
```

- Check if OAI sends the Page message. OSC should follow OAI's method; otherwise, OAI Layer 1 might behave unexpectedly.

- Page message struct in `OSC` use

```cpp
typedef struct dlPageAlloc
{
   uint16_t       cellId;
   SlotTimingInfo dlPageTime;
   uint8_t        ssbIdx;
   bool           shortMsgInd;
   uint8_t        shortMsg;
   BwpCfg         bwp;
   PageDlDci      pageDlDci;
   PageDlSch      pageDlSch;
}DlPageAlloc;
```