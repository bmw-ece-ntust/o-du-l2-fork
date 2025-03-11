# DMRS

Start Date: 2024/10/13
Summary: Development of DMRS symbol positions for downlink PDSCH in NR systems.
Status: padding
Assign: Ming 咚咚 [銘鴻]

## **dlDmrsSymbPos**

```c
  /* dmrs symbol positions*/
  dlsch_pdu->dlDmrsSymbPos = fill_dmrs_mask(pdsch_config,
                                            NR_DL_DCI_FORMAT_1_0,
                                            mac->dmrs_TypeA_Position,
                                            dlsch_pdu->number_symbols,
                                            dlsch_pdu->start_symbol,
                                            tda_info.mapping_type,
                                            1);
```

```c
int16_t fill_dmrs_mask(const NR_PDSCH_Config_t *pdsch_Config,
                       int dci_format,
                       int dmrs_TypeA_Position,
                       int NrOfSymbols,
                       int startSymbol,
                       mappingType_t mappingtype,
                       int length)
{
  int dmrs_AdditionalPosition = 0;
  NR_DMRS_DownlinkConfig_t *dmrs_config = NULL;

  LOG_D(MAC, "NrofSymbols:%d, startSymbol:%d, mappingtype:%d, dmrs_TypeA_Position:%d\n", NrOfSymbols, startSymbol, mappingtype, dmrs_TypeA_Position);

  int l0 = 0; // type B
  if (mappingtype == typeA) {
    if (dmrs_TypeA_Position == NR_ServingCellConfigCommon__dmrs_TypeA_Position_pos2) l0 = 2;
    else if (dmrs_TypeA_Position == NR_ServingCellConfigCommon__dmrs_TypeA_Position_pos3) l0 = 3;
    else AssertFatal(1==0,"Illegal dmrs_TypeA_Position %d\n",(int)dmrs_TypeA_Position);
  }
  // in case of DCI FORMAT 1_0 or dedicated pdsch config not received additionposition = pos2, len1 should be used
  // referred to section 5.1.6.2 in 38.214
  dmrs_AdditionalPosition = 2;

  if (pdsch_Config != NULL) {
    if (mappingtype == typeA) { // Type A
      if (dci_format != NR_DL_DCI_FORMAT_1_0 &&
          pdsch_Config->dmrs_DownlinkForPDSCH_MappingTypeA && pdsch_Config->dmrs_DownlinkForPDSCH_MappingTypeA->present == NR_SetupRelease_DMRS_DownlinkConfig_PR_setup)
        dmrs_config = (NR_DMRS_DownlinkConfig_t *)pdsch_Config->dmrs_DownlinkForPDSCH_MappingTypeA->choice.setup;
    } else if (mappingtype == typeB) {
      if (pdsch_Config->dmrs_DownlinkForPDSCH_MappingTypeB && pdsch_Config->dmrs_DownlinkForPDSCH_MappingTypeB->present == NR_SetupRelease_DMRS_DownlinkConfig_PR_setup)
        dmrs_config = (NR_DMRS_DownlinkConfig_t *)pdsch_Config->dmrs_DownlinkForPDSCH_MappingTypeB->choice.setup;
    } else {
      AssertFatal(1==0,"Incorrect Mappingtype\n");
    }

    // default values of additionalposition is pos2
    if (dmrs_config && dmrs_config->dmrs_AdditionalPosition != NULL)
      dmrs_AdditionalPosition = *dmrs_config->dmrs_AdditionalPosition;
  }

  uint8_t ld, row, column;
  int32_t l_prime = -1;

  // columns 0-3 for TypeA, 4-7 for TypeB
  column = (mappingtype == typeA) ? dmrs_AdditionalPosition : (dmrs_AdditionalPosition + 4);

  // Section 7.4.1.1.2 in Spec 38.211
  // For PDSCH Mapping TypeA, ld is duration between first OFDM of the slot and last OFDM symbol of the scheduled PDSCH resources
  // For TypeB, ld is the duration of the scheduled PDSCH resources
  ld = (mappingtype == typeA) ? (NrOfSymbols + startSymbol) : NrOfSymbols;

  AssertFatal(ld > 2 && ld < 15,"Illegal NrOfSymbols according to Table 5.1.2.1-1 Spec 38.214 %d\n",ld);
  AssertFatal((NrOfSymbols + startSymbol) < 15,"Illegal S+L according to Table 5.1.2.1-1 Spec 38.214 S:%d L:%d\n",startSymbol, NrOfSymbols);

  if (mappingtype == typeA) {

    // Section 7.4.1.1.2 in Spec 38.211
    AssertFatal((l0 == 2) || (l0 == 3 && dmrs_AdditionalPosition != 3),"Wrong config, If dmrs_TypeA_Position POS3, ADD POS cannot be POS3 \n");

    // Table 5.1.2.1-1 in Spec 38.214
    AssertFatal(startSymbol <= l0, "Wrong config, Start symbol %d cannot be later than dmrs_TypeA_Position %d \n", startSymbol, l0);

    // Section 7.4.1.1.2 in Spec 38.211
    AssertFatal(l0 == 2 || (l0 == 3 && (ld != 3 && ld != 4)), "ld 3 or 4 symbols only possible with dmrs_TypeA_Position POS2 \n");
  }

  // number of front loaded symbols
  if (length == 1) {
    row = ld - 2;
    l_prime = table_7_4_1_1_2_3_pdsch_dmrs_positions_l[row][column];
    l0 = 1 << l0;
  }
  else {
    row = (ld < 4) ? 0 : (ld - 3);
    l_prime = table_7_4_1_1_2_4_pdsch_dmrs_positions_l[row][column];
    l0 = 1<<l0 | 1<<(l0+1);
  }

  LOG_D(MAC, "l0:%d, ld:%d,row:%d, column:%d, addpos:%d, maxlen:%d\n", l0, ld, row, column, dmrs_AdditionalPosition, length);
  AssertFatal(l_prime>=0,"ERROR in configuration.Check Time Domain allocation of this Grant. l_prime < 1. row:%d, column:%d\n", row, column);

  l_prime = (mappingtype == typeA) ? (l_prime | l0) : (l_prime << startSymbol);
  LOG_D(MAC, " PDSCH DMRS MASK in HEX:%x\n", l_prime);

  return l_prime;
}
```