# monolithic-UE log

Start Date: 2024/09/30
Summary: Monolithic-UE log records the initialization and operation details of a user equipment (UE) within a 5G network environment.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: LOG

```c
CMDLINE: "./nr-uesoftmodem" "-r" "106" "--numerology" "1" "--band" "78" "-C" "3619200000" "--sa" "--uicc0.imsi" "001010000000001" "--rfsim" 
[CONFIG] debug flags: 0x00400000
log init done
[ENB_APP]   nfapi (0) running mode: MONOLITHIC
[UTIL]   threadCreate() for Tpool0_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool1_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool2_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool3_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool4_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool5_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool6_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool7_-1: creating thread with affinity ffffffff, priority 97
[OPT]   OPT disabled
shlib_path libldpc.so
[LOADER] library libldpc.so successfully loaded
[HW]   Version: Branch: develop Abrev. Hash: ccdabb4c2c Date: Tue Sep 24 08:16:36 2024 +0000
[UTIL]   Opened socket oaitun_ue1 with fd nas_sock_fd[0]=97
[PDCP]   UE pdcp will use tun interface
[NR_MAC]   [UE0] Initializing MAC
[NR_MAC]   Initializing dl and ul config_request. num_slots = 20
[RLC]   Activated srb0 for UE 0
[RLC]   SRB0 already exists for UE 0, do nothing
[PHY]   Set UE_fo_compensation 0, UE_scan_carrier 0, UE_no_timing_correction 0 
, chest-freq 0, chest-time 0
[PHY]   Set UE nb_rx_antenna 1, nb_tx_antenna 1, threequarter_fs 0, ssb_start_subcarrier 516
[PHY]   SA init parameters. DL freq 3619200000 UL offset 0 SSB numerology 1 N_RB_DL 106
[PHY]   Init: N_RB_DL 106, first_carrier_offset 1412, nb_prefix_samples 144,nb_prefix_samples0 176, ofdm_symbol_size 2048
[PHY]   samples_per_subframe 61440/per second 61440000, wCP 57344
[PHY]   Initializing UE vars for gNB TXant 1, UE RXant 1
shlib_path libdfts.so
[LOADER] library libdfts.so successfully loaded
[PHY]   prs_config configuration NOT found..!! Skipped configuring UE for the PRS reception
[PHY]   Doing symbol rotation calculation for TX/RX, f0 3619200000.000000 Hz, Nsymb 28
[PHY]   Doing symbol rotation calculation for TX/RX, f0 3619200000.000000 Hz, Nsymb 28
[PHY]   UE 0 Setting N_TA_offset to 800 samples (factor 2.000000, UL Freq 3619200000, N_RB 106, mu 1)
[PHY]   HW: Configuring card 0, sample_rate 61440000.000000, tx/rx num_channels 1/1, duplex_mode TDD
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_gain 0, rx_gain 110
[PHY]   HW: Configuring card 1, sample_rate 61440000.000000, tx/rx num_channels 1/1, duplex_mode TDD
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_gain 0, rx_gain 110
[PHY]   HW: Configuring card 2, sample_rate 61440000.000000, tx/rx num_channels 1/1, duplex_mode TDD
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_gain 0, rx_gain 110
[PHY]   HW: Configuring card 3, sample_rate 61440000.000000, tx/rx num_channels 1/1, duplex_mode TDD
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_gain 0, rx_gain 110
[PHY]   HW: Configuring card 4, sample_rate 61440000.000000, tx/rx num_channels 1/1, duplex_mode TDD
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_gain 0, rx_gain 110
[PHY]   HW: Configuring card 5, sample_rate 61440000.000000, tx/rx num_channels 1/1, duplex_mode TDD
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_gain 0, rx_gain 110
[PHY]   HW: Configuring card 6, sample_rate 61440000.000000, tx/rx num_channels 1/1, duplex_mode TDD
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_gain 0, rx_gain 110
[PHY]   HW: Configuring card 7, sample_rate 61440000.000000, tx/rx num_channels 1/1, duplex_mode TDD
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200000 Hz, rx_freq 3619200000 Hz, tune_offset 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_gain 0, rx_gain 110
[PHY]   Intializing UE Threads for instance 0 ...
[UTIL]   threadCreate() for UEthread_0: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for L1_UE_stats_0: creating thread with affinity ffffffff, priority 1
UE threads created by 4138989
TYPE <CTRL-C> TO TERMINATE
[NR_RRC]   create TASK_RRC_NRUE 
[UTIL]   threadCreate() for TASK_RRC_NRUE: creating thread with affinity ffffffff, priority 50
shlib_path librfsimulator.so
[LOADER] library librfsimulator.so successfully loaded
[HW]   Running as client: will connect to a rfsimulator server side
[UTIL]   threadCreate() for TASK_NAS_NRUE: creating thread with affinity ffffffff, priority 50
Initializing random number generator, seed 10405771219905811990
[HW]   [RRU] has loaded RFSIMULATOR device.
[HW]   Trying to connect to 127.0.0.1:4043
[HW]   Connection to 127.0.0.1:4043 established
[HW]   connect() to 127.0.0.1:4043 failed, errno(0)
[SIM]   UICC simulation: IMSI=001010000000001, IMEISV=6754567890123413, Ki=fec86ba6eb707ed08905757b1bb44b8f, OPc=c42449363bbad02b66d16bc975d77cc1, DNN=oai, SST=0x01, SD=0xffffff
[PHY]   SSB position provided
[NR_PHY]   Starting sync detection
[PHY]   [UE thread Synch] Running Initial Synch 
[NR_PHY]   Starting cell search with center freq: 3619200000, bandwidth: 106. Scanning for 1 number of GSCN.
[NR_PHY]   Scanning GSCN: 0, with SSB offset: 516, SSB Freq: 0.000000
[PHY]   Initial sync: pbch decoded sucessfully, ssb index 0
[PHY]   pbch rx ok. rsrp:51 dB/RE, adjust_rxgain:-1 dB
[NR_PHY]   Cell Detected with GSCN: 0, SSB SC offset: 516, SSB Ref: 0.000000, PSS Corr peak: 99 dB, PSS Corr Average: 61
[PHY]   [UE0] In synch, rx_offset 491520 samples
[PHY]   [UE 0] Measured Carrier Frequency offset 16 Hz
[PHY]   Initial sync successful, PCI: 0
[PHY]   HW: Configuring channel 0 (rf_chain 0): setting tx_freq 3619200016 Hz, rx_freq 3619200016 Hz, tune_offset 0
[PHY]   Got synch: hw_slot_offset 32, carrier off 16 Hz, rxgain 0.000000 (DL 3619200016.000000 Hz, UL 3619200016.000000 Hz)
[PHY]   UE synchronized! decoded_frame_rx=112 UE->init_sync_frame=1 trashed_frames=70
[PHY]   Resynchronizing RX by 491520 samples
[HW]   received write reorder clear context
[HW]   Gap in writing to USRP: last written 113049599, now 113140959, gap 91360
[NR_RRC]   SIB1 decoded
[NR_PHY]   ============================================
[NR_PHY]   [UE 0] Harq round stats for Downlink: 1/0/0
[NR_PHY]   ============================================
[NR_PHY]   ============================================
[NR_PHY]   [UE 0] Harq round stats for Downlink: 1/0/0
[NR_PHY]   ============================================
[NR_MAC]   Initialization of 4-step contention-based random access procedure
[NR_MAC]   PRACH scheduler: Selected RO Frame 263, Slot 19, Symbol 0, Fdm 0
[PHY]   PRACH [UE 0] in frame.slot 263.19, placing PRACH in position 2828, msg1 frequency start 0 (k1 0), preamble_offset 0, first_nonzero_root_idx 0
[NR_MAC]   [UE 0][RAPROC][RA-RNTI 0005] Got BI RAR subPDU 267 ms
[NR_MAC]   [UE 0][RAPROC][RA-RNTI 010b] Got RAPID RAR subPDU
[NR_MAC]   [UE 0][RAPROC][264.7] Found RAR with the intended RAPID 1
[MAC]   received TA command 31
[PHY]   RAR-Msg2 decoded
[NR_MAC]   [RAPROC][264.17] RA-Msg3 transmitted
[MAC]   [UE 0]Frame 265 Contention resolution identity: 0x12e549ac5a46 Terminating RA procedure
[MAC]   [UE 0][265.10][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
[NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
[RLC]   Added srb 1 to UE 0
[MAC]   [UE 0] Applying CellGroupConfig from gNodeB
[NR_RRC]   State = NR_RRC_CONNECTED
[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   ============================================
[NR_PHY]   [UE 0] Harq round stats for Downlink: 4/0/0
[NR_PHY]   ============================================
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   ============================================
[NR_PHY]   [UE 0] Harq round stats for Downlink: 5/0/0
[NR_PHY]   ============================================
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
[NR_PHY]   [UE 0] RSRP = -42 dBm
```