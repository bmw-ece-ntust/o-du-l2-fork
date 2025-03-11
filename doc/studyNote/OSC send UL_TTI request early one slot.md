# OSC  send UL_TTI.request early one slot

Start Date: 2024/06/05
Summary: Sending UL_TTI.request early one slot while modifying OSC shift time source code to achieve UL_TTI in slot 19 every 2 frames.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 `UL_TTI.request` sent in a different slot compared to OAI (OAI in slot 19 every two frames, OSC in slot 18 every two frames)

</aside>

```c
[NR_PHY]   frame 185, slot 19, Got NFAPI_NR_UL_TTI_PRACH_PDU_TYPE for 185.19
```

```c
[NR_PHY]   frame 185, slot 18, Got NFAPI_NR_UL_TTI_PRACH_PDU_TYPE for 185.18
```

# Status

currently, we modify OSC shift time source code, we get UL_TTI in slot 19 every 2 frames

<aside>
💡 But we still can’t get max_preamble_energy[0] > 0 value

</aside>

```
juin 06 11:11:37 [0m1717665097.660140 [PHY]   (184,1) <- (183,19)
juin 06 11:11:37 [0m1717665097.660155 [NR_PHY]   frame 183, slot 19, Got NFAPI_NR_UL_TTI_PRACH_PDU_TYPE for 183.19
juin 06 11:11:37 [0m1717665097.660158 [PHY]   searching for PRACH in 183.19 prach_index 0=> -1.-1
juin 06 11:11:37 [0m1717665097.660363 [PHY]   (184,2) <- (184,0)
juin 06 11:11:37 [0m1717665097.660380 [NR_PHY]   184.0 : ssb index 0 pbch_pdu: 60617
juin 06 11:11:37 [0m1717665097.660404 [PHY]   [nr_generate_pbch] pbch_pdu[0]: 0x17
juin 06 11:11:37 [0m1717665097.660406 [PHY]   [nr_generate_pbch] pbch_pdu[1]: 0x06
juin 06 11:11:37 [0m1717665097.660407 [PHY]   [nr_generate_pbch] pbch_pdu[2]: 0x06
juin 06 11:11:37 [0m1717665097.660408 [PHY]   [nr_generate_pbch] pbch->pbch_a: 0x006060e8
juin 06 11:11:37 [0m1717665097.660410 [PHY]   [nr_generate_pbch] pbch_a_prime: 0x822de410
juin 06 11:11:37 [0m1717665097.660611 [PHY]   (184,3) <- (184,1)
juin 06 11:11:37 [0m1717665097.660922 [PHY]   (184,4) <- (184,2)
juin 06 11:11:37 [0m1717665097.660965 [NR_PHY]   183.17 Starting RX processing
juin 06 11:11:37 [0m1717665097.660972 [PHY]   searching for PRACH in 183.17 prach_index 0=> 183.19
juin 06 11:11:37 [0m1717665097.660974 [PHY]   searching for PRACH in 183.17 prach_index 1=> -1.-1
juin 06 11:11:37 [0m1717665097.660975 [PHY]   searching for PRACH in 183.17 prach_index 2=> -1.-1
juin 06 11:11:37 [0m1717665097.660976 [PHY]   searching for PRACH in 183.17 prach_index 3=> -1.-1
juin 06 11:11:37 [0m1717665097.660977 [PHY]   searching for PRACH in 183.17 prach_index 4=> -1.-1
juin 06 11:11:37 [0m1717665097.660978 [PHY]   searching for PRACH in 183.17 prach_index 5=> -1.-1
juin 06 11:11:37 [0m1717665097.660979 [PHY]   searching for PRACH in 183.17 prach_index 6=> -1.-1
juin 06 11:11:37 [0m1717665097.660980 [PHY]   searching for PRACH in 183.17 prach_index 7=> -1.-1
juin 06 11:11:37 [0m1717665097.661513 [PHY]   (184,5) <- (184,3)
juin 06 11:11:37 [0m1717665097.661551 [NR_PHY]   183.18 Starting RX processing
juin 06 11:11:37 [0m1717665097.661556 [PHY]   searching for PRACH in 183.18 prach_index 0=> 183.19
juin 06 11:11:37 [0m1717665097.661558 [PHY]   searching for PRACH in 183.18 prach_index 1=> -1.-1
juin 06 11:11:37 [0m1717665097.661559 [PHY]   searching for PRACH in 183.18 prach_index 2=> -1.-1
juin 06 11:11:37 [0m1717665097.661560 [PHY]   searching for PRACH in 183.18 prach_index 3=> -1.-1
juin 06 11:11:37 [0m1717665097.661561 [PHY]   searching for PRACH in 183.18 prach_index 4=> -1.-1
juin 06 11:11:37 [0m1717665097.661562 [PHY]   searching for PRACH in 183.18 prach_index 5=> -1.-1
juin 06 11:11:37 [0m1717665097.661563 [PHY]   searching for PRACH in 183.18 prach_index 6=> -1.-1
juin 06 11:11:37 [0m1717665097.661564 [PHY]   searching for PRACH in 183.18 prach_index 7=> -1.-1
juin 06 11:11:37 [0m1717665097.661821 [PHY]   (184,6) <- (184,4)
juin 06 11:11:37 [0m1717665097.661854 [NR_PHY]   183.19 Starting RX processing
juin 06 11:11:37 [0m1717665097.661859 [PHY]   searching for PRACH in 183.19 prach_index 0=> 183.19
juin 06 11:11:37 [0m1717665097.661861 [NR_PHY]   183.19 Got prach entry id 0
juin 06 11:11:37 [0m1717665097.661921 [NR_PHY]   prach_energy_counter:100
juin 06 11:11:37 [0m1717665097.661923 [NR_PHY]   max_preamble_energy[0]:564
juin 06 11:11:37 [0m1717665097.661924 [NR_PHY]   [RAPROC] 183.19 Initiating RA procedure with preamble 49, energy 56.4 dB (I0 0, thres 150), delay 0 start symbol 0 freq index 0
juin 06 11:11:37 
```

