# Issue: After MSG4 ACK/NACK UL config_request called at wrong slot 1 or 2

Start Date: 2024/09/26
Summary: Investigating the issue of UL config_request being called at incorrect slots during MSG4 ACK/NACK process.
Status: Reject
Assign: 陳奕全

![image.png](image%2054.png)

![image.png](image%2055.png)

```bash
 九  26 13:58:42 Assertion (is_nr_UL_slot(tdd_config, slot_tx, mac->frame_type) != 0) failed!
 九  26 13:58:42 In lockGet_ul_config() /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:79
 九  26 13:58:42 UL config_request called at wrong slot 1
 
 ---
  九  26 14:18:04 Assertion (is_nr_UL_slot(tdd_config, slot_tx, mac->frame_type) != 0) failed!
 九  26 14:18:04 In lockGet_ul_config() /home/hpe/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_scheduler.c:79
 九  26 14:18:04 UL config_request called at wrong slot 2
```

Plan:

1. Check how to modify k2
2. Check MSG3 delta 

In `schProcessRaReq` k2 add msg3Delta(3)

![image.png](image%2056.png)

```
 九  26 14:18:04 =======K2:4 index:0=======
 九  26 14:18:04 =======K2:7=======
```

```bash
[DLTTI] SFN/SLOT 185.15
[DLTTI] SFN/SLOT 186.0
```

15~2 is  7 slot  and 16

~~so maybe this problem is occur to MSG3delta~~ 

~~We need to use K2 = 4 directly instead of （K2 + MSG3 delta =7) when MSG4 ACK/NACK~~

**schProcessRaReq has MSG3 delta**

**schProcessMsg4Req**

```c
uint8_t defaultUlAckTbl[DEFAULT_UL_ACK_LIST_COUNT]= {1, 2, 3 , 4, 5, 6, 7, 8};

```

**schDlRsrcAllocMsg4**

<aside>
👀

[Issues:  Assertion is_nr_UL_slot() failed](Issues%20Assertion%20is_nr_UL_slot()%20failed%201211009831438180a3e9f623fa434c83.md)

</aside>

1. Faster CU
2. ~~Revise k1 in odu~~
3. Faster PNF execution speed
4. UE k1 Revise TX_data PDU K1 relate parameter?
5.