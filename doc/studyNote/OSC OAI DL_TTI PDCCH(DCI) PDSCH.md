# OSC OAI DL_TTI PDCCH(DCI) PDSCH

Start Date: 2024/05/14
Summary: The project involves the development and implementation of PDCCH and PDSCH for NR (New Radio) communication with a focus on encoding, configuration, and analysis of control and data channels.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全

![Untitled](Untitled%2082.png)

![Untitled](Untitled%2083.png)

```c
int encode_SIB1_NR(NR_BCCH_DL_SCH_Message_t *sib1, uint8_t *buffer, int max_buffer_size)
{
  AssertFatal(max_buffer_size <= NR_MAX_SIB_LENGTH / 8,
              "%s(): maximum buffer size too large: 3GPP TS 38.331 section 5.2.1 - The physical layer imposes a limit to the "
              "maximum size a SIB can take. The maximum SIB1 or SI message size is 2976 bits.\n",
              __func__);
  asn_enc_rval_t enc_rval = uper_encode_to_buffer(&asn_DEF_NR_BCCH_DL_SCH_Message, NULL, sib1, buffer, max_buffer_size);
  AssertFatal(enc_rval.encoded > 0 && enc_rval.encoded <= max_buffer_size * 8, "ASN1 message encoding failed (%s, %lu)!\n", enc_rval.failed_type->name, enc_rval.encoded);
  return (enc_rval.encoded + 7) / 8;
}
```

```
mai 15 10:46:03 [0m1715762763.365539 [NR_MAC]   cellID: bc614e
mai 15 10:46:03 [0m1715762763.365541 [NR_RRC]   SIB1 freq: offsetToPointA 86
mai 15 10:46:03 [0m1715762763.365556 [NR_RRC]   searchSpaceSIB1: 0
mai 15 10:46:03 [0m1715762763.365557 [NR_RRC]   ra_SearchSpace: 1
mai 15 10:46:03 [0m1715762763.365557 [NR_RRC]   pagingSearchSpace: 2
```

```
 五  15 16:47:19                                     <searchSpaceSIB1>1</searchSpaceSIB1>
 五  15 16:47:19                                     <pagingSearchSpace>1</pagingSearchSpace>
 五  15 16:47:19                                     <ra-SearchSpace>1</ra-SearchSpace>
 五  15 16:47:19                                 </setup>
 五  15 16:47:19                             </pdcch-ConfigCommon>
```

![Untitled](Untitled%2084.png)

# DL_TTI.request PDCCH

