# Issues: OSC don’t send UL_TTI

Start Date: 2024/09/10
Summary: Investigating and resolving issues with OSC's transmission of UL_TTI and RACH indications in a high-level design context.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡

When I want to limit **`SCF_procRachInd`** to only run once, OSC will stop sending **`UL_TTI`** to receive **MSG3** (`RX_Data`, `CRC` indication). 
Fixed→ [Issue: Scheduling UE with the wrong ID](Issue%20Scheduling%20UE%20with%20the%20wrong%20ID%2012110098314381e7b09bfc80f995542c.md) 

</aside>

- This problem like [Fix OSC can’t get MSG3](Fix%20OSC%20can%E2%80%99t%20get%20MSG3%2012110098314381029eefecd420ad24ae.md), [Study MSG3](Study%20MSG3%201211009831438133ab92d50e48cf5bf3.md)

![Untitled](Untitled%2029.png)

# Main

After my revision, OSC no longer calls this function.

```c
SchPuschInfo* schAllocMsg3Pusch(Inst schInst, uint16_t crnti, uint8_t k2Index, SlotTimingInfo msg3SlotTime, SchUlHqProcCb* msg3HqProc, bool isRetx)
```

In summary, the main issue with OSC DU High lies in the design where all downlink data follows DL_TTI. It only checks if there are other uplink data to transmit (UL_TTI, UL_DCI) when there is a DL_TTI PDU scheduled for a given slot by the scheduler. However, for cases like CRC and RX_DATA indication, only UL_TTI is needed, and it doesn't require simultaneous transmission with DL_TTI. This results in a problem: when UL_TTI is expected to be sent, there is no DL_TTI PDU, so UL_TTI cannot be transmitted as scheduled. Therefore, the MSG3 (RX_Data, CRC indication) cannot be received successfully.

**Solution**: For every slot, check if there are DL and UL PDUs, then calculate the quantity and fill them before transmission.

**Issue encountered**: When OSC DU High is preparing to receive PRACH, it seems that the originally designed UL_TTI PDU gets filled one slot earlier, waiting to be transmitted together with DL_TTI. As a result, two consecutive UL_TTI messages for PRACH are sent, causing a timing mismatch. A new solution needs to be found.

**Solution**: Set a condition to delay sending UL_TTI until after SIB1 is transmitted (this does not resolve the issue, as RACH succeeds only on the second attempt).

- If no conditions are set and UL_TTI is sent alone when there is no DL_TTI, the following issue arises: RACH Indication is received twice across two consecutive slots.

| **UE** | Sent once at 183/19 and next at 195/19, continuously sending RA but did not receive RAR and did not send MSG3. |
| --- | --- |
| **PNF** | Due to the VNF’s UL_TTI, UL_TTI was sent twice at consecutive slots 183/18 and 183/19 with the same data, and RX_Data was also received. |
| **VNF** | Sent UL_TTI twice in consecutive slots to PNF, received RACH twice, and sent RAR once. It also sent UL_TTI to request RX_Data and determined there were two UEs. After RA, the allocations were assigned to UE ID: 2. |

```c
[DEBUG] RACH Indication at [183, 18] with 1 PDUs
...
[DEBUG] RACH Indication at [183, 19] with 1 PDUs
```

**Current main issue identified**: The problem is caused by putting RACH into the queue twice and getting from the queue twice. As a result, UL_TTI for RACH indication is regularly sent every two slots every two frames to request RA.

```c
    printf("\n[NTUST]	put_queue gnb_rach_ind_queue\n");
    if (!put_queue(&gnb_rach_ind_queue, rach_ind))
    {
```

# Flow table

| **schProcessRaReq** |
| --- |
| **schAllocMsg3Pusch** |

