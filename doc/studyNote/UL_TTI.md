# UL_TTI

Tags: UL_TTI

```c
typedef struct {
  nfapi_p7_message_header_t header;
  uint16_t SFN; //0->1023   
  uint16_t Slot;//0->319
  uint8_t n_pdus;//Number of PDUs that are included in this message. All PDUs in the message are numbered in order. Value 0 -> 255
  uint8_t  rach_present;//Indicates if a RACH PDU will be included in this message. 0: no RACH in this slot 1: RACH in this slot
  uint8_t  n_ulsch;//Number of ULSCH PDUs that are included in this message.
  uint8_t  n_ulcch;//Number of ULCCH PDUs
  uint8_t n_group;//Number of UE Groups included in this message. Value 0 -> 8
  nfapi_nr_ul_tti_request_number_of_pdus_t pdus_list[NFAPI_MAX_NUM_UL_PDU];
  nfapi_nr_ul_tti_request_number_of_groups_t groups_list[NFAPI_MAX_NUM_GROUPS];
} nfapi_nr_ul_tti_request_t;
```

|  | OAI | OSC |
| --- | --- | --- |
| rach_present | 1 | 2 |
|  |  |  |

```c
  LOG_I(PHY,"pNfapiMsg->SFN: %d\n", pNfapiMsg->SFN);
  LOG_I(PHY,"pNfapiMsg->Slot: %d\n", pNfapiMsg->Slot);
  LOG_I(PHY,"pNfapiMsg->n_pdus: %d\n", pNfapiMsg->n_pdus);
  LOG_I(PHY,"pNfapiMsg->rach_present: %d\n", pNfapiMsg->rach_present);
  LOG_I(PHY,"pNfapiMsg->n_ulcch: %d\n", pNfapiMsg->n_ulcch);
  LOG_I(PHY,"pNfapiMsg->n_ulsch: %d\n", pNfapiMsg->n_ulsch);
  LOG_I(PHY,"pNfapiMsg->n_group: %d\n", pNfapiMsg->n_group);
```