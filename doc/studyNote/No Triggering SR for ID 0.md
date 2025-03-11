# No Triggering SR for ID 0

Start Date: 2025/02/12
Summary: Debugging the issue of scheduling requests (SR) not being triggered for ID 0 in the PUCCH configuration due to missing cell group configuration settings.
Status: In progress
Assign: Ming 咚咚 [銘鴻]

![image.png](image%20103.png)

<aside>
💡

This note primarily documents the debugging process, with the aim of clearly presenting the problem (placed at the beginning) and the solution (placed at the end). Through tracing source code and breaking down and organizing struct definitions, the solution approach is recorded in subheadings.

</aside>

# Issue Definition

This note follows up on an issue documented in [UE Segmentation fault after Generating RRCSetupComplete](UE%20Segmentation%20fault%20after%20Generating%20RRCSetupCom%2012110098314381d1adf3f719885a3bf8.md). It records my debugging process and status.

<aside>
📃

This document investigates a critical issue where scheduling requests (SR) are not being triggered for ID 0 in the PUCCH configuration. The problem stems from missing cell group configuration settings, specifically in the PUCCH dedicated configuration. Through detailed analysis of both OSC DU High and OAI UE logs, we aim to identify the root cause and propose a solution.

</aside>

- The issue discovered by OSC DU High is: Filling PUCCH dedicated cfg failed
- The issue discovered by OAI UE is: When comparing with the UE log of the normally functioning control group (OAI DU + OAI L1), the process stops before **Triggering SR for ID 0, and does not execute the trigger SR. Initial assessment suggests this is caused by missing cellgroupconfig settings, which is consistent with the OSC DU error log**

```bash
 一  20 11:27:47 recvfrom() len 20
 一  20 11:27:47 [NTUST] (p7) header.message_id:130
 一  20 11:27:47 INFO   --> [slot_indication] VNF SFN/Slot 185.15 
 一  20 11:27:47 
 一  20 11:27:47 ERROR  --> SCH : Filling PUCCH dedicated cfg failed at fillPucchResourceInfo()
                 INFO   --> [DlTtiReq] dlTtiReqTimingInfo: sfn : 185, slot : 17
```

Here are the OAI L2+L1 logs as a reference for comparison

```bash
 一  18 00:01:50 </CellGroupConfig>
 一  18 00:01:50 [RLC]   Added srb 1 to UE 0
 一  18 00:01:50 [0m[MAC]   Applying CellGroupConfig from gNodeB
 一  18 00:01:50 [0m[NR_RRC]   State = NR_RRC_CONNECTED
 一  18 00:01:50 [0m[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
 一  18 00:01:50 [0m[NR_RRC]   [RRC_UE 0] PDCP_DATA_REQ/33 Bytes RRCSetupComplete ---> 1
 一  18 00:01:50 [0m[PDCP]   nr_pdcp_data_req_srb() called, size 33
 一  18 00:01:50 [0m[NR_MAC]   Updating SR
 一  18 00:01:50 [0m[NR_MAC]   SR ID 0
 一  18 00:01:50 [0m[NR_MAC]   No pending SR for ID 0
 **一  18 00:01:50 [0m[NR_MAC]   Triggering SR for ID 0**
 一  18 00:01:50 [0m[NR_MAC]   SR updated
 一  18 00:01:50 [0m[NR_MAC]   Updating SR
 一  18 00:01:50 [0m[NR_MAC]   SR ID 0
 一  18 00:01:50 [0m[NR_MAC]   SR updated
```

```bash
 一  18 00:02:46 </CellGroupConfig>
 一  18 00:02:46 [RLC]   Added srb 1 to UE 0
 一  18 00:02:46 [0m[MAC]   Applying CellGroupConfig from gNodeB
 一  18 00:02:46 [0m[NR_RRC]   State = NR_RRC_CONNECTED
 一  18 00:02:46 [0m[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
 一  18 00:02:46 [0m[NR_RRC]   [RRC_UE 0] PDCP_DATA_REQ/33 Bytes RRCSetupComplete ---> 1
 一  18 00:02:46 [0m[PDCP]   nr_pdcp_data_req_srb() called, size 33
 一  18 00:02:46 [0m[NR_MAC]   Updating SR
 一  18 00:02:46 [0m[NR_MAC]   SR ID 0
 一  18 00:02:46 [0m[NR_MAC]   No pending SR for ID 0
```

