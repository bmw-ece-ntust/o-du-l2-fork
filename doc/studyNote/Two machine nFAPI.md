# Two machine nFAPI

Start Date: 2024/04/19
Summary: Implementing nfAPI on two machines to address stability issues with the Round Robin Scheduler, while troubleshooting Downlink request transmission problems.
Status: padding
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 Currently, the Round Robin Scheduler (RRT) remains stably around 100ms and cannot be reduced despite various attempted methods. All bugs in the log have been addressed, yet no solution has been found. Therefore, there's a new idea: whether the resources are insufficient if it only runs on a single computer. Hence, an attempt is made to run nfapi on two computers. However, the current issue encountered is that Downlink requests cannot be transmitted downwards each time, although slot indication is feasible, being transmitted from the Physical Network Function (PNF) to the Virtual Network Function (VNF) in each slot.

</aside>

[LOG list](LOG%20list%2012110098314381abb836d893459f4ea4.csv)

## Stop in here

![**`nr_config_resp_cb`** openairinterface5g/nfapi/oai_integration/nfapi_vnf.c](Untitled%2011.png)

**`nr_config_resp_cb`** openairinterface5g/nfapi/oai_integration/nfapi_vnf.c

### Compare with execute in one mechine.

<aside>
⛔ Start.response is missing.

</aside>

![execute in two machines](Untitled%2012.png)

execute in two machines

![execute in one machine](Untitled%2013.png)

execute in one machine

### VNF

vnf_nr_read_dispatch_message: VNF Failed to peek sctp message size errno:104

