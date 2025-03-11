# OSC OAI SIB1 diff

Start Date: 2024/05/16
Summary: Comparison of SIB1 configurations and parameters between OAI and OSC implementations.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全

## SIB1 struct

```c
/* NR_SIB1 */
typedef struct NR_SIB1 {
	struct NR_SIB1__cellSelectionInfo {
		NR_Q_RxLevMin_t	 q_RxLevMin;
		long	*q_RxLevMinOffset;	/* OPTIONAL */
		NR_Q_RxLevMin_t	*q_RxLevMinSUL;	/* OPTIONAL */
		NR_Q_QualMin_t	*q_QualMin;	/* OPTIONAL */
		long	*q_QualMinOffset;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *cellSelectionInfo;
	NR_CellAccessRelatedInfo_t	 cellAccessRelatedInfo;
	struct NR_ConnEstFailureControl	*connEstFailureControl;	/* OPTIONAL */
	struct NR_SI_SchedulingInfo	*si_SchedulingInfo;	/* OPTIONAL */
	struct NR_ServingCellConfigCommonSIB	*servingCellConfigCommon;	/* OPTIONAL */
	long	*ims_EmergencySupport;	/* OPTIONAL */
	long	*eCallOverIMS_Support;	/* OPTIONAL */
	struct NR_UE_TimersAndConstants	*ue_TimersAndConstants;	/* OPTIONAL */
	struct NR_SIB1__uac_BarringInfo {
		struct NR_UAC_BarringPerCatList	*uac_BarringForCommon;	/* OPTIONAL */
		struct NR_UAC_BarringPerPLMN_List	*uac_BarringPerPLMN_List;	/* OPTIONAL */
		NR_UAC_BarringInfoSetList_t	 uac_BarringInfoSetList;
		struct NR_SIB1__uac_BarringInfo__uac_AccessCategory1_SelectionAssistanceInfo {
			NR_SIB1__uac_BarringInfo__uac_AccessCategory1_SelectionAssistanceInfo_PR present;
			union NR_SIB1__NR_uac_BarringInfo__NR_uac_AccessCategory1_SelectionAssistanceInfo_u {
				NR_UAC_AccessCategory1_SelectionAssistanceInfo_t	 plmnCommon;
				struct NR_SIB1__uac_BarringInfo__uac_AccessCategory1_SelectionAssistanceInfo__individualPLMNList {
					A_SEQUENCE_OF(NR_UAC_AccessCategory1_SelectionAssistanceInfo_t) list;
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *individualPLMNList;
			} choice;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *uac_AccessCategory1_SelectionAssistanceInfo;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *uac_BarringInfo;
	long	*useFullResumeID;	/* OPTIONAL */
	OCTET_STRING_t	*lateNonCriticalExtension;	/* OPTIONAL */
	struct NR_SIB1_v1610_IEs	*nonCriticalExtension;	/* OPTIONAL */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NR_SIB1_t;
```

## TX_DATA

|  | OAI | OSC |
| --- | --- | --- |
| TLV value | **0x7a7d79e8** | **0x5d11e9e8 or 0xe711e9e8** |
|  | **20a8064** |  |
| TLV length | 129 or 123 (per 6 times) | 129 |

```c
      // Data to be transmitted
      memcpy(tx_req->TLVs[0].value.direct, cc->sib1_bcch_pdu, TBS);
```

```c
void nr_mac_configure_sib1(gNB_MAC_INST *nrmac, const f1ap_plmn_t *plmn, uint64_t cellID, int tac)
{
  AssertFatal(get_softmodem_params()->sa > 0, "error: SIB1 only applicable for SA\n");

  NR_COMMON_channels_t *cc = &nrmac->common_channels[0];
  NR_ServingCellConfigCommon_t *scc = cc->ServingCellConfigCommon;
  NR_BCCH_DL_SCH_Message_t *sib1 = get_SIB1_NR(scc, plmn, cellID, tac);
  cc->sib1 = sib1;
  cc->sib1_bcch_length = encode_SIB1_NR(sib1, cc->sib1_bcch_pdu, sizeof(cc->sib1_bcch_pdu));
  AssertFatal(cc->sib1_bcch_length > 0, "could not encode SIB1\n");
}
```

![Untitled](Untitled%2035.png)

