# Check Page message in dltti

Start Date: 2024/09/02
Summary: Preliminary checks and debugging of the paging message process in the DL TTI implementation.
Status: Done
Assign: 陳奕全

Check page message code is ok

```
         //TODO: ADD Paging done
         if(currDlSlot->pageAllocInfo != NULLP)
         {
            // Filling DL Paging Alloc param
            if(numPduEncoded != nPdu)
            {
               rntiType = P_RNTI_TYPE;
               //TODO:OAI_OSC_fillPagePdcchPdu done
               OAI_OSC_fillPagePdcchPdu(&dlTtiReq->dl_tti_request_body.dl_tti_pdu_list[numPduEncoded], \
                                 currDlSlot->pageAllocInfo, &macCellCfg);
               numPduEncoded++;
               //TODO:OAI_OSC_fillPagePdschPdu done
               OAI_OSC_fillPagePdschPdu(&dlTtiReq->dl_tti_request_body.dl_tti_pdu_list[numPduEncoded], \
                                 currDlSlot->pageAllocInfo, pduIndex, &macCellCfg);
               dlTtiReq->dl_tti_request_body.PduIdx[pduIndex][0] = pduIndex;
               pduIndex++;
               numPduEncoded++;
            }
            DU_LOG("\033[1;34m");
            DU_LOG("\nDEBUG  -->  LWR_MAC: PAGE sent...");
            DU_LOG("\033[0m");
         }
```

**OAI_OSC_fillPageDlDciPdu to be check**

拿page回來會卡在這 

- 在  02 15:58:11 DEBUG  -->  LWR_MAC: RAR sent…之後
    
    ![image.png](image%2025.png)
    
- `In OSC source code it increased the number of dltti_PDU to “2”`

```
   if(dlSlot->pageAllocInfo)
   {
      /* PDCCH and PDSCH PDU is filled */
      count += 2;
   }
```

<aside>
👀

1. 可以先調看看K2的值讓DU能夠順利接收到MSG3
    1. insight:  DU 並不是馬上crash out他是在RAR sent…跑了一下之後才出現 
        1. SCH: schProcessMsg4Req() : No process 
        2. ERROR  --> SCH : Resource allocation failed for MSG4
        3. ERROR  -->  SCH: Scheduling of Msg4 failed in slot [0]
        4. ERROR  -->  MAC : Failed to find free UE Idx in UE bit map of cell Id
2. Fix page message  crash issue
    1. `OAI_OSC_fillPageDlDciPdu`
</aside>

![image.png](image%2026.png)

Crash at `OAI_OSC_fillPageDlDciPdu` 

![image.png](image%2027.png)

![image.png](image%2028.png)

<aside>
👀

策略:

先把page comment掉看odu停在哪

</aside>