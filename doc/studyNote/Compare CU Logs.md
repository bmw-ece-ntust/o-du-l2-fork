# Compare CU Logs

Start Date: 2024/09/30
Summary: The project involves comparing CU logs and analyzing various F1AP message transfers and configurations in a telecommunications context.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Compare

![image.png](image%2016.png)

<aside>
💡

Reference:
https://www.etsi.org/deliver/etsi_TS/138400_138499/138473/15.03.00_60/ts_138473v150300p.pdf

https://hackmd.io/@sheryl0625/H1fDsvgoC

</aside>

[1-OAI_CU.log](1-OAI_CU.log)

![image.png](image.png)

# OAI CU + OSC DU

## **F1SetupRequest**

```jsx
<F1AP-PDU>
 九  30 12:47:06     <initiatingMessage>
 九  30 12:47:06         <procedureCode>1</procedureCode>
 九  30 12:47:06         <criticality><reject/></criticality>
 九  30 12:47:06         <value>
 九  30 12:47:06             <F1SetupRequest>
 九  30 12:47:06                 <protocolIEs>
 九  30 12:47:06                     <F1SetupRequestIEs>
 九  30 12:47:06                         <id>78</id>
 九  30 12:47:06                         <criticality><reject/></criticality>
 九  30 12:47:06                         <value>
 九  30 12:47:06                             <TransactionID>1</TransactionID>
 九  30 12:47:06                         </value>
 九  30 12:47:06                     </F1SetupRequestIEs>
 九  30 12:47:06                     <F1SetupRequestIEs>
 九  30 12:47:06                         <id>42</id>
 九  30 12:47:06                         <criticality><reject/></criticality>
 九  30 12:47:06                         <value>
 九  30 12:47:06                             <GNB-DU-ID>1</GNB-DU-ID>
 九  30 12:47:06                         </value>
 九  30 12:47:06                     </F1SetupRequestIEs>
 九  30 12:47:06                     <F1SetupRequestIEs>
 九  30 12:47:06                         <id>45</id>
 九  30 12:47:06                         <criticality><ignore/></criticality>
 九  30 12:47:06                         <value>
 九  30 12:47:06                             <GNB-DU-Name>ORAN OAM DU</GNB-DU-Name>
 九  30 12:47:06                         </value>
 九  30 12:47:06                     </F1SetupRequestIEs>
 九  30 12:47:06                     <F1SetupRequestIEs>
 九  30 12:47:06                         <id>44</id>
 九  30 12:47:06                         <criticality><reject/></criticality>
 九  30 12:47:06                         <value>
 九  30 12:47:06                             <GNB-DU-Served-Cells-List>
 九  30 12:47:06                                 <ProtocolIE-SingleContainer>
 九  30 12:47:06                                     <id>43</id>
 九  30 12:47:06                                     <criticality><reject/></criticality>
 九  30 12:47:06                                     <value>
 九  30 12:47:06                                         <GNB-DU-Served-Cells-Item>
 九  30 12:47:06                                             <served-Cell-Information>
 九  30 12:47:06                                                 <nRCGI>
 九  30 12:47:06                                                     <pLMN-Identity>00 F1 10</pLMN-Identity>
 九  30 12:47:06                                                     <nRCellIdentity>
 九  30 12:47:06                                                         000000000000000000000000000000000001
 九  30 12:47:06                                                     </nRCellIdentity>
 九  30 12:47:06                                                 </nRCGI>
 九  30 12:47:06                                                 <nRPCI>1</nRPCI>
 九  30 12:47:06                                                 <fiveGS-TAC>00 00 01</fiveGS-TAC>
 九  30 12:47:06                                                 <servedPLMNs>
 九  30 12:47:06                                                     <ServedPLMNs-Item>
 九  30 12:47:06                                                         <pLMN-Identity>00 F1 10</pLMN-Identity>
 九  30 12:47:06                                                         <iE-Extensions>
 九  30 12:47:06                                                             <ServedPLMNs-ItemExtIEs>
 九  30 12:47:06                                                                 <id>131</id>
 九  30 12:47:06                                                                 <criticality><ignore/></criticality>
 九  30 12:47:06                                                                 <extensionValue>
 九  30 12:47:06                                                                     <SliceSupportList>
 九  30 12:47:06                                                                         <SliceSupportItem>
 九  30 12:47:06                                                                             <sNSSAI>
 九  30 12:47:06                                                                                 <sST>01</sST>
 九  30 12:47:06                                                                                 <sD>02 03 04</sD>
 九  30 12:47:06                                                                             </sNSSAI>
 九  30 12:47:06                                                                         </SliceSupportItem>
 九  30 12:47:06                                                                         <SliceSupportItem>
 九  30 12:47:06                                                                             <sNSSAI>
 九  30 12:47:06                                                                                 <sST>05</sST>
 九  30 12:47:06                                                                                 <sD>06 07 08</sD>
 九  30 12:47:06                                                                             </sNSSAI>
 九  30 12:47:06                                                                         </SliceSupportItem>
 九  30 12:47:06                                                                     </SliceSupportList>
 九  30 12:47:06                                                                 </extensionValue>
 九  30 12:47:06                                                             </ServedPLMNs-ItemExtIEs>
 九  30 12:47:06                                                         </iE-Extensions>
 九  30 12:47:06                                                     </ServedPLMNs-Item>
 九  30 12:47:06                                                 </servedPLMNs>
 九  30 12:47:06                                                 <nR-Mode-Info>
 九  30 12:47:06                                                     <tDD>
 九  30 12:47:06                                                         <nRFreqInfo>
 九  30 12:47:06                                                             <nRARFCN>623400</nRARFCN>
 九  30 12:47:06                                                             <freqBandListNr>
 九  30 12:47:06                                                                 <FreqBandNrItem>
 九  30 12:47:06                                                                     <freqBandIndicatorNr>78</freqBandIndicatorNr>
 九  30 12:47:06                                                                     <supportedSULBandList>
 九  30 12:47:06                                                                         <SupportedSULFreqBandItem>
 九  30 12:47:06                                                                             <freqBandIndicatorNr>2</freqBandIndicatorNr>
 九  30 12:47:06                                                                         </SupportedSULFreqBandItem>
 九  30 12:47:06                                                                     </supportedSULBandList>
 九  30 12:47:06                                                                 </FreqBandNrItem>
 九  30 12:47:06                                                             </freqBandListNr>
 九  30 12:47:06                                                         </nRFreqInfo>
 九  30 12:47:06                                                         <transmission-Bandwidth>
 九  30 12:47:06                                                             <nRSCS><scs30/></nRSCS>
 九  30 12:47:06                                                             <nRNRB><nrb273/></nRNRB>
 九  30 12:47:06                                                         </transmission-Bandwidth>
 九  30 12:47:06                                                     </tDD>
 九  30 12:47:06                                                 </nR-Mode-Info>
 九  30 12:47:06                                                 <measurementTimingConfiguration>10 11 33 D4 05 02 00</measurementTimingConfiguration>
 九  30 12:47:06                                             </served-Cell-Information>
 九  30 12:47:06                                             <gNB-DU-System-Information>
 九  30 12:47:06                                                 <mIB-message>02 0C 0C</mIB-message>
 九  30 12:47:06                                                 <sIB1-message>
 九  30 12:47:06                                                     64 80 0A 02 08 00 80 40 00 00 40 00 00 00 06 90 
 九  30 12:47:06                                                     84 D0 56 00 00 26 96 70 CB 35 DE 01 B8 20 10 00 
 九  30 12:47:06                                                     00 40 40 00 20 D2 1C 8D 87 21 D3 30 00 08 00 00 
 九  30 12:47:06                                                     9A 72 73 86 59 95 18 80 06 B5 33 5F 72 70 12 4E 
 九  30 12:47:06                                                     71 2A 63 5B C6 A9 8D 52 5C 2E 00 50 E1 D0 08 2C 
 九  30 12:47:06                                                     07 60 12 23 37 B1 0C
 九  30 12:47:06                                                 </sIB1-message>
 九  30 12:47:06                                             </gNB-DU-System-Information>
 九  30 12:47:06                                         </GNB-DU-Served-Cells-Item>
 九  30 12:47:06                                     </value>
 九  30 12:47:06                                 </ProtocolIE-SingleContainer>
 九  30 12:47:06                             </GNB-DU-Served-Cells-List>
 九  30 12:47:06                         </value>
 九  30 12:47:06                     </F1SetupRequestIEs>
 九  30 12:47:06                     <F1SetupRequestIEs>
 九  30 12:47:06                         <id>171</id>
 九  30 12:47:06                         <criticality><reject/></criticality>
 九  30 12:47:06                         <value>
 九  30 12:47:06                             <RRC-Version>
 九  30 12:47:06                                 <latest-RRC-Version>
 九  30 12:47:06                                     000
 九  30 12:47:06                                 </latest-RRC-Version>
 九  30 12:47:06                                 <iE-Extensions>
 九  30 12:47:06                                     <RRC-Version-ExtIEs>
 九  30 12:47:06                                         <id>199</id>
 九  30 12:47:06                                         <criticality><reject/></criticality>
 九  30 12:47:06                                         <extensionValue>
 九  30 12:47:06                                             <Latest-RRC-Version-Enhanced>0F 05 00</Latest-RRC-Version-Enhanced>
 九  30 12:47:06                                         </extensionValue>
 九  30 12:47:06                                     </RRC-Version-ExtIEs>
 九  30 12:47:06                                 </iE-Extensions>
 九  30 12:47:06                             </RRC-Version>
 九  30 12:47:06                         </value>
 九  30 12:47:06                     </F1SetupRequestIEs>
 九  30 12:47:06                 </protocolIEs>
 九  30 12:47:06             </F1SetupRequest>
 九  30 12:47:06         </value>
 九  30 12:47:06     </initiatingMessage>
 九  30 12:47:06 </F1AP-PDU>
```

