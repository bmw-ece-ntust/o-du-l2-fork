# OAI UE MSG3

Start Date: 2024/07/23
Summary: The project involves the development and analysis of the RACH Msg3 process in a mobile communication context.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全

# What the context of MSG3

<aside>
💡 Reference:
https://www.telecomhall.net/t/what-content-is-sent-in-msg3-during-nr-rach-in-endc/13074/23
https://www.etsi.org/deliver/etsi_ts/138300_138399/138321/15.06.00_60/ts_138321v150600p.pdf
https://hackmd.io/@YTL0307/BkQNhKxUs#CRC-Cyclic-Redundancy-Check

</aside>

- The UE sends the RACH Msg3 containing the 48-bit Contention Resolution ID (CRID)
- **Content of the RRC Connection Request (MSG3)**:
    - **UE Identity**: A temporary identity or a pre-configured identity.

### 

![Untitled](Untitled%20101.png)

## CRC

![Untitled](Untitled%20102.png)

![Untitled](Untitled%20103.png)

```c
void print_RA_config(RA_config_t *ra) {
    LOG_I(PHY, "cfra: %u\n", ra->cfra);
    LOG_I(PHY, "RA_offset: %u\n", ra->RA_offset);
    LOG_I(PHY, "ra_rnti: %u\n", ra->ra_rnti);
    LOG_I(PHY, "t_crnti: %u\n", ra->t_crnti);
    LOG_I(PHY, "RA_attempt_number: %u\n", ra->RA_attempt_number);
    LOG_I(PHY, "RA_active: %s\n", ra->RA_active ? "true" : "false");
    LOG_I(PHY, "ra_PreambleIndex: %d\n", ra->ra_PreambleIndex);
    LOG_I(PHY, "ssb_nb_in_ro: %u\n", ra->ssb_nb_in_ro);
    LOG_I(PHY, "RA_window_cnt: %d\n", ra->RA_window_cnt);
    LOG_I(PHY, "RA_RAPID_found: %u\n", ra->RA_RAPID_found);
    LOG_I(PHY, "RA_BI_found: %u\n", ra->RA_BI_found);
    LOG_I(PHY, "RA_backoff_indicator: %d\n", ra->RA_backoff_indicator);
    LOG_I(PHY, "RA_usedGroupA: %u\n", ra->RA_usedGroupA);
    LOG_I(PHY, "RA_backoff_cnt: %d\n", ra->RA_backoff_cnt);
    LOG_I(PHY, "preambleTransMax: %d\n", ra->preambleTransMax);
    LOG_I(PHY, "cb_preambles_per_ssb: %ld\n", ra->cb_preambles_per_ssb);
    LOG_I(PHY, "starting_preamble_nb: %d\n", ra->starting_preamble_nb);
    LOG_I(PHY, "Msg3_TPC: %d\n", ra->Msg3_TPC);
    LOG_I(PHY, "first_Msg3: %s\n", ra->first_Msg3 ? "true" : "false");
    LOG_I(PHY, "Msg3_size: %u\n", ra->Msg3_size);
    LOG_I(PHY, "Msg3_buffer: %p\n", ra->Msg3_buffer);
    LOG_I(PHY, "msg3_C_RNTI: %s\n", ra->msg3_C_RNTI ? "true" : "false");
}

```

```c
static uint8_t *fill_msg3_pdu_from_rlc(NR_UE_MAC_INST_t *mac, uint8_t *pdu, int TBS_max)
{
  RA_config_t *ra = &mac->ra;
```

