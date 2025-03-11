# [2] open problems - DL traffic: assertion

Start Date: 2024/04/10
Summary: Investigating and resolving issues related to DL traffic assertion and precoding parameters in a network environment.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全
Tags: Robert Task

- DL traffic: assertion. Generate traffic, try to understand why there is an assertion: one of the packets is not encoded properly (PDSCH?)

```bash
docker exec -it oai-ext-dn iperf3 -si1   # server, reports every 1s status
iperf3 -c 192.168.70.135 -B 10.0.0.33 -t 40 -R # TCP, reverse -> TCP in DL from server to client
iperf3 ... -t 40 -b1M -u # UDP in UL from client to server
```

[https://youtu.be/DUl4sPdZsT0](https://youtu.be/DUl4sPdZsT0)

```c
            AssertFatal(frame_parms->nb_antennas_tx > 1, "No precoding can be done with a single antenna port\n");
```

<aside>
🔥 **(rel15->precodingAndBeamforming.prg_size > 0) can’t be `True`**

or `pmi` will be set to **`pmi:47171` instead of `0`**.

Following the log, we can observe that **`frame_parms->nb_antennas_tx` is always set to `1`**.

</aside>

so, what is `pmi`?, and what is **`precodingAndBeamforming.prg_size`?**

<aside>
💡 `pmi` is **precoding matrix index 
Layer Precoding and Antenna port mapping
tx_layers 1-8 are mapped on antenna ports 1000-1007
The precoding info is supported by nfapi such as num_prgs, prg_size, prgs_list and pm_idx
The same precoding matrix is applied on prg_size RBs
pmi = prgs_list[rbidx/prg_size].pm_idx, rbidx =0,...,rbSize-1**

</aside>

**`rel15->precodingAndBeamforming.prg_size` will be : `0`, `5`, `9`,`11`, `43`, `275`**

### Here will set value to `pmi`

```c
// Precoding
    pdsch_pdu->precodingAndBeamforming.prg_size = pdsch_pdu->rbSize;
    LOG_I(NR_MAC, "sched_pdsch->pm_index:%d\n",sched_pdsch->pm_index);
    pdsch_pdu->precodingAndBeamforming.prgs_list[0].pm_idx = sched_pdsch->pm_index;
```

But when I print here, I observe that always is `0` .

```bash
**1712837728.819613 [NR_MAC]   (259/6)sched_pdsch->pm_index:0
1712837728.820689 [NR_MAC]   (259/7)sched_pdsch->pm_index:0**
```

```
avril 11 14:15:28 [0m1712837728.833252 [PHY]   (259/6) rel15->precodingAndBeamforming.prg_size:106
avril 11 14:15:28 [0m1712837728.833253 [PHY]   [0]:0
avril 11 14:15:28 [0m1712837728.833254 [PHY]   (int)rb/prg_size:0
avril 11 14:15:28 [0m1712837728.833255 [PHY]   pmi:0
avril 11 14:15:28 [0m1712837728.833663 [PHY]   ant:0,l_symbol:1
avril 11 14:15:28 [0m1712837728.833665 [PHY]   (259/7) rel15->precodingAndBeamforming.prg_size:106
avril 11 14:15:28 [0m1712837728.833666 [PHY]   [0]:14677
avril 11 14:15:28 [0m1712837728.833666 [PHY]   (int)rb/prg_size:0
avril 11 14:15:28 [0m1712837728.833667 [PHY]   pmi:14677
```

In each time show this `50`will abort

`rel15->precodingAndBeamforming.prg_size:50` → `pmi:5466` 

Maybe not true, because sometime will abort in `prg_size:106` 

Check pdsch_pdu_rel15

`pack_dl_tti_pdsch_pdu_rel15_value`

`unpack_dl_tti_pdsch_pdu_rel15_value`

error unpack pm_idx value

![In VNF pack `pm_idx`is always 0, however PNF got incorrect `pm_idx`???](Untitled%2065.png)

In VNF pack `pm_idx`is always 0, however PNF got incorrect `pm_idx`???

![Untitled](Untitled%2066.png)

![**`prg_size` will from `0` change to `106` and `pmi` also will change to can’t except value.**](Untitled%2067.png)

**`prg_size` will from `0` change to `106` and `pmi` also will change to can’t except value.**

<aside>
💡 **Robert Schmidt**

[](https://ca.slack-edge.com/T5NGZN2BA-UBGEW7W21-2a6e25498af5-48)

[下午 3:55](https://openairinterface.slack.com/archives/D06MS6VMKQS/p1712843755106849)

we only have SISO so far, so it's not that puzzling that we don't have anything

but very good, please continue. we will come to adding some tests to verify this works, but we don't have it, so maybe you want to help yourself by writing one function that dumps the comment, and you call it on packing and unpacking and compare with diff ("poor man's" test)

</aside>

![Untitled](Untitled%2068.png)

<aside>
✅ I revise this condition to ensure logical consistency.

</aside>

![Ping](Untitled%2069.png)

Ping