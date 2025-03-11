# Trace:Fill MSG4 PDU

Start Date: 2024/10/08
Summary: Fill and analyze the MSG4 PDU to resolve decoding issues in the UE related to the TBS value.
Status: Done
Assign: 陳奕全
Finish Date: 2024/10/14
SUM: 🗓️ Days Spent to Complete: 6

# MSG4 Procedure

![image.png](image%2010.png)

<aside>
☑️

1. Check the msg4TxPduLen
2. Check the msg4Pdu
3. Check the msg3Pdu

[**TX_PAYLOAD_HDR_LEN**](TX_PAYLOAD_HDR_LEN%201211009831438147b076edaeb93695da.md)

</aside>

In function **`fillMsg4Pdu` first get the `msg4TxPduLen` then fillMsg4DlData and fillMacCe(Mac ce identities LCID:CRI), finally invoke `macMuxPdu` to Forming Mux Pdu**

msg4TxPduLen is 116

msg4PduLen is 103

MAX_CRI_SIZE is 6

## Check MSG4 PDU byte → No problem

1. CRI bytePos:

![image.png](image%2011.png)

1. CCCH bytePos

![image.png](image%2012.png)

1. padding

![image.png](image%2013.png)

---

<aside>
💡

After continuous trial and error, we finally found the reason why the UE couldn't decode msg4. The issue was due to an error in the UE when receiving the msg4 DLSCH Configuration (PDSCH), causing an incorrect `TBS` value (we're still investigating the root cause). Interestingly, both SIB1 and RAR (MSG2) use the same function, but they do not encounter this issue.So, I hard-coded the TBS to the correct value(116 Bytes) on the OAI UE side, and the OAI UE was able to successfully decode msg4 and complete the RRC connection.

</aside>

If we use hard-code in UE TBS

![image.png](image%2014.png)

UE can decode MSG4….

![image.png](image%2015.png)

<aside>
💡

So we need to find out why UE got the wrong TBS from MSG4 PDSCH PDU.

Maybe can trace

1. Check OAI L1 how to forward the PDSCH message
2. Check PDSCH message between VNF and PNF (nFAPI)
</aside>