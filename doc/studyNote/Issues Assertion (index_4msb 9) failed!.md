# Issues: Assertion (index_4msb < 9) failed!

Start Date: 2024/09/09
Summary: Debugging an assertion failure in NR MAC layer related to subcarrier spacing and configuration parameters.
Status: padding
Assign: Ming 咚咚 [銘鴻]

## Sometimes log will failed in here!

| NR_SubcarrierSpacing_kHz30  | 1 |
| --- | --- |
| scs_ssb  | 1 |
| scs_pdcch | 0 |
| min_chan_bw  | 2 |

```
 九  09 09:46:28 [0m[NR_MAC]   NR_SubcarrierSpacing_kHz30 1, scs_ssb 1, scs_pdcch 0, min_chan_bw 2
 九  09 09:46:28 [0m
 九  09 09:46:28 Assertion (index_4msb < 9) failed!
 九  09 09:46:28 In get_type0_PDCCH_CSS_config_parameters() /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_COMMON/nr_mac_common.c:4009
 九  09 09:46:28 38.213 Table 13-3 4 MSB out of range
 九  09 09:46:28 
 九  09 09:46:28 Exiting execution
 九  09 09:46:28 /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_COMMON/nr_mac_common.c:4009 get_type0_PDCCH_CSS_config_parameters() Exiting OAI softmodem: _Assert_Exit_

```

```c
  LOG_I(NR_MAC,"NR_SubcarrierSpacing_kHz30 %d, scs_ssb %d, scs_pdcch %d, min_chan_bw %d\n",(int)NR_SubcarrierSpacing_kHz30,(int)scs_ssb,(int)scs_pdcch,min_channel_bw);

  //  type0-pdcch coreset
  switch( ((int)scs_ssb << 3) | (int)scs_pdcch ){
    case (NR_SubcarrierSpacing_kHz15 << 3) | NR_SubcarrierSpacing_kHz15:
      AssertFatal(index_4msb < 15, "38.213 Table 13-1 4 MSB out of range\n");
      type0_PDCCH_CSS_config->type0_pdcch_ss_mux_pattern = 1;
      type0_PDCCH_CSS_config->num_rbs     = table_38213_13_1_c2[index_4msb];
      type0_PDCCH_CSS_config->num_symbols = table_38213_13_1_c3[index_4msb];
      type0_PDCCH_CSS_config->rb_offset   = table_38213_13_1_c4[index_4msb];
      break;

    case (NR_SubcarrierSpacing_kHz15 << 3) | NR_SubcarrierSpacing_kHz30:
      AssertFatal(index_4msb < 14, "38.213 Table 13-2 4 MSB out of range\n");
      type0_PDCCH_CSS_config->type0_pdcch_ss_mux_pattern = 1;
      type0_PDCCH_CSS_config->num_rbs     = table_38213_13_2_c2[index_4msb];
      type0_PDCCH_CSS_config->num_symbols = table_38213_13_2_c3[index_4msb];
      type0_PDCCH_CSS_config->rb_offset   = table_38213_13_2_c4[index_4msb];
      break;

    case (NR_SubcarrierSpacing_kHz30 << 3) | NR_SubcarrierSpacing_kHz15:
      if((min_channel_bw & bw_5MHz) | (min_channel_bw & bw_10MHz)){
        AssertFatal(index_4msb < 9, "38.213 Table 13-3 4 MSB out of range\n");
        type0_PDCCH_CSS_config->type0_pdcch_ss_mux_pattern = 1;
        type0_PDCCH_CSS_config->num_rbs     = table_38213_13_3_c2[index_4msb];
        type0_PDCCH_CSS_config->num_symbols = table_38213_13_3_c3[index_4msb];
        type0_PDCCH_CSS_config->rb_offset   = table_38213_13_3_c4[index_4msb];
      }else if(min_channel_bw & bw_40MHz){
        AssertFatal(index_4msb < 9, "38.213 Table 13-5 4 MSB out of range\n");
        type0_PDCCH_CSS_config->type0_pdcch_ss_mux_pattern = 1;
        type0_PDCCH_CSS_config->num_rbs     = table_38213_13_5_c2[index_4msb];
        type0_PDCCH_CSS_config->num_symbols = table_38213_13_5_c3[index_4msb];
        type0_PDCCH_CSS_config->rb_offset   = table_38213_13_5_c4[index_4msb];
      }else{ ; }

      break;
```

## work status

```
 九  09 10:39:07 [0m[NR_MAC]   NR_SubcarrierSpacing_kHz30 1, scs_ssb 1, scs_pdcch 1, min_chan_bw 2
 九  09 10:39:07 [0m[NR_MAC]   index_4msb 12, index_4lsb 0, ssb_index 0, ssb_period 1, ssb_offset_point_a 43
```

```bash
 九  09 09:46:28 [0m[NR_MAC]   NR_SubcarrierSpacing_kHz30 1, scs_ssb 1, scs_pdcch 0, min_chan_bw 2

```

```
 九  18 16:40:36 [0m[MAC]   cell barred (0=barred,1=notBarred): 1
 九  18 16:40:36 [0m[MAC]   intra frequency reselection (0=allowed,1=notAllowed): 1
 九  18 16:40:36 [0m[MAC]   half frame bit(extra bits):    0
 九  18 16:40:36 [0m[MAC]   ssb index(extra bits):         0
 九  18 16:40:36 [0m[MAC]   system frame number(6 MSB bits): 44
 九  18 16:40:36 [0m[MAC]   system frame number(with LSB): 180
 九  18 16:40:36 [0m[MAC]   subcarrier spacing (0=15or60, 1=30or120): 1
 九  18 16:40:36 [0m[MAC]   ssb carrier offset(with MSB):  0
 九  18 16:40:36 [0m[MAC]   dmrs type A position (0=pos2,1=pos3): 0
 九  18 16:40:36 [0m[MAC]   controlResourceSetZero: 12
 九  18 16:40:36 [0m[MAC]   searchSpaceZero: 0
```