# VNF

Created time: 2024年10月16日 下午1:25

```bash
CMDLINE: "./nr-softmodem" "-O" "../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf" "--nfapi" "VNF" "--sa" "--log_config.global_log_options" "wall_clock" "--emulate-l1" 
[CONFIG] get parameters from libconfig ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf [LIBCONFIG] Path for include directive set to: ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF
[CONFIG] function config_libconfig_init returned 0
[CONFIG] config module libconfig loaded
[LIBCONFIG] config: 2/2 parameters successfully set, (2 to default value)
[CONFIG] debug flags: 0x00000000
[LIBCONFIG] log_config: 3/3 parameters successfully set, (1 to default value)
[LIBCONFIG] log_config: 53/53 parameters successfully set, (52 to default value)
[LIBCONFIG] log_config: 53/53 parameters successfully set, (53 to default value)
[LIBCONFIG] log_config: 16/16 parameters successfully set, (16 to default value)
[LIBCONFIG] log_config: 16/16 parameters successfully set, (16 to default value)
log init done
1713863149.253783 [HW]   # /dev/cpu_dma_latency set to 2 us
Reading in command-line options
[LIBCONFIG] (root): 40/40 parameters successfully set, (37 to default value)
[LIBCONFIG] (root): 6/6 parameters successfully set, (5 to default value)
1713863149.271888 [ENB_APP]   nfapi running mode: VNF
1713863149.271900 [GNB_APP]   Getting GNBSParams
[LIBCONFIG] (root): 2/2 parameters successfully set, (0 to default value)
[LIBCONFIG] list L1s not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
[LIBCONFIG] list RUs not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
[LIBCONFIG] list THREAD_STRUCT not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
[CONFIG] parallel_conf is set to 2
[CONFIG] worker_conf is set to 1
Configuration: nb_rrc_inst 1, nb_nr_L1_inst 0, nb_ru 0
[LIBCONFIG] TTracer: 3/3 parameters successfully set, (3 to default value)
configuring for RAU/RRU
1713863150.272074 [ITTI]   Starting itti queue: TASK_UNKNOWN as task 0
1713863150.272105 [ITTI]   Starting itti queue: TASK_TIMER as task 1
1713863150.272108 [ITTI]   Starting itti queue: TASK_L2L1 as task 2
1713863150.272111 [ITTI]   Starting itti queue: TASK_BM as task 3
1713863150.272113 [ITTI]   Starting itti queue: TASK_PHY_ENB as task 4
1713863150.272115 [ITTI]   Starting itti queue: TASK_MAC_GNB as task 5
1713863150.272118 [ITTI]   Starting itti queue: TASK_RLC_ENB as task 6
1713863150.272120 [ITTI]   Starting itti queue: TASK_RRC_ENB_NB_IoT as task 7
1713863150.272124 [ITTI]   Starting itti queue: TASK_PDCP_ENB as task 8
1713863150.272127 [ITTI]   Starting itti queue: TASK_PDCP_GNB as task 9
1713863150.272131 [ITTI]   Starting itti queue: TASK_DATA_FORWARDING as task 10
1713863150.272134 [ITTI]   Starting itti queue: TASK_END_MARKER as task 11
1713863150.272139 [ITTI]   Starting itti queue: TASK_RRC_ENB as task 12
1713863150.272142 [ITTI]   Starting itti queue: TASK_RRC_GNB as task 13
1713863150.272146 [ITTI]   Starting itti queue: TASK_RAL_ENB as task 14
1713863150.272149 [ITTI]   Starting itti queue: TASK_S1AP as task 15
1713863150.272153 [ITTI]   Starting itti queue: TASK_NGAP as task 16
1713863150.272159 [ITTI]   Starting itti queue: TASK_X2AP as task 17
1713863150.272163 [ITTI]   Starting itti queue: TASK_M2AP_ENB as task 18
1713863150.272166 [ITTI]   Starting itti queue: TASK_M2AP_MCE as task 19
1713863150.272170 [ITTI]   Starting itti queue: TASK_M3AP as task 20
1713863150.272175 [ITTI]   Starting itti queue: TASK_M3AP_MME as task 21
1713863150.272177 [ITTI]   Starting itti queue: TASK_M3AP_MCE as task 22
1713863150.272180 [ITTI]   Starting itti queue: TASK_SCTP as task 23
1713863150.272184 [ITTI]   Starting itti queue: TASK_ENB_APP as task 24
1713863150.272187 [ITTI]   Starting itti queue: TASK_GNB_APP as task 25
1713863150.272190 [ITTI]   Starting itti queue: TASK_MCE_APP as task 26
1713863150.272193 [ITTI]   Starting itti queue: TASK_MME_APP as task 27
1713863150.272196 [ITTI]   Starting itti queue: TASK_PHY_UE as task 28
1713863150.272199 [ITTI]   Starting itti queue: TASK_MAC_UE as task 29
1713863150.272204 [ITTI]   Starting itti queue: TASK_RLC_UE as task 30
1713863150.272207 [ITTI]   Starting itti queue: TASK_PDCP_UE as task 31
1713863150.272209 [ITTI]   Starting itti queue: TASK_RRC_UE as task 32
1713863150.272212 [ITTI]   Starting itti queue: TASK_RRC_NRUE as task 33
1713863150.272216 [ITTI]   Starting itti queue: TASK_NAS_UE as task 34
1713863150.272219 [ITTI]   Starting itti queue: TASK_RAL_UE as task 35
1713863150.272223 [ITTI]   Starting itti queue: TASK_GTPV1_U as task 36
1713863150.272226 [ITTI]   Starting itti queue: TASK_CU_F1 as task 37
1713863150.272229 [ITTI]   Starting itti queue: TASK_DU_F1 as task 38
1713863150.272232 [ITTI]   Starting itti queue: TASK_CUCP_E1 as task 39
1713863150.272235 [ITTI]   Starting itti queue: TASK_CUUP_E1 as task 40
1713863150.272238 [ITTI]   Starting itti queue: TASK_RRC_UE_SIM as task 41
1713863150.272240 [ITTI]   Starting itti queue: TASK_RRC_GNB_SIM as task 42
1713863150.272243 [ITTI]   Starting itti queue: TASK_RRC_NSA_UE as task 43
1713863150.272246 [ITTI]   Starting itti queue: TASK_RRC_NSA_NRUE as task 44
1713863150.272249 [ITTI]   Starting itti queue: TASK_NAS_NRUE as task 45
[LIBCONFIG] opt: 3/3 parameters successfully set, (3 to default value)
1713863150.272263 [OPT]   OPT disabled
1713863150.272265 [HW]   Version: Branch: nfapi-fixes-NTUST Abrev. Hash: b8613082b6 Date: Mon Apr 15 10:10:42 2024 +0200
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
[LIBCONFIG] list gNBs.[0].E1_INTERFACE not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
1713863150.272323 [PHY]   create_gNB_tasks() Task ready initialize structures
[LIBCONFIG] (root): 2/2 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
1713863150.272351 [NR_PHY]   RC.gNB = 0x600835d974b0
[LIBCONFIG] list prs_config not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
1713863150.272354 [PHY]   No prs_config configuration found..!!
[LIBCONFIG] (root): 2/2 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
1713863150.272403 [GNB_APP]   pdsch_AntennaPorts N1 1 N2 1 XP 1 pusch_AntennaPorts 1
1713863150.272405 [GNB_APP]   minTXRXTIME 6
1713863150.272406 [GNB_APP]   SIB1 TDA 1
1713863150.272407 [GNB_APP]   CSI-RS 0, SRS 0, 256 QAM may be on
[LIBCONFIG] gNBs.[0].servingCellConfigCommon.[0]: 60/60 parameters successfully set, (9 to default value)
1713863150.272483 [RRC]   Read in ServingCellConfigCommon (PhysCellId 0, ABSFREQSSB 641280, DLBand 78, ABSFREQPOINTA 640008, DLBW 106,RACH_TargetReceivedPower -96
1713863150.272486 [NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[37].band = 78)
1713863150.272488 [RRC]   absoluteFrequencySSB 641280 corresponds to 3619200000 Hz
1713863150.272490 [NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[37].band = 78)
1713863150.272491 [NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
1713863150.272494 [NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[37].band = 78)
1713863150.272496 [NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
[LIBCONFIG] list gNBs.[0].servingCellConfigDedicated not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
[LIBCONFIG] list gNBs.[0].E1_INTERFACE not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
1713863150.272571 [MAC]   [MAIN] Init function start:nb_nr_macrlc_inst=1
1713863150.272583 [UTIL]   Creating thread MAC_STATS with affinity -1 and priority 2
1713863150.273475 [UTIL]   threadCreate for MAC_STATS, affinity ffffffff, priority 2
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
[LIBCONFIG] list gNBs.[0].E1_INTERFACE not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
1713863150.278407 [PHY]   Installing callbacks for IF_Module - UL_indication
1713863150.278412 [MAC]   Allocating shared L1/L2 interface structure for instance 0 @ 0x600835db25b0
1713863150.278416 [NR_MAC]   Configuring common parameters from NR ServingCellConfig
1713863150.278418 [NR_MAC]   DL_Bandwidth:40
1713863150.278421 [NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[37].band = 78)
1713863150.278423 [NR_MAC]   DL_Bandwidth:40
1713863150.278426 [NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[37].band = 78)
1713863150.278427 [NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[37].band = 78)
1713863150.278429 [NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
1713863150.278433 [NR_MAC]   ssb_OffsetPointA 86, ssb_SubcarrierOffset 0
1713863150.278435 [NR_MAC]   Set RX antenna number to 1, Set TX antenna number to 1 (num ssb 1: 80000000,0)
1713863150.278437 [NR_MAC]   Setting TDD configuration period to 6
1713863150.278441 [NR_MAC]   TDD has been properly configurated
1713863150.278455 [NR_MAC]   PUSCH Target 200, PUCCH Target 150, PUCCH Failure 10, PUSCH Failure 10
**************** vnf_port:50001
1713863150.278459 [ENB_APP]   nfapi running mode: VNF
5328127210 [I]  733081600: nfapi_trace_init: NFAPI_TRACE_LEVEL='info'
5328127213 [I]  733081600: configure_nr_nfapi_vnf: [VNF] configure_nr_nfapi_vnf() vnf.p7_vnfs[0].config:0x600835db8930 VNF ADDRESS:172.24.10.72:50001
5328127216 [I]  733081600: configure_nr_nfapi_vnf: [VNF] Creating VNF NFAPI start thread configure_nr_nfapi_vnf
5328128545 [I]  733081600: configure_nr_nfapi_vnf: [VNF] Created VNF NFAPI start thread configure_nr_nfapi_vnf
**************** RETURNED FROM configure_nfapi_vnf() vnf_port:50001
[LIBCONFIG] (root): 2/2 parameters successfully set, (0 to default value)
5328128563 [I]  685749824: vnf_nr_start_thread: [VNF] VNF NFAPI thread - nfapi_vnf_start()vnf_nr_start_thread
5328128610 [I]  685749824: nfapi_nr_vnf_start: nfapi_nr_vnf_start()
5328128612 [I]  685749824: nfapi_nr_vnf_start: Starting P5 VNF connection on port 50001
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
5328128625 [I]  685749824: nfapi_nr_vnf_start: P5 socket created... 99
5328128628 [N]  685749824: nfapi_nr_vnf_start: VNF Setting the SCTP_INITMSG
5328128631 [I]  685749824: nfapi_nr_vnf_start: IPV4 binding to port 50001
[LIBCONFIG] gNBs.[0].plmn_list.[0]: 3/3 parameters successfully set, (0 to default value)
5328128635 [I]  685749824: nfapi_nr_vnf_start: bind succeeded..99.
1713863150.279894 [GNB_APP]   no slices transported via F1 Setup Request!
1713863150.279899 [NR_RRC]   SIB1 freq: offsetToPointA 86
5328128650 [I]  685749824: nfapi_nr_vnf_start: listen succeeded...
1713863150.279922 [NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[37].band = 78)
1713863150.279924 [NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
1713863150.279955 [GNB_APP]   F1AP: gNB idx 0 gNB_DU_id 3584, gNB_DU_name gNB-Eurecom-5GNRBox, TAC 1 MCC/MNC/length 1/1/2 cellID 12345678
1713863150.279957 [GNB_APP]   ngran_DU: Configuring Cell 0 for TDD
1713863150.279975 [PHY]   create_gNB_tasks() RC.nb_nr_L1_inst:0
1713863150.279977 [GNB_APP]   Allocating gNB_RRC_INST for 1 instances
[LIBCONFIG] (root): 2/2 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
NRRRC 0: Southbound Transport local_mac
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
[LIBCONFIG] list gNBs.[0].E1_INTERFACE not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
[LIBCONFIG] gNBs.[0].plmn_list.[0]: 3/3 parameters successfully set, (0 to default value)
1713863150.280074 [GNB_APP]   SDAP layer is disabled
1713863150.280076 [GNB_APP]   Data Radio Bearer count 1
1713863150.280109 [NR_RRC]   do_SIB23_NR, size 9 
 [LIBCONFIG] security: 4/4 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
[LIBCONFIG] list gNBs.[0].E1_INTERFACE not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
[LIBCONFIG] list gNBs.[0].E1_INTERFACE not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
[LIBCONFIG] list gNBs.[0].E1_INTERFACE not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
1713863150.280278 [PDCP]   pdcp init,usegtp 
[LIBCONFIG] eNBs.[0]: 1/1 parameters successfully set, (1 to default value)
[LIBCONFIG] gNBs.[0]: 1/1 parameters successfully set, (1 to default value)
[LIBCONFIG] (root): 2/2 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] gNBs.[0].plmn_list.[0]: 3/3 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0].plmn_list.[0].snssaiList.[0]: 2/2 parameters successfully set, (1 to default value)
[LIBCONFIG] gNBs.[0].amf_ip_address.[0]: 4/4 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0].SCTP: 2/2 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0].NETWORK_INTERFACES: 10/10 parameters successfully set, (3 to default value)
1713863150.280364 [GNB_APP]   default drx 0
1713863150.280369 [GNB_APP]   [gNB 0] gNB_app_register for instance 0
1713863150.280372 [UTIL]   Creating thread TASK_SCTP with affinity -1 and priority 50
1713863150.281342 [UTIL]   threadCreate for TASK_SCTP, affinity ffffffff, priority 50
1713863150.282604 [ITTI]   Created Posix thread TASK_SCTP
1713863150.282607 [X2AP]   X2AP is disabled.
[LIBCONFIG] gNBs.[0].NETWORK_INTERFACES: 10/10 parameters successfully set, (3 to default value)
1713863150.282631 [UTIL]   Creating thread TASK_NGAP with affinity -1 and priority 50
1713863150.283472 [UTIL]   threadCreate for TASK_NGAP, affinity ffffffff, priority 50
1713863150.284732 [ITTI]   Created Posix thread TASK_NGAP
1713863150.284735 [UTIL]   Creating thread TASK_GNB_APP with affinity -1 and priority 50
1713863150.284791 [NGAP]   Registered new gNB[0] and macro gNB id 3584
1713863150.284805 [NGAP]   [gNB 0] check the amf registration state
1713863150.285096 [NGAP]   3584 -> 0000e000
1713863150.285600 [UTIL]   threadCreate for TASK_GNB_APP, affinity ffffffff, priority 50
1713863150.286844 [ITTI]   Created Posix thread TASK_GNB_APP
1713863150.286848 [UTIL]   Creating thread TASK_RRC_GNB with affinity -1 and priority 50
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] MACRLCs.[0]: 34/34 parameters successfully set, (24 to default value)
[LIBCONFIG] list gNBs.[0].E1_INTERFACE not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.conf 
1713863150.286945 [GNB_APP]   [gNB 0] Received NGAP_REGISTER_GNB_CNF: associated AMF 1
1713863150.287755 [UTIL]   threadCreate for TASK_RRC_GNB, affinity ffffffff, priority 50
1713863150.289004 [ITTI]   Created Posix thread TASK_RRC_GNB
[LIBCONFIG] (root): 2/2 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0]: 30/30 parameters successfully set, (20 to default value)
[LIBCONFIG] gNBs.[0].plmn_list.[0]: 3/3 parameters successfully set, (0 to default value)
[LIBCONFIG] gNBs.[0].plmn_list.[0].snssaiList.[0]: 2/2 parameters successfully set, (1 to default value)
1713863150.289050 [GTPU]   Configuring GTPu
1713863150.289052 [NR_RRC]   Entering main loop of NR_RRC message task
[LIBCONFIG] (root): 2/2 parameters successfully set, (0 to default value)
1713863150.289055 [NR_RRC]   Received F1 Setup Request from gNB_DU 3584 (gNB-Eurecom-5GNRBox) on assoc_id -1
[LIBCONFIG] gNBs.[0].NETWORK_INTERFACES: 10/10 parameters successfully set, (3 to default value)
1713863150.289069 [GTPU]   SA mode 
1713863150.289080 [GTPU]   Configuring GTPu address : 192.168.70.129, port : 2152
1713863150.289082 [GTPU]   Initializing UDP for local address 192.168.70.129 with port 2152
1713863150.289094 [RRC]   Accepting DU 3584 (gNB-Eurecom-5GNRBox), sending F1 Setup Response
1713863150.289095 [RRC]   DU uses RRC version 17.3.0
1713863150.289096 [GTPU]   Created gtpu instance id: 101
1713863150.289099 [UTIL]   Creating thread TASK_GTPV1_U with affinity -1 and priority 50
1713863150.289100 [MAC]   received F1 Setup Response from CU (null)
1713863150.289101 [MAC]   CU uses RRC version 17.3.0
1713863150.289103 [NR_RRC]   Accepting new CU-UP ID 3584 name gNB-Eurecom-5GNRBox (assoc_id -1)
1713863150.289873 [UTIL]   threadCreate for TASK_GTPV1_U, affinity ffffffff, priority 50
1713863150.291097 [ITTI]   Created Posix thread TASK_GTPV1_U
NFAPI*** - mutex and cond created - will block shortly for completion of PNF connection
START MAIN THREADS
RC.nb_nr_L1_inst:0
wait_gNBs()
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 0)
gNB L1 are configured
About to Init RU threads RC.nb_RU:0
Entering ITTI signals handler
TYPE <CTRL-C> TO TERMINATE
5328258341 [I]  685749824: nfapi_nr_vnf_start: Accepting connection from PNF...
5328258402 [I]  685749824: nfapi_nr_vnf_start: PNF connection (fd:102) accepted from 172.24.11.58:52299 
5328258457 [I]  685749824: nfapi_nr_vnf_start: MALLOC nfapi_vnf_pnf_info_t for pnf_list pnf:0x7c4210000b70
5328258459 [I]  685749824: pnf_nr_connection_indication_cb: [VNF] pnf connection indication idx:0
5328258461 [I]  685749824: oai_create_gnb: oai_create_gnb() gNB is now configured
5328258486 [I]  685749824: nfapi_nr_vnf_start: VNF Association ID = 33
5328258488 [I]  685749824: nfapi_nr_vnf_start: VNF Receiver window size = 106488
5328258489 [I]  685749824: nfapi_nr_vnf_start: VNF In Streams = 5
5328258490 [I]  685749824: nfapi_nr_vnf_start: VNF Out Streams = 5
5328261933 [I]  685749824: vnf_nr_handle_pnf_param_response: Received PNF_PARAM.reponse
5328261937 [I]  685749824: pnf_nr_param_resp_cb: [VNF] pnf param response idx:0 error:0
5328261938 [I]  685749824: pnf_nr_param_resp_cb: [VNF] (PHY:0) phy_config_idx:0
5328261939 [I]  685749824: nfapi_vnf_phy_info_list_add: Adding phy p5_idx:0 phy_id:1
5328261944 [I]  685749824: pnf_nr_param_resp_cb: [VNF] (PHY:0) (RF0) 0
5328261954 [I]  685749824: pnf_nr_param_resp_cb: [VNF] (PHY:0) (RF1) 0
5328261964 [I]  685749824: pnf_nr_param_resp_cb: Hard coded num phy rf to 2
5328264491 [I]  685749824: vnf_nr_handle_pnf_config_response: Received PNF_CONFIG_RESPONSE
5328264494 [I]  685749824: pnf_nr_config_resp_cb: [VNF] pnf config response idx:0 resp[header[phy_id:0 message_id:103 message_length:1]]
5328267300 [I]  685749824: vnf_nr_handle_pnf_start_response: Received PNF_START_RESPONSE
5328267301 [I]  685749824: pnf_nr_start_resp_cb: [VNF] pnf start response idx:0 config:0x600835db8a80 user_data:0x600833e41e20 p7_vnf[config:0x600835db8930 thread_started:0]
5328269083 [I]  685749824: pnf_nr_start_resp_cb: [VNF] Sending NFAPI_VNF_PARAM_REQUEST phy_id:1
Calling sched_setscheduler(79)
5328269150 [I]  562013760: vnf_nr_p7_thread_start: [VNF] Creating VNF NFAPI P7 start thread vnf_nr_p7_thread_start
5328270933 [I]  553621056: vnf_nr_p7_start_thread: vnf_nr_p7_start_thread()
5328270943 [I]  553621056: nfapi_nr_vnf_p7_start: nfapi_nr_vnf_p7_start()
5328270944 [I]  553621056: nfapi_nr_vnf_p7_start: Initialising VNF P7 port:50011
5328270959 [I]  553621056: nfapi_nr_vnf_p7_start: VNF P7 socket created...
5328270963 [I]  553621056: nfapi_nr_vnf_p7_start: VNF P7 setsockopt succeeded...
5328270966 [I]  553621056: nfapi_nr_vnf_p7_start: VNF P7 binding too 0.0.0.0:50011
5328270971 [I]  553621056: nfapi_nr_vnf_p7_start: VNF P7 bind succeeded...
5328272669 [I]  685749824: vnf_nr_handle_param_response: Received PARAM_RESPONSE
5328272707 [I]  685749824: vnf_nr_handle_param_response: PNF P7 IPv4 address: 172.24.11.58
5328272710 [I]  685749824: vnf_nr_handle_param_response: PNF P7 IPv6 address: ::
5328272711 [I]  685749824: vnf_nr_handle_param_response: PNF P7 Port: 23235
5328272712 [I]  685749824: nr_param_resp_cb: [VNF] Received NFAPI_PARAM_RESP idx:0 phy_id:1
5328272713 [I]  685749824: nr_param_resp_cb: [VNF] 0.1 pnf p7 172.24.11.58:23235 timing 30 1 0 1
5328272715 [I]  685749824: nfapi_vnf_p7_add_pnf: nfapi_vnf_p7_add_pnf(config:0x600835db8930 phy_id:1 pnf_addr:172.24.11.58 pnf_p7_port:23235)
5328272718 [I]  685749824: vnf_p7_connection_info_list_add: vnf_p7_connection_info_list_add()
5328272719 [I]  685749824: nr_param_resp_cb: [VNF] Send NFAPI_CONFIG_REQUEST
5328272720 [I]  685749824: nr_param_resp_cb: [VNF] Local_port:23491
5328272721 [I]  685749824: nr_param_resp_cb: [VNF] Local_addr:172.24.10.72
5328272722 [I]  685749824: nr_param_resp_cb: 
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
    prach_root_sequence_index t 4117 l 131 v 1
    num_root_sequences t 4118 l 0 v 16
    k1 t 4119 l 0 v 0
    prach_zero_corr_conf t 4120 l 28524 v 13
    num_unused_root_sequences t 4121 l 26996 v 0
  ssb_per_rach t 4123 l 0 v 3
  prach_multiple_carriers_in_a_band t 0 l 0 v 0
[VNF] Sent NFAPI_VNF_CONFIG_REQ num_tlv:127
5328308356 [I]  685749824: vnf_nr_handle_config_response: Received CONFIG_RESPONSE
5328308361 [I]  685749824: nr_config_resp_cb: [VNF] Received NFAPI_CONFIG_RESP idx:0 phy_id:1
5328308362 [I]  685749824: nr_config_resp_cb: [VNF] Calling oai_enb_init()
5331824328 [I]  685749824: vnf_nr_read_dispatch_message: VNF Failed to peek sctp message size errno:104
5331824346 [I]  685749824: pnf_disconnection_indication_cb: [VNF] pnf disconnection indication idx:0
5331824349 [I]  685749824: nfapi_vnf_p7_del_pnf: nfapi_vnf_p7_del_pnf(phy_id:1)
5331824351 [I]  685749824: nfapi_vnf_p7_del_pnf: nfapi_vnf_p7_del_pnf(phy_id:1) deleting connection info
```