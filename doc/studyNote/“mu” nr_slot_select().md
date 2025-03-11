# “mu” nr_slot_select()

Start Date: 2024/04/23
Summary: The project involves analyzing the parameters of the NR slot selection function for 5G communication systems.
Status: Done
Assign: 陳奕全
Tags: Robert Task

![Untitled](Untitled%2093.png)

Subcarrier spacing (KHz)	

Subcarrier spacing, Number of OFDM symbols and slots

| Subcarrier spacing (KHz) | 15 | 30 | 60 | 120 | 240 |
| --- | --- | --- | --- | --- | --- |
| Symbol duration (µs) | 66.7 | 33.3 | 16.7 | 8.33 | 4.17 |
| CP duration (µS) | 4.7 | 2.3 | 1.2 (Normal CP), 4.13 (Extended CP) | 0.59 | 0.29 |
| Max. nominal system BW (MHz) | 50 | 100 | 100 (sub-6 GHz), 200 (mmwave) | 400 | 400 |
| FFT size (max.) | 4096 | 4096 | 4096 | 4096 | 4096 |
| Symbols per slot | 14 | 14 | 14 (normal CP), 12 (extended CP) | 14 | 14 |
| Slots per subframe | 1 | 2 | 4 | 8 | 16 |
| Slots per frame | 10 | 20 | 40 | 80 | 160 |
|  |  |  |  |  |  |

We need to check if we get the correct value. 

```c
int nr_slot_select(nfapi_nr_config_request_scf_t *cfg, int nr_frame, int nr_slot) {
  /* for FFD all slot can be considered as an uplink */
  int mu = cfg->ssb_config.scs_common.value,check_slot=0;
 ...
 ...
```

<aside>
👀 mu is **1, SCS is 30kHz**

</aside>

![Untitled](Untitled%2094.png)