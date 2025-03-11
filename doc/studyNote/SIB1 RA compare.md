# SIB1 RA compare

Start Date: 2024/06/03
Summary: A comparison of RA parameters and configurations between two systems, including a detailed code structure for NR_RACH_ConfigGeneric.
Status: Done
Assign: Ming 咚咚 [銘鴻]

|  | OAI | OSC |
| --- | --- | --- |
| ra_ResponseWindow | (config) 5 | 4 |
| **totalNumberOfRA_Preambles** | (config) null | 63 |
| **cb_preambles_per_ssb** | (print) 60 | 8 |
| **rsrp_ThresholdSSB** | 19 | 31 |
| **prach_RootSequenceIndex** | 1 | 0 |
| **msg3_DeltaPreamble** | 1 | 0 |
| **p0_NominalWithGrant** | -90 | -70 |
| **p0_nominal** | -90 | -74 |
|  |  |  |

```c
/* NR_RACH-ConfigGeneric */
typedef struct NR_RACH_ConfigGeneric {
	long	 prach_ConfigurationIndex;
	long	 msg1_FDM;
	long	 msg1_FrequencyStart;
	long	 zeroCorrelationZoneConfig;
	long	 preambleReceivedTargetPower;
	long	 preambleTransMax;
	long	 powerRampingStep;
	long	 ra_ResponseWindow;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct NR_RACH_ConfigGeneric__ext1 {
		long	*prach_ConfigurationPeriodScaling_IAB_r16;	/* OPTIONAL */
		long	*prach_ConfigurationFrameOffset_IAB_r16;	/* OPTIONAL */
		long	*prach_ConfigurationSOffset_IAB_r16;	/* OPTIONAL */
		long	*ra_ResponseWindow_v1610;	/* OPTIONAL */
		long	*prach_ConfigurationIndex_v1610;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext1;
	struct NR_RACH_ConfigGeneric__ext2 {
		long	*ra_ResponseWindow_v1700;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext2;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NR_RACH_ConfigGeneric_t;
```