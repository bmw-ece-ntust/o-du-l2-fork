# OSC Integration by fix P5 message

Start Date: 2024/05/29
Summary: Integrating OSC by fixing the P5 message for improved configuration management and data handling in research projects.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

```c
typedef struct {
  uint32_t config_mask;

  fapi_nr_ue_carrier_config_t carrier_config;
  fapi_nr_cell_config_t cell_config;
  fapi_nr_ssb_config_t ssb_config;
  fapi_nr_ssb_table_t ssb_table;
  fapi_nr_tdd_table_t tdd_table_1;
  fapi_nr_tdd_table_t *tdd_table_2;
  fapi_nr_prach_config_t prach_config;

} fapi_nr_config_request_t;
```

| Category | Parameter | OAI Value | OSC Value | OAI Length | OSC Length |
| --- | --- | --- | --- | --- | --- |
| carrier_config | bw | 40 | 100 | 4097 | 4097 |
|  | freq | 3600120 | 3351000 | 4098 | 4098 |
|  | dl_k0[0] | 0 | 0 | 0 | 0 |
|  | dl_k0[1] | 0 | 0 | 0 | 0 |
|  | dl_k0[2] | 0 | 0 | 0 | 0 |
|  | dl_k0[3] | 0 | 0 | 0 | 0 |
|  | dl_k0[4] | 0 | 0 | 0 | 0 |
|  | dl_grid_size[0] | 0 | 0 | 0 | 0 |
|  | dl_grid_size[1] | 106 | 106 | 4100 | 4100 |
|  | dl_grid_size[2] | 0 | 0 | 0 | 0 |
|  | dl_grid_size[3] | 0 | 0 | 0 | 0 |
|  | dl_grid_size[4] | 0 | 0 | 0 | 0 |
|  | num_tx_ant | 1 | 1 | 4101 | 4101 |
|  | uplink_bandwidth | 40 | 100 | 4102 | 4102 |
|  | uplink_frequency | 3600120 | 3351000 | 4103 | 4103 |
|  | ul_k0[0] | 0 | 0 | 0 | 0 |
|  | ul_k0[1] | 0 | 0 | 0 | 0 |
|  | ul_k0[2] | 0 | 0 | 0 | 0 |
|  | ul_k0[3] | 0 | 0 | 0 | 0 |
|  | ul_k0[4] | 0 | 0 | 0 | 0 |
|  | ul_grid_size[0] | 0 | 0 | 0 | 0 |
|  | ul_grid_size[1] | 106 | 106 | 4105 | 4105 |
|  | ul_grid_size[2] | 0 | 0 | 0 | 0 |
|  | ul_grid_size[3] | 0 | 0 | 0 | 0 |
|  | ul_grid_size[4] | 0 | 0 | 0 | 0 |
|  | num_rx_ant | 1 | 1 | 4106 | 4106 |
|  | frequency_shift_7p5khz | 0 | 0 | 0 | 0 |
| prach_config | prach_sequence_length | 1 | 1 | 4113 | 4113 |
|  | prach_sub_c_spacing | 1 | 1 | 4114 | 4114 |
|  | restricted_set_config | 0 | 0 | 4115 | 4115 |
|  | num_prach_fd_occasions | 1 | 1 | 4116 | 4116 |
|  | prach_ConfigurationIndex | 98 | 88 | 4137 | 4137 |
|  | prach_root_sequence_index | 1 | 0 | 4117 | 4117 |
|  | num_root_sequences | 16 | 1 | 4118 | 4118 |
|  | k1 | 0 | 0 | 4119 | 4119 |
|  | prach_zero_corr_conf | 13 | 4 | 4120 | 4120 |
|  | num_unused_root_sequences | 0 | 0 | 0 | 0 |
|  | ssb_per_rach | 3 | 1 | 4123 | 4123 |
|  | prach_multiple_carriers_in_a_band | 0 | 0 | 0 | 0 |
|  |  | OAI Value |  | OAI Length |  |
| ssb_config | bch_payload | 1 | 1 | 4111 | 4111 |
|  | scs_common | 1 | 1 | 4112 | 4112 |
|  | ss_pbch_power | -25 | -25 | 4110 | 4110 |
| ssb_table | ssb_offset_point_a | 86 | 86 | 4125 | 4125 |
|  | beta_pss | 0 | 0 | 0 | 0 |
|  | ssb_period | 2 | 2 | 4127 | 4127 |
|  | ssb_subcarrier_offset | 0 | 0 | 4128 | 4128 |
|  | MIB | 0 | 0 | 4129 | 4129 |
|  | ssb_mask_list | **-2147483648    0** | 1 0 |  |  |
|  | ssb_beam_id_list | 64 zreos | 64 zreos |  |  |
|  | ss_pbch_multiple_carriers_in_a_band | 0 | 0 |  |  |
|  | multiple_cells_ss_pbch_in_a_carrier | 0 | 0 |  |  |
| tdd_table | tdd_period | 6 | 6 | 0 | 0 |
|  | slot_config | 0 | 0 | 0 | 0 |
| cell_config | frame_duplex_type | 1 | 1 | 4134 | 4134 |
|  | phy_cell_id | 0 | 0 | 4135 | 4135 |
| nfapi_nr_measurement_config_t | rssi_measurement | 1 | 1 | 4109 | 4109 |
| nfapi_nr_nfapi_t | dl_tti_timing_offset | 0 | 0 | 4108 | 4108 |
|  | ul_tti_timing_offset | 0 | 0 | 4136 | 4136 |
|  | ul_dci_timing_offset | 0 | 0 | 0 | 0 |
|  | tx_data_timing_offset | 0 | 0 | 0 | 0 |
|  | p7_pnf_port | 0 | 0 | 0 | 0 |
|  | timing_window | 30 | 30 | 0 | 0 |
|  | timing_info_mode | 3 | 3 | 0 | 0 |
|  | timing_info_period | 10 | 10 | 286 | 286 |
| pmi_list | num_pm_idx | **-1229177848** | 1016871944 | 287 | 287 |
|  | pm_idx | 0 | 0 | 288 | 288 |
|  | numLayers | 2 | 2 |  |  |
|  | num_ant_ports | 4 | 4 |  |  |
|  | weights | 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66 | 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66 |  |  |

