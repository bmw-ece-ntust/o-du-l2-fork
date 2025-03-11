# 【OSC】SIB1 config

Start Date: 2024/05/14
Summary: Configuration details and implementation for SIB1 in a communication system, including code snippets and settings related to PDCCH and search space configurations.
Status: Done
Assign: 陳奕全

```c
#define PDCCH_SEARCH_SPACE_ID_SIB1 1    /* Search space id for sib1 */

/* ======== small cell integration ======== */
#ifdef NFAPI
#define OFFSET_TO_POINT_A 86                     /* PRB Offset to Point A OAI */
#else 
#define OFFSET_TO_POINT_A 24                     /* PRB Offset to Point A */
#endif
/* ======================================== */

#define SSB_SUBCARRIER_OFFSET 0      

#define NR_SCS SCS_30KHZ

#define NR_BANDWIDTH BANDWIDTH_40MHZ //OAI

#define FREQ_LOC_BW  28875             /* DL frequency location and bandwidth. Spec 38.508 Table 4.3.1.0B-1*/

	SearchSpace__searchSpaceType_PR_common, = 1
	
	BuildSib1Msg
	
	PDCCH_SEARCH_SPACE_ID_SIB1
```

```c
TODO
   /* Configuring PDCCH Config Common For SIB1 */
   pdcchCfg.present = BWP_DownlinkCommon__pdcch_ConfigCommon_PR_setup;
   pdcchCfg.ctrlRsrcSetZero = CORESET_0_INDEX;
   pdcchCfg.searchSpcZero = SEARCHSPACE_0_INDEX;
   pdcchCfg.searchSpcId = PDCCH_SEARCH_SPACE_ID;
   pdcchCfg.ctrlRsrcSetId = PDCCH_CTRL_RSRC_SET_ID;
   pdcchCfg.monitorSlotPrdAndOffPresent = SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1;
   //pdcchCfg.monitorSlotPrdAndOff = \
   SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1;
   pdcchCfg.monitorSymbolsInSlot[0] = 128;
   pdcchCfg.monitorSymbolsInSlot[1] = 0;
   pdcchCfg.numCandAggLvl1 = SearchSpace__nrofCandidates__aggregationLevel1_n8;
   pdcchCfg.numCandAggLvl2 = SearchSpace__nrofCandidates__aggregationLevel2_n4;
   pdcchCfg.numCandAggLvl4 = SearchSpace__nrofCandidates__aggregationLevel4_n2;
   pdcchCfg.numCandAggLvl8 = SearchSpace__nrofCandidates__aggregationLevel8_n1;
   pdcchCfg.numCandAggLvl16 = SearchSpace__nrofCandidates__aggregationLevel16_n0;
   pdcchCfg.searchSpcType = SearchSpace__searchSpaceType_PR_common;
   pdcchCfg.commSrchSpcDciFrmt = PDCCH_SERACH_SPACE_DCI_FORMAT;
   pdcchCfg.searchSpcSib1 = PDCCH_SEARCH_SPACE_ID_SIB1;
   pdcchCfg.pagingSearchSpc = PDCCH_SEARCH_SPACE_ID_PAGING;
   pdcchCfg.raSearchSpc = PDCCH_SEARCH_SPACE_ID_PAGING;
   srvCellCfgComm->dlCfg.pdcchCfg = pdcchCfg;
```

```c
mai 15 10:39:27 [0m[NR_MAC]   Coreset0: index_4msb=12, num_rbs=48, num_symb=1, rb_offset=16
mai 15 10:39:27 [0m[NR_MAC]   NR_SubcarrierSpacing_kHz30 1, scs_ssb 1, scs_pdcch 1, min_chan_bw 2

 五  15 16:36:17 [0m[NR_MAC]   Coreset0: index_4msb=12, num_rbs=48, num_symb=1, rb_offset=16
 五  15 16:36:17 [0m[NR_MAC]   NR_SubcarrierSpacing_kHz30 1, scs_ssb 1, scs_pdcch 1, min_chan_bw 2
 
```

![Untitled](Untitled%2076.png)

Check DCI

![Untitled](Untitled%2077.png)

