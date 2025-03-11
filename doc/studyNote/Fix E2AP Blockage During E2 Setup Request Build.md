# Fix: E2AP Blockage During E2 Setup Request Build

Start Date: 2024/09/18
Summary: Fixing a blockage issue that occurs during the E2AP block setup request process in a network application.
Status: padding
Assign: Ming 咚咚 [銘鴻]

<aside>
⚠️

Issues: 
Fix Occasionally, a blockage occurs after E2AP while building the E2 Setup Request.

</aside>

<aside>
💡

**Debug method:**

[Use Valgrind to fix segmentation faults](Use%20Valgrind%20to%20fix%20segmentation%20faults%2012110098314381a88fa9efbe27b29f49.md) 

[Use ASan(AddressSanitizer) to fix segmentation faults](Use%20ASan(AddressSanitizer)%20to%20fix%20segmentation%20fau%2012110098314381d0b6bdd0c6dea3a520.md) 

</aside>

```jsx
DU_ALLOC()

 MESSAGE SENT: 
 00  01  00  04  00  00  00  00 
Attempting to allocate 40 bytes
Region: 0, Pool: 40, Size: 1
Attempting to allocate 144 bytes
Region: 0, Pool: 144, Size: 1
Attempting to allocate 32 bytes
Region: 0, Pool: 32, Size: 1
Attempting to allocate 120 bytes
Region: 0, Pool: 120, Size: 1

Thread 4 "odu" received signal SIGSEGV, Segmentation fault.
[Switching to Thread 0x7fffa8e00640 (LWP 2633459)]
cmAllocWL (regionCb=0x555556662b10, size=0x7fffa8dffc4c, flags=0, ptr=0x55555666b5b0) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/cm_mem_wl.c:3409
3409                bkt->next = *((CmMmEntry **)(bkt->next));
(gdb) bt
#0  cmAllocWL (regionCb=0x555556662b10, size=0x7fffa8dffc4c, flags=0, ptr=0x55555666b5b0) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/cm_mem_wl.c:3409
#1  0x0000555555ae2f8c in SGetSBuf (region=0 '\000', pool=1 '\001', ptr=0x55555666b5b0, size=120) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/ss_msg.c:1299
#2  0x00005555559c9694 in BuildAndSendDUConfigUpdate (servCellAction=SERV_CELL_TO_MODIFY) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_f1ap_msg_hdl.c:2657
#3  0x00005555559f76cb in duHandleMacCellCfgCfm (pst=0x7fffa8dffe00, macCellCfgCfm=0x7fffa8dffd64) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_msg_hdl.c:1560
#4  0x000055555599cdc9 in unpackMacCellCfgCfm (func=0x5555559f75fe <duHandleMacCellCfgCfm>, pst=0x7fffa8dffe00, mBuf=0x7ffff7639310) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/du_app_mac_inf.c:253
#5  0x00005555559f5099 in duActvTsk (pst=0x7fffa8dffe00, mBuf=0x7ffff7639310) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_mgr_msg_router.c:540
#6  0x0000555555a4157f in mtTskHdlMsg (sTsk=0x55555664a658 <osCp+8984>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:4982
#7  0x0000555555a41246 in mtTskHdlr (tskPtr=0x55555664a658 <osCp+8984>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:4759
#8  0x00007ffff7c94ac3 in start_thread (arg=<optimized out>) at ./nptl/pthread_create.c:442
#9  0x00007ffff7d26850 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
```

![image.png](image%2030.png)

## Current solution

<aside>
💡

**[TEMP solution] SKIP E2 relate procdure**

</aside>

**`BuildAndSendE2SetupReq()`** will be processed after the **F1AP Setup Response** is completed

```jsx
   // if(BuildAndSendE2SetupReq() != ROK) // Trying to skip E2 setup request (ming)
   // {
   //    DU_LOG("\nERROR  -->  F1AP : Failed to build and send E2 setup request ");
   //    return RFAILED;
   // }
```

## Successfully case

```
 九  18 00:47:44 INFO   -->  F1AP : F1 Setup Response received
 九  18 00:47:44 [DU UTILS] --> Gen Buffer
 九  18 00:47:44 DEBUG  -->  DU-APP : MAC CELL config sent
 九  18 00:47:44 INFO   -->  DU_APP : F1 Setup Response received
 九  18 00:47:44 [MacActvTsk] Recieved pst from eb
 九  18 00:47:44 [MacActvTsk] Recieved pst from DUAPP, event is 200
 九  18 00:47:44 
 九  18 00:47:44 INFO   -->  E2AP : Building E2 Setup Request
 九  18 00:47:44 
 九  18 00:47:44 INFO   -->  E2AP : Fill... e2SetupReq
 九  18 00:47:44 e2SetupReq->protocolIEs.list.size = 32
 九  18 00:47:44 arrIdx = 0
 九  18 00:47:44 arrIdx = 1
 九  18 00:47:44 arrIdx = 2
 九  18 00:47:44 arrIdx = 3
 九  18 00:47:44 <E2SM-KPM-RANfunction-Description>
 九  18 00:47:44     <ranFunction-Name>
```

