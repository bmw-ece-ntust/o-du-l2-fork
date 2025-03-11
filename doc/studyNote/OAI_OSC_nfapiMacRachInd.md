# OAI_OSC_nfapiMacRachInd

Start Date: 2024/05/31
Summary: Processes RACH indications from OAI PHY and manages related information in the MAC layer.
Status: Done
Assign: 陳奕全
Tags: OSC Integration

```c
/*******************************************************************
 *
 * @brief Processes RACH indication from OAI PHY
 *
 * @details
 *
 *    Function : OAI_OSC_nfapiMacRachInd
 *
 *    Functionality:
 *      Processes RACH indication from OAI PHY
 *
 * @params[in] Post structure
 *             Rach indication message
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/ 
uint8_t OAI_OSC_nfapiMacRachInd(Pst *pst, RachInd *rachInd)
{
   uint8_t      ret = ROK;
   uint8_t      pduIdx = 0;
   uint8_t      preambleIdx = 0;
   uint16_t     cellIdx = 0;  
   RachIndInfo  *rachIndInfo = NULLP;
   MacCellCb    *cellCb = NULLP;

   DU_LOG("\nINFO  -->  MAC : Received RACH indication");
   /* Considering one pdu and one preamble */
   pduIdx = 0;
   preambleIdx = 0;

   /* Validate cell Id */
   GET_CELL_IDX(rachInd->cellId, cellIdx);
   if(macCb.macCell[cellIdx] && (macCb.macCell[cellIdx]->cellId == rachInd->cellId))
         cellCb = macCb.macCell[cellIdx];

   if(!cellCb)
   {
      DU_LOG("\nERROR  --> MAC : Invalid Cell ID [%d] received in RACH Indication", rachInd->cellId);
      return RFAILED;
   }

   MAC_ALLOC(rachIndInfo, sizeof(RachIndInfo));
   if(!rachIndInfo)
   {
      DU_LOG("\nERROR  --> MAC : Memory allocation failure in fapiMacRachInd");
      MAC_FREE_SHRABL_BUF(pst->region, pst->pool, rachInd, sizeof(RachInd));
      return RFAILED;
   }

   rachIndInfo->cellId = rachInd->cellId;
   rachIndInfo->timingInfo.sfn = rachInd->timingInfo.sfn;
   rachIndInfo->timingInfo.slot = rachInd->timingInfo.slot;
   rachIndInfo->slotIdx = rachInd->rachPdu[pduIdx].slotIdx;
   rachIndInfo->symbolIdx = rachInd->rachPdu[pduIdx].symbolIdx;
   rachIndInfo->freqIdx = rachInd->rachPdu[pduIdx].freqIdx;
   rachIndInfo->preambleIdx = rachInd->rachPdu[pduIdx].preamInfo[preambleIdx].preamIdx;
   rachIndInfo->timingAdv = rachInd->rachPdu[pduIdx].preamInfo[preambleIdx].timingAdv;

   /* Store the value in macRaCb */
   if((ret = createMacRaCb(cellCb, rachIndInfo)) == ROK)
   {
      /* Send RACH Indication to SCH */
      ret = sendRachIndMacToSch(rachIndInfo);
   }

   /* Free sharable buffer used to send RACH Indication from lower MAC to MAC */
   MAC_FREE_SHRABL_BUF(pst->region, pst->pool, rachInd, sizeof(RachInd));

   return ret;
}

```