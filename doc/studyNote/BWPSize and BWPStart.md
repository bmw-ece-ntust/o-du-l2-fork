# BWPSize and BWPStart

## Flow

- **schedule_nr_sib1**
    - **schedule_control_sib1**
        - **fill_searchSpaceZero**
        - **fill_coresetZero**
        - **set_pdcch_structure**
    - **nr_fill_nfapi_dl_sib1_pdu**
        - **nr_configure_pdcch**
        - **fill_dci_pdu_rel15**

```c
static uint32_t schedule_control_sib1(module_id_t module_id,
                                      int CC_id,
                                      NR_Type0_PDCCH_CSS_config_t *type0_PDCCH_CSS_config,
                                      int time_domain_allocation,
                                      NR_pdsch_dmrs_t *dmrs_parms,
                                      NR_tda_info_t *tda_info,
                                      uint8_t candidate_idx,
                                      uint16_t num_total_bytes)
{
  gNB_MAC_INST *gNB_mac = RC.nrmac[module_id];
  NR_COMMON_channels_t *cc = &gNB_mac->common_channels[CC_id];
  NR_ServingCellConfigCommon_t *scc = cc->ServingCellConfigCommon;
  uint16_t *vrb_map = cc->vrb_map;

  if (gNB_mac->sched_ctrlCommon == NULL){
    LOG_D(NR_MAC,"schedule_control_common: Filling nr_mac->sched_ctrlCommon\n");
    gNB_mac->sched_ctrlCommon = calloc(1,sizeof(*gNB_mac->sched_ctrlCommon));
    gNB_mac->sched_ctrlCommon->search_space = calloc(1,sizeof(*gNB_mac->sched_ctrlCommon->search_space));
    gNB_mac->sched_ctrlCommon->coreset = calloc(1,sizeof(*gNB_mac->sched_ctrlCommon->coreset));
    fill_searchSpaceZero(gNB_mac->sched_ctrlCommon->search_space,
                         nr_slots_per_frame[*scc->ssbSubcarrierSpacing],
                         type0_PDCCH_CSS_config);
    fill_coresetZero(gNB_mac->sched_ctrlCommon->coreset, type0_PDCCH_CSS_config);
    gNB_mac->cset0_bwp_start = type0_PDCCH_CSS_config->cset_start_rb;
    gNB_mac->cset0_bwp_size = type0_PDCCH_CSS_config->num_rbs;
```

```c
  if (bwp) { // This is not for SIB1
    if(coreset->controlResourceSetId == 0){
      pdcch.BWPSize  = gNB_mac->cset0_bwp_size;
      pdcch.BWPStart = gNB_mac->cset0_bwp_start;
    }
    else {
      pdcch.BWPSize  = NRRIV2BW(bwp->locationAndBandwidth, MAX_BWP_SIZE);
      pdcch.BWPStart = NRRIV2PRBOFFSET(bwp->locationAndBandwidth, MAX_BWP_SIZE);
    }
    pdcch.SubcarrierSpacing = bwp->subcarrierSpacing;
    pdcch.CyclicPrefix = (bwp->cyclicPrefix==NULL) ? 0 : *bwp->cyclicPrefix;

    //AssertFatal(pdcch_scs==kHz15, "PDCCH SCS above 15kHz not allowed if a symbol above 2 is monitored");
    sps = bwp->cyclicPrefix == NULL ? 14 : 12;
  }
```

## Size

```c
int NRRIV2BW(int locationAndBandwidth,int N_RB) {
  int tmp = locationAndBandwidth/N_RB;
  int tmp2 = locationAndBandwidth%N_RB;
  if (tmp <= ((N_RB>>1)+1) && (tmp+tmp2)<N_RB) return(tmp+1);
  else                      return(N_RB+1-tmp);

}
```

## Start

```c
int NRRIV2PRBOFFSET(int locationAndBandwidth,int N_RB) {
  int tmp = locationAndBandwidth/N_RB;
  int tmp2 = locationAndBandwidth%N_RB;
  if (tmp <= ((N_RB>>1)+1) && (tmp+tmp2)<N_RB) return(tmp2);
  else                      return(N_RB-1-tmp2);
}
```