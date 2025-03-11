# UE Segmentation fault after Generating RRCSetupComplete

Start Date: 2024/10/14
Summary: Debugging a segmentation fault issue in UE after generating RRCSetupComplete in a 5G NR context.
Status: In progress
Assign: Ming 咚咚 [銘鴻]
Tags: PIN, SR

![image.png](image%2072.png)

![{89B1770B-9180-4075-907D-8263609C61EA}.png](89B1770B-9180-4075-907D-8263609C61EA.png)

![image.png](image%2073.png)

## Error logs and GDB logs

```jsx
[NR_RRC]   SIB1 decoded
[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
[NR_PHY]   ============================================
[NR_PHY]   Harq round stats for Downlink: 1/0/0
[NR_PHY]   ============================================
[NR_PHY]   ============================================
[NR_PHY]   Harq round stats for Downlink: 1/0/0
[NR_PHY]   ============================================
[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
[NR_MAC]   Initialization of 4-step contention-based random access procedure
[NR_MAC]   PRACH scheduler: Selected RO Frame 167, Slot 19, Symbol 0, Fdm 0
[PHY]   PRACH [UE 0] in frame.slot 167.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 0, first_nonzero_root_idx 0
[NR_MAC]   Trying to process acknack for an inactive harq process (0)
[NR_MAC]   [UE 0][RAPROC][RA-RNTI 0005] Got BI RAR subPDU 267 ms
[NR_MAC]   [UE 0][RAPROC][RA-RNTI 010b] Got RAPID RAR subPDU
[NR_MAC]   [UE 0][RAPROC][168.12] Found RAR with the intended RAPID 0
[MAC]   received TA command 31
[PHY]   RAR-Msg2 decoded
[NR_MAC]   [RAPROC][168.19] RA-Msg3 transmitted
[MAC]   [UE 0]Frame 169 Contention resolution identity: 0x1f223c8231e6 Terminating RA procedure
[MAC]   [UE 0][169.15][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
[NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
[RLC]   Added srb 1 to UE 0
[MAC]   Applying CellGroupConfig from gNodeB
[NR_RRC]   State = NR_RRC_CONNECTED
 十  14 17:14:45 [0m[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
 十  14 17:14:45 [0m[NR_MAC]   BWP ID: 0
 十  14 17:14:45 [0m[NR_MAC]   SCS: 1
 十  14 17:14:45 [0m[NR_MAC]   BWP Size: 106
 十  14 17:14:45 [0m[NR_MAC]   BWP Start: 0
 十  14 17:14:45 [0m[NR_MAC]   RACH Config Common: 0x719a88001e40
 十  14 17:14:45 [0m[NR_MAC]   TDA List Common: 0x719a88002030
 十  14 17:14:45 [0m[NR_MAC]   PUCCH Config Common: 0x719a88002290
 十  14 17:14:45 [0m[NR_MAC]   Msg3 Delta Preamble: 0
 十  14 17:14:45 [0m[NR_MAC]   Transform Precoding: 0
 十  14 17:14:45 [0m[NR_MAC]   MCS Table: 0
 十  14 17:14:45 [0m[NR_MAC]   DCI Format: 0
 十  14 17:14:45 [0m[NR_MAC]   Max FB Time: 0
 
Thread 8 "Tpool6_-1" received signal SIGSEGV, Segmentation fault.
[Switching to Thread 0x7ffff3400640 (LWP 382284)]
nr_update_sr (mac=0x7fffef000010) at /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:1184
1184          if (check_pucchres_for_pending_SR(pucch_Config, lc_info->sr_id)) {
(gdb) bt
#0  nr_update_sr (mac=0x7fffef000010) at /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:1184
#1  nr_ue_ul_scheduler (mac=mac@entry=0x7fffef000010, ul_info=ul_info@entry=0x7ffff33ff440)
    at /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:1358
#2  0x0000555555922b25 in nr_ue_ul_indication (ul_info=0x7ffff33ff440)
    at /home/hpe/openairinterface5g/openair2/NR_UE_PHY_INTERFACE/NR_IF_Module.c:1152
#3  0x000055555582f20f in processSlotTX (arg=0x7fffe005eb80) at /home/hpe/openairinterface5g/executables/nr-ue.c:586
#4  0x000055555585feb9 in one_thread (arg=0x5555563a3e50) at /home/hpe/openairinterface5g/common/utils/threadPool/thread-pool.h:102
#5  0x00007ffff7294ac3 in start_thread (arg=<optimized out>) at ./nptl/pthread_create.c:442
#6  0x00007ffff7326850 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
```

### Compare with only OAI UE logs