```c
typedef struct {
  ///Bandwidth part size [TS38.213 sec12]. Number of contiguous PRBs allocated to the BWP,Value: 1->275
  uint16_t BWPSize;
  ///bandwidth part start RB index from reference CRB, [TS38.213 sec 12], Value: 0->274
  uint16_t BWPStart;
  ///subcarrierSpacing [TS38.211 sec 4.2], Value:0->4
  uint8_t SubcarrierSpacing;
  ///Cyclic prefix type [TS38.211 sec 4.2], 0: Normal; 1: Extended
  uint8_t CyclicPrefix;
  ///Starting OFDM symbol for the CORESET, Value: 0->13
  uint8_t StartSymbolIndex;
///Contiguous time duration of the CORESET in number of symbols. Corresponds to L1 parameter 𝑁𝑠𝑦𝑚𝑏_𝐶𝑂𝑅𝐸𝑆𝐸𝑇 [TS38.211 sec 7.3.2.2] Value: 1,2,3
  uint8_t DurationSymbols; 
  ///Frequency domain resources. This is a bitmap defining non-overlapping groups of 6 PRBs in ascending order. [TS38.213 10.1]. Also, corresponds to L1 parameter CORE SET RB N [TS38.211 sec 7.3.2.2] Bitmap of uint8 array. 45 bits.
  uint8_t FreqDomainResource[6];
  ///CORESET-CCE-to-REG-mapping-type [TS38.211 sec 7.3.2.2] 0: non-interleaved 1: interleaved
  uint8_t CceRegMappingType;
  ///The number of REGs in a bundle. Must be 6 for cceRegMappingType = nonInterleaved. For cceRegMappingType = interleaved, must belong to {2,6} if duration = 1,2 and must belong to {3,6} if duration = 3. Corresponds to parameter L. [TS38.211 sec 7.3.2.2] Value: 2,3,6
  uint8_t RegBundleSize;
  ///The interleaver size. For interleaved mapping belongs to {2,3,6} and for non-interleaved mapping is NA. Corresponds to parameter R. [TS38.211 sec 7.3.2.2] Value: 2,3,6 CoreSetType
  uint8_t InterleaverSize; 
  ///[TS38.211 sec 7.3.2.2 and sec 7.4.1.3.2] 0: CORESET is configured by the PBCH or SIB1 (subcarrier 0 of CRB0 for DMRS mapping) 1: otherwise (subcarrier 0 of CORESET)
  uint8_t CoreSetType;
  ///[TS38.211 sec 7.3.2.2] Not applicable for non-interleaved mapping. For interleaved mapping and a PDCCH transmitted in a CORESET configured by the PBCH or SIB1 this should be set to phy cell ID. Value: 10 bits Otherwise, for interleaved mapping this is set to 0-> max num of PRBs. Value 0-> 275
  uint16_t ShiftIndex;
  ///Granularity of precoding [TS38.211 sec 7.3.2.2] Field Type Description 0: sameAsRegBundle 1: allContiguousRBs
  uint8_t precoderGranularity;
  ///Number of DCIs in this CORESET.Value: 0->MaxDciPerSlot
  uint16_t numDlDci;
  ///DL DCI PDU
  nfapi_nr_dl_dci_pdu_t dci_pdu[MAX_DCI_CORESET];
}  nfapi_nr_dl_tti_pdcch_pdu_rel15_t;
```

| Name | OAI (SIB1) | OAI (Other) | OSC |
| --- | --- | --- | --- |
| BWPSize | 48 | 106 | 273 |
| BWPStart | 27 | 0 | 0 |
| SubcarrierSpacing | 1 | 1 | 0 |
| CyclicPrefix | 0 | 0 | 0 |
| StartSymbolIndex | 0 | 0 | 0 |
| DurationSymbols | 1 | 1 | 1 |
| FreqDomainResource[] | **255 0 0 0 0 0** | **255 255 0 0 0 0** | **0 0 0 252 3 0** |
|  |  |  | **0 31 224 0 0 0** |
| CceRegMappingType | 1 | 0 | 1 |
| RegBundleSize | 6 | 6 | 6 |
| InterleaverSize | 2 | 0 | 2 |
| CoreSetType | 0 | 1 | 0 |
| ShiftIndex (PCI) | 0 | 0 | 1 |
| precoderGranularity | 0 | 0 | 0 |
| numDlDci | 1 | 1 | 1 |

```c
static NR_ControlResourceSet_t *get_coreset_config(int bwp_id, int curr_bwp, uint64_t ssb_bitmap)
{
  NR_ControlResourceSet_t *coreset = calloc(1, sizeof(*coreset));
  AssertFatal(coreset != NULL, "out of memory\n");
  // frequency domain resources depending on BWP size
  coreset->frequencyDomainResources.buf = calloc(1,6);
  coreset->frequencyDomainResources.buf[0] = (curr_bwp < 48) ? 0xf0 : 0xff;
  coreset->frequencyDomainResources.buf[1] = (curr_bwp < 96) ? 0x00 : 0xff;
  coreset->frequencyDomainResources.buf[2] = (curr_bwp < 144) ? 0x00 : 0xff;
  coreset->frequencyDomainResources.buf[3] = (curr_bwp < 192) ? 0x00 : 0xff;
  coreset->frequencyDomainResources.buf[4] = (curr_bwp < 240) ? 0x00 : 0xff;
  coreset->frequencyDomainResources.buf[5] = 0x00;
  coreset->frequencyDomainResources.size = 6;
  coreset->frequencyDomainResources.bits_unused = 3;
  coreset->duration = (curr_bwp < 48) ? 2 : 1;
  coreset->cce_REG_MappingType.present = NR_ControlResourceSet__cce_REG_MappingType_PR_nonInterleaved;
  coreset->precoderGranularity = NR_ControlResourceSet__precoderGranularity_sameAsREG_bundle;

```

