# OAI_OSC_nfapiMacRxDataInd

Start Date: 2024/05/31
Summary: The project involves processing received Rx Data indications at the MAC layer in a wireless communication system.
Status: Done
Assign: 陳奕全
Tags: OSC Integration

```c
/*******************************************************************
 *
 * @brief Process Rx Data Ind at MAC
 *
 * @details
 *
 *    Function : OAI_OSC_nfapiMacRxDataInd
 *
 *    Functionality:
 *       Process Rx Data Ind at MAC
 *
 * @params[in] Post structure
 *             Rx Data Indication
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t OAI_OSC_nfapiMacRxDataInd(Pst *pst, RxDataInd *rxDataInd)
{
   uint8_t ueId = 0;
   uint16_t pduIdx, cellIdx = 0;
   DU_LOG("\nDEBUG  -->  MAC : Received Rx Data indication from OAI PHY");
   /* TODO : compare the handle received in RxDataInd with handle send in PUSCH
    * PDU, which is stored in raCb */

   for(pduIdx = 0; pduIdx < rxDataInd->numPdus; pduIdx++)
   {

      GET_CELL_IDX(rxDataInd->cellId, cellIdx);
      GET_UE_ID(rxDataInd->pdus[pduIdx].rnti, ueId);
      
      if(macCb.macCell[cellIdx] && macCb.macCell[cellIdx]->ueCb[ueId -1].transmissionAction == STOP_TRANSMISSION)
      {
         DU_LOG("\nINFO   -->  MAC : UL data transmission not allowed for UE %d", macCb.macCell[cellIdx]->ueCb[ueId -1].ueId);
      }
      else
      {
         unpackRxData(rxDataInd->cellId, rxDataInd->timingInfo, &rxDataInd->pdus[pduIdx]);
      }
      MAC_FREE_SHRABL_BUF(pst->region, pst->pool, rxDataInd->pdus[pduIdx].pduData,\
         rxDataInd->pdus[pduIdx].pduLength);
   }
   MAC_FREE_SHRABL_BUF(pst->region, pst->pool, rxDataInd, sizeof(RxDataInd));
   return ROK;
}
```