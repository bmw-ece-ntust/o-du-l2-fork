# UL DCI

Tags: UL_DCI

```c
typedef struct {
  /// only possible value 0: PDCCH PDU
  uint16_t PDUType;
  ///Size of the PDU control information (in bytes). This length value includes the 4 bytes required for the PDU type and PDU size parameters. Value 0 -> 65535
  uint16_t PDUSize;
  nfapi_nr_dl_tti_pdcch_pdu pdcch_pdu;
} nfapi_nr_ul_dci_request_pdus_t;
```

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

| Field | OAI Value | OSC Value |
| --- | --- | --- |
| PDUType | 0 |  |
| PDUSize | 49 |  |
| BWPSize | 106 |  |
| BWPStart | 0 |  |
| SubcarrierSpacing | 1 |  |
| CyclicPrefix | 0 |  |
| StartSymbolIndex | 0 |  |
| DurationSymbols | 1 |  |
| CceRegMappingType | 0 |  |
| RegBundleSize | 6 |  |
| InterleaverSize | 0 |  |
| CoreSetType | 1 |  |
| ShiftIndex | 0 |  |
| precoderGranularity | 0 |  |
| numDlDci | 1 |  |
| RNTI | 63491 |  |
| ScramblingId | 0 |  |
| ScramblingRNTI | 0 |  |
| CceIndex | 8 |  |
| AggregationLevel | 2 |  |
| precodingAndBeamforming.num_prgs | 0 |  |
| precodingAndBeamforming.prg_size | 0 |  |
| precodingAndBeamforming.dig_bf_interfaces | 0 |  |
| beta_PDCCH_1_0 | 0 |  |
| powerControlOffsetSS | 1 |  |
| PayloadSizeBits | 39 |  |

```c
  LOG_I(PHY, "value->PDUType: %d\n", value->PDUType);
  LOG_I(PHY, "value->PDUSize: %d\n", value->PDUSize);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.BWPSize: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.BWPSize);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.BWPStart: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.BWPStart);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.SubcarrierSpacing: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.SubcarrierSpacing);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.CyclicPrefix: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.CyclicPrefix);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.StartSymbolIndex: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.StartSymbolIndex);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.DurationSymbols: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.DurationSymbols);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.CceRegMappingType: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.CceRegMappingType);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.RegBundleSize: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.RegBundleSize);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.InterleaverSize: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.InterleaverSize);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.CoreSetType: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.CoreSetType);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.ShiftIndex: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.ShiftIndex);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.precoderGranularity: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.precoderGranularity);
  LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.numDlDci: %d\n", value->pdcch_pdu.pdcch_pdu_rel15.numDlDci);

  for (uint16_t i = 0; i < value->pdcch_pdu.pdcch_pdu_rel15.numDlDci; ++i) {
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].RNTI: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].RNTI);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].ScramblingId: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].ScramblingId);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].ScramblingRNTI: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].ScramblingRNTI);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].CceIndex: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].CceIndex);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].AggregationLevel: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].AggregationLevel);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].precodingAndBeamforming.num_prgs: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].precodingAndBeamforming.num_prgs);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].precodingAndBeamforming.prg_size: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].precodingAndBeamforming.prg_size);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].precodingAndBeamforming.dig_bf_interfaces: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].precodingAndBeamforming.dig_bf_interfaces);

    for (int prg = 0; prg < value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].precodingAndBeamforming.num_prgs; prg++) {
      LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].precodingAndBeamforming.prgs_list[%d].pm_idx: %d\n", i, prg, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].precodingAndBeamforming.prgs_list[prg].pm_idx);

      for (int digInt = 0; digInt < value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].precodingAndBeamforming.dig_bf_interfaces; digInt++) {
        LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].precodingAndBeamforming.prgs_list[%d].dig_bf_interface_list[%d].beam_idx: %d\n", i, prg, digInt, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].precodingAndBeamforming.prgs_list[prg].dig_bf_interface_list[digInt].beam_idx);
      }
    }

    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].beta_PDCCH_1_0: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].beta_PDCCH_1_0);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].powerControlOffsetSS: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].powerControlOffsetSS);
    LOG_I(PHY, "value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[%d].PayloadSizeBits: %d\n", i, value->pdcch_pdu.pdcch_pdu_rel15.dci_pdu[i].PayloadSizeBits);
  }
```