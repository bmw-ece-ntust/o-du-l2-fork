# Write a function dump pack/unpack value

Start Date: 2024/04/12
Summary: Develop a function to dump and unpack values while analyzing differences in log outputs between PACK and UNPACK states.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Robert Task

List the differences in the printed log output from the dump function when comparing PACK and UNPACK values. By default, in normal execution, the value will be such that PACK value is 0.

|  | PACK | UNPACK | note |
| --- | --- | --- | --- |
| targetCodeRate[1]:  | 0 | 23579 |  |
| qamModOrder[1]: | 0 | 67 |  |
| mcsIndex[1]: | 0 | 112 |  |
| mcsTable[1]: | 0 | 40 |  |
| rvIndex[1]: | 0 | 160 |  |
| TBSize[1]: | 0 | 1365431162 |  |
| PTRSPortIndex: | 0 | 160 | pduBitmap bit0 =0 |
| PTRSTimeDensity: | 0 | 105 | pduBitmap bit0 =0 |
| PTRSFreqDensity: | 0 | 115 | pduBitmap bit0 =0 |
|  PTRSReOffset: | 0 | 81 | pduBitmap bit0 =0 |
| nEpreRatioOfPDSCHToPTRS: | 0 | 77 | pduBitmap bit0 =0 |
|  |  |  |  |

![Untitled](Untitled%2026.png)

![Red side is PACK Green side is UNPACK, only occur problem in `pm_idx` and `beam_idx` when iperf3 UL](Untitled%2027.png)

Red side is PACK Green side is UNPACK, only occur problem in `pm_idx` and `beam_idx` when iperf3 UL

### Full compare

```
avril 12 10:54:33 1712912073.295823 [PHY]   nfapi_nr_dl_tti_pdsch_pdu_rel15_t:
avril 12 10:54:33 [0m1712912073.295828 [PHY]     pduBitmap: 0
avril 12 10:54:33 [0m1712912073.295830 [PHY]     rnti: 59351
avril 12 10:54:33 [0m1712912073.295831 [PHY]     pduIndex: 0
avril 12 10:54:33 [0m1712912073.295832 [PHY]     BWPSize: 106
avril 12 10:54:33 [0m1712912073.295832 [PHY]     BWPStart: 0
avril 12 10:54:33 [0m1712912073.295833 [PHY]     SubcarrierSpacing: 1
avril 12 10:54:33 [0m1712912073.295834 [PHY]     CyclicPrefix: 0
avril 12 10:54:33 [0m1712912073.295835 [PHY]     NrOfCodewords: 1
avril 12 10:54:33 [0m1712912073.295836 [PHY]     targetCodeRate[0]: 3400
avril 12 10:54:33 [0m1712912073.295836 [PHY]     targetCodeRate[1]: 0
avril 12 10:54:33 [0m1712912073.295837 [PHY]     qamModOrder[0]: 4
avril 12 10:54:33 [0m1712912073.295838 [PHY]     qamModOrder[1]: 0
avril 12 10:54:33 [0m1712912073.295839 [PHY]     mcsIndex[0]: 10
avril 12 10:54:33 [0m1712912073.295840 [PHY]     mcsIndex[1]: 0
avril 12 10:54:33 [0m1712912073.295840 [PHY]     mcsTable[0]: 0
avril 12 10:54:33 [0m1712912073.295841 [PHY]     mcsTable[1]: 0
avril 12 10:54:33 [0m1712912073.295842 [PHY]     rvIndex[0]: 0
avril 12 10:54:33 [0m1712912073.295843 [PHY]     rvIndex[1]: 0
avril 12 10:54:33 [0m1712912073.295844 [PHY]     TBSize[0]: 944
avril 12 10:54:33 [0m1712912073.295845 [PHY]     TBSize[1]: 0
avril 12 10:54:33 [0m1712912073.295845 [PHY]     dataScramblingId: 0
avril 12 10:54:33 [0m1712912073.295846 [PHY]     nrOfLayers: 1
avril 12 10:54:33 [0m1712912073.295847 [PHY]     transmissionScheme: 0
avril 12 10:54:33 [0m1712912073.295848 [PHY]     refPoint: 0
avril 12 10:54:33 [0m1712912073.295848 [PHY]     dlDmrsSymbPos: 4
avril 12 10:54:33 [0m1712912073.295849 [PHY]     dmrsConfigType: 0
avril 12 10:54:33 [0m1712912073.295850 [PHY]     dlDmrsScramblingId: 0
avril 12 10:54:33 [0m1712912073.295851 [PHY]     SCID: 0
avril 12 10:54:33 [0m1712912073.295852 [PHY]     numDmrsCdmGrpsNoData: 1
avril 12 10:54:33 [0m1712912073.295853 [PHY]     dmrsPorts: 1
avril 12 10:54:33 [0m1712912073.295853 [PHY]     resourceAlloc: 1
avril 12 10:54:33 [0m1712912073.295854 [PHY]     rbStart: 0
avril 12 10:54:33 [0m1712912073.295855 [PHY]     rbSize: 106
avril 12 10:54:33 [0m1712912073.295856 [PHY]     VRBtoPRBMapping: 1
avril 12 10:54:33 [0m1712912073.295857 [PHY]     StartSymbolIndex: 1
avril 12 10:54:33 [0m1712912073.295857 [PHY]     NrOfSymbols: 5
avril 12 10:54:33 [0m1712912073.295858 [PHY]     PTRSPortIndex: 0
avril 12 10:54:33 [0m1712912073.295859 [PHY]     PTRSTimeDensity: 0
avril 12 10:54:33 [0m1712912073.295860 [PHY]     PTRSFreqDensity: 0
avril 12 10:54:33 [0m1712912073.295861 [PHY]     PTRSReOffset: 0
avril 12 10:54:33 [0m1712912073.295862 [PHY]     nEpreRatioOfPDSCHToPTRS: 0
avril 12 10:54:33 [0m1712912073.295862 [PHY]   nfapi_nr_tx_precoding_and_beamforming_t:
avril 12 10:54:33 [0m1712912073.295863 [PHY]     num_prgs: 0
avril 12 10:54:33 [0m1712912073.295864 [PHY]     prg_size: 106
avril 12 10:54:33 [0m1712912073.295865 [PHY]     dig_bf_interfaces: 0
avril 12 10:54:33 [0m1712912073.295866 [PHY]   nfapi_nr_tx_precoding_aintnd_beamforming_number_of_prgs_t:
avril 12 10:54:33 [0m1712912073.295866 [PHY]     pm_idx[0]: 0
avril 12 10:54:33 [0m1712912073.295867 [PHY]     pm_idx[1]: 1
avril 12 10:54:33 [0m1712912073.295868 [PHY]   nfapi_nr_dig_bf_interface_t:
avril 12 10:54:33 [0m1712912073.295869 [PHY]     beam_idx[0][0]: 0
avril 12 10:54:33 [0m1712912073.295870 [PHY]     beam_idx[0][1]: 1
avril 12 10:54:33 [0m1712912073.295870 [PHY]     beam_idx[1][0]: 0
avril 12 10:54:33 [0m1712912073.295871 [PHY]     beam_idx[1][1]: 53352
avril 12 10:54:33 [0m1712912073.295872 [PHY]   nfapi_v3_pdsch_maintenance_parameters_t:
avril 12 10:54:33 [0m1712912073.295874 [PHY]     ldpcBaseGraph: 1
avril 12 10:54:33 [0m1712912073.295874 [PHY]     tbSizeLbrmBytes: 184424
```

