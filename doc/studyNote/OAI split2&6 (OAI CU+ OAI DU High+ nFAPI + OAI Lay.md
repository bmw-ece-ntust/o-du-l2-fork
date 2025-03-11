# OAI split2&6 (OAI CU+ OAI DU High+ nFAPI + OAI Layer1 + OAI UE)

Start Date: 2025/02/22
Summary: Implementation and configuration of OAI CU and DU systems for high-performance nFAPI and Layer1 communication.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: PIN
Finish Date: 2025/02/22
SUM: 🗓️ Days Spent to Complete: 0

![image.png](image%20123.png)

<aside>
📃

Reference Link and Notes : [doc/nfapi.md · develop · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/nfapi.md?ref_type=heads)

[OAI split2 (OAI CU + OAI DU + OAI UE)](OAI%20split2%20(OAI%20CU%20+%20OAI%20DU%20+%20OAI%20UE)%201a2100983143808a8c3fcc9cf136143e.md) 

[OAI split6 (OAI VNF+ nFAPI + OAI PNF + OAI UE)](OAI%20split6%20(OAI%20VNF+%20nFAPI%20+%20OAI%20PNF%20+%20OAI%20UE)%201a2100983143800db810f9d6e5ff856c.md) 

</aside>

# Source

[](https://gitlab.eurecom.fr/oai/openairinterface5g)

### Branch: `develop`

### Tag: `2025.w07`

# Config files

---

[gnb-cu.sa.band78.106prb.conf](gnb-cu.sa.band78.106prb%201.conf)

[gnb-du.sa.band78.106prb.rfsim.conf](gnb-du.sa.band78.106prb.rfsim%201.conf)

[gnb-pnf.band78.rfsim.conf](gnb-pnf.band78.rfsim%201.conf)

[gnb-vnf-du.sa.band78.106prb.nfapi.conf](gnb-vnf-du.sa.band78.106prb.nfapi.conf)

[ue.conf](ue.conf)

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
sudo cmake_targets/ran_build/build/nr-softmodem --sa -O ci-scripts/conf_files/gnb-cu.sa.band78.106prb.conf
```

## OAI DU

```css
sudo NFAPI_TRACE_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb-vnf-du.sa.band78.106prb.nfapi.conf --nfapi VNF
```

## OAI Layer1

```bash
sudo NFAPI_TRACE_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb-pnf.band78.rfsim.conf --nfapi PNF --rfsim 
```

## OAI UE

```bash
sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --uicc0.imsi 001010000000001 --rfsim
```

# PCAP (Only SCTP)

---

[OAI_split2,6RFsim,UE.pcap](OAI_split26RFsimUE.pcap)

[nFAPI_TCPdump.pcap](nFAPI_TCPdump.pcap)

[nFAPI_TCPdump.pcap](nFAPI_TCPdump%201.pcap)

### NGAP

![image.png](image%20124.png)

### F1AP

![image.png](image%20125.png)

### SCTP

![image.png](image%20126.png)

### nFAPI

![image.png](image%20127.png)

# Logs

---

[VNF-CU-nfapi.log](VNF-CU-nfapi.log)

[VNF-DU-nfapi.log](VNF-DU-nfapi.log)

[PNF-nfapi.log](PNF-nfapi.log)

[UE-nfapi.log](UE-nfapi.log)

## RTT & Iperf

---

```bash
docker exec -it oai-ext-dn iperf3 -si1   # server, reports every 1s status
iperf3 -c 192.168.70.135 -B 12.1.1.132 -t 40 -R # TCP, reverse -> TCP in DL from server to client
iperf3 ... -t 40 -b1M -u # UDP in UL from client to server

iperf3 -B 10.0.0.2 -c 192.168.70.135 -t 5 -R
```

```bash
ping 192.168.70.135 -I oaitun_ue1
```

![image.png](image%20128.png)

![image.png](image%20129.png)

![image.png](image%20130.png)