# PNF_CONFIG_REQ

| Description (**NFAPI_PNF_PHY_RF_TAG 0x1003**) | OAI Value | OSC Value |
| --- | --- | --- |
| pNfapiMsg->num_tlvs | 0 | 0 |
| pNfapiMsg->pnf_phy_rf_config.number_phy_rf_config_info | 2 | 2 |
| pNfapiMsg->pnf_phy_rf_config.phy_rf_config->phy_config_index | 0 | 0 |
| pNfapiMsg->pnf_phy_rf_config.phy_rf_config->phy_id | 1 | 1 |
| pNfapiMsg->pnf_phy_rf_config.phy_rf_config->rf_config_index | 0 | 0 |

```c
  int ret =  unpack_nr_tlv_list(unpack_fns,
                            sizeof(unpack_fns) / sizeof(unpack_tlv_t),
                            ppReadPackedMsg,
                            end,
                            config,
                            &pNfapiMsg->vendor_extension);
  LOG_I(PHY,"pNfapiMsg->num_tlvs:%d\n",pNfapiMsg->num_tlvs);
  LOG_I(PHY,"pNfapiMsg->pnf_phy_rf_config.number_phy_rf_config_info:%d\n",pNfapiMsg->pnf_phy_rf_config.number_phy_rf_config_info);
  LOG_I(PHY,"pNfapiMsg->pnf_phy_rf_config.phy_rf_config->phy_config_index:%d\n",pNfapiMsg->pnf_phy_rf_config.phy_rf_config->phy_config_index);
  LOG_I(PHY,"pNfapiMsg->pnf_phy_rf_config.phy_rf_config->phy_id:%d\n",pNfapiMsg->pnf_phy_rf_config.phy_rf_config->phy_id);
  LOG_I(PHY,"pNfapiMsg->pnf_phy_rf_config.phy_rf_config->rf_config_index:%d\n",pNfapiMsg->pnf_phy_rf_config.phy_rf_config->rf_config_index);
  return ret;
```

![Untitled](Untitled%2073.png)

# Full Table

[P5 config request](P5%20config%20request%2012110098314381ad9f5ece4e905b7079.csv)