```
avril 12 10:54:33 1712912073.295896 [PHY]   nfapi_nr_dl_tti_pdsch_pdu_rel15_t:
avril 12 10:54:33 [0m1712912073.295900 [PHY]     pduBitmap: 0
avril 12 10:54:33 [0m1712912073.295901 [PHY]     rnti: 59351
avril 12 10:54:33 [0m1712912073.295902 [PHY]     pduIndex: 0
avril 12 10:54:33 [0m1712912073.295903 [PHY]     BWPSize: 106
avril 12 10:54:33 [0m1712912073.295904 [PHY]     BWPStart: 0
avril 12 10:54:33 [0m1712912073.295905 [PHY]     SubcarrierSpacing: 1
avril 12 10:54:33 [0m1712912073.295906 [PHY]     CyclicPrefix: 0
avril 12 10:54:33 [0m1712912073.295906 [PHY]     NrOfCodewords: 1
avril 12 10:54:33 [0m1712912073.295907 [PHY]     targetCodeRate[0]: 3400
avril 12 10:54:33 [0m1712912073.295908 [PHY]     targetCodeRate[1]: 22434
avril 12 10:54:33 [0m1712912073.295909 [PHY]     qamModOrder[0]: 4
avril 12 10:54:33 [0m1712912073.295910 [PHY]     qamModOrder[1]: 203
avril 12 10:54:33 [0m1712912073.295911 [PHY]     mcsIndex[0]: 10
avril 12 10:54:33 [0m1712912073.295912 [PHY]     mcsIndex[1]: 141
avril 12 10:54:33 [0m1712912073.295912 [PHY]     mcsTable[0]: 0
avril 12 10:54:33 [0m1712912073.295913 [PHY]     mcsTable[1]: 118
avril 12 10:54:33 [0m1712912073.295914 [PHY]     rvIndex[0]: 0
avril 12 10:54:33 [0m1712912073.295915 [PHY]     rvIndex[1]: 122
avril 12 10:54:33 [0m1712912073.295916 [PHY]     TBSize[0]: 944
avril 12 10:54:33 [0m1712912073.295917 [PHY]     TBSize[1]: 1025841167
avril 12 10:54:33 [0m1712912073.295918 [PHY]     dataScramblingId: 0
avril 12 10:54:33 [0m1712912073.295919 [PHY]     nrOfLayers: 1
avril 12 10:54:33 [0m1712912073.295919 [PHY]     transmissionScheme: 0
avril 12 10:54:33 [0m1712912073.295920 [PHY]     refPoint: 0
avril 12 10:54:33 [0m1712912073.295921 [PHY]     dlDmrsSymbPos: 4
avril 12 10:54:33 [0m1712912073.295922 [PHY]     dmrsConfigType: 0
avril 12 10:54:33 [0m1712912073.295923 [PHY]     dlDmrsScramblingId: 0
avril 12 10:54:33 [0m1712912073.295923 [PHY]     SCID: 0
avril 12 10:54:33 [0m1712912073.295924 [PHY]     numDmrsCdmGrpsNoData: 1
avril 12 10:54:33 [0m1712912073.295925 [PHY]     dmrsPorts: 1
avril 12 10:54:33 [0m1712912073.295926 [PHY]     resourceAlloc: 1
avril 12 10:54:33 [0m1712912073.295927 [PHY]     rbStart: 0
avril 12 10:54:33 [0m1712912073.295928 [PHY]     rbSize: 106
avril 12 10:54:33 [0m1712912073.295928 [PHY]     VRBtoPRBMapping: 1
avril 12 10:54:33 [0m1712912073.295929 [PHY]     StartSymbolIndex: 1
avril 12 10:54:33 [0m1712912073.295930 [PHY]     NrOfSymbols: 5
avril 12 10:54:33 [0m1712912073.295931 [PHY]     PTRSPortIndex: 225
avril 12 10:54:33 [0m1712912073.295932 [PHY]     PTRSTimeDensity: 63
avril 12 10:54:33 [0m1712912073.295933 [PHY]     PTRSFreqDensity: 214
avril 12 10:54:33 [0m1712912073.295933 [PHY]     PTRSReOffset: 60
avril 12 10:54:33 [0m1712912073.295934 [PHY]     nEpreRatioOfPDSCHToPTRS: 222
avril 12 10:54:33 [0m1712912073.295935 [PHY]   nfapi_nr_tx_precoding_and_beamforming_t:
avril 12 10:54:33 [0m1712912073.295936 [PHY]     num_prgs: 0
avril 12 10:54:33 [0m1712912073.295937 [PHY]     prg_size: 106
avril 12 10:54:33 [0m1712912073.295938 [PHY]     dig_bf_interfaces: 0
avril 12 10:54:33 [0m1712912073.295938 [PHY]   nfapi_nr_tx_precoding_aintnd_beamforming_number_of_prgs_t:
avril 12 10:54:33 [0m1712912073.295939 [PHY]     pm_idx[0]: 5044
avril 12 10:54:33 [0m1712912073.295940 [PHY]     pm_idx[1]: 14081
avril 12 10:54:33 [0m1712912073.295941 [PHY]   nfapi_nr_dig_bf_interface_t:
avril 12 10:54:33 [0m1712912073.295942 [PHY]     beam_idx[0][0]: 25183
avril 12 10:54:33 [0m1712912073.295942 [PHY]     beam_idx[0][1]: 14081
avril 12 10:54:33 [0m1712912073.295943 [PHY]     beam_idx[1][0]: 11847
avril 12 10:54:33 [0m1712912073.295944 [PHY]     beam_idx[1][1]: 53352
avril 12 10:54:33 [0m1712912073.295945 [PHY]   nfapi_v3_pdsch_maintenance_parameters_t:
avril 12 10:54:33 [0m1712912073.295946 [PHY]     ldpcBaseGraph: 1
avril 12 10:54:33 [0m1712912073.295947 [PHY]     tbSizeLbrmBytes: 184424
```

