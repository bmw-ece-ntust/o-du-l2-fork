# PRB start

Start Date: 2024/10/17
Summary: Defines and allocates Physical Resource Blocks (PRB) for 5G NR systems while addressing implementation differences between OAI and OSC.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/18
SUM: 🗓️ Days Spent to Complete: 1

## Summary

- Defines maximum transmission bandwidth for 5G NR systems
- Discusses PRB allocation based on 3GPP specifications (38.101, Section 5.3.2)
- Covers PDCCH DCI configuration, including frequency domain resource allocation
- Explains PDSCH configuration, particularly startPrb and numPrb calculations
- Compares OAI and OSC implementations, highlighting differences in startPrb and coreset0Size

## Define Maximum transmission bandwidth

![image.png](image%2089.png)

```c
/* PRB allocation as per 38.101, Section 5.3.2 */
#define TOTAL_PRB_20MHZ_MU0 106
#define TOTAL_PRB_100MHZ_MU1 273
#ifdef NR_TDD
   #ifdef NFAPI
      #define MAX_NUM_RB TOTAL_PRB_100MHZ_MU1  /*//Use OSC 100MHz value for numerology 1, 100 MHz */
   #else
      #define MAX_NUM_RB TOTAL_PRB_100MHZ_MU1  /* value for numerology 1, 100 MHz */
   #endif
#else
#define MAX_NUM_RB TOTAL_PRB_20MHZ_MU0 /* value for numerology 0, 20 MHz */
#endif
```

## PDCCH DCI

![image.png](image%2090.png)

```c
      /* Calculating freq domain resource allocation field value and size
       * coreset0Size = Size of coreset 0
       * RBStart = Starting Virtual Rsource block
       * RBLen = length of contiguously allocted RBs
       * Spec 38.214 Sec 5.1.2.2.2
       */
      coreset0Size= sib1PdcchInfo->coresetCfg.coreSetSize;
      rbStart = sib1PdcchInfo->dci.pdschCfg.pdschFreqAlloc.startPrb;
      rbLen = sib1PdcchInfo->dci.pdschCfg.pdschFreqAlloc.numPrb;
      int BWPsize = coreset0Size;
      if((rbLen >=1) && (rbLen <= BWPsize - rbStart)) {
         if((rbLen - 1) <= floor(BWPsize / 2))
            freqDomResAssign = (BWPsize * (rbLen-1)) + rbStart;
         else
            freqDomResAssign = (BWPsize * (BWPsize - rbLen + 1)) \
                     + (BWPsize - 1 - rbStart);
         freqDomResAssignSize = ceil(log2(BWPsize * (BWPsize + 1) / 2));
      }
```

## PDSCH

```c
   pdsch->pdschFreqAlloc.startPrb = MAX_NUM_RB;
   pdsch->pdschFreqAlloc.numPrb = schCalcNumPrb(tbSize, mcs, pdschNumSymbols);
```

- In `allocatePrbDl`

```c
   /* If startPrb is set to MAX_NUM_RB, it means startPrb is not known currently.
    * Search for an appropriate location in PRB grid and allocate requested resources */
```

### allocatePrbDl