```c
void fill_coresetZero(NR_ControlResourceSet_t *coreset0, NR_Type0_PDCCH_CSS_config_t *type0_PDCCH_CSS_config)
{
  AssertFatal(type0_PDCCH_CSS_config, "No type0 CSS configuration\n");
  AssertFatal(coreset0, "Coreset0 should have been allocated outside of this function\n");
  coreset0->controlResourceSetId = 0;
  int duration = type0_PDCCH_CSS_config->num_symbols;

  if(coreset0->frequencyDomainResources.buf == NULL)
    coreset0->frequencyDomainResources.buf = calloc(1,6);

  switch(type0_PDCCH_CSS_config->num_rbs){
    case 24:
      coreset0->frequencyDomainResources.buf[0] = 0xf0;
      coreset0->frequencyDomainResources.buf[1] = 0;
      break;
    case 48:
      coreset0->frequencyDomainResources.buf[0] = 0xff;
      coreset0->frequencyDomainResources.buf[1] = 0;
      break;
    case 96:
      coreset0->frequencyDomainResources.buf[0] = 0xff;
      coreset0->frequencyDomainResources.buf[1] = 0xff;
      break;
```

[trace code](trace%20code%2012110098314381c78cbffdee90b90c8f.csv)

## DCI PDU

```c
typedef struct {
  // The RNTI used for identifying the UE when receiving the PDU Value: 1 -> 65535.
  uint16_t RNTI;
  // For a UE-specific search space it equals the higher-layer parameter PDCCH-DMRSScrambling-ID if configured,
  // otherwise it should be set to the phy cell ID. [TS38.211, sec 7.3.2.3] Value: 0->65535
  uint16_t ScramblingId;
  // For a UE-specific search space where PDCCH-DMRSScrambling- ID is configured This param equals the CRNTI.
  // Otherwise, it should be set to 0. [TS38.211, sec 7.3.2.3] Value: 0 -> 65535 
  uint16_t ScramblingRNTI;
  // CCE start Index used to send the DCI Value: 0->135
  uint8_t CceIndex;
  // Aggregation level used [TS38.211, sec 7.3.2.1] Value: 1,2,4,8,16
  uint8_t AggregationLevel;
  // Precoding and Beamforming structure See Table 3-43
  nfapi_nr_tx_precoding_and_beamforming_t precodingAndBeamforming;
  // PDCCH power value used for PDCCH Format 1_0 with CRC scrambled by SI-RNTI, PI-RNTI or RA-RNTI.
  // This is ratio of SSB/PBCH EPRE to PDCCH and PDCCH DMRS EPRE [TS38.213, sec 4.1]
  // Value :0->17 Report title: 5G FAPI: PHY API Specification Issue date: 29 June 2019 Version: 222.10.17 68 Field Type Description representing -8 to 8 dB in 1dB steps
  uint8_t beta_PDCCH_1_0;
  // PDCCH power value used for all other PDCCH Formats.
  // This is ratio of SSB/PBCH block EPRE to PDCCH and PDCCH DMRS EPRE [TS38.214, sec 4.1] Values: 0: -3dB,1: 0dB,2: 3dB,3: 6dB
  uint8_t powerControlOffsetSS;
  // The total DCI length (in bits) including padding bits [TS38.212 sec 7.3.1] Range 0->DCI_PAYLOAD_BYTE_LEN*8
  uint16_t PayloadSizeBits;
  // DCI payload, where the actual size is defined by PayloadSizeBits. The bit order is as following bit0-bit7 are mapped to first byte of MSB - LSB
  uint8_t Payload[DCI_PAYLOAD_BYTE_LEN] __attribute__((aligned(32)));

} nfapi_nr_dl_dci_pdu_t;
```

