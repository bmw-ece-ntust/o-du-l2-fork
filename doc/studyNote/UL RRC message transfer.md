# UL RRC message transfer

Start Date: 2024/09/30
Summary: UL RRC message transfer project involves encoding messages from the CellGroupConfig and handling initial UL RRC message transfers in both OAI CU and OSC DU environments.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2024/10/08
SUM: 🗓️ Days Spent to Complete: 8

<aside>
💡

`UL RRC message transfer` is encode from `CellGroupConfig` message

</aside>

# Source code (OSC DU High)

```c
uint8_t BuildAndSendInitialRrcMsgTransfer(uint32_t gnbDuUeF1apId, uint16_t crnti,
      uint16_t rrcContSize, uint8_t *rrcContainer)
{
   uint8_t   ret;
   uint8_t   elementCnt;
   uint8_t   ieIdx, cellIdx, ueIdx;
   DuUeCb    *duUeCb = NULLP;
   asn_enc_rval_t  encRetVal;
   F1AP_PDU_t  *f1apMsg = NULLP;
   InitialULRRCMessageTransfer_t *initULRRCMsg = NULLP;
   memset(&encRetVal, 0, sizeof(asn_enc_rval_t));
```

```c
-> Function: BuildAndSendInitialRrcMsgTransfer()      
      
      /*DUtoCURRCContainer*/
      ieIdx++;
      initULRRCMsg->protocolIEs.list.array[ieIdx]->id = ProtocolIE_ID_id_DUtoCURRCContainer;
      initULRRCMsg->protocolIEs.list.array[ieIdx]->criticality = Criticality_reject;
      initULRRCMsg->protocolIEs.list.array[ieIdx]->value.present =\
								 InitialULRRCMessageTransferIEs__value_PR_DUtoCURRCContainer;

      for(cellIdx = 0; cellIdx < MAX_NUM_CELL; cellIdx++)
      {
         for(ueIdx = 0; ueIdx < 3; ueIdx++) //Test RXdata LCID
         {
            if(duCb.actvCellLst[cellIdx] && (duCb.actvCellLst[cellIdx]->ueCb[ueIdx].gnbDuUeF1apId == gnbDuUeF1apId)&&\
                  (duCb.actvCellLst[cellIdx]->ueCb[ueIdx].crnti == crnti))
            {
               duUeCb = &duCb.actvCellLst[cellIdx]->ueCb[ueIdx];
            }
         }
      }

      ret = BuildCellGroupConfigRrc(duUeCb, &initULRRCMsg->protocolIEs.list.array[ieIdx]->value.choice.DUtoCURRCContainer);
      
```

```c
/*******************************************************************
 *
 * @brief Builds CellGroupConfigRrc for DU To CU RRC Container 
 *
 * @details
 *
 *    Function : BuildCellGroupConfigRrc
 *
 *    Functionality: Builds and copied Cell group config buffer into 
 *       DuToCuRrcContainer
 *
 * @params[in] idx, index in F1AP msg
 *             DuToCuRRCContainer, DuToCuRRCContainer
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t BuildCellGroupConfigRrc(DuUeCb *ueCb, OCTET_STRING_t *duToCuRrcContainer)
{
```

As we can see from the OSC function description, `BuildCellGroupConfigRrc` builds and copies the cell group configuration buffer into the `DuToCuRrcContainer`.

---

# Source code (OAI CU)

```c
int CU_handle_INITIAL_UL_RRC_MESSAGE_TRANSFER(instance_t instance, sctp_assoc_t assoc_id, uint32_t stream, F1AP_F1AP_PDU_t *pdu)
{
  LOG_D(F1AP, "CU_handle_INITIAL_UL_RRC_MESSAGE_TRANSFER\n");
  // decode the F1 message
  // get the rrc message from the contauiner
  // call func rrc_eNB_decode_ccch: <-- needs some update here
  MessageDef                            *message_p;
  F1AP_InitialULRRCMessageTransfer_t    *container;
  F1AP_InitialULRRCMessageTransferIEs_t *ie;
  DevAssert(pdu != NULL);

  if (stream != 0) {
    LOG_E(F1AP, "[SCTP %d] Received F1 on stream != 0 (%d)\n",
          assoc_id, stream);
    return -1;
  }
```

