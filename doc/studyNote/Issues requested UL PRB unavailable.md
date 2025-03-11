# Issues: requested UL PRB unavailable

Start Date: 2024/09/19
Summary: Addressing the issue of unavailable UL PRB in high logs and comparing OSC OAI time slots for resolution.
Status: Done
Assign: Ming 咚咚 [銘鴻]

## Define issues

- **In OSC DU High Logs**

```
 九  19 14:17:37 DEBUG  -> Info : sfn : 185, slot : 18
 九  19 14:17:37 
 九  19 14:17:37 [NTUST] (p7) header.message_id:130
 九  19 14:17:37 INFO   --> VNF SFN/Slot 185.17 
 九  19 14:17:37 
 九  19 14:17:37 [DEBUG] FILL_PST_LWR_MAC_TO_MAC EVENT:5
 九  19 14:17:37 
 九  19 14:17:37 INFO   -->  SCH : RACH occassion set for slot 19
 九  19 14:17:37 ERROR  -->  SCH: Requested UL PRB unavailable
 九  19 14:17:37 INFO  --> OAI_OSC_fillDlTtiReq()
 九  19 14:17:37 
 九  19 14:17:37 INFO  ->  The current Timing Info : sfn : 185, slot : 17
 九  19 14:17:37 
 九  19 14:17:37 INFO  ->  The DL TTI Timing Info : sfn : 185, slot : 19
 九  19 14:17:37 
 九  19 14:17:37 [DEBUG] -->  dlTtiReq->dl_tti_request_body.nPDUs:0
 九  19 14:17:37 
 九  19 14:17:37 INFO  -->  OAI_OSC_fillUlTtiReq()
 九  19 14:17:37 
 九  19 14:17:37 INFO  -->  ulTtiReq->n_pdus :0
```

- **In OAI Layer1 Logs**

```
九  19 14:17:37 [PHY]   pNfapiMsg->SFN: 185
 九  19 14:17:37 [0m[PHY]   pNfapiMsg->Slot: 19
 九  19 14:17:37 [0m[PHY]   pNfapiMsg->n_pdus: 2
 九  19 14:17:37 [0m[PHY]   pNfapiMsg->rach_present: 1
 九  19 14:17:37 [0m[PHY]   pNfapiMsg->n_ulcch: 0
 九  19 14:17:37 [0m[PHY]   pNfapiMsg->n_ulsch: 1
 九  19 14:17:37 [0m[PHY]   pNfapiMsg->n_group: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   PUCCH:
 九  19 14:17:37 [0m[NFAPI_PNF]   rnti: 100
 九  19 14:17:37 [0m[NFAPI_PNF]   handle: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   bwp_size: 106
 九  19 14:17:37 [0m[NFAPI_PNF]   bwp_start: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   subcarrier_spacing: 1
 九  19 14:17:37 [0m[NFAPI_PNF]   cyclic_prefix: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   format_type: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   multi_slot_tx_indicator: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   pi_2bpsk: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   prb_start: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   prb_size: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   start_symbol_index: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   nr_of_symbols: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   freq_hop_flag: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   second_hop_prb: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   group_hop_flag: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   sequence_hop_flag: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   hopping_id: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   initial_cyclic_shift: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   data_scrambling_id: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   time_domain_occ_idx: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   pre_dft_occ_idx: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   pre_dft_occ_len: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   add_dmrs_flag: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   dmrs_scrambling_id: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   dmrs_cyclic_shift: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   sr_flag: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   bit_len_harq: 1
 九  19 14:17:37 [0m[NFAPI_PNF]   bit_len_csi_part1: 0
 九  19 14:17:37 [0m[NFAPI_PNF]   bit_len_csi_part2: 0
```

[Fix: match PUCCH config (OSC and OAI)](Fix%20match%20PUCCH%20config%20(OSC%20and%20OAI)%20121100983143815597a0fe86f92aba6f.md) 

[Issues: OSC DU MSG4 is sent but the UE does not receive it.](Issues%20OSC%20DU%20MSG4%20is%20sent%20but%20the%20UE%20does%20not%20rec%2012110098314381ba89bddcafc0ae64e2.md) 

## Trace code in OSC DU High

[https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=tkgDop18eDsZmSPhkqs3#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=tkgDop18eDsZmSPhkqs3#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)

## Compare OSC OAI time slot

![image.png](image%2031.png)

```
 九  24 13:09:25  PUCCH Pres
 九  24 13:09:25 
 九  24 13:09:25  CRNTI 100
 九  24 13:09:25 
 九  24 13:09:25  fill pucch common cfg in slot 17
 九  24 13:09:25 
 九  24 13:09:25 [common] startSymb: 12, numSymb: 2
 九  24 13:09:25 [common] startPrb 0
 九  24 13:09:25 
 九  24 13:09:25 [fillPrbBitmap] startsymbol = 12, symbolLength = 2
 九  24 13:09:25 [fillPrbBitmap] startPrb = 0, numPrb = 1
 九  24 13:09:25 [fillPrbBitmap] startsymbol = 12, symbolLength = 2
 九  24 13:09:25 [fillPrbBitmap] startPrb = 0, numPrb = 1
```

After change **`MIN_NUM_K1_IDX` 4 → 0**

PUCCH could be scheduler at slot 17, then it will not reuse the same PRB with UL_TTI for PRACH at slot 19!

<aside>
💡

Complete!

</aside>