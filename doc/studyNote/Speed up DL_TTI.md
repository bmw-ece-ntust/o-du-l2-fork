# Speed up DL_TTI

Start Date: 2024/04/23
Summary: Refactor DL TTI request handling to improve code clarity and performance by using stack allocation instead of heap allocation.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全
Tags: Robert Task

<aside>
💡

Refactor DL TTI request handling and improve code clarity

This commit refactors the DL TTI request handling in the PNF P7 module and enhances code clarity.

Changes made:

- Updated the definition of `dl_tti_req` in the `nfapi_pnf_interface.h` header file to directly store the `nfapi_nr_dl_tti_request_t` structure instead of a pointer.
- Refactored DL TTI request processing in the `pnf_handle_dl_tti_request` function in `pnf_p7.c` to simplify the code structure and improve readability.
- Introduced a static function, `cp_nr_dl_tti_req`, to copy DL TTI request structures, improving code modularity and reducing duplication.
- Updated DL TTI request handling to utilize the refactored logic.
- Removed unnecessary deallocation of DL TTI request in error handling path to prevent double deallocation.
</aside>

Follow TX_date.req method to speed up DL_tti (use stack instead of heap) → reference:

[**do not allocate tx_data on heap, introduces huge delay**](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/e8461d1571d7405894b89b5e2aea0c4de7fad488)

Modify these two file:

```c
openairinterface5g\nfapi\open-nFAPI\pnf\public_inc\nfapi_pnf_interface.h
openairinterface5g\nfapi\open-nFAPI\pnf\src\pnf_p7.c
```

## nfapi_pnf_interface.h

```c

typedef struct 
{
	//uint16_t sfn_slot
	int16_t sfn;
	int16_t slot;
	//TODO: Change P7 structs to NR
	nfapi_nr_dl_tti_request_t dl_tti_req;
	nfapi_nr_ul_tti_request_t ul_tti_req;
  nfapi_nr_ul_dci_request_t ul_dci_req;
	nfapi_nr_tx_data_request_t tx_data_req;

	//TODO: check these two later
	//nfapi_lbt_dl_config_request_t* lbt_dl_config_req;
	//nfapi_ue_release_request_t* ue_release_req;
} nfapi_pnf_p7_slot_buffer_t;

```

reference

```c
typedef struct {
  nfapi_p7_message_header_t header;
  /// System Frame Number (0-1023)
  uint16_t SFN;
  /// Slot number (0-19)
  uint16_t Slot;
  nfapi_nr_dl_tti_request_body_t dl_tti_request_body;
  nfapi_vendor_extension_tlv_t vendor_extension;
} nfapi_nr_dl_tti_request_t;

```

## pnf_p7.c

<aside>
👀 **do not allocate dl_tti on heap, introduces huge delay**

- Process dl_tti whenever the number of dl_tti PDUs in the buffer > 0.
- Using allocation on the stack instead of dynamic allocation on the heap.
- Create a new function, **`cp_nr_dl_tti_req`**, to copy the **`dl_tti_req`**.
</aside>

---

Check

```c
~~allocate_nfapi_dl_tti_request
deallocate_nfapi_dl_tti_request~~
```