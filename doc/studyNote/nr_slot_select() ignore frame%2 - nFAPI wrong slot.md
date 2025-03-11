# nr_slot_select(): ignore frame%2 -> nFAPI wrong slot pattern?

Start Date: 2024/04/24
Summary: Investigating and resolving issues related to the nFAPI wrong slot pattern in the TDD configuration for NR systems.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: TDD-table

<aside>
💡 Solution

</aside>

[Fix P5 packing and unpacking issue for TDD table (74a8ac35) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/74a8ac35a83001f0fb6c9b920ef05dd8d0aad205)

```bash
git revert 71e2546cc9be9615310fd4685af412def5cfd63c
```

[nr_slot_select(): ignore frame%2 -> nFAPI wrong slot pattern? (71e2546c) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/71e2546cc9be9615310fd4685af412def5cfd63c)

![Untitled](Untitled%2057.png)

period is 10 slots

![Untitled](Untitled%2058.png)

### Maybe pack/unpack error in config request

<aside>
💡 check **`pack_nr_config_request` in `openairinterface5g/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c`**

</aside>

```c
  // START TDD Table
  printf("pNfapiMsg->tdd_table.tdd_period:%d\n",pNfapiMsg->tdd_table.tdd_period.value);
  retval &=
      pack_nr_tlv(NFAPI_NR_CONFIG_TDD_PERIOD_TAG, &(pNfapiMsg->tdd_table.tdd_period), ppWritePackedMsg, end, &pack_uint8_tlv_value);
  numTLVs++;

  assert(6 == pNfapiMsg->tdd_table.tdd_period.value);
  for (int i = 0; i < 20; i++) {
    for (int k = 0; k < 14; k++) {
      pack_nr_tlv(NFAPI_NR_CONFIG_SLOT_CONFIG_TAG,
                  &pNfapiMsg->tdd_table.max_tdd_periodicity_list[i].max_num_of_symbol_per_slot_list[k].slot_config,
                  ppWritePackedMsg,
                  end,
                  &pack_uint8_tlv_value);
      numTLVs++;
    }
  }
```

| 6 | **6** |
| --- | --- |
|  |  |
|  |  |

![1000102079.jpg](1000102079.jpg)

## Table size

In PNF P5 unpack source code we can know table is 40*14

```c
  nfapi_nr_config_request_scf_t *pNfapiMsg = (nfapi_nr_config_request_scf_t *)msg;
  // Memory allocations
  pNfapiMsg->tdd_table.max_tdd_periodicity_list =
      (nfapi_nr_max_tdd_periodicity_t *)malloc(40 * sizeof(nfapi_nr_max_tdd_periodicity_t));

  for (int i = 0; i < 40; i++) {
    pNfapiMsg->tdd_table.max_tdd_periodicity_list[i].max_num_of_symbol_per_slot_list =
        (nfapi_nr_max_num_of_symbol_per_slot_t *)malloc(14 * sizeof(nfapi_nr_max_num_of_symbol_per_slot_t));
  }
```

**tdd_periodicity_idx = 20**

All of TDD table

```c
  for (int row = 0; row < 40; row++) {
    for (int symbol_count = 0; symbol_count < 14; symbol_count++) {
        printf("%d ", req->tdd_table.max_tdd_periodicity_list[row].max_num_of_symbol_per_slot_list[symbol_count].slot_config.value);
    }
    printf("\n"); // Print newline after each row
  }
```

```
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
	avril 26 12:03:16 0 0 0 0 0 0 2 2 2 2 1 1 1 1 
avril 26 12:03:16 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
avril 26 12:03:16 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 2 2 2 2 1 1 1 1 
avril 26 12:03:16 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
avril 26 12:03:16 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

```
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 2 2 2 2 1 1 1 1 
avril 26 12:03:16 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
avril 26 12:03:16 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 2 2 2 2 1 1 1 1 
avril 26 12:03:16 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
avril 26 12:03:16 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
avril 26 12:03:16 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

## Set TDD table in VNF

