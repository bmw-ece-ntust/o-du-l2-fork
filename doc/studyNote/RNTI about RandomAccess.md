# RNTI about RandomAccess

Start Date: 2024/07/17
Summary: The project focuses on the implementation and computation of Random Access RNTI in telecommunications.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 Rederence:
[LTE：RA-RNTI、T-CRNTI、C-RNTI-CSDN博客](https://blog.csdn.net/dxpqxb/article/details/104237992)
https://blog.csdn.net/qq_31985307/article/details/127820714

</aside>

<aside>
💡 Fixed in [OSC can’t send RAR](OSC%20can%E2%80%99t%20send%20RAR%2012110098314381478ea0cf574169add5.md)

</aside>

![Untitled](Untitled%2074.png)

![Untitled](Untitled%2075.png)

| **symbolIdx** | 0 |
| --- | --- |
| **slotIdx** | 0 |
| **freqIdx** | 0 |
| **RA_RNTI** | 1 |

```c
uint16_t calculateRaRnti(uint8_t symbolIdx, uint8_t slotIdx, uint8_t freqIdx)
{
   uint16_t raRnti = 0;
   uint8_t  ulCarrierIdx = 0; /* Uplink carrier used for MSG1 transmission. 0:NUL carrier; 1:SUL carrier */
   
   /* Refer to spec 38.321, section 5.1.3 */
   raRnti = (1 + symbolIdx + (14*slotIdx) + (14*80*freqIdx) + (14*80*8*ulCarrierIdx));
   return raRnti;
}
```

| **f_id** | 0 |
| --- | --- |
| **t_id** | 19 |
| **s_id** | 0 |
| **ul_carrier_id** | 0 |
| **RA_RNTI** | **0x010B** |

```c
// RA-RNTI computation (associated to PRACH occasion in which the RA Preamble is transmitted)
// - this does not apply to contention-free RA Preamble for beam failure recovery request
// - getting star_symb, SFN_nbr from table 6.3.3.2-3 (TDD and FR1 scenario)
// - s_id is starting symbol of the PRACH occasion [0...14]
// - t_id is the first slot of the PRACH occasion in a system frame [0...80]
// - f_id: index of the PRACH occasion in the frequency domain
// - ul_carrier_id: UL carrier used for RA preamble transmission, hardcoded for NUL carrier
rnti_t nr_get_ra_rnti(uint8_t s_id, uint8_t t_id, uint8_t f_id, uint8_t ul_carrier_id)
{
  // 3GPP TS 38.321 Section 5.1.3
  rnti_t ra_rnti = 1 + s_id + 14 * t_id + 1120 * f_id + 8960 * ul_carrier_id;
  LOG_D(MAC, "f_id %d t_id %d s_id %d ul_carrier_id %d Computed RA_RNTI is 0x%04X\n", f_id, t_id, s_id, ul_carrier_id, ra_rnti);

  return ra_rnti;
}

```

Fixed in [OSC can’t send RAR](OSC%20can%E2%80%99t%20send%20RAR%2012110098314381478ea0cf574169add5.md)