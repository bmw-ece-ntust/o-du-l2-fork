# Try to dump the full P5 config request message

Start Date: 2024/06/03
Summary: Dumping and analyzing the full P5 configuration request message for nfapi_NR.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration

# I add dump more part

```c
static void dump_nr_config_request(nfapi_nr_config_request_scf_t *config)
{
  printf("num_tlv:%d\n", config->num_tlv);
  nfapi_nr_ssb_config_t *sc = &config->ssb_config;
  printf("ssb_config\n");
  PRINT_TLV("  bch_payload", &sc->bch_payload);
  PRINT_TLV("  scs_common", &sc->scs_common);
  PRINT_TLV("  ss_pbch_power", &sc->ss_pbch_power);
  nfapi_nr_ssb_table_t *st = &config->ssb_table;
  printf("ssb_table\n");
  PRINT_TLV("  ssb_offset_point_a", &st->ssb_offset_point_a);
  PRINT_TLV("  beta_pss", &st->beta_pss);
  PRINT_TLV("  ssb_period", &st->ssb_period);
  PRINT_TLV("  ssb_subcarrier_offset", &st->ssb_subcarrier_offset);
  PRINT_TLV("  MIB", &st->MIB);
  // Print ssb_mask_list
  printf("ssb_mask_list:\n");
  for (int i = 0; i < 2; ++i) {
      printf("%d\t", st->ssb_mask_list[i].ssb_mask.value);
  }
  // Print ssb_beam_id_list
  printf("\nssb_beam_id_list:\n");
  for (int i = 0; i < 64; ++i) {
      printf("%d\t", st->ssb_beam_id_list[i].beam_id.value);
  }
  printf("\n");
  PRINT_TLV("  ss_pbch_multiple_carriers_in_a_band", &st->ss_pbch_multiple_carriers_in_a_band);
  PRINT_TLV("  multiple_cells_ss_pbch_in_a_carrier", &st->multiple_cells_ss_pbch_in_a_carrier);  
  
  printf("tdd_table\n");
  nfapi_nr_tdd_table_t  *stt = &config->tdd_table;
  PRINT_TLV("  tdd_period", &stt->tdd_period);
  PRINT_TLV("  slot_config", &stt->max_tdd_periodicity_list->max_num_of_symbol_per_slot_list->slot_config);
  
  printf("cell_config\n");
  nfapi_nr_cell_config_t *scc = &config->cell_config;
  PRINT_TLV("  frame_duplex_type", &scc->frame_duplex_type);
  PRINT_TLV("  phy_cell_id", &scc->phy_cell_id);

  printf("nfapi_nr_measurement_config_t\n");
  nfapi_nr_measurement_config_t *smc = &config->measurement_config;
  PRINT_TLV("  rssi_measurement", &smc->rssi_measurement);

  printf("nfapi_nr_nfapi_t\n");
  nfapi_nr_nfapi_t *sn = &config->nfapi_config;
  PRINT_TLV("  dl_tti_timing_offset", &sn->dl_tti_timing_offset);
  PRINT_TLV("  ul_tti_timing_offset", &sn->ul_tti_timing_offset);
  PRINT_TLV("  ul_dci_timing_offset", &sn->ul_dci_timing_offset);
  PRINT_TLV("  tx_data_timing_offset", &sn->tx_data_timing_offset);
  for(int i=0;i<4;i++)
    printf("%d\t",sn->p7_pnf_address_ipv4.address[i]);
  printf("\n");
  for(int i=0;i<4;i++)
    printf("%d\t",sn->p7_pnf_address_ipv6.address[i]);
  printf("\n");
  PRINT_TLV("  p7_pnf_port", &sn->p7_pnf_port);
  PRINT_TLV("  timing_window", &sn->timing_window);
  PRINT_TLV("  timing_info_mode", &sn->timing_info_mode);
  PRINT_TLV("  timing_info_period", &sn->timing_info_period);

  printf("pmi_list:\n");
  printf("  num_pm_idx:%d\n",&config->pmi_list.num_pm_idx);
  printf("  pm_idx:%d\n",&config->pmi_list.pmi_pdu->pm_idx);
  printf("  numLayers:%d\n",&config->pmi_list.pmi_pdu->numLayers);
  printf("  num_ant_ports:%d\n",&config->pmi_list.pmi_pdu->num_ant_ports);
  printf("  weights:");
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++)
      printf("  %d\t",&config->pmi_list.pmi_pdu->weights[i][j]);
  }
  printf("\n");
```

