# Design MSG2 function

Start Date: 2024/06/18
Summary: Designing the MSG2 function for efficient communication between the UE and Layer1 during RACH procedures.
Status: In progress
Assign: 陳奕全

After received RACH.indication from Layer1 (UE send MSG1)

Scheduler fills pdcch and pdsch info for RAR into the `rarAlloc` struct
LowerMAC will fillPdcchPdu and fillPdschPdu into (n)FAPI struct and through DL_tti.req send to Layer1, and at the same slot fillRarTxDataReq into (n)FAPI struct and through TX_data.req send to Layer1.

![Untitled](Untitled%2038.png)

https://viewer.diagrams.net/?border=0&tags={}&title=Eurecom.drawio#Uhttps://drive.google.com/uc?id=1W_o7Se11USgVPska8-t5i0JgpRSCQf4h&export=download

![Untitled](Untitled%2039.png)