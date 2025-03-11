# OAI CU/DU High Low split

Start Date: 2024/10/05
Summary: Capturing F1AP messages between OAI CU and OAI DU while troubleshooting configuration issues and exploring Docker Compose setups.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/11/13
SUM: 🗓️ Days Spent to Complete: 39

<aside>
✅

[OAI split2 (OAI CU + OAI DU + OAI UE)](OAI%20split2%20(OAI%20CU%20+%20OAI%20DU%20+%20OAI%20UE)%201a2100983143808a8c3fcc9cf136143e.md) 

</aside>

<aside>
💡

Reference(idea) :

https://docs.sd-ran.org/master/sdran-in-a-box/docs/HW_Installation_oai_source.html

https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/F1AP/F1-design.md#how-to-run

</aside>

[docker-compose.yaml](docker-compose.yaml)

I want to capture the F1AP messages between the OAI CU and OAI DU. However, in my current setup where OAI VNF and OAI PNF are split, the messages are not transmitted via F1AP; they are sent directly.

From reference mention, I think I can find a config file in OAI is `du.band7.tm1.25PRB.conf` , then try to execute it in OAI CU/DU High Low split.

But I can’t find it, maybe I need to check with EURECOM’s Robert

<aside>
💡

ASK EURECOM’s Robert

</aside>

```
Hi, long time no see! Since returning to Taiwan, I've been continuing the integration of nFAPI. I'm currently facing issues with the RA MSG4 process from DU->CU->L1->UE.
In the final UE LOG, it shows "invalid CCCH." I want to observe and compare the F1AP messages when using OAI for CU, DU, L1, and UE altogether. However, I found that it uses direct communication (function name: dl_rrc_message_transfer_direct) instead of F1AP.
I watched the demo video you sent me during the F2F at the end of July. You had Split 2, 6, and 7.2, but it seemed to be using Docker containers. Therefore, my main question is: could you please teach me how to execute OAI Split 2 with CU/DU separation and see the F1AP messages?
Thank you very much!
```

```jsx

Robert Schmidt
Hi Ming, yes you can run with F1 and it's not too difficult. It is described here: https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/F1AP/F1-design.md#how-to-run
let me know if that helps
GitLabGitLab
doc/F1AP/F1-design.md · develop · oai / openairinterface5G · GitLab
Openairinterface 5G Wireless Implementation
```

## Directly execute

<aside>
💡

Reference: https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/F1AP/F1-design.md#how-to-run

</aside>

![{60A60E21-94E0-4B9D-9D11-D03754029F3E}.png](60A60E21-94E0-4B9D-9D11-D03754029F3E.png)

I tried following the steps, but I kept encountering unknown issues that caused the program to terminate. 

<aside>
💡

OAI Branch: `develop`

OAI tag: `2024.w44-3-ge8d8384e7e`

</aside>

```bash
sudo cmake_targets/ran_build/build/nr-softmodem --sa -O ci-scripts/conf_files/gnb-cu.sa.band78.106prb.conf
sudo cmake_targets/ran_build/build/nr-softmodem --sa -O ci-scripts/conf_files/gnb-du.sa.band78.106prb.rfsim.conf
```

### Error Logs:

[cu.log](cu.log)

[du.log](du.log)

```bash
Assertion (getCxt(instance)->gtpInst > 0) failed!
In F1AP_CU_task() /home/hpe/OnlyOAI/openairinterface5g/openair2/F1AP/f1ap_cu_task.c:124
Failed to create CU F1-U UDP listener
```

```bash
Assertion (gtpInst > 0) failed!
In F1AP_DU_task() /home/hpe/OnlyOAI/openairinterface5g/openair2/F1AP/f1ap_du_task.c:146
cannot create DU F1-U GTP module

Exiting execution
/home/hpe/OnlyOAI/openairinterface5g/openair2/F1AP/f1ap_du_task.c:146 F1AP_DU_task() Exiting OAI softmodem: _Assert_Exit_
```

<aside>
💡

Solution: modify config in setting IP adress

</aside>

```bash
  local_s_address = "192.168.130.83";
  remote_s_address = "192.168.130.81";
```

## Docker composed

However, running it through a YAML file in a container worked quite smoothly. The next step is to modify the code and try to print the messages I want (within the container).

```jsx
cd ~/oaicu_develope/openairinterface5g/ci-scripts/yaml_files/5g_f1_rfsimulator
docker-compose up -d
docker-compose config --services
```

```jsx
rvices
mysql
oai-amf
oai-smf
oai-upf
oai-ext-dn
oai-cu
oai-du
oai-nr-ue
```

```jsx
docker-compose logs oai-cu
docker-compose logs oai-du
```

[Docker Compose-du.log](Docker_Compose-du.log)

[Docker Compose-cu.log](Docker_Compose-cu.log)

## I need print more log

<aside>
⚠️

However, I can't execute it directly from the command line.

- I was able to execute it successfully using OAI's provided Docker Compose setup. I believe this is because it needs to configure some network settings and core network IP addresses. Attempting to execute directly results in an assertion error.
- Therefore, I think I can create a new image myself and modify the docker-compose.yaml file. This should allow me to see the logs I want to examine.
</aside>

---

## Ask Robert

I just tried again with the latest version of the OAI source code and followed the "how to run CU/DU split" instructions you provided. However, both the CU and DU execution encounter assertions. I think there might be settings required for the network card or environment, but I'm not sure how to configure them.

Additionally, I noticed that the F1-design.md file you provided mentions a Docker Compose method. I found the file at **`openairinterface5g/ci-scripts/yaml_files/5g_f1_rfsimulator`** and was able to see logs successfully by running it. However, this setup doesn’t allow me to print logs freely for debugging purposes. So, I'm currently trying to add my own **`printf()`** statements, build the image, and replace the YAML file to view the logs I need. But ideally, if I can set up the environment correctly and run it directly, that would be best. Could you guide me on which environment factors need adjustment?

### Reply

```bash

Robert Schmidt
  下午 3:08
did you read the assertions? it points you to wrong IP configuration
3:08
correctly configure the IP addresses in your config

F1 now works
3:33
it fials loading the USRP driver
3:33
or RFsim or whatever you try to do

is it possible you are missing --rfsim on the command line?
```