| Name | OAI | OSC |
| --- | --- | --- |
| RNTI | 65535 | 65535 |
| ScramblingId (pci) | 0 | 1 |
| ScramblingRNTI | 0 | 0 |
| CceIndex | 0 | 0 |
| **AggregationLevel** | 4 | 4 |
| beta_PDCCH_1_0 | 0 | 0 |
| powerControlOffsetSS | 1 | 0 |
| PayloadSizeBits | 39 | 28 |
| **Payload** | 0 0 14 1 2d 0 0 0 | 0 0 0 80 0 0 0 0 |
|  | **2d 0 1 14 0 0 0 0** | 0 0 5 3 d0 0 0 0 (no reverse) |
|  | **2d 01 14 00 00** | 0 0 14 8 5a 0 0 0 (reverse) |
|  |  | 0 0 14 1 2d 0 0 0 (only reverse MCS) |

```
 五  23 17:00:30 dlDciPtr->Payload[2]:0x14 is mcs
 五  23 17:00:30 dlDciPtr->Payload[3]:0x8 is timedomainassign
 五  23 17:00:30 dlDciPtr->Payload[4]:0x5a is freqdomainassign
```

## DCI Payload

![Untitled](Untitled%2085.png)

```c
typedef struct {

  uint8_t     format_indicator; //1 bit
  uint8_t     ra_preamble_index; //6 bits
  uint8_t     ss_pbch_index; //6 bits
  uint8_t     prach_mask_index; //4 bits
  uint8_t     mcs; //5 bits
  uint8_t     ndi; //1 bit
  uint8_t     rv; //2 bits
  uint8_t     harq_pid; //4 bits
  uint8_t     tpc; //2 bits
  uint8_t     short_messages_indicator; //2 bits
  uint8_t     short_messages; //8 bits
  uint8_t     tb_scaling; //2 bits
  uint8_t     pucch_resource_indicator; //3 bits
  uint8_t     system_info_indicator; //1 bit
  uint8_t     ulsch_indicator;
  uint8_t     slot_format_indicator_count;
  uint8_t     *slot_format_indicators;
 
  uint8_t     pre_emption_indication_count;
  uint16_t    *pre_emption_indications; //14 bit each
 
  uint8_t     block_number_count;
  uint8_t     *block_numbers;
  uint8_t     padding;

  dci_field_t mcs2; //variable
  dci_field_t ndi2; //variable
  dci_field_t rv2; //variable
  dci_field_t frequency_domain_assignment; //variable
  dci_field_t time_domain_assignment; //variable
  dci_field_t frequency_hopping_flag; //variable
  dci_field_t vrb_to_prb_mapping; //variable
  dci_field_t dai[2]; //variable
  dci_field_t pdsch_to_harq_feedback_timing_indicator; //variable
  dci_field_t carrier_indicator; //variable
  dci_field_t bwp_indicator; //variable
  dci_field_t prb_bundling_size_indicator; //variable
  dci_field_t rate_matching_indicator; //variable
  dci_field_t zp_csi_rs_trigger; //variable
  dci_field_t transmission_configuration_indication; //variable
  dci_field_t srs_request; //variable
  dci_field_t cbgti; //variable
  dci_field_t cbgfi; //variable
  dci_field_t srs_resource_indicator; //variable
  dci_field_t precoding_information; //variable
  dci_field_t csi_request; //variable
  dci_field_t ptrs_dmrs_association; //variable
  dci_field_t beta_offset_indicator; //variable
  dci_field_t cloded_loop_indicator; //variable
  dci_field_t ul_sul_indicator; //variable
  dci_field_t antenna_ports; //variable
  dci_field_t dmrs_sequence_initialization;
  dci_field_t reserved; //1_0/C-RNTI:10 bits, 1_0/P-RNTI: 6 bits, 1_0/SI-&RA-RNTI: 16 bits

} dci_pdu_rel15_t;
```