## F1SetupResponse

```jsx
<F1AP-PDU>
    <successfulOutcome>
        <procedureCode>1</procedureCode>
        <criticality><reject/></criticality>
        <value>
            <F1SetupResponse>
                <protocolIEs>
                    <F1SetupResponseIEs>
                        <id>78</id>
                        <criticality><reject/></criticality>
                        <value>
                            <TransactionID>1</TransactionID>
                        </value>
                    </F1SetupResponseIEs>
                    <F1SetupResponseIEs>
                        <id>82</id>
                        <criticality><ignore/></criticality>
                        <value>
                            <GNB-CU-Name>gNB-Eurecom-CU</GNB-CU-Name>
                        </value>
                    </F1SetupResponseIEs>
                    <F1SetupResponseIEs>
                        <id>3</id>
                        <criticality><reject/></criticality>
                        <value>
                            <Cells-to-be-Activated-List>
                                <ProtocolIE-SingleContainer>
                                    <id>4</id>
                                    <criticality><reject/></criticality>
                                    <value>
                                        <Cells-to-be-Activated-List-Item>
                                            <nRCGI>
                                                <pLMN-Identity>00 F1 10</pLMN-Identity>
                                                <nRCellIdentity>
                                                    000000000000000000000000000000000001
                                                </nRCellIdentity>
                                            </nRCGI>
                                            <nRPCI>1</nRPCI>
                                        </Cells-to-be-Activated-List-Item>
                                    </value>
                                </ProtocolIE-SingleContainer>
                            </Cells-to-be-Activated-List>
                        </value>
                    </F1SetupResponseIEs>
                    <F1SetupResponseIEs>
                        <id>170</id>
                        <criticality><reject/></criticality>
                        <value>
                            <RRC-Version>
                                <latest-RRC-Version>
                                    000
                                </latest-RRC-Version>
                                <iE-Extensions>
                                    <RRC-Version-ExtIEs>
                                        <id>199</id>
                                        <criticality><ignore/></criticality>
                                        <extensionValue>
                                            <OCTET STRING (SIZE(3))>11 03 00</OCTET STRING (SIZE(3))>
                                        </extensionValue>
                                    </RRC-Version-ExtIEs>
                                </iE-Extensions>
                            </RRC-Version>
                        </value>
                    </F1SetupResponseIEs>
                </protocolIEs>
            </F1SetupResponse>
        </value>
    </successfulOutcome>
</F1AP-PDU>
```

## GNBDUConfigurationUpdateAcknowledge

```jsx
<F1AP-PDU>
    <successfulOutcome>
        <procedureCode>3</procedureCode>
        <criticality><reject/></criticality>
        <value>
            <GNBDUConfigurationUpdateAcknowledge>
                <protocolIEs>
                    <GNBDUConfigurationUpdateAcknowledgeIEs>
                        <id>78</id>
                        <criticality><reject/></criticality>
                        <value>
                            <TransactionID>1</TransactionID>
                        </value>
                    </GNBDUConfigurationUpdateAcknowledgeIEs>
                </protocolIEs>
            </GNBDUConfigurationUpdateAcknowledge>
        </value>
    </successfulOutcome>
</F1AP-PDU>
```

## CellGroupConfig

