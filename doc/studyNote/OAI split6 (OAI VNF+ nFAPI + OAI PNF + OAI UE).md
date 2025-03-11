# OAI split6 (OAI VNF+ nFAPI + OAI PNF + OAI UE)

Start Date: 2025/02/22
Summary: The project involves the implementation and testing of OAI split6, integrating VNF, PNF, nFAPI, and UE components.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: PIN
Finish Date: 2025/02/22
SUM: 🗓️ Days Spent to Complete: 0

<aside>
📃

Reference Link: [doc/nfapi.md · develop · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/nfapi.md?ref_type=heads)

</aside>

# Source

[](https://gitlab.eurecom.fr/oai/openairinterface5g)

### Branch: `develop`

### Tag: `2025.w07`

# Config files

---

[gnb-vnf.sa.band78.106prb.nfapi.conf](gnb-vnf.sa.band78.106prb.nfapi.conf)

[gnb-pnf.band78.rfsim.conf](gnb-pnf.band78.rfsim.conf)

# Command

---

## Build

```css
## IF execute first time in your PC you need to add `-I`
sudo ./build_oai -c --ninja --nrUE --gNB -g

# ninja 
sudo ninja nr-softmodem nr-uesoftmodem dfts ldpc params_libconfig rfsimulator
```

## VNF

```css
sudo NFAPI_TRACE_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb-vnf.sa.band78.106prb.nfapi.conf --nfapi VNF
```

## PNF

```bash
sudo NFAPI_TRACE_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-NR-5GC/CONF/gnb-pnf.band78.rfsim.conf --nfapi PNF --rfsim 
```

## UE

```bash
sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --uicc0.imsi 001010000000001 --rfsim 
```

# PCAP (Only SCTP)

---

[OAI split6 (OAI VNF + OAI PNF + nFAPI + OAI UE).pcap](OAI_split6_(OAI_VNF__OAI_PNF__nFAPI__OAI_UE).pcap)

# Logs

---

[PNF-nfapi-fixes.log](PNF-nfapi-fixes.log)

[UE-nfapi-fixes.log](UE-nfapi-fixes.log)

[VNF-nfapi-fixes.log](VNF-nfapi-fixes.log)

[(split2)OAI CU + OAI DU + OAI UE.pcap]((split2)OAI_CU__OAI_DU__OAI_UE.pcap)