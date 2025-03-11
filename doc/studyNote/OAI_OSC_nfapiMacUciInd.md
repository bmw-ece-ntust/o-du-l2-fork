# OAI_OSC_nfapiMacUciInd

Start Date: 2024/05/31
Summary: Processes UCI indications from OAI PHY in the OAI_OSC_nfapiMacUciInd function.
Status: Done
Assign: 陳奕全
Tags: OSC Integration

```c
/*******************************************************************
 *
 * @brief Processes UCI Indication from OAI PHY
 *
 * @details
 *
 *    Function : fapiMacUciInd
 *
 *    Functionality:
 *       Processes UCI Indication from OAI PHY
 *
 * @params[in] Post Structure Pointer
 *             UCI Indication Pointer
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t OAI_OSC_nfapiMacUciInd(Pst *pst, UciInd *macUciInd)
{
   uint8_t     pduIdx = 0, ret = ROK;
   uint16_t    nPdus = 0, crnti = 0, cellIdx = 0;

   if(macUciInd)
   {
      nPdus = macUciInd->numUcis;
      while(nPdus)
      {
         switch(macUciInd->pdus[pduIdx].pduType)
         {
            case UCI_IND_PUSCH:
               break;
            case UCI_IND_PUCCH_F0F1:
            {
               {
                  DU_LOG("\nDEBUG  -->  MAC : Received HARQ UCI Indication from OAI PHY\n");
                  GET_CELL_IDX(macUciInd->cellId, cellIdx);
                  buildAndSendHarqInd(&macUciInd->pdus[pduIdx].uci.uciPucchF0F1.harqInfo, macUciInd->pdus[pduIdx].uci.uciPucchF0F1.crnti, cellIdx, &macUciInd->slotInd);
               }
               if(macUciInd->pdus[pduIdx].uci.uciPucchF0F1.srInfo.srIndPres)
               {
                  DU_LOG("\nDEBUG  -->  MAC : Received SR UCI indication from OAI PHY");
                  crnti = macUciInd->pdus[pduIdx].uci.uciPucchF0F1.crnti; 
                  ret = buildAndSendSrInd(macUciInd, crnti);
               }
            }
               break;
            case UCI_IND_PUCCH_F2F3F4:
               break;
            default:
               DU_LOG("\nERROR  -->  MAC: Invalid Pdu Type %d at FapiMacUciInd", macUciInd->pdus[pduIdx].pduType);
               ret = RFAILED;
               break;
         }
         pduIdx++;
         nPdus--;
      }
   }
   else
   {
      DU_LOG("\nERROR  -->  MAC: Received Uci Ind is NULL at FapiMacUciInd()");
      ret = RFAILED;
   }
   MAC_FREE_SHRABL_BUF(pst->region, pst->pool, macUciInd, sizeof(UciInd));
   return ret;
}
```