```
 九  11 12:19:52 [32m[NR_RRC]   SIB1 decoded
 九  11 12:19:52 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 九  11 12:19:52 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 九  11 12:19:53 [0m[NR_PHY]   ============================================
 九  11 12:19:53 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
 九  11 12:19:53 [0m[NR_PHY]   ============================================
 九  11 12:19:54 [0m[NR_PHY]   ============================================
 九  11 12:19:54 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
 九  11 12:19:54 [0m[NR_PHY]   ============================================
 九  11 12:19:55 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 九  11 12:19:55 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 九  11 12:19:55 [0m[NR_MAC]   Initialization of 4-step contention-based random access procedure
 九  11 12:19:55 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
 九  11 12:19:55 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 2, first_nonzero_root_idx 0
 九  11 12:19:55 [0m[1;31m[PHY]   [UE 0] frame 186, nr_slot_rx 0, Error decoding PBCH!
 九  11 12:19:55 [0m[1;31m[PHY]   [UE 0] frame 188, nr_slot_rx 0, Error decoding PBCH!
 九  11 12:19:55 [0m[1;31m[PHY]   [UE 0] frame 190, nr_slot_rx 0, Error decoding PBCH!
 九  11 12:19:55 [0m[1;31m[PHY]   [UE 0] frame 192, nr_slot_rx 0, Error decoding PBCH!
 九  11 12:19:55 [0m[NR_PHY]   ============================================
 九  11 12:19:55 [0m[NR_PHY]   Harq round stats for Downlink: 1/0/0
 九  11 12:19:55 [0m[NR_PHY]   ============================================
```

```
 九  11 12:19:51 [0m[HW]   A client connects, sending the current time
 九  11 12:19:55 [0m[NR_PHY]   [RAPROC] 183.18 Initiating RA procedure with preamble 10, energy 54.0 dB (I0 0, thres 150), delay 0 start symbol 0 freq index 0
 九  11 12:19:55 [0m[PHY]   pack_nr_rach_indication_body
 九  11 12:19:55 [0m[PHY]   value->slot_index:18
 九  11 12:19:55 [0m[PHY]   value->phy_cell_id:1
 九  11 12:19:55 [0m[PHY]   value->symbol_index:0
 九  11 12:19:55 [0m[PHY]   value->freq_index:0
 九  11 12:19:55 [0m[PHY]   value->avg_rssi:236
 九  11 12:19:55 [0m[PHY]   value->avg_snr:255
 九  11 12:19:55 [0m[PHY]   value->num_preamble:1
 九  11 12:19:55 [0m[PHY]   value->preamble_list[0].preamble_index:10
 九  11 12:19:55 [0m[PHY]   value->preamble_list[0].timing_advance:0
 九  11 12:19:55 [0m[PHY]   value->preamble_list[0].preamble_pwr:-1
 九  11 12:19:55 [0m[NR_PHY]   [RAPROC] 183.19 Initiating RA procedure with preamble 10, energy 54.0 dB (I0 50, thres 150), delay 0 start symbol 0 freq index 0
 九  11 12:19:55 [0m[PHY]   pack_nr_rach_indication_body
 九  11 12:19:55 [0m[PHY]   value->slot_index:19
 九  11 12:19:55 [0m[PHY]   value->phy_cell_id:1
 九  11 12:19:55 [0m[PHY]   value->symbol_index:0
 九  11 12:19:55 [0m[PHY]   value->freq_index:0
 九  11 12:19:55 [0m[PHY]   value->avg_rssi:236
 九  11 12:19:55 [0m[PHY]   value->avg_snr:255
 九  11 12:19:55 [0m[PHY]   value->num_preamble:1
 九  11 12:19:55 [0m[PHY]   value->preamble_list[0].preamble_index:10
 九  11 12:19:55 [0m[PHY]   value->preamble_list[0].timing_advance:0
 九  11 12:19:55 [0m[PHY]   value->preamble_list[0].preamble_pwr:-1
 九  11 12:19:55 [0m[PHY]   pusch_pdu->pdu_bit_map: 1
 九  11 12:19:55 [0m[PHY]   pusch_pdu->rnti: 100
 九  11 12:19:55 [0m[PHY]   pusch_pdu->handle: 0
 九  11 12:19:55 [0m[PHY]   pusch_pdu->bwp_size: 106
 九  11 12:19:55 [0m[PHY]   pusch_pdu->bwp_start: 0
 九  11 12:19:55 [0m[PHY]   pusch_pdu->subcarrier_spa
```