# Source Code

## Identify Missing Components in OAI UE Configuration

According to OAI UE logs, attempting to identify which part of the cellgroupconfig received from OSC DU High is missing → `schedulingRequestResourceToAddModList`

```c
    LOG_I(NR_MAC, "SR ID %d\n", lc_info->sr_id);
    nr_sr_info_t *sr = &sched_info->sr_info[lc_info->sr_id];
    if (!sr->pending) {
      LOG_I(NR_MAC, "No pending SR for ID %d\n", lc_info->sr_id);
      NR_UE_UL_BWP_t *current_UL_BWP = mac->current_UL_BWP;
      NR_PUCCH_Config_t *pucch_Config = current_UL_BWP ? current_UL_BWP->pucch_Config : NULL;
      if (check_pucchres_for_pending_SR(pucch_Config, lc_info->sr_id)) {
        // trigger SR
        LOG_I(NR_MAC, "Triggering SR for ID %d\n", lc_info->sr_id);
        sr->pending = true;
        sr->counter = 0;
      }
```

```
<uplinkConfig>
   <initialUplinkBWP>
       <pucch-Config>
           <setup>
	           <resourceSetToAddModList>
	           ...
	           </resourceSetToAddModList>
           .........

						<schedulingRequestResourceToAddModList>
						    <SchedulingRequestResourceConfig>
						        <schedulingRequestResourceId>1</schedulingRequestResourceId>
						        <schedulingRequestID>0</schedulingRequestID>
						        <periodicityAndOffset>
						            <sl10>7</sl10>
						        </periodicityAndOffset>
						        <resource>0</resource>
						    </SchedulingRequestResourceConfig>
						</schedulingRequestResourceToAddModList>
```

![image.png](image%20104.png)

```
<uplinkConfig>
    <initialUplinkBWP>
        <pucch-Config>
            <setup>
                <resourceSetToAddModList>
                    <PUCCH-ResourceSet>
                        <pucch-ResourceSetId>1</pucch-ResourceSetId>
                        <resourceList>
                            <PUCCH-ResourceId>1</PUCCH-ResourceId>
                        </resourceList>
                    </PUCCH-ResourceSet>
                </resourceSetToAddModList>
                <resourceToAddModList>
                    <PUCCH-Resource>
                        <pucch-ResourceId>1</pucch-ResourceId>
                        <startingPRB>0</startingPRB>
                        <format>
                            <format1>
                                <initialCyclicShift>0</initialCyclicShift>
                                <nrofSymbols>4</nrofSymbols>
                                <startingSymbolIndex>0</startingSymbolIndex>
                                <timeDomainOCC>0</timeDomainOCC>
                            </format1>
                        </format>
                    </PUCCH-Resource>
                </resourceToAddModList>
                <format1>
                    <setup>
                        <nrofSlots><n4/></nrofSlots>
                    </setup>
                </format1>
                <dl-DataToUL-ACK>
                    <INTEGER>1</INTEGER>
                    <INTEGER>2</INTEGER>
                </dl-DataToUL-ACK>
            </setup>
        </pucch-Config>
```

![image.png](image%20105.png)

A more detailed comparison

Due to the large amount of information contained in the OAI UE logs (OAI CU + OAI Layer2 + OAI Layer1 + OAI UE), I have reorganized it into a hierarchical list to clearly show the differences