```jsx
<CellGroupConfig>
 九  30 12:47:17     <cellGroupId>0</cellGroupId>
 九  30 12:47:17     <rlc-BearerToAddModList>
 九  30 12:47:17         <RLC-BearerConfig>
 九  30 12:47:17             <logicalChannelIdentity>1</logicalChannelIdentity>
 九  30 12:47:17             <servedRadioBearer>
 九  30 12:47:17                 <srb-Identity>1</srb-Identity>
 九  30 12:47:17             </servedRadioBearer>
 九  30 12:47:17             <rlc-Config>
 九  30 12:47:17                 <am>
 九  30 12:47:17                     <ul-AM-RLC>
 九  30 12:47:17                         <sn-FieldLength>[DEBUG] --> ULTTI nPDUs:0
 九  30 12:47:17 <size12/></sn-FieldLength>
 九  30 12:47:17                         <t-PollRetransmit><ms45/></t-PollRetransmit>
 九  30 12:47:17                         <pollPDU><p4/></pollPDU>
 九  30 12:47:17                         <pollByte><infinity/></pollByte>
 九  30 12:47:17                         <maxRetxThreshold><t8/></maxRetxThreshold>
 九  30 12:47:17                     </ul-AM-RLC>
 九  30 12:47:17                     <dl-AM-RLC>
 九  30 12:47:17                         <sn-FieldLength><size12/></sn-FieldLength>
 九  30 12:47:17                         <t-Reassembly><ms40/></t-Reassembly>
 九  30 12:47:17                         <t-StatusProhibit><ms35/></t-StatusProhibit>
 九  30 12:47:17                     </dl-AM-RLC>
 九  30 12:47:17                 </am>
 九  30 12:47:17             </rlc-Config>
 九  30 12:47:17             <mac-LogicalChannelConfig>
 九  30 12:47:17                 <ul-SpecificParameters>
 九  30 12:47:17                     <priority>1</priority>
 九  30 12:47:17                     <prioritisedBitRate><infinity/></prioritisedBitRate>
 九  30 12:47:17                     <bucketSizeDuration><ms150/></bucketSizeDuration>
 九  30 12:47:17                     <logicalChannelGroup>0</logicalChannelGroup>
 九  30 12:47:17                     <schedulingRequestID>0</schedulingRequestID>
 九  30 12:47:17                     <logicalChannelSR-Mask><false/></logicalChannelSR-Mask>
 九  30 12:47:17                     <logicalChannelSR-DelayTimerApplied><false/></logicalChannelSR-DelayTimerApplied>
 九  30 12:47:17                 </ul-SpecificParameters>
 九  30 12:47:17             </mac-LogicalChannelConfig>
 九  30 12:47:17         </RLC-BearerConfig>
 九  30 12:47:17     </rlc-BearerToAddModList>
 九  30 12:47:17     <mac-CellGroupConfig>
 九  30 12:47:17         <schedulingRequestConfig>
 九  30 12:47:17             <schedulingRequestToAddModList>
 九  30 12:47:17                 <SchedulingRequestToAddMod>
 九  30 12:47:17                     <schedulingRequestId>0</schedulingRequestId>
 九  30 12:47:17                     <sr-ProhibitTimer><ms32/></sr-ProhibitTimer>
 九  30 12:47:17                     <sr-TransMax><n16/></sr-TransMax>
 九  30 12:47:17                 </SchedulingRequestToAddMod>
 九  30 12:47:17             </schedulingRequestToAddModList>
 九  30 12:47:17         </schedulingRequestConfig>
 九  30 12:47:17         <bsr-Config>
 九  30 12:47:17             <periodicBSR-Timer><sf10/></periodicBSR-Timer>
 九  30 12:47:17             <retxBSR-Timer><sf320/></retxBSR-Timer>
 九  30 12:47:17         </bsr-Config>
 九  30 12:47:17         <tag-Config>
 九  30 12:47:17             <tag-ToAddModList>
 九  30 12:47:17                 <TAG>
 九  30 12:47:17                     <tag-Id>0</tag-Id>
 九  30 12:47:17                     <timeAlignmentTimer><infinity/></timeAlignmentTimer>
 九  30 12:47:17                 </TAG>
 九  30 12:47:17             </tag-ToAddModList>
 九  30 12:47:17         </tag-Config>
 九  30 12:47:17         <phr-Config>
 九  30 12:47:17             <setup>
 九  30 12:47:17                 <phr-PeriodicTimer><infinity/></phr-PeriodicTimer>
 九  30 12:47:17                 <phr-ProhibitTimer><sf0/></phr-ProhibitTimer>
 九  30 12:47:17                 <phr-Tx-PowerFactorChange><infinity/></phr-Tx-PowerFactorChange>
 九  30 12:47:17                 <multiplePHR><false/></multiplePHR>
 九  30 12:47:17                 <dummy><false/></dummy>
 九  30 12:47:17                 <phr-Type2OtherCell><false/></phr-Type2OtherCell>
 九  30 12:47:17                 <phr-ModeOtherCG><real/></phr-ModeOtherCG>
 九  30 12:47:17             </setup>
 九  30 12:47:17         </phr-Config>
 九  30 12:47:17         <skipUplinkTxDynamic><false/></skipUplinkTxDynamic>
 九  30 12:47:17     </mac-CellGroupConfig>
 九  30 12:47:17     <physicalCellGroupConfig>
 九  30 12:47:17         <p-NR-FR1>0</p-NR-FR1>
 九  30 12:47:17         <pdsch-HARQ-ACK-Codebook><dynamic/></pdsch-HARQ-ACK-Codebook>
 九  30 12:47:17     </physicalCellGroupConfig>
 九  30 12:47:17     <spCellConfig>
 九  30 12:47:17         <servCellIndex>0</servCellIndex>
 九  30 12:47:17         <rlmInSyncOutOfSyncThreshold><n1/></rlmInSyncOutOfSyncThreshold>
 九  30 12:47:17         <spCellConfigDedicated>
 九  30 12:47:17             <initialDownlinkBWP>
 九  30 12:47:17                 <pdcch-Config>
 九  30 12:47:17                     <setup>
 九  30 12:47:17                         <controlResourceSetToAddModList>
 九  30 12:47:17                             <ControlResourceSet>
 九  30 12:47:17                                 <controlResourceSetId>1</controlResourceSetId>
 九  30 12:47:17                                 <frequencyDomainResources>
 九  30 12:47:17                                     000000000111100000000000000000000000000000000
 九  30 12:47:17                                 </frequencyDomainResources>
 九  30 12:47:17                                 <duration>2</duration>
 九  30 12:47:17                                 <cce-REG-MappingType>
 九  30 12:47:17                                     <nonInterleaved></nonInterleaved>
 九  30 12:47:17                                 </cce-REG-MappingType>
 九  30 12:47:17                                 <precoderGranularity><allContiguousRBs/></precoderGranularity>
 九  30 12:47:17                                 <pdcch-DMRS-ScramblingID>1</pdcch-DMRS-ScramblingID>
 九  30 12:47:17                             </ControlResourceSet>
 九  30 12:47:17                         </controlResourceSetToAddModList>
 九  30 12:47:17                         <searchSpacesToAddModList>
 九  30 12:47:17                             <SearchSpace>
 九  30 12:47:17                                 <searchSpaceId>2</searchSpaceId>
 九  30 12:47:17                                 <controlResourceSetId>1</controlResourceSetId>
 九  30 12:47:17                                 <monitoringSlotPeriodicityAndOffset>
 九  30 12:47:17                                     <sl1></sl1>
 九  30 12:47:17                                 </monitoringSlotPeriodicityAndOffset>
 九  30 12:47:17                                 <monitoringSymbolsWithinSlot>
 九  30 12:47:17                                     10000000000000
 九  30 12:47:17                                 </monitoringSymbolsWithinSlot>
 九  30 12:47:17                                 <nrofCandidates>
 九  30 12:47:17                                     <aggregationLevel1><n8/></aggregationLevel1>
 九  30 12:47:17                                     <aggregationLevel2><n8/></aggregationLevel2>
 九  30 12:47:17                                     <aggregationLevel4><n4/></aggregationLevel4>
 九  30 12:47:17                                     <aggregationLevel8><n2/></aggregationLevel8>
 九  30 12:47:17                                     <aggregationLevel16><n1/></aggregationLevel16>
 九  30 12:47:17                                 </nrofCandidates>
 九  30 12:47:17                                 <searchSpaceType>
 九  30 12:47:17                                     <ue-Specific>
 九  30 12:47:17                                         <dci-Formats><formats0-0-And-1-0/></dci-Formats>
 九  30 12:47:17                                     </ue-Specific>
 九  30 12:47:17                                 </searchSpaceType>
 九  30 12:47:17                             </SearchSpace>
 九  30 12:47:17                         </searchSpacesToAddModList>
 九  30 12:47:17                     </setup>
 九  30 12:47:17                 </pdcch-Config>
 九  30 12:47:17                 <pdsch-Config>
 九  30 12:47:17                     <setup>
 九  30 12:47:17                         <dmrs-DownlinkForPDSCH-MappingTypeA>
 九  30 12:47:17                             <setup>
 九  30 12:47:17                                 <dmrs-AdditionalPosition><pos0/></dmrs-AdditionalPosition>
 九  30 12:47:17                             </setup>
 九  30 12:47:17                         </dmrs-DownlinkForPDSCH-MappingTypeA>
 九  30 12:47:17                         <resourceAllocation><resourceAllocationType1/></resourceAllocation>
 九  30 12:47:17                         <pdsch-TimeDomainAllocationList>
 九  30 12:47:17                             <setup>
 九  30 12:47:17                                 <PDSCH-TimeDomainResourceAllocation>
 九  30 12:47:17                                     <k0>0</k0>
 九  30 12:47:17                                     <mappingType><typeA/></mappingType>
 九  30 12:47:17                                     <startSymbolAndLength>57</startSymbolAndLength>
 九  30 12:47:17                                 </PDSCH-TimeDomainResourceAllocation>
 九  30 12:47:17                                 <PDSCH-TimeDomainResourceAllocation>
 九  30 12:47:17                                     <k0>1</k0>
 九  30 12:47:17                                     <mappingType><typeA/></mappingType>
 九  30 12:47:17                                     <startSymbolAndLength>57</startSymbolAndLength>
 九  30 12:47:17                                 </PDSCH-TimeDomainResourceAllocation>
 九  30 12:47:17                             </setup>
 九  30 12:47:17                         </pdsch-TimeDomainAllocationList>
 九  30 12:47:17                         <rbg-Size><config1/></rbg-Size>
 九  30 12:47:17                         <maxNrofCodeWordsScheduledByDCI><n1/></maxNrofCodeWordsScheduledByDCI>
 九  30 12:47:17                         <prb-BundlingType>
 九  30 12:47:17                             <staticBundling>
 九  30 12:47:17                             </staticBundling>
 九  30 12:47:17                         </prb-BundlingType>
 九  30 12:47:17                     </setup>
 九  30 12:47:17                 </pdsch-Config>
 九  30 12:47:17             </initialDownlinkBWP>
 九  30 12:47:17             <firstActiveDownlinkBWP-Id>0</firstActiveDownlinkBWP-Id>
 九  30 12:47:17             <defaultDownlinkBWP-Id>0</defaultDownlinkBWP-Id>
 九  30 12:47:17             <uplinkConfig>
 九  30 12:47:17                 <initialUplinkBWP>
 九  30 12:47:17                     <pucch-Config>
 九  30 12:47:17                         <setup>
 九  30 12:47:17                             <resourceSetToAddModList>
 九  30 12:47:17                                 <PUCCH-ResourceSet>
 九  30 12:47:17                                     <pucch-ResourceSetId>1</pucch-ResourceSetId>
 九  30 12:47:17                                     <resourceList>
 九  30 12:47:17                                         <PUCCH-ResourceId>1</PUCCH-ResourceId>
 九  30 12:47:17                                     </resourceList>
 九  30 12:47:17                                 </PUCCH-ResourceSet>
 九  30 12:47:17                             </resourceSetToAddModList>
 九  30 12:47:17                             <resourceToAddModList>
 九  30 12:47:17                                 <PUCCH-Resource>
 九  30 12:47:17                                     <pucch-ResourceId>1</pucch-ResourceId>
 九  30 12:47:17                                     <startingPRB>0</startingPRB>
 九  30 12:47:17                                     <format>
 九  30 12:47:17                                         <format1>
 九  30 12:47:17                                             <initialCyclicShift>0</initialCyclicShift>
 九  30 12:47:17                                             <nrofSymbols>4</nrofSymbols>
 九  30 12:47:17                                             <startingSymbolIndex>0</startingSymbolIndex>
 九  30 12:47:17                                             <timeDomainOCC>0</timeDomainOCC>
 九  30 12:47:17                                         </format1>
 九  30 12:47:17                                     </format>
 九  30 12:47:17                                 </PUCCH-Resource>
 九  30 12:47:17                             </resourceToAddModList>
 九  30 12:47:17                             <format1>
 九  30 12:47:17                                 <setup>
 九  30 12:47:17                                     <nrofSlots><n4/></nrofSlots>
 九  30 12:47:17                                 </setup>
 九  30 12:47:17                             </format1>
 九  30 12:47:17                             <dl-DataToUL-ACK>
 九  30 12:47:17                                 <INTEGER>1</INTEGER>
 九  30 12:47:17                                 <INTEGER>2</INTEGER>
 九  30 12:47:17                             </dl-DataToUL-ACK>
 九  30 12:47:17                         </setup>
 九  30 12:47:17                     </pucch-Config>
 九  30 12:47:17                     <pusch-Config>
 九  30 12:47:17                         <setup>
 九  30 12:47:17                             <dataScramblingIdentityPUSCH>1</dataScramblingIdentityPUSCH>
 九  30 12:47:17                             <dmrs-UplinkForPUSCH-MappingTypeA>
 九  30 12:47:17                                 <setup>
 九  30 12:47:17                                     <dmrs-AdditionalPosition><pos0/></dmrs-AdditionalPosition>
 九  30 12:47:17                                     <transformPrecodingDisabled>
 九  30 12:47:17                                         <scramblingID0>1</scramblingID0>
 九  30 12:47:17                                     </transformPrecodingDisabled>
 九  30 12:47:17                                 </setup>
 九  30 12:47:17                             </dmrs-UplinkForPUSCH-MappingTypeA>
 九  30 12:47:17                             <resourceAllocation><resourceAllocationType1/></resourceAllocation>
 九  30 12:47:17                             <pusch-TimeDomainAllocationList>
 九  30 12:47:17                                 <setup>
 九  30 12:47:17                                     <PUSCH-TimeDomainResourceAllocation>
 九  30 12:47:17                                         <k2>4</k2>
 九  30 12:47:17                                         <mappingType><typeA/></mappingType>
 九  30 12:47:17                                         <startSymbolAndLength>41</startSymbolAndLength>
 九  30 12:47:17                                     </PUSCH-TimeDomainResourceAllocation>
 九  30 12:47:17                                     <PUSCH-TimeDomainResourceAllocation>
 九  30 12:47:17                                         <k2>6</k2>
 九  30 12:47:17                                         <mappingType><typeA/></mappingType>
 九  30 12:47:17                                         <startSymbolAndLength>41</startSymbolAndLength>
 九  30 12:47:17                                     </PUSCH-TimeDomainResourceAllocation>
 九  30 12:47:17                                 </setup>
 九  30 12:47:17                             </pusch-TimeDomainAllocationList>
 九  30 12:47:17                             <transformPrecoder><disabled/></transformPrecoder>
 九  30 12:47:17                         </setup>
 九  30 12:47:17                     </pusch-Config>
 九  30 12:47:17                     <srs-Config>
 九  30 12:47:17                         <setup>
 九  30 12:47:17                             <srs-ResourceSetToAddModList>
 九  30 12:47:17                                 <SRS-ResourceSet>
 九  30 12:47:17                                     <srs-ResourceSetId>1</srs-ResourceSetId>
 九  30 12:47:17                                     <srs-ResourceIdList>
 九  30 12:47:17                                         <SRS-ResourceId>1</SRS-ResourceId>
 九  30 12:47:17                                     </srs-ResourceIdList>
 九  30 12:47:17                                     <resourceType>
 九  30 12:47:17                                         <aperiodic>
 九  30 12:47:17                                             <aperiodicSRS-ResourceTrigger>1</aperiodicSRS-ResourceTrigger>
 九  30 12:47:17                                         </aperiodic>
 九  30 12:47:17                                     </resourceType>
 九  30 12:47:17                                     <usage><codebook/></usage>
 九  30 12:47:17                                 </SRS-ResourceSet>
 九  30 12:47:17                             </srs-ResourceSetToAddModList>
 九  30 12:47:17                             <srs-ResourceToAddModList>
 九  30 12:47:17                                 <SRS-Resource>
 九  30 12:47:17                                     <srs-ResourceId>1</srs-ResourceId>
 九  30 12:47:17                                     <nrofSRS-Ports><port1/></nrofSRS-Ports>
 九  30 12:47:17                                     <transmissionComb>
 九  30 12:47:17                                         <n2>
 九  30 12:47:17                                             <combOffset-n2>0</combOffset-n2>
 九  30 12:47:17                                             <cyclicShift-n2>0</cyclicShift-n2>
 九  30 12:47:17                                         </n2>
 九  30 12:47:17                                     </transmissionComb>
 九  30 12:47:17                                     <resourceMapping>
 九  30 12:47:17                                         <startPosition>0</startPosition>
 九  30 12:47:17                                         <nrofSymbols><n1/></nrofSymbols>
 九  30 12:47:17                                         <repetitionFactor><n1/></repetitionFactor>
 九  30 12:47:17                                     </resourceMapping>
 九  30 12:47:17                                     <freqDomainPosition>0</freqDomainPosition>
 九  30 12:47:17                                     <freqDomainShift>0</freqDomainShift>
 九  30 12:47:17                                     <freqHopping>
 九  30 12:47:17                                         <c-SRS>0</c-SRS>
 九  30 12:47:17                                         <b-SRS>0</b-SRS>
 九  30 12:47:17                                         <b-hop>0</b-hop>
 九  30 12:47:17                                     </freqHopping>
 九  30 12:47:17                                     <groupOrSequenceHopping><neither/></groupOrSequenceHopping>
 九  30 12:47:17                                     <resourceType>
 九  30 12:47:17                                         <aperiodic>
 九  30 12:47:17                                         </aperiodic>
 九  30 12:47:17                                     </resourceType>
 九  30 12:47:17                                     <sequenceId>0</sequenceId>
 九  30 12:47:17                                 </SRS-Resource>
 九  30 12:47:17                             </srs-ResourceToAddModList>
 九  30 12:47:17                         </setup>
 九  30 12:47:17                     </srs-Config>
 九  30 12:47:17                 </initialUplinkBWP>
 九  30 12:47:17                 <firstActiveUplinkBWP-Id>0</firstActiveUplinkBWP-Id>
 九  30 12:47:17                 <pusch-ServingCellConfig>
 九  30 12:47:17                     <setup>
 九  30 12:47:17                         <ext1>
 九  30 12:47:17                             <maxMIMO-Layers>1</maxMIMO-Layers>
 九  30 12:47:17                             <processingType2Enabled><false/></processingType2Enabled>
 九  30 12:47:17                         </ext1>
 九  30 12:47:17                     </setup>
 九  30 12:47:17                 </pusch-ServingCellConfig>
 九  30 12:47:17             </uplinkConfig>
 九  30 12:47:17             <pdsch-ServingCellConfig>
 九  30 12:47:17                 <setup>
 九  30 12:47:17                     <nrofHARQ-ProcessesForPDSCH><n16/></nrofHARQ-ProcessesForPDSCH>
 九  30 12:47:17                 </setup>
 九  30 12:47:17             </pdsch-ServingCellConfig>
 九  30 12:47:17             <tag-Id>0</tag-Id>
 九  30 12:47:17         </spCellConfigDedicated>
 九  30 12:47:17     </spCellConfig>
 九  30 12:47:17 </CellGroupConfig>
```

