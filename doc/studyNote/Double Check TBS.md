# Double Check TBS

Start Date: 2024/10/11
Summary: The project involves calculating transport block sizes (TBS) and the number of physical resource blocks (PRB) in a communication system based on various parameters and functions.
Status: Done
Assign: 陳奕全
Finish Date: 2024/10/14
SUM: 🗓️ Days Spent to Complete: 3

[Compute TBS and PRB](Compute%20TBS%20and%20PRB%20121100983143819aa2b2c12155d157f8.md)

Basicly if payloadsize > Tb size table, tbsize index++ and retrieve enough large TB size 

![image.png](image%2017.png)

```c
uint16_t schCalcTbSize(uint32_t payLoadSize)
{
   uint8_t tbsIndex = 0;
   uint16_t maxTbSize;

   maxTbSize = tbSizeTable[TOTAL_TBSIZE_VALUES -1]/8;
   if(payLoadSize >= maxTbSize)
      return maxTbSize;

   payLoadSize = payLoadSize*8;
   uint32_t n = max(3, floor(log2(payLoadSize)) - 6);
   // printf("n = %d\n", n);
   uint32_t Np_info = max(24, (payLoadSize>>n)<<n);
   // printf("Np_info = %d\n", Np_info);
   while(Np_info > tbSizeTable[tbsIndex])
   {
      tbsIndex++;
   }

   /* return the TBsize in bytes */
   return (tbSizeTable[tbsIndex]/8);
}
```

---

Use TBsize and mcs and number of symbols to calculate Number of PRB

> Qm and R are get from MCS table
> 

https://www.sharetechnote.com/html/5G/5G_MCS_TBS_CodeRate.html

![image.png](image%2018.png)

```c
uint16_t schCalcNumPrb(uint16_t tbSize, uint16_t mcs, uint8_t numSymbols)
{
   uint16_t numPrb = 0;
   uint16_t nre = 0;
   uint16_t nreDash = 0;
   uint8_t  qm     = mcsTable[mcs][1];
   uint16_t rValue = mcsTable[mcs][2];
   uint8_t  numLayer = 1;       /* v value */
   uint8_t  numDmrsRePerPrb = 12*3;

   tbSize = tbSize * 8; //Calculate tbSize in bits

   /* formula used for calculation of rbSize, 38.214 section 5.1.3.2 *
    * Ninfo = S . Nre . R . Qm . v                                       *
    * Nre' = Nsc . NsymPdsch - NdmrsSymb - Noh                       *
    * Nre = min(156,Nre') . nPrb                                     */

  // Rx1024 is tabulated as 10 times the actual code rate
   nre = ceil( (float)tbSize * 1024 / (rValue * qm * numLayer));

   nreDash = ceil( (12 * numSymbols) - numDmrsRePerPrb - 0);

   if (nreDash > 156)
      nreDash = 156;

   numPrb = ceil((float)nre / nreDash);   
   return numPrb;
}

```

![image.png](image%2019.png)

---

OAI MSC

```c
// the following tables contain 10 times the value reported in 214 (in line with SCF specification and to avoid fractional values)
//Table 5.1.3.1-1 of 38.214
static const uint16_t Table_51311[32][2] = {{2, 1200}, {2, 1570}, {2, 1930}, {2, 2510}, {2, 3080}, {2, 3790}, {2, 4490}, {2, 5260},
                                            {2, 6020}, {2, 6790}, {4, 3400}, {4, 3780}, {4, 4340}, {4, 4900}, {4, 5530}, {4, 6160},
                                            {4, 6580}, {6, 4380}, {6, 4660}, {6, 5170}, {6, 5670}, {6, 6160}, {6, 6660}, {6, 7190},
                                            {6, 7720}, {6, 8220}, {6, 8730}, {6, 9100}, {6, 9480}, {2, 0}, {4, 0}, {6, 0}};

```

<aside>
👀

OAI’s MSC table `R` is bigger than OSC’s 10 times 

</aside>

 十  11 19:35:46 [TEST] schCalcNumPrb(schCalcTbSize(88), 5, 10): 6

 十  11 19:38:17 [TEST] schCalcNumPrb(schCalcTbSize(88), 5, 10): 12

```c
 //original OAI 
 十  11 20:57:37 [0m1728651457.982654 [NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 1, nb_symb_sch 10, nb_dmrs_prb 0, nb_rb_oh 0, tb_scaling 0, Nl 1, tbs 88 bits
```

```
 十  11 21:05:06 [0m[MAC]   dlsch_pdu->mcs: 5, dlsch_pdu->mcs_table: 0
 十  11 21:05:06 [0m[MAC]   qamModOrder: 2, R: 3790, number_rbs: 12, number_symbols: 10, nb_re_dmrs: 12, dlsch_pdu->dlDmrsSymbPos: 580, get_num_dmrs(): 3, nb_rb_oh: 0
 十  11 21:05:06 [0m[NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 12, nb_symb_sch 10, nb_dmrs_prb 36, nb_rb_oh 0, tb_scaling 0, Nl 1
 十  11 21:05:06 [0m[NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 7, nb_symb_sch 10, nb_dmrs_prb 36, nb_rb_oh 0, tb_scaling 0, Nl 1
 十  11 21:05:06 [0m[MAC]   TBS 768, test_tbs 432 for RB 7
 十  11 21:05:06 [0m[NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 8, nb_symb_sch 10, nb_dmrs_prb 36, nb_rb_oh 0, tb_scaling 0, Nl 1
 十  11 21:05:06 [0m[MAC]   TBS 768, test_tbs 504 for RB 8
 十  11 21:05:06 [0m[NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 9, nb_symb_sch 10, nb_dmrs_prb 36, nb_rb_oh 0, tb_
```