```
 九  11 13:30:39 1726032639.453797 [PHY]   UL_TTI_REQUEST: SFN/SLOT 1/19, n_pdus 1, rach_present 1, n_ulsch 0, n_ulcch 0, n_group 0
 九  11 13:30:39 [0m1726032639.453807 [PHY]   Packing PRACH PDU phys_cell_id:1, num_prach_ocas:3, prach_format:5, num_ra:0, prach_start_symbol:0, num_cs:34
 九  11 13:30:39 [0m1726032639.495470 [PHY]   UL_TTI_REQUEST: SFN/SLOT 3/19, n_pdus 1, rach_present 1, n_ulsch 0, n_ulcch 0, n_group 0
 九  11 13:30:39 [0m1726032639.495480 [PHY]   Packing PRACH PDU phys_cell_id:1, num_prach_ocas:3, prach_format:5, num_ra:0, prach_start_symbol:0, num_cs:34
 九  11 13:30:39 [0m1726032639.537066 [PHY]   UL_TTI_REQUEST: SFN/SLOT 5/19, n_pdus 1, rach_present 1, n_ulsch 0, n_ulcch 0, n_group 0
 九  11 13:30:39 [0m1726032639.537076 [PHY]   Packing PRACH PDU phys_cell_id:1, num_prach_ocas:3, prach_format:5, num_ra:0, prach_start_symbol:0, num_cs:34
 九  11 13:30:39 [0m1726032639.578635 [PHY]   UL_TTI_REQUEST: SFN/SLOT 7/19, n_pdus 1, rach_present 1, n_ulsch 0, n_ulcch 0, n_group 0
 九  11 13:30:39 [0m1726032639.578645 [PHY]   Packing PRACH PDU phys_cell_id:1, num_prach_ocas:3, prach_format:5, num_ra:0, prach_start_symbol:0, num_cs:34
 九  11 13:30:39 [0m1726032639.620253 [PHY]   UL_TTI_REQUEST: SFN/SLOT 9/19, n_pdus 1, rach_present 1, n_ulsch 0, n_ulcch 0, n_group 0
 九  11 13:30:39 [0m1726032639.620263 [PHY]   Packing PRACH PDU phys_cell_id:1, num_prach_ocas:3, prach_format:5, num_ra:0, prach_start_symbol:0, num_cs:34
 九  11 13:30:39 [0m1726032639.661834 [PHY]   UL_TTI_REQUEST: SFN/SLOT 11/19, n_pdus 1, rach_present 1, n_ulsch 0, n_ulcch 0, n_group 0
 九  11 13:30:39 [0m1726032639.661843 [PHY]   Packing PRACH PDU phys_cell_id:1, num_prach_ocas:3, prach_format:5, num_ra:0, prach_start_symbol:0, num_cs:34
 九  11 13:30:39 [0m1726032639.703596 [PHY]   UL_TTI_REQUEST: SFN/SLOT 13/19, n_pdus 1, rach_present 1, n_ulsch 0, n_ulcch 0, n_group 0
 九  11 13:30:39 [0m1726032639.703607 [PHY]   Packing PRACH PDU phys_cell_id:1, num_prach_ocas:3, prach_format:5, num_ra:0, prach_start_symbol:0, num_cs:34
 九  11 13:30:39 [0m1726032639.745453 [PHY]   
```

