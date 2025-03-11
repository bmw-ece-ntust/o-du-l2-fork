# OSC E2AP ASN.1 file

Start Date: 2024/10/16
Summary: The project involves creating and managing ASN.1 files for the E2AP and KPM protocols, including rebuilding, testing, and executing related commands.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2025/01/09
SUM: 🗓️ Days Spent to Complete: 85

Use the following command to rebuild the RRC ASN.1 files

- Clone the `NTUST-script` repository into the `home` directory → https://github.com/dong881/NTUST-script
- Install mouse07410 version of asn1c → [Installation Guide for ASN.1 Compiler (mouse07410)](Installation%20Guide%20for%20ASN%201%20Compiler%20(mouse07410)%2017e10098314380d0a8dbd26bcbc32e42.md)
- Have the `o-du-l2` project source code in the `home` directory → https://github.com/o-ran-sc/o-du-l2

This command can be executed from any directory

## E2AP

```bash
sudo rm -rf ~/o-du-l2/src/codec_utils/E2AP/* && sudo /opt/asn1c/bin/asn1c -gen-APER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ~/o-du-l2/src/codec_utils/E2AP ~/NTUST-script/CONFIG/E2APV0300.asn1 &&  ~/NTUST-script/Tools/Pick-commonFiles.sh E2AP
```

## E2SM_KPM

```bash
sudo rm -rf ~/o-du-l2/src/codec_utils/E2SM_KPM/* && sudo /opt/asn1c/bin/asn1c -no-gen-BER -gen-UPER -no-gen-OER -no-gen-JER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ~/o-du-l2/src/codec_utils/E2SM_KPM ~/NTUST-script/CONFIG/ASN.1_KPM_v2.03.asn ~/NTUST-script/CONFIG/ASN.1_SM_v2.01.asn && ~/NTUST-script/Tools/Pick-commonFiles.sh E2SM_KPM
```

---

# Appendices

- Rebuild ANS1 file for E2AP

```bash
cd /opt/asn1c/bin
sudo rm -r /home/hpe/o-du-l2/src/codec_utils/E2AP
sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp /home/hpe/NTUST-script/CONFIG/E2APV0300.asn1
mkdir /home/hpe/o-du-l2/src/codec_utils/E2AP
sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/E2AP

#### one line command
cd /opt/asn1c/bin && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/E2AP && sudo ./asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D ./temp /home/hpe/NTUST-script/CONFIG/E2APV0300.asn1 && mkdir /home/hpe/o-du-l2/src/codec_utils/E2AP && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/E2AP

### Use OAI .asn1 file 
cd /opt/asn1c/bin && sudo ./asn1c -gen-APER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ./temp /home/hpe/NTUST-script/CONFIG/e2ap_v3_01.asn && mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP && cd /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP

### Use OSC .asn1 file and mkdir new temp folder
cd /opt/asn1c/bin && sudo ./asn1c -gen-APER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ./temp /home/hpe/NTUST-script/CONFIG/E2APV0300.asn1 && mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP && cd /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP
### auto run script to pick into E2AP folder and remove temp folder
cd /opt/asn1c/bin && sudo ./asn1c -gen-APER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ./temp /home/hpe/NTUST-script/CONFIG/E2APV0300.asn1 && mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP && cd /home/hpe/o-du-l2/src/codec_utils/ && sudo rm /home/hpe/o-du-l2/src/codec_utils/E2AP/* && ./pick.sh && sudo rm -r /home/hpe/o-du-l2/src/codec_utils/Temp_E2AP
```

version: **E2APV0300.asn1**

