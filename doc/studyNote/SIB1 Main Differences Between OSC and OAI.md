# SIB1: Main Differences Between OSC and OAI

Tags: TX_Data

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

**<BCCH-DL-SCH-Message> (Following OAI SIB1 config mapping)**

| Element | OAI Value | OSC Value |
| --- | --- | --- |
| trackingAreaCode[3] | 0x0 0x0 0x1 | 000000010000000000000000 (BuildTac) |
| **monitoringSymbolsWithinSlot** | **0x00100000 00000000** | **10000000 00000000** |
|  |  |  |

| Element | OAI Value | OSC Value |
| --- | --- | --- |
| q-RxLevMin | -65 | -50 |
| MCC-MNC-Digit | 208 | 466 |
| MCC-MNC-Digit | 95 | 920 |
| trackingAreaCode[3] | 0x0 0x0 0x1 | 000000010000000000000000 (BuildTac) |
| cellIdentity (cellID) | 0xbc614e
(12345678) | 000000000000000000000000000000000001 |
| PLMN Identity | 208-95 |  |
| Frequency Band Indicator NR | 78 | 78 |
| Offset to Point A | 86 | 86 |
| Subcarrier Spacing | 30 kHz | kHz30 |
| Carrier Bandwidth | 106 | 106 |
| Control Resource Set Zero | 12 | 12 (CORESET_0_INDEX) |
| Search Space Zero | 0 | 0 |
| Search Space Id | 1 | 1 (PDCCH_SEARCH_SPACE_ID) |
| Monitoring Slot Periodicity and Offset | SL1 | sl1 |
| Monitoring Symbols Within Slot | 0x20 0x00
0x00100000 0x00000000 | 0x20 0x00
0x00100000 0x00000000 |
| Aggregation Level 1 Candidates | 0 (NR_SearchSpace__nrofCandidates__aggregationLevel1_n0) | n8 |
| Aggregation Level 2 Candidates | 0 (NR_SearchSpace__nrofCandidates__aggregationLevel2_n0) | n4 |
| Aggregation Level 4 Candidates | 1 (NR_SearchSpace__nrofCandidates__aggregationLevel4_n1) | n2 |
| Aggregation Level 8 Candidates | 0 (NR_SearchSpace__nrofCandidates__aggregationLevel8_n0) | n1 |
| Aggregation Level 16 Candidates | 0 (NR_SearchSpace__nrofCandidates__aggregationLevel16_n0) | n0 |
| Search Space Type | Common |  |
| DCI Format 0-0 and Format 1-0 |  |  |
| Search Space Id | 2 |  |
| Monitoring Slot Periodicity and Offset | SL1 |  |
| Monitoring Symbols Within Slot | 100000 00000000 |  |
| Aggregation Level 1 Candidates | 0 |  |
| Aggregation Level 2 Candidates | 0 |  |
| Aggregation Level 4 Candidates | 1 |  |
| Aggregation Level 8 Candidates | 0 |  |
| Aggregation Level 16 Candidates | 0 |  |
| Search Space Type | Common (DCI Format 0-0 and Format 1-0) |  |
| Search Space Id | 3 |  |
| Monitoring Slot Periodicity and Offset | SL1 |  |
| Monitoring Symbols Within Slot | 100000 00000000 |  |
| Aggregation Level 1 Candidates | 0 |  |
| Aggregation Level 2 Candidates | 0 |  |
| Aggregation Level 4 Candidates | 1 |  |
| Aggregation Level 8 Candidates | 0 |  |
| Aggregation Level 16 Candidates | 0 |  |
| Search Space Type | Common (DCI Format 0-0 and Format 1-0) |  |
| Search Space SIB1 | 0 |  |
| Search Space Other System Information | 3 |  |
| Paging Search Space | 2 |  |
| RA Search Space | 1 |  |
| Location and Bandwidth | 28875 |  |
| Subcarrier Spacing | 30 kHz |  |
| Control Resource Set Id | 0 |  |
| Monitoring Slot Periodicity and Offset | SL1 |  |
| Monitoring Symbols Within Slot | 10000000000000 |  |
| Aggregation Level 1 Candidates | 0 |  |
| Aggregation Level 2 Candidates | 0 |  |
| Aggregation Level 4 Candidates | 1 |  |
| Aggregation Level 8 Candidates | 0 |  |
| Aggregation Level 16 Candidates | 0 |  |
| Search Space Type | Common (DCI Format 0-0 and Format 1-0)  |  |
| **searchSpaceSIB1** | 0 |  |
| **searchSpaceOtherSystemInformation** | 3 |  |
| **pagingSearchSpace** | 2 |  |
| **ra-SearchSpace** | 1 |  |
| PDSCH Time Domain Allocation | Type A, Start Symbol and Length: 40 |  |
| PDSCH Time Domain Allocation | Type A, Start Symbol and Length: 54 |  |
| PDSCH Time Domain Allocation | Type A, Start Symbol and Length: 57 |  |
| **modificationPeriodCoeff** | n2 |  |
| Default Paging Cycle | RF256 |  |
| Quarter T | 1 |  |
| NS | 1 |  |
| First PDCCH Monitoring Occasion of PO | SCS120KHZoneT-SCS60KHZhalfT-SCS30KHZquarterT-SCS15KHZoneEighthT: 0 |  |
| PDCCH Block Power | -25 |  |
| T300 | 400 ms |  |
| T301 | 400 ms |  |
| T310 | 2000 ms |  |
| N310 | 10 |  |
| T311 | 3000 ms |  |
| N311 | 1 |  |
| T319 | 400 ms |  |

