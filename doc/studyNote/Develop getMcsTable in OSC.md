# Develop getMcsTable in OSC

Start Date: 2024/10/14
Summary: Developing the getMcsTable function in OSC to automate the retrieval of related parameters for improved accuracy and efficiency in parameter adjustments.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/14
SUM: 🗓️ Days Spent to Complete: 0

## **Development of Automated Parameter Calculation Functions for OSC**

In OSC, many parameters are set using `#define` constants, placed in header files for developers to manually adjust. However, I observed that many of these parameters are interrelated. Whether they should be determined by reference tables or through calculations, adjusting one parameter without automatically updating the related values can lead to entirely incorrect results being transmitted.

To address this issue, I began developing tool functions that enable OSC to automatically compute or look up related parameters based on specifications (e.g., 3GPP). This way, the parameters are calculated dynamically, minimizing the need for manual verification. For example, when modifying the Modulation and Coding Scheme (MCS), parameters like Qm (modulation order) and the target code rate should be derived from the relevant specification tables. However, in OSC, all three parameters (MCS, Qm, and code rate) are manually specified. To streamline this, I developed a function that, when given an MCS value, automatically looks up the corresponding Qm and code rate from the specification tables, reducing the need for manual table verification every time an OSC parameter is adjusted.

### **Function Overview: `getMcsTable`**

```c
/**
 * @brief Get value from MCS table
 *
 * @details
 *
 *     Function: getMcsTable
 *
 *     This function retrieves a value from the MCS table based on the MCS index and column index.
 *
 *  @param[in]  mcs - MCS index
 *  @param[in]  colIdx - Column index (1: Qm, 2: R)
 *  @return     Value from the MCS table
 **/
uint16_t getMcsTable(uint16_t mcs, uint8_t colIdx)
{
   if (mcs < 32 && colIdx < 3)
   {
      return mcsTable[mcs][colIdx];
   }
   return 0; // Return 0 for invalid indices
}

```

This function `getMcsTable` allows for automatic retrieval of the Qm (modulation order) and target code rate based on a given MCS index, reducing the chance of manual input errors and enhancing the efficiency and accuracy of parameter adjustments in OSC. By automating these relationships, this approach ensures that the values are consistent with the defined specifications, reducing the risk of incorrect data transmission.

## Application Example

- [FAPI PDSCH codeword](FAPI%20PDSCH%20codeword%2012110098314381479720f19089f29aa9.md)