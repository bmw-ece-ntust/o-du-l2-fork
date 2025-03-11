# Fill DL/UL k0 in config.request

Start Date: 2024/05/31
Summary: Implement the configuration changes for DL/UL k0 in the config.request file, including special case handling and code modifications.
Status: Done
Assign: 陳奕全
Tags: OSC Integration

Remove Fill tlvs tag: FAPI_DL_GRIDSIZE_TAG、FAPI_UL_GRID_SIZE_TAG from Config.request
Write the special case for 0x1004 and 0x1009

```c
if (tlv.tl.tag == NFAPI_NR_CONFIG_DL_K0_TAG){
  push16(NFAPI_NR_CONFIG_DL_K0_TAG, ppWritePackedMsg, end) && push16(5 * sizeof(uint16_t), ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end); // Padding
}
else if (tlv.tl.tag == NFAPI_NR_CONFIG_UL_K0_TAG){
  push16(NFAPI_NR_CONFIG_UL_K0_TAG, ppWritePackedMsg, end) && push16(5 * sizeof(uint16_t), ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end)
	&& push16(0, ppWritePackedMsg, end); // Padding
}
```