# Rate Matching too low

Start Date: 2024/06/06
Summary: Rate Matching is being analyzed due to low coded bits and performance metrics in a specific code segment.
Status: Done
Assign: Ming 咚咚 [銘鴻]

<aside>
💡 After **Initiating RA procedure, Rate Matching, Code segment 0/1 (coded bits (G) 768, E 768) → (0, E 0), too low.**

</aside>

### Rate Matching

| Field | Origin | OAI Value | OSC integration |
| --- | --- | --- | --- |
| Code Segment | 0/1 | 0/1 | 0/1 |
| Coded Bits (G) | 2688 | 768 | 0 |
| E | 2688 | 768 | 0 |
| Filler Bits | 72 | 76 | 88 |
| Filler Offset | 824 | 68 | 264 |
| Mod Order | 2 | 2 | 2 |
| NB_RB | 16 | 8 | 16 |
| NrOfLayer | 1 | 1 | 1 |

```
juin 06 15:04:01 [0m1717679041.567815 [NR_PHY]   Rate Matching, Code segment 0/1 (coded bits (G) 2688, E 2688, Filler bits 72, Filler offset 824 mod_order 2, nb_rb 16,nrOfLayer 1)...
juin 06 15:04:01 [0m1717679041.577357 [NR_PHY]   Rate Matching, Code segment 0/1 (coded bits (G) 2688, E 2688, Filler bits 72, Filler offset 824 mod_order 2, nb_rb 16,nrOfLayer 1)...
juin 06 15:04:01 [0m1717679041.578895 [NR_PHY]   [RAPROC] 183.19 Initiating RA procedure with preamble 25, energy 56.4 dB (I0 0, thres 150), delay 0 start symbol 0 freq index 0
juin 06 15:04:01 [0m1717679041.579039 [PHY]   pack_nr_rach_indication_body
juin 06 15:04:01 [0m1717679041.579741 [NR_PHY]   Rate Matching, Code segment 0/1 (coded bits (G) 768, E 768, Filler bits 76, Filler offset 68 mod_order 2, nb_rb 8,nrOfLayer 1)...

```

```
六  06 21:06:16 [0m[NR_PHY]   Rate Matching, Code segment 0/1 (coded bits (G) 2688, E 2688, Filler bits 72, Filler offset 824 mod_order 2, nb_rb 16,nrOfLayer 1)...
六  06 21:06:16 [0m[NR_PHY]   Rate Matching, Code segment 0/1 (coded bits (G) 2688, E 2688, Filler bits 72, Filler offset 824 mod_order 2, nb_rb 16,nrOfLayer 1)...
六  06 21:06:16 [0m[NR_PHY]   [RAPROC] 183.19 Initiating RA procedure with preamble 25, energy 56.4 dB (I0 0, thres 150), delay 0 start symbol 0 freq index 0
六  06 21:06:16 [0m[PHY]   pack_nr_rach_indication_body
六  06 21:06:16 [0m[NR_PHY]   Rate Matching, Code segment 0/1 (coded bits (G) 0, E 0, Filler bits 88, Filler offset 264 mod_order 2, nb_rb 16,nrOfLayer 1)...
 
```