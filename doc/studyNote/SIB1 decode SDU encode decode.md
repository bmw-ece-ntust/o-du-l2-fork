# SIB1 decode SDU encode/decode

Start Date: 2024/06/25
Summary: Decoding and encoding processes for SIB1 in NR-BCCH-DL-SCH message handling.
Status: Reject
Assign: Ming 咚咚 [銘鴻], 陳奕全

```c
    case NR_BCCH_DL_SCH:
      if (pdu_len>0) {
        LOG_T(NR_RRC, "[UE %d] Received SDU for NR-BCCH-DL-SCH on SRB %u from gNB %d\n", module_id, channel & RAB_OFFSET,
              gNB_index);

        MessageDef *message_p;
        int msg_sdu_size = BCCH_SDU_SIZE;

        if (pdu_len > msg_sdu_size) {
          LOG_E(NR_RRC, "SDU larger than NR-BCCH-DL-SCH SDU buffer size (%d, %d)", sdu_size, msg_sdu_size);
          sdu_size = msg_sdu_size;
        } else {
          sdu_size = pdu_len;
        }

        message_p = itti_alloc_new_message(TASK_MAC_UE, 0, NR_RRC_MAC_BCCH_DATA_IND);
        memset(NR_RRC_MAC_BCCH_DATA_IND (message_p).sdu, 0, BCCH_SDU_SIZE);
        memcpy(NR_RRC_MAC_BCCH_DATA_IND (message_p).sdu, pduP, sdu_size);
        NR_RRC_MAC_BCCH_DATA_IND (message_p).frame = frame; //frameP
        NR_RRC_MAC_BCCH_DATA_IND (message_p).slot = slot;
        NR_RRC_MAC_BCCH_DATA_IND (message_p).sdu_size = sdu_size;
        NR_RRC_MAC_BCCH_DATA_IND (message_p).gnb_index = gNB_index;
        NR_RRC_MAC_BCCH_DATA_IND (message_p).phycellid = cellid;
        NR_RRC_MAC_BCCH_DATA_IND (message_p).ssb_arfcn = arfcn;
        NR_RRC_MAC_BCCH_DATA_IND (message_p).is_bch = (channel == NR_BCCH_BCH);
        itti_send_msg_to_task(TASK_RRC_NRUE, GNB_MODULE_ID_TO_INSTANCE(module_id), message_p);
```

```c
// This piece of code is not used in "normal" ue, but in "fapi mode"
void check_and_process_dci(nfapi_nr_dl_tti_request_t *dl_tti_request,
                           nfapi_nr_tx_data_request_t *tx_data_request,
                           nfapi_nr_ul_dci_request_t *ul_dci_request,
                           nfapi_nr_ul_tti_request_t *ul_tti_request)
{

---

    nr_ue_dl_scheduler(mac, &mac->dl_info);
    nr_ue_dl_indication(&mac->dl_info)
```

// 0 1 1

```bash
7c 80 a 2 9 4 65 40 0 0 4 0 0 0 0 7b f8 0 1 1 40 90 84 d0 56 0 0 26 96 70 cb 35 de 1 b0 20 10 0 0 40 0 0 68 8a 6 c1 d3 10 58 20 0 2 69 c9 ce 19 66 54 62 0 1a d4 cd 7d c9 c0 49 38 c6 a9 8d 6e 9c 2a 3 87 40 20 b0 1d 80 48 8c de c4 30 
```

// 0 1 1 

```bash
7c 80 a 2 9 4 65 40 0 0 4 0 0 0 0 7b f8 0 1 1 40 90 84 d0 56 0 0 26 96 70 cb 35 de 1 b8 20 10 0 0 40 40 0 41 a2 28 1b 7 4c 41 60 80 0 9 a7 27 38 65 99 51 88 0 6b 53 35 f7 27 1 24 e3 1a a6 35 ba 70 a8 e 1d 0 82 c0 76 1 22 33 7b 10 c0 
```

// 1 1 1

```bash
7c 80 a 2 9 4 65 40 0 0 4 0 0 0 0 7b f8 0 1 1 40 90 84 d0 56 0 0 26 96 70 cb 35 de 1 b8 20 10 0 0 40 40 10 41 a2 28 1b 7 4c 41 60 80 0 9 a7 27 38 65 99 51 88 0 6b 53 35 f7 27 1 24 e3 1a a6 35 ba 70 a8 e 1d 0 82 c0 76 1 22 33 7b 10 c0 
```

