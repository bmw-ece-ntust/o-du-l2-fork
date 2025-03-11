# Total of EURECOM internship-april

04/30

---

**Issue Identification and Analysis: → [LINK](https://www.notion.so/Fix-problem-HARQ-sdu_len-PBCH-54bada65a71d44a6816a948bb0744ec6?pvs=21)**

- Identified timing issue with TX_DATA arrival causing assertion failure.
- Discovered timing discrepancy in VNF data transmission to PNF after UE connection.

**Proposed Solutions and Implementation: →** [**LINK**](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/697fa11fd12d8c0645c358de2ff2b3c360fff8be)

- Considered adjusting slot_ahead parameter to address timing discrepancy.
- Implemented code changes to set slot_ahead = 0 for faster VNF to PNF speed.

**Challenges and Uncertainties: → Discuss with Robert**

- Uncertain about the impact of setting slot_ahead = 0 on UE sim's ability to acquire SIB1.
- Lack of familiarity with UE sim part poses debugging challenges.

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月29日 下午4:05](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-662f54dd232c20adf92093a6)

(已編輯)

04/29

---

- Solve the problem by dimitic pack/unpack P5 config.request() by mu → [nr_slot_select(): ignore frame%2 -> nFAPI wrong slot pattern? | Notion](https://www.notion.so/nr_slot_select-ignore-frame-2-nFAPI-wrong-slot-pattern-550b1d0006a84678b11d8df3dd653279?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Create a call flow diagram for Layer 1 thread including RU, tx_func, and rx_func.→ [LINK](https://viewer.diagrams.net/?border=0&tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=URs28cEerZ-29d-8ayi0&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)
- Find a main problem is When [HW] A client connects, sending the current time, which is when the UE sim starts execution, the slot offset between the PNF and VNF, originally differing by two slots, will become zero slots apart. This is the source of the issue.→ [Fix problem (HARQ,sdu_len,PBCH) | Notion](https://www.notion.so/Fix-problem-HARQ-sdu_len-PBCH-54bada65a71d44a6816a948bb0744ec6?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月26日 晚上7:47](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-662b9460150cd50a7ae4e81e)

(已編輯)

4/26

---

- Print log to find VNF send to PNF TDD table → [nr_slot_select(): ignore frame%2 -> nFAPI wrong slot pattern? | Notion](https://www.notion.so/nr_slot_select-ignore-frame-2-nFAPI-wrong-slot-pattern-550b1d0006a84678b11d8df3dd653279?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Study Information about TDD table. → [Information about TDD table | Notion](https://www.notion.so/Information-about-TDD-table-39ebd8f09d8548e49f128eec2dc09233?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月25日 下午3:41](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-662a092fd869b3758ebcf732)

(已編輯)

4/25

---

- Identifying the issue with HARQ, sdu_len, and PBCH in RFsim involves the use of usleep(1000).-> [Fix problem (HARQ,sdu_len,PBCH) | Notion](https://www.notion.so/Fix-problem-HARQ-sdu_len-PBCH-54bada65a71d44a6816a948bb0744ec6?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Update `UL_TTI.request()` deep copy function. → [https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/37ee09f3580a11bdebc30d222d008d4220cd0d86](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/37ee09f3580a11bdebc30d222d008d4220cd0d86)
- The issue primarily arises from a git revert affecting RFsim, leading to tx_func executing faster than PNF, causing missed opportunities for pnf_phy_tx_data_req. → [Fix problem (HARQ,sdu_len,PBCH) | Notion](https://www.notion.so/Fix-problem-HARQ-sdu_len-PBCH-54bada65a71d44a6816a948bb0744ec6?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
    - socket is too slow → [Notion – The all-in-one workspace for your notes, tasks, wikis, and databases.](https://www.notion.so/Fix-problem-HARQ-sdu_len-PBCH-54bada65a71d44a6816a948bb0744ec6?pvs=21)
        
        [https://www.notion.so/images/favicon.ico](https://www.notion.so/images/favicon.ico)
        
    - Got a big problem is `tx_func` too fast, sometimes is 10us per slot → [Notion – The all-in-one workspace for your notes, tasks, wikis, and databases.](https://www.notion.so/Fix-problem-HARQ-sdu_len-PBCH-54bada65a71d44a6816a948bb0744ec6?pvs=21)
        
        [https://www.notion.so/images/favicon.ico](https://www.notion.so/images/favicon.ico)
        

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月24日 下午3:38](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-6628b6fa1a0a58fccc1da8d3)

(已編輯)

4/24

---

- Try to fix Robert’s task about nr_slot_selece → [nr_slot_select(): ignore frame%2 -> nFAPI wrong slot pattern? | Notion](https://www.notion.so/nr_slot_select-ignore-frame-2-nFAPI-wrong-slot-pattern-550b1d0006a84678b11d8df3dd653279?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Attempt to resolve the issue of why modifying UL_DCI and DL_TTI results in an inability to ping.

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月23日 下午4:43](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-662774b66c89703a5cd716e2)

(已編輯)

4/23

---

- Reduce RRT from 100ms to 10ms → [Notion – The all-in-one workspace for your notes, tasks, wikis, and databases.](https://www.notion.so/Reduce-nfapi-split-RRT-f1755299f7f34c98a057b7d9c3d57b7f?pvs=21)
    
    [https://www.notion.so/images/favicon.ico](https://www.notion.so/images/favicon.ico)
    
- After reducing RRT from 100ms to 10~20ms, appear more paste problem, need to check and solve it → [Fix problem (HARQ,sdu_len,PBCH) | Notion](https://www.notion.so/Fix-problem-HARQ-sdu_len-PBCH-54bada65a71d44a6816a948bb0744ec6?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Meeting with Robert → [Agenda | Notion](https://www.notion.so/Agenda-a1ed669ece3d4a249b8ecdb8b24b9e73?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- New task after meeting
    - Fix check frame wrap around function → [Fix timming window | Notion](https://www.notion.so/Fix-timming-window-fe96286d50d44db68b0d4c920099c323?pvs=21)
        
        ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
        
    - Speed up UL_TTI → [Speed up UL_TTI | Notion](https://www.notion.so/Speed-up-UL_TTI-587229df870c4b059af7306d00fa92a8?pvs=21)
        
        ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
        
    - Speed up DL_TTI → [Speed up DL_TTI | Notion](https://www.notion.so/Speed-up-DL_TTI-f241ddead83942a89eca84de59d45f27?pvs=21)
        
        ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
        

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月22日 下午3:38](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-662613e12538878d32f68175)

(已編輯)

04/22

---

- Prepare for the meeting with Robert's agenda. → [https://ming-hong.notion.site/Question-Report-f472a41a0b104de2961247e5a2c57672?pvs=4](https://www.notion.so/Question-Report-f472a41a0b104de2961247e5a2c57672?pvs=21)
- Create a detailed flowchart for a downlink request. → [ReMeasure | Notion](https://www.notion.so/ReMeasure-3d0fa0d4029a43eb888ad80bd8b46dc3?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Trace PRACH source code → [chain of PRACH | Notion](https://www.notion.so/chain-of-PRACH-4c20082063c846b38257b54352a55001?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Fix the RFsim problem by speed up UL_TTI procdure → [[3] open problems - [not relevant yet] revert commit for rfsim slowdown | Notion](https://www.notion.so/3-open-problems-not-relevant-yet-revert-commit-for-rfsim-slowdown-7e9fe40cbe694b10bd346a4ba86ec2ec?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月19日 下午3:45](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-6622210495056dbc8085b6c4)

(已編輯)

04/19

---

- Fix timming window [Correcting the logic for timing_window judgment.](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/61470e99230685f9cbd5067cca20b7f03c4ae040) → [Fix timming window | Notion](https://www.notion.so/Fix-timming-window-fe96286d50d44db68b0d4c920099c323?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Learn use `nmcli d wifi hotspot ifname wlp2s0 ssid MyWiFiAP password 123321123` to set Ubuntu be a WIFI AP.
- Try to execute nfapi in two machines. → [Two machine nFAPI | Notion](https://www.notion.so/Two-machine-nFAPI-2b536ceabebe47269e158870704b0876?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Measure when use `iperf3` log and Wireshark, will get high ping and high infrequence `TX_Data.request` → [Iperf and RRT | Notion](https://www.notion.so/Iperf-and-RRT-9ba00a58a5444408a5ce7739d3ce282c?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月18日 下午4:05](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-6620d430484ae2ac5bd872ea)

(已編輯)

04/18

---

- Prepare slide for progress sync → [EURECOM - 4/18 report](https://www.canva.com/design/DAGCNRRu-k8/OhiZ2jxqxyk2S6YQX7RZuQ/edit?utm_content=DAGCNRRu-k8&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)
- Update study note about `Does UL_TTI total number increase by set --MACRLCs.[0].ulsch_max_frame_inactivity 0` → [Solve SR problem to reduce RRT | Notion](https://www.notion.so/Solve-SR-problem-to-reduce-RRT-99076dd8ebc84b0cac4728145ff7d62d?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月17日 下午3:48](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-661f7eb8211272b26ec3841b)

(已編輯)

04/17

---

- Check PNF decode SR to VNF check scheduling request result is no problem. → [Solve SR problem to reduce RRT | Notion](https://www.notion.so/Solve-SR-problem-to-reduce-RRT-99076dd8ebc84b0cac4728145ff7d62d?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Trying to find a solution because if I don't let RFsim slow down, it will cause many new problems. → [[3] open problems - [not relevant yet] revert commit for rfsim slowdown | Notion](https://www.notion.so/3-open-problems-not-relevant-yet-revert-commit-for-rfsim-slowdown-7e9fe40cbe694b10bd346a4ba86ec2ec?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Draw the SR relation graph → [link](https://viewer.diagrams.net/?border=0&tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=bxoGHoSG30ykjC3lLpej&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)
- Trace SR scheduler relation source code → [chain of SR scheduler | Notion](https://www.notion.so/chain-of-SR-scheduler-25da7635c9d545eb9140f9df699114ae?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Draw the SR scheduler relation graph. → [Link](https://viewer.diagrams.net/?border=0&tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=JBJ_xvR98S1I9Tq9xvpl&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月16日 下午5:09](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-661e403e42c9a1a7046832e7)

(已編輯)

04/16

---

- Measure UL_DCI execute time about 3ms → [measure UL_DCI (some issues, don’t match Slot) | Notion](https://www.notion.so/measure-UL_DCI-some-issues-don-t-match-Slot-498e3e4bc0a040a985ffee0fe651c355?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
    - Modify code → [https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/251ebcf6117a88e8df83df8828bd65dd9a9e0ea3](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/251ebcf6117a88e8df83df8828bd65dd9a9e0ea3)
- Retrace UCI.indication source code → [chain of function UCI | Notion](https://www.notion.so/chain-of-function-UCI-e67ca08321ec4d678382e002a6a46831?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Prepare slide for progress sync → [EURECOM - 7/30 report](https://www.canva.com/design/DAGCNRRu-k8/OhiZ2jxqxyk2S6YQX7RZuQ/edit?utm_content=DAGCNRRu-k8&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)
    
    ![https://static.canva.com/static/images/android-192x192-2.png](https://static.canva.com/static/images/android-192x192-2.png)
    
- Study OAI doc about nfapi design → [Information on how NR nFAPI works | Notion](https://www.notion.so/Information-on-how-NR-nFAPI-works-bd54aca1fa9848c29f99be0d7e69091a?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Try to find the RRT so high reason. → [Solve SR problem to reduce RRT | Notion](https://www.notion.so/Solve-SR-problem-to-reduce-RRT-99076dd8ebc84b0cac4728145ff7d62d?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月15日 下午4:59](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-661cec56474d543381a16f44)

(已編輯)

04/15

---

- Try to look for the reason UL_TTI spend 9ms. → [[5] look for the reason UL_TTI spend 9ms | Notion](https://www.notion.so/5-look-for-the-reason-UL_TTI-spend-9ms-f8c1d79be52d424fad986fad457cc288?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Fix and rewrite `is_nr_p7_request_in_window` function → [[4] Frame number wraps around from 1023→0 | Notion](https://www.notion.so/4-Frame-number-wraps-around-from-1023-0-13e72b754cf9499b9cd6f6a2f5696559?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
    - Correcting the logic for timing_window judgment. → [https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/7d17e25766dc8579a32f0e31262ecaee40f0ccca](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/7d17e25766dc8579a32f0e31262ecaee40f0ccca)
- Update root issues note → [Reduce nfapi-split RRT | Notion](https://www.notion.so/Reduce-nfapi-split-RRT-f1755299f7f34c98a057b7d9c3d57b7f?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月12日 下午3:38](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-6618e4d6a3e5fef9d50b5ea0)

(已編輯)

04/12

---

- Create a function to dump all data structure values for VNF and PNF PACK/UNPACK, then compare where there are differences. → [Write a function to dump pack/unpack value (notion.site)](https://www.notion.so/Write-a-function-dump-pack-unpack-value-dca9247103bf4c05ad27f89e410e94a9?pvs=21)
- Create an automated script to wait, find, and fill in the oaitun_ue1 IP in the iperf script. → [Create an automated script to wait, find, and fill in the oaitun_ue1 … · dong881/nfapi-split-script@6a6c44c](https://github.com/dong881/nfapi-split-script/commit/6a6c44c76efa3acc668f0414567f6d28a50d9fac)
    
    ![https://github.com/fluidicon.png](https://github.com/fluidicon.png)
    
- New version for automated script in path : build -> all-in-one-> gNB&UE-> iperf3-> ping and all of them will save in LOG folder!! → [New version for automated script in path : build -> all-in-one-> gNB&… · dong881/nfapi-split-script@2f85dda (github.com)](https://github.com/dong881/nfapi-split-script/commit/2f85dda873babae23376c429b89ccf7373d9f12b)
- Find a problem to let when execute with `-MACRLCs.[0].ulsch_max_frame_inactivity 0` could use iperf3 for Uplink, it doesn't abort! → [https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/1b20be0bbe7691842128e15b93ff23d9b41b198e](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/1b20be0bbe7691842128e15b93ff23d9b41b198e)
- Update the task assign list → [TaskLists | Notion](https://www.notion.so/TaskLists-317b4c7393764bff8509413c69d84f21?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Complete the second task assigned by Robert, please. → [[2] open problems - DL traffic: assertion | Notion](https://www.notion.so/2-open-problems-DL-traffic-assertion-8ca16dadd90a4f6bbbd6159045165df4?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Trace source code and Mearse `DL_TTI` execute time → [chain of function DL_TTI | Notion](https://www.notion.so/chain-of-function-DL_TTI-c8b54ca902084dce9e18002df7d19edf?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

Create an automated script to wait, find, and fill in the oaitun_ue1 IP in the iperf script.由 dong881 提交 6a6c44c

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubNew version for automated script in path : build -> all-in-one-> gNB&UE-> iperf3-> ping and all of them will save in LOG folder!!由 dong881 提交 2f85dda

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月11日 下午4:11](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-66179b2741c481293148a0d9)

(已編輯)

04/11

---

- Record current problem: DL traffic: assertion → [OAI nfapi DL traffic assertion.](https://youtu.be/DUl4sPdZsT0)
    
    ![https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png](https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png)
    
- Creat a Note for this problem: [2] open problems - DL traffic: assertion → [[2] open problems - DL traffic: assertion | Notion](https://www.notion.so/2-open-problems-DL-traffic-assertion-8ca16dadd90a4f6bbbd6159045165df4?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Regarding the second open problem - DL traffic: assertion. I have identified that the issue lies in nFAPI when unpacking `value->precodingAndBeamforming.prgs_list[i].pm_idx`. → [Find DL traffic assertion reason: (15e2b440) · 提交 · oai / openairinterface5G · GitLab (eurecom.fr)](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/15e2b440cec307edc410de81e1a1196366037ee2)

![https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png](https://www.youtube.com/s/desktop/d6f8896a/img/favicon_32x32.png)

[OAI nfapi DL traffic assertion.](https://youtu.be/DUl4sPdZsT0)

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月10日 下午5:43](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-66165f2aa5c0bdb7f6f346ec)

(已編輯)

04/10

---

- List meeting with Robert agenda → [Question | Notion](https://www.notion.so/Question-fa92b43093084c5996f222368795d22d?pvs=21) .
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- List currently task list in Notion database → [TaskLists | Notion](https://www.notion.so/TaskLists-317b4c7393764bff8509413c69d84f21?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- List Robert task about currently OAI `nfapi-fixe` proberm → [[1] open problems - ping time is very high | Notion](https://www.notion.so/1-open-problems-ping-time-is-very-high-8806b226a27a4142ad6f50ba140a1248?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月9日 晚上8:05](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-66152f1f7aa35a3cc6fe603e)

(已編輯)

04/09

---

- List all of Note about trace OAI source (chain of function) → [P7 | Notion](https://www.notion.so/6680b20dbfa8465fadea5fed55e59552?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Drow a flow chart for UCI.indication and UL_TTI.request relationship → [Link](https://viewer.diagrams.net/?border=0&tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=QrwC18-C1UwuHl0rLvJM&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)
- Add `-MACRLCs.[0].ulsch_max_frame_inactivity 0` on VNF and fixed PUCCH problem can execute on RRT about 22~42ms. → [Link](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/add93b6bc5c563ce99959ebf76c49ba87251c85b)

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月8日 下午4:19](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-6613a86fddd9320af6504e1d)

(已編輯)

04/08

---

- Collect all tasks and outcomes from the start of the internship until now. → [Reduce nfapi-split RRT | Notion](https://www.notion.so/Reduce-nfapi-split-RRT-f1755299f7f34c98a057b7d9c3d57b7f?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- have a new finding to report to you, along with a preliminary solution idea:The issue of `UE ca6d expected HARQ pid 6 feedback at 181.17, but is at 181.18 instead (HARQ feedback is in the past)` occurs when the scheduler requests PNF to return HARQ feedback in consecutive slots, as observed from the logs. This error happens because after `nr_fill_pucch` is filled, it may be overwritten by the next slot before being used by `rx_func`'s `phy_procedures_gNB_uespec_RX`, resulting in the inability to return HARQ at the expected SFN/SL.Considering that it is being overwritten, our current thought is to introduce an additional buffer layer in `nr_fill_pucch` similar to the form of TX_Data.request. This would prevent the PUCCH PDU content from being overwritten. → [chain of function HARQ | Notion](https://www.notion.so/chain-of-function-HARQ-5363255e10ea44d59658e120369ddffa?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月5日 下午4:57](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-660fbcf4ffcfc6ee3913cf9e)

(已編輯)

04/05

---

- Attend the NTN-workshop → [OAI NTN Working Gorup Meeting Note | Notion](https://www.notion.so/OAI-NTN-Working-Gorup-Meeting-Note-a856a4808f6a41d8b5eab99878ea9429?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Summary all of measurements about P7 Downlink and Uplink → [Measurement | Notion](https://www.notion.so/Measurement-53597d2861cc4212aac5c1a2aa518f14?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Find UL_TTI.request() where is use in PNF and print log time to measure execute time.
    - Measure UL_TTI (From VNF to PNF used) execute time about: 9ms. → [chain of function UL_TTI | Notion](https://www.notion.so/chain-of-function-UL_TTI-4544ab969fb84d5cb7ff381a96b9059b?pvs=21)
        
        ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
        
- List all task lists. → [TaskLists | Notion](https://www.notion.so/TaskLists-317b4c7393764bff8509413c69d84f21?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- For UL_TTI.request()From VNF `oai_nfapi_ul_tti_req` to PNF `save slot_buffer` to tx_func `nr_fill_pucch` to rx_func `nr_decode_pucch0` finish is about : 9ms.
- For HARQ
- For`nfapi_nr_sr_pdu_2_3_4_t` `sr_bit_len`:
    1. PNF sends either 1 or 256.
    2. VNF always receives 0.
    3. Extracting a case from the log : PNF sends 256, and VNF receives 0.
- For`nfapi_nr_harq_pdu_0_1_t` `num_harq`:
    1. PNF sends either 2 or 1.
    2. VNF may receive either 2 or 1 or 0.
    3. Extracting a case from the log: PNF sends 1, and VNF receives 0.
- For VNF I print UCI.indication message in `handle_nr_uci_pucch_0_1` and `handle_nr_uci_pucch_2_3_4`
- For PNF I print UCI.indication message in the bottom of `nr_decode_pucch0` and `nr_decode_pucch2`
- For UCI.indication message data struct I print all of `nfapi_nr_uci_pucch_pdu_format_0_1_t` and `nfapi_nr_uci_pucch_pdu_format_2_3_4_t`

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月4日 下午3:32](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-660e579301b822416abf69ae)

(已編輯)

04/04

---

- Write a `UCI.indication` note. → [chain of function UCI | Notion](https://www.notion.so/chain-of-function-UCI-e67ca08321ec4d678382e002a6a46831?pvs=21) .
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Learn how to use `start_meas` and `stop_mead` (OAI measure time tool).
- Drow `NR_UL_indication` flow chart. → [Link](https://viewer.diagrams.net/?tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=kkXRUhwP1FXfcOAHlaR7&title=nFAPI.drawio#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts%26export%3Ddownload)
- Measure [uci_indication] [crc_indication] [rx_data_indication] execute time → [Measurement | Notion](https://www.notion.so/Measurement-53597d2861cc4212aac5c1a2aa518f14?pvs=21)
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Write a `DCI.indication` note. → [chain of function UL_DCI | Notion](https://www.notion.so/chain-of-function-UL_DCI-6cd8db49567e4762a43538fab8bb359d?pvs=21) .
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    
- Write a `UL_TTI.request`note. → [chain of function UL_TTI | Notion](https://www.notion.so/chain-of-function-UL_TTI-4544ab969fb84d5cb7ff381a96b9059b?pvs=21) .
    
    ![https://www.notion.so/front-static/logo-ios.png](https://www.notion.so/front-static/logo-ios.png)
    

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月3日 下午4:14](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-660d0ff7258d813957545560)

(已編輯)

04/03

---

- Learn how to use FlameGraph → [brendangregg/FlameGraph: Stack trace visualizer (github.com)](https://github.com/brendangregg/FlameGraph)
    - [Memory Flame Graphs (brendangregg.com)](https://www.brendangregg.com/FlameGraphs/memoryflamegraphs.html)
- Search about Wireshark unpack method
    - → [B.4. Plugin folders (wireshark.org)](https://www.wireshark.org/docs/wsug_html_chunked/ChPluginFolders.html)
    - Cisco have old version → [open-nFAPI/wireshark/packet-nfapi.c at master · cisco/open-nFAPI (github.com)](https://github.com/cisco/open-nFAPI/blob/master/wireshark/packet-nfapi.c)
- Trace UCI.indication source code → [Trace Note](https://www.notion.so/chain-of-function-UCI-e67ca08321ec4d678382e002a6a46831?pvs=21)
- Measure UCI.indication() From PNF to VNF execute time: about 70us. → [Note](https://www.notion.so/Measurement-53597d2861cc4212aac5c1a2aa518f14?pvs=21).

brendangregg/FlameGraphStack trace visualizer

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHubpacket-nfapi.c316.55 KB

![https://github.trello.services/images/github.png](https://github.trello.services/images/github.png)

GitHub

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年4月2日 晚上9:52](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-660c0da625e88b644974f405)

(已編輯)

04/02

---

- Learn how to use `iper`. (By Robert suggest) → [Linux perf Examples (brendangregg.com)](https://www.brendangregg.com/perf.html)
    - Referenced Brendan Gregg's article on perf profiling for understanding and debugging.
- Identified excessive `memset` calls using `sudo perf top -p <pid-of-nr-softmodem>`. → [https://nfapi.notion.site/too-more-memsetting-a62e22f93cf84cc7b50fb7a5a23a9840?pvs=4](https://www.notion.so/too-more-memsetting-a62e22f93cf84cc7b50fb7a5a23a9840?pvs=21)
- Tasked with eliminating the excessive `memset` calls using `nfapi-fixes`.
    - Merge `nfapi-fixes`branch into `nfapi-fixes-NTUST`. → [Merge branch 'nfapi-fixes' into nfapi-fixes-NTUST (0893be7b) · 提交 · oai / openairinterface5G · GitLab (eurecom.fr)](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/0893be7b49fc6aa1b846749fb5081e33cfbe0d68)
- Advised to compile with `fno-omit-frame-pointer` option.
    - Revised common options in `CMakeLists.txt` to include `fno-omit-frame-pointer`. → [git patch from Robert (e821440e) · 提交 · oai / openairinterface5G · GitLab (eurecom.fr)](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/e821440ea4ac4bc655e8c95d081188cab3c11899)

[編輯](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [新增連結為附件](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#) • [刪除](https://trello.com/c/EU96ibXv/136-ming-osc-du-high-and-oai-phy-layer-integration#)

**Ming徐銘鴻**

[2024年3月30日 凌晨12:28](https://trello.com/c/EU96ibXv/136-ming-oai-du-high-and-oai-phy-layer-integration#comment-6606ec1d2813a66ee15a4a03)

每個主題下列出討論或完成的項目。對於每個項目，指定負責人和分派的工作。包含任何必要的參考或連結以進一步了解每個項目的細節。

Akmal案例更偏向於以會議和工作日為基礎的組織，注重於每天的進度摘要和問題的紀錄。