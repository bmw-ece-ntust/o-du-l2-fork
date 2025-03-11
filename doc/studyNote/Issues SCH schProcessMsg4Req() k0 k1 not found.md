# Issues: SCH: schProcessMsg4Req() : k0 k1 not found

Start Date: 2024/09/11
Summary: Resolving synchronization issues in nFAPI integration, focusing on the k0 and k1 values not found during the schProcessMsg4Req() stage.
Status: Done
Assign: Ming 咚咚 [銘鴻]

## Task: Resolve Current nFAPI Integration Issues

### Goal:

Identify and address synchronization issues between OSC DU High and OAI Layer1. Improve the flow of RACH indications and ensure correct message flow from **Message3** to **Message4**.

### Focus Today:

Resolve the issue of **k0** and **k1** not being found during the `schProcessMsg4Req()` stage, which is impacting the scheduling of **RRC Setup**.

### Defined Issue:

The error occurs when the function `findValidK0K1Value()` fails to find valid k0 and k1 values:

```c
if(findValidK0K1Value(cell, currTime, ueId, false, &pdschStartSymbol,
   &pdschNumSymbols, &pdcchTime, &pdschTime, &pucchTime,
   isRetxMsg4, *msg4HqProc) != true )
{
   DU_LOG("\\nERROR  -->  SCH: schProcessMsg4Req() : k0 k1 not found");
   return RFAILED;
}

```

### Proposed Solution:

Trace the `BuildK0K1Table` function to debug the issue.

### Function Definition:

```c
void BuildK0K1Table(SchCellCb *cell, SchK0K1TimingInfoTbl *k0K1InfoTbl,
   bool pdschCfgCmnPres, SchPdschCfgCmn pdschCmnCfg, SchPdschConfig pdschDedCfg,
   uint8_t ulAckListCount, uint8_t *UlAckTbl)
{
   // Function logic here
}

```

By tracing this function, we can determine if the k0/k1 values are being calculated correctly or if additional configuration or timing alignment is needed.

```

This structure helps break down the issue and proposed solution with clear sections.
```

### Current Status

| Item | Status |
| --- | --- |
| DU Initializing | ✅ |
| F1 setup request | ✅ |
| F1 Setup response | ✅ |
| P5 config.request | ✅ |
| P5 config.response | ✅ |
| DU configuration Update | ✅ |
| DU configurationUpdate ACK | ✅ |
| P5 start.request | ✅ |
| P5 start.response | ✅ |
| MIB | ✅ |
| SIB1 | ✅ |
| MSG1 (Preamble) | ✅ |
| MSG2 (RAR) | ✅ |
| MSG3 (RRC request) | ✅ |
| F1AP: Initial UL RRC transfer transfer | ✅ |
| F1AP: DL RRC message transfer | ✅ |
| MSG4 (RRC response) | ⌛ |
| UL RRC transfer | ❌ |
| F1AP: Authentication request | ❌ |
| DL RRC transfer | ❌ |
|  |  |

# Issues define: findValidK0K1Value failed

```c
   if(findValidK0K1Value(cell, currTime, ueId, false, &pdschStartSymbol, &pdschNumSymbols, &pdcchTime, &pdschTime,\
            &pucchTime, isRetxMsg4, *msg4HqProc) != true )
   {
      DU_LOG("\nERROR  -->  SCH: schProcessMsg4Req() : k0 k1 not found");
      return RFAILED;
   }
```

# Solution→ Trace BuildK0K1Table

```c
void BuildK0K1Table(SchCellCb *cell, SchK0K1TimingInfoTbl *k0K1InfoTbl, bool pdschCfgCmnPres, SchPdschCfgCmn pdschCmnCfg,\
SchPdschConfig pdschDedCfg, uint8_t ulAckListCount, uint8_t *UlAckTbl)
{
```

## Error Logs:

```jsx
func findValidK0K1Value numK0 0 in slot: 15
```

![image.png](image%2032.png)

# Trach function (**BuildK0K1Table**)

**@brief Fills k0 and k1 information table** 

## Check (current slot) is DL for PDCCH :