Original

```bash
7c 80 a 2 9 4 65 40 0 0 4 0 0 0 0 7b f8 0 1 1 40 90 84 d0 56 0 0 26 96 70 cb 35 de 1 b8 20 10 0 0 40 40 0 41 a2 28 1b 7 4c 41 60 80 0 9 a7 27 38 65 99 51 88 0 6b 53 35 f7 27 1 24 e3 1a a6 35 ba 70 a8 e 1d 0 82 c0 76 1 22 33 7b 10 c0 
```

After shift

```
<searchSpaceSIB1>1</searchSpaceSIB1>
<pagingSearchSpace>1</pagingSearchSpace>
<ra-SearchSpace>1</ra-SearchSpace>
```

```bash
7c 80 0a 02 09 04 65 40 00 00 04 00 00 00 00 7b
f8 00 01 01 40 90 84 d0 56 00 00 26 96 70 cb 35
de 01 b0 20 10 00 00 40 04 22 31 30 11 34 45 03
60 68 08 2c 10 00 01 34 64 67 0c 33 2a 31 00 0d
6a 66 3e 64 60 24 1c 63 54 46 37 4e 15 01 43 20
10 58 0e 40 24 46 6f 62 18
```

```bash
7c 80 0a 02 09 04 65 40 00 00 04 00 00 00 00 7b f8 00 01 01 40 90 84 d0 56 00 00 26 96 70 cb 35 de 01 b8 20 10 00 00 40 40
```

```bash
 00 41 a2 28 1b 07 4c 41 60 80 00 09 a7 27 38 65 99 51 88 00 6b 53 35 f7 27 01 24 e3 1a a6 35 ba 70 a8 0e 1d 00 82 c0 76 01 22 33 7b 10 c0
```

```bash
00000000 01000001 10100010 00101000 00011011 00000111 01001100 01000001 01100000 10000000 00000000 00001001 10100111 00100111 00111000 01100101 10011001 01010001 10001000 00000000 01101011 01010011 00110101 11110111 00100111 00000001 00100100 11100011 00011010 10100110 00110101 10111010 01110000 10101000 00001110 00011101 00000000 10000010 11000000 01110110 00000001 00100010 00110011 01111011 00010000 11000000
```

```bash
0000000 01000001 10100010 00101000 00011011 00000111 01001100 01000001 01100000 10000000 00000000 00001001 10100111 00100111 00111000 01100101 10011001 01010001 10001000 00000000 01101011 01010011 00110101 11110111 00100111 00000001 00100100 11100011 00011010 10100110 00110101 10111010 01110000 10101000 00001110 00011101 00000000 10000010 11000000 01110110 00000001 00100010 00110011 01111011 00010000 110000000
```

Shift left 1

```bash
00000000 10000011 01000100 01010000 00110110 00001110 10011000 10000010 11000001 00000000 00000000 00001001 10100111 00100111 00111000 01100101 10011001 01010001 10001000 00000000 01101011 01010011 00110101 11110111 00100111 00000001 00100100 11100011 00011010 10100110 00110101 10111010 01110000 10101000 00001110 00011101 00000000 10000010 11000000 01110110 00000001 00100010 00110011 01111011 00010000 11000000
```

Hex

```bash
00 83 44 50 36 0e 98 82 c1 00 00 00 09 a7 27 38 65 99 51 88 00 6b 53 35 f7 27 01 24 e3 1a a6 35 ba 70 a8 0e 1d 00 82 c0 76 01 22 33 7b 10 c0
```

```bash
7c 80 0a 02 09 04 65 40 00 00 04 00 00 00 00 7b f8 00 01 01 40 90 84 d0 56 00 00 26 96 70 cb 35 de 01 b8 20 10 00 00 40 40 00 83 44 50 36 0e 98 82 c1 00 00 00 09 a7 27 38 65 99 51 88 00 6b 53 35 f7 27 01 24 e3 1a a6 35 ba 70 a8 0e 1d 00 82 c0 76 01 22 33 7b 10 c0
```

