# Notes on Robert’s Response Regarding RRCSetupRequest & CellGroupConfig

Start Date: 2025/02/20
Summary: Analyzing Robert's response regarding the RRCSetupRequest and CellGroupConfig to address issues related to user equipment configuration and potential missing data in the implementation.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: mail
Finish Date: 2025/02/21
SUM: 🗓️ Days Spent to Complete: 1

**Notes on Robert’s Response Regarding RRCSetupRequest & CellGroupConfig**

1. **CellGroupConfig & SIB1**
    - UE already has SIB1; it is not inserted into CellGroupConfig.
    - Some fields in CellGroupConfig may be configured from common configuration (e.g., initial BWP).
    - To check what OAI DU puts into CellGroupConfig initially, refer to `get_initial_cellGroupConfig()` in `nr_rrc_config.c`.
2. **CellGroupConfig Transmission Process**
    - CU inserts CellGroupConfig into **RRC Setup** (as per 3GPP 38.331: `masterCellGroup OCTET STRING (CONTAINING CellGroupConfig)`).
    - The reason CellGroupConfig is sent from DU to CU before being forwarded to UE:
        - CU is responsible for encoding RRC messages, which require CellGroupConfig.
        - DU, not CU, has knowledge of radio configuration, so it provides CellGroupConfig.
        - 3GPP spec mandates DU to include CellGroupConfig in **DU-to-CU RRC Container**, and CU must forward it transparently to UE.
        - This process is also used to activate MIMO and other features.
3. **OAI UE Issue – Missing `schedulingRequestResourceToAddModList` in CellGroupConfig**
    - 3GPP 38.331 requires `schedulingRequestResourceToAddModList` to have at least one element.
    - OAI UE crashes due to missing this structure in received CellGroupConfig.
    - Likely issue: **OSC DU did not populate `schedulingRequestResourceToAddModList`**.
    - UE should handle this more gracefully. Robert will forward the issue to a UE developer.
4. **Reference to OAI 4G vs. 5G Implementation**
    - In OAI 4G, RRC was aware of radio configuration and handled CellGroupConfig.
    - Initially, OAI 5G CU handled CellGroupConfig, but it was later moved to DU (commit `7e2487c29412`).

### 

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

---

