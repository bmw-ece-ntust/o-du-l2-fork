# Issue: Scheduling UE with the wrong ID

Start Date: 2024/09/09
Summary: Scheduling issues arise due to incorrect UE IDs being processed repeatedly without being cleared, leading to potential data loss in the system.
Status: Done
Assign: Ming 咚咚 [銘鴻]

![image.png](image%2079.png)

![image.png](image%2080.png)

![image.png](image%2081.png)

| SFN / Slot | **Scheduling UE** ID |
| --- | --- |
| 185 / 2 | 8 |
| 185 / 3 | 5 |
| 185 / 4 | 9 |

```
 九  09 20:23:57 INFO  -->  MAC : Received RACH indication from OAI PHY
 九  09 20:23:57 INFO  -->  SCH : Received Rach indication
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : Adding UE 13 to cell->ueToBeScheduled list
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 3
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 8
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 5
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 9
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 2
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 10
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 6
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 11
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 4
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 12
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : ueId = 7
 九  09 20:23:57 
 九  09 20:23:57 INFO  -->  func : schFcfsAddUeToSchedule() : Adding ueId = 13 to cell->ueToBeScheduled list
 九  09 20:23:57 
```

- It will remain in the queue forever, and it keeps extending each time. I think it's triggered by each `RACH` indication received from `OAI PHY`.
    - So, I need to ensure that when OAI Layer 1 sends a RACH indication, OSC DU High decodes it only once. It should clear or free the variable afterward.

| **nfapi_nr_vnf_p7_start** |
| --- |
| **SCF_procRachInd** |
| **OAI_OSC_nfapiMacRachInd** |
| **SchProcRachInd** |
| **schFcfsAddUeToSchedule** |

## First step:

- I found that the issue is `nfapiRachInd->number_of_pdus` is never cleared to zero, so the condition is always true.
- condition:

```c
				if (UL_INFO.rach_ind.number_of_pdus > 0){
					SCF_procRachInd(&UL_INFO.rach_ind);
				}
```

- I t**ried setting `nfapiRachInd->number_of_pdus` to zero**

```c
   rachInd->numPdu = nfapiRachInd->number_of_pdus;
   nfapiRachInd->number_of_pdus = 0;
```

**Tried setting `nfapiRachInd->number_of_pdus` to zero after copying the value to the next struct, but this caused OSC DU High to miss RX_data and not send F1AP to the CU.**

- The issue seems to be that OSC DU High doesn't send UL_TTI, so it doesn't receive RX_Data and CRC indication. After clearing the `number_of_pdus` variable, the following condition is always true. I need to investigate further.

```c
         printf("currUlSlot->ulInfo.dataType :%d\n",currUlSlot->ulInfo.dataType);
         printf("condition :%d\n",currUlSlot->ulInfo.dataType & SCH_DATATYPE_PRACH);
		   if(currUlSlot->ulInfo.dataType & SCH_DATATYPE_PRACH)
		   {
            pduIdx++;
            //TODO:OAI_OSC_fillPrachPdu done
            OAI_OSC_fillPrachPdu(&ulTtiReq->pdus_list[pduIdx], &macCellCfg, currUlSlot);
		   }
```

- The current problem after revise is OSC can’t get RX_Data and CRC indication → [Issues: OSC don’t send UL_TTI](Issues%20OSC%20don%E2%80%99t%20send%20UL_TTI%201211009831438149a2cdc685827c3887.md)