# research XFAPI doc

Start Date: 2024/11/20
Summary: Deployment guidelines for the xFAPI component in O-RAN architecture, detailing installation steps, system requirements, and troubleshooting tips.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/11/26
SUM: 🗓️ Days Spent to Complete: 6

https://lf-o-ran-sc.atlassian.net/wiki/spaces/IAT/pages/176226489/xFAPI+Deployment+Guideline

[IAT xFAPI Deployment Guideline Nov 24.pdf](IAT_xFAPI_Deployment_Guideline_Nov_24.pdf)

## Focus on Modify OSC-DU High

- "Modify the Makefile :
Go to the /build/odu directory and make the following changes in the Makefile:"
- "Copy the wls_lib folder from the O-DU PHY repository:
After cloning, copy the wls_lib folder into the O-DU L2 source directory (/o-du-l2/src/):"
- "Build O-DU High in the o-du-l2/build/odu Directory:
make clean_odu PHY=INTEL_L1 MACHINE=BIT64 MODE=TDD
make odu PHY=INTEL_L1 MACHINE=BIT64 MODE=TDD"
- "Build cu_stub :
make clean_cu NODE=TEST_STUB MACHINE=BIT64 MODE=TDD
make cu_stub NODE=TEST_STUB MACHINE=BIT64 MODE=TDD"
- "Copy the [libxsm.so](http://libxsm.so) from /src/xSM_lib :
cp ../../src/xSM_lib/libxsm.so ../../bin/odu"

## Summary of xFAPI Deployment Guidelines

# Introduction

xFAPI is an intermediate component bridging L1 and L2 layers in O-RAN architecture, translating between FAPI and nFAPI interfaces. It consists of an API Translator and IPC Integrator, offering features like PDU statistics, debugging tools, and a monitoring dashboard.

# System Requirements

- Minimum: 3rd gen N series Intel CPU, ACC100 accelerator, 128GB RAM, 500GB storage
- Recommended: 4th Gen N series Intel CPU with Vran boost, 256GB RAM
- OS: Ubuntu 22.04 with Real-time kernel

# Installation Steps

## 1. Environment Setup

- Set up environment variables for FlexRAN and xFAPI
- Configure IPs for OSC-DU High and cu_stub

## 2. Prerequisites

- Install GCC 9.5, LKSCTP library, PCAP, ICX, Intel oneAPI, DPDK, and CMake

## 3. Component Installation

- FlexRAN: Clone repo and set up environment
- xSM Library: Unzip and deploy
- OSC Du-High: Clone repo, modify Makefile, copy wls_lib folder, build components
- xFAPI: Unzip and deploy

# Execution Sequence

1. FlexRAN
2. xFAPI
3. cu_stub
4. OSC DU-High

# Troubleshooting

Common issues addressed include library loading errors, parsing errors in FlexRAN, xSM lib loading issues in xFAPI, and socket binding failures in cu_stub.

# Additional Resources

The document mentions the availability of log files for detailed analysis, which can be configured in the xfapi_cfg.cfg file.