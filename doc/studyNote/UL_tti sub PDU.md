# UL_tti sub PDU

Start Date: 2024/05/03
Summary: The project involves the implementation and integration of various types of uplink TTI PDUs (PRACH, PUSCH, PUCCH, SRS) in a communication system.
Status: Done
Assign: 陳奕全
Tags: Robert Task

<aside>
〰️ 
Robert: UL_TTI.request and DL_TTI.request: avoid big switch, make cp functions for "sub"PDUs (PRACH, ...) -> indicate Robert to integrate in nfapi-fixes

</aside>

src->pdus_list[i].pdu_type

1. PRACH PDU
2. PUSCH PDU
3. PUCCH PDU
4. SRS PDU

```c
  union
  {
    nfapi_nr_prach_pdu_t prach_pdu;
    nfapi_nr_pusch_pdu_t pusch_pdu;
    nfapi_nr_pucch_pdu_t pucch_pdu;
    nfapi_nr_srs_pdu_t srs_pdu;
  };

} nfapi_nr_ul_tti_request_number_of_pdus_t;
```

1. For every PDU

```c
    switch (src->pdus_list[i].pdu_type) {
        case 0: // PRACH PDU
            cp_nr_ul_tti_req_prach_pdu(&src->pdus_list[i].prach_pdu, &dst->pdus_list[i].prach_pdu);
            break;
        case 1: // PUSCH PDU
            cp_nr_ul_tti_req_pusch_pdu(&src->pdus_list[i].pusch_pdu, &dst->pdus_list[i].pusch_pdu);
            break;
        case 2: // PUCCH PDU
            cp_nr_ul_tti_req_pucch_pdu(&src->pdus_list[i].pucch_pdu, &dst->pdus_list[i].pucch_pdu);
            break;
        case 3: // SRS PDU
            cp_nr_ul_tti_req_srs_pdu(&src->pdus_list[i].srs_pdu, &dst->pdus_list[i].srs_pdu);
            break;
    }
```

1. PRACH PDU

```
void cp_nr_ul_tti_req_prach_pdu(const nfapi_nr_prach_pdu_t *src_prach_pdu, nfapi_nr_prach_pdu_t *dst_prach_pdu) {
    dst_prach_pdu->phys_cell_id = src_prach_pdu->phys_cell_id;
    dst_prach_pdu->num_prach_ocas = src_prach_pdu->num_prach_ocas;
    dst_prach_pdu->prach_format = src_prach_pdu->prach_format;
    dst_prach_pdu->num_ra = src_prach_pdu->num_ra;
    dst_prach_pdu->prach_start_symbol = src_prach_pdu->prach_start_symbol;
		dst_prach_pdu->num_cs = src_prach_pdu->num_cs;
		dst_prach_pdu->beamforming.trp_scheme = src_prach_pdu->beamforming.trp_scheme;
		dst_prach_pdu->beamforming.num_prgs = src_prach_pdu->beamforming.num_prgs;
		dst_prach_pdu->beamforming.prg_size = src_prach_pdu->beamforming.prg_size;
		dst_prach_pdu->beamforming.dig_bf_interface = src_prach_pdu->beamforming.dig_bf_interface;
		if(src_prach_pdu->beamforming.num_prgs>0){
	    dst_prach_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx = src_prach_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx;			
    }
}
```

1. PUSCH PDU