```bash
• uplinkConfig
    • initialUplinkBWP
        • pucch-Config
            • setup
                • resourceSetToAddModList
                    • PUCCH-ResourceSet (1)
                        • pucch-ResourceSetId: 0
                        • resourceList
                            • PUCCH-ResourceId: 0
                    • PUCCH-ResourceSet (2)
                        • pucch-ResourceSetId: 1
                        • resourceList
                            • PUCCH-ResourceId: 2
                • resourceToAddModList
                    • PUCCH-Resource (1)
                        • pucch-ResourceId: 0
                        • startingPRB: 8
                        • format
                            • format0
                                • initialCyclicShift: 0
                                • nrofSymbols: 1
                                • startingSymbolIndex: 13
                    • PUCCH-Resource (2)
                        • pucch-ResourceId: 2
                        • startingPRB: 0
                        • format
                            • format2
                                • nrofPRBs: 8
                                • nrofSymbols: 1
                                • startingSymbolIndex: 13
                • format2
                    • setup
                        • maxCodeRate: zeroDot15
                        • simultaneousHARQ-ACK-CSI: true
                • schedulingRequestResourceToAddModList
                    • SchedulingRequestResourceConfig
                        • schedulingRequestResourceId: 1
                        • schedulingRequestID: 0
                        • periodicityAndOffset
                            • sl10: 7
                        • resource: 0
                • DataToUL-ACK
                    • INTEGER: 6, 7, 8, 9, 10, 11, 12, 13
                • spatialRelationInfoToAddModList
                    • PUCCH-SpatialRelationInfo
                        • pucch-SpatialRelationInfoId: 1
                        • referenceSignal
                            • ssb-Index: 0
                        • pucch-PathlossReferenceRS-Id: 0
                        • p0-PUCCH-Id: 1
                        • closedLoopIndex: i0
                • pucch-PowerControl
                    • deltaF-PUCCH-f0: 0
                    • deltaF-PUCCH-f2: 0
                    • p0-Set
                        • P0-PUCCH
                            • p0-PUCCH-Id: 1
                            • p0-PUCCH-Value: 0
                    • pathlossReferenceRSs
                        • PUCCH-PathlossReferenceRS
                            • pucch-PathlossReferenceRS-Id: 0
                            • referenceSignal
                                • ssb-Index: 0
```

for-loop not executed (schedulingRequestResourceToAddModList missing in cellgroupconfig)

```c
static bool check_pucchres_for_pending_SR(NR_PUCCH_Config_t *pucch_Config, int target_sr_id)
{
  LOG_I(NR_MAC, "Checking PUCCH resources for SR ID %d\n", target_sr_id);
  LOG_I(NR_MAC, "pucch_Config->schedulingRequestResourceToAddModList->list.count = %d\n", pucch_Config->schedulingRequestResourceToAddModList->list.count);
  for (int id = 0; id < pucch_Config->schedulingRequestResourceToAddModList->list.count; id++) {
    NR_SchedulingRequestResourceConfig_t *sr_Config = pucch_Config->schedulingRequestResourceToAddModList->list.array[id];
    LOG_I(NR_MAC, "SchedulingRequestResourceConfig ID: %ld\n", sr_Config->schedulingRequestResourceId);
    LOG_I(NR_MAC, "SchedulingRequest ID: %ld\n", sr_Config->schedulingRequestID);
    
```

`schedulingRequestResourceToAddModList` missing in cellgroupconfig

```cpp
typedef struct pucchSchedReqCfg
{
   uint8_t           schedAddModListCount;
   SchedReqResrcInfo schedAddModList[MAX_NUM_SR_CFG_PER_CELL_GRP];
   uint8_t           schedRelListCount;
   uint8_t           schedRelList[MAX_NUM_SR_CFG_PER_CELL_GRP];
}PucchSchedReqCfg;
```

## Identifying why OSC DU High has missing configurations

### 1. Locate where OSC DU-High fills `initialULRRCmsg`