```c
 // TDD Table Configuration
  if (cfg->cell_config.frame_duplex_type.value == TDD) {
    cfg->tdd_table.tdd_period.tl.tag = NFAPI_NR_CONFIG_TDD_PERIOD_TAG;
    cfg->num_tlv++;
    if (scc->tdd_UL_DL_ConfigurationCommon->pattern1.ext1 == NULL) {
      cfg->tdd_table.tdd_period.value = scc->tdd_UL_DL_ConfigurationCommon->pattern1.dl_UL_TransmissionPeriodicity;
    } else {
      AssertFatal(scc->tdd_UL_DL_ConfigurationCommon->pattern1.ext1->dl_UL_TransmissionPeriodicity_v1530 != NULL,
                  "In %s: scc->tdd_UL_DL_ConfigurationCommon->pattern1.ext1->dl_UL_TransmissionPeriodicity_v1530 is null\n",
                  __FUNCTION__);
      cfg->tdd_table.tdd_period.value = *scc->tdd_UL_DL_ConfigurationCommon->pattern1.ext1->dl_UL_TransmissionPeriodicity_v1530;
    }
    LOG_I(NR_MAC, "Setting TDD configuration period to %d\n", cfg->tdd_table.tdd_period.value);
    int periods_per_frame = set_tdd_config_nr(cfg,
                                              frequencyInfoUL->scs_SpecificCarrierList.list.array[0]->subcarrierSpacing,
                                              scc->tdd_UL_DL_ConfigurationCommon->pattern1.nrofDownlinkSlots,
                                              scc->tdd_UL_DL_ConfigurationCommon->pattern1.nrofDownlinkSymbols,
                                              scc->tdd_UL_DL_ConfigurationCommon->pattern1.nrofUplinkSlots,
                                              scc->tdd_UL_DL_ConfigurationCommon->pattern1.nrofUplinkSymbols);

```

```c
int set_tdd_config_nr( nfapi_nr_config_request_scf_t *cfg,
                       int mu,
                       int nrofDownlinkSlots, int nrofDownlinkSymbols,
                       int nrofUplinkSlots,   int nrofUplinkSymbols)
{

  int slot_number = 0;
  int nb_periods_per_frame = get_nb_periods_per_frame(cfg->tdd_table.tdd_period.value);
  int nb_slots_to_set = TDD_CONFIG_NB_FRAMES*(1<<mu)*NR_NUMBER_OF_SUBFRAMES_PER_FRAME;

  int nb_slots_per_period = ((1<<mu) * NR_NUMBER_OF_SUBFRAMES_PER_FRAME)/nb_periods_per_frame;

  if ( (nrofDownlinkSymbols + nrofUplinkSymbols) == 0 )
    AssertFatal(nb_slots_per_period == (nrofDownlinkSlots + nrofUplinkSlots),
                "set_tdd_configuration_nr: given period is inconsistent with current tdd configuration, nrofDownlinkSlots %d, nrofUplinkSlots %d, nb_slots_per_period %d \n",
                nrofDownlinkSlots,nrofUplinkSlots,nb_slots_per_period);
  else {
    AssertFatal(nrofDownlinkSymbols + nrofUplinkSymbols < 14,"illegal symbol configuration DL %d, UL %d\n",nrofDownlinkSymbols,nrofUplinkSymbols);
    AssertFatal(nb_slots_per_period == (nrofDownlinkSlots + nrofUplinkSlots + 1),
                "set_tdd_configuration_nr: given period is inconsistent with current tdd configuration, nrofDownlinkSlots %d, nrofUplinkSlots %d, nrofMixed slots 1, nb_slots_per_period %d \n",
                nrofDownlinkSlots,nrofUplinkSlots,nb_slots_per_period);
  }

  cfg->tdd_table.max_tdd_periodicity_list = (nfapi_nr_max_tdd_periodicity_t *) malloc(nb_slots_to_set*sizeof(nfapi_nr_max_tdd_periodicity_t));

  for(int memory_alloc =0 ; memory_alloc<nb_slots_to_set; memory_alloc++) {
    cfg->tdd_table.max_tdd_periodicity_list[memory_alloc].max_num_of_symbol_per_slot_list = (nfapi_nr_max_num_of_symbol_per_slot_t *) malloc(NR_NUMBER_OF_SYMBOLS_PER_SLOT*sizeof(
          nfapi_nr_max_num_of_symbol_per_slot_t));
    for(int number_of_symbol = 0; number_of_symbol < NR_NUMBER_OF_SYMBOLS_PER_SLOT; number_of_symbol++ ){
      //for each symbol, assign the TLV tag for usage when packing
      cfg->tdd_table.max_tdd_periodicity_list[memory_alloc].max_num_of_symbol_per_slot_list[number_of_symbol].slot_config.tl.tag = NFAPI_NR_CONFIG_SLOT_CONFIG_TAG;
    }
  }

  while(slot_number != nb_slots_to_set) {
    if(nrofDownlinkSlots != 0) {
      for (int number_of_symbol = 0; number_of_symbol < nrofDownlinkSlots*NR_NUMBER_OF_SYMBOLS_PER_SLOT; number_of_symbol++) {
        cfg->tdd_table.max_tdd_periodicity_list[slot_number].max_num_of_symbol_per_slot_list[number_of_symbol%NR_NUMBER_OF_SYMBOLS_PER_SLOT].slot_config.value= 0;

        if((number_of_symbol+1)%NR_NUMBER_OF_SYMBOLS_PER_SLOT == 0)
          slot_number++;
      }
    }

    if (nrofDownlinkSymbols != 0 || nrofUplinkSymbols != 0) {
      for(int number_of_symbol =0; number_of_symbol < nrofDownlinkSymbols; number_of_symbol++) {
        cfg->tdd_table.max_tdd_periodicity_list[slot_number].max_num_of_symbol_per_slot_list[number_of_symbol].slot_config.value= 0;
      }

      for(int number_of_symbol = nrofDownlinkSymbols; number_of_symbol < NR_NUMBER_OF_SYMBOLS_PER_SLOT-nrofUplinkSymbols; number_of_symbol++) {
        cfg->tdd_table.max_tdd_periodicity_list[slot_number].max_num_of_symbol_per_slot_list[number_of_symbol].slot_config.value= 2;
      }

      for(int number_of_symbol = NR_NUMBER_OF_SYMBOLS_PER_SLOT-nrofUplinkSymbols; number_of_symbol < NR_NUMBER_OF_SYMBOLS_PER_SLOT; number_of_symbol++) {
        cfg->tdd_table.max_tdd_periodicity_list[slot_number].max_num_of_symbol_per_slot_list[number_of_symbol].slot_config.value= 1;
      }

      slot_number++;
    }

    if(nrofUplinkSlots != 0) {
      for (int number_of_symbol = 0; number_of_symbol < nrofUplinkSlots*NR_NUMBER_OF_SYMBOLS_PER_SLOT; number_of_symbol++) {
        cfg->tdd_table.max_tdd_periodicity_list[slot_number].max_num_of_symbol_per_slot_list[number_of_symbol%NR_NUMBER_OF_SYMBOLS_PER_SLOT].slot_config.value= 1;

        if((number_of_symbol+1)%NR_NUMBER_OF_SYMBOLS_PER_SLOT == 0)
          slot_number++;
      }
    }
  }

```

