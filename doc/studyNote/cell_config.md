# cell_config

```c
typedef struct 
{
  uint8_t phy_cell_id;//Physical Cell ID, 𝑁_{𝐼𝐷}^{𝑐𝑒𝑙𝑙} [38.211, sec 7.4.2.1] Value: 0 ->1007
  uint8_t frame_duplex_type;//Frame duplex type Value: 0 = FDD 1 = TDD

} fapi_nr_cell_config_t;
```