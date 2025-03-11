# E2E temp

Summary: Integration process for the Morelink repeater in a 5G network, covering setup, configuration, testing procedures, and performance measures.
Status: Not started

<aside>

 ****🎯**Readme:**

1. Briefly summarize what information readers can expect from this note.
2. If you encounter an error you can refer to the [Troubleshooting note](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md).

🏷️**Reference:**

- [**Reference**](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md)
</aside>

This document provides an overview of the integration process for the Morelink repeater in a 5G network environment, covering setup, configuration, and testing procedures, along with status updates and performance measures.

## Topology

> CoreNetwork, gNB, RU, Fronthaul Gateway, IP, and NIC interface names should be included in the topology.
> 

![image.png](image%2093.png)

## Environment

---

### gNB

**Hardware:**

| Item | Info |
| --- | --- |
| CPU |  |
| Memory |  |
| Disk |  |
| NIC |  |
| Server Model |  |

**Software:**

| **Item** | **Info** |
| --- | --- |
| OS |  |
| Kernel |  |
| DPDK |  |
| LinuxPTP |  |
| gNB Branch |  |

### RU

| Item | Info |
| --- | --- |
| product_name |  |
| model id |  |
| firmware version |  |
| kernal |  |

## Current Status

| Item | Status |
| --- | --- |
| [Bring up RU](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Check RU PTP sync](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Bring up CN](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [PTP sync of gNB](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Bring up gNB](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [NG Setup](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [RU get on time packet from DU](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [DU get FH packet from RU](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Nemo handy setting](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [UE get mib and sib1 for DL sync](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [UE send preamble](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [DU get preamble](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [DU send RACH response(msg2)](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [UE get RACH response(msg2)](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [UE send RRC setup request(msg3)](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [DU get RRC setup request(msg3)](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [DU send RRC Set up(msg4)](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [UE get RRC Set up(msg4)](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [RRC setup complete](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [NAS registration](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [NAS identity request](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [NAS identity response](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Authenication request](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Authenication response](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [NAS Security mode command](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [NAS Security mode complete](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [UECapabilityEnquiry](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [UECapabilityInformation](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [AS SecurityModeCommand](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [AS SecurityModeComplete](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [RRCReconfiguration](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Registration accept](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [RRCReconfigurationComplete](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Registration complete](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [PDU session establish request](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [PDU session establish accept](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Internet access](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |
| [Performance](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) | ✅ |

## Access Method

<aside>

oaidur750

- IP : 192.168.8.43
- username : oai72
- pssword : bmwlab

**RU**

- console
    - username :
    - password :
- ssh (optional)
    - IP :
    - username :
    - ssh password :
    - root password :

**Core Network (Server name)**

- IP :
- username :
- pssword :
</aside>

## Configuration

| Parameters | Value |
| --- | --- |
| vlan id |  |
| pdsch/pusch eaxcid |  |
| prach eaxcid |  |
| dl/ul compression bits |  |
| DU MAC address |  |
| RU MAC address |  |
| DL center frequency |  |
| SSB center frequency |  |
| System Bandwidth |  |
| SCS |  |

## Run Application

<aside>

⚠️**Show us the correct steps only and list the debugging process to the Appendix. Hopefully, no one need to follow your Appendix to fix the bugs if your document is well-written.**

</aside>

## 1. RU Status

### Step1.1 Configure RU

- Put command here

```bash

```

### Step1.2 RU PTP Synchronization

- Put command here

```bash

```

## 2. Core Network and gNB Connection

### Step2.1 Configure CN IP

- Put command here

```bash

```

### Step2.2 Connect Data Network

- Put command here

```bash

```

### Step2.3 Bring up CN

- Put command here

```bash

```

## 3. Bring up gNB

### Step 3.1 Configure gNB

- Put command here

```bash

```

### Step 3.2 gNB PTP synchronization

- Put command here

```bash

```

### Step 3.3 Run gNB

- Put command here

```bash

```

## 4. Nemo handy setting

- Setting APN: Test INTERNET

![image.png](image%2094.png)

## 5. Result

<aside>

Put [gNB log](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md), Nemo log, and [PCAP file](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md) here.

</aside>

- [gNB log](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md)
- [Nemo log](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md)
- [PCAP file](Integration%20Morelink%20repeter%20E2E%2014a1009831438006b50bcfef11a049c0.md)

## 6. Performance measure

### Step 6.1 ping

- Put command here

```bash

```

### Step 6.2 iperf

- Put command here

```bash

```

### Step 6.3 YT stream

- Put picture

# Appendix

## Troubleshooting note

- Error record.

## MSC

### 5G NR SA Registration/Attach Call Flow

![image.png](image%2095.png)

![image.png](image%2096.png)