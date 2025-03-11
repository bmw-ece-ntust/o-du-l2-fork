# SSB (MIB)

Tags: DL_TTI, MIB, SSB

```c
typedef struct {
  /// Physical Cell ID Value 0~>1007
  uint16_t PhysCellId;
  ///PSS EPRE to SSS EPRE in a SS/PBCH block 0 = 0dB 1 = 3dB
  uint8_t  BetaPss;
  ///SS/PBCH block index within a SSB burst set. Required for PBCH DMRS scrambling. Value: 0->63 (Lmax)
  uint8_t  SsbBlockIndex;
  /// ssbSubcarrierOffset or 𝑘𝑆𝑆𝐵 (TS38.211, section 7.4.3.1) Value: 0->31
  uint8_t  SsbSubcarrierOffset;
  ///Offset of lowest subcarrier of lowest resource block used for SS/PBCH block. Value: 0->2199
  uint16_t ssbOffsetPointA;
  /// A value indicating how the BCH payload is generated. This should match the PARAM/CONFIG TLVs. Value: 0: MAC generates the full PBCH payload, see Table 3-41, where bchPayload has 31 bits 1: PHY generates the timing PBCH bits, see Table 3-41, where the bchPayload has 24 bits 2: PHY generates the full PBCH payload
  uint8_t  bchPayloadFlag;
  uint32_t bchPayload;
  /// A value indicating the channel quality between the gNB and nrUE. Value: 0->255 dBM
  uint8_t  ssbRsrp;
  nfapi_nr_tx_precoding_and_beamforming_t precoding_and_beamforming;
} nfapi_nr_dl_tti_ssb_pdu_rel15_t;
```

| Variable | OAI Value | OSC Value |
| --- | --- | --- |
| value->PhysCellId | 0 | 1 |
| value->BetaPss | 0 | 0 |
| value->SsbBlockIndex | 0 | 0 |
| value->SsbSubcarrierOffset | 0 | 0 |
| value->ssbOffsetPointA | 86 | 24 |
| value->bchPayloadFlag | 1 | 1 |
| byte3 | 6 | ERROR |
| byte2 | 6 | ERROR |
| byte1 | 1 | ERROR |
| byte0 | 0 | ERROR |
| value->bchPayload | **394753** | ERROR |
| value->precoding_and_beamforming.num_prgs | 1 | 0 |
| value->precoding_and_beamforming.prg_size | 275 | 0 |
| value->precoding_and_beamforming.dig_bf_interfaces | 1 | 0 |
| value->precoding_and_beamforming.prgs_list[0].pm_idx | 0 | 0 |
| value->precoding_and_beamforming.prgs_list[0].dig_bf_interface_list[0].beam_idx | 0 | 0 |
|  |  |  |

```c
/* NR_MIB */
typedef struct NR_MIB {
	BIT_STRING_t	 systemFrameNumber;
	long	 subCarrierSpacingCommon;
	long	 ssb_SubcarrierOffset;
	long	 dmrs_TypeA_Position;
	NR_PDCCH_ConfigSIB1_t	 pdcch_ConfigSIB1;
	long	 cellBarred;
	long	 intraFreqReselection;
	BIT_STRING_t	 spare;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NR_MIB_t;
```

|  | OAI | OSC |
| --- | --- | --- |
| **systemFrameNumber** | sfn (6bits) | sfn (6bits) → wrong order |
| **subCarrierSpacingCommon (SCS)** | 1 | 1 |
| ssb-SubcarrierOffset | 0 | 0 |
| dmrs-TypeA-Position | 0 (pos2) | 0 |
| pdcch-ConfigSIB1- ControlResourceSetZero (CORESET) Zero | 12 | 0 |
| pdcch-ConfigSIB1- searchSpaceZero | 0 | 0 |
| **cellBarred** | 1 (notBarred) | 1 |
| intraFreqReselection | 1 (notAllowed) | 1 |

# Debug Log

```c
  LOG_I(PHY, "value->PhysCellId: %d\n", value->PhysCellId);
  LOG_I(PHY, "value->BetaPss: %d\n", value->BetaPss);
  LOG_I(PHY, "value->SsbBlockIndex: %d\n", value->SsbBlockIndex);
  LOG_I(PHY, "value->SsbSubcarrierOffset: %d\n", value->SsbSubcarrierOffset);
  LOG_I(PHY, "value->ssbOffsetPointA: %d\n", value->ssbOffsetPointA);
  LOG_I(PHY, "value->bchPayloadFlag: %d\n", value->bchPayloadFlag);
  LOG_I(PHY, "byte3: %lx\n", byte3);
  LOG_I(PHY, "byte2: %lx\n", byte2);
  LOG_I(PHY, "byte1: %lx\n", byte1);
  LOG_I(PHY, "byte0: %lx\n", byte0);
  LOG_I(PHY, "value->bchPayload: %lx\n", value->bchPayload);
  LOG_I(PHY, "value->precoding_and_beamforming.num_prgs: %d\n", value->precoding_and_beamforming.num_prgs);
  LOG_I(PHY, "value->precoding_and_beamforming.prg_size: %d\n", value->precoding_and_beamforming.prg_size);
  LOG_I(PHY, "value->precoding_and_beamforming.dig_bf_interfaces: %d\n", value->precoding_and_beamforming.dig_bf_interfaces);
  for (int i = 0; i < value->precoding_and_beamforming.num_prgs; ++i) {
      LOG_I(PHY, "value->precoding_and_beamforming.prgs_list[%d].pm_idx: %d\n", i, value->precoding_and_beamforming.prgs_list[i].pm_idx);
      for (int k = 0; k < value->precoding_and_beamforming.dig_bf_interfaces; ++k) {
          LOG_I(PHY, "value->precoding_and_beamforming.prgs_list[%d].dig_bf_interface_list[%d].beam_idx: %d\n", i, k, value->precoding_and_beamforming.prgs_list[i].dig_bf_interface_list[k].beam_idx);
      }
  }
```