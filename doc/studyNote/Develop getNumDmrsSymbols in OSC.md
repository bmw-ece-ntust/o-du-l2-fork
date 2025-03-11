# Develop getNumDmrsSymbols in OSC

Start Date: 2024/10/14
Summary: Developed a function to automate the calculation of the number of Demodulation Reference Signal (DMRS) symbols in OSC based on the DMRS mask, enhancing accuracy and reducing manual errors.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/14
SUM: 🗓️ Days Spent to Complete: 0

## **Development of DMRS Symbol Calculation in OSC**

In the context of OSC, parameters are often manually defined using `#define` constants in header files. This setup requires developers to make adjustments manually, but in many cases, parameters are interrelated and should be updated in sync. Manually adjusting these interconnected values introduces the risk of inconsistency and errors, especially when the parameters are derived from specification-defined rules, such as the number of Demodulation Reference Signal (DMRS) symbols based on the DMRS mask (`dlDmrsSymbPos`).

To minimize such risks, I developed a function that automates the calculation of the number of DMRS symbols (`nrOfDmrsSymbols`) based on the DMRS mask. This ensures that the number of DMRS symbols is computed dynamically, reducing the need for manual verification and adjustment. For instance, DMRS symbols are positioned according to a mask, and each symbol position corresponds to a bit in a 16-bit bitmap. Instead of manually counting and updating the number of DMRS symbols, this function accurately determines the number based on the mask.

### **Function Overview: `getNumDmrsSymbols`**

```c
/**
 * @brief Get the number of DMRS symbols
 *
 * @details
 *
 *     Function: getNumDmrsSymbols
 *
 *     This function calculates the number of DMRS symbols based on the DMRS mask.
 *
 *  @param[in]  dmrsMask - DMRS symbol position bitmap
 *  @return     Number of DMRS symbols
 **/
int getNumDmrsSymbols(uint16_t dmrsMask)
{
   int numDmrsSymbols = 0;
   for (int i = 0; i < 16; i++)
   {
      numDmrsSymbols += ((dmrsMask >> i) & 1);
   }
   return numDmrsSymbols;
}

```

The function `getNumDmrsSymbols` takes a 16-bit DMRS symbol position bitmap (`dmrsMask`) and counts the number of active DMRS symbols by iterating through the bitmap and checking each bit. This ensures that the number of DMRS symbols is correctly calculated without requiring manual intervention, ensuring alignment with the 3GPP specifications.

By automating this calculation, this function enhances accuracy and efficiency when configuring DMRS parameters in OSC. It reduces the chances of errors stemming from manual miscalculations and helps maintain consistency across related parameter values.