```sql
void cp_nr_ul_tti_req_pusch_pdu(const nfapi_nr_pusch_pdu_t *src_pusch_pdu, nfapi_nr_pusch_pdu_t *dst_pusch_pdu) {
    // Copy common fields
    dst_pusch_pdu->pdu_bit_map = src_pusch_pdu->pdu_bit_map;
    dst_pusch_pdu->rnti = src_pusch_pdu->rnti;
    dst_pusch_pdu->handle = src_pusch_pdu->handle;
    dst_pusch_pdu->bwp_size = src_pusch_pdu->bwp_size;
    dst_pusch_pdu->bwp_start = src_pusch_pdu->bwp_start;
    dst_pusch_pdu->subcarrier_spacing = src_pusch_pdu->subcarrier_spacing;
    dst_pusch_pdu->cyclic_prefix = src_pusch_pdu->cyclic_prefix;
    dst_pusch_pdu->target_code_rate = src_pusch_pdu->target_code_rate;
    dst_pusch_pdu->qam_mod_order = src_pusch_pdu->qam_mod_order;
    dst_pusch_pdu->mcs_index = src_pusch_pdu->mcs_index;
    dst_pusch_pdu->mcs_table = src_pusch_pdu->mcs_table;
    dst_pusch_pdu->transform_precoding = src_pusch_pdu->transform_precoding;
    dst_pusch_pdu->data_scrambling_id = src_pusch_pdu->data_scrambling_id;
    dst_pusch_pdu->nrOfLayers = src_pusch_pdu->nrOfLayers;
    dst_pusch_pdu->ul_dmrs_symb_pos = src_pusch_pdu->ul_dmrs_symb_pos;
    dst_pusch_pdu->dmrs_config_type = src_pusch_pdu->dmrs_config_type;
    dst_pusch_pdu->ul_dmrs_scrambling_id = src_pusch_pdu->ul_dmrs_scrambling_id;
    dst_pusch_pdu->pusch_identity = src_pusch_pdu->pusch_identity;
    dst_pusch_pdu->scid = src_pusch_pdu->scid;
    dst_pusch_pdu->num_dmrs_cdm_grps_no_data = src_pusch_pdu->num_dmrs_cdm_grps_no_data;
    dst_pusch_pdu->dmrs_ports = src_pusch_pdu->dmrs_ports;
    dst_pusch_pdu->resource_alloc = src_pusch_pdu->resource_alloc;
    memcpy(dst_pusch_pdu->rb_bitmap, src_pusch_pdu->rb_bitmap, sizeof(src_pusch_pdu->rb_bitmap));
    dst_pusch_pdu->rb_start = src_pusch_pdu->rb_start;
    dst_pusch_pdu->rb_size = src_pusch_pdu->rb_size;
    dst_pusch_pdu->vrb_to_prb_mapping = src_pusch_pdu->vrb_to_prb_mapping;
    dst_pusch_pdu->frequency_hopping = src_pusch_pdu->frequency_hopping;
    dst_pusch_pdu->tx_direct_current_location = src_pusch_pdu->tx_direct_current_location;
    dst_pusch_pdu->uplink_frequency_shift_7p5khz = src_pusch_pdu->uplink_frequency_shift_7p5khz;
    dst_pusch_pdu->start_symbol_index = src_pusch_pdu->start_symbol_index;
    dst_pusch_pdu->nr_of_symbols = src_pusch_pdu->nr_of_symbols;

    // Copy optional data if present
    if (src_pusch_pdu->pdu_bit_map & 0x01) // data 
        memcpy(&dst_pusch_pdu->pusch_data, &src_pusch_pdu->pusch_data, sizeof(nfapi_nr_pusch_data_t));
    if (src_pusch_pdu->pdu_bit_map & 0x10) // UCI
        memcpy(&dst_pusch_pdu->pusch_uci, &src_pusch_pdu->pusch_uci, sizeof(nfapi_nr_pusch_uci_t));
    if (src_pusch_pdu->pdu_bit_map & 0x100){ // PTRS
        // Copy the PUSCH PTRS fields directly
        dst_pusch_pdu->pusch_ptrs.num_ptrs_ports = src_pusch_pdu->pusch_ptrs.num_ptrs_ports;
        dst_pusch_pdu->pusch_ptrs.ptrs_time_density = src_pusch_pdu->pusch_ptrs.ptrs_time_density;
        dst_pusch_pdu->pusch_ptrs.ptrs_freq_density = src_pusch_pdu->pusch_ptrs.ptrs_freq_density;
        dst_pusch_pdu->pusch_ptrs.ul_ptrs_power = src_pusch_pdu->pusch_ptrs.ul_ptrs_power;
        for (int j = 0; j < src_pusch_pdu->pusch_ptrs.num_ptrs_ports; j++) {
            dst_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_port_index = src_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_port_index;
            dst_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_dmrs_port = src_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_dmrs_port;
            dst_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_re_offset = src_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_re_offset;
        }
    }
    if (src_pusch_pdu->pdu_bit_map & 0x1000) // DFTS
        memcpy(&dst_pusch_pdu->dfts_ofdm, &src_pusch_pdu->dfts_ofdm, sizeof(nfapi_nr_dfts_ofdm_t));
				
    dst_pusch_pdu->beamforming.trp_scheme = src_pusch_pdu->beamforming.trp_scheme;
    dst_pusch_pdu->beamforming.num_prgs = src_pusch_pdu->beamforming.num_prgs;
    dst_pusch_pdu->beamforming.prg_size = src_pusch_pdu->beamforming.prg_size;
    dst_pusch_pdu->beamforming.dig_bf_interface = src_pusch_pdu->beamforming.dig_bf_interface;
    if(src_pusch_pdu->beamforming.num_prgs>0)
        dst_pusch_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx = src_pusch_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx;
    
    memcpy(&dst_pusch_pdu->maintenance_parms_v3, &src_pusch_pdu->maintenance_parms_v3, sizeof(nfapi_v3_pdsch_maintenance_parameters_t));
}
```

1. PUCCH PDU

