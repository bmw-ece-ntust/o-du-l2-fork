# ssb_config

```c
typedef struct 
{
  int ss_pbch_power;//SSB Block Power Value: TBD (-60..50 dBm)
  uint8_t  bch_payload;//Defines option selected for generation of BCH payload, see Table 3-13 (v0.0.011 Value: 0: MAC generates the full PBCH payload 1: PHY generates the timing PBCH bits 2: PHY generates the full PBCH payload
  uint8_t  scs_common;//subcarrierSpacing for common, used for initial access and broadcast message. [38.211 sec 4.2] Value:0->3

} fapi_nr_ssb_config_t;
```