# F1SetupResponse

```bash
 十  23 12:00:26 DEBUG   -->  F1AP : Received flat buffer to be decoded : 40104000404e020105240106ffffff80674e422d45757265636f6d2d43550301100040b400fffffff110000010010ffffffaa0affffff80000ffffffc74031130
 十  23 12:00:26 <F1AP-PDU>
 十  23 12:00:26     <successfulOutcome>
 十  23 12:00:26         <procedureCode>1</procedureCode>
 十  23 12:00:26         <criticality><reject/></criticality>
 十  23 12:00:26         <value>
 十  23 12:00:26             <F1SetupResponse>
 十  23 12:00:26                 <protocolIEs>
 十  23 12:00:26                     <F1SetupResponseIEs>
 十  23 12:00:26                         <id>78</id>
 十  23 12:00:26                         <criticality><reject/></criticality>
 十  23 12:00:26                         <value>
 十  23 12:00:26                             <TransactionID>1</TransactionID>
 十  23 12:00:26                         </value>
 十  23 12:00:26                     </F1SetupResponseIEs>
 十  23 12:00:26                     <F1SetupResponseIEs>
 十  23 12:00:26                         <id>82</id>
 十  23 12:00:26                         <criticality><ignore/></criticality>
 十  23 12:00:26                         <value>
 十  23 12:00:26                             <GNB-CU-Name>gNB-Eurecom-CU</GNB-CU-Name>
 十  23 12:00:26                         </value>
 十  23 12:00:26                     </F1SetupResponseIEs>
 十  23 12:00:26                     <F1SetupResponseIEs>
 十  23 12:00:26                         <id>3</id>
 十  23 12:00:26                         <criticality><reject/></criticality>
 十  23 12:00:26                         <value>
 十  23 12:00:26                             <Cells-to-be-Activated-List>
 十  23 12:00:26                                 <ProtocolIE-SingleContainer>
 十  23 12:00:26                                     <id>4</id>
 十  23 12:00:26                                     <criticality><reject/></criticality>
 十  23 12:00:26                                     <value>
 十  23 12:00:26                                         <Cells-to-be-Activated-List-Item>
 十  23 12:00:26                                             <nRCGI>
 十  23 12:00:26                                                 <pLMN-Identity>00 F1 10</pLMN-Identity>
 十  23 12:00:26                                                 <nRCellIdentity>
 十  23 12:00:26                                                     000000000000000000000000000000000001
 十  23 12:00:26                                                 </nRCellIdentity>
 十  23 12:00:26                                             </nRCGI>
 十  23 12:00:26                                             <nRPCI>1</nRPCI>
 十  23 12:00:26                                         </Cells-to-be-Activated-List-Item>
 十  23 12:00:26                                     </value>
 十  23 12:00:26                                 </ProtocolIE-SingleContainer>
 十  23 12:00:26                             </Cells-to-be-Activated-List>
 十  23 12:00:26                         </value>
 十  23 12:00:26                     </F1SetupResponseIEs>
 十  23 12:00:26                     <F1SetupResponseIEs>
 十  23 12:00:26                         <id>170</id>
 十  23 12:00:26                         <criticality><reject/></criticality>
 十  23 12:00:26                         <value>
 十  23 12:00:26                             <RRC-Version>
 十  23 12:00:26                                 <latest-RRC-Version>
 十  23 12:00:26                                     000
 十  23 12:00:26                                 </latest-RRC-Version>
 十  23 12:00:26                                 <iE-Extensions>
 十  23 12:00:26                                     <RRC-Version-ExtIEs>
 十  23 12:00:26                                         <id>199</id>
 十  23 12:00:26                                         <criticality><ignore/></criticality>
 十  23 12:00:26                                         <extensionValue>
 十  23 12:00:26                                             <Latest-RRC-Version-Enhanced>11 03 00</Latest-RRC-Version-Enhanced>
 十  23 12:00:26                                         </extensionValue>
 十  23 12:00:26                                     </RRC-Version-ExtIEs>
 十  23 12:00:26                                 </iE-Extensions>
 十  23 12:00:26                             </RRC-Version>
 十  23 12:00:26                         </value>
 十  23 12:00:26                     </F1SetupResponseIEs>
 十  23 12:00:26                 </protocolIEs>
 十  23 12:00:26             </F1SetupResponse>
 十  23 12:00:26         </value>
 十  23 12:00:26     </successfulOutcome>
 十  23 12:00:26 </F1AP-PDU>
```