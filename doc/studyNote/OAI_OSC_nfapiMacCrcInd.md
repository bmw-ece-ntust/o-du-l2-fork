# OAI_OSC_nfapiMacCrcInd

Start Date: 2024/05/31
Summary: Processes CRC indications from the OAI PHY in the OAI_OSC_nfapiMacCrcInd function.
Status: Done
Assign: 陳奕全
Tags: OSC Integration

```c
/*******************************************************************
 *
 * @brief Processes CRC Indication from OAI PHY
 *
 * @details
 *
 *    Function : OAI_OSC_nfapiMacCrcInd
 *
 *    Functionality:
 *       Processes CRC Indication from OAI PHY
 *
 * @params[in] Post Structure Pointer
 *             Crc Indication Pointer
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t OAI_OSC_nfapiMacCrcInd(Pst *pst, CrcInd *crcInd)
{
   uint16_t     cellIdx;
   CrcIndInfo   crcIndInfo;
   DU_LOG("\nDEBUG  -->  MAC : Received CRC indication from OAI PHY");
   GET_CELL_IDX(crcInd->cellId, cellIdx);
   /* Considering one pdu and one preamble */ 
   crcIndInfo.cellId = macCb.macCell[cellIdx]->cellId;
   crcIndInfo.crnti = crcInd->crcInfo[0].rnti;
   crcIndInfo.timingInfo.sfn = crcInd->timingInfo.sfn;
   crcIndInfo.timingInfo.slot = crcInd->timingInfo.slot;
   crcIndInfo.numCrcInd = crcInd->crcInfo[0].numCb;
   crcIndInfo.crcInd[0] = crcInd->crcInfo[0].cbCrcStatus[0];

   MAC_FREE_SHRABL_BUF(pst->region, pst->pool, crcInd, sizeof(CrcInd));
   return(sendCrcIndMacToSch(&crcIndInfo));
}

```