### Soruce code

```c
static void dump_nfapi_nr_dl_tti_pdcch_pdu_rel15_value(nfapi_nr_dl_tti_pdsch_pdu_rel15_t *value){
  LOG_I(PHY, "nfapi_nr_dl_tti_pdsch_pdu_rel15_t:\n");
  LOG_I(PHY, "  pduBitmap: %d\n", value->pduBitmap);
  LOG_I(PHY, "  rnti: %d\n", value->rnti);
  LOG_I(PHY, "  pduIndex: %d\n", value->pduIndex);
  LOG_I(PHY, "  BWPSize: %d\n", value->BWPSize);
  LOG_I(PHY, "  BWPStart: %d\n", value->BWPStart);
  LOG_I(PHY, "  SubcarrierSpacing: %d\n", value->SubcarrierSpacing);
  LOG_I(PHY, "  CyclicPrefix: %d\n", value->CyclicPrefix);
  LOG_I(PHY, "  NrOfCodewords: %d\n", value->NrOfCodewords);
  LOG_I(PHY, "  targetCodeRate[0]: %d\n", value->targetCodeRate[0]);
  LOG_I(PHY, "  targetCodeRate[1]: %d\n", value->targetCodeRate[1]);
  LOG_I(PHY, "  qamModOrder[0]: %d\n", value->qamModOrder[0]);
  LOG_I(PHY, "  qamModOrder[1]: %d\n", value->qamModOrder[1]);
  LOG_I(PHY, "  mcsIndex[0]: %d\n", value->mcsIndex[0]);
  LOG_I(PHY, "  mcsIndex[1]: %d\n", value->mcsIndex[1]);
  LOG_I(PHY, "  mcsTable[0]: %d\n", value->mcsTable[0]);
  LOG_I(PHY, "  mcsTable[1]: %d\n", value->mcsTable[1]);
  LOG_I(PHY, "  rvIndex[0]: %d\n", value->rvIndex[0]);
  LOG_I(PHY, "  rvIndex[1]: %d\n", value->rvIndex[1]);
  LOG_I(PHY, "  TBSize[0]: %d\n", value->TBSize[0]);
  LOG_I(PHY, "  TBSize[1]: %d\n", value->TBSize[1]);
  LOG_I(PHY, "  dataScramblingId: %d\n", value->dataScramblingId);
  LOG_I(PHY, "  nrOfLayers: %d\n", value->nrOfLayers);
  LOG_I(PHY, "  transmissionScheme: %d\n", value->transmissionScheme);
  LOG_I(PHY, "  refPoint: %d\n", value->refPoint);
  LOG_I(PHY, "  dlDmrsSymbPos: %d\n", value->dlDmrsSymbPos);
  LOG_I(PHY, "  dmrsConfigType: %d\n", value->dmrsConfigType);
  LOG_I(PHY, "  dlDmrsScramblingId: %d\n", value->dlDmrsScramblingId);
  LOG_I(PHY, "  SCID: %d\n", value->SCID);
  LOG_I(PHY, "  numDmrsCdmGrpsNoData: %d\n", value->numDmrsCdmGrpsNoData);
  LOG_I(PHY, "  dmrsPorts: %d\n", value->dmrsPorts);
  LOG_I(PHY, "  resourceAlloc: %d\n", value->resourceAlloc);
  LOG_I(PHY, "  rbStart: %d\n", value->rbStart);
  LOG_I(PHY, "  rbSize: %d\n", value->rbSize);
  LOG_I(PHY, "  VRBtoPRBMapping: %d\n", value->VRBtoPRBMapping);
  LOG_I(PHY, "  StartSymbolIndex: %d\n", value->StartSymbolIndex);
  LOG_I(PHY, "  NrOfSymbols: %d\n", value->NrOfSymbols);
  LOG_I(PHY, "  PTRSPortIndex: %d\n", value->PTRSPortIndex);
  LOG_I(PHY, "  PTRSTimeDensity: %d\n", value->PTRSTimeDensity);
  LOG_I(PHY, "  PTRSFreqDensity: %d\n", value->PTRSFreqDensity);
  LOG_I(PHY, "  PTRSReOffset: %d\n", value->PTRSReOffset);
  LOG_I(PHY, "  nEpreRatioOfPDSCHToPTRS: %d\n", value->nEpreRatioOfPDSCHToPTRS);

  LOG_I(PHY, "nfapi_nr_tx_precoding_and_beamforming_t:\n");
  LOG_I(PHY, "  num_prgs: %d\n", value->precodingAndBeamforming.num_prgs);
  LOG_I(PHY, "  prg_size: %d\n", value->precodingAndBeamforming.prg_size);
  LOG_I(PHY, "  dig_bf_interfaces: %d\n", value->precodingAndBeamforming.dig_bf_interfaces);

  // LOG_I(PHY, "nfapi_nr_tx_precoding_and_beamforming_number_of_prgs_t:\n");
  // LOG_I(PHY, "  pm_idx: %d\n", value->maintenance_parms_v3.pm_idx);

  // LOG_I(PHY, "nfapi_nr_dig_bf_interface_t:\n");
  // LOG_I(PHY, "  beam_idx: %d\n", value->maintenance_parms_v3.dig_bf_interface_list[0].beam_idx);

  LOG_I(PHY, "nfapi_v3_pdsch_maintenance_parameters_t:\n");
  LOG_I(PHY, "  ldpcBaseGraph: %d\n", value->maintenance_parms_v3.ldpcBaseGraph);
  LOG_I(PHY, "  tbSizeLbrmBytes: %d\n", value->maintenance_parms_v3.tbSizeLbrmBytes);

}
```