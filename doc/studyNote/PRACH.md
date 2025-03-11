# PRACH

Tags: UL_TTI

```c
typedef struct
{
  uint16_t phys_cell_id;
  uint8_t  num_prach_ocas;
  // SCF PRACH PDU format field does not consider A1/B1 etc. possibilities
  // We added 9 = A1/B1 10 = A2/B2 11 A3/B3
  uint8_t  prach_format;
  uint8_t  num_ra;
  uint8_t  prach_start_symbol;
  uint16_t num_cs;
  nfapi_nr_ul_beamforming_t beamforming;

} nfapi_nr_prach_pdu_t;
```

| Field | OAI Value | OSC Value |
| --- | --- | --- |
| phys_cell_id | 0 | 0 |
| num_prach_ocas | 3 | 3 |
| prach_format | 5 | 5 |
| num_ra | 0 | 0 |
| prach_start_symbol | 0 | 0 |
| num_cs | 34 | 34 |
| beamforming.num_prgs | 0 | 0 |
| beamforming.prg_size | 0 | 0 |
| beamforming.dig_bf_interface | 0 | 0 |

```c
  LOG_I(PHY, "prach_pdu->phys_cell_id: %d\n", prach_pdu->phys_cell_id);
  LOG_I(PHY, "prach_pdu->num_prach_ocas: %d\n", prach_pdu->num_prach_ocas);
  LOG_I(PHY, "prach_pdu->prach_format: %d\n", prach_pdu->prach_format);
  LOG_I(PHY, "prach_pdu->num_ra: %d\n", prach_pdu->num_ra);
  LOG_I(PHY, "prach_pdu->prach_start_symbol: %d\n", prach_pdu->prach_start_symbol);
  LOG_I(PHY, "prach_pdu->num_cs: %d\n", prach_pdu->num_cs);

  LOG_I(PHY, "prach_pdu->beamforming.num_prgs: %d\n", prach_pdu->beamforming.num_prgs);
  LOG_I(PHY, "prach_pdu->beamforming.prg_size: %d\n", prach_pdu->beamforming.prg_size);
  LOG_I(PHY, "prach_pdu->beamforming.dig_bf_interface: %d\n", prach_pdu->beamforming.dig_bf_interface);

  if (prach_pdu->beamforming.num_prgs > 0) {
      LOG_I(PHY, "Allocating memory for prach_pdu->beamforming.prgs_list\n");
      prach_pdu->beamforming.prgs_list = calloc(prach_pdu->beamforming.num_prgs, sizeof(*prach_pdu->beamforming.prgs_list));
      if (prach_pdu->beamforming.dig_bf_interface > 0) {
          for (int prg_idx = 0; prg_idx < prach_pdu->beamforming.num_prgs; prg_idx++) {
              LOG_I(PHY, "Allocating memory for prach_pdu->beamforming.prgs_list[%d].dig_bf_interface_list\n", prg_idx);
              prach_pdu->beamforming.prgs_list[prg_idx].dig_bf_interface_list =
                  calloc(prach_pdu->beamforming.dig_bf_interface, sizeof(*prach_pdu->beamforming.prgs_list[0].dig_bf_interface_list));
          }
      }
  }

  for (int prg = 0; prg < prach_pdu->beamforming.num_prgs; prg++) {
      for (int digBFInterface = 0; digBFInterface < prach_pdu->beamforming.dig_bf_interface; digBFInterface++) {
          LOG_I(PHY, "prach_pdu->beamforming.prgs_list[%d].dig_bf_interface_list[%d].beam_idx: %d\n", prg, digBFInterface,
                prach_pdu->beamforming.prgs_list[prg].dig_bf_interface_list[digBFInterface].beam_idx);
      }
  }
```

## RACH indication body

```
 七  19 16:06:36 [0m[PHY]   pack_nr_rach_indication_body
 七  19 16:06:36 [0m[PHY]   value->slot_index:19
 七  19 16:06:36 [0m[PHY]   value->phy_cell_id:0
 七  19 16:06:36 [0m[PHY]   value->symbol_index:0
 七  19 16:06:36 [0m[PHY]   value->freq_index:0
 七  19 16:06:36 [0m[PHY]   value->avg_rssi:236
 七  19 16:06:36 [0m[PHY]   value->avg_snr:255
 七  19 16:06:36 [0m[PHY]   value->num_preamble:1
 七  19 16:06:36 [0m[PHY]   value->preamble_list[0].preamble_index:26
 七  19 16:06:36 [0m[PHY]   value->preamble_list[0].timing_advance:0
 七  19 16:06:36 [0m[PHY]   value->preamble_list[0].preamble_pwr:-1
```

| param | OAI value | OSC value |
| --- | --- | --- |
| value->slot_index | 19 | 19 |
| value->phy_cell_id | 0 | 0 |
| value->symbol_index | 0 | 0 |
| value->freq_index | 0 | 0 |
| value->avg_rssi | 236 | 236 |
| value->avg_snr | 255 | 255 |
| value->num_preamble | 1 | 1 |
| value->preamble_list[0].preamble_index | 52 | 26 |
| value->preamble_list[0].timing_advance | 0 | 0 |
| value->preamble_list[0].preamble_pwr | -1 | -1 |