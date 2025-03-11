# Fix timming window

Start Date: 2024/04/23
Summary: Fixing the timing window logic in the is_nr_p7_request_in_window function to improve accuracy and handle edge cases.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Robert Task

<aside>
💡

Refactor is_nr_p7_request_in_window function for clarity and efficiency

The function now utilizes simpler variable names and logic to determine if a given NR P7 request falls within the timing window.

The logic for determining if a request is within the timing window is as follows:

- The function calculates the absolute difference between the current and received SFN slots, taking into account the possibility of wraparound.
- If the absolute difference is greater than half of the maximum SFN slot value, it subtracts this difference from the maximum SFN slot value to get the actual difference.
- The function then checks if this difference is less than or equal to the specified timing window. If it is, the request is considered to be within the window.

Additionally, the commit updates the function signature to return a boolean value for better readability and consistency.

Changes made:

- Simplified variable names for readability
- Improved logic for handling wraparound scenarios
- Updated function signature to return a boolean value
</aside>

Yes, however, applying this condition alone sometimes results in incorrect judgment (delta :-2 also show `is out of window`) because current_sfn_slot_dec is occasionally smaller than recv_sfn_slot_dec. Therefore, we have readjusted the content of the function as follows:

```c
uint8_t is_nr_p7_request_in_window(uint16_t sfn,uint16_t slot, const char* name, pnf_p7_t* phy)
{
	uint32_t recv_sfn_slot_dec = NFAPI_SFNSLOT2DEC(sfn,slot);
	uint32_t current_sfn_slot_dec = NFAPI_SFNSLOT2DEC(phy->sfn,phy->slot);
	// printf("p7_msg_sfn: %d, p7_msg_slot: %d, phy_sfn:%d , phy_slot:%d \n",sfn,slot,phy->sfn,phy->slot);
	uint8_t timing_window = phy->_public.slot_buffer_size;
	if(
		(((NFAPI_MAX_SFNSLOTDEC + recv_sfn_slot_dec - current_sfn_slot_dec) % NFAPI_MAX_SFNSLOTDEC)  > timing_window) &&
		(((NFAPI_MAX_SFNSLOTDEC + current_sfn_slot_dec - recv_sfn_slot_dec) % NFAPI_MAX_SFNSLOTDEC)  > timing_window)
	){
		NFAPI_TRACE(NFAPI_TRACE_NOTE, "[%d] %s is out of window %d (delta:%d) [max:%d]\n", current_sfn_slot_dec, name, recv_sfn_slot_dec,  (current_sfn_slot_dec - recv_sfn_slot_dec), timing_window);
		return 0;
	}
	return 1;
}
```

We've just reconsidered all conditions and rewritten the function accordingly. At present, the issue should no longer occur.commit: [https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/7d17e25766dc8579a32f0e31262ecaee40f0ccca](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/7d17e25766dc8579a32f0e31262ecaee40f0ccca)

```
uint8_t is_nr_p7_request_in_window(uint16_t sfn,uint16_t slot, const char* name, pnf_p7_t* phy)
{
    uint32_t recv_sfn_slot_dec = NFAPI_SFNSLOT2DEC(sfn,slot);
    uint32_t current_sfn_slot_dec = NFAPI_SFNSLOT2DEC(phy->sfn,phy->slot);
    // printf("p7_msg_sfn: %d, p7_msg_slot: %d, phy_sfn:%d , phy_slot:%d \n",sfn,slot,phy->sfn,phy->slot);
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

**GitLab**

[**Correcting the logic for timing_window judgment. (7d17e257) · Commits · oai / openairinterface5G · GitLab**](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/7d17e25766dc8579a32f0e31262ecaee40f0ccca)

Openairinterface 5G Wireless Implementation

**Robert Schmidt**

[下午 3:59](https://openairinterface.slack.com/archives/D06MS6VMKQS/p1713189545276619)

let's discuss the function next time. One problem is that it is hardcoded for numerology=1.

[4:00](https://openairinterface.slack.com/archives/D06MS6VMKQS/p1713189634266809)

and the numerology aside, you might write:

```
(NFAPI_MAX_SFNSLOTDEC + current_sfn_slot_dec - recv_sfn_slot_dec) % NFAPI_MAX_SFNSLOTDEC

```

should always be positive and capture both cases

---

`current_sfn_slot_dec` is phy’s SFN/slot 

`recv_sfn_slot_dec` is P7 message’s SFN/slot

![Untitled](Untitled%2014.png)

## Only **`ul_tti_req`** and **`ul_dci_request` and `tx_data`** delta>0

![Untitled](Untitled%2015.png)

![Untitled](Untitled%2016.png)

```
Correcting the logic for timing_window judgment.
Judge whether recv_sfn_slot_dec has transitioned from 1023 to 0, and also consider delta>0 as out of window. Delta should be <= 0.
recv_sfn_slot_dec is the unpacked result.
```

<aside>
👀 I think in case of `recv_sfn_slot_dec` < `current_sfn_slot_dec` if delta is smaller than timing_window(30) is ok. Because `is_nr_p7_request_in_window` is just a judgement to check this P7 message whether “OUTSIDE OF TRANSMIT BUFFER WINDOW” and whether store into buffer.

</aside>

I think It depends on the unpacked SFN/SL and the current SFN/SL. We also consider that even if delta is between -30 and 30, it can be stored into the buffer for use. Therefore, the conditional statement should remain unchanged, and it has been modified to return a boolean.