---

## Shift Right

```bash
000000000 01000001 10100010 00101000 00011011 00000111 01001100 01000001 01100000 10000000 00000000 00001001 10100111 00100111 00111000 01100101 10011001 01010001 10001000 00000000 01101011 01010011 00110101 11110111 00100111 00000001 00100100 11100011 00011010 10100110 00110101 10111010 01110000 10101000 00001110 00011101 00000000 10000010 11000000 01110110 00000001 00100010 00110011 01111011 00010000 1100000
```

```bash
00000000001000001101000100010100000011011000001110100110001000001011000001000000000000000000010011010011100100111001110000110010110011001010100011000100000000000011010110101001100110101111101110010011100000001001001001110001100011010101001100011010110111010011100001010100000001110000111010000000010000010110000000111011000000001001000100011001101111011000100001100000
```

Shift right

```bash
00000000 00100000 11010001 00010100 00001101 10000011 10100110 00100000 10110000 01000000 00000000 00000000 00010011 01001110 01001110 00111000 01100101 10011001 01010001 10001000 00000000 01101011 01010011 00110101 11101110 01001110 00000010 01001001 00111000 01100011 01010100 11000110 01011011 10100111 00010101 01000000 00111000 01110100 00000000 10000001 01100000 00111011 00000000 10010001 00011001 10111101 10001000 01100000
```

Hex

```bash
00 20 d1 14 0d 83 a6 20 b0 40 00 00 13 4e 4e 38 65 99 51 88 00 6b 53 35 ee 4e 02 49 38 63 54 c6 5b a7 15 40 38 74 00 81 60 3b 00 91 19 bd 88 60
```

```bash
7c 80 0a 02 09 04 65 40 00 00 04 00 00 00 00 7b f8 00 01 01 40 90 84 d0 56 00 00 26 96 70 cb 35 de 01 b8 20 10 00 00 40 40 00 20 d1 14 0d 83 a6 20 b0 40 00 00 13 4e 4e 38 65 99 51 88 00 6b 53 35 ee 4e 02 49 38 63 54 c6 5b a7 15 40 38 74 00 81 60 3b 00 91 19 bd 88 60
```

## Decode ASN.1 Online

