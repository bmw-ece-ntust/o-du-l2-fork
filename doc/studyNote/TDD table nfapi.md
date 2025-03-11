# TDD table nfapi

Start Date: 2024/05/27
Summary: Development and debugging of TDD table calculations and their implementation in the NFAPI framework.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Robert Task

# why do you calculate `tdd_table_num`?

- why do we need to pack for all slots, and not only up to the TDD transmission periodicity?
- what is your take on "For MAX_TDD_PERIODICITY" from table 3-47?

<aside>
💡

After some careful reflection, I realized that I calculated `tdd_table_num` to dynamically adjust the packing cycle based on the config file, which is the correct approach. Therefore, the patch file I mentioned earlier shouldn't be removed; they should be retained. I also agree that we should only pack the minimum required amount.

Initially, I encountered difficulty in modifying the unpacking process since it uses a function array, so I opted to expand the tdd table at the packing stage.

My oversight was due to the FAPI spec defining MAX_TDD_PERIODICITY. Now, I can modify it to only transmit TDD transmission periodicity and expand it into a complete TDD table at the unpacking stage.

</aside>

# what is the "tdd_table_num"? it's not a "number of a table"? already, the name is not good

also, I disagree with expanding to complete TDD table, nr_slot_select() can simply look up in the correct place in the table, given any slot number?

for the calculation, the problem is the float, I think that should not be done in float as it can lead to rounding errors. We can instead do that:
int nr_slots_frame[] = {10, 20, 40, 80, 160};
int slots = nr_slots_frame[mu];
and then calculate e.g. using the function get_nb_periods_per_frame() (or something similar)?

<aside>
💡

Yes, that makes sense. At first, I thought the same way. However, I kept encountering segmentation faults.

I believe it's because in the PNF, there are many places where TDD_Table[slot] is accessed beyond its bounds, which is hardcoded based on the current mu.
At that point, I changed my mind and decided to modify the VNF instead. Hehe. I'm now starting to look into where it's being used and trying to make modifications.

</aside>

```c
[HW]   No connected device, generating void samples...
Segmentation fault
```

- Find the problem is `executables/nr-ru.c` and `openair1/SCHED_NR/phy_procedures_nr_gNB.c`

## Reformat with clang-format

Reference: [information about clang-format](https://www.notion.so/information-about-clang-format-121100983143817c8cc3ecbdf2012c86?pvs=21) 

```c
# cd openairinterface5g/
clang-format -lines=391:397 -i common/utils/nr/nr_common.c
clang-format -lines=772:773 -i executables/nr-ru.c
clang-format -lines=778:778 -i executables/nr-ru.c
clang-format -lines=935:935 -i executables/nr-ru.c
clang-format -lines=1938:1951 -i nfapi/open-nFAPI/nfapi/src/nfapi_p5.c
clang-format -lines=3196:3197 -i nfapi/open-nFAPI/nfapi/src/nfapi_p5.c
clang-format -lines=3385:3399 -i nfapi/open-nFAPI/nfapi/src/nfapi_p5.c
clang-format -lines=298:329 -i openair1/SCHED_NR/phy_frame_config_nr.c
clang-format -lines=570:570 -i openair1/SCHED_NR/phy_procedures_nr_gNB.c
clang-format -lines=573:573 -i openair1/SCHED_NR/phy_procedures_nr_gNB.c
clang-format -lines=593:594 -i openair1/SCHED_NR/phy_procedures_nr_gNB.c
clang-format -lines=598:598 -i openair1/SCHED_NR/phy_procedures_nr_gNB.c
clang-format -lines=726:726 -i openair1/SCHED_NR/phy_procedures_nr_gNB.c
clang-format -lines=730:730 -i openair1/SCHED_NR/phy_procedures_nr_gNB.c
```

[included clang-format.patch](included_clang-format.patch)