# Try to force fill P5 all message at unpack

Start Date: 2024/06/04
Summary: Force fill P5 all message at unpack with carrier and cell configuration details.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

[](P5%20config%20request%2012110098314381ad9f5ece4e905b7079.md) 

[OSC Integration by fix P5 message](OSC%20Integration%20by%20fix%20P5%20message%20121100983143818faab3ecfcbb67dac6.md) 

[Try to dump the full P5 config request message](Try%20to%20dump%20the%20full%20P5%20config%20request%20message%2012110098314381c4a6b4c24fd2fe3881.md) 

| Field | OAI Value | OSC Value |
| --- | --- | --- |
| **carrier_config.dl_bandwidth** | 40 | 100 |
| carrier_config.dl_frequency | 3600120 |  |
| carrier_config.dl_grid_size[1] | 106 |  |
| carrier_config.dl_k0[1] | 0 |  |
| carrier_config.num_tx_ant | 1 |  |
| carrier_config.uplink_bandwidth | 40 | 100 |
| carrier_config.uplink_frequency | 3600120 |  |
| carrier_config.ul_grid_size[1] | 106 |  |
| carrier_config.ul_k0[1] | 0 |  |
| carrier_config.num_rx_ant | 1 |  |
| carrier_config.frequency_shift_7p5khz | 0 |  |
| cell_config.phy_cell_id | 0 |  |
| cell_config.frame_duplex_type | 1 |  |
| ssb_config.ss_pbch_power | -25 |  |
| ssb_config.bch_payload | 1 |  |
| ssb_config.scs_common | 1 |  |
| prach_config.prach_sequence_length | 1 |  |
| prach_config.prach_sub_c_spacing | 1 |  |
| prach_config.restricted_set_config | 0 |  |
| prach_config.num_prach_fd_occasions | 1 |  |
| prach_config.prach_ConfigurationIndex | 98 |  |
| prach_config.num_prach_fd_occasions_list[0].prach_root_sequence_index | 1 |  |
| prach_config.num_prach_fd_occasions_list[0].num_root_sequences | 16 |  |
| prach_config.num_prach_fd_occasions_list[0].k1 | 0 |  |
| prach_config.num_prach_fd_occasions_list[0].prach_zero_corr_conf | 13 |  |
| prach_config.num_prach_fd_occasions_list[0].num_unused_root_sequences | 0 |  |
| prach_config.ssb_per_rach | 3 |  |
| prach_config.prach_multiple_carriers_in_a_band | 0 |  |
| ssb_table.ssb_offset_point_a | 86 |  |
| ssb_table.beta_pss | 0 |  |
| ssb_table.ssb_period | 2 |  |
| ssb_table.ssb_subcarrier_offset | 0 |  |
| ssb_table.MIB | 0 |  |
| ssb_table.ssb_mask_list[0].ssb_mask | -2147483648 |  |
| ssb_table.ssb_beam_id_list[0].beam_id | 0 |  |
| ssb_table.ss_pbch_multiple_carriers_in_a_band | 0 |  |
| ssb_table.multiple_cells_ss_pbch_in_a_carrier | 0 |  |
| tdd_table.tdd_period | 6 |  |
| tdd_table.max_tdd_periodicity_list[0].max_num_of_symbol_per_slot_list[0].slot_config | 0 |  |
| measurement_config.rssi_measurement | 1 |  |
| nfapi_config.p7_vnf_address_ipv4 | a73c3b94 |  |
| nfapi_config.p7_vnf_address_ipv6 | a73c3b9c |  |
| nfapi_config.p7_vnf_port | 50011 |  |
| nfapi_config.timing_window | 30 |  |
| nfapi_config.timing_info_mode | 3 |  |
| nfapi_config.timing_info_period | 10 |  |
| nfapi_config.p7_pnf_address_ipv6 |  |  |
| nfapi_config.p7_pnf_port | 0 |  |
| num_tlv | 247 |  |

# Dump function at unpack

