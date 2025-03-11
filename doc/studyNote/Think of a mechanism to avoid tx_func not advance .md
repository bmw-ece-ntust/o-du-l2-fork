# Think of a mechanism to avoid tx_func not advance too much

Start Date: 2024/04/26
Summary: Develop a mechanism to ensure that the transmission function (tx_func) does not advance excessively ahead of the reception process.
Status: Reject
Assign: 陳奕全

- Before the PNF socket receives TX_Data from VNF 106/0, according to the print log of tx_data->pnf_p7_slot_ind(), it has already completed execution for 106/0, and even progressed to 106/2 or 106/3, causing pnf_phy_tx_data_req to miss the chance of being called.
    
    

<aside>
👀 I see. There is a conceptual problem in the RFsim, that it can be much faster than RX. I cannot readily tell you an answer, but maybe try to understand why tx_func is so much in advance. Then, we can think of a mechanism to not advance too much .

</aside>

[https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=0FgPUjF3F-U6_w06v1H8&title=Eurecom.drawio#Uhttps://drive.google.com/uc?id=1W_o7Se11USgVPska8-t5i0JgpRSCQf4h&export=download](https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=0FgPUjF3F-U6_w06v1H8&title=Eurecom.drawio#Uhttps://drive.google.com/uc?id=1W_o7Se11USgVPska8-t5i0JgpRSCQf4h&export=download)