# PDSCH PDU

Tags: DL_TTI, PDSCH, SIB1

```c
typedef struct {
  uint16_t pduBitmap;
  uint16_t rnti;
  uint16_t pduIndex;
  // BWP  [TS38.213 sec 12]
  /// Bandwidth part size [TS38.213 sec12]. Number of contiguous PRBs allocated to the BWP, Value: 1->275
  uint16_t BWPSize;
  /// bandwidth part start RB index from reference CRB [TS38.213 sec 12],Value: 0->274
  uint16_t BWPStart;
  /// subcarrierSpacing [TS38.211 sec 4.2], Value:0->4
  uint8_t SubcarrierSpacing;
  /// Cyclic prefix type [TS38.211 sec 4.2], 0: Normal; 1: Extended
  uint8_t CyclicPrefix;
  // Codeword information
  /// Number of code words for this RNTI (UE), Value: 1 -> 2
  uint8_t NrOfCodewords;
  /// Target coding rate [TS38.212 sec 5.4.2.1 and 38.214 sec 5.1.3.1]. This is the number of information bits per 1024 coded bits expressed in 0.1 bit units
  uint16_t targetCodeRate[2]; 
  /// QAM modulation [TS38.212 sec 5.4.2.1 and 38.214 sec 5.1.3.1], Value: 2,4,6,8
  uint8_t qamModOrder[2];
  ///  MCS index [TS38.214, sec 5.1.3.1], should match value sent in DCI Value : 0->31
  uint8_t mcsIndex[2];
  /// MCS-Table-PDSCH [TS38.214, sec 5.1.3.1] 0: notqam256, 1: qam256, 2: qam64LowSE
  uint8_t mcsTable[2];   
  /// Redundancy version index [TS38.212, Table 5.4.2.1-2 and 38.214, Table 5.1.2.1-2], should match value sent in DCI Value : 0->3
  uint8_t rvIndex[2];
  /// Transmit block size (in bytes) [TS38.214 sec 5.1.3.2], Value: 0->65535
  uint32_t TBSize[2];
  /// dataScramblingIdentityPdsch [TS38.211, sec 7.3.1.1], It equals the higher-layer parameter Datascrambling-Identity if configured and the RNTI equals the C-RNTI, otherwise L2 needs to set it to physical cell id. Value: 0->65535
  uint16_t dataScramblingId;
  /// Number of layers [TS38.211, sec 7.3.1.3]. Value : 1->8
  uint8_t nrOfLayers;
  /// PDSCH transmission schemes [TS38.214, sec5.1.1] 0: Up to 8 transmission layers
  uint8_t transmissionScheme;
  /// Reference point for PDSCH DMRS "k" - used for tone mapping [TS38.211, sec 7.4.1.1.2] Resource block bundles [TS38.211, sec 7.3.1.6] Value: 0 -> 1 If 0, the 0 reference point for PDSCH DMRS is at Point A [TS38.211 sec 4.4.4.2]. Resource block bundles generated per sub-bullets 2 and 3 in [TS38.211, sec 7.3.1.6]. For sub-bullet 2, the start of bandwidth part must be set to the start of actual bandwidth part +NstartCORESET and the bandwidth of the bandwidth part must be set to the bandwidth of the initial bandwidth part. If 1, the DMRS reference point is at the lowest VRB/PRB of the allocation. Resource block bundles generated per sub-bullets 1 [TS38.211, sec 7.3.1.6]
  uint8_t refPoint;
  // DMRS  [TS38.211 sec 7.4.1.1]
  /// DMRS symbol positions [TS38.211, sec 7.4.1.1.2 and Tables 7.4.1.1.2-3 and 7.4.1.1.2-4] Bitmap occupying the 14 LSBs with: bit 0: first symbol and for each bit 0: no DMRS 1: DMRS
  uint16_t dlDmrsSymbPos;  
  /// DL DMRS config type [TS38.211, sec 7.4.1.1.2] 0: type 1,  1: type 2
  uint8_t dmrsConfigType;
  /// DL-DMRS-Scrambling-ID [TS38.211, sec 7.4.1.1.2 ] If provided by the higher-layer and the PDSCH is scheduled by PDCCH with CRC scrambled by CRNTI or CS-RNTI, otherwise, L2 should set this to physical cell id. Value: 0->65535
  uint16_t dlDmrsScramblingId;
  /// DMRS sequence initialization [TS38.211, sec 7.4.1.1.2]. Should match what is sent in DCI 1_1, otherwise set to 0. Value : 0->1
  uint8_t SCID;
  /// Number of DM-RS CDM groups without data [TS38.212 sec 7.3.1.2.2] [TS38.214 Table 4.1-1] it determines the ratio of PDSCH EPRE to DM-RS EPRE. Value: 1->3
  uint8_t numDmrsCdmGrpsNoData;
  /// DMRS ports. [TS38.212 7.3.1.2.2] provides description between DCI 1-1 content and DMRS ports. Bitmap occupying the 11 LSBs with: bit 0: antenna port 1000 bit 11: antenna port 1011 and for each bit 0: DMRS port not used 1: DMRS port used
  uint16_t dmrsPorts;
  // Pdsch Allocation in frequency domain [TS38.214, sec 5.1.2.2]
  /// Resource Allocation Type [TS38.214, sec 5.1.2.2] 0: Type 0, 1: Type 1
  uint8_t resourceAlloc;
  /// For resource alloc type 0. TS 38.212 V15.0.x, 7.3.1.2.2 bitmap of RBs, 273 rounded up to multiple of 32. This bitmap is in units of VRBs. LSB of byte 0 of the bitmap represents the first RB of the bwp 
  uint8_t rbBitmap[36];
  /// For resource allocation type 1. [TS38.214, sec 5.1.2.2.2] The starting resource block within the BWP for this PDSCH. Value: 0->274
  uint16_t rbStart;
  /// For resource allocation type 1. [TS38.214, sec 5.1.2.2.2] The number of resource block within for this PDSCH. Value: 1->275
  uint16_t rbSize;
  /// VRB-to-PRB-mapping [TS38.211, sec 7.3.1.6] 0: non-interleaved 1: interleaved with RB size 2 2: Interleaved with RB size 4
  uint8_t VRBtoPRBMapping;
  // Resource Allocation in time domain [TS38.214, sec 5.1.2.1]
  /// Start symbol index of PDSCH mapping from the start of the slot, S. [TS38.214, Table 5.1.2.1-1] Value: 0->13
  uint8_t StartSymbolIndex;
  /// PDSCH duration in symbols, L [TS38.214, Table 5.1.2.1-1] Value: 1->14
  uint8_t NrOfSymbols;
  // PTRS [TS38.214, sec 5.1.6.3]
  /// PT-RS antenna ports [TS38.214, sec 5.1.6.3] [TS38.211, table 7.4.1.2.2-1] Bitmap occupying the 6 LSBs with: bit 0: antenna port 1000 bit 5: antenna port 1005 and for each bit 0: PTRS port not used 1: PTRS port used
  uint8_t PTRSPortIndex ;
  /// PT-RS time density [TS38.214, table 5.1.6.3-1] 0: 1 1: 2 2: 4
  uint8_t PTRSTimeDensity;
  /// PT-RS frequency density [TS38.214, table 5.1.6.3-2] 0: 2 1: 4
  uint8_t PTRSFreqDensity;
  /// PT-RS resource element offset [TS38.211, table 7.4.1.2.2-1] Value: 0->3
  uint8_t PTRSReOffset;
  ///  PT-RS-to-PDSCH EPRE ratio [TS38.214, table 4.1-2] Value :0->3
  uint8_t nEpreRatioOfPDSCHToPTRS;
  // Beamforming
  nfapi_nr_tx_precoding_and_beamforming_t precodingAndBeamforming;
  nfapi_v3_pdsch_maintenance_parameters_t maintenance_parms_v3;
}nfapi_nr_dl_tti_pdsch_pdu_rel15_t;
```

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