[Free Online ASN.1 Decoder](https://www.marben-products.com/cgi-bin/asn1tools/free-online-asn1-decoder.pl)

Fail → have other error 

```bash
ASN.1 interface: 3GPP NR Release 16 NR-RRC (BCCH-DL-SCH-Message) 16.1.0

*** DECODING ***
<encoding>
7C800A02 09046540 00000400 0000007B F8000101 409084D0 56000026 9670CB35
DE01B820 10000040 400020D1 140D83A6 20B04000 00134E4E 38659951 88006B53
</encoding>

<BCCH-DL-SCH-Message>
  <message>
    <c1>
      <systemInformationBlockType1>
        <cellSelectionInfo>
          <q-RxLevMin>-65</q-RxLevMin>
        </cellSelectionInfo>
        <cellAccessRelatedInfo>
          <plmn-IdentityList>
            <PLMN-IdentityInfo>
              <plmn-IdentityList>
                <PLMN-Identity>
                  <mcc>
                    <MCC-MNC-Digit>2</MCC-MNC-Digit>
                    <MCC-MNC-Digit>0</MCC-MNC-Digit>
                    <MCC-MNC-Digit>8</MCC-MNC-Digit>
                  </mcc>
                  <mnc>
                    <MCC-MNC-Digit>9</MCC-MNC-Digit>
                    <MCC-MNC-Digit>5</MCC-MNC-Digit>
                    <MCC-MNC-Digit>0</MCC-MNC-Digit>
                  </mnc>
                </PLMN-Identity>
              </plmn-IdentityList>
              <trackingAreaCode>000000000000000000000001</trackingAreaCode>
              <cellIdentity>000000000000000000000000000000000001</cellIdentity>
              <cellReservedForOperatorUse>
                <notReserved/>
              </cellReservedForOperatorUse>
            </PLMN-IdentityInfo>
          </plmn-IdentityList>
        </cellAccessRelatedInfo>
        <connEstFailureControl>
          <connEstFailCount>
            <n3/>
          </connEstFailCount>
          <connEstFailOffsetValidity>
            <s900/>
          </connEstFailOffsetValidity>
          <connEstFailOffset>15</connEstFailOffset>
        </connEstFailureControl>
        <si-SchedulingInfo>
          <schedulingInfoList>
            <SchedulingInfo>
              <si-BroadcastStatus>
                <broadcasting/>
              </si-BroadcastStatus>
              <si-Periodicity>
                <rf8/>
              </si-Periodicity>
              <sib-MappingInfo>
                <SIB-TypeInfo>
                  <type>
                    <sibType2/>
                  </type>
                  <valueTag>10</valueTag>
                </SIB-TypeInfo>
              </sib-MappingInfo>
            </SchedulingInfo>
          </schedulingInfoList>
          <si-WindowLength>
            <s5/>
          </si-WindowLength>
        </si-SchedulingInfo>
        <servingCellConfigCommon>
          <downlinkConfigCommon>
            <frequencyInfoDL>
              <frequencyBandList>
                <NR-MultiBandInfo>
                  <freqBandIndicatorNR>78</freqBandIndicatorNR>
                </NR-MultiBandInfo>
              </frequencyBandList>
              <offsetToPointA>86</offsetToPointA>
              <scs-SpecificCarrierList>
                <SCS-SpecificCarrier>
                  <offsetToCarrier>0</offsetToCarrier>
                  <subcarrierSpacing>
                    <kHz30/>
                  </subcarrierSpacing>
                  <carrierBandwidth>106</carrierBandwidth>
                </SCS-SpecificCarrier>
              </scs-SpecificCarrierList>
            </frequencyInfoDL>
            <initialDownlinkBWP>
              <genericParameters>
                <locationAndBandwidth>28875</locationAndBandwidth>
                <subcarrierSpacing>
                  <kHz30/>
                </subcarrierSpacing>
              </genericParameters>
              <pdcch-ConfigCommon>
                <setup>
                  <controlResourceSetZero>12</controlResourceSetZero>
                  <searchSpaceZero>0</searchSpaceZero>
                  <commonSearchSpaceList>
                    <SearchSpace>
                      <searchSpaceId>1</searchSpaceId>
                      <controlResourceSetId>0</controlResourceSetId>
                      <monitoringSlotPeriodicityAndOffset>
                        <sl1/>
                      </monitoringSlotPeriodicityAndOffset>
                      <monitoringSymbolsWithinSlot>10000000000000</monitoringSymbolsWithinSlot>
                      <nrofCandidates>
                        <aggregationLevel1>
                          <n0/>
                        </aggregationLevel1>
                        <aggregationLevel2>
                          <n0/>
                        </aggregationLevel2>
                        <aggregationLevel4>
                          <n1/>
                        </aggregationLevel4>
                        <aggregationLevel8>
                          <n0/>
                        </aggregationLevel8>
                        <aggregationLevel16>
                          <n0/>
                        </aggregationLevel16>
                      </nrofCandidates>
                      <searchSpaceType>
                        <common>
                          <dci-Format0-0-AndFormat1-0/>
                        </common>
                      </searchSpaceType>
                    </SearchSpace>
                  </commonSearchSpaceList>
                  <searchSpaceSIB1>0</searchSpaceSIB1>
                  <pagingSearchSpace>1</pagingSearchSpace>
                  <ra-SearchSpace>1</ra-SearchSpace>
                </setup>
              </pdcch-ConfigCommon>
              <pdsch-ConfigCommon>
                <setup>
                  <pdsch-TimeDomainAllocationList>
                    <PDSCH-TimeDomainResourceAllocation>
                      <mappingType>
                        <typeA/>
                      </mappingType>
                      <startSymbolAndLength>40</startSymbolAndLength>
                    </PDSCH-TimeDomainResourceAllocation>
                    <PDSCH-TimeDomainResourceAllocation>
                      <mappingType>
                        <typeA/>
                      </mappingType>
                      <startSymbolAndLength>54</startSymbolAndLength>
                    </PDSCH-TimeDomainResourceAllocation>
                  </pdsch-TimeDomainAllocationList>
                </setup>
              </pdsch-ConfigCommon>
            </initialDownlinkBWP>
            <bcch-Config>
              <modificationPeriodCoeff>
                <n2/>
              </modificationPeriodCoeff>
            </bcch-Config>
            <pcch-Config>
              <defaultPagingCycle>
                <rf256/>
              </defaultPagingCycle>
              <nAndPagingFrameOffset>
                <quarterT>1</quarterT>
              </nAndPagingFrameOffset>
              <ns>
                <one/>
              </ns>
              <firstPDCCH-MonitoringOccasionOfPO>
                <sCS30KHZoneT-SCS15KHZhalfT>
                  <INTEGER>44</INTEGER>
                </sCS30KHZoneT-SCS15KHZhalfT>
              </firstPDCCH-MonitoringOccasionOfPO>
            </pcch-Config>
          </downlinkConfigCommon>
          <uplinkConfigCommon>
            <frequencyInfoUL>
              <scs-SpecificCarrierList>
                <SCS-SpecificCarrier>
                  <offsetToCarrier>0</offsetToCarrier>
                  <subcarrierSpacing>
                    <kHz15/>
                  </subcarrierSpacing>
                  <carrierBandwidth>10</carrierBandwidth>
                </SCS-SpecificCarrier>
              </scs-SpecificCarrierList>
              <p-Max>11</p-Max>
            </frequencyInfoUL>
            <initialUplinkBWP>
              <genericParameters>
                <locationAndBandwidth>14561</locationAndBandwidth>
                <subcarrierSpacing>
                  <kHz240/>
                </subcarrierSpacing>
                <cyclicPrefix>
                  <extended/>
                </cyclicPrefix>
              </genericParameters>
              <rach-ConfigCommon>
                <setup>
                  <rach-ConfigGeneric>
                    <prach-ConfigurationIndex>168</prach-ConfigurationIndex>
                    <msg1-FDM>
                      <eight/>
                    </msg1-FDM>
                    <msg1-FrequencyStart>32</msg1-FrequencyStart>
                    <zeroCorrelationZoneConfig>0</zeroCorrelationZoneConfig>
                    <preambleReceivedTargetPower>-176</preambleReceivedTargetPower>
                    <preambleTransMax>
                      <n3/>
                    </preambleTransMax>
                    <powerRampingStep>
                      <!-- Mandatory Field Missing -->
                    </powerRampingStep>
                    <ra-ResponseWindow>
                      <!-- Mandatory Field Missing -->
                    </ra-ResponseWindow>
                  </rach-ConfigGeneric>
                  <ra-ContentionResolutionTimer>
                    <!-- Mandatory Field Missing -->
                  </ra-ContentionResolutionTimer>
                  <prach-RootSequenceIndex>
                    <!-- Mandatory Field Missing -->
                  </prach-RootSequenceIndex>
                  <restrictedSetConfig>
                    <!-- Mandatory Field Missing -->
                  </restrictedSetConfig>
                </setup>
              </rach-ConfigCommon>
            </initialUplinkBWP>
            <timeAlignmentTimerCommon>
              <!-- Mandatory Field Missing -->
            </timeAlignmentTimerCommon>
          </uplinkConfigCommon>
          <ssb-PositionsInBurst>
            <!-- Mandatory Field Missing -->
          </ssb-PositionsInBurst>
          <ssb-PeriodicityServingCell>
            <!-- Mandatory Field Missing -->
          </ssb-PeriodicityServingCell>
          <ss-PBCH-BlockPower>
            <!-- Mandatory Field Missing -->
          </ss-PBCH-BlockPower>
        </servingCellConfigCommon>
      </systemInformationBlockType1>
    </c1>
  </message>
</BCCH-DL-SCH-Message>

<error>
  <description>the value has an invalid enumerated value</description>
  <nature>fr.marben.asnsdk.japi.InvalidValueException</nature>
  <ErrorOffset>64</ErrorOffset>
  <ValuePath>BCCH-DL-SCH-Message.message.c1.systemInformationBlockType1.servingCellConfigCommon.uplinkConfigCommon.initialUplinkBWP.rach-ConfigCommon.setup.rach-ConfigGeneric.preambleTransMax</ValuePath>
</error>

*** DECODING FAILED ***

```