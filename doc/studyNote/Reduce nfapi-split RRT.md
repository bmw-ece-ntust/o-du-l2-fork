# Reduce nfapi-split RRT

Start Date: 2024/04/08 → 2024/04/30
Summary: The project focuses on reducing round-trip time (RRT) in nfapi-split by optimizing UL_TTI processing and implementing various fixes to improve performance and stability.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全
Tags: Robert Task

The RTT with nfapi was initially high, averaging 100–200ms, and a previous change adding usleep(1000) in RFsim caused an assertion failure: Assertion (((prach_id >= 0) && (prach_id < 8))) failed!. The root cause was traced to delays in UL_TTI processing, which led to buffer overflows and triggered the assertion. To resolve this, we optimized all downlink TTI processes to reduce execution time, modified data types in the unpacking section, and introduced a new function, cp_nr_ul_tti_req, to streamline processing. As a result, the RTT was successfully reduced to 10–20ms, matching the performance of setups without nfapi.

With this fix, it is now possible to successfully implement OAI CN + OAI CU + OAI DU + OAI Layer1 + OAI RFsim + OAI UE.

<aside>
💡 Target: RRT: 22~42ms

</aside>

> Why: OAI nfapi MONOLITHIC mode is 20~40ms (Suggested by OAI Robert.)
> 

<aside>
👀 Test stability, is there any interruption or assert?

</aside>

> from avril 15 13:33:52  to avril 15 14:08:27 OK~~
> 

---

## Check PNF and VNF connection successfully.

you need to follow the following steps. 

