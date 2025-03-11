# compare MSG2 RAR DCI PDU

Start Date: 2024/07/05
Summary: Comparison of MSG2, RAR, DCI, and PDU formats in 5G communications, detailing structures, parameters, and log functions.
Status: Done
Assign: 陳奕全, Ming 咚咚 [銘鴻]

- nfapi_nr_dl_tti_pdcch_pdu_rel15_t
    - nfapi_nr_dl_dci_pdu_t → `OAI_OSC_fillRarDlDciPdu`
        - Payload

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

```c
/* Reference -> O-RAN.WG8.AAD.0-v07.00, Table 9-42 DL-DCI Configuration */
typedef struct dlDCI
{
   uint16_t rnti;
   uint16_t scramblingId;
   uint16_t scramblingRnti;
   uint8_t cceIndex;
   uint8_t aggregLevel;
   BeamformingInfo beamPdcchInfo;
   TxPowerPdcchInfo txPdcchPower;
   PdschCfg     pdschCfg;
}DlDCI;

typedef struct pdcchCfg
{
   /* coreset-0 configuration */
   CoresetCfg coresetCfg;
   uint16_t   numDlDci;
   DlDCI      dci[MAX_NUM_PDCCH]; 
} PdcchCfg;
/* end of SIB1 PDCCH structures */
```

<aside>
💡 PATH:
- mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/lwr_mac_fsm.c
- openairinterface5g/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_RA.c

</aside>

- DL_TTI PDCCH

| Name | OAI Value | OSC Value |
| --- | --- | --- |
| BWPSize | 48 | 106 |
| BWPStart | 27 | 0 |
| SubcarrierSpacing | 1 | 1 |
| CyclicPrefix | 0 | 0 |
| StartSymbolIndex | 0 | 0 |
| DurationSymbols | 1 | 1 |
| FreqDomainResource | ff 00 00 00 00 00 | 00 1f e0 00 00 00 |
| CceRegMappingType | 1 | 1 |
| RegBundleSize | 6 | 6 |
| InterleaverSize | 2 | 2 |
| CoreSetType | 0 | 0 |
| ShiftIndex | 0 | 0 |
| precoderGranularity | 0 | 0 |
| numDlDci | 1 | 1 |

<aside>
💡 Modify path:
- mwnl-odu-at-oai-based-on-scf/l2/src/5gnrsch/sch_rach.c :958

</aside>

- DL_TTI PDSCH
    
    
    | Parameter | OAI Value | OSC Value |  |
    | --- | --- | --- | --- |
    | pduBitmap | 0 | 0 |  |
    | rnti | 267 | 1 | calculateRaRnti |
    | pduIndex | 0 | 0 |  |
    | BWPSize | 48 | 106 |  |
    | BWPStart | 27 | 0 |  |
    | SubcarrierSpacing | 1 | 1 |  |
    | CyclicPrefix | 0 | 0 |  |
    | NrOfCodewords | 1 | 1 |  |
    | targetCodeRate[0] | 1200 | 308 |  |
    | qamModOrder[0] | 2 | 2 |  |
    | mcsIndex[0] | 0 | 5 | 0 |
    | mcsTable[0] | 0 | 0 |  |
    | rvIndex[0] | 0 | 0 |  |
    | TBSize[0] | 11 | 42 | 11 |
    | dataScramblingId | 0 | 0 |  |
    | nrOfLayers | 1 | 1 |  |
    | transmissionScheme | 0 | 0 |  |
    | refPoint | 0 | 0 |  |
    | dlDmrsSymbPos | 4 | 4 |  |
    | dmrsConfigType | 0 | 0 |  |
    | dlDmrsScramblingId | 0 | 0 |  |
    | SCID | 0 | 0 |  |
    | numDmrsCdmGrpsNoData | 2 | 1 |  |
    | dmrsPorts | 1 | 0 |  |
    | resourceAlloc | 1 | 1 |  |
    | rbStart | 0 | 269 |  |
    | rbSize | 8 | 4 |  |
    | VRBtoPRBMapping | 0 | 0 |  |
    | StartSymbolIndex | 1 | 1 |  |
    | NrOfSymbols | 5 | 13 |  |
    | num_prgs | 0 | 1 |  |
    | prg_size | 0 | 1 |  |
    | dig_bf_interfaces | 0 | 0 |  |
    | pm_idx | 0 | 0 |  |
    | beam_idx | 0 | 0 |  |
    | tbSizeLbrmBytes | 92200 | N/A |  |
    | ldpcBaseGraph | 2 | N/A |  |

