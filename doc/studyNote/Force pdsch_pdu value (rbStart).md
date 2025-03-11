# Force pdsch_pdu value (rbStart)

Start Date: 2024/05/30
Summary: Implementing a function to unpack the PDSCH PDU value for downlink transmission with specified parameters.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

```c
static uint8_t unpack_dl_tti_pdsch_pdu_rel15_value(void *tlv, uint8_t **ppReadPackedMsg, uint8_t *end)

// ...

	value->rbStart = 0;
	value->rbSize = 16;
	
	powerControlOffset = 0;
	powerControlOffsetSS = 0;
	
	value->maintenance_parms_v3.ldpcBaseGraph = 2;
	value->maintenance_parms_v3.tbSizeLbrmBytes = 57376;
}
```