| Name | OAI | OSC |
| --- | --- | --- |
| **dci_format** | **0  (NR_DL_DCI_FORMAT_1_0)** |  |
| **rnti_type** | 4  (TYPE_SI_RNTI_) | SI_RNTI_TYPE |
| coreset0Size |  | 24 |
| **pdsch_pdu_rel15->rbSize** | 16 | 14 |
| **pdsch_pdu_rel15->rbStart** | 0 | 86 |
| **type0_PDCCH_CSS_config->num_rbs** | 48 |  |
| **sib1:bwpStart** | 27 | 0 |
| **bwpSize** | 48 | 273 |
| **dlDmrsSymbPos** | **0x244** |  |

| Variable | OAI Value | OSC Value |
| --- | --- | --- |
| dci_payload.bwp_indicator.val | 0 |  |
| dci_payload.frequency_domain_assignment.val | 720 | 0 |
| dci_payload.time_domain_assignment.val | 1 | 0 |
| dci_payload.mcs | 5 |  |
| dci_payload.rv | 0 |  |
| dci_payload.harq_pid | 0 |  |
| dci_payload.ndi | 0 |  |
| dci_payload.dai[0].val | 0 |  |
| dci_payload.tpc | 0 |  |
| dci_payload.pucch_resource_indicator | 0 |  |
| dci_payload.pdsch_to_harq_feedback_timing_indicator.val | 0 |  |
| dci_payload.antenna_ports.val | 0 |  |
| dci_payload.dmrs_sequence_initialization.val | 0 |  |
|  |  |  |

Case **TYPE_SI_RNTI_ (4)**

| Variable | OAI Value | OSC value | OAI bits len | OSC bits len |
| --- | --- | --- | --- | --- |
| dci_pdu_rel15->frequency_domain_assignment.val | 720 | 0 | 11 | 0 |
| dci_pdu_rel15->time_domain_assignment.val | 1 | 0 | 4 | 4 |
| dci_pdu_rel15->vrb_to_prb_mapping.val | 0 | 0 | 1 | 1 |
| dci_pdu_rel15->mcs | 5 | 4 | 5 | 5 |
| dci_pdu_rel15->rv | 0 | 0 | 2 | 2 |
| dci_pdu_rel15->system_info_indicator | 0 (SIB 1) | 0 (SIB 1) | 1 | 1 |

### **NR_DL_DCI_FORMAT_1_0**

```c
case TYPE_SI_RNTI_:
        pos = 1;
        // Freq domain assignment 0-16 bit
        fsize = (int)ceil(log2((N_RB * (N_RB + 1)) >> 1));
        LOG_D(NR_MAC, "fsize = %i\n", fsize);
        for (int i = 0; i < fsize; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->frequency_domain_assignment.val >> (fsize - i - 1)) & 1) << (dci_size - pos++);
        LOG_D(NR_MAC, "dci_pdu_rel15->frequency_domain_assignment.val = %i\n", dci_pdu_rel15->frequency_domain_assignment.val);
        // Time domain assignment 4 bit
        for (int i = 0; i < 4; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->time_domain_assignment.val >> (3 - i)) & 1) << (dci_size - pos++);
        LOG_D(NR_MAC, "dci_pdu_rel15->time_domain_assignment.val = %i\n", dci_pdu_rel15->time_domain_assignment.val);
        // VRB to PRB mapping 1 bit
        *dci_pdu |= ((uint64_t)dci_pdu_rel15->vrb_to_prb_mapping.val & 1) << (dci_size - pos++);
        LOG_D(NR_MAC, "dci_pdu_rel15->vrb_to_prb_mapping.val = %i\n", dci_pdu_rel15->vrb_to_prb_mapping.val);
        // MCS 5bit  //bit over 32, so dci_pdu ++
        for (int i = 0; i < 5; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->mcs >> (4 - i)) & 1) << (dci_size - pos++);
        LOG_D(NR_MAC, "dci_pdu_rel15->mcs = %i\n", dci_pdu_rel15->mcs);
        // Redundancy version  2bit
        for (int i = 0; i < 2; i++)
          *dci_pdu |= (((uint64_t)dci_pdu_rel15->rv >> (1 - i)) & 1) << (dci_size - pos++);
        LOG_D(NR_MAC, "dci_pdu_rel15->rv = %i\n", dci_pdu_rel15->rv);
        // System information indicator 1bit
        *dci_pdu |= ((uint64_t)dci_pdu_rel15->system_info_indicator & 1) << (dci_size - pos++);
        LOG_D(NR_MAC, "dci_pdu_rel15->system_info_indicator = %i\n", dci_pdu_rel15->system_info_indicator);
	        break;
```

