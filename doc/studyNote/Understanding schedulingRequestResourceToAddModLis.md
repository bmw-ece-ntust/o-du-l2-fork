# Understanding schedulingRequestResourceToAddModList in OAI

Start Date: 2025/02/20
Summary: A function for configuring scheduling request resources in NR (New Radio) with specific parameters and resource assignments.
Status: padding
Assign: Ming 咚咚 [銘鴻]
Tags: OAI

![image.png](image%20114.png)

```c
static void scheduling_request_config(const NR_ServingCellConfigCommon_t *scc, NR_PUCCH_Config_t *pucch_Config, int scs)
{
  // format with <=2 bits in pucch resource set 0
  NR_PUCCH_ResourceSet_t *pucchresset = pucch_Config->resourceSetToAddModList->list.array[0];
  // assigning the 1st pucch resource in the set to scheduling request
  NR_PUCCH_ResourceId_t *pucchressetid = pucchresset->resourceList.list.array[0];

  pucch_Config->schedulingRequestResourceToAddModList = calloc(1,sizeof(*pucch_Config->schedulingRequestResourceToAddModList));
  NR_SchedulingRequestResourceConfig_t *schedulingRequestResourceConfig = calloc(1,sizeof(*schedulingRequestResourceConfig));
  schedulingRequestResourceConfig->schedulingRequestResourceId = 1;
  schedulingRequestResourceConfig->schedulingRequestID = 0;

  set_SR_periodandoffset(schedulingRequestResourceConfig, scc, scs);

  schedulingRequestResourceConfig->resource = calloc(1,sizeof(*schedulingRequestResourceConfig->resource));
  *schedulingRequestResourceConfig->resource = *pucchressetid;
  asn1cSeqAdd(&pucch_Config->schedulingRequestResourceToAddModList->list,schedulingRequestResourceConfig);
}
```