## InitialULRRCMessageTransfer

```
<initiatingMessage>
 九  30 12:47:17         <procedureCode>11</procedureCode>
 九  30 12:47:17         <criticality><ignore/></criticality>
 九  30 12:47:17         <value>
 九  30 12:47:17             <InitialULRRCMessageTransfer>
 九  30 12:47:17                 <protocolIEs>
 九  30 12:47:17                     <InitialULRRCMessageTransferIEs>
 九  30 12:47:17                         <id>41</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <GNB-DU-UE-F1AP-ID>1</GNB-DU-UE-F1AP-ID>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </InitialULRRCMessageTransferIEs>
 九  30 12:47:17                     <InitialULRRCMessageTransferIEs>
 九  30 12:47:17                         <id>111</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <NRCGI>
 九  30 12:47:17                                 <pLMN-Identity>00 F1 10</pLMN-Identity>
 九  30 12:47:17                                 <nRCellIdentity>
 九  30 12:47:17                                     000000000000000000000000000000000001
 九  30 12:47:17                                 </nRCellIdentity>
 九  30 12:47:17                             </NRCGI>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </InitialULRRCMessageTransferIEs>
 九  30 12:47:17                     <InitialULRRCMessageTransferIEs>
 九  30 12:47:17                         <id>95</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <C-RNTI>100</C-RNTI>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </InitialULRRCMessageTransferIEs>
 九  30 12:47:17                     <InitialULRRCMessageTransferIEs>
 九  30 12:47:17                         <id>50</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <RRCContainer>17 04 25 0F B8 E6</RRCContainer>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </InitialULRRCMessageTransferIEs>
 九  30 12:47:17                     <InitialULRRCMessageTransferIEs>
 九  30 12:47:17                         <id>128</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <DUtoCURRCContainer>
 九  30 12:47:17                                 5C 00 B0 01 10 0A EC 81 D0 61 EA 00 7C 22 A0 95 
 九  30 12:47:17                                 07 B8 C0 20 7A 98 04 B2 03 2A 00 22 00 F0 00 00 
 九  30 12:47:17                                 00 07 00 01 0D C2 10 80 03 F8 8C 90 81 01 20 31 
 九  30 12:47:17                                 80 73 04 E4 00 4C D5 50 20 20 02 00 02 00 20 00 
 九  30 12:47:17                                 22 24 4A A1 10 00 32 42 00 01 63 10 A6 31 4E 50 
 九  30 12:47:17                                 20 20 08 04 00 08 00 00 00 00 00 00 01 80 50 07 
 九  30 12:47:17                                 02 2A 00
 九  30 12:47:17                             </DUtoCURRCContainer>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </InitialULRRCMessageTransferIEs>
 九  30 12:47:17                 </protocolIEs>
 九  30 12:47:17             </InitialULRRCMessageTransfer>
 九  30 12:47:17         </value>
 九  30 12:47:17     </initiatingMessage>
 九  30 12:47:17 </F1AP-PDU>
```

