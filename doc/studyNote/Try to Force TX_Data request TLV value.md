# Try to Force TX_Data.request TLV value

Start Date: 2024/05/28
Summary: Force the TX_Data.request TLV value for testing payloads in the context of nFAPI integration.
Status: Done
Assign: Ming 咚咚 [銘鴻]

# Thought nFAPI, we can force send we want payload to test

<aside>
💡 Currently, we can’t decode SIB1 when integrate OSC DU High and OAI Layer 1

</aside>

```c
  LOG_I(PHY,"pNfapiMsg->TLVs[i].tag:%d\n",pNfapiMsg->TLVs[i].tag);
  LOG_I(PHY,"pNfapiMsg->TLVs[i].length:%d\n",pNfapiMsg->TLVs[i].length);
    switch(pNfapiMsg->TLVs[i].tag) {
      case 0: {
        if (!pullarray32(ppReadPackedMsg, pNfapiMsg->TLVs[i].value.direct,
                         sizeof(pNfapiMsg->TLVs[i].value.direct) / sizeof(uint32_t),
                         (pNfapiMsg->TLVs[i].length+3)/4, end))
          return 0;
        // *pNfapiMsg->TLVs[i].value.direct = 34242660;
        // LOG_I(PHY,"pNfapiMsg->TLVs[i].value.direct:%lx\n",*pNfapiMsg->TLVs[i].value.direct);
				pNfapiMsg->PDU_length = 141;
        int out[33] = {
            34242660, 1082130440, 37748736, 2419754481,
            5689476, 1888888320, 100545995, 1056952,
            3091283968, 4160, 1622688064, 1073741840,
            56688704, 473321544, 12602503, 1761738784,
            1712967369, 436232788, 3380465108, 3325643200,
            443518377, 1882340762, 2269315512, 498081856,
            3733735552, 12484, 0, 0, 0, 0, 0, 0, 0
        };
        for(int j=0;j<33;j++) {
          pNfapiMsg->TLVs[i].value.direct[j] = out[j];
          LOG_I(PHY,"(%ld) pNfapiMsg->TLVs[i].value.direct[%d]:%lx\n",sizeof(pNfapiMsg->TLVs[i].value.direct) / sizeof(uint32_t),j,pNfapiMsg->TLVs[i].value.direct[j]);
        }
```