```bash
AMFName.c                                RANfunctionsID-List.c
AMFName.h                                RANfunctionsID-List.h
CauseE2.c                                RANfunctions-List.c
CauseE2.h                                RANfunctions-List.h
CauseE2Misc.c                            ResetRequestE2.c
CauseE2Misc.h                            ResetRequestE2.h
CauseE2node.c                            ResetResponseE2.c
CauseE2node.h                            ResetResponseE2.h
CauseE2Protocol.c                        RICaction-AddedForModification-Item.c
CauseE2Protocol.h                        RICaction-AddedForModification-Item.h
CauseE2RICrequest.c                      RICaction-Admitted-Item.c
CauseE2RICrequest.h                      RICaction-Admitted-Item.h
CauseE2RICservice.c                      RICaction-Admitted-List.c
CauseE2RICservice.h                      RICaction-Admitted-List.h
CauseE2Transport.c                       RICaction-ConfirmedForModification-Item.c
CauseE2Transport.h                       RICaction-ConfirmedForModification-Item.h
CriticalityDiagnosticsE2.c               RICaction-ConfirmedForRemoval-Item.c
CriticalityDiagnosticsE2.h               RICaction-ConfirmedForRemoval-Item.h
CriticalityDiagnostics-IE-ItemE2.c       RICactionDefinition.c
CriticalityDiagnostics-IE-ItemE2.h       RICactionDefinition.h
CriticalityDiagnostics-IE-ListE2.c       RICactionExecutionOrder.c
CriticalityDiagnostics-IE-ListE2.h       RICactionExecutionOrder.h
CriticalityE2.c                          RICaction-FailedToBeAddedForModification-Item.c
CriticalityE2.h                          RICaction-FailedToBeAddedForModification-Item.h
E2AP-PDU.c                               RICaction-FailedToBeModifiedForModification-Item.c
E2AP-PDU.h                               RICaction-FailedToBeModifiedForModification-Item.h
E2connectionSetupFailed-Item.c           RICaction-FailedToBeRemovedForModification-Item.c
E2connectionSetupFailed-Item.h           RICaction-FailedToBeRemovedForModification-Item.h
E2connectionSetupFailed-List.c           RICactionID.c
E2connectionSetupFailed-List.h           RICactionID.h
E2connectionUpdateAcknowledge.c          RICaction-ModifiedForModification-Item.c
E2connectionUpdateAcknowledge.h          RICaction-ModifiedForModification-Item.h
E2connectionUpdate.c                     RICaction-NotAdmitted-Item.c
E2connectionUpdateFailure.c              RICaction-NotAdmitted-Item.h
E2connectionUpdateFailure.h              RICaction-NotAdmitted-List.c
E2connectionUpdate.h                     RICaction-NotAdmitted-List.h
E2connectionUpdate-Item.c                RICaction-RefusedToBeModified-Item.c
E2connectionUpdate-Item.h                RICaction-RefusedToBeModified-Item.h
E2connectionUpdate-List.c                RICaction-RefusedToBeRemoved-Item.c
E2connectionUpdate-List.h                RICaction-RefusedToBeRemoved-Item.h
E2connectionUpdateRemove-Item.c          RICaction-RemovedForModification-Item.c
E2connectionUpdateRemove-Item.h          RICaction-RemovedForModification-Item.h
E2connectionUpdateRemove-List.c          RICaction-RequiredToBeModified-Item.c
E2connectionUpdateRemove-List.h          RICaction-RequiredToBeModified-Item.h
E2nodeComponentConfigAdditionAck-Item.c  RICaction-RequiredToBeRemoved-Item.c
E2nodeComponentConfigAdditionAck-Item.h  RICaction-RequiredToBeRemoved-Item.h
E2nodeComponentConfigAdditionAck-List.c  RICactions-AddedForModification-List.c
E2nodeComponentConfigAdditionAck-List.h  RICactions-AddedForModification-List.h
E2nodeComponentConfigAddition-Item.c     RICactions-ConfirmedForModification-List.c
E2nodeComponentConfigAddition-Item.h     RICactions-ConfirmedForModification-List.h
E2nodeComponentConfigAddition-List.c     RICactions-ConfirmedForRemoval-List.c
E2nodeComponentConfigAddition-List.h     RICactions-ConfirmedForRemoval-List.h
E2nodeComponentConfigRemovalAck-Item.c   RICactions-FailedToBeAddedForModification-List.c
E2nodeComponentConfigRemovalAck-Item.h   RICactions-FailedToBeAddedForModification-List.h
E2nodeComponentConfigRemovalAck-List.c   RICactions-FailedToBeModifiedForModification-List.c
E2nodeComponentConfigRemovalAck-List.h   RICactions-FailedToBeModifiedForModification-List.h
E2nodeComponentConfigRemoval-Item.c      RICactions-FailedToBeRemovedForModification-List.c
E2nodeComponentConfigRemoval-Item.h      RICactions-FailedToBeRemovedForModification-List.h
E2nodeComponentConfigRemoval-List.c      RICactions-ModifiedForModification-List.c
E2nodeComponentConfigRemoval-List.h      RICactions-ModifiedForModification-List.h
E2nodeComponentConfigUpdateAck-Item.c    RICactions-RefusedToBeModified-List.c
E2nodeComponentConfigUpdateAck-Item.h    RICactions-RefusedToBeModified-List.h
E2nodeComponentConfigUpdateAck-List.c    RICactions-RefusedToBeRemoved-List.c
E2nodeComponentConfigUpdateAck-List.h    RICactions-RefusedToBeRemoved-List.h
E2nodeComponentConfigUpdate-Item.c       RICactions-RemovedForModification-List.c
E2nodeComponentConfigUpdate-Item.h       RICactions-RemovedForModification-List.h
E2nodeComponentConfigUpdate-List.c       RICactions-RequiredToBeModified-List.c
E2nodeComponentConfigUpdate-List.h       RICactions-RequiredToBeModified-List.h
E2nodeComponentConfigurationAck.c        RICactions-RequiredToBeRemoved-List.c
E2nodeComponentConfigurationAck.h        RICactions-RequiredToBeRemoved-List.h
E2nodeComponentConfiguration.c           RICactions-ToBeAddedForModification-List.c
E2nodeComponentConfiguration.h           RICactions-ToBeAddedForModification-List.h
E2nodeComponentID.c                      RICactions-ToBeModifiedForModification-List.c
E2nodeComponentID.h                      RICactions-ToBeModifiedForModification-List.h
E2nodeComponentInterfaceE1.c             RICactions-ToBeRemovedForModification-List.c
E2nodeComponentInterfaceE1.h             RICactions-ToBeRemovedForModification-List.h
E2nodeComponentInterfaceF1.c             RICactions-ToBeSetup-List.c
E2nodeComponentInterfaceF1.h             RICactions-ToBeSetup-List.h
E2nodeComponentInterfaceNG.c             RICaction-ToBeAddedForModification-Item.c
E2nodeComponentInterfaceNG.h             RICaction-ToBeAddedForModification-Item.h
E2nodeComponentInterfaceS1.c             RICaction-ToBeModifiedForModification-Item.c
E2nodeComponentInterfaceS1.h             RICaction-ToBeModifiedForModification-Item.h
E2nodeComponentInterfaceType.c           RICaction-ToBeRemovedForModification-Item.c
E2nodeComponentInterfaceType.h           RICaction-ToBeRemovedForModification-Item.h
E2nodeComponentInterfaceW1.c             RICaction-ToBeSetup-Item.c
E2nodeComponentInterfaceW1.h             RICaction-ToBeSetup-Item.h
E2nodeComponentInterfaceX2.c             RICactionType.c
E2nodeComponentInterfaceX2.h             RICactionType.h
E2nodeComponentInterfaceXn.c             RICcallProcessID.c
E2nodeComponentInterfaceXn.h             RICcallProcessID.h
E2nodeConfigurationUpdateAcknowledge.c   RICcontrolAcknowledge.c
E2nodeConfigurationUpdateAcknowledge.h   RICcontrolAcknowledge.h
E2nodeConfigurationUpdate.c              RICcontrolAckRequest.c
E2nodeConfigurationUpdateFailure.c       RICcontrolAckRequest.h
E2nodeConfigurationUpdateFailure.h       RICcontrolFailure.c
E2nodeConfigurationUpdate.h              RICcontrolFailure.h
E2nodeTNLassociationRemoval-Item.c       RICcontrolHeader.c
E2nodeTNLassociationRemoval-Item.h       RICcontrolHeader.h
E2nodeTNLassociationRemoval-List.c       RICcontrolMessage.c
E2nodeTNLassociationRemoval-List.h       RICcontrolMessage.h
E2RemovalFailure.c                       RICcontrolOutcome.c
E2RemovalFailure.h                       RICcontrolOutcome.h
E2RemovalRequest.c                       RICcontrolRequest.c
E2RemovalRequest.h                       RICcontrolRequest.h
E2RemovalResponse.c                      RICeventTriggerDefinition.c
E2RemovalResponse.h                      RICeventTriggerDefinition.h
E2setupFailure.c                         RICindication.c
E2setupFailure.h                         RICindication.h
E2setupRequest.c                         RICindicationHeader.c
E2setupRequest.h                         RICindicationHeader.h
E2setupResponse.c                        RICindicationMessage.c
E2setupResponse.h                        RICindicationMessage.h
ENB-ID.c                                 RICindicationSN.c
ENB-ID-Choice.c                          RICindicationSN.h
ENB-ID-Choice.h                          RICindicationType.c
ENB-ID.h                                 RICindicationType.h
ENGNB-ID.c                               RICqueryDefinition.c
ENGNB-ID.h                               RICqueryDefinition.h
ErrorIndicationE2.c                      RICQueryFailure.c
ErrorIndicationE2.h                      RICQueryFailure.h
GlobalE2node-eNB-ID.c                    RICqueryHeader.c
GlobalE2node-eNB-ID.h                    RICqueryHeader.h
GlobalE2node-en-gNB-ID.c                 RICqueryOutcome.c
GlobalE2node-en-gNB-ID.h                 RICqueryOutcome.h
GlobalE2node-gNB-ID.c                    RICQueryRequest.c
GlobalE2node-gNB-ID.h                    RICQueryRequest.h
GlobalE2node-ID.c                        RICQueryResponse.c
GlobalE2node-ID.h                        RICQueryResponse.h
GlobalE2node-ng-eNB-ID.c                 RICrequestID.c
GlobalE2node-ng-eNB-ID.h                 RICrequestID.h
GlobalENB-ID.c                           RICserviceQuery.c
GlobalENB-ID.h                           RICserviceQuery.h
GlobalenGNB-ID.c                         RICserviceUpdateAcknowledge.c
GlobalenGNB-ID.h                         RICserviceUpdateAcknowledge.h
GlobalgNB-ID.c                           RICserviceUpdate.c
GlobalgNB-ID.h                           RICserviceUpdateFailure.c
GlobalngeNB-ID.c                         RICserviceUpdateFailure.h
GlobalngeNB-ID.h                         RICserviceUpdate.h
GlobalNG-RANNode-ID.c                    RICsubscriptionDeleteFailure.c
GlobalNG-RANNode-ID.h                    RICsubscriptionDeleteFailure.h
GlobalRIC-ID.c                           RICsubscriptionDeleteRequest.c
GlobalRIC-ID.h                           RICsubscriptionDeleteRequest.h
GNB-CU-UP-ID.c                           RICsubscriptionDeleteRequired.c
GNB-CU-UP-ID.h                           RICsubscriptionDeleteRequired.h
GNB-DU-ID.c                              RICsubscriptionDeleteResponse.c
GNB-DU-ID.h                              RICsubscriptionDeleteResponse.h
GNB-ID-Choice.c                          RICsubscriptionDetails.c
GNB-ID-Choice.h                          RICsubscriptionDetails.h
InitiatingMessageE2.c                    RICsubscriptionFailure.c
InitiatingMessageE2.h                    RICsubscriptionFailure.h
Makefile.am.libasncodec                  RICsubscription-List-withCause.c
MMEname.c                                RICsubscription-List-withCause.h
MMEname.h                                RICsubscriptionModificationConfirm.c
NGENB-DU-ID.c                            RICsubscriptionModificationConfirm.h
NGENB-DU-ID.h                            RICsubscriptionModificationFailure.c
PLMN-Identity.c                          RICsubscriptionModificationFailure.h
PLMN-Identity.h                          RICsubscriptionModificationRefuse.c
PresenceE2.c                             RICsubscriptionModificationRefuse.h
PresenceE2.h                             RICsubscriptionModificationRequest.c
PrintableString.c                        RICsubscriptionModificationRequest.h
PrintableString.h                        RICsubscriptionModificationRequired.c
ProcedureCodeE2.c                        RICsubscriptionModificationRequired.h
ProcedureCodeE2.h                        RICsubscriptionModificationResponse.c
ProtocolIE-ContainerE2.c                 RICsubscriptionModificationResponse.h
ProtocolIE-ContainerE2.h                 RICsubscriptionRequest.c
ProtocolIE-ContainerList.c               RICsubscriptionRequest.h
ProtocolIE-ContainerList.h               RICsubscriptionResponse.c
ProtocolIE-ContainerPairE2.c             RICsubscriptionResponse.h
ProtocolIE-ContainerPairE2.h             RICsubscriptionTime.c
ProtocolIE-ContainerPairList.c           RICsubscriptionTime.h
ProtocolIE-ContainerPairList.h           RICsubscription-withCause-Item.c
ProtocolIE-FieldE2.c                     RICsubscription-withCause-Item.h
ProtocolIE-FieldE2.h                     RICsubsequentAction.c
ProtocolIE-FieldPairE2.c                 RICsubsequentAction.h
ProtocolIE-FieldPairE2.h                 RICsubsequentActionType.c
ProtocolIE-IDE2.c                        RICsubsequentActionType.h
ProtocolIE-IDE2.h                        RICtimeToWait.c
ProtocolIE-SingleContainerE2.c           RICtimeToWait.h
ProtocolIE-SingleContainerE2.h           SuccessfulOutcomeE2.c
RANfunctionDefinition.c                  SuccessfulOutcomeE2.h
RANfunctionDefinition.h                  TimeToWaitE2.c
RANfunctionID.c                          TimeToWaitE2.h
RANfunctionIDcause-Item.c                TNLinformation.c
RANfunctionIDcause-Item.h                TNLinformation.h
RANfunctionID.h                          TNLusage.c
RANfunctionID-Item.c                     TNLusage.h
RANfunctionID-Item.h                     TransactionID.c
RANfunction-Item.c                       TransactionID.h
RANfunction-Item.h                       TriggeringMessageE2.c
RANfunctionOID.c                         TriggeringMessageE2.h
RANfunctionOID.h                         TypeOfErrorE2.c
RANfunctionRevision.c                    TypeOfErrorE2.h
RANfunctionRevision.h                    UnsuccessfulOutcomeE2.c
RANfunctionsIDcause-List.c               UnsuccessfulOutcomeE2.h
RANfunctionsIDcause-List.h

```

