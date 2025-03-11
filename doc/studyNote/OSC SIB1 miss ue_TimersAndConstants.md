# OSC SIB1 miss ue_TimersAndConstants

Start Date: 2024/05/30
Summary: Implementation and configuration of UE timers and constants for SIB1 messages in a 5G NR context.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

[5G NR Timers and Constants (wirelessbrew.com)](https://wirelessbrew.com/5g-nr/5g-nr-timers-and-constants/)

```c
[NR_RRC]   SIB1 decoded
[NR_RRC]   SIB1 should not be NULL and neither UE_Timers_Constants
```

## OAI

```c
  // ue-TimersAndConstants
  sib1->ue_TimersAndConstants = CALLOC(1,sizeof(struct NR_UE_TimersAndConstants));
  AssertFatal(sib1->ue_TimersAndConstants != NULL, "out of memory\n");
  sib1->ue_TimersAndConstants->t300 = NR_UE_TimersAndConstants__t300_ms400;
  sib1->ue_TimersAndConstants->t301 = NR_UE_TimersAndConstants__t301_ms400;
  sib1->ue_TimersAndConstants->t310 = NR_UE_TimersAndConstants__t310_ms2000;
  sib1->ue_TimersAndConstants->n310 = NR_UE_TimersAndConstants__n310_n10;
  sib1->ue_TimersAndConstants->t311 = NR_UE_TimersAndConstants__t311_ms3000;
  sib1->ue_TimersAndConstants->n311 = NR_UE_TimersAndConstants__n311_n1;
  sib1->ue_TimersAndConstants->t319 = NR_UE_TimersAndConstants__t319_ms400;
```

### Add new field in OSC fill SIB1 message

```c
    /* NR_UE_TimersAndConstants */
    DU_ALLOC(sib1Msg->ue_TimersAndConstants, sizeof(sib1Msg->ue_TimersAndConstants));
    sib1Msg->ue_TimersAndConstants->t300 = 3;
    sib1Msg->ue_TimersAndConstants->t301 = 3;
    sib1Msg->ue_TimersAndConstants->t310 = 6;
    sib1Msg->ue_TimersAndConstants->n310 = 6;
    sib1Msg->ue_TimersAndConstants->t311 = 1;
    sib1Msg->ue_TimersAndConstants->n311 = 0;
    sib1Msg->ue_TimersAndConstants->t319 = 3;
```