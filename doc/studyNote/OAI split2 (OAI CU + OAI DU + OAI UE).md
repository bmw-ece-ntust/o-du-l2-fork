# OAI split2 (OAI CU + OAI DU + OAI UE)

Start Date: 2025/02/22
Summary: A project focused on the implementation and configuration of OAI split2 components, including CU, DU, and UE, with details on build commands and log files.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: PIN
Finish Date: 2025/02/22
SUM: 🗓️ Days Spent to Complete: 0

<aside>
📃

Reference Note: [OAI CU/DU High Low split](OAI%20CU%20DU%20High%20Low%20split%201211009831438174bad5e4fed49746f1.md) 

</aside>

# Config files

---

[gnb-du.sa.band78.106prb.rfsim.conf](gnb-du.sa.band78.106prb.rfsim.conf)

[gnb-cu.sa.band78.106prb.conf](gnb-cu.sa.band78.106prb.conf)

# Command

---

## Build

```css
## IF execute first time in your PC you need to add `-I`
sudo ./build_oai -c --ninja --nrUE --gNB -g

# ninja 
sudo ninja nr-softmodem nr-uesoftmodem dfts ldpc params_libconfig rfsimulator
```

## CU

```css
sudo cmake_targets/ran_build/build/nr-softmodem --sa -O ci-scripts/conf_files/gnb-cu.sa.band78.106prb.conf
```

## DU

```bash
sudo cmake_targets/ran_build/build/nr-softmodem --sa -O ci-scripts/conf_files/gnb-du.sa.band78.106prb.rfsim.conf --rfsim
```

## UE

```bash
sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --sa --uicc0.imsi 001010000000001 --rfsim
```

# PCAP (Only SCTP)

---

[split2_tcpdump(SCTP).pcap](split2_tcpdump(SCTP).pcap)

# Logs

---

[split2_cu.log](split2_cu.log)

[split2_du.log](split2_du.log)

[split2_ue.log](split2_ue.log)