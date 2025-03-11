# PDCCH PDU

Tags: DCI, DL_TTI, PDCCH

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

# DCI PDU

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

<aside>
💡 Fixed problem

[Fix OSC DCI payload encode method](Fix%20OSC%20DCI%20payload%20encode%20method%201211009831438103ba6cc71c9ece87ab.md) 

</aside>

# DCI Payload

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

Case **TYPE_SI_RNTI_ (4)**

| Variable | OAI Value | OSC value | OAI bits len | OSC bits len |
| --- | --- | --- | --- | --- |
| dci_pdu_rel15->frequency_domain_assignment.val | 720 | 0 | 11 | 0 |
| dci_pdu_rel15->time_domain_assignment.val | 1 | 0 | 4 | 4 |
| dci_pdu_rel15->vrb_to_prb_mapping.val | 0 | 0 | 1 | 1 |
| dci_pdu_rel15->mcs | 5 | 4 | 5 | 5 |
| dci_pdu_rel15->rv | 0 | 0 | 2 | 2 |
| dci_pdu_rel15->system_info_indicator | 0 (SIB 1) | 0 (SIB 1) | 1 | 1 |

# Check PDU unpack is correct:

```c
LOG_I(PHY, "value->BWPSize: %d\n", value->BWPSize);
LOG_I(PHY, "value->BWPStart: %d\n", value->BWPStart);
LOG_I(PHY, "value->SubcarrierSpacing: %d\n", value->SubcarrierSpacing);
LOG_I(PHY, "value->CyclicPrefix: %d\n", value->CyclicPrefix);
LOG_I(PHY, "value->StartSymbolIndex: %d\n", value->StartSymbolIndex);
LOG_I(PHY, "value->DurationSymbols: %d\n", value->DurationSymbols);
LOG_I(PHY, "value->FreqDomainResource: ");
for (int i = 0; i < 6; ++i) {
    LOG_I(PHY, "%d ", value->FreqDomainResource[i]);
}
LOG_I(PHY, "\n");
LOG_I(PHY, "value->CceRegMappingType: %d\n", value->CceRegMappingType);
LOG_I(PHY, "value->RegBundleSize: %d\n", value->RegBundleSize);
LOG_I(PHY, "value->InterleaverSize: %d\n", value->InterleaverSize);
LOG_I(PHY, "value->CoreSetType: %d\n", value->CoreSetType);
LOG_I(PHY, "value->ShiftIndex: %d\n", value->ShiftIndex);
LOG_I(PHY, "value->precoderGranularity: %d\n", value->precoderGranularity);
LOG_I(PHY, "value->numDlDci: %d\n", value->numDlDci);
for (uint16_t i = 0; i < value->numDlDci; ++i) {
    LOG_I(PHY, "value->dci_pdu[%d].RNTI: %d\n", i, value->dci_pdu[i].RNTI);
    LOG_I(PHY, "value->dci_pdu[%d].ScramblingId: %d\n", i, value->dci_pdu[i].ScramblingId);
    LOG_I(PHY, "value->dci_pdu[%d].ScramblingRNTI: %d\n", i, value->dci_pdu[i].ScramblingRNTI);
    LOG_I(PHY, "value->dci_pdu[%d].CceIndex: %d\n", i, value->dci_pdu[i].CceIndex);
    LOG_I(PHY, "value->dci_pdu[%d].AggregationLevel: %d\n", i, value->dci_pdu[i].AggregationLevel);
    LOG_I(PHY, "value->dci_pdu[%d].precodingAndBeamforming.num_prgs: %d\n", i, value->dci_pdu[i].precodingAndBeamforming.num_prgs);
    LOG_I(PHY, "value->dci_pdu[%d].precodingAndBeamforming.prg_size: %d\n", i, value->dci_pdu[i].precodingAndBeamforming.prg_size);
    LOG_I(PHY, "value->dci_pdu[%d].precodingAndBeamforming.dig_bf_interfaces: %d\n", i, value->dci_pdu[i].precodingAndBeamforming.dig_bf_interfaces);
    for (int prg = 0; prg < value->dci_pdu[i].precodingAndBeamforming.num_prgs; prg++) {
        LOG_I(PHY, "value->dci_pdu[%d].precodingAndBeamforming.prgs_list[%d].pm_idx: %d\n", i, prg, value->dci_pdu[i].precodingAndBeamforming.prgs_list[prg].pm_idx);
        for (int digInt = 0; digInt < value->dci_pdu[i].precodingAndBeamforming.dig_bf_interfaces; digInt++) {
            LOG_I(PHY, "value->dci_pdu[%d].precodingAndBeamforming.prgs_list[%d].dig_bf_interface_list[%d].beam_idx: %d\n", i, prg, digInt, value->dci_pdu[i].precodingAndBeamforming.prgs_list[prg].dig_bf_interface_list[digInt].beam_idx);
        }
    }
    LOG_I(PHY, "value->dci_pdu[%d].beta_PDCCH_1_0: %d\n", i, value->dci_pdu[i].beta_PDCCH_1_0);
    LOG_I(PHY, "value->dci_pdu[%d].powerControlOffsetSS: %d\n", i, value->dci_pdu[i].powerControlOffsetSS);
    LOG_I(PHY, "value->dci_pdu[%d].PayloadSizeBits: %d\n", i, value->dci_pdu[i].PayloadSizeBits);
    LOG_I(PHY,"value->dci_pdu[i].Payload:%lx\n",value->dci_pdu[i].Payload);
}
```