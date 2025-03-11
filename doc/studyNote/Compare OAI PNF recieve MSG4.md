# Compare OAI PNF recieve MSG4

Start Date: 2024/10/10
Summary: Comparison of OAI and OSC settings in the MSG4 reception process, highlighting differences in data configurations and transmission timings.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Compare
Finish Date: 2024/10/10
SUM: 🗓️ Days Spent to Complete: 0

### When DU send compare table → [Compare OSC DU send MSG4](Compare%20OSC%20DU%20send%20MSG4%201211009831438147a50bd917d4b0a91d.md)

### When UE recieve compare table → [Compare OAI UE receive MSG4](Compare%20OAI%20UE%20receive%20MSG4%2012110098314381d690cdc975187a879a.md)

# Summary

After checking the fill data source code, the **`ShiftIndex`**, **`dci_pdu[0].ScramblingId`**, and **`dlDmrsScramblingId`** are set to the `phyCellId` value. These values differ between OSC and OAI settings, which was already known from previous debugging.

I revised the `dci_pdu[0].Payload` to enable faster UE MSG4 ACK/NACK. In the OAI setting, transmission between DU and CU is direct and quicker. However, in the OSC DU + OAI CU case, it takes 2–3 more slots. Consequently, I needed to adjust the UE ACK/NACK timing to fall within the `UL` slot interval of the TDD pattern.

## Compare PNF different

|  | OAI value | OSC value |
| --- | --- | --- |
| **BWPSize** | 48 | 48 |
| **BWPStart** | 27 | 27 |
| **SubcarrierSpacing** | 1 | 1 |
| **CyclicPrefix** | 0 | 0 |
| **StartSymbolIndex** | 0 | 0 |
| **DurationSymbols** | 1 | 1 |
| **FreqDomainResource[0]** | 255 | 255 |
| **FreqDomainResource[1]** | 0 | 0 |
| **FreqDomainResource[2]** | 0 | 0 |
| **FreqDomainResource[3]** | 0 | 0 |
| **FreqDomainResource[4]** | 0 | 0 |
| **FreqDomainResource[5]** | 0 | 0 |
| **CceRegMappingType** | 1 | 1 |
| **RegBundleSize** | 6 | 6 |
| **InterleaverSize** | 2 | 2 |
| **CoreSetType** | 0 | 0 |
| **ShiftIndex** | 0 | 1 (phyCellId) |
| **precoderGranularity** | 0 | 0 |
| **numDlDci** | 1 | 1 |
| **dci_pdu[0].RNTI** | 58657 | 100 |
| **dci_pdu[0].ScramblingId** | 0 | 1 (phyCellId) |
| **dci_pdu[0].ScramblingRNTI** | 0 | 0 |
| **dci_pdu[0].CceIndex** | 0 | 0 |
| **dci_pdu[0].AggregationLevel** | 4 | 4 |
| **dci_pdu[0].precodingAndBeamforming.num_prgs** | 0 | 0 |
| **dci_pdu[0].precodingAndBeamforming.prg_size** | 0 | 0 |
| **dci_pdu[0].precodingAndBeamforming.dig_bf_interfaces** | 0 | 0 |
| **dci_pdu[0].beta_PDCCH_1_0** | 0 | 0 |
| **dci_pdu[0].powerControlOffsetSS** | 1 | 1 |
| **dci_pdu[0].PayloadSizeBits** | 39 | 39 |
| **dci_pdu[0].Payload[0]** | 5 | 2 |
| **dci_pdu[0].Payload[1]** | 0 | 0 |
| **dci_pdu[0].Payload[2]** | 0 | 0 |
| **dci_pdu[0].Payload[3]** | 248 | 248 |
| **dci_pdu[0].Payload[4]** | 75 | 96 |
| **dci_pdu[0].Payload[5]** | 0 | 0 |
| **dci_pdu[0].Payload[6]** | 0 | 0 |
| **dci_pdu[0].Payload[7]** | 0 | 0 |
| **dci_pdu[0].Payload[8]** | 0 | 0 |
| **dci_pdu[0].Payload[9]** | 0 | 0 |
| **dci_pdu[0].Payload[10]** | 0 | 0 |
| **dci_pdu[0].Payload[11]** | 0 | 0 |
| **dci_pdu[0].Payload[12]** | 0 | 0 |
| **dci_pdu[0].Payload[13]** | 0 | 0 |
| **dci_pdu[0].Payload[14]** | 0 | 0 |
| **dci_pdu[0].Payload[15]** | 0 | 0 |
| **dci_pdu[0].Payload[16]** | 0 | 0 |
| **dci_pdu[0].Payload[17]** | 0 | 0 |
| **dci_pdu[0].Payload[18]** | 0 | 0 |
| **dci_pdu[0].Payload[19]** | 0 | 0 |
| **DLTTI PDSCH** |  |  |
| **pduBitmap** | 0 | 0 |
| **rnti** | 58657 | 100 |
| **pduIndex** | 0 | 0 |
| **targetCodeRate[0]** | 1200 | 1200 |
| **qamModOrder[0]** | 2 | 2 |
| **mcsIndex[0]** | 0 | 0 |
| **mcsTable[0]** | 0 | 0 |
| **rvIndex[0]** | 0 | 0 |
| **TBSize[0]** | 149 | 116 |
| **dataScramblingId** | 0 | 1 |
| **nrOfLayers** | 1 | 1 |
| **transmissionScheme** | 0 | 0 |
| **dlDmrsSymbPos** | 2180 | 2180 |
| **dmrsConfigType** | 0 | 0 |
| **dlDmrsScramblingId** | 0 | 1 (phyCellId) |
| **SCID** | 0 | 0 |
| **numDmrsCdmGrpsNoData** | 2 | 2 |
| **dmrsPorts** | 1 | 1 |
| **resourceAlloc** | 1 | 1 |
| **rbStart** | 0 | 0 |
| **rbSize** | 42 | 28 |
| **VRBtoPRBMapping** | 0 | 0 |
| **StartSymbolIndex** | 1 | 1 |
| **NrOfSymbols** | 13 | 13 |
| **num_prgs** | 1 | 1 |
| **prg_size** | 275 | 275 |
| **dig_bf_interfaces** | 1 | 1 |
| **pm_idx[0]** | 0 | 0 |
| **beam_idx[0][0]** | 0 | 0 |
| **powerControlOffset** | 0 | 0 |
| **powerControlOffsetSS** | 0 | 0 |
| **ldpcBaseGraph** | 2 | 2 |
| **tbSizeLbrmBytes** | 92200 | 92200 |