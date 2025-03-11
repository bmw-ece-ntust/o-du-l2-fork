# Speed up UL_TTI

Start Date: 2024/04/23
Summary: Refactored UL TTI request handling in the PNF P7 module to improve code clarity and modularity.
Status: Done
Assign: Ming 咚咚 [銘鴻]

Refactor UL TTI request handling and add clarity to function logic

This commit refactors the UL TTI request handling in the PNF P7 module and improves the clarity of function logic.

Changes made:

- Refactored UL TTI request handling to simplify code structure and improve readability.
- Introduced a static function, `cp_nr_ul_tti_req`, to copy UL TTI request structures, improving code modularity and reducing duplication.
- Updated UL TTI request processing to utilize the refactored logic.
- Removed unnecessary deallocation of UL TTI request in error handling path to prevent double deallocation.

Additionally, the commit enhances comments and debug traces for better understanding of the code flow and debugging.