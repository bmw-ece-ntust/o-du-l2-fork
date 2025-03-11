# Compare CellGroupConfig receive by UE

Start Date: 2024/10/15
Summary: The project involves comparing the CellGroupConfig received by the UE and analyzing the configuration details for various parameters and settings.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Compare
Finish Date: 2024/10/16
SUM: 🗓️ Days Spent to Complete: 1

```c
static void nr_rrc_ue_process_masterCellGroup(NR_UE_RRC_INST_t *rrc,
                                              OCTET_STRING_t *masterCellGroup,
                                              long *fullConfig)
{
  AssertFatal(!fullConfig, "fullConfig not supported yet\n");
  NR_CellGroupConfig_t *cellGroupConfig = NULL;
  uper_decode(NULL,
              &asn_DEF_NR_CellGroupConfig,   //might be added prefix later
              (void **)&cellGroupConfig,
              (uint8_t *)masterCellGroup->buf,
              masterCellGroup->size, 0, 0);

  if (LOG_DEBUGFLAG(DEBUG_ASN1)) {
    xer_fprint(stdout, &asn_DEF_NR_CellGroupConfig, (const void *) cellGroupConfig);
  }
  xer_fprint(stdout, &asn_DEF_NR_CellGroupConfig, (const void *) cellGroupConfig);

  nr_rrc_cellgroup_configuration(rrc, cellGroupConfig);

  LOG_D(RRC,"Sending CellGroupConfig to MAC\n");
  nr_rrc_mac_config_req_cg(rrc->ue_id, 0, cellGroupConfig, rrc->UECap.UE_NR_Capability);
  asn1cFreeStruc(asn_DEF_NR_CellGroupConfig, cellGroupConfig);
}
```

<aside>
💡

The OSC DU sent to the UE is missing some values in `spCellConfigDedicated`.

</aside>

## OSC fill **`spCellConfigDedicated`**

```jsx
   if(**BuildSpCellCfgDed**(ueCb, spCellCfg->spCellConfigDedicated) != ROK)
   {
      DU_LOG("\nERROR  -->  F1AP : BuildSpCellCfgDed failed");
      return RFAILED;
   }
```

# OSC DU HIgh CellGroupConfig Overview

## RLC-BearerToAddModList

- RLC-BearerConfig
    - logicalChannelIdentity: 1
    - servedRadioBearer
        - srb-Identity: 1
    - rlc-Config (AM mode)
        - ul-AM-RLC
            - sn-FieldLength: size12
            - t-PollRetransmit: ms45
            - pollPDU: p4
            - pollByte: infinity
            - maxRetxThreshold: t8
        - dl-AM-RLC
            - sn-FieldLength: size12
            - t-Reassembly: ms40
            - t-StatusProhibit: ms35
    - mac-LogicalChannelConfig
        - ul-SpecificParameters
            - priority: 1
            - prioritisedBitRate: infinity
            - bucketSizeDuration: ms150
            - logicalChannelGroup: 0
            - schedulingRequestID: 0
            - logicalChannelSR-Mask: false
            - logicalChannelSR-DelayTimerApplied: false

## mac-CellGroupConfig

- schedulingRequestConfig
    - schedulingRequestToAddModList
        - SchedulingRequestToAddMod
            - schedulingRequestId: 0
            - sr-ProhibitTimer: ms32
            - sr-TransMax: n16
- bsr-Config
    - periodicBSR-Timer: sf10
    - retxBSR-Timer: sf320
- tag-Config
    - tag-ToAddModList
        - TAG
            - tag-Id: 0
            - timeAlignmentTimer: infinity
- phr-Config
    - setup
        - phr-PeriodicTimer: infinity
        - phr-ProhibitTimer: sf0
        - phr-Tx-PowerFactorChange: infinity
        - multiplePHR: false
        - dummy: false
        - phr-Type2OtherCell: false
        - phr-ModeOtherCG: real
- skipUplinkTxDynamic: false

## physicalCellGroupConfig

- p-NR-FR1: 0
- pdsch-HARQ-ACK-Codebook: dynamic

## spCellConfig

- servCellIndex: 0
- rlmInSyncOutOfSyncThreshold: n1
- spCellConfigDedicated
    - downlinkBWP-ToReleaseList: (empty)
    - tag-Id: 0

# OAI DU CellGroupConfig Overview

## RLC-BearerToAddModList

