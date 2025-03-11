# measure UL_DCI (some issues, don’t match Slot)

Start Date: 2024/04/16
Summary: Measuring UL_DCI performance and addressing issues related to slot matching in the transmission process.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全

Re-measure From [VNF] **`oai_nfapi_ul_dci_req`**  **to [PNF] `nr_generate_dci` is about 3ms.**

- Why for-loop only execute one time → `msgTx->num_ul_pdcch = 0;`
    - `msgTx->num_ul_pdcch` value always be `0` or `1` . For-loop maximum is execute one time.
    - So, I think we can move the code "msgTx->num_ul_pdcch set to zero" out of the for-loop, even though it is always 0 or 1, the for-loop will execute at most once.

```c
void nr_generate_dci_top(processingData_L1tx_t *msgTx,
                         int slot,
                         int32_t *txdataF,
                         int16_t amp,
                         NR_DL_FRAME_PARMS *frame_parms) {

  for (int i=0; i<msgTx->num_ul_pdcch; i++) {
    nr_generate_dci(msgTx->gNB,&msgTx->ul_pdcch_pdu[i].pdcch_pdu.pdcch_pdu_rel15,txdataF,amp,frame_parms,slot);
    msgTx->num_ul_pdcch = 0;
  }
  for (int i=0; i<msgTx->num_dl_pdcch; i++)
    nr_generate_dci(msgTx->gNB,&msgTx->pdcch_pdu[i].pdcch_pdu_rel15,txdataF,amp,frame_parms,slot);

}
```

[[Move the code "msgTx->num_ul_pdcch set to zero" out of the for-loop, even... (eb52a3f4) · Commits · oai / openairinterface5G · GitLab (eurecom.fr)](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/eb52a3f47637e8b10bbd8c44eda987cfde77ed45)](Move%20the%20code%20msgTx-%20num_ul_pdcch%20set%20to%20zero%20out%20%2012110098314381d493ecfc14070da20b.md)

## UL_DCI.request SFN/Slot are match between VNF and PNF.

![VNF send UL_DCI.request](Untitled%2033.png)

VNF send UL_DCI.request

![PNF handel UL DCI](Untitled%2034.png)

PNF handel UL DCI