# prach_config

```c
typedef struct 
{
  uint8_t prach_sequence_length;//RACH sequence length. Only short sequence length is supported for FR2. [38.211, sec 6.3.3.1] Value: 0 = Long sequence 1 = Short sequence
  uint8_t prach_sub_c_spacing; // Subcarrier spacing of PRACH. [38.211 sec 4.2] Value: 0: 15 kHz 1: 30 kHz 2: 60 kHz 3: 120 kHz
                               // 4: 1.25 kHz 5: 5 kHz
  uint8_t restricted_set_config;//PRACH restricted set config Value: 0: unrestricted 1: restricted set type A 2: restricted set type B
  uint8_t num_prach_fd_occasions;//Corresponds to the parameter 𝑀 in [38.211, sec 6.3.3.2] which equals the higher layer parameter msg1FDM Value: 1,2,4,8
  fapi_nr_num_prach_fd_occasions_t* num_prach_fd_occasions_list;
  uint8_t ssb_per_rach;//SSB-per-RACH-occasion Value: 0: 1/8 1:1/4, 2:1/2 3:1 4:2 5:4, 6:8 7:16
  uint8_t prach_multiple_carriers_in_a_band;//0 = disabled 1 = enabled

} fapi_nr_prach_config_t;
```