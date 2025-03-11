# OSC CommonSib is different

Start Date: 2024/06/17
Summary: A project focused on the configuration and implementation of common SIB (System Information Block) settings for serving cells in telecommunications.
Status: Reject
Assign: Ming 咚咚 [銘鴻]

```c
typedef struct ServingCellConfigCommonSIB {
	DownlinkConfigCommonSIB_t	 downlinkConfigCommon;
	struct UplinkConfigCommonSIB	*uplinkConfigCommon;	/* OPTIONAL */
	struct UplinkConfigCommonSIB	*supplementaryUplink;	/* OPTIONAL */
	long	*n_TimingAdvanceOffset;	/* OPTIONAL */
	struct ServingCellConfigCommonSIB__ssb_PositionsInBurst {
		BIT_STRING_t	 inOneGroup;
		BIT_STRING_t	*groupPresence;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ssb_PositionsInBurst;
	long	 ssb_PeriodicityServingCell;
	struct TDD_UL_DL_ConfigCommon	*tdd_UL_DL_ConfigurationCommon;	/* OPTIONAL */
	long	 ss_PBCH_BlockPower;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ServingCellConfigCommonSIB_t;
```

```c
/* NR_ServingCellConfigCommon */
typedef struct NR_ServingCellConfigCommon {
	NR_PhysCellId_t	*physCellId;	/* OPTIONAL */
	struct NR_DownlinkConfigCommon	*downlinkConfigCommon;	/* OPTIONAL */
	struct NR_UplinkConfigCommon	*uplinkConfigCommon;	/* OPTIONAL */
	struct NR_UplinkConfigCommon	*supplementaryUplinkConfig;	/* OPTIONAL */
	long	*n_TimingAdvanceOffset;	/* OPTIONAL */
	struct NR_ServingCellConfigCommon__ssb_PositionsInBurst {
		NR_ServingCellConfigCommon__ssb_PositionsInBurst_PR present;
		union NR_ServingCellConfigCommon__NR_ssb_PositionsInBurst_u {
			BIT_STRING_t	 shortBitmap;
			BIT_STRING_t	 mediumBitmap;
			BIT_STRING_t	 longBitmap;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ssb_PositionsInBurst;
	long	*ssb_periodicityServingCell;	/* OPTIONAL */
	long	 dmrs_TypeA_Position;
	struct NR_SetupRelease_RateMatchPatternLTE_CRS	*lte_CRS_ToMatchAround;	/* OPTIONAL */
	struct NR_ServingCellConfigCommon__rateMatchPatternToAddModList {
		A_SEQUENCE_OF(struct NR_RateMatchPattern) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *rateMatchPatternToAddModList;
	struct NR_ServingCellConfigCommon__rateMatchPatternToReleaseList {
		A_SEQUENCE_OF(NR_RateMatchPatternId_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *rateMatchPatternToReleaseList;
	NR_SubcarrierSpacing_t	*ssbSubcarrierSpacing;	/* OPTIONAL */
	struct NR_TDD_UL_DL_ConfigCommon	*tdd_UL_DL_ConfigurationCommon;	/* OPTIONAL */
	long	 ss_PBCH_BlockPower;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct NR_ServingCellConfigCommon__ext1 {
		struct NR_ServingCellConfigCommon__ext1__channelAccessMode_r16 {
			NR_ServingCellConfigCommon__ext1__channelAccessMode_r16_PR present;
			union NR_ServingCellConfigCommon__NR_ext1__NR_channelAccessMode_r16_u {
				NULL_t	 dynamic;
				struct NR_SemiStaticChannelAccessConfig_r16	*semiStatic;
			} choice;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *channelAccessMode_r16;
		long	*discoveryBurstWindowLength_r16;	/* OPTIONAL */
		NR_SSB_PositionQCL_Relation_r16_t	*ssb_PositionQCL_r16;	/* OPTIONAL */
		struct NR_HighSpeedConfig_r16	*highSpeedConfig_r16;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext1;
	struct NR_ServingCellConfigCommon__ext2 {
		struct NR_HighSpeedConfig_v1700	*highSpeedConfig_v1700;	/* OPTIONAL */
		long	*channelAccessMode2_r17;	/* OPTIONAL */
		long	*discoveryBurstWindowLength_r17;	/* OPTIONAL */
		NR_SSB_PositionQCL_Relation_r17_t	*ssb_PositionQCL_r17;	/* OPTIONAL */
		struct NR_HighSpeedConfigFR2_r17	*highSpeedConfigFR2_r17;	/* OPTIONAL */
		struct NR_UplinkConfigCommon_v1700	*uplinkConfigCommon_v1700;	/* OPTIONAL */
		struct NR_NTN_Config_r17	*ntn_Config_r17;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext2;
	struct NR_ServingCellConfigCommon__ext3 {
		struct NR_ServingCellConfigCommon__ext3__featurePriorities_r17 {
			NR_FeaturePriority_r17_t	*redCapPriority_r17;	/* OPTIONAL */
			NR_FeaturePriority_r17_t	*slicingPriority_r17;	/* OPTIONAL */
			NR_FeaturePriority_r17_t	*msg3_Repetitions_Priority_r17;	/* OPTIONAL */
			NR_FeaturePriority_r17_t	*sdt_Priority_r17;	/* OPTIONAL */
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *featurePriorities_r17;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext3;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NR_ServingCellConfigCommon_t;
```