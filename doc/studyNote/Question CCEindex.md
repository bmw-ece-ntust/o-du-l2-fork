# Question: CCEindex

Start Date: 2024/09/25
Summary: The project involves managing the CCE index for resource allocation in NR MAC and PDCCH scheduling.
Status: padding
Assign: Ming 咚咚 [銘鴻]

## What is `CCEindex`

## In OSC

```bash
pdcch->dci.cceIndex = 4; /* considering SIB1 is sent at cce 0-1-2-3 */
```

```bash
pdcch->dci.cceIndex = 0; /* 0-3 for UL and 4-7 for DL */
```

## In OAI

```bash
      // get CCEindex, needed also for PUCCH and then later for PDCCH
      int CCEIndex = get_cce_index(nr_mac,
                                 CC_id, slotP, 0,
                                 &aggregation_level,
                                 ss,
                                 coreset,
                                 &ra->sched_pdcch,
                                 true);

    if (CCEIndex < 0) {
      LOG_E(NR_MAC, "%s(): cannot find free CCE for RA RNTI 0x%04x!\n", __func__, ra->rnti);
      return;
    }
  
    const int delta_PRI = 0;
    int r_pucch = nr_get_pucch_resource(coreset, ra->UL_BWP.pucch_Config, CCEIndex);

    LOG_I(NR_MAC, "Msg4 r_pucch %d (CCEIndex %d, delta_PRI %d)\n", r_pucch, CCEIndex, delta_PRI);

```