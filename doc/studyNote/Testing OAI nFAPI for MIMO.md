# Testing OAI nFAPI for MIMO

Start Date: 2024/05/27
Summary: Testing OAI nFAPI for MIMO to evaluate performance and connectivity between virtual and physical network functions.
Status: Done
Assign: 陳奕全
Tags: Robert Task

<aside>
👀

- can you please test with RFsim and OAI UE for MIMO? this should help us iron out some problems so we can later test with 7.2 fronthaul. Specifically, you find a docker-compose file for this: ci-scripts/yaml_files/5g_rfsimulator_2x2/docker-compose.yaml
</aside>

<aside>
〰️ Reference: openairinterface5g/ci-scripts/conf_files/gnb.sa.band78.106prb.rfsim.2x2.conf、openairinterface5g/ci-scripts/conf_files/nrue.uicc.conf

</aside>

## Write config file for nFAPI MIMO testing

# Config Files

[nrue.uicc.nfapi.conf](nrue.uicc.nfapi.conf)

[oaiL1.nfapi.rfsim.2x2.conf](oaiL1.nfapi.rfsim.2x2.conf)

[rcc.band78.tm1.106PRB.nfapi.2x2.conf](rcc.band78.tm1.106PRB.nfapi.2x2.conf)

# Command

VNF:

```
sudo LD_LIBRARY_PATH=./ NFAPI\_TRACE\_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.2x2.conf --nfapi VNF --sa --log\_config.global\_log\_options wall\_clock --emulate-l1

```

PNF:

```
sudo LD_LIBRARY_PATH=./ NFAPI\_TRACE\_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/oaiL1.nfapi.rfsim.2x2.conf --nfapi PNF --rfsim --rfsimulator.serveraddr server --log\_config.global\_log\_options wall\_clock --sa

```

UE:

```
sudo ./nr-uesoftmodem -O ../../../ci-scripts/conf_files/nrue.uicc.nfapi.conf --sa --rfsim -r 106 --numerology 1 --band 78 -C 3619200000 --ue-nb-ant-tx 2 --uicc0.imsi 001010000000001 --ue-nb-ant-rx 2 --uecap_file /opt/oai-nr-ue/etc/uecap.xml

```

# LOG

[VNF_MIMO.log](VNF_MIMO.log)

[UE_MINO.log](UE_MINO.log)

[PNF_MINO.log](PNF_MINO.log)

---

## Write config file for nFAPI MIMO testing

### rcc.band78.tm1.106PRB.nfapi.2x2.conf

openairinterface5g/targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.2x2.conf

--nfapi VNF --sa --rfsim --emulate-l1 --log_config.global_log_options level,nocolor,time

```bash
cd ~/openairinterface5g/cmake\_targets/ran\_build/build
sudo LD_LIBRARY_PATH=./ NFAPI\_TRACE\_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/rcc.band78.tm1.106PRB.nfapi.2x2.conf --nfapi VNF --sa --log\_config.global\_log\_options wall\_clock --emulate-l1
```

### oaiL1.nfapi.rfsim.2x2.conf

openairinterface5g/targets/PROJECTS/GENERIC-LTE-EPC/CONF/oaiL1.nfapi.rfsim.2x2.conf

--sa -O --nfapi PNF --rfsim --log_config.global_log_options level,nocolor,time

```bash
cd ~/openairinterface5g/cmake\_targets/ran\_build/build
sudo LD_LIBRARY_PATH=./ NFAPI\_TRACE\_LEVEL=info ./nr-softmodem -O ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/oaiL1.nfapi.rfsim.2x2.conf --nfapi PNF --rfsim --rfsimulator.serveraddr server --log\_config.global\_log\_options wall\_clock --sa
```

### nrue.uicc.nfapi.conf

not success yet

sudo ./nr-uesoftmodem -O ../../../ci-scripts/conf_files/nrue.uicc.nfapi.conf --sa --rfsim -r 106 --numerology 1 --band 78 -C 3619200000 --ue-nb-ant-tx 2 --uicc0.imsi 001010000000001 --ue-nb-ant-rx 2 --uecap_file /opt/oai-nr-ue/etc/uecap.xml --rfsimulator.serveraddr 192.168.71.140

--sa --rfsim -r 106 --numerology 1 --band 78 -C 3319680000 --ue-nb-ant-tx 2 --uicc0.imsi 208990100001100 --ue-nb-ant-rx 2 --uecap_file /opt/oai-nr-ue/etc/uecap.xml --rfsimulator.serveraddr 192.168.71.140 --log_config.global_log_options level,nocolor,time

openairinterface5g/ci-scripts/conf_files/nrue.uicc.nfapi.conf

```bash
cd ~/openairinterface5g/cmake\_targets/ran\_build/build
#sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --sa --uicc0.imsi 001010000000001 --rfsim
sudo ./nr-uesoftmodem -O ../../../ci-scripts/conf_files/nrue.uicc.nfapi.conf --sa --rfsim -r 106 --numerology 1 --band 78 -C 3619200000 --ue-nb-ant-tx 2 --uicc0.imsi 001010000000001 --ue-nb-ant-rx 2 --uecap_file /opt/oai-nr-ue/etc/uecap.xml --rfsimulator.serveraddr 192.168.71.140 --log_config.global_log_options level,nocolor,time
```

```bash
cd ~/openairinterface5g/cmake\_targets/ran\_build/build
#sudo ./nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --sa --uicc0.imsi 001010000000001 --rfsim
sudo ./nr-uesoftmodem -O ../../../ci-scripts/conf_files/nrue.uicc.nfapi.conf --sa --rfsim -r 106 --numerology 1 --band 78 -C 3619200000 --ue-nb-ant-tx 2 --uicc0.imsi 001010000000001 --ue-nb-ant-rx 2 --uecap_file /opt/oai-nr-ue/etc/uecap.xml --log_config.global_log_options level,nocolor,time
```

```bash
sudo ./nr-uesoftmodem -O ../../../ci-scripts/conf_files/nrue.uicc.nfapi.conf --sa --rfsim -r 106 --numerology 1 --band 78 -C 3619200000 --ue-nb-ant-tx 2 --uicc0.imsi 001010000000001 --ue-nb-ant-rx 2 --uecap_file /opt/oai-nr-ue/etc/uecap.xml
```

### Outcome

PNF got number of antenna 2 from VNF

![Untitled](Untitled%2030.png)

UE not successfully connected yet

![Untitled](Untitled%2031.png)

UE decoded successfully

![Untitled](Untitled%2032.png)

UE detail log: