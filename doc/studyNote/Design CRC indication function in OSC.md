# Design CRC.indication function in OSC

Start Date: 2024/06/20
Summary: Designing the CRC indication function for the Open Source Community (OSC) based on existing OAI code to improve data handling in communication systems.
Status: Done
Assign: 陳奕全

TODO: Check how to use CRC indication

<aside>
👀 Refer to OAI's code to design the OSC code using crc.indication.

</aside>

## CRC.indication unqueue_matching

OAI example:

```c
    if (gnb_rx_ind_queue.num_items > 0 && gnb_crc_ind_queue.num_items > 0) {
      LOG_D(NR_MAC, "gnb_rx_ind_queue size = %zu and gnb_crc_ind_queue size = %zu\n",
            gnb_rx_ind_queue.num_items, gnb_crc_ind_queue.num_items);
      rx_ind = get_queue(&gnb_rx_ind_queue);
      int sfn_slot = NFAPI_SFNSLOT2HEX(rx_ind->sfn, rx_ind->slot);
      crc_ind = unqueue_matching(&gnb_crc_ind_queue,
                                 MAX_QUEUE_SIZE,
                                 crc_sfn_slot_matcher,
                                 &sfn_slot);
      if (!crc_ind) {
        LOG_I(NR_PHY, "No crc indication with the same SFN SLOT of rx indication %u %u\n", rx_ind->sfn, rx_ind->slot);
        requeue(&gnb_rx_ind_queue, rx_ind);
      }
      else {
        AssertFatal(rx_ind->number_of_pdus > 0, "Invalid number of PDUs\n");
        AssertFatal(crc_ind->number_crcs > 0, "Invalid number of PDUs\n");
        if (crc_ind->number_crcs != rx_ind->number_of_pdus)
          match_crc_rx_pdu(rx_ind, crc_ind);
        UL_info->rx_ind = *rx_ind;
        UL_info->crc_ind = *crc_ind;
      }
    }
```

I design for OSC:

```c
		if (gnb_rx_ind_queue.num_items > 0 && gnb_crc_ind_queue.num_items > 0) {
			nfapi_nr_rx_data_indication_t *rx_ind = get_queue(&gnb_rx_ind_queue);
			// printf("[NTUST]	rx indication: %d\n", rx_ind);
			printf("[NTUST]	rx indication: %d, size: %d\n", rx_ind, gnb_rx_ind_queue.num_items);
			// TODO: Check how to use CRC indication
			int sfn_slot = NFAPI_SFNSLOT2HEX(rx_ind->sfn, rx_ind->slot);
      		nfapi_nr_crc_indication_t *crc_ind = unqueue_matching(&gnb_crc_ind_queue,
                                 MAX_QUEUE_SIZE,
                                 crc_sfn_slot_matcher,
                                 &sfn_slot);
			if (!crc_ind) {
				printf("No crc indication with the same SFN SLOT of rx indication %u %u\n", rx_ind->sfn, rx_ind->slot);
				requeue(&gnb_rx_ind_queue, rx_ind);
      		}
			else {
				// printf("[NTUST]	crc indication: %d\n", crc_ind);
				printf("[NTUST]	crc indication: %d, size: %d\n", crc_ind, gnb_crc_ind_queue.num_items);
				// TODO : Match CRC and RX PDU
				UL_INFO.rx_ind = *rx_ind;
				UL_INFO.crc_ind = *crc_ind;
			}
		}
```

```c
      nfapi_nr_crc_indication_t *crc_ind = unqueue_matching(&gnb_crc_ind_queue,
                                 MAX_QUEUE_SIZE,
                                 crc_sfn_slot_matcher,
                                 &sfn_slot);
```

Add new function `crc_sfn_slot_matcher` from OAI

```c
/* ======== small cell integration ======== */
static bool crc_sfn_slot_matcher(void *wanted, void *candidate)
{
  nfapi_p7_message_header_t *msg = candidate;
  int sfn_sf = *(int*)wanted;

  switch (msg->message_id)
  {
    case NFAPI_NR_PHY_MSG_TYPE_CRC_INDICATION:
    {
      nfapi_nr_crc_indication_t *ind = candidate;
      return NFAPI_SFNSLOT2SFN(sfn_sf) == ind->sfn && NFAPI_SFNSLOT2SLOT(sfn_sf) == ind->slot;
    }

    default:
      printf("sfn_slot_match bad ID: %d\n", msg->message_id);

  }
  return false;
}
/* ======================================== */
```

---

## CRC.indication process

OAI:

```c
if (UL_info->rx_ind.number_of_pdus > 0 && UL_info->crc_ind.number_crcs > 0) {
    // see nr_fill_indication about why this mutex is necessary
    int rc = pthread_mutex_lock(&UL_info->crc_rx_mutex);
    DevAssert(rc == 0);
    AssertFatal(UL_info->rx_ind.number_of_pdus == UL_info->crc_ind.number_crcs,
                "number_of_pdus %d, number_crcs %d\n",
                UL_info->rx_ind.number_of_pdus, UL_info->crc_ind.number_crcs);
    for (int i = 0; i < UL_info->rx_ind.number_of_pdus; i++) {
      const nfapi_nr_rx_data_pdu_t *rx = &UL_info->rx_ind.pdu_list[i];
      const nfapi_nr_crc_t *crc = &UL_info->crc_ind.crc_list[i];
      LOG_D(NR_PHY, "UL_info->crc_ind.pdu_list[%d].rnti:%04x "
                    "UL_info->rx_ind.pdu_list[%d].rnti:%04x\n",
                    i, crc->rnti, i, rx->rnti);

      AssertFatal(crc->rnti == rx->rnti, "mis-match between CRC RNTI %04x and RX RNTI %04x\n",
                  crc->rnti, rx->rnti);

      LOG_D(NR_MAC,
            "%4d.%2d Calling rx_sdu (CRC %s/tb_crc_status %d)\n",
            UL_info->frame,
            UL_info->slot,
            crc->tb_crc_status ? "error" : "ok",
            crc->tb_crc_status);

      /* if CRC passes, pass PDU, otherwise pass NULL as error indication */
      nr_rx_sdu(UL_info->module_id,
                UL_info->CC_id,
                UL_info->rx_ind.sfn,
                UL_info->rx_ind.slot,
                crc->rnti,
                crc->tb_crc_status ? NULL : rx->pdu,
                rx->pdu_length,
                crc->timing_advance,
                crc->ul_cqi,
                crc->rssi);
      handle_nr_ul_harq(UL_info->CC_id, UL_info->module_id, UL_info->frame, UL_info->slot, crc);
    }
    UL_info->rx_ind.number_of_pdus = 0;
    UL_info->crc_ind.number_crcs = 0;
    rc = pthread_mutex_unlock(&UL_info->crc_rx_mutex);
    DevAssert(rc == 0);
  }
```

```c
				if (UL_INFO.rx_ind.number_of_pdus > 0){
					SCF_procRxDataInd(&UL_INFO.rx_ind);
					UL_INFO.rx_ind.number_of_pdus = 0;
				}
```

I design for OSC:

```c
if (UL_INFO.rx_ind.number_of_pdus > 0 && UL_INFO.crc_ind.number_crcs > 0){
	SCF_procRxDataInd(&UL_INFO.rx_ind);
	SCF_procCrcInd(&UL_INFO.crc_ind);
	UL_INFO.rx_ind.number_of_pdus = 0;
	UL_INFO.crc_ind.number_crcs = 0;
}

```

---

## Match crc and rx PDU

```c
      else {
        AssertFatal(rx_ind->number_of_pdus > 0, "Invalid number of PDUs\n");
        AssertFatal(crc_ind->number_crcs > 0, "Invalid number of PDUs\n");
        if (crc_ind->number_crcs != rx_ind->number_of_pdus)
          match_crc_rx_pdu(rx_ind, crc_ind);
        UL_info->rx_ind = *rx_ind;
        UL_info->crc_ind = *crc_ind;
      }
```

Copy from OAI

