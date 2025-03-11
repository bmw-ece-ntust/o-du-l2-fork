# Fix can’t encode MIB to ASN.1

Start Date: 2024/07/04
Summary: Fixing issues related to encoding MIB to ASN.1 in BCCH-BCH messages.
Status: Done
Assign: Ming 咚咚 [銘鴻]

```
juil. 04 15:16:12 <BCCH-BCH-Message>
juil. 04 15:16:12     <message>
juil. 04 15:16:12         <mib>
juil. 04 15:16:12             <systemFrameNumber>
juil. 04 15:16:12                 000011
juil. 04 15:16:12             </systemFrameNumber>
juil. 04 15:16:12             <subCarrierSpacingCommon><scs30or120/></subCarrierSpacingCommon>
juil. 04 15:16:12             <ssb-SubcarrierOffset>0</ssb-SubcarrierOffset>
juil. 04 15:16:12             <dmrs-TypeA-Position><pos2/></dmrs-TypeA-Position>
juil. 04 15:16:12             <pdcch-ConfigSIB1>
juil. 04 15:16:12                 <controlResourceSetZero>12</controlResourceSetZero>
juil. 04 15:16:12                 <searchSpaceZero>0</searchSpaceZero>
juil. 04 15:16:12             </pdcch-ConfigSIB1>
juil. 04 15:16:12             <cellBarred><notBarred/></cellBarred>
juil. 04 15:16:12             <intraFreqReselection><notAllowed/></intraFreqReselection>
juil. 04 15:16:12             <spare>
juil. 04 15:16:12                 0
juil. 04 15:16:12             </spare>
juil. 04 15:16:12         </mib>
juil. 04 15:16:12     </message>
juil. 04 15:16:12 </BCCH-BCH-Message>
```

```
<BCCH-BCH-Message>
 七  04 21:08:05     <message>
 七  04 21:08:05         <mib>
 七  04 21:08:05             <systemFrameNumber>
 七  04 21:08:05                 000000
 七  04 21:08:05             </systemFrameNumber>
 七  04 21:08:05             <subCarrierSpacingCommon><scs30or120/></subCarrierSpacingCommon>
 七  04 21:08:05             <ssb-SubcarrierOffset>0</ssb-SubcarrierOffset>
 七  04 21:08:05             <dmrs-TypeA-Position><pos2/></dmrs-TypeA-Position>
 七  04 21:08:05             <pdcch-ConfigSIB1>
 七  04 21:08:05                 <controlResourceSetZero>12</controlResourceSetZero>
 七  04 21:08:05                 <searchSpaceZero>0</searchSpaceZero>
 七  04 21:08:05             </pdcch-ConfigSIB1>
 七  04 21:08:05             <cellBarred><notBarred/></cellBarred>
 七  04 21:08:05             <intraFreqReselection><notAllowed/></intraFreqReselection>
 七  04 21:08:05             <spare>
 七  04 21:08:05                 0
 七  04 21:08:05             </spare>
 七  04 21:08:05         </mib>
 七  04 21:08:05     </message>
 七  04 21:08:05 </BCCH-BCH-Message>
```

ERROR show:

```
 七  04 21:08:05 ERROR  -->  DU APP: Could not encode BCCH BCH Message Type structure(at BIT STRING)
 七  04 21:08:05 
 七  04 21:08:05 ERROR  -->  Failed to build MIB PDU
```

Then, I found struct → `systemFrameNumber` and `spare` need to check

```c
/* MIB */
typedef struct MIB {
	BIT_STRING_t	 systemFrameNumber;
	long	 subCarrierSpacingCommon;
	long	 ssb_SubcarrierOffset;
	long	 dmrs_TypeA_Position;
	PDCCH_ConfigSIB1_t	 pdcch_ConfigSIB1;
	long	 cellBarred;
	long	 intraFreqReselection;
	BIT_STRING_t	 spare;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MIB_t;
```

```
 七  04 22:56:49 [0m<BCCH-BCH-Message>
 七  04 22:56:49     <message>
 七  04 22:56:49         <mib>
 七  04 22:56:49             <systemFrameNumber>
 七  04 22:56:49                 000001
 七  04 22:56:49             </systemFrameNumber>
 七  04 22:56:49             <subCarrierSpacingCommon><scs30or120/></subCarrierSpacingCommon>
 七  04 22:56:49             <ssb-SubcarrierOffset>0</ssb-SubcarrierOffset>
 七  04 22:56:49             <dmrs-TypeA-Position><pos2/></dmrs-TypeA-Position>
 七  04 22:56:49             <pdcch-ConfigSIB1>
 七  04 22:56:49                 <controlResourceSetZero>12</controlResourceSetZero>
 七  04 22:56:49                 <searchSpaceZero>0</searchSpaceZero>
 七  04 22:56:49             </pdcch-ConfigSIB1>
 七  04 22:56:49             <cellBarred><notBarred/></cellBarred>
 七  04 22:56:49             <intraFreqReselection><notAllowed/></intraFreqReselection>
 七  04 22:56:49             <spare>
 七  04 22:56:49                 0
 七  04 22:56:49             </spare>
 七  04 22:56:49         </mib>
 七  04 22:56:49     </message>
 七  04 22:56:49 </BCCH-BCH-Message>
```

- Sometimes OSC send correct MIB but OAI can’t decode MIB correctly

```
 七  11 21:27:25 [0m<BCCH-BCH-Message>
 七  11 21:27:25     <message>
 七  11 21:27:25         <mib>
 七  11 21:27:25             <systemFrameNumber>
 七  11 21:27:25                 000010
 七  11 21:27:25             </systemFrameNumber>
 七  11 21:27:25             <subCarrierSpacingCommon><scs15or60/></subCarrierSpacingCommon>
 七  11 21:27:25             <ssb-SubcarrierOffset>0</ssb-SubcarrierOffset>
 七  11 21:27:25             <dmrs-TypeA-Position><pos2/></dmrs-TypeA-Position>
 七  11 21:27:25             <pdcch-ConfigSIB1>
 七  11 21:27:25                 <controlResourceSetZero>0</controlResourceSetZero>
 七  11 21:27:25                 <searchSpaceZero>0</searchSpaceZero>
 七  11 21:27:25             </pdcch-ConfigSIB1>
 七  11 21:27:25             <cellBarred><barred/></cellBarred>
 七  11 21:27:25             <intraFreqReselection><allowed/></intraFreqReselection>
 七  11 21:27:25             <spare>
 七  11 21:27:25                 0
 七  11 21:27:25             </spare>
 七  11 21:27:25         </mib>
 七  11 21:27:25     </message>
 七  11 21:27:25 </BCCH-BCH-Message>
```