```
 六  06 17:10:24 [0m[PHY]   (184,1) <- (183,19)
 六  06 17:10:24 [0m[NR_PHY]   frame 183, slot 19, Got NFAPI_NR_UL_TTI_PRACH_PDU_TYPE for 183.19
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.19 prach_index 0=> -1.-1
 六  06 17:10:24 [0m[PHY]   (184,2) <- (184,0)
 六  06 17:10:24 [0m[PHY]   Process dl_tti SFN/slot 184.0 buffer index: 0 
 六  06 17:10:24 [0m[PHY]   Process tx_data SFN/slot 184.0 buffer index: 0 
 六  06 17:10:24 [0m[PHY]   [nr_generate_pbch] pbch_pdu[0]: 0x17
 六  06 17:10:24 [0m[PHY]   [nr_generate_pbch] pbch_pdu[1]: 0x06
 六  06 17:10:24 [0m[PHY]   [nr_generate_pbch] pbch_pdu[2]: 0x06
 六  06 17:10:24 [0m[PHY]   [nr_generate_pbch] pbch->pbch_a: 0x006060e8
 六  06 17:10:24 [0m[PHY]   [nr_generate_pbch] pbch_a_prime: 0x822de410
 六  06 17:10:24 [0m[PHY]   pbch_e[0]: 0x8c3bd661	[0m[PHY]   pbch_e[1]: 0xb0f8c48c	[0m[PHY]   pbch_e[2]: 0x155d6129	[0m[PHY]   pbch_e[3]: 0x07b05dea	[0m[PHY]   pbch_e[4]: 0xd6617c34	[0m[PHY]   pbch_e[5]: 0x8c3b266e	[0m[PHY]   pbch_e[6]: 0xc48c6ed9	[0m[PHY]   pbch_e[7]: 0x6129cb7c	[0m[PHY]   pbch_e[8]: 0xb0f81aad	[0m[PHY]   pbch_e[9]: 0x155dbf08	[0m[PHY]   pbch_e[10]: 0x5deaf7bf	[0m[PHY]   pbch_e[11]: 0x07b0ade5	[0m[PHY]   pbch_e[12]: 0x266e7c34	[0m[PHY]   pbch_e[13]: 0x1aad6ed9	[0m[PHY]   pbch_e[14]: 0xbf08cb7c	[0m[PHY]   pbch_e[15]: 0xade5f7bf	[0m[PHY]   pbch_e[16]: 0x8c3bd661	[0m[PHY]   pbch_e[17]: 0xb0f8c48c	[0m[PHY]   pbch_e[18]: 0x155d6129	[0m[PHY]   pbch_e[19]: 0x07b05dea	[0m[PHY]   pbch_e[20]: 0xd6617c34	[0m[PHY]   pbch_e[21]: 0x8c3b266e	[0m[PHY]   pbch_e[22]: 0xc48c6ed9	[0m[PHY]   pbch_e[23]: 0x6129cb7c	[0m[PHY]   pbch_e[24]: 0xb0f81aad	[0m[PHY]   pbch_e[25]: 0x155dbf08	[0m[PHY]   pbch_e[26]: 0x5deaf7bf	[0m[PHY]   (184,3) <- (184,1)
 六  06 17:10:24 [0m[PHY]   (184,4) <- (184,2)
 六  06 17:10:24 [0m[NR_PHY]   183.17 Starting RX processing
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.17 prach_index 0=> 183.19
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.17 prach_index 1=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.17 prach_index 2=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.17 prach_index 3=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.17 prach_index 4=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.17 prach_index 5=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.17 prach_index 6=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.17 prach_index 7=> -1.-1
 六  06 17:10:24 [0m[PHY]   (184,5) <- (184,3)
 六  06 17:10:24 [0m[NR_PHY]   183.18 Starting RX processing
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.18 prach_index 0=> 183.19
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.18 prach_index 1=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.18 prach_index 2=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.18 prach_index 3=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.18 prach_index 4=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.18 prach_index 5=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.18 prach_index 6=> -1.-1
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.18 prach_index 7=> -1.-1
 六  06 17:10:24 [0m[PHY]   (184,6) <- (184,4)
 六  06 17:10:24 [0m[NR_PHY]   183.19 Starting RX processing
 六  06 17:10:24 [0m[PHY]   searching for PRACH in 183.19 prach_index 0=> 183.19
 六  06 17:10:24 [0m[NR_PHY]   183.19 Got prach entry id 0
 六  06 17:10:24 [0m[NR_PHY]   prach_energy_counter:100
 六  06 17:10:24 [0m[NR_PHY]   max_preamble_energy[0]:0
 六  06 17:10:24 [0m[NR_PHY]   prach_energy_counter++
 六  06 17:10:24 [0m[NR_PHY]   prach_energy_counter:100
 六  06 17:10:24 [0m[NR_PHY]   max_preamble_energy[0]:0
 六  06 17:10:24 [0m[NR_PHY]   prach_energy_counter++
 六  06 17:10:24 [0m[NR_PHY]   prach_energy_counter:100
 六  06 17:10:24 [0m[NR_PHY]   max_preamble_energy[0]:0
 六  06 17:10:24 [0m[NR_PHY]   prach_energy_counter++
```