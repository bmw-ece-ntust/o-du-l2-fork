# Adjust OSC DU CellGroupConfig Parameters for OAI Consistency

Start Date: 2024/11/13
Summary: Adjusting OSC DU CellGroupConfig parameters to ensure consistency with OAI.
Status: padding
Assign: Ming 咚咚 [銘鴻]

<aside>
💡

Adjust the OSC DU build **`CellGroupConfig`** parameters to make the content as consistent as possible with OAI.

</aside>

[CellGroupConfig.diff](CellGroupConfig.diff)

[Responding to Robert's email about the F1AP Version and CellGroupConfig Debugging Tasks.](Responding%20to%20Robert's%20email%20about%20the%20F1AP%20Versio%2013510098314380fe87bee342af7f4c08.md) 

[OSC-DUHigh-CellGroupConfig.xml](OSC-DUHigh-CellGroupConfig.xml)

[OAIsplit2-CellGroupConfig.xml](OAIsplit2-CellGroupConfig%201.xml)

[CellGroupConfig_DU.xml](CellGroupConfig_DU.xml)

Below is a comparison table between `OAISPLIT2-CELLGROUPCONFIG.XML` and `CELLGROUPCONFIG_DU.XML`:

| 範疇 | `OAISPLIT2-CELLGROUPCONFIG.XML` | `CELLGROUPCONFIG_DU.XML` |
| --- | --- | --- |
| `t-PollRetransmit` | `<ms45/>` | `<ms45/>` |
| `pollPDU` | `<infinity/>` | `<p4/>` |
| `t-Reassembly` | `<ms35/>` | `<ms40/>` |
| `t-StatusProhibit` | `<ms0/>` | `<ms35/>` |
| `bucketSizeDuration` | `<ms1000/>` | `<ms150/>` |
| `sr-TransMax` | `<n64/>` | `<n16/>` |
| `sr-ProhibitTimer` | 無 | `<ms32/>` |
| `retxBSR-Timer` | `<sf80/>` | `<sf320/>` |
| `phr-PeriodicTimer` | `<sf10/>` | `<infinity/>` |
| `phr-ProhibitTimer` | `<sf10/>` | `<sf0/>` |
| `phr-Tx-PowerFactorChange` | `<dB1/>` | `<infinity/>` |
| `p-NR-FR1` | 無 | `0` |
| `rlmInSyncOutOfSyncThreshold` | 無 | `<n1/>` |
| `controlResourceSetId` | `1` | `1` |
| `frequencyDomainResources` | `111111111111111100000000000000000000000000000` | `000000000111100000000000000000000000000000000` |
| `duration` | `1` | `2` |
| `precoderGranularity` | `<sameAsREG-bundle/>` | `<allContiguousRBs/>` |
| `pdcch-DMRS-ScramblingID` | 無 | `1` |
| `searchSpaceId` | `5` | `2` |
| `aggregationLevel1` | `<n0/>` | `<n8/>` |
| `aggregationLevel2` | `<n2/>` | `<n8/>` |
| `aggregationLevel4` | `<n0/>` | `<n4/>` |
| `aggregationLevel8` | `<n0/>` | `<n2/>` |
| `aggregationLevel16` | `<n0/>` | `<n1/>` |
| `dci-Formats` | `<formats0-1-And-1-1/>` | `<formats0-0-And-1-0/>` |
| `dmrs-AdditionalPosition` | `<pos1/>` | `<pos0/>` |
| `startSymbolAndLength` | 無 | `40` |
| `maxNrofCodeWordsScheduledByDCI` | 無 | `<n1/>` |
| `pusch-Config` | `<codebook/>` | `<disabled/>` |
| `pusch-ServingCellConfig` | 無 | `<processingType2Enabled><false/></processingType2Enabled>` |
| `maxMIMO-Layers` | `2` | `1` |
| `schedulingRequestResourceId` | `1` | `1` |
| `periodicityAndOffset` | `<sl10>7</sl10>` | 無 |
| `resource` | `0` | 無 |
| `dl-DataToUL-ACK` | `6, 7, 8, 9, 10, 11, 12, 13` | `1, 2` |
| `srs-ResourceId` | `0` | `1` |
| `startPosition` | `1` | `0` |
| `sequenceId` | `40` | `0` |
| `pusch-PathlossReferenceRS-Id` | `0` | `1` |
| `p0-PUCCH-Id` | `1` | `1` |
| `p0-PUCCH-Value` | `0` | `0` |
| `p0` | `-80` | `0` |
| `aperiodicSRS-ResourceTrigger` | `1` | `1` |
| `slotOffset` | `6` | 無 |
| `c-SRS` | `25` | `0` |
| `b-SRS` | `0` | `0` |
| `b-hop` | `0` | `0` |
| `groupOrSequenceHopping` | `<neither/>` | `<neither/>` |
| `resourceType` | `<aperiodic/>` | `<aperiodic/>` |
| `spatialRelationInfo` | `<ssb-Index>0</ssb-Index>` | `<ssb-Index>0</ssb-Index>` |
| `uplinkBandwidthPartId` | `0` | `0` |
| `pucch-Resource` | `2` | `1` |
| `maxCodeRate` | `<zeroDot15/>` | 無 |
| `simultaneousHARQ-ACK-CSI` | `<true/>` | 無 |
| `pucch-ResourceSetId` | `0, 1` | `1` |
| `resourceList` | `0, 2` | `1` |
| `startingPRB` | `8, 0` | `0` |
| `format` | `<format0>, <format2>` | `<format1>` |
| `initialCyclicShift` | `0` | `0` |
| `nrofSymbols` | `1` | `4` |
| `startingSymbolIndex` | `13` | `0` |
| `timeDomainOCC` | 無 | `0` |
| `nrofSlots` | 無 | `<n4/>` |
| `dataScramblingIdentityPUSCH` | 無 | `1` |
| `scramblingID0` | 無 | `1` |
| `k2` | 無 | `4, 6` |
| `startSymbolAndLength` | 無 | `41` |
| `transformPrecoder` | 無 | `<disabled/>` |
| `pusch-PowerControl` | `<msg3-Alpha><alpha1/></msg3-Alpha>` | 無 |
| `p0-AlphaSets` | `<P0-PUSCH-AlphaSet>` | 無 |
| `p0-PUSCH-AlphaSetId` | `0` | 無 |
| `p0` | `0` | 無 |
| `alpha` | `<alpha1/>` | 無 |
| `pathlossReferenceRSToAddModList` | `<PUSCH-PathlossReferenceRS>` | 無 |
| `pusch-PathlossReferenceRS-Id` | `0` | 無 |
| `referenceSignal` | `<ssb-Index>0</ssb-Index>` | 無 |
| `csi-SSB-ResourceSetId` | `0` | 無 |
| `csi-SSB-ResourceList` | `<SSB-Index>0</SSB-Index>` | 無 |
| `csi-ResourceConfigId` | `20` | 無 |
| `csi-RS-ResourceSetList` | `<nzp-CSI-RS-SSB>` | 無 |
| `csi-SSB-ResourceSetList` | `<CSI-SSB-ResourceSetId>0</CSI-SSB-ResourceSetId>` | 無 |
| `bwp-Id` | `0` | 無 |
| `resourceType` | `<periodic/>` | 無 |
| `reportConfigId` | `10` | 無 |
| `resourcesForChannelMeasurement` | `20` | 無 |
| `reportSlotConfig` | `<slots160>8</slots160>` | 無 |
| `pucch-CSI-ResourceList` | `<PUCCH-CSI-Resource>` | 無 |
| `uplinkBandwidthPartId` | `0` | 無 |
| `pucch-Resource` | `2` | 無 |
| `ssb-Index-RSRP` | 無 | 無 |
| `timeRestrictionForChannelMeasurements` | `<configured/>` | 無 |
| `timeRestrictionForInterferenceMeasurements` | `<configured/>` | 無 |
| `groupBasedBeamReporting` | `<disabled>` | 無 |
| `nrofReportedRS` | `<n1/>` | 無 |
| `subbandSize` | `<value1/>` | 無 |

These are the main differences between the two XML documents.

```c
#define PDCCH_SRCH_SPC_TWO_ID 5
#define PDCCH_SRCH_SPC_TWO_AGG_LVL1_CANDIDATE 0   /* Num of candidate at aggregation level 1 */
#define PDCCH_SRCH_SPC_TWO_AGG_LVL2_CANDIDATE 2   /* Num of candidate at aggregation level 2 */
#define PDCCH_SRCH_SPC_TWO_AGG_LVL4_CANDIDATE 0   /* Num of candidate at aggregation level 4 */
#define PDCCH_SRCH_SPC_TWO_AGG_LVL8_CANDIDATE 0   /* Num of candidate at aggregation level 8 */
#define PDCCH_SRCH_SPC_TWO_AGG_LVL16_CANDIDATE 0  /* Num of candidate at aggregation level 16 */
// #define PDCCH_SRCH_SPC_TWO_UE_SPEC_DCI_FORMAT  0  /* format 0-0 and 1-0 */
#define PDCCH_SRCH_SPC_TWO_UE_SPEC_DCI_FORMAT  1  /* format 0-1 and 1-1 */
```