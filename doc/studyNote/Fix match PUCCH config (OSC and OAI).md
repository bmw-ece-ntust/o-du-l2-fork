# Fix: match PUCCH config (OSC and OAI)

Start Date: 2024/09/18
Summary: Fixing the PUCCH configuration to ensure proper functionality between OSC and OAI systems.
Status: Done
Assign: Ming 咚咚 [銘鴻]

## FAPI spec

![image.png](image%2044.png)

![{B064A838-F42F-43CC-B8DD-E7AD0BA399E7}.png](B064A838-F42F-43CC-B8DD-E7AD0BA399E7.png)

![{21770209-DCF7-415E-A589-6C7556A5F03C}.png](21770209-DCF7-415E-A589-6C7556A5F03C.png)

![{4091F34A-B644-4531-A3BF-F0A12B2FD33D}.png](4091F34A-B644-4531-A3BF-F0A12B2FD33D.png)

![{72B3BF1D-8457-4516-BB79-442A355E18D8}.png](72B3BF1D-8457-4516-BB79-442A355E18D8.png)

![{7467054F-8F2C-429A-BFC8-49ABA67DBB71}.png](7467054F-8F2C-429A-BFC8-49ABA67DBB71.png)

## compare table

| Field | OAI Value1 | OAI Value2 | OSC Value 2 | OSC Value |
| --- | --- | --- | --- | --- |
| SFN/SL | 185/17 | 187/7 | 186/6 | 186/6 |
| rnti | 24637 | 24637 | 100 | 100 |
| handle | 0 | 0 | 0 | 0 |
| bwp_size | 106 | 106 | 106 | 106 |
| bwp_start | 0 | 0 | 0 | 0 |
| subcarrier_spacing | 1 | 1 | 1 | 1 |
| cyclic_prefix | 0 | 0 | 0 | 0 |
| format_type | 0 | 0 | 0 | 0 |
| multi_slot_tx_indicator | 0 | 0 | 0 | 0 |
| pi_2bpsk | 0 | 0 | 0 | 0 |
| prb_start | 0 | 8 | 0 | 0 |
| prb_size | 1 | 1 | 1 | 0 |
| start_symbol_index | 12 | 13 | 12 | 0 |
| nr_of_symbols | 2 | 1 | 2 | 0 |
| freq_hop_flag | 1 | 0 | 0 | 0 |
| second_hop_prb | 105 | 0 | 0 | 0 |
| group_hop_flag | 0 | 0 | 0 | 0 |
| sequence_hop_flag | 0 | 0 | 0 | 0 |
| hopping_id | 40 | 40 | 0 | 0 |
| initial_cyclic_shift | 0 | 0 | 0 | 0 |
| data_scrambling_id | 0 | 0 | 0 | 0 |
| time_domain_occ_idx | 0 | 0 | 0 | 0 |
| pre_dft_occ_idx | 0 | 0 | 0 | 0 |
| pre_dft_occ_len | 0 | 0 | 0 | 0 |
| add_dmrs_flag | 0 | 0 | 0 | 0 |
| dmrs_scrambling_id | 0 | 0 | 0 | 0 |
| dmrs_cyclic_shift | 0 | 0 | 0 | 0 |
| sr_flag | 0 | 1 | 1 | 0 |
| bit_len_harq | 1 | 0 | 1 | 1 |
| bit_len_csi_part1 | 0 | 0 | 0 | 0 |
| bit_len_csi_part2 | 0 | 0 | 0 | 0 |

## Only OAI VNF + PNF

| SFN/SL | PDU Type | PUCCH Type |
| --- | --- | --- |
| 185/17 | **n_ulcch** | **freq_hop_flag** |
| 185/19 | **rach_present** |  |
| 187/7 | **n_ulcch** | **sr_flag** |
| 187/17 | **n_ulcch, n_ulcch** | **sr_flag** |
| 187/19 | **rach_present** |  |

```jsx
 九  18 15:31:28 [0m1726644688.969470 [NR_MAC]   UE 603d Generate msg4: feedback at  185.17, payload 149 bytes, next state WAIT_Msg4_ACK
 九  18 15:31:28 [0m1726644688.973740 [PHY]   UL_TTI_REQUEST: SFN/SLOT 185/17, n_pdus 1, rach_present 0, n_ulsch 0, n_ulcch 1, n_group 0
 九  18 15:31:28 [0m1726644688.975200 [PHY]   UL_TTI_REQUEST: SFN/SLOT 185/19, n_pdus 1, rach_present 1, n_ulsch 0, n_ulcch 0, n_group 0
 九  18 15:31:28 [0m1726644688.975203 [PHY]   Packing PRACH PDU phys_cell_id:1, num_prach_ocas:3, prach_format:5, num_ra:0, prach_start_symbol:0, num_cs:34
 九  18 15:31:28 [0m[32m1726644688.980759 [NR_MAC]   (UE RNTI 0x603d) Received Ack of RA-Msg4. CBRA procedure succeeded!
 九  18 15:31:28 [0m1726644688.995255 [PHY]   UL_TTI_REQUEST: SFN/SLOT 187/7, n_pdus 1, rach_present 0, n_ulsch 0, n_ulcch 1, n_group 0
```

Based on the observation of the OAI VNF+PNF logs, the PUCCH has two flags: `freq_hop_flag` and `sr_flag`. The `freq_hop_flag` appears once when a UE connects for the first time, while in normal conditions, only the `sr_flag` is transmitted.

In the current situation, even the `freq_hop_flag` is unable to be sent successfully. It is suspected that this issue may be due to **SCH: Requested UL PRB unavailable**, which occurs before sending the PUCCH. Therefore, it has been decided to resolve this problem first. →[Issues: r**equested UL PRB unavailable**](Issues%20requested%20UL%20PRB%20unavailable%20121100983143813b8c12f0cba11b69e8.md) 

## Compare Resource

|  | OAI | OSC |
| --- | --- | --- |
| PRB_Start | 0 | 0 |
| PRB_Size |  | 1 |
| Symbol_start | 12 | 12 |
| Symbol_len | 2 | 2 |

![image.png](image%2045.png)