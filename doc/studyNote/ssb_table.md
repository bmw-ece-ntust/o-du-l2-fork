# ssb_table

```c
typedef struct 
{
  uint16_t ssb_offset_point_a;//Offset of lowest subcarrier of lowest resource block used for SS/PBCH block. Given in PRB [38.211, section 4.4.4.2] Value: 0->2199
  uint8_t  beta_pss;//PSS EPRE to SSS EPRE in a SS/PBCH block [38.213, sec 4.1] Values: 0 = 0dB
  uint8_t  ssb_period;//SSB periodicity in msec Value: 0: ms5 1: ms10 2: ms20 3: ms40 4: ms80 5: ms160
  uint8_t  ssb_subcarrier_offset;//ssbSubcarrierOffset or 𝑘𝑆𝑆𝐵 (38.211, section 7.4.3.1) Value: 0->31
  uint32_t MIB;//MIB payload, where the 24 MSB are used and represent the MIB in [38.331 MIB IE] and represent 0 1 2 3 1 , , , ,..., A− a a a a a [38.212, sec 7.1.1]
  fapi_nr_ssb_mask_size_2_t ssb_mask_list[2];
  fapi_nr_ssb_mask_size_64_t* ssb_beam_id_list;//64
  uint8_t  ss_pbch_multiple_carriers_in_a_band;//0 = disabled 1 = enabled
  uint8_t  multiple_cells_ss_pbch_in_a_carrier;//Indicates that multiple cells will be supported in a single carrier 0 = disabled 1 = enabled

} fapi_nr_ssb_table_t;
```