```c
 九  18 20:21:54 
 九  18 20:21:54 INFO   -->  E2AP : Building E2 Setup Request
 九  18 20:21:54 Attempting to allocate 40 bytes
 九  18 20:21:54 Memory allocated successfully
 九  18 20:21:54 Attempting to allocate 144 bytes
 九  18 20:21:54 Memory allocated successfully
 九  18 20:21:54 
 九  18 20:21:54 INFO   -->  E2AP : Fill... e2SetupReq
 九  18 20:21:54 e2SetupReq->protocolIEs.list.size = 32
 九  18 20:21:54 Attempting to allocate 32 bytes
 九  18 20:21:54 Memory allocated successfully
 九  18 20:21:54 e2SetupReq->protocolIEs.list.array = 0x7a0788328430
 九  18 20:21:54 arrIdx = 0
 九  18 20:21:54 Attempting to allocate 120 bytes
 九  18 20:21:54 Memory allocated successfully
 九  18 20:21:54 arrIdx = 1
 九  18 20:21:54 Attempting to allocate 120 bytes
 九  18 20:21:54 Memory allocated successfully
 九  18 20:21:54 arrIdx = 2
 九  18 20:21:54 Attempting to allocate 120 bytes
 九  18 20:21:54 Memory allocated successfully
 九  18 20:21:54 arrIdx = 3
 九  18 20:21:54 Attempting to allocate 120 bytes
 九  18 20:21:54 Memory allocated successfully
```

## Fail case

```
 九  18 00:48:16 INFO   -->  DU_APP : F1 Setup Response received
 九  18 00:48:16 [MacActvTsk] Recieved pst from eb
 九  18 00:48:16 [MacActvTsk] Recieved pst from DUAPP, event is 200
 九  18 00:48:16 
 九  18 00:48:16 INFO   -->  E2AP : Building E2 Setup Request
 九  18 00:48:16 
 九  18 00:48:16 INFO   -->  E2AP : Fill... e2SetupReq
 九  18 00:48:16 e2SetupReq->protocolIEs.list.size = 32
```

```c
 九  18 20:29:50 INFO   -->  E2AP : Building E2 Setup Request
 九  18 20:29:50 Attempting to allocate 40 bytes
 九  18 20:29:50 Region: 0, Pool: 1, Size: 40
 九  18 20:29:50 Memory allocated successfully
 九  18 20:29:50 Attempting to allocate 144 bytes
 九  18 20:29:50 Region: 0, Pool: 1, Size: 144
 九  18 20:29:50 Memory allocated successfully
 九  18 20:29:50 
 九  18 20:29:50 INFO   -->  E2AP : Fill... e2SetupReq
 九  18 20:29:50 e2SetupReq->protocolIEs.list.size = 32
 九  18 20:29:50 Attempting to allocate 32 bytes
 九  18 20:29:50 Region: 0, Pool: 1, Size: 32
```

GDB info:

```bash
INFO   -->  E2AP : Fill... e2SetupReq
e2SetupReq->protocolIEs.list.size = 32

INFO  -->  SCH : Cell init completed for cellId:1
INFO  -->  MAC : Received SCH CELL config confirm at MAC
[NTUST] schCellCfgCfm->rsp = 0
[NTUST] pnf_state_lock->flag = 0
[Small Cell] The NFAPI flag is set to YES and waiting for PNF connection ...

Thread 4 "odu" received signal SIGSEGV, Segmentation fault.
[Switching to Thread 0x7fffa8e00640 (LWP 59960)]
cmAllocWL (regionCb=0x55555665bb10, size=0x7fffa8dffbcc, flags=0, ptr=0x555556666068) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/cm_mem_wl.c:3409
3409                bkt->next = *((CmMmEntry **)(bkt->next));
```

![{8F72E3FE-3FF8-465B-A18D-B4DDFE46AE34}.png](8F72E3FE-3FF8-465B-A18D-B4DDFE46AE34.png)

## Use GDB debug