| **sib1->servingCellConfigCommon->downlinkConfigCommon** | OAI | OSC |
| --- | --- | --- |
| **frequencyInfoDL->frequencyBandList.list.array[0]** | 78 | 78 |
| **frequencyInfoDL.offsetToPointA** | 86 | 86 |
| **offsetToCarrier** | 0 |  |
| **carrierBandwidth** | 106 |  |
| **subcarrierSpacing** | 1 |  |

**<BCCH-DL-SCH-Message> (Following OSC SIB1 config mapping)**

| **參數名稱** | OAI | OSC |
| --- | --- | --- |
| q-RxLevMin | -65 | -50 |
| q-RxLevMinSUL | no | -50 |
| q-QualMin | no | -30 |
| MCC | 001 | 466 |
| MNC | 01 | 920 |
| trackingAreaCode[3] | 0x0 0x0 0x1 | 000000010000000000000000 (BuildTac) |
| ranac | unknow | 1 |
| cellIdentity (cellID) | 0xbc614e
(12345678) | 000000000000000000000000000000000001 |
| cellReservedForOperatorUse | 1 (NR_PLMN_IdentityInfo__cellReservedForOperatorUse_notReserved) | notReserved |
| connEstFailCount | OAI TODO | n3 |
| connEstFailOffsetValidity | OAI TODO | s900 |
| connEstFailOffset | OAI TODO | 15 |
| si-BroadcastStatus | OAI TODO | broadcasting |
| si-Periodicity | OAI TODO | rf8 |
| sibType2 valueTag | OAI TODO | 10 |
| si-WindowLength | OAI TODO | s5 |
| freqBandIndicatorNR | 78 | 78 |
| offsetToPointA | 86 | 86 |
| offsetToCarrier | 0 | 0 |
| subcarrierSpacing (Downlink) | 1 (kHz30) | kHz30 |
| carrierBandwidth (Downlink) | 106 | 106 |
| locationAndBandwidth (Downlink) | 28875 | 28875 |
| controlResourceSetZero | 12 | 12 (CORESET_0_INDEX) |
| searchSpaceZero | 0 | 0 |
| searchSpaceId  error | 0 | 1 (PDCCH_SEARCH_SPACE_ID) |
| coreset→controlResourceSetId error | 1 (bwp_id + 1) | 0 (PDCCH_CTRL_RSRC_SET_ID) |
| monitoringSlotPeriodicityAndOffset->present | 1 (NR_SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1) | sl1 |
| monitoringSymbolsWithinSlot[2] | 0x80 0x00
1000 0000 0000 0000 | 0x20 0x00
10000000000000
1000000000000000 (bits_unused) |
| aggregationLevel1 | 0 (NR_SearchSpace__nrofCandidates__aggregationLevel1_n0) | n8 |
| aggregationLevel2 | 0 (NR_SearchSpace__nrofCandidates__aggregationLevel2_n0) | n4 |
| aggregationLevel4 | 1 (NR_SearchSpace__nrofCandidates__aggregationLevel4_n1) | n2 |
| aggregationLevel8 | 0 (NR_SearchSpace__nrofCandidates__aggregationLevel8_n0) | n1 |
| aggregationLevel16 | 0 (NR_SearchSpace__nrofCandidates__aggregationLevel16_n0) | n0 |
| searchSpaceSIB1 | 0 | 1 |
| pagingSearchSpace | 2 | 1 (PDCCH_SEARCH_SPACE_ID_PAGING) * |
| ra-SearchSpace | 1 | 1 |
| pdsch-TimeDomainResourceAllocation k0 | (optional) OAI comment the code | 0, 1 |
| pdsch-TimeDomainResourceAllocation mappingType | 0 (NR_PDSCH_TimeDomainResourceAllocation__mappingType_typeA) | typeA |
| pdsch-TimeDomainResourceAllocation startSymbolAndLength | 40, 54 (SLIV) | 66 (算法不一樣) |
| modificationPeriodCoeff | 0 (NR_BCCH_Config__modificationPeriodCoeff_n2) | n16 |
| defaultPagingCycle | 3 (NR_PagingCycle_rf256) | rf256 |
| oneT (nAndPagingFrameOffset) | 3 (NR_PCCH_Config__nAndPagingFrameOffset_PR_quarterT) | oneT |
| ns | 2 (NR_PCCH_Config__ns_one) | one |
| firstPDCCH-MonitoringOccasionOfPO | 4 (NR_PCCH_Config__firstPDCCH_MonitoringOccasionOfPO_PR_sCS120KHZoneT_SCS60KHZhalfT_SCS30KHZquarterT_SCS15KHZoneEighthT) | 44 (PCCH_Config__firstPDCCH_MonitoringOccasionOfPO_PR_sCS30KHZoneT_SCS15KHZhalfT)

