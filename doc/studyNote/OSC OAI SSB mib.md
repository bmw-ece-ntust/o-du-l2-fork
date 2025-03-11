# OSC OAI SSB mib

Start Date: 2024/05/06
Summary: Development and implementation of the OSC OAI SSB MIB project, including research, coding, and data analysis related to 5G NR technology.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

# Revise OSC DU High

![image.png](image%2086.png)

```c
void setMibPdu(uint8_t *mibPdu, uint32_t *val, uint16_t sfn)
{
   *mibPdu |= (((uint8_t)(sfn << 2)) & MIB_SFN_BITMASK); // MIB_SFN_BITMASK = 0xFC
   *val = (mibPdu[0] << 24 | mibPdu[1] << 16 | mibPdu[2] << 8);
   DU_LOG("\nDEBUG  -->  LWR_MAC: MIB PDU %x", *val);
}
```

```c
void setMibPdu(uint8_t *mibPdu, uint32_t *val, uint16_t sfn)
{
   *mibPdu |= ((uint8_t)((sfn >> 4) & 0x3f) << 1);
   *val = (mibPdu[2] << 24 | mibPdu[1] << 16 | mibPdu[0] << 8);
   DU_LOG("\nDEBUG  -->  LWR_MAC: MIB PDU %x", *val);
}
```

![Untitled](Untitled%20117.png)

