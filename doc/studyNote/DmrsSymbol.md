# DmrsSymbol

Start Date: 2024/09/30
Summary: Determine the total number of symbols occupied by the Physical Downlink Shared Channel (PDSCH), including Demodulation Reference Signal (DMRS) symbols, using a specific code function.
Status: Done
Assign: Ming 咚咚 [銘鴻]

### Note on PDSCH Symbol Occupation Including DMRS

### Context

The following code snippet is used to determine the total number of symbols occupied by the Physical Downlink Shared Channel (PDSCH), including the Demodulation Reference Signal (DMRS) symbols. This is achieved by calling the `findDmrsStartSymbol` function and then using its result to decide how to mark the symbols as occupied.

### Code Explanation

```c
/**
 * @brief Function to find first DMRS symbol in PDSCH
 *
 * @details
 *
 *     Function: findDmrsStartSymbol
 *
 *     This function finds first DMRS symbol using DMRS symbol 
 *     position bitmap.
 *
 *  @param[in]  DMRS symbol position bitmap
 *  @return     Success : First DRMS symbol
 *              Failure : MAX_SYMB_PER_SLOT 
 **/
uint8_t findDmrsStartSymbol(uint16_t dlDmrsSymbBitMap)
{
   uint8_t position = 0;
   uint16_t mask = 1;

   while(position < MAX_SYMB_PER_SLOT)
   {
      if(dlDmrsSymbBitMap & mask)
         break;  
      mask = mask << 1;
      position++;
   }
   return position;   
}
```

```c
/* Find total symbols occupied including DMRS */
dmrsStartSymbol = findDmrsStartSymbol(pdsch->dmrs.dlDmrsSymbPos);

/* If there are no DRMS symbols, findDmrsStartSymbol() returns MAX_SYMB_PER_SLOT,
 * in that case only PDSCH symbols are marked as occupied */
if(dmrsStartSymbol == MAX_SYMB_PER_SLOT)
{
   printf("\\nMSG4: No DMRS symbols found");
   startSymbol = pdsch->pdschTimeAlloc.startSymb;
   numSymbol = pdsch->pdschTimeAlloc.numSymb;
}
/* If DMRS symbol is found, mark DMRS and PDSCH symbols as occupied */
else
{
   printf("\\nMSG4: DMRS symbols found at %d, nrOfDmrsSymbols %d\\n", dmrsStartSymbol, pdsch->dmrs.nrOfDmrsSymbols);
   startSymbol = dmrsStartSymbol;
   numSymbol = pdsch->dmrs.nrOfDmrsSymbols + pdsch->pdschTimeAlloc.numSymb;
}

```

### Detailed Steps

1. **Finding DMRS Start Symbol:**
    - The function `findDmrsStartSymbol` is called with `pdsch->dmrs.dlDmrsSymbPos` as the argument. This function returns the position of the first DMRS symbol in the bitmap.
2. **Handling No DMRS Symbols:**
    - If `findDmrsStartSymbol` returns `MAX_SYMB_PER_SLOT`, it indicates that no DMRS symbols are found.
    - In this case, only the PDSCH symbols are marked as occupied.
    - The start symbol is set to `pdsch->pdschTimeAlloc.startSymb`.
    - The number of symbols is set to `pdsch->pdschTimeAlloc.numSymb`.
    - A message is printed to indicate that no DMRS symbols were found.
3. **Handling Found DMRS Symbols:**
    - If a DMRS symbol is found, the start symbol is set to the position of the first DMRS symbol.
    - The total number of symbols is calculated by adding the number of DMRS symbols (`pdsch->dmrs.nrOfDmrsSymbols`) to the number of PDSCH symbols (`pdsch->pdschTimeAlloc.numSymb`).
    - A message is printed to indicate the position of the first DMRS symbol and the number of DMRS symbols found.

### Practical Application

This code is crucial in scenarios where it is necessary to determine the exact symbol occupation in a slot for PDSCH, including any DMRS symbols. This information is used for resource allocation and scheduling in the physical layer of a communication system. By accurately marking the occupied symbols, the system can ensure efficient utilization of resources and avoid conflicts in symbol allocation.