# Compare:RX_data content

Start Date: 2024/10/03
Summary: Comparison of RX_data PDU content between monolithic and OSC nFAPI modes, highlighting differences in key fields.
Status: Done
Assign: 陳奕全

To compare monolithic and OSC nFAPI mode RX_data PDU content

## OSC:

```c
printf("message_id: %d\n", rx_ind->header.message_id);
printf("sfn: %d\n", rx_ind->sfn);
printf("slot: %d\n", rx_ind->slot);
printf("number_of_pdus: %d\n", rx_ind->number_of_pdus);

for (int j = 0; j < ind->number_of_pdus; j++) {
    printf("PDU #%d:\n", j + 1);
    printf("    handle: %d\n", rx_ind->pdu_list[j].handle);
    printf("    harq_id: %d\n", rx_ind->pdu_list[j].harq_id);
    printf("    pdu_length: %d\n", rx_ind->pdu_list[j].pdu_length);
    printf("    rnti: %d\n", rx_ind->pdu_list[j].rnti);
    printf("    timing_advance: %d\n", rx_ind->pdu_list[j].timing_advance);
    printf("    ul_cqi: %d\n", rx_ind->pdu_list[j].ul_cqi);
    printf("    rssi: %d\n", rx_ind->pdu_list[j].rssi);
}

```

```
 十  03 11:45:28 INFO   --> =============RXDATA PDU===========
 十  03 11:45:28 message_id: 133
 十  03 11:45:28 sfn: 168
 十  03 11:45:28 slot: 18
 十  03 11:45:28 number_of_pdus: 1
 十  03 11:45:28 PDU #1:
 十  03 11:45:28     handle: 0
 十  03 11:45:28     harq_id: 0
 十  03 11:45:28     pdu_length: 28
 十  03 11:45:28     rnti: 100
 十  03 11:45:28     timing_advance: 31
 十  03 11:45:28     ul_cqi: 230
 十  03 11:45:28     rssi: 860
 十  03 11:45:28 
 十  03 11:45:28 INFO   --> =====================================
```

## OAI

```c
    printf("========RX DATA PDU========\n");
    printf("message_id: %d\n", rx_ind->header.message_id);
    printf("sfn: %d\n", rx_ind->sfn);
    printf("slot: %d\n", rx_ind->slot);
    printf("number_of_pdus: %d\n", rx_ind->number_of_pdus);

    for (int j = 0; j < ind->number_of_pdus; j++) {
        printf("PDU #%d:\n", j + 1);
        printf("    handle: %d\n", rx_ind->pdu_list[j].handle);
        printf("    harq_id: %d\n", rx_ind->pdu_list[j].harq_id);
        printf("    pdu_length: %d\n", rx_ind->pdu_list[j].pdu_length);
        printf("    rnti: %d\n", rx_ind->pdu_list[j].rnti);
        printf("    timing_advance: %d\n", rx_ind->pdu_list[j].timing_advance);
        printf("    ul_cqi: %d\n", rx_ind->pdu_list[j].ul_cqi);
        printf("    rssi: %d\n", rx_ind->pdu_list[j].rssi);
    }
    printf("==================================\n");
```

```
 十  03 11:49:14 [0m========RX DATA PDU========
 十  03 11:49:14 message_id: 133
 十  03 11:49:14 sfn: 168
 十  03 11:49:14 slot: 19
 十  03 11:49:14 number_of_pdus: 1
 十  03 11:49:14 PDU #1:
 十  03 11:49:14     handle: 0
 十  03 11:49:14     harq_id: 0
 十  03 11:49:14     pdu_length: 28
 十  03 11:49:14     rnti: 17842
 十  03 11:49:14     timing_advance: 31
 十  03 11:49:14     ul_cqi: 230
 十  03 11:49:14     rssi: 860
 十  03 11:49:14 ==================================
```

<aside>
👀

They are same excluding RNTI

</aside>

| Field | OAI | OSC |
| --- | --- | --- |
| message_id | 133 | 133 |
| sfn | 168 | 168 |
| slot | 19 | 18 |
| number_of_pdus | 1 | 1 |
| handle | 0 | 0 |
| harq_id | 0 | 0 |
| pdu_length | 28 | 28 |
| rnti | 17842 | 100 |
| timing_advance | 31 | 31 |
| ul_cqi | 230 | 230 |
| rssi | 860 | 860 |