## DLRRCMessageTransfer  (at OAI CU send)

```jsx
<F1AP-PDU>
    <initiatingMessage>
        <procedureCode>12</procedureCode>
        <criticality><ignore/></criticality>
        <value>
            <DLRRCMessageTransfer>
                <protocolIEs>
                    <DLRRCMessageTransferIEs>
                        <id>40</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-CU-UE-F1AP-ID>1</GNB-CU-UE-F1AP-ID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>41</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-DU-UE-F1AP-ID>1</GNB-DU-UE-F1AP-ID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>64</id>
                        <criticality><reject/></criticality>
                        <value>
                            <SRBID>0</SRBID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>50</id>
                        <criticality><reject/></criticality>
                        <value>
                            <RRCContainer>
                                28 40 03 1A E0 05 80 08 80 57 64 0E 83 0F 50 03 
                                E1 15 04 A8 3D C6 01 03 D4 C0 25 90 19 50 01 10 
                                07 80 00 00 00 38 00 08 6E 10 84 00 1F C4 64 84 
                                08 09 01 8C 03 98 27 20 02 66 AA 81 01 00 10 00 
                                10 01 00 01 11 22 55 08 80 01 92 10 00 0B 18 85 
                                31 8A 72 81 01 00 40 20 00 40 00 00 00 00 00 00 
                                0C 02 80 38 11 50 00
                            </RRCContainer>
                        </value>
                    </DLRRCMessageTransferIEs>
                </protocolIEs>
            </DLRRCMessageTransfer>
        </value>
    </initiatingMessage>
</F1AP-PDU>
```

## DLRRCMessageTransfer (at OSC DU receive)

```
<F1AP-PDU>
 九  30 12:47:17     <initiatingMessage>
 九  30 12:47:17         <procedureCode>12</procedureCode>
 九  30 12:47:17         <criticality><ignore/></criticality>
 九  30 12:47:17         <value>
 九  30 12:47:17             <DLRRCMessageTransfer>
 九  30 12:47:17                 <protocolIEs>
 九  30 12:47:17                     <DLRRCMessageTransferIEs>
 九  30 12:47:17                         <id>40</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <GNB-CU-UE-F1AP-ID>1</GNB-CU-UE-F1AP-ID>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </DLRRCMessageTransferIEs>
 九  30 12:47:17                     <DLRRCMessageTransferIEs>
 九  30 12:47:17                         <id>41</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <GNB-DU-UE-F1AP-ID>1</GNB-DU-UE-F1AP-ID>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </DLRRCMessageTransferIEs>
 九  30 12:47:17                     <DLRRCMessageTransferIEs>
 九  30 12:47:17                         <id>64</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <SRBID>0</SRBID>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </DLRRCMessageTransferIEs>
 九  30 12:47:17                     <DLRRCMessageTransferIEs>
 九  30 12:47:17                         <id>50</id>
 九  30 12:47:17                         <criticality><reject/></criticality>
 九  30 12:47:17                         <value>
 九  30 12:47:17                             <RRCContainer>
 九  30 12:47:17                                 28 40 03 1A E0 05 80 08 80 57 64 0E 83 0F 50 03 
 九  30 12:47:17                                 E1 15 04 A8 3D C6 01 03 D4 C0 25 90 19 50 01 10 
 九  30 12:47:17                                 07 80 00 00 00 38 00 08 6E 10 84 00 1F C4 64 84 
 九  30 12:47:17                                 08 09 01 8C 03 98 27 20 02 66 AA 81 01 00 10 00 
 九  30 12:47:17                                 10 01 00 01 11 22 55 08 80 01 92 10 00 0B 18 85 
 九  30 12:47:17                                 31 8A 72 81 01 00 40 20 00 40 00 00 00 00 00 00 
 九  30 12:47:17                                 0C 02 80 38 11 50 00
 九  30 12:47:17                             </RRCContainer>
 九  30 12:47:17                         </value>
 九  30 12:47:17                     </DLRRCMessageTransferIEs>
 九  30 12:47:17                 </protocolIEs>
 九  30 12:47:17             </DLRRCMessageTransfer>
 九  30 12:47:17         </value>
 九  30 12:47:17     </initiatingMessage>
 九  30 12:47:17 </F1AP-PDU>
```

# OAI VNF + OAI PNF

## UL-CCCH-Message (rrcSetupRequest)

```
 十  05 00:50:13 <UL-CCCH-Message>
 十  05 00:50:13     <message>
 十  05 00:50:13         <c1>
 十  05 00:50:13             <rrcSetupRequest>
 十  05 00:50:13                 <rrcSetupRequest>
 十  05 00:50:13                     <ue-Identity>
 十  05 00:50:13                         <randomValue>
 十  05 00:50:13                             010011000000111110110011000001100001001
 十  05 00:50:13                         </randomValue>
 十  05 00:50:13                     </ue-Identity>
 十  05 00:50:13                     <establishmentCause><mo-Signalling/></establishmentCause>
 十  05 00:50:13                     <spare>
 十  05 00:50:13                         0
 十  05 00:50:13                     </spare>
 十  05 00:50:13                 </rrcSetupRequest>
 十  05 00:50:13             </rrcSetupRequest>
 十  05 00:50:13         </c1>
 十  05 00:50:13     </message>
 十  05 00:50:13 </UL-CCCH-Message>
```

## DL-CCCH-Message (masterCellGroup)

```
 九  30 16:52:26 [0m<DL-CCCH-Message>
 九  30 16:52:26     <message>
 九  30 16:52:26         <c1>
 九  30 16:52:26             <rrcSetup>
 九  30 16:52:26                 <rrc-TransactionIdentifier>1</rrc-TransactionIdentifier>
 九  30 16:52:26                 <criticalExtensions>
 九  30 16:52:26                     <rrcSetup>
 九  30 16:52:26                         <radioBearerConfig>
 九  30 16:52:26                             <srb-ToAddModList>
 九  30 16:52:26                                 <SRB-ToAddMod>
 九  30 16:52:26                                     <srb-Identity>1</srb-Identity>
 九  30 16:52:26                                 </SRB-ToAddMod>
 九  30 16:52:26                             </srb-ToAddModList>
 九  30 16:52:26                         </radioBearerConfig>
 九  30 16:52:26                         <masterCellGroup>
 九  30 16:52:26                             5C 00 B0 01 11 7A EC 70 10 61 F0 00 7C 02 04 68 
 九  30 16:52:26                             3C 08 00 04 12 09 81 95 00 81 FF FF 00 00 00 01 
 九  30 16:52:26                             00 00 37 14 42 00 00 80 16 50 00 04 82 00 00 44 
 九  30 16:52:26                             09 34 0D 54 93 50 00 04 00 80 80 01 00 1A 02 00 
 九  30 16:52:26                             27 6C 92 30 1D C0 76 78 9A BC D0 00 00 29 A1 00 
 九  30 16:52:26                             20 00 25 80 C2 0C 02 C9 C1 82 1C 00 31 28 1C 00 
 九  30 16:52:26                             00 20 5E F4 01 00 01 00 00 06 40 01 40 03 2A 0A 
 九  30 16:52:26                             00 C4 40 15 00 00 00 00 01 42 00 80 00 14 50 80 
 九  30 16:52:26                             80 02 C6 00
 九  30 16:52:26                         </masterCellGroup>
 九  30 16:52:26                     </rrcSetup>
 九  30 16:52:26                 </criticalExtensions>
 九  30 16:52:26             </rrcSetup>
 九  30 16:52:26         </c1>
 九  30 16:52:26     </message>
 九  30 16:52:26 </DL-CCCH-Message>
```

