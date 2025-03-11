# Fix: Revise MSG4 DCI for UE send ACK by PUCCH

Start Date: 2024/09/27
Summary: Revise MSG4 DCI to ensure the UE sends ACK via PUCCH in the correct time slots.
Status: Done
Assign: Ming 咚咚 [銘鴻]

# Issues define

<aside>
⚠️

Because of the issue → [Issues:  Assertion is_nr_UL_slot() failed](Issues%20Assertion%20is_nr_UL_slot()%20failed%201211009831438180a3e9f623fa434c83.md)  the UE attempts to send MSG4 ACK/NACK via PUCCH in incorrect time slots (1 or 2). One solution I propose is to revise the DCI to ensure the UE sends in the correct time slot.

</aside>

<aside>
💡

Reference Note:

[Issues:  Assertion is_nr_UL_slot() failed](Issues%20Assertion%20is_nr_UL_slot()%20failed%201211009831438180a3e9f623fa434c83.md) 

[Compare OSC DU send MSG4](Compare%20OSC%20DU%20send%20MSG4%201211009831438147a50bd917d4b0a91d.md) 

</aside>

## Trace code in OSC DU High

- `harqFeedbackInd`

```c
-> Function: OAI_OSC_fillDlMsgDlDciPdu()

      /* Fetching DCI field values */
      dciFormatId      = dlMsgSchInfo->dciFormatId;     /* Always set to 1 for DL */
      timeDomResAssign = 0; //pdcchInfo->dci.pdschCfg.pdschTimeAlloc.rowIndex -1;
      VRB2PRBMap       = pdcchInfo->dci.pdschCfg.pdschFreqAlloc.vrbPrbMapping;
      modNCodScheme    = 0; //pdcchInfo->dci.pdschCfg.codeword[0].mcsIndex;
      ndi              = dlMsgSchInfo->transportBlock[0].ndi;
      redundancyVer    = pdcchInfo->dci.pdschCfg.codeword[0].rvIndex;
      harqProcessNum   = dlMsgSchInfo->harqProcNum;
      dlAssignmentIdx  = dlMsgSchInfo->dlAssignIdx;
      pucchTpc         = dlMsgSchInfo->pucchTpc;
      pucchResoInd     = dlMsgSchInfo->pucchResInd;
      harqFeedbackInd  = 1;//dlMsgSchInfo->harqFeedbackInd;
```

```jsx
void fillDlMsgInfo(DlMsgSchInfo *dlMsgSchInfo, uint16_t crnti, bool isRetx, SchDlHqProcCb *hqP)
{
   hqP->tbInfo[0].isEnabled = TRUE;
   hqP->tbInfo[0].state = HQ_TB_WAITING;
   hqP->tbInfo[0].txCntr++;
   hqP->tbInfo[1].isEnabled = TRUE;
   hqP->tbInfo[1].state = HQ_TB_WAITING;
   hqP->tbInfo[1].txCntr++;
   dlMsgSchInfo->crnti = crnti;
   dlMsgSchInfo->transportBlock[0].ndi = hqP->tbInfo[0].ndi; /*How to handle two tb case?TBD*/
   dlMsgSchInfo->harqProcNum = hqP->procId;
   dlMsgSchInfo->dlAssignIdx = 0;
   dlMsgSchInfo->pucchTpc = 0;
   dlMsgSchInfo->pucchResInd = 0;
   dlMsgSchInfo->harqFeedbackInd = hqP->k1;
   dlMsgSchInfo->dciFormatId = 1;
}
```

## Trace code in OAI VNF

Before all tasks, I think I need to check how OAI sets the DCI to let the UE know when it can send MSG4 via PUCCH, because OSC sets the value the same as UL_TTI for the PUCCH K1 value.

- `curr_pucch->timing_indicator`

```jsx
  for (int f = 0; f < fb_size; f++) {
    // can't schedule ACKNACK before minimum feedback time
    if(pdsch_to_harq_feedback[f] < minfbtime)
      continue;
    const int pucch_slot = (slot + pdsch_to_harq_feedback[f]) % n_slots_frame;
    // check if the slot is UL
    if(pucch_slot%nr_slots_period < first_ul_slot_period)
      continue;
    const int pucch_frame = (frame + ((slot + pdsch_to_harq_feedback[f]) / n_slots_frame)) & 1023;
    // we store PUCCH resources according to slot, TDD configuration and size of the vector containing PUCCH structures
    const int pucch_index = get_pucch_index(pucch_frame, pucch_slot, n_slots_frame, tdd, sched_ctrl->sched_pucch_size);
    NR_sched_pucch_t *curr_pucch = &sched_ctrl->sched_pucch[pucch_index];
    if (curr_pucch->active &&
        curr_pucch->frame == pucch_frame &&
        curr_pucch->ul_slot == pucch_slot) { // if there is already a PUCCH in given frame and slot
      LOG_D(NR_MAC, "pucch_acknack DL %4d.%2d, UL_ACK %4d.%2d Bits already in current PUCCH: DAI_C %d CSI %d\n",
            frame, slot, pucch_frame, pucch_slot, curr_pucch->dai_c, curr_pucch->csi_bits);
      // we can't schedule if short pucch is already full
      if (curr_pucch->csi_bits == 0 &&
          curr_pucch->dai_c == 2)
        continue;
      // if there is CSI but simultaneous HARQ+CSI is disable we can't schedule
      if (curr_pucch->csi_bits > 0 && !curr_pucch->simultaneous_harqcsi)
        continue;
      // check if the number of bits to be scheduled can fit in current PUCCH
      // according to PUCCH code rate (if not we search for another allocation)
      // the number of bits in the check need to include possible SR (1 bit)
      // and the ack/nack bit to be scheduled (1 bit)
      // so the number of bits already scheduled in current pucch + 2
      if (curr_pucch->csi_bits > 0
          && !check_bits_vs_coderate_limit(pucch_Config,
                                           curr_pucch->csi_bits + curr_pucch->dai_c + 2,
                                           curr_pucch->resource_indicator))
        continue;
      // TODO temporarily limit ack/nak to 3 bits because of performances of polar for PUCCH (required for > 11 bits)
      if (curr_pucch->csi_bits > 0 && curr_pucch->dai_c >= 3)
        continue;

      // otherwise we can schedule in this active PUCCH
      // no need to check VRB occupation because already done when PUCCH has been activated
      curr_pucch->timing_indicator = f;
```

![image.png](image%2029.png)

Revise `harqFeedbackInd` from 6 (OAI use) to 2. This change could make the UE send MSG4 ACK via PUCCH in slot 17 (the correct UL slot).

It looks like it successfully received MSG4 DCI (PDCCH). But it still does not get MSG4 PDSCH currently. I still need to trace the OAI UE source code to check what the problem is. → [UE is unable to receive MSG4 PDSCH message](UE%20is%20unable%20to%20receive%20MSG4%20PDSCH%20message%201211009831438136bf93dadd77d7f40f.md)