```
 十  11 20:57:47 [0m[MAC]   dlsch_pdu->mcs: 5, dlsch_pdu->mcs_table: 0
 十  11 20:57:47 [0m[MAC]   qamModOrder: 2, R: 3790, number_rbs: 16, number_symbols: 10, nb_re_dmrs: 12, dlsch_pdu->dlDmrsSymbPos: 580, get_num_dmrs(): 3, nb_rb_oh: 0
 十  11 20:57:47 [0m[NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 16, nb_symb_sch 10, nb_dmrs_prb 36, nb_rb_oh 0, tb_scaling 0, Nl 1
 十  11 20:57:47 [0m[NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 11, nb_symb_sch 10, nb_dmrs_prb 36, nb_rb_oh 0, tb_scaling 0, Nl 1
 十  11 20:57:47 [0m[MAC]   TBS 1032, test_tbs 704 for RB 11
 十  11 20:57:47 [0m[NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 12, nb_symb_sch 10, nb_dmrs_prb 36, nb_rb_oh 0, tb_scaling 0, Nl 1
 十  11 20:57:47 [0m[MAC]   TBS 1032, test_tbs 768 for RB 12
 十  11 20:57:47 [0m[NR_MAC]   In nr_compute_tbs: Qm 2, R 3790, nb_rb 13, nb_symb_sch 10, nb_dmrs_prb 36, nb_rb_oh 0, tb_scaling 0, Nl 1
 十  11 20:57:47 [0m[MAC]   TBS 1032, test_tbs 808 for RB 13
```

<aside>
💡

I follow this condition   

Qm 2, 

R 3790, 

nb_rb 12, 

nb_symb_sch 10, 

nb_dmrs_prb 36, 

nb_rb_oh 0, 

tb_scaling 0, 

Nl 1

and this formula

```c
  const int nb_subcarrier_per_rb = 12;
  const uint32_t nbp_re =  nb_subcarrier_per_rb * nb_symb_sch - nb_dmrs_prb - nb_rb_oh;
  const uint32_t nb_re = min(156, nbp_re) * nb_rb;
  // Intermediate number of information bits
  // Rx1024 is tabulated as 10 times the actual code rate
  const uint32_t R_5 = R/5; // R can be fractional so we can't divide by 10
  // So we ned to right shift by 11 (10 for x1024 and 1 additional as above)
  const uint32_t Ninfo = ((nb_re * R_5 * Qm * Nl)>>11)>>tb_scaling;

  uint32_t nr_tbs=0;
  uint32_t Np_info, C, n;

  if (Ninfo <= NR_MAX_PDSCH_TBS) {
    n = max(3, floor(log2(Ninfo)) - 6);
      Np_info = max(24, (Ninfo>>n)<<n);
      for (int i=0; i<INDEX_MAX_TBS_TABLE; i++) {
        if (Tbstable_nr[i] >= Np_info){
          nr_tbs = Tbstable_nr[i];
          break;
        }
    
```

Get the Np_info is 744 and check the table if  Tbstable_nr[]= 768 this loop will be break.

~~I think the problem maybe is `R` but `>>11`~~ is equal to divide 1024 and divide 2 

$$
2^{11}
$$

</aside>

### OSC:

$$
RBsize=ceil({TBsize*1024}/Qm*R*n)/(sub carriersPerRB*10-36)
$$

$$
RBsize​=⌈Qm​×R×nTBsize​×1024​⌉÷(subcarriersPerRB×10−36)
$$

![{9EFDDD94-C7D7-490D-B9FB-1AD78B143990}.png](9EFDDD94-C7D7-490D-B9FB-1AD78B143990.png)

### OAI:

$$
TBsize=({R*Qm*n*(Subcarrier Per RB*10-36)*RBsize}/1024)
$$

$$
TBsize=R×Qm×n×(SubcarrierPerRB×NbSymbSch−36)×RBsize÷1024
$$

![{FAB1E36D-8CB3-4107-90A3-39B3A801787D}.png](FAB1E36D-8CB3-4107-90A3-39B3A801787D.png)

<aside>
💡

I think the function calculate RB has some difference place lead to get difference TBsize

I believe the reason for the mismatch between the `TBsize`obtained by the UE and the ODU is that the OSC always uses `ceil` (rounding up) when calculating the `RBsize`. This causes mismatch when the UE calculates the `TBS` using the `RBsize`provided by the ODU.

The RBsize calculation formula in the OSC DU is as follows:

```c
uint16_t schCalcNumPrb(uint16_t tbSize, uint16_t mcs, uint8_t numSymbols)
{
   uint16_t numPrb = 0;
   uint16_t nre = 0;
   uint16_t nreDash = 0;
   uint8_t  qm     = mcsTable[mcs][1];
   uint16_t rValue = mcsTable[mcs][2];
   uint8_t  numLayer = 1;       /* v value */
   uint8_t  numDmrsRePerPrb = 12 * 3;

   tbSize = tbSize * 8; // Calculate tbSize in bits
   
   nre = ceil( (float)tbSize * 1024 / (rValue * qm * numLayer));

   nreDash = ceil( (12 * numSymbols) - numDmrsRePerPrb - 0);

   if (nreDash > 156)
      nreDash = 156;

   numPrb = ceil((float)nre / nreDash);   
   return numPrb;
}

```

</aside>

<aside>
💡

Do not use `ceil` to get `numPrb` replace with `floor`

</aside>