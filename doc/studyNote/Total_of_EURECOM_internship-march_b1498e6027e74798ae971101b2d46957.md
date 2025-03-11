# Total of EURECOM internship-march

3/29

---

- [Correcting the logic for timing_window judgment.](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/c9e29064f8192497e8ac98528273516293f77f5c)

### **Daily Goals:**

1. Fix the issue with `request_in_window` when encountering time wrap-around.
2. Ensure proper startup of the core.
3. Test `usleep(1000);` in `simulator.c` and verify gNB's iperf functionality.
4. Conduct testing using the `oaitun_ue1` interface and configure iperf3 to avoid NR tunnel bypass issues.

### **Summary of Completed Progress:**

1. Fixed the issue with `request_in_window` by implementing the solution outlined [here](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/c9e29064f8192497e8ac98528273516293f77f5c).
2. Resolved the core startup issue by modifying the MCC MNC.
3. Tested `usleep(1000);` in `simulator.c` and conducted iperf functionality testing on gNB.
4. Ensured testing using the `oaitun_ue1` interface and configured iperf3 to avoid NR tunnel bypass issues.

Notes Hyperlinks:

- Solution for fixing `request_in_window` issue: [GitLab Commit](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/c9e29064f8192497e8ac98528273516293f77f5c)

### **Current Issues Encountered:**

1. AMF not associated with gNB during core startup.
2. Need to conduct iperf functionality testing on gNB.
3. Incorrect understanding regarding sending 35Gbps traffic over NR, requiring clarification.
4. Further investigation and resolution of potential additional issues required.

Description Hyperlinks:

- No hyperlinks available for issue descriptions at the moment.

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月28日 下午6:53](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-66054c330f392f95fa4d7c0f)

(已編輯)

3/28

---

- Print in [t3] socket `receive`data size()
- Develop deep copy function → [test1 for cp_nr_tx_data_req() (4e0a7207) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/4e0a72075a4619baa2b735557167bdebacac2d62)
    
    ![https://gitlab.eurecom.fr/assets/favicon-72a2cad5025aa931d6ea56c3201d1f18e68a8cd39788c7c80d5b2b82aa5143ef.png](https://gitlab.eurecom.fr/assets/favicon-72a2cad5025aa931d6ea56c3201d1f18e68a8cd39788c7c80d5b2b82aa5143ef.png)
    
- Modify more part for change `nfapi_nr_tx_data_request_t` data struct with call by value (not call by address).
- [outcome] effective, as now the execution time through this cp_nr_tx_data_req function has been reduced to **2 microseconds**.

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月27日 下午6:49](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-6603f9a2a47f4e05c82eee88)

(已編輯)

3/27

---

