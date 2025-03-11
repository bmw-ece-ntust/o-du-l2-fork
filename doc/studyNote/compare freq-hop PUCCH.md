# compare freq-hop PUCCH

Start Date: 2024/10/14
Summary: Comparison of frequency-hopping PUCCH configurations and their corresponding parameters across different setups.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Compare
Finish Date: 2024/10/16
SUM: 🗓️ Days Spent to Complete: 2

## **PUCCH Config**

| 項目 | OAI value | OSC vlaue |
| --- | --- | --- |
| rnti | 13439 | 100 |
| handle | 0 | 0 |
| bwp_size | 106 | 106 |
| bwp_start | 0 | 0 |
| subcarrier_spacing | 1 | 1 |
| cyclic_prefix | 0 | 0 |
| format_type | 0 | 0 |
| multi_slot_tx_indicator | 0 | 0 |
| pi_2bpsk | 0 | 0 |
| prb_start | 0 | 0 |
| prb_size | 1 | 1 |
| start_symbol_index | 12 | 12 |
| nr_of_symbols | 2 | 2 |
| freq_hop_flag | 1 | 0 |
| second_hop_prb | 105 | 0 |
| group_hop_flag | 0 | 0 |
| sequence_hop_flag | 0 | 0 |
| hopping_id | 40 | 0 |
| initial_cyclic_shift | 0 | 0 |
| data_scrambling_id | 0 | 0 |
| time_domain_occ_idx | 0 | 0 |
| pre_dft_occ_idx | 0 | 0 |
| pre_dft_occ_len | 0 | 0 |
| add_dmrs_flag | 0 | 0 |
| dmrs_scrambling_id | 0 | 0 |
| dmrs_cyclic_shift | 0 | 0 |
| sr_flag | 0 | 1 |
| bit_len_harq | 1 | 1 |
| bit_len_csi_part1 | 0 | 0 |
| bit_len_csi_part2 | 0 | 0 |

| **參數名稱** | **值** |
| --- | --- |
| rnti | 100 |
| handle | 0 |
| bwp_size | 106 |
| bwp_start | 0 |
| subcarrier_spacing | 1 |
| cyclic_prefix | 0 |
| format_type | 0 |
| multi_slot_tx_indicator | 0 |
| pi_2bpsk | 0 |
| prb_start | 0 |
| prb_size | 1 |
| start_symbol_index | 12 |
| nr_of_symbols | 2 |
| freq_hop_flag | 0 |
| second_hop_prb | 0 |
| group_hop_flag | 0 |
| sequence_hop_flag | 0 |
| hopping_id | 0 |
| initial_cyclic_shift | 0 |
| data_scrambling_id | 0 |
| time_domain_occ_idx | 0 |
| pre_dft_occ_idx | 0 |
| pre_dft_occ_len | 0 |
| add_dmrs_flag | 0 |
| dmrs_scrambling_id | 0 |
| dmrs_cyclic_shift | 0 |
| sr_flag | 0 |
| bit_len_harq | 1 |
| bit_len_csi_part1 | 0 |
| bit_len_csi_part2 | 0 |

## OAI UE receive and fill PUCCH config

<aside>
💡

By tracing the code, I believe the data in the UE is obtained from an ASN.1 message. Therefore, I think it would be beneficial to print it out and compare it first.

- ‣
</aside>

```c
static void configure_dedicated_BWP_ul(NR_UE_MAC_INST_t *mac, int bwp_id, NR_BWP_UplinkDedicated_t *ul_dedicated)
{
  LOG_I(NR_MAC, "Configuring UL BWP %d\n", bwp_id);
  if (ul_dedicated) {
    LOG_I(NR_MAC, "Configuring ul_dedicated\n");
    NR_UE_UL_BWP_t *bwp = get_ul_bwp_structure(mac, bwp_id, true);
    bwp->bwp_id = bwp_id;
    if(ul_dedicated->pucch_Config) {
      LOG_I(NR_MAC, "Configuring PUCCH\n");
      if (ul_dedicated->pucch_Config->present == NR_SetupRelease_PUCCH_Config_PR_release)
        asn1cFreeStruc(asn_DEF_NR_PUCCH_Config, bwp->pucch_Config);
      if (ul_dedicated->pucch_Config->present == NR_SetupRelease_PUCCH_Config_PR_setup) {
        if (!bwp->pucch_Config)
          bwp->pucch_Config = calloc(1, sizeof(*bwp->pucch_Config));
        setup_pucchconfig(ul_dedicated->pucch_Config->choice.setup, bwp->pucch_Config);
      }
    }
    if(ul_dedicated->pusch_Config) {
      if (ul_dedicated->pusch_Config->present == NR_SetupRelease_PUSCH_Config_PR_release)
        asn1cFreeStruc(asn_DEF_NR_PUSCH_Config, bwp->pusch_Config);
      if (ul_dedicated->pusch_Config->present == NR_SetupRelease_PUSCH_Config_PR_setup) {
        if (!bwp->pusch_Config)
          bwp->pusch_Config = calloc(1, sizeof(*bwp->pusch_Config));
        setup_puschconfig(ul_dedicated->pusch_Config->choice.setup, bwp->pusch_Config);
      }
    }
```

