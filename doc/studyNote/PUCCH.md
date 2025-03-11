# PUCCH

Tags: UL_TTI

```c
typedef struct
{
  uint16_t rnti;
  uint32_t handle;
  //BWP
  uint16_t bwp_size;
  uint16_t bwp_start;
  uint8_t  subcarrier_spacing;
  uint8_t  cyclic_prefix;

  uint8_t  format_type;
  uint8_t  multi_slot_tx_indicator;
  uint8_t  pi_2bpsk;
  //pucch allocation in freq domain
  uint16_t prb_start;
  uint16_t prb_size;
  //pucch allocation in tome domain
  uint8_t  start_symbol_index;
  uint8_t  nr_of_symbols;
  //hopping info
  uint8_t  freq_hop_flag;
  uint16_t second_hop_prb;
  uint8_t  group_hop_flag;
  uint8_t  sequence_hop_flag;
  uint16_t hopping_id;
  uint16_t initial_cyclic_shift;

  uint16_t data_scrambling_id;
  uint8_t  time_domain_occ_idx;
  uint8_t  pre_dft_occ_idx;
  uint8_t  pre_dft_occ_len;
  //DMRS
  uint8_t  add_dmrs_flag;
  uint16_t dmrs_scrambling_id;
  uint8_t  dmrs_cyclic_shift;

  uint8_t  sr_flag;
  uint8_t  bit_len_harq;
  uint16_t bit_len_csi_part1;
  uint16_t bit_len_csi_part2;

  nfapi_nr_ul_beamforming_t beamforming;

} nfapi_nr_pucch_pdu_t;
```

| Field | OAI Value | OSC Value |
| --- | --- | --- |
| rnti | 48768 |  |
| handle | 0 |  |
| bwp_size | 106 |  |
| bwp_start | 0 |  |
| subcarrier_spacing | 1 |  |
| cyclic_prefix | 0 |  |
| format_type | 0 |  |
| multi_slot_tx_indicator | 0 |  |
| pi_2bpsk | 0 |  |
| prb_start | 0 |  |
| prb_size | 1 |  |
| start_symbol_index | 12 |  |
| nr_of_symbols | 2 |  |
| freq_hop_flag | 1 |  |
| second_hop_prb | 105 |  |
| group_hop_flag | 0 |  |
| sequence_hop_flag | 0 |  |
| hopping_id | 40 |  |
| initial_cyclic_shift | 0 |  |
| data_scrambling_id | 0 |  |
| time_domain_occ_idx | 0 |  |
| pre_dft_occ_idx | 0 |  |
| pre_dft_occ_len | 0 |  |
| add_dmrs_flag | 0 |  |
| dmrs_scrambling_id | 0 |  |
| dmrs_cyclic_shift | 0 |  |
| sr_flag | 0 |  |
| bit_len_harq | 1 |  |
| bit_len_csi_part1 | 0 |  |
| bit_len_csi_part2 | 0 |  |

```c
LOG_I(NFAPI_PNF, "PUCCH:\n");
LOG_I(NFAPI_PNF, "rnti: %d\n", pucch_pdu->rnti);
LOG_I(NFAPI_PNF, "handle: %d\n", pucch_pdu->handle);
LOG_I(NFAPI_PNF, "bwp_size: %d\n", pucch_pdu->bwp_size);
LOG_I(NFAPI_PNF, "bwp_start: %d\n", pucch_pdu->bwp_start);
LOG_I(NFAPI_PNF, "subcarrier_spacing: %d\n", pucch_pdu->subcarrier_spacing);
LOG_I(NFAPI_PNF, "cyclic_prefix: %d\n", pucch_pdu->cyclic_prefix);
LOG_I(NFAPI_PNF, "format_type: %d\n", pucch_pdu->format_type);
LOG_I(NFAPI_PNF, "multi_slot_tx_indicator: %d\n", pucch_pdu->multi_slot_tx_indicator);
LOG_I(NFAPI_PNF, "pi_2bpsk: %d\n", pucch_pdu->pi_2bpsk);
LOG_I(NFAPI_PNF, "prb_start: %d\n", pucch_pdu->prb_start);
LOG_I(NFAPI_PNF, "prb_size: %d\n", pucch_pdu->prb_size);
LOG_I(NFAPI_PNF, "start_symbol_index: %d\n", pucch_pdu->start_symbol_index);
LOG_I(NFAPI_PNF, "nr_of_symbols: %d\n", pucch_pdu->nr_of_symbols);
LOG_I(NFAPI_PNF, "freq_hop_flag: %d\n", pucch_pdu->freq_hop_flag);
LOG_I(NFAPI_PNF, "second_hop_prb: %d\n", pucch_pdu->second_hop_prb);
LOG_I(NFAPI_PNF, "group_hop_flag: %d\n", pucch_pdu->group_hop_flag);
LOG_I(NFAPI_PNF, "sequence_hop_flag: %d\n", pucch_pdu->sequence_hop_flag);
LOG_I(NFAPI_PNF, "hopping_id: %d\n", pucch_pdu->hopping_id);
LOG_I(NFAPI_PNF, "initial_cyclic_shift: %d\n", pucch_pdu->initial_cyclic_shift);
LOG_I(NFAPI_PNF, "data_scrambling_id: %d\n", pucch_pdu->data_scrambling_id);
LOG_I(NFAPI_PNF, "time_domain_occ_idx: %d\n", pucch_pdu->time_domain_occ_idx);
LOG_I(NFAPI_PNF, "pre_dft_occ_idx: %d\n", pucch_pdu->pre_dft_occ_idx);
LOG_I(NFAPI_PNF, "pre_dft_occ_len: %d\n", pucch_pdu->pre_dft_occ_len);
LOG_I(NFAPI_PNF, "add_dmrs_flag: %d\n", pucch_pdu->add_dmrs_flag);
LOG_I(NFAPI_PNF, "dmrs_scrambling_id: %d\n", pucch_pdu->dmrs_scrambling_id);
LOG_I(NFAPI_PNF, "dmrs_cyclic_shift: %d\n", pucch_pdu->dmrs_cyclic_shift);
LOG_I(NFAPI_PNF, "sr_flag: %d\n", pucch_pdu->sr_flag);
LOG_I(NFAPI_PNF, "bit_len_harq: %d\n", pucch_pdu->bit_len_harq);
LOG_I(NFAPI_PNF, "bit_len_csi_part1: %d\n", pucch_pdu->bit_len_csi_part1);
LOG_I(NFAPI_PNF, "bit_len_csi_part2: %d\n", pucch_pdu->bit_len_csi_part2);
```