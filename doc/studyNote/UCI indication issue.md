# UCI indication issue

Start Date: 2024/10/14
Summary: Addressing a UCI indication issue that results in an "invalid pointer" error during processing.
Status: Done
Assign: 陳奕全, Ming 咚咚 [銘鴻]
Finish Date: 2024/10/14
SUM: 🗓️ Days Spent to Complete: 0

<aside>
💡

There is an error at the point where UCI is received: `free(): invalid pointer`. 

</aside>

![螢幕擷取畫面 2024-10-14 184215.png](%25E8%259E%25A2%25E5%25B9%2595%25E6%2593%25B7%25E5%258F%2596%25E7%2595%25AB%25E9%259D%25A2_2024-10-14_184215.png)

## Error log:

```bash
 十  14 09:15:01 INFO   --> [slot_indication] VNF SFN/Slot 186.5 
 十  14 09:15:01 INFO   --> [DlTtiReq] dlTtiReqTimingInfo: sfn : 186, slot : 7
 十  14 09:15:01 [DEBUG] --> DLTTI nPDUs:0
 十  14 09:15:01 [DEBUG] --> ULTTI nPDUs:0
 十  14 09:15:01 
 十  14 09:15:01 DEBUG  -->  LWR_MAC: Processing UCI Indication
 十  14 09:15:01 INFO  -->  LWR_MAC: Number of UCI PDUs 1
 十  14 09:15:01 
 十  14 09:15:01 INFO  -->  LWR_MAC: Sending UCI Indication to MAC
 十  14 09:15:01 DEBUG  -->  MAC : Received HARQ UCI Indication from OAI PHY
 十  14 09:15:01 
 十  14 09:15:01 DEBUG  -->  SCH : Received HARQ
 十  14 09:15:01 ERROR  -->  SCH : schUpdateHarqFdbk(): Invalid RA state
 十  14 09:15:01 free(): invalid pointer
```

## DU get UCI indication in SFN/SL: 185/17

```jsx
 十  14 09:15:01 INFO   --> [VNF] In phy_nr_uci_indication() NFAPI SFN/SF: 185/17 number_of_pdus :1
 十  14 09:15:01 [DEBUG]	get_queue uci indication: -70160
```

## GDB back trace

```jsx
===================== DL Throughput Per UE==============================
Number of UEs : 1
UE Id : 1   DL Tpt : 0.00
==================================================================

recvfrom() len 20
[NTUST] (p7) header.message_id:130
INFO   --> [slot_indication] VNF SFN/Slot 186.5 
INFO   --> [DlTtiReq] dlTtiReqTimingInfo: sfn : 186, slot : 7
[DEBUG] --> DLTTI nPDUs:0
[DEBUG] --> ULTTI nPDUs:0

DEBUG  -->  LWR_MAC: Processing UCI Indication
INFO  -->  LWR_MAC: Number of UCI PDUs 1

INFO  -->  LWR_MAC: Sending UCI Indication to MAC
DEBUG  -->  MAC : Received HARQ UCI Indication from OAI PHY

DEBUG  -->  SCH : Received HARQ
ERROR  -->  SCH : schUpdateHarqFdbk(): Invalid RA state
free(): invalid pointer

Thread 33 "VNF_P7" received signal SIGABRT, Aborted.
[Switching to Thread 0x7fffa8000640 (LWP 269154)]
__pthread_kill_implementation (no_tid=0, signo=6, threadid=140736011961920) at ./nptl/pthread_kill.c:44
44      ./nptl/pthread_kill.c: No such file or directory.
(gdb) bt
#0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=140736011961920) at ./nptl/pthread_kill.c:44
#1  __pthread_kill_internal (signo=6, threadid=140736011961920) at ./nptl/pthread_kill.c:78
#2  __GI___pthread_kill (threadid=140736011961920, signo=signo@entry=6) at ./nptl/pthread_kill.c:89
#3  0x00007ffff7042476 in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
#4  0x00007ffff70287f3 in __GI_abort () at ./stdlib/abort.c:79
#5  0x00007ffff7089676 in __libc_message (action=action@entry=do_abort, fmt=fmt@entry=0x7ffff71dbb77 "%s\n") at ../sysdeps/posix/libc_fatal.c:155
#6  0x00007ffff70a0cfc in malloc_printerr (str=str@entry=0x7ffff71d9744 "free(): invalid pointer") at ./malloc/malloc.c:5664
#7  0x00007ffff70a2a44 in _int_free (av=<optimized out>, p=<optimized out>, have_lock=0) at ./malloc/malloc.c:4439
#8  0x00007ffff70a5453 in __GI___libc_free (mem=<optimized out>) at ./malloc/malloc.c:3391
#9  0x0000555555a6df5d in SCF_procUciInd (nfapiUciInd=0x5555560ddff8 <UL_INFO+152>) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/lwr_mac_handle_phy.c:407
#10 0x0000555555b56664 in nfapi_nr_vnf_p7_start (config=0x5555566fa1f0) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/nfapi/open-nFAPI/vnf/src/vnf_p7_interface.c:371
#11 0x0000555555ad07e7 in vnf_nr_p7_start_thread (ptr=0x5555566fa1f0) at /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/nfapi/oai_integration/nfapi_vnf.c:1411
#12 0x00007ffff7094ac3 in start_thread (arg=<optimized out>) at ./nptl/pthread_create.c:442
#13 0x00007ffff7126850 in clone3 () at ../sysdeps/unix/sysv/linux/x86_64/clone3.S:81
```

[nFAPI chart.drawio](https://drive.google.com/file/d/1_aKW_1MaCjcsYj9sIVtSJ8CLodyT1LyX/view?usp=sharing)

![image.png](image%2048.png)

**SchProcDlHarqInd has some problem:**

Invalid pointer

![image.png](image%2049.png)

Enable **`callFlowSchMsgRouter`**

```c
uint8_t SchMessageRouter(Pst *pst, void *msg)
{
	...
 callFlowSchMsgRouter(pst);
   switch(pst->event)
   {
```

```bash
 //LOG
 九  30 13:06:41 DEBUG  -->  LWR_MAC: Processing UCI Indication
 九  30 13:06:41 INFO  -->  LWR_MAC: Number of UCI PDUs 1
 九  30 13:06:41 
 九  30 13:06:41 INFO  -->  LWR_MAC: Sending UCI Indication to MAC
 九  30 13:06:41 DEBUG  -->  MAC : Received HARQ UCI Indication from OAI PHY
 九  30 13:06:41 
 九  30 13:06:41 Call Flow: ENTMAC -> ENTSCH : EVENT_DL_HARQ_IND_TO_SCH
 九  30 13:06:41 
 九  30 13:06:41 Call Flow: ENTMAC -> ENTSCH : EVENT_DL_HARQ_IND_TO_SCH
 九  30 13:06:41 
 九  30 13:06:41 free(): invalid pointer
```

<aside>
💡

Do not free `macUciInd` in `SCF_procUciInd`

</aside>

![image.png](image%2050.png)