# OAI TX_data payload value

```c
mai 28 14:29:57 1716899397.045954 [PHY]   pNfapiMsg->TLVs[i].tag:0
mai 28 14:29:57 [0m1716899397.045959 [PHY]   pNfapiMsg->TLVs[i].length:129
mai 28 14:29:57 [0m1716899397.045961 [PHY]   out[0]:20a8064
mai 28 14:29:57 [0m1716899397.045962 [PHY]   out[1]:40800008
mai 28 14:29:57 [0m1716899397.045963 [PHY]   out[2]:2400000
mai 28 14:29:57 [0m1716899397.045964 [PHY]   out[3]:903a85f1
mai 28 14:29:57 [0m1716899397.045964 [PHY]   out[4]:56d084
mai 28 14:29:57 [0m1716899397.045965 [PHY]   out[5]:70962600
mai 28 14:29:57 [0m1716899397.045966 [PHY]   out[6]:5fe35cb
mai 28 14:29:57 [0m1716899397.045967 [PHY]   out[7]:1020b8
mai 28 14:29:57 [0m1716899397.045967 [PHY]   out[8]:b8414000
mai 28 14:29:57 [0m1716899397.045968 [PHY]   out[9]:1040
mai 28 14:29:57 [0m1716899397.045969 [PHY]   out[10]:60b84140
mai 28 14:29:57 [0m1716899397.045969 [PHY]   out[11]:40000010
mai 28 14:29:57 [0m1716899397.045970 [PHY]   out[12]:3610040
mai 28 14:29:57 [0m1716899397.045971 [PHY]   out[13]:1c365048
mai 28 14:29:57 [0m1716899397.045972 [PHY]   out[14]:c04c87
mai 28 14:29:57 [0m1716899397.045972 [PHY]   out[15]:69020020
mai 28 14:29:57 [0m1716899397.045973 [PHY]   out[16]:6619cec9
mai 28 14:29:57 [0m1716899397.045974 [PHY]   out[17]:1a006254
mai 28 14:29:57 [0m1716899397.045974 [PHY]   out[18]:c97dcdd4
mai 28 14:29:57 [0m1716899397.045975 [PHY]   out[19]:c63949c0
mai 28 14:29:57 [0m1716899397.045976 [PHY]   out[20]:1a6f8da9
mai 28 14:29:57 [0m1716899397.045977 [PHY]   out[21]:70323d9a
mai 28 14:29:57 [0m1716899397.045977 [PHY]   out[22]:874301b8
mai 28 14:29:57 [0m1716899397.045978 [PHY]   out[23]:1db02040
mai 28 14:29:57 [0m1716899397.045979 [PHY]   out[24]:de8c4880
mai 28 14:29:57 [0m1716899397.045979 [PHY]   out[25]:30c4
mai 28 14:29:57 [0m1716899397.045980 [PHY]   out[26]:0
mai 28 14:29:57 [0m1716899397.045981 [PHY]   out[27]:0
mai 28 14:29:57 [0m1716899397.045981 [PHY]   out[28]:0
mai 28 14:29:57 [0m1716899397.045982 [PHY]   out[29]:0
mai 28 14:29:57 [0m1716899397.045983 [PHY]   out[30]:0
mai 28 14:29:57 [0m1716899397.045983 [PHY]   out[31]:0
mai 28 14:29:57 [0m1716899397.045984 [PHY]   out[32]:0
```

[OAI SIB1 Full XML](OAI%20SIB1%20Full%20XML%2012110098314381fab27fd554f9bf36dd.md)