## **OSC DU High fill PUCCH Config**

```c
typedef struct schPucchInfo
{
   uint16_t         rnti;
   uint8_t          pucchFormat;
   FreqDomainAlloc  fdAlloc;      /* Freq domain allocation */
   TimeDomainAlloc  tdAlloc;      /* Time domain allocation */
   uint8_t          srFlag;
   uint8_t          harqFlag;
   uint8_t          numHarqBits;
   uint8_t          uciFlag;
   uint8_t          numUciBits;
   uint8_t          intraFreqHop;
   uint16_t         secondPrbHop;
   uint8_t          initialCyclicShift;
   uint8_t          occLen;
   uint8_t          occIdx;
   uint8_t          timeDomOCC;
   SchPucchFormatCfg cmnFormatCfg;
}SchPucchInfo;
```

```jsx
   {
      /* fill pucch common cfg */
      /* derive pucchResourceSet from schCellCfg */
      pucchCfg = &cell->cellCfg.ulCfgCommon.schInitialUlBwp.pucchCommon;
      pucchIdx = pucchCfg->pucchResourceCommon;
      ulBwp = &cell->cellCfg.ulCfgCommon.schInitialUlBwp.bwp;
      startPrb = ulBwp->freqAlloc.startPrb + pucchResourceSet[pucchIdx][3];
      ret = allocatePrbUl(cell, slotInfo, pucchResourceSet[pucchIdx][1], pucchResourceSet[pucchIdx][2],\
            &startPrb, PUCCH_NUM_PRB_FORMAT_0_1_4);
      if (ret == ROK)
      {
         schPucchInfo->fdAlloc.startPrb = ulBwp->freqAlloc.startPrb + pucchResourceSet[pucchIdx][3];
         schPucchInfo->fdAlloc.numPrb = PUCCH_NUM_PRB_FORMAT_0_1_4;
         schPucchInfo->tdAlloc.startSymb = pucchResourceSet[pucchIdx][1];
         schPucchInfo->tdAlloc.numSymb = pucchResourceSet[pucchIdx][2];
         schPucchInfo->pucchFormat = pucchResourceSet[pucchIdx][0];
```

```c
#define PUCCH_NUM_PRB_FORMAT_0_1_4 1  /* number of PRBs in freq domain, spec 38.213 - 9.2.1 */
```

### pucchResourceSet

![image.png](image%2085.png)

```c
/* PUCCH resource sets before dedicated PUCCH resource configuration */
/* Table 9.2.1-1 spec 38.213      */ 
uint8_t pucchResourceSet[MAX_PUCCH_RES_SET_IDX][4] = {
{ 0,  12,  2,  0 }, /* index  0 */
{ 0,  12,  2,  0 }, /* index  1 */
{ 0,  12,  2,  3 }, /* index  2 */
{ 1,  10,  4,  0 }, /* index  3 */
{ 1,  10,  4,  0 }, /* index  4 */
{ 1,  10,  4,  2 }, /* index  5 */
{ 1,  10,  4,  4 }, /* index  6 */
{ 1,   4, 10,  0 }, /* index  7 */
{ 1,   4, 10,  0 }, /* index  8 */
{ 1,   4, 10,  2 }, /* index  9 */
{ 1,   4, 10,  4 }, /* index 10 */
{ 1,   0, 14,  0 }, /* index 11 */
{ 1,   0, 14,  0 }, /* index 12 */
{ 1,   0, 14,  2 }, /* index 13 */
{ 1,   0, 14,  4 }, /* index 14 */
{ 1,   0, 14,  0 }, /* index 15 */
};
```

## OAI VNF Fill PUCCH

```c
//for pucch_pdu:
typedef struct
{
  uint16_t rnti;
  uint32_t handle;
  //BWP
  uint16_t bwp_size;
  uint16_t bwp_start;
  uint8_t  subcarrier_spacing;
  uint8_t  cyclic_prefix;

  uint8_t  format_type;
  uint8_t  multi_slot_tx_indicator;
  uint8_t  pi_2bpsk;
  //pucch allocation in freq domain
  uint16_t prb_start;
  uint16_t prb_size;
  //pucch allocation in tome domain
  uint8_t  start_symbol_index;
  uint8_t  nr_of_symbols;
  //hopping info
  uint8_t  freq_hop_flag;
  uint16_t second_hop_prb;
  uint8_t  group_hop_flag;
  uint8_t  sequence_hop_flag;
  uint16_t hopping_id;
  uint16_t initial_cyclic_shift;

  uint16_t data_scrambling_id;
  uint8_t  time_domain_occ_idx;
  uint8_t  pre_dft_occ_idx;
  uint8_t  pre_dft_occ_len;
  //DMRS
  uint8_t  add_dmrs_flag;
  uint16_t dmrs_scrambling_id;
  uint8_t  dmrs_cyclic_shift;

  uint8_t  sr_flag;
  uint8_t  bit_len_harq;
  uint16_t bit_len_csi_part1;
  uint16_t bit_len_csi_part2;

  nfapi_nr_ul_beamforming_t beamforming;

} nfapi_nr_pucch_pdu_t;
```

