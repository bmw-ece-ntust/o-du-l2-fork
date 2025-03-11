# OAI SIB1 Full XML

Start Date: 2024/05/28
Summary: A detailed XML configuration for OAI SIB1, including parameters such as start date, assignment, status, and various technical values.
Status: Done
Assign: Ming 咚咚 [銘鴻]

| Element | Value |
| --- | --- |
| q-RxLevMin | -65 |
| MCC | 001 |
| MNC | 01 |
| Tracking Area Code | 000000000000000000000001 |
| Cell Identity | 000000000000101111000110000101001110 |
| Frequency Band Indicator (NR) | 78 |
| Offset to Point A | 86 |
| Subcarrier Spacing | 30 kHz |
| Carrier Bandwidth | 106 |
| Control Resource Set Zero | 12 |
| Search Space Zero | 0 |
| Monitoring Symbols Within Slot | 10000000000000 |
| Search Space ID | 1, 2, 3 |
| Control Resource Set ID | 0 |
| Monitoring Slot Periodicity | SL1 |
| Search Space Type | Common |
| DCI Format | Format0-0-AndFormat1-0 |
| Search Space SIB1 | 0 |
| Search Space Other System Info | 3 |
| Paging Search Space | 2 |
| RA Search Space | 1 |
| PDSCH Mapping Type | Type A |
| Start Symbol and Length (PDSCH) | 40, 54, 57 |
| BCCH Modification Period Coeff | n2 |
| Default Paging Cycle | RF256 |
| N and Paging Frame Offset | QuarterT: 1 |
| NS | One |
| First PDCCH Monitoring Occasion | SCS120KHZoneT-SCS60KHZhalfT-SCS30KHZquarterT-SCS15KHZoneEighthT: 0 |
| P-Max | 20 |
| PRACH Configuration Index | 98 |
| MSG1-FDM | One |
| MSG1 Frequency Start | 0 |
| Zero Correlation Zone Config | 13 |
| Preamble Received Target Power | -96 |
| Preamble Trans Max | n10 |
| Power Ramping Step | dB2present |
| RA Response Window | sl20 |
| Preamble Subcarrier Spacing | 30 kHz |
| Restricted Set Config | Unrestricted Set |
| PUSCH Mapping Type | Type B |
| Start Symbol and Length (PUSCH) | 41, 55, 38 |
| MSG3 Delta Preamble | 1 |
| P0 Nominal With Grant | -90 |
| PUCCH Resource Common | 0 |
| PUCCH Group Hopping | Neither |
| Hopping ID | 40 |
| P0 Nominal | -90 |
| Reference Subcarrier Spacing | 30 kHz |
| DL-UL Transmission Periodicity | ms5 |
| Number of DL Slots | 7 |
| Number of DL Symbols | 6 |
| Number of UL Slots | 2 |
| Number of UL Symbols | 4 |
| SSB PBCH Block Power | -25 |
| T300 | ms400 |
| T301 | ms400 |
| T310 | ms2000 |
| N310 | n10 |
| T311 | ms3000 |
| N311 | n1 |
| T319 | ms400 |
| SSB Periodicity Serving Cell | ms20 |
| DL-UL Configuration Common | Reference Subcarrier Spacing: 30 kHz, DL-UL Transmission Periodicity: ms5, Number of DL Slots: 7, Number of DL Symbols: 6, Number of UL Slots: 2, Number of UL Symbols: 4 |
| SSB Positions In Burst | In One Group: 10000000 |
| Time Alignment Timer Common | Infinity |

