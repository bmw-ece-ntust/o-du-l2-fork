# Fix SSB RBstart and remove hard-code

Start Date: 2024/10/12
Summary: Fixing SSB RBstart issues by removing hard-code and implementing dynamic configurations.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/12
SUM: 🗓️ Days Spent to Complete: 0

## Why we need hard-code before

<aside>
⛔

**SCH: Requested DL PRB unavailable**

**SCH: PRB allocation failed for SIB1**

</aside>

## Solution

![image.png](image%2088.png)

- Before

- After

| SSB-startPRB | 0 |
| --- | --- |
| SSB-numPRB | 21 |
| SIB1-startPRB | 27 → pack hardcode 0 |
| SIB1-numPRB | 10 |

| SSB-startPRB | 43 |
| --- | --- |
| SSB-numPRB | 21 |
| SIB1-startPRB | 0 |
| SIB1-numPRB | 10 |

### In **`schBroadcastSsbAlloc()`**

add 43 PRB, same as OAI configuration

```
#  downlinkConfigCommon
    #frequencyInfoDL
      # this is 3600 MHz + 43 PRBs@30kHz SCS (same as initial BWP)
```

```jsx
ssbStartPrb = 43 + cell->cellCfg.ssbSubcOffset; //cell->cellCfg.ssbSubcOffset = 0
```

In **`fillSchSib1Cfg()`**

```c
#ifdef NFAPI
   pdsch->pdschFreqAlloc.startPrb  = 0;
   pdsch->pdschFreqAlloc.numPrb    = schCalcNumPrb(tbSize, SIB1_MCS, NUM_PDSCH_SYMBOL);
#else
```

In **`unpack_dl_tti_pdsch_pdu_rel15_value()`**

remove hard-code

```jsx
  // value->rbStart = 0;
```