- DCI

| Name | OAI Value | OSC Value |
| --- | --- | --- |
| RNTI | 267 | 1 |
| ScramblingId | 0 | 0 |
| ScramblingRNTI | 0 | 0 |
| CceIndex | 0 | 4 |
| CceIndex **/* considering SIB1 is sent at cce 0-1-2-3 */** |  |  |
| AggregationLevel | 4 | 4 |
| precodingAndBeamforming.num_prgs | 0 | 1 |
| precodingAndBeamforming.prg_size | 0 | 1 |
| precodingAndBeamforming.dig_bf_interfaces | 0 | 0 |
| precodingAndBeamforming.prgs_list[0].pm_idx | 0 | 0 |
| precodingAndBeamforming.prgs_list[0].dig_bf_interface_list[0].beam_idx | 0 | 0 |
| beta_PDCCH_1_0 | 0 | 0 |
| powerControlOffsetSS | 1 | 0 |
| PayloadSizeBits | 39 | 28 |
| Payload | 00 00 00 02 15 00 00 00 | 00 00 00 05 00 00 00 00 |

<aside>
💡 Modify path:
mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/lwr_mac_fsm.c :4760

</aside>

Case **RA-RNTI**

| Variable | OAI Value | OSC value |
| --- | --- | --- |
| **pdsch_pdu_rel15->rbSize** | 8 | same as PDSCH |
| **pdsch_pdu_rel15->rbStart:** | 0 | same as PDSCH |
| **BWPSize:** | 48 | same as PDCCH |
| **dci_payload.frequency_domain_assignment.val** | 336 | 720 |
| **dci_payload.time_domain_assignment.val** | 2 | 0 |
| **dci_payload.vrb_to_prb_mapping.val** | 0 | 0 |
| **dci_payload.mcs** | 0 | 0 |
| **dci_payload.tb_scaling** | 0 | 0 |

- OAI
    - **DCI params: rnti 0x10b**
    - **rnti_type 5**
    - **dci_format 0**
    - **coreset params:**
        - **FreqDomainResource 6010000000000ff**
        - **start_symbol 0**
        - **n_symb 1**

---

## Backup print log function:

### print_dl_dci_pdu

```bash
void print_dl_dci_pdu(const nfapi_nr_dl_dci_pdu_t* dlDciPtr) {
    printf("RNTI: %u\n", dlDciPtr->RNTI);
    printf("ScramblingId: %u\n", dlDciPtr->ScramblingId);
    printf("ScramblingRNTI: %u\n", dlDciPtr->ScramblingRNTI);
    printf("CceIndex: %u\n", dlDciPtr->CceIndex);
    printf("AggregationLevel: %u\n", dlDciPtr->AggregationLevel);
    printf("precodingAndBeamforming.num_prgs: %u\n", dlDciPtr->precodingAndBeamforming.num_prgs);
    printf("precodingAndBeamforming.prg_size: %u\n", dlDciPtr->precodingAndBeamforming.prg_size);
    printf("precodingAndBeamforming.dig_bf_interfaces: %u\n", dlDciPtr->precodingAndBeamforming.dig_bf_interfaces);
    printf("precodingAndBeamforming.prgs_list[0].pm_idx: %u\n", dlDciPtr->precodingAndBeamforming.prgs_list[0].pm_idx);
    printf("precodingAndBeamforming.prgs_list[0].dig_bf_interface_list[0].beam_idx: %u\n", dlDciPtr->precodingAndBeamforming.prgs_list[0].dig_bf_interface_list[0].beam_idx);
    printf("beta_PDCCH_1_0: %u\n", dlDciPtr->beta_PDCCH_1_0);
    printf("powerControlOffsetSS: %u\n", dlDciPtr->powerControlOffsetSS);
    printf("PayloadSizeBits: %u\n", dlDciPtr->PayloadSizeBits);

    printf("Payload: ");
    for(int i = 0; i < DCI_PAYLOAD_BYTE_LEN; ++i) {
        printf("%02x ", dlDciPtr->Payload[i]);
    }
    printf("\n");
}
```

