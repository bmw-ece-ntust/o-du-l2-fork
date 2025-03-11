# speed up UL_DCI

Start Date: 2024/04/23
Summary: Optimize the UL_DCI process by using stack allocation instead of heap allocation to reduce delays.
Status: Done
Assign: 陳奕全
Tags: Robert Task

Follow TX_date.req method to speed up UL_DCI (use stack instead of heap) → reference:

[**do not allocate tx_data on heap, introduces huge delay**](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/e8461d1571d7405894b89b5e2aea0c4de7fad488)

Modify these two file:

```c
openairinterface5g\nfapi\open-nFAPI\pnf\public_inc\nfapi_pnf_interface.h
openairinterface5g\nfapi\open-nFAPI\pnf\src\pnf_p7.c
```

## nfapi_pnf_interface.h

```c

typedef struct 
{
	//uint16_t sfn_slot
	int16_t sfn;
	int16_t slot;
	//TODO: Change P7 structs to NR
	nfapi_nr_dl_tti_request_t* dl_tti_req;//nfapi_dl_config_request_t* dl_config_req; 
	nfapi_nr_ul_tti_request_t ul_tti_req;//nfapi_ul_config_request_t* ul_config_req;
  nfapi_nr_ul_dci_request_t ul_dci_req;//nfapi_hi_dci0_request_t* hi_dci0_req;
	nfapi_nr_tx_data_request_t tx_data_req;//nfapi_tx_request_t* tx_req;

	//TODO: check these two later
	//nfapi_lbt_dl_config_request_t* lbt_dl_config_req;
	//nfapi_ue_release_request_t* ue_release_req;
} nfapi_pnf_p7_slot_buffer_t;
```

reference

```c
typedef struct {
  nfapi_p7_message_header_t header;
  uint16_t SFN;
  uint16_t Slot;
  uint8_t  numPdus;
  nfapi_nr_ul_dci_request_pdus_t ul_dci_pdu_list[NFAPI_NR_MAX_NB_CORESETS];
} nfapi_nr_ul_dci_request_t;

```

## pnf_p7.c

```c

		if(tx_slot_buffer->ul_dci_req.numPdus > 0 && tx_slot_buffer->ul_dci_req.SFN == sfn_tx && tx_slot_buffer->ul_dci_req.Slot == slot_tx)
		{
			DevAssert(pnf_p7->_public.ul_dci_req_fn != NULL);
			LOG_D(PHY, "Process ul_dci SFN/slot %d.%d buffer index: %d \n",sfn_tx,slot_tx,buffer_index_tx);
			// pnf_phy_ul_dci_req()
     (pnf_p7->_public.ul_dci_req_fn)(NULL, &(pnf_p7->_public), &tx_slot_buffer->ul_dci_req);
		~~~~}

```

Remove

```c
		if(tx_slot_buffer->ul_dci_req != 0)
		{
			deallocate_nfapi_ul_dci_request(tx_slot_buffer->ul_dci_req, pnf_p7);
			tx_slot_buffer->ul_dci_req = 0;
		}
```

Add

```c
static void cp_nr_ul_dci_req(nfapi_nr_ul_dci_request_t *dst, const nfapi_nr_ul_dci_request_t *src)
{
    dst->header = src->header;
    dst->SFN = src->SFN;
    dst->Slot = src->Slot;
    dst->numPdus = src->numPdus;

    for (int i = 0; i < dst->numPdus; ++i) {
        dst->ul_dci_pdu_list[i] = src->ul_dci_pdu_list[i];
    }
}
```

Modify `pnf_handle_ul_dci_request`

```c
void pnf_handle_ul_dci_request(void* pRecvMsg, int recvMsgLen, pnf_p7_t* pnf_p7)
{
	//NFAPI_TRACE(NFAPI_TRACE_INFO, "HI_DCI0.req Received\n");

	nfapi_nr_ul_dci_request_t req;

	int unpack_result = nfapi_nr_p7_message_unpack(pRecvMsg, recvMsgLen, &req, sizeof(nfapi_nr_ul_dci_request_t), &pnf_p7->_public.codec_config);

	if(unpack_result == 0)
	{
		if(pthread_mutex_lock(&(pnf_p7->mutex)) != 0)
		{
			NFAPI_TRACE(NFAPI_TRACE_INFO, "failed to lock mutex\n");
			return;
		}

		if(is_nr_p7_request_in_window(req.SFN,req.Slot,"ul_dci_request", pnf_p7))
		{
			uint32_t sfn_slot_dec = NFAPI_SFNSLOT2DEC(req.SFN,req.Slot);
			uint8_t buffer_index = sfn_slot_dec % 20;

			pnf_p7->slot_buffer[buffer_index].sfn = req.SFN;
			cp_nr_ul_dci_req(&pnf_p7->slot_buffer[buffer_index].ul_dci_req, &req);

			pnf_p7->stats.ul_dci_ontime++;
			
		}
		else
		{
			if(pnf_p7->_public.timing_info_mode_aperiodic)
			{
				pnf_p7->timing_info_aperiodic_send = 1;
			}

			pnf_p7->stats.ul_dci_late++;
		}

		if(pthread_mutex_unlock(&(pnf_p7->mutex)) != 0)
		{
			NFAPI_TRACE(NFAPI_TRACE_INFO, "failed to unlock mutex\n");
			return;
		}
	}
	else
	{
		NFAPI_TRACE(NFAPI_TRACE_ERROR, "Failed to unpack UL DCI req\n");
	}
}
```

**do not allocate ul_dci on heap, introduces huge delay**

- Process ul_dci whenever the number of ul_dci PDUs in the buffer > 0.
- Using allocation on the stack instead of dynamic allocation on the heap.
- Create a new function, **`cp_nr_ul_dci_req`**, to copy the **`ul_dci_req`**.

```c
static void cp_nr_ul_dci_req(nfapi_nr_ul_dci_request_t *dst, const nfapi_nr_ul_dci_request_t *src)
{
  dst->header = src->header;
  dst->SFN = src->SFN;
  dst->Slot = src->Slot;
  dst->numPdus = src->numPdus;
  
  for (int i = 0; i < dst->numPdus; ++i) {
    nfapi_nr_ul_dci_request_pdus_t *dst_pdu = &dst->ul_dci_pdu_list[i];
    const nfapi_nr_ul_dci_request_pdus_t *src_pdu = &src->ul_dci_pdu_list[i];
    dst_pdu->PDUType = src_pdu->PDUType;
    dst_pdu->PDUSize = src_pdu->PDUSize;
    dst_pdu->pdcch_pdu = src_pdu->pdcch_pdu;
  }
}
```