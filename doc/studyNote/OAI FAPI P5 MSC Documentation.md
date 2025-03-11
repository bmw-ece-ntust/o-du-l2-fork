# OAI FAPI P5 MSC Documentation

Start Date: 2025/02/10
Summary: Development and documentation of OAI FAPI P5 specifications for 5G implementation, including TLVs structure and associated field names.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: PIN
Finish Date: 2025/02/12
SUM: 🗓️ Days Spent to Complete: 2

A documentation of SCP FAPI P5 specifications, focusing on the TLVs structure and their associated field names for 5G implementation.

# Source: SCF Specification

[SCF222_5G_FAPI_PHY_API_specification-23.pdf](SCF222_5G_FAPI_PHY_API_specification-23.pdf)

# Message sequence chart (MSC)

![image.png](image%20101.png)

# OAI Tag Definitions

```c
#define  NFAPI_NR_PARAM_TLV_RELEASE_CAPABILITY_TAG 0x0001
#define  NFAPI_NR_PARAM_TLV_PHY_STATE_TAG         0x0002
#define  NFAPI_NR_PARAM_TLV_SKIP_BLANK_DL_CONFIG_TAG 0x0003
#define  NFAPI_NR_PARAM_TLV_SKIP_BLANK_UL_CONFIG_TAG 0x0004
#define  NFAPI_NR_PARAM_TLV_NUM_CONFIG_TLVS_TO_REPORT_TAG 0x0005
#define  NFAPI_NR_PARAM_TLV_CYCLIC_PREFIX_TAG 0x0006
#define  NFAPI_NR_PARAM_TLV_SUPPORTED_SUBCARRIER_SPACINGS_DL_TAG 0x0007
#define  NFAPI_NR_PARAM_TLV_SUPPORTED_BANDWIDTH_DL_TAG 0x0008
#define  NFAPI_NR_PARAM_TLV_SUPPORTED_SUBCARRIER_SPACINGS_UL_TAG 0x0009
#define  NFAPI_NR_PARAM_TLV_SUPPORTED_BANDWIDTH_UL_TAG 0x000A
#define  NFAPI_NR_PARAM_TLV_CCE_MAPPING_TYPE_TAG 0x000B
#define  NFAPI_NR_PARAM_TLV_CORESET_OUTSIDE_FIRST_3_OFDM_SYMS_OF_SLOT_TAG 0x000C
#define  NFAPI_NR_PARAM_TLV_PRECODER_GRANULARITY_CORESET_TAG 0x000D
#define  NFAPI_NR_PARAM_TLV_PDCCH_MU_MIMO_TAG 0x000E
#define  NFAPI_NR_PARAM_TLV_PDCCH_PRECODER_CYCLING_TAG 0x000F
#define  NFAPI_NR_PARAM_TLV_MAX_PDCCHS_PER_SLOT_TAG 0x0010
#define  NFAPI_NR_PARAM_TLV_PUCCH_FORMATS_TAG 0x0011
#define  NFAPI_NR_PARAM_TLV_MAX_PUCCHS_PER_SLOT_TAG 0x0012
#define  NFAPI_NR_PARAM_TLV_PDSCH_MAPPING_TYPE_TAG 0x0013
#define  NFAPI_NR_PARAM_TLV_PDSCH_ALLOCATION_TYPES_TAG 0x0014
#define  NFAPI_NR_PARAM_TLV_PDSCH_VRB_TO_PRB_MAPPING_TAG 0x0015
#define  NFAPI_NR_PARAM_TLV_PDSCH_CBG_TAG 0x0016
#define  NFAPI_NR_PARAM_TLV_PDSCH_DMRS_CONFIG_TYPES_TAG 0x0017
#define  NFAPI_NR_PARAM_TLV_PDSCH_DMRS_MAX_LENGTH_TAG 0x0018
#define  NFAPI_NR_PARAM_TLV_PDSCH_DMRS_ADDITIONAL_POS_TAG 0x0019
#define  NFAPI_NR_PARAM_TLV_MAX_PDSCH_S_YBS_PER_SLOT_TAG 0x001A
#define  NFAPI_NR_PARAM_TLV_MAX_NUMBER_MIMO_LAYERS_PDSCH_TAG 0x001B
#define  NFAPI_NR_PARAM_TLV_SUPPORTED_MAX_MODULATION_ORDER_DL_TAG 0x001C //unused
#define  NFAPI_NR_PARAM_TLV_MAX_MU_MIMO_USERS_DL_TAG 0x001D
#define  NFAPI_NR_PARAM_TLV_PDSCH_DATA_IN_DMRS_SYMBOLS_TAG 0x001E
#define  NFAPI_NR_PARAM_TLV_PREMPTION_SUPPORT_TAG 0x001F
#define  NFAPI_NR_PARAM_TLV_PDSCH_NON_SLOT_SUPPORT_TAG 0x0020
#define  NFAPI_NR_PARAM_TLV_UCI_MUX_ULSCH_IN_PUSCH_TAG 0x0021
#define  NFAPI_NR_PARAM_TLV_UCI_ONLY_PUSCH_TAG 0x0022
#define  NFAPI_NR_PARAM_TLV_PUSCH_FREQUENCY_HOPPING_TAG 0x0023
#define  NFAPI_NR_PARAM_TLV_PUSCH_DMRS_CONFIG_TYPES_TAG 0x0024
#define  NFAPI_NR_PARAM_TLV_PUSCH_DMRS_MAX_LEN_TAG 0x0025
#define  NFAPI_NR_PARAM_TLV_PUSCH_DMRS_ADDITIONAL_POS_TAG 0x0026
#define  NFAPI_NR_PARAM_TLV_PUSCH_CBG_TAG 0x0027
#define  NFAPI_NR_PARAM_TLV_PUSCH_MAPPING_TYPE_TAG 0x0028
#define  NFAPI_NR_PARAM_TLV_PUSCH_ALLOCATION_TYPES_TAG 0x0029
#define  NFAPI_NR_PARAM_TLV_PUSCH_VRB_TO_PRB_MAPPING_TAG 0x002A
#define  NFAPI_NR_PARAM_TLV_PUSCH_MAX_PTRS_PORTS_TAG 0x002B
#define  NFAPI_NR_PARAM_TLV_MAX_PDUSCHS_TBS_PER_SLOT_TAG 0x002C
#define  NFAPI_NR_PARAM_TLV_MAX_NUMBER_MIMO_LAYERS_NON_CB_PUSCH_TAG 0x002D
#define  NFAPI_NR_PARAM_TLV_SUPPORTED_MODULATION_ORDER_UL_TAG 0x002E
#define  NFAPI_NR_PARAM_TLV_MAX_MU_MIMO_USERS_UL_TAG 0x002F
#define  NFAPI_NR_PARAM_TLV_DFTS_OFDM_SUPPORT_TAG 0x0030
#define  NFAPI_NR_PARAM_TLV_PUSCH_AGGREGATION_FACTOR_TAG 0x0031
#define  NFAPI_NR_PARAM_TLV_PRACH_LONG_FORMATS_TAG 0x0032
#define  NFAPI_NR_PARAM_TLV_PRACH_SHORT_FORMATS_TAG 0x0033
#define  NFAPI_NR_PARAM_TLV_PRACH_RESTRICTED_SETS_TAG 0x0034
#define  NFAPI_NR_PARAM_TLV_MAX_PRACH_FD_OCCASIONS_IN_A_SLOT_TAG 0x0035
#define  NFAPI_NR_PARAM_TLV_RSSI_MEASUREMENT_SUPPORT_TAG 0x0036
```