|  | OAI | OSC |
| --- | --- | --- |
| **N_RB / coreset0Size** | 48 | 273 |

![Untitled](Untitled%2086.png)

![Untitled](Untitled%2087.png)

![Untitled](Untitled%2088.png)

## PDSCH

| Variable | OAI Value | OSC Value |  |
| --- | --- | --- | --- |
| value->targetCodeRate[0] | 3790 | 308 | 308 (not important) |
| value->qamModOrder[0] | 2 | 2 |  |
| value->mcsIndex[0] | 5 | 4 | 5 |
| value->mcsTable[0] | 0 | 0 |  |
| value->rvIndex[0] | 0 | 0 |  |
| value->TBSize[0] | 129 | 123 | 123 (can’t connect) |
| value->pduBitmap | 0 | 0 |  |
| value->rnti | 65535 | 65535 |  |
| value->pduIndex | 0 | 0 |  |
| value->BWPSize | 48 | 273 | 48 |
| value->BWPStart | 27 | 0 | 27 |
| value->SubcarrierSpacing | 1 | 1 |  |
| value->CyclicPrefix | 0 | 0 |  |
| value->NrOfCodewords | 1 | 1 |  |
| value->dataScramblingId | 0 | 1 | 0 |
| value->nrOfLayers | 1 | 1 |  |
| value->transmissionScheme | 0 | 0 |  |
| value->refPoint | 1 | 0 | important |
| value->dlDmrsSymbPos | 580 | 4 | important |
| value->dmrsConfigType | 0 | 0 |  |
| value->dlDmrsScramblingId | 0 | 1 | 0 |
| value->SCID | 0 | 0 |  |
| value->numDmrsCdmGrpsNoData | 2 | 1 | important |
| value->dmrsPorts | 1 | 1 |  |
| value->resourceAlloc | 1 | 1 |  |
| value->rbBitmap[0] | 0 | 0 |  |
| value->rbStart | 0 | 106 | 0 |
| value->rbSize | 16 | 14 | 16 |
| value->VRBtoPRBMapping | 0 | 0 |  |
| value->StartSymbolIndex | 2 | 3 | important |
| value->NrOfSymbols | 10 | 11 | important |
| **powerControlOffset** | 0 | 8 |  |
| **powerControlOffsetSS** | 0 | 1 |  |
| value->PTRSPortIndex | 0 | 0 |  |
| value->PTRSTimeDensity | 0 | 0 |  |
| value->PTRSFreqDensity | 0 | 0 |  |
| value->PTRSReOffset | 0 | 0 |  |
| value->nEpreRatioOfPDSCHToPTRS | 0 | 0 |  |
| value->precodingAndBeamforming.num_prgs | 0 | 1 | important |
| value->precodingAndBeamforming.prg_size | 0 | 1 | important |
| value->precodingAndBeamforming.dig_bf_interfaces | 0 | 0 |  |
| **value->maintenance_parms_v3.ldpcBaseGraph** | 2 |  |  |
| **value->maintenance_parms_v3.tbSizeLbrmBytes** | **57376** |  |  |

