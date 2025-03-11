# BubbleRAN-training course

Start Date: 2024/07/29
Summary: Training course for BubbleRAN focusing on setup, configuration, and execution of projects involving Kubernetes and xApps.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 Reference:
[https://bubbleran.com/docs/tutorials/studio/labs/prerequisites](https://bubbleran.com/docs/tutorials/studio/labs/prerequisites)

</aside>

- Different ID
- Different name

- Run C-plan in BubbleRAN
    - see log
    - pcap in wireshark
- see the graph in grafarna
- modify the configuration to only measure the xAPP
- OSC RIC
- GCP
- modify config to USRP
- 

## define command line use name

```bash
# bubbleran cli aliases
alias cli=br-t9s.cli
alias brc=br-t9s.cli
alias t9s-cli=br-t9s.cli
alias br-cli=br-t9s.cli
alias br-ctl=br-t9s.cli
alias t9s-ctl=br-t9s.cli

# bubbleran cdk aliases
alias cdk=br-t9s.cdk
alias t9s-cdk=br-t9s.cdk
alias br-cdk=br-t9s.cdk
```

- If we prepare a Kubernetes environment, and if I get the config file from BubbleRAN, similar to a license, I can deploy the BubbleRAN.
- BubbleRAN supports executing an Xapp outside of BubbleRAN. we need to set IP router to correct IP and porr.
- The TDD pattern will influence the uplink and downlink throughput.
- We can see packets sent to 8.8.8.8 successfully in Wireshark to ensure the UE C-plane and U-plane are successfully set up.

## Connect to Bubble RAN server

![Untitled](Untitled%2045.png)