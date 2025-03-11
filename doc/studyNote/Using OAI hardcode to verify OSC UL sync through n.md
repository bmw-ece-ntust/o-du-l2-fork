# Using OAI hardcode to verify OSC UL sync. through nFAPI

Start Date: 2024/06/17
Summary: Verification of OSC UL synchronization through OAI hardcode using nFAPI.
Status: Done
Assign: 陳奕全

![Untitled](Untitled%20114.png)

<aside>
👀 
GCC version : 9.5.0
ubuntu 22

Distributor ID: Ubuntu
Description:    Ubuntu 22.04.4 LTS
Release:        22.04
Codename:       jammy

</aside>

## build

[[OAIOSC] O-DU nFAPI Installation Guide - HackMD](https://hackmd.io/ziGxQy05S0i1TdsZaYG0HQ#11-OAI-CU)

```bash
sudo echo "Build OAI CU"

cd /home/chen/quan/bmwlab_tony_cu_du/oai_cu/cmake_targets
sudo echo "Build OAI CU - step1"
# compile all of the code
./build_oai --gNB --nrUE -w SIMU

sudo echo "Build OAI CU- step2"
# sync up the format of F1AP
./f1ap_codec_mod.sh

sudo echo "Build OAI CU - step3"
# compile the part of RAN
cd /home/hpe/bmwlab_tony_cu_du/oai_cu/cmake_targets
./build_oai --gNB
```

![Untitled](Untitled%20115.png)

## Script

```bash
#!/bin/bash
HOME_PATH="/home/chen/quan"
wait_sec=15

Target_PATH="$HOME_PATH/NTUST-script"
L2_PATH="$HOME_PATH/mwnl-odu-at-oai-based-on-scf/l2"
LOG_PATH="$Target_PATH/LOG"
LOCKFILE="$Target_PATH/tmp-build_run.lock"
mkdir -p "$LOG_PATH"

# LOG File name
OAI_CU_LOG_FILE="$LOG_PATH/1-OAI_CU.log"
RIC_LOG_FILE="$LOG_PATH/2-RIC_STUB.log"
ODU_LOG_FILE="$LOG_PATH/3-OSC_DU.log"
PNF_LOG_FILE="$LOG_PATH/PNF-nfapi-fixes.log"
UE_LOG_FILE="$LOG_PATH/5-OAI_UEsim.log"
TCP_LOG_FILE="$LOG_PATH/TCPdump.pcap"

## CU & CU stub
CU_STUB_PATH="$L2_PATH/bin/cu_stub/cu_stub"
OAI_CU_PATH="$HOME_PATH/bmwlab_tony_cu_du/oai_cu/cmake_targets/ran_build/build/nr-softmodem"
CU_CONF="$HOME_PATH/bmwlab_tony_cu_du/oai_cu/targets/PROJECTS/GENERIC-NR-5GC/CONF/cu_fdd_gnb.sa.band66.fr1.106PRB.usrpb210.conf"

# OSC root
OSC_root_PATH="$L2_PATH/build/odu"
# OAI root
OAI_root_PATH="$HOME_PATH/openairinterface5g/cmake_targets/ran_build/build"
# RIC stub
RIC_STUB_PATH="$L2_PATH/bin/ric_stub/ric_stub"
# CU stub
CU_STUB_PATH="$L2_PATH/bin/cu_stub/cu_stub"
# OSC DU
ODU_PATH="$L2_PATH/bin/odu/odu"
# OAI gNB (OAI PNF)
PNF_CONF="$Target_PATH/ELSE/oaiL1.nfapi.usrpb210.conf"

# FID
PID_FILE="$LOG_PATH/PID_FILE_NAME"

# Check if the lock file exists
if [ -e $LOCKFILE ]; then
    echo "Another user is currently building and running the code. Please wait."
    exit 1
else
    bash "$Target_PATH/q"
    bash "$Target_PATH/exit"
    # Create the lock file
    touch $LOCKFILE
    touch $PID_FILE

    sudo ifconfig lo:RIC_STUB down
    sudo ifconfig lo:CU_STUB  down
    sudo ifconfig lo:ODU  down
    sudo ifconfig lo:OAI_CU down
    sudo ifconfig lo:RIC_STUB "192.168.130.80"
    sudo ifconfig lo:ODU  "192.168.130.81"
    sudo ifconfig lo:OAI_CU "192.168.130.83"
    sudo ifconfig lo:CU_STUB "192.168.130.82"
    
    # TCPdump
    # sudo echo "Start TCPdump..."
    # sudo tcpdump -i any -nn -w $TCP_LOG_FILE &

    # clean & compile OSC DU
    #cd /home/chen/quan/mwnl-odu-at-oai-based-on-scf/l2/build/odu
    #make clean_cu NODE=TEST_STUB MACHINE=BIT64 MODE=TDD
    #make cu_stub NODE=TEST_STUB MACHINE=BIT64 MODE=TDD
    cd $OSC_root_PATH
    make clean_odu MACHINE=BIT64 MODE=TDD NFAPI=YES
    make odu MACHINE=BIT64 MODE=TDD NFAPI=YES

    # clean & build OAI all
    cd $OAI_root_PATH
    sudo ninja nr-softmodem nr-uesoftmodem dfts ldpc params_libconfig rfsimulator

    cd ~

    # # echo "RUN OAI CU"
    # sudo stdbuf -oL $OAI_CU_PATH -O $CU_CONF --sa 2>&1 | ts &>$OAI_CU_LOG_FILE &
    # echo "RUN CU stub"
    sudo stdbuf -oL $CU_STUB_PATH 2>&1 | ts &>$RIC_LOG_FILE &
    sleep 1
    CU_PID=$(pgrep -o cu_stub)
    # echo $CU_PID
    echo -n $CU_PID >> $PID_FILE
    echo -n " " >> $PID_FILE
    # echo "RUN OSC RIC_STUB"
    sudo stdbuf -oL $RIC_STUB_PATH 2>&1 | ts &>$RIC_LOG_FILE &
    sleep 1
    RIC_PID=$(pgrep -o ric_stub)
    # echo $RIC_PID
    echo -n $RIC_PID >> $PID_FILE
    echo -n " " >> $PID_FILE

    # echo "RUN OSC DU"
    sudo stdbuf -oL $ODU_PATH 2>&1 | ts &>$ODU_LOG_FILE &
    sleep 2
    ODU_PID=$(pgrep -o odu)
    # echo $ODU_PID
    echo -n $ODU_PID >> $PID_FILE
    echo -n " " >> $PID_FILE

    # echo "RUN OAI PNF"
    pnf_cmd="$OAI_root_PATH/nr-softmodem -O $PNF_CONF --nfapi PNF --rfsim --rfsimulator.serveraddr server --sa"
    sudo stdbuf -oL $pnf_cmd 2>&1 | ts &>$PNF_LOG_FILE &
    sleep 3
    # echo "RUN OAI UEsim"
    ue_cmd="$OAI_root_PATH/nr-uesoftmodem -r 106 --numerology 1 --band 78 -C 3619200000 --sa --uicc0.imsi 001010000000001 --rfsim"
    sudo stdbuf -oL $ue_cmd 2>&1 | ts &>$UE_LOG_FILE &

    echo "The script automatically closes after $wait_sec seconds..."
    sleep $wait_sec
    bash "$Target_PATH/exit"
    bash "$Target_PATH/q"
    echo "Time to $wait_sec seconds..."
fi
```

<aside>
⛔ Resource not enough

</aside>