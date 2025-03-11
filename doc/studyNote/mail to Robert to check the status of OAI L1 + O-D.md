# mail to Robert to check the status of OAI L1 + O-DU HIGH integration.

Start Date: 2024/12/17
Summary: Checking the status of the OAI L1 + O-DU HIGH integration and addressing key challenges in message encoding.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: mail
Finish Date: 2024/12/24
SUM: 🗓️ Days Spent to Complete: 7

```markdown
Follow-Up on OAI L1 + O-DU HIGH Integration

Dear Robert,

I hope this email finds you well.
Could you please provide an update on the status of the OAI L1 + O-DU HIGH integration? 
If there are any recent findings or progress, I would greatly appreciate your insights.
Could you please share any updates on the progress or any key challenges that need to be addressed?
Looking forward to your response.

Best regards,
Ming
```

```markdown
Hi,

the status is not fundamentally different. Still, we cannot reliably
decode SIB1 at the UE. Radisys L2 does not encode the P7 messages for
PDCCH correctly, it seems.

So the key challenge is that L2 sends messages that are encoded
according to FAPI spec, which does not seem to be the case as of now.

Robert 
```

## Summary of OAI L1 + O-DU HIGH Integration Status:

### Current Status:

- No fundamental changes in the integration status
- Unable to reliably decode SIB1 at the UE level

### Key Issues:

- Radisys L2 appears to have incorrect PDCCH message encoding
- L2 messages are not properly following FAPI specification requirements

### Next Steps Required:

- Verify PDCCH message encoding compliance with FAPI specifications
- Investigate L2 message encoding implementation
- Address SIB1 decoding issues at UE level