```c
uint8_t BuildBWPUlDedPucchCfg(PucchCfg *pucchCfgDb, PUCCH_Config_t *pucchCfg)
{
   PucchResrcSetCfg *rsrcSetCfgDb = NULLP;
   PucchResrcCfg *rsrcCfgDb = NULLP;
   PucchFormatCfg *format1Db = NULLP;
   PucchFormatCfg *format2Db = NULLP;
   PucchFormatCfg *format3Db = NULLP;
   PucchFormatCfg *format4Db = NULLP;
   PucchSchedReqCfg *schReqDb = NULLP;   
   PucchMultiCsiCfg  *multiCsiDb = NULLP;
   PucchDlDataToUlAck *dlDataToUlAckDb = NULLP;

   if(pucchCfgDb)
   {
      rsrcSetCfgDb = pucchCfgDb->resrcSet;
      rsrcCfgDb = pucchCfgDb->resrc;
      format1Db = pucchCfgDb->format1;
      format2Db = pucchCfgDb->format2;
      format3Db = pucchCfgDb->format3;
      format4Db = pucchCfgDb->format4;
      schReqDb = pucchCfgDb->schedReq;
      multiCsiDb = pucchCfgDb->multiCsiCfg;
      dlDataToUlAckDb = pucchCfgDb->dlDataToUlAck;
   }

   /* RESOURCE SET */
   DU_ALLOC(pucchCfg->resourceSetToAddModList, sizeof(struct PUCCH_Config__resourceSetToAddModList));
   if(pucchCfg->resourceSetToAddModList == NULL)
   {
      DU_LOG("\nERROR  -->  F1AP : Memory allocation failed in BuildBWPUlDedPucchCfg");
      return RFAILED;
   }

   if(BuildPucchRsrcSetAddModList(rsrcSetCfgDb, pucchCfg->resourceSetToAddModList) != ROK)
   {
      DU_LOG("\nERROR  -->  F1AP : Memory allocation failed in BuildBWPUlDedPucchCfg");
      return RFAILED;
   }

   /* PUCCH RESOURCE */
   DU_ALLOC(pucchCfg->resourceToAddModList, sizeof(struct PUCCH_Config__resourceToAddModList));
   if(pucchCfg->resourceToAddModList == NULLP)
   {
      DU_LOG("\nERROR  -->  F1AP : Memory allocation failed in BuildBWPUlDedPucchCfg");
      return RFAILED;
   }

   if(BuildPucchRsrcAddModList(rsrcCfgDb, pucchCfg->resourceToAddModList) != ROK)
   {
      DU_LOG("\nERROR  -->  F1AP : Memory allocation failed in BuildBWPUlDedPucchCfg");
      return RFAILED;
   }

   /* PUCCH Format 1 */
   DU_ALLOC(pucchCfg->format1, sizeof(struct PUCCH_Config__format1));
   if(pucchCfg->format1 == NULLP)
   {
      DU_LOG("\nERROR  -->  F1AP : Memory allocation failed in BuildBWPUlDedPucchCfg");
      return RFAILED;
   }
   
```

### 2. Find where OSC implements the `cellgroupconfig` source code

![image.png](image%20106.png)

Error log shows that the function `fillUlSchedPucchDedicatedCfg` returned a failure message. Tracing this function reveals that the cause is missing (pucchDedCfg->resrcSet && pucchDedCfg->resrc)

```c
uint16_t fillPucchResourceInfo(uint8_t ueId, SchPucchInfo *schPucchInfo, Inst inst, SlotTimingInfo slotInfo)
{
   uint8_t ret = ROK,  ueIdx = 0, pucchIdx = 0;
   SchCellCb  *cell = schCb[inst].cells[inst];
   SchPucchCfgCmn *pucchCfg = NULLP;
   SchBwpParams *ulBwp = NULLP;
#ifdef NR_DRX 
   SchUeCb *ueCb = NULLP;
#endif
   uint16_t startPrb;

   ueIdx = ueId -1;
#ifdef NR_DRX 
   ueCb = &(cell->ueCb[ueIdx]); 
   if(ueCb->ueDrxInfoPres)
   {
      if(!ueCb->drxUeCb.drxUlUeActiveStatus)
         return RFAILED;
   }
#endif
   if(cell->ueCb[ueIdx].ueCfg.spCellCfg.servCellRecfg.initUlBwp.pucchCfgPres)
   {
      /* fill pucch dedicated cfg */
      ret = fillUlSchedPucchDedicatedCfg(cell,\
       &cell->ueCb[ueIdx].ueCfg.spCellCfg.servCellRecfg.initUlBwp.pucchCfg, &slotInfo, schPucchInfo);
      if(ret == RFAILED)
      {
         memset(schPucchInfo, 0, sizeof(SchPucchInfo));
         DU_LOG("\nERROR  --> SCH : Filling PUCCH dedicated cfg failed at fillPucchResourceInfo()");
	 return ret;
```