- **RLC-BearerConfig**
    - logicalChannelIdentity: 1
    - servedRadioBearer:
        - srb-Identity: 1
    - rlc-Config:
        - am:
            - ul-AM-RLC:
                - sn-FieldLength: size12
                - t-PollRetransmit: ms45
                - pollPDU: infinity
                - pollByte: infinity
                - maxRetxThreshold: t8
            - dl-AM-RLC:
                - sn-FieldLength: size12
                - t-Reassembly: ms35
                - t-StatusProhibit: ms0
    - mac-LogicalChannelConfig:
        - ul-SpecificParameters:
            - priority: 1
            - prioritisedBitRate: infinity
            - bucketSizeDuration: ms1000
            - logicalChannelGroup: 0
            - schedulingRequestID: 0
            - logicalChannelSR-Mask: false
            - logicalChannelSR-DelayTimerApplied: false

## MAC-CellGroupConfig

- schedulingRequestConfig:
    - schedulingRequestToAddModList:
        - SchedulingRequestToAddMod:
            - schedulingRequestId: 0
            - sr-TransMax: n64
- bsr-Config:
    - periodicBSR-Timer: sf10
    - retxBSR-Timer: sf80
- tag-Config:
    - tag-ToAddModList:
        - TAG:
            - tag-Id: 0
            - timeAlignmentTimer: infinity
- phr-Config:
    - setup:
        - phr-PeriodicTimer: sf10
        - phr-ProhibitTimer: sf10
        - phr-Tx-PowerFactorChange: dB1
        - multiplePHR: false
        - dummy: false
        - phr-Type2OtherCell: false
        - phr-ModeOtherCG: real
- skipUplinkTxDynamic: false

## PhysicalCellGroupConfig

- pdsch-HARQ-ACK-Codebook: dynamic

## SpCellConfig

### SpCellConfigDedicated

### InitialDownlinkBWP

- pdcch-Config:
    - controlResourceSetToAddModList:
        - ControlResourceSet:
            - controlResourceSetId: 1
            - frequencyDomainResources: 111111111111111100000000000000000000000000000
            - duration: 1
            - cce-REG-MappingType: nonInterleaved
            - precoderGranularity: sameAsREG-bundle
            - tci-StatesPDCCH-ToAddList: 0
    - searchSpacesToAddModList:
        - SearchSpace:
            - searchSpaceId: 5
            - controlResourceSetId: 1
            - monitoringSlotPeriodicityAndOffset: sl1
            - monitoringSymbolsWithinSlot: 10000000000000
            - nrofCandidates:
                - aggregationLevel1: n0
                - aggregationLevel2: n2
                - aggregationLevel4: n0
                - aggregationLevel8: n0
                - aggregationLevel16: n0
            - searchSpaceType:
                - ue-Specific:
                    - dci-Formats: formats0-1-And-1-1
- pdsch-Config:
    - dmrs-DownlinkForPDSCH-MappingTypeA:
        - dmrs-AdditionalPosition: pos1
    - tci-StatesToAddModList:
        - TCI-State:
            - tci-StateId: 0
            - qcl-Type1:
                - bwp-Id: 0
                - referenceSignal:
                    - ssb: 0
                - qcl-Type: typeC
    - resourceAllocation: resourceAllocationType1
    - rbg-Size: config1
    - prb-BundlingType:
        - staticBundling:
            - bundleSize: wideband

### UplinkConfig

### InitialUplinkBWP

### PUCCH-Config

- resourceSetToAddModList:
    - PUCCH-ResourceSet:
        - pucch-ResourceSetId: 0
        - resourceList: 0
    - PUCCH-ResourceSet:
        - pucch-ResourceSetId: 1
        - resourceList: 2
- resourceToAddModList:
    - PUCCH-Resource:
        - pucch-ResourceId: 0
        - startingPRB: 8
        - format:
            - format0:
                - initialCyclicShift: 0
                - nrofSymbols: 1
                - startingSymbolIndex: 13
    - PUCCH-Resource:
        - pucch-ResourceId: 2
        - startingPRB: 0
        - format:
            - format2:
                - nrofPRBs: 8
                - nrofSymbols: 1
                - startingSymbolIndex: 13
- format2:
    - maxCodeRate: zeroDot15
    - simultaneousHARQ-ACK-CSI: true
