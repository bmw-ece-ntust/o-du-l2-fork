# OAI Pack/Unpack PDUSize Issues

Start Date: 2024/10/09
Summary: Addressing issues with PDUSize discrepancies in the pack/unpack functions within OAI related structures.
Status: padding
Assign: Ming 咚咚 [銘鴻]

<aside>
💡

Although unit tests have confirmed that there are errors with PDUSize after pack/unpack, causing the values to be different, tracing the code and unit tests with random value fills can confirm that this variable is not used in OAI PNF and OAI UE. Therefore, it is not a major issue, and this problem is considered to have low priority for fixing.

- Some issues have been discovered where the structure is declared as uint32_t but pack uses push16(), and unpack uses pull16(), yet it is forcibly cast to (uint16_t *) → Various solutions have been attempted to adjust to consistent types, but none have been able to resolve the problem!
</aside>

## Struct

```c
typedef struct {
  uint16_t PDUType;
  uint32_t PDUSize;

```

## Pack function

```c
static uint8_t pack_dl_tti_request_body_value(void *tlv, uint8_t **ppWritePackedMsg, uint8_t *end)
{
  nfapi_nr_dl_tti_request_pdu_t *value = (nfapi_nr_dl_tti_request_pdu_t *)tlv;
  uintptr_t msgHead = (uintptr_t)*ppWritePackedMsg;
  if (!push16(value->PDUType, ppWritePackedMsg, end))
    return 0;
  printf("[pack_dl_tti_request_body_value] PDUSize: %d\n", value->PDUSize);
```

## Unpack function

```c
static uint8_t unpack_dl_tti_request_body_value(uint8_t **ppReadPackedMsg, uint8_t *end, void *msg) {
  nfapi_nr_dl_tti_request_pdu_t *value = (nfapi_nr_dl_tti_request_pdu_t *)msg;

  if(!(pull16(ppReadPackedMsg, &value->PDUType, end) &&
       pull16(ppReadPackedMsg, (uint16_t *) &value->PDUSize, end)))
    return 0;
  LOG_I(PHY, "unpack_dl_tti_request_body_value: PDUType %d, PDUSize %ld\n", value->PDUType, value->PDUSize);
```