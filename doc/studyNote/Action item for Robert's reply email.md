# Action item for Robert's reply email

Start Date: 2024/10/21
Summary: Action item involves addressing Msg4 decoding issues in the integration of OAI L1 and OSC L2.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/21
SUM: 🗓️ Days Spent to Complete: 0

### Summary

1. **Integration Progress in Robert**:
    - The integration of OAI L1 and OSC L2 using FAPI is ongoing.
    - The team is currently forwarding P7 messages but facing challenges, including FAPI message encoding issues and difficulties with the `wls_lib`.
2. **Slack Channel**:
    - There is an internal Slack channel between Radisys and OSA, but most discussions occur in private chats between key personnel.
3. **Repository Information**:
    - The team is using the OAI RAN repository (`oai/openairinterface5G`), but they are not as advanced in the integration process.
4. **Msg4 Decoding Issue**:
    - Ming and Richard are working on OAI UE, OAI L1, and OSC L2. They encountered issues decoding Msg4 due to different ASN.1 encoders used by OAI and OSC.
    - The message reaches the CU, and decoding issues might arise from DU decoding attempts. However, according to TS 38.473, DUs should forward the message transparently.

### Action Items

1. **Msg4 Decoding**:
    - Clarify the exact issue with Msg4 decoding.
    - Review logs and error messages for further analysis.
    - Check if OSC DU attempts to decode the message unnecessarily and explore ways to forward it transparently, as suggested in TS 38.473.
    - Trace OAI source code in `dl_rrc_message_transfer` → [Trace OAI dl_rrc_message_transfer](Trace%20OAI%20dl_rrc_message_transfer%2012610098314380e89639c87d5243b362.md)