```c
void rrc_gNB_process_initial_ul_rrc_message(sctp_assoc_t assoc_id, const f1ap_initial_ul_rrc_message_t *ul_rrc)
{
  AssertFatal(assoc_id != 0, "illegal assoc_id == 0: should be -1 (monolithic) or >0 (split)\n");

  gNB_RRC_INST *rrc = RC.nrrrc[0];
  LOG_I(NR_RRC, "Decoding CCCH: RNTI %04x, payload_size %d\n", ul_rrc->crnti, ul_rrc->rrc_container_length);
  NR_UL_CCCH_Message_t *ul_ccch_msg = NULL;
  asn_dec_rval_t dec_rval = uper_decode(NULL,
                                        &asn_DEF_NR_UL_CCCH_Message,
                                        (void **)&ul_ccch_msg,
                                        ul_rrc->rrc_container,
                                        ul_rrc->rrc_container_length,
                                        0,
                                        0);
  if (dec_rval.code != RC_OK || dec_rval.consumed == 0) {
    LOG_E(NR_RRC, " FATAL Error in receiving CCCH\n");
    return;
  }
```

## Call a function to print

```c
xer_fprint(stdout, &asn_DEF_NR_UL_CCCH_Message, ul_ccch_msg);
```

|  | OAI CU + OAI DU | OAI CU + OSC DU |
| --- | --- | --- |
| **RNTI** | **e088** | **0064** |
| **payload_size** | 6 | 6 |
| **RRCSetup Encoded** | **1093 bits (137 bytes)** | **821 bits (103 bytes)** |
|  |  | duToCuRrcContainer->size = encBufSize +33;

RRCSetup Encoded 1093 bits (137 bytes) |
- Both execute
    - **rrc_gnb_task**
    - **rrc_gNB_process_initial_ul_rrc_message**
    - **rrc_handle_RRCSetupRequest**
    
    ```c
      rrc_gNB_generate_RRCSetup(0, msg->crnti, ue_context_p, msg->du2cu_rrc_container, msg->du2cu_rrc_container_length);
    ```
    
    - **rrc_gNB_generate_RRCSetup**
    - **do_RRCSetup**
- **Only OAI CU + OSC DU execute**
    - **CU_handle_INITIAL_UL_RRC_MESSAGE_TRANSFER()**

```c
void mac_rrc_dl_direct_init(nr_mac_rrc_dl_if_t *mac_rrc)
{
  mac_rrc->f1_setup_response = f1_setup_response_direct;
  mac_rrc->f1_setup_failure = f1_setup_failure_direct;
  mac_rrc->gnb_du_configuration_update_acknowledge = gnb_du_configuration_update_ack_direct;
  mac_rrc->ue_context_setup_request = ue_context_setup_request_direct;
  mac_rrc->ue_context_modification_request = ue_context_modification_request_direct;
  mac_rrc->ue_context_modification_confirm = ue_context_modification_confirm_direct;
  mac_rrc->ue_context_modification_refuse = ue_context_modification_refuse_direct;
  mac_rrc->ue_context_release_command = ue_context_release_command_direct;
  mac_rrc->dl_rrc_message_transfer = dl_rrc_message_transfer_direct;
}
```

```c
void mac_rrc_dl_f1ap_init(nr_mac_rrc_dl_if_t *mac_rrc)
{
  mac_rrc->f1_setup_response = f1_setup_response_f1ap;
  mac_rrc->f1_setup_failure = f1_setup_failure_f1ap;
  mac_rrc->gnb_du_configuration_update_acknowledge = gnb_du_configuration_update_ack_f1ap;
  mac_rrc->ue_context_setup_request = ue_context_setup_request_f1ap;
  mac_rrc->ue_context_modification_request = ue_context_modification_request_f1ap;
  mac_rrc->ue_context_modification_confirm = ue_context_modification_confirm_f1ap;
  mac_rrc->ue_context_modification_refuse = ue_context_modification_refuse_f1ap;
  mac_rrc->ue_context_release_command = ue_context_release_command_f1ap;
  mac_rrc->dl_rrc_message_transfer = dl_rrc_message_transfer_f1ap;
}

```