### print_dl_tti_pdcch_pdu_rel15

```bash
void print_dl_tti_pdcch_pdu_rel15(const nfapi_nr_dl_tti_pdcch_pdu_rel15_t* pdu) {
    printf("BWPSize: %u\n", pdu->BWPSize);
    printf("BWPStart: %u\n", pdu->BWPStart);
    printf("SubcarrierSpacing: %u\n", pdu->SubcarrierSpacing);
    printf("CyclicPrefix: %u\n", pdu->CyclicPrefix);
    printf("StartSymbolIndex: %u\n", pdu->StartSymbolIndex);
    printf("DurationSymbols: %u\n", pdu->DurationSymbols);
    
    printf("FreqDomainResource: ");
    for (int i = 0; i < 6; ++i) {
        printf("%02x ", pdu->FreqDomainResource[i]);
    }
    printf("\n");

    printf("CceRegMappingType: %u\n", pdu->CceRegMappingType);
    printf("RegBundleSize: %u\n", pdu->RegBundleSize);
    printf("InterleaverSize: %u\n", pdu->InterleaverSize);
    printf("CoreSetType: %u\n", pdu->CoreSetType);
    printf("ShiftIndex: %u\n", pdu->ShiftIndex);
    printf("precoderGranularity: %u\n", pdu->precoderGranularity);
    printf("numDlDci: %u\n", pdu->numDlDci);

    for (int i = 0; i < pdu->numDlDci; ++i) {
        printf("DL DCI PDU %d:\n", i + 1);
        print_dl_dci_pdu(&pdu->dci_pdu[i]);
    }
}
```

## PDSCH

OAI_OSC_fillPdschPdu

```c
printf("======pdsch=======\n");

printf("pduBitmap: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.pduBitmap);
printf("rnti: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.rnti);
printf("pduIndex: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.pduIndex);
printf("BWPSize: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.BWPSize);
printf("BWPStart: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.BWPStart);
printf("SubcarrierSpacing: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.SubcarrierSpacing);
printf("CyclicPrefix: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.CyclicPrefix);
printf("NrOfCodewords: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.NrOfCodewords);

printf("targetCodeRate[0]: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.targetCodeRate[0]);
printf("qamModOrder[0]: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.qamModOrder[0]);
printf("mcsIndex[0]: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.mcsIndex[0]);
printf("mcsTable[0]: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.mcsTable[0]);
printf("rvIndex[0]: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.rvIndex[0]);
printf("TBSize[0]: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.TBSize[0]);

printf("dataScramblingId: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.dataScramblingId);
printf("nrOfLayers: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.nrOfLayers);
printf("transmissionScheme: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.transmissionScheme);
printf("refPoint: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.refPoint);
printf("dlDmrsSymbPos: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.dlDmrsSymbPos);

printf("dmrsConfigType: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.dmrsConfigType);
printf("dlDmrsScramblingId: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.dlDmrsScramblingId);
printf("SCID: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.SCID);
printf("numDmrsCdmGrpsNoData: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.numDmrsCdmGrpsNoData);
printf("dmrsPorts: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.dmrsPorts);
printf("resourceAlloc: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.resourceAlloc);
printf("rbStart: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.rbStart);
printf("rbSize: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.rbSize);
printf("VRBtoPRBMapping: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.VRBtoPRBMapping);
printf("StartSymbolIndex: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.StartSymbolIndex);
printf("NrOfSymbols: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.NrOfSymbols);
printf("num_prgs: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.precodingAndBeamforming.num_prgs);
printf("prg_size: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.precodingAndBeamforming.prg_size);
printf("dig_bf_interfaces: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.precodingAndBeamforming.dig_bf_interfaces);
printf("pm_idx: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.precodingAndBeamforming.prgs_list[0].pm_idx);
printf("beam_idx: %d\n", dlTtiReqPdu->pdsch_pdu.pdsch_pdu_rel15.precodingAndBeamforming.prgs_list[0].dig_bf_interface_list[0].beam_idx);

```