```c
void cp_nr_ul_tti_req_pucch_pdu(const nfapi_nr_pucch_pdu_t *src_pucch_pdu, nfapi_nr_pucch_pdu_t *dst_pucch_pdu) {
    // Copy common fields
    dst_pucch_pdu->rnti = src_pucch_pdu->rnti;
    dst_pucch_pdu->handle = src_pucch_pdu->handle;
    dst_pucch_pdu->bwp_size = src_pucch_pdu->bwp_size;
    dst_pucch_pdu->bwp_start = src_pucch_pdu->bwp_start;
    dst_pucch_pdu->subcarrier_spacing = src_pucch_pdu->subcarrier_spacing;
    dst_pucch_pdu->cyclic_prefix = src_pucch_pdu->cyclic_prefix;
    dst_pucch_pdu->format_type = src_pucch_pdu->format_type;
    dst_pucch_pdu->multi_slot_tx_indicator = src_pucch_pdu->multi_slot_tx_indicator;
    dst_pucch_pdu->pi_2bpsk = src_pucch_pdu->pi_2bpsk;
    dst_pucch_pdu->prb_start = src_pucch_pdu->prb_start;
    dst_pucch_pdu->prb_size = src_pucch_pdu->prb_size;
    dst_pucch_pdu->start_symbol_index = src_pucch_pdu->start_symbol_index;
    dst_pucch_pdu->nr_of_symbols = src_pucch_pdu->nr_of_symbols;
    dst_pucch_pdu->freq_hop_flag = src_pucch_pdu->freq_hop_flag;
    dst_pucch_pdu->second_hop_prb = src_pucch_pdu->second_hop_prb;
    dst_pucch_pdu->group_hop_flag = src_pucch_pdu->group_hop_flag;
    dst_pucch_pdu->sequence_hop_flag = src_pucch_pdu->sequence_hop_flag;
    dst_pucch_pdu->hopping_id = src_pucch_pdu->hopping_id;
    dst_pucch_pdu->initial_cyclic_shift = src_pucch_pdu->initial_cyclic_shift;
    dst_pucch_pdu->data_scrambling_id = src_pucch_pdu->data_scrambling_id;
    dst_pucch_pdu->time_domain_occ_idx = src_pucch_pdu->time_domain_occ_idx;
    dst_pucch_pdu->pre_dft_occ_idx = src_pucch_pdu->pre_dft_occ_idx;
    dst_pucch_pdu->pre_dft_occ_len = src_pucch_pdu->pre_dft_occ_len;
    dst_pucch_pdu->add_dmrs_flag = src_pucch_pdu->add_dmrs_flag;
    dst_pucch_pdu->dmrs_scrambling_id = src_pucch_pdu->dmrs_scrambling_id;
    dst_pucch_pdu->dmrs_cyclic_shift = src_pucch_pdu->dmrs_cyclic_shift;
    dst_pucch_pdu->sr_flag = src_pucch_pdu->sr_flag;
    dst_pucch_pdu->bit_len_harq = src_pucch_pdu->bit_len_harq;
    dst_pucch_pdu->bit_len_csi_part1 = src_pucch_pdu->bit_len_csi_part1;
    dst_pucch_pdu->bit_len_csi_part2 = src_pucch_pdu->bit_len_csi_part2;
    
    dst_pucch_pdu->beamforming.trp_scheme = src_pucch_pdu->beamforming.trp_scheme;
    dst_pucch_pdu->beamforming.num_prgs = src_pucch_pdu->beamforming.num_prgs;
    dst_pucch_pdu->beamforming.prg_size = src_pucch_pdu->beamforming.prg_size;
    dst_pucch_pdu->beamforming.dig_bf_interface = src_pucch_pdu->beamforming.dig_bf_interface;
	
    if(src_pucch_pdu->beamforming.num_prgs>0)
        dst_pucch_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx = src_pucch_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx;
}
```

1. SRS PDU