```c
 value->pduBitmap: 0
 五  24 21:16:50 [0m[PHY]   value->rnti: 65535
 五  24 21:16:50 [0m[PHY]   value->pduIndex: 0
 五  24 21:16:50 [0m[PHY]   value->BWPSize: 48
 五  24 21:16:50 [0m[PHY]   value->BWPStart: 27
 五  24 21:16:50 [0m[PHY]   value->SubcarrierSpacing: 1
 五  24 21:16:50 [0m[PHY]   value->CyclicPrefix: 0
 五  24 21:16:50 [0m[PHY]   value->NrOfCodewords: 1
 五  24 21:16:50 [0m[PHY]   value->targetCodeRate[0]: 308
 五  24 21:16:50 [0m[PHY]   value->qamModOrder[0]: 2
 五  24 21:16:50 [0m[PHY]   value->mcsIndex[0]: 5
 五  24 21:16:50 [0m[PHY]   value->mcsTable[0]: 0
 五  24 21:16:50 [0m[PHY]   value->rvIndex[0]: 0
 五  24 21:16:50 [0m[PHY]   value->TBSize[0]: 129
 五  24 21:16:50 [0m[PHY]   value->dataScramblingId: 0
 五  24 21:16:50 [0m[PHY]   value->nrOfLayers: 1
 五  24 21:16:50 [0m[PHY]   value->transmissionScheme: 0
 五  24 21:16:50 [0m[PHY]   value->refPoint: 1
 五  24 21:16:50 [0m[PHY]   value->dlDmrsSymbPos: 580
 五  24 21:16:50 [0m[PHY]   value->dmrsConfigType: 0
 五  24 21:16:50 [0m[PHY]   value->dlDmrsScramblingId: 0
 五  24 21:16:50 [0m[PHY]   value->SCID: 0
 五  24 21:16:50 [0m[PHY]   value->numDmrsCdmGrpsNoData: 2
 五  24 21:16:50 [0m[PHY]   value->dmrsPorts: 1
 五  24 21:16:50 [0m[PHY]   value->resourceAlloc: 1
 五  24 21:16:50 [0m[PHY]   value->rbBitmap: [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   0 [0m[PHY]   
 五  24 21:16:50 [0m[PHY]   value->rbStart: 27
 五  24 21:16:50 [0m[PHY]   value->rbSize: 13
 五  24 21:16:50 [0m[PHY]   value->VRBtoPRBMapping: 0
 五  24 21:16:50 [0m[PHY]   value->StartSymbolIndex: 2
 五  24 21:16:50 [0m[PHY]   value->NrOfSymbols: 10
 五  24 21:16:50 [0m[PHY]   value->PTRSPortIndex: 0
 五  24 21:16:50 [0m[PHY]   value->PTRSTimeDensity: 0
 五  24 21:16:50 [0m[PHY]   value->PTRSFreqDensity: 0
 五  24 21:16:50 [0m[PHY]   value->PTRSReOffset: 0
 五  24 21:16:50 [0m[PHY]   value->nEpreRatioOfPDSCHToPTRS: 0
 五  24 21:16:50 [0m[PHY]   value->precodingAndBeamforming.num_prgs: 0
 五  24 21:16:50 [0m[PHY]   value->precodingAndBeamforming.prg_size: 0
 五  24 21:16:50 [0m[PHY]   value->precodingAndBeamforming.dig_bf_interfaces: 0
 五  24 21:16:50 [0m[PHY]   powerControlOffset: 8
 五  24 21:16:50 [0m[PHY]   powerControlOffsetSS: 1
 五  24 21:16:50 [0m[PHY]   value->maintenance_parms_v3.ldpcBaseGraph: 2
 五  24 21:16:50 [0m[PHY]   value->maintenance_parms_v3.tbSizeLbrmBytes: 0
 五  24 21:16:50 [0m[PHY]   value->pduBitmap: 0
```