```c
uint8_t fillUlSchedPucchDedicatedCfg(SchCellCb *cell, SchPucchCfg *pucchDedCfg,\
   SlotTimingInfo *slotInfo, SchPucchInfo *ulSchedPucch)
{
   uint8_t ret, resrcSetIdx, resrcIdx, schedReqIdx, srPeriodicity = 0;
   uint16_t srOffset = 0;
   uint16_t numSlots = cell->numSlots;
   bool isAllocated = false;
   uint16_t pucchStartPrb;
   ret = ROK;
   if(pucchDedCfg->resrcSet && pucchDedCfg->resrc)
   {
      printf("pucchDedCfg is resrcSet or resrc\n");
      //Assuming one entry in the list
      printf("pucchDedCfg->resrcSet->resrcSetToAddModListCount: %d\n", pucchDedCfg->resrcSet->resrcSetToAddModListCount);
      for(resrcSetIdx = 0; resrcSetIdx < pucchDedCfg->resrcSet->resrcSetToAddModListCount; resrcSetIdx++)
      {
```

According to the flow chart, we can trace back to `duBuildAndSendUeCreateReqToMac`, where the message path is du → mac → sch. The error log shows up on the sch side, so we need to trace back to the du side to check if the parameters were created correctly. The key lies in the **`updateDuMacUeCfg`** **function**

![image.png](image%20107.png)

```c
uint8_t duBuildAndSendUeCreateReqToMac(uint16_t cellId, uint8_t gnbDuUeF1apId, uint16_t crnti, DuUeCfg *ueCfgDb, DuMacUeCfg *duMacUeCfg)
{
   printf("\nDEBUG   -->  DU_APP: Building UE create request to MAC");
   uint8_t  ret = ROK;
   MacUeCreateReq *macUeCfg = NULLP;
   Pst       pst;
   memset(&pst, 0, sizeof(Pst));

   ret = updateDuMacUeCfg(cellId, gnbDuUeF1apId, crnti, ueCfgDb, duMacUeCfg);
   if(ret == RFAILED)
   {
      DU_LOG("\nERROR  -->  DU APP : Failed to fill MacUeCfg at duBuildAndSendUeCreateReqToMac()");
      return RFAILED;
   }

   /* Fill Pst */
   FILL_PST_DUAPP_TO_MAC(pst, EVENT_MAC_UE_CREATE_REQ);

   /* Copying ueCb to a sharable buffer */
   DU_ALLOC_SHRABL_BUF(macUeCfg, sizeof(MacUeCreateReq));
```

According to the current version and environment logs, the `updateDuMacUeCfg` function is currently executing Filling Default Mac Cell Group Config. Therefore, the solution is clear: identify and complete the missing parameters in the default configuration.

- `fillDefaultMacCellGrpInfo`
- `fillDefaultPhyCellGrpInfo`
- `fillDefaultSpCellGrpInfo`
- `fillDefaultModulation`
- `fillMacSrb1LcCfg`

![image.png](image%20108.png)

```c
uint8_t updateDuMacUeCfg(uint16_t cellId, uint8_t gnbDuUef1apId, uint16_t crnti, DuUeCfg *ueCfgDb, DuMacUeCfg *duMacUeCfg)
{
   uint8_t ret = ROK, dbIdx = 0, lcIdx = 0, cellIdx = 0;
   bool lcIdFound = false;
   DuMacUeCfg *duMacDb = NULLP;

   duMacUeCfg->cellId = cellId;
   duMacUeCfg->ueId = gnbDuUef1apId;
   duMacUeCfg->crnti = crnti;

   if(!ueCfgDb)
   {
      printf("\nDEBUG  -->  DU APP : Filling Default Mac Cell Group Config");
      fillDefaultMacCellGrpInfo(duMacUeCfg);
      fillDefaultPhyCellGrpInfo(duMacUeCfg);

      if((fillDefaultSpCellGrpInfo(duMacUeCfg)) != ROK)
      {
         DU_LOG("\nERROR  --> DUAPP : Failed in fillDefaultSpCellGrpInfo");
         return RFAILED;
      }

      duMacUeCfg->ambrCfg = NULLP;
      fillDefaultModulation(duMacUeCfg);
      fillMacSrb1LcCfg(&duMacUeCfg->lcCfgList[0]);
      duMacUeCfg->numLcs++;
   }
```

![image.png](image%20109.png)

