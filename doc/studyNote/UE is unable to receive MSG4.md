# UE is unable to receive MSG4

Start Date: 2024/09/24
Summary: Investigating the issue of UE not receiving MSG4 despite successful transmission from OSC DU High.
Status: padding
Assign: Ming 咚咚 [銘鴻]

## Issues defined

<aside>
💡

The current issue is that the UE cannot receive or decode MSG4 after OSC DU High sends it.

</aside>

I've already fixed the previous issue where OSC DU High couldn't send MSG4 after receiving MSG3 (details [here](Fix%20OSC%20can%E2%80%99t%20get%20MSG3%2012110098314381029eefecd420ad24ae.md)). Now, although MSG4 is sent from OSC DU High, the UE is still not receiving it. The next step is to check if the PDSCH (TX_data) is being transmitted correctly or if the data needs to be modified.

More details on the current issue can be found [here](Issues%20OSC%20DU%20MSG4%20is%20sent%20but%20the%20UE%20does%20not%20rec%2012110098314381ba89bddcafc0ae64e2.md).

| OSC DU High send MSG4 DCI (PDCCH) | ✅ |
| --- | --- |
| OSC DU High send MSG4 (PDSCH) | ✅ |
| OSC DU High send MSG4 ACK/NACK (PUCCH) | ✅ (payload needs to be checked) |
| OAI PNF receive MSG4 DCI (PDCCH) | ✅ |
| OAI PNF receive MSG4 (PDSCH) | ✅ |
| OAI PNF receive MSG4 ACK/NACK (PUCCH) | ✅ (payload needs to be checked) |
| OAI UE decode MSG4 DCI (PDCCH) | ✅ |
| OAI UE decode MSG4 (PDSCH) | ⏳ |
| OAI UE send MSG4 ACK/NACK (PUCCH) | ⏳ |
| OAI PNF send MSG4 ACK/NACK (PUCCH) | ⏳ |
| OSC DU High decode MSG4 ACK/NACK (PUCCH) | ⏳ |

### Solution

Following the issue where OSC DU High sends MSG4 but the UE does not receive it (details [here](Issues%20OSC%20DU%20MSG4%20is%20sent%20but%20the%20UE%20does%20not%20rec%2012110098314381ba89bddcafc0ae64e2.md)), the next step is to prepare and verify the following components for MSG4 transmission:

- DL_TTI for PDCCH (DCI)
- DL_TTI for PDSCH
- TX_Data for MSG4

I will check the values of each field, make any necessary revisions, and compare them with OAI settings (comparison note [here](Compare%20OSC%20DU%20send%20MSG4%201211009831438147a50bd917d4b0a91d.md)).

- [x]  DL_TTI for PDCCH
- [x]  DL_TTI for PDSCH
- [x]  TX_Data

After revising the OSC configuration (see [comparison note](Compare%20OSC%20DU%20send%20MSG4%201211009831438147a50bd917d4b0a91d.md)), the UE appears to receive MSG4 but triggers an assertion that needs fixing (issue details [here](Issues%20Assertion%20is_nr_UL_slot()%20failed%201211009831438180a3e9f623fa434c83.md)).

I resolved the assertion issue by revising MSG4's DCI (fix [here](Fix%20Revise%20MSG4%20DCI%20for%20UE%20send%20ACK%20by%20PUCCH%201211009831438127ae57f72634801405.md)).

While the UE now successfully receives MSG4 DCI (PDCCH), it still doesn't get MSG4 PDSCH. The next step is to trace the OAI UE source code to identify the root cause (tracking progress [here](UE%20is%20unable%20to%20receive%20MSG4%20PDSCH%20message%201211009831438136bf93dadd77d7f40f.md)).