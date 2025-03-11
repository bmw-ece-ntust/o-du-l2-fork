# Revise OSC DU DL_TTI PDSCH RB size

Start Date: 2024/10/11
Summary: Revise the constant value for numDmrsRePerPrb in OSC to align with OAI's calculation for TBS and PRB size integration.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/15
SUM: 🗓️ Days Spent to Complete: 4

After fully understand how to compute TBS and PRB size, I found in OSC is const value 12 for `numDmrsRePerPrb` , in OAI is calcuate by `dmrs_info.N_PRB_DMRS` * `dmrs_info.N_DMRS_SLOT`  = 12 * 3, so for intergration I need to revise const value in OSC is 12*3.

# Path reference:

| OAI UE decode number_rbs (RB size) | **nr_ue_process_dci_freq_dom_resource_assignment**
openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_procedures.c |
| --- | --- |
| OAI UE compute TBS (use RBsize) | **nr_ue_process_dci_dl_10**
openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_procedures.c |
| OAI VNF fill SIB1 RBsize | **schedule_control_sib1
OnlyOAI/openairinterface5g/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_bch.c** |
| OSC DU fill SIB1 TBS and RBsize | **fillSchSib1Cfg**
mwnl-odu-at-oai-based-on-scf/l2/src/5gnrsch/sch.c |
| OSC DU fill freqDomResAssign | **OAI_OSC_fillSib1DlDciPdu
mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/lwr_mac_fsm.c** |

## OSC DU

|  | MCS | RB start | number_rbs (rbSize) | start synbol | number of symbol | PDU_length | **dlDmrsSymbPos** | TBS (tb size) |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| SIB1 | 5 | 0 | 12 | 2 | 10 | 88 | 580 | 88 |
| MSG2 (RAR) | 0 | 0 | 4 | 1 | 13 | 14 | 2180 | 14 |
| MSG4 | 0 | 0 | 33 | 1 | 13 | 128 | 2180 | 116 |

## Current status

```jsx
 十  13 15:10:08 [0m[PHY]   Updating harq_status for harq_id 0, ack/nak 1
 十  13 15:10:08 [0m[NR_MAC]   ul config in slot 18
 十  13 15:10:08 [0m[MAC]   In [169.15] Handling DLSCH PDU type 3
 十  13 15:10:08 [0m[MAC]   pduP: 0x7f34805dd760, pdu_len: 116
 十  13 15:10:08 [0m[MAC]   [169.15]: processing PDU 0 (with length 116) of 1 total number of PDUs...
 十  13 15:10:08 [0m[MAC]   [UE] LCID 62, PDU length 116
 十  13 15:10:08 [0m[MAC]   [UE 0]Frame 169 Contention resolution identity: 0x1c50b01e0526 Terminating RA procedure
 十  13 15:10:08 [0m[32m[MAC]   [UE 0][169.15][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
 十  13 15:10:08 [0m[MAC]   [UE] LCID 0, PDU length 109
 十  13 15:10:08 [0m[MAC]   [UE] LCID 63, PDU length 4
 十  13 15:10:08 [0m[NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
 十  13 15:10:08 [0m[PHY]   Copying pucch pdu to UE PHY
 十  13 15:10:08 [0m[RLC]   Added srb 1 to UE 0
 十  13 15:10:08 [0m[MAC]   Applying CellGroupConfig from gNodeB
 十  13 15:10:08 [0m[NR_RRC]   State = NR_RRC_CONNECTED
 十  13 15:10:08 [0m[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
 十  13 15:10:08 [0m
```