# SPcell configuration and message structure

Start Date: 2024/10/18
Summary: Configuration and analysis of SPcell settings, including encountered issues and proposed solutions.
Status: padding
Assign: Ming 咚咚 [銘鴻]

### 1. Encountered Issues

- Follow the MM with Radisys actinon item [Radisys quick call](https://www.notion.so/Radisys-quick-call-1231009831438041be80c71c611e1390?pvs=21)
- To review function code, particularly `BuildSpCellCfgDed`.

### 2. SIB1 RRC ASN.1 Revision in `BuildSpCellCfgDed()`

```bash
   srvCellCfg->supplementaryUplink = NULLP;
   srvCellCfg->pdcch_ServingCellConfig = NULLP;

   srvCellCfg->pdsch_ServingCellConfig = NULLP;
   DU_ALLOC(srvCellCfg->pdsch_ServingCellConfig, sizeof(struct	ServingCellConfig__pdsch_ServingCellConfig));
   DU_ALLOC(srvCellCfg->pdsch_ServingCellConfig, sizeof(struct	SetupRelease_PDSCH_ServingCellConfig));
   if(!srvCellCfg->pdsch_ServingCellConfig)
   {
      DU_LOG("\nERROR  -->  F1AP : Memory allocation failure in BuildSpCellCfgDed");
      return RFAILED;
#endif
   srvCellCfg->sCellDeactivationTimer = NULLP;
   srvCellCfg->crossCarrierSchedulingConfig = NULLP;
   srvCellCfg->tag_Id = TAG_ID;
   srvCellCfg->dummy = NULLP;
   srvCellCfg->dummy1 = NULLP;
   srvCellCfg->pathlossReferenceLinking = NULLP;
   srvCellCfg->servingCellMO = NULLP;
   srvCellCfg->ext1 = NULLP;
```

### 3. Solutions and Analysis