# ReMeasure

Start Date: 2024/04/22
Summary: A project focused on measurement and assessment scheduled to start on April 22, 2024, and assigned to Ming 咚咚 [銘鴻], currently marked as done.
Status: Done
Assign: Ming 咚咚 [銘鴻]

[https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=tJYECNdYWPltoWKFx9pj&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=tJYECNdYWPltoWKFx9pj&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)

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