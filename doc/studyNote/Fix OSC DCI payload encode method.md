# Fix OSC DCI payload encode method

Start Date: 2024/05/23
Summary: Fixing the OSC DCI payload encoding method to ensure proper bit positioning and interoperability with OAI.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

## Comment origin reverseBits function

The function only performs bit shifting, and its original purpose is uncertain. However, referencing the OAI encoding method, this step is deemed unnecessary and thus commented out.

```c
      /* Reversing bits in each DCI field */
      // printf("freqDomResAssign:%lx\n",freqDomResAssign);
      // freqDomResAssign = reverseBits(freqDomResAssign, freqDomResAssignSize);
      // printf("freqDomResAssign:%lx\n",freqDomResAssign);
      // timeDomResAssign = reverseBits(timeDomResAssign, timeDomResAssignSize);
      // // printf("timeDomResAssign:%x\n",timeDomResAssign);
      // VRB2PRBMap       = reverseBits(VRB2PRBMap, VRB2PRBMapSize);
      // modNCodScheme    = reverseBits(modNCodScheme, modNCodSchemeSize);
      // redundancyVer    = reverseBits(redundancyVer, redundancyVerSize);
      // sysInfoInd       = reverseBits(sysInfoInd, sysInfoIndSize);
```

## Ensure bitPos because MSB reversebits

DCI PDUs are not necessarily transmitted in byte units. For instance, in the current scenario, only 39 bits need to be transmitted, with an empty bit needing to be reserved at the Most Significant Bit (MSB) to ensure proper encoding. Therefore, while the original implementation fixed the bit position to 0, I adjusted it to dynamically calculate the starting bit position based on the determined DCI payload size.

```c
    //  if(dlDciPtr->PayloadSizeBits % 8)
    //     numBytes += 1;
    //   bitPos = 0;
    
      if(dlDciPtr->PayloadSizeBits % 8){
         numBytes += 1;
         bitPos = 8 - (dlDciPtr->PayloadSizeBits % 8);
      }
```

## Modifly fillDlDciPayload function

The function is divided into two parts, both of which had issues. In the first part, if the data size exactly fit into the current byte, it would be directly inserted, overwriting the LSB's data length position. Thus, I added a bit shift to the correct bit position. In the second part, when the data length exceeded the capacity of the byte, it would be split, and the remaining bits would be recursively inserted into the DCI payload. The original implementation's handling of bytePart1 and bytePart2 seemed counterintuitive to me, so I made adjustments. Currently, the encoding method is successfully interoperable with OAI.

The commented-out section is the OSC original code.

```c
void fillDlDciPayload(uint8_t *buf, uint8_t *bytePos, uint8_t *bitPos,\
      uint32_t val, uint8_t valSize)
{
   uint8_t temp;
   uint8_t bytePart1;
   uint32_t bytePart2;
   uint8_t bytePart1Size;
   uint8_t bytePart2Size;

   if(*bitPos + valSize <= 8)
   {
      bytePart1 = (uint8_t)val;
      bytePart1 = (~((~0) << valSize)) & bytePart1;
      // buf[*bytePos] |= bytePart1;
      buf[*bytePos] |= bytePart1 << (8-*bitPos-valSize);

      *bitPos += valSize;
   }
   else if(*bitPos + valSize > 8)
   {
      temp = (uint8_t)val;
      bytePart1Size = 8 - *bitPos;
      bytePart2Size = valSize - bytePart1Size;
      // bytePart1 = ((~((~0) << bytePart1Size)) & temp) << *bitPos;
      bytePart1 = (val >> bytePart2Size) & (~((~0) << bytePart1Size));
      bytePart2 = ((~((~0) << bytePart2Size)) & val);
      // bytePart2 = val >> bytePart1Size;

      buf[*bytePos] |= bytePart1;
      (*bytePos)--;
      *bitPos = 0;
      fillDlDciPayload(buf, bytePos, bitPos, bytePart2, bytePart2Size);
   }
}

```