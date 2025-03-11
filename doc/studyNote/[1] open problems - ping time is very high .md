# [1] open problems - ping time is very high

Start Date: 2024/04/10
Summary: Investigating and resolving high ping time issues in the network, including analyzing message processing times and buffer performance in PNF and VNF systems.
Status: Done
Assign: 陳奕全
Tags: Robert Task

- ping time is very high -- unclear why.

![Untitled](Untitled%205.png)

- [x]  Check again SR is properly received?
    - YES
    - Check by print log with bitmap_pdu in VNF and PNFx`x
- [x]  When a message is put into the buffer in the `PNF` , how long does it take till this message is processed by L1?
    - When `PNF` receive header.message_id:
        - `NFAPI_NR_PHY_MSG_TYPE_DL_TTI_REQUEST`
            - For `TX_DATA` is about 2ms. (from put buffer to end of use.)
        - `NFAPI_NR_PHY_MSG_TYPE_UL_TTI_REQUEST`
            - For `UL_TTI` is about 2ms. (from put buffer to end of use.)
        - `NFAPI_NR_PHY_MSG_TYPE_TX_DATA_REQUEST`
            - For `TX_DATA` is about 2.3ms. (from put buffer to end of use.)
        - `NFAPI_NR_PHY_MSG_TYPE_UL_DCI_REQUEST`
            - For `UL_DCI` is about 2.8ms. (from put buffer to end of use.)
- [x]  In UL, does it buffer the PDUs for a long time? how long?
    - For `UCI` is about 1.2ms. (from put buffer to end of use.)
- [x]  where is the code?
    
    
    | DL_TTI.request | From [VNF] `oai_nfapi_dl_tti_req` 
    to [PNF] **`nr_schedule_dl_tti_req` Finsh (include PDCCH,PDSCH,SSB,CSI_RS)** |
    | --- | --- |
    | TX_Data.request | From [VNF] **`schedule_nr_mib` to [PNF] `nr_generate_pdsch`** |
    | UL_DCI.request | From [VNF] **`oai_nfapi_ul_dci_req`**  **to [PNF] `nr_generate_dci`** |
    | DCI.request | From [VNF] **`oai_nfapi_ul_dci_req` to [PNF] `nr_generate_dci`** |
    | UL_DCI.request | From [VNF] **`pnf_p7->slot_buffer[buffer_index].ul_dci_req = req;` to 
    [PNF] `pnf_phy_ul_dci_req`** |
    | UL_TTI.request | From VNF `oai_nfapi_ul_tti_req` to PNF `save slot_buffer` 
    to tx_func `nr_fill_pucch` to rx_func `nr_decode_pucch0` finish |
    | UCI.indication | From PNF `handle_nr_uci` 
    to VNF `handle_nr_uci_pucch_0_1` (NB_scheduler_uci.c) Finish |
    | RXdata.indication | From PNF `handle_nr_ulsch` to VNF `nr_rx_sdu`(gNB_scheduler_ulsch.c) Finish |
    | CRC.indication | From PNF `handle_nr_ulsch` 
    to VNF  `handle_nr_ul_harq` (gNB_scheduler_ulsch.c) Finish |

<aside>
👀 reference

- [chain of function UL_TTI (notion.so)](https://www.notion.so/chain-of-function-UL_TTI-12110098314381458393d5ff06926d75?pvs=21)
- [chain of function DCI (notion.so)](https://www.notion.so/chain-of-function-UL_DCI-121100983143811e8c1dfc6edad9ce88?pvs=21)
- [chain of function UCI (notion.so)](https://www.notion.so/chain-of-function-UCI-12110098314381e1b5d2e840a4973515?pvs=21)
</aside>

## UL_TTI

When a message is put into the buffer in the PNF, how long does it take till this message is processed by L1?

| tag | description | path |
| --- | --- | --- |
| buffer | **pnf_p7->slot_buffer[buffer_index].ul_tti_req = req;** | openairinterface5g/nfapi/open-nFAPI/pnf/src/pnf_p7.c `pnf_handle_ul_tti_request` |
| L1 use | **pnf_phy_ul_tti_req** | openairinterface5g/nfapi/open-nFAPI/pnf/src/pnf_p7.c  `pnf_p7_slot_ind` |

| No. | use buffer (s) | End of use(s) |
| --- | --- | --- |
| 1 | 0.001993 | 0.001999 |
| 2 | 0.001992 | 0.001999 |
| 3 | 0.002014 | 0.002021 |
| 4 | 0.002354 | 0.002367 |

![Untitled](Untitled%206.png)

## UL_DCI

When a message is put into the buffer in the PNF, how long does it take till this message is processed by L1?

| tag | description | path |
| --- | --- | --- |
| buffer | **pnf_p7->slot_buffer[buffer_index].ul_dci_req = req;** | openairinterface5g/nfapi/open-nFAPI/pnf/src/pnf_p7.c `pnf_handle_ul_dci_request` |
| L1 use | **pnf_phy_ul_dci_req** | openairinterface5g/nfapi/open-nFAPI/pnf/src/pnf_p7.c `pnf_p7_slot_ind` |

| No. | use buffer (s) | End of use(s) |
| --- | --- | --- |
| 1 | 0.002816 | 0.002820 |
| 2 | 0.002845 | 0.002850 |
| 3 | 0.002634 | 0.002639 |
| 4 | 0.002968 | 0.002982 |

![Untitled](Untitled%207.png)

## UCI

In UL, does it buffer the PDUs for a long time? how long? where is the code?

| tag | description | path |
| --- | --- | --- |
| buffer | **put_queue(&gnb_uci_ind_queue, uci_ind)** | openairinterface5g/nfapi/oai_integration/nfapi_vnf.c `phy_nr_uci_indication` |
| L2 get | **get_queue(&gnb_uci_ind_queue);** | openairinterface5g/openair2/NR_PHY_INTERFACE/NR_IF_Module.c
`NR_UL_indication` |
| L2 use | **handle_nr_uci** | openairinterface5g/openair2/NR_PHY_INTERFACE/NR_IF_Module.c `NR_UL_indication` |

| No. | use buffer (s) | End of use(s) |
| --- | --- | --- |
| 1 | 0.001297 | 0.001302 |
| 2 | 0.001189 | 0.001194 |
| 3 | 0.001348 | 0.001356 |
| 4 | 0.001041 | 0.001046 |

![Untitled](Untitled%208.png)

## Check again SR is properly received?

<aside>
✅ Yes. SR is match

</aside>

```c
**pack_nr_uci_pucch_0_1
...**

printf("pduBitmap:%d , sr_indication:%d\n",value->pduBitmap**,value->sr.sr_indication**);
```

```c
**unpack_nr_uci_pucch_0_1
...
printf("pduBitmap:%d , sr_indication:%d\n",value->pduBitmap,value->sr.sr_indication);**

```

Run period 120s

![PNF](Untitled%209.png)

PNF

![VNF](Untitled%2010.png)

VNF