# Timer T310 expired

Start Date: 2024/06/04
Summary: Timer T310 has expired, leading to a radio link failure that has not yet been handled.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

<aside>
💡 Can’t decode PBCH (MIB) → [**Error decoding PBCH!**](Error%20decoding%20PBCH!%201211009831438162bc60cfb6935f1e65.md)

</aside>

## OAI UE LOG

```
 六  04 21:34:49 [0m[93m[NR_RRC]   Timer T310 expired
 六  04 21:34:49 [0m
 六  04 21:34:49 Assertion (0) failed!
 六  04 21:34:49 In nr_rrc_handle_timers() /home/hpe/openairinterface5g/openair2/RRC/NR_UE/rrc_timers_and_constants.c:156
 六  04 21:34:49 Radio link failure! Not handled yet!
 六  04 21:34:49 
 六  04 21:34:49 Exiting execution
 六  04 21:34:49 /home/hpe/openairinterface5g/openair2/RRC/NR_UE/rrc_timers_and_constants.c:156 nr_rrc_handle_timers() Exiting OAI softmodem: _Assert_Exit_
```

## OAI UE code

```c
  bool t310_expired = nr_timer_tick(&timers->T310);
  if(t310_expired) {
    LOG_W(NR_RRC, "Timer T310 expired\n");
    // TODO
    // handle detection of radio link failure
    // as described in 5.3.10.3 of 38.331
    AssertFatal(false, "Radio link failure! Not handled yet!\n");
  }
```

## 5.3.10.3 of 38.331

![Untitled](Untitled%2061.png)

![Untitled](Untitled%2062.png)