```c
const int default_pucch_fmt[]       = {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1};
const int default_pucch_firstsymb[] = {12,12,12,10,10,10,10,4,4,4,4,0,0,0,0,0};
const int default_pucch_numbsymb[]  = {2,2,2,2,4,4,4,4,10,10,10,10,14,14,14,14,14};
const int default_pucch_prboffset[] = {0,0,3,0,0,2,4,0,0,2,4,0,0,2,4,-1};
const int default_pucch_csset[]     = {2,3,3,2,4,4,4,2,4,4,4,2,4,4,4,4};
```

```c
void set_r_pucch_parms(int rsetindex,
                       int r_pucch,
                       int bwp_size,
                       int *prb_start,
                       int *second_hop_prb,
                       int *nr_of_symbols,
                       int *start_symbol_index) {

  // procedure described in 38.213 section 9.2.1

  int prboffset = r_pucch/default_pucch_csset[rsetindex];
  int prboffsetm8 = (r_pucch-8)/default_pucch_csset[rsetindex];

  *prb_start = (r_pucch>>3)==0 ?
              default_pucch_prboffset[rsetindex] + prboffset:
              bwp_size-1-default_pucch_prboffset[rsetindex]-prboffsetm8;

  *second_hop_prb = (r_pucch>>3)==0?
                   bwp_size-1-default_pucch_prboffset[rsetindex]-prboffset:
                   default_pucch_prboffset[rsetindex] + prboffsetm8;

  *nr_of_symbols = default_pucch_numbsymb[rsetindex];
  *start_symbol_index = default_pucch_firstsymb[rsetindex];
}
```

```c
  } else { // this is the default PUCCH configuration, PUCCH format 0 or 1
    LOG_I(NR_MAC,
          "pucch_acknak: Filling default PUCCH configuration from Tables (r_pucch %d, pucch_Config %p)\n",
          r_pucch,
          pucch_Config);
    int rsetindex = *pucch_ConfigCommon->pucch_ResourceCommon;
    int prb_start, second_hop_prb, nr_of_symb, start_symb;
    set_r_pucch_parms(rsetindex,
                      r_pucch,
                      pucch_pdu->bwp_size,
                      &prb_start,
                      &second_hop_prb,
                      &nr_of_symb,
                      &start_symb);

    pucch_pdu->prb_start = prb_start;
    pucch_pdu->rnti = UE->rnti;
    pucch_pdu->freq_hop_flag = 1;
    pucch_pdu->second_hop_prb = second_hop_prb;
    pucch_pdu->format_type = default_pucch_fmt[rsetindex];
    pucch_pdu->initial_cyclic_shift = r_pucch%default_pucch_csset[rsetindex];
    if (rsetindex==3||rsetindex==7||rsetindex==11) pucch_pdu->initial_cyclic_shift*=6;
    else if (rsetindex==1||rsetindex==2) pucch_pdu->initial_cyclic_shift*=4;
    else pucch_pdu->initial_cyclic_shift*=3;
    pucch_pdu->nr_of_symbols = nr_of_symb;
    pucch_pdu->start_symbol_index = start_symb;
    if (pucch_pdu->format_type == 1) pucch_pdu->time_domain_occ_idx = 0; // check this!!
    pucch_pdu->sr_flag = O_sr;
    pucch_pdu->prb_size=1;
  }
  // Beamforming
  pucch_pdu->beamforming.num_prgs = 0;
  pucch_pdu->beamforming.prg_size = 0; // pucch_pdu->prb_size;
  pucch_pdu->beamforming.dig_bf_interface = 0;
  if (pucch_pdu->beamforming.num_prgs > 0) {
    if (pucch_pdu->beamforming.prgs_list == NULL) {
      pucch_pdu->beamforming.prgs_list = calloc(pucch_pdu->beamforming.num_prgs, sizeof(*pucch_pdu->beamforming.prgs_list));
    }
    if (pucch_pdu->beamforming.dig_bf_interface > 0) {
      if (pucch_pdu->beamforming.prgs_list[0].dig_bf_interface_list == NULL) {
        pucch_pdu->beamforming.prgs_list[0].dig_bf_interface_list =
            calloc(pucch_pdu->beamforming.dig_bf_interface, sizeof(*pucch_pdu->beamforming.prgs_list[0].dig_bf_interface_list));
      }
    }
    pucch_pdu->beamforming.prgs_list[0].dig_bf_interface_list[0].beam_idx = 0;
  }
}
```