# [5] look for the reason UL_TTI spend 9ms

Start Date: 2024/04/15
Summary: Analyzing the UL_TTI processing time and its impact on message transmission efficiency.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Robert Task

<aside>
📎 Reference:

[chain of function UL_TTI](https://www.notion.so/chain-of-function-UL_TTI-12110098314381458393d5ff06926d75?pvs=21) 

</aside>

List all of UL_TTI will send message (by OAI source code)

- nr_fill_ulsch
- nr_fill_pucch
- nr_fill_prach
- nr_fill_prach_ru
- nr_fill_srs

### Measure from VNF to PNF time

| nr_fill_ulsch | 0.002497s |
| --- | --- |
| nr_fill_pucch | 0.002424s |
| nr_fill_prach | 0.002056s |
| nr_fill_prach_ru | 0.002061s |
| nr_fill_srs | none |

---

## Measure From VNF to PNF to RX_func time

| UL_TTI.request | 0.009000s | From VNF `oai_nfapi_ul_tti_req` to PNF `save slot_buffer` to tx_func `nr_fill_pucch` to rx_func `nr_decode_pucch0` finish |
| --- | --- | --- |
| PUCCH | 0.002424s | From VNF `oai_nfapi_ul_tti_req` to PNF `nr_fill_pucch` |
| rx_func | 0.006373s | From PNF `nr_fill_pucch` to [RX_func] **`nr_decode_pucch0`** |

![Untitled](Untitled%20110.png)

<aside>
💡 Based on the table, it can be concluded that more time was spent from PFU filling to being used by `RX_func`. (between two arrow)

</aside>

![Untitled](Untitled%20111.png)

---

<aside>
💡 I think that the UL_TTI measurement reaching 9ms is likely due to UL_TTI notifying Layer 1 6ms in advance that the MAC PDU is being sent from the UE. This should not cause a delay issue. In actuality, the PNF takes approximately 2ms from receiving UL_TTI to filling it into the buffer, which is similar to other messages. Hence, I think there's no need to be concerned about it.

</aside>

| DL_TTI.request | 0.002105s | From [VNF] `oai_nfapi_dl_tti_req` to [PNF] **`nr_schedule_dl_tti_req` Finsh (include PDCCH,PDSCH,SSB,CSI_RS)** |
| --- | --- | --- |
| TX_Data.request | 0.002428s | From [VNF] **`schedule_nr_mib` to [PNF] `nr_generate_pdsch`** |
| UL_DCI.request | 0.003028s | From [VNF] **`oai_nfapi_ul_dci_req`**  **to [PNF] `nr_generate_dci`** |
| DCI.request | 0.002064s | From [VNF] **`oai_nfapi_ul_dci_req` to [PNF] `nr_generate_dci`** |
| UCI.indication | 0.001223s | From PNF `handle_nr_uci` to VNF `handle_nr_uci_pucch_0_1` (NB_scheduler_uci.c) Finish |
| RXdata.indication | 0.001006s | From PNF `handle_nr_ulsch` to VNF `nr_rx_sdu`(gNB_scheduler_ulsch.c) Finish |
| CRC.indication | 0.001179s | From PNF `handle_nr_ulsch` to VNF  `handle_nr_ul_harq` (gNB_scheduler_ulsch.c) Finish |
| UL_TTI.request | 0.009000s | From VNF `oai_nfapi_ul_tti_req` to PNF `save slot_buffer` to tx_func `nr_fill_pucch` to rx_func `nr_decode_pucch0` finish |
| ULSCH | 0.002497s | From VNF `oai_nfapi_ul_tti_req` to PNF `nr_fill_ulsch`  |
| PUCCH | 0.002424s | From VNF `oai_nfapi_ul_tti_req` to PNF `nr_fill_pucch` |
| **`nr_decode_pucch0`** | 0.006373s | From PNF `nr_fill_pucch` to [RX_func] **`nr_decode_pucch0`** |
| PRACH | 0.002056s | From VNF `oai_nfapi_ul_tti_req` to PNF `nr_fill_prach` |