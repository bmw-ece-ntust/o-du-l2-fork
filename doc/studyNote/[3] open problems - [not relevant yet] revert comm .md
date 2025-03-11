# [3] open problems - [not relevant yet] revert commit for rfsim slowdown

Start Date: 2024/04/17
Summary: Reverting a commit related to rfsim slowdown to address various problems in PNF functionality.
Status: Done
Assign: Ming 咚咚 [銘鴻]

- [not relevant yet] revert commit for rfsim slowdown (`git revert -n f79d48e607371219c92ac2ca4bf3465b3846622d`) blocks PNF, why?

---

<aside>
💡 Main solution:
Modify `UL_TTI.request` source code and add new `cp_function`

</aside>

## Problem lists

- [x]  PRACH buffer full
    - Maybe UL_TTI is too late
- [x]  Didn’t get **[`NGAP`] response in LOG**
    - In Wireshark it have response
    
    ![Untitled](Untitled%2091.png)
    
- [ ]  Show error log about : buffer_index occupied - free it
    - I think this is a filled buffer that wasn't used, and now I need to fill it again.

In `PNF` print error log

```
avril 22 15:02:25 [0m1713790945.044723 [PHY]   searching for PRACH in 643.19 prach_index 0=> 367.19
avril 22 15:02:25 [0m1713790945.044732 [PHY]   searching for PRACH in 643.19 prach_index 1=> 801.19
avril 22 15:02:25 [0m1713790945.044734 [PHY]   searching for PRACH in 643.19 prach_index 2=> 869.19
avril 22 15:02:25 [0m1713790945.044735 [PHY]   searching for PRACH in 643.19 prach_index 3=> 871.19
avril 22 15:02:25 [0m1713790945.044736 [PHY]   searching for PRACH in 643.19 prach_index 4=> 131.19
avril 22 15:02:25 [0m1713790945.044737 [PHY]   searching for PRACH in 643.19 prach_index 5=> 159.19
avril 22 15:02:25 [0m1713790945.044738 [PHY]   searching for PRACH in 643.19 prach_index 6=> 551.19
avril 22 15:02:25 [0m1713790945.044739 [PHY]   searching for PRACH in 643.19 prach_index 7=> 641.19
avril 22 15:02:25 [0m
avril 22 15:02:25 Assertion (((prach_id >= 0) && (prach_id < 8))) failed!
avril 22 15:02:25 In nr_fill_prach() /home/chen/openairinterface5g/openair1/PHY/NR_TRANSPORT/nr_prach.c:79
avril 22 15:02:25 illegal or no prach_id found!!! prach_id -1
avril 22 15:02:25 
avril 22 15:02:25 Exiting execution
avril 22 15:02:25 Aborted

```

![Untitled](Untitled%2092.png)

From **`oai_nfapi_ul_tti_req` to `pnf_phy_ul_tti_req`** 

| normal | bug |
| --- | --- |
| 0.1ms | 3~4ms |
|  |  |

In `PNF` will print this one error log.

```
avril 17 10:45:10 1713343510.776483 [NR_PHY]   [gNB 0][RAPROC] Frame 455, slot 19 Initiating RA procedure with preamble 36, energy 54.0 dB (I0 0, thres 150), delay 0 start symbol 0 freq index 0
avril 17 10:45:10 [0m176451962454 [N] 2130826816: pnf_handle_dl_tti_request: pnf_handle_dl_tti_request() is_nr_p7_request_in_window()=TRUE buffer_index occupied - free it first sfn_slot:9340 buffer_index:0
avril 17 10:45:10 176451979927 [N] 2130826816: pnf_nr_nfapi_p7_read_dispatch_message: reallocing rx buffer 254
avril 17 10:45:10 176452017928 [N] 2130826816: pnf_nr_nfapi_p7_read_dispatch_message: reallocing rx buffer 298
avril 17 10:45:11 176452345919 [N] 2130826816: pnf_handle_dl_tti_request: pnf_handle_dl_tti_request()
```

```c
        if(is_nr_p7_request_in_window(req->SFN,req->Slot, "dl_tti_request", pnf_p7))
            {
                uint32_t sfn_slot_dec = NFAPI_SFNSLOT2DEC(req->SFN,req->Slot);
                uint8_t buffer_index = sfn_slot_dec % 20;

                struct timespec t;
                clock_gettime(CLOCK_MONOTONIC, &t);

                NFAPI_TRACE(NFAPI_TRACE_DEBUG,"%s() %ld.%09ld POPULATE DL_TTI_REQ current tx sfn/slot:%d.%d p7 msg sfn/slot: %d.%d buffer_index:%d\n", __FUNCTION__, t.tv_sec, t.tv_nsec, pnf_p7->sfn,pnf_p7->slot, req->SFN, req->Slot, buffer_index);

			// if there is already an dl_tti_req make sure we free it.
			if(pnf_p7->slot_buffer[buffer_index].dl_tti_req != 0)
			{
				NFAPI_TRACE(NFAPI_TRACE_NOTE, "%s() is_nr_p7_request_in_window()=TRUE buffer_index occupied - free it first sfn_slot:%d buffer_index:%d\n", __FUNCTION__, NFAPI_SFNSLOT2DEC(req->SFN,req->Slot), buffer_index);
				//NFAPI_TRACE(NFAPI_TRACE_NOTE, "[%d] Freeing dl_config_req at index %d (%d/%d)", 
				//			pMyPhyInfo->sfnSf, bufferIdx,
				//			SFNSF2SFN(dreq->sfn_sf), SFNSF2SF(dreq->sfn_sf));
				deallocate_nfapi_dl_tti_request(pnf_p7->slot_buffer[buffer_index].dl_tti_req, pnf_p7);
			}
```