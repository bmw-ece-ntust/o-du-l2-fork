# PNF

Created time: 2024年10月16日 下午1:25

```bash
CMDLINE: "./nr-softmodem" "-O" "../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/oaiL1.nfapi.usrpb210.conf" "--nfapi" "PNF" "--rfsim" "--rfsimulator.serveraddr" "server" "--log_config.global_log_options" "wall_clock" "--sa" 
[CONFIG] get parameters from libconfig ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/oaiL1.nfapi.usrpb210.conf [LIBCONFIG] Path for include directive set to: ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF
[CONFIG] function config_libconfig_init returned 0
[CONFIG] config module libconfig loaded
[LIBCONFIG] config: 2/2 parameters successfully set, (2 to default value)
[CONFIG] debug flags: 0x00000000
[LIBCONFIG] log_config: 3/3 parameters successfully set, (1 to default value)
[LIBCONFIG] log_config: 53/53 parameters successfully set, (51 to default value)
[LIBCONFIG] log_config: 53/53 parameters successfully set, (53 to default value)
[LIBCONFIG] log_config: 16/16 parameters successfully set, (16 to default value)
[LIBCONFIG] log_config: 16/16 parameters successfully set, (16 to default value)
log init done
1713863139.113001 [HW]   # /dev/cpu_dma_latency set to 2 us
Reading in command-line options
[LIBCONFIG] (root): 40/40 parameters successfully set, (37 to default value)
[LIBCONFIG] (root): 6/6 parameters successfully set, (5 to default value)
1713863139.273383 [ENB_APP]   nfapi running mode: PNF
1713863139.273469 [GNB_APP]   Getting GNBSParams
[LIBCONFIG] (root): 2/2 parameters successfully set, (1 to default value)
[LIBCONFIG] list MACRLCs not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/oaiL1.nfapi.usrpb210.conf 
[LIBCONFIG] list THREAD_STRUCT not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/oaiL1.nfapi.usrpb210.conf 
[CONFIG] parallel_conf is set to 2
[CONFIG] worker_conf is set to 1
Configuration: nb_rrc_inst 0, nb_nr_L1_inst 1, nb_ru 1
[LIBCONFIG] TTracer: 3/3 parameters successfully set, (3 to default value)
configuring for RAU/RRU
1713863140.273956 [ITTI]   Starting itti queue: TASK_UNKNOWN as task 0
1713863140.274042 [ITTI]   Starting itti queue: TASK_TIMER as task 1
1713863140.274074 [ITTI]   Starting itti queue: TASK_L2L1 as task 2
1713863140.274105 [ITTI]   Starting itti queue: TASK_BM as task 3
1713863140.274134 [ITTI]   Starting itti queue: TASK_PHY_ENB as task 4
1713863140.274165 [ITTI]   Starting itti queue: TASK_MAC_GNB as task 5
1713863140.274193 [ITTI]   Starting itti queue: TASK_RLC_ENB as task 6
1713863140.274222 [ITTI]   Starting itti queue: TASK_RRC_ENB_NB_IoT as task 7
1713863140.274252 [ITTI]   Starting itti queue: TASK_PDCP_ENB as task 8
1713863140.274290 [ITTI]   Starting itti queue: TASK_PDCP_GNB as task 9
1713863140.274320 [ITTI]   Starting itti queue: TASK_DATA_FORWARDING as task 10
1713863140.274350 [ITTI]   Starting itti queue: TASK_END_MARKER as task 11
1713863140.274379 [ITTI]   Starting itti queue: TASK_RRC_ENB as task 12
1713863140.274407 [ITTI]   Starting itti queue: TASK_RRC_GNB as task 13
1713863140.274436 [ITTI]   Starting itti queue: TASK_RAL_ENB as task 14
1713863140.274465 [ITTI]   Starting itti queue: TASK_S1AP as task 15
1713863140.274494 [ITTI]   Starting itti queue: TASK_NGAP as task 16
1713863140.274524 [ITTI]   Starting itti queue: TASK_X2AP as task 17
1713863140.274552 [ITTI]   Starting itti queue: TASK_M2AP_ENB as task 18
1713863140.274581 [ITTI]   Starting itti queue: TASK_M2AP_MCE as task 19
1713863140.274614 [ITTI]   Starting itti queue: TASK_M3AP as task 20
1713863140.274645 [ITTI]   Starting itti queue: TASK_M3AP_MME as task 21
1713863140.274674 [ITTI]   Starting itti queue: TASK_M3AP_MCE as task 22
1713863140.274703 [ITTI]   Starting itti queue: TASK_SCTP as task 23
1713863140.274732 [ITTI]   Starting itti queue: TASK_ENB_APP as task 24
1713863140.274762 [ITTI]   Starting itti queue: TASK_GNB_APP as task 25
1713863140.274790 [ITTI]   Starting itti queue: TASK_MCE_APP as task 26
1713863140.274824 [ITTI]   Starting itti queue: TASK_MME_APP as task 27
1713863140.274853 [ITTI]   Starting itti queue: TASK_PHY_UE as task 28
1713863140.274883 [ITTI]   Starting itti queue: TASK_MAC_UE as task 29
1713863140.274919 [ITTI]   Starting itti queue: TASK_RLC_UE as task 30
1713863140.274949 [ITTI]   Starting itti queue: TASK_PDCP_UE as task 31
1713863140.274979 [ITTI]   Starting itti queue: TASK_RRC_UE as task 32
1713863140.275010 [ITTI]   Starting itti queue: TASK_RRC_NRUE as task 33
1713863140.275039 [ITTI]   Starting itti queue: TASK_NAS_UE as task 34
1713863140.275071 [ITTI]   Starting itti queue: TASK_RAL_UE as task 35
1713863140.275100 [ITTI]   Starting itti queue: TASK_GTPV1_U as task 36
1713863140.275129 [ITTI]   Starting itti queue: TASK_CU_F1 as task 37
1713863140.275158 [ITTI]   Starting itti queue: TASK_DU_F1 as task 38
1713863140.275191 [ITTI]   Starting itti queue: TASK_CUCP_E1 as task 39
1713863140.275221 [ITTI]   Starting itti queue: TASK_CUUP_E1 as task 40
1713863140.275252 [ITTI]   Starting itti queue: TASK_RRC_UE_SIM as task 41
1713863140.275282 [ITTI]   Starting itti queue: TASK_RRC_GNB_SIM as task 42
1713863140.275311 [ITTI]   Starting itti queue: TASK_RRC_NSA_UE as task 43
1713863140.275339 [ITTI]   Starting itti queue: TASK_RRC_NSA_NRUE as task 44
1713863140.275368 [ITTI]   Starting itti queue: TASK_NAS_NRUE as task 45
[LIBCONFIG] opt: 3/3 parameters successfully set, (3 to default value)
1713863140.275460 [OPT]   OPT disabled
1713863140.275474 [HW]   Version: Branch: nfapi-fixes Abrev. Hash: f50933751c Date: Tue Feb 20 16:33:03 2024 +0100
[LIBCONFIG] list gNBs not found in config file ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/oaiL1.nfapi.usrpb210.conf 
1713863140.275508 [NR_PHY]   RC.gNB = 0x56051be600b0
[LIBCONFIG] L1s.[0]: 20/20 parameters successfully set, (11 to default value)
1713863140.277391 [PHY]   L1_RX_THREAD_CORE -1 (16)
1713863140.277412 [PHY]   TX_AMP = 519 (-36 dBFS)
1713863140.277431 [PHY]   RCconfig_NR_L1() NFAPI PNF mode - RC.nb_nr_inst=1 this is because phy_init_RU() uses that to index and not RC.num_gNB - why the 2 similar variables?
1713863140.277447 [PHY]   RCconfig_NR_L1() NFAPI PNF mode - RC.nb_nr_CC[0]=1 for init_gNB_afterRU()
1713863140.277463 [PHY]   RCconfig_NR_L1() NFAPI PNF mode - RC.nb_nr_macrlc_inst:1 because used by mac_top_init_gNB()
configure_nr_nfapi_pnf() PNF

1713863140.277493 [ENB_APP]   nfapi running mode: PNF
configure_nr_nfapi_pnf() VNF:172.24.10.72:50001 PNF_PHY[addr:172.24.11.58 UDP:tx_addr:172.24.10.72:50011 rx:50010]
178875815 [I] 1386710848: nfapi_trace_init: NFAPI_TRACE_LEVEL='info'
178875831 [I] 1386710848: configure_nr_nfapi_pnf: [PNF] Creating PNF NFAPI start thread configure_nr_nfapi_pnf
178881916 [I] 1348306688: pnf_nr_start_thread: [PNF] IN PNF NFAPI start thread pnf_nr_start_thread
Initializing northbound interface for L1
178881976 [I] 1348306688: nfapi_nr_pnf_start: nfapi_nr_pnf_start
1713863140.283710 [PHY]   l1_north_init_gNB() RC.nb_nr_L1_inst:1
178882023 [I] 1348306688: pnf_connect: Starting P5 PNF connection to VNF at 172.24.10.72:50001
1713863140.283742 [PHY]   Installing callbacks for IF_Module - UL_indication
1713863140.283763 [MAC]   Allocating shared L1/L2 interface structure for instance 0 @ 0x56051be63430
1713863140.283781 [PHY]   l1_north_init_gNB() RC.gNB[0] installing callbacks
NFAPI*** - mutex and cond created - will block shortly for completion of PNF connection
START MAIN THREADS
RC.nb_nr_L1_inst:1
Initializing gNB threads single_thread_flag:1 wait_for_sync:0
1713863140.318323 [PHY]   Initializing gNB 0 single_thread_flag:1
1713863140.318351 [PHY]   Initializing gNB 0
1713863140.318367 [PHY]   Registering with MAC interface module (before 0x56051be63430)
1713863140.318383 [PHY]   Installing callbacks for IF_Module - UL_indication
1713863140.318400 [PHY]   Registering with MAC interface module (after 0x56051be63430)
1713863140.318415 [PHY]   Setting indication lists
1713863140.318430 [PHY]   [nr-gnb.c] gNB structure allocated
wait_gNBs()
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
178964066 [N] 1348306688: pnf_connect: PNF Setting the SCTP_INITMSG
178964121 [I] 1348306688: pnf_connect: P5 socket created...
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
178967032 [E] 1348306688: pnf_connect: After connect (address:172.24.10.72 port:50001) errno: 111
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
180970773 [I] 1348306688: pnf_connect: Starting P5 PNF connection to VNF at 172.24.10.72:50001
180970907 [N] 1348306688: pnf_connect: PNF Setting the SCTP_INITMSG
180970952 [I] 1348306688: pnf_connect: P5 socket created...
180984695 [E] 1348306688: pnf_connect: After connect (address:172.24.10.72 port:50001) errno: 111
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
182986765 [I] 1348306688: pnf_connect: Starting P5 PNF connection to VNF at 172.24.10.72:50001
182986927 [N] 1348306688: pnf_connect: PNF Setting the SCTP_INITMSG
182986966 [I] 1348306688: pnf_connect: P5 socket created...
182990299 [E] 1348306688: pnf_connect: After connect (address:172.24.10.72 port:50001) errno: 111
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
185002815 [I] 1348306688: pnf_connect: Starting P5 PNF connection to VNF at 172.24.10.72:50001
185002917 [N] 1348306688: pnf_connect: PNF Setting the SCTP_INITMSG
185002960 [I] 1348306688: pnf_connect: P5 socket created...
185005878 [E] 1348306688: pnf_connect: After connect (address:172.24.10.72 port:50001) errno: 111
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
187018784 [I] 1348306688: pnf_connect: Starting P5 PNF connection to VNF at 172.24.10.72:50001
187018901 [N] 1348306688: pnf_connect: PNF Setting the SCTP_INITMSG
187018941 [I] 1348306688: pnf_connect: P5 socket created...
187022528 [E] 1348306688: pnf_connect: After connect (address:172.24.10.72 port:50001) errno: 111
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
189034777 [I] 1348306688: pnf_connect: Starting P5 PNF connection to VNF at 172.24.10.72:50001
189034879 [N] 1348306688: pnf_connect: PNF Setting the SCTP_INITMSG
189034911 [I] 1348306688: pnf_connect: P5 socket created...
189041124 [I] 1348306688: pnf_connect: connect succeeded...
189041159 [N] 1348306688: pnf_connect: After connect loop
189041184 [I] 1348306688: pnf_connect: Association ID = 3
189041200 [I] 1348306688: pnf_connect: Receiver window size = 67108864
189041216 [I] 1348306688: pnf_connect: In Streams = 5
189041231 [I] 1348306688: pnf_connect: Out Streams = 5
189041247 [N] 1348306688: pnf_connect: Socket CONNECTED
189041299 [I] 1348306688: pnf_nr_handle_pnf_param_request: PNF_PARAM.request received
[PNF] pnf param request
189043783 [I] 1348306688: pnf_nr_handle_pnf_config_request: PNF_CONFIG.request received
[PNF] pnf config request
[PNF] pnf config request assigned phy_id 1 to phy_config_index 0
[PNF] Sent pnf_config_resp
189046732 [I] 1348306688: pnf_nr_handle_pnf_start_request: PNF_START.request Received
Received NFAPI_PNF_START_REQUEST
[PNF] Sent NFAPI_PNF_START_RESP
Waiting for gNB L1 instances to all get configured ... sleeping 50ms (nb_nr_sL1_inst 1)
189051761 [I] 1348306688: pnf_nr_handle_param_request: PARAM.request received
[PNF] Received NFAPI_PARAM_REQUEST phy_id:1
TAG value :2
RUNNING pack_param_response
[PNF] Sent NFAPI_PNF_PARAM_RESPONSE phy_id:1 number_of_tlvs:62
189083081 [I] 1348306688: pnf_nr_handle_config_request: CONFIG.request received
7f 10 01 00 02 00 28 00 00 10 02 00 04 00 36 ee f8 10 03 00 0a 00 00 00 00 00 00 00 00 00 00 00 00 10 04 00 0a 00 00 00 6a 00 00 00 00 00 00 00 00 10 05 00 02 00 01 00 00 10 06 00 02 00 28 00 00 10 07 00 04 00 36 ee f8 10 08 00 0a 00 00 00 00 00 00 00 00 00 00 00 00 10 09 00 0a 00 00 00 6a 00 00 00 00 00 00 00 00 10 0a 00 02 00 01 00 00 10 0c 00 02 00 00 00 00 10 0d 00 01 01 00 00 00 10 0e 00 04 ff ff ff e7 10 0f 00 01 01 00 00 00 10 10 00 01 01 00 00 00 10 11 00 01 01 00 00 00 10 12 00 01 01 00 00 00 10 13 00 01 00 00 00 00 10 14 00 01 01 00 00 00 10 29 00 01 62 00 00 00 10 15 00 02 00 01 00 00 10 16 00 01 10 00 00 00 10 17 00 02 00 00 00 00 10 18 00 01 0d 00 00 00 10 19 00 02 6e 00 00 00 10 1b 00 01 03 00 00 00 10 1d 00 02 00 56 00 00 10 1f 00 01 02 00 00 00 10 20 00 01 00 00 00 00 10 22 00 04 80 00 00 00 10 22 00 04 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 23 00 01 00 00 00 00 10 26 00 01 06 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 02 00 00 00 10 27 00 01 02 00 00 00 10 27 00 01 02 00 00 00 10 27 00 01 02 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 00 00 00 00 10 27 00 01 02 00 00 00 10 27 00 01 02 00 00 00 10 27 00 01 02 00 00 00 10 27 00 01 02 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 10 27 00 01 01 00 00 00 01 00 00 04 ac 18 0a 48 01 02 00 02 c3 5b 00 00 01 1e 00 01 1e 00 00 00 01 1f 00 01 03 00 00 00 01 20 00 01 0a 00 00 00 f0 02 00 04 00 00 07 e0 
*** have tag 1001, idx 0
*** have tag 1002, idx 1
*** have tag 1005, idx 4
*** have tag 1006, idx 5
*** have tag 1007, idx 6
*** have tag 100a, idx 9
*** have tag 100c, idx 11
*** have tag 100d, idx 12
*** have tag 100e, idx 13
*** have tag 100f, idx 14
*** have tag 1010, idx 15
*** have tag 1011, idx 16
*** have tag 1012, idx 17
*** have tag 1013, idx 18
*** have tag 1014, idx 19
*** have tag 1029, idx 20
*** have tag 101b, idx 27
*** have tag 101d, idx 29
*** have tag 101f, idx 31
*** have tag 1020, idx 32
*** have tag 1026, idx 38
*** have tag 100, idx 41
*** have tag 102, idx 43
*** have tag 11e, idx 44
*** have tag 11f, idx 45
*** have tag 120, idx 46
[PNF] vnf p7 0.1.4.0:50011
carrier_config
  bw t 4097 l 2 v 40
  freq t 4098 l 4 v 3600120
  dl_k0[0] t 0 l 0 v 0
  dl_k0[1] t 4099 l 10 v 0
  dl_k0[2] t 0 l 0 v 0
  dl_k0[3] t 0 l 0 v 0
  dl_k0[4] t 0 l 0 v 0
  dl_grid_size[0] t 0 l 0 v 0
  dl_grid_size[1] t 4100 l 10 v 106
  dl_grid_size[2] t 0 l 0 v 0
  dl_grid_size[3] t 0 l 0 v 0
  dl_grid_size[4] t 0 l 0 v 0
  num_tx_ant t 4101 l 2 v 1
  uplink_bandwidth t 4102 l 2 v 40
  uplink_frequency t 4103 l 4 v 3600120
  ul_k0[0] t 0 l 0 v 0
  ul_k0[1] t 4104 l 10 v 0
  ul_k0[2] t 0 l 0 v 0
  ul_k0[3] t 0 l 0 v 0
  ul_k0[4] t 0 l 0 v 0
  ul_grid_size[0] t 0 l 0 v 0
  ul_grid_size[1] t 4105 l 10 v 106
  ul_grid_size[2] t 0 l 0 v 0
  ul_grid_size[3] t 0 l 0 v 0
  ul_grid_size[4] t 0 l 0 v 0
  num_rx_ant t 4106 l 2 v 1
  frequency_shift_7p5khz t 0 l 0 v 0
prach_config
  prach_sequence_length t 4113 l 1 v 1
  prach_sub_c_spacing t 4114 l 1 v 1
  restricted_set_config t 4115 l 1 v 0
  num_prach_fd_occasions t 4116 l 1 v 1
  prach_ConfigurationIndex t 4137 l 1 v 98
    prach_root_sequence_index t 4117 l 2 v 1
    num_root_sequences t 4118 l 1 v 16
    k1 t 4119 l 2 v 0
    prach_zero_corr_conf t 4120 l 1 v 13
    num_unused_root_sequences t 4121 l 2 v 0
  ssb_per_rach t 4123 l 1 v 3
  prach_multiple_carriers_in_a_band t 0 l 0 v 0
[PNF] Received NFAPI_CONFIG_REQ phy_id:1

Timing window tag: 286
Phy_info:Timing window:30 NFAPI_CONFIG:timing_window:30
timing info mode:3
timing info period provided value:10
189086437 [E] 1348306688: nr_config_request: nr_config_request() NFAPI_NR_CONFIG_DL_BANDWIDTH_TAG N_RB_DL:40
[PNF] CONFIG_REQUEST[num_tlv:127] TLVs processed:6
[PNF] Simulating PHY CONFIG
DL frequency 3619200000: band 48, UL frequency 3619200000
1713863150.488212 [PHY]   DL frequency 3619200000 Hz, UL frequency 3619200000 Hz: band 48, uldl offset 0 Hz
1713863150.488238 [PHY]   Configuring MIB for instance 0, : (Nid_cell 0,DL freq 3619200000, UL freq 3619200000)
1713863150.488258 [PHY]   Initializing frame parms for mu 1, N_RB 106, Ncp 0
1713863150.488277 [PHY]   Init: N_RB_DL 106, first_carrier_offset 1412, nb_prefix_samples 144,nb_prefix_samples0 176, ofdm_symbol_size 2048
1713863150.489164 [PHY]   gNB 0 configured
1713863150.489190 [PHY]   fp->scs=30000
1713863150.489207 [PHY]   fp->ofdm_symbol_size=2048
1713863150.489224 [PHY]   fp->nb_prefix_samples0=176
1713863150.489238 [PHY]   fp->nb_prefix_samples=144
1713863150.489252 [PHY]   fp->slots_per_subframe=2
1713863150.489266 [PHY]   fp->samples_per_subframe_wCP=57344
1713863150.489282 [PHY]   fp->samples_per_frame_wCP=573440
1713863150.489296 [PHY]   fp->samples_per_subframe=61440
1713863150.489310 [PHY]   fp->samples_per_frame=614400
1713863150.489325 [PHY]   fp->dl_CarrierFreq=3619200000
1713863150.489339 [PHY]   fp->ul_CarrierFreq=3619200000
[PNF] 1 vnf p7 172.24.10.72:50011 timing 30 3 10
[PNF] Sent NFAPI_PNF_CONFIG_RESPONSE phy_id:1
189089784 [I] 1348306688: pnf_nr_handle_start_request: pnf_nr_handle_start_request() START.request received state:2
[PNF] Received NFAPI_START_REQ phy_id:1
gNB L1 are configured
About to Init RU threads RC.nb_RU:1
Initializing RU threads
configuring RU from file
[LIBCONFIG] RUs.[0]: 43/43 parameters successfully set, (34 to default value)
Set RU mask to 1
[PNF] P7 remote:172.24.10.72:50011 local:172.24.11.58:50010
subframe_buffer_size configured using phy_info->timing_window:30
189223290 [I] 1348306688: nr_start_request: [PNF] Creating P7 thread nr_start_request
189228973 [I] 1348306688: nr_start_request: [PNF] Calling l1_north_init_eNB() nr_start_request
189228993 [I] 1339913984: pnf_nr_p7_thread_start: [NR_PNF] NR P7 THREAD pnf_nr_p7_thread_start
1713863150.630734 [PHY]   l1_north_init_gNB() RC.nb_nr_L1_inst:1
Calling sched_setscheduler(79)
1713863150.630770 [PHY]   Installing callbacks for IF_Module - UL_indication
1713863150.630787 [PHY]   l1_north_init_gNB() RC.gNB[0] installing callbacks
189229096 [I] 1348306688: nr_start_request: [PNF] HACK - Set p7_config global ready for subframe indnr_start_request
189229110 [I] 1339913984: nfapi_nr_pnf_p7_start: nfapi_nr_pnf_p7_start
189229187 [I] 1339913984: pnf_nr_p7_message_pump: PNF P7 socket created (99)...
189229216 [I] 1339913984: pnf_nr_p7_message_pump: PNF P7 binding 99 too 172.24.11.58:50010
189229240 [I] 1339913984: pnf_nr_p7_message_pump: PNF P7 bind succeeded...
Creating RC.ru[0]:0x56051be66040
1713863150.631612 [PHY]   RU GPIO control set as 'generic'
1713863150.631633 [PHY]   Setting clock source to internal
1713863150.631647 [PHY]   Setting time source to internal
Setting function for RU 0 to gNodeB_3GPP
[RU 0] Setting nr_flag 0, nr_band 78, nr_scs_for_raster 1
[RU 0] Setting half-slot parallelization to 1
1713863150.631754 [PHY]   number of L1 instances 1, number of RU 1, number of CPU cores 8
1713863150.631773 [PHY]   Copying frame parms from gNB in RC to gNB 0 in ru 0 and frame_parms in ru
configuring ru_id 0 (start_rf 0x560516fd3a10)
1713863150.632307 [PHY]   Initialized RU proc 0 (,synch_to_ext_device),
1713863150.632346 [PHY]   RU Thread pool size 2
1713863150.632378 [PHY]   RU thread-pool core string -1,-1
create a thread for core -1
1713863150.632434 [UTIL]   Creating thread Tpool0_-1 with affinity -1 and priority 97
1713863150.649641 [UTIL]   threadCreate for Tpool0_-1, affinity ffffffff, priority 97
create a thread for core -1
1713863150.658329 [UTIL]   Creating thread Tpool1_-1 with affinity -1 and priority 97
1713863150.675233 [UTIL]   threadCreate for Tpool1_-1, affinity ffffffff, priority 97
1713863150.681232 [UTIL]   Creating thread ru_thread with affinity -1 and priority 97
1713863150.698453 [UTIL]   threadCreate for ru_thread, affinity ffffffff, priority 97
1713863150.704302 [PHY]   Starting RU 0 (,synch_to_ext_device) on cpu 3
1713863150.704388 [PHY]   Initializing frame parms for mu 1, N_RB 106, Ncp 0
1713863150.704403 [PHY]   Init: N_RB_DL 106, first_carrier_offset 1412, nb_prefix_samples 144,nb_prefix_samples0 176, ofdm_symbol_size 2048
1713863150.704415 [PHY]   fp->scs=30000
1713863150.704423 [PHY]   fp->ofdm_symbol_size=2048
1713863150.704431 [PHY]   fp->nb_prefix_samples0=176
1713863150.704439 [PHY]   fp->nb_prefix_samples=144
1713863150.704446 [PHY]   fp->slots_per_subframe=2
1713863150.704453 [PHY]   fp->samples_per_subframe_wCP=57344
1713863150.704462 [PHY]   fp->samples_per_frame_wCP=573440
1713863150.704470 [PHY]   fp->samples_per_subframe=61440
1713863150.704477 [PHY]   fp->samples_per_frame=614400
1713863150.704484 [PHY]   fp->dl_CarrierFreq=3619200000
1713863150.704492 [PHY]   fp->ul_CarrierFreq=3619200000
1713863150.704506 [PHY]   Initializing RU signal buffers (if_south local RF) nb_tx 1, nb_rx 1
1713863150.708970 [PHY]   [INIT] common.txdata[0] = 0x7f144da2a040 (2458880 bytes,sf_extension 320)
1713863150.708987 [PHY]   [INIT] common.txdata[0] = 0x7f144da2a540 
1713863150.710888 [PHY]   nb_tx 1
1713863150.711685 [PHY]   rxdata_7_5kHz[0] 0x7f144d6e0040 for RU 0
1713863150.713503 [PHY]   [INIT] common.txdata_BF= 0x7f1438000b00 (8 bytes)
1713863150.713708 [PHY]   txdataF_BF[0] 0x7f1452919040 for RU 0
1713863150.714084 [PHY]   rxdataF[0] 0x7f14528a8040 for RU 0
waiting for NFAPI PNF connection and population of global structure (main?)
1713863150.729115 [PHY]   [INIT] nr_phy_init_RU() ru->num_gNB:1 
1713863150.730917 [PHY]   Setting RF config for N_RB 106, NB_RX 1, NB_TX 1
1713863150.730939 [PHY]   tune_offset 0 Hz, sample_rate 61440000 Hz
1713863150.730965 [PHY]   Channel 0: setting tx_gain offset 0, tx_freq 3619200000 Hz
1713863150.730989 [PHY]   Channel 0: setting rx_gain offset 125, rx_freq 3619200000 Hz
[LIBCONFIG] device.recplay: 8/8 parameters successfully set, (8 to default value)
[LIBCONFIG] device: 1/1 parameters successfully set, (1 to default value)
[LIBCONFIG] loader: 2/2 parameters successfully set, (2 to default value)
[LIBCONFIG] loader.rfsimulator: 2/2 parameters successfully set, (1 to default value)
shlib_path librfsimulator.so
[LOADER] library librfsimulator.so successfully loaded
[LIBCONFIG] rfsimulator: 9/9 parameters successfully set, (8 to default value)
1713863150.735211 [HW]   sample_rate 61440000.000000
1713863150.735238 [HW]   Running as server waiting opposite rfsimulators to connect
Initializing random number generator, seed 1118965682306293138
1713863150.735633 [HW]   [RAU] has loaded RFSIMULATOR device.
setup_RU_buffers: frame_parms = 0x7f144f486010
1713863150.735666 [PHY]   RU 0 Setting N_TA_offset to 800 samples (factor 2.000000, UL Freq 3600120, N_RB 106, mu 1)
1713863150.735685 [PHY]   Signaling main thread that RU 0 is ready, sl_ahead 5
waiting for sync (ru_thread,-1/0x560517d7d0b4,0x5605196b3e80,0x5605196b30c0)
[PNF] waiting for OAI to be configured (eNB/RU)
[PNF] OAI eNB/RU configured
[PNF] About to call init_eNB_afterRU()
1713863155.630927 [PHY]   init_eNB_afterRU() RC.nb_nr_inst:0
1713863155.630966 [PHY]   RC.nb_nr_CC[inst:0]:0x7f14505d9010
1713863155.630998 [PHY]   [gNB 0] phy_init_nr_gNB() About to wait for gNB to be configured
[LIBCONFIG] loader.dfts: 2/2 parameters successfully set, (1 to default value)
shlib_path libdfts.so
[LOADER] library libdfts.so successfully loaded
[LIBCONFIG] loader.ldpc: 2/2 parameters successfully set, (1 to default value)
shlib_path libldpc.so
[LOADER] library libldpc.so successfully loaded
1713863157.359081 [PHY]   Initialise nr transport
1713863158.667812 [PHY]   Mapping RX ports from 1 RUs to gNB 0
1713863158.667861 [PHY]   gNB->num_RU:1
1713863158.667878 [PHY]   Attaching RU 0 antenna 0 to gNB antenna 0
create a thread for core -1
1713863158.667935 [UTIL]   Creating thread Tpool0_-1 with affinity -1 and priority 97
1713863158.816157 [UTIL]   threadCreate for Tpool0_-1, affinity ffffffff, priority 97
create a thread for core -1
1713863158.822233 [UTIL]   Creating thread Tpool1_-1 with affinity -1 and priority 97
1713863158.894015 [UTIL]   threadCreate for Tpool1_-1, affinity ffffffff, priority 97
create a thread for core -1
1713863158.900003 [UTIL]   Creating thread Tpool2_-1 with affinity -1 and priority 97
1713863159.036661 [UTIL]   threadCreate for Tpool2_-1, affinity ffffffff, priority 97
create a thread for core -1
1713863159.042548 [UTIL]   Creating thread Tpool3_-1 with affinity -1 and priority 97
1713863159.185601 [UTIL]   threadCreate for Tpool3_-1, affinity ffffffff, priority 97
create a thread for core -1
1713863159.191494 [UTIL]   Creating thread Tpool4_-1 with affinity -1 and priority 97
1713863159.335190 [UTIL]   threadCreate for Tpool4_-1, affinity ffffffff, priority 97
create a thread for core -1
1713863159.365311 [UTIL]   Creating thread Tpool5_-1 with affinity -1 and priority 97
1713863159.509519 [UTIL]   threadCreate for Tpool5_-1, affinity ffffffff, priority 97
create a thread for core -1
1713863159.515356 [UTIL]   Creating thread Tpool6_-1 with affinity -1 and priority 97
1713863159.660265 [UTIL]   threadCreate for Tpool6_-1, affinity ffffffff, priority 97
create a thread for core -1
1713863159.666142 [UTIL]   Creating thread Tpool7_-1 with affinity -1 and priority 97
1713863159.810897 [UTIL]   threadCreate for Tpool7_-1, affinity ffffffff, priority 97
1713863159.816736 [UTIL]   Creating thread L1_rx_thread with affinity -1 and priority 97
1713863159.961970 [UTIL]   threadCreate for L1_rx_thread, affinity ffffffff, priority 97
1713863159.992016 [UTIL]   Creating thread L1_tx_thread with affinity -1 and priority 97
1713863160.137608 [UTIL]   threadCreate for L1_tx_thread, affinity ffffffff, priority 97
1713863160.202934 [UTIL]   Creating thread L1_stats with affinity -1 and priority 1
1713863160.374919 [UTIL]   threadCreate for L1_stats, affinity ffffffff, priority 1
waiting for sync (L1_stats_thread,-1/0x560517d7d0b4,0x5605196b3e80,0x5605196b30c0)
[PNF] Sending PNF_START_RESP
Sending NFAPI_START_RESPONSE config:0x56051be611b0 phy_id:1
NFAPI: got sync (main?)
wait RUs
198979188 [E] 1348306688: pnf_send_message: sctp_sendmsg failed errno: 104
1713863160.380943 [PHY]   Waiting for RUs to be configured ... RC.ru_mask:00
[PNF] Sending first P7 slot indication
1713863160.380977 [PHY]   RUs configured
[PNF] Sent first P7 slot ind
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
1713863160.383749 [HW]   running command "/sbin/sysctl -n -e -q -w net.core.rmem_default=134217728" to increase RFsim performance

```