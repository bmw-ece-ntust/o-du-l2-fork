# check TDD table with 2.5ms TDD period, and check for mu=0 (FDD, band66)

Start Date: 2024/05/15
Summary: Dynamic adjustment of the TDD table based on configuration settings for improved performance in NR systems.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Robert Task

b69d356a9828e6cf7e7c7da850845a5c557cd1b1

```c
From 4cb7abf0d72f41e82bfd7fa06463f7fbaf9ae89d Mon Sep 17 00:00:00 2001
From: hsum <ming-hong.hsu@eurecom.fr>
Date: Wed, 22 May 2024 10:47:27 +0200
Subject: [PATCH] Enable Dynamic Adjustment of TDD Table Based on Configuration

- Enhanced `pack_nr_config_request` and `unpack_nr_config_request` functions in `nfapi_p5.c`:
  - Removed static assertion for TDD period value.
  - Introduced dynamic calculation of the TDD table size based on `dl_UL_TransmissionPeriodicity` and subcarrier spacing.
  - Added detailed logging for the TDD table content.
- Refactored `nr_slot_select` function in `phy_frame_config_nr.c` to streamline the selection logic for different slot types, removing outdated code handling alternating frames.

Now, the TDD table can be dynamically adjusted based on the `dl_UL_TransmissionPeriodicity` settings in the configuration file. Each transmission will pack and send a complete TDD table.
---
 nfapi/open-nFAPI/nfapi/src/nfapi_p5.c   | 42 ++++++++++++++-----------
 openair1/SCHED_NR/phy_frame_config_nr.c | 30 ++----------------
 2 files changed, 26 insertions(+), 46 deletions(-)

diff --git a/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c b/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c
index 4fb530a5a59..2676620291b 100644
--- a/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c
+++ b/nfapi/open-nFAPI/nfapi/src/nfapi_p5.c
@@ -1896,11 +1896,16 @@ static uint8_t pack_nr_config_request(void *msg, uint8_t **ppWritePackedMsg, uin
       pack_nr_tlv(NFAPI_NR_CONFIG_TDD_PERIOD_TAG, &(pNfapiMsg->tdd_table.tdd_period), ppWritePackedMsg, end, &pack_uint8_tlv_value);
   numTLVs++;
 
-  assert(6 == pNfapiMsg->tdd_table.tdd_period.value);
-  for (int i = 0; i < 2*(1<<mu)*10; i++) {
+  // assert(6 == pNfapiMsg->tdd_table.tdd_period.value);
+  float scs2perSlot_table[] = {1,0.5,0.25,0.2,0.125,0.1,0.0625,0.05};
+  float dl_UL_TransmissionPeriodicity_table[] = {0.5,0.625,1,1.25,2,2.5,5,10};
+  int tdd_table_num = dl_UL_TransmissionPeriodicity_table[pNfapiMsg->tdd_table.tdd_period.value] / scs2perSlot_table[mu];
+  assert((int)tdd_table_num*10 == tdd_table_num*10);
+
+  for (int i = 0; i < 10*pow(2,mu); i++) {
     for (int k = 0; k < 14; k++) {
       pack_nr_tlv(NFAPI_NR_CONFIG_SLOT_CONFIG_TAG,
-                  &pNfapiMsg->tdd_table.max_tdd_periodicity_list[i].max_num_of_symbol_per_slot_list[k].slot_config,
+                  &pNfapiMsg->tdd_table.max_tdd_periodicity_list[i%tdd_table_num].max_num_of_symbol_per_slot_list[k].slot_config,
                   ppWritePackedMsg,
                   end,
                   &pack_uint8_tlv_value);
@@ -3144,8 +3149,8 @@ static uint8_t unpack_nr_config_request(uint8_t **ppReadPackedMsg, uint8_t *end,
   pNfapiMsg->tdd_table.max_tdd_periodicity_list =
       (nfapi_nr_max_tdd_periodicity_t *)malloc(1 * sizeof(nfapi_nr_max_tdd_periodicity_t));
   // Initialize first, and upon receiving the SCS, reallocate memory to the correct size.
-    pNfapiMsg->tdd_table.max_tdd_periodicity_list[0].max_num_of_symbol_per_slot_list =
-        (nfapi_nr_max_num_of_symbol_per_slot_t *)malloc(14 * sizeof(nfapi_nr_max_num_of_symbol_per_slot_t));
+  pNfapiMsg->tdd_table.max_tdd_periodicity_list[0].max_num_of_symbol_per_slot_list =
+      (nfapi_nr_max_num_of_symbol_per_slot_t *)malloc(14 * sizeof(nfapi_nr_max_num_of_symbol_per_slot_t));
   pNfapiMsg->prach_config.num_prach_fd_occasions_list =
       (nfapi_nr_num_prach_fd_occasions_t *)calloc(10, sizeof(nfapi_nr_num_prach_fd_occasions_t));
   // unpack TLVs
@@ -3333,6 +3338,20 @@ static uint8_t unpack_nr_config_request(uint8_t **ppReadPackedMsg, uint8_t *end,
                                                     end);
             config_beam_idx++;
             break;
+          case NFAPI_NR_CONFIG_TDD_PERIOD_TAG:
+            printf("*** have tag %x, idx %ld\n", generic_tl.tag, idx);
+            assert(idx <= sizeof(unpack_fns) / sizeof(unpack_fns[0]));
+            result = (*unpack_fns[idx].unpack_func)(tl, ppReadPackedMsg, end);
+            uint8_t mu = pNfapiMsg->ssb_config.scs_common.value;
+            uint8_t period = pNfapiMsg->tdd_table.tdd_period.value;
+            // Memory allocations
+            pNfapiMsg->tdd_table.max_tdd_periodicity_list =
+                (nfapi_nr_max_tdd_periodicity_t *)malloc(10*pow(2,mu) * sizeof(nfapi_nr_max_tdd_periodicity_t));
+            for (int i = 0; i < 10*pow(2,mu); i++) {
+              pNfapiMsg->tdd_table.max_tdd_periodicity_list[i].max_num_of_symbol_per_slot_list =
+                  (nfapi_nr_max_num_of_symbol_per_slot_t *)malloc(14 * sizeof(nfapi_nr_max_num_of_symbol_per_slot_t));
+            }
+            break;
           case NFAPI_NR_CONFIG_SLOT_CONFIG_TAG:
             pNfapiMsg->tdd_table.max_tdd_periodicity_list[tdd_periodicity_idx]
                 .max_num_of_symbol_per_slot_list[symbol_per_slot_idx]
@@ -3350,19 +3369,6 @@ static uint8_t unpack_nr_config_request(uint8_t **ppReadPackedMsg, uint8_t *end,
               tdd_periodicity_idx++;
             }
             break;
-          case NFAPI_NR_CONFIG_SCS_COMMON_TAG:
-            printf("*** have tag %x, idx %ld\n", generic_tl.tag, idx);
-            assert(idx <= sizeof(unpack_fns) / sizeof(unpack_fns[0]));
-            result = (*unpack_fns[idx].unpack_func)(tl, ppReadPackedMsg, end);
-            uint8_t mu = pNfapiMsg->ssb_config.scs_common.value;
-            // Memory allocations
-            pNfapiMsg->tdd_table.max_tdd_periodicity_list =
-                (nfapi_nr_max_tdd_periodicity_t *)malloc(2*(1<<mu)*10 * sizeof(nfapi_nr_max_tdd_periodicity_t));
-            for (int i = 0; i < 2*(1<<mu)*10; i++) {
-              pNfapiMsg->tdd_table.max_tdd_periodicity_list[i].max_num_of_symbol_per_slot_list =
-                  (nfapi_nr_max_num_of_symbol_per_slot_t *)malloc(14 * sizeof(nfapi_nr_max_num_of_symbol_per_slot_t));
-            }
-            break;
           default:
             /* unpack based on unpack_fns table above, this is a normal case */
             printf("*** have tag %x, idx %ld\n", generic_tl.tag, idx);
diff --git a/openair1/SCHED_NR/phy_frame_config_nr.c b/openair1/SCHED_NR/phy_frame_config_nr.c
index 83ce412701f..2b425b60a81 100644
--- a/openair1/SCHED_NR/phy_frame_config_nr.c
+++ b/openair1/SCHED_NR/phy_frame_config_nr.c
@@ -297,13 +297,12 @@ int get_next_downlink_slot(PHY_VARS_gNB *gNB, nfapi_nr_config_request_scf_t *cfg
 
 int nr_slot_select(nfapi_nr_config_request_scf_t *cfg, int nr_frame, int nr_slot) {
   /* for FFD all slot can be considered as an uplink */
-  int mu = cfg->ssb_config.scs_common.value,check_slot=0;
-
+  // int mu = cfg->ssb_config.scs_common.value;
+  int check_slot=0;
   if (cfg->cell_config.frame_duplex_type.value == FDD) {
     return (NR_UPLINK_SLOT | NR_DOWNLINK_SLOT );
   }
 
-  if (nr_frame%2 == 0) {
     for(int symbol_count=0; symbol_count<NR_NUMBER_OF_SYMBOLS_PER_SLOT; symbol_count++) {
       if (cfg->tdd_table.max_tdd_periodicity_list[nr_slot].max_num_of_symbol_per_slot_list[symbol_count].slot_config.value==1) {
         check_slot++;
@@ -327,31 +326,6 @@ int nr_slot_select(nfapi_nr_config_request_scf_t *cfg, int nr_frame, int nr_slot
     } else {
       return (NR_MIXED_SLOT);
     }
-  } else {
-    for(int symbol_count=0; symbol_count<NR_NUMBER_OF_SYMBOLS_PER_SLOT; symbol_count++) {
-      if (cfg->tdd_table.max_tdd_periodicity_list[((1<<mu) * NR_NUMBER_OF_SUBFRAMES_PER_FRAME) + nr_slot].max_num_of_symbol_per_slot_list[symbol_count].slot_config.value==1) {
-        check_slot++;
-      }
-    }
-
-    if(check_slot == NR_NUMBER_OF_SYMBOLS_PER_SLOT) {
-      return (NR_UPLINK_SLOT);
-    }
-
-    check_slot = 0;
-
-    for(int symbol_count=0; symbol_count<NR_NUMBER_OF_SYMBOLS_PER_SLOT; symbol_count++) {
-      if (cfg->tdd_table.max_tdd_periodicity_list[((1<<mu) * NR_NUMBER_OF_SUBFRAMES_PER_FRAME) + nr_slot].max_num_of_symbol_per_slot_list[symbol_count].slot_config.value==0) {
-        check_slot++;
-      }
-    }
-
-    if(check_slot == NR_NUMBER_OF_SYMBOLS_PER_SLOT) {
-      return (NR_DOWNLINK_SLOT);
-    } else {
-      return (NR_MIXED_SLOT);
-    }
-  }
 }
 
 /*******************************************************************
-- 
GitLab

```