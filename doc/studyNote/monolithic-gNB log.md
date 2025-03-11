# monolithic-gNB log

Start Date: 2024/09/30
Summary: Logging and analyzing the performance of a monolithic gNB (next-generation NodeB) implementation for 5G networks.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: LOG

```c
hpe@hpe-ProLiant-DL380-Gen10:~/OnlyOAI/nfapi-split-script$ ./monolithic-gNB 
CMDLINE: "./nr-softmodem" "-O" "../../../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb.sa.band78.fr1.106PRB.usrpb210.conf" "--gNBs.[0].min_rxtxtime" "6" "--rfsim" "--sa" 
[LIBCONFIG] Path for include directive set to: ../../../targets/PROJECTS/GENERIC-NR-5GC/CONF
[CONFIG] function config_libconfig_init returned 0
[CONFIG] config module libconfig loaded
[CONFIG] debug flags: 0x00000000
log init done
Reading in command-line options
[ENB_APP]   nfapi (0) running mode: MONOLITHIC
[GNB_APP]   Getting GNBSParams
Configuration: nb_rrc_inst 1, nb_nr_L1_inst 1, nb_ru 1
configuring for RAU/RRU
[OPT]   OPT disabled
[HW]   Version: Branch: develop Abrev. Hash: ccdabb4c2c Date: Tue Sep 24 08:16:36 2024 +0000
[NR_PHY]   RC.gNB = 0x5d058f963be0
[NR_PHY]   PRB blacklist 
[NR_PHY]   Copying 0 blacklisted PRB to L1 context
[PHY]   L1_RX_THREAD_CORE -1 (15)
[PHY]   TX_AMP = 519 (-36 dBFS)
Initializing northbound interface for L1
[PHY]   l1_north_init_gNB() RC.nb_nr_L1_inst:1
[PHY]   Installing callbacks for IF_Module - UL_indication
[MAC]   Allocating shared L1/L2 interface structure for instance 0 @ 0x5d058f96c420
[PHY]   l1_north_init_gNB() RC.gNB[0] installing callbacks
[PHY]   create_gNB_tasks() Task ready initialize structures
[PHY]   No prs_config configuration found..!!
[GNB_APP]   pdsch_AntennaPorts N1 1 N2 1 XP 1 pusch_AntennaPorts 1
[GNB_APP]   minTXRXTIME 6
[GNB_APP]   SIB1 TDA 1
[GNB_APP]   CSI-RS 1, SRS 1, 256 QAM may be on, delta_MCS off, maxMIMO_Layers -1, HARQ feedback enabled, num DLHARQ:16, num ULHARQ:16
[GNB_APP]   sr_ProhibitTimer 0, sr_TransMax 64, sr_ProhibitTimer_v1700 0, t300 400, t301 400, t310 2000, n310 10, t311 3000, n311 1, t319 400
[RRC]   Read in ServingCellConfigCommon (PhysCellId 0, ABSFREQSSB 641280, DLBand 78, ABSFREQPOINTA 640008, DLBW 106,RACH_TargetReceivedPower -96
[RRC]   absoluteFrequencySSB 641280 corresponds to 3619200000 Hz
[MAC]   [MAIN] Init function start:nb_nr_macrlc_inst=1
[UTIL]   threadCreate() for MAC_STATS: creating thread with affinity ffffffff, priority 2
[PHY]   Installing callbacks for IF_Module - UL_indication
[NR_MAC]   Configuring common parameters from NR ServingCellConfig
[NR_MAC]   DL_Bandwidth:40
[NR_MAC]   DL_Bandwidth:40
[NR_MAC]   ssb_OffsetPointA 86, ssb_SubcarrierOffset 0
[NR_MAC]   Set RX antenna number to 1, Set TX antenna number to 1 (num ssb 1: 80000000,0)
[NR_MAC]   Setting TDD configuration period to 6
DL frequency 3619200000: band 48, UL frequency 3619200000
[PHY]   DL frequency 3619200000 Hz, UL frequency 3619200000 Hz: band 48, uldl offset 0 Hz
[PHY]   Configuring MIB for instance 0, : (Nid_cell 0,DL freq 3619200000, UL freq 3619200000)
[PHY]   Initializing frame parms for mu 1, N_RB 106, Ncp 0
[PHY]   Init: N_RB_DL 106, first_carrier_offset 1412, nb_prefix_samples 144,nb_prefix_samples0 176, ofdm_symbol_size 2048
[PHY]   Doing symbol rotation calculation for TX/RX, f0 3619200000.000000 Hz, Nsymb 28
[PHY]   Doing symbol rotation calculation for TX/RX, f0 3619200000.000000 Hz, Nsymb 28
[PHY]   gNB 0 configured
[NR_MAC]   PUSCH Target 150, PUCCH Target 200, PUCCH Failure 10, PUSCH Failure 10
[NR_RRC]   SIB1 freq: offsetToPointA 86
[GNB_APP]   F1AP: gNB idx 0 gNB_DU_id 3584, gNB_DU_name gNB-OAI, TAC 1 MCC/MNC/length 1/1/2 cellID 12345678
[GNB_APP]   ngran_DU: Configuring Cell 0 for TDD
<MeasurementTimingConfiguration>
    <criticalExtensions>
        <c1>
            <measTimingConf>
                <measTiming>
                    <MeasTiming>
                        <frequencyAndTiming>
                            <carrierFreq>641280</carrierFreq>
                            <ssbSubcarrierSpacing><kHz30/></ssbSubcarrierSpacing>
                            <ssb-MeasurementTimingConfiguration>
                                <periodicityAndOffset>
                                    <sf20>0</sf20>
                                </periodicityAndOffset>
                                <duration><sf1/></duration>
                            </ssb-MeasurementTimingConfiguration>
                        </frequencyAndTiming>
                    </MeasTiming>
                </measTiming>
            </measTimingConf>
        </c1>
    </criticalExtensions>
</MeasurementTimingConfiguration>
[PHY]   create_gNB_tasks() RC.nb_nr_L1_inst:1
[PHY]   l1_north_init_gNB() RC.nb_nr_L1_inst:1
[PHY]   Installing callbacks for IF_Module - UL_indication
[PHY]   l1_north_init_gNB() RC.gNB[0] installing callbacks
[GNB_APP]   Allocating gNB_RRC_INST for 1 instances
NRRRC 0: Southbound Transport local_mac
[GNB_APP]   SDAP layer is disabled
[GNB_APP]   Data Radio Bearer count 1
[NR_RRC]   do_SIB23_NR, size 9 
 [GNB_APP]   default drx 0
[GNB_APP]   [gNB 0] gNB_app_register for instance 0
[UTIL]   threadCreate() for TASK_SCTP: creating thread with affinity ffffffff, priority 50
[X2AP]   X2AP is disabled.
[UTIL]   threadCreate() for TASK_NGAP: creating thread with affinity ffffffff, priority 50
[UTIL]   threadCreate() for TASK_GNB_APP: creating thread with affinity ffffffff, priority 50
[NGAP]   Starting NGAP layer
[UTIL]   threadCreate() for TASK_RRC_GNB: creating thread with affinity ffffffff, priority 50
[NGAP]   Registered new gNB[0] and macro gNB id 3584
[NGAP]   [gNB 0] check the amf registration state
[GTPU]   Configuring GTPu
[NR_RRC]   Entering main loop of NR_RRC message task
[NR_RRC]   Received F1 Setup Request from gNB_DU 3584 (gNB-OAI) on assoc_id -1
[GTPU]   SA mode 
[GTPU]   Configuring GTPu address : 192.168.70.129, port : 2152
[GTPU]   Initializing UDP for local address 192.168.70.129 with port 2152
[GTPU]   Created gtpu instance id: 99
[UTIL]   threadCreate() for TASK_GTPV1_U: creating thread with affinity ffffffff, priority 50
[RRC]   Accepting DU 3584 (gNB-OAI), sending F1 Setup Response
[RRC]   DU uses RRC version 17.3.0
[MAC]   received F1 Setup Response from CU (null)
[MAC]   CU uses RRC version 17.3.0
[MAC]   Clearing the DU's UE states before, if any.
[NR_RRC]   Accepting new CU-UP ID 3584 name gNB-OAI (assoc_id -1)
START MAIN THREADS
RC.nb_nr_L1_inst:1
Initializing gNB threads wait_for_sync:0
[PHY]   Initializing gNB 0
[PHY]   Initializing gNB 0
[PHY]   Registering with MAC interface module (before 0x5d058f96c420)
[PHY]   Installing callbacks for IF_Module - UL_indication
[PHY]   Registering with MAC interface module (after 0x5d058f96c420)
[PHY]   Setting indication lists
[PHY]   [nr-gnb.c] gNB structure allocated
wait_gNBs()
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
gNB L1 are configured
About to Init RU threads RC.nb_RU:1
Initializing RU threads
configuring RU from file
Set RU mask to 1
Creating RC.ru[0]:0x5d058f9be3a0
[PHY]   RU GPIO control set as 'generic'
[PHY]   RU clock source set as internal
[PHY]   Setting time source to internal
Setting function for RU 0 to gNodeB_3GPP
[RU 0] Setting nr_flag 0, nr_band 78, nr_scs_for_raster 1
[RU 0] Setting half-slot parallelization to 1
[PHY]   number of L1 instances 1, number of RU 1, number of CPU cores 64
[PHY]   Copying frame parms from gNB in RC to gNB 0 in ru 0 and frame_parms in ru
configuring ru_id 0 (start_rf 0x5d058b128520)
[PHY]   Initialized RU proc 0 (,synch_to_ext_device),
[PHY]   RU Thread pool size 2
[PHY]   RU thread-pool core string -1,-1
[UTIL]   threadCreate() for Tpool0_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool1_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for ru_thread: creating thread with affinity ffffffff, priority 97
wait RUs
[PHY]   Waiting for RUs to be configured ... RC.ru_mask:01
[PHY]   Starting RU 0 (,synch_to_ext_device) on cpu 36
[PHY]   Initializing frame parms for mu 1, N_RB 106, Ncp 0
[PHY]   Init: N_RB_DL 106, first_carrier_offset 1412, nb_prefix_samples 144,nb_prefix_samples0 176, ofdm_symbol_size 2048
[PHY]   fp->scs=30000
[PHY]   fp->ofdm_symbol_size=2048
[PHY]   fp->nb_prefix_samples0=176
[PHY]   fp->nb_prefix_samples=144
[PHY]   fp->slots_per_subframe=2
[PHY]   fp->samples_per_subframe_wCP=57344
[PHY]   fp->samples_per_frame_wCP=573440
[PHY]   fp->samples_per_subframe=61440
[PHY]   fp->samples_per_frame=614400
[PHY]   fp->dl_CarrierFreq=3619200000
[PHY]   fp->ul_CarrierFreq=3619200000
[PHY]   fp->Nid_cell=0
[PHY]   fp->first_carrier_offset=1412
[PHY]   fp->ssb_start_subcarrier=0
[PHY]   fp->Ncp=0
[PHY]   fp->N_RB_DL=106
[PHY]   fp->numerology_index=1
[PHY]   fp->nr_band=48
[PHY]   fp->ofdm_offset_divisor=8
[PHY]   fp->threequarter_fs=0
[PHY]   fp->sl_CarrierFreq=0
[PHY]   fp->N_RB_SL=0
[PHY]   Initializing RU signal buffers (if_south local RF) nb_tx 1, nb_rx 1
[PHY]   [INIT] common.txdata[0] = 0x761cdde00040 (2458880 bytes,sf_extension 320)
[PHY]   [INIT] common.txdata[0] = 0x761cdde00540 
[PHY]   nb_tx 1
[PHY]   rxdata_7_5kHz[0] 0x761cee10f040 for RU 0
[PHY]   [INIT] common.txdata_BF= 0x761cc4000ac0 (8 bytes)
[PHY]   txdataF_BF[0] 0x761ceece0040 for RU 0
[PHY]   rxdataF[0] 0x761ceec6f040 for RU 0
[PHY]   [INIT] nr_phy_init_RU() ru->num_gNB:1 
[PHY]   Setting RF config for N_RB 106, NB_RX 1, NB_TX 1
[PHY]   tune_offset 0 Hz, sample_rate 61440000 Hz
[PHY]   Channel 0: setting tx_gain offset 12, tx_freq 3619200000 Hz
[PHY]   Channel 0: setting rx_gain offset 102, rx_freq 3619200000 Hz
shlib_path librfsimulator.so
[LOADER] library librfsimulator.so successfully loaded
[HW]   Running as server waiting opposite rfsimulators to connect
Initializing random number generator, seed 15074425899197230368
[HW]   [RAU] has loaded RFSIMULATOR device.
setup_RU_buffers: frame_parms = 0x761cee4af010
[PHY]   RU 0 Setting N_TA_offset to 800 samples (factor 2.000000, UL Freq 3600120, N_RB 106, mu 1)
[PHY]   Signaling main thread that RU 0 is ready, sl_ahead 6
waiting for sync (ru_thread,-1/0x5d058bd2f0a8,0x5d058d655ec0,0x5d058d6551c0)
RC.ru_mask:00
[PHY]   RUs configured
ALL RUs READY!
RC.nb_RU:1
ALL RUs ready - init gNBs
Not NFAPI mode - call init_eNB_afterRU()
[PHY]   init_eNB_afterRU() RC.nb_nr_inst:1
[PHY]   RC.nb_nr_CC[inst:0]:0x761cee200010
[PHY]   [gNB 0] phy_init_nr_gNB() About to wait for gNB to be configured
shlib_path libdfts.so
[LOADER] library libdfts.so successfully loaded
shlib_path libldpc.so
[LOADER] library libldpc.so successfully loaded
shlib_path libldpc.so
[LOADER] library libldpc.so has been loaded previously, reloading function pointers
[LOADER] library libldpc.so successfully loaded
[PHY]   Initialise nr transport
[PHY]   Mapping RX ports from 1 RUs to gNB 0
[PHY]   gNB->num_RU:1
[PHY]   Attaching RU 0 antenna 0 to gNB antenna 0
[UTIL]   threadCreate() for Tpool0_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool1_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool2_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool3_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool4_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool5_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool6_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for Tpool7_-1: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for L1_rx_thread: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for L1_tx_thread: creating thread with affinity ffffffff, priority 97
[UTIL]   threadCreate() for L1_stats: creating thread with affinity ffffffff, priority 1
ALL RUs ready - ALL gNBs ready
Sending sync to all threads
Entering ITTI signals handler
TYPE <CTRL-C> TO TERMINATE
got sync (ru_thread)
waiting for sync (L1_stats_thread,0/0x5d058bd2f0a8,0x5d058d655ec0,0x5d058d6551c0)
got sync (L1_stats_thread)
[PHY]   RU 0 rf device ready
[PHY]   RU 0 RF started cpu_meas_enabled 0
[HW]   No connected device, generating void samples...
[PHY]   Command line parameters for OAI UE: -C 3619200000 -r 106 --numerology 1 --ssb 516 
[HW]   A client connects, sending the current time
[HW]   Not supported to send Tx out of order 68352000, 68351999
[NR_MAC]   Frame.Slot 128.0

[NR_MAC]   Frame.Slot 256.0

[NR_PHY]   [RAPROC] 263.19 Initiating RA procedure with preamble 1, energy 56.4 dB (I0 0, thres 120), delay 0 start symbol 0 freq index 0
[NR_MAC]   263.19 UE RA-RNTI 010b TC-RNTI d104: Activating RA process index 0
[NR_MAC]   UE d104: 264.7 Generating RA-Msg2 DCI, RA RNTI 0x10b, state 1, CoreSetType 0, RAPID 1
[NR_MAC]   UE d104: Msg3 scheduled at 264.17 (264.7 TDA 3)
[NR_MAC]   Adding new UE context with RNTI 0xd104
[NR_MAC]    264.17 PUSCH with TC_RNTI 0xd104 received correctly
[MAC]   [RAPROC] Received SDU for CCCH length 6 for UE d104
[RLC]   Activated srb0 for UE 53508
[RLC]   Added srb 1 to UE 53508
[NR_MAC]   Activating scheduling RA-Msg4 for TC_RNTI 0xd104 (state WAIT_Msg3)
[NR_MAC]   Unexpected ULSCH HARQ PID 0 (have -1) for RNTI 0xd104 (ignore this warning for RA)
[NR_RRC]   Decoding CCCH: RNTI d104, payload_size 6
[NR_RRC]   Created new UE context: CU UE ID 1 DU UE ID 53508 (rnti: d104, random ue id a4c59a542e000000)
[RRC]   activate SRB 1 of UE 1
[NR_RRC]   rrc_gNB_generate_RRCSetup for RNTI d104
[NR_RRC]   asn_DEF_NR_CellGroupConfig
[NR_RRC]   asn_DEF_NR_DL_CCCH_Message
<DL-CCCH-Message>
    <message>
        <c1>
            <rrcSetup>
                <rrc-TransactionIdentifier>1</rrc-TransactionIdentifier>
                <criticalExtensions>
                    <rrcSetup>
                        <radioBearerConfig>
                            <srb-ToAddModList>
                                <SRB-ToAddMod>
                                    <srb-Identity>1</srb-Identity>
                                </SRB-ToAddMod>
                            </srb-ToAddModList>
                        </radioBearerConfig>
                        <masterCellGroup>
                            5C 00 B0 01 11 7A EC 70 10 61 F0 00 7C 02 04 68 
                            3C 08 00 04 12 59 81 95 00 81 FF FF 00 00 00 01 
                            00 00 37 14 42 00 00 80 16 50 00 04 82 00 00 44 
                            09 30 12 35 52 4D 40 00 10 02 02 00 04 00 68 08 
                            00 9D B2 48 C0 77 01 D9 E2 6A F3 40 00 00 A6 84 
                            00 80 00 96 03 08 30 0B 07 06 08 70 00 C4 A0 70 
                            00 00 85 7B D0 04 00 04 00 00 19 00 05 00 01 95 
                            05 00 62 2A 0A 80 03 80 08 00 8D 10 01 51 08 01 
                            40 00 00 00 00 00 00 00 00 01 14 20 08 01 00 02 
                            00 00 50 02 02 00 0A 98 00
                        </masterCellGroup>
                    </rrcSetup>
                </criticalExtensions>
            </rrcSetup>
        </c1>
    </message>
</DL-CCCH-Message>
[NR_MAC]   No CU UE ID stored for UE RNTI d104, adding CU UE ID 1
[NR_MAC]   UE d104 Generate msg4: feedback at  265.17, payload 169 bytes, next state WAIT_Msg4_ACK
[NR_MAC]   (UE RNTI 0xd104) Received Ack of RA-Msg4. CBRA procedure succeeded!
[NR_RRC]   UE 1 Processing NR_RRCSetupComplete from UE
[NR_RRC]   [FRAME 00000][gNB][MOD 00][RNTI 1] UE State = NR_RRC_CONNECTED 
[NGAP]   No AMF is associated to the gNB
[NR_MAC]   Frame.Slot 384.0
UE RNTI d104 CU-UE-ID 1 in-sync PH 52 dB PCMAX 20 dBm, average RSRP -44 (14 meas)
UE d104: dlsch_rounds 3/0/0/0, dlsch_errors 0, pucch0_DTX 0, BLER 0.09000 MCS (0) 9
UE d104: ulsch_rounds 14/0/0/0, ulsch_errors 0, ulsch_DTX 0, BLER 0.03138 MCS (0) 9 (Qm 2 deltaMCS 0 dB) NPRB 5  SNR 51.0 dB
UE d104: MAC:    TX            246 RX           1364 bytes
UE d104: LCID 1: TX              3 RX             45 bytes

[NR_MAC]   Frame.Slot 512.0
UE RNTI d104 CU-UE-ID 1 in-sync PH 52 dB PCMAX 20 dBm, average RSRP -44 (16 meas)
UE d104: dlsch_rounds 4/0/0/0, dlsch_errors 0, pucch0_DTX 0, BLER 0.08100 MCS (0) 9
UE d104: ulsch_rounds 27/0/0/0, ulsch_errors 0, ulsch_DTX 0, BLER 0.00798 MCS (0) 9 (Qm 2 deltaMCS 0 dB) NPRB 5  SNR 51.0 dB
UE d104: MAC:    TX            369 RX           2872 bytes
UE d104: LCID 1: TX              3 RX             45 bytes
```