```c
      /* Checking all possible indexes for K0 and K1 values. */
      printf("Checking all possible indexes for K0 and K1 values.\n");
      printf("\tTotal Slot = %d\n", cell->numSlots);
      for(slotIdx = 0; slotIdx < cell->numSlots; slotIdx++)
      {
         /* If current slot is UL or FLEXI then Skip because PDCCH is sent only in DL slots. */
         slotCfg = schGetSlotSymbFrmt(slotIdx%totalCfgSlot, cell->slotFrmtBitMap);
         printf("\tSlot Idx = %d, Slot Cfg = %d\n", slotIdx, slotCfg);
         if(slotCfg == UL_SLOT || slotCfg == FLEXI_SLOT)
         {
            continue;
         }
```

## Check (current slot + k0) is DL:

```c
            /* If current slot + k0 is UL then skip the slot
             * else if it is DL slot then continue the next steps
             * else if it is a FLEXI slot then check symbols of slot, It should not
             * contain any UL slot. */
            tmpSlot = (slotIdx+k0TmpVal) % totalCfgSlot;
            slotCfg = schGetSlotSymbFrmt(tmpSlot, cell->slotFrmtBitMap);
            if(slotCfg == UL_SLOT)
            {
               continue;
            }
            if(slotCfg == FLEXI_SLOT)
            {
               for(checkSymbol = startSymbol; checkSymbol<endSymbol; checkSymbol ++)
               {
                  slotCfg = cell->slotCfg[tmpSlot][checkSymbol];
                  if(slotCfg == UL_SLOT)
                  {
                     ulSlotPresent = true;
                     break;
                  }
               }
               if(ulSlotPresent == true)
               {
                  continue;
               }
            }
```

## Count (current slot + k0 + k1) is UL:

```c
            /* If current slot + k0 + k1 is a DL slot then skip the slot
             * else if it is UL slot then store the information 
             * else if it is FLEXI slot then check the symbols, it must have
             * at least one UL symbol. */
            numK1 = 0;
            for(k1Index = 0; k1Index < ulAckListCount; k1Index++)
            {
               k1TmpVal = UlAckTbl[k1Index]; // uint8_t defaultUlAckTbl[DEFAULT_UL_ACK_LIST_COUNT]= {1, 2, 3 , 4, 5, 6, 7, 8};
               printf("[k1Index %d] k0 TmpVal = %d, k1TmpVal = %d\n", k1Index, k0TmpVal, k1TmpVal);
               if(k1TmpVal > MIN_NUM_K1_IDX) //MIN_NUM_K1_IDX 4
```

# something need to check:

| K0 | 0 |
| --- | --- |
| K1 | 7 |
- current use K1 value:  7 (done)

## debug **`schGetSlotSymbFrmt()` and `cell->slotFrmtBitMap`**

```c
         ADD_DELTA_TO_TIME((*pdschTime),(*pucchTime), k1Val, cell->numSlots);
#ifdef NR_TDD
         printf("slotFrmtBitMap %lx\n", cell->slotFrmtBitMap);
         for(int islot = 0; islot < 20; islot++)
            printf("[TEST schGetSlotSymbFrmt] %d -> %d\n",islot ,schGetSlotSymbFrmt(islot, cell->slotFrmtBitMap));
         if(schGetSlotSymbFrmt(pucchTime->slot, cell->slotFrmtBitMap) == DL_SLOT)
         {
            printf("pucchTime->slot %d != UL_SLOT\n", pucchTime->slot);
            continue;
         }
#endif
```

```
 九  17 20:06:19 slotFrmtBitMap 58000
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 0 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 1 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 2 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 3 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 4 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 5 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 6 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 7 -> 2
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 8 -> 1
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 9 -> 1
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 10 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 11 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 12 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 13 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 14 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 15 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 16 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 17 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 18 -> 0
 九  17 20:06:19 [TEST schGetSlotSymbFrmt] 19 -> 0
 九  17 20:06:19 pucchTime->slot 19 != UL_SLOT
```

<aside>
💡

There is a bug when using `slotFrmtBitMap` and querying through `schGetSlotSymbFrmt`! The slot needs to be modded by 10 first!

</aside>

[https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/0dd1210eeca53d020d53fcb3f3d35cc18849cc62](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/0dd1210eeca53d020d53fcb3f3d35cc18849cc62)

[https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/2d2e6cfce24688196f83ff0addea8969445aa46c](https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/2d2e6cfce24688196f83ff0addea8969445aa46c)

## Solution

- modded by 10
- Revise **MIN_NUM_K1_IDX 4→3**

After that! It can success get **`LWR_MAC: MSG4 sent...` !!! → complete~ next step**