| Parameter | OAI Value | OSC Value |
| --- | --- | --- |
| len | 6 | 6 |
| cfra | 0 | 0 |
| RA_offset | 2 | 2 |
| ra_rnti | 267 | 267 |
| t_crnti | 49489 (random) | 100 |
| RA_attempt_number | 1 | 1 |
| RA_active | true | true |
| ra_PreambleIndex | 57 (random) | 15 |
| ssb_nb_in_ro | 0 | 0 |
| RA_window_cnt | 57 | 57 |
| RA_RAPID_found | 1 | 1 |
| RA_BI_found | 1 | 0 |
| RA_backoff_indicator | 5 | 0 |
| RA_usedGroupA | 1 | 1 |
| RA_backoff_cnt | 0 | 0 |
| preambleTransMax | 10 | 10 |
| cb_preambles_per_ssb | 60 | 60 |
| starting_preamble_nb | 0 | 0 |
| Msg3_TPC | 0 | 0 |
| first_Msg3 | true | true |
| Msg3_size | 0 | 0 |
| Msg3_buffer | (nil) | (nil) |
| msg3_C_RNTI | false | false |

![Untitled](Untitled%2041.png)

```c
# OSC buffer:
Msg3 buffer: 34 1A 2A F3 AF C1 46 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 3F 00 
# OAI buffer:
Msg3 buffer: 34 1F 1D 8A 17 77 A6 
```

```c
 # OSC
 七  23 21:43:39 [0m[NR_MAC]   harq_id 0, new_data_indicator 1, TBS_bytes 36 (ra_state 2)
# OAI
juil. 23 15:38:14 [0m[NR_MAC]   harq_id 0, new_data_indicator 1, TBS_bytes 7 (ra_state 2)
```

## In **`nr_config_pusch_pdu`**

`openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c`

| Parameter | OAI Value | OSC Value |
| --- | --- | --- |
| pusch_data.tb_size | 7 | 36 |
| qam_mod_order | 2 | 2 |
| R | 1570 | 1570 |
| rb_size | 8 | 8 |
| nr_of_symbols | 3 | 13 |
| nb_dmrs_re_per_rb | 12 | 12 |
| number_dmrs_symbols | 1 | 3 |
| N_PRB_oh | 0 | 0 |
| nrOfLayers | 1 | 1 |
| TBS | 7 | 36 |

```c
    pusch_config_pdu->nr_of_symbols = tda_info->nrOfSymbols;

```

## ra->Msg3_buffer

```bash
# OSC payload
34 1F 23 96 0D 7B 66
34 1D 69 EB B7 D2 E6 
34 1C FB 35 37 9F C6 
# OAI payload
34 1F 1D 8A 17 77 A6 
34 15 32 B3 7E 39 66 
34 11 9D 66 05 32 A6 
34 19 97 26 A5 9C 46 
```

## By Robert comment

check slot and PRB is correct → apply following two patch files:

[patch2.patch](patch2.patch)

[ul.patch](ul.patch)

**[184.12]: [UE 0] Received RAR with t_alloc**

| Parameter | Value |
| --- | --- |
| t_alloc | 0 |
| f_alloc | 742 |
| mcs | 1 |
| freq_hopping | 0 |
| tpc_command | 3 |

t_alloc should be 3 is correct → [RAR PDU](RAR%20PDU%20121100983143813f9531d126bef7e972.md) 

|  | OAI value | OSC value |
| --- | --- | --- |
| 9o0ooFoo9HF | 0 | 0 |
| Freq allocation | 742 | 720 |
| Time allocation | 3 | 0 |
| MCS | 1 | 1 |
| TPC | 3 | 3 |
| CSI | 0 | 0 |

UL transmission in [0184.19]

| Parameter | Value |
| --- | --- |
| k2 | 4 |
| delta | 3 |

**MSG3**

| Parameter | Value |
| --- | --- |
| start_sym | 10 |
| NR Symb | 3 |
| mappingtype | 1 |
| DMRS_MASK | 400 |

**Received UL grant**

| Parameter | Value |
| --- | --- |
| rb_start | 0 |
| rb_size | 8 |
| start_symbol_index | 10 |
| nr_of_symbols | 3 |
| RNTI Type | TYPE_TC_RNTI |

---

## Check what data send by MSG3

RA-Msg3 transmitted

`nr_get_msg3_payload`

```c
  if (ra->msg3_C_RNTI)
    pdu = fill_msg3_crnti_pdu(ra, pdu, mac->crnti);
  else 
    pdu = fill_msg3_pdu_from_rlc(mac, pdu, TBS_max);

```