- [**change PLMN to match OAI Core Network**](https://github.com/dong881/openairinterface5g-NTUST/commit/40544493b24ebcbe72d95f7f88ad1fccfe6dcb47)

### OAI MONOLITHIC mode

- 📝Note → [https://hackmd.io/@MingHung/NR_SA_Tutorial_OAI_nrUE](https://hackmd.io/@MingHung/NR_SA_Tutorial_OAI_nrUE)
- 💻 video → [https://youtu.be/NhayA_kw46c](https://youtu.be/NhayA_kw46c)
    
    [https://youtu.be/NhayA_kw46c](https://youtu.be/NhayA_kw46c)
    

### OAI nFAPI-split mode

- 📝 Note → [https://hackmd.io/@MingHung/VNF-PNF-split](https://hackmd.io/@MingHung/VNF-PNF-split)
- 💻 video → [https://youtu.be/eZJWNlcV6b8](https://youtu.be/eZJWNlcV6b8)
    
    [https://youtu.be/eZJWNlcV6b8](https://youtu.be/eZJWNlcV6b8)
    

## Study background about nFAPI

- Channel information
    - PCH → [PCH (notion.site)](https://www.notion.so/cb01ae92c5934592ba2af37f0aaeb759?pvs=21)
    - DL-SCH → [DL_SCH (notion.site)](https://www.notion.so/f5bceb1e250943c08e8399f992c92e94?pvs=21)
    - UL_SCH → [UL_SCH (notion.site)](https://www.notion.so/2bd2922ff760404d890c09d0c5594009?pvs=21)
    - SRS → [SRS (notion.site)](https://www.notion.so/dc0237f153be4798ae0780873fd0847f?pvs=21)
    - SCI→ [CSI (notion.site)](https://www.notion.so/9930d594258344e1923ca056d9c70982?pvs=21)
    - SR → [https://nfapi.notion.site/SR-24c5ed39adb149f388f2e541dd5b6bea?pvs=74](https://www.notion.so/24c5ed39adb149f388f2e541dd5b6bea?pvs=21)
    - Uplink Reference Signals → [Uplink Reference Signals (notion.site)](https://www.notion.so/828c28b4210e4ee38869f477578d7a05?pvs=21)
- Downlink
    
    [chain of function TX_Data](https://www.notion.so/chain-of-function-TX_Data-12110098314381a29e84d1d2ee0eb023?pvs=21)
    
    [chain of function TX_Data](https://www.notion.so/chain-of-function-TX_Data-12110098314381b1a38ad5f46d35f5f8?pvs=21)
    
- Uplink
    
    [chain of function UCI](https://www.notion.so/chain-of-function-UCI-12110098314381e1b5d2e840a4973515?pvs=21)
    
    [chain of function UL_DCI](https://www.notion.so/chain-of-function-UL_DCI-121100983143811e8c1dfc6edad9ce88?pvs=21)
    
    [chain of function UL_TTI](https://www.notion.so/chain-of-function-UL_TTI-12110098314381458393d5ff06926d75?pvs=21)
    

### Fix - Measure execution time.

| DL_TTI.request | 0.002105s | From [VNF] `oai_nfapi_dl_tti_req` to [PNF] **`nr_schedule_dl_tti_req` Finsh (include PDCCH,PDSCH,SSB,CSI_RS)** |
| --- | --- | --- |
| TX_Data.request | 0.002428s | From [VNF] **`schedule_nr_mib` to [PNF] `nr_generate_pdsch`** |
| UL_DCI.request | 0.003028s | From [VNF] **`oai_nfapi_ul_dci_req`**  **to [PNF] `nr_generate_dci`** |
| DCI.request | 0.002064s | From [VNF] **`oai_nfapi_ul_dci_req` to [PNF] `nr_generate_dci`** |
| UCI.indication | 0.001223s | From PNF `handle_nr_uci` to VNF `handle_nr_uci_pucch_0_1` (NB_scheduler_uci.c) Finish |
| RXdata.indication | 0.001006s | From PNF `handle_nr_ulsch` to VNF `nr_rx_sdu`(gNB_scheduler_ulsch.c) Finish |
| CRC.indication | 0.001179s | From PNF `handle_nr_ulsch` to VNF  `handle_nr_ul_harq` (gNB_scheduler_ulsch.c) Finish |
| UL_TTI.request | 0.009000s | From VNF `oai_nfapi_ul_tti_req` to PNF `save slot_buffer` to tx_func `nr_fill_pucch` to rx_func `nr_decode_pucch0` finish |
| ULSCH | 0.002497s | From VNF `oai_nfapi_ul_tti_req` to PNF `nr_fill_ulsch`  |
| PUCCH | 0.002424s | From VNF `oai_nfapi_ul_tti_req` to PNF `nr_fill_pucch` |
| **`nr_decode_pucch0`** | 0.006373s | From PNF `nr_fill_pucch` to [RX_func] **`nr_decode_pucch0`** |
| PRACH | 0.002056s | From VNF `oai_nfapi_ul_tti_req` to PNF `nr_fill_prach` |

### 🪛Fix - Remove **not necessary code**

This part takes up too much time, and it may not need to remain here, so remove it to reduce execution time.

[Memset on P7 messages not necessary: they will be read afterwards from rx'ed (0e8ed3ff) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/0e8ed3ff8d8ee8ed6b61b0aa5169bfff855e058a)

### 🪛Fix - Develop a new function (`cp_nr_tx_data_req`)

Initially, the task was to identify the cause of the assertion failure "hard->pdu is null." Robert provided us with a direction, suspecting that it was caused by a delay in TX_Data. He suggested measuring the execution time related to TX_Data, from its generation in the VNF, transmission through the socket, reception by the PNF, and all the way to its utilization by the PNF. Eventually, we identified two memory allocation parts that were particularly time-consuming, occurring when the PNF received TX_Data. This delay was because the PNF didn't process it immediately but instead stored it in a buffer to handle it during the next slot for transmission. Our final solution involved avoiding the use of heap memory and instead utilizing stack memory, specifically local variables. Additionally, we developed a new function to copy all data into the buffer when filling it. Moreover, we changed the type declaration of the original buffer from pointer to data storage.

After discussing with Robert, it was decided to redesign a new function (cp_nr_tx_data_req) and modify all related data structures (such as changing from storing pointers in the original buffer to storing data). Before storing each item in the buffer, the data would be copied to the buffer through a for-loop. This decision was made because the original approach of allocating tx_data on the heap and storing its pointer in the buffer for the next tx_func to use was confused due to unknown reasons causing the heap to allocate the same address each time, leading to transmission disorder.

[do not allocate tx_data on heap, introduces huge delay (e8461d15) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/e8461d1571d7405894b89b5e2aea0c4de7fad488)

### 🪛Fix - **Remove huge `memset`**

- Learn how to use `iper`. (By Robert suggest) → [Linux perf Examples (brendangregg.com)](https://www.brendangregg.com/perf.html)
- After removing it, we no longer see anything in the flame graph, but it still has a 100ms round-trip time (RTT).

[Remove huge memset that is pointless (08fa9a56) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/08fa9a569b9aa6fc12751c72854b80c282f2e267)

### 🪛Fix - get pmi info

- Issue: Whenever I use perf to measure DL traffic, PNF will be interrupted by error precoding matrix index.
- solution: After tracing pack and unpack UL_tti.request code, I found out that `pmi!=0` only when  `rel15->precodingAndBeamforming.num_prgs>0` . Therefore, I added a condition when PHY get pmi info to avoid getting error value.

[Commits · nfapi-fixes · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commits/nfapi-fixes/?ref_type=heads)

### 🪛Fix - Correcting the logic for timing_window judgment.

- Issue: The timing window judgment is incorrect when SFN/SL transitions from 1023 to 0, falsely indicating it exceeds the timing window (30 slots).
- Solution: reconsidered all conditions and rewritten the function accordingly.

[Correcting the logic for timing_window judgment. (7d17e257) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/7d17e25766dc8579a32f0e31262ecaee40f0ccca)

### 🪛Fix - Investigate High RTT

- **Allow to use multiple PUCCH at once**

<aside>
💡 We are required to store multiple PUCCH (e.g., for multiple UEs).
However, nr_fill_pucch() automatically freed the previously active PUCCH
structure. Of course(!) this does not make sense.

However, the problem is that init_nr_transport() allocated only one
PUCCH structure. Also this does not make sense to me. The problem was
that slot_ahead was 0, which logically cannot happen in this function
(because slot_ahead is illogical, we must give the radio some time). The
reason is that it uses if_inst->sl_ahead, which, prior to this commit,
was not set.

The init_nr_transport() function is called normally from main() through
init_eNB_afterRU(). In this case, we initialize if_inst->sl_ahead to
what is set in main(). In the PNF case, however, we call
init_nr_transport() from the PNF thread, when receiving the start
request. In the main(), we wait for this to happen, before setting
if_inst->sl_ahead. Hence, initializing this variable (which we should
safely be able to do) befor...

</aside>

[Allow to use multiple PUCCH at once (c971677d) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/c971677dce45e585bc94d0671598425ff1b67a54)

### 🪛Fix - Reduce RTT

The primary step is to reverse the previous commit: adding usleep(1000) in RFsim. It triggers an assertion: `Assertion (((prach_id >= 0) && (prach_id < 8))) failed!` After tracing the code, it's found that sometimes UL_TTI takes too long to execute, from VNF scheduler completion to PNF rx_func. Several instances showed significantly prolonged execution times, leading to buffer occupancy reaching full capacity and consequently triggering the assertion.

Resolution: I expedited the UL_TTI process, changed the data type in the unpack body section, and introduced a new function: **`cp_nr_ul_tti_req`**. This ultimately achieved the current RRT of approximately 10~20ms.

[Let UL_TTI speed up and newly developed cp_nr_ul_tti_req (a05184e8) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/a05184e8df85238a713d9b3aeebf08fbce29352d)

<aside>
💡 However, there are still issues present. Please refer to the relevant troubleshooting notes for further details.

[Fix problem (HARQ,**sdu_len**,**PBCH**)](Fix%20problem%20(HARQ,sdu_len,PBCH)%20121100983143812ab2f5fa41035a185c.md) 
[Refactor function](Refactor%20function%2012110098314381908db0fb056029a4fc.md)

</aside>

### 🪛Fix - Refactor `UL_TTII` and `DL_TTI`

- UL_TTI.request and DL_TTI.request: avoid big switch, make cp functions for "sub"PDUs (PRACH, ...) -> indicate Robert to integrate in nfapi-fixes

<aside>
💡 Revert "Slow down RFsim a bit for FAPI" → usleep(1000) in RFsim by Reboert two month ago. will improve RRT time.

</aside>

[Revert "Slow down RFsim a bit for FAPI" (93d6984f) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/93d6984fc18828045841c197d9a6fa94498db041)

[Refactor DL TTI request handling and improve code clarity (dff187c6) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/dff187c6c822529903f595f920a83e06d9da00c4)

[Refactor UL TTI request handling and add clarity to function logic (56e5c957) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/56e5c9576714ca072facaa4876e498e4c2fea9b5)

[do not allocate ul_dci on heap, introduces huge delay (21d6cf57) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/21d6cf574b578fb618a88126846155dce4820098)

### 🪛Fix - TDD table pack/unpack dynamically

<aside>
🗣 Robert:

regarding my idea, you can check this commit: [https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/71e2546cc9be9615310fd4685af412def5cfd63c](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/71e2546cc9be9615310fd4685af412def5cfd63c)
I needed to take that out initially. It is probably not correct. We need to fix the problem here as well.

</aside>

[nr_slot_select(): ignore frame%2 -> nFAPI wrong slot pattern? (71e2546c) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/71e2546cc9be9615310fd4685af412def5cfd63c)

I have an idea regarding the patch [71e254](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/71e2546cc9be9615310fd4685af412def5cfd63c) . I've found that the reason for the failure to execute lies in the unequal number of slots in the P5 pack and unpack. Let me start from the beginning. After configuring the tdd-UL-DL-ConfigurationCommon in the config file, the VNF converts it into a TDD table of two frame sizes based on mu.
`int nb_slots_to_set = TDD_CONFIG_NB_FRAMES*(1<<mu)*NR_NUMBER_OF_SUBFRAMES_PER_FRAME;`
In our current scenario where mu equals 1, this means 40 slots. However, during packing, the VNF hard-codes it to only 20 slots. Subsequently, the PNF declares a hard-coded size of 40 slots and unpacks only 20 slots of the TDD table. As a result, the PNF receives a complete frame table along with another frame that is empty. This seems to pose a serious issue because an empty slot in the TDD table represents the Downlink.
and I just finished modifying the code,
[https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/74a8ac35a83001f0fb6c9b920ef05dd8d0aad205](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/74a8ac35a83001f0fb6c9b920ef05dd8d0aad205)
and now it can dynamically pack and unpack. Could you take a look? I'm also puzzled about why there are two frames. The TDD table should have 10 slots appearing cyclically, so there shouldn't be a need for 'if (nr_frame%2 == 0)', and it might not even need to be related to 'mu'.

<aside>
💡 [**nr_slot_select(): ignore frame%2 -> nFAPI wrong slot pattern?**](nr_slot_select()%20ignore%20frame%252%20-%20nFAPI%20wrong%20slot%2012110098314381588efbcb0b17a82049.md)

Improve the execution speed of RFsim

---

</aside>

[Fix P5 packing and unpacking issue for TDD table (74a8ac35) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/74a8ac35a83001f0fb6c9b920ef05dd8d0aad205)

### 🪛Fix - Final issues solution

I believe the current issue primarily stems from the git revert of usleep(1000) in RFsim, resulting in the slot execution of tx_func being faster than PNF. For instance, many times, before the PNF socket receives TX_Data from VNF 106/0, according to the print log of tx_data->pnf_p7_slot_ind(), it has already completed execution for 106/0, and even progressed to 106/2 or 106/3, causing pnf_phy_tx_data_req to miss the chance of being called. I think this is no longer an issue of TX_Data processing taking too long.Currently, I have two ideas:

1. Find a way to make VNF transmit earlier.

2. Shift the SFN/SL of tx_func forward by at least 1 to 2 slots.

![Untitled](Untitled%202.png)

After making modifications to the TDD table, the remaining issue from before is that the `TX_DATA` is arriving too late, leading to an assertion failure `(harq->sdu_len > 0)`. Last time, I mentioned that the `tx_func` was too fast. However, I've made a new discovery:
Although it speeds up after `UE` connects, there's a change in timing for when the `VNF` sends data to the `PNF` after `UE` connection. This change results in a delay of one slot_ahead. Consequently, the `pnf_phy_tx_data_req` is executed slot_ahead slots earlier, causing errors (even when I adjust slot_ahead to 2 or 1, the same phenomenon occurs). This appears to be a problem caused by some slot synchronization process after `UE` connection.
So, I have another idea. After measurement, the speed from `VNF` to `PNF` is quite fast. I think it seems feasible to set `slot_ahead = 0`. I've already made the necessary code changes, but the current conclusion is that the `UE` sim won't be able to acquire `SIB1` because I'm unfamiliar with the `UE` sim part.

→  I've drawn a picture to represent the content I want to convey more clearly.

[https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=4OUmYvqLlam8OXf4rA_K&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=4OUmYvqLlam8OXf4rA_K&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)

<aside>
💡 we keep "VNF slot ahead" of 2 (e.g., for network deployment with VNF/PNF on different machines), but PNF needs to wait -> in slot indication, measure slot duration and wait to not be faster in slot than 300us

</aside>

[Ensure Proper Timing for VNF and PNF Slot Allocation (1fd2d958) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/1fd2d9580c3eefe9c3d058cc78808db847a9d0f9)

<aside>
🗣 Robert:

measure iperf throughput in monolithic and clarify why less in nFAPI split (assuming both monolithic and nFAPI are 40MHz, SISO, RFsim)

</aside>

```c
PING 192.168.70.135 (192.168.70.135) from 10.0.0.8 oaitun_ue1: 56(84) bytes of data.
64 bytes from 192.168.70.135: icmp_seq=1 ttl=63 time=5.75 ms
64 bytes from 192.168.70.135: icmp_seq=2 ttl=63 time=18.6 ms
64 bytes from 192.168.70.135: icmp_seq=3 ttl=63 time=20.2 ms
64 bytes from 192.168.70.135: icmp_seq=4 ttl=63 time=19.4 ms
64 bytes from 192.168.70.135: icmp_seq=5 ttl=63 time=16.2 ms
64 bytes from 192.168.70.135: icmp_seq=6 ttl=63 time=14.2 ms
64 bytes from 192.168.70.135: icmp_seq=7 ttl=63 time=17.3 ms
64 bytes from 192.168.70.135: icmp_seq=8 ttl=63 time=13.1 ms
64 bytes from 192.168.70.135: icmp_seq=9 ttl=63 time=13.8 ms
64 bytes from 192.168.70.135: icmp_seq=10 ttl=63 time=24.3 ms
64 bytes from 192.168.70.135: icmp_seq=11 ttl=63 time=14.6 ms
64 bytes from 192.168.70.135: icmp_seq=12 ttl=63 time=14.2 ms
64 bytes from 192.168.70.135: icmp_seq=13 ttl=63 time=21.1 ms
64 bytes from 192.168.70.135: icmp_seq=14 ttl=63 time=17.8 ms
64 bytes from 192.168.70.135: icmp_seq=15 ttl=63 time=26.2 ms
64 bytes from 192.168.70.135: icmp_seq=16 ttl=63 time=15.5 ms
64 bytes from 192.168.70.135: icmp_seq=17 ttl=63 time=16.4 ms
64 bytes from 192.168.70.135: icmp_seq=18 ttl=63 time=16.2 ms
64 bytes from 192.168.70.135: icmp_seq=19 ttl=63 time=13.8 ms
64 bytes from 192.168.70.135: icmp_seq=20 ttl=63 time=34.0 ms
64 bytes from 192.168.70.135: icmp_seq=21 ttl=63 time=14.7 ms
64 bytes from 192.168.70.135: icmp_seq=22 ttl=63 time=16.4 ms
64 bytes from 192.168.70.135: icmp_seq=23 ttl=63 time=14.7 ms
--- 192.168.70.135 ping statistics ---
23 packets transmitted, 23 received, 0% packet loss, time 22028ms
rtt min/avg/max/mdev = 5.751/17.324/33.990/5.348 ms
```

```c
$ iperf3 -c 192.168.70.135 -B 10.0.0.5 -t 40 -R
Connecting to host 192.168.70.135, port 5201
Reverse mode, remote host 192.168.70.135 is sending
[  5] local 10.0.0.5 port 48361 connected to 192.168.70.135 port 5201
[ ID] Interval           Transfer     Bitrate
[  5]   0.00-1.00   sec  5.76 MBytes  48.3 Mbits/sec
[  5]   1.00-2.00   sec  10.6 MBytes  88.6 Mbits/sec
[  5]   2.00-3.00   sec  9.28 MBytes  77.8 Mbits/sec
[  5]   3.00-4.00   sec  10.1 MBytes  85.0 Mbits/sec
[  5]   4.00-5.00   sec  10.6 MBytes  89.3 Mbits/sec
[  5]   5.00-6.00   sec  11.7 MBytes  98.0 Mbits/sec
[  5]   6.00-7.00   sec  10.7 MBytes  89.9 Mbits/sec
[  5]   7.00-8.00   sec  11.3 MBytes  94.8 Mbits/sec
[  5]   8.00-9.00   sec  10.2 MBytes  85.2 Mbits/sec
[  5]   9.00-10.00  sec  11.3 MBytes  95.1 Mbits/sec
[  5]  10.00-11.00  sec  10.7 MBytes  89.6 Mbits/sec
[  5]  11.00-12.00  sec  11.3 MBytes  94.5 Mbits/sec
[  5]  12.00-13.00  sec  10.5 MBytes  88.5 Mbits/sec
[  5]  13.00-14.00  sec  10.4 MBytes  87.5 Mbits/sec
[  5]  14.00-15.00  sec  7.65 MBytes  64.2 Mbits/sec
[  5]  15.00-16.00  sec  10.9 MBytes  91.3 Mbits/sec
[  5]  16.00-17.00  sec  10.5 MBytes  88.4 Mbits/sec
[  5]  17.00-18.00  sec  10.9 MBytes  91.3 Mbits/sec
[  5]  18.00-19.00  sec  10.3 MBytes  86.1 Mbits/sec
[  5]  19.00-20.00  sec  10.7 MBytes  89.8 Mbits/sec
[  5]  20.00-21.00  sec  10.5 MBytes  88.2 Mbits/sec
[  5]  21.00-22.00  sec  11.2 MBytes  93.6 Mbits/sec
[  5]  22.00-23.00  sec  10.4 MBytes  87.3 Mbits/sec
[  5]  23.00-24.00  sec  10.6 MBytes  89.5 Mbits/sec
[  5]  24.00-25.00  sec  10.2 MBytes  85.3 Mbits/sec
[  5]  25.00-26.00  sec  8.96 MBytes  75.2 Mbits/sec
[  5]  26.00-27.00  sec  7.46 MBytes  62.6 Mbits/sec
[  5]  27.00-28.00  sec  11.0 MBytes  92.4 Mbits/sec
[  5]  28.00-29.00  sec  9.55 MBytes  80.1 Mbits/sec
[  5]  29.00-30.00  sec  10.4 MBytes  87.4 Mbits/sec
[  5]  30.00-31.00  sec  9.71 MBytes  81.5 Mbits/sec
[  5]  31.00-32.00  sec  10.4 MBytes  87.6 Mbits/sec
[  5]  32.00-33.00  sec  9.80 MBytes  82.2 Mbits/sec
[  5]  33.00-34.00  sec  10.6 MBytes  88.7 Mbits/sec
[  5]  34.00-35.00  sec  10.3 MBytes  86.3 Mbits/sec
[  5]  35.00-36.00  sec  10.3 MBytes  86.7 Mbits/sec
[  5]  36.00-37.00  sec  9.85 MBytes  82.6 Mbits/sec
[  5]  37.00-38.00  sec  9.37 MBytes  78.6 Mbits/sec
[  5]  38.00-39.01  sec  8.22 MBytes  68.5 Mbits/sec
[  5]  39.01-40.00  sec  9.79 MBytes  82.6 Mbits/sec
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bitrate         Retr
[  5]   0.00-40.05  sec   408 MBytes  85.4 Mbits/sec  448             sender
[  5]   0.00-40.00  sec   404 MBytes  84.8 Mbits/sec                  receiver
iperf Done.
```

```c
$ ./ping
[sudo] password for chen: 
PING 192.168.70.135 (192.168.70.135) from 10.0.0.2 oaitun_ue1: 56(84) bytes of data.
64 bytes from 192.168.70.135: icmp_seq=1 ttl=63 time=18.4 ms
64 bytes from 192.168.70.135: icmp_seq=2 ttl=63 time=19.9 ms
64 bytes from 192.168.70.135: icmp_seq=3 ttl=63 time=21.0 ms
64 bytes from 192.168.70.135: icmp_seq=4 ttl=63 time=20.2 ms
64 bytes from 192.168.70.135: icmp_seq=5 ttl=63 time=16.2 ms
64 bytes from 192.168.70.135: icmp_seq=6 ttl=63 time=7.05 ms
64 bytes from 192.168.70.135: icmp_seq=7 ttl=63 time=19.4 ms
64 bytes from 192.168.70.135: icmp_seq=8 ttl=63 time=7.80 ms
^C
--- 192.168.70.135 ping statistics ---
8 packets transmitted, 8 received, 0% packet loss, time 7008ms
rtt min/avg/max/mdev = 7.051/16.247/20.999/5.270 ms
```

```c
$ ./iperf-client
Connecting to host 192.168.70.135, port 5201
Reverse mode, remote host 192.168.70.135 is sending
[  5] local 10.0.0.3 port 36359 connected to 192.168.70.135 port 5201
[ ID] Interval           Transfer     Bitrate
[  5]   0.00-1.00   sec  7.99 MBytes  67.1 Mbits/sec                  
[  5]   1.00-2.00   sec  13.2 MBytes   111 Mbits/sec                  
[  5]   2.00-3.00   sec  13.3 MBytes   112 Mbits/sec                  
[  5]   3.00-4.00   sec  13.9 MBytes   117 Mbits/sec                  
[  5]   4.00-5.00   sec  13.1 MBytes   110 Mbits/sec                  
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bitrate         Retr
[  5]   0.00-5.04   sec  64.9 MBytes   108 Mbits/sec    0             sender
[  5]   0.00-5.00   sec  61.6 MBytes   103 Mbits/sec                  receiver

iperf Done.
```

Figure 14. The current DL traffic throughput of the nFAPI mode gNB