# Debug

```c
LOG_I(PHY, "value->pduBitmap: %d\n", value->pduBitmap);
LOG_I(PHY, "value->rnti: %d\n", value->rnti);
LOG_I(PHY, "value->pduIndex: %d\n", value->pduIndex);
LOG_I(PHY, "value->BWPSize: %d\n", value->BWPSize);
LOG_I(PHY, "value->BWPStart: %d\n", value->BWPStart);
LOG_I(PHY, "value->SubcarrierSpacing: %d\n", value->SubcarrierSpacing);
LOG_I(PHY, "value->CyclicPrefix: %d\n", value->CyclicPrefix);
LOG_I(PHY, "value->NrOfCodewords: %d\n", value->NrOfCodewords);
for (int i = 0; i < value->NrOfCodewords; ++i) {
    LOG_I(PHY, "value->targetCodeRate[%d]: %d\n", i, value->targetCodeRate[i]);
    LOG_I(PHY, "value->qamModOrder[%d]: %d\n", i, value->qamModOrder[i]);
    LOG_I(PHY, "value->mcsIndex[%d]: %d\n", i, value->mcsIndex[i]);
    LOG_I(PHY, "value->mcsTable[%d]: %d\n", i, value->mcsTable[i]);
    LOG_I(PHY, "value->rvIndex[%d]: %d\n", i, value->rvIndex[i]);
    LOG_I(PHY, "value->TBSize[%d]: %d\n", i, value->TBSize[i]);
}
LOG_I(PHY, "value->dataScramblingId: %d\n", value->dataScramblingId);
LOG_I(PHY, "value->nrOfLayers: %d\n", value->nrOfLayers);
LOG_I(PHY, "value->transmissionScheme: %d\n", value->transmissionScheme);
LOG_I(PHY, "value->refPoint: %d\n", value->refPoint);
LOG_I(PHY, "value->dlDmrsSymbPos: %d\n", value->dlDmrsSymbPos);
LOG_I(PHY, "value->dmrsConfigType: %d\n", value->dmrsConfigType);
LOG_I(PHY, "value->dlDmrsScramblingId: %d\n", value->dlDmrsScramblingId);
LOG_I(PHY, "value->SCID: %d\n", value->SCID);
LOG_I(PHY, "value->numDmrsCdmGrpsNoData: %d\n", value->numDmrsCdmGrpsNoData);
LOG_I(PHY, "value->dmrsPorts: %d\n", value->dmrsPorts);
LOG_I(PHY, "value->resourceAlloc: %d\n", value->resourceAlloc);
LOG_I(PHY, "value->rbBitmap: ");
for (int i = 0; i < 36; ++i) {
    LOG_I(PHY, "%d ", value->rbBitmap[i]);
}
LOG_I(PHY, "\n");
value->rbStart = 0;
value->rbSize = 16;
LOG_I(PHY, "value->rbStart: %d\n", value->rbStart);
LOG_I(PHY, "value->rbSize: %d\n", value->rbSize);
LOG_I(PHY, "value->VRBtoPRBMapping: %d\n", value->VRBtoPRBMapping);
LOG_I(PHY, "value->StartSymbolIndex: %d\n", value->StartSymbolIndex);
LOG_I(PHY, "value->NrOfSymbols: %d\n", value->NrOfSymbols);
if (value->pduBitmap & 0b1) {
    LOG_I(PHY, "value->PTRSPortIndex: %d\n", value->PTRSPortIndex);
    LOG_I(PHY, "value->PTRSTimeDensity: %d\n", value->PTRSTimeDensity);
    LOG_I(PHY, "value->PTRSFreqDensity: %d\n", value->PTRSFreqDensity);
    LOG_I(PHY, "value->PTRSReOffset: %d\n", value->PTRSReOffset);
    LOG_I(PHY, "value->nEpreRatioOfPDSCHToPTRS: %d\n", value->nEpreRatioOfPDSCHToPTRS);
}
LOG_I(PHY, "value->precodingAndBeamforming.num_prgs: %d\n", value->precodingAndBeamforming.num_prgs);
LOG_I(PHY, "value->precodingAndBeamforming.prg_size: %d\n", value->precodingAndBeamforming.prg_size);
LOG_I(PHY, "value->precodingAndBeamforming.dig_bf_interfaces: %d\n", value->precodingAndBeamforming.dig_bf_interfaces);
for (int i = 0; i < value->precodingAndBeamforming.num_prgs; ++i) {
    LOG_I(PHY, "value->precodingAndBeamforming.prgs_list[%d].pm_idx: %d\n", i, value->precodingAndBeamforming.prgs_list[i].pm_idx);
    for (int k = 0; k < value->precodingAndBeamforming.dig_bf_interfaces; ++k) {
        LOG_I(PHY, "value->precodingAndBeamforming.prgs_list[%d].dig_bf_interface_list[%d].beam_idx: %d\n", i, k, value->precodingAndBeamforming.prgs_list[i].dig_bf_interface_list[k].beam_idx);
    }
}
LOG_I(PHY, "powerControlOffset: %d\n", powerControlOffset);
LOG_I(PHY, "powerControlOffsetSS: %d\n", powerControlOffsetSS);

LOG_I(PHY, "value->maintenance_parms_v3.ldpcBaseGraph: %d\n", value->maintenance_parms_v3.ldpcBaseGraph);
LOG_I(PHY, "value->maintenance_parms_v3.tbSizeLbrmBytes: %d\n", value->maintenance_parms_v3.tbSizeLbrmBytes);
```