# searchspaceID

Start Date: 2024/06/18
Summary: Developing and modifying a common search space list for PDCCH configuration in a communication system.
Status: Reject
Assign: 陳奕全

OSC:

`BuildCommonSerachSpaceList` will build search space ID and only has one search space in this list

```c
duCfgParam.macCellCfg.cellCfg.initialDlBwp.pdcchCommon.commonSearchSpace.searchSpaceId = SEARCHSPACE_1_INDEX;
duCfgParam.macCellCfg.cellCfg.initialDlBwp.pdcchCommon.raSearchSpaceId = SEARCHSPACE_1_INDEX;
```

```c
            elementCnt = ODU_VALUE_THREE;
            pdcchSetup->commonSearchSpaceList->list.count = elementCnt;
            pdcchSetup->commonSearchSpaceList->list.size =  elementCnt * sizeof(SearchSpace_t *);
            ret = BuildCommonSerachSpaceList(pdcchSetup->commonSearchSpaceList);
```

Should be modify → use loop to fill 3 difference search space case 

```c

   for(idx = 0; idx < searchSpclist->list.count; idx++){
      searchSpace = searchSpclist->list.array[idx];

      /* Search Space id */
      // searchSpace->searchSpaceId = duPdcchCfg.searchSpcId;
      searchSpace->searchSpaceId = duPdcchCfg.searchSpcId+idx;

      /* Control Resource Set Id */
      DU_ALLOC(searchSpace->controlResourceSetId, sizeof(ControlResourceSetId_t));
      if(!searchSpace->controlResourceSetId)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      *searchSpace->controlResourceSetId = duPdcchCfg.ctrlRsrcSetId;

      /* Monitoring Slot periodicity and offset */
      DU_ALLOC(searchSpace->monitoringSlotPeriodicityAndOffset,\
            sizeof(struct SearchSpace__monitoringSlotPeriodicityAndOffset));
      if(!searchSpace->monitoringSlotPeriodicityAndOffset)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      searchSpace->monitoringSlotPeriodicityAndOffset->present = duPdcchCfg.monitorSlotPrdAndOffPresent;

      switch(searchSpace->monitoringSlotPeriodicityAndOffset->present)
      {
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1:
            {
               //searchSpace->monitoringSlotPeriodicityAndOffset->choice.s11 =  duPdcchCfg.monitorSlotPrdAndOff;
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl2:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl4:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl5:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl8:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl10:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl16:
            {
               //TODO;
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl20:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl40:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl80:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl160:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl320:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl640:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1280:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl2560:
            {
               //TODO
               break;
            }
         default:
            {
               DU_LOG("\nERROR  -->  DU APP : Invalid value:Montoring slot periodicity and offset");
               return RFAILED;
            }
      }

      /* Monitoring Symbols Within Slot */
      DU_ALLOC(searchSpace->monitoringSymbolsWithinSlot, sizeof(BIT_STRING_t));
      if(!searchSpace->monitoringSymbolsWithinSlot)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      searchSpace->monitoringSymbolsWithinSlot->size = 2 * sizeof(uint8_t);

      DU_ALLOC(searchSpace->monitoringSymbolsWithinSlot->buf, searchSpace->monitoringSymbolsWithinSlot->size);
      if(!searchSpace->monitoringSymbolsWithinSlot->buf)
      {  
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      searchSpace->monitoringSymbolsWithinSlot->buf[0] = duPdcchCfg.monitorSymbolsInSlot[0];
      searchSpace->monitoringSymbolsWithinSlot->buf[1] = duPdcchCfg.monitorSymbolsInSlot[1];
      searchSpace->monitoringSymbolsWithinSlot->bits_unused = 2;

      /* Number of candidates per aggregation level */
      DU_ALLOC(searchSpace->nrofCandidates, sizeof(struct SearchSpace__nrofCandidates));
      if(!searchSpace->nrofCandidates)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      searchSpace->nrofCandidates->aggregationLevel1 = duPdcchCfg.numCandAggLvl1;
      searchSpace->nrofCandidates->aggregationLevel2 = duPdcchCfg.numCandAggLvl2;
      searchSpace->nrofCandidates->aggregationLevel4 = duPdcchCfg.numCandAggLvl4;
      searchSpace->nrofCandidates->aggregationLevel8 = duPdcchCfg.numCandAggLvl8;
      searchSpace->nrofCandidates->aggregationLevel16 = duPdcchCfg.numCandAggLvl16;
   }
```

