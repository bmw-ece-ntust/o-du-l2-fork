# Paging message (PCH)

Start Date: 2024/09/08
Summary: Paging messages are transmitted to the user equipment (UE) through the PCH transport channel, which operates based on specific paging occasions calculated by L2/L3 software.
Status: Done
Assign: Ming 咚咚 [銘鴻]

## 2.2.5.2 PCH

The PCH transport channel is used to transmit paging messages to the UE. The UE has specific paging occasions where it listens for paging information Figure 2-28. The L2/L3 software is responsible for calculating the correct paging occasion for a UE. The PHY is only responsible for transmitting PCH PDUs when instructed by the DL_TTI.request message.
The PCH procedure is shown in Figure 2-28. To transmit a PCH PDU the L2/L3 software must provide the following information:

- In DL_TTI.request a PDSCH PDU and PDCCH PDU are included.

![image.png](image%2024.png)