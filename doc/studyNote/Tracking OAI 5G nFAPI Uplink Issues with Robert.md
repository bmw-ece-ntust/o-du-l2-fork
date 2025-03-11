# Tracking OAI 5G nFAPI Uplink Issues with Robert

Start Date: 2025/01/11
Summary: Tracking and addressing uplink issues in the OAI 5G nFAPI, focusing on frequent retransmissions and hardcoded numerology.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2025/01/17
SUM: 🗓️ Days Spent to Complete: 6

## Key Points Summary:

- Issue Origin: Discovered through GitLab merge request "Repair nFAPI in 5G" (#2999)
- Current Status:
    - Uplink (UL) traffic is functional but experiencing frequent retransmissions
    - Code is currently limited by hardcoded numerology
- Development Stage:
    - Previous demonstration was an early proof-of-concept
    - Integration testing is not yet complete
- Pending Actions:
    - Investigation needed for UL retransmission issues
    - Numerology hardcoding needs to be addressed

# Questions for Clarification

I came across the merge request on GitLab regarding "Repair nFAPI in 5G" ([link](https://gitlab.eurecom.fr/oai/openairinterface5g/-/merge_requests/2999)) and noticed your comment mentioning that the UL is not working properly yet.

If I recall correctly, when you completed the integration testing with USRP and the LiteOn RU, everything was functioning well. However, I noticed the merge request is still open and marked as "Ready to merge by members who can write to the target branch."

Could you share more details about the current status of nFAPI in OAI 5G? Specifically, are there still any unresolved issues with the UL functionality? From the website, it seems the problem arises in the FDD environment. Does the TDD mode work as expected, or does it face similar challenges?

Looking forward to your insights, too! 

# Reply from Robert

Robert Schmidt

[今天下午 5:03](https://openairinterface.slack.com/archives/D06MS6VMKQS/p1736758985359249?thread_ts=1736609747.558749&cid=D06MS6VMKQS)

UL traffic works, but has many more retransmissions and I want to find out why.also, the code is hardcoded to a specific numerology, which is not good and I never "completed the integration testing", what you saw last year was an early proof-of-concept