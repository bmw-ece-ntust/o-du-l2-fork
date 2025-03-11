# Solve SR problem to reduce RRT

Start Date: 2024/04/16
Summary: Solve the scheduling request issue to reduce UL inactivity in NR MAC layer operations.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 Reference:

[chain of ulsch_max_frame_inactivity](https://www.notion.so/chain-of-ulsch_max_frame_inactivity-1211009831438157ab81ef7201b25c13?pvs=21)

[chain of function UCI](https://www.notion.so/chain-of-function-UCI-12110098314381e1b5d2e840a4973515?pvs=21)  

[chain of SR scheduler](https://www.notion.so/chain-of-SR-scheduler-1211009831438188a9fbc94b8a310b4b?pvs=21) 

</aside>

> openairinterface5g/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_ulsch.c
> 

UE is to be scheduled if

- (1) we think the UE has more bytes awaiting than what we scheduled
- (2) there is a scheduling request
- (3) or we did not schedule it in more than 10 frames

```c
  const NR_UE_sched_ctrl_t *sched_ctrl =&UE->UE_sched_ctrl;

```

```c
  const bool high_inactivity = diff >= (ulsch_max_frame_inactivity > 0 ? ulsch_max_frame_inactivity * n : num_slots_per_period);
  LOG_I(NR_MAC,
        "%4d.%2d UL inactivity %d slots has_data %d SR %d tooHigh %d max_frame %d period %d\n",
        frame,
        slot,
        diff,
        has_data,
        sched_ctrl->SR,
        high_inactivity,
        ulsch_max_frame_inactivity,
        num_slots_per_period);
```

```bash
avril 16 15:00:01 [0m1713272401.620780 [NR_MAC]    194. 8 UL inactivity 100 slots has_data 0 SR 0 tooHigh 0 max_frame 10 period 10
avril 16 15:00:01 [0m1713272401.620792 [NR_MAC]   pf_ul: do_sched UE 425c => no
```

I summary to table let easy to read

| **Parameter** | **Value** |
| --- | --- |
| UL inactivity | 194.8 |
| Slots | 100 |
| Has data | 0 |
| SR | 0 |
| Too high | 0 |
| Max frame | 10 |
| Period | 10 |
| n | 20 |
| do_sched UE | no |

### Try to find where `sched_ctrl->SR` is set

- [ ]  Verify that the transition from `PNF` to `VNF` is correctly sent.
- [ ]  Confirm that the variable `sched_ctrl->SR` is correctly set when received by the `VNF`.

By tracing the chain of `UCI.indication` → [chain of function UCI](https://www.notion.so/chain-of-function-UCI-12110098314381e1b5d2e840a4973515?pvs=21) , we can identify the point where `sched_ctrl->SR` is set to true based on certain conditions being met. 

```c
  // check scheduling request result, confidence_level == 0 is good
  if (uci_01->pduBitmap & 0x1) {
    if (uci_01->sr.sr_indication && uci_01->sr.sr_confidence_level == 0 && uci_01->ul_cqi >= 148) {
      // SR detected with SNR >= 10dB
      sched_ctrl->SR |= true;
      LOG_D(NR_MAC, "SR UE %04x ul_cqi %d\n", uci_01->rnti, uci_01->ul_cqi);
    }
```

## Main Function

## 🔥Major three condition

`has_data` || `sched_ctrl->SR` || `high_inactivity`

```c
static bool nr_UE_is_to_be_scheduled(const NR_ServingCellConfigCommon_t *scc, int CC_id,  NR_UE_info_t* UE, frame_t frame, sub_frame_t slot, uint32_t ulsch_max_frame_inactivity)
{
  const int n = nr_slots_per_frame[*scc->ssbSubcarrierSpacing];
  const int now = frame * n + slot;

  const NR_UE_sched_ctrl_t *sched_ctrl =&UE->UE_sched_ctrl;

  const NR_TDD_UL_DL_Pattern_t *tdd =
      scc->tdd_UL_DL_ConfigurationCommon ? &scc->tdd_UL_DL_ConfigurationCommon->pattern1 : NULL;
  int num_slots_per_period;
  int last_ul_slot;
  if (tdd) { // Force the default transmission in a full slot as early as possible in the UL portion of TDD period (last_ul_slot)
    num_slots_per_period =  n / get_nb_periods_per_frame(tdd->dl_UL_TransmissionPeriodicity);
    last_ul_slot = 1 + tdd->nrofDownlinkSlots;
  } else {
    num_slots_per_period = n;
    last_ul_slot = sched_ctrl->last_ul_slot;
  }

  const int last_ul_sched = sched_ctrl->last_ul_frame * n + last_ul_slot;
  const int diff = (now - last_ul_sched + 1024 * n) % (1024 * n);
  /* UE is to be scheduled if
   * (1) we think the UE has more bytes awaiting than what we scheduled
   * (2) there is a scheduling request
   * (3) or we did not schedule it in more than 10 frames */
  const bool has_data = sched_ctrl->estimated_ul_buffer > sched_ctrl->sched_ul_bytes;
  const bool high_inactivity = diff >= (ulsch_max_frame_inactivity > 0 ? ulsch_max_frame_inactivity * n : num_slots_per_period);
  LOG_D(NR_MAC,
        "%4d.%2d UL inactivity %d slots has_data %d SR %d tooHigh %d max_frame %d period %d n %d\n",
        frame,
        slot,
        diff,
        has_data,
        sched_ctrl->SR,
        high_inactivity,
        ulsch_max_frame_inactivity,
        num_slots_per_period,
        n);
  return has_data || sched_ctrl->SR || high_inactivity;
}
```

| execute 100 s | **has_data** | **sched_ctrl->SR** | **high_inactivity** |
| --- | --- | --- | --- |
| **max_frame 10** |  | 179 |  |
| **max_frame 0** |  | 1171 |  |

### 💡Idea: what frequence different with add config or not add **`--MACRLCs.[0].ulsch_max_frame_inactivity 0`**

compare part 1: 

```c
  // check scheduling request result, confidence_level == 0 is good
  if (uci_01->pduBitmap & 0x1) {
    if (uci_01->sr.sr_indication && uci_01->sr.sr_confidence_level == 0 && uci_01->ul_cqi >= 148) {
      // SR detected with SNR >= 10dB
      sched_ctrl->SR |= true;
      LOG_I(NR_MAC, "SR UE %04x ul_cqi %d\n", uci_01->rnti, uci_01->ul_cqi);
    }

  }
```

compare part 2:

```c
    const bool do_sched = nr_UE_is_to_be_scheduled(scc, 0, UE, sched_pusch->frame, sched_pusch->slot, nrmac->ulsch_max_frame_inactivity);
    LOG_I(NR_MAC,"pf_ul: do_sched UE %04x => %s\n",UE->rnti,do_sched ? "yes" : "no");
```

compare part 3:

```c
  LOG_I(PHY, "sr.sr_indication %d sr_confidence_level: %d\n",uci_pdu->sr.sr_indication, uci_pdu->sr.sr_confidence_level);
```

```c
  // check scheduling request result, confidence_level == 0 is good
  if (uci_01->pduBitmap & 0x1) {
    if (uci_01->sr.sr_indication && uci_01->sr.sr_confidence_level == 0 && uci_01->ul_cqi >= 148) {
      // SR detected with SNR >= 10dB
      sched_ctrl->SR |= true;
      LOG_I(NR_MAC, "SR UE %04x ul_cqi %d\n", uci_01->rnti, uci_01->ul_cqi);
    }

  }
```

```cpp
  /// maximum number of slots before a UE will be scheduled ULSCH automatically
  uint32_t ulsch_max_frame_inactivity;
```

| sum in run 100s | **max_frame 0** | **max_frame 10** |
| --- | --- | --- |
| **part 3: sr_indication 1  sr_confidence_level 0** | 3324 | 170 |
| part 1: SR UE 1cda ul_cqi | 1174 | 168 |
| part 2: pf_ul: do_sched UE 1cda => yes | 10235 | 481 |

## 💡Idea: Can I map the PNF generated and the VNF used? Are the total numbers the same?

### VNF

```c
  // check scheduling request result, confidence_level == 0 is good
  if (uci_01->pduBitmap & 0x1) {
    if (uci_01->sr.sr_indication && uci_01->sr.sr_confidence_level == 0 && uci_01->ul_cqi >= 148) {
      // SR detected with SNR >= 10dB
      sched_ctrl->SR |= true;
      LOG_I(NR_MAC, "(%d/%d)SR UE %04x ul_cqi %d\n",frame, slot, uci_01->rnti, uci_01->ul_cqi);
    }
```

### PNF

```c
  if(uci_pdu->sr.sr_indication == 1 && uci_pdu->sr.sr_confidence_level == 0)
  LOG_I(PHY, "(%d/%d) SR => yes\n",frame,slot);

```

![Untitled](Untitled%20106.png)

<aside>
💡 All mappings are correct. No miss between PNF and VNF in init()

</aside>

![Untitled](Untitled%20107.png)

|  | PNF | VNF |
| --- | --- | --- |
| **max_frame 10** | 538 | 228 |
| **max_frame 0** | 2853 | 1019 |

<aside>
💡 The problem is I don’t put the same condition before print log

</aside>

```
  if(uci_pdu->sr.sr_indication == 1 && uci_pdu->sr.sr_confidence_level == 0 && cqi>=148)
  LOG_I(PHY, "(%d/%d) SR => yes: %d\n",frame,slot,uci_stats->pucch0_positive_SR);
```

```c
  if (uci_01->pduBitmap & 0x1) {
    if (uci_01->sr.sr_indication && uci_01->sr.sr_confidence_level == 0 && uci_01->ul_cqi >= 148) {
      // SR detected with SNR >= 10dB
      sched_ctrl->SR |= true;
      LOG_I(NR_MAC, "(%d/%d)SR UE %04x ul_cqi %d\n",frame, slot, uci_01->rnti, uci_01->ul_cqi);
    }
  }
```

| sum in run 100s | PNF | VNF |
| --- | --- | --- |
| **max_frame 10** | 177 | 177 |
| **max_frame 0** | 1103 | 1103 |

## 💡Idea: Does UL_TTI total number increase by set **`--MACRLCs.[0].ulsch_max_frame_inactivity 0`**

- YES

| sum in run 100s | UL_TTI | **nr_fill_pucch** |
| --- | --- | --- |
| **max_frame 10** | 10642 | 6928 |
| **max_frame 0** | 13517 | 9208 |

## 💡Idea: Why

| UL_TTI | From VNF to PNF use | From VNF to PNF recv | Freq. |
| --- | --- | --- | --- |
| **max_frame 10** | 0.009447 s | 0.002042 s | 2~3 slot per Frame |
| **max_frame 0** | 0.009551 s | 0.002041 s | 4~5 slot per Frame |

[https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=bxoGHoSG30ykjC3lLpej&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=bxoGHoSG30ykjC3lLpej&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)

<aside>
💡 According to the measurement data, it is known that adjusting the parameter `--MACRLCs.[0].ulsch_max_frame_inactivity` increases the number of scheduler PUCCH PDU transmissions. Consequently, it also increases the number of UL_TTI.requests and thus triggers UCI.indication more frequently.

</aside>