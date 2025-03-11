# TXdata code review

Start Date: 2024/09/05
Summary: Code review of TXdata functions, focusing on fill PDU functionality and necessary code adjustments.
Status: Done
Assign: 陳奕全

<aside>
👀

Fill PDU functions are correct, just need to comment or remove page message relate code in TX data request function.

![image.png](image%2047.png)

</aside>

```c
uint8_t OAI_OSC_fillDlMsgTxDataReq(nfapi_nr_pdu_t *pduDesc, uint16_t pduIndex, DlMsgSchInfo *dlMsgSchInfo, PdschCfg *pdschCfg)
{
   printf("\nDEBUG  -->  %s()\n", __FUNCTION__);
   uint16_t payloadSize;
   uint8_t  *dlMsgPayload = NULLP;

   pduDesc[pduIndex].PDU_index = pduIndex;
   pduDesc[pduIndex].num_TLV = 1;

   /* fill the TLV */
   payloadSize = pdschCfg->codeword[0].tbSize;
   pduDesc[pduIndex].TLVs[0].tag = FAPI_TX_DATA_PAYLOAD; //pack direct
   pduDesc[pduIndex].TLVs[0].length = payloadSize;
   LWR_MAC_ALLOC(dlMsgPayload, payloadSize);
   if(dlMsgPayload == NULLP)
   {
      return RFAILED;
   }
   memcpy(dlMsgPayload, dlMsgSchInfo->dlMsgPdu, dlMsgSchInfo->dlMsgPduLen);

   memcpy(pduDesc[pduIndex].TLVs[0].value.direct, dlMsgPayload, payloadSize);
   // pduDesc[pduIndex].TLVs[0].value.ptr = dlMsgPayload;
   pduDesc[pduIndex].PDU_length = payloadSize;

   LWR_MAC_FREE(dlMsgPayload, payloadSize);

   return ROK;
}
```

```c
uint8_t OAI_OSC_fillRarTxDataReq(nfapi_nr_pdu_t *pduDesc, uint16_t pduIndex, RarInfo *rarInfo, PdschCfg *pdschCfg)
{
   printf("\nDEBUG  -->  %s()\n", __FUNCTION__);
   uint16_t payloadSize;
   uint8_t  *rarPayload = NULLP;

   pduDesc[pduIndex].PDU_index = pduIndex;
   pduDesc[pduIndex].num_TLV = 1;

   /* fill the TLV */
   payloadSize = pdschCfg->codeword[0].tbSize;
   pduDesc[pduIndex].TLVs[0].tag = FAPI_TX_DATA_PAYLOAD; //pack direct
   pduDesc[pduIndex].TLVs[0].length = payloadSize;
   LWR_MAC_ALLOC(rarPayload, payloadSize);
   if(rarPayload == NULLP)
   {
      return RFAILED;
   }
   
   memcpy(rarPayload, rarInfo->rarPdu, rarInfo->rarPduLen);

   memcpy(pduDesc[pduIndex].TLVs[0].value.direct, rarPayload, payloadSize);
   // pduDesc[pduIndex].TLVs[0].value.direct = rarPayload;
   pduDesc[pduIndex].PDU_length = payloadSize;

   LWR_MAC_FREE(rarPayload, payloadSize);
   return ROK;
}

```