# KPM

```bash
/* original OSC
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "../../ASN1_Input/E2SM_KPM_V_3_0.asn1"
 * 	`asn1c -D ./../../E2_output/E2SM_KPM_v3.0_output -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */
 
```

```bash
cd /opt/asn1c/bin && sudo ./asn1c -no-gen-BER -no-gen-UPER -no-gen-OER -no-gen-JER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps -D ./temp /home/hpe/NTUST-script/CONFIG/ASN.1_KPM_v2.03.asn /home/hpe/NTUST-script/CONFIG/ASN.1_SM_v2.01.asn && mkdir /home/hpe/o-du-l2/src/codec_utils/Temp_E2SM_KPM && sudo mv ./temp/* /home/hpe/o-du-l2/src/codec_utils/Temp_E2SM_KPM && cd /home/hpe/o-du-l2/src/codec_utils/Temp_E2SM_KPM 
```

version: **E2SM_KPM_V_3_0.asn1**

```bash
AMFPointer.c                               GranularityPeriod.h            NGENB-CU-UE-W1AP-ID.h
AMFPointer.h                               GUAMI.c                        NgENB-ID.c
AMFRegionID.c                              GUAMI.h                        NgENB-ID.h
AMFRegionID.h                              GUMMEI.c                       NG-RANnodeUEXnAPID.c
AMFSetID.c                                 GUMMEI.h                       NG-RANnodeUEXnAPID.h
AMFSetID.h                                 LabelInfoItem.c                NRCellIdentity.c
AMF-UE-NGAP-ID.c                           LabelInfoItem.h                NRCellIdentity.h
AMF-UE-NGAP-ID.h                           LabelInfoList.c                NR-CGI.c
BinIndex.c                                 LabelInfoList.h                NR-CGI.h
BinIndex.h                                 LogicalOR.c                    NULL.c
BinRangeDefinition.c                       LogicalOR.h                    NULL.h
BinRangeDefinition.h                       Makefile.am.libasncodec        PLMNIdentity.c
BinRangeItem.c                             MatchingCondItem.c             PLMNIdentity.h
BinRangeItem.h                             MatchingCondItem-Choice.c      QCI.c
BinRangeList.c                             MatchingCondItem-Choice.h      QCI.h
BinRangeList.h                             MatchingCondItem.h             QosFlowIdentifier.c
BinRangeValue.c                            MatchingCondList.c             QosFlowIdentifier.h
BinRangeValue.h                            MatchingCondList.h             RANfunction-Name.c
CGI.c                                      MatchingUeCondPerSubItem.c     RANfunction-Name.h
CGI.h                                      MatchingUeCondPerSubItem.h     RANUEID.c
DistMeasurementBinRangeItem.c              MatchingUeCondPerSubList.c     RANUEID.h
DistMeasurementBinRangeItem.h              MatchingUeCondPerSubList.h     REAL.c
DistMeasurementBinRangeList.c              MatchingUEidItem.c             REAL.h
DistMeasurementBinRangeList.h              MatchingUEidItem.h             RIC-EventTriggerStyle-Item.c
E2SM-KPM-ActionDefinition.c                MatchingUEidItem-PerGP.c       RIC-EventTriggerStyle-Item.h
E2SM-KPM-ActionDefinition-Format1.c        MatchingUEidItem-PerGP.h       RIC-Format-Type.c
E2SM-KPM-ActionDefinition-Format1.h        MatchingUEidList.c             RIC-Format-Type.h
E2SM-KPM-ActionDefinition-Format2.c        MatchingUEidList.h             RIC-ReportStyle-Item.c
E2SM-KPM-ActionDefinition-Format2.h        MatchingUEidList-PerGP.c       RIC-ReportStyle-Item.h
E2SM-KPM-ActionDefinition-Format3.c        MatchingUEidList-PerGP.h       RIC-Style-Name.c
E2SM-KPM-ActionDefinition-Format3.h        MatchingUEidPerGP.c            RIC-Style-Name.h
E2SM-KPM-ActionDefinition-Format4.c        MatchingUEidPerGP.h            RIC-Style-Type.c
E2SM-KPM-ActionDefinition-Format4.h        MatchingUEidPerGP-Item.c       RIC-Style-Type.h
E2SM-KPM-ActionDefinition-Format5.c        MatchingUEidPerGP-Item.h       SD.c
E2SM-KPM-ActionDefinition-Format5.h        MatchingUEidPerSubItem.c       SD.h
E2SM-KPM-ActionDefinition.h                MatchingUEidPerSubItem.h       S-NSSAI.c
E2SM-KPM-EventTriggerDefinition.c          MatchingUEidPerSubList.c       S-NSSAI.h
E2SM-KPM-EventTriggerDefinition-Format1.c  MatchingUEidPerSubList.h       SST.c
E2SM-KPM-EventTriggerDefinition-Format1.h  MeasurementCondItem.c          SST.h
E2SM-KPM-EventTriggerDefinition.h          MeasurementCondItem.h          TestCond-Expression.c
E2SM-KPM-IndicationHeader.c                MeasurementCondList.c          TestCond-Expression.h
E2SM-KPM-IndicationHeader-Format1.c        MeasurementCondList.h          TestCondInfo.c
E2SM-KPM-IndicationHeader-Format1.h        MeasurementCondUEidItem.c      TestCondInfo.h
E2SM-KPM-IndicationHeader.h                MeasurementCondUEidItem.h      TestCond-Type.c
E2SM-KPM-IndicationMessage.c               MeasurementCondUEidList.c      TestCond-Type.h
E2SM-KPM-IndicationMessage-Format1.c       MeasurementCondUEidList.h      TestCond-Value.c
E2SM-KPM-IndicationMessage-Format1.h       MeasurementData.c              TestCond-Value.h
E2SM-KPM-IndicationMessage-Format2.c       MeasurementData.h              TimeStamp.c
E2SM-KPM-IndicationMessage-Format2.h       MeasurementDataItem.c          TimeStamp.h
E2SM-KPM-IndicationMessage-Format3.c       MeasurementDataItem.h          UEID.c
E2SM-KPM-IndicationMessage-Format3.h       MeasurementInfo-Action-Item.c  UEID-ENB.c
E2SM-KPM-IndicationMessage.h               MeasurementInfo-Action-Item.h  UEID-ENB.h
E2SM-KPM-RANfunction-Description.c         MeasurementInfo-Action-List.c  UEID-EN-GNB.c
E2SM-KPM-RANfunction-Description.h         MeasurementInfo-Action-List.h  UEID-EN-GNB.h
ENB-UE-X2AP-ID.c                           MeasurementInfoItem.c          UEID-GNB.c
ENB-UE-X2AP-ID-Extension.c                 MeasurementInfoItem.h          UEID-GNB-CU-CP-E1AP-ID-Item.c
ENB-UE-X2AP-ID-Extension.h                 MeasurementInfoList.c          UEID-GNB-CU-CP-E1AP-ID-Item.h
ENB-UE-X2AP-ID.h                           MeasurementInfoList.h          UEID-GNB-CU-CP-E1AP-ID-List.c
EUTRACellIdentity.c                        MeasurementLabel.c             UEID-GNB-CU-CP-E1AP-ID-List.h
EUTRACellIdentity.h                        MeasurementLabel.h             UEID-GNB-CU-CP-F1AP-ID-Item.c
EUTRA-CGI.c                                MeasurementRecord.c            UEID-GNB-CU-CP-F1AP-ID-Item.h
EUTRA-CGI.h                                MeasurementRecord.h            UEID-GNB-CU-F1AP-ID-List.c
FiveQI.c                                   MeasurementRecordItem.c        UEID-GNB-CU-F1AP-ID-List.h
FiveQI.h                                   MeasurementRecordItem.h        UEID-GNB-CU-UP.c
GlobalENB-ID.c                             MeasurementType.c              UEID-GNB-CU-UP.h
GlobalENB-ID.h                             MeasurementType.h              UEID-GNB-DU.c
GlobalGNB-ID.c                             MeasurementTypeID.c            UEID-GNB-DU.h
GlobalGNB-ID.h                             MeasurementTypeID.h            UEID-GNB.h
GlobalNgENB-ID.c                           MeasurementTypeName.c          UEID.h
GlobalNgENB-ID.h                           MeasurementTypeName.h          UEID-NG-ENB.c
GlobalNGRANNodeID.c                        MME-Code.c                     UEID-NG-ENB-DU.c
GlobalNGRANNodeID.h                        MME-Code.h                     UEID-NG-ENB-DU.h
GNB-CU-CP-UE-E1AP-ID.c                     MME-Group-ID.c                 UEID-NG-ENB.h
GNB-CU-CP-UE-E1AP-ID.h                     MME-Group-ID.h                 UEMeasurementReportItem.c
GNB-CU-UE-F1AP-ID.c                        MME-UE-S1AP-ID.c               UEMeasurementReportItem.h
GNB-CU-UE-F1AP-ID.h                        MME-UE-S1AP-ID.h               UEMeasurementReportList.c
GNB-ID.c                                   NativeReal.c                   UEMeasurementReportList.h
GNB-ID.h                                   NativeReal.h
GranularityPeriod.c                        NGENB-CU-UE-W1AP-ID.c
```