```c
mai 15 11:07:53 [0m[MAC]   [DCI_CONFIG] Configure DCI PDU: rnti_type 4 BWPSize 48 BWPStart 27 rel15->SubcarrierSpacing 1 rel15->dci_format 0 rel15->dci_length 39 sps 14 monitoringSymbolsWithinSlot 8192 

 五  15 17:09:04 [0m[MAC]   [DCI_CONFIG] Configure DCI PDU: rnti_type 4 BWPSize 48 BWPStart 27 rel15->SubcarrierSpacing 1 rel15->dci_format 0 rel15->dci_length 39 sps 14 monitoringSymbolsWithinSlot 8192 

```

Check

```c
uint8_t fillSchSib1Cfg(uint8_t mu, uint8_t bandwidth, uint8_t numSlots,SchPdcchConfigSib1 *pdcchCfgSib1,\
               SchSib1Cfg *sib1SchCfg, uint16_t pci, uint8_t offsetPointA, uint16_t sib1PduLen)
{
```

```c
   covertFreqDomRsrcMapToIAPIFormat(FreqDomainResource, pdcch->coresetCfg.freqDomainResource);

```

![Untitled](Untitled%2078.png)

```
 五  15 19:19:15 BWPSize: 273[0m[PHY]   
 五  15 19:19:15 BWPStart: 0[0m[PHY]   
```

![Untitled](Untitled%2079.png)

```
 五  15 21:03:35 [0m[NR_MAC]   Monitoring DCI for SIB1 in frame 58 slot 0
 五  15 21:03:35 [0m[MAC]   [DCI_CONFIG] Configure DCI PDU: rnti_type 4 BWPSize 48 BWPStart 27 rel15->SubcarrierSpacing 1 rel15->dci_format 0 rel15->dci_length 39 sps 14 monitoringSymbolsWithinSlot 8192 
 五  15 21:03:35 [0m[PHY]   Copying DL DCI PDU of 1 total DL PDUs:
 五  15 21:03:35 [0m[NR_PHY]   UE call nr_ue_pdcch_procedures
 五  15 21:03:35 [0m[NR_MAC]   Monitoring DCI for SIB1 in frame 58 slot 1
 五  15 21:03:35 [0m[MAC]   [DCI_CONFIG] Configure DCI PDU: rnti_type 4 BWPSize 48 BWPStart 27 rel15->SubcarrierSpacing 1 rel15->dci_format 0 rel15->dci_length 39 sps 14 monitoringSymbolsWithinSlot 8192 
 五  15 21:03:35 [0m[PHY]   Copying DL DCI PDU of 1 total DL PDUs:

mai 15 15:09:15 [0m[NR_MAC]   Monitoring DCI for SIB1 in frame 60 slot 0
mai 15 15:09:15 [0m[MAC]   [DCI_CONFIG] Configure DCI PDU: rnti_type 4 BWPSize 48 BWPStart 27 rel15->SubcarrierSpacing 1 rel15->dci_format 0 rel15->dci_length 39 sps 14 monitoringSymbolsWithinSlot 8192 
mai 15 15:09:15 [0m[PHY]   Copying DL DCI PDU of 1 total DL PDUs:
mai 15 15:09:15 [0m[PHY]   Number of DCI SearchSpaces 1
mai 15 15:09:15 [0m[PHY]   Copying DL SI_DLSCH PDU of 1 total DL PDUs:
```

No found DCI

![Untitled](Untitled%2080.png)

DCI payload 

![Untitled](Untitled%2081.png)

```c
/* ======== small cell integration ======== */
#ifdef NFAPI
#ifdef NR_TDD
   configReq->number_of_tlvs = 30 + 140;
#else
   configReq->number_of_tlvs = 26;
#endif
#else
   configReq->number_of_tlvs = 24;
#endif
   /* ======================================== */
   fillTlvs(&configReq->tlvs[index++], FAPI_BCH_PAYLOAD_TAG,
            sizeof(uint8_t), macCfgParams.ssbCfg.bchPayloadFlag, &msgLen);
  fillTlvs(&configReq->tlvs[index++], FAPI_NUM_ROOT_SEQUENCES_TAG,
        sizeof(uint8_t), macCfgParams.prachCfg.fdm[0].numRootSeq, &msgLen);

```