- schedulingRequestResourceToAddModList:
    - SchedulingRequestResourceConfig:
        - schedulingRequestResourceId: 1
        - schedulingRequestID: 0
        - periodicityAndOffset:
            - sl10: 7
        - resource: 0
- dl-DataToUL-ACK: [6, 7, 8, 9, 10, 11, 12, 13]
- spatialRelationInfoToAddModList:
    - PUCCH-SpatialRelationInfo:
        - pucch-SpatialRelationInfoId: 1
        - referenceSignal:
            - ssb-Index: 0
        - pucch-PathlossReferenceRS-Id: 0
        - p0-PUCCH-Id: 1
        - closedLoopIndex: i0
- pucch-PowerControl:
    - deltaF-PUCCH-f0: 0
    - deltaF-PUCCH-f2: 0
    - p0-Set:
        - P0-PUCCH:
            - p0-PUCCH-Id: 1
            - p0-PUCCH-Value: 0
    - pathlossReferenceRSs:
        - PUCCH-PathlossReferenceRS:
            - pucch-PathlossReferenceRS-Id: 0
            - referenceSignal:
                - ssb-Index: 0

### PUSCH-Config

- txConfig: codebook
- dmrs-UplinkForPUSCH-MappingTypeB: setup
- pusch-PowerControl:
    - msg3-Alpha: alpha1
    - p0-AlphaSets:
        - P0-PUSCH-AlphaSet:
            - p0-PUSCH-AlphaSetId: 0
            - p0: 0
            - alpha: alpha1
    - pathlossReferenceRSToAddModList:
        - PUSCH-PathlossReferenceRS:
            - pusch-PathlossReferenceRS-Id: 0
            - referenceSignal:
                - ssb-Index: 0
    - deltaMCS: enabled
- resourceAllocation: resourceAllocationType1
- codebookSubset: nonCoherent
- maxRank: 1

### SRS-Config

- srs-ResourceSetToAddModList:
    - SRS-ResourceSet:
        - srs-ResourceSetId: 0
        - srs-ResourceIdList: 0
        - resourceType:
            - aperiodic:
                - aperiodicSRS-ResourceTrigger: 1
                - slotOffset: 2
        - usage: codebook
        - alpha: alpha1
        - p0: -80
- srs-ResourceToAddModList:
    - SRS-Resource:
        - srs-ResourceId: 0
        - nrofSRS-Ports: port1
        - transmissionComb:
            - n2:
                - combOffset-n2: 0
                - cyclicShift-n2: 0
        - resourceMapping:
            - startPosition: 1
            - nrofSymbols: n1
            - repetitionFactor: n1
        - freqDomainPosition: 0
        - freqDomainShift: 0
        - freqHopping:
            - c-SRS: 25
            - b-SRS: 0
            - b-hop: 0
        - groupOrSequenceHopping: neither
        - resourceType: aperiodic
        - sequenceId: 40
        - spatialRelationInfo:
            - referenceSignal:
                - ssb-Index: 0

### PDSCH-ServingCellConfig

- nrofHARQ-ProcessesForPDSCH: n16
- maxMIMO-Layers: 2

### CSI-MeasConfig

- csi-SSB-ResourceSetToAddModList:
    - CSI-SSB-ResourceSet:
        - csi-SSB-ResourceSetId: 0
        - csi-SSB-ResourceList: 0
- csi-ResourceConfigToAddModList:
    - CSI-ResourceConfig:
        - csi-ResourceConfigId: 20
        - csi-RS-ResourceSetList:
            - nzp-CSI-RS-SSB:
                - csi-SSB-ResourceSetList: 0
        - bwp-Id: 0
        - resourceType: periodic
- csi-ReportConfigToAddModList:
    - CSI-ReportConfig:
        - reportConfigId: 10
        - resourcesForChannelMeasurement: 20
        - reportConfigType:
            - periodic:
                - reportSlotConfig:
                    - slots160: 8
                - pucch-CSI-ResourceList:
                    - PUCCH-CSI-Resource:
                        - uplinkBandwidthPartId: 0
                        - pucch-Resource: 2
        - reportQuantity: ssb-Index-RSRP
        - timeRestrictionForChannelMeasurements: configured
        - timeRestrictionForInterferenceMeasurements: configured
        - groupBasedBeamReporting:
            - disabled:
                - nrofReportedRS: n1
        - subbandSize: value1

### Tag-Id: 0