| Struct Name | Member | Description | Value Range |
| --- | --- | --- | --- |
| fapi_nr_ue_carrier_config_t | dl_bandwidth | Carrier bandwidth for DL in MHz | 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 200, 400 |
|  | sl_bandwidth | Carrier bandwidth for SL in MHz | 10, 20, 30, 40 |
|  | dl_frequency | Absolute frequency of DL point A in KHz | 450000 -> 52600000 |
|  | sl_frequency | Absolute frequency of SL point A in KHz |  |
|  | dl_k0 | 𝑘_{0}^{𝜇} for each of the numerologies | 0 -> 23699 |
|  | dl_grid_size | Grid size 𝑁_{𝑔𝑟𝑖𝑑}^{𝑠𝑖𝑧𝑒,𝜇} for each of the numerologies | 0 -> 275 |
|  | num_tx_ant | Number of Tx antennas |  |
|  | uplink_bandwidth | Carrier bandwidth for UL in MHz | 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 200, 400 |
|  | uplink_frequency | Absolute frequency of UL point A in KHz | 450000 -> 52600000 |
|  | ul_k0 | 𝑘0 𝜇 for each of the numerologies | 0 -> 23699 |
|  | ul_grid_size | Grid size 𝑁𝑔𝑟𝑖𝑑 𝑠𝑖𝑧𝑒,𝜇 for each of the numerologies | 0 -> 275 |
|  | sl_grid_size |  | 0 -> 275 |
|  | num_rx_ant |  |  |
|  | frequency_shift_7p5khz | Indicates presence of 7.5KHz frequency shift | 0 = false, 1 = true |
| fapi_nr_cell_config_t | phy_cell_id | Physical Cell ID, 𝑁_{𝐼𝐷}^{𝑐𝑒𝑙𝑙} | 0 -> 1007 |
|  | frame_duplex_type | Frame duplex type | 0 = FDD, 1 = TDD |
| fapi_nr_ssb_config_t | ss_pbch_power | SSB Block Power | TBD (-60..50 dBm) |
|  | bch_payload | Defines option selected for generation of BCH payload | 0, 1, 2 |
|  | scs_common | subcarrierSpacing for common, used for initial access and broadcast message | 0 -> 3 |
| fapi_nr_ssb_table_t | ssb_offset_point_a | Offset of lowest subcarrier of lowest resource block used for SS/PBCH block | 0 -> 2199 |
|  | beta_pss | PSS EPRE to SSS EPRE in a SS/PBCH block | 0 = 0dB |
|  | ssb_period | SSB periodicity in msec | 0: ms5, 1: ms10, 2: ms20, 3: ms40, 4: ms80, 5: ms160 |
|  | ssb_subcarrier_offset | ssbSubcarrierOffset or 𝑘𝑆𝑆𝐵 | 0 -> 31 |
|  | MIB | MIB payload |  |
|  | ssb_mask_list |  |  |
|  | ssb_beam_id_list |  |  |
|  | ss_pbch_multiple_carriers_in_a_band | 0 = disabled, 1 = enabled |  |
|  | multiple_cells_ss_pbch_in_a_carrier | Indicates that multiple cells will be supported in a single carrier | 0 = disabled, 1 = enabled |
| fapi_nr_tdd_table_t | tdd_period_in_slots |  |  |
|  | max_tdd_periodicity_list |  |  |
| fapi_nr_prach_config_t | prach_sequence_length | RACH sequence length | 0 = Long sequence, 1 = Short sequence |
|  | prach_sub_c_spacing | Subcarrier spacing of PRACH | 0: 15 kHz, 1: 30 kHz, 2: 60 kHz, 3: 120 kHz, 4: 1.25 kHz, 5: 5 kHz |
|  | restricted_set_config | PRACH restricted set config | 0: unrestricted, 1: restricted set type A, 2: restricted set type B |
|  | num_prach_fd_occasions | Corresponds to the parameter 𝑀 in [38.211, sec 6.3.3.2] which equals the higher layer parameter msg1FDM | 1, 2, 4, 8 |
|  | num_prach_fd_occasions_list |  |  |
|  | ssb_per_rach | SSB-per-RACH-occasion | 0: 1/8, 1:1/4, 2:1/2, 3:1, 4:2, 5:4, 6:8, 7:16 |
|  | prach_multiple_carriers_in_a_band | 0 = disabled, 1 = enabled |  |

# Force fill at unpack P5

[Try to Fill P5 config.req as OAI](Try%20to%20Fill%20P5%20config%20req%20as%20OAI%2012110098314381a38b03fe3bd29c91a6.md)