```c
 LOG_I(PHY,"pNfapiMsg->carrier_config.dl_bandwidth: %d\n", pNfapiMsg->carrier_config.dl_bandwidth.value);
  LOG_I(PHY,"pNfapiMsg->carrier_config.dl_frequency: %d\n", pNfapiMsg->carrier_config.dl_frequency.value);
  for(int i=0;i<5;i++)
  LOG_I(PHY,"pNfapiMsg->carrier_config.dl_grid_size[5]: %d\n", pNfapiMsg->carrier_config.dl_grid_size[i].value);
  for(int i=0;i<5;i++)
  LOG_I(PHY,"pNfapiMsg->carrier_config.dl_k0[5]: %d\n", pNfapiMsg->carrier_config.dl_k0[i].value);
  LOG_I(PHY,"pNfapiMsg->carrier_config.num_tx_ant: %d\n", pNfapiMsg->carrier_config.num_tx_ant.value);
  LOG_I(PHY,"pNfapiMsg->carrier_config.uplink_bandwidth: %d\n", pNfapiMsg->carrier_config.uplink_bandwidth.value);
  LOG_I(PHY,"pNfapiMsg->carrier_config.uplink_frequency: %d\n", pNfapiMsg->carrier_config.uplink_frequency.value);
  for(int i=0;i<5;i++)
  LOG_I(PHY,"pNfapiMsg->carrier_config.ul_grid_size[5]: %d\n", pNfapiMsg->carrier_config.ul_grid_size[i].value);
  for(int i=0;i<5;i++)
  LOG_I(PHY,"pNfapiMsg->carrier_config.ul_k0[5]: %d\n", pNfapiMsg->carrier_config.ul_k0[i].value);
  LOG_I(PHY,"pNfapiMsg->carrier_config.num_rx_ant: %d\n", pNfapiMsg->carrier_config.num_rx_ant.value);
  LOG_I(PHY,"pNfapiMsg->carrier_config.frequency_shift_7p5khz: %d\n", pNfapiMsg->carrier_config.frequency_shift_7p5khz.value);
  LOG_I(PHY,"pNfapiMsg->cell_config.phy_cell_id: %d\n", pNfapiMsg->cell_config.phy_cell_id.value);
  LOG_I(PHY,"pNfapiMsg->cell_config.frame_duplex_type: %d\n", pNfapiMsg->cell_config.frame_duplex_type.value);
  LOG_I(PHY,"pNfapiMsg->ssb_config.ss_pbch_power: %d\n", pNfapiMsg->ssb_config.ss_pbch_power.value);
  LOG_I(PHY,"pNfapiMsg->ssb_config.bch_payload: %d\n", pNfapiMsg->ssb_config.bch_payload.value);
  LOG_I(PHY,"pNfapiMsg->ssb_config.scs_common: %d\n", pNfapiMsg->ssb_config.scs_common.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.prach_sequence_length: %d\n", pNfapiMsg->prach_config.prach_sequence_length.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.prach_sub_c_spacing: %d\n", pNfapiMsg->prach_config.prach_sub_c_spacing.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.restricted_set_config: %d\n", pNfapiMsg->prach_config.restricted_set_config.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.num_prach_fd_occasions: %d\n", pNfapiMsg->prach_config.num_prach_fd_occasions.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.prach_ConfigurationIndex: %d\n", pNfapiMsg->prach_config.prach_ConfigurationIndex.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].prach_root_sequence_index: %d\n", pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].prach_root_sequence_index.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].num_root_sequences: %d\n", pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].num_root_sequences.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].k1: %d\n", pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].k1.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].prach_zero_corr_conf: %d\n", pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].prach_zero_corr_conf.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].num_unused_root_sequences: %d\n", pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].num_unused_root_sequences.value);
  if(pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].unused_root_sequences_list)
  LOG_I(PHY,"pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].unused_root_sequences_list[0]: %d\n", pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].unused_root_sequences_list[0].value);
  LOG_I(PHY,"pNfapiMsg->prach_config.ssb_per_rach: %d\n", pNfapiMsg->prach_config.ssb_per_rach.value);
  LOG_I(PHY,"pNfapiMsg->prach_config.prach_multiple_carriers_in_a_band: %d\n", pNfapiMsg->prach_config.prach_multiple_carriers_in_a_band.value);
  LOG_I(PHY,"pNfapiMsg->ssb_table.ssb_offset_point_a: %d\n", pNfapiMsg->ssb_table.ssb_offset_point_a.value);
  LOG_I(PHY,"pNfapiMsg->ssb_table.beta_pss: %d\n", pNfapiMsg->ssb_table.beta_pss.value);
  LOG_I(PHY,"pNfapiMsg->ssb_table.ssb_period: %d\n", pNfapiMsg->ssb_table.ssb_period.value);
  LOG_I(PHY,"pNfapiMsg->ssb_table.ssb_subcarrier_offset: %d\n", pNfapiMsg->ssb_table.ssb_subcarrier_offset.value);
  LOG_I(PHY,"pNfapiMsg->ssb_table.MIB: %d\n", pNfapiMsg->ssb_table.MIB.value);
  for(int i=0;i<2;i++)
  LOG_I(PHY,"pNfapiMsg->ssb_table.ssb_mask_list[2].ssb_mask: %d\n", pNfapiMsg->ssb_table.ssb_mask_list[i].ssb_mask.value);
  LOG_I(PHY,"pNfapiMsg->ssb_table.ssb_beam_id_list[64].beam_id: %d\n", pNfapiMsg->ssb_table.ssb_beam_id_list[0].beam_id.value);
  LOG_I(PHY,"pNfapiMsg->ssb_table.ss_pbch_multiple_carriers_in_a_band: %d\n", pNfapiMsg->ssb_table.ss_pbch_multiple_carriers_in_a_band.value);
  LOG_I(PHY,"pNfapiMsg->ssb_table.multiple_cells_ss_pbch_in_a_carrier: %d\n", pNfapiMsg->ssb_table.multiple_cells_ss_pbch_in_a_carrier.value);
  LOG_I(PHY,"pNfapiMsg->tdd_table.tdd_period: %d\n", pNfapiMsg->tdd_table.tdd_period.value);
  LOG_I(PHY,"pNfapiMsg->tdd_table.max_tdd_periodicity_list[0].max_num_of_symbol_per_slot_list[0].slot_config: %d\n", pNfapiMsg->tdd_table.max_tdd_periodicity_list[0].max_num_of_symbol_per_slot_list[0].slot_config.value);
  LOG_I(PHY,"pNfapiMsg->measurement_config.rssi_measurement: %d\n", pNfapiMsg->measurement_config.rssi_measurement.value);
  LOG_I(PHY,"pNfapiMsg->nfapi_config.p7_vnf_address_ipv4: %x\n", pNfapiMsg->nfapi_config.p7_vnf_address_ipv4.address);
  LOG_I(PHY,"pNfapiMsg->nfapi_config.p7_vnf_address_ipv6: %x\n", pNfapiMsg->nfapi_config.p7_vnf_address_ipv6.address);
  LOG_I(PHY,"pNfapiMsg->nfapi_config.p7_vnf_port: %d\n", pNfapiMsg->nfapi_config.p7_vnf_port.value);
  LOG_I(PHY,"pNfapiMsg->nfapi_config.timing_window: %d\n", pNfapiMsg->nfapi_config.timing_window.value);
  LOG_I(PHY,"pNfapiMsg->nfapi_config.timing_info_mode: %d\n", pNfapiMsg->nfapi_config.timing_info_mode.value);
  LOG_I(PHY,"pNfapiMsg->nfapi_config.timing_info_period: %d\n", pNfapiMsg->nfapi_config.timing_info_period.value);
  LOG_I(PHY,"pNfapiMsg->nfapi_config.p7_pnf_address_ipv6: %s\n", pNfapiMsg->nfapi_config.p7_pnf_address_ipv6.address);
  LOG_I(PHY,"pNfapiMsg->nfapi_config.p7_pnf_port: %d\n", pNfapiMsg->nfapi_config.p7_pnf_port.value);
  LOG_I(PHY,"pNfapiMsg->num_tlv: %d\n", pNfapiMsg->num_tlv);
```