## LOG

```c
 九  30 23:36:42 [0m<UL-CCCH-Message>
 九  30 23:36:42     <message>
 九  30 23:36:42         <c1>
 九  30 23:36:42             <rrcSetupRequest>
 九  30 23:36:42                 <rrcSetupRequest>
 九  30 23:36:42                     <ue-Identity>
 九  30 23:36:42                         <randomValue>
 九  30 23:36:42                             001110011010101011001011010100100010111
 九  30 23:36:42                         </randomValue>
 九  30 23:36:42                     </ue-Identity>
 九  30 23:36:42                     <establishmentCause><mo-Signalling/></establishmentCause>
 九  30 23:36:42                     <spare>
 九  30 23:36:42                         0
 九  30 23:36:42                     </spare>
 九  30 23:36:42                 </rrcSetupRequest>
 九  30 23:36:42             </rrcSetupRequest>
 九  30 23:36:42         </c1>
 九  30 23:36:42     </message>
 九  30 23:36:42 </UL-CCCH-Message>
```

```
<UL-CCCH-Message>
    <message>
        <c1>
            <rrcSetupRequest>
                <rrcSetupRequest>
                    <ue-Identity>
                        <randomValue>
                            111010100000111101101101000110100110001
                        </randomValue>
                    </ue-Identity>
                    <establishmentCause><mo-Signalling/></establishmentCause>
                    <spare>
                        0
                    </spare>
                </rrcSetupRequest>
            </rrcSetupRequest>
        </c1>
    </message>
</UL-CCCH-Message>
```

|  | randomValue |
| --- | --- |
| OAI no.1 | 001110011010101011001011010100100010111 |
| OAI no.2 | **011111001000111000001101001110010110101** |
| OSC no.1 | 111010100000111101101101000110100110001 |

# Struct

```cpp
/* NR_UL-CCCH-MessageType */
typedef struct NR_UL_CCCH_MessageType {
	NR_UL_CCCH_MessageType_PR present;
	union NR_UL_CCCH_MessageType_u {
		struct NR_UL_CCCH_MessageType__c1 {
			NR_UL_CCCH_MessageType__c1_PR present;
			union NR_UL_CCCH_MessageType__NR_c1_u {
				struct NR_RRCSetupRequest	*rrcSetupRequest;
				struct NR_RRCResumeRequest	*rrcResumeRequest;
				struct NR_RRCReestablishmentRequest	*rrcReestablishmentRequest;
				struct NR_RRCSystemInfoRequest	*rrcSystemInfoRequest;
			} choice;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *c1;
		struct NR_UL_CCCH_MessageType__messageClassExtension {
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *messageClassExtension;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NR_UL_CCCH_MessageType_t;
```

```cpp
/* NR_RRCSetupRequest */
typedef struct NR_RRCSetupRequest {
	NR_RRCSetupRequest_IEs_t	 rrcSetupRequest;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NR_RRCSetupRequest_t;
```

```cpp
/* NR_RRCSetupRequest-IEs */
typedef struct NR_RRCSetupRequest_IEs {
	NR_InitialUE_Identity_t	 ue_Identity;
	NR_EstablishmentCause_t	 establishmentCause;
	BIT_STRING_t	 spare;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NR_RRCSetupRequest_IEs_t;
```

```cpp
/* NR_InitialUE-Identity */
typedef struct NR_InitialUE_Identity {
	NR_InitialUE_Identity_PR present;
	union NR_InitialUE_Identity_u {
		BIT_STRING_t	 ng_5G_S_TMSI_Part1;
		BIT_STRING_t	 randomValue;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NR_InitialUE_Identity_t;
```