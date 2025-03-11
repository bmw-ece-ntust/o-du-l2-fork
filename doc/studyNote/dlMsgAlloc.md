# dlMsgAlloc

Start Date: 2024/07/24
Summary: Researching and troubleshooting memory allocation issues in the dlMsgAlloc function within the MAC layer of a 5G NR software project.
Status: In progress
Assign: 陳奕全

[無標題](%E7%84%A1%E6%A8%99%E9%A1%8C%201211009831438170a728ca86a4b6deb1.csv)

mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/mac_slot_ind.c

![Untitled](Untitled%2095.png)

Where allocate `cell->schDlSlotInfo[dlSchedInfo.schSlotValue.dlMsgTime.slot]->dlMsgAlloc[ueIdx]`

sch_slot_ind.c

![Untitled](Untitled%2096.png)

schDlRsrcAllocDlMsg alloacate `dlMsgPdcchCfg` 可能是元凶，程式碼碰到dlMsgPdcchCfg 就會死
>sch_common.c

<aside>
👀 schDlRsrcAllocMsg4 allocate  `dlMsgAlloc->dlMsgPdcchCfg`

</aside>

Use error message to debug 

```c
         if(dlSchedInfo.dlMsgAlloc[ueIdx]->dlMsgPdcchCfg == NULLP)
         {
            DU_LOG("\nERROR  --> MAC : SchProcSlotInd : dlMsgPdcchCfg Memory Allocation is failed!");
            return RFAILED;
         }
```

```c
  //1783:
   if(cell->schDlSlotInfo[pdcchTime.slot]->dlMsgAlloc[ueId-1]->dlMsgPdcchCfg == NULL)
if(cell->schDlSlotInfo[pdcchTime.slot]->dlMsgAlloc[ueId-1] == NULL)
```

schDlRsrcAllocMsg4

![Untitled](Untitled%2097.png)

```c
					   /* Filling RAR param */
					   rntiType = RA_RNTI_TYPE;
                  if(currDlSlot->dlInfo.rarAlloc[ueIdx]->rarPdcchCfg)
                  {
						   fillPdcchPdu(&dlTtiReq->pdus[numPduEncoded], &vendorMsg->p7_req_vendor.dl_tti_req.pdus[numPduEncoded],
								   currDlSlot, -1, rntiType, CORESET_TYPE0, ueIdx);
						   numPduEncoded++;
                     MAC_FREE(currDlSlot->dlInfo.rarAlloc[ueIdx]->rarPdcchCfg, sizeof(PdcchCfg));
                  }
					   if(currDlSlot->dlInfo.rarAlloc[ueIdx]->rarPdschCfg)
					   {
						   fillPdschPdu(&dlTtiReq->pdus[numPduEncoded], &vendorMsg->p7_req_vendor.dl_tti_req.pdus[numPduEncoded],
								   currDlSlot->dlInfo.rarAlloc[ueIdx]->rarPdschCfg,
								   currDlSlot->dlInfo.rarAlloc[ueIdx]->bwp,
								   pduIndex);
						   numPduEncoded++;
						   pduIndex++;

                     DU_LOG("\033[1;32m");
						   DU_LOG("\nDEBUG  -->  LWR_MAC: RAR sent...");
						   DU_LOG("\033[0m");
					   }
				   }
```

---

Find out why dlMsgAlloc allocated here

schFillBoGrantDlSchedInfo → Dedicate DL message allocate 

[Step6]: pdcch and pdsch data is filled schDlRsrcAllocDlMsg → `SCH_ALLOC(dlMsgAlloc->dlMsgPdcchCfg, sizeof(PdcchCfg));`
schDlRsrcAllocMsg4 → `SCH_ALLOC(msg4Alloc->dlMsgPdcchCfg, sizeof(PdcchCfg));`

---

```c
         /* If MSG4 is pending for this UE, schedule PDCCH,PDSCH to send MSG4 and
          * PUCCH to receive UL msg as per k0-k1 configuration  */
         if (cell->ueCb[ueId-1].retxMsg4HqProc) //should work from dlmap later tbd
         {
            /* Retransmission of MSG4 */
            isMsg4Pending = true;
            if(schProcessMsg4Req(cell, *slotInd, ueId, TRUE, &cell->ueCb[ueId-1].retxMsg4HqProc) == ROK)
               isMsg4Scheduled = true;
         }
         else
         {
            /* First transmission of MSG4 */
            if(cell->raCb[ueId-1].msg4recvd)
            {
               isMsg4Pending = true;
               if(schProcessMsg4Req(cell, *slotInd, ueId, FALSE, &cell->ueCb[ueId-1].msg4HqProc) == ROK)
                  isMsg4Scheduled = true;

               /* If MSG4 scheduling failed, free the newly assigned HARQ process */
               if(!isMsg4Scheduled)
                  schDlReleaseHqProcess(cell->ueCb[ueId-1].msg4HqProc);
            }
         }
```

[https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Eurecom.drawio#Uhttps://drive.google.com/uc?id=1W_o7Se11USgVPska8-t5i0JgpRSCQf4h&export=download](https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Eurecom.drawio#Uhttps://drive.google.com/uc?id=1W_o7Se11USgVPska8-t5i0JgpRSCQf4h&export=download)

<aside>
⛔ Fail. Can’t find out where allocate the dlMsgAlloc

</aside>

![Untitled](Untitled%2098.png)

```bash
sudo gdb ./odu

```

```bash
sudo ./nr-softmodem -O ~/NTUST-script/ELSE/oaiL1.nfapi.usrpb210.conf --nfapi PNF --rfsim --rfsimulator.serveraddr server --sa

```

![](https://hackmd.io/_uploads/HypviYkFC.png)

![Untitled](Untitled%2099.png)

**Running the Program**:
Start running your program. You can pass arguments if needed.

```bash
(gdb) run
```

ric send e2ap fail

![Untitled](Untitled%20100.png)

```bash
Thread 7 "odu" received signal SIGSEGV, Segmentation fault.
[Switching to Thread 0x7fffa8e46640 (LWP 1586236)]
cmAllocWL (regionCb=0x55555665cb10, size=0x7fffa8e45bcc, flags=0, ptr=0x555556667cc8) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/cm_mem_wl.c:3409
3409                bkt->next = *((CmMmEntry **)(bkt->next));
```