# Force assign value

```c
  pNfapiMsg->carrier_config.dl_bandwidth.value = 40;
  pNfapiMsg->carrier_config.dl_frequency.value = 3600120;
  pNfapiMsg->carrier_config.dl_grid_size[1].value = 106;
  pNfapiMsg->carrier_config.dl_k0[1].value = 0;
  pNfapiMsg->carrier_config.num_tx_ant.value = 1;
  pNfapiMsg->carrier_config.uplink_bandwidth.value = 40;
  pNfapiMsg->carrier_config.uplink_frequency.value = 3600120;
  pNfapiMsg->carrier_config.ul_grid_size[1].value = 106;
  pNfapiMsg->carrier_config.ul_k0[1].value = 0;
  pNfapiMsg->carrier_config.num_rx_ant.value = 1;
  pNfapiMsg->carrier_config.frequency_shift_7p5khz.value = 0;
  pNfapiMsg->cell_config.phy_cell_id.value = 0;
  pNfapiMsg->cell_config.frame_duplex_type.value = 1;
  pNfapiMsg->ssb_config.ss_pbch_power.value = -25;
  pNfapiMsg->ssb_config.bch_payload.value = 1;
  pNfapiMsg->ssb_config.scs_common.value = 1;
  pNfapiMsg->prach_config.prach_sequence_length.value = 1;
  pNfapiMsg->prach_config.prach_sub_c_spacing.value = 1;
  pNfapiMsg->prach_config.restricted_set_config.value = 0;
  pNfapiMsg->prach_config.num_prach_fd_occasions.value = 1;
  pNfapiMsg->prach_config.prach_ConfigurationIndex.value = 98;
  pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].prach_root_sequence_index.value = 1;
  pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].num_root_sequences.value = 16;
  pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].k1.value = 0;
  pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].prach_zero_corr_conf.value = 13;
  pNfapiMsg->prach_config.num_prach_fd_occasions_list[0].num_unused_root_sequences.value = 0;
  pNfapiMsg->prach_config.ssb_per_rach.value = 3;
  pNfapiMsg->prach_config.prach_multiple_carriers_in_a_band.value = 0;
  pNfapiMsg->ssb_table.ssb_offset_point_a.value = 86;
  pNfapiMsg->ssb_table.beta_pss.value = 0;
  pNfapiMsg->ssb_table.ssb_period.value = 2;
  pNfapiMsg->ssb_table.ssb_subcarrier_offset.value = 0;
  pNfapiMsg->ssb_table.MIB.value = 0;
  pNfapiMsg->ssb_table.ssb_mask_list[0].ssb_mask.value = -2147483648;
  pNfapiMsg->ssb_table.ssb_beam_id_list[0].beam_id.value = 0;
  pNfapiMsg->ssb_table.ss_pbch_multiple_carriers_in_a_band.value = 0;
  pNfapiMsg->ssb_table.multiple_cells_ss_pbch_in_a_carrier.value = 0;
  pNfapiMsg->tdd_table.tdd_period.value = 6;
  pNfapiMsg->tdd_table.max_tdd_periodicity_list[0].max_num_of_symbol_per_slot_list[0].slot_config.value = 0;
  pNfapiMsg->measurement_config.rssi_measurement.value = 1;
  pNfapiMsg->nfapi_config.timing_window.value = 30;
  pNfapiMsg->nfapi_config.timing_info_mode.value = 3;
  pNfapiMsg->nfapi_config.timing_info_period.value = 10;
  pNfapiMsg->num_tlv = 247;
```