```bash
Hi Robert,
Yes, thank you~ I plan to continue raising the issue and persuading OSC to adopt the method.
Also, I would like to ask you a question for clarification.
I want to better understand the process related to the RRCSetupRequest, particularly the CellGroupConfig.
After the UE receives MSG4, it sends an RRCSetupRequest. My understanding is that the UE carries identity-providing data, such as the UE-ID and some additional minor details. Then, when the message is forwarded to the DU, the DU sends an Initial UL RRC Message Transfer, which includes CGI (PLMN, cell ID), C-RNTI, RRCSetupRequest, and the DU-to-CU-container via F1 to the CU.
The DU-to-CU-container is where the DU determines whether the UE is allowed to connect. If permitted, the DU includes the CellGroupConfig in the DU-to-CU-container. This CellGroupConfig also contains SIB1, which is provided to CU-CP. After the CU receives the Initial UL RRC Message Transfer, it inserts the CellGroupConfig into the DL RRC Message Transfer and sends it back to the DU, which then forwards it to the UE. This allows the UE to learn about the gNB configuration.
This is my understanding based on the spec, source code, and online resources. However, I am puzzled as to why the CellGroupConfig needs to be sent up to the CU and then down to the DU before being forwarded to the UE. While I don’t mind the complexity of the process, I am concerned that I may have misunderstood something, which could lead to more significant issues.
Additionally, considering my current environment (OAI CU + OSC DU High + nFAPI + OAI L1 + OAI UE), I suspect the issue on the OAI UE is related to a missing structure—specifically, pucch_Config->schedulingRequestResourceToAddModList—in the received CellGroupConfig.

In path: openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c
function: check_pucchres_for_pending_SR()

OAI UE Logs (OAI CU + OSC DU High + OAI Layer1 + OAI UE)
```
[PHY]   RAR-Msg2 decoded
[NR_MAC]   [RAPROC][168.19] RA-Msg3 transmitted
[MAC]   [UE 0]Frame 169 Contention resolution identity: 0x1f223c8231e6 Terminating RA procedure
[MAC]   [UE 0][169.15][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
[NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
[RLC]   Added srb 1 to UE 0
[MAC]   Applying CellGroupConfig from gNodeB
[NR_RRC]   State = NR_RRC_CONNECTED
[NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
[NR_MAC]   BWP ID: 0
[NR_MAC]   SCS: 1
[NR_MAC]   BWP Size: 106
[NR_MAC]   BWP Start: 0
[NR_MAC]   RACH Config Common: 0x719a88001e40
[NR_MAC]   TDA List Common: 0x719a88002030
[NR_MAC]   PUCCH Config Common: 0x719a88002290
[NR_MAC]   Msg3 Delta Preamble: 0
[NR_MAC]   Transform Precoding: 0
[NR_MAC]   MCS Table: 0
[NR_MAC]   DCI Format: 0
[NR_MAC]   Max FB Time: 0
 
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

Therefore, based on my description of the CellGroupConfig, my assumption is that the OSC DU did not populate the <schedulingRequestResourceToAddModList>, which I believe caused the issue.
I would greatly appreciate your opinion on this.

Best regards,
Ming
```

## Response from Robert - English version

```bash
Hi,
On 25-02-20, Ming Hung HSU wrote:
> Hi Robert,
> Yes, thank you~ I plan to continue raising the issue and persuading OSC to adopt the method.
> Also, I would like to ask you a question for clarification.
> I want to better understand the process related to the RRCSetupRequest, particularly the CellGroupConfig.
> After the UE receives MSG4, it sends an RRCSetupRequest. My understanding is that the UE carries identity-providing data, such as the UE-ID and some additional minor details. Then, when the message is forwarded to the DU, the DU sends an Initial UL RRC Message Transfer, which includes CGI (PLMN, cell ID), C-RNTI, RRCSetupRequest, and the DU-to-CU-container via F1 to the CU.
> The DU-to-CU-container is where the DU determines whether the UE is allowed to connect. If permitted, the DU includes the CellGroupConfig in the DU-to-CU-container.

That is correct so far.

>This CellGroupConfig also contains SIB1, which is provided to CU-CP.

Why do you think that? the UE already has SIB1. There are a couple of
fields in the CellGroupConfig that might be configured from common
configuration (e.g., initial BWP etc), but SIB1 is not exactly inserted
into the cellGroupConfig either.

If you want to see what OAI DU puts into the CellGroupConfig in the
beginning, see get_initial_cellGroupConfig() in nr_rrc_config.c.

> After the CU receives the Initial UL RRC Message Transfer, it inserts the CellGroupConfig into the DL RRC Message Transfer and sends it back to the DU, which then forwards it to the UE. This allows the UE to learn about the gNB configuration.

Almost. The CellGroupConfig is inserted into rrcSetup. You can see in
38.331 that RRCSetupIEs contains

    masterCellGroup   OCTET STRING (CONTAINING CellGroupConfig),

(mandatorily!). RRC Setup is the encoded and sent to the UE.

> This is my understanding based on the spec, source code, and online resources. However, I am puzzled as to why the CellGroupConfig needs to be sent up to the CU and then down to the DU before being forwarded to the UE. While I don’t mind the complexity of the process, I am concerned that I may have misunderstood something, which could lead to more significant issues.

For multiple reasons:

- as you can see above, the CellGroupConfig is part of RRC messages
  (e.g., RRC Setup, RRC Reconfiguration, ...). RRC Messages are encoded
  by the CU, so it needs to have the CellGroupConfig to put it into the
  RRC message, and to forward it then to the UE
- you might ask why the CellGroupConfig is not in the CU directly? Well,
  because CellGroupConfig basically has radio configuration, and the CU
  knows nothing about the radio configuration, only the DU. [1]
- the spec says this in some places: for Initial UL RRC
  message:

  > gNB-DU shall include the DU to CU RRC Container IE and the gNB-CU
  > shall configure the UE as specified in TS 38.331 [8].

  [38.331 specifies that the RRC Setup MUST have the CellGroupConfig, as
  an OCTET STRING]

  and in e.g. 8.3.1 UE Context Setup it also says explicitly

  > If the CellGroupConfig IE is included in the DU to CU RRC
  > Information IE contained in the UE CONTEXT SETUP RESPONSE message,
  > the gNB-CU shall perform RRC Reconfiguration or RRC connection
  > resume as described in TS 38.331 [8]. The CellGroupConfig IE shall
  > transparently be signaled to the UE as specified in TS 38.331 [8].

  So you see, the spec says here explicitly that the DU gives up the
  CellGroupConfig, and that the CU forwards this *transparently* [with
  no modifications] to the UE.

  This is also used to activate MIMO etc.

[1] fun fact: in OAI 4G, the CellGroupConfig is created and processed in
RRC, which is pretty much aware of the radio configuration. That's also
why the CellGroupConfig was originally in the OAI 5G CU, and it was a
headache to bring it down to the CU. See commit 7e2487c29412 ("Handle
CellGroupConfig completely at MAC") where I did that

> Additionally, considering my current environment (OAI CU + OSC DU High + nFAPI + OAI L1 + OAI UE), I suspect the issue on the OAI UE is related to a missing structure—specifically, pucch_Config->schedulingRequestResourceToAddModList—in the received CellGroupConfig.

See 38.331

    schedulingRequestResourceToAddModList   SEQUENCE (SIZE (1..maxNrofSR-Resources)) OF SchedulingRequestResourceConfig

there must be *at least one* element.

> In path: openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c
> function: check_pucchres_for_pending_SR()
>
> OAI UE Logs (OAI CU + OSC DU High + OAI Layer1 + OAI UE)
> ```
> [PHY]   RAR-Msg2 decoded
> [NR_MAC]   [RAPROC][168.19] RA-Msg3 transmitted
> [MAC]   [UE 0]Frame 169 Contention resolution identity: 0x1f223c8231e6 Terminating RA procedure
> [MAC]   [UE 0][169.15][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
> [NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
> [RLC]   Added srb 1 to UE 0
> [MAC]   Applying CellGroupConfig from gNodeB
> [NR_RRC]   State = NR_RRC_CONNECTED
> [NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
> [NR_MAC]   BWP ID: 0
> [NR_MAC]   SCS: 1
> [NR_MAC]   BWP Size: 106
> [NR_MAC]   BWP Start: 0
> [NR_MAC]   RACH Config Common: 0x719a88001e40
> [NR_MAC]   TDA List Common: 0x719a88002030
> [NR_MAC]   PUCCH Config Common: 0x719a88002290
> [NR_MAC]   Msg3 Delta Preamble: 0
> [NR_MAC]   Transform Precoding: 0
> [NR_MAC]   MCS Table: 0
> [NR_MAC]   DCI Format: 0
> [NR_MAC]   Max FB Time: 0
>
> Thread 8 "Tpool6_-1" received signal SIGSEGV, Segmentation fault.
> [Switching to Thread 0x7ffff3400640 (LWP 382284)]
> nr_update_sr (mac=0x7fffef000010) at /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:1184
> 1184          if (check_pucchres_for_pending_SR(pucch_Config, lc_info->sr_id)) {
> (gdb) bt
> #0  nr_update_sr (mac=0x7fffef000010) at /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:1184
> #1  nr_ue_ul_scheduler (mac=mac@entry=0x7fffef000010, ul_info=ul_info@entry=0x7ffff33ff440)
>     at /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:1358
> #2  0x0000555555922b25 in nr_ue_ul_indication (ul_info=0x7ffff33ff440)
>     at /home/hpe/openairinterface5g/openair2/NR_UE_PHY_INTERFACE/NR_IF_Module.c:1152
> #3  0x000055555582f20f in processSlotTX (arg=0x7fffe005eb80) at /home/hpe/openairinterface5g/executables/nr-ue.c:586
> #4  0x000055555585feb9 in one_thread (arg=0x5555563a3e50) at /home/hpe/openairinterface5g/common/utils/threadPool/thread-pool.h:102
> #5  0x00007ffff7294ac3 in start_thread (arg=<optimized out>) at ./nptl/pthread_create.c:442
> #6  0x00007ffff7326850 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
> ```
>
> Therefore, based on my description of the CellGroupConfig, my assumption is that the OSC DU did not populate the <schedulingRequestResourceToAddModList>, which I believe caused the issue.

I agree, although the UE could handle this a bit more gracefully. I
forward to a UE developer.

Robert
```

```bash
Regarding the PUCCH problem, can you please open an issue on the bug
tracker?

https://gitlab.eurecom.fr/oai/openairinterface5g/-/issues

instructions

https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/code-style-contrib.md#reporting-bugs

Robert
```

## Response from Robert - Chinese version

以下是 Robert 的回覆翻譯成繁體中文(翻譯保留了原文的技術細節與專業性)：

---

是的，到目前為止你的理解是正確的。

> 這個 CellGroupConfig 也包含 SIB1，並提供給 CU-CP。
> 

為什麼你會這麼認為？UE 已經擁有 SIB1 了。在 CellGroupConfig 中確實有一些欄位可能是從公共配置 (common configuration) 設定的，例如初始 BWP 等，但 SIB1 並不會直接被插入到 CellGroupConfig 中。

如果你想查看 OAI DU 在最初的 CellGroupConfig 中放了什麼，請參考 `nr_rrc_config.c` 檔案中的 `get_initial_cellGroupConfig()` 函式。

> 當 CU 收到 Initial UL RRC Message Transfer 後，它會將 CellGroupConfig 插入 DL RRC Message Transfer，然後發送回 DU，最後 DU 會再轉發給 UE，使其了解 gNB 配置。
> 

幾乎正確。CellGroupConfig 其實是插入到 RRCSetup 中的。在 3GPP 38.331 規範中，你可以看到 RRCSetupIEs 包含以下內容：

```
masterCellGroup   OCTET STRING (CONTAINING CellGroupConfig),

```

這是 **強制性** 的！RRC Setup 會被編碼並發送給 UE。

> 這是我根據規範、原始碼以及線上資料所理解的內容。但我對於為什麼 CellGroupConfig 需要先上傳到 CU，再從 CU 傳回 DU，最後才轉發給 UE 感到困惑。雖然我不介意這個過程的複雜性，但我擔心自己可能有嚴重的理解錯誤。
> 

這麼做有多重原因：

- 如你所見，CellGroupConfig 是 RRC 訊息的一部分 (例如 RRC Setup, RRC Reconfiguration 等)。這些 RRC 訊息是由 CU 編碼的，因此 CU 需要先獲取 CellGroupConfig，才能將其放入 RRC 訊息並轉發給 UE。
- 你可能會問，為什麼 CellGroupConfig 不直接放在 CU 裡？原因是 CellGroupConfig 主要是與無線電配置 (radio configuration) 相關，而 CU 並不瞭解無線電配置，只有 DU 知道。[1]
- 3GPP 規範在多個地方都有提到這點，例如在 Initial UL RRC Message 這部分：
    
    > gNB-DU 必須包含 DU to CU RRC Container IE，而 gNB-CU 應該按照 TS 38.331 [8] 的規範來配置 UE。
    > 
    
    [38.331 明確規定 RRC Setup **必須** 包含 CellGroupConfig，作為一個 OCTET STRING]
    
    另外，在 8.3.1 UE Context Setup 這部分，規範也明確說明：
    
    > 如果 CellGroupConfig IE 被包含在 UE CONTEXT SETUP RESPONSE 訊息中的 DU to CU RRC Information IE，則 gNB-CU 必須執行 RRC Reconfiguration 或 RRC connection resume，如 TS 38.331 [8] 所述。CellGroupConfig IE 應該被透明地傳遞給 UE，如 TS 38.331 [8] 所述。
    > 
    
    因此，規範清楚指出 DU 需要提供 CellGroupConfig，而 CU 必須 **透明地** (不做任何修改) 將其轉發給 UE。
    
    此外，這個過程也用於啟動 MIMO 等功能。
    

[1] 有趣的是，在 OAI 4G 中，CellGroupConfig 是在 RRC 層創建和處理的，而 RRC 層對無線電配置非常了解。因此，最初 OAI 5G 將 CellGroupConfig 放在 CU 中，後來才花了很大力氣把它移到 DU 來處理。你可以參考 commit `7e2487c29412 ("Handle CellGroupConfig completely at MAC")`，當時我就是這樣調整的。

> 另外，根據我目前的環境 (OAI CU + OSC DU High + nFAPI + OAI L1 + OAI UE)，我懷疑 OAI UE 的問題與 CellGroupConfig 中缺少 pucch_Config->schedulingRequestResourceToAddModList 結構有關。
> 

根據 38.331 規範：

```
schedulingRequestResourceToAddModList   SEQUENCE (SIZE (1..maxNrofSR-Resources)) OF SchedulingRequestResourceConfig

```

這裡的 **SEQUENCE (SIZE (1..maxNrofSR-Resources))** 表示該欄位至少應該有 **一個** 元素。

> 在路徑 openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c
> 
> 
> 函式 `check_pucchres_for_pending_SR()`
> 
> OAI UE 日誌 (OAI CU + OSC DU High + OAI Layer1 + OAI UE)
> 
> ```
> [PHY]   RAR-Msg2 decoded
> [NR_MAC]   [RAPROC][168.19] RA-Msg3 transmitted
> [MAC]   [UE 0]Frame 169 Contention resolution identity: 0x1f223c8231e6 Terminating RA procedure
> [MAC]   [UE 0][169.15][RAPROC] RA procedure succeeded. CB-RA: Contention Resolution is successful.
> [NR_RRC]   [UE0][RAPROC] Logical Channel DL-CCCH (SRB0), Received NR_RRCSetup
> [RLC]   Added srb 1 to UE 0
> [MAC]   Applying CellGroupConfig from gNodeB
> [NR_RRC]   State = NR_RRC_CONNECTED
> [NR_RRC]   [UE 0][RAPROC] Logical Channel UL-DCCH (SRB1), Generating RRCSetupComplete (bytes33)
> [NR_MAC]   BWP ID: 0
> [NR_MAC]   SCS: 1
> [NR_MAC]   BWP Size: 106
> [NR_MAC]   BWP Start: 0
> [NR_MAC]   RACH Config Common: 0x719a88001e40
> [NR_MAC]   TDA List Common: 0x719a88002030
> [NR_MAC]   PUCCH Config Common: 0x719a88002290
> [NR_MAC]   Msg3 Delta Preamble: 0
> [NR_MAC]   Transform Precoding: 0
> [NR_MAC]   MCS Table: 0
> [NR_MAC]   DCI Format: 0
> [NR_MAC]   Max FB Time: 0
> 
> Thread 8 "Tpool6_-1" received signal SIGSEGV, Segmentation fault.
> [Switching to Thread 0x7ffff3400640 (LWP 382284)]
> nr_update_sr (mac=0x7fffef000010) at /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:1184
> 1184          if (check_pucchres_for_pending_SR(pucch_Config, lc_info->sr_id)) {
> 
> ```
> 

> 因此，根據我對 CellGroupConfig 的描述，我的假設是 OSC DU 並沒有填入 <schedulingRequestResourceToAddModList>，這可能導致了這個問題。
> 

我同意這個推測，不過 UE 這邊應該可以更穩健地處理這個情況。我會將這個問題轉給 UE 開發人員進一步分析。

Robert

---