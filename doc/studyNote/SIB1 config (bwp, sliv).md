# SIB1 config (bwp, sliv)

Start Date: 2024/10/12
Summary: Configuration details for SIB1, including parameters for coreset0, BWP, and SLIV, along with associated code snippets and specifications.
Status: padding
Assign: Ming 咚咚 [銘鴻]

## **fillSchSib1Cfg**

mwnl-odu-at-oai-based-on-scf/l2/src/5gnrsch/sch.c 

### **coreset0 params**

| **coreset0Idx**  | 12 | **searchSpace0Idx**  | 0 |
| --- | --- | --- | --- |
| **numRbs**  | 48 | **oValue**  | 0 |
| **numSymbols**  | 1 | **oValue**  | 2 |
| **offset** | 16 | **firstSymbol**  | 0 |

<aside>
💡

[Information about **CORESET** ](https://www.notion.so/Information-about-CORESET-12110098314381ff98a6cb9b8698f6ba?pvs=21) 

</aside>

```c
 coreset0Idx     = pdcchCfgSib1->coresetZeroIndex;
 searchSpace0Idx = pdcchCfgSib1->searchSpaceZeroIndex;

 /* derive the sib1 coreset0 params from table 13-4 spec 38.213 */
 //ssbMuxPattern = coresetIdxTable[coreset0Idx][0];
 numRbs        = coresetIdxTable[coreset0Idx][1];
 numSymbols    = coresetIdxTable[coreset0Idx][2];
 offset        = coresetIdxTable[coreset0Idx][3];
 
 /* derive the search space params from table 13-11 spec 38.213 */
 oValue                = searchSpaceIdxTable[searchSpace0Idx][0];
 //numSearchSpacePerSlot = searchSpaceIdxTable[searchSpace0Idx][1];
 mValue                = searchSpaceIdxTable[searchSpace0Idx][2];
 firstSymbol           = searchSpaceIdxTable[searchSpace0Idx][3];
```

![{1974673E-6AE8-4818-8111-5E7F0C21608C}.png](1974673E-6AE8-4818-8111-5E7F0C21608C.png)

![{816AA08F-5002-4824-B85C-F33E4A11571D}.png](816AA08F-5002-4824-B85C-F33E4A11571D.png)

```cpp
#ifdef NFAPI
#define CORESET_0_INDEX      12
#else
#define CORESET_0_INDEX      0
#endif
#define SEARCHSPACE_0_INDEX   0
```

### BWP

![{2F5C77C5-405C-4172-B661-265CA03C0C28}.png](2F5C77C5-405C-4172-B661-265CA03C0C28.png)

![{67C738A1-B9DE-40A5-9198-138C12A83543}.png](67C738A1-B9DE-40A5-9198-138C12A83543.png)

```c
   /* fill BWP */
   switch(bandwidth)
   {
      case BANDWIDTH_20MHZ:
	 {
            bwp->freqAlloc.numPrb = TOTAL_PRB_20MHZ_MU0;
	 }
	 break;
      case BANDWIDTH_100MHZ:
	 {
/* ======== small cell integration ======== */
#ifdef NFAPI
            bwp->freqAlloc.numPrb = numRbs; /*For OAI*/
#else
            bwp->freqAlloc.numPrb = TOTAL_PRB_100MHZ_MU1;
#endif
/* ======================================== */
	 }
	 break;
      default:
	 DU_LOG("\nERROR  -->  SCH : Bandwidth %d not supported", bandwidth);

   }
/* ======== small cell integration ======== */
#ifdef NFAPI
   bwp->freqAlloc.startPrb = 27;             /* From 27 */
   bwp->subcarrierSpacing  = 1;              /* 30Khz */
#else
   bwp->freqAlloc.startPrb = 0;
   bwp->subcarrierSpacing  = 0;         /* 15Khz */
#endif
   bwp->cyclicPrefix       = 0;              /* normal */
/* ======================================== */

```

```c
/* PRB allocation as per 38.101, Section 5.3.2 */
#define TOTAL_PRB_20MHZ_MU0 106
#define TOTAL_PRB_40MHZ_MU1 106 //OAI
#define TOTAL_PRB_100MHZ_MU1 273
#ifdef NR_TDD
   #ifdef NFAPI
      #define MAX_NUM_RB TOTAL_PRB_100MHZ_MU1  /*//Use OSC 100MHz value for numerology 1, 100 MHz */
   #else
      #define MAX_NUM_RB TOTAL_PRB_100MHZ_MU1  /* value for numerology 1, 100 MHz */
   #endif
#else
#define MAX_NUM_RB TOTAL_PRB_20MHZ_MU0 /* value for numerology 0, 20 MHz */
#endif
```

### SLIV

### StartSymbol

```jsx
pdsch->pdschTimeAlloc.startSymb = 3; /* spec-38.214, Table 5.1.2.1-1 */
pdsch->pdschTimeAlloc.numSymb   = NUM_PDSCH_SYMBOL;
```

![{2893AFBB-8884-448D-88EE-40628F791666}.png](2893AFBB-8884-448D-88EE-40628F791666.png)

![{4F93E5B6-BBC7-492C-AF7B-380BB0935BEB}.png](4F93E5B6-BBC7-492C-AF7B-380BB0935BEB.png)