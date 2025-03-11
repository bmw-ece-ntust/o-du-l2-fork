# Fix no SIB1

Start Date: 2024/05/02
Summary: Fix the SIB1 by implementing the necessary code changes and handling downlink indications effectively.
Status: Reject
Assign: Ming 咚咚 [銘鴻], 陳奕全

| **proc->rx_slot_type** | 1 |
| --- | --- |
| nr_fill_dl_indication |  |
|  |  |
- List normal will process code part:

```c
  if (proc->rx_slot_type == NR_DOWNLINK_SLOT || proc->rx_slot_type == NR_MIXED_SLOT) {

    if(UE->if_inst != NULL && UE->if_inst->dl_indication != NULL) {
      LOG_I(MAC, "UE_dl_preprocessing\n");
      nr_downlink_indication_t dl_indication;
      nr_fill_dl_indication(&dl_indication, NULL, NULL, proc, UE, phy_data);
      UE->if_inst->dl_indication(&dl_indication);
    }
```

![Untitled](Untitled%2053.png)

```c
  sdu_size_t sdu_size = 0;

  switch(channel) {
    case NR_BCCH_BCH:
    case NR_BCCH_DL_SCH:
      if (pdu_len>0) {
        LOG_T(NR_RRC, "[UE %d] Received SDU for NR-BCCH-DL-SCH on SRB %u from gNB %d\n", module_id, channel & RAB_OFFSET,
              gNB_index);

        MessageDef *message_p;
        int msg_sdu_size = BCCH_SDU_SIZE;

        if (pdu_len > msg_sdu_size) {
          LOG_E(NR_RRC, "SDU larger than NR-BCCH-DL-SCH SDU buffer size (%d, %d)", sdu_size, msg_sdu_size);
          sdu_size = msg_sdu_size;
        } else {
          sdu_size = pdu_len;
        }

        message_p = itti_alloc_new_message(TASK_MAC_UE, 0, NR_RRC_MAC_BCCH_DATA_IND);
        memset(NR_RRC_MAC_BCCH_DATA_IND (message_p).sdu, 0, BCCH_SDU_SIZE);
        memcpy(NR_RRC_MAC_BCCH_DATA_IND (message_p).sdu, pduP, sdu_size);
        NR_RRC_MAC_BCCH_DATA_IND (message_p).frame = frame; //frameP
        NR_RRC_MAC_BCCH_DATA_IND (message_p).slot = slot;
        NR_RRC_MAC_BCCH_DATA_IND (message_p).sdu_size = sdu_size;
        NR_RRC_MAC_BCCH_DATA_IND (message_p).gnb_index = gNB_index;
        NR_RRC_MAC_BCCH_DATA_IND (message_p).is_bch = (channel == NR_BCCH_BCH);
        itti_send_msg_to_task(TASK_RRC_NRUE, GNB_MODULE_ID_TO_INSTANCE(module_id), message_p);
      }
      break;
```

```c
int8_t nr_ue_decode_BCCH_DL_SCH(NR_UE_MAC_INST_t *mac,
                                int cc_id,
                                unsigned int gNB_index,
                                uint8_t ack_nack,
                                uint8_t *pduP,
                                uint32_t pdu_len)
{
  if(ack_nack) {
    LOG_D(NR_MAC, "Decoding NR-BCCH-DL-SCH-Message (SIB1 or SI)\n");
    nr_mac_rrc_data_ind_ue(mac->ue_id, cc_id, gNB_index, 0, 0, 0, NR_BCCH_DL_SCH, (uint8_t *) pduP, pdu_len);
    mac->get_sib1 = false;
    mac->get_otherSI = false;
  }
  else
    LOG_E(NR_MAC, "Got NACK on NR-BCCH-DL-SCH-Message (%s)\n", mac->get_sib1 ? "SIB1" : "other SI");
  return 0;
}
```

```c
          case FAPI_NR_RX_PDU_TYPE_SIB:
            ret_mask |= (handle_bcch_dlsch(mac,
                                           dl_info->cc_id, dl_info->gNB_index,
                                           rx_indication_body.pdsch_pdu.ack_nack,
                                           rx_indication_body.pdsch_pdu.pdu,
                                           rx_indication_body.pdsch_pdu.pdu_length)) << FAPI_NR_RX_PDU_TYPE_SIB;
            break;
```

---

`check_and_process_dci` → `copy_dl_tti_req_to_dl_info` or `copy_tx_data_req_to_dl_info` will `fill_rx_ind`

`process_queued_nr_nfapi_msgs`

`NRUE_phy_stub_standalone_pnf_task`

`nr_ue_dlsch_procedures` or  `nr_rx_pbch` or `nr_dlsch_decoding`

 call fill nr_fill_dl_indication  

->dl_indication

```c
  if (msgTx->num_pdsch_slot > 0) {
    VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME(VCD_SIGNAL_DUMPER_FUNCTIONS_GENERATE_DLSCH,1);
    LOG_D(PHY, "PDSCH generation started (%d) in frame %d.%d\n", msgTx->num_pdsch_slot,frame,slot);
    nr_generate_pdsch(msgTx, frame, slot);
    VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME(VCD_SIGNAL_DUMPER_FUNCTIONS_GENERATE_DLSCH,0);
  }
```

 in slot indication, measure slot duration and wait to not be faster in slot than 300us