Fail decode 

![Untitled](Untitled%2042.png)

<aside>
👀 Maybe should modify 
1. Number of search space
2. aggregationLevel
3. searchSpaceType

</aside>

```c
   pdcchCfg.monitorSlotPrdAndOffPresent = SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1;
      
      
	 pdcchCfg.searchSpcType = SearchSpace__searchSpaceType_PR_common;

```

## Try to fix

```c
/*******************************************************************
 *
 * @brief Builds common search space list 
 *
 * @details
 *
 *    Function : BuildCommonSerachSpaceList
 *
 *    Functionality:
 *      Builds common search space list
 *
 * @params[in] PDCCH_ConfigCommon__commonSearchSpaceList pointer
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t BuildCommonSerachSpaceList( struct PDCCH_ConfigCommon__commonSearchSpaceList *searchSpclist)
{
   uint8_t idx;
   SearchSpace_t    *searchSpace;
   PdcchCfgCommon   duPdcchCfg;

   duPdcchCfg = duCfgParam.sib1Params.srvCellCfgCommSib.dlCfg.pdcchCfg;

   DU_ALLOC(searchSpclist->list.array, searchSpclist->list.size);
   if(!searchSpclist->list.array)
   {
      DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
      return RFAILED;
   }

   for(idx = 0; idx < searchSpclist->list.count; idx++)
   {
      DU_ALLOC(searchSpclist->list.array[idx], sizeof(SearchSpace_t));
      if(!searchSpclist->list.array[idx])
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
   }

   // idx = 0;
   for (idx = 0; idx < searchSpclist->list.count; idx++)
   {

      searchSpace = searchSpclist->list.array[idx];

      /* Search Space id */
      searchSpace->searchSpaceId = idx+1;//duPdcchCfg.searchSpcId;

      /* Control Resource Set Id */
      DU_ALLOC(searchSpace->controlResourceSetId, sizeof(ControlResourceSetId_t));
      if(!searchSpace->controlResourceSetId)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      *searchSpace->controlResourceSetId = duPdcchCfg.ctrlRsrcSetId;

      /* Monitoring Slot periodicity and offset */
      DU_ALLOC(searchSpace->monitoringSlotPeriodicityAndOffset,\
            sizeof(struct SearchSpace__monitoringSlotPeriodicityAndOffset));
      if(!searchSpace->monitoringSlotPeriodicityAndOffset)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      searchSpace->monitoringSlotPeriodicityAndOffset->present = duPdcchCfg.monitorSlotPrdAndOffPresent;

      switch(searchSpace->monitoringSlotPeriodicityAndOffset->present)
      {
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1:
            {
               //searchSpace->monitoringSlotPeriodicityAndOffset->choice.s11 =  duPdcchCfg.monitorSlotPrdAndOff;
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl2:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl4:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl5:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl8:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl10:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl16:
            {
               //TODO;
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl20:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl40:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl80:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl160:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl320:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl640:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1280:
            {
               //TODO
               break;
            }
         case SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl2560:
            {
               //TODO
               break;
            }
         default:
            {
               DU_LOG("\nERROR  -->  DU APP : Invalid value:Montoring slot periodicity and offset");
               return RFAILED;
            }
      }

      /* Monitoring Symbols Within Slot */
      DU_ALLOC(searchSpace->monitoringSymbolsWithinSlot, sizeof(BIT_STRING_t));
      if(!searchSpace->monitoringSymbolsWithinSlot)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
   /* ======== small cell integration ======== */
   #ifdef NFAPI
      searchSpace->monitoringSymbolsWithinSlot->size = 2;
   #else 
      searchSpace->monitoringSymbolsWithinSlot->size = 2 * sizeof(uint8_t);
   #endif
   /* ======================================== */
      DU_ALLOC(searchSpace->monitoringSymbolsWithinSlot->buf, searchSpace->monitoringSymbolsWithinSlot->size);
      if(!searchSpace->monitoringSymbolsWithinSlot->buf)
      {  
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      searchSpace->monitoringSymbolsWithinSlot->buf[0] = duPdcchCfg.monitorSymbolsInSlot[0];
      searchSpace->monitoringSymbolsWithinSlot->buf[1] = duPdcchCfg.monitorSymbolsInSlot[1];
      searchSpace->monitoringSymbolsWithinSlot->bits_unused = 2;

      /* Number of candidates per aggregation level */
      DU_ALLOC(searchSpace->nrofCandidates, sizeof(struct SearchSpace__nrofCandidates));
      if(!searchSpace->nrofCandidates)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      searchSpace->nrofCandidates->aggregationLevel1 = duPdcchCfg.numCandAggLvl1;
      searchSpace->nrofCandidates->aggregationLevel2 = duPdcchCfg.numCandAggLvl2;
      searchSpace->nrofCandidates->aggregationLevel4 = duPdcchCfg.numCandAggLvl4;
      searchSpace->nrofCandidates->aggregationLevel8 = duPdcchCfg.numCandAggLvl8;
      searchSpace->nrofCandidates->aggregationLevel16 = duPdcchCfg.numCandAggLvl16;

      DU_ALLOC(searchSpace->searchSpaceType, sizeof( struct SearchSpace__searchSpaceType));
      if(!searchSpace->searchSpaceType)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      DU_ALLOC(searchSpace->searchSpaceType->choice.common, sizeof(struct SearchSpace__searchSpaceType__common));
      if(!searchSpace->searchSpaceType->choice.common)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      
      DU_ALLOC(searchSpace->searchSpaceType->choice.common->dci_Format0_0_AndFormat1_0, \
         sizeof(struct SearchSpace__searchSpaceType__common__dci_Format0_0_AndFormat1_0));
      if(!searchSpace->searchSpaceType->choice.common->dci_Format0_0_AndFormat1_0)
      {
         DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
         return RFAILED;
      }
      
      searchSpace->searchSpaceType->present = duPdcchCfg.searchSpcType; 
   }

/* Commented due to ASN decode failure in wireshark.
 * Parameters like dci_Format0_0_AndFormat1_0 which are pointer to a structure that 
 * does not have any member parameter lead to decode failure in wireshark. 
 * The issue has been reported to Nokia.
 * The following code will be uncommented once the issue is resolved */
#if 0
   /* Search Space type and  DCI Format */
   DU_ALLOC(searchSpace->searchSpaceType, sizeof( struct SearchSpace__searchSpaceType));
   if(!searchSpace->searchSpaceType)
   {
      DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
      return RFAILED;
   }

   searchSpace->searchSpaceType->present = duPdcchCfg.searchSpcType; 
   switch(searchSpace->searchSpaceType->present)
   {
      case SearchSpace__searchSpaceType_PR_NOTHING:
         {
            //TODO
            break;
         }
      case SearchSpace__searchSpaceType_PR_common:
         {
            DU_ALLOC(searchSpace->searchSpaceType->choice.common, sizeof(struct SearchSpace__searchSpaceType__common));
            if(!searchSpace->searchSpaceType->choice.common)
            {
               DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
               return RFAILED;
            }
            
            searchSpace->searchSpaceType->choice.common->dci_Format0_0_AndFormat1_0 = NULLP;
            DU_ALLOC(searchSpace->searchSpaceType->choice.common->dci_Format0_0_AndFormat1_0, \
               sizeof(struct SearchSpace__searchSpaceType__common__dci_Format0_0_AndFormat1_0));
            if(!searchSpace->searchSpaceType->choice.common->dci_Format0_0_AndFormat1_0)
            {
               DU_LOG("\nERROR  -->  DU APP : Common search space list memory alloc failed");
               return RFAILED;
            }

            searchSpace->searchSpaceType->choice.common->dci_Format2_0 = NULLP;
            searchSpace->searchSpaceType->choice.common->dci_Format2_1 = NULLP;
            searchSpace->searchSpaceType->choice.common->dci_Format2_2 = NULLP;
            searchSpace->searchSpaceType->choice.common->dci_Format2_3 = NULLP;
            break;
         }
      case SearchSpace__searchSpaceType_PR_ue_Specific:
         {
            break;
         }
      default:
         {
            DU_LOG("\nERROR  -->  DU_APP: Invalid Search Space type");
            return RFAILED;
         }
   }
#endif

   return ROK;
}/* BuildCommonSerachSpaceList */
```