OAI 

openairinterface5g/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_RA.c

```c
printf("======pdsch=======\n");

printf("num_prgs: %d\n", pdsch_pdu_rel15->precodingAndBeamforming.num_prgs);
printf("prg_size: %d\n", pdsch_pdu_rel15->precodingAndBeamforming.prg_size);
printf("dig_bf_interfaces: %d\n", pdsch_pdu_rel15->precodingAndBeamforming.dig_bf_interfaces);
printf("pm_idx: %d\n", pdsch_pdu_rel15->precodingAndBeamforming.prgs_list[0].pm_idx);
printf("beam_idx: %d\n", pdsch_pdu_rel15->precodingAndBeamforming.prgs_list[0].dig_bf_interface_list[0].beam_idx);

printf("pduBitmap: %d\n", pdsch_pdu_rel15->pduBitmap);
printf("rnti: %d\n", pdsch_pdu_rel15->rnti);
printf("pduIndex: %d\n", pdsch_pdu_rel15->pduIndex);
printf("BWPSize: %d\n", pdsch_pdu_rel15->BWPSize);
printf("BWPStart: %d\n", pdsch_pdu_rel15->BWPStart);
printf("SubcarrierSpacing: %d\n", pdsch_pdu_rel15->SubcarrierSpacing);
printf("CyclicPrefix: %d\n", pdsch_pdu_rel15->CyclicPrefix);
printf("NrOfCodewords: %d\n", pdsch_pdu_rel15->NrOfCodewords);
printf("mcsTable[0]: %d\n", pdsch_pdu_rel15->mcsTable[0]);
printf("rvIndex[0]: %d\n", pdsch_pdu_rel15->rvIndex[0]);
printf("dataScramblingId: %d\n", pdsch_pdu_rel15->dataScramblingId);
printf("nrOfLayers: %d\n", pdsch_pdu_rel15->nrOfLayers);
printf("transmissionScheme: %d\n", pdsch_pdu_rel15->transmissionScheme);
printf("refPoint: %d\n", pdsch_pdu_rel15->refPoint);
printf("dmrsConfigType: %d\n", pdsch_pdu_rel15->dmrsConfigType);
printf("dlDmrsScramblingId: %d\n", pdsch_pdu_rel15->dlDmrsScramblingId);
printf("SCID: %d\n", pdsch_pdu_rel15->SCID);
printf("numDmrsCdmGrpsNoData: %d\n", pdsch_pdu_rel15->numDmrsCdmGrpsNoData);
printf("dmrsPorts: %d\n", pdsch_pdu_rel15->dmrsPorts);
printf("resourceAlloc: %d\n", pdsch_pdu_rel15->resourceAlloc);
printf("rbStart: %d\n", pdsch_pdu_rel15->rbStart);
printf("rbSize: %d\n", pdsch_pdu_rel15->rbSize);
printf("VRBtoPRBMapping: %d\n", pdsch_pdu_rel15->VRBtoPRBMapping);
printf("StartSymbolIndex: %d\n", pdsch_pdu_rel15->StartSymbolIndex);
printf("NrOfSymbols: %d\n", pdsch_pdu_rel15->NrOfSymbols);
printf("dlDmrsSymbPos: %d\n", pdsch_pdu_rel15->dlDmrsSymbPos);

printf("targetCodeRate[0]: %d\n", pdsch_pdu_rel15->targetCodeRate[0]);
printf("qamModOrder[0]: %d\n", pdsch_pdu_rel15->qamModOrder[0]);
printf("mcsIndex[0]: %d\n", pdsch_pdu_rel15->mcsIndex[0]);
printf("TBSize[0]: %d\n", pdsch_pdu_rel15->TBSize[0]);

printf("tbSizeLbrmBytes: %d\n", pdsch_pdu_rel15->maintenance_parms_v3.tbSizeLbrmBytes);
printf("ldpcBaseGraph: %d\n", pdsch_pdu_rel15->maintenance_parms_v3.ldpcBaseGraph);

```