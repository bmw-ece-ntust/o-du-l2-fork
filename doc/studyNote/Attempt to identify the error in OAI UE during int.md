# Attempt to identify the error in OAI UE during integration with OSC where it fails to decode SIB.

Start Date: 2024/05/28
Summary: Identifying the error in OAI UE during integration with OSC where it fails to decode SIB, resulting in incorrect output for p_b values.
Status: Done
Assign: Ming 咚咚 [銘鴻]

# In `nr_ue_dlsch_procedures` `nr_dlsch_decoding` func

```
static bool nr_ue_dlsch_procedures(PHY_VARS_NR_UE *ue,
                                   const UE_nr_rxtx_proc_t *proc,
                                   NR_UE_DLSCH_t dlsch[2],
                                   int16_t *llr[2],
                                   int G)
```

```c
  ret = nr_dlsch_decoding(ue,
                          proc,
                          gNB_id,
                          llr[0],
                          &ue->frame_parms,
                          &dlsch[0],
                          dl_harq0,
                          frame_rx,
                          nb_symb_sch,
                          nr_slot_rx,
                          harq_pid,
                          dlsch_bytes,
                          p_b,
                          G);
  LOG_I(PHY,"p_b = %lx\n", *p_b);
```

目前OAI L2 + OAI L1 串接是可以輸出p_b[0]… 是有值的: 0x64，但是OSC 儘管nr_dlsch_decoding輸入參數都是一致的(除了無關緊要的frame_rx和沒有使用到的llr[0]不一樣外) 還是輸出p_b[0] = 0x0

Currently, while the concatenation of OAI L2 + OAI L1 outputs a value for p_b[0]... as 0x64, in OSC, even though the input parameters for nr_dlsch_decoding are consistent (except for irrelevant frame_rx and unused llr[0]), it still outputs p_b[0] = 0x0.