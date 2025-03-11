# Issues:  Assertion is_nr_UL_slot() failed

Start Date: 2024/09/26
Summary: Investigation of an assertion failure in the UE scheduler due to incorrect UL slot configuration during MSG4 processing.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡

~~After revising the OSC config, the UE seems to receive MSG4 but encounters an assertion that needs to be fixed.~~

Due to UL config_request called at **wrong slot** interruption in UE, so UE encounters an assertion.

Attempt to Advance or improve the issue of MSG4 ACK/NACK delayed delivery to the DU.

</aside>

<aside>
💡

1. ~~Faster CU (Because the OAI CU and OSC DU are separate, it is slower than OAI CU + OAI DU.)~~
2. ~~Revise k1 in odu~~
3. ~~Speed up PNF execute CRC and RX_data indication~~
4. Revise UE send MSG4 ACK/NACK(PUCCH) slot 
    1.  ~~Revise TX_data PDU N_t1 relate parameter?~~
    2. Revise DL_DCI PDU N_t1 relate parameter See `harqFeedbackInd`
    
    → [Fix: Revise MSG4 DCI for UE send ACK by PUCCH](Fix%20Revise%20MSG4%20DCI%20for%20UE%20send%20ACK%20by%20PUCCH%201211009831438127ae57f72634801405.md) 
    
</aside>

## ERROR LOG

```jsx
 九  26 13:17:21 [0m[93m[MAC]   received TA command 31
 九  26 13:17:21 [0m[PHY]   RAR-Msg2 decoded
 九  26 13:17:21 [0m[32m[NR_MAC]   [RAPROC][184.19] RA-Msg3 transmitted
 九  26 13:17:21 [0m
 九  26 13:17:21 Assertion (is_nr_UL_slot(tdd_config, slot_tx, mac->frame_type) != 0) failed!
 九  26 13:17:21 In lockGet_ul_config() /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:79
 九  26 13:17:21 UL config_request called at wrong slot 2
 九  26 13:17:21 
 九  26 13:17:21 Exiting execution
 九  26 13:17:21 /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:79 lockGet_ul_config() Exiting OAI softmodem: _Assert_Exit_

```

![image.png](image%2051.png)

### Problem Breakdown:

1. **Assertion Failure**: The failure occurs at the point where the UE scheduler (`nr_ue_scheduler.c:79`) checks whether the current slot is a valid UL slot for the configuration (`lockGet_ul_config`). The error message suggests that the UL configuration is being called at an incorrect slot (`UL config_request called at wrong slot 2`).
2. **Process Context**:
    - **Msg4 Reception**: The UE has received MSG4, which is the contention resolution message sent by the gNB.
    - **ACK/NACK Response**: Upon receiving MSG4, the UE should transmit a HARQ-ACK/NACK on the PUCCH to acknowledge or negatively acknowledge the contention resolution process.
    - The assertion failure (`is_nr_UL_slot(tdd_config, slot_tx, mac->frame_type) != 0`) indicates that the system is checking if the current slot is valid for UL transmission (PUCCH HARQ-ACK in this case), and the check failed.
3. **PUCCH Timing Issue**:
    - The minimum time between the PDSCH (contention resolution message) and the corresponding PUCCH (HARQ-ACK) is determined by `NT,1`, which corresponds to the PDSCH processing time.
    - If the UE scheduler miscalculates this timing or if the PUCCH is attempted in an invalid slot, it could trigger the assertion failure, as seen in the logs.

![image.png](image%2052.png)

### Key Points to Investigate:

1. **Slot Allocation for PUCCH**:
    - Ensure that the UE is scheduling the PUCCH HARQ-ACK in a valid UL slot. This involves checking if the slot configuration (`tdd_config`) aligns with the uplink scheduling for this specific scenario.
2. **PDSCH Processing Time**:
    - Double-check if the time allocated for PDSCH processing and the subsequent HARQ-ACK on the PUCCH is correct, especially considering `NT,1` and the subcarrier spacing configuration.
3. **Potential TTI Overlap or Mismatch**:
    - There could be a mismatch between the time slots used for MSG4 reception and the slot scheduled for HARQ-ACK on PUCCH. This might lead to the UE trying to send an ACK/NACK at the wrong time.

```c
   for(ueIdx=0; ueIdx<MAX_NUM_UE; ueIdx++)
   {
      if(currDlSlot->dlInfo.dlMsgAlloc[ueIdx])
      {
         if((macCb.macCell[cellIdx]->macRaCb[ueIdx].macMsg4Status)&& (currDlSlot->dlInfo.dlMsgAlloc[ueIdx]->dlMsgPdschCfg))
         {
            fillMsg4Pdu(currTimingInfo.cellId, currDlSlot->dlInfo.dlMsgAlloc[ueIdx]);
         }
      }
   }
```