`fillPucchSchedReqCfg()` fill → **`macPucchCfg->schedReq` forward → `PucchSchedReqCfg *schReqDb`**

issues: `macPucchCfg->schedReq` is null

```c
   if(macPucchCfg->schedReq)
   {
      MAC_ALLOC(schPucchCfg->schedReq, sizeof(SchPucchSchedReqCfg));
      if(schPucchCfg->schedReq == NULLP)
      {
         DU_LOG("\nERROR  --> MAC : Failed to allocate Mem for  PucchSchedReqCfg in fillInitialUlBwpPucchCfg()");
         return RFAILED;
      }
      memset(schPucchCfg->schedReq, 0, sizeof(SchPucchSchedReqCfg));
      fillPucchSchedReqCfg(macPucchCfg->schedReq, schPucchCfg->schedReq);
   }
```

```c
void fillDefaultMacCellGrpInfo(DuMacUeCfg *macUeCfg)
{
   uint8_t idx;
   MacCellGrpCfg *cellGrp = NULL;
   
   if(macUeCfg)
      cellGrp = &macUeCfg->macCellGrpCfg;

   if(cellGrp)
   {
      macUeCfg->macCellGrpCfgPres = true;
      printf("\nDEBUG  -->  DU APP : Filling Mac Cell Group Config");
      /* Filling Scheduling Request Config */
      cellGrp->schReqCfg.addModListCount = 1;
      if(cellGrp->schReqCfg.addModListCount <= MAX_NUM_SR_CFG_PER_CELL_GRP)
      {
         for(idx = 0; idx < cellGrp->schReqCfg.addModListCount; idx++)
         {
            cellGrp->schReqCfg.addModList[idx].schedReqId    = SCH_REQ_ID;
            cellGrp->schReqCfg.addModList[idx].srProhibitTmr = SR_PROHIBIT_MS_32;
            cellGrp->schReqCfg.addModList[idx].srTransMax    = SR_TRANS_MAX_N_16;
         }
      }
      cellGrp->schReqCfg.relListCount = 0;
```

### 3. OSC DU-High missing implementation of `schedulingRequestResourceToAddModList` structure

![image.png](image%20110.png)

