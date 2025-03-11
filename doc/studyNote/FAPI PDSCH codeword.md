# FAPI PDSCH codeword

Start Date: 2024/10/12
Summary: Implementation of FAPI PDSCH codeword handling and development of a new function to retrieve MCS table values.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/12
SUM: 🗓️ Days Spent to Complete: 0

## In SCF FAPI spec define

![{2285315C-E046-4037-9444-25B808FC1B37}.png](2285315C-E046-4037-9444-25B808FC1B37.png)

## OSC SIB1

```c
   for(cwCount = 0; cwCount < pdsch->numCodewords; cwCount++)
   {
      pdsch->codeword[cwCount].targetCodeRate = 308;
      pdsch->codeword[cwCount].qamModOrder = 2;
      pdsch->codeword[cwCount].mcsIndex = DEFAULT_MCS;
      pdsch->codeword[cwCount].mcsTable = 0; /* notqam256 */
      pdsch->codeword[cwCount].rvIndex = 0;
      tbSize = schCalcTbSize(sib1PduLen);
      pdsch->codeword[cwCount].tbSize = tbSize;
   }
```

### develop a new function `getMcsTable()`

[Develop **getMcsTable** in OSC](Develop%20getMcsTable%20in%20OSC%2012110098314381f0b3bce42ce2eefff6.md) 

```jsx
uint16_t getMcsTable(uint16_t mcs, uint8_t colIdx);
```

```c
uint16_t getMcsTable(uint16_t mcs, uint8_t colIdx)
{
   if (mcs < 32 && colIdx < 3)
   {
      return mcsTable[mcs][colIdx];
   }
   return 0; // Return 0 for invalid indices
}
```

```c
   for(cwCount = 0; cwCount < pdsch->numCodewords; cwCount++)
   {
      pdsch->codeword[cwCount].targetCodeRate = getMcsTable(SIB1_MCS,2);
      pdsch->codeword[cwCount].qamModOrder = getMcsTable(SIB1_MCS,1);
      pdsch->codeword[cwCount].mcsIndex = SIB1_MCS;
      pdsch->codeword[cwCount].mcsTable = 0; /* notqam256 */
      pdsch->codeword[cwCount].rvIndex = 0;
      tbSize = schCalcTbSize(sib1PduLen);
      pdsch->codeword[cwCount].tbSize = tbSize;
   }
```