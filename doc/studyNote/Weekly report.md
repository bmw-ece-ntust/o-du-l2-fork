# Weekly report

Start Date: 2024/09/10
Summary: Enabled OSC DU High to receive RX_Data and CRC indication while addressing issues with RACH reception and Message4 processing.
Status: Done
Assign: Ming 咚咚 [銘鴻]

![image.png](image%2033.png)

This week, I successfully enabled OSC DU High to receive RX_Data and CRC indication, moving forward to the next step of handling the F1AP Initial UL RRC Message Transfer and DL RRC Message Transfer. Currently, the OSC DU High program stops when preparing to send Message4 for the UE RRC setup.

Before tackling the Message4 issue, I noticed another problem: although the UE and OAI PNF only send the RACH indication once, the OSC DU High reception state does not clear, resulting in the program continually receiving messages. This disrupts the processing of subsequent messages, and the UE's count keeps increasing.

I have a solution in mind to conditionally clear the reception state after processing the RACH indication once. However, this approach prevents the correct reception of Message3 (due to the UL_TTI transmission timing) and also disrupts the subsequent F1AP processing. I believe I can find a more complete solution with better condition checks to address both issues (RACH repeated reception and not receiving MSG3). Once resolved, I will focus on solving the OSC DU High issue of not sending Message4 after processing F1AP.

[https://viewer.diagrams.net/?tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI chart.drawio#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1_aKW_1MaCjcsYj9sIVtSJ8CLodyT1LyX%26export%3Ddownload](https://viewer.diagrams.net/?tags=%7B%7D&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI%20chart.drawio#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1_aKW_1MaCjcsYj9sIVtSJ8CLodyT1LyX%26export%3Ddownload)

![image.png](image%2034.png)

### Why wasn't OSC DU High receiving RX_Data and CRC indication?

While tracing the code, I found that OSC's `unpackRxData` uses a switch-case to handle different processes based on the `lcId` sent from the PNF. However, the `lcId` (MAC_LCID_CCCH_48BIT) from OAI Layer1 did not have an implemented case in OSC's code, causing the switch case to break without further processing. In contrast, the `MAC_LCID_CCCH` case was fully implemented, which led to an infinite loop, causing OSC DU High to not receive RX_Data.

I then traced the OAI implementation and found that OAI handles both `MAC_LCID_CCCH_48BIT` and `MAC_LCID_CCCH` in the same case. So, I modified OSC's switch-case to combine both `MAC_LCID_CCCH_48BIT` and `MAC_LCID_CCCH`, and the issue was resolved.

### OSC DU High not clearing the reception state

At this stage, I'm still investigating the issue. When debugging, I usually keep various hypotheses in mind, such as:

- Does OSC have a reason for maintaining this state for successful further processing?
- Could the changes I made to SIB1, RA, or RAR have caused this result?
- OAI does not have this issue, so I can't easily reference it for a solution.

Many of my solutions have been inspired by OAI's implementation, so I will start by assuming there is an error in OSC that requires setting the RACH reception status properly while ensuring F1AP can be sent successfully.

<aside>
💡

Adding a flowchart will make it easier for everyone to understand.

</aside>