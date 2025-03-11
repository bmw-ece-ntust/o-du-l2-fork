# PUCCH Bug Report

Start Date: 2025/02/20
Summary: A bug report for the PUCCH issue detailing the segmentation fault during the random access procedure due to a missing mandatory configuration field in the RRCSetup message.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2025/02/27
SUM: 🗓️ Days Spent to Complete: 7

<aside>
✅

Issue raised on OAI GitLab: oai/openairinterface5g#909 https://gitlab.eurecom.fr/oai/openairinterface5g/-/issues/909

</aside>

<aside>
📃

Reference task from [**Notes on Robert’s Response Regarding RRCSetupRequest & CellGroupConfig**](Notes%20on%20Robert%E2%80%99s%20Response%20Regarding%20RRCSetupReque%201a01009831438030aae6ede75db763a1.md) 

</aside>

### **Next Steps for PUCCH Issue**

1. **Open an Issue on the Bug Tracker**
    - Go to: [OAI Bug Tracker](https://gitlab.eurecom.fr/oai/openairinterface5g/-/issues)
    - Follow the bug reporting guidelines: [Bug Reporting Instructions](https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/code-style-contrib.md#reporting-bugs)
2. **Prepare Issue Details**
    - **Title:** Clearly describe the PUCCH problem.
    - **Description:**
        - Briefly explain the issue.
        - Steps to reproduce the problem.
        - Expected vs. actual behavior.
        - Relevant logs, screenshots, or test results.
        - Environment details (branch, commit ID, hardware, OS, compiler version).
3. **Submit the Issue**
    - Double-check the report for completeness and clarity.
    - Submit the issue on GitLab.

<aside>
💡

Issues have already been fixed in the latest develop branch. After updating the UE to tag:`2025.w07`, I confirmed the problem no longer exists.

</aside>

```bash
**Description:**  
In my testing environment (OAI CU + OSC DU High + nFAPI + OAI L1 + OAI UE), the UE experiences a segmentation fault during the random access procedure after receiving the RRCSetup message. Investigation indicates that the CellGroupConfig provided in the RRCSetup message is missing the mandatory **schedulingRequestResourceToAddModList** field (which, per TS 38.331, must include at least one SchedulingRequestResourceConfig element).
While the OSC DU is responsible for providing a complete configuration, the OAI UE should be resilient enough to handle such anomalies without crashing.

**Expected Behavior:**  
- **Robust Error Handling:** Even if the OSC DU fails to populate the **schedulingRequestResourceToAddModList**, the UE should detect the anomaly and handle it gracefully—either by logging an error and aborting the affected procedure or by applying a default/fallback configuration.
- **Complete Configuration:** Ideally, the CellGroupConfig should include all mandatory radio configuration details, including a non-empty **schedulingRequestResourceToAddModList**.

**Actual Behavior:**  
- The OSC DU sends a CellGroupConfig without populating the **schedulingRequestResourceToAddModList**.
- The UE processes the RRCSetup message, and during the call to `check_pucchres_for_pending_SR()` (via `nr_update_sr()` in `nr_ue_scheduler.c`), the absence of the field leads to a null pointer dereference and subsequent segmentation fault.

**Steps to Reproduce:**  
1. **Set up the following components:**
   - **OAI CU** (branch: develop:2024.w30)  
     Command:  
     `sudo ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-NR-5GC/CONF/cu_gnb.conf --sacd`
   - **OSC DU High**
   - **nFAPI**
   - **OAI L1** (branch: nfapi-fixes-rebased-demo)  
     Command:  
     `sudo ./nr-softmodem -O $PATH_TO_SCRIPT/CONFIG/oaiL1.nfapi.usrpb210.conf --nfapi PNF --rfsim --rfsimulator.serveraddr server --sa`
   - **OAI UE** (branch: nfapi-fixes-rebased-demo)  
     Command:  
     `sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --sa --uicc0.imsi 001010000000001 --rfsim`
2. **Execute the random access procedure:**
   - The UE sends an RRCSetupRequest, prompting the DU to forward a DU-to-CU RRC Container that includes the CellGroupConfig.
   - The CU embeds this CellGroupConfig into the RRCSetup message (as defined by TS 38.331, where `masterCellGroup` is an OCTET STRING containing the CellGroupConfig) and sends it to the UE.
3. **UE Processing:**
   - Upon receiving the RRCSetup message, the UE attempts to process the CellGroupConfig.
   - Due to the missing **schedulingRequestResourceToAddModList**, the UE crashes during the scheduling request resource check.

**Log Extract:**  
```plaintext
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

**Additional Context:**  
- TS 38.331 specifies that the **schedulingRequestResourceToAddModList** field is a mandatory SEQUENCE (with size constraints of 1..maxNrofSR-Resources) and must include at least one element.
- Although OSC DU’s incomplete configuration is problematic, the UE should not crash but rather handle such configuration anomalies more gracefully.
- The DU’s function `get_initial_cellGroupConfig()` in `nr_rrc_config.c` might offer guidance on how the configuration should be initialized.

**Proposed Fix / Next Steps:**  
- **For OAI UE:**  
  - Improve error checking in the UE’s RRCSetup processing. The UE should verify the presence of mandatory fields like **schedulingRequestResourceToAddModList** and either apply a safe default or gracefully abort the process if the configuration is incomplete.
```