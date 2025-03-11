# Issues: OSC DU MSG4 is sent but the UE does not receive it.

Start Date: 2024/09/18
Summary: The project focuses on troubleshooting the issue where OSC DU MSG4 is sent but not received by the UE, involving analysis of logs and error messages.
Status: padding
Assign: Ming 咚咚 [銘鴻]

<aside>
💡

Reference:

https://www.nrexplained.com/ra_msg4

https://blog.csdn.net/kakamilan/article/details/121192611

https://blog.csdn.net/hhd1988/article/details/131460116

</aside>

In response to a PUSCH transmission scheduled by a RAR UL grant when a UE has not been provided a C-RNTI, the UE attempts to detect a DCI format 1_0 with CRC scrambled by a corresponding TC-RNTI scheduling a PDSCH that includes a UE contention resolution identity ([TS 38.321](https://www.3gpp.org/DynaReport/38321.htm)).

In response to the PDSCH reception with the UE contention resolution identity, the UE transmits HARQ-ACK information in a PUCCH. The PUCCH transmission is within a same active UL BWP as the PUSCH transmission.

A minimum time between the last symbol of the PDSCH reception and the first symbol of the corresponding PUCCH transmission with the HARQ-ACK information is equal to *NT,1* + 0.5 msec. *NT,1* is a time duration of *N1* symbols corresponding to a PDSCH processing time for UE processing capability 1 when additional PDSCH DM-RS is configured. ***N*1 = {14, 13, 20, 24} for *μ* = {0, 1, 2, 3}**.

When detecting a DCI format in response to a PUSCH transmission scheduled by a RAR UL grant, or corresponding PUSCH retransmission scheduled by a DCI format 0_0 with CRC scrambled by a TCRNTI provided in the corresponding RAR message, the UE may assume **the PDCCH carrying the DCI format has the same DM-RS antenna port quasi co-location properties as for a SS/PBCH block the UE used for PRACH association**, regardless of whether or not the UE is provided TCI-State for the CORESET where the UE receives the PDCCH with the DCI format.

![image.png](image%2052.png)

![image.png](image%2057.png)

![image.png](image%2058.png)

## List all of ERROR in current status

|  Invalid IE received in E2SetupRsp | ⏳ | [**Fix: E2AP Blockage During E2 Setup Request Build**](Fix%20E2AP%20Blockage%20During%20E2%20Setup%20Request%20Build%201211009831438136b428fa8de1a96aad.md)  |
| --- | --- | --- |
| SCH: schProcessMsg4Req() : No process | ✅ | [Issues: SCH: schProcessMsg4Req() : k0 k1 not found](Issues%20SCH%20schProcessMsg4Req()%20k0%20k1%20not%20found%201211009831438145a753ea7090dbe44d.md)  |
| SCH: Requested UL PRB unavailable | ✅ | [Issues: r**equested UL PRB unavailable**](Issues%20requested%20UL%20PRB%20unavailable%20121100983143813b8c12f0cba11b69e8.md)  |
| Main Fixing note | ⏳ | [UE is unable to receive MSG4](UE%20is%20unable%20to%20receive%20MSG4%2012110098314381f48123c7e96011e156.md)  |

### OSC DU High Logs

- Invalid IE received in E2SetupRsp:9 ⏳ temp solution → OSC need to fix Memory allocate function issues
    - [**Fix: E2AP Blockage During E2 Setup Request Build**](Fix%20E2AP%20Blockage%20During%20E2%20Setup%20Request%20Build%201211009831438136b428fa8de1a96aad.md)

```jsx
 九  18 11:05:35         </value>
 九  18 11:05:35     </successfulOutcome>
 九  18 11:05:35 </E2AP-PDU>
 九  18 11:05:35 
 九  18 11:05:35 INFO   -->  E2AP : E2 Setup Response received
 九  18 11:05:35 ERROR  -->  E2AP : Invalid IE received in E2SetupRsp:9
 九  18 11:05:35 INFO   -->  E2AP : Building E2 Node config update
 九  18 11:05:35 <E2AP-PDU>
 九  18 11:05:35     <initiatingMessage>
 九  18 11:05:35         <procedureCode>10</procedureCode>
```

- SCH: schProcessMsg4Req() : No process ✅
    - [Issues: SCH: schProcessMsg4Req() : k0 k1 not found](Issues%20SCH%20schProcessMsg4Req()%20k0%20k1%20not%20found%201211009831438145a753ea7090dbe44d.md)

```jsx
 九  18 11:05:47 DEBUG   -->  DU_APP: Sending UE create request to MAC
 九  18 11:05:47 [DEBUG] FILL_PST_LWR_MAC_TO_MAC EVENT:5
 九  18 11:05:47 
 九  18 11:05:47 ERROR  -->  SCH: schProcessMsg4Req() : No process
 九  18 11:05:47 [DU UTILS] --> Gen Buffer
 九  18 11:05:47 [MacActvTsk] Recieved pst from eb
 九  18 11:05:47 [MacActvTsk] Recieved pst from DUAPP, event is 208
```

- SCH: Requested UL PRB unavailable ✅
    - [Issues: r**equested UL PRB unavailable**](Issues%20requested%20UL%20PRB%20unavailable%20121100983143813b8c12f0cba11b69e8.md)

```jsx
 九  18 11:05:47 DEBUG  -> Info : sfn : 185, slot : 18
 九  18 11:05:47 
 九  18 11:05:47 [NTUST] (p7) header.message_id:130
 九  18 11:05:47 INFO   --> VNF SFN/Slot 185.17 
 九  18 11:05:47 
 九  18 11:05:47 [DEBUG] FILL_PST_LWR_MAC_TO_MAC EVENT:5
 九  18 11:05:47 
 九  18 11:05:47 INFO   -->  SCH : RACH occassion set for slot 19
 九  18 11:05:47 ERROR  -->  SCH: Requested UL PRB unavailable
 九  18 11:05:47 INFO  --> OAI_OSC_fillDlTtiReq()
 九  18 11:05:47 
 九  18 11:05:47 INFO  ->  The current Timing Info : sfn : 185, slot : 17
 九  18 11:05:47 
 九  18 11:05:47 INFO  ->  The DL TTI Timing Info : sfn : 185, slot : 19
```

### OAI PNF LOG

```
 九  18 11:05:47 [0m[NFAPI_PNF]   PUCCH:
 九  18 11:05:47 [0m[NFAPI_PNF]   rnti: 100
 九  18 11:05:47 [0m[NFAPI_PNF]   handle: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   bwp_size: 106
 九  18 11:05:47 [0m[NFAPI_PNF]   bwp_start: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   subcarrier_spacing: 1
 九  18 11:05:47 [0m[NFAPI_PNF]   cyclic_prefix: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   format_type: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   multi_slot_tx_indicator: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   pi_2bpsk: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   prb_start: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   prb_size: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   start_symbol_index: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   nr_of_symbols: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   freq_hop_flag: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   second_hop_prb: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   group_hop_flag: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   sequence_hop_flag: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   hopping_id: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   initial_cyclic_shift: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   data_scrambling_id: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   time_domain_occ_idx: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   pre_dft_occ_idx: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   pre_dft_occ_len: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   add_dmrs_flag: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   dmrs_scrambling_id: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   dmrs_cyclic_shift: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   sr_flag: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   bit_len_harq: 1
 九  18 11:05:47 [0m[NFAPI_PNF]   bit_len_csi_part1: 0
 九  18 11:05:47 [0m[NFAPI_PNF]   bit_len_csi_part2: 0
 九  18 11:05:47 [0m
```

PNF got MSG4 TX_data.request from ODU 

![image.png](image%2059.png)

![image.png](image%2060.png)