![[5G-NR Master Information Block (MIB) - wirelessbrew.com](https://wirelessbrew.com/5g-nr/5g-nr-master-information-block-mib/)](Untitled%20118.png)

[5G-NR Master Information Block (MIB) - wirelessbrew.com](https://wirelessbrew.com/5g-nr/5g-nr-master-information-block-mib/)

## OAI OSC MIB value (23bits)

|  | OAI | OSC |
| --- | --- | --- |
| **systemFrameNumber** | sfn (6bits) | sfn (6bits) → wrong order |
| **subCarrierSpacingCommon (SCS)** | 1 | 1 |
| ssb-SubcarrierOffset | 0 | 0 |
| dmrs-TypeA-Position | 0 (pos2) | 0 |
| pdcch-ConfigSIB1- ControlResourceSetZero (CORESET) Zero | 12 | 0 |
| pdcch-ConfigSIB1- searchSpaceZero | 0 | 0 |
| **cellBarred** | 1 (notBarred) | 1 |
| intraFreqReselection | 1 (notAllowed) | 1 |

![image.png](image%2087.png)

| 0 | 1x | 2x | 3x | 4x | 5x | 6x | 1 |
| --- | --- | --- | --- | --- | --- | --- | --- |

| 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 |
| --- | --- | --- | --- | --- | --- | --- | --- |

| 0 | 0 | 0 | 0 | 0 | 1 | 1 | 0 |
| --- | --- | --- | --- | --- | --- | --- | --- |
- SFN Consists of 10 Bits and the 6 most significant bits (MSB) of the 10-bit System Frame Number (SFN) are defined in MIB .
- UE gets the 4 LSB of the SFN which are conveyed in the PBCH transport block as part of channel coding (i.e. outside the MIB encoding)

| SFN | 0~1023 total 10bits, 6bits for MIB, 4 bits for PBCH channel coding |
| --- | --- |
|  |  |
|  |  |

![Untitled](Untitled%20119.png)

Flag → 1  PHY generates the timing PBCH bits, see Table 3-91, where the bchPayload has 24 bits

![Untitled](Untitled%20120.png)

38.331

![Untitled](Untitled%20121.png)

![Untitled](Untitled%20122.png)

![Untitled](Untitled%20123.png)

```c
void setMibPdu(uint8_t *mibPdu, uint32_t *val, uint16_t sfn)
{
   *mibPdu |= (((uint8_t)(sfn << 2)) & MIB_SFN_BITMASK); // MIB_SFN_BITMASK = 0xFC
   *val = (mibPdu[0] << 24 | mibPdu[1] << 16 | mibPdu[2] << 8);
   DU_LOG("\nDEBUG  -->  LWR_MAC: MIB PDU %x", *val);
}
```

| 5 | 6 | 7 | 8 | 9 | 0 | 1 | 1 |
| --- | --- | --- | --- | --- | --- | --- | --- |

```c
uint8_t BuildMibPdu()
{
   uint8_t ret = RFAILED;
   BCCH_BCH_Message_t *bcchMsg;
   asn_enc_rval_t encRetVal;        /* Encoder return value */
   while(true)
   {
...
      xer_fprint(stdout, &asn_DEF_BCCH_BCH_Message, bcchMsg);
      memset(encBuf, 0, ENC_BUF_MAX_LEN);
      encBufSize = 0;
      encRetVal = uper_encode(&asn_DEF_BCCH_BCH_Message, 0,
            bcchMsg, PrepFinalEncBuf, encBuf);
      printf("\nencbufSize:%d\n", encBufSize);

...

}
```

```c
int encode_MIB_NR(NR_BCCH_BCH_Message_t *mib, int frame, uint8_t *buf, int buf_size)
{
  DevAssert(mib != NULL && mib->message.choice.mib->systemFrameNumber.buf != NULL);
  uint8_t sfn_msb = (uint8_t)((frame >> 4) & 0x3f); // 0011 1111
  *mib->message.choice.mib->systemFrameNumber.buf = sfn_msb << 2;

  asn_enc_rval_t enc_rval = uper_encode_to_buffer(&asn_DEF_NR_BCCH_BCH_Message, NULL, mib, buf, buf_size);
  AssertFatal(enc_rval.encoded > 0, "ASN1 message encoding failed (%s, %lu)!\n", enc_rval.failed_type->name, enc_rval.encoded);
  LOG_D(NR_RRC, "Encoded MIB for frame %d sfn_msb %d, bits %lu\n", frame, sfn_msb, enc_rval.encoded);
  return (enc_rval.encoded + 7) / 8;
}
```

| 1 | 2 | 3 | 4 | 5 | 6 | 0 | 1 |
| --- | --- | --- | --- | --- | --- | --- | --- |

```c
static int encode_mib(NR_BCCH_BCH_Message_t *mib, frame_t frame, uint8_t *buffer, int buf_size)
{
  int encode_size = 3;
  AssertFatal(buf_size >= encode_size, "buffer of size %d too small, need 3 bytes\n", buf_size);
  int encoded = encode_MIB_NR(mib, frame, buffer, encode_size);
  DevAssert(encoded == encode_size);
  return encode_size;
}
```

```c
    // get MIB every 8 frames
    if(((slotP == 0) && (frameP & 7) == 0) ||
       gNB->first_MIB) {
      int mib_sdu_length = encode_mib(cc->mib, frameP, cc->MIB_pdu, sizeof(cc->MIB_pdu));

      // flag to avoid sending an empty MIB in the first frames of execution since gNB doesn't get at the beginning in frame 0 slot 0
      gNB->first_MIB = false;

      LOG_D(MAC,
            "[gNB %d] Frame %d : MIB->BCH  CC_id %d, Received %d bytes\n",
            module_idP,
            frameP,
            CC_id,
            mib_sdu_length);
    }

    uint32_t mib_pdu = (*(uint32_t *)cc->MIB_pdu) & ((1 << 24) - 1);
```

![1000014973.jpg](1000014973.jpg)

1234567890
3456789000
0012345678

1234567800

| OAI CU (guess) | blank | array index[2] | array index[1] | array index[0] |
| --- | --- | --- | --- | --- |
| OSC DU | array index[0] ooooooxx | array index[1] | array index[2] | blank |
| OAI Layer1 | blank | array index[2] | array index[1] | array index[0] ooooooxx |

array index[0] is include timing related `PBCH` payload

<aside>
🗣 [Question: Why `OAI` reorder by one line code, how to do it?](Question%20Why%20OAI%20reorder%20by%20one%20line%20code,%20how%20to%20%20121100983143818397a3c4ea0d65ee73.md) 
`uint32_t mib_pdu = (*(uint32_t *)cc->MIB_pdu) & ((1 << 24) - 1);`

</aside>

## Final status

```c
void setMibPdu(uint8_t *mibPdu, uint32_t *val, uint16_t sfn)
{
   *mibPdu |= (((uint8_t)(sfn >> 4)) & 0x3F) << 2; //0xFC 1111 1100
   *val = (mibPdu[2] << 24 | mibPdu[1] << 16 | mibPdu[0] << 8);
   DU_LOG("\nDEBUG  -->  LWR_MAC: MIB PDU %x", *val);
}
```

```c
void setMibPdu(uint8_t *mibPdu, uint32_t *val, uint16_t sfn)
{
   DU_LOG("\nDEBUG  -->  sfn %x", sfn);
   DU_LOG("\nDEBUG  -->  *mibPdu %x", *mibPdu);
   *mibPdu |= ((uint8_t)((sfn >> 4) & 0x1f) << 1); // 0xFC 1111 1100
   DU_LOG("\nDEBUG  -->  LWR_MAC: mibPdu %x", (uint8_t)((sfn >> 4) & 0x3f) << 2);
   *val = (mibPdu[2] << 24 | mibPdu[1] << 16 | mibPdu[0] << 8);
   DU_LOG("\nDEBUG  -->  LWR_MAC: MIB PDU %x", *val);
}
```

```c
void setMibPdu(uint8_t *mibPdu, uint32_t *val, uint16_t sfn)
{
   DU_LOG("\nDEBUG  -->  sfn %x", sfn);
   DU_LOG("\nDEBUG  -->  *mibPdu %x", *mibPdu);
   *mibPdu |= ((uint8_t)((sfn >> 4) & 0x3f) << 1);
   DU_LOG("\nDEBUG  -->  LWR_MAC: mibPdu %x", (uint8_t)((sfn >> 4) & 0x3f) << 2);
   *val = (mibPdu[2] << 24 | mibPdu[1] << 16 | mibPdu[0] << 8);
   DU_LOG("\nDEBUG  -->  LWR_MAC: MIB PDU %x", *val);
}
```

```c
static uint8_t pack_dl_tti_ssb_pdu_rel15_value(void *tlv, uint8_t **ppWritePackedMsg, uint8_t *end)
{
  NFAPI_TRACE(NFAPI_TRACE_DEBUG, "Packing ssb. \n");
  nfapi_nr_dl_tti_ssb_pdu_rel15_t *value = (nfapi_nr_dl_tti_ssb_pdu_rel15_t *)tlv;
  if (!(push16(value->PhysCellId, ppWritePackedMsg, end) && push8(value->BetaPss, ppWritePackedMsg, end)
        && push8(value->SsbBlockIndex, ppWritePackedMsg, end) && push8(value->SsbSubcarrierOffset, ppWritePackedMsg, end)
        && push16(value->ssbOffsetPointA, ppWritePackedMsg, end) && push8(value->bchPayloadFlag, ppWritePackedMsg, end)
        && push8((value->bchPayload >> 24) & 0xff, ppWritePackedMsg, end)
        && push8((value->bchPayload >> 16) & 0xff, ppWritePackedMsg, end) 
        && push8((value->bchPayload >> 8) & 0xff, ppWritePackedMsg, end)
        && push8(0, ppWritePackedMsg, end) &&
        // TODO add Tx Power Info
        push8(0, ppWritePackedMsg, end) && push8(0, ppWritePackedMsg, end)
        && push16(value->precoding_and_beamforming.num_prgs, ppWritePackedMsg, end)
        && push16(value->precoding_and_beamforming.prg_size, ppWritePackedMsg, end)
        && push8(value->precoding_and_beamforming.dig_bf_interfaces, ppWritePackedMsg, end))) {
    return 0;
  }
```

```
mai 14 10:49:06 1715676546.059320 [NR_RRC]   frame: 0
mai 14 10:49:06 [0m1715676546.059326 [NR_RRC]   sfn_msb << 2: 0
mai 14 10:49:06 [0m1715676546.059328 [NR_RRC]   cc->MIB_pdu: 0 0 0
mai 14 10:49:06 [0m1715676546.059337 [NR_RRC]   cc->MIB_pdu: 1 6 6
mai 14 10:49:06 [0m68953234442 [N] 3061827136: vnf_nr_p7_read_dispatch_message: reallocing rx buffer 76
mai 14 10:49:07 1715676547.146121 [NR_RRC]   frame: 8
mai 14 10:49:07 [0m1715676547.146135 [NR_RRC]   sfn_msb << 2: 0
mai 14 10:49:07 [0m1715676547.146137 [NR_RRC]   cc->MIB_pdu: 1 6 6
mai 14 10:49:07 [0m1715676547.146149 [NR_RRC]   cc->MIB_pdu: 1 6 6
mai 14 10:49:07 [0m1715676547.187266 [NR_RRC]   frame: 16
mai 14 10:49:07 [0m1715676547.187279 [NR_RRC]   sfn_msb << 2: 4
mai 14 10:49:07 [0m1715676547.187281 [NR_RRC]   cc->MIB_pdu: 1 6 6
mai 14 10:49:07 [0m1715676547.187290 [NR_RRC]   cc->MIB_pdu: 3 6 6
mai 14 10:49:07 [0m1715676547.227435 [NR_RRC]   frame: 24
mai 14 10:49:07 [0m1715676547.227448 [NR_RRC]   sfn_msb << 2: 4
mai 14 10:49:07 [0m1715676547.227449 [NR_RRC]   cc->MIB_pdu: 3 6 6
mai 14 10:49:07 [0m1715676547.227459 [NR_RRC]   cc->MIB_pdu: 3 6 6
mai 14 10:49:07 [0m1715676547.263168 [NR_RRC]   frame: 32
mai 14 10:49:07 [0m1715676547.263180 [NR_RRC]   sfn_msb << 2: 8
mai 14 10:49:07 [0m1715676547.263181 [NR_RRC]   cc->MIB_pdu: 3 6 6
mai 14 10:49:07 [0m1715676547.263190 [NR_RRC]   cc->MIB_pdu: 5 6 6
```