# Fix problem (HARQ,sdu_len,PBCH)

Start Date: 2024/04/23
Summary: Fixing issues related to HARQ, sdu_len, and PBCH in a telecommunications protocol implementation.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 Main Problem

</aside>

> before the PNF socket receives TX_Data from VNF 106/0, according to the print log of tx_data->pnf_p7_slot_ind(), it has already completed execution for 106/0, and even progressed to 106/2 or 106/3, causing pnf_phy_tx_data_req to miss the chance of being called.
> 

Robert:

I see. There is a conceptual problem in the RFsim, that it can be much faster than RX. I cannot readily tell you an answer, but maybe try to understand why tx_func is so much in advance. Then, we can think of a mechanism to not advance too much .

→ [chain of Layer1 thread (tx_func, rx_func, ru)](https://www.notion.so/chain-of-Layer1-thread-tx_func-rx_func-ru-121100983143810298dbff12aa6a6515?pvs=21) 

<aside>
💡 Try to find a good solution

</aside>

- 🔥 Current solution is → [let `PNF` send slot.indication slow about 300us](let%20PNF%20send%20slot%20indication%20slow%20about%20300us%20121100983143814e93f4ed641a2ed780.md)
- 🔥 When [HW] A client connects, sending the current time, which is when the UE sim starts execution, the slot offset between the PNF and VNF, originally differing by two slots, will become zero slots apart. This is the source of the issue.

```c
[HW]   A client connects, sending the current time
```

- 🔥 I also have another question. Currently, when '[HW] A client connects, sending the current time' appears in the LOG, the interval between each slot.indication of PNF speeds up from the original 1.2ms to almost 10us. Is this normal? (I suspect it might be because there is no message to process, hence the acceleration, but it seems a bit too fast, doesn't it?)
    - Solve note → [Fix no SIB1](Fix%20no%20SIB1%20121100983143814db9cbf280e3ce6c23.md) → not solution
- Current issues

[https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=4OUmYvqLlam8OXf4rA_K&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=4OUmYvqLlam8OXf4rA_K&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)

After using copy UL.tti PDU directly, the ping delay is reduced.

If reuse usleep in RFsim

![Untitled](b307bcf2-5112-449a-a862-a20b265cb549.png)

![Untitled](Untitled%2017.png)

So, it is cause by Rfsim usleep()

- Make sure PNF in correct time send `slot.indication`

![Untitled](Untitled%2018.png)

- 🔥 If you add the configuration in the VNF script: `--MACRLCs.[0].ulsch_max_frame_inactivity 0`, the RRT will reduce to about 10ms.

![Untitled](Untitled%2019.png)

# Problem List

- [ ]  HARQ
- [ ]  **sdu_len**
- [ ]  **PBCH**
- [x]  **Msg3_frame → no occure**
- [ ]  `tx_func` too fast, sometimes is 10us per slot
- [x]  socket is too slow → current is quickly
- [x]  Maybe Fix hash [`71e2546cc9be9615310fd4685af412def5cfd63c`](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/71e2546cc9be9615310fd4685af412def5cfd63c) will fix → already fix

I believe the current issue primarily stems from the git revert of usleep(1000) in RFsim, resulting in the slot execution of tx_func being faster than PNF. For instance, many times, before the PNF socket receives TX_Data from VNF 106/0, according to the print log of tx_data->pnf_p7_slot_ind(), it has already completed execution for 106/0, and even progressed to 106/2 or 106/3, causing pnf_phy_tx_data_req to miss the chance of being called. I think this is no longer an issue of TX_Data processing taking too long.

Currently, I have two ideas:

1. Find a way to make VNF transmit earlier.
2. Shift the SFN/SL of tx_func forward by at least 1 to 2 slots.

![Untitled](Untitled%2020.png)

If slot_ahead = 4 will fix lots of **`sdu_len` issues**

![Untitled](Untitled%2021.png)

## Got a big problem is `tx_func` too fast, sometimes is 10us per slot

![Untitled](Untitled%2022.png)

## socket is too slow

I use my PC run a sample socket `UDP` localhost is about 20~30 us, but in `nfapi-fixes` it always execute 250~500 us.

[socket.c](socket.c)

## Log Links

### PNF

[nfapi-split-script/LOG/PNF-nfapi-fixes.log at cabb8e261619ee5c22bf45ab5b7af3d377482196 · dong881/nfapi-split-script](https://github.com/dong881/nfapi-split-script/blob/cabb8e261619ee5c22bf45ab5b7af3d377482196/LOG/PNF-nfapi-fixes.log)

### VNF

[nfapi-split-script/LOG/VNF-nfapi-fixes.log at cabb8e261619ee5c22bf45ab5b7af3d377482196 · dong881/nfapi-split-script](https://github.com/dong881/nfapi-split-script/blob/cabb8e261619ee5c22bf45ab5b7af3d377482196/LOG/VNF-nfapi-fixes.log)

### UE

[nfapi-split-script/LOG/UE-nfapi-fixes.log at cabb8e261619ee5c22bf45ab5b7af3d377482196 · dong881/nfapi-split-script](https://github.com/dong881/nfapi-split-script/blob/cabb8e261619ee5c22bf45ab5b7af3d377482196/LOG/UE-nfapi-fixes.log)

### TX_data problem

```bash
avril 23 10:29:26 [0m[93m1713860966.057490 [NR_MAC]   UE bdbe expected HARQ pid 10 feedback at  447. 7, but is at  457. 7 instead (HARQ feedback is in the past)
avril 23 10:29:26 [0m[1;31m1713860966.068722 [NR_MAC]   UE bdbe: Could not find a HARQ process at  459.18!
avril 23 10:29:26 [0m[93m1713860966.103170 [NR_MAC]   UE bdbe expected HARQ pid 14 feedback at  467.17, but is at  467. 9 instead (HARQ feedback is in the future)
avril 23 10:29:26 [0m[1;31m1713860966.103185 [NR_MAC]   UE bdbe: Could not find a HARQ process at  467. 9!
```

```bash
avril 23 10:29:55 Assertion (harq->sdu_len > 0) failed!
avril 23 10:29:55 In nr_generate_pdsch() /home/chen/openairinterface5g/openair1/PHY/NR_TRANSPORT/nr_dlsch.c:115
avril 23 10:29:55 no HARQ SDU present
avril 23 10:29:55 
avril 23 10:29:55 Assertion (harq->sdu_len > 0) failed!
avril 23 10:29:55 In nr_generate_pdsch() /home/chen/openairinterface5g/openair1/PHY/NR_TRANSPORT/nr_dlsch.c:115
avril 23 10:29:55 no HARQ SDU present
```

```bash
avril 23 10:29:22 [0m[NR_PHY]   ============================================
avril 23 10:29:22 [0m[NR_PHY]   Harq round stats for Downlink: 148/2/0
avril 23 10:29:22 [0m[NR_PHY]   ============================================
avril 23 10:29:22 [0m[1;31m[NR_MAC]   Invalid CCCH message!, pdu_len: 80
avril 23 10:29:22 [0m[1;31m[PHY]   [UE 0] frame 642, nr_slot_rx 0, Error decoding PBCH!
avril 23 10:29:22 [0m[1;31m[PHY]   [UE 0] frame 644, nr_slot_rx 0, Error decoding PBCH!
avril 23 10:29:22 [0m[1;31m[PHY]   [UE 0] frame 646, nr_slot_rx 0, Error decoding PBCH!
avril 23 10:29:22 [0m[1;31m[PHY]   [UE 0] frame 648, nr_slot_rx 0, Error decoding PBCH!
avril 23 10:29:22 [0m[1;31m[NR_MAC]   Invalid CCCH message!, pdu_len: 80
avril 23 10:29:23 [0m[NR_PHY]   ============================================
avril 23 10:29:23 [0m[NR_PHY]   Harq round stats for Downlink: 155/2/0
avril 23 10:29:23 [0m[NR_PHY]   ============================================
```

---

```
avril 23 11:09:29 Assertion (future_ul_tti_req->SFN == ra->Msg3_frame && future_ul_tti_req->Slot == ra->Msg3_slot) failed!
avril 23 11:09:29 In nr_add_msg3() /home/chen/openairinterface5g/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_RA.c:1142
avril 23 11:09:29 future UL_tti_req's frame.slot 881.17 does not match PUSCH 690.17
avril 23 11:09:29 
avril 23 11:09:29 Exiting execution
avril 23 11:09:29 /home/chen/openairinterface5g/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_RA.c:1142 nr_add_msg3() Exiting OAI softmodem: _Assert_Exit_
```

PNF fill tx_data into buffer is a bit slow, lead to NO HARQ SDU

![Untitled](Untitled%2023.png)

|  |  |
| --- | --- |
| 50 us |  |
| 61 us |  |