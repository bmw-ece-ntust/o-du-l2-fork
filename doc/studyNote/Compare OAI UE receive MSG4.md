# Compare OAI UE receive MSG4

Start Date: 2024/10/09
Summary: Investigating discrepancies in transport block sizes received by the UE during MSG4 processing and comparing results between OAI and OSC implementations.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Compare
Finish Date: 2024/10/12
SUM: 🗓️ Days Spent to Complete: 3

### When DU send compare table → [Compare OSC DU send MSG4](Compare%20OSC%20DU%20send%20MSG4%201211009831438147a50bd917d4b0a91d.md)

### When PNF send compare table → [Compare OAI PNF recieve MSG4](Compare%20OAI%20PNF%20recieve%20MSG4%2012110098314381c180f1e4809fbc4292.md)

So, now I need to trace why UE recieve TBS is wrong

| OSC DU send TBS | ✅ (116 Byte) |
| --- | --- |
| OAI Layer1 recv TBS | ✅ (116 Byte) |
| OAI UE recv TBS | ❌ (101 Byte) |

## When UE recieve MSG4 DLSCH

```c
    int ret_pdsch = nr_ue_pdsch_procedures(ue, proc, dlsch, llr, rxdataF, G);
```

→ The UE then processes the received data using the function **`nr_ue_dlsch_procedures(ue, proc, dlsch, llr, G);`**

## DLSCH

|  | OAI value | OSC value |
| --- | --- | --- |
| BWP Size | 48 | 48 |
| BWP Start | 27 | 27 |
| Subcarrier Spacing | 1 | 1 |
| Resource Allocation | 1 | 1 |
| Number of RBs | 42 | 28 |
| Start RB | 0 | 0 |
| Number of Symbols | 13 | 5 ✅ |
| Start Symbol | 1 | 1 |
| RB Offset | 27 | 27 |
| DL DMRS Symbol Position | 2180 | 4  ✅ |
| DMRS Config Type | 0 | 0 |
| PRB Bundling Size Indicator | 0 | 0 |
| Rate Matching Indicator | 0 | 0 |
| ZP CSI-RS Trigger | 0 | 0 |
| MCS | 0 | 0 |
| New Data Indicator | 1 | 1 |
| Redundancy Version | 0 | 0 |
| Target Code Rate | 1200 | 1200 |
| QAM Modulation Order | 2 | 2 |
| TBS | 1192 | 320 → 808 |
| TB2 MCS | 0 | 0 |
| TB2 New Data Indicator | 0 | 0 |
| TB2 Redundancy Version | 0 | 0 |
| HARQ Process Number | 0 | 0 |
| VRB to PRB Mapping | 0 | 0 |
| DAI | 0 | 0 |
| Scaling Factor S | 1.000000 | 1.000000 |
| Accumulated Delta PUCCH | -1 | -1 |
| PUCCH Resource ID | 0 | 0 |
| PDSCH to HARQ Feedback Time Indicator | 0 | 0 |
| Number of DMRS CDM Groups | 2 | 2 |
| DMRS Ports | 1 | 1 |
| Number of Front Load Symbols | 0 | 0 |
| TCI State | 0 | 0 |
| CBG Transmission Indicator | 0 | 0 |
| Code Block Group Flush Indicator | 0 | 0 |
| PTRS Port Index | 0 | 0 |
| PTRS Time Density | 0 | 0 |
| PTRS Frequency Density | 0 | 0 |
| PTRS Resource Element Offset | 0 | 0 |
| EPRE Ratio of PDSCH to PTRS | 0 | 0 |
| MCS Table | 0 | 0 |
| TBSLBRM | 92200 | 92200 |
| NSCID | 0 | 0 |
| DL DMRS Scrambling ID | 0 | 1 |
| DL Data Scrambling ID | 0 | 1 |
| PDU Bitmap | 0 | 0 |
| K1 Feedback | 6 | 3 |
| LDPC Base Graph | 2 | 2 |
| Nl | 1 | 1 |
| Active | 1 | 1 |