`fill_msg3_pdu_from_rlc`

`nr_config_pusch_pdu`

`nr_ue_process_rar`

MSG3 return TC-RNTI

```
juil. 26 14:52:53 [0m[MAC]   Returning rnti_type TYPE_TC_RNTI_ 
juil. 26 14:52:53 [0m[NR_MAC]   MSG3 start_sym:10 NR Symb:3 mappingtype:1, DMRS_MASK:400
juil. 26 14:52:53 [0m[NR_MAC]   Received UL grant (rb_start 0, rb_size 8, start_symbol_index 10, nr_of_symbols 3) for RNTI type TYPE_TC_RNTI_
```

![Untitled](Untitled%20104.png)

```c
    LOG_I(NR_MAC,"\n\n=========msg3=========\n");
    LOG_I(NR_MAC,"dmrs_config_type: %d\n", pusch_config_pdu->dmrs_config_type);
    LOG_I(NR_MAC,"pdu_bit_map: %d\n", pusch_config_pdu->pdu_bit_map);
    LOG_I(NR_MAC,"nrOfLayers: %d\n", pusch_config_pdu->nrOfLayers);
    LOG_I(NR_MAC,"Tpmi: %d\n", pusch_config_pdu->Tpmi);
    LOG_I(NR_MAC,"rnti: %d\n", pusch_config_pdu->rnti);
    LOG_I(NR_MAC,"bwp_start: %d\n", pusch_config_pdu->bwp_start);
    LOG_I(NR_MAC,"bwp_size: %d\n", pusch_config_pdu->bwp_size);
    LOG_I(NR_MAC,"start_symbol_index: %d\n", pusch_config_pdu->start_symbol_index);
    LOG_I(NR_MAC,"nr_of_symbols: %d\n", pusch_config_pdu->nr_of_symbols);
    LOG_I(NR_MAC,"mcs_index: %d\n", pusch_config_pdu->mcs_index);
    LOG_I(NR_MAC,"frequency_hopping: %d\n", pusch_config_pdu->frequency_hopping);
    LOG_I(NR_MAC,"num_dmrs_cdm_grps_no_data: %d\n", pusch_config_pdu->num_dmrs_cdm_grps_no_data);
    LOG_I(NR_MAC,"dmrs_ports: %d\n", pusch_config_pdu->dmrs_ports);
    LOG_I(NR_MAC,"scid: %d\n", pusch_config_pdu->scid);
    LOG_I(NR_MAC,"transform_precoding: %d\n", pusch_config_pdu->transform_precoding);
    LOG_I(NR_MAC,"resource_alloc: %d\n", pusch_config_pdu->resource_alloc);
    LOG_I(NR_MAC,"mcs_table: %d\n", pusch_config_pdu->mcs_table);
    LOG_I(NR_MAC,"cyclic_prefix: %d\n", pusch_config_pdu->cyclic_prefix);
    LOG_I(NR_MAC,"data_scrambling_id: %d\n", pusch_config_pdu->data_scrambling_id);
    LOG_I(NR_MAC,"ul_dmrs_scrambling_id: %d\n", pusch_config_pdu->ul_dmrs_scrambling_id);
    LOG_I(NR_MAC,"subcarrier_spacing: %d\n", pusch_config_pdu->subcarrier_spacing);
    LOG_I(NR_MAC,"vrb_to_prb_mapping: %d\n", pusch_config_pdu->vrb_to_prb_mapping);
    LOG_I(NR_MAC,"uplink_frequency_shift_7p5khz: %d\n", pusch_config_pdu->uplink_frequency_shift_7p5khz);
    LOG_I(NR_MAC,"pusch_data.rv_index: %d\n", pusch_config_pdu->pusch_data.rv_index);
    LOG_I(NR_MAC,"pusch_data.harq_process_id: %d\n", pusch_config_pdu->pusch_data.harq_process_id);
    LOG_I(NR_MAC,"pusch_data.new_data_indicator: %d\n", pusch_config_pdu->pusch_data.new_data_indicator);
    LOG_I(NR_MAC,"pusch_data.num_cb: %d\n", pusch_config_pdu->pusch_data.num_cb);
    LOG_I(NR_MAC,"tbslbrm: %d\n", pusch_config_pdu->tbslbrm);
    LOG_I(NR_MAC,"====================\n\n\n");
```

