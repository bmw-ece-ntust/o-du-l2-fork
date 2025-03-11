# Trace OAI dl_rrc_message_transfer

Start Date: 2024/10/21
Summary: Trace the OAI downlink RRC message transfer process, including handling user equipment context and message reception.
Status: Reject
Assign: Ming 咚咚 [銘鴻]

### 1. Encountered Issues

- Issue : [UE Segmentation fault after Generating RRCSetupComplete](UE%20Segmentation%20fault%20after%20Generating%20RRCSetupCom%2012110098314381d1adf3f719885a3bf8.md)

### 2. Source Code Records

```bash
void dl_rrc_message_transfer(const f1ap_dl_rrc_message_t *dl_rrc)
{
  LOG_D(NR_MAC,
        "DL RRC Message Transfer with %d bytes for RNTI %04x SRB %d\n",
        dl_rrc->rrc_container_length,
        dl_rrc->gNB_DU_ue_id,
        dl_rrc->srb_id);

  gNB_MAC_INST *mac = RC.nrmac[0];
  pthread_mutex_lock(&mac->sched_lock);
  /* check first that the scheduler knows such UE */
  NR_UE_info_t *UE = find_nr_UE(&mac->UE_info, dl_rrc->gNB_DU_ue_id);
  if (UE == NULL) {
    LOG_E(MAC, "ERROR: unknown UE with RNTI %04x, ignoring DL RRC Message Transfer\n", dl_rrc->gNB_DU_ue_id);
    pthread_mutex_unlock(&mac->sched_lock);
    return;
  }
  pthread_mutex_unlock(&mac->sched_lock);

  if (!du_exists_f1_ue_data(dl_rrc->gNB_DU_ue_id)) {
    LOG_I(NR_MAC, "No CU UE ID stored for UE RNTI %04x, adding CU UE ID %d\n", dl_rrc->gNB_DU_ue_id, dl_rrc->gNB_CU_ue_id);
    f1_ue_data_t new_ue_data = {.secondary_ue = dl_rrc->gNB_CU_ue_id};
    du_add_f1_ue_data(dl_rrc->gNB_DU_ue_id, &new_ue_data);
  }

  if (UE->expect_reconfiguration && dl_rrc->srb_id == 1) {
    /* we expected a reconfiguration, and this is on DCCH. We assume this is
     * the reconfiguration: nr_mac_prepare_cellgroup_update() already stored
     * the CellGroupConfig. Below, we trigger a timer, and the CellGroupConfig
     * will be applied after its expiry in nr_mac_apply_cellgroup().*/
    NR_SCHED_LOCK(&mac->sched_lock);
    nr_mac_enable_ue_rrc_processing_timer(mac, UE, /* apply_cellGroup = */ true);
    NR_SCHED_UNLOCK(&mac->sched_lock);
    UE->expect_reconfiguration = false;
    /* Re-establish RLC for all remaining bearers */
    if (UE->reestablish_rlc) {
      for (int i = 1; i < UE->UE_sched_ctrl.dl_lc_num; ++i)
        nr_rlc_reestablish_entity(dl_rrc->gNB_DU_ue_id, UE->UE_sched_ctrl.dl_lc_ids[i]);
      UE->reestablish_rlc = false;
    }
  }

  if (dl_rrc->old_gNB_DU_ue_id != NULL) {
    AssertFatal(*dl_rrc->old_gNB_DU_ue_id != dl_rrc->gNB_DU_ue_id,
                "logic bug: current and old gNB DU UE ID cannot be the same\n");
    /* 38.401 says: "Find UE context based on old gNB-DU UE F1AP ID, replace
     * old C-RNTI/PCI with new C-RNTI/PCI". Below, we do the inverse: we keep
     * the new UE context (with new C-RNTI), but set up everything to reuse the
     * old config. */
    NR_UE_info_t *oldUE = find_nr_UE(&mac->UE_info, *dl_rrc->old_gNB_DU_ue_id);
    DevAssert(oldUE);
    pthread_mutex_lock(&mac->sched_lock);
    /* 38.331 5.3.7.2 says that the UE releases the spCellConfig, so we drop it
     * from the current configuration. Also, expect the reconfiguration from
     * the CU, so save the old UE's CellGroup for the new UE */
    UE->CellGroup->spCellConfig = NULL;
    NR_UE_sched_ctrl_t *sched_ctrl = &UE->UE_sched_ctrl;
    NR_ServingCellConfigCommon_t *scc = mac->common_channels[0].ServingCellConfigCommon;
    uid_t temp_uid = UE->uid;
    UE->uid = oldUE->uid;
    oldUE->uid = temp_uid;
    configure_UE_BWP(mac, scc, sched_ctrl, NULL, UE, -1, -1);

    nr_mac_prepare_cellgroup_update(mac, UE, oldUE->CellGroup);
    oldUE->CellGroup = NULL;
    mac_remove_nr_ue(mac, *dl_rrc->old_gNB_DU_ue_id);
    pthread_mutex_unlock(&mac->sched_lock);
    nr_rlc_remove_ue(dl_rrc->gNB_DU_ue_id);
    nr_rlc_update_id(*dl_rrc->old_gNB_DU_ue_id, dl_rrc->gNB_DU_ue_id);
    /* Set flag to trigger RLC re-establishment
     * for remaining RBs in next RRCReconfiguration */
    UE->reestablish_rlc = true;
    /* 38.331 clause 5.3.7.4: apply the specified configuration defined in 9.2.1 for SRB1 */
    nr_rlc_reconfigure_entity(dl_rrc->gNB_DU_ue_id, 1, NULL);
    instance_t f1inst = get_f1_gtp_instance();
    if (f1inst >= 0) // we actually use F1-U
      gtpv1u_update_ue_id(f1inst, *dl_rrc->old_gNB_DU_ue_id, dl_rrc->gNB_DU_ue_id);
  }

  /* the DU ue id is the RNTI */
  nr_rlc_srb_recv_sdu(dl_rrc->gNB_DU_ue_id, dl_rrc->srb_id, dl_rrc->rrc_container, dl_rrc->rrc_container_length);
}

```