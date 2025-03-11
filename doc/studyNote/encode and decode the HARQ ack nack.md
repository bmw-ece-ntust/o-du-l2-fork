# encode and decode the HARQ ack/nack

Start Date: 2024/04/05 → 2024/04/11
Summary: Encoding and decoding HARQ acknowledgment/nack feedback in NR systems while ensuring proper functionality and data integrity.
Status: Reject
Tags: Robert Task

<aside>
💡 Define

</aside>

```
1712244952.039800 [NR_MAC]   UE 7a79 expected HARQ pid 10 feedback at  264. 7, but is at  274. 7 instead (HARQ feedback is in the past)
1712244953.123094 [NR_MAC]   UE 7a79 expected HARQ pid 6 feedback at  304. 7, but is at  314. 7 instead (HARQ feedback is in the past)
1712244954.216258 [NR_MAC]   UE 7a79 expected HARQ pid 12 feedback at  344. 7, but is at  354. 7 instead (HARQ feedback is in the past)
```

this is when there is no load. You should check whether we encode and decode the HARQ ack/nack properly. That means:

- check in L1 when we have PUCCH 0 for acknack: see patch below
- check what we pack in the UCI.indication
- check what we unpack in the UCI.indication message
- compare if all matches
- Check when the scheduler requests ack, and check if that is the same in the L1 (you can check with the PUCCH0 function, that should work, you can compare with monolithic)

same for UL in second step

pucch-check.patch

```cpp
diff --git a/openair1/PHY/NR_TRANSPORT/pucch_rx.c b/openair1/PHY/NR_TRANSPORT/pucch_rx.c
index 35b5b1be3d..622ed7941d 100644
--- a/openair1/PHY/NR_TRANSPORT/pucch_rx.c
+++ b/openair1/PHY/NR_TRANSPORT/pucch_rx.c
@@ -402,7 +402,7 @@ void nr_decode_pucch0(PHY_VARS_gNB *gNB,
     uci_pdu->harq.num_harq = 1;
     uci_pdu->harq.harq_confidence_level = no_conf;
     uci_pdu->harq.harq_list[0].harq_value = !(index&0x01);
-    LOG_D(PHY,
+    LOG_I(PHY,
           "[DLSCH/PDSCH/PUCCH] %d.%d HARQ %s with confidence level %s xrt_mag "
           "%d xrt_mag_next %d pucch_power_dBtimes10 %d n0 %d "
           "(%d,%d) pucch0_thres %d, "
@@ -438,7 +438,7 @@ void nr_decode_pucch0(PHY_VARS_gNB *gNB,
 
     uci_pdu->harq.harq_list[1].harq_value = !(index&0x01);
     uci_pdu->harq.harq_list[0].harq_value = !((index>>1)&0x01);
-    LOG_D(PHY,
+    LOG_I(PHY,
           "[DLSCH/PDSCH/PUCCH] %d.%d HARQ values (%s, %s) with confidence level %s, xrt_mag %d xrt_mag_next %d pucch_power_dBtimes10 %d n0 %d (%d,%d) "
           "pucch0_thres %d, cqi %d, SNRtimes10 %d\n",
           frame,
diff --git a/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_dlsch.c b/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_dlsch.c
index 54a5bd4b6a..920a1408aa 100644
--- a/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_dlsch.c
+++ b/openair2/LAYER2/NR_MAC_gNB/gNB_scheduler_dlsch.c
@@ -996,7 +996,7 @@ void nr_schedule_ue_spec(module_id_t module_id,
     harq->feedback_slot = pucch->ul_slot;
     harq->is_waiting = true;
     UE->mac_stats.dl.rounds[harq->round]++;
-    LOG_D(NR_MAC,
+    LOG_I(NR_MAC,
           "%4d.%2d [DLSCH/PDSCH/PUCCH] RNTI %04x DCI L %d start %3d RBs %3d startSymbol %2d nb_symbol %2d dmrspos %x MCS %2d nrOfLayers %d TBS %4d HARQ PID %2d round %d RV %d NDI %d dl_data_to_ULACK %d (%d.%d) PUCCH allocation %d TPC %d\n",
           frame,
           slot,
```