## MSG4 TX_Data (OAI VNF)

```jsx
 十  04 23:32:39 [0m1728055959.499805 [NR_MAC]   UE fe23 Generate msg4: feedback at  185.18, payload 149 bytes, next state WAIT_Msg4_ACK
 十  04 23:32:39 [0m1728055959.499828 [NR_MAC]   Direct Value:
 十  04 23:32:39 [0m1728055959.499831 [NR_MAC]   b9a113e
 十  04 23:32:39 [0m1728055959.499833 [NR_MAC]   86a9a7
 十  04 23:32:39 [0m1728055959.499834 [NR_MAC]   4402889
 十  04 23:32:39 [0m1728055959.499835 [NR_MAC]   5e02204
 十  04 23:32:39 [0m1728055959.499837 [NR_MAC]   d78b0880
 十  04 23:32:39 [0m1728055959.499838 [NR_MAC]   f838063
 十  04 23:32:39 [0m1728055959.499839 [NR_MAC]   10e00380
 十  04 23:32:39 [0m1728055959.499841 [NR_MAC]   40e04123
 十  04 23:32:39 [0m1728055959.499842 [NR_MAC]   4c902000
 十  04 23:32:39 [0m1728055959.499843 [NR_MAC]   f04a80c
 十  04 23:32:39 [0m1728055959.499845 [NR_MAC]   f8ff
 十  04 23:32:39 [0m1728055959.499846 [NR_MAC]   1000800
 十  04 23:32:39 [0m1728055959.499847 [NR_MAC]   10a2b8
 十  04 23:32:39 [0m1728055959.499849 [NR_MAC]   80b20004
 十  04 23:32:39 [0m1728055959.499850 [NR_MAC]   102400
 十  04 23:32:39 [0m1728055959.499851 [NR_MAC]   a0492002
 十  04 23:32:39 [0m1728055959.499853 [NR_MAC]   809aa46a
 十  04 23:32:39 [0m1728055959.499854 [NR_MAC]   4042000
 十  04 23:32:39 [0m1728055959.499855 [NR_MAC]   d0000800
 十  04 23:32:39 [0m1728055959.499856 [NR_MAC]   643b0110
 十  04 23:32:39 [0m1728055959.499858 [NR_MAC]   3ee8091
 十  04 23:32:39 [0m1728055959.499859 [NR_MAC]   e6d5c4b3
 十  04 23:32:39 [0m1728055959.499860 [NR_MAC]   4d010080
 十  04 23:32:39 [0m1728055959.499862 [NR_MAC]   1000108
 十  04 23:32:39 [0m1728055959.499864 [NR_MAC]   6010062c
 十  04 23:32:39 [0m1728055959.499866 [NR_MAC]   100c4e16
 十  04 23:32:39 [0m1728055959.499867 [NR_MAC]   408901e0
 十  04 23:32:39 [0m1728055959.499868 [NR_MAC]   20100e0
 十  04 23:32:39 [0m1728055959.499869 [NR_MAC]   8a0f7
 十  04 23:32:39 [0m1728055959.499871 [NR_MAC]   32000008
 十  04 23:32:39 [0m1728055959.499872 [NR_MAC]   19000a00
 十  04 23:32:39 [0m1728055959.499874 [NR_MAC]   22065050
 十  04 23:32:39 [0m1728055959.499875 [NR_MAC]   a800
 十  04 23:32:39 [0m1728055959.499876 [NR_MAC]   100a0000
 十  04 23:32:39 [0m1728055959.499877 [NR_MAC]   a2000004
 十  04 23:32:39 [0m1728055959.499879 [NR_MAC]   16000484
 十  04 23:32:39 [0m1728055959.499880 [NR_MAC]   3f0030
 十  04 23:32:39 [0m1728055959.499881 [NR_MAC]   00
```

# Tony’s CU + OSC DU

```jsx
<DL-CCCH-Message>
    <message>
        <c1>
            <rrcSetup>
                <rrc-TransactionIdentifier>1</rrc-TransactionIdentifier>
                <criticalExtensions>
                    <rrcSetup>
                        <radioBearerConfig>
                            <srb-ToAddModList>
                                <SRB-ToAddMod>
                                    <srb-Identity>1</srb-Identity>
                                </SRB-ToAddMod>
                            </srb-ToAddModList>
                        </radioBearerConfig>
                        <masterCellGroup>
                            5C 00 B0 01 10 0A EC 81 D0 61 EA 00 7C 22 A0 95 
                            07 B8 C0 20 7A 98 09 64 06 54 00 44 01 E0 00 00 
                            00 0E 00 02 1B 84 21 00 07 F1 19 21 02 02 40 63 
                            01 0A 0A 10 00 99 AA A0 40 40 04 00 04 00 40 00 
                            44 48 95 42 20 00 64 84 00 02 C6 22 14 54 2C A0 
                            40 40 10 08 00 10 0C 00 00 00 00 00 06 00 40 70 
                            22 A0
                        </masterCellGroup>
                    </rrcSetup>
                </criticalExtensions>
            </rrcSetup>
        </c1>
    </message>
</DL-CCCH-Message>
```

## CellGroupConfigRrc

