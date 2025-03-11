# limit only to one PUCCH

Summary: Limit the implementation to a single PUCCH to ensure proper functionality in the system.
Status: Done

What happens if you just do this??

```
diff --git a/openair1/PHY/NR_TRANSPORT/pucch_rx.c b/openair1/PHY/NR_TRANSPORT/pucch_rx.c
index 118c828519..f5ba5a860c 100644
--- a/openair1/PHY/NR_TRANSPORT/pucch_rx.c
+++ b/openair1/PHY/NR_TRANSPORT/pucch_rx.c
@@ -60,10 +60,6 @@ void nr_fill_pucch(PHY_VARS_gNB *gNB,
                    int slot,
                    nfapi_nr_pucch_pdu_t *pucch_pdu)
 {
-
-  if (NFAPI_MODE == NFAPI_MODE_PNF)
-    gNB->pucch[0].active = 0; // check if ture in monolithic mode
-
   bool found = false;
   for (int i = 0; i < gNB->max_nb_pucch; i++) {
     NR_gNB_PUCCH_t *pucch = &gNB->pucch[i];

```

ok, yes, ideally you provide a fix but I think the patch is necessary: why should we limit only to one PUCCH at a time? it should work like in monolithic.