**Summary: →** [Note](https://www.notion.so/PNF-allocate-same-memory-279a85aac41d4888b1e2c04a8644951c?pvs=21)

1. [**Memory Allocation Performance:**](https://www.notion.so/PNF-allocate-same-memory-279a85aac41d4888b1e2c04a8644951c?pvs=21) I confirmed that using `malloc` for memory allocation takes approximately `0.002209s` to `0.001493s`, which could contribute to the overall execution time. I am exploring strategies to optimize memory allocation, including using `malloc_trim(0)` or releasing memory only after use.
2. **Potential Changes:** I am considering reverting the "slot_ahead" parameter back to its original value of "2" to further investigate its impact on performance.
3. **Improving Memory Allocation:** While `alloca` speeds up the process by allocating memory from the stack, it may still face challenges with address allocation. I plan to explore allocating arrays directly on the stack, such as `uint8_t buf[1024]`, and assess its impact.
4. **Address Sanitizer Usage:** I plan to run the code with the address sanitizer (`-sanitize` flag) to identify any memory-related issues and ensure code robustness.
5. **Face-to-Face Meeting:** I have requested a face-to-face meeting with Robert to discuss the progress and potential next steps. Alternatively, I am prepared to continue with their current progress and report back with updates.

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月26日 下午4:48](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-66028be0b5534d27e99709ef)

(已編輯)

3/26

---

- DL_TTI.request and TX_Data.request will be sent in the same slot from VNF to PNF. → [Note](https://www.notion.so/TX_Data-request-65fb696c71c04f9d94d3846ee73908de?pvs=21)
- **Summary:**I have made progress on addressing the issue related to memory allocation in the `pnf_handle_tx_data_request` function. Here are the key updates:
    1. **Memory Allocation Issue:** I observed that `malloc` always assigns the same address to `req`, causing overwriting of values in `pnf_p7->slot_buffer[buffer_index].tx_data_req` during consecutive slots.
    2. **Processing Speed Improvement:** I accelerated the processing speed by using `alloca` instead of `memset`, ensuring that `req` is filled before triggering `nr_schedule_tx_req`.
    3. **Reduced Occurrence of Error:** After these improvements, the occurrence of the "harq->pdu is null" error reduced, with ping times dropping to 90~100ms.
    4. **Root Cause Analysis:** The issue specifically arises when two consecutive slots receive `TX.data.request`, leading to `harq->pdu` being null due to the SFN/Slot offset failure in triggering `nr_schedule_tx_req`.
    5. **Next Steps:** I plan to create a new branch on top of `nfapi-fixes` and push these changes for further testing and integration.This update provides a clearer understanding of the issue and the steps taken to mitigate it, with a plan in place for further implementation and testing.

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月25日 下午4:55](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-66013c07fb873f58fa7e4160)

(已編輯)

3/25

---

- `size16: 4866456`
- `size1: 304176`
- Since Robert comment, remove `buffer_index_tx` function

![https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/66013cf51674c02b75812fdf/download/image.png](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/66013cf51674c02b75812fdf/download/image.png)

**Today's Objectives:**

1. Investigate the issue related to memory reuse in the `pnf_handle_tx_data_request` function.
2. Understand why the address of `req` remains constant (`0x7f762001d0d0`) despite multiple calls to `malloc`.
3. Analyze how `tx_slot_buffer->tx_data_req->Slot` reuses the same memory and causes errors.
4. Determine why removing `(void)memset(pUnpackedBuf, 0, unpackedBufLen)` results in the UE socket being lost.
5. Review suggestions such as using `alloca`, replacing `memset` with `alloca`, and adding print statements to trace the issue.
6. Resolve the issue causing the "harq->pdu is null" error during the decoding of requests.

[**Today's Progress:**](https://www.notion.so/PNF-allocate-same-memory-279a85aac41d4888b1e2c04a8644951c?pvs=21) **→** [**All in one Note**](https://www.notion.so/PNF-allocate-same-memory-279a85aac41d4888b1e2c04a8644951c?pvs=21)

1. Investigated the issue of memory reuse in `pnf_handle_tx_data_request`.
2. Observed that the address of `req` remains constant despite multiple calls to `malloc`, leading to potential memory overwrite issues.
3. Analyzed how `tx_slot_buffer->tx_data_req->Slot` reuses memory, causing errors in continuous slots.
4. Determined that removing `(void)memset(pUnpackedBuf, 0, unpackedBufLen)` results in the UE socket being lost, indicating a critical dependency.
5. Reviewed suggestions such as using `alloca`, replacing `memset` with `alloca`, and adding print statements to trace the issue.
6. Identified the problematic behavior in `buffer_index_tx`, which could be related to memory management issues.

**Current Issues:**

Continuing investigation into the root cause of memory reuse and finding a robust solution to prevent errors during decoding, specifically addressing the "harq->pdu is null" issue.

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月22日 下午6:20](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65fd5b7ebfe934f0a460e57f)

(已編輯)

3/22

---

- **Today's Objectives:**
    1. Add print statements to display "unpack type" and measure the execution time for "check_nr_unpack_length".
    2. Print and verify the value of "idx" for "dlsch[idx]".
    3. Print and verify the type of "dl_pdu" in NFAPI.
- **Today's Progress:**
    1. Added print statements to display "unpack type" and measured the execution time for "check_nr_unpack_length". [Code Commit](https://github.com/dong881/nfapi-split-script/blob/main/LOG/PNF-nfapi-fixes.log)
    2. Printed and verified the value of "idx" for "dlsch[idx]". [Verification Notes](https://www.notion.so/measure-time-04f7c5c61c04409280a8cd1064a94e63?pvs=21)
    3. Printed and verified the type of "dl_pdu" in NFAPI.
- **Current Issues:**
    1. According to the LOG, it was found that it was normal when filling in the data, but abnormal when taking it out.

PNF-nfapi-fixes.log6.23 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月21日 下午4:47](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65fbf41348e14eee82bd64d7)

(已編輯)

3/21

---

**Today's Objectives:**

1. Map the functions related to "dltti" and "tx_data" for both VNF and PNF.
2. Document the chain of functions for "tx_data" in the PNF and organize it in Notion.
3. Print logs from timestamps "t1" to "t2".
4. Identify where "harq->pdu" is filled and ensure it doesn't result in data loss.
5. Correct the typo in the code.
6. Remove the unnecessary print statement related to "schedule_nr_mib".

**Today's Progress:**

1. Successfully mapped functions for "dltti" and "tx_data" in both VNF and PNF. [See Mapping Notes](https://www.notion.so/TX_Data-request-65fb696c71c04f9d94d3846ee73908de?pvs=21)
2. List the chain of functions for "tx_data" in the PNF and documented it in Notion. [Chain of Functions](https://www.notion.so/PNF-chain-of-function-for-TX_Data-e8160b6d9c01443aa34bf3bc44b8b1c1?pvs=21)
3. Printed logs from timestamps "t1" to "t2". [Log Outputs](https://github.com/dong881/nfapi-split-script/blob/main/LOG/VNF-nfapi-fixes.log)
4. Identified the location where "harq->pdu" is filled.

**Current Issues:**

1. Need to ensure that filling "harq->pdu" doesn't result in data loss.

VNF-nfapi-fixes.log4.75 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月20日 下午4:45](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65faa234f31f97023f46bfa1)

(已編輯)

3/20

---

- [add <common/utils/LOG/log.h> for every user easy to use script](https://github.com/dong881/openairinterface5g-NTUST/commit/620abc0dc92864b1f97f3811b4065412b6c7a25e)
- [replace pnf_p7 function to calloc(1,len)](https://github.com/dong881/openairinterface5g-NTUST/commit/495bc1a6bf007475a20cf7b174cb357be1932c80)
- [only three times error by change to alloca()](https://github.com/dong881/nfapi-split-script/commit/eda26710c6d60d560e69a27ba3f27f86a6b37e33) - (origin about 1000 times)
- Reduce Ping UE time → [https://youtu.be/nIUp1FEHGtA](https://youtu.be/nIUp1FEHGtA) by :
    - [replace to alloca() reduce execute time](https://github.com/dong881/openairinterface5g-NTUST/commit/6147346b7e2a4696c0d249ccbf64f4e1f44f97ca)
    - [remove deallocate_nfapi_tx_data_request() beacuse LOG show double free or corruption (out)](https://github.com/dong881/openairinterface5g-NTUST/commit/0caa0e1ef1db4c5016a74bd7d6bbb1bb18275425)
    - Same as last mechine (EURECOM NB) video → [OAI nFAPI split VNF/PNF (EURECOM NB)](https://youtu.be/vmfVCgAOwdQ)
        
        ![https://www.youtube.com/s/desktop/ef8ce500/img/favicon_32x32.png](https://www.youtube.com/s/desktop/ef8ce500/img/favicon_32x32.png)
        

![https://www.youtube.com/s/desktop/ef8ce500/img/favicon_32x32.png](https://www.youtube.com/s/desktop/ef8ce500/img/favicon_32x32.png)

[OAI split VNF-PNF (fix allocate_nfapi_tx_data_reques) reduce ping UE time](https://youtu.be/nIUp1FEHGtA)

![https://www.youtube.com/s/desktop/ef8ce500/img/favicon_32x32.png](https://www.youtube.com/s/desktop/ef8ce500/img/favicon_32x32.png)

[OAI nFAPI split VNF/PNF (EURECOM NB)](https://youtu.be/vmfVCgAOwdQ)

add <common/utils/LOG/log.h> for every user easy to use script由 dong881 提交 620abc0

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubreplace pnf_p7 function to calloc(1,len)由 dong881 提交 495bc1a

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubno bug by change to alloca()由 dong881 提交 eda2671

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubreplace to alloca() reduce execute time由 dong881 提交 6147346

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubremove deallocate_nfapi_tx_data_request() beacuse LOG show double free or corruption (out)由 dong881 提交 0caa0e1

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月19日 下午4:53](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65f952924b658b3cd323a0a0)

(已編輯)

3/19

---

- Learn how to use OAI measure time tool: `start_meas`、 `stop_meas`
- add the time point to measure time at t1,t2,t3,t4
- Drow the chain of function from Scheduler to VNF to PNF to Layer. → [https://nfapi.notion.site/chain-of-function-197740ecbb094ba191bdbc66ca2b05a0?pvs=4](https://www.notion.so/VNF-chain-of-function-for-TX_Data-197740ecbb094ba191bdbc66ca2b05a0?pvs=21)
- [check nfapi_nr_tx_data_request_t size: 4866456](https://github.com/dong881/openairinterface5g-NTUST/commit/68aee3002ae5ff43e810a70a7f679e028cb7fad5)
- [add print log to Measure execution time (t1, t2, t3, t4) from scheduler to VNF socket, to PNF socket, and to PNF transmission to Layer1.](https://github.com/dong881/openairinterface5g-NTUST/commit/ce511d113fd6a1abd20330e3c5cfa8afd990cb0a)
    - [t3,t4](https://github.com/dong881/openairinterface5g-NTUST/commit/ce511d113fd6a1abd20330e3c5cfa8afd990cb0a#diff-36fd5b20f6b651be51ffcd490b1f04e0b99985052c3c5fdea2788751028fb48a)
    - [t2](https://github.com/dong881/openairinterface5g-NTUST/commit/ce511d113fd6a1abd20330e3c5cfa8afd990cb0a#diff-e75a0b1fcd4bb83bc6e8e5ca9bb37ed9fb09b421a837265689536f67d12e7e85)
    - [t1](https://github.com/dong881/openairinterface5g-NTUST/commit/ce511d113fd6a1abd20330e3c5cfa8afd990cb0a#diff-5540404ebe8e7a103604ccc03dfe020fd1237a64e91f580ee9c74c31cf698ef0)

check nfapi_nr_tx_data_request_t size: 4866456由 dong881 提交 68aee30

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubadd print log to Measure execution time (t1, t2, t3, t4) from scheduler to VNF socket, to PNF socket, and to PNF transmission to Layer1.由 dong881 提交 ce511d1

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月18日 下午4:42](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65f7fe508a84e49fd7fa5338)

(已編輯)

3/18

---

- Meeting with Robert at 14:00. → [Ask Robert's question | Notion](https://www.notion.so/Ask-Robert-s-question-88d292be7af14aa4b6375931e881d7a0?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- [New task after meeting](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65f8507c24c0b966fd2d5a02/previews/65f8507d24c0b966fd2d5b36/download/20240318_153154.jpg)
    - Why does usleep() make it run better?
    - How big is tx_data.request c struct?
    - trace / write the functions that are called?
    - write chain of functions!
    - measure time in VNF PNF (t1,t2,t3,t4).
- Find the solution way about currently `nfapi-fixes` branch problem → [Report to Robert | Notion](https://www.notion.so/Report-to-Robert-e597963b6cce4897a15052e6dfc2b055?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Fix `nfapi-fixes` branch problem: `TX_Data.request()` send later[https://github.com/dong881/openairinterface5g-NTUST/commit/a2af0b42fb7e609539fcb35906fbecb7d8b9f6ca](https://github.com/dong881/openairinterface5g-NTUST/commit/a2af0b42fb7e609539fcb35906fbecb7d8b9f6ca)[https://github.com/dong881/openairinterface5g-NTUST/commit/e3145660ebc639f570660643a6922719fe75f618](https://github.com/dong881/openairinterface5g-NTUST/commit/e3145660ebc639f570660643a6922719fe75f618)
- Log list
    - [PNF](https://github.com/dong881/nfapi-split-script/blob/274535c3c3f81c4e02147bf1678a0fcb4d5d6e4b/LOG/PNF-nfapi-fixes.log)
    - [VNF](https://github.com/dong881/nfapi-split-script/blob/274535c3c3f81c4e02147bf1678a0fcb4d5d6e4b/LOG/VNF-nfapi-fixes.log)
    - [UE](https://github.com/dong881/nfapi-split-script/blob/274535c3c3f81c4e02147bf1678a0fcb4d5d6e4b/LOG/UE-nfapi-fixes.log)
- [Drow the flow about UL-SCH after chat with Robert](https://viewer.diagrams.net/?border=0&tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=2eD-Zuup9r3zOLd5AIMz&title=nFAPI.drawio#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts%26export%3Ddownload)

add continue when PNF can't recieve TX_Data.request由 dong881 提交 a2af0b4

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub[TEST] Try VNF send TX_Data.request later由 dong881 提交 e314566

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubPNF-nfapi-fixes.log6.23 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubVNF-nfapi-fixes.log4.75 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubUE-nfapi-fixes.log13.81 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月15日 下午5:00](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65f40e2631629835ae687291)

(已編輯)

3/15

---

- [Draw timing diagram](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65f40e0ddc6b67ce87d2a785/download/image.png)
- Study what is DCI (Downlink Control Information), and mapping OAI source code data struct. → [DCI (notion.site)](https://www.notion.so/DCI-8f01462df5cb43d494e9917a89821f1e?pvs=21).
- [use LOG_I print](https://github.com/dong881/openairinterface5g-NTUST/commit/ef42e73761b964d166535591d930bc38a46b9753)
- [check problem with BG value is: 2](https://github.com/dong881/openairinterface5g-NTUST/commit/03284ff50af06a8a050575d9783c1218156c8c0c)
- [check num_tx_ant.value is: 1](https://github.com/dong881/openairinterface5g-NTUST/commit/9235821c5785d9009fdc1fd004cbc63db8ea247e)
- [edit print method](https://github.com/dong881/openairinterface5g-NTUST/commit/fdf19088d912253715f0b21f03ca248f949d3fd5)
- [Try to mapping VNF and PNF send TX_Data.request](https://github.com/dong881/nfapi-split-script/commit/cebac3a6b31d146066067caacf613cf1ee419453)
    - [PNF](https://github.com/dong881/nfapi-split-script/blob/cebac3a6b31d146066067caacf613cf1ee419453/LOG/PNF-nfapi-fixes.log) LOG
    - [VNF](https://github.com/dong881/nfapi-split-script/blob/cebac3a6b31d146066067caacf613cf1ee419453/LOG/VNF-nfapi-fixes.log) LOG
    - [UE](https://github.com/dong881/nfapi-split-script/blob/cebac3a6b31d146066067caacf613cf1ee419453/LOG/UE-nfapi-fixes.log) LOG

use LOG_I print由 dong881 提交 ef42e73

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubcheck problem with BG value is: 2由 dong881 提交 03284ff

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubcheck num_tx_ant.value is: 1由 dong881 提交 9235821

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubedit print method由 dong881 提交 fdf1908

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubTry to mapping VNF and PNF send TX_Data.request由 dong881 提交 cebac3a

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubPNF-nfapi-fixes.log6.23 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubVNF-nfapi-fixes.log4.75 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubUE-nfapi-fixes.log13.81 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月14日 下午5:05](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65f2bdb76abac2f764260800)

(已編輯)

3/14

---

- Mapping TX_Data.request → [TX_Data.request (notion.site)](https://www.notion.so/TX_Data-request-65fb696c71c04f9d94d3846ee73908de?pvs=21)
- Mapping Slot.indication → [Slot.indication (notion.site)](https://www.notion.so/Slot-indication-41159f8bb4ff44f2bbf7da774651b7a1?pvs=21)
    - Also find how is Tx_data.request, once received in PNF, given to l1 for processing → [TX_Data.request (notion.site)](https://www.notion.so/TX_Data-request-65fb696c71c04f9d94d3846ee73908de?pvs=21)
- [Scheduler next meeting time with Robert.](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65f2fc223334357f6cf4c8fa/previews/65f2fc233334357f6cf4c93e/download/image.png)
- [change PLMN to match OAI CoreNetwork](https://github.com/dong881/openairinterface5g-NTUST/commit/40544493b24ebcbe72d95f7f88ad1fccfe6dcb47)
- [ensure this is no work for nfapi VNF/PNF split](https://github.com/dong881/openairinterface5g-NTUST/commit/296a1d62481ce89ecf1d735c714da5ff5fedf094)
- [check for OSC DU integration group number -> alaways 0](https://github.com/dong881/openairinterface5g-NTUST/commit/2ccf47d3bba407f38555c6e65cb7a52f6a359070)

change PLMN to match OAI CoreNetwork由 dong881 提交 4054449

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubensure this is no work for nfapi VNF/PNF split由 dong881 提交 296a1d6

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubcheck for OSC DU integration group number -> alaways 0由 dong881 提交 2ccf47d

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月13日 下午6:20](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65f17de5b1f3c41e135d6a21)

(已編輯)

3/13

---

- Meeting with Prof.Ray:
    - Discuss system architecture diagram with Robert
    - Discuss OAI L1 with Prof. Hsu's students
    - Clarify Robert's plan and architecture diagram
    - Prepare a rough outline before the next discussion and draw his plan based on our understanding
    - Ask Robert about how to work with nFAPI, and why it breaks when ported to 5G
- [Attempting to fix the laptops distributed by EURECOM to connect to WiFi (instead of Ethernet) and attempting to SSH into EURECOM laptops using Windows.](https://stackoverflow.com/questions/42863913/key-load-public-invalid-format)
    - Try to creat SSH key then I don’t need press password everytimes. → [How to setup SSH key | Notion](https://www.notion.so/How-to-setup-SSH-key-6dc5bb4e412842cca698d924a5715fca?pvs=21)
        
        ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
        
- Study FAPI spec. (Robert task Q1)
    - PCH → [PCH (notion.site)](https://www.notion.so/PCH-cb01ae92c5934592ba2af37f0aaeb759?pvs=21)
    - DL-SCH → [DL_SCH (notion.site)](https://www.notion.so/DL_SCH-f5bceb1e250943c08e8399f992c92e94?pvs=21)
    - UL_SCH → [UL_SCH (notion.site)](https://www.notion.so/UL_SCH-2bd2922ff760404d890c09d0c5594009?pvs=21)
    - SRS → [SRS (notion.site)](https://www.notion.so/SRS-dc0237f153be4798ae0780873fd0847f?pvs=21)
    - SCI→ [CSI (notion.site)](https://www.notion.so/CSI-9930d594258344e1923ca056d9c70982?pvs=21)
    - SR → [https://nfapi.notion.site/SR-24c5ed39adb149f388f2e541dd5b6bea?pvs=74](https://www.notion.so/SR-24c5ed39adb149f388f2e541dd5b6bea?pvs=21)
    - Uplink Reference Signals → [Uplink Reference Signals (notion.site)](https://www.notion.so/Uplink-Reference-Signals-828c28b4210e4ee38869f477578d7a05?pvs=21)

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月12日 下午4:46](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65f0164d6fa25483721abd9d)

(已編輯)

3/12

---

- Analyze P5 and P7 packets using Wireshark → [run OAI VNF/PNF split, connect UE - HackMD](https://hackmd.io/@MingHung/VNF-PNF-split#Outcome-Wireshark)
- Setup Notion note page. → [https://nfapi.notion.site/8674ddb6afa341f391c14eb8783241b4?v=9a9811964814421d85d8789145cf2647&pvs=4](https://www.notion.so/8674ddb6afa341f391c14eb8783241b4?pvs=21)
- Mapping Wireshark outcome with source code. (Robert task Q1) → [Mapping nFAPI source code (notion.site)](https://www.notion.so/8674ddb6afa341f391c14eb8783241b4?pvs=21)

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月11日 下午5:05](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65eec941178550fe35c6d262)

(已編輯)

3/11

---

- run VNF/PNF split, connect UE, observe ping times
    - [run OAI VNF/PNF split, connect UE - HackMD](https://hackmd.io/@MingHung/VNF-PNF-split)
        
        ![https://hackmd.io/favicon.png](https://hackmd.io/favicon.png)
        
    - [OAI VNF/PNF split, connect UE](https://youtu.be/eZJWNlcV6b8)
        
        ![https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png](https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png)
        
- Design an auto execute script. list all executive log->
    - [VNF](https://github.com/dong881/nfapi-split-script/blob/c48ad4608a459148da40476d0a167a1b734902ca/LOG/VNF-nfapi-fixes.log)
    - [PNF](https://github.com/dong881/nfapi-split-script/blob/c48ad4608a459148da40476d0a167a1b734902ca/LOG/PNF-nfapi-fixes.log)
    - [UE](https://github.com/dong881/nfapi-split-script/blob/c48ad4608a459148da40476d0a167a1b734902ca/LOG/UE-nfapi-fixes.log)
    - [PING-value](https://github.com/dong881/nfapi-split-script/blob/c48ad4608a459148da40476d0a167a1b734902ca/LOG/ping-nfapi-fixes.log)

![https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png](https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png)

[OAI VNF/PNF split, connect UE](https://youtu.be/eZJWNlcV6b8)

VNF-nfapi-fixes.log4.75 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubPNF-nfapi-fixes.log6.23 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubUE-nfapi-fixes.log13.81 MB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月8日 晚上9:15](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65eb0f63fdad14f527f9d46a)

(已編輯)

3/8

---

- run VNF/PNF split, connect UE, observe ping times and differences to step 2
    - run VNF-PNF-split and connect UE → [run OAI VNF/PNF split, connect UE](https://youtu.be/zRK5XU76MJQ)
        
        ![https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png](https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png)
        
    - [some issuse] trace ping time
    - Write a note for video step → [run OAI VNF/PNF split, connect UE - HackMD](https://hackmd.io/@MingHung/VNF-PNF-split)
        
        ![https://hackmd.io/favicon.png](https://hackmd.io/favicon.png)
        

![https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png](https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png)

[run OAI VNF/PNF split, connect UE](https://youtu.be/zRK5XU76MJQ)

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月7日 下午5:07](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65e983b89f7c7c3a603a1197)

(已編輯)

3/7

---

- Finish run normal gNB (no PNF/VNF), cnonect UE, observe ping times, throughput with iperf, see behavior. → [ping time about 25ms.](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65e9838f67fe275addfcf1af/download/image.png)
- [Record a video for normal OAI gNB running behavior.](https://youtu.be/NhayA_kw46c)
- [Write the step-by-step note for video.](https://hackmd.io/@MingHung/NR_SA_Tutorial_OAI_nrUE)
- [Study Robert give us quiz question.](https://hackmd.io/@MingHung/Robert-quiz)
- Use `iperf` to test throughput.
    - [OAI gNB throughput.](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65e9d8a1dfd577bf358586de/download/image.png)
    - [OAI UE throughput.](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65e9d9703eec337d38805287/download/image.png)

![https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png](https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png)

[NR_SA_Tutorial_OAI_nrUE.md](https://youtu.be/NhayA_kw46c)

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月4日 晚上11:36](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65e5ea878698086d78e436a9)

(已編輯)

3/6

---

- Discuss progress with Robert → Task already add into TODO list.
- Set up BMW lab VM .
    - install git and other tools on VM.
    - git clone latest OAI nfapi-fixes branch.
    - [Install Core Network](https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/NR_SA_Tutorial_OAI_CN5G.md) - > [outcome](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65e88ca78178f8ff92a7ce97/download/image.png).
- Follow [doc/NR_SA_Tutorial_OAI_nrUE.md · develop · oai / openairinterface5G · GitLab (eurecom.fr)](https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/NR_SA_Tutorial_OAI_nrUE.md) to run normal gNB (no PNF/VNF), cnonect UE.
    
    TODO
    
    ```
    make test # This step is optional
    sudo make install
    sudo ldconfig
    sudo uhd_images_downloader
    ```
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月4日 下午4:09](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65e581aaf44cd33ca7255f9e)

(已編輯)

3/4

---

- Unable to connect with Robert via email;
    - [last communication was last Friday.](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65e5eaf0ed68b20fe4261196/download/image.png)
- Contact IT (Tom) to understand how to set up SSH access with public and private keys. Refer to the following URL for guidance:
    - Useful URL: [My.eurecom.fr - Authentication](https://my.eurecom.fr/)
    - Share my public key with Tom. Once I provide Tom with my public key, I will be able to utilize ssh to save files on their Linux server.
    - During the testing phase of executing the OAI nfapi-fixes branch, I encountered an authentication Insufficient permissions issue, possibly restricted to file storage. Maybe further investigation if is needed.
- Request JOE to provide both Richard and me with a virtual machine (VM) for executing OAI nfapi-fixes, [as my laptop lacks the necessary processing power.](https://trello.com/1/cards/65e1de1ec46b55c1a5727968/attachments/65e5ec1d8bdef401d87b78e0/previews/65e5ec1e8bdef401d87b8047/download/%E7%AD%86%E9%9B%BB%E6%95%88%E8%83%BD%E4%B8%8D%E8%B6%B3.png)
- Also, ask JOE to set up an OpenVPN, enabling me to access BMW's lab network.
- Submit bank account to HR

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月1日 晚上9:55](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-65e1de3ee5216b13898cfc8f)

(已編輯)

3/1

---

- Onboard to EURECOM and sign a confidentiality agreement, and explain transportation subsidies and meal vouchers.
- IT allocates resources to us, leads us to understand the internal resources of the environment (how to borrow conference rooms, etc.), and assists us in changing our own internal passwords.
- Assign lab location, seating, laptops

---

- [Study the Small Cell Forum’s FAPI 6.0 specifications, P5, P7, P9](https://scf.io/en/documents/222_5G_FAPI_PHY_API_Specification.php)
    - [Focus on P9 to study.](https://www.notion.so/SCF-PHY-API-P9-78093aa5545b4efea7e1120b642b867b?pvs=21)
- Search and study `nfapi-fixes` procedure.