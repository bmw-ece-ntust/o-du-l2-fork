# split2&6 (OAI CU+ OSC DU High+ nFAPI + OAI Layer1 + OAI UE)

Start Date: 2025/02/22
Summary: Development and testing of OAI CU, OSC DU, and OAI UE functionalities with a focus on high-performance configurations.
Status: In progress
Assign: Ming 咚咚 [銘鴻]
Tags: PIN

![image.png](image%20115.png)

<aside>
📃

Reference Link and Notes : [doc/nfapi.md · develop · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/nfapi.md?ref_type=heads)

[OAI split2 (OAI CU + OAI DU + OAI UE)](OAI%20split2%20(OAI%20CU%20+%20OAI%20DU%20+%20OAI%20UE)%201a2100983143808a8c3fcc9cf136143e.md) 

[OAI split6 (OAI VNF+ nFAPI + OAI PNF + OAI UE)](OAI%20split6%20(OAI%20VNF+%20nFAPI%20+%20OAI%20PNF%20+%20OAI%20UE)%201a2100983143800db810f9d6e5ff856c.md) 

[OAI split2&6 (OAI CU+ OAI DU High+ nFAPI + OAI Layer1 + OAI UE)](OAI%20split2&6%20(OAI%20CU+%20OAI%20DU%20High+%20nFAPI%20+%20OAI%20Lay%201a210098314380feac8ef2b589dd2dbd.md) 

</aside>

<aside>
⚠️

Current issues: [UE Segmentation fault after Generating RRCSetupComplete](UE%20Segmentation%20fault%20after%20Generating%20RRCSetupCom%2012110098314381d1adf3f719885a3bf8.md) 

</aside>

# Source

[](https://gitlab.eurecom.fr/oai/openairinterface5g)

### Branch: `develop`

### Tag: `2025.w07`

# Config files

---

# Command

---

## Build

```css
## IF execute first time in your PC you need to add `-I`
sudo ./build_oai -c --ninja --nrUE --gNB -g

# ninja 
sudo ninja nr-softmodem nr-uesoftmodem dfts ldpc params_libconfig rfsimulator
```

## OAI CU

```css
sudo ~/oaicu_develope/openairinterface5g/cmake_targets/ran_build/build/nr-softmodem --sa -O ci-scripts/conf_files/gnb-cu.sa.band78.106prb.conf
```

```css
sudo ~/oaicu_develope/openairinterface5g/cmake_targets/ran_build/build/nr-softmodem --sa -O /home/hpe/NTUST-script/CONFIG/gnb-cu.sa.band78.106prb.conf
```

## OSC DU

```css

sudo ~/o-du-l2/bin/odu/odu 
```

## OAI Layer1

```bash
sudo NFAPI_TRACE_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb-pnf.band78.rfsim.conf --nfapi PNF --rfsim 

#or directly path:

sudo ~/openairinterface5g/cmake_targets/ran_build/build/nr-softmodem -O /home/hpe/OnlyOAI/openairinterface5g/targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb-pnf.band78.rfsim.conf --nfapi PNF --rfsim --rfsimulator.serveraddr server --sa
```

## OAI UE

```bash
sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --uicc0.imsi 001010000000001 --rfsim 
```

# PCAP (Only SCTP)

---

[(split2&6) OAI CU + OSC DU High + OAI Layer1 + OAI UE.pcap]((split26)_OAI_CU__OSC_DU_High__OAI_Layer1__OAI_UE%201.pcap)

# Logs

---

[1-OAI_CU.log](1-OAI_CU%201.log)

[3-OSC_DU.log](3-OSC_DU.log)

[4-OAI_PNF.log](4-OAI_PNF.log)

[5-OAI_UE.log](5-OAI_UE.log)

## Wireshark

---

### NGAP

![image.png](image%20116.png)

### F1AP

![image.png](image%20117.png)

### NFAPI P5

![image.png](image%20118.png)

### NFAPI P7

![image.png](image%20119.png)

# Known Issues

---

PDSCH to HARQ feedback time (3) needs to be higher than DURATION_RX_TO_TX (3)

```
 三  07 14:43:23 [0m[PHY]   RAR-Msg2 decoded
 三  07 14:43:23 [0m[32m[NR_MAC]   [RAPROC][280.19] RA-Msg3 transmitted
 三  07 14:43:23 [0m
 三  07 14:43:23 Assertion (feedback_ti > GET_DURATION_RX_TO_TX(&mac->ntn_ta)) failed!
 三  07 14:43:23 In nr_ue_process_dci_dl_10() /home/hpe/OnlyOAI/openairinterface5g/openair2/LAYER2/NR_MAC_UE/nr_ue_procedures.c:915
 三  07 14:43:23 PDSCH to HARQ feedback time (3) needs to be higher than DURATION_RX_TO_TX (3).
 三  07 14:43:23 
```

Comparing the F1AP differences between OAI DU and OSC DU implementations

![image.png](image%20120.png)

F1AP packet capture content under OAI DU architecture

![image.png](image%20121.png)

F1AP packet capture content under OSC DU architecture

![image.png](image%20122.png)