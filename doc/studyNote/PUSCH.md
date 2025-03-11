# PUSCH

Tags: UL_TTI

```c
typedef struct
{
  uint16_t pdu_bit_map;//Bitmap indicating presence of optional PDUs (see above)
  uint16_t rnti;
  uint32_t handle;//An opaque handling returned in the RxData.indication and/or UCI.indication message
  //BWP
  uint16_t bwp_size;
  uint16_t bwp_start;
  uint8_t  subcarrier_spacing;
  uint8_t  cyclic_prefix;
  //pusch information always include
  uint16_t target_code_rate;
  uint8_t  qam_mod_order;
  uint8_t  mcs_index;
  uint8_t  mcs_table;
  uint8_t  transform_precoding;
  uint16_t data_scrambling_id;
  uint8_t  nrOfLayers;
  //DMRS
  uint16_t  ul_dmrs_symb_pos;
  uint8_t  dmrs_config_type;
  uint16_t ul_dmrs_scrambling_id;
  uint16_t pusch_identity;
  uint8_t  scid;
  uint8_t  num_dmrs_cdm_grps_no_data;
  uint16_t dmrs_ports;//DMRS ports. [TS38.212 7.3.1.1.2] provides description between DCI 0-1 content and DMRS ports. Bitmap occupying the 11 LSBs with: bit 0: antenna port 1000 bit 11: antenna port 1011 and for each bit 0: DMRS port not used 1: DMRS port used
  //Pusch Allocation in frequency domain [TS38.214, sec 6.1.2.2]
  uint8_t  resource_alloc;
  uint8_t  rb_bitmap[36];//
  uint16_t rb_start;
  uint16_t rb_size;
  uint8_t  vrb_to_prb_mapping;
  uint8_t  frequency_hopping;
  uint16_t tx_direct_current_location;//The uplink Tx Direct Current location for the carrier. Only values in the value range of this field between 0 and 3299, which indicate the subcarrier index within the carrier corresponding 1o the numerology of the corresponding uplink BWP and value 3300, which indicates "Outside the carrier" and value 3301, which indicates "Undetermined position within the carrier" are used. [TS38.331, UplinkTxDirectCurrentBWP IE]
  uint8_t  uplink_frequency_shift_7p5khz;
  //Resource Allocation in time domain
  uint8_t  start_symbol_index;
  uint8_t  nr_of_symbols;
  //Optional Data only included if indicated in pduBitmap
  nfapi_nr_pusch_data_t pusch_data;
  nfapi_nr_pusch_uci_t  pusch_uci;
  nfapi_nr_pusch_ptrs_t pusch_ptrs;
  nfapi_nr_dfts_ofdm_t dfts_ofdm;
  //beamforming
  nfapi_nr_ul_beamforming_t beamforming;
  nfapi_v3_pdsch_maintenance_parameters_t maintenance_parms_v3;
} nfapi_nr_pusch_pdu_t;
```

| Field | OAI Value | OSC Value |
| --- | --- | --- |
| pdu_bit_map | 1 |  |
| rnti | 63851 |  |
| handle | 0 |  |
| bwp_size | 106 |  |
| bwp_start | 0 |  |
| subcarrier_spacing | 1 |  |
| cyclic_prefix | 0 |  |
| target_code_rate | 1570 |  |
| qam_mod_order | 2 |  |
| mcs_index | 1 |  |
| mcs_table | 0 |  |
| transform_precoding | 1 |  |
| data_scrambling_id | 0 |  |
| nrOfLayers | 1 |  |
| ul_dmrs_symb_pos | 1024 |  |
| dmrs_config_type | 0 |  |
| ul_dmrs_scrambling_id | 0 |  |
| pusch_identity | 0 |  |
| scid | 0 |  |
| num_dmrs_cdm_grps_no_data | 2 |  |
| dmrs_ports | 1 |  |
| resource_alloc | 1 |  |
| rb_start | 0 |  |
| rb_size | 8 |  |
| vrb_to_prb_mapping | 0 |  |
| frequency_hopping | 0 |  |
| tx_direct_current_location | 0 |  |
| uplink_frequency_shift_7p5khz | 0 |  |
| start_symbol_index | 10 |  |
| nr_of_symbols | 3 |  |
| pusch_data.rv_index | 0 |  |
| pusch_data.harq_process_id | 0 |  |
| pusch_data.new_data_indicator | 1 |  |
| pusch_data.tb_size | 7 |  |
| pusch_data.num_cb | 0 |  |
| maintenance_parms_v3.ldpcBaseGraph | 2 |  |
| maintenance_parms_v3.tbSizeLbrmBytes | 0 |  |

