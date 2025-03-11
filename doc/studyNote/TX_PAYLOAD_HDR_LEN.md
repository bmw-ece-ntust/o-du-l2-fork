# TX_PAYLOAD_HDR_LEN

Start Date: 2024/10/07
Summary: Implementing and defining the TX payload header length for Intel L1 in the context of MAC PDU processing and DL message transmission.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/08
SUM: 🗓️ Days Spent to Complete: 1

<aside>
💡

From the definition, it can be known that because the OSC design requires an additional 32-byte header for Intel L1, it is currently unnecessary to integrate OAI Layer1, so it should be completely removed.

</aside>

# Define

```cpp
#define TX_PAYLOAD_HDR_LEN 32           /* Intel L1 requires adding a 32 byte header to transmitted payload */
```

## SCH calculates TB size and fills in the DL_TTI PDSCH `tbsize` field.

```jsx
      if(isRetx != TRUE)
      {
         /* Intel L1 requires adding a 32 byte header to transmitted payload */
         tbSize = schCalcTbSize(msg4Alloc->dlMsgPduLen + 36); // TX_PAYLOAD_HDR_LEN /* MSG4 size + FAPI header size*/
         hqP->tbInfo[cwCount].tbSzReq = tbSize;
         pdsch->codeword[cwCount].rvIndex = 0;
      }
```

## **fillMsg4Pdu()**

It will call `macMuxPdu()`

```
   hqProcCb = &macCb.macCell[cellIdx]->macRaCb[ueIdx].msg4HqInfo;
   msg4TxPduLen = hqProcCb->tbInfo[0].tbSize - 36; // TX_PAYLOAD_HDR_LEN
   if(macCb.macCell[cellIdx]->macRaCb[ueIdx].msg4Pdu != NULLP)
   {
      MAC_ALLOC(msg4DlData.pduInfo[msg4DlData.numPdu].dlPdu, macCb.macCell[cellIdx]->macRaCb[ueIdx].msg4PduLen);
      if(msg4DlData.pduInfo[msg4DlData.numPdu].dlPdu != NULLP)
      {
         fillMsg4DlData(&msg4DlData, macCb.macCell[cellIdx]->macRaCb[ueIdx].msg4PduLen, \
            macCb.macCell[cellIdx]->macRaCb[ueIdx].msg4Pdu);
         fillMacCe(&macCeData, macCb.macCell[cellIdx]->macRaCb[ueIdx].msg3Pdu);

         /* Forming Mux Pdu */
         hqProcCb->tbInfo[0].tb = NULLP;
         MAC_ALLOC(hqProcCb->tbInfo[0].tb, msg4TxPduLen);
         if(hqProcCb->tbInfo[0].tb != NULLP)
         {
            memset(hqProcCb->tbInfo[0].tb, 0, msg4TxPduLen);
            macMuxPdu(&msg4DlData, &macCeData, hqProcCb->tbInfo[0].tb, msg4TxPduLen);
         }
```

## macMuxPdu(): **The MAC PDU will be MUXed and formed**

- **(14 Byte)** /* Packing fields into MAC PDU R/R/LCID */ → Fill **macCeData**
- **(lenField + 16 Byte)** /* Packing fields into MAC PDU R/F/LCID/L */ → Fill **macCeData**
- **(7 Byte)** /* padding remaining bytes */
- **Total: 37 Byte + lenField**

```c
void macMuxPdu(MacDlData *dlData, MacCeInfo *macCeData, uint8_t *txPdu, uint16_t tbSize)
{
   uint16_t bytePos = 0;
   uint8_t bitPos = 7;
   uint8_t pduIdx = 0;
   printf("\n[MAC] tbSize = %d\n", tbSize);
   uint8_t macPdu[tbSize];
   memset(macPdu, 0, (tbSize * sizeof(uint8_t)));

   /* subheader fields */
   uint8_t RBit = 0;              /* Reserved bit */
   uint8_t FBit =0;                  /* Format Indicator */
   uint8_t lcid =0;                  /* LCID */
   uint16_t lenField = 0;         /* Length field */

   /* subheader field size (in bits) */
   uint8_t RBitSize = 1;
   uint8_t FBitSize = 1;
   uint8_t lcidSize = 6;
   uint8_t lenFieldSize = 0;      /* 8-bit or 16-bit L field  */

   /* Total: lenField + 37 = */

   /* PACK ALL MAC CE */
   if(macCeData != NULLP)
   {
      for(pduIdx = 0; pduIdx < macCeData->numCes; pduIdx++)
      {
         lcid = macCeData->macCe[pduIdx].macCeLcid;
         switch(lcid)
         {
            case MAC_LCID_CRI:
               {
                  /* Packing fields into MAC PDU R/R/LCID */
                  /* 2 + 6 + 6 = 14 */
                  printf("[Start] bytePos = %d, bitPos = %d\n", bytePos, bitPos);
                  packBytes(macPdu, &bytePos, &bitPos, RBit, (RBitSize * 2));
                  printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
                  packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
                  printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
                  memcpy(&macPdu[bytePos], macCeData->macCe[pduIdx].macCeValue,\
                        MAX_CRI_SIZE);
                  bytePos += MAX_CRI_SIZE;
                  break;
               }
            default:
               DU_LOG("\nERROR  -->  MAC: Invalid LCID %d in mac pdu",lcid);
               break;
         }
      }
   }

   /* PACK ALL MAC SDUs */
   for(pduIdx = 0; pduIdx < dlData->numPdu; pduIdx++)
   {
      lcid = dlData->pduInfo[pduIdx].lcId;
      switch(lcid)
      {
         case MAC_LCID_CCCH:
         case MAC_LCID_MIN ... MAC_LCID_MAX :
            {
               lenField = dlData->pduInfo[pduIdx].pduLen;
               printf("\nlenField = %d\n", lenField);
               lenField = 137;
               if(dlData->pduInfo[pduIdx].pduLen > 255)
               {
                  FBit = 1;
                  lenFieldSize = 16;

               }
               else
               {
                  FBit = 0;
                  lenFieldSize = 8;
               }
               /* Packing fields into MAC PDU R/F/LCID/L */
               /* 1 + 1 + 6 + 8 + lenField = lenField + 16*/
               packBytes(macPdu, &bytePos, &bitPos, RBit, RBitSize);
               printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
               packBytes(macPdu, &bytePos, &bitPos, FBit, FBitSize);
               printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
               packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
               printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
               packBytes(macPdu, &bytePos, &bitPos, lenField, lenFieldSize);
               printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
               memcpy(&macPdu[bytePos], dlData->pduInfo[pduIdx].dlPdu, lenField);
               bytePos += lenField;
               printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
               break;
            }

         default:
            DU_LOG("\nERROR  -->  MAC: Invalid LCID %d in mac pdu",lcid);
            break;
      }
   }
   if(bytePos < tbSize && (tbSize-bytePos >= 1))
   {
      /* padding remaining bytes */
      /* 1 + 6 = 7*/
      RBitSize = 2;
      lcid = MAC_LCID_PADDING;
      packBytes(macPdu, &bytePos, &bitPos, RBit, RBitSize);
      printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
      packBytes(macPdu, &bytePos, &bitPos, lcid, lcidSize);
      printf("bytePos = %d, bitPos = %d\n", bytePos, bitPos);
   }

   /*Storing the muxed pdu */
   if(txPdu != NULLP)
   {
      memcpy(txPdu, macPdu, tbSize);
   }
}
```