```c

void cp_nr_ul_tti_req_srs_pdu(const nfapi_nr_srs_pdu_t *src_srs_pdu, nfapi_nr_srs_pdu_t *dst_srs_pdu) {
    dst_srs_pdu->rnti = src_srs_pdu->rnti;
    dst_srs_pdu->handle = src_srs_pdu->handle;
    dst_srs_pdu->bwp_size = src_srs_pdu->bwp_size;
    dst_srs_pdu->bwp_start = src_srs_pdu->bwp_start;
    dst_srs_pdu->subcarrier_spacing = src_srs_pdu->subcarrier_spacing;
    dst_srs_pdu->cyclic_prefix = src_srs_pdu->cyclic_prefix;
    dst_srs_pdu->num_ant_ports = src_srs_pdu->num_ant_ports;
    dst_srs_pdu->num_symbols = src_srs_pdu->num_symbols;
    dst_srs_pdu->num_repetitions = src_srs_pdu->num_repetitions;
    dst_srs_pdu->time_start_position = src_srs_pdu->time_start_position;
    dst_srs_pdu->config_index = src_srs_pdu->config_index;
    dst_srs_pdu->sequence_id = src_srs_pdu->sequence_id;
    dst_srs_pdu->bandwidth_index = src_srs_pdu->bandwidth_index;
    dst_srs_pdu->comb_size = src_srs_pdu->comb_size;
    dst_srs_pdu->comb_offset = src_srs_pdu->comb_offset;
    dst_srs_pdu->cyclic_shift = src_srs_pdu->cyclic_shift;
    dst_srs_pdu->frequency_position = src_srs_pdu->frequency_position;
    dst_srs_pdu->frequency_shift = src_srs_pdu->frequency_shift;
    dst_srs_pdu->frequency_hopping = src_srs_pdu->frequency_hopping;
    dst_srs_pdu->group_or_sequence_hopping = src_srs_pdu->group_or_sequence_hopping;
    dst_srs_pdu->resource_type = src_srs_pdu->resource_type;
    dst_srs_pdu->t_srs = src_srs_pdu->t_srs;
    dst_srs_pdu->t_offset = src_srs_pdu->t_offset;
    //beamforming
    dst_srs_pdu->beamforming.trp_scheme = src_srs_pdu->beamforming.trp_scheme;
    dst_srs_pdu->beamforming.num_prgs = src_srs_pdu->beamforming.num_prgs;
    dst_srs_pdu->beamforming.prg_size = src_srs_pdu->beamforming.prg_size;
    dst_srs_pdu->beamforming.dig_bf_interface = src_srs_pdu->beamforming.dig_bf_interface;
    dst_srs_pdu->beamforming.prgs_list = src_srs_pdu->beamforming.prgs_list;
    if(src_srs_pdu->beamforming.num_prgs>0)
        dst_srs_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx = src_srs_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx;
    
    //srs_parameters_v4
    dst_srs_pdu->srs_parameters_v4.srs_bandwidth_size = src_srs_pdu->srs_parameters_v4.srs_bandwidth_size;
    dst_srs_pdu->srs_parameters_v4.symbol_list->srs_bandwidth_start = src_srs_pdu->srs_parameters_v4.symbol_list->srs_bandwidth_start;
    dst_srs_pdu->srs_parameters_v4.symbol_list->sequence_group = src_srs_pdu->srs_parameters_v4.symbol_list->sequence_group;
    dst_srs_pdu->srs_parameters_v4.symbol_list->sequence_number = src_srs_pdu->srs_parameters_v4.symbol_list->sequence_number;
    dst_srs_pdu->srs_parameters_v4.usage = src_srs_pdu->srs_parameters_v4.usage;
    memcpy(dst_srs_pdu->srs_parameters_v4.report_type, src_srs_pdu->srs_parameters_v4.report_type, sizeof(src_srs_pdu->srs_parameters_v4.report_type));
    dst_srs_pdu->srs_parameters_v4.singular_Value_representation = src_srs_pdu->srs_parameters_v4.singular_Value_representation;
    dst_srs_pdu->srs_parameters_v4.iq_representation = src_srs_pdu->srs_parameters_v4.iq_representation;
    dst_srs_pdu->srs_parameters_v4.prg_size = src_srs_pdu->srs_parameters_v4.prg_size;
    dst_srs_pdu->srs_parameters_v4.num_total_ue_antennas = src_srs_pdu->srs_parameters_v4.num_total_ue_antennas;
    dst_srs_pdu->srs_parameters_v4.ue_antennas_in_this_srs_resource_set = src_srs_pdu->srs_parameters_v4.ue_antennas_in_this_srs_resource_set;
    dst_srs_pdu->srs_parameters_v4.sampled_ue_antennas = src_srs_pdu->srs_parameters_v4.sampled_ue_antennas;
    dst_srs_pdu->srs_parameters_v4.report_scope = src_srs_pdu->srs_parameters_v4.report_scope;
    dst_srs_pdu->srs_parameters_v4.num_ul_spatial_streams_ports = src_srs_pdu->srs_parameters_v4.num_ul_spatial_streams_ports;
    memcpy(dst_srs_pdu->srs_parameters_v4.Ul_spatial_stream_ports, src_srs_pdu->srs_parameters_v4.Ul_spatial_stream_ports, sizeof(src_srs_pdu->srs_parameters_v4.Ul_spatial_stream_ports));
}
```