```bash
/*******************************************************************
 *
 * @brief Allocates requested PRBs for DL
 *
 * @details
 *
 *    Function : allocatePrbDl
 *
 *    Functionality:
 *      Allocates requested PRBs in DL
 *      Keeps track of allocated PRB (using bitmap) and remaining PRBs
 *
 * @params[in] prbAlloc table
 *             Start symbol
 *             Number of symbols
 *             Start PRB
 *             Number of PRBs
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t allocatePrbDl(SchCellCb *cell, SlotTimingInfo slotTime, \
   uint8_t startSymbol, uint8_t symbolLength, uint16_t *startPrb, uint16_t numPrb)
{
   uint8_t        symbol = 0;
   uint16_t       broadcastPrbStart=0, broadcastPrbEnd=0;
   FreePrbBlock   *freePrbBlock = NULLP;
   CmLList        *freePrbNode = NULLP;
   PduTxOccsaion  ssbOccasion=0, sib1Occasion=0;
   SchDlSlotInfo  *schDlSlotInfo = cell->schDlSlotInfo[slotTime.slot];
   SchPrbAlloc    *prbAlloc = &schDlSlotInfo->prbAlloc;

   /* If startPrb is set to MAX_NUM_RB, it means startPrb is not known currently.
    * Search for an appropriate location in PRB grid and allocate requested resources */
   if(*startPrb == MAX_NUM_RB)
   {
      /* Check if SSB/SIB1 is also scheduled in this slot  */
      ssbOccasion = schCheckSsbOcc(cell, slotTime);
      sib1Occasion = schCheckSib1Occ(cell, slotTime);

      if(ssbOccasion && sib1Occasion)
      {
         broadcastPrbStart = cell->cellCfg.dlCfgCommon.schFreqInfoDlSib.offsetToPointA; 
         broadcastPrbEnd = broadcastPrbStart + SCH_SSB_NUM_PRB + cell->sib1SchCfg.sib1PdcchCfg.dci[0].pdschCfg.pdschFreqAlloc.numPrb -1;
      }
      else if(ssbOccasion)
      {
         broadcastPrbStart = cell->cellCfg.dlCfgCommon.schFreqInfoDlSib.offsetToPointA;
         broadcastPrbEnd = broadcastPrbStart + SCH_SSB_NUM_PRB -1;
      }
      else if(sib1Occasion)
      {
         broadcastPrbStart = cell->sib1SchCfg.sib1PdcchCfg.dci[0].pdschCfg.pdschFreqAlloc.startPrb;
         broadcastPrbEnd = broadcastPrbStart + cell->sib1SchCfg.sib1PdcchCfg.dci[0].pdschCfg.pdschFreqAlloc.numPrb -1;
      }

      /* Iterate through all free PRB blocks */
      freePrbNode = prbAlloc->freePrbBlockList.first; 
      while(freePrbNode)
      {
         freePrbBlock = (FreePrbBlock *)freePrbNode->node; 

         /* If broadcast message is scheduled in this slot, then check if its PRBs belong to the current free block.
          * Since SSB/SIB1 PRB location is fixed, these PRBs cannot be allocated to other message in same slot */
         if((ssbOccasion || sib1Occasion) && 
            ((broadcastPrbStart >= freePrbBlock->startPrb) && (broadcastPrbStart <= freePrbBlock->endPrb)) && \
            ((broadcastPrbEnd >= freePrbBlock->startPrb) && (broadcastPrbEnd <= freePrbBlock->endPrb)))
         {
            /* Implmentation is done such that highest-numbered free-RB is allocated first */ 
            if((freePrbBlock->endPrb > broadcastPrbEnd) && ((freePrbBlock->endPrb - broadcastPrbEnd) >= numPrb))
            {
               /* If sufficient free PRBs are available above bradcast message then,
                * endPrb = freePrbBlock->endPrb
                * startPrb = endPrb - numPrb +1;
                */
               *startPrb = freePrbBlock->endPrb - numPrb +1;
               break;
            }
            else if((broadcastPrbStart > freePrbBlock->startPrb) && ((broadcastPrbStart - freePrbBlock->startPrb) >= numPrb))
            {
               /* If free PRBs are available below broadcast message then,
                * endPrb = broadcastPrbStart - 1
                * startPrb = endPrb - numPrb +1
                */
               *startPrb = broadcastPrbStart - numPrb; 
               break;
            }
            else
            {
               freePrbNode = freePrbNode->next;
               continue;
            }
         }
         else
         {
            /* Check if requested number of blocks can be allocated from the current block */ 
            if (freePrbBlock->numFreePrb < numPrb)
            {
               freePrbNode = freePrbNode->next;
               continue;
            }
            *startPrb = freePrbBlock->endPrb - numPrb +1;
            break;  
         }
      }

      /* If no free block can be used to allocated request number of RBs */
      if(*startPrb == MAX_NUM_RB)
         return RFAILED;
   }

   /* If startPrb is known already, check if requested PRBs are available for allocation */
   else
   {
      freePrbNode = isPrbAvailable(&prbAlloc->freePrbBlockList, *startPrb, numPrb);
      if(!freePrbNode)
      {
         DU_LOG("\nERROR  -->  SCH: Requested DL PRB unavailable");
         return RFAILED;
      }
   }

   /* Update bitmap to allocate PRBs */
   for(symbol=startSymbol; symbol < (startSymbol+symbolLength); symbol++)
   {
      if(fillPrbBitmap(prbAlloc->prbBitMap[symbol], *startPrb, numPrb) != ROK)
      {
         DU_LOG("\nERROR  -->  SCH: fillPrbBitmap() failed for symbol [%d] in DL", symbol);
         return RFAILED;
      }
   }
   
   /* Update statistics of PRB usage if stats calculation is enabled */
   if(schCb[cell->instIdx].statistics.activeKpiList.dlTotPrbUseList.count)
      prbAlloc->numPrbAlloc += numPrb;

   /* Update the remaining number for free PRBs */
   removeAllocatedPrbFromFreePrbList(&prbAlloc->freePrbBlockList, freePrbNode, *startPrb, numPrb);

   return ROK;
}
```

---

![{33D8832B-2C50-4C28-988B-ED185600842B}.png](33D8832B-2C50-4C28-988B-ED185600842B.png)

![{B68F51FC-FAF8-4B69-9AEC-804427AB5C6A}.png](B68F51FC-FAF8-4B69-9AEC-804427AB5C6A.png)

|  | OAI | OSC |
| --- | --- | --- |
| startPrb | 0 | 240 |
| **coreset0Size** |  | 48 |
| MAX_NUM_RB |  | 273 (spec) |

## Issues and solution

I encountered issues that I need to explain first. When setting the start PRB to 273, OSC's `allocatePrbDl` function searches for an appropriate location in the PRB grid and allocates requested resources at 240. However, the OAI UE fails to decode the message. After reviewing related specifications, I found no clear guidance on how the start PRB should be set. I'm uncertain whether this is an OSC or OAI problem. Interestingly, setting the PRB to start from zero resolves the issue. For now, I've decided to use zero as the starting point.

I believe OAI aims to allocate PRBs starting from zero, while OSC intends to allocate them starting from `MAX_NUM_PRB`.

[https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=vX--CaoYNOIizKzAAY4T#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=vX--CaoYNOIizKzAAY4T#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)