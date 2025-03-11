# Compute TBS and PRB

Start Date: 2024/10/08
Summary: Development and analysis of Transport Block Size (TBS) and Physical Resource Block (PRB) calculations in 5G NR systems, addressing discrepancies between different implementations.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/15
SUM: 🗓️ Days Spent to Complete: 7

<aside>
💡

[Identify and resolve issues](Compute%20TBS%20and%20PRB%20121100983143819aa2b2c12155d157f8.md) 

</aside>

<aside>
💡

**Transport Block (TB)**

**Modulation and Coding Scheme (MCS)**

**Resource Elements (REs)**

**Physical Resource Blocks (PRBs)**

</aside>

[https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=BxmrTluOHl3hw8C2wvRX#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=BxmrTluOHl3hw8C2wvRX#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)

# Main different

## OSC & OAI

- OAI follows the 3GPP spec formulas step by step for calculations, but when calculating the RB size, if following the spec's calculation process, it needs to use an exhaustive method to ultimately determine the TBS
- OSC, on the other hand, rearranges and simplifies the formula on its own, calculating backwards from the end, thus resulting in a function with input TBS / output RB size (opposite to the formula defined in the spec)

## Math

The formula after my understanding and simplification:

$$
TBS = S*R*Q_m*N_{\text{level}}*(12*N_{\text{Symbol}}-N_{\text{DMRS}})*PRB
$$

### Comparison of Two Functions: `nr_compute_tbs` vs `schCalcNumPrb`

These two functions are designed to compute related aspects of 5G NR physical layer parameters, specifically the Transport Block Size (TBS) and the number of Physical Resource Blocks (PRB). While they aim to achieve similar results, the algorithms they implement differ, leading to variations in their outputs.

- **`nr_compute_tbs`**:

Here's a detailed table with the input, output, and variable definitions for the `nr_compute_tbs` function, based on 3GPP TS 38.214 Section 6.1.4.2 regarding transport block size determination.

| **Category** | **Parameter** | **Definition** |
| --- | --- | --- |
| **Output** | `nr_tbs` | The calculated transport block size (TBS) in bits, as determined by the formula based on 3GPP TS 38.214 specifications. |
| **Input** | `Qm` | Modulation order (e.g., QPSK = 2, 16-QAM = 4). |
|  | `R` | Code rate multiplied by 1024, where R/1024 is the effective code rate. |
|  | `nb_rb` | Number of resource blocks assigned for the transport block. |
|  | `nb_symb_sch` | Number of scheduled symbols per resource block. |
|  | `nb_dmrs_prb` | Number of demodulation reference signal (DMRS) symbols per resource block, which are overhead and do not carry data. |
|  | `nb_rb_oh` | Overhead associated with resource blocks, accounting for control channels or other non-data overhead. |
|  | `tb_scaling` | Scaling factor for the transport block size, used to scale down the calculated TBS for reduced payloads. |
|  | `Nl` | Number of layers, which affects the number of streams transmitted in parallel. |
| **Other Variables** | `nbp_re` | Number of physical resource elements (REs) per resource block, calculated by multiplying the number of subcarriers per resource block (`12`) by the number of scheduled symbols, then subtracting DMRS and overhead REs. |
|  | `nb_re` | Total number of REs available for data transmission, limited to 156 REs per resource block, then multiplied by the number of resource blocks (`nb_rb`). |
|  | `R_5` | Adjusted code rate to avoid fractional calculations by dividing R by 5. |
|  | `Ninfo` | Intermediate number of information bits, calculated using available REs, code rate, modulation order, and number of layers, scaled down by the transport block scaling factor. |
|  | `Np_info` | Adjusted number of information bits based on TBS tables, used to find the appropriate transport block size. |
|  | `C` | Number of code blocks, determined by splitting large transport blocks into smaller units. |
|  | `n` | Used in bit shifting to ensure values align with the TBS tables. |
- **`schCalcNumPrb`** is responsible for calculating the number of Physical Resource Blocks (PRBs) required to transmit a given transport block (TB) in a 5G NR system. Here's an overview of the function's inputs, calculations, and output:

| **Category** | **Parameter** | **Definition** |
| --- | --- | --- |
| **Output** | `numPrb` | The number of Physical Resource Blocks (PRBs) required to carry the transport block of size `tbSize`. |
| **Input** | `tbSize` | Transport block size in bytes. The function multiplies this by 8 to convert to bits. |
|  | `mcs` | Modulation and Coding Scheme (MCS) index, which determines the modulation order (`qm`) and the coding rate (`rValue`) from the `mcsTable`. |
|  | `numSymbols` | Number of symbols available for data transmission. |
| **Other Variables** | `nre` | Number of Resource Elements (REs) needed for transmission, based on the TB size, modulation order, coding rate, and number of layers. |
|  | `nreDash` | Adjusted number of REs per PRB, accounting for available subcarriers (`12`), scheduled symbols (`numSymbols`), and DMRS overhead (`numDmrsRePerPrb`). |
|  | `qm` | Modulation order, retrieved from `mcsTable[mcs][1]`, indicating how many bits are transmitted per symbol (e.g., QPSK = 2, 16-QAM = 4, etc.). |
|  | `rValue` | Code rate (scaled by 1024) retrieved from `mcsTable[mcs][2]`, which represents the coding rate applied to the transmitted data. |
|  | `numLayer` | Number of layers used for transmission, set to 1 in this implementation (no multi-layer transmission). |
|  | `numDmrsRePerPrb` | Number of Resource Elements per PRB reserved for Demodulation Reference Signals (DMRS), which are overhead and do not carry data. In this case, 12 REs per PRB are reserved. |

### Formula:

- **`nre`**: Calculates the number of Resource Elements required to transmit the transport block. This is based on the TB size (in bits), modulation order, coding rate, and number of layers:
    
    $$
    N_{info} = \frac{S \cdot N_{re} \cdot R \cdot Q_m \cdot v}{1024}
    $$
    

Where `S` is the TB size in bits, `$N_{re}$` is the total number of REs, `R` is the coding rate, `$Q_m$` is the modulation order, and `v` is the number of layers.

- **`nreDash`**: Adjusts the number of REs available per PRB based on the number of subcarriers (`12` per PRB), symbols, and DMRS overhead.
- **`numPrb`**: Calculates the number of PRBs needed by dividing the required REs by the adjusted REs per PRB.

This function follows the guidelines from 3GPP TS 38.214, Section 5.1.3.2, and calculates the required PRBs to meet a given transport block size under specified conditions.

### 1. Overview of the Functions

- **`nr_compute_tbs`**:
    - This function calculates the Transport Block Size (TBS) based on the 3GPP TS 38.214 Section 6.1.4.2 standard.
    - The logic is built upon:
        - Calculating the number of Resource Elements (RE) per PRB (`nbp_re`), followed by the total number of REs (`nb_re`).
        - Using the code rate, modulation order, and transmission layers to compute the number of information bits.
        - It performs boundary checks and looks up the nearest TBS value from predefined tables.
- **`schCalcNumPrb`**:
    - This function calculates the required number of PRBs based on the input TBS, Modulation and Coding Scheme (MCS), and the number of symbols.
    - The logic is based on:
        - The value of `N_re` is derived from the number of REs per PRB, which is capped at a maximum value of 156.

### 2. Key Differences

- **TBS Calculation vs PRB Calculation**:
    - `nr_compute_tbs` is a more comprehensive algorithm, considering multiple physical layer parameters to compute the final TBS value.
    - `schCalcNumPrb` simplifies the process by estimating the number of PRBs required for a given TBS and MCS, with less detailed handling of edge cases.
- **Simplified Formula**:
    - `schCalcNumPrb` uses a simplified formula and assumes certain parameters are constant (e.g., maximum RE per PRB = 156), whereas `nr_compute_tbs` calculates these dynamically based on various conditions, including DMRS and overhead.

# OSC DU

### Query from the table

Return the value from the table that is larger than the expected TBS.

![{03585082-1A7A-4BAF-834E-74E91E902A03}.png](03585082-1A7A-4BAF-834E-74E91E902A03.png)

![{FA251940-816C-4698-ACCD-3A6A6B4789CD}.png](FA251940-816C-4698-ACCD-3A6A6B4789CD.png)

```c
uint16_t tbSizeTable[TOTAL_TBSIZE_VALUES] = {
         24,    32,    40,    48,    56,    64,    72,    80,    88,    96, \
        104,   112,   120,   128,   136,   144,   152,   160,   168,   176, \
        184,   192,   208,   224,   240,   256,   272,   288,   304,   320, \
        336,   352,   368,   384,   408,   432,   456,   480,   504,   528, \
        552,   576,   608,   640,   672,   704,   736,   768,   808,   848, \
        888,   928,   984,  1032,  1064,  1128,  1160,  1192,  1224,  1256, \
       1288,  1320,  1352,  1416,  1480,  1544,  1608,  1672,  1736,  1800, \
       1864,  1928,  2024,  2088,  2152,  2216,  2280,  2408,  2472,  2536, \
       2600,  2664,  2728,  2792,  2856,  2976,  3104,  3240,  3368,  3496, \
       3624,  3752,  3824 };
       
uint16_t mcsTable[32][3] = {
      {   0,   2,   120},   /* mcs index  0 */ 
      {   1,   2,   157},   /* mcs index  1 */ 
      {   2,   2,   193},   /* mcs index  2 */ 
      {   3,   2,   251},   /* mcs index  3 */ 
      {   4,   2,   308},   /* mcs index  4 */ 
      {   5,   2,   379},   /* mcs index  5 */ 
      ...
      ...
      ...
             
/**
 * @brief frequency domain allocation function. 
 *
 * @details
 *
 *     Function: schCalcTbSize
 *     
 *     This function finds the TBSize from table Table 5.1.3.2-1 spec 38.214
 *     
 *  @param[in]  payLoadSize - size of payload in bytes
 *  @return     TBsize from the Table in bytes
 **/
uint16_t schCalcTbSize(uint32_t payLoadSize)
{
   uint8_t tbsIndex = 0;
   uint16_t maxTbSize;

   maxTbSize = tbSizeTable[TOTAL_TBSIZE_VALUES -1]/8;
   if(payLoadSize >= maxTbSize)
      return maxTbSize;

   payLoadSize = payLoadSize*8;
   while(payLoadSize > tbSizeTable[tbsIndex])
   {
      tbsIndex++;
   }

   /* return the TBsize in bytes */
   return (tbSizeTable[tbsIndex]/8);
}
```

## Get PRB by (TBS and symbol and MCS)

OSC flexibly uses the method of formula transposition to directly derive the TB size and PRB size. However, in the implementation, some parameters are hard-coded as constants within the functions, rather than being used as function inputs. For example, `nb_dmrs_prb` is hard-coded to a value of 12 in OSC. This is the main issue causing invalid CCCH in MSG4 at the UE, because I adjusted `dlDmrsSymbPos` in MSG4, then `nb_dmrs_prb` should be 36. Please refer to the detailed notes for more information -> [Develop schCalcNumPrb_withDmrs in OSC](Develop%20schCalcNumPrb_withDmrs%20in%20OSC%201211009831438173b598f24af78392d5.md) 

$$
\text{tbSize}_{\text{bits}} = \text{tbSize} \times 8
$$

$$
N_{\text{info}} = S \cdot N_{\text{re}} \cdot R \cdot Q_m \cdot v

$$

$$
N_{\text{re}}' = (12 \cdot \text{numSymbols}) - \text{numDmrsRePerPrb} - N_{\text{oh}}

$$

$$
N_{\text{re}} = \min(156, N_{\text{re}}')

$$

$$
n_{\text{re}} = \left\lceil \frac{\text{tbSize} \times 1024}{Q_m \times r_{\text{Value}} \times \text{numLayer}} \right\rceil
$$

$$
\text{numPrb} = \left\lceil \frac{n_{\text{re}}}{N_{\text{re}}} \right\rceil

$$

```c
/**
 * @brief frequency domain allocation function. 
 *
 * @details
 *
 *     Function: schCalcNumPrb
 *     
 *     This function calculates the number of PRbs 
 *     
 *  @param[in]  tbSize in bytes
 *  @param[in]  mcs
 *  @param[in]  number of symbols
 *  @return   number PRBs
 **/
uint16_t schCalcNumPrb(uint16_t tbSize, uint16_t mcs, uint8_t numSymbols)
{
   uint16_t numPrb = 0;
   uint16_t nre = 0;
   uint16_t nreDash = 0;
   uint8_t  qm     = mcsTable[mcs][1];
   uint16_t rValue = mcsTable[mcs][2];
   uint8_t  numLayer = 1;       /* v value */
   uint8_t  numDmrsRePerPrb = 12;

   tbSize = tbSize * 8; //Calculate tbSize in bits

   /* formula used for calculation of rbSize, 38.214 section 5.1.3.2 *
    * Ninfo = S . Nre . R . Qm . v                                       *
    * Nre' = Nsc . NsymPdsch - NdmrsSymb - Noh                       *
    * Nre = min(156,Nre') . nPrb                                     */

   nre = ceil( (float)tbSize * 1024 / (qm * rValue * numLayer));

   nreDash = ceil( (12 * numSymbols) - numDmrsRePerPrb - 0);

   if (nreDash > 156)
      nreDash = 156;

   numPrb = ceil((float)nre / nreDash);   
   return numPrb;
}
```

# OAI UE

## Get PRB number from `frequency_domain_assignment`

Decode PDCCH MSG4 DCI → `frequency_domain_assignment`

```c
    else {
      // TS 38.214 subclause 5.1.2.2.2 Downlink resource allocation type 1
      dlsch_config_pdu->resource_alloc = 1;
      int riv = frequency_domain_assignment.val;
      dlsch_config_pdu->number_rbs = NRRIV2BW(riv,n_RB_DLBWP);
      dlsch_config_pdu->start_rb   = NRRIV2PRBOFFSET(riv,n_RB_DLBWP);
```

## Get PRB number from `time_domain_assignment`

```c
  NR_tda_info_t tda_info = get_dl_tda_info(current_DL_BWP,
                                           dci_ind->ss_type,
                                           dci->time_domain_assignment.val,
                                           dmrs_typeA_pos,
                                           mux_pattern,
                                           get_rnti_type(mac, dci_ind->rnti),
                                           coreset_type,
                                           mac->get_sib1);

  dlsch_pdu->number_symbols = tda_info.nrOfSymbols;
  dlsch_pdu->start_symbol = tda_info.startSymbolIndex;
```

## Get TBS by PRB and symbol

- **Starting from 1 and incrementing through all possible PRBs**
    
    Just like mentioned earlier, OAI is written entirely according to the 3GPP specifications, even following the same order. Therefore, when calculating TBS, it is necessary to use an **exhaustive method**, starting from 1 and incrementing through all possible PRBs, applying the formula to check if the TBS is sufficient.
    
- **Implementation fully adheres to the variable settings**
    
    Additionally, OAI's implementation fully adheres to the variable settings in the specifications, making all parameters that need to be considered for calculations as function inputs. Like: `nb_dmrs_prb`
    

<aside>
💡

Use **`nr_compute_tbs()`**

</aside>

## MCS table

```c
// the following tables contain 10 times the value reported in 214 (in line with SCF specification and to avoid fractional values)
//Table 5.1.3.1-1 of 38.214
static const uint16_t Table_51311[32][2] = {{2, 1200}, {2, 1570}, {2, 1930}, {2, 2510}, {2, 3080}, {2, 3790}, {2, 4490}, {2, 5260},
                                            {2, 6020}, {2, 6790}, {4, 3400}, {4, 3780}, {4, 4340}, {4, 4900}, {4, 5530}, {4, 6160},
                                            {4, 6580}, {6, 4380}, {6, 4660}, {6, 5170}, {6, 5670}, {6, 6160}, {6, 6660}, {6, 7190},
                                            {6, 7720}, {6, 8220}, {6, 8730}, {6, 9100}, {6, 9480}, {2, 0}, {4, 0}, {6, 0}};

```

## **Finds the TBSize from table**

```c
//Table 5.1.2.2-2
static const uint16_t Tbstable_nr[INDEX_MAX_TBS_TABLE] = {
    24,   32,   40,   48,   56,   64,   72,   80,   88,   96,   104,  112,  120,  128,  136,  144,  152,  160,  168,
    176,  184,  192,  208,  224,  240,  256,  272,  288,  304,  320,  336,  352,  368,  384,  408,  432,  456,  480,
    504,  528,  552,  576,  608,  640,  672,  704,  736,  768,  808,  848,  888,  928,  984,  1032, 1064, 1128, 1160,
    1192, 1224, 1256, 1288, 1320, 1352, 1416, 1480, 1544, 1608, 1672, 1736, 1800, 1864, 1928, 2024, 2088, 2152, 2216,
    2280, 2408, 2472, 2536, 2600, 2664, 2728, 2792, 2856, 2976, 3104, 3240, 3368, 3496, 3624, 3752, 3824};

```

```c
    // increase PRBs until we get to BWPSize or TBS is bigger than MAC PDU size
    do {
      if(rbSize < BWPSize)
        rbSize++;
      else
        mcsIndex++;
      LOG_D(NR_MAC,"Calling nr_compute_tbs with N_PRB_DMRS %d, N_DMRS_SLOT %d\n",dmrs_info.N_PRB_DMRS,dmrs_info.N_DMRS_SLOT);
      tb_size = nr_compute_tbs(nr_get_Qm_dl(mcsIndex, mcsTableIdx),
                                     nr_get_code_rate_dl(mcsIndex, mcsTableIdx),
                                     rbSize, msg4_tda.nrOfSymbols, dmrs_info.N_PRB_DMRS * dmrs_info.N_DMRS_SLOT, 0, tb_scaling,1) >> 3;
    } while (tb_size < pdu_length && mcsIndex<=28);
```

$$
\text{nbp}_{\text{re}} = \text{nb}_{\text{subcarrier\_per\_rb}} \cdot \text{nb}_{\text{symb\_sch}} - \text{nb}_{\text{dmrs\_prb}} - \text{nb}_{\text{rb\_oh}}
$$

$$
\text{nb}_{\text{re}} = \min(156, \text{nbp}_{\text{re}}) \cdot \text{nb}_{\text{rb}}

$$

$$
R_5 = \frac{R}{5}

$$

$$
N_{\text{info}} = \frac{(\text{nb}_{\text{re}} \times \frac{R}{5} \times Q_m \times N_l)}{2^{11 + \text{tb\_scaling}}}
$$

$$
n = \max\left(3, \left\lfloor \log_2(N_{\text{info}}) \right\rfloor - 6\right)

$$

$$
N_p^{\text{info}} = \max\left(24, \left(\frac{N_{\text{info}}}{2^n}\right) \cdot 2^n \right)

$$

$$
\text{nr\_tbs} = \min\left\{Tbstable_{\text{nr}}[i] \, \middle| \, Tbstable_{\text{nr}}[i] \geq N_p^{\text{info}} \right\}

$$

```c
// Transport block size determination according to 6.1.4.2 of TS 38.214
// returns the TBS in bits
uint32_t nr_compute_tbs(uint16_t Qm,
                        uint16_t R,
                        uint16_t nb_rb,
                        uint16_t nb_symb_sch,
                        uint16_t nb_dmrs_prb,
                        uint16_t nb_rb_oh,
                        uint8_t tb_scaling,
                        uint8_t Nl)
{

  LOG_D(NR_MAC, "In %s: nb_symb_sch %d, nb_dmrs_prb %d, nb_rb %d, nb_rb_oh %d, tb_scaling %d Nl %d\n", __FUNCTION__, nb_symb_sch, nb_dmrs_prb, nb_rb, nb_rb_oh, tb_scaling, Nl);

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
      }
  } else {
    n = log2(Ninfo-24)-5;
    Np_info = max(3840, (ROUNDIDIV((Ninfo-24),(1<<n)))<<n);

    if (R <= 2560) {
        C = CEILIDIV((Np_info+24),3816);
        nr_tbs = (C<<3)*CEILIDIV((Np_info+24),(C<<3)) - 24;
    } else {
      if (Np_info > 8424){
          C = CEILIDIV((Np_info+24),8424);
          nr_tbs = (C<<3)*CEILIDIV((Np_info+24),(C<<3)) - 24;
      } else {
        nr_tbs = ((CEILIDIV((Np_info+24),8))<<3) - 24;
      }
    }
  }

  LOG_D(NR_MAC, "In %s: Ninfo %u nbp_re %d nb_re %d Qm %d, R %d, tbs %d bits\n", __FUNCTION__, Ninfo, nbp_re, nb_re, Qm, R, nr_tbs);

  return nr_tbs;

}

```

# OAI VNF (DU)

<aside>
💡

Also use **`nr_compute_tbs()`**

</aside>

# Identify and resolve issues

From the above description, several issues can be identified. Besides the fact that OSC has some hardcoding within the function, OSC also omits the algorithm specified by the spec and calculates in the opposite way compared to OAI. This results in a discrepancy of one or two PRBs in the calculation of PRB size and TB size, which can cause serious consequences where the UE cannot decode. To resolve this issue, I reviewed the code and developed a new function to replace the original function used by OSC, thereby addressing the problem.

## Describe the issue:

I listed several cases that I believe have problems using Excel and found solutions. 

 The spec defines the process as step 1: calculate Nre, step 2: calculate Ninfo, step 3: calculate and look up the table to get the final TBsize.

Under the conditions of MCS = 0, num of Symbol = 13, DMRS symbol per slot = 3 -> nb_dmrs_prb = 36, OSC DU High will first look up the table (spec-defined step 3) with the current PDU size and then directly derive the PRB. At this point, OAI UE will only recalculate the TB size using the PRB number and symbol number obtained from frequency_domain_assignment and time_domain_assignment.

For example, if OSC DU High wants to send an 11-byte PDU, it will first look up the table (spec-defined step 3) and still get 11 bytes. Then, through the formula calculation, it will get 3.129 PRBs, and using the ceil() function, it will round up to 4 PRBs to send out. On the other hand, OAI UE, after receiving the PRB, symbol, MCS, etc., will calculate the TBS = 14 bytes using PRB number = 4.

Another aspect of the problem: The above issue can be resolved by changing OSC to round down (as per spec) instead of rounding up, similar to OAI. However, this introduces another problem: Suppose OSC DU High still wants to send an 11-byte PDU. After looking up the table, it still gets 11 bytes. After formula calculation, it gets 3.129 PRBs, and rounding down sends out 3 PRBs. OAI UE, after receiving this, calculates TBS = 84.38 bits -> according to the spec, before looking up the table, it needs to calculate max(24, (TBS>>n)<<n) to get 80 bits. Therefore, after looking up the table, it gets 10 bytes, which still does not equal 11 bytes.

$$
\max\left(24, Floor\left(\frac{N_{\text{info}}}{2^n}\right) \cdot 2^n \right)
  = max(24, (TBS>>n)<<n)
$$

To solve this, I added a piece of code at the end of the OSC function. Each time the PRB is calculated using the original method, it recalculates the TBS according to the spec. If the TBS is insufficient according to the spec, it continues to accumulate PRBs until the TBS calculated by the spec is sufficient for the actual value to be transmitted, thus updating the PRB size and TB size.

Detail about new function **`schCalcNumPrb_withDmrs`: [Develop schCalcNumPrb_withDmrs in OSC](Develop%20schCalcNumPrb_withDmrs%20in%20OSC%201211009831438173b598f24af78392d5.md)** 

In OSC, many parameters are set using `#define` constants, placed in header files for developers to manually adjust. However, I observed that many of these parameters are interrelated. Whether they should be determined by reference tables or through calculations, adjusting one parameter without automatically updating the related values can lead to entirely incorrect results being transmitted.

Detail about new function **`getNumDmrsSymbols` : [Develop **getNumDmrsSymbols** in OSC](Develop%20getNumDmrsSymbols%20in%20OSC%2012110098314381cea39ec544cb53b9b3.md)** 

Detail about new function **`getMcsTable`: [Develop **getMcsTable** in OSC](Develop%20getMcsTable%20in%20OSC%2012110098314381f0b3bce42ce2eefff6.md)** 

# 3GPP spec TS 38.214 version 15.3.0 Release 15

<aside>
💡

Reference: https://www.bing.com/ck/a?!&&p=1d8d730b530497c84a0a36d8995778be8729012ea03ca14a5234cdc2e0fe2be5JmltdHM9MTcyODUxODQwMA&ptn=3&ver=2&hsh=4&fclid=29a0e1c0-65fc-6fe8-08f0-f29764686e7b&psq=TS+38.214&u=a1aHR0cHM6Ly93d3cuZXRzaS5vcmcvZGVsaXZlci9ldHNpX3RzLzEzODIwMF8xMzgyOTkvMTM4MjE0LzE1LjAzLjAwXzYwL3RzXzEzODIxNHYxNTAzMDBwLnBkZg&ntb=1

</aside>

1 subcarriers = 12 PRB 

![{243FB2E1-E871-4CC9-9DD2-E9A913A59181}.png](243FB2E1-E871-4CC9-9DD2-E9A913A59181.png)

![{52FFBF88-7B52-41D2-9BD5-AB504044B580}.png](52FFBF88-7B52-41D2-9BD5-AB504044B580.png)

![{0BD2C04E-0A0A-4F03-858D-83FB7AAADB19}.png](0BD2C04E-0A0A-4F03-858D-83FB7AAADB19.png)

![{D5304DCD-ABD0-4B6B-8530-3842C4C680D6}.png](D5304DCD-ABD0-4B6B-8530-3842C4C680D6.png)

![{2D610D42-AE02-40E5-A532-6C4D2A5C667F}.png](2D610D42-AE02-40E5-A532-6C4D2A5C667F.png)

![{EFC58D4D-28B0-4C81-BC35-7A56E902B8F5}.png](EFC58D4D-28B0-4C81-BC35-7A56E902B8F5.png)

![{E90E9CA5-5908-4475-8E7C-73EA5AEFDCB2}.png](E90E9CA5-5908-4475-8E7C-73EA5AEFDCB2.png)

# Relate Note

- [Double Check TBS](Double%20Check%20TBS%20121100983143811d9175f1c7652e31e0.md)