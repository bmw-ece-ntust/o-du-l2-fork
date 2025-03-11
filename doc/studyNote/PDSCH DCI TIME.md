# PDSCH DCI TIME

Start Date: 2024/07/24
Summary: A detailed overview of the PDSCH DCI time assignment and its related programming implementation.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 dci_payload.time_domain_assignment.val

</aside>

|  | OAI | OSC |
| --- | --- | --- |
| dci_payload.time_domain_assignment.val | 2 (get_dl_tda) | 0 (k0Index) |
| startSymbolIndex | 1 (k0Index=0) | 1 (k0Index=0) |
| nrOfSymbols | 13 (k0Index=0) | 13 (k0Index=0) |

```c
int get_dl_tda(const gNB_MAC_INST *nrmac, const NR_ServingCellConfigCommon_t *scc, int slot) {

  /* we assume that this function is mutex-protected from outside */
  const NR_TDD_UL_DL_Pattern_t *tdd = scc->tdd_UL_DL_ConfigurationCommon ? &scc->tdd_UL_DL_ConfigurationCommon->pattern1 : NULL;
  AssertFatal(tdd || nrmac->common_channels->frame_type == FDD, "Dynamic TDD not handled yet\n");

  // Use special TDA in case of CSI-RS
  if(nrmac->UE_info.sched_csirs > 0)
    return 1;

  if (tdd && tdd->nrofDownlinkSymbols > 1) { // if there is a mixed slot where we can transmit DL
    const int nr_slots_period = tdd->nrofDownlinkSlots + tdd->nrofUplinkSlots + 1;
    if ((slot % nr_slots_period) == tdd->nrofDownlinkSlots)
      return 2;
  }
  return 0; // if FDD or not mixed slot in TDD, for now use default TDA
}
```

```c
  LOG_I(NR_MAC, "Msg2 startSymbolIndex.nrOfSymbols %d.%d\n", tda_info.startSymbolIndex, tda_info.nrOfSymbols);
```