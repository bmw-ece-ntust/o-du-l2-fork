# POCCH freqDomainResource

Start Date: 2024/05/24
Summary: Development of frequency domain resource allocation functions for NR control resource sets.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

```c
void fillCoresetFeqDomAllocMap(uint16_t startPrbGrp, uint16_t numPrbGrp, uint8_t *freqDomain)
{
   uint8_t  idx;
   uint8_t  prbGrpStartBit = 0;
   uint8_t  numBitsToRightShift = 0;
   uint64_t mask = 0;
   uint64_t freqAllocBitMap = 0;

   /* 
    * Frequency allocation bit string is 45 bits long. Hence using 6 bytes (i.e. 48 bits) to represent it.
    * Each bit corresponds to a group of 6 RBs.
    *
    * For example if a coreset includes PRB 24 to 47, then on dividing the PRBs into group of 6, 
    * startPrbGrp = 24/6 = 4
    * numPrbGrp = 24/6 = 4
    * 
    * Frequency allocation bit string is 48 bits long i.e. Bit 47...0
    * Here, Bit 47 represents RB group 0, Bit 46 represent RB group 45 and so on.
    * Since startPrbGrp = 4 and numPrbGrp = 4, it means RB group 4,5,6 and 7 are used in coreset.
    * i.e. Bits 43, 42, 42 and 40 are masked to 1 and rest all bits are 0 in bitstring    
    */
   prbGrpStartBit = 47; 
   while(numPrbGrp)
   {
      mask = 1;
      mask = mask << (prbGrpStartBit - startPrbGrp);
      freqAllocBitMap = freqAllocBitMap | mask;
      startPrbGrp++;
      numPrbGrp--;
   }

   /* Copying 48 LSBs from 64-bit integer to the 45 MSBS in 6-byte array 
    * The first (left-most / most significant) bit corresponds to the first RB
    * group in the BWP, and so on
    */
   /* On right shifting freqAllocBitMap by 40 bits, the bits 47 to 40 of freqAllocBitMap 
    * will now become 8-LSB. Copying these 8-bits into freqDomain[].
    * Now shifting freqAllocBitMap by 32 bits, the bit 39 to 32 of freqAllocBitMap will
    * now become 8-LSB. Copying these 8-bits into next index of freqDomain.
    * and so on.
    */
   numBitsToRightShift = 40; 
   mask = 0x0000FF0000000000;
   for(idx=0; idx<FREQ_DOM_RSRC_SIZE; idx++)
   {
      freqDomain[idx] = (freqAllocBitMap & mask) >> numBitsToRightShift;
      numBitsToRightShift -= 8;
      mask = mask >> 8;
   }
}
```

```c
void fill_coresetZero(NR_ControlResourceSet_t *coreset0, NR_Type0_PDCCH_CSS_config_t *type0_PDCCH_CSS_config)
{
  ****AssertFatal(type0_PDCCH_CSS_config, "No type0 CSS configuration\n");
  AssertFatal(coreset0, "Coreset0 should have been allocated outside of this function\n");
  coreset0->controlResourceSetId = 0;
  int duration = type0_PDCCH_CSS_config->num_symbols;

  if(coreset0->frequencyDomainResources.buf == NULL)
    coreset0->frequencyDomainResources.buf = calloc(1,6);

  switch(type0_PDCCH_CSS_config->num_rbs){
    case 24:
      coreset0->frequencyDomainResources.buf[0] = 0xf0;
      coreset0->frequencyDomainResources.buf[1] = 0;
      break;
    case 48:
      coreset0->frequencyDomainResources.buf[0] = 0xff;
      coreset0->frequencyDomainResources.buf[1] = 0;
      break;
    case 96:
      coreset0->frequencyDomainResources.buf[0] = 0xff;
      coreset0->frequencyDomainResources.buf[1] = 0xff;
      break;
  default:
    AssertFatal(1==0,"Invalid number of PRBs %d for Coreset0\n",type0_PDCCH_CSS_config->num_rbs);
  }
  coreset0->frequencyDomainResources.buf[2] = 0;
  coreset0->frequencyDomainResources.buf[3] = 0;
  coreset0->frequencyDomainResources.buf[4] = 0;
  coreset0->frequencyDomainResources.buf[5] = 0;
```

frequencyDomainResources

45 bits

5 8 8 8 8 8