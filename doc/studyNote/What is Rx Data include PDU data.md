# What is Rx Data include PDU data

Start Date: 2024/09/04
Summary: The project involves analyzing Rx data within MSG3 and comparing logs from OAI VNF and PNF through practical implementation.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡

Recently, I read some information related to MSG3, like those notes → [Study MSG3](Study%20MSG3%201211009831438133ab92d50e48cf5bf3.md) . Now, I want to gain a deeper understanding of the data content and meaning conveyed in the Rx data within MSG3. Additionally, I plan to compare logs from the OAI VNF+PNF through practical implementation.

</aside>

# SCF spec with RX data

![image.png](image%2082.png)

![image.png](image%2083.png)

![image.png](image%2084.png)

# Struct

```cpp
typedef struct
{
   uint32_t      handle;
   uint16_t      rnti;
   uint8_t       harqId;
   uint16_t      pduLength;
   uint8_t       ul_cqi;
   uint16_t      timingAdvance;
   uint16_t      rssi;
   uint8_t       *pduData;
}RxDataIndPdu;

typedef struct
{
   uint16_t      cellId;
   SlotTimingInfo   timingInfo;
   uint16_t      numPdus;
   RxDataIndPdu  pdus[MAX_ULSCH_PDUS_PER_TTI];
}RxDataInd;
```

# In OAI VNF + PNF log

| title | vlaue |
| --- | --- |
| harq_id | 0 |
| new_data_indicator | 1 |
| TBS_bytes | 28 |
| ra_state | 2 |
| mac->crnti | 0 |
| ra->msg3_C_RNTI | 0 |
| channel_idP | 0 |
| entity->tx_size | 0 |
| txpdu_pkts | 1 |
| txpdu_bytes | 27 |
| len | 6 |
| cfra | 0 |
| RA_offset | 2 |
| ra_rnti | 267 |
| t_crnti | 32940 |
| RA_attempt_number | 1 |
| RA_active | true |
| ra_PreambleIndex | 8 |
| ssb_nb_in_ro | 0 |
| RA_window_cnt | 57 |
| RA_RAPID_found | 1 |
| RA_BI_found | 1 |
| RA_backoff_indicator | 5 |
| RA_usedGroupA | 1 |
| RA_backoff_cnt | 0 |
| preambleTransMax | 10 |
| cb_preambles_per_ssb | 60 |
| starting_preamble_nb | 0 |
| Msg3_TPC | 0 |
| first_Msg3 | true |
| Msg3_size | 0 |
| Msg3_buffer | (nil) |
| msg3_C_RNTI | false |
| Remaining bytes to fill | 7 |
| Padding Values | 0x34, 0x17, 0x3, 0x51, 0xef, 0xaa, 0x46, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x0 |
| RA-Msg3 transmitted | [RAPROC][184.19] RA-Msg3 transmitted |