```c
    LOG_I(PHY, "DLSCH Configuration:\n");
    LOG_I(PHY, "  BWP Size: %d\n", dlsch[0].dlsch_config.BWPSize);
    LOG_I(PHY, "  BWP Start: %d\n", dlsch[0].dlsch_config.BWPStart);
    LOG_I(PHY, "  Subcarrier Spacing: %d\n", dlsch[0].dlsch_config.SubcarrierSpacing);
    LOG_I(PHY, "  Resource Allocation: %d\n", dlsch[0].dlsch_config.resource_alloc);
    LOG_I(PHY, "  Number of RBs: %d\n", dlsch[0].dlsch_config.number_rbs);
    LOG_I(PHY, "  Start RB: %d\n", dlsch[0].dlsch_config.start_rb);
    LOG_I(PHY, "  Number of Symbols: %d\n", dlsch[0].dlsch_config.number_symbols);
    LOG_I(PHY, "  Start Symbol: %d\n", dlsch[0].dlsch_config.start_symbol);
    LOG_I(PHY, "  RB Offset: %d\n", dlsch[0].dlsch_config.rb_offset);
    LOG_I(PHY, "  DL DMRS Symbol Position: %d\n", dlsch[0].dlsch_config.dlDmrsSymbPos);
    LOG_I(PHY, "  DMRS Config Type: %d\n", dlsch[0].dlsch_config.dmrsConfigType);
    LOG_I(PHY, "  PRB Bundling Size Indicator: %d\n", dlsch[0].dlsch_config.prb_bundling_size_ind);
    LOG_I(PHY, "  Rate Matching Indicator: %d\n", dlsch[0].dlsch_config.rate_matching_ind);
    LOG_I(PHY, "  ZP CSI-RS Trigger: %d\n", dlsch[0].dlsch_config.zp_csi_rs_trigger);
    LOG_I(PHY, "  MCS: %d\n", dlsch[0].dlsch_config.mcs);
    LOG_I(PHY, "  New Data Indicator: %d\n", dlsch[0].dlsch_config.new_data_indicator);
    LOG_I(PHY, "  Redundancy Version: %d\n", dlsch[0].dlsch_config.rv);
    LOG_I(PHY, "  Target Code Rate: %d\n", dlsch[0].dlsch_config.targetCodeRate);
    LOG_I(PHY, "  QAM Modulation Order: %d\n", dlsch[0].dlsch_config.qamModOrder);
    LOG_I(PHY, "  TBS: %d\n", dlsch[0].dlsch_config.TBS);
    LOG_I(PHY, "  TB2 MCS: %d\n", dlsch[0].dlsch_config.tb2_mcs);
    LOG_I(PHY, "  TB2 New Data Indicator: %d\n", dlsch[0].dlsch_config.tb2_new_data_indicator);
    LOG_I(PHY, "  TB2 Redundancy Version: %d\n", dlsch[0].dlsch_config.tb2_rv);
    LOG_I(PHY, "  HARQ Process Number: %d\n", dlsch[0].dlsch_config.harq_process_nbr);
    LOG_I(PHY, "  VRB to PRB Mapping: %d\n", dlsch[0].dlsch_config.vrb_to_prb_mapping);
    LOG_I(PHY, "  DAI: %d\n", dlsch[0].dlsch_config.dai);
    LOG_I(PHY, "  Scaling Factor S: %f\n", dlsch[0].dlsch_config.scaling_factor_S);
    LOG_I(PHY, "  Accumulated Delta PUCCH: %d\n", dlsch[0].dlsch_config.accumulated_delta_PUCCH);
    LOG_I(PHY, "  PUCCH Resource ID: %d\n", dlsch[0].dlsch_config.pucch_resource_id);
    LOG_I(PHY, "  PDSCH to HARQ Feedback Time Indicator: %d\n", dlsch[0].dlsch_config.pdsch_to_harq_feedback_time_ind);
    LOG_I(PHY, "  Number of DMRS CDM Groups: %d\n", dlsch[0].dlsch_config.n_dmrs_cdm_groups);
    LOG_I(PHY, "  DMRS Ports: %d\n", dlsch[0].dlsch_config.dmrs_ports);
    LOG_I(PHY, "  Number of Front Load Symbols: %d\n", dlsch[0].dlsch_config.n_front_load_symb);
    LOG_I(PHY, "  TCI State: %d\n", dlsch[0].dlsch_config.tci_state);
    LOG_I(PHY, "  CBG Transmission Indicator: %d\n", dlsch[0].dlsch_config.cbgti);
    LOG_I(PHY, "  Code Block Group Flush Indicator: %d\n", dlsch[0].dlsch_config.codeBlockGroupFlushIndicator);
    LOG_I(PHY, "  PTRS Port Index: %d\n", dlsch[0].dlsch_config.PTRSPortIndex);
    LOG_I(PHY, "  PTRS Time Density: %d\n", dlsch[0].dlsch_config.PTRSTimeDensity);
    LOG_I(PHY, "  PTRS Frequency Density: %d\n", dlsch[0].dlsch_config.PTRSFreqDensity);
    LOG_I(PHY, "  PTRS Resource Element Offset: %d\n", dlsch[0].dlsch_config.PTRSReOffset);
    LOG_I(PHY, "  EPRE Ratio of PDSCH to PTRS: %d\n", dlsch[0].dlsch_config.nEpreRatioOfPDSCHToPTRS);
    LOG_I(PHY, "  MCS Table: %d\n", dlsch[0].dlsch_config.mcs_table);
    LOG_I(PHY, "  TBSLBRM: %d\n", dlsch[0].dlsch_config.tbslbrm);
    LOG_I(PHY, "  NSCID: %d\n", dlsch[0].dlsch_config.nscid);
    LOG_I(PHY, "  DL DMRS Scrambling ID: %d\n", dlsch[0].dlsch_config.dlDmrsScramblingId);
    LOG_I(PHY, "  DL Data Scrambling ID: %d\n", dlsch[0].dlsch_config.dlDataScramblingId);
    LOG_I(PHY, "  PDU Bitmap: %d\n", dlsch[0].dlsch_config.pduBitmap);
    LOG_I(PHY, "  K1 Feedback: %d\n", dlsch[0].dlsch_config.k1_feedback);
    LOG_I(PHY, "  LDPC Base Graph: %d\n", dlsch[0].dlsch_config.ldpcBaseGraph);
    LOG_I(PHY, "  Nl: %d\n", dlsch[0].Nl);
    LOG_I(PHY, "  Active: %d\n", dlsch[0].active);

```

