# UE is unable to receive MSG4 PDSCH message

Start Date: 2024/09/28
Summary: Fixing the nr_of_symbols parameter for MSG4 to ensure correct PDSCH message reception and addressing the "Invalid CCCH message" error.
Status: padding
Assign: Ming 咚咚 [銘鴻]

## Problem Description

### **Problem Phenomenon**:

The `nr_of_symbols` parameter for MSG3 was not set correctly, causing issues with UE decoding. After fixing the parameter, the PDSCH message is successfully received, but an "Invalid CCCH message" error occurs.

## Solution: Revise `nr_of_symbols`

Revise `nr_of_symbols` → [DmrsSymbol](DmrsSymbol%20121100983143811fbf28eeba03817b56.md) to be hardcoded like SIB1. For MSG3, the parameter in the `sch_common.c` config file needs to be fixed to `nr_of_symbols = 5` so that the UE can decode it. Other messages will use hardcoded values set to different values currently. For example, in this case (message4), we need to set `nr_of_symbols` to 13.

```c
/* ======== small cell integration ======== */
#ifdef NFAPI   
   pdsch->pdschTimeAlloc.numSymb = 13;
#else
   pdsch->pdschTimeAlloc.numSymb = pdschNumSymbols;
#endif
/* ======================================== */
```

Currently, the number of symbols for SIB1 and MSG4 is filled using a hardcoded approach. Ideally, the number of symbols should be selected from a list in the SIB1 payload (which contains four sets of symbol numbers), with the selection starting from the first set and moving to subsequent ones if the first is not suitable. However, in OSC’s current logic, the number of symbols for PDSCH is always taken from the first set.

Messages that currently use PDSCH include SIB1, MSG2 (RAR), and MSG4. In OAI’s configuration, only MSG2 uses a different number of symbols, while in OSC, it always sends just one set. As a result, the current situation is:

- SIB1 is hardcoded
- MSG2 follows the original code using the regular reference parameters
- MSG4 is hardcoded

Of course, the reverse setup is also possible:

- SIB1 follows the original code using the regular reference parameters
- MSG2 is hardcoded
- MSG4 follows the original code using the regular reference parameters

However, the most important thing is to fix OSC so that it can automatically choose the correct number of symbols.

For now, since I want to quickly move past MSG4, I am evaluating whether this level of hardcoding won't impact the subsequent processes, so I will temporarily pause addressing this issue and proceed to work on the latest problems.

---

## Then, next issues: `Invalid CCCH message!`

It successfully received the PDSCH message from PNF and from OSC DU High, but the CCCH message is invalid.

```
 九  28 01:42:07 [0m[32m[NR_MAC]   [RAPROC][184.19] RA-Msg3 transmitted
 九  28 01:42:07 [0m[NR_MAC]   ul config in slot 18
 九  28 01:42:07 [0m[MAC]   In [185.15] Handling DLSCH PDU type 3
 九  28 01:42:07 [0m[MAC]   [185.15]: processing PDU 0 (with length 60) of 1 total number of PDUs...
 九  28 01:42:07 [0m[MAC]   [UE] LCID 0, PDU length 60
 九  28 01:42:07 [0m[1;31m[NR_MAC]   Invalid CCCH message!, pdu_len: 60
 九  28 01:42:07 [0m[PHY]   Copying pucch pdu to UE PHY
```

→ [`Invalid CCCH messag`e](Invalid%20CCCH%20message%2012110098314381d08d2ff1cc30b8716f.md) 

---

Can’t enter 

```
static uint32_t nr_ue_dl_processing(nr_downlink_indication_t *dl_info)

{

	...
	        case FAPI_NR_RX_PDU_TYPE_DLSCH:
          ret_mask |= (handle_dlsch(mac, dl_info, i)) << FAPI_NR_RX_PDU_TYPE_DLSCH;
          break;
```

`TX_PAYLOAD_HDR_LEN`

InitialULRRCMessageTransfer