| Field | Value |
| --- | --- |
| dmrs_config_type | 0 |
| pdu_bit_map | 1 |
| nrOfLayers | 1 |
| Tpmi | 0 |
| rnti | 60139 (random) |
| bwp_start | 0 |
| bwp_size | 106 |
| start_symbol_index | 0 |
| nr_of_symbols | 13 |
| mcs_index | 0 |
| frequency_hopping | 0 |
| num_dmrs_cdm_grps_no_data | 2 |
| dmrs_ports | 1 |
| scid | 0 |
| transform_precoding | 1 |
| resource_alloc | 1 |
| mcs_table | 0 |
| cyclic_prefix | 0 |
| data_scrambling_id | 1 |
| ul_dmrs_scrambling_id | 1 |
| subcarrier_spacing | 1 |
| vrb_to_prb_mapping | 0 |
| uplink_frequency_shift_7p5khz | 0 |
| pusch_data.rv_index | 0 |
| pusch_data.harq_process_id | 0 |
| pusch_data.new_data_indicator | 1 |
| pusch_data.num_cb | 0 |
| tbslbrm | 0 |

![Untitled](Untitled%20105.png)

Oai nFAPI and OSC nFAPI are difference

```
juil. 26 16:43:15 [0m[NR_RRC]   Generation of RRCSetupRequest
juil. 26 16:43:15 [0m<UL-CCCH-Message>
juil. 26 16:43:15     <message>
juil. 26 16:43:15         <c1>
juil. 26 16:43:15             <rrcSetupRequest>
juil. 26 16:43:15                 <rrcSetupRequest>
juil. 26 16:43:15                     <ue-Identity>
juil. 26 16:43:15                         <randomValue>
juil. 26 16:43:15                             000000001110001010110001000011001011101
juil. 26 16:43:15                         </randomValue>
juil. 26 16:43:15                     </ue-Identity>
juil. 26 16:43:15                     <establishmentCause><mo-Signalling/></establishmentCause>
juil. 26 16:43:15                     <spare>
juil. 26 16:43:15                         0
juil. 26 16:43:15                     </spare>
juil. 26 16:43:15                 </rrcSetupRequest>
juil. 26 16:43:15             </rrcSetupRequest>
juil. 26 16:43:15         </c1>
juil. 26 16:43:15     </message>
juil. 26 16:43:15 </UL-CCCH-Message>
```

```jsx
 七  30 16:06:14 </BCCH-DL-SCH-Message>
 七  30 16:06:14 [32m[NR_RRC]   SIB1 decoded
 七  30 16:06:14 [0m<UL-CCCH-Message>
 七  30 16:06:14     <message>
 七  30 16:06:14         <c1>
 七  30 16:06:14             <rrcSetupRequest>
 七  30 16:06:14                 <rrcSetupRequest>
 七  30 16:06:14                     <ue-Identity>
 七  30 16:06:14                         <randomValue>
 七  30 16:06:14                             000011001011011011011000000001010010001
 七  30 16:06:14                         </randomValue>
 七  30 16:06:14                     </ue-Identity>
 七  30 16:06:14                     <establishmentCause><mo-Signalling/></establishmentCause>
 七  30 16:06:14                     <spare>
 七  30 16:06:14                         0
 七  30 16:06:14                     </spare>
 七  30 16:06:14                 </rrcSetupRequest>
 七  30 16:06:14             </rrcSetupRequest>
 七  30 16:06:14         </c1>
 七  30 16:06:14     </message>
 七  30 16:06:14 </UL-CCCH-Message>
```