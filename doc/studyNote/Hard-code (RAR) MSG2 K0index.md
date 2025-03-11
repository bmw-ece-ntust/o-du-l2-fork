# Hard-code (RAR) MSG2 K0index

Start Date: 2024/10/12
Summary: Hard-coded the K0index from 0 to 2 due to a runtime error encountered in the PDSCH symbol allocation process.
Status: padding
Assign: Ming 咚咚 [銘鴻]
Tags: Hard-code

<aside>
⛔

Beacuse of the following error message, so I hard-code K0index from 0→2

</aside>

```
 十  12 16:28:55 [RAR] k0Index = 0
 十  12 16:28:55 [RAR] initialBwp->pdschCommon.timeDomRsrcAllocList[k0Index].startSymbol = 1
 十  12 16:28:55 [RAR] initialBwp->pdschCommon.timeDomRsrcAllocList[k0Index].lengthSymbol = 13
 十  12 16:28:55 
 十  12 16:28:55 INFO  --> SCH : DMRS symbol found at [2], PDSCH symbols [14]
 十  12 16:28:55 /home/hpe/mwnl-odu-at-oai-based-on-scf/l2/src/5gnrsch/sch.c:1445:43: runtime error: index 15 out of bounds for type 'uint64_t [14][5]'
```

In function: `schFillRar(SchCellCb *cell, SlotTimingInfo rarTime, uint16_t ueId, RarAlloc *rarAlloc, uint8_t k0Index)`

```c
      if((schFillRar(cell, rarTime, ueId, dciSlotAlloc, 2)) != ROK)
```