- Only fill 10 slot but pack function can pack 20 slot value, and unpack 40 slots
- Only `NR_MAC_UE` fill TDD table

<aside>
💡 Sloution

</aside>

### **pack_nr_config_request**

![openairinterface5g/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c](Untitled%2059.png)

openairinterface5g/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c

### un**pack_nr_config_request**

![openairinterface5g/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c](Untitled%2060.png)

openairinterface5g/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c

Hi, I have an idea regarding the patch. I've found that the reason for the failure to execute lies in the unequal number of slots in the P5 pack and unpack. Let me start from the beginning. After configuring the tdd-UL-DL-ConfigurationCommon in the config file, the VNF converts it into a TDD table of two frame sizes based on mu. In our current scenario where mu equals 1, this means 40 slots. However, during packing, the VNF hard-codes it to only 20 slots. Subsequently, the PNF declares a hard-coded size of 40 slots and unpacks only 20 slots of the TDD table. As a result, the PNF receives a complete frame table along with another frame that is empty. This seems to pose a serious issue because an empty slot in the TDD table represents the Downlink.

Therefore, I believe adjusting the quantities for packing and unpacking dynamically based on mu would be more reasonable. I'd like to hear your thoughts on this proposed solution.

---

# Status

```c
$ iperf3 -c 192.168.70.135 -B 10.0.0.2 -t 40 -R -b100M
Connecting to host 192.168.70.135, port 5201
Reverse mode, remote host 192.168.70.135 is sending
[  5] local 10.0.0.2 port 60397 connected to 192.168.70.135 port 5201
[ ID] Interval           Transfer     Bitrate
[  5]   0.00-1.00   sec  1.22 MBytes  10.2 Mbits/sec                  
[  5]   1.00-2.00   sec  1.95 MBytes  16.3 Mbits/sec                  
[  5]   2.00-3.00   sec  2.01 MBytes  16.9 Mbits/sec                  
[  5]   3.00-4.00   sec  1.89 MBytes  15.9 Mbits/sec                  
[  5]   4.00-5.00   sec  1.89 MBytes  15.9 Mbits/sec                  
[  5]   5.00-6.00   sec  2.05 MBytes  17.2 Mbits/sec                  
[  5]   6.00-7.00   sec  2.02 MBytes  17.0 Mbits/sec                  
[  5]   7.00-8.00   sec  2.11 MBytes  17.7 Mbits/sec                  
[  5]   8.00-9.00   sec  2.12 MBytes  17.7 Mbits/sec                  
[  5]   9.00-10.00  sec  1.31 MBytes  11.0 Mbits/sec                  
[  5]  10.00-11.00  sec   921 KBytes  7.54 Mbits/sec                  
[  5]  11.00-12.00  sec   921 KBytes  7.54 Mbits/sec                  
[  5]  12.00-13.00  sec   839 KBytes  6.87 Mbits/sec                  
[  5]  13.00-14.00  sec   803 KBytes  6.58 Mbits/sec                  
[  5]  14.00-15.00  sec   805 KBytes  6.59 Mbits/sec             
```