## Origin part

```c
nfapi_nr_carrier_config_t *cc = &config->carrier_config;
  printf("carrier_config\n");
  PRINT_TLV("  bw", &cc->dl_bandwidth);
  PRINT_TLV("  freq", &cc->dl_frequency);
  PRINT_TLV("  dl_k0[0]", &cc->dl_k0[0]);
  PRINT_TLV("  dl_k0[1]", &cc->dl_k0[1]);
  PRINT_TLV("  dl_k0[2]", &cc->dl_k0[2]);
  PRINT_TLV("  dl_k0[3]", &cc->dl_k0[3]);
  PRINT_TLV("  dl_k0[4]", &cc->dl_k0[4]);
  PRINT_TLV("  dl_grid_size[0]", &cc->dl_grid_size[0]);
  PRINT_TLV("  dl_grid_size[1]", &cc->dl_grid_size[1]);
  PRINT_TLV("  dl_grid_size[2]", &cc->dl_grid_size[2]);
  PRINT_TLV("  dl_grid_size[3]", &cc->dl_grid_size[3]);
  PRINT_TLV("  dl_grid_size[4]", &cc->dl_grid_size[4]);
  PRINT_TLV("  num_tx_ant", &cc->num_tx_ant);
  PRINT_TLV("  uplink_bandwidth", &cc->uplink_bandwidth);
  PRINT_TLV("  uplink_frequency", &cc->uplink_frequency);
  PRINT_TLV("  ul_k0[0]", &cc->ul_k0[0]);
  PRINT_TLV("  ul_k0[1]", &cc->ul_k0[1]);
  PRINT_TLV("  ul_k0[2]", &cc->ul_k0[2]);
  PRINT_TLV("  ul_k0[3]", &cc->ul_k0[3]);
  PRINT_TLV("  ul_k0[4]", &cc->ul_k0[4]);
  PRINT_TLV("  ul_grid_size[0]", &cc->ul_grid_size[0]);
  PRINT_TLV("  ul_grid_size[1]", &cc->ul_grid_size[1]);
  PRINT_TLV("  ul_grid_size[2]", &cc->ul_grid_size[2]);
  PRINT_TLV("  ul_grid_size[3]", &cc->ul_grid_size[3]);
  PRINT_TLV("  ul_grid_size[4]", &cc->ul_grid_size[4]);
  PRINT_TLV("  num_rx_ant", &cc->num_rx_ant);
  PRINT_TLV("  frequency_shift_7p5khz", &cc->frequency_shift_7p5khz);

  nfapi_nr_prach_config_t *pc = &config->prach_config;
  printf("prach_config\n");
  PRINT_TLV("  prach_sequence_length", &pc->prach_sequence_length);
  PRINT_TLV("  prach_sub_c_spacing", &pc->prach_sub_c_spacing);
  PRINT_TLV("  restricted_set_config", &pc->restricted_set_config);
  PRINT_TLV("  num_prach_fd_occasions", &pc->num_prach_fd_occasions);
  PRINT_TLV("  prach_ConfigurationIndex", &pc->prach_ConfigurationIndex);
  for (int i = 0; i < pc->num_prach_fd_occasions.value; ++i) {
    nfapi_nr_num_prach_fd_occasions_t *pfdo = &pc->num_prach_fd_occasions_list[i];
    PRINT_TLV("    prach_root_sequence_index", &pfdo->prach_root_sequence_index);
    PRINT_TLV("    num_root_sequences", &pfdo->num_root_sequences);
    PRINT_TLV("    k1", &pfdo->k1);
    PRINT_TLV("    prach_zero_corr_conf", &pfdo->prach_zero_corr_conf);
    PRINT_TLV("    num_unused_root_sequences", &pfdo->num_unused_root_sequences);
  };

  PRINT_TLV("  ssb_per_rach", &pc->ssb_per_rach);
  PRINT_TLV("  prach_multiple_carriers_in_a_band", &pc->prach_multiple_carriers_in_a_band);
```