```c
  LOG_I(PHY, "pusch_pdu->pdu_bit_map: %d\n", pusch_pdu->pdu_bit_map);
  LOG_I(PHY, "pusch_pdu->rnti: %d\n", pusch_pdu->rnti);
  LOG_I(PHY, "pusch_pdu->handle: %ld\n", pusch_pdu->handle);
  LOG_I(PHY, "pusch_pdu->bwp_size: %d\n", pusch_pdu->bwp_size);
  LOG_I(PHY, "pusch_pdu->bwp_start: %d\n", pusch_pdu->bwp_start);
  LOG_I(PHY, "pusch_pdu->subcarrier_spacing: %d\n", pusch_pdu->subcarrier_spacing);
  LOG_I(PHY, "pusch_pdu->cyclic_prefix: %d\n", pusch_pdu->cyclic_prefix);
  LOG_I(PHY, "pusch_pdu->target_code_rate: %d\n", pusch_pdu->target_code_rate);
  LOG_I(PHY, "pusch_pdu->qam_mod_order: %d\n", pusch_pdu->qam_mod_order);
  LOG_I(PHY, "pusch_pdu->mcs_index: %d\n", pusch_pdu->mcs_index);
  LOG_I(PHY, "pusch_pdu->mcs_table: %d\n", pusch_pdu->mcs_table);
  LOG_I(PHY, "pusch_pdu->transform_precoding: %d\n", pusch_pdu->transform_precoding);
  LOG_I(PHY, "pusch_pdu->data_scrambling_id: %ld\n", pusch_pdu->data_scrambling_id);
  LOG_I(PHY, "pusch_pdu->nrOfLayers: %d\n", pusch_pdu->nrOfLayers);
  LOG_I(PHY, "pusch_pdu->ul_dmrs_symb_pos: %d\n", pusch_pdu->ul_dmrs_symb_pos);
  LOG_I(PHY, "pusch_pdu->dmrs_config_type: %d\n", pusch_pdu->dmrs_config_type);
  LOG_I(PHY, "pusch_pdu->ul_dmrs_scrambling_id: %ld\n", pusch_pdu->ul_dmrs_scrambling_id);
  LOG_I(PHY, "pusch_pdu->pusch_identity: %ld\n", pusch_pdu->pusch_identity);
  LOG_I(PHY, "pusch_pdu->scid: %d\n", pusch_pdu->scid);
  LOG_I(PHY, "pusch_pdu->num_dmrs_cdm_grps_no_data: %d\n", pusch_pdu->num_dmrs_cdm_grps_no_data);
  LOG_I(PHY, "pusch_pdu->dmrs_ports: %d\n", pusch_pdu->dmrs_ports);
  LOG_I(PHY, "pusch_pdu->resource_alloc: %d\n", pusch_pdu->resource_alloc);
  LOG_I(PHY, "pusch_pdu->rb_start: %d\n", pusch_pdu->rb_start);
  LOG_I(PHY, "pusch_pdu->rb_size: %d\n", pusch_pdu->rb_size);
  LOG_I(PHY, "pusch_pdu->vrb_to_prb_mapping: %d\n", pusch_pdu->vrb_to_prb_mapping);
  LOG_I(PHY, "pusch_pdu->frequency_hopping: %d\n", pusch_pdu->frequency_hopping);
  LOG_I(PHY, "pusch_pdu->tx_direct_current_location: %d\n", pusch_pdu->tx_direct_current_location);
  LOG_I(PHY, "pusch_pdu->uplink_frequency_shift_7p5khz: %d\n", pusch_pdu->uplink_frequency_shift_7p5khz);
  LOG_I(PHY, "pusch_pdu->start_symbol_index: %d\n", pusch_pdu->start_symbol_index);
  LOG_I(PHY, "pusch_pdu->nr_of_symbols: %d\n", pusch_pdu->nr_of_symbols);

  switch (pusch_pdu->pdu_bit_map) {
      case PUSCH_PDU_BITMAP_PUSCH_DATA: {
          LOG_I(PHY, "pusch_pdu->pusch_data.rv_index: %d\n", pusch_pdu->pusch_data.rv_index);
          LOG_I(PHY, "pusch_pdu->pusch_data.harq_process_id: %d\n", pusch_pdu->pusch_data.harq_process_id);
          LOG_I(PHY, "pusch_pdu->pusch_data.new_data_indicator: %d\n", pusch_pdu->pusch_data.new_data_indicator);
          LOG_I(PHY, "pusch_pdu->pusch_data.tb_size: %ld\n", pusch_pdu->pusch_data.tb_size);
          LOG_I(PHY, "pusch_pdu->pusch_data.num_cb: %d\n", pusch_pdu->pusch_data.num_cb);
      } break;

      case PUSCH_PDU_BITMAP_PUSCH_UCI: {
          LOG_I(PHY, "pusch_pdu->pusch_uci.harq_ack_bit_length: %d\n", pusch_pdu->pusch_uci.harq_ack_bit_length);
          LOG_I(PHY, "pusch_pdu->pusch_uci.csi_part1_bit_length: %d\n", pusch_pdu->pusch_uci.csi_part1_bit_length);
          LOG_I(PHY, "pusch_pdu->pusch_uci.csi_part2_bit_length: %d\n", pusch_pdu->pusch_uci.csi_part2_bit_length);
          LOG_I(PHY, "pusch_pdu->pusch_uci.alpha_scaling: %d\n", pusch_pdu->pusch_uci.alpha_scaling);
          LOG_I(PHY, "pusch_pdu->pusch_uci.beta_offset_harq_ack: %d\n", pusch_pdu->pusch_uci.beta_offset_harq_ack);
          LOG_I(PHY, "pusch_pdu->pusch_uci.beta_offset_csi1: %d\n", pusch_pdu->pusch_uci.beta_offset_csi1);
          LOG_I(PHY, "pusch_pdu->pusch_uci.beta_offset_csi2: %d\n", pusch_pdu->pusch_uci.beta_offset_csi2);
      } break;

      case PUSCH_PDU_BITMAP_PUSCH_PTRS: {
          LOG_I(PHY, "pusch_pdu->pusch_ptrs.num_ptrs_ports: %d\n", pusch_pdu->pusch_ptrs.num_ptrs_ports);
          LOG_I(PHY, "pusch_pdu->pusch_ptrs.ptrs_ports_list->ptrs_dmrs_port: %d\n", pusch_pdu->pusch_ptrs.ptrs_ports_list->ptrs_dmrs_port);
          LOG_I(PHY, "pusch_pdu->pusch_ptrs.ptrs_ports_list->ptrs_port_index: %d\n", pusch_pdu->pusch_ptrs.ptrs_ports_list->ptrs_port_index);
          LOG_I(PHY, "pusch_pdu->pusch_ptrs.ptrs_ports_list->ptrs_re_offset: %d\n", pusch_pdu->pusch_ptrs.ptrs_ports_list->ptrs_re_offset);
          LOG_I(PHY, "pusch_pdu->pusch_ptrs.ptrs_time_density: %d\n", pusch_pdu->pusch_ptrs.ptrs_time_density);
          LOG_I(PHY, "pusch_pdu->pusch_ptrs.ptrs_freq_density: %d\n", pusch_pdu->pusch_ptrs.ptrs_freq_density);
          LOG_I(PHY, "pusch_pdu->pusch_ptrs.ul_ptrs_power: %d\n", pusch_pdu->pusch_ptrs.ul_ptrs_power);
      } break;

      case PUSCH_PDU_BITMAP_DFTS_OFDM: {
          LOG_I(PHY, "pusch_pdu->dfts_ofdm.low_papr_group_number: %d\n", pusch_pdu->dfts_ofdm.low_papr_group_number);
          LOG_I(PHY, "pusch_pdu->dfts_ofdm.low_papr_sequence_number: %d\n", pusch_pdu->dfts_ofdm.low_papr_sequence_number);
          LOG_I(PHY, "pusch_pdu->dfts_ofdm.ul_ptrs_sample_density: %d\n", pusch_pdu->dfts_ofdm.ul_ptrs_sample_density);
          LOG_I(PHY, "pusch_pdu->dfts_ofdm.ul_ptrs_time_density_transform_precoding: %d\n", pusch_pdu->dfts_ofdm.ul_ptrs_time_density_transform_precoding);
      } break;

      default: {
          LOG_I(PHY, "Invalid pdu bitmap %d\n", pusch_pdu->pdu_bit_map);
      }
  }

  LOG_I(PHY, "pusch_pdu->maintenance_parms_v3.ldpcBaseGraph: %d\n", pusch_pdu->maintenance_parms_v3.ldpcBaseGraph);
  LOG_I(PHY, "pusch_pdu->maintenance_parms_v3.tbSizeLbrmBytes: %ld\n", pusch_pdu->maintenance_parms_v3.tbSizeLbrmBytes);

```