```jsx
<CellGroupConfigRrc>
    <cellGroupId>0</cellGroupId>
    <rlc-BearerToAddModList>
        <RLC-BearerConfig>
            <logicalChannelIdentity>1</logicalChannelIdentity>
            <servedRadioBearer>
                <srb-Identity>1</srb-Identity>
            </servedRadioBearer>
            <rlc-Config>
                <am>
                    <ul-AM-RLC>
                        <sn-FieldLength><size12/></sn-FieldLength>
                        <t-PollRetransmit><ms45/></t-PollRetransmit>
                        <pollPDU><p4/></pollPDU>
                        <pollByte><infinity/></pollByte>
                        <maxRetxThreshold><t8/></maxRetxThreshold>
                    </ul-AM-RLC>
                    <dl-AM-RLC>
                        <sn-FieldLength><size12/></sn-FieldLength>
                        <t-Reassembly><ms40/></t-Reassembly>
                        <t-StatusProhibit><ms35/></t-StatusProhibit>
                    </dl-AM-RLC>
                </am>
            </rlc-Config>
            <mac-LogicalChannelConfig>
                <ul-SpecificParameters>
                    <priority>1</priority>
                    <prioritisedBitRate><infinity/></prioritisedBitRate>
                    <bucketSizeDuration><ms150/></bucketSizeDuration>
                    <logicalChannelGroup>0</logicalChannelGroup>
                    <schedulingRequestID>0</schedulingRequestID>
                    <logicalChannelSR-Mask><false/></logicalChannelSR-Mask>
                    <logicalChannelSR-DelayTimerApplied><false/></logicalChannelSR-DelayTimerApplied>
                </ul-SpecificParameters>
            </mac-LogicalChannelConfig>
        </RLC-BearerConfig>
    </rlc-BearerToAddModList>
    <mac-CellGroupConfig>
        <schedulingRequestConfig>
            <schedulingRequestToAddModList>
                <SchedulingRequestToAddMod>
                    <schedulingRequestId>0</schedulingRequestId>
                    <sr-ProhibitTimer><ms32/></sr-ProhibitTimer>
                    <sr-TransMax><n16/></sr-TransMax>
                </SchedulingRequestToAddMod>
            </schedulingRequestToAddModList>
        </schedulingRequestConfig>
        <bsr-Config>
            <periodicBSR-Timer><sf10/></periodicBSR-Timer>
            <retxBSR-Timer><sf320/></retxBSR-Timer>
        </bsr-Config>
        <tag-Config>
            <tag-ToAddModList>
                <TAG>
                    <tag-Id>0</tag-Id>
                    <timeAlignmentTimer><infinity/></timeAlignmentTimer>
                </TAG>
            </tag-ToAddModList>
        </tag-Config>
        <phr-Config>
            <setup>
                <phr-PeriodicTimer><infinity/></phr-PeriodicTimer>
                <phr-ProhibitTimer>
===================== DL Throughput Per UE==============================<sf0/></phr-ProhibitTimer>
                <phr-Tx-PowerFactorChange><infinity/></phr-Tx-PowerFactorChange>
                <multiplePHR><false/></multiplePHR>
                <dummy><false/></dummy>
                <phr-Type2OtherCell><false/></phr-Type2OtherCell>
                <phr-ModeOtherCG><real/></phr-ModeOtherCG>
            
Number of UEs : 0</setup>
        </phr-Config>
        <skipUplinkTxDynamic><false/></skipUplinkTxDynamic>
    </mac-CellGroupConfig>
    <physicalCellGroupConfig>
        <p-NR-FR1>0</p-NR-FR1>
==================================================================
        <pdsch-HARQ-ACK-Codebook><dynamic/></pdsch-HARQ-ACK-Codebook>
    </physicalCellGroupConfig>
    <spCellConfig>
        <servCellIndex>0</servCellIndex>
        <rlmInSyncOutOfSyncThreshold><n1/></rlmInSyncOutOfSyncThreshold>
        <spCellConfigDedicated>
            <initialDownlinkBWP>
                <pdcch-Config>
                    <setup>
                        <controlResourceSetToAddModList>
                            <ControlResourceSet>
                                <controlResourceSetId>1</controlResourceSetId>
                                <frequencyDomainResources>
                                    000000000111100000000000000000000000000000000
                                </frequencyDomainResources>
                                <duration>2</duration>
                                <cce-REG-MappingType>
                                    <nonInterleaved></nonInterleaved>
                                </cce-REG-MappingType>
                                <precoderGranularity><allContiguousRBs/></precoderGranularity>
                                <pdcch-DMRS-ScramblingID>1</pdcch-DMRS-ScramblingID>
                            </ControlResourceSet>
                        </controlResourceSetToAddModList>
                        <searchSpacesToAddModList>
                            <SearchSpace>
                                <searchSpaceId>2</searchSpaceId>
                                <controlResourceSetId>1</controlResourceSetId>
                                <monitoringSlotPeriodicityAndOffset>
                                    <sl1></sl1>
                                </monitoringSlotPeriodicityAndOffset>
                                <monitoringSymbolsWithinSlot>
                                    10000000000000
                                </monitoringSymbolsWithinSlot>
                                <nrofCandidates>
                                    <aggregationLevel1><n8/></aggregationLevel1>
                                    <aggregationLevel2><n8/></aggregationLevel2>
                                    <aggregationLevel4><n4/></aggregationLevel4>
                                    <aggregationLevel8><n2/></aggregationLevel8>
                                    <aggregationLevel16><n1/></aggregationLevel16>
                                </nrofCandidates>
                                <searchSpaceType>
                                    <ue-Specific>
                                        <dci-Formats><formats0-0-And-1-0/></dci-Formats>
                                    </ue-Specific>
                                </searchSpaceType>
                            </SearchSpace>
                        </searchSpacesToAddModList>
                    </setup>
                </pdcch-Config>
                <pdsch-Config>
                    <setup>
                        <dmrs-DownlinkForPDSCH-MappingTypeA>
                            <setup>
                                <dmrs-AdditionalPosition><pos0/></dmrs-AdditionalPosition>
                            </setup>
                        </dmrs-DownlinkForPDSCH-MappingTypeA>
                        <resourceAllocation><resourceAllocationType1/></resourceAllocation>
                        <pdsch-TimeDomainAllocationList>
                            <setup>
                                <PDSCH-TimeDomainResourceAllocation>
                                    <k0>0</k0>
                                    <mappingType><typeA/></mappingType>
                                    <startSymbolAndLength>66</startSymbolAndLength>
                                </PDSCH-TimeDomainResourceAllocation>
                                <PDSCH-TimeDomainResourceAllocation>
                                    <k0>1</k0>
                                    <mappingType><typeA/></mappingType>
                                    <startSymbolAndLength>66</startSymbolAndLength>
                                </PDSCH-TimeDomainResourceAllocation>
                            </setup>
                        </pdsch-TimeDomainAllocationList>
                        <rbg-Size><config1/></rbg-Size>
                        <maxNrofCodeWordsScheduledByDCI><n1/></maxNrofCodeWordsScheduledByDCI>
                        <prb-BundlingType>
                            <staticBundling>
                            </staticBundling>
                        </prb-BundlingType>
                    </setup>
                </pdsch-Config>
            </initialDownlinkBWP>
            <firstActiveDownlinkBWP-Id>0</firstActiveDownlinkBWP-Id>
            <defaultDownlinkBWP-Id>0</defaultDownlinkBWP-Id>
            <uplinkConfig>
                <initialUplinkBWP>
===================== DL Throughput Per UE==============================
                    <pucch-Config>
                        <setup>
                            <resourceSetToAddModList>
                                <PUCCH-ResourceSet>
                                    <pucch-ResourceSetId>1</pucch-ResourceSetId>
Number of UEs : 0
                                    <resourceList>
                                        <PUCCH-ResourceId>1</PUCCH-ResourceId>
                                    </resourceList>
                                </PUCCH-ResourceSet>
                            </resourceSetToAddModList>
==================================================================
                            <resourceToAddModList>
                                <PUCCH-Resource>
                                    <pucch-ResourceId>1</pucch-ResourceId>
                                    <startingPRB>0</startingPRB>
                                    <format>
                                        <format1>
                                            <initialCyclicShift>0</initialCyclicShift>
                                            <nrofSymbols>4</nrofSymbols>
                                            <startingSymbolIndex>0</startingSymbolIndex>
                                            <timeDomainOCC>0</timeDomainOCC>
                                        </format1>
                                    </format>
                                </PUCCH-Resource>
                            </resourceToAddModList>
                            <format1>
                                <setup>
                                    <nrofSlots><n4/></nrofSlots>
                                </setup>
                            </format1>
                            <dl-DataToUL-ACK>
                                <INTEGER>1</INTEGER>
                                <INTEGER>2</INTEGER>
                            </dl-DataToUL-ACK>
                        </setup>
                    </pucch-Config>
                    <pusch-Config>
                        <setup>
                            <dataScramblingIdentityPUSCH>1</dataScramblingIdentityPUSCH>
                            <dmrs-UplinkForPUSCH-MappingTypeA>
                                <setup>
                                    <dmrs-AdditionalPosition><pos0/></dmrs-AdditionalPosition>
                                    <transformPrecodingDisabled>
                                        <scramblingID0>1</scramblingID0>
                                    </transformPrecodingDisabled>
                                </setup>
                            </dmrs-UplinkForPUSCH-MappingTypeA>
                            <resourceAllocation><resourceAllocationType1/></resourceAllocation>
                            <pusch-TimeDomainAllocationList>
                                <setup>
                                    <PUSCH-TimeDomainResourceAllocation>
                                        <k2>4</k2>
                                        <mappingType><typeA/></mappingType>
                                        <startSymbolAndLength>66</startSymbolAndLength>
                                    </PUSCH-TimeDomainResourceAllocation>
                                    <PUSCH-TimeDomainResourceAllocation>
                                        <k2>5</k2>
                                        <mappingType><typeA/></mappingType>
                                        <startSymbolAndLength>66</startSymbolAndLength>
                                    </PUSCH-TimeDomainResourceAllocation>
                                </setup>
                            </pusch-TimeDomainAllocationList>
                            <transformPrecoder><disabled/></transformPrecoder>
                        </setup>
                    </pusch-Config>
                    <srs-Config>
                        <setup>
                            <srs-ResourceSetToAddModList>
                                <SRS-ResourceSet>
                                    <srs-ResourceSetId>1</srs-ResourceSetId>
                                    <srs-ResourceIdList>
                                        <SRS-ResourceId>1</SRS-ResourceId>
                                    </srs-ResourceIdList>
                                    <resourceType>
                                        <aperiodic>
                                            <aperiodicSRS-ResourceTrigger>1</aperiodicSRS-ResourceTrigger>
                                        </aperiodic>
                                    </resourceType>
                                    <usage><codebook/></usage>
                                </SRS-ResourceSet>
                            </srs-ResourceSetToAddModList>
                            <srs-ResourceToAddModList>
                                <SRS-Resource>
                                    <srs-ResourceId>1</srs-ResourceId>
                                    <nrofSRS-Ports><port1/></nrofSRS-Ports>
                                    <transmissionComb>
                                        <n2>
                                            <combOffset-n2>0</combOffset-n2>
                                            <cyclicShift-n2>0</cyclicShift-n2>

DEBUG  -->  LWR_MAC: MIB PDU 50000600                                        </n2>
                                    </transmissionComb>
                                    <resourceMapping>
                                        <startPosition>3</startPosition>
                                        <nrofSymbols><n1/></nrofSymbols>
                                [1;31m        <repetitionFactor><n1/></repetitionFactor>
                                    </resourceMapping>
                                    <freqDomainPosition>0</freqDomainPosition>
                                    <freqDomainShift>0</freqDomainShift
DEBUG  -->  LWR_MAC: MIB sent..>
                                    <freqHopping>
                                        <c-SRS>0</c-SRS>
                                        <b-SRS>0</b-SRS>
                        [0m                <b-hop>0</b-hop>
                                    </freqHopping>
                                    <groupOrSequenceHopping><neither/></groupOrSequenceHopping>
                                    <resourceType>
                                        <aperiodic>
                                        </aperiodic>
                                    </resourceType>
                                    <[1;34msequenceId>0</sequenceId>
                                </SRS-Resource>
                            </srs-ResourceToAddModList>
                        </setup>
                    </srs-Config>
                </initialUplinkBWP>
                <firstActiveUplinkBWP-Id>0</firstActiveUplinkBWP-Id>
                
DEBUG  -->  LWR_MAC: SIB1 sent...<pusch-ServingCellConfig>
                    <setup>
                        <ext1>
                            <maxMIMO-Layers>1</maxMIMO-Layers>
                            <processingType2Enabled><false/></processingType2Enabled>
            [0m            </ext1>
                    </setup>
                </pusch-ServingCellConfig>
            </uplinkConfig>
            <pdsch-ServingCellConfig>
                <setup>
                    <nrofHARQ-ProcessesForPDSCH><n16/></nrofHARQ-ProcessesForPDSCH>
                </setup>
            </pdsch-ServingCellConfig>
            <tag-Id>0</tag-Id>
        </spCellConfigDedicated>
    </spCellConfig>
</CellGroupConfigRrc>
```

