# [4] Frame number wraps around from 1023→0

Start Date: 2024/04/15
Summary: Fix the issue of frame number wrapping around from 1023 to 0 in the system by revising the timing window condition in the function is_nr_p7_request_in_window.
Status: Done
Assign: 陳奕全
Tags: Robert Task

- there is also still this problem as in the logs below. It is when the frame number wraps around from 1023->0. Can you please fix that?

```
4227569564255 [N] 3510384192: is_nr_p7_request_in_window: [20478] dl_tti_request is out of window 0 (delta:20478) [max:30]
4227569564306 [N] 3510384192: is_nr_p7_request_in_window: [20478] tx_request is out of window 0 (delta:20478) [max:30]
4227569564312 [I] 3510384192: pnf_handle_tx_data_request: pnf_handle_tx_data_request() TX_DATA_REQUEST Request is outside of window REQ:SFN_SLOT:0 CURR:SFN_SLOT:20478

```

I think we can solve this problem by revise timing_window condition. see patch:

[Correcting the logic for timing_window judgment. (c9e29064) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/c9e29064f8192497e8ac98528273516293f77f5c)

Original code

```c
	else if(current_sfn_slot_dec + NFAPI_MAX_SFNSLOTDEC <= recv_sfn_slot_dec + timing_window){ //checking for wrap
		in_window = 1;
		//NFAPI_TRACE(NFAPI_TRACE_NOTE, "[%d] %s is in window %d\n", current_sfn_slot_dec, name, recv_sfn_slot_dec);
	}
	
```

> The original condition is **illogical**. To make a correct judgment on whether the current SFN/slot is in the window or not, it is necessary to **revise this condition**. Otherwise, an error of SFN 1023 → 0 will occur.
> 

Error Fix

```c
	else if(current_sfn_slot_dec <= NFAPI_MAX_SFNSLOTDEC + recv_sfn_slot_dec + timing_window){ //checking for wrap
		in_window = 1;
		//NFAPI_TRACE(NFAPI_TRACE_NOTE, "[%d] %s is in window %d\n", current_sfn_slot_dec, name, recv_sfn_slot_dec);
	}
```

---

**Robert Schmidt**

can you please explain why this would solve it? In my opinion, this is always true:

```
current_sfn_slot_dec <= NFAPI_MAX_SFNSLOTDEC
```

because the current frame/slot number cannot be bigger than maximum, so the condition you put is also always wrong. But we cannot detect whene it is outside of the window

## CHECK

```c
// return 1 if in window
// return 0 if out of window

uint8_t is_nr_p7_request_in_window(uint16_t sfn,uint16_t slot, const char* name, pnf_p7_t* phy)
{
	uint32_t recv_sfn_slot_dec = NFAPI_SFNSLOT2DEC(sfn,slot);
	uint32_t current_sfn_slot_dec = NFAPI_SFNSLOT2DEC(phy->sfn,phy->slot);
	printf("p7_msg_sfn: %d, p7_msg_slot: %d, phy_sfn:%d , phy_slot:%d \n",sfn,slot,phy->sfn,phy->slot);
	uint8_t in_window = 0;
	uint8_t timing_window = phy->_public.slot_buffer_size;
	if(current_sfn_slot_dec <= recv_sfn_slot_dec + timing_window){
		in_window = 1;
	}
	else if(current_sfn_slot_dec + NFAPI_MAX_SFNSLOTDEC <= recv_sfn_slot_dec + timing_window){ //checking for wrap
		in_window = 1;
	}
  
	else
	{ 	
		NFAPI_TRACE(NFAPI_TRACE_NOTE, "[%d] %s is out of window %d (delta:%d) [max:%d]\n", 
		current_sfn_slot_dec, name, recv_sfn_slot_dec,  \
		(current_sfn_slot_dec - recv_sfn_slot_dec), timing_window);
		
	}//Need to add more cases
	
	return in_window;
}
```

PNF Log:

```
avril 15 14:24:03 p7_msg_sfn: 1023, p7_msg_slot: 19, phy_sfn:1023 , phy_slot:17 
avril 15 14:24:03 p7_msg_sfn: 0, p7_msg_slot: 0, phy_sfn:1023 , phy_slot:18 
avril 15 14:24:03 16784992077 [N]  887563840: is_nr_p7_request_in_window: [20478] dl_tti_request is out of window 0 (delta:20478) [max:30]
avril 15 14:24:03 p7_msg_sfn: 0, p7_msg_slot: 0, phy_sfn:1023 , phy_slot:18 
avril 15 14:24:03 16784992108 [N]  887563840: is_nr_p7_request_in_window: [20478] tx_request is out of window 0 (delta:20478) [max:30]

...
avril 15 14:23:09 p7_msg_sfn: 0, p7_msg_slot: 0, phy_sfn:1023 , phy_slot:19 
avril 15 14:23:09 16730919329 [N]  887563840: is_nr_p7_request_in_window: [20479] dl_tti_request is out of window 0 (delta:20479) [max:30]
avril 15 14:23:09 p7_msg_sfn: 0, p7_msg_slot: 0, phy_sfn:1023 , phy_slot:19 
avril 15 14:23:09 16730919394 [N]  887563840: is_nr_p7_request_in_window: [20479] tx_request is out of window 0 (delta:20479) [max:30]

```

We try to revise `is_nr_p7_request_in_window.` make the logic remains correct every time SFN/SLOT is refreshed.

[Add an additional 'in window' condition. (13d8c745) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/13d8c74512ecbf041bbeac77311b7bb8531c39f2)

```c
uint8_t is_nr_p7_request_in_window(uint16_t sfn,uint16_t slot, const char* name, pnf_p7_t* phy)
{
	uint32_t recv_sfn_slot_dec = NFAPI_SFNSLOT2DEC(sfn,slot);
	uint32_t current_sfn_slot_dec = NFAPI_SFNSLOT2DEC(phy->sfn,phy->slot);
	printf("p7_msg_sfn: %d, p7_msg_slot: %d, phy_sfn:%d , phy_slot:%d \n",sfn,slot,phy->sfn,phy->slot);
	uint8_t timing_window = phy->_public.slot_buffer_size;
	if(abs(recv_sfn_slot_dec - current_sfn_slot_dec) > timing_window){
		if(abs(NFAPI_MAX_SFNSLOTDEC + recv_sfn_slot_dec - current_sfn_slot_dec) > timing_window){
			return 0;
			NFAPI_TRACE(NFAPI_TRACE_NOTE, "[%d] %s is out of window %d (delta:%d) [max:%d]\n", current_sfn_slot_dec, name, recv_sfn_slot_dec,  (current_sfn_slot_dec - recv_sfn_slot_dec), timing_window);
		}
	}
	return 1;
}
```

We've reconsidered all conditions and rewritten the function accordingly. At present, the issue should no longer occur.

[Correcting the logic for timing_window judgment. (7d17e257) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/7d17e25766dc8579a32f0e31262ecaee40f0ccca)