```c
<BCCH-DL-SCH-Message>
mai 28 14:13:35     <message>
mai 28 14:13:35         <c1>
mai 28 14:13:35             <systemInformationBlockType1>
mai 28 14:13:35                 <cellSelectionInfo>
mai 28 14:13:35                     <q-RxLevMin>-65</q-RxLevMin>
mai 28 14:13:35                 </cellSelectionInfo>
mai 28 14:13:35                 <cellAccessRelatedInfo>
mai 28 14:13:35                     <plmn-IdentityInfoList>
mai 28 14:13:35                         <PLMN-IdentityInfo>
mai 28 14:13:35                             <plmn-IdentityList>
mai 28 14:13:35                                 <PLMN-Identity>
mai 28 14:13:35                                     <mcc>
mai 28 14:13:35                                         <MCC-MNC-Digit>0</MCC-MNC-Digit>
mai 28 14:13:35                                         <MCC-MNC-Digit>0</MCC-MNC-Digit>
mai 28 14:13:35                                         <MCC-MNC-Digit>1</MCC-MNC-Digit>
mai 28 14:13:35                                     </mcc>
mai 28 14:13:35                                     <mnc>
mai 28 14:13:35                                         <MCC-MNC-Digit>0</MCC-MNC-Digit>
mai 28 14:13:35                                         <MCC-MNC-Digit>1</MCC-MNC-Digit>
mai 28 14:13:35                                     </mnc>
mai 28 14:13:35                                 </PLMN-Identity>
mai 28 14:13:35                             </plmn-IdentityList>
mai 28 14:13:35                             <trackingAreaCode>
mai 28 14:13:35                                 000000000000000000000001
mai 28 14:13:35                             </trackingAreaCode>
mai 28 14:13:35                             <cellIdentity>
mai 28 14:13:35                                 000000000000101111000110000101001110
mai 28 14:13:35                             </cellIdentity>
mai 28 14:13:35                             <cellReservedForOperatorUse><notReserved/></cellReservedForOperatorUse>
mai 28 14:13:35                         </PLMN-IdentityInfo>
mai 28 14:13:35                     </plmn-IdentityInfoList>
mai 28 14:13:35                 </cellAccessRelatedInfo>
mai 28 14:13:35                 <servingCellConfigCommon>
mai 28 14:13:35                     <downlinkConfigCommon>
mai 28 14:13:35                         <frequencyInfoDL>
mai 28 14:13:35                             <frequencyBandList>
mai 28 14:13:35                                 <NR-MultiBandInfo>
mai 28 14:13:35                                     <freqBandIndicatorNR>78</freqBandIndicatorNR>
mai 28 14:13:35                                 </NR-MultiBandInfo>
mai 28 14:13:35                             </frequencyBandList>
mai 28 14:13:35                             <offsetToPointA>86</offsetToPointA>
mai 28 14:13:35                             <scs-SpecificCarrierList>
mai 28 14:13:35                                 <SCS-SpecificCarrier>
mai 28 14:13:35                                     <offsetToCarrier>0</offsetToCarrier>
mai 28 14:13:35                                     <subcarrierSpacing><kHz30/></subcarrierSpacing>
mai 28 14:13:35                                     <carrierBandwidth>106</carrierBandwidth>
mai 28 14:13:35                                 </SCS-SpecificCarrier>
mai 28 14:13:35                             </scs-SpecificCarrierList>
mai 28 14:13:35                         </frequencyInfoDL>
mai 28 14:13:35                         <initialDownlinkBWP>
mai 28 14:13:35                             <genericParameters>
mai 28 14:13:35                                 <locationAndBandwidth>28875</locationAndBandwidth>
mai 28 14:13:35                                 <subcarrierSpacing><kHz30/></subcarrierSpacing>
mai 28 14:13:35                             </genericParameters>
mai 28 14:13:35                             <pdcch-ConfigCommon>
mai 28 14:13:35                                 <setup>
mai 28 14:13:35                                     <controlResourceSetZero>12</controlResourceSetZero>
mai 28 14:13:35                                     <searchSpaceZero>0</searchSpaceZero>
mai 28 14:13:35                                     <commonSearchSpaceList>
mai 28 14:13:35                                         <SearchSpace>
mai 28 14:13:35                                             <searchSpaceId>1</searchSpaceId>
mai 28 14:13:35                                             <controlResourceSetId>0</controlResourceSetId>
mai 28 14:13:35                                             <monitoringSlotPeriodicityAndOffset>
mai 28 14:13:35                                                 <sl1></sl1>
mai 28 14:13:35                                             </monitoringSlotPeriodicityAndOffset>
mai 28 14:13:35                                             <monitoringSymbolsWithinSlot>
mai 28 14:13:35                                                 10000000000000
mai 28 14:13:35                                             </monitoringSymbolsWithinSlot>
mai 28 14:13:35                                             <nrofCandidates>
mai 28 14:13:35                                                 <aggregationLevel1><n0/></aggregationLevel1>
mai 28 14:13:35                                                 <aggregationLevel2><n0/></aggregationLevel2>
mai 28 14:13:35                                                 <aggregationLevel4><n1/></aggregationLevel4>
mai 28 14:13:35                                                 <aggregationLevel8><n0/></aggregationLevel8>
mai 28 14:13:35                                                 <aggregationLevel16><n0/></aggregationLevel16>
mai 28 14:13:35                                             </nrofCandidates>
mai 28 14:13:35                                             <searchSpaceType>
mai 28 14:13:35                                                 <common>
mai 28 14:13:35                                                     <dci-Format0-0-AndFormat1-0>
mai 28 14:13:35                                                     </dci-Format0-0-AndFormat1-0>
mai 28 14:13:35                                                 </common>
mai 28 14:13:35                                             </searchSpaceType>
mai 28 14:13:35                                         </SearchSpace>
mai 28 14:13:35                                         <SearchSpace>
mai 28 14:13:35                                             <searchSpaceId>2</searchSpaceId>
mai 28 14:13:35                                             <controlResourceSetId>0</controlResourceSetId>
mai 28 14:13:35                                             <monitoringSlotPeriodicityAndOffset>
mai 28 14:13:35                                                 <sl1></sl1>
mai 28 14:13:35                                             </monitoringSlotPeriodicityAndOffset>
mai 28 14:13:35                                             <monitoringSymbolsWithinSlot>
mai 28 14:13:35                                                 10000000000000
mai 28 14:13:35                                             </monitoringSymbolsWithinSlot>
mai 28 14:13:35                                             <nrofCandidates>
mai 28 14:13:35                                                 <aggregationLevel1><n0/></aggregationLevel1>
mai 28 14:13:35                                                 <aggregationLevel2><n0/></aggregationLevel2>
mai 28 14:13:35                                                 <aggregationLevel4><n1/></aggregationLevel4>
mai 28 14:13:35                                                 <aggregationLevel8><n0/></aggregationLevel8>
mai 28 14:13:35                                                 <aggregationLevel16><n0/></aggregationLevel16>
mai 28 14:13:35                                             </nrofCandidates>
mai 28 14:13:35                                             <searchSpaceType>
mai 28 14:13:35                                                 <common>
mai 28 14:13:35                                                     <dci-Format0-0-AndFormat1-0>
mai 28 14:13:35                                                     </dci-Format0-0-AndFormat1-0>
mai 28 14:13:35                                                 </common>
mai 28 14:13:35                                             </searchSpaceType>
mai 28 14:13:35                                         </SearchSpace>
mai 28 14:13:35                                         <SearchSpace>
mai 28 14:13:35                                             <searchSpaceId>3</searchSpaceId>
mai 28 14:13:35                                             <controlResourceSetId>0</controlResourceSetId>
mai 28 14:13:35                                             <monitoringSlotPeriodicityAndOffset>
mai 28 14:13:35                                                 <sl1></sl1>
mai 28 14:13:35                                             </monitoringSlotPeriodicityAndOffset>
mai 28 14:13:35                                             <monitoringSymbolsWithinSlot>
mai 28 14:13:35                                                 10000000000000
mai 28 14:13:35                                             </monitoringSymbolsWithinSlot>
mai 28 14:13:35                                             <nrofCandidates>
mai 28 14:13:35                                                 <aggregationLevel1><n0/></aggregationLevel1>
mai 28 14:13:35                                                 <aggregationLevel2><n0/></aggregationLevel2>
mai 28 14:13:35                                                 <aggregationLevel4><n1/></aggregationLevel4>
mai 28 14:13:35                                                 <aggregationLevel8><n0/></aggregationLevel8>
mai 28 14:13:35                                                 <aggregationLevel16><n0/></aggregationLevel16>
mai 28 14:13:35                                             </nrofCandidates>
mai 28 14:13:35                                             <searchSpaceType>
mai 28 14:13:35                                                 <common>
mai 28 14:13:35                                                     <dci-Format0-0-AndFormat1-0>
mai 28 14:13:35                                                     </dci-Format0-0-AndFormat1-0>
mai 28 14:13:35                                                 </common>
mai 28 14:13:35                                             </searchSpaceType>
mai 28 14:13:35                                         </SearchSpace>
mai 28 14:13:35                                     </commonSearchSpaceList>
mai 28 14:13:35                                     <searchSpaceSIB1>0</searchSpaceSIB1>
mai 28 14:13:35                                     <searchSpaceOtherSystemInformation>3</searchSpaceOtherSystemInformation>
mai 28 14:13:35                                     <pagingSearchSpace>2</pagingSearchSpace>
mai 28 14:13:35                                     <ra-SearchSpace>1</ra-SearchSpace>
mai 28 14:13:35                                 </setup>
mai 28 14:13:35                             </pdcch-ConfigCommon>
mai 28 14:13:35                             <pdsch-ConfigCommon>
mai 28 14:13:35                                 <setup>
mai 28 14:13:35                                     <pdsch-TimeDomainAllocationList>
mai 28 14:13:35                                         <PDSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                             <mappingType><typeA/></mappingType>
mai 28 14:13:35                                             <startSymbolAndLength>40</startSymbolAndLength>
mai 28 14:13:35                                         </PDSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                         <PDSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                             <mappingType><typeA/></mappingType>
mai 28 14:13:35                                             <startSymbolAndLength>54</startSymbolAndLength>
mai 28 14:13:35                                         </PDSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                         <PDSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                             <mappingType><typeA/></mappingType>
mai 28 14:13:35                                             <startSymbolAndLength>57</startSymbolAndLength>
mai 28 14:13:35                                         </PDSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                     </pdsch-TimeDomainAllocationList>
mai 28 14:13:35                                 </setup>
mai 28 14:13:35                             </pdsch-ConfigCommon>
mai 28 14:13:35                         </initialDownlinkBWP>
mai 28 14:13:35                         <bcch-Config>
mai 28 14:13:35                             <modificationPeriodCoeff><n2/></modificationPeriodCoeff>
mai 28 14:13:35                         </bcch-Config>
mai 28 14:13:35                         <pcch-Config>
mai 28 14:13:35                             <defaultPagingCycle><rf256/></defaultPagingCycle>
mai 28 14:13:35                             <nAndPagingFrameOffset>
mai 28 14:13:35                                 <quarterT>1</quarterT>
mai 28 14:13:35                             </nAndPagingFrameOffset>
mai 28 14:13:35                             <ns><one/></ns>
mai 28 14:13:35                             <firstPDCCH-MonitoringOccasionOfPO>
mai 28 14:13:35                                 <sCS120KHZoneT-SCS60KHZhalfT-SCS30KHZquarterT-SCS15KHZoneEighthT>
mai 28 14:13:35                                     <INTEGER>0</INTEGER>
mai 28 14:13:35                                 </sCS120KHZoneT-SCS60KHZhalfT-SCS30KHZquarterT-SCS15KHZoneEighthT>
mai 28 14:13:35                             </firstPDCCH-MonitoringOccasionOfPO>
mai 28 14:13:35                         </pcch-Config>
mai 28 14:13:35                     </downlinkConfigCommon>
mai 28 14:13:35                     <uplinkConfigCommon>
mai 28 14:13:35                         <frequencyInfoUL>
mai 28 14:13:35                             <scs-SpecificCarrierList>
mai 28 14:13:35                                 <SCS-SpecificCarrier>
mai 28 14:13:35                                     <offsetToCarrier>0</offsetToCarrier>
mai 28 14:13:35                                     <subcarrierSpacing><kHz30/></subcarrierSpacing>
mai 28 14:13:35                                     <carrierBandwidth>106</carrierBandwidth>
mai 28 14:13:35                                 </SCS-SpecificCarrier>
mai 28 14:13:35                             </scs-SpecificCarrierList>
mai 28 14:13:35                             <p-Max>20</p-Max>
mai 28 14:13:35                         </frequencyInfoUL>
mai 28 14:13:35                         <initialUplinkBWP>
mai 28 14:13:35                             <genericParameters>
mai 28 14:13:35                                 <locationAndBandwidth>28875</locationAndBandwidth>
mai 28 14:13:35                                 <subcarrierSpacing><kHz30/></subcarrierSpacing>
mai 28 14:13:35                             </genericParameters>
mai 28 14:13:35                             <rach-ConfigCommon>
mai 28 14:13:35                                 <setup>
mai 28 14:13:35                                     <rach-ConfigGeneric>
mai 28 14:13:35                                         <prach-ConfigurationIndex>98</prach-ConfigurationIndex>
mai 28 14:13:35                                         <msg1-FDM><one/></msg1-FDM>
mai 28 14:13:35                                         <msg1-FrequencyStart>0</msg1-FrequencyStart>
mai 28 14:13:35                                         <zeroCorrelationZoneConfig>13</zeroCorrelationZoneConfig>
mai 28 14:13:35                                         <preambleReceivedTargetPower>-96</preambleReceivedTargetPower>
mai 28 14:13:35                                         <preambleTransMax><n10/></preambleTransMax>
mai 28 14:13:35                                         <powerRampingStep><dB2/></powerRampingStep>
mai 28 14:13:35                                         <ra-ResponseWindow><sl20/></ra-ResponseWindow>
mai 28 14:13:35                                     </rach-ConfigGeneric>
mai 28 14:13:35                                     <ssb-perRACH-OccasionAndCB-PreamblesPerSSB>
mai 28 14:13:35                                         <one><n60/></one>
mai 28 14:13:35                                     </ssb-perRACH-OccasionAndCB-PreamblesPerSSB>
mai 28 14:13:35                                     <ra-ContentionResolutionTimer><sf64/></ra-ContentionResolutionTimer>
mai 28 14:13:35                                     <rsrp-ThresholdSSB>19</rsrp-ThresholdSSB>
mai 28 14:13:35                                     <prach-RootSequenceIndex>
mai 28 14:13:35                                         <l139>1</l139>
mai 28 14:13:35                                     </prach-RootSequenceIndex>
mai 28 14:13:35                                     <msg1-SubcarrierSpacing><kHz30/></msg1-SubcarrierSpacing>
mai 28 14:13:35                                     <restrictedSetConfig><unrestrictedSet/></restrictedSetConfig>
mai 28 14:13:35                                 </setup>
mai 28 14:13:35                             </rach-ConfigCommon>
mai 28 14:13:35                             <pusch-ConfigCommon>
mai 28 14:13:35                                 <setup>
mai 28 14:13:35                                     <pusch-TimeDomainAllocationList>
mai 28 14:13:35                                         <PUSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                             <k2>6</k2>
mai 28 14:13:35                                             <mappingType><typeB/></mappingType>
mai 28 14:13:35                                             <startSymbolAndLength>41</startSymbolAndLength>
mai 28 14:13:35                                         </PUSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                         <PUSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                             <k2>6</k2>
mai 28 14:13:35                                             <mappingType><typeB/></mappingType>
mai 28 14:13:35                                             <startSymbolAndLength>55</startSymbolAndLength>
mai 28 14:13:35                                         </PUSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                         <PUSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                             <k2>6</k2>
mai 28 14:13:35                                             <mappingType><typeB/></mappingType>
mai 28 14:13:35                                             <startSymbolAndLength>38</startSymbolAndLength>
mai 28 14:13:35                                         </PUSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                         <PUSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                             <k2>7</k2>
mai 28 14:13:35                                             <mappingType><typeB/></mappingType>
mai 28 14:13:35                                             <startSymbolAndLength>38</startSymbolAndLength>
mai 28 14:13:35                                         </PUSCH-TimeDomainResourceAllocation>
mai 28 14:13:35                                     </pusch-TimeDomainAllocationList>
mai 28 14:13:35                                     <msg3-DeltaPreamble>1</msg3-DeltaPreamble>
mai 28 14:13:35                                     <p0-NominalWithGrant>-90</p0-NominalWithGrant>
mai 28 14:13:35                                 </setup>
mai 28 14:13:35                             </pusch-ConfigCommon>
mai 28 14:13:35                             <pucch-ConfigCommon>
mai 28 14:13:35                                 <setup>
mai 28 14:13:35                                     <pucch-ResourceCommon>0</pucch-ResourceCommon>
mai 28 14:13:35                                     <pucch-GroupHopping><neither/></pucch-GroupHopping>
mai 28 14:13:35                                     <hoppingId>40</hoppingId>
mai 28 14:13:35                                     <p0-nominal>-90</p0-nominal>
mai 28 14:13:35                                 </setup>
mai 28 14:13:35                             </pucch-ConfigCommon>
mai 28 14:13:35                         </initialUplinkBWP>
mai 28 14:13:35                         <timeAlignmentTimerCommon><infinity/></timeAlignmentTimerCommon>
mai 28 14:13:35                     </uplinkConfigCommon>
mai 28 14:13:35                     <ssb-PositionsInBurst>
mai 28 14:13:35                         <inOneGroup>
mai 28 14:13:35                             10000000
mai 28 14:13:35                         </inOneGroup>
mai 28 14:13:35                     </ssb-PositionsInBurst>
mai 28 14:13:35                     <ssb-PeriodicityServingCell><ms20/></ssb-PeriodicityServingCell>
mai 28 14:13:35                     <tdd-UL-DL-ConfigurationCommon>
mai 28 14:13:35                         <referenceSubcarrierSpacing><kHz30/></referenceSubcarrierSpacing>
mai 28 14:13:35                         <pattern1>
mai 28 14:13:35                             <dl-UL-TransmissionPeriodicity><ms5/></dl-UL-TransmissionPeriodicity>
mai 28 14:13:35                             <nrofDownlinkSlots>7</nrofDownlinkSlots>
mai 28 14:13:35                             <nrofDownlinkSymbols>6</nrofDownlinkSymbols>
mai 28 14:13:35                             <nrofUplinkSlots>2</nrofUplinkSlots>
mai 28 14:13:35                             <nrofUplinkSymbols>4</nrofUplinkSymbols>
mai 28 14:13:35                         </pattern1>
mai 28 14:13:35                     </tdd-UL-DL-ConfigurationCommon>
mai 28 14:13:35                     <ss-PBCH-BlockPower>-25</ss-PBCH-BlockPower>
mai 28 14:13:35                 </servingCellConfigCommon>
mai 28 14:13:35                 <ue-TimersAndConstants>
mai 28 14:13:35                     <t300><ms400/></t300>
mai 28 14:13:35                     <t301><ms400/></t301>
mai 28 14:13:35                     <t310><ms2000/></t310>
mai 28 14:13:35                     <n310><n10/></n310>
mai 28 14:13:35                     <t311><ms3000/></t311>
mai 28 14:13:35                     <n311><n1/></n311>
mai 28 14:13:35                     <t319><ms400/></t319>
mai 28 14:13:35                 </ue-TimersAndConstants>
mai 28 14:13:35             </systemInformationBlockType1>
mai 28 14:13:35         </c1>
mai 28 14:13:35     </message>
mai 28 14:13:35 </BCCH-DL-SCH-Message>
```