## **InitialULRRCMessageTransfer**

```jsx
<initiatingMessage>
        <procedureCode>11</procedureCode>
        <criticality><ignore/></criticality>
        <value>
            <InitialULRRCMessageTransfer>
                <protocolIEs>
                    <InitialULRRCMessageTransferIEs>
                        <id>41</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-DU-UE-F1AP-ID>1</GNB-DU-UE-F1AP-ID>
                        </value>
                    </InitialULRRCMessageTransferIEs>
                    <InitialULRRCMessageTransferIEs>
                        <id>111</id>
                        <criticality><reject/></criticality>
                        <value>
                            <NRCGI>
                                <pLMN-Identity>13 F1 84</pLMN-Identity>
                                <nRCellIdentity>
                                    000000000000000000000000000000000001
                                </nRCellIdentity>
                            </NRCGI>
                        </value>
                    </InitialULRRCMessageTransferIEs>
                    <InitialULRRCMessageTransferIEs>
                        <id>95</id>
                        <criticality><reject/></criticality>
                        <value>
                            <C-RNTI>100</C-RNTI>
                        </value>
                    </InitialULRRCMessageTransferIEs>
                    <InitialULRRCMessageTransferIEs>
                        <id>50</id>
                        <criticality><reject/></criticality>
                        <value>
                            <RRCContainer>10 00 00 00 00 67</RRCContainer>
                        </value>
                    </InitialULRRCMessageTransferIEs>
                    <InitialULRRCMessageTransferIEs>
                        <id>128</id>
                        <criticality><reject/></criticality>
                        <value>
                            <DUtoCURRCContainer>
                                5C 00 B0 01 10 0A EC 81 D0 61 EA 00 7C 22 A0 95 
                                07 B8 C0 20 7A 98 09 64 06 54 00 44 01 E0 00 00 
                                00 0E 00 02 1B 84 21 00 07 F1 19 21 02 02 40 63 
                                01 0A 0A 10 00 99 AA A0 40 40 04 00 04 00 40 00 
                                44 48 95 42 20 00 64 84 00 02 C6 22 14 54 2C A0 
                                40 40 10 08 00 10 0C 00 00 00 00 00 06 00 40 70 
                                22 A0
                            </DUtoCURRCContainer>
                        </value>
                    </InitialULRRCMessageTransferIEs>
                </protocolIEs>
            </InitialULRRCMessageTransfer>
        </value>
    </initiatingMessage>
</F1AP-PDU>
```

## DLRRCMessageTransfer

```jsx
<F1AP-PDU>
    <initiatingMessage>
        <procedureCode>12</procedureCode>
        <criticality><ignore/></criticality>
        <value>
            <DLRRCMessageTransfer>
                <protocolIEs>
                    <DLRRCMessageTransferIEs>
                        <id>40</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-CU-UE-F1AP-ID>1</GNB-CU-UE-F1AP-ID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>41</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-DU-UE-F1AP-ID>1</GNB-DU-UE-F1AP-ID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>64</id>
                        <criticality><reject/></criticality>
                        <value>
                            <SRBID>0</SRBID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>50</id>
                        <criticality><reject/></criticality>
                        <value>
                            <RRCContainer>
                                28 40 03 12 E0 05 80 08 80 57 64 0E 83 0F 50 03 
                                E1 15 04 A8 3D C6 01 03 D4 C0 4B 20 32 A0 02 20 
                                0F 00 00 00 00 70 00 10 DC 21 08 00 3F 88 C9 08 
                                10 12 03 18 08 50 50 80 04 CD 55 02 02 00 20 00 
                                20 02 00 02 22 44 AA 11 00 03 24 20 00 16 31 10 
                                A2 A1 65 02 02 00 80 40 00 80 60 00 00 00 00 00 
                                30 02 03 81 15 00
                            </RRCContainer>
                        </value>
                    </DLRRCMessageTransferIEs>
                </protocolIEs>
            </DLRRCMessageTransfer>
        </value>
    </initiatingMessage>
</F1AP-PDU>

```

## **ULRRCMessageTransfer**

```jsx
<F1AP-PDU>
    <initiatingMessage>
        <procedureCode>13</procedureCode>
        <criticality><ignore/></criticality>
        <value>
            <ULRRCMessageTransfer>
                <protocolIEs>
                    <ULRRCMessageTransferIEs>
                        <id>40</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-CU-UE-F1AP-ID>1</GNB-CU-UE-F1AP-ID>
                        </value>
                    </ULRRCMessageTransferIEs>
                    <ULRRCMessageTransferIEs>
                        <id>41</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-DU-UE-F1AP-ID>1</GNB-DU-UE-F1AP-ID>
                        </value>
                    </ULRRCMessageTransferIEs>
                    <ULRRCMessageTransferIEs>
                        <id>64</id>
                        <criticality><reject/></criticality>
                        <value>
                            <SRBID>1</SRBID>
                        </value>
                    </ULRRCMessageTransferIEs>
                    <ULRRCMessageTransferIEs>
                        <id>50</id>
                        <criticality><reject/></criticality>
                        <value>
                            <RRCContainer>
                                00 01 3A 0E 3F 00 CA 95 E9 19 41 3F 00 2B 96 88 
                                06 D7 16 C6 8B EA AE 45 D1 01 FD 34 D4 FD D5 71 
                                00 00 00 00 00
                            </RRCContainer>
                        </value>
                    </ULRRCMessageTransferIEs>
                </protocolIEs>
            </ULRRCMessageTransfer>
        </value>
    </initiatingMessage>
</F1AP-PDU>
```

## **DLRRCMessageTransfer**

```jsx
DEBUG   -->  SCTP : Forwarding received message to duApp
INFO  -->  F1AP : Received F1AP message buffer
DEBUG   -->  F1AP : Received flat buffer to be decoded : 0c403500402802010290201040012003201d1c012effffff826fffffffc063ffffffa4723b0fffffffc0bffffffa04005c1c1c6ffffffc020400000
<F1AP-PDU>
    <initiatingMessage>
        <procedureCode>12</procedureCode>
        <criticality><ignore/></criticality>
        <value>
            <DLRRCMessageTransfer>
                <protocolIEs>
                    <DLRRCMessageTransferIEs>
                        <id>40</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-CU-UE-F1AP-ID>1</GNB-CU-UE-F1AP-ID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>41</id>
                        <criticality><reject/></criticality>
                        <value>
                            <GNB-DU-UE-F1AP-ID>1</GNB-DU-UE-F1AP-ID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>64</id>
                        <criticality><reject/></criticality>
                        <value>
                            <SRBID>1</SRBID>
                        </value>
                    </DLRRCMessageTransferIEs>
                    <DLRRCMessageTransferIEs>
                        <id>50</id>
                        <criticality><reject/></criticality>
                        <value>
                            <RRCContainer>
                                00 01 2E 82 6F C0 63 A4 72 3B 00 0F C0 0B A0 40 
                                00 5C 1C 1C 06 C0 20 40 00 00 00 00
                            </RRCContainer>
                        </value>
                    </DLRRCMessageTransferIEs>
                </protocolIEs>
            </DLRRCMessageTransfer>
        </value>
    </initiatingMessage>
</F1AP-PDU>

```