```c
/* ======== small cell integration ======== */
static void match_crc_rx_pdu(nfapi_nr_rx_data_indication_t *rx_ind, nfapi_nr_crc_indication_t *crc_ind) {
  if (crc_ind->number_crcs > rx_ind->number_of_pdus) {
    int num_unmatched_crcs = 0;
    nfapi_nr_crc_indication_t *crc_ind_unmatched = calloc(1, sizeof(*crc_ind_unmatched));
    crc_ind_unmatched->header = crc_ind->header;
    crc_ind_unmatched->sfn = crc_ind->sfn;
    crc_ind_unmatched->slot = crc_ind->slot;
    crc_ind_unmatched->number_crcs = crc_ind->number_crcs - rx_ind->number_of_pdus;
    crc_ind_unmatched->crc_list = calloc(crc_ind_unmatched->number_crcs, sizeof(nfapi_nr_crc_t));
    for (int i = 0; i < crc_ind->number_crcs; i++) {
      if (!rx_ind_has_rnti(rx_ind, crc_ind->crc_list[i].rnti)) {
          printf("crc_ind->crc_list[%d].rnti %x does not match any rx_ind pdu rnti\n",
                i, crc_ind->crc_list[i].rnti);
          crc_ind_unmatched->crc_list[num_unmatched_crcs] = crc_ind->crc_list[i];
          num_unmatched_crcs++;
          remove_crc_pdu(crc_ind, i);
      }
      if (crc_ind->number_crcs == rx_ind->number_of_pdus) {
        break;
      }
    }
    if (!requeue(&gnb_crc_ind_queue, crc_ind_unmatched))
    {
      printf("requeue failed for crc_ind_unmatched.\n");
      free(crc_ind_unmatched->crc_list);
      crc_ind_unmatched->crc_list = NULL;
      free(crc_ind_unmatched);
      crc_ind_unmatched = NULL;
    }
  }
  else if (crc_ind->number_crcs < rx_ind->number_of_pdus) {
    int num_unmatched_rxs = 0;
    nfapi_nr_rx_data_indication_t *rx_ind_unmatched = calloc(1, sizeof(*rx_ind_unmatched));
    rx_ind_unmatched->header = rx_ind->header;
    rx_ind_unmatched->sfn = rx_ind->sfn;
    rx_ind_unmatched->slot = rx_ind->slot;
    rx_ind_unmatched->number_of_pdus = rx_ind->number_of_pdus - crc_ind->number_crcs;
    rx_ind_unmatched->pdu_list = calloc(rx_ind_unmatched->number_of_pdus, sizeof(nfapi_nr_pdu_t));
    for (int i = 0; i < rx_ind->number_of_pdus; i++) {
      if (!crc_ind_has_rnti(crc_ind, rx_ind->pdu_list[i].rnti)) {
        printf("rx_ind->pdu_list[%d].rnti %d does not match any crc_ind pdu rnti\n",
              i, rx_ind->pdu_list[i].rnti);
        rx_ind_unmatched->pdu_list[num_unmatched_rxs] = rx_ind->pdu_list[i];
        num_unmatched_rxs++;
        remove_rx_pdu(rx_ind, i);
      }
      if (rx_ind->number_of_pdus == crc_ind->number_crcs) {
        break;
      }
    }
    if (!requeue(&gnb_rx_ind_queue, rx_ind_unmatched))
    {
      printf("requeue failed for rx_ind_unmatched.\n");
      free(rx_ind_unmatched->pdu_list);
      rx_ind_unmatched->pdu_list = NULL;
      free(rx_ind_unmatched);
      rx_ind_unmatched = NULL;
    }
  }
  else {
    printf("The number of crc pdus %d = the number of rx pdus %d\n",
          crc_ind->number_crcs, rx_ind->number_of_pdus);
  }
}
/* ======================================== */
```

## Remove and has RNTI function

rx_ind_has_rnti

```c
/* ======== small cell integration ======== */
static bool rx_ind_has_rnti(nfapi_nr_rx_data_indication_t *rx_ind, uint16_t rnti) {
  for (int i = 0; i < rx_ind->number_of_pdus; i++) {
    if (rnti == rx_ind->pdu_list[i].rnti) {
      return true;
    }
  }
  return false;
}
/* ======================================== */
```

remove_crc_pdu

```c
/* ======== small cell integration ======== */
static void remove_crc_pdu(nfapi_nr_crc_indication_t *crc_ind, int index) {
  memmove(crc_ind->crc_list + index,
          crc_ind->crc_list + index + 1,
          sizeof(*crc_ind->crc_list) * (crc_ind->number_crcs - index - 1));
  crc_ind->number_crcs--;
}
/* ======================================== */
```

crc_ind_has_rnti

```c
/* ======== small cell integration ======== */
static bool crc_ind_has_rnti(nfapi_nr_crc_indication_t *crc_ind, uint16_t rnti) {
  for (int i = 0; i < crc_ind->number_crcs; i++) {
    if (rnti == crc_ind->crc_list[i].rnti) {
      return true;
    }
  }
  return false;
}
/* ======================================== */
```

remove_rx_pdu

```c
/* ======== small cell integration ======== */
static void remove_rx_pdu(nfapi_nr_rx_data_indication_t *rx_ind, int index) {
  memmove(rx_ind->pdu_list + index,
          rx_ind->pdu_list + index + 1,
          sizeof(*rx_ind->pdu_list) * (rx_ind->number_of_pdus - index - 1));
  rx_ind->number_of_pdus--;
}
/* ======================================== */
```