not important |
| offsetToCarrier (Uplink) | 0 | 0 |
| subcarrierSpacing (Uplink) | 1 (kHz30) | kHz30 |
| carrierBandwidth (Uplink) | 106 | 106 |
| p-Max | 20 | 23 |
| prach-ConfigurationIndex | 98 | 98 |
| msg1-FDM | 0 (one) | one |
| msg1-FrequencyStart | 0 | 82 |
| zeroCorrelationZoneConfig | 13 | 4 |
| preambleReceivedTargetPower | -96 | -74 |
| preambleTransMax
(0...10) = (3,4,5,6,7,8,10,20,50,100,200) | 6 (n10) | n200 |
| powerRampingStep
0=dB0,1=dB2,2=dB4,3=dB6 | 1 (dB2) | dB2 |
| ra-ResponseWindow
1,2,4,8,10,20,40,80 | 4 (sl10) | sl10 |
| totalNumberOfRA-Preambles | unknow | 63 |
| one (ssb-perRACH-OccasionAndCB-PreamblesPerSSB)
oneHalf (0..15) 4,8,12,16,...60,64 | 14 (60) | n8 |
| ra-ContentionResolutionTimer | 7 (sf64) | sf64 |
| rsrp-ThresholdSSB | 19 | 31 |
| l139 (prach-RootSequenceIndex) | 1 | 1 |
| msg1-SubcarrierSpacing | 1 (kHz30) | kHz30 |
| restrictedSetConfig | 0 (unrestricted) | unrestrictedSet |
| k2 (PUSCH-TimeDomainResourceAllocation) | 6 | 4, 5 |
| msg3-DeltaPreamble | 1 | 0 |
| p0-NominalWithGrant | -90 | -70 |
| pucch-ResourceCommon | null (0) | 0 |
| pucch-GroupHopping | 0 (neither) | neither |
| p0-nominal | -90 | -74 |
| timeAlignmentTimerCommon | 7 (NR_TimeAlignmentTimer_infinity) | infinity |
| inOneGroup (ssb-PositionsInBurst) | **PR=2(medium), Bitmap=1** | 11000000 |
| ssb-PeriodicityServingCell | 2 (ms20) | ms20 |
| referenceSubcarrierSpacing | 1 (kHz) | kHz30 |
| dl-UL-TransmissionPeriodicity | 6 (ms5) | ms5 |
| nrofDownlinkSlots | 7 | 7 |
| nrofDownlinkSymbols | 6 | 6 |
| nrofUplinkSlots | 2 | 2 |
| nrofUplinkSymbols | 4 | 4 |
| ss-PBCH-BlockPower | -25 | 0 |

```
 <sib2>
 五  24 21:37:18                                     <cellReselectionInfoCommon>
 五  24 21:37:18                                         <q-Hyst><dB0/></q-Hyst>
 五  24 21:37:18                                     </cellReselectionInfoCommon>
 五  24 21:37:18                                     <cellReselectionServingFreqInfo>
 五  24 21:37:18                                         <threshServingLowP>0</threshServingLowP>
 五  24 21:37:18                                         <cellReselectionPriority>0</cellReselectionPriority>
 五  24 21:37:18                                     </cellReselectionServingFreqInfo>
 五  24 21:37:18                                     <intraFreqCellReselectionInfo>
 五  24 21:37:18                                         <q-RxLevMin>-70</q-RxLevMin>
 五  24 21:37:18                                         <s-IntraSearchP>0</s-IntraSearchP>
 五  24 21:37:18                                         <t-ReselectionNR>0</t-ReselectionNR>
 五  24 21:37:18                                         <deriveSSB-IndexFromCell><false/></deriveSSB-IndexFromCell>
 五  24 21:37:18                                     </intraFreqCellReselectionInfo>
```

```c
uint8_t BuildSib1Msg()
BuildServCellCfgCommonSib
BuildCommonSerachSpaceList
```

nr_ue_postDecode

OAI:

![Untitled](Untitled%2036.png)

OSC:

![Untitled](Untitled%2037.png)

configure_dlsch