```c
void cp_nr_ul_tti_req_prach_pdu(const nfapi_nr_prach_pdu_t *src_prach_pdu, nfapi_nr_prach_pdu_t *dst_prach_pdu) {
    dst_prach_pdu->phys_cell_id = src_prach_pdu->phys_cell_id;
    dst_prach_pdu->num_prach_ocas = src_prach_pdu->num_prach_ocas;
    dst_prach_pdu->prach_format = src_prach_pdu->prach_format;
    dst_prach_pdu->num_ra = src_prach_pdu->num_ra;
    dst_prach_pdu->prach_start_symbol = src_prach_pdu->prach_start_symbol;
		dst_prach_pdu->num_cs = src_prach_pdu->num_cs;
		dst_prach_pdu->beamforming.trp_scheme = src_prach_pdu->beamforming.trp_scheme;
		dst_prach_pdu->beamforming.num_prgs = src_prach_pdu->beamforming.num_prgs;
		dst_prach_pdu->beamforming.prg_size = src_prach_pdu->beamforming.prg_size;
		dst_prach_pdu->beamforming.dig_bf_interface = src_prach_pdu->beamforming.dig_bf_interface;
		if(src_prach_pdu->beamforming.num_prgs>0){
	    dst_prach_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx = src_prach_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx;			
    }
}
void cp_nr_ul_tti_req_pusch_pdu(const nfapi_nr_pusch_pdu_t *src_pusch_pdu, nfapi_nr_pusch_pdu_t *dst_pusch_pdu) {
    // Copy common fields
    dst_pusch_pdu->pdu_bit_map = src_pusch_pdu->pdu_bit_map;
    dst_pusch_pdu->rnti = src_pusch_pdu->rnti;
    dst_pusch_pdu->handle = src_pusch_pdu->handle;
    dst_pusch_pdu->bwp_size = src_pusch_pdu->bwp_size;
    dst_pusch_pdu->bwp_start = src_pusch_pdu->bwp_start;
    dst_pusch_pdu->subcarrier_spacing = src_pusch_pdu->subcarrier_spacing;
    dst_pusch_pdu->cyclic_prefix = src_pusch_pdu->cyclic_prefix;
    dst_pusch_pdu->target_code_rate = src_pusch_pdu->target_code_rate;
    dst_pusch_pdu->qam_mod_order = src_pusch_pdu->qam_mod_order;
    dst_pusch_pdu->mcs_index = src_pusch_pdu->mcs_index;
    dst_pusch_pdu->mcs_table = src_pusch_pdu->mcs_table;
    dst_pusch_pdu->transform_precoding = src_pusch_pdu->transform_precoding;
    dst_pusch_pdu->data_scrambling_id = src_pusch_pdu->data_scrambling_id;
    dst_pusch_pdu->nrOfLayers = src_pusch_pdu->nrOfLayers;
    dst_pusch_pdu->ul_dmrs_symb_pos = src_pusch_pdu->ul_dmrs_symb_pos;
    dst_pusch_pdu->dmrs_config_type = src_pusch_pdu->dmrs_config_type;
    dst_pusch_pdu->ul_dmrs_scrambling_id = src_pusch_pdu->ul_dmrs_scrambling_id;
    dst_pusch_pdu->pusch_identity = src_pusch_pdu->pusch_identity;
    dst_pusch_pdu->scid = src_pusch_pdu->scid;
    dst_pusch_pdu->num_dmrs_cdm_grps_no_data = src_pusch_pdu->num_dmrs_cdm_grps_no_data;
    dst_pusch_pdu->dmrs_ports = src_pusch_pdu->dmrs_ports;
    dst_pusch_pdu->resource_alloc = src_pusch_pdu->resource_alloc;
    memcpy(dst_pusch_pdu->rb_bitmap, src_pusch_pdu->rb_bitmap, sizeof(src_pusch_pdu->rb_bitmap));
    dst_pusch_pdu->rb_start = src_pusch_pdu->rb_start;
    dst_pusch_pdu->rb_size = src_pusch_pdu->rb_size;
    dst_pusch_pdu->vrb_to_prb_mapping = src_pusch_pdu->vrb_to_prb_mapping;
    dst_pusch_pdu->frequency_hopping = src_pusch_pdu->frequency_hopping;
    dst_pusch_pdu->tx_direct_current_location = src_pusch_pdu->tx_direct_current_location;
    dst_pusch_pdu->uplink_frequency_shift_7p5khz = src_pusch_pdu->uplink_frequency_shift_7p5khz;
    dst_pusch_pdu->start_symbol_index = src_pusch_pdu->start_symbol_index;
    dst_pusch_pdu->nr_of_symbols = src_pusch_pdu->nr_of_symbols;

    // Copy optional data if present
    if (src_pusch_pdu->pdu_bit_map & 0x01) // data 
        memcpy(&dst_pusch_pdu->pusch_data, &src_pusch_pdu->pusch_data, sizeof(nfapi_nr_pusch_data_t));
    if (src_pusch_pdu->pdu_bit_map & 0x10) // UCI
        memcpy(&dst_pusch_pdu->pusch_uci, &src_pusch_pdu->pusch_uci, sizeof(nfapi_nr_pusch_uci_t));
    if (src_pusch_pdu->pdu_bit_map & 0x100){ // PTRS
        // Copy the PUSCH PTRS fields directly
        dst_pusch_pdu->pusch_ptrs.num_ptrs_ports = src_pusch_pdu->pusch_ptrs.num_ptrs_ports;
        dst_pusch_pdu->pusch_ptrs.ptrs_time_density = src_pusch_pdu->pusch_ptrs.ptrs_time_density;
        dst_pusch_pdu->pusch_ptrs.ptrs_freq_density = src_pusch_pdu->pusch_ptrs.ptrs_freq_density;
        dst_pusch_pdu->pusch_ptrs.ul_ptrs_power = src_pusch_pdu->pusch_ptrs.ul_ptrs_power;
        for (int j = 0; j < src_pusch_pdu->pusch_ptrs.num_ptrs_ports; j++) {
            dst_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_port_index = src_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_port_index;
            dst_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_dmrs_port = src_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_dmrs_port;
            dst_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_re_offset = src_pusch_pdu->pusch_ptrs.ptrs_ports_list[j].ptrs_re_offset;
        }
    }
    if (src_pusch_pdu->pdu_bit_map & 0x1000) // DFTS
        memcpy(&dst_pusch_pdu->dfts_ofdm, &src_pusch_pdu->dfts_ofdm, sizeof(nfapi_nr_dfts_ofdm_t));
				
    dst_pusch_pdu->beamforming.trp_scheme = src_pusch_pdu->beamforming.trp_scheme;
    dst_pusch_pdu->beamforming.num_prgs = src_pusch_pdu->beamforming.num_prgs;
    dst_pusch_pdu->beamforming.prg_size = src_pusch_pdu->beamforming.prg_size;
    dst_pusch_pdu->beamforming.dig_bf_interface = src_pusch_pdu->beamforming.dig_bf_interface;
    if(src_pusch_pdu->beamforming.num_prgs>0)
        dst_pusch_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx = src_pusch_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx;
    
    memcpy(&dst_pusch_pdu->maintenance_parms_v3, &src_pusch_pdu->maintenance_parms_v3, sizeof(nfapi_v3_pdsch_maintenance_parameters_t));
}
void cp_nr_ul_tti_req_pucch_pdu(const nfapi_nr_pucch_pdu_t *src_pucch_pdu, nfapi_nr_pucch_pdu_t *dst_pucch_pdu) {
    // Copy common fields
    dst_pucch_pdu->rnti = src_pucch_pdu->rnti;
    dst_pucch_pdu->handle = src_pucch_pdu->handle;
    dst_pucch_pdu->bwp_size = src_pucch_pdu->bwp_size;
    dst_pucch_pdu->bwp_start = src_pucch_pdu->bwp_start;
    dst_pucch_pdu->subcarrier_spacing = src_pucch_pdu->subcarrier_spacing;
    dst_pucch_pdu->cyclic_prefix = src_pucch_pdu->cyclic_prefix;
    dst_pucch_pdu->format_type = src_pucch_pdu->format_type;
    dst_pucch_pdu->multi_slot_tx_indicator = src_pucch_pdu->multi_slot_tx_indicator;
    dst_pucch_pdu->pi_2bpsk = src_pucch_pdu->pi_2bpsk;
    dst_pucch_pdu->prb_start = src_pucch_pdu->prb_start;
    dst_pucch_pdu->prb_size = src_pucch_pdu->prb_size;
    dst_pucch_pdu->start_symbol_index = src_pucch_pdu->start_symbol_index;
    dst_pucch_pdu->nr_of_symbols = src_pucch_pdu->nr_of_symbols;
    dst_pucch_pdu->freq_hop_flag = src_pucch_pdu->freq_hop_flag;
    dst_pucch_pdu->second_hop_prb = src_pucch_pdu->second_hop_prb;
    dst_pucch_pdu->group_hop_flag = src_pucch_pdu->group_hop_flag;
    dst_pucch_pdu->sequence_hop_flag = src_pucch_pdu->sequence_hop_flag;
    dst_pucch_pdu->hopping_id = src_pucch_pdu->hopping_id;
    dst_pucch_pdu->initial_cyclic_shift = src_pucch_pdu->initial_cyclic_shift;
    dst_pucch_pdu->data_scrambling_id = src_pucch_pdu->data_scrambling_id;
    dst_pucch_pdu->time_domain_occ_idx = src_pucch_pdu->time_domain_occ_idx;
    dst_pucch_pdu->pre_dft_occ_idx = src_pucch_pdu->pre_dft_occ_idx;
    dst_pucch_pdu->pre_dft_occ_len = src_pucch_pdu->pre_dft_occ_len;
    dst_pucch_pdu->add_dmrs_flag = src_pucch_pdu->add_dmrs_flag;
    dst_pucch_pdu->dmrs_scrambling_id = src_pucch_pdu->dmrs_scrambling_id;
    dst_pucch_pdu->dmrs_cyclic_shift = src_pucch_pdu->dmrs_cyclic_shift;
    dst_pucch_pdu->sr_flag = src_pucch_pdu->sr_flag;
    dst_pucch_pdu->bit_len_harq = src_pucch_pdu->bit_len_harq;
    dst_pucch_pdu->bit_len_csi_part1 = src_pucch_pdu->bit_len_csi_part1;
    dst_pucch_pdu->bit_len_csi_part2 = src_pucch_pdu->bit_len_csi_part2;
    
    dst_pucch_pdu->beamforming.trp_scheme = src_pucch_pdu->beamforming.trp_scheme;
    dst_pucch_pdu->beamforming.num_prgs = src_pucch_pdu->beamforming.num_prgs;
    dst_pucch_pdu->beamforming.prg_size = src_pucch_pdu->beamforming.prg_size;
    dst_pucch_pdu->beamforming.dig_bf_interface = src_pucch_pdu->beamforming.dig_bf_interface;
	
    if(src_pucch_pdu->beamforming.num_prgs>0)
        dst_pucch_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx = src_pucch_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx;
}

void cp_nr_ul_tti_req_srs_pdu(const nfapi_nr_srs_pdu_t *src_srs_pdu, nfapi_nr_srs_pdu_t *dst_srs_pdu) {
    dst_srs_pdu->rnti = src_srs_pdu->rnti;
    dst_srs_pdu->handle = src_srs_pdu->handle;
    dst_srs_pdu->bwp_size = src_srs_pdu->bwp_size;
    dst_srs_pdu->bwp_start = src_srs_pdu->bwp_start;
    dst_srs_pdu->subcarrier_spacing = src_srs_pdu->subcarrier_spacing;
    dst_srs_pdu->cyclic_prefix = src_srs_pdu->cyclic_prefix;
    dst_srs_pdu->num_ant_ports = src_srs_pdu->num_ant_ports;
    dst_srs_pdu->num_symbols = src_srs_pdu->num_symbols;
    dst_srs_pdu->num_repetitions = src_srs_pdu->num_repetitions;
    dst_srs_pdu->time_start_position = src_srs_pdu->time_start_position;
    dst_srs_pdu->config_index = src_srs_pdu->config_index;
    dst_srs_pdu->sequence_id = src_srs_pdu->sequence_id;
    dst_srs_pdu->bandwidth_index = src_srs_pdu->bandwidth_index;
    dst_srs_pdu->comb_size = src_srs_pdu->comb_size;
    dst_srs_pdu->comb_offset = src_srs_pdu->comb_offset;
    dst_srs_pdu->cyclic_shift = src_srs_pdu->cyclic_shift;
    dst_srs_pdu->frequency_position = src_srs_pdu->frequency_position;
    dst_srs_pdu->frequency_shift = src_srs_pdu->frequency_shift;
    dst_srs_pdu->frequency_hopping = src_srs_pdu->frequency_hopping;
    dst_srs_pdu->group_or_sequence_hopping = src_srs_pdu->group_or_sequence_hopping;
    dst_srs_pdu->resource_type = src_srs_pdu->resource_type;
    dst_srs_pdu->t_srs = src_srs_pdu->t_srs;
    dst_srs_pdu->t_offset = src_srs_pdu->t_offset;
    //beamforming
    dst_srs_pdu->beamforming.trp_scheme = src_srs_pdu->beamforming.trp_scheme;
    dst_srs_pdu->beamforming.num_prgs = src_srs_pdu->beamforming.num_prgs;
    dst_srs_pdu->beamforming.prg_size = src_srs_pdu->beamforming.prg_size;
    dst_srs_pdu->beamforming.dig_bf_interface = src_srs_pdu->beamforming.dig_bf_interface;
    dst_srs_pdu->beamforming.prgs_list = src_srs_pdu->beamforming.prgs_list;
    if(src_srs_pdu->beamforming.num_prgs>0)
        dst_srs_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx = src_srs_pdu->beamforming.prgs_list->dig_bf_interface_list->beam_idx;
    
    //srs_parameters_v4
    dst_srs_pdu->srs_parameters_v4.srs_bandwidth_size = src_srs_pdu->srs_parameters_v4.srs_bandwidth_size;
    dst_srs_pdu->srs_parameters_v4.symbol_list->srs_bandwidth_start = src_srs_pdu->srs_parameters_v4.symbol_list->srs_bandwidth_start;
    dst_srs_pdu->srs_parameters_v4.symbol_list->sequence_group = src_srs_pdu->srs_parameters_v4.symbol_list->sequence_group;
    dst_srs_pdu->srs_parameters_v4.symbol_list->sequence_number = src_srs_pdu->srs_parameters_v4.symbol_list->sequence_number;
    dst_srs_pdu->srs_parameters_v4.usage = src_srs_pdu->srs_parameters_v4.usage;
    memcpy(dst_srs_pdu->srs_parameters_v4.report_type, src_srs_pdu->srs_parameters_v4.report_type, sizeof(src_srs_pdu->srs_parameters_v4.report_type));
    dst_srs_pdu->srs_parameters_v4.singular_Value_representation = src_srs_pdu->srs_parameters_v4.singular_Value_representation;
    dst_srs_pdu->srs_parameters_v4.iq_representation = src_srs_pdu->srs_parameters_v4.iq_representation;
    dst_srs_pdu->srs_parameters_v4.prg_size = src_srs_pdu->srs_parameters_v4.prg_size;
    dst_srs_pdu->srs_parameters_v4.num_total_ue_antennas = src_srs_pdu->srs_parameters_v4.num_total_ue_antennas;
    dst_srs_pdu->srs_parameters_v4.ue_antennas_in_this_srs_resource_set = src_srs_pdu->srs_parameters_v4.ue_antennas_in_this_srs_resource_set;
    dst_srs_pdu->srs_parameters_v4.sampled_ue_antennas = src_srs_pdu->srs_parameters_v4.sampled_ue_antennas;
    dst_srs_pdu->srs_parameters_v4.report_scope = src_srs_pdu->srs_parameters_v4.report_scope;
    dst_srs_pdu->srs_parameters_v4.num_ul_spatial_streams_ports = src_srs_pdu->srs_parameters_v4.num_ul_spatial_streams_ports;
    memcpy(dst_srs_pdu->srs_parameters_v4.Ul_spatial_stream_ports, src_srs_pdu->srs_parameters_v4.Ul_spatial_stream_ports, sizeof(src_srs_pdu->srs_parameters_v4.Ul_spatial_stream_ports));
}
static void cp_nr_ul_tti_req(nfapi_nr_ul_tti_request_t *dst, const nfapi_nr_ul_tti_request_t *src)
{
    dst->header = src->header;
    dst->SFN = src->SFN;
    dst->Slot = src->Slot;
    dst->n_pdus = src->n_pdus;
    dst->rach_present = src->rach_present;
    dst->n_ulsch = src->n_ulsch;
    dst->n_ulcch = src->n_ulcch;
    dst->n_group = src->n_group;
	// LOG_I(PHY,"cp_nr_ul_tti_req: dst->n_pdus=%d\n", dst->n_pdus);
	for (int i = 0; i < dst->n_pdus; ++i) {
		dst->pdus_list[i].pdu_type = src->pdus_list[i].pdu_type;
		dst->pdus_list[i].pdu_size = src->pdus_list[i].pdu_size;
		switch (src->pdus_list[i].pdu_type) {
			case 0: // PRACH PDU
				cp_nr_ul_tti_req_prach_pdu(&src->pdus_list[i].prach_pdu, &dst->pdus_list[i].prach_pdu);
				break;
			case 1: // PUSCH PDU
				cp_nr_ul_tti_req_pusch_pdu(&src->pdus_list[i].pusch_pdu, &dst->pdus_list[i].pusch_pdu);
				break;
			case 2: // PUCCH PDU
				cp_nr_ul_tti_req_pucch_pdu(&src->pdus_list[i].pucch_pdu, &dst->pdus_list[i].pucch_pdu);
				break;
			case 3: // SRS PDU
				cp_nr_ul_tti_req_srs_pdu(&src->pdus_list[i].srs_pdu, &dst->pdus_list[i].srs_pdu);
				break;
		}
	}
	for (int i = 0; i < dst->n_group; ++i) {
		dst->groups_list[i].n_ue = src->groups_list[i].n_ue;
		for (int j = 0; j < src->groups_list[i].n_ue; ++j) {
			dst->groups_list[i].ue_list[j].pdu_idx = src->groups_list[i].ue_list[j].pdu_idx;
		}
	}
}
```