```c
//nfapi_nr_config_tlv_format_t carrier config ~ precoding config:

#define NFAPI_NR_CONFIG_DL_BANDWIDTH_TAG 0x1001
#define NFAPI_NR_CONFIG_DL_FREQUENCY_TAG 0x1002
#define NFAPI_NR_CONFIG_DL_K0_TAG 0x1003
#define NFAPI_NR_CONFIG_DL_GRID_SIZE_TAG 0x1004
#define NFAPI_NR_CONFIG_NUM_TX_ANT_TAG 0x1005
#define NFAPI_NR_CONFIG_UPLINK_BANDWIDTH_TAG 0x1006
#define NFAPI_NR_CONFIG_UPLINK_FREQUENCY_TAG 0x1007
#define NFAPI_NR_CONFIG_UL_K0_TAG 0x1008
#define NFAPI_NR_CONFIG_UL_GRID_SIZE_TAG 0x1009
#define NFAPI_NR_CONFIG_NUM_RX_ANT_TAG 0x100A
#define NFAPI_NR_CONFIG_FREQUENCY_SHIFT_7P5KHZ_TAG 0x100B

#define NFAPI_NR_CONFIG_PHY_CELL_ID_TAG 0x100C
#define NFAPI_NR_CONFIG_FRAME_DUPLEX_TYPE_TAG 0x100D

#define NFAPI_NR_CONFIG_SS_PBCH_POWER_TAG 0x100E
#define NFAPI_NR_CONFIG_BCH_PAYLOAD_TAG 0x100F
#define NFAPI_NR_CONFIG_SCS_COMMON_TAG 0x1010

#define NFAPI_NR_CONFIG_PRACH_SEQUENCE_LENGTH_TAG 0x1011
#define NFAPI_NR_CONFIG_PRACH_SUB_C_SPACING_TAG 0x1012
#define NFAPI_NR_CONFIG_RESTRICTED_SET_CONFIG_TAG 0x1013
#define NFAPI_NR_CONFIG_NUM_PRACH_FD_OCCASIONS_TAG 0x1014
#define NFAPI_NR_CONFIG_PRACH_CONFIG_INDEX_TAG 0x1029
#define NFAPI_NR_CONFIG_PRACH_ROOT_SEQUENCE_INDEX_TAG 0x1015
#define NFAPI_NR_CONFIG_NUM_ROOT_SEQUENCES_TAG 0x1016
#define NFAPI_NR_CONFIG_K1_TAG 0x1017
#define NFAPI_NR_CONFIG_PRACH_ZERO_CORR_CONF_TAG 0x1018
#define NFAPI_NR_CONFIG_NUM_UNUSED_ROOT_SEQUENCES_TAG 0x1019
#define NFAPI_NR_CONFIG_UNUSED_ROOT_SEQUENCES_TAG 0x101A
#define NFAPI_NR_CONFIG_SSB_PER_RACH_TAG 0x101B
#define NFAPI_NR_CONFIG_PRACH_MULTIPLE_CARRIERS_IN_A_BAND_TAG 0x101C

#define NFAPI_NR_CONFIG_SSB_OFFSET_POINT_A_TAG 0x101D
#define NFAPI_NR_CONFIG_BETA_PSS_TAG 0x101E
#define NFAPI_NR_CONFIG_SSB_PERIOD_TAG 0x101F
#define NFAPI_NR_CONFIG_SSB_SUBCARRIER_OFFSET_TAG 0x1020
#define NFAPI_NR_CONFIG_MIB_TAG 0x1021
#define NFAPI_NR_CONFIG_SSB_MASK_TAG 0x1022
#define NFAPI_NR_CONFIG_BEAM_ID_TAG 0x1023
#define NFAPI_NR_CONFIG_SS_PBCH_MULTIPLE_CARRIERS_IN_A_BAND_TAG 0x1024
#define NFAPI_NR_CONFIG_MULTIPLE_CELLS_SS_PBCH_IN_A_CARRIER_TAG 0x1025
#define NFAPI_NR_CONFIG_TDD_PERIOD_TAG 0x1026
#define NFAPI_NR_CONFIG_SLOT_CONFIG_TAG 0x1027

#define NFAPI_NR_CONFIG_RSSI_MEASUREMENT_TAG 0x1028
#define NFAPI_NR_CONFIG_TDD_TABLE 0x1035
```