```bash
3807862437 [I] 2709497408: vnf_nr_p7_thread_start: [VNF] Creating VNF NFAPI P7 start thread vnf_nr_p7_thread_start
3807863629 [I] 2701104704: vnf_nr_p7_start_thread: vnf_nr_p7_start_thread()
3807863635 [I] 2701104704: nfapi_nr_vnf_p7_start: nfapi_nr_vnf_p7_start()
3807863636 [I] 2701104704: nfapi_nr_vnf_p7_start: Initialising VNF P7 port:50011
3807863647 [I] 2701104704: nfapi_nr_vnf_p7_start: VNF P7 socket created...
3807863650 [I] 2701104704: nfapi_nr_vnf_p7_start: VNF P7 setsockopt succeeded...
3807863652 [I] 2701104704: nfapi_nr_vnf_p7_start: VNF P7 binding too 0.0.0.0:50011
3807863656 [I] 2701104704: nfapi_nr_vnf_p7_start: VNF P7 bind succeeded...
3807867025 [I] 2833233472: vnf_nr_handle_param_response: Received PARAM_RESPONSE
3807867032 [I] 2833233472: vnf_nr_handle_param_response: PNF P7 IPv4 address: 172.24.11.58
3807867033 [I] 2833233472: vnf_nr_handle_param_response: PNF P7 IPv6 address: ::
3807867034 [I] 2833233472: vnf_nr_handle_param_response: PNF P7 Port: 23235
3807867035 [I] 2833233472: nr_param_resp_cb: [VNF] Received NFAPI_PARAM_RESP idx:0 phy_id:1
3807867037 [I] 2833233472: nr_param_resp_cb: [VNF] 0.1 pnf p7 172.24.11.58:23235 timing 30 1 0 1
3807867038 [I] 2833233472: nfapi_vnf_p7_add_pnf: nfapi_vnf_p7_add_pnf(config:0x5ee6720919c0 phy_id:1 pnf_addr:172.24.11.58 pnf_p7_port:23235)
3807867041 [I] 2833233472: vnf_p7_connection_info_list_add: vnf_p7_connection_info_list_add()
3807867043 [I] 2833233472: nr_param_resp_cb: [VNF] Send NFAPI_CONFIG_REQUEST
3807867043 [I] 2833233472: nr_param_resp_cb: [VNF] Local_port:23491
3807867044 [I] 2833233472: nr_param_resp_cb: [VNF] Local_addr:172.24.11.80
3807867046 [I] 2833233472: nr_param_resp_cb: 
[VNF]Timing window tag : 286 Timing window:30
carrier_config
  bw t 4097 l 0 v 40
  freq t 4098 l 0 v 3600120
  dl_k0[0] t 0 l 0 v 0
  dl_k0[1] t 4099 l 0 v 0
  dl_k0[2] t 0 l 0 v 0
  dl_k0[3] t 0 l 0 v 0
  dl_k0[4] t 0 l 0 v 0
  dl_grid_size[0] t 0 l 0 v 0
  dl_grid_size[1] t 4100 l 0 v 106
  dl_grid_size[2] t 0 l 0 v 0
  dl_grid_size[3] t 0 l 0 v 0
  dl_grid_size[4] t 0 l 0 v 0
  num_tx_ant t 4101 l 0 v 1
  uplink_bandwidth t 4102 l 0 v 40
  uplink_frequency t 4103 l 0 v 3600120
  ul_k0[0] t 0 l 0 v 0
  ul_k0[1] t 4104 l 0 v 0
  ul_k0[2] t 0 l 0 v 0
  ul_k0[3] t 0 l 0 v 0
  ul_k0[4] t 0 l 0 v 0
  ul_grid_size[0] t 0 l 0 v 0
  ul_grid_size[1] t 4105 l 0 v 106
  ul_grid_size[2] t 0 l 0 v 0
  ul_grid_size[3] t 0 l 0 v 0
  ul_grid_size[4] t 0 l 0 v 0
  num_rx_ant t 4106 l 0 v 1
  frequency_shift_7p5khz t 0 l 0 v 0
prach_config
  prach_sequence_length t 4113 l 0 v 1
  prach_sub_c_spacing t 4114 l 0 v 1
  restricted_set_config t 4115 l 0 v 0
  num_prach_fd_occasions t 4116 l 0 v 1
  prach_ConfigurationIndex t 4137 l 0 v 98
    prach_root_sequence_index t 4117 l 0 v 1
    num_root_sequences t 4118 l 0 v 16
    k1 t 4119 l 0 v 0
    prach_zero_corr_conf t 4120 l 0 v 13
    num_unused_root_sequences t 4121 l 0 v 0
  ssb_per_rach t 4123 l 0 v 3
  prach_multiple_carriers_in_a_band t 0 l 0 v 0
[VNF] Sent NFAPI_VNF_CONFIG_REQ num_tlv:127
3807876720 [I] 2833233472: vnf_nr_handle_config_response: Received CONFIG_RESPONSE
3807876727 [I] 2833233472: nr_config_resp_cb: [VNF] Received NFAPI_CONFIG_RESP idx:0 phy_id:1
3807876728 [I] 2833233472: nr_config_resp_cb: [VNF] Calling oai_enb_init()
3811192079 [I] 2833233472: vnf_nr_read_dispatch_message: VNF Failed to peek sctp message size errno:104
3811192088 [I] 2833233472: pnf_disconnection_indication_cb: [VNF] pnf disconnection indication idx:0
3811192091 [I] 2833233472: nfapi_vnf_p7_del_pnf: nfapi_vnf_p7_del_pnf(phy_id:1)
3811192092 [I] 2833233472: nfapi_vnf_p7_del_pnf: nfapi_vnf_p7_del_pnf(phy_id:1) deleting connection info
3813755249 [N] 2701104704: vnf_nr_p7_read_dispatch_message: reallocing rx buffer 20
3813764081 [N] 2701104704: vnf_nr_p7_read_dispatch_message: reallocing rx buffer 76
3813791148 [E] 2701104704: vnf_p7_connection_info_list_find: vnf_p7_connection_info_list_find(): could not find P7 connection for phy_id 1
3813791183 [I] 2701104704: vnf_nr_p7_pack_and_send_p7_msg: vnf_nr_p7_pack_and_send_p7_msg() cannot find p7 connection info for phy_id:1
1713518305.650866 [PHY]   oai_nfapi_ul_tti_req() Problem sending retval:-1
3813791785 [E] 2701104704: vnf_p7_connection_info_list_find: vnf_p7_connection_info_list_find(): could not find P7 connection for phy_id 1
3813791787 [I] 2701104704: vnf_nr_p7_pack_and_send_p7_msg: vnf_nr_p7_pack_and_send_p7_msg() cannot find p7 connection info for phy_id:1
1713518305.651449 [PHY]   oai_nfapi_dl_tti_req() Problem sending retval:-1
```