```jsx
(gdb) bt 
#0  schProcessMsg4Req (cell=0x7fffddd0e520, currTime=..., ueId=1 '\001', isRetxMsg4=false, msg4HqProc=0x7fffddd12498) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrsch/sch_common.c:1759
#1  0x0000555555b26678 in schFcfsScheduleSlot (cell=0x7fffddd0e520, slotInd=0x7fffd6606c10, schInst=0 '\000') at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrsch/sch_fcfs.c:1202
#2  0x0000555555b308d5 in SchProcSlotInd (pst=0x7fffa43ffb40, slotInd=0x7fffd6606c10) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrsch/sch_slot_ind.c:716
#3  0x0000555555b280fc in SchMessageRouter (pst=0x7fffa43ffb40, msg=0x7fffd6606c10) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrsch/sch_msg_router.c:290
#4  0x0000555555a8009e in sendSlotIndMacToSch (slotInd=0x7fffd6606c10) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/mac_slot_ind.c:385
#5  0x0000555555a8094d in OAI_OSC_nfapiMacSlotInd (pst=0x7fffa43ffbd0, slotInd=0x7fffd6606c10) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/mac_slot_ind.c:652
#6  0x0000555555a6dcfd in SCF_procSlotInd (UL_INFO=0x5555560dff80 <UL_INFO>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/lwr_mac_handle_phy.c:156
#7  0x0000555555b57132 in nfapi_nr_vnf_p7_start (config=0x5555566fdcb0) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/nfapi/open-nFAPI/vnf/src/vnf_p7_interface.c:363
#8  0x0000555555ad16de in vnf_nr_p7_start_thread (ptr=0x5555566fdcb0) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/nfapi/oai_integration/nfapi_vnf.c:1411
```

```jsx
(gdb) bt
#0  sendDlRlcBoInfoToSch (dlBoInfo=0x7fffa4dffc1c) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/mac_msg_hdl.c:66
#1  0x0000555555a793e2 in MacProcDlCcchInd (pst=0x7fffa4dffd30, dlCcchIndInfo=0x7ffff697e410)
    at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/mac_msg_hdl.c:699
#2  0x00005555559e3312 in unpackMacDlCcchInd (func=0x555555a78e64 <MacProcDlCcchInd>, pst=0x7fffa4dffd30, mBuf=0x7ffff697da10)
    at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/du_app_mac_inf.c:749
#3  0x0000555555a7ad11 in MacHdlDuappEvents (pst=0x7fffa4dffd30, mBuf=0x7ffff697da10)
    at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/mac_msg_router.c:131
#4  0x0000555555a7b15a in macActvTsk (pst=0x7fffa4dffd30, mBuf=0x7ffff697da10)
    at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/mac_msg_router.c:549
#5  0x0000555555a8f049 in mtTskHdlMsg (sTsk=0x5555566ca898 <osCp+11544>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:4982
#6  0x0000555555a8ec9d in mtTskHdlr (tskPtr=0x5555566ca898 <osCp+11544>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:4759
#7  0x00007ffff7094ac3 in start_thread (arg=<optimized out>) at ./nptl/pthread_create.c:442
#8  0x00007ffff7126850 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
```

## OSC MSG3 and MSG4 message flow

| **SFN.SLOT** | **VNF** | **PNF** | **UE** |
| --- | --- | --- | --- |
| 184.19 |  |  | RA-Msg3 transmitted |
| 185.5
(2 slot_ahead) |  | PACK CRC Finish
PACK RX_DATA Finish |  |
| 185.7 | Received crc_ind, get_queue crc indication
Received rx_data, get_queue rx indication |  |  |
| 185.8 | DU APP : UL CCCH Indication received
F1AP : Building RRC Setup Request |  |  |
| 185.9 | F1AP : Created APER encoded buffer for Initial UL RRC
SCTP : sending the message to CU
SCTP : Forwarding received message to duApp |  |  |
| 185.10 | F1AP : Received F1AP message buffer
DU_APP : DL RRC message transfer Recevied |  |  |
| 185.11 | DU APP : Building and Sending DL CCCH Ind to MAC
MAC : Handling DL CCCH IND | recv MSG4 DLTTI PDCCH
recv MSG4DLTTI PDSCH
(will use it in 185.15) |  |
| 185.12 | MSG4 scheduling for UE 1 |  |  |
| 185.13
(2 slot ahead) |  LWR_MAC: MSG4 sent… | use MSG4 DLTTI PDCCH
use MSG4DLTTI PDSCH |  |
| 185.15 |  |  |  |

## OAI MSG3 and MSG4 message flow

| **SFN.SLOT** | **VNF** | **PNF** | **UE** |
| --- | --- | --- | --- |
| 184.19 |  |  | RA-Msg3 transmitted |
| 185.5
(2 slot_ahead) |  | PACK CRC Finish
PACK RX_DATA Finish |  |
| 185.8 | Received crc_ind, get_queue crc indication
Received rx_data, get_queue rx indication

PUSCH with TC_RNTI 0x4348 received correctly
[NR_MAC]   [RAPROC] RA-Msg3 received (sdu_lenP 28)
Decoding CCCH: RNTI 4348, payload_size 6 | recv MSG4 DLTTI PDCCH
recv MSG4DLTTI PDSCH
(will use it in 185.10) |  |
| 185.9 | rrc_gNB_generate_RRCSetup for RNTI 4348 |  |  |
| 185.10 | Msg4 r_pucch 0 (CCEIndex 0, delta_PRI 0) | use MSG4 DLTTI PDCCH
use MSG4DLTTI PDSCH |  |
|  |  |  |  |

---

| K1 index | SFN/slot |
| --- | --- |
| 0 | 169.13 or 185.13 |
| 1 | 185.13 |
| 2 | 185.13 |
| 3 | 185.16 |
| 4 | 185.19 |
| 5 | 185.19 |