```jsx
 十  14 16:53:42 [0m[PHY]   RAR-Msg2 decoded
 十  14 16:53:43 [0m[32m[NR_MAC]   [RAPROC][184.19] RA-Msg3 transmitted
 十  14 16:53:43 [0m[MAC]   [UE 0]Frame 185 Contention resolution identity: 0x14f0e3d94e46 Terminating RA procedure
 十  14 16:53:43 [0m[32m[MAC]   [UE 0][185.10][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
 十  15 11:06:10 [0m[NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
 十  15 11:06:10 [0m[RLC]   Added srb 1 to UE 0
 十  15 11:06:10 [0m[MAC]   Applying CellGroupConfig from gNodeB
 十  15 11:06:10 [0m[NR_MAC]   Configuring UL BWP 0
 十  15 11:06:10 [0m[NR_MAC]   Configuring ul_dedicated
                 [0m[NR_MAC]   Configuring PUCCH
 十  15 11:06:10 [0m[NR_RRC]   State = NR_RRC_CONNECTED
 十  15 11:06:10 [0m[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
 十  15 11:06:10 [0m[NR_MAC]   BWP ID: 0
 十  15 11:06:10 [0m[NR_MAC]   SCS: 1
 十  15 11:06:10 [0m[NR_MAC]   BWP Size: 106
 十  15 11:06:10 [0m[NR_MAC]   BWP Start: 0
 十  15 11:06:10 [0m[NR_MAC]   RACH Config Common: 0x7fc7f8002260
 十  15 11:06:10 [0m[NR_MAC]   TDA List Common: 0x7fc7f8002450
 十  15 11:06:10 [0m[NR_MAC]   PUSCH Config: 0x7fc7f800b330
 十  15 11:06:10 [0m[NR_MAC]   PUCCH Config: 0x7fc7f800add0
 十  15 11:06:10 [0m[NR_MAC]   PUCCH Config Common: 0x7fc7f80026b0
 十  15 11:06:10 [0m[NR_MAC]   SRS Config: 0x7fc7f800b550
 十  15 11:06:10 [0m[NR_MAC]   Msg3 Delta Preamble: 1
 十  15 11:06:10 [0m[NR_MAC]   Transform Precoding: 0
 十  15 11:06:10 [0m[NR_MAC]   MCS Table: 0
 十  15 11:06:10 [0m[NR_MAC]   DCI Format: 0
 十  15 11:06:10 [0m[NR_MAC]   Max FB Time: 0
 十  14 17:13:56 [0m[NR_MAC]   Checking PUCCH resources for SR ID 0, pucch_Config->schedulingRequestResourceToAddModList->list.count 1
 十  14 16:53:43 [0m[NR_PHY]   ============================================
 十  14 16:53:43 [0m[NR_PHY]   Harq round stats for Downlink: 4/0/0
 十  14 16:53:43 [0m[NR_PHY]   ============================================
```

## Final Solution

---

unknow

## Debugging Process

---

[compare freq-hop PUCCH](compare%20freq-hop%20PUCCH%2012110098314381f88babffd9e6371e2e.md) 

From the logs, it can be determined that the OAI PNF received the PUCCH, but it can be seen from the UE side that the PUCCH data was not filled in.

[Trace OAI dl_rrc_message_transfer](Trace%20OAI%20dl_rrc_message_transfer%2012610098314380e89639c87d5243b362.md) 

Detailed Analysis of UE SR Transmission and RRC Connection Setup in 5G NR → [**NR RRC Connection Setup Flow**](NR%20RRC%20Connection%20Setup%20Flow%20199100983143801b8726f22625e4eb0b.md) 

[**PUCCH_Config__schedulingRequestResource in 5G NR**](PUCCH_Config__schedulingRequestResource%20in%205G%20NR%2019a10098314380e280e9ef4063fef923.md) 

---

Currently, we have implemented unit tests for encoding and decoding F1AP ASN.1 structures. These tests work successfully in OSC, but the OAI UE cannot fully decode all values. We have two potential solutions: First, we can wait for Nokia to resolve their compiler issues → [Radisys Weekly meeting](https://www.notion.so/Radisys-Weekly-meeting-122100983143803b8082e67b4501d2f8?pvs=21) , which should fix all related problems. Alternatively, we can attempt to use the compiler that OAI uses in OSC → [Fix ASN.1 compiler issues](Fix%20ASN%201%20compiler%20issues%201221009831438019ae05ee8563d9a476.md).

✅ Found temporary solution independently [How to Fix OSC asn1c Issues](How%20to%20Fix%20OSC%20asn1c%20Issues%20176100983143804bb9f3fd6a511b919c.md) 

## Known Issues

[No **Triggering SR for ID 0**](No%20Triggering%20SR%20for%20ID%200%201981009831438004b9c3effedda319d2.md)