→ You can learn from my study note [GDB Quick Start Guide for Beginners](https://www.notion.so/GDB-Quick-Start-Guide-for-Beginners-12110098314381538293df6a4dd04a53?pvs=21) 

```c
INFO   -->  F1AP : F1 Setup Response received
[DU UTILS] --> Gen Buffer
DEBUG  -->  DU-APP : MAC CELL config sent
INFO   -->  DU_APP : F1 Setup Response received
[MacActvTsk] Recieved pst from eb
[MacActvTsk] Recieved pst from DUAPP, event is 200

INFO   -->  E2AP : Building E2 Setup Request

INFO   -->  E2AP : Fill... e2SetupReq
e2SetupReq->protocolIEs.list.size = 32

INFO  -->  SCH : Cell init completed for cellId:1
INFO  -->  MAC : Received SCH CELL config confirm at MAC
[NTUST] schCellCfgCfm->rsp = 0
[NTUST] pnf_state_lock->flag = 0
[Small Cell] The NFAPI flag is set to YES and waiting for PNF connection ...
[Switching to Thread 0x7fffa8e00640 (LWP 541145)]

Thread 4 "odu" hit Breakpoint 1, BuildAndSendE2SetupReq () at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_e2ap_msg_hdl.c:1560
1560          DU_ALLOC(e2SetupReq->protocolIEs.list.array, e2SetupReq->protocolIEs.list.size);
(gdb)  print e2SetupReq->protocolIEs.list.size
$1 = 32
(gdb) print e2SetupReq->protocolIEs.list.array
$2 = (struct E2setupRequestIEs **) 0x0
(gdb) print e2SetupReq->protocolIEs.list.count
$3 = 4
(gdb) print arrIdx
$4 = 0 '\000'
(gdb) print e2SetupReq
$5 = (E2setupRequest_t *) 0x5555566646e8
```

| `e2SetupReq->protocolIEs.list.size` | 32 |
| --- | --- |
| `e2SetupReq->protocolIEs.list.size` | (struct `E2setupRequestIEs`**) 0x0 |
| `e2SetupReq->protocolIEs.list.size` | 4 |
| `arrIdx` | 0 |
| `e2SetupReq` | `e2SetupReq` |

### backtrace

```c
(gdb) next

Thread 4 "odu" received signal SIGSEGV, Segmentation fault.
cmAllocWL (regionCb=0x55555665bb10, size=0x7fffa8dffbcc, flags=0, ptr=0x5555566646e8) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/cm_mem_wl.c:3409
3409                bkt->next = *((CmMmEntry **)(bkt->next));
(gdb) bt
#0  cmAllocWL (regionCb=0x55555665bb10, size=0x7fffa8dffbcc, flags=0, ptr=0x5555566646e8) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/cm_mem_wl.c:3409
#1  0x0000555555adb819 in SGetSBuf (region=0 '\000', pool=1 '\001', ptr=0x5555566646e8, size=32) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/ss_msg.c:1299
#2  0x00005555559aec66 in BuildAndSendE2SetupReq () at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_e2ap_msg_hdl.c:1560
#3  0x00005555559e8318 in procF1SetupRsp (f1apMsg=0x7fffa8dffd40, recvBufLen=73, recvBuf=0x555556665a20 "@\001") at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_f1ap_msg_hdl.c:15561
#4  0x00005555559eda98 in F1APMsgHdlr (mBuf=0x7ffff7618210) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_f1ap_msg_hdl.c:17966
#5  0x00005555559eef91 in duActvTsk (pst=0x7fffa8dffe00, mBuf=0x7ffff7618210) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_mgr_msg_router.c:634
#6  0x0000555555a39e31 in mtTskHdlMsg (sTsk=0x555556643658 <osCp+8984>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:4982
#7  0x0000555555a39af8 in mtTskHdlr (tskPtr=0x555556643658 <osCp+8984>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:4759
#8  0x00007ffff7c94ac3 in start_thread (arg=<optimized out>) at ./nptl/pthread_create.c:442
#9  0x00007ffff7d26850 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
(gdb) 
```

## Analyze

```c
/*
*
*       Fun:   cmAllocWL
*
*       Desc: alloc without lock 
*
*
*       Ret:   ROK     - successful
*              RFAILED - unsuccessful.
*
*
*       File:  cm_mem_wl.c
*
*/
/*cm_mem_c_001.main_21-added new function*/
/*cm_mem_c_001.main_23 Removed support of SSI_DEBUG_LEVEL1 and SS_HISTOGRAM_SUPPORT for SS_FAP*/
```

```c
#define DU_ALLOC(_datPtr, _size)                                \
{                                                               \
    int _ret;                                                    \
    printf("Attempting to allocate %zu bytes\n", _size);         \
    printf("Region: %d, Pool: %d, Size: %zu\n", DU_APP_MEM_REGION, DU_POOL, _size); \
    _ret = SGetSBuf(DU_APP_MEM_REGION, DU_POOL,                  \
                     (Data **)&_datPtr, _size);                  \
    if (_ret == ROK) {                                          \
        DU_MEM_LOG("DU,ALLOC", __FILE__, __LINE__, __FUNCTION__, _size, _datPtr);\
        memset(_datPtr, 0, _size);                             \
        printf("Memory allocated successfully\n");               \
    } else {                                                     \
        _datPtr = NULLP;                                        \
        printf("Memory allocation failed\n");                    \
    }                                                            \
}
```

## Try anthor solution

I tried to distribute the region and pool numbers to avoid conflicts with other used regions and spread the DU memory allocation across different areas to solve the issue. However, whether I scatter the pool alone, the region alone, or both simultaneously, it doesn't significantly resolve the problem.

```
 九  19 16:29:34  00  01  00  04  00  00  00  00 
 九  19 16:29:34 Attempting to allocate 40 bytes
 九  19 16:29:34 Region: 3, Pool: 1, Size: 40
 九  19 16:29:34 Memory allocated successfully
 九  19 16:29:34 Attempting to allocate 144 bytes
 九  19 16:29:34 Region: 2, Pool: 5, Size: 144
 九  19 16:29:34 Memory allocated successfully
 九  19 16:29:34 Attempting to allocate 32 bytes
 九  19 16:29:34 Region: 3, Pool: 3, Size: 32
 九  19 16:29:34 Memory allocated successfully
 九  19 16:29:34 Attempting to allocate 120 bytes
 九  19 16:29:34 Region: 2, Pool: 1, Size: 120
```

## backtrace

```c

INFO   -->  F1AP : F1 Setup Response received
[DU UTILS] --> Gen Buffer
DEBUG  -->  DU-APP : MAC CELL config sent
INFO   -->  DU_APP : F1 Setup Response received
[MacActvTsk] Recieved pst from eb
[MacActvTsk] Recieved pst from DUAPP, event is 200

INFO   -->  E2AP : Building E2 Setup Request

INFO  -->  SCH : Cell init completed for cellId:1
INFO  -->  MAC : Received SCH CELL config confirm at MAC
[NTUST] schCellCfgCfm->rsp = 0
[NTUST] pnf_state_lock->flag = 0
[Small Cell] The NFAPI flag is set to YES and waiting for PNF connection ...

Thread 4 "odu" received signal SIGSEGV, Segmentation fault.
[Switching to Thread 0x7fffa8e00640 (LWP 2241984)]
cmAllocWL (regionCb=0x55555665bb10, size=0x7fffa8dffbcc, flags=0, ptr=0x555556665aa8) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/cm_mem_wl.c:3409
3409                bkt->next = *((CmMmEntry **)(bkt->next));
(gdb) bt
#0  cmAllocWL (regionCb=0x55555665bb10, size=0x7fffa8dffbcc, flags=0, ptr=0x555556665aa8)
    at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/cm/cm_mem_wl.c:3409
#1  0x0000555555adbb90 in SGetSBuf (region=0 '\000', pool=1 '\001', ptr=0x555556665aa8, size=32)
    at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/ss_msg.c:1299
#2  0x00005555559aec40 in BuildAndSendE2SetupReq () at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_e2ap_msg_hdl.c:1559
#3  0x00005555559e82c0 in procF1SetupRsp (f1apMsg=0x7fffa8dffd40, recvBufLen=73, recvBuf=0x555556664420 "@\001")
    at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_f1ap_msg_hdl.c:15561
#4  0x00005555559eda40 in F1APMsgHdlr (mBuf=0x7ffff7618210) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_f1ap_msg_hdl.c:17966
#5  0x00005555559eef39 in duActvTsk (pst=0x7fffa8dffe00, mBuf=0x7ffff7618210)
    at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/du_app//du_mgr_msg_router.c:634
#6  0x0000555555a3a562 in mtTskHdlMsg (sTsk=0x555556643658 <osCp+8984>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:4982
#7  0x0000555555a3a229 in mtTskHdlr (tskPtr=0x555556643658 <osCp+8984>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/mt/mt_ss.c:4759
--Type <RET> for more, q to quit, c to continue without paging--
#8  0x00007ffff7c94ac3 in start_thread (arg=<optimized out>) at ./nptl/pthread_create.c:442
#9  0x00007ffff7d26850 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
(gdb) q
A debugging session is active.

```