# In DLMSG case OSC develop a new function to fill TX_Data

```c
            if(dlSlot->dlInfo.dlMsgAlloc[ueIdx]->dlMsgPdschCfg) 
            {
               fillDlMsgTxDataReq(txDataReq->pdu_desc, pduIndex, \
                     dlSlot->dlInfo.dlMsgAlloc[ueIdx], \
                     dlSlot->dlInfo.dlMsgAlloc[ueIdx]->dlMsgPdschCfg);
               pduIndex++;
               txDataReq->num_pdus++;
               MAC_FREE(dlSlot->dlInfo.dlMsgAlloc[ueIdx]->dlMsgPdschCfg,sizeof(PdschCfg));
            }
```

```jsx
uint8_t fillDlMsgTxDataReq(fapi_tx_pdu_desc_t *pduDesc, uint16_t pduIndex, DlMsgSchInfo *dlMsgSchInfo, PdschCfg *pdschCfg)
{
   printf("[fillDlMsgTxDataReq] pdschCfg->codeword[0].tbSize: %d, dlMsgSchInfo->dlMsgPduLen: %d\n", pdschCfg->codeword[0].tbSize, dlMsgSchInfo->dlMsgPduLen);
   uint16_t payloadSize;
   uint8_t  *dlMsgPayload = NULLP;
   fapi_api_queue_elem_t *payloadElem = NULLP;
#ifdef INTEL_WLS_MEM
   void * wlsHdlr = NULLP;
#endif

   pduDesc[pduIndex].pdu_index = pduIndex;
   pduDesc[pduIndex].num_tlvs = 1;

   /* fill the TLV */
   payloadSize = pdschCfg->codeword[0].tbSize;
   pduDesc[pduIndex].tlvs[0].tl.tag = FAPI_TX_DATA_PTR_TO_PAYLOAD_64;
   pduDesc[pduIndex].tlvs[0].tl.length = payloadSize;
   LWR_MAC_ALLOC(dlMsgPayload, payloadSize);
   if(dlMsgPayload == NULLP)
   {
      return RFAILED;
   }
   payloadElem = (fapi_api_queue_elem_t *)dlMsgPayload;
   FILL_FAPI_LIST_ELEM(payloadElem, NULLP, FAPI_VENDOR_MSG_PHY_ZBC_BLOCK_REQ, 1, dlMsgSchInfo->dlMsgPduLen);
   memcpy(dlMsgPayload + TX_PAYLOAD_HDR_LEN, dlMsgSchInfo->dlMsgPdu, dlMsgSchInfo->dlMsgPduLen);

#ifdef INTEL_WLS_MEM
   mtGetWlsHdl(&wlsHdlr);
   pduDesc[pduIndex].tlvs[0].value = (uint8_t *)(WLS_VA2PA(wlsHdlr, dlMsgPayload));
#else
   pduDesc[pduIndex].tlvs[0].value = dlMsgPayload;
#endif
   pduDesc[pduIndex].pdu_length = payloadSize;

#ifdef INTEL_WLS_MEM
   addWlsBlockToFree(dlMsgPayload, payloadSize, (lwrMacCb.phySlotIndCntr-1));
#else
   LWR_MAC_FREE(dlMsgPayload, payloadSize);
#endif
   return ROK;
}
```

## Updated Function for NFAPI Integration

```c
uint8_t OAI_OSC_fillDlMsgTxDataReq(nfapi_nr_pdu_t *pduDesc, uint16_t pduIndex, DlMsgSchInfo *dlMsgSchInfo, PdschCfg *pdschCfg)
{
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