## Revise

- MSG2 (RAR)'s `Number of Symbols` is now hard-coded to select the third option from the SIB1 list, instead of auto-selecting. (This is because OSC can't automatically detect the need to select the third option; the current conditions seem insufficient for proper detection.)
- SIB1's SLIV (`start Symbol` and `Number of Symbols`) has been reverted to match the OAI settings. (Previously, Irevised the first group to send MSG2 (RAR), but it's currently hard-coded to select the third option.)

## Trace UE **compute**TBS

```c
// Transport block size determination according to 6.1.4.2 of TS 38.214
// returns the TBS in bits
uint32_t nr_compute_tbs(uint16_t Qm,
                        uint16_t R,
                        uint16_t nb_rb,
                        uint16_t nb_symb_sch,
                        uint16_t nb_dmrs_prb,
                        uint16_t nb_rb_oh,
                        uint8_t tb_scaling,
                        uint8_t Nl)
{
```

```c
    LOG_I(MAC,"nb_re_dmrs %d\n", nb_re_dmrs);
    LOG_I(MAC, "qamModOrder: %d, R: %d, number_rbs: %d, number_symbols: %d, nb_re_dmrs: %d, nb_rb_oh: %d\n",
        dlsch_pdu->qamModOrder, R, dlsch_pdu->number_rbs, dlsch_pdu->number_symbols, nb_re_dmrs, nb_rb_oh);
    dlsch_pdu->TBS = nr_compute_tbs(dlsch_pdu->qamModOrder,
                                    R,
                                    dlsch_pdu->number_rbs,
                                    dlsch_pdu->number_symbols,
                                    nb_re_dmrs * get_num_dmrs(dlsch_pdu->dlDmrsSymbPos),
                                    nb_rb_oh,
                                    0,
                                    1);
    LOG_I(MAC, "TBS %d\n", dlsch_pdu->TBS);
```

I also used unit tests to ensure the UE will use the following parameters to compute TBS. When I varied the RB size while fixing other parameters, I got 28→808 and 42→1192. Therefore, I need to verify which OSC RB size and TBS are correct.

| Parameter | use OSC Value | use OAI Value |
| --- | --- | --- |
| qamModOrder | 2 | 2 |
| R | 1200 | 1200 |
| number_rbs | 28 | 42 |
| number_symbols | 13 | 13 |
| nb_re_dmrs | 12 | 12 |
| **dlsch_pdu->dlDmrsSymbPos** | 2180 | 2180 |
| **get_num_dmrs** | 3 | 3 |
| nb_rb_oh | 0 | 0 |
| TBS | 808 | **1192** |

```c
    for (int rb = 28; rb <= 40; rb++) {
      uint32_t test_tbs = nr_compute_tbs(dlsch_pdu->qamModOrder,
                         R,
                         rb,
                         dlsch_pdu->number_symbols,
                         nb_re_dmrs * get_num_dmrs(dlsch_pdu->dlDmrsSymbPos),
                         nb_rb_oh,
                         0,
                         1);
      LOG_I(MAC, "TBS %d, test_tbs %d for RB %d\n", dlsch_pdu->TBS, test_tbs, rb);
    }
```

So, I check in OSC DU how to CalcNumPrb:

```c
   printf("test numPrb: %d\n", schCalcNumPrb(149, mcs, pdschNumSymbols));
   printf("test numPrb: %d\n", schCalcNumPrb(113, mcs, pdschNumSymbols));
   printf("test numPrb: %d\n", schCalcNumPrb(103, mcs, pdschNumSymbols));
```

| RB Size | TBS (bits) |
| --- | --- |
| 28 | 808 |
| 29 | 808 |
| 30 | 848 |
| 31 | 888 |
| 32 | 928 |
| 33 | 928 |
| 34 | 984 |
| 35 | 984 |
| 36 | 1032 |
| 37 | 1064 |
| 38 | 1064 |
| 39 | 1128 |
| 40 | 1128 |
| 42 | 1192 |

| RB Size | TBS (Byte) | TBS (bits) |
| --- | --- | --- |
| 36 | 149 | 1192 |
| 28 | 116 | 928 |
| 27 | 113 | 904 |
| 25 | 103 | 824 |

Based on this analysis, I can conclude that OSC and OAI use different methods to compute TBS, which will result in mismatched encoding and decoding of TBS.

[MSG4 TBS](MSG4%20TBS%2012110098314381548571e517d77ee088.md) 

[Double Check TBS](Double%20Check%20TBS%20121100983143811d9175f1c7652e31e0.md)