[https://viewer.diagrams.net/?border=0&tags=%7B%7D&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=WS-VHd4syMk4Ym1l1xB8&dark=auto#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts%26export%3Ddownload](https://viewer.diagrams.net/?border=0&tags=%7B%7D&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=WS-VHd4syMk4Ym1l1xB8&dark=auto#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts%26export%3Ddownload)

Based on the trace code and further analysis, we can understand that:

- [**NR RRC Connection Setup Flow**](NR%20RRC%20Connection%20Setup%20Flow%20199100983143801b8726f22625e4eb0b.md)
- [Understanding the Role of CellGroupConfig in 5G NR UE Access Procedures](Understanding%20the%20Role%20of%20CellGroupConfig%20in%205G%20NR%2019a10098314380bba593d691b115f79f.md)
- [**PUCCH_Config__schedulingRequestResource in 5G NR**](PUCCH_Config__schedulingRequestResource%20in%205G%20NR%2019a10098314380e280e9ef4063fef923.md)

After receiving MSG4, the UE sends an RRCSetupRequest containing basic identity information like the UE-ID. The DU then forwards this to the CU through an Initial UL RRC Message Transfer, which includes CGI (PLMN, cell ID), C-RNTI, RRCSetupRequest, and the DU-to-CU-container via F1.

The DU uses the DU-to-CU-container to verify UE connection eligibility. For approved connections, the DU includes the CellGroupConfig (containing SIB1) in this container for the CU-CP. Once the CU receives the Initial UL RRC Message Transfer, it incorporates the CellGroupConfig into the DL RRC Message Transfer, sends it back to the DU, which then forwards it to the UE to provide gNB configuration details.

While reviewing the spec, source code, and online resources, I found this process puzzling - specifically why the CellGroupConfig must travel up to the CU and back down to the DU before reaching the UE. Though the complexity isn't problematic, I'm concerned I might be missing something important.

In this current setup (OAI CU + OSC DU High + nFAPI + OAI L1 + OAI UE), I've identified that the OAI UE issue stems from a missing `pucch_Config->schedulingRequestResourceToAddModList` structure in the received CellGroupConfig. Based on my analysis, this issue occurs because the OSC DU fails to populate the , leading to the current problem.

<aside>

consulting with Robert to verify this information → [**Notes on Robert’s Response Regarding RRCSetupRequest & CellGroupConfig**](Notes%20on%20Robert%E2%80%99s%20Response%20Regarding%20RRCSetupReque%201a01009831438030aae6ede75db763a1.md) 

</aside>

<aside>

consulting with Anlit to verify this information → [**Notes on Ankit Response Regarding RRCSetupRequest & CellGroupConfig**](Notes%20on%20Ankit%20Response%20Regarding%20RRCSetupRequest%20%201a110098314380008ac5e69d37728ade.md) 

</aside>

My next step will be to trace OAI's implementation and use it as a golden sample for reference to identify the issue → [Understanding schedulingRequestResourceToAddModList in OAI](Understanding%20schedulingRequestResourceToAddModLis%201a01009831438099aca0d7097ffb3c13.md) 

# Struct definition

To identify the missing components in OSC DU, I decided to trace the struct creation process layer by layer, starting from its origin. The flow begins with creation in du_app, then passes to MAC, and finally reaches SCH.

## DU_APP

```cpp
typedef struct duMacUeCfg
{
   uint16_t               cellId;
   uint8_t                ueId;
   uint16_t               crnti;
   bool                   macCellGrpCfgPres;
   MacCellGrpCfg          macCellGrpCfg;
   bool                   phyCellGrpCfgPres;
   PhyCellGrpCfg          phyCellGrpCfg;
   bool                   spCellCfgPres;
   SpCellRecfg            spCellCfg;
   AmbrCfg                *ambrCfg;
   ModulationInfo         dlModInfo;    /* DL modulation info */ //TBD
   ModulationInfo         ulModInfo;    /* UL modulation info */  //TBD
   uint8_t                numLcs;
   DuLcCfg                lcCfgList[MAX_NUM_LC];
   UeCfgState             macUeCfgState;    /* InActive / Completed */ //TBD
   DataTransmissionAction transmissionAction; //TBD
#ifdef NR_DRX
   bool     drxConfigIndicatorRelease;
#endif
}DuMacUeCfg;
```

### `macCellGrpCfg`

```
typedef struct macCellGrpCfg
{
   SchedReqCfg schReqCfg;
   TagCfg      tagCfg;
   BsrTmrCfg   bsrTmrCfg;
   bool        phrCfgSetupPres;   /* true/false: phrCfgSetup/phrCfgRelease */
   PhrCfg      phrCfg;
#ifdef NR_DRX
   bool        drxCfgPresent;
   DrxCfg      drxCfg;
#endif
}MacCellGrpCfg;
```

### `SchedReqCfg`

```
/* Info of Scheduling Request to Add/Modify */
typedef struct schedReqInfo
{
   uint8_t         schedReqId;
   SrProhibitTimer srProhibitTmr;
   SrTransMax      srTransMax;
}SchedReqInfo;

/* Scheduling Request Configuration */
typedef struct schedReqCfg
{
   uint8_t       addModListCount;
   SchedReqInfo  addModList[MAX_NUM_SR_CFG_PER_CELL_GRP];   /* List of Scheduling req to be added/modified */
   uint8_t       relListCount;
   uint8_t       relList[MAX_NUM_SR_CFG_PER_CELL_GRP];      /* list of scheduling request Id to be deleted */
}SchedReqCfg;
```

### `SpCellCfg`

```
/* Serving cell configuration */
typedef struct servCellCfgInfo
{
   InitialDlBwp         initDlBwp;
   RadioLinkConfig      radioLinkMonConfig;
   uint8_t              numDlBwpToAdd;
   DlBwpInfo            dlBwpToAddList[MAX_NUM_BWP];
   uint8_t              firstActvDlBwpId;
   uint8_t              defaultDlBwpId;
   uint8_t              *bwpInactivityTmr;
   PdschServCellCfg     pdschServCellCfg;
   InitialUlBwp         initUlBwp;
   BeamFailRecoveryCfg  beamFailureRecoveryCfg;
   uint8_t              numUlBwpToAdd;
   UlBwpInfo            ulBwpToAddList[MAX_NUM_BWP];
   uint8_t              firstActvUlBwpId;
}ServCellCfgInfo;

/* Special cell configuration */
typedef struct spCellCfg
{
   uint8_t           servCellIdx;
   ServCellCfgInfo   servCellCfg;
}SpCellCfg;
```

## DU_APP & MAC

<aside>
💡

The main issue is the missing **`PucchCfg` structure**

</aside>

- **DuCb       /* global variables */**
    - **DuCellCb**
        - `duUeCb`
            - **DuMacUeCfg**
                - **SpCellRecfg**
                    - **ServCellRecfgInfo**
                        - **InitialUlBwp**
                            - **`PucchCfg`**

### `duUeCb`

```cpp
typedef struct duUeCb
{
   F1UeContextSetupDb *f1UeDb;
   uint16_t crnti;
   uint32_t gnbDuUeF1apId;   /* GNB DU UE F1AP ID */
   uint32_t gnbCuUeF1apId;   /* GNB CU UE F1AP ID */
   uint32_t drbBitMap;       /* Drb Bit Map */
   UeState  ueState;         /* UE Active/ Ue Inactive state */
   MacCfraResource cfraResource; /* CF-RA resource assigned by MAC/SCH */
   DuMacUeCfg duMacUeCfg;        /* Mac Ue Cfg */
   DuRlcUeCfg duRlcUeCfg;        /* Rlc Ue Cfg */
}DuUeCb;
```

### `macPucchCfg->schedReq`

```c
typedef struct pucchCfg
{
   PucchResrcSetCfg  *resrcSet;
   PucchResrcCfg     *resrc;
   PucchFormatCfg    *format1; 
   PucchFormatCfg    *format2; 
   PucchFormatCfg    *format3; 
   PucchFormatCfg    *format4;
   PucchSchedReqCfg  *schedReq;
   PucchMultiCsiCfg  *multiCsiCfg;
   PucchSpatialCfg   *spatialInfo;
   PucchDlDataToUlAck *dlDataToUlAck;
   PucchPowerControl *powerControl;
}PucchCfg;
```

## SCH

### **`pucchDedCfg->resrcSet`**

```cpp
typedef struct schPucchCfg
{
   SchPucchResrcSetCfg   *resrcSet;
   SchPucchResrcCfg      *resrc;
   SchPucchFormatCfg     *format1; 
   SchPucchFormatCfg     *format2; 
   SchPucchFormatCfg     *format3; 
   SchPucchFormatCfg     *format4;
   SchPucchSchedReqCfg   *schedReq;
   SchPucchMultiCsiCfg   *multiCsiCfg;
   SchPucchSpatialCfg    *spatialInfo;
   SchPucchDlDataToUlAck *dlDataToUlAck;
   SchPucchPowerControl  *powerControl;
}SchPucchCfg;
```

```
/* Scheduling Request Configuration */
typedef struct schedReqCfg
{
   uint8_t       addModListCount;
   SchedReqInfo  addModList[MAX_NUM_SR_CFG_PER_CELL_GRP];   /* List of Scheduling req to be added/modified */
   uint8_t       relListCount;
   uint8_t       relList[MAX_NUM_SR_CFG_PER_CELL_GRP];      /* list of scheduling request Id to be deleted */
}SchedReqCfg;
```

```c
typedef struct macCellGrpCfg
{
   SchedReqCfg schReqCfg;
   TagCfg      tagCfg;
   BsrTmrCfg   bsrTmrCfg;
   bool        phrCfgSetupPres;   /* true/false: phrCfgSetup/phrCfgRelease */
   PhrCfg      phrCfg;
#ifdef NR_DRX
   bool        drxCfgPresent;
   DrxCfg      drxCfg;
#endif
}MacCellGrpCfg;
```

```
typedef struct pucchSchedReqCfg
{
   uint8_t           schedAddModListCount;
   SchedReqResrcInfo schedAddModList[MAX_NUM_SR_CFG_PER_CELL_GRP];
   uint8_t           schedRelListCount;
   uint8_t           schedRelList[MAX_NUM_SR_CFG_PER_CELL_GRP];
}PucchSchedReqCfg;
```

# solution