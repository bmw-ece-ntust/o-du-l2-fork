# F1AP: Cell group config

Start Date: 2024/10/16
Summary: Configuring and troubleshooting F1AP cell group settings for improved uplink and downlink communication.
Status: padding
Assign: 陳奕全

[Compare CellGroupConfig receive by UE](Compare%20CellGroupConfig%20receive%20by%20UE%20121100983143819a91fce020542ad2c2.md)

<aside>
💡

Lack PUCCH and PUSCH config

</aside>

**nr_rrc_cellgroup_configuration**

```
 十  16 12:19:21     <spCellConfig>
 十  16 12:19:21         <spCellConfigDedicated>
 十  16 12:19:21             **<uplinkConfig>**
 十  16 12:19:21                 <initialUplinkBWP>
 十  16 12:19:21                     <pucch-Config>
 十  16 12:19:21                         <setup>
```

**configure_servingcell_info**

![image.png](image%207.png)

**nr_rrc_cellgroup_configuration**

OAI + UE

```jsx
 十  16 13:26:09 [0m[RRC]   Sending CellGroupConfig to MAC
 十  16 13:26:09 [0m[MAC]   Applying CellGroupConfig from gNodeB
 十  16 13:26:09 [0m[MAC]   configuring spCellConfig
 十  16 13:26:09 [0m[MAC]   configuring scd
 十  16 13:26:09 [0m[MAC]   Configuring DL BWP -> initialDownlinkBWP
 十  16 13:26:09 [0m[MAC]   Configuring UL BWP -> uplinkConfig
```

OSC+ UE

```jsx
 十  16 12:19:21 [0m[RRC]   Sending CellGroupConfig to MAC
 十  16 12:19:21 [0m[MAC]   Applying CellGroupConfig from gNodeB
 十  16 12:19:21 [0m[MAC]   configuring spCellConfig
 十  16 12:19:21 [0m[MAC]   configuring scd
 十  16 12:19:21 [0m[MAC]   Configuring DL BWP -> initialDownlinkBWP
```

<aside>
💡

It seem to OAI UE didn’t get `uplinkConfig`  from higher layer.

</aside>

Check RRC cellgroupconfig ASN decoder and encoder

```jsx
        asn_dec_rval_t dec_rval = uper_decode(NULL,
                                              &asn_DEF_NR_CellGroupConfig, // might be added prefix later
                                              (void **)&cellGroupConfig,
                                              (uint8_t *)ie->secondaryCellGroup->buf,
                                              ie->secondaryCellGroup->size,
                                              0,
                                              0);
```

## Idea 1

Decode cellgroupconfig following encode in DU

**`BuildCellGroupConfigRrc`**

✅ No problem Decode the encoded buffer back into cellGrpCfg 

```c
      else
      {
         DU_LOG("\nDEBUG   -->  F1AP : Created APER encoded buffer for DuToCuRrcContainer\n");

         DU_LOG("\nDEBUG   -->  F1AP : Decode the encoded buffer back into cellGrpCfg\n\n\n\n");
         /* Decode the encoded buffer back into cellGrpCfg */
         asn_dec_rval_t decRetVal;
         CellGroupConfig_t *decodedCellGrpCfg = NULL;

         decRetVal = uper_decode(0, &asn_DEF_CellGroupConfig, (void **)&decodedCellGrpCfg, encBuf, (encRetVal.encoded + 7) / 8, 0, 0);
         
         if(decRetVal.code == ROK)
         {
            DU_LOG("\nINFO  --> F1AP : Successfully decoded DuToCuRrcContainer");

            /* Use xer_fprint to print the decoded structure */
            xer_fprint(stdout, &asn_DEF_CellGroupConfig, decodedCellGrpCfg);
         }
         //OAI DECODE
   //         asn_dec_rval_t dec_rval = uper_decode(NULL,
                                             //  &asn_DEF_NR_CellGroupConfig, // might be added prefix later
                                             //  (void **)&cellGroupConfig,
                                             //  (uint8_t *)masterCellGroup->buf,
                                             //  masterCellGroup->size,
                                             //  0,
                                             //  0);
```

```jsx
5c0ffffffb0110affffffecffffff81ffffffd061ffffffea07c22ffffffa0ffffff957ffffffb8ffffffc0207affffff984ffffffb232a0220fffffff0000701dffffffc210ffffff803fffffff8ffffff8cffffff90ffffff8112031ffffff80514ffffffa004cffffffd5502020202020022244affffffa11003242016310ffffffa6314e50202084080000001ffffff8050722a0
```

<aside>
💡

After investigating, I think this problem originates from the `uper_decode` and `uper_encode` between the ODU and the OAI UE. This is because both the `encBuf` and `encBufSize` being sent are identical. While decoding the `encBuf` directly on the ODU allows for correctly retrieving all member data of the cell group config, decoding on the OAI UE cannot properly decode everything.(Lack PUCCH and PUSCH config)

</aside>

![image.png](image%208.png)

Regarding the previously mentioned segmentation fault in the UE after completing the RRC setup complete, we have discussed and identified the root cause. The issue stems from the UE failing to properly decode the `pucch_Config` within `asn_DEF_CellGroupConfig`. On the ODU side, decoding directly after encoding works correctly, but the logs on the OAI UE show that the decoded result is missing a lot of the `spCellConfig` data. We suspect this is due to an ASN.1 version mismatch. Currently, Ming plans to temporarily resolve this issue in the same way as was done for SIB1.

![image.png](image%209.png)

## Review

- BuildSpCellCfg
    - **BuildRecfgWithSync**
    - **BuildSpCellCfgDed**
        - **BuildInitialDlBWP**
            - **BuildBWPDlDedPdcchCfg**
                - **BuildControlRSetToAddModList**
                - **BuildSearchSpcToAddModList**
            - **BuildBWPDlDedPdschCfg**
                - **BuildDMRSDLPdschMapTypeA**
                - **BuildPdschTimeDomAllocList**
                - **BuildPdschPrbBundlingType**
        - **BuildDlBwpToAddModList**
        - **BuildUlCfg**
            - **BuildInitialUlBWP**
                - **BuildBWPUlDedPucchCfg**
                    - **BuildPucchRsrcSetAddModList**
                    - **BuildPucchRsrcAddModList**
                    - **BuildPucchFormat**
                - **BuildBWPUlDedPuschCfg**
                    - **BuildDMRSULPuschMapTypeA**
                    - **BuildPuschTimeDomAllocList**
                - **BuildBWPUlDedSrsCfg**
                    - **BuildSrsRsrcSetAddModList**
                    - **BuildSrsRsrcAddModList**
            - **BuildPuschSrvCellCfg**
        - **BuildPdschSrvCellCfg**