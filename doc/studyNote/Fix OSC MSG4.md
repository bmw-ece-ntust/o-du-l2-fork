# Fix OSC MSG4

Start Date: 2024/08/29
Summary: Fix the OSC MSG4 allocation issue in the SFN/SL system related to the handling of message timing and resource allocation.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 Issues: OSC need to allocate MSG4 in SFN/SL: 184.19 for MSG4 in 185.0 (slot_ahead=2)

</aside>

```bash
 七  31 06:08:03 INFO  ->  The current Timing Info : sfn : 184, slot : 18
 七  31 06:08:03 
 七  31 06:08:03 INFO  ->  The DL TTI Timing Info : sfn : 185, slot : 0
 七  31 06:08:03 
 七  31 06:08:03 [DEBUG] -->  dlTtiReq->dl_tti_request_body.nPDUs:2
 七  31 06:08:03 
 七  31 06:08:03 nfapi_vnf_p7_nr_dl_config_req(config:0x5ba78c4ec2e0 req:0x71f0cd57d200)
 七  31 06:08:03 
 七  31 06:08:03 pack_dl_tti_request_body_value() PDU Type: 0
 七  31 06:08:03 
 七  31 06:08:03 pack_dl_tti_request_body_value() PDU Type: 0
 七  31 06:08:03 
 七  31 06:08:03 Number of pNfapiMsg->dl_tti_request_body.nGroup 0
 七  31 06:08:03 
 七  31 06:08:03 INFO  -->  OAI_OSC_fillUlTtiReq()
 七  31 06:08:03 
 七  31 06:08:03 INFO  -->  ulTtiReq->n_pdus :1
 七  31 06:08:03 
 七  31 06:08:03 DEBUG  --> Finished OAI_OSC_fillPrachPdu
 七  31 06:08:03 
 七  31 06:08:03 DEBUG  --> Pusch true pduIdx:0
 七  31 06:08:03 INFO  -->  retval 0 OAI_OSC_fillUlTtiReq 6607
 七  31 06:08:03 
 七  31 06:08:03 INFO  -->  OAI_OSC_fillUlDciReq()
 七  31 06:08:03 DEBUG  -> Info : sfn : 185, slot : 0
 七  31 06:08:03 
 七  31 06:08:03 DEBUG  ->  currDlSlot->dlInfo.ulGrant == NULLP 
 七  31 06:08:03 INFO  -->  OAI_OSC_sendTxDataReq()
 七  31 06:08:03 DEBUG  -> Info : sfn : 185, slot : 0
 七  31 06:08:03 
 七  31 06:08:03 INFO  -->  calcTxDataReqPduCount()
 七  31 06:08:03 OAI_OSC_sendTxDataReq, nPdu:1
```

## 目前狀況:

- UE已經發送MSG3，並且OAI PNF已經成功decode MSG3 → [Fix OSC can’t get MSG3](Fix%20OSC%20can%E2%80%99t%20get%20MSG3%2012110098314381029eefecd420ad24ae.md)
- UE已經pack CRC indication、RX_Data indication 給OSC DU High
    - 但是OSC DU在前面就卡住了!!
    - OSC DU 在 Allocate RAR的時候也會allocate Msg4 → 合理，因為184.19收到MSG3後185.0就會送MSG4
    - 若考慮加上 nfapi 的slot ahead，VNF應該在 184.18的時候就將所有資料填入buffer準備在兩個slot後發送
    - 目前OSC還有三個問題(或許是同一個解法)：
        - alloc RAR完後會馬上alloca MSG4 但是會因為有結構找不到因此崩潰停住
        - 後續的UL_DCI 因為沒有PDU 就跳過沒有填
        - DL_TTI **PDU Type: 0 在185.0的時候pack了兩次 (可參考上面log)**

---

Don’t calculate page message pdu 

```c
#ifndef NFAPI
   if(dlSlot->pageAllocInfo)
   {
      /* PDCCH and PDSCH PDU is filled */
      count += 2;
   }
#endif
```

**schFcfsScheduleSlot**

**schProcessMsg4Req**

**schDlRsrcAllocMsg4**

![image.png](image%2077.png)

![image.png](image%2078.png)