# FAPI P5 Param.Request Parameters in OAI Implementation

![image.png](image%20102.png)

# FAPI P5 Param.Response Parameters in OAI Implementation

| Tag | Table Field Name | Table |
| --- | --- | --- |
| 0x0001 | releaseCapability | [Cell and PHY Parameters (Table 3-19)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0002 | phy-State | [Cell and PHY Parameters (Table 3-19)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0003 | skipBlank-DL | [Cell and PHY Parameters (Table 3-19)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0004 | skipBlank-UL | [Cell and PHY Parameters (Table 3-19)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0005 | numConfig-TLVsToReport | [Cell and PHY Parameters (Table 3-19)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0006 | cyclicPrefix | [Carrier Parameters (Table 3-20)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0007 | subcarrierSpacings-DL | [Carrier Parameters (Table 3-20)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0008 | supportedBandwidth-DL | [Carrier Parameters (Table 3-20)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0009 | subcarrierSpacings-UL | [Carrier Parameters (Table 3-20)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x000A | supportedBandwidth-UL | [Carrier Parameters (Table 3-20)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x000B | cce-MappingType | [PDCCH Parameters (Table 3-21)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x000C | coreset-OutsideFirst3-OFDM-SymsOfSlot | [PDCCH Parameters (Table 3-21)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x000D | precoderGranularity-CORESET | [PDCCH Parameters (Table 3-21)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x000E | pdcch-MU-MIMO | [PDCCH Parameters (Table 3-21)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x000F | pdcch-PrecoderCycling | [PDCCH Parameters (Table 3-21)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0010 | max-PDCCHs-PerSlot | [PDCCH Parameters (Table 3-21)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0011 | pucch-Formats | [PUCCH Parameters (Table 3-22)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0012 | max-PUCCHs-PerSlot | [PUCCH Parameters (Table 3-22)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0013 | pdsch-MappingType | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0014 | pdsch-AllocationTypes | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0015 | pdsch-VRB-To-PRB-Mapping | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0016 | pdsch-CBG | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0017 | pdsch-DMRS-ConfigTypes | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0018 | pdsch-DMRS-MaxLength | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0019 | pdsch-DMRS-AdditionalPos | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x002C | max-PDSCH-TBs-PerSlot | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x001B | maxNumber-MIMO-Layers-PDSCH | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x001C | maxModulationOrder-DL | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x001D | max-MU-MIMO-UsersDL | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x001E | pdsch-DataIn-DMRS-Symbols | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x001F | preemptionSupport | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0020 | pdsch-NonSlotSupport | [PDSCH Parameters (Table 3-23)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0021 | uci-MUX-UL-SCH-In-PUSCH | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0022 | uci-Only-PUSCH | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0023 | pusch-FrequencyHopping | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0024 | pusch-DMRS-ConfigTypes | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0025 | pusch-DMRS-MaxLen | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0026 | pusch-DMRS-AdditionalPos | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0027 | pusch-CBG | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0028 | pusch-MappingType | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0029 | pusch-AllocationTypes | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x002A | pusch-VRB-To-PRB-Mapping | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x002B | pusch-Max-PTRS-Ports | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x002C | maxPUSCH-TBs-PerSlot | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x002D | max-MIMO-LayersNonCB-PUSCH | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x002E | maxModulationOrder-UL | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x002F | maxMU-MIMO-Users-UL | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0030 | dfts-OFDM | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0031 | pusch-AggregationFactor | [PUSCH Parameters (Table 3-26)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0032 | prach-Long-Formats | [PRACH Configuration (Table 3-28)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0033 | prach-Short-Formats | [PRACH Configuration (Table 3-28)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0034 | prach-Restricted-Sets | [PRACH Configuration (Table 3-28)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0035 | max-PRACH-FD-Occasions-In-A-Slot | [PRACH Configuration (Table 3-28)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x0036 | rssi-Measurement-Support | [PRACH Configuration (Table 3-30)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |

# FAPI P5 Config.Request Parameters in OAI Implementation

| Tag | Table Field Name | Table |
| --- | --- | --- |
| 0x1001 | dl-Bandwidth | [Carrier Configuration (Table 3-47)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1002 | dl-Frequency | [Carrier Configuration (Table 3-47)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1005 | num-TX-Ant | [Carrier Configuration (Table 3-47)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1006 | ul-Bandwidth | [Carrier Configuration (Table 3-47)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1007 | ul-Frequency | [Carrier Configuration (Table 3-47)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x100A | num-RX-Ant | [Carrier Configuration (Table 3-47)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x100B | frequencyShift7p5khz | [Carrier Configuration (Table 3-47)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x100C | phy-Cell-ID | [Cell Configuration (Table 3-48)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x100D | frameDuplexType | [Cell Configuration (Table 3-48)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x100E | ss-PBCH-Power | [SSB Power and PBCH Configuration (Table 3-49)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x100F | bch-PayloadFlag | [SSB Power and PBCH Configuration (Table 3-49)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1010 | subCarrierSpacingCommon | [SSB Resource Configuration (Table 3-55)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1011 | prach-SequenceLength | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1012 | prach-SCS | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1013 | restrictedSetConfig | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1014 | num-PRACH-FD-Occasions | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1029 | prach-ConfigIndex | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1015 | prach-RootSequenceIndex | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1016 | numRootSequences | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1017 | msgA-PUSCH-TimeDomainOffset-v4 | [MsgA-PUSCH Configuration (Table 3-52)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1018 | prach-ZeroCorrConf | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1019 | numUnusedRootSequences | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x101B | ssb-Per-RACH | [PRACH Configuration (Table 3-50)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x101C | num-PRACH-Configurations-v3 | [Multi-PRACH Configuration (Table 3-51)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x101D | Ssb-OffsetPointA | [SSB Resource Configuration (Table 3-55)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x101F | ssb-Period | [SSB Resource Configuration (Table 3-55)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1020 | ssb-SubcarrierOffset | [SSB Resource Configuration (Table 3-55)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1021 | rmsi-Presence-v3 | [SSB Resource Configuration (Table 3-55)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1022 | ssb-Mask | [SSB Resource Configuration (Table 3-55)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1023 | Beam-ID-v5 | [SSB Resource Configuration (Table 3-55)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1026 | tdd-Period | [TDD Configuration (Table 3-57)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |
| 0x1027 | slotConfig | [TDD Configuration (Table 3-57)](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) |

# FAPI P5 Config.responseParameters in OAI Implementation

<aside>
💡

When configuration succeeds, the system returns a `MSG_OK` error code **without any TLV tags**. When configuration fails, it returns MSG_INVALID_CONFIG along with TLVs that identify the specific issues.

</aside>

# Code Trace

<aside>
💡

I traced one of the CONFIG Request parameters in the code to understand how data flows from DU High to DU Low (Layer). Below are two examples: one where the config.request parameter is extracted from a parameter file, and another where the parameter value is directly hard-coded.

</aside>

## From parameter file: phy-Cell-ID

→ [**Cell Configuration (Table 3-48)**](OAI%20FAPI%20P5%20MSC%20Documentation%201961009831438048861dc07da77127c5.md) 

<aside>
💡

From this example, we can see that `phy-Cell-ID` is extracted from the `rcc.band78.tm1.106PRB.nfapi.conf` parameter file, which indicates that some parameters in FAPI P5 are obtained directly from the parameter file

</aside>

```
 #spCellConfigCommon

      physCellId                                                    = 1;
```

**Filling the prach fapi structure**

```c
nfapi_nr_prach_pdu_t  *prach_pdu = &UL_tti_req->pdus_list[UL_tti_req->n_pdus].prach_pdu;
memset(prach_pdu,0,sizeof(nfapi_nr_prach_pdu_t));
UL_tti_req->n_pdus+=1;

// filling the prach fapi structure
prach_pdu->phys_cell_id = *scc->physCellId;
```

## Calculate: dl-Bandwidth

<aside>
💡

It should be noted that this parameter (timingWindow-v3) is not read from the `oaiL1.nfapi.usrpb210.conf` parameter file, but is calculated in the program before being sent to Layer1 for configuration (P5 config.request)

</aside>

```c
static void config_common(gNB_MAC_INST *nrmac, nr_pdsch_AntennaPorts_t pdsch_AntennaPorts, int pusch_AntennaPorts, NR_ServingCellConfigCommon_t *scc)
{
  nfapi_nr_config_request_scf_t *cfg = &nrmac->config[0];
  nrmac->common_channels[0].ServingCellConfigCommon = scc;

  // Carrier configuration
  struct NR_FrequencyInfoDL *frequencyInfoDL = scc->downlinkConfigCommon->frequencyInfoDL;
  cfg->carrier_config.dl_bandwidth.value = get_supported_bw_mhz(*frequencyInfoDL->frequencyBandList.list.array[0] > 256 ? FR2 : FR1,
                                                                frequencyInfoDL->scs_SpecificCarrierList.list.array[0]->subcarrierSpacing,
                                                                frequencyInfoDL->scs_SpecificCarrierList.list.array[0]->carrierBandwidth);
  cfg->carrier_config.dl_bandwidth.tl.tag = NFAPI_NR_CONFIG_DL_BANDWIDTH_TAG; // temporary
  cfg->num_tlv++;
  LOG_I(NR_MAC, "DL_Bandwidth:%d\n", cfg->carrier_config.dl_bandwidth.value);

```

<aside>
💡

In the P5 process, `param.request` and `config.request` are the key components. Following the SCF FAPI specifications, I have organized these notes to summarize the P5 field names, providing a quick reference for parameter controls. For detailed information, you can search for specific field names in the specification document.

</aside>

# PARAM TLVs

<aside>
💡

From this summary list, you can quickly browse through all the parameters supported in FAPI P5

</aside>

## Cell and PHY parameters (Table 3-19)

- releaseCapability
- phy-State
- skipBlank-DL
- skipBlank-UL
- numConfig-TLVsToReport
- powerProfilesSupported-v3
- phy-IncludesSplit7-v6
- reference-RS-v3
- powerOffsetMin-v3
- powerOffsetMax-v3
- ss-PBCH-BlockPowerScalingUnitChoice-v4
- maxNumPDUs-InDL-TTI-v3
- maxNumPDUs-InUL-TTI-v3
- maxNumPDUs-InUL-DCI
- maxNumPDUs-InUL-DCI

## Carrier Parameters (Table 3-20)

- cyclicPrefix
- subcarrierSpacings-DL
- subcarrierSpacings-SSB-v4
- supportedBandwidth-DL
- subcarrierSpacings-UL
- supportedBandwidth-UL
- ss-PBCH-MultipleCarriersInABand-v3
- multipleCells-SS-PBCH-InACarrier-v3
- meaningOfCarrierFreq-v4
- frequencyShift7p5khz-v7
- dynamicConfigSupport-v7
- rb-BitMappingMethod-v7
- rrc-FieldBitMappingMethod-v7

## PDCCH Parameters (Table 3-21)

- cce-MappingType
- coreset-OutsideFirst3-OFDM-SymsOfSlot
- precoderGranularity-CORESET
- pdcch-MU-MIMO
- pdcch-PrecoderCycling
- max-PDCCHs-PerSlot

## PUCCH Parameters (Table 3-22)

- pucch-Formats
- max-PUCCHs-PerSlot
- pucch-GroupAndSequenceHopping-v3
- maxNum-UL-BWP-Ids-v3
- pucch-Aggregation-v3

## PDSCH Parameters (Table 3-23)

- pdsch-MappingType
- pdsch-AllocationTypes
- pdsch-VRB-To-PRB-Mapping
- pdsch-CBG
- pdsch-DMRS-ConfigTypes
- pdsch-DMRS-MaxLength
- pdsch-DMRS-AdditionalPos
- max-PDSCH-TBs-PerSlot
- max-PDSCH-TBs-PerSlot-v6
- maxNumber-MIMO-Layers-PDSCH-v6
- maxModulationOrder-DL
- max-MU-MIMO-UsersDL
- pdsch-DataIn-DMRS-Symbols
- preemptionSupport
- pdsch-NonSlotSupport
- ssb-RateMatch-v3
- rm-PatternTypeAndMethod-v3
- pdcch-RateMatch-v3
- num-RM-Pattern-LTE-CRS-PerSlot-v3
- num-RM-Pattern-LTE-CRS-In-PHY-v3
- num-RM-PatternCORESET-In-PHY-v6
- num-RM-Pattern-PRB-SymbIn-PHY-v6
- lte-CRS-RM-MBSFN-Derivation-v4
- lte-CRS-RM-Method-v4
- csi-RS-RM-v3
- pdsch-TransTypeSupport-v3
- pdsch-MAC-PDU-BitAlignment-v3
- maxNum-PRB-SymBitmapsPerSlot-v4
- maxNum-CSI-RS-RM-PerSlot-v4
- maxNum-PRS-PuncturingPerSlot-v5
- maxNum-SSB-PerPDSCH-Slot-v4
- universalRateMatch-v4
- require-PDSCH-SignalingAssociations-v4

## CSI-RS BWP Support (Table 3-24)

- csi-RS-BWP-Support

## PRS Parameters (Table 3-25)

- puncturingOf-PRS-Symbols-v5
- prs-PDUs-PerSlot-v5
- proportion-PRS-RBs-PerSlot-v5

## PUSCH Parameters (Table 3-26)

- uci-MUX-UL-SCH-In-PUSCH
- uci-Only-PUSCH
- pusch-FrequencyHopping
- pusch-DMRS-ConfigTypes
- pusch-DMRS-MaxLen
- pusch-DMRS-AdditionalPos
- pusch-CBG
- pusch-MappingType
- pusch-AllocationTypes
- pusch-VRB-To-PRB-Mapping
- pusch-Max-PTRS-Ports
- maxPUSCH-TBs-PerSlot
- maxPUSCH-TBs-PerSlot-v6
- max-MIMO-LayersNonCB-PUSCH
- Max-MIMO-LayersCB-PUSCH-v3
- maxModulationOrder-UL
- maxMU-MIMO-Users-UL
- dfts-OFDM
- pusch-AggregationFactor
- pusch-LBRM-Support-v3
- pusch-TransTypeSupport-v3
- pusch-MAC-PDU-BitAlignment-v3
- srs-TLV-BitAlignment-v6

## MsgA-PUSCH Parameters (Table 3-27)

- msgA-Num-PUSCH-ResConfig-v4
- msgA-PUSCH-TransPrecoding-v4
- msgA-IntraSlot-PUSCH-FreqHop-v4
- msgA-Max-PUSCH-FD-Occasions-v4
- msgA-GuardBand-v4
- msgA-GuardPeriod-v4
- msgA-PUSCH-MappingType-v4
- msgA-PUSCH-DMRS-MaxLen-v4
- msgA-PUSCH-DMRS-CDM-Group-v4
- msgA-PUSCH-DMRS-AdditionalPos-v4
- msgA-MaxModulationOrderUL-v4
- msgA-Max-PUSCH-PerPRU-v4
- msgA-MaxNum-CDM-Group-v4
- msgA-Max-Num-DMRS-Port-v4
- msgA-PRACH-To-PUSCH-MappingScheme-v4

## PRACH Parameters (Table 3-28)

- prach-LongFormats
- prach-ShortFormats
- prach-ShortFormatNumerologies-v5
- prach-RestrictedSets
- maxPRACH-FD-OccasionsInASlot
- maxNum-PRACH-Configurations-v3
- prach-MultipleCarriersInABand-v3
- Prach-FreqOffsetMeaning-v4
- maxNum-TD-FD-PRACH-OccasionsPerSlot-v4
- numFormats-v4
- prach-RootProcessingRate-v4
- numFormatsExt-v7
- prach-RootProcessingRateExt-v4
- prach-OccasionQueueSize-v4
- prach-OccasionsCombining-v7

## MsgA-PRACH Parameters (Table 3-29)

- msgA-MaxNum-PRACH-Configs-v4
- msgA-PRACH-LongFormats-v4
- msgA-PRACH-ShortFormats-v4
- msgA-PRACH-RestrictedSets-v4
- msgA-Max-PRACH-FD-OccasionsInASlot-v4
- msgA-PRACH-MultipleCarriersInABand-v4

## Measurement Parameters (Table 3-30)

- rssi-MeasurementSupport
- rsrp-MeasurementSupport-v4
- preamblePowerUnit-v5
- srs-RSRP-PowerUnit-v5

## UCI Parameters (Table 3-31)

- maxNum-UCI-Maps-v3
- uci-ReportFormatPUCCH-Format234-v4
- maxTotalSize-P1-P2-UCI-Maps-v7

## Capability Validity Scope (Table 3-32)

- numCapabilities-v3
- capabilityTag-v3
- validityScope-v3

## PHY Support (Table 3-33)

- num-PHY-Profiles-v3
- num-DL-BB-Ports-v3
- num-UL-BB-Ports-v3
- maxNum-PHYs-v3
- num-DL-PortRanges-v3
- dl-PortRangeStart-v3
- dl-PortRangeLen-v3
- num-UL-PortRanges-v3
- ul-PortRangeStart-v3
- ul-PortRangeLen-v3

## PHY/DFE Validity Map (Table 3-34)

- dfe-ProcessingDelays
- dfe-ProcessingLatency

## Delay Management (Table 3-35)

- timingAdvanceGranularity
- maxProcessingDelay

## Rel-16 mTRP Support (Table 3-36)

- mTRP-ProcessingSupport
- mTRP-AggregationSupport

## Protocol, User Plane and Encapsulation Parameters (Table 3-37)

- encapsulationMethod
- userPlanePacketization

## SRS Capabilities (Table 3-38)

- srs-TransmissionSchemes
- srs-MaxNumberPorts

## Spatial Multiplexing & MIMO Capabilities (Table 3-39)

- mimo-LayersSupported
- spatialMultiplexingMethods

## Semistatic Precoding and Beamforming Capabilities (Table 3-40)

- beamformingMethods
- precodingMatrixRestrictions

## 2D-DFT Capabilities (Table 3-41)

- dft-SupportedSizes
- dft-MaxTransformSize

---

# CONFIG TLVs

<aside>
💡

From this summary list, you can quickly browse through all the configuration parameters supported by DU High in FAPI P5

</aside>

## PHY Configuration (Table 3-46)

- phy-Profile-ID-v3
- indicationInstancesPerSlot-v3
- requestInstancesPerSlot-v3
- sfn-v4
- slot-v4
- subcarrierSpacing-v4
- cyclicPrefixType-v4
- phy-Group-v6
- timeOffsetToFrame-v6

---

## **Carrier Configuration (Table 3-47)**

- dl-Bandwidth
- dl-Frequency
- dl-CarrierOffset
- dl-GridSize
- num-TX-Ant
- ul-Bandwidth
- ul-Frequency
- ul-CarrierOffset
- ul-GridSize
- num-RX-Ant
- frequencyShift7p5khz
- powerProfile-v3
- powerOffset-RS-Index-v3

---

## **Cell Configuration (Table 3-48)**

- phy-Cell-ID
- frameDuplexType
- pdsch-TransTypeValidity-v3
- pusch-TransTypeValidity-v3
- n-TimingAdvanceOffset-v6

---

## **SSB Power and PBCH Configuration (Table 3-49)**

- ss-PBCH-Power
- ss-PBCH-BlockPowerScaling-v3
- bch-PayloadFlag

---

## **PRACH Configuration (Table 3-50)**

- prach-ResConfigIndex-v3
- prach-SequenceLength
- prach-SCS
- ul-BWP-PUSCH-SCS-v3
- restrictedSetConfig
- num-PRACH-FD-Occasions
- prach-ConfigIndex
- prach-Format-v4
- num-PRACH-TD-Occasions-v4
- numberOfPreambles-v4
- startPreambleIndex-v4
- prach-RootSequenceIndex
- numRootSequences
- prach-FrequencyOffset-v4
- prach-GuardbandOffset-v4
- prach-ZeroCorrConf
- numUnusedRootSequences
- unusedRootSequences
- ssb-Per-RACH
- prach-ConfigIndexExtended

---

## **Multi-PRACH Configuration (Table 3-51)**

- num-PRACH-Configurations-v3
- prach-Configuration-TLVs-v3

---

## **MsgA-PUSCH Configuration (Table 3-52)**

- msgA-PUSCH-ResConfigIndex-v4
- msgA-PRACH-ResConfigIndex-v4
- msgA-groupAorB-v4
- n-ID-MsgA-PUSCH-v4
- dmrs-Ports-v4
- available-DMRS-Sequence-IDs-v4
- pusch-DMRS-ScramblingIds-v4
- num-PUSCH-Ocas-FD-v4
- num-PUSCH-Ocas-TD-v4
- Num-PUSCH-Ocas-Slots-v4
- msgA-PUSCH-TimeDomainOffset-v4
- n-Preambles-v4
- associationPatternPeriodInSlots-v4
- num-PRACH-SlotsFor-PRACH-To-PRU-And-DMRS-Map-v4
- Prach-SlotIndicesModulusAPP-Slots-v4
- msgA-PRACH-To-PRU-And-DMRS-Mapping-v4

---

## **MsgA-PRACH-to-(PRU & DMRS) Mapping (Table 3-53)**

- Valid-RO-v4
- pru-PreambleIndexForFirstPreambleInGroup-v4
- firstPreambleIndexInGroup-v5
- num-PUSCH-Assoc-DMRS-OccasionsForThis-PRACH-RO-v4
- msgA-PUSCH-Assoc-DMRS-Occasion-v4

---

## **Multi-MsgA-PUSCH Configuration (Table 3-54)**

- num-MsgA-PUSCH-Configurations-v4
- num-PRACH-ConfigurationTLVs-v4

---

## **SSB Resource Configuration (Table 3-55)**

- ssb-ConfigIndex-v3
- Ssb-OffsetPointA
- beta-PSS-Profile-NR
- beta-PSS-Profile-SSS-v3
- ssb-Period
- ssb-SubcarrierOffset
- case-v3
- subcarrierSpacing
- subCarrierSpacingCommon
- l-Max-v3
- ssb-Mask
- beam-ID-Presence-v5
- Beam-ID-v5
- rmsi-Presence-v3

---

## **Multi-SSB Resource Configuration (Table 3-56)**

- num-SSB-Configurations-v3
- ssb-Configuration-TLVs-v3

---

## **TDD Configuration (Table 3-57)**

- tdd-Period
- slotConfig

---

## **Measurement Configuration (Table 3-58)**

- rssi-Measurement
- rsrp-Measurement-v4
- preamblePowerUnitSelection-v5
- srs-PowerUnitSelection-v5

---

## **Beamforming and Precoding Configuration (Table 3-59)**

- beamformingTable-v5
- precodingMatrix-v5
- precodingTable-v6

---

## **UCI Configuration (Table 3-60)**

- num-UCI2-Maps-v3
- numPart1Params-v3
- sizesPart1Params-v3
- mapBitWidth-v5
- map-v3

---

## **PRB-Symbol Rate Match Patterns Configuration (Table 3-61)**

- numberOf-PRB-SymbRM-Patterns-v3
- prb-Symb-RM-Pattern-ID-v3
- freqDomain-RB-v3
- symbolsIn-RB-v3
- subcarrierSpacing-v3

---

## **CORESET Rate Match Patterns Configuration (Table 3-62)**

- numberOfCORESET-RM-Patterns-v3
- coreset-RM-PatternID-v3
- freqDomainResources-v3
- symbolsPattern-v3
- subcarrierSpacing-v3

---

## **LTE-CRS Rate Match Patterns Configuration (Table 3-63)**

- numberOf-LTE-CRS-RM-Patterns-v3
- crs-RM-Pattern-ID-v3
- carrierFreq-DL-v3
- carrierBandwidth-DL-v3
- num-CRS-Ports-v3
- v-Shift-v3
- Size-MBSFN-SubframeConfigList-v3
- radioframeAllocationPeriod-v3
- radioframeAllocationOffset-v3
- lte-FrameStructureType-v3
- subframeAllocLength-v3
- subframeAllocationBitmap-v3

---

## **PUCCH Semi-Static Configuration (Table 3-64)**

- num-UL-BWP-IDs-v3
- pucch-GroupHopping-v3
- n-ID-PUCCH-Hopping-v3

---

## **PDSCH Semi-Static Configuration (Table 3-65)**

- pdsch-CBG-Scheme-v3

---

## **Delay Management Configuration (Table 3-66)**

- timingWindow-v3
- timingMode-v3
- timingPeriod-v3
- dl-TTI-RX-WindowFor-SSB-v5
- ul-TTI-RX-WindowFor-PRACH-v5

---

## **Rel-16 mTRP Configuration (Table 3-67)**

- num-TX-Ports-TRP1-v3
- num-RX-Ports-TRP1-v3

---