```c
ping: Warning: source address might be selected on device other than: oaitun_ue1
PING 192.168.70.135 (192.168.70.135) from 172.24.11.12 oaitun_ue1: 56(84) bytes of data.
64 bytes from 192.168.70.135: icmp_seq=9 ttl=63 time=7.79 ms
64 bytes from 192.168.70.135: icmp_seq=10 ttl=63 time=20.8 ms
64 bytes from 192.168.70.135: icmp_seq=11 ttl=63 time=5.99 ms
64 bytes from 192.168.70.135: icmp_seq=12 ttl=63 time=19.6 ms
64 bytes from 192.168.70.135: icmp_seq=13 ttl=63 time=28.8 ms
64 bytes from 192.168.70.135: icmp_seq=14 ttl=63 time=17.2 ms
64 bytes from 192.168.70.135: icmp_seq=15 ttl=63 time=15.5 ms
64 bytes from 192.168.70.135: icmp_seq=16 ttl=63 time=13.9 ms
64 bytes from 192.168.70.135: icmp_seq=17 ttl=63 time=13.7 ms
64 bytes from 192.168.70.135: icmp_seq=18 ttl=63 time=13.7 ms
64 bytes from 192.168.70.135: icmp_seq=19 ttl=63 time=18.2 ms
64 bytes from 192.168.70.135: icmp_seq=20 ttl=63 time=15.9 ms
64 bytes from 192.168.70.135: icmp_seq=21 ttl=63 time=16.1 ms
64 bytes from 192.168.70.135: icmp_seq=22 ttl=63 time=17.1 ms
64 bytes from 192.168.70.135: icmp_seq=23 ttl=63 time=13.3 ms
64 bytes from 192.168.70.135: icmp_seq=24 ttl=63 time=32.9 ms
64 bytes from 192.168.70.135: icmp_seq=25 ttl=63 time=15.4 ms
64 bytes from 192.168.70.135: icmp_seq=26 ttl=63 time=12.0 ms
64 bytes from 192.168.70.135: icmp_seq=27 ttl=63 time=12.6 ms
64 bytes from 192.168.70.135: icmp_seq=28 ttl=63 time=15.4 ms
64 bytes from 192.168.70.135: icmp_seq=29 ttl=63 time=15.3 ms
64 bytes from 192.168.70.135: icmp_seq=30 ttl=63 time=13.2 ms
64 bytes from 192.168.70.135: icmp_seq=31 ttl=63 time=15.9 ms
64 bytes from 192.168.70.135: icmp_seq=32 ttl=63 time=29.2 ms
64 bytes from 192.168.70.135: icmp_seq=33 ttl=63 time=15.6 ms
64 bytes from 192.168.70.135: icmp_seq=34 ttl=63 time=49.5 ms
64 bytes from 192.168.70.135: icmp_seq=35 ttl=63 time=18.5 ms
64 bytes from 192.168.70.135: icmp_seq=36 ttl=63 time=16.1 ms
64 bytes from 192.168.70.135: icmp_seq=37 ttl=63 time=24.6 ms
64 bytes from 192.168.70.135: icmp_seq=38 ttl=63 time=76.1 ms
64 bytes from 192.168.70.135: icmp_seq=39 ttl=63 time=142 ms
64 bytes from 192.168.70.135: icmp_seq=40 ttl=63 time=142 ms
64 bytes from 192.168.70.135: icmp_seq=41 ttl=63 time=208 ms
64 bytes from 192.168.70.135: icmp_seq=42 ttl=63 time=226 ms
64 bytes from 192.168.70.135: icmp_seq=43 ttl=63 time=294 ms
64 bytes from 192.168.70.135: icmp_seq=44 ttl=63 time=339 ms
64 bytes from 192.168.70.135: icmp_seq=45 ttl=63 time=424 ms
64 bytes from 192.168.70.135: icmp_seq=46 ttl=63 time=982 ms
64 bytes from 192.168.70.135: icmp_seq=47 ttl=63 time=1091 ms
64 bytes from 192.168.70.135: icmp_seq=48 ttl=63 time=1172 ms
64 bytes from 192.168.70.135: icmp_seq=49 ttl=63 time=1455 ms
64 bytes from 192.168.70.135: icmp_seq=50 ttl=63 time=1430 ms
64 bytes from 192.168.70.135: icmp_seq=51 ttl=63 time=2092 ms
64 bytes from 192.168.70.135: icmp_seq=52 ttl=63 time=2274 ms
64 bytes from 192.168.70.135: icmp_seq=53 ttl=63 time=2301 ms
64 bytes from 192.168.70.135: icmp_seq=54 ttl=63 time=2273 ms
64 bytes from 192.168.70.135: icmp_seq=55 ttl=63 time=2164 ms
64 bytes from 192.168.70.135: icmp_seq=56 ttl=63 time=2196 ms
64 bytes from 192.168.70.135: icmp_seq=57 ttl=63 time=2136 ms
64 bytes from 192.168.70.135: icmp_seq=58 ttl=63 time=2011 ms
64 bytes from 192.168.70.135: icmp_seq=59 ttl=63 time=1967 ms
64 bytes from 192.168.70.135: icmp_seq=60 ttl=63 time=2215 ms
64 bytes from 192.168.70.135: icmp_seq=61 ttl=63 time=2300 ms
64 bytes from 192.168.70.135: icmp_seq=62 ttl=63 time=2271 ms
64 bytes from 192.168.70.135: icmp_seq=63 ttl=63 time=2349 ms
64 bytes from 192.168.70.135: icmp_seq=64 ttl=63 time=2551 ms
64 bytes from 192.168.70.135: icmp_seq=65 ttl=63 time=2723 ms
64 bytes from 192.168.70.135: icmp_seq=66 ttl=63 time=2615 ms
64 bytes from 192.168.70.135: icmp_seq=67 ttl=63 time=2415 ms
64 bytes from 192.168.70.135: icmp_seq=68 ttl=63 time=2202 ms
64 bytes from 192.168.70.135: icmp_seq=69 ttl=63 time=2199 ms
64 bytes from 192.168.70.135: icmp_seq=70 ttl=63 time=2138 ms
64 bytes from 192.168.70.135: icmp_seq=71 ttl=63 time=2232 ms
64 bytes from 192.168.70.135: icmp_seq=72 ttl=63 time=2167 ms
64 bytes from 192.168.70.135: icmp_seq=73 ttl=63 time=2153 ms
64 bytes from 192.168.70.135: icmp_seq=74 ttl=63 time=2005 ms
64 bytes from 192.168.70.135: icmp_seq=75 ttl=63 time=2128 ms
64 bytes from 192.168.70.135: icmp_seq=76 ttl=63 time=2070 ms
64 bytes from 192.168.70.135: icmp_seq=77 ttl=63 time=1687 ms
64 bytes from 192.168.70.135: icmp_seq=78 ttl=63 time=685 ms
64 bytes from 192.168.70.135: icmp_seq=79 ttl=63 time=40.8 ms
64 bytes from 192.168.70.135: icmp_seq=80 ttl=63 time=107 ms
64 bytes from 192.168.70.135: icmp_seq=81 ttl=63 time=43.1 ms
64 bytes from 192.168.70.135: icmp_seq=82 ttl=63 time=45.7 ms
64 bytes from 192.168.70.135: icmp_seq=83 ttl=63 time=49.3 ms
64 bytes from 192.168.70.135: icmp_seq=84 ttl=63 time=52.4 ms
64 bytes from 192.168.70.135: icmp_seq=85 ttl=63 time=18.4 ms
64 bytes from 192.168.70.135: icmp_seq=86 ttl=63 time=42.6 ms
64 bytes from 192.168.70.135: icmp_seq=87 ttl=63 time=46.2 ms
64 bytes from 192.168.70.135: icmp_seq=88 ttl=63 time=41.8 ms
64 bytes from 192.168.70.135: icmp_seq=89 ttl=63 time=24.8 ms
64 bytes from 192.168.70.135: icmp_seq=90 ttl=63 time=20.4 ms
64 bytes from 192.168.70.135: icmp_seq=91 ttl=63 time=22.9 ms
64 bytes from 192.168.70.135: icmp_seq=92 ttl=63 time=21.9 ms
```