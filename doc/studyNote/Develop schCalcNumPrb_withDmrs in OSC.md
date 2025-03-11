# Develop schCalcNumPrb_withDmrs in OSC

Start Date: 2024/10/13
Summary: Developing the schCalcNumPrb_withDmrs function in OSC to dynamically calculate the number of Physical Resource Blocks (PRBs) and adjust the Transport Block (TB) size, addressing issues related to hard-coded parameters and discrepancies in calculations.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/14
SUM: 🗓️ Days Spent to Complete: 1

### Development Note for `schCalcNumPrb_withDmrs`

### Problem Overview:

In the OSC implementation, the Transport Block (TB) size and Physical Resource Block (PRB) size are derived using formula transposition, allowing for flexible calculations. However, certain parameters in the function, such as `nb_dmrs_prb`, are hard-coded as constants rather than passed as inputs. Specifically, `nb_dmrs_prb` is set to 12 in OSC.

This hard-coding becomes problematic when dealing with specific scenarios, such as when `dlDmrsSymbPos` is adjusted in MSG4. In this case, `nb_dmrs_prb` should be 36 instead of 12. This mismatch leads to issues like invalid CCCH in MSG4 at the UE, since the calculation does not correctly account for the increased number of DMRS Resource Elements (REs) per PRB.

The calculation process defined in the specification involves three steps:

1. Calculate `Nre` (number of Resource Elements).
2. Calculate `Ninfo` (number of information bits).
3. Look up a table to determine the final Transport Block (TB) size.

However, a discrepancy arises between the OSC DU High and OAI UE implementations when rounding PRB calculations:

- **OSC DU High**: Rounds PRB values up using `ceil()`, causing the calculated PRB number to exceed what is needed. For instance, sending an 11-byte PDU results in 4 PRBs being used.
- **OAI UE**: Follows spec-defined steps and recalculates the TB size using the PRB number, symbol count, and MCS. This recalculation results in a TB size mismatch.

This mismatch can result in insufficient TB sizes, as rounding up gives OAI a larger TB than required, while rounding down could result in a smaller TB size after table lookup.

### Solution:

The issue can be resolved by:

1. Adding a final recalculation step to the OSC DU High function.
2. Ensuring the recalculated TB size complies with the specification by accumulating additional PRBs as needed.

This way, after each initial PRB calculation, the TB size is recalculated according to the spec. If the recalculated TB size is insufficient, more PRBs are added until the spec-compliant TB size is sufficient to match the actual data being sent.

To resolve this issue, the `nb_dmrs_prb` parameter was updated to be dynamically calculated based on the current configuration (e.g., `dlDmrsSymbPos`). This allows the function to handle different scenarios correctly, such as when MSG4 requires an increased `nb_dmrs_prb` value of 36. By making `nb_dmrs_prb` flexible and aligned with the current conditions, the function ensures proper PRB calculation and avoids invalid signaling at the UE.

### Implementation of `schCalcNumPrb_withDmrs` Function:

```jsx
/*A structure containing the calculated number of PRBs and the adjusted TB size.*/
typedef struct {
    uint16_t numPrb;
    uint16_t tbSize;
} schCalcResult;
```

```jsx
#define max(a,b) ((a) > (b) ? (a) : (b))
```

```c
/**
 * @brief frequency domain allocation function.
 *
 * @details
 *     Function: schCalcNumPrb_withDmrs
 *     Calculates the number of Physical Resource Blocks (PRBs) required for a given Transport Block (TB) size,
 *     considering DMRS overhead. The calculation follows the 3GPP 38.214 specification and checks with OAI methods.
 *
 * @param[in]  tbSize - The size of the Transport Block (TB) in bytes.
 * @param[in]  mcs - The Modulation and Coding Scheme (MCS) index.
 * @param[in]  numSymbols - number of symbols.
 * @param[in]  numDmrsRePerPrb - The number of DMRS Resource Elements (REs) per PRB.
 * @return  schCalcResult - A structure containing the calculated number of PRBs and the adjusted TB size.
 **/
schCalcResult schCalcNumPrb_withDmrs(uint16_t tbSize, uint16_t mcs, uint8_t numSymbols, uint8_t numDmrsRePerPrb)
{
   schCalcResult result;
   uint16_t numPrb = 0;
   uint16_t nre = 0;
   uint16_t nreDash = 0;
   uint8_t  qm     = mcsTable[mcs][1];
   uint16_t rValue = mcsTable[mcs][2];
   uint8_t  numLayer = 1;       /* v value */
   tbSize = tbSize * 8; //Calculate tbSize in bits

   /* Formula: 38.214 section 5.1.3.2
    * Ninfo = S * Nre * R * Qm * v
    * Nre' = Nsc * NsymPdsch - NdmrsSymb - Noh
    * Nre = min(156, Nre') * nPrb
    */

   nreDash = ceil( (12 * numSymbols) - numDmrsRePerPrb - 0);

   if (nreDash > 156)
      nreDash = 156;

   numPrb = floor(tbSize * 1024.0 / (rValue * qm * numLayer * nreDash));

   /* OAI double-check */
   uint32_t n, ninfo, npinfo;
   uint8_t tbsIndex;
   for (int i = 0; i < 2; i++) {
      ninfo = (rValue * qm * numLayer * nreDash * numPrb) >> 10;
      n = max(3, floor(log2(ninfo)) - 6);
      npinfo = max(24, (ninfo >> n) << n);
      tbsIndex = 0;
      while(npinfo > tbSizeTable[tbsIndex]) /* search Table */
         tbsIndex++;
      ninfo = tbSizeTable[tbsIndex];
      if(tbSize <= tbSizeTable[tbsIndex])
         break;
      else
         numPrb++;
   }

   result.numPrb = numPrb;
   result.tbSize = tbSizeTable[tbsIndex] / 8;
   return result;
}

```

### Key Adjustments:

- **Recalculation of TB size**: If the calculated TB size does not match the required size after PRB determination, the function accumulates more PRBs until a sufficient size is reached.
- **Table lookup and PRB rounding**: To handle PRB rounding discrepancies between OSC DU High and OAI, the function follows the spec's floor rounding behavior while ensuring the final size is correct.
- **Dynamic `nb_dmrs_prb`**: Rather than hard-coding this parameter, it is now calculated based on the actual number of DMRS symbols required per slot, reflecting adjustments such as those in MSG4 where `nb_dmrs_prb` should be 36.
- **Addressing CCCH in MSG4**: This change fixes issues where the UE would receive an invalid CCCH due to incorrect PRB calculations.

This approach ensures the calculated PRBs and TB size are accurate according to both the spec and the practical constraints of OAI UE.