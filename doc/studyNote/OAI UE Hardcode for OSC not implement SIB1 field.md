# OAI UE Hardcode for OSC not implement SIB1 field

Start Date: 2024/06/03
Summary: Implement hardcoding for the SIB1 field in the OAI UE for OSC.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

# HARD CODE

**`pdcch_config->ra_SS`**

| **searchSpaceType** |  |  |
| --- | --- | --- |
|  | **present** | 1 |
|  | **->choice.common->dci_Format0_0_AndFormat1_0** | 0 |

```c
  if (mac->state == UE_PERFORMING_RA && mac->ra.ra_state >= nrRA_WAIT_RAR) {
    LOG_D(PHY, "Configuring DCI for RA\n");
    // if RA is ongoing use RA search space
    if (is_ss_monitor_occasion(frame, slot, slots_per_frame, pdcch_config->ra_SS)) {
      int rnti_type = mac->ra.ra_state == nrRA_WAIT_RAR ? TYPE_RA_RNTI_ : TYPE_TC_RNTI_;
      LOG_I(PHY, "rnti_type:%d\n",rnti_type);
        /*HARD CODE*/
      pdcch_config->ra_SS->searchSpaceType = calloc(1,sizeof(*pdcch_config->ra_SS->searchSpaceType));
      // pdcch_config->ra_SS->searchSpaceType->present = (NR_SearchSpace__searchSpaceType_PR *)calloc(1,sizeof(NR_SearchSpace__searchSpaceType_PR ));
      pdcch_config->ra_SS->searchSpaceType->present = 1;
      pdcch_config->ra_SS->searchSpaceType->choice.common = calloc(1,sizeof(*pdcch_config->ra_SS->searchSpaceType->choice.common));
      pdcch_config->ra_SS->searchSpaceType->choice.common->dci_Format0_0_AndFormat1_0 = calloc(1,sizeof(*pdcch_config->ra_SS->searchSpaceType->choice.common->dci_Format0_0_AndFormat1_0));

```