- From OAI, we know that they send UL_TTI for RACH every two frames fixed at slot 19, so this issue may not occur with OSC. This could potentially be an issue with the OAI PNF, but it could also be a limitation of the NR specification (which requires further in-depth study).
- For now, I would prefer to debug by modifying the OSC to send UL_TTI at the same frequency as OAI. If this turns out to be a specification issue, it means there might be a problem with OAI PNF, which would need to be addressed as well. Currently, the direction is to focus on making this adjustment to OSC.
- I will discuss this with Robert later to get his opinion and have him evaluate whether this is an issue with OAI PNF.

## Design conditions for VNF to determine when to send UL_TTI for RACH

- OAI always sends UL_TTI at SLOT 19, and OAI UE also transmits at SLOT 19.
- When OSC sends UL_TTI for RACH continuously in SLOT 18 and 19, OAI PNF incorrectly responds with RACH indications for two consecutive slots.
- Currently, it is tentatively believed to be an issue with OAI PNF, which should not exhibit such behavior. Therefore, on the OSC side, we should adjust the conditions to ensure that DU High sends UL_TTI for RACH only in slot 19 every two frames → This method is feasible and allows a UE to successfully communicate with F1AP.

```c
   /* Schedule resources for PRACH */
   if(cell->firstSib1Transmitted && ulTimingInfo.slot == 19)
    schPrachResAlloc(cell, &ulSchedInfo, ulTimingInfo);
```

```c
      UL_tti_req->SFN = frameP;
      UL_tti_req->Slot = slotP;
      UL_tti_req->rach_present = 1;
      for (int fdm_index=0; fdm_index < fdm; fdm_index++) { // one structure per frequency domain occasion
        for (int td_index=0; td_index<N_t_slot; td_index++) {

          prach_occasion_id = (((frameP % (cc->max_association_period * config_period))/config_period) * cc->total_prach_occasions_per_config_period) +
                              (RA_sfn_index + slot_index) * N_t_slot * fdm + td_index * fdm + fdm_index;

          if((prach_occasion_id < cc->total_prach_occasions) && (td_index == 0)){
            AssertFatal(UL_tti_req->n_pdus < sizeof(UL_tti_req->pdus_list) / sizeof(UL_tti_req->pdus_list[0]),
                        "Invalid UL_tti_req->n_pdus %d\n", UL_tti_req->n_pdus);

            UL_tti_req->pdus_list[UL_tti_req->n_pdus].pdu_type = NFAPI_NR_UL_CONFIG_PRACH_PDU_TYPE;
            UL_tti_req->pdus_list[UL_tti_req->n_pdus].pdu_size = sizeof(nfapi_nr_prach_pdu_t);
            nfapi_nr_prach_pdu_t  *prach_pdu = &UL_tti_req->pdus_list[UL_tti_req->n_pdus].prach_pdu;
            memset(prach_pdu,0,sizeof(nfapi_nr_prach_pdu_t));
            UL_tti_req->n_pdus+=1;

```

![{AA88F62D-B55A-4104-9505-CD8E967777D8}.png](AA88F62D-B55A-4104-9505-CD8E967777D8.png)

![{1AE43D43-A8BC-4BCB-8ADC-DA7E529CD359}.png](1AE43D43-A8BC-4BCB-8ADC-DA7E529CD359.png)

Based on the specification (`FAPI` spec) and the process flow, it seems that the issue lies with the `OAI PNF`. According to the specification defining the `PHY` behavior:

If a `UE` decides to `RACH`, and a preamble is detected by the `PHY`, then a `RACH indication` message is sent. However, if no `RACH` preamble is detected by the `PHY`, then no `RACH.indication` message is sent.

In this case, OSC is sending UL_TTI.request to the PHY including a RACH PDU in two consecutive slots. In the first slot, the `UE` has not yet sent the preamble, but the `OAI PNF` is returning `RACH.indication` in both of these slots.

<aside>
💡

Complete!

</aside>