### PNF

```bash
Timing window tag: 286
Phy_info:Timing window:30 NFAPI_CONFIG:timing_window:30
timing info mode:3
timing info period provided value:10
92214832432 [E] 2377582336: nr_config_request: nr_config_request() NFAPI_NR_CONFIG_DL_BANDWIDTH_TAG N_RB_DL:40
[PNF] CONFIG_REQUEST[num_tlv:127] TLVs processed:6
[PNF] Simulating PHY CONFIG
DL frequency 3619200000: band 48, UL frequency 3619200000
1713518299.720477 [PHY]   DL frequency 3619200000 Hz, UL frequency 3619200000 Hz: band 48, uldl offset 0 Hz
1713518299.720488 [PHY]   Configuring MIB for instance 0, : (Nid_cell 0,DL freq 3619200000, UL freq 3619200000)
1713518299.720498 [PHY]   Initializing frame parms for mu 1, N_RB 106, Ncp 0
1713518299.720508 [PHY]   Init: N_RB_DL 106, first_carrier_offset 1412, nb_prefix_samples 144,nb_prefix_samples0 176, ofdm_symbol_size 2048
1713518299.720970 [PHY]   gNB 0 configured
1713518299.720980 [PHY]   fp->scs=30000
1713518299.720988 [PHY]   fp->ofdm_symbol_size=2048
1713518299.720995 [PHY]   fp->nb_prefix_samples0=176
1713518299.721003 [PHY]   fp->nb_prefix_samples=144
1713518299.721010 [PHY]   fp->slots_per_subframe=2
1713518299.721018 [PHY]   fp->samples_per_subframe_wCP=57344
1713518299.721025 [PHY]   fp->samples_per_frame_wCP=573440
1713518299.721033 [PHY]   fp->samples_per_subframe=61440
1713518299.721040 [PHY]   fp->samples_per_frame=614400
1713518299.721048 [PHY]   fp->dl_CarrierFreq=3619200000
1713518299.721055 [PHY]   fp->ul_CarrierFreq=3619200000
[PNF] 1 vnf p7 172.24.11.80:50011 timing 30 3 10
[PNF] Sent NFAPI_PNF_CONFIG_RESPONSE phy_id:1
92214836754 [I] 2377582336: pnf_nr_handle_start_request: pnf_nr_handle_start_request() START.request received state:2
[PNF] Received NFAPI_START_REQ phy_id:1
gNB L1 are configured
About to Init RU threads RC.nb_RU:1
Initializing RU threads
configuring RU from file
[LIBCONFIG] RUs.[0]: 43/43 parameters successfully set, (34 to default value)
Set RU mask to 1
[PNF] P7 remote:172.24.11.80:50011 local:172.24.11.58:50010
subframe_buffer_size configured using phy_info->timing_window:30
92214866424 [I] 2377582336: nr_start_request: [PNF] Creating P7 thread nr_start_request
Creating RC.ru[0]:0x556d888bf040
1713518299.754689 [PHY]   RU GPIO control set as 'generic'
1713518299.754696 [PHY]   Setting clock source to internal
1713518299.754701 [PHY]   Setting time source to internal
Setting function for RU 0 to gNodeB_3GPP
[RU 0] Setting nr_flag 0, nr_band 78, nr_scs_for_raster 1
[RU 0] Setting half-slot parallelization to 1
1713518299.754740 [PHY]   number of L1 instances 1, number of RU 1, number of CPU cores 8
1713518299.754745 [PHY]   Copying frame parms from gNB in RC to gNB 0 in ru 0 and frame_parms in ru
configuring ru_id 0 (start_rf 0x556d84f33a10)
1713518299.754902 [PHY]   Initialized RU proc 0 (,synch_to_ext_device),
1713518299.754907 [PHY]   RU Thread pool size 2
1713518299.754912 [PHY]   RU thread-pool core string -1,-1
create a thread for core -1
1713518299.754922 [UTIL]   Creating thread Tpool0_-1 with affinity -1 and priority 97
92214868185 [I] 2377582336: nr_start_request: [PNF] Calling l1_north_init_eNB() nr_start_request
92214868195 [I] 2367809280: pnf_nr_p7_thread_start: [NR_PNF] NR P7 THREAD pnf_nr_p7_thread_start
1713518299.756220 [PHY]   l1_north_init_gNB() RC.nb_nr_L1_inst:1
Calling sched_setscheduler(79)
1713518299.756232 [PHY]   Installing callbacks for IF_Module - UL_indication
1713518299.756238 [PHY]   l1_north_init_gNB() RC.gNB[0] installing callbacks
92214868227 [I] 2377582336: nr_start_request: [PNF] HACK - Set p7_config global ready for subframe indnr_start_request
92214868233 [I] 2367809280: nfapi_nr_pnf_p7_start: nfapi_nr_pnf_p7_start
92214868250 [I] 2367809280: pnf_nr_p7_message_pump: PNF P7 socket created (99)...
92214868260 [I] 2367809280: pnf_nr_p7_message_pump: PNF P7 binding 99 too 172.24.11.58:50010
92214868269 [I] 2367809280: pnf_nr_p7_message_pump: PNF P7 bind succeeded...
1713518299.761215 [UTIL]   threadCreate for Tpool0_-1, affinity ffffffff, priority 97
create a thread for core -1
1713518299.762798 [UTIL]   Creating thread Tpool1_-1 with affinity -1 and priority 97
1713518299.767596 [UTIL]   threadCreate for Tpool1_-1, affinity ffffffff, priority 97
1713518299.769183 [UTIL]   Creating thread ru_thread with affinity -1 and priority 97
1713518299.774113 [UTIL]   threadCreate for ru_thread, affinity ffffffff, priority 97
1713518299.775660 [PHY]   Starting RU 0 (,synch_to_ext_device) on cpu 1
1713518299.775682 [PHY]   Initializing frame parms for mu 1, N_RB 106, Ncp 0
waiting for NFAPI PNF connection and population of global structure (main?)
1713518299.775688 [PHY]   Init: N_RB_DL 106, first_carrier_offset 1412, nb_prefix_samples 144,nb_prefix_samples0 176, ofdm_symbol_size 2048
1713518299.775699 [PHY]   fp->scs=30000
1713518299.775704 [PHY]   fp->ofdm_symbol_size=2048
1713518299.775707 [PHY]   fp->nb_prefix_samples0=176
1713518299.775711 [PHY]   fp->nb_prefix_samples=144
1713518299.775714 [PHY]   fp->slots_per_subframe=2
1713518299.775718 [PHY]   fp->samples_per_subframe_wCP=57344
1713518299.775721 [PHY]   fp->samples_per_frame_wCP=573440
1713518299.775725 [PHY]   fp->samples_per_subframe=61440
1713518299.775728 [PHY]   fp->samples_per_frame=614400
1713518299.775732 [PHY]   fp->dl_CarrierFreq=3619200000
1713518299.775735 [PHY]   fp->ul_CarrierFreq=3619200000
1713518299.775739 [PHY]   Initializing RU signal buffers (if_south local RF) nb_tx 1, nb_rx 1
1713518299.776907 [PHY]   [INIT] common.txdata[0] = 0x7f287ddc3040 (2458880 bytes,sf_extension 320)
1713518299.776914 [PHY]   [INIT] common.txdata[0] = 0x7f287ddc3540 
1713518299.777424 [PHY]   nb_tx 1
1713518299.777647 [PHY]   rxdata_7_5kHz[0] 0x7f288c12c040 for RU 0
1713518299.778112 [PHY]   [INIT] common.txdata_BF= 0x7f2878000b00 (8 bytes)
1713518299.778169 [PHY]   txdataF_BF[0] 0x7f288feb1040 for RU 0
1713518299.778266 [PHY]   rxdataF[0] 0x7f288fe40040 for RU 0
1713518299.782137 [PHY]   [INIT] nr_phy_init_RU() ru->num_gNB:1 
1713518299.782619 [PHY]   Setting RF config for N_RB 106, NB_RX 1, NB_TX 1
1713518299.782625 [PHY]   tune_offset 0 Hz, sample_rate 61440000 Hz
1713518299.782634 [PHY]   Channel 0: setting tx_gain offset 0, tx_freq 3619200000 Hz
1713518299.782639 [PHY]   Channel 0: setting rx_gain offset 125, rx_freq 3619200000 Hz
[LIBCONFIG] device.recplay: 8/8 parameters successfully set, (8 to default value)
[LIBCONFIG] device: 1/1 parameters successfully set, (1 to default value)
[LIBCONFIG] loader: 2/2 parameters successfully set, (2 to default value)
[LIBCONFIG] loader.rfsimulator: 2/2 parameters successfully set, (1 to default value)
shlib_path librfsimulator.so
[LOADER] library librfsimulator.so successfully loaded
[LIBCONFIG] rfsimulator: 9/9 parameters successfully set, (8 to default value)
1713518299.782931 [HW]   sample_rate 61440000.000000
1713518299.782938 [HW]   Running as server waiting opposite rfsimulators to connect
Initializing random number generator, seed 17736993058083626744
1713518299.783052 [HW]   [RAU] has loaded RFSIMULATOR device.
setup_RU_buffers: frame_parms = 0x7f288d21f010
1713518299.783061 [PHY]   RU 0 Setting N_TA_offset to 800 samples (factor 2.000000, UL Freq 3600120, N_RB 106, mu 1)
1713518299.783068 [PHY]   Signaling main thread that RU 0 is ready, sl_ahead 5
waiting for sync (ru_thread,-1/0x556d85cdd0b4,0x556d87613e80,0x556d876130c0)
[PNF] waiting for OAI to be configured (eNB/RU)
[PNF] OAI eNB/RU configured
[PNF] About to call init_eNB_afterRU()
1713518304.756296 [PHY]   init_eNB_afterRU() RC.nb_nr_inst:0
1713518304.756319 [PHY]   RC.nb_nr_CC[inst:0]:0x7f288db71010
1713518304.756332 [PHY]   [gNB 0] phy_init_nr_gNB() About to wait for gNB to be configured
[LIBCONFIG] loader.dfts: 2/2 parameters successfully set, (1 to default value)
shlib_path libdfts.so
[LOADER] library libdfts.so successfully loaded
[LIBCONFIG] loader.ldpc: 2/2 parameters successfully set, (1 to default value)
shlib_path libldpc.so
[LOADER] library libldpc.so successfully loaded
1713518305.015305 [PHY]   Initialise nr transport
1713518305.240831 [PHY]   Mapping RX ports from 1 RUs to gNB 0
1713518305.240849 [PHY]   gNB->num_RU:1
1713518305.240853 [PHY]   Attaching RU 0 antenna 0 to gNB antenna 0
create a thread for core -1
1713518305.240873 [UTIL]   Creating thread Tpool0_-1 with affinity -1 and priority 97
1713518305.262358 [UTIL]   threadCreate for Tpool0_-1, affinity ffffffff, priority 97
create a thread for core -1
1713518305.264011 [UTIL]   Creating thread Tpool1_-1 with affinity -1 and priority 97
1713518305.283699 [UTIL]   threadCreate for Tpool1_-1, affinity ffffffff, priority 97
create a thread for core -1
1713518305.285300 [UTIL]   Creating thread Tpool2_-1 with affinity -1 and priority 97
1713518305.305421 [UTIL]   threadCreate for Tpool2_-1, affinity ffffffff, priority 97
create a thread for core -1
1713518305.307074 [UTIL]   Creating thread Tpool3_-1 with affinity -1 and priority 97
1713518305.328101 [UTIL]   threadCreate for Tpool3_-1, affinity ffffffff, priority 97
create a thread for core -1
1713518305.329782 [UTIL]   Creating thread Tpool4_-1 with affinity -1 and priority 97
1713518305.351338 [UTIL]   threadCreate for Tpool4_-1, affinity ffffffff, priority 97
create a thread for core -1
1713518305.353085 [UTIL]   Creating thread Tpool5_-1 with affinity -1 and priority 97
1713518305.374993 [UTIL]   threadCreate for Tpool5_-1, affinity ffffffff, priority 97
create a thread for core -1
1713518305.376709 [UTIL]   Creating thread Tpool6_-1 with affinity -1 and priority 97
1713518305.398991 [UTIL]   threadCreate for Tpool6_-1, affinity ffffffff, priority 97
create a thread for core -1
1713518305.400752 [UTIL]   Creating thread Tpool7_-1 with affinity -1 and priority 97
1713518305.423351 [UTIL]   threadCreate for Tpool7_-1, affinity ffffffff, priority 97
1713518305.425090 [UTIL]   Creating thread L1_rx_thread with affinity -1 and priority 97
1713518305.448011 [UTIL]   threadCreate for L1_rx_thread, affinity ffffffff, priority 97
1713518305.449749 [UTIL]   Creating thread L1_tx_thread with affinity -1 and priority 97
1713518305.472712 [UTIL]   threadCreate for L1_tx_thread, affinity ffffffff, priority 97
1713518305.485059 [UTIL]   Creating thread L1_stats with affinity -1 and priority 1
1713518305.508590 [UTIL]   threadCreate for L1_stats, affinity ffffffff, priority 1
waiting for sync (L1_stats_thread,-1/0x556d85cdd0b4,0x556d87613e80,0x556d876130c0)
[PNF] Sending PNF_START_RESP
Sending NFAPI_START_RESPONSE config:0x556d888ba1b0 phy_id:1
NFAPI: got sync (main?)
92220622409 [E] 2377582336: pnf_send_message: sctp_sendmsg failed errno: 104
[PNF] Sending first P7 slot indication
wait RUs
[PNF] Sent first P7 slot ind
1713518305.510452 [PHY]   Waiting for RUs to be configured ... RC.ru_mask:00
1713518305.510464 [PHY]   RUs configured
ALL RUs READY!
RC.nb_RU:1
ALL RUs ready - init gNBs
NFAPI mode - DO NOT call init_gNB_afterRU()
ALL RUs ready - ALL gNBs ready
Sending sync to all threads
Entering ITTI signals handler
TYPE <CTRL-C> TO TERMINATE
got sync (L1_stats_thread)
got sync (ru_thread)
1713518305.511305 [HW]   running command "/sbin/sysctl -n -e -q -w net.core.rmem_default=134217728" to increase RFsim performance
1713518305.532442 [HW]   running command "/sbin/sysctl -n -e -q -w net.core.rmem_max=134217728" to increase RFsim performance
1713518305.553765 [HW]   running command "/sbin/sysctl -n -e -q -w net.core.wmem_default=134217728" to increase RFsim performance
1713518305.575749 [HW]   running command "/sbin/sysctl -n -e -q -w net.core.wmem_max=134217728" to increase RFsim performance
1713518305.598307 [PHY]   RU 0 rf device ready
1713518305.598321 [PHY]   RU 0 RF started opp_enabled 0
1713518305.598332 [HW]   No connected device, generating void samples...
```