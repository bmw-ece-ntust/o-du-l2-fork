# Current integration OSC and OAI status

Start Date: 2024/05/30
Summary: Integration status and preliminary results of OSC and OAI projects, including message evaluations and system logs.
Status: padding
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

<aside>
💡  Both messages sent through OSC's `DL_TTI.request`and `TX_data.request` are identical to those sent through OAI. We have: `MIB` 、`DCI` 、`SIB1`

</aside>

| **`DL_TTI.request`** |  |
| --- | --- |
|  | powerControlOffsetSS |
| **`TX_data.request`** |  |
|  | rbStart  |
|  | rbSize  |
|  | powerControlOffset  |
|  | powerControlOffsetSS  |
|  | maintenance_parms_v3.ldpcBaseGraph |
|  | maintenance_parms_v3.tbSizeLbrmBytes |
| **`config.request`** |  |
|  |  |
- **`DL_TTI.request`** is modified by the source.
    - [Force **pdcch_pdu** value (powerControlOffsetSS)](Force%20pdcch_pdu%20value%20(powerControlOffsetSS)%2012110098314381dd8e75c98fca7687df.md)
    - `rb_start` is hard code in unpack nfapi → [Force **pdsch_pdu** value (rbStart)](Force%20pdsch_pdu%20value%20(rbStart)%2012110098314381498ca1fe618fe04995.md)
- **`TX_data.request`** is modified by the source.
    - First step: [Try to Force TX_Data.request TLV value](Try%20to%20Force%20TX_Data%20request%20TLV%20value%201211009831438124bdb7e1380e268758.md)
    - OSC not impelment is hard code
        - [OSC SIB1 miss ue_TimersAndConstants](OSC%20SIB1%20miss%20ue_TimersAndConstants%20121100983143813b86a8c43fcccb68f1.md)
- **P5 `config.request`** is modified by the source.
    - First step: [Try to Fill P5 config.req as OAI](Try%20to%20Fill%20P5%20config%20req%20as%20OAI%2012110098314381a38b03fe3bd29c91a6.md)
    - [OSC Integration by fix P5 message](OSC%20Integration%20by%20fix%20P5%20message%20121100983143818faab3ecfcbb67dac6.md)

## MIB

```c
 五  30 21:27:49 [0m[HW]   Connection to 127.0.0.1:4043 established
 五  30 21:27:49 [0m[HW]   connect() to 127.0.0.1:4043 failed, errno(111)
 五  30 21:27:50 [0m[PHY]   [SCHED][UE] Check absolute frequency DL 3619200000.000000, UL 3619200000.000000 (RF card 0, oai_exit 0, channel 0, rx_num_channels 1)
 五  30 21:27:50 [0m[93m[NR_PHY]   Starting sync detection
 五  30 21:27:50 [0m[PHY]   [UE thread Synch] Running Initial Synch 
 五  30 21:27:50 [0m[PHY]   [UE] nr_synchro_time: Sync source (nid2) = 0, Peak found at pos 188880, val = 8707632712 (99 dB power over signal avg 58 dB), ffo 0.000000
 五  30 21:27:50 [0m[PHY]   PSS execution duration 72951 microseconds 
 五  30 21:27:50 [0m[93m[NR_PHY]   SSS detected, PCI: 0, ffo_pss 0.000000 (0 Hz), ffo_sss 0.000507 (15 Hz),  ffo_pss+ffo_sss 0.000507 (15 Hz), nid1: 0, nid2: 0
 五  30 21:27:50 [0m[NR_MAC]   slot 0 Sending DL indication to MAC. 1 PDU type 1 of 1 total number of PDUs 
 五  30 21:27:50 [0m[NR_RRC]   [UE 0] Received SDU for NR-BCCH-DL-SCH on SRB 5 from gNB 0
 五  30 21:27:50 [0m[PHY]   [UE0] Initial sync: pbch decoded sucessfully, ssb index 0
 五  30 21:27:50 [0m[PHY]   [UE0] In synch, rx_offset 184320 samples
 五  30 21:27:50 [0m[PHY]   [UE 0] Measured Carrier Frequency offset 0 Hz
 五  30 21:27:50 [0m[32m[PHY]   Initial sync successful
 五  30 21:27:50 [0m[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
 五  30 21:27:50 [0m[PHY]   Got synch: hw_slot_offset 12, carrier off 0 Hz, rxgain 0.000000 (DL 3619200000.000000 Hz, UL 3619200000.000000 Hz)
 五  30 21:27:50 [0m[32m[PHY]   UE synchronized! decoded_frame_rx=32 UE->init_sync_frame=1 trashed_frames=18
 五  30 21:27:50 [0m[PHY]   Resynchronizing RX by 184320 samples
```

## DCI

```c
 五  30 21:27:54 [0m(36.0) Received dci indication (rnti ffff,dci format 0,n_CCE 0,payloadSize 39,payload 2d01140000)
 五  30 21:27:54 [PHY]   [UE  0] AbsSubFrame 36.0: DCI 1 of 1 total DCIs found --> rnti ffff : format 0
 五  30 21:27:54 [0m[PHY]   [UE 0] nr_slot_rx 0, harq_pid 0 (1), BWP start 27, rb_start 0, nb_rb 16, symbol_start 2, nb_symbols 10, DMRS mask 244, Nl 1
 五  30 21:27:54 [0m[PHY]   LDPCoutput = 7c
 五  30 21:27:54 [0m[PHY]   p_b = 7c
 五  30 21:27:54 [0m[NR_MAC]   slot 0 Sending DL indication to MAC. 1 PDU type 2 of 1 total number of PDUs 
 五  30 21:27:54 [0m[NR_MAC]   Decoding NR-BCCH-DL-SCH-Message (SIB1 or SI)
 五  30 21:27:54 [0m[NR_RRC]   [UE 0] Received SDU for NR-BCCH-DL-SCH on SRB 3 from gNB 0
```

## SIB1

```c
...
 五  30 21:27:54                     <t319><ms400/></t319>
 五  30 21:27:54                 </ue-TimersAndConstants>
 五  30 21:27:54             </systemInformationBlockType1>
 五  30 21:27:54         </c1>
 五  30 21:27:54     </message>
 五  30 21:27:54 </BCCH-DL-SCH-Message>
 五  30 21:27:54 [32m[NR_RRC]   SIB1 decoded
 五  30 21:27:54 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 五  30 21:27:54 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 
 ...

 五  30 21:27:55 [0m[NR_MAC]   slot 0 Sending DL indication to MAC. 1 PDU type 1 of 1 total number of PDUs 
 五  30 21:27:55 [0m[1;31m[PHY]   [UE 0] frame 182, nr_slot_rx 0, Error decoding PBCH!
 五  30 21:27:55 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 五  30 21:27:55 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 五  30 21:27:55 [0m[NR_MAC]   Initialization of 4-step contention-based random access procedure
 五  30 21:27:55 [0m[NR_MAC]   PRACH scheduler: Selected RO Frame 183, Slot 19, Symbol 0, Fdm 0
 五  30 21:27:55 [0m[PHY]   PRACH [UE 0] in frame.slot 183.19, placing PRACH in position 700, msg1 frequency start 82 (k1 82), preamble_offset 1, first_nonzero_root_idx 0
 五  30 21:27:55 [0m[PHY]   In nr_ue_prach_procedures: [UE 0][RAPROC][183.19]: Generated PRACH Msg1 (TX power PRACH -30 dBm, digital power 42 dBW (amp 512)
 五  30 21:27:55 [0m
```