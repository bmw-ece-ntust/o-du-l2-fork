# DL_tti sub PDU

Start Date: 2024/05/03
Summary: Development and implementation of the DL_tti sub PDU for efficient data transmission in communication systems.
Status: Done
Assign: Ming 咚咚 [銘鴻]

```c
static void cp_nr_dl_tti_pdcch_pdu(nfapi_nr_dl_tti_pdcch_pdu_rel15_t *dst, const nfapi_nr_dl_tti_pdcch_pdu_rel15_t *src) {
    if (dst == NULL || src == NULL) {
        return;
    }
    nfapi_nr_dl_tti_pdcch_pdu_rel15_t *dst_pdcch_pdu = &dst_pdu->pdcch_pdu.pdcch_pdu_rel15;
		const nfapi_nr_dl_tti_pdcch_pdu_rel15_t *src_pdcch_pdu = &src_pdu->pdcch_pdu.pdcch_pdu_rel15;
		dst_pdcch_pdu->BWPSize = src_pdcch_pdu->BWPSize;
		dst_pdcch_pdu->BWPStart = src_pdcch_pdu->BWPStart;
		dst_pdcch_pdu->SubcarrierSpacing = src_pdcch_pdu->SubcarrierSpacing;
		dst_pdcch_pdu->CyclicPrefix = src_pdcch_pdu->CyclicPrefix;
		dst_pdcch_pdu->StartSymbolIndex = src_pdcch_pdu->StartSymbolIndex;
		dst_pdcch_pdu->DurationSymbols = src_pdcch_pdu->DurationSymbols;
		memcpy(dst_pdcch_pdu->FreqDomainResource, src_pdcch_pdu->FreqDomainResource, sizeof(src_pdcch_pdu->FreqDomainResource));
		dst_pdcch_pdu->CceRegMappingType = src_pdcch_pdu->CceRegMappingType;
		dst_pdcch_pdu->RegBundleSize = src_pdcch_pdu->RegBundleSize;
		dst_pdcch_pdu->InterleaverSize = src_pdcch_pdu->InterleaverSize;
		dst_pdcch_pdu->CoreSetType = src_pdcch_pdu->CoreSetType;
		dst_pdcch_pdu->ShiftIndex = src_pdcch_pdu->ShiftIndex;
		dst_pdcch_pdu->precoderGranularity = src_pdcch_pdu->precoderGranularity;
		dst_pdcch_pdu->numDlDci = src_pdcch_pdu->numDlDci;
		for (int i = 0; i < src_pdcch_pdu->numDlDci; ++i) {
			dst_pdcch_pdu->dci_pdu[i] = src_pdcch_pdu->dci_pdu[i];
		}
}

static void cp_nr_dl_tti_pdsch_pdu(nfapi_nr_dl_tti_pdsch_pdu_rel15_t *dst, const nfapi_nr_dl_tti_pdsch_pdu_rel15_t *src) {
    if (dst == NULL || src == NULL) {
        return;
    }
		dst_pdsch_pdu->pduBitmap = src_pdsch_pdu->pduBitmap;
		dst_pdsch_pdu->rnti = src_pdsch_pdu->rnti;
		dst_pdsch_pdu->pduIndex = src_pdsch_pdu->pduIndex;
		dst_pdsch_pdu->BWPSize = src_pdsch_pdu->BWPSize;
		dst_pdsch_pdu->BWPStart = src_pdsch_pdu->BWPStart;
		dst_pdsch_pdu->SubcarrierSpacing = src_pdsch_pdu->SubcarrierSpacing;
		dst_pdsch_pdu->CyclicPrefix = src_pdsch_pdu->CyclicPrefix;
		dst_pdsch_pdu->NrOfCodewords = src_pdsch_pdu->NrOfCodewords;
		memcpy(dst_pdsch_pdu->targetCodeRate, src_pdsch_pdu->targetCodeRate, sizeof(src_pdsch_pdu->targetCodeRate));
		memcpy(dst_pdsch_pdu->qamModOrder, src_pdsch_pdu->qamModOrder, sizeof(src_pdsch_pdu->qamModOrder));
		memcpy(dst_pdsch_pdu->mcsIndex, src_pdsch_pdu->mcsIndex, sizeof(src_pdsch_pdu->mcsIndex));
		memcpy(dst_pdsch_pdu->mcsTable, src_pdsch_pdu->mcsTable, sizeof(src_pdsch_pdu->mcsTable));
		memcpy(dst_pdsch_pdu->rvIndex, src_pdsch_pdu->rvIndex, sizeof(src_pdsch_pdu->rvIndex));
		memcpy(dst_pdsch_pdu->TBSize, src_pdsch_pdu->TBSize, sizeof(src_pdsch_pdu->TBSize));
		dst_pdsch_pdu->dataScramblingId = src_pdsch_pdu->dataScramblingId;
		dst_pdsch_pdu->nrOfLayers = src_pdsch_pdu->nrOfLayers;
		dst_pdsch_pdu->transmissionScheme = src_pdsch_pdu->transmissionScheme;
		dst_pdsch_pdu->refPoint = src_pdsch_pdu->refPoint;
		dst_pdsch_pdu->dlDmrsSymbPos = src_pdsch_pdu->dlDmrsSymbPos;
		dst_pdsch_pdu->dmrsConfigType = src_pdsch_pdu->dmrsConfigType;
		dst_pdsch_pdu->dlDmrsScramblingId = src_pdsch_pdu->dlDmrsScramblingId;
		dst_pdsch_pdu->SCID = src_pdsch_pdu->SCID;
		dst_pdsch_pdu->numDmrsCdmGrpsNoData = src_pdsch_pdu->numDmrsCdmGrpsNoData;
		dst_pdsch_pdu->dmrsPorts = src_pdsch_pdu->dmrsPorts;
		dst_pdsch_pdu->resourceAlloc = src_pdsch_pdu->resourceAlloc;
		memcpy(dst_pdsch_pdu->rbBitmap, src_pdsch_pdu->rbBitmap, sizeof(src_pdsch_pdu->rbBitmap));
		dst_pdsch_pdu->rbStart = src_pdsch_pdu->rbStart;
		dst_pdsch_pdu->rbSize = src_pdsch_pdu->rbSize;
		dst_pdsch_pdu->VRBtoPRBMapping = src_pdsch_pdu->VRBtoPRBMapping;
		dst_pdsch_pdu->StartSymbolIndex = src_pdsch_pdu->StartSymbolIndex;
		dst_pdsch_pdu->NrOfSymbols = src_pdsch_pdu->NrOfSymbols;
		dst_pdsch_pdu->PTRSPortIndex = src_pdsch_pdu->PTRSPortIndex;
		dst_pdsch_pdu->PTRSTimeDensity = src_pdsch_pdu->PTRSTimeDensity;
		dst_pdsch_pdu->PTRSFreqDensity = src_pdsch_pdu->PTRSFreqDensity;
		dst_pdsch_pdu->PTRSReOffset = src_pdsch_pdu->PTRSReOffset;
		dst_pdsch_pdu->nEpreRatioOfPDSCHToPTRS = src_pdsch_pdu->nEpreRatioOfPDSCHToPTRS;
		dst_pdsch_pdu->precodingAndBeamforming = src_pdsch_pdu->precodingAndBeamforming;
		dst_pdsch_pdu->maintenance_parms_v3 = src_pdsch_pdu->maintenance_parms_v3;
}

static void cp_nr_dl_tti_csi_rs_pdu(nfapi_nr_dl_tti_csi_rs_pdu_rel15_t *dst, const nfapi_nr_dl_tti_csi_rs_pdu_rel15_t *src) {
    if (dst == NULL || src == NULL) {
        return;
    }
		dst_csi_rs_pdu->bwp_size = src_csi_rs_pdu->bwp_size;
		dst_csi_rs_pdu->bwp_start = src_csi_rs_pdu->bwp_start;
		dst_csi_rs_pdu->subcarrier_spacing = src_csi_rs_pdu->subcarrier_spacing;
		dst_csi_rs_pdu->cyclic_prefix = src_csi_rs_pdu->cyclic_prefix;
		dst_csi_rs_pdu->start_rb = src_csi_rs_pdu->start_rb;
		dst_csi_rs_pdu->nr_of_rbs = src_csi_rs_pdu->nr_of_rbs;
		dst_csi_rs_pdu->csi_type = src_csi_rs_pdu->csi_type;
		dst_csi_rs_pdu->row = src_csi_rs_pdu->row;
		dst_csi_rs_pdu->freq_domain = src_csi_rs_pdu->freq_domain;
		dst_csi_rs_pdu->symb_l0 = src_csi_rs_pdu->symb_l0;
		dst_csi_rs_pdu->symb_l1 = src_csi_rs_pdu->symb_l1;
		dst_csi_rs_pdu->cdm_type = src_csi_rs_pdu->cdm_type;
		dst_csi_rs_pdu->freq_density = src_csi_rs_pdu->freq_density;
		dst_csi_rs_pdu->scramb_id = src_csi_rs_pdu->scramb_id;
		dst_csi_rs_pdu->power_control_offset = src_csi_rs_pdu->power_control_offset;
		dst_csi_rs_pdu->power_control_offset_ss = src_csi_rs_pdu->power_control_offset_ss;
}

static void cp_nr_dl_tti_ssb_pdu(nfapi_nr_dl_tti_ssb_pdu_rel15_t *dst, const nfapi_nr_dl_tti_ssb_pdu_rel15_t *src) {
    if (dst == NULL || src == NULL) {
        return;
    }
		dst_ssb_pdu->PhysCellId = src_ssb_pdu->PhysCellId;
		dst_ssb_pdu->BetaPss = src_ssb_pdu->BetaPss;
		dst_ssb_pdu->SsbBlockIndex = src_ssb_pdu->SsbBlockIndex;
		dst_ssb_pdu->SsbSubcarrierOffset = src_ssb_pdu->SsbSubcarrierOffset;
		dst_ssb_pdu->ssbOffsetPointA = src_ssb_pdu->ssbOffsetPointA;
		dst_ssb_pdu->bchPayloadFlag = src_ssb_pdu->bchPayloadFlag;
		dst_ssb_pdu->bchPayload = src_ssb_pdu->bchPayload;
		dst_ssb_pdu->ssbRsrp = src_ssb_pdu->ssbRsrp;
		dst_ssb_pdu->precoding_and_beamforming = src_ssb_pdu->precoding_and_beamforming;
}
```

```c
static void cp_nr_dl_tti_req(nfapi_nr_dl_tti_request_t *dst, const nfapi_nr_dl_tti_request_t *src)
{
	if (dst == NULL || src == NULL) {
		NFAPI_TRACE(NFAPI_TRACE_ERROR, "cp_nr_dl_tti_req: dst or src is NULL\n");
        return;
	}
    dst->header = src->header;
    dst->SFN = src->SFN;
    dst->Slot = src->Slot;
    // Copy dl_tti_request_body
    dst->dl_tti_request_body.nPDUs = src->dl_tti_request_body.nPDUs;
    dst->dl_tti_request_body.nGroup = src->dl_tti_request_body.nGroup;
	// Iterate over dl_tti_pdu_list
    for (int i = 0; i < dst->dl_tti_request_body.nPDUs; ++i) {
        nfapi_nr_dl_tti_request_pdu_t *dst_pdu = &dst->dl_tti_request_body.dl_tti_pdu_list[i];
        const nfapi_nr_dl_tti_request_pdu_t *src_pdu = &src->dl_tti_request_body.dl_tti_pdu_list[i];
        dst_pdu->PDUType = src_pdu->PDUType;
        dst_pdu->PDUSize = src_pdu->PDUSize;
        // Copy union based on PDUType
        switch (src_pdu->PDUType) {
	        case NFAPI_NR_DL_TTI_PDCCH_PDU_TYPE:
	            cp_nr_dl_tti_pdcch_pdu(&dst->pdcch_pdu.pdcch_pdu_rel15, &src->pdcch_pdu.pdcch_pdu_rel15);
	            break;
	        case NFAPI_NR_DL_TTI_PDSCH_PDU_TYPE:
	            cp_nr_dl_tti_pdsch_pdu(&dst->pdsch_pdu.pdsch_pdu_rel15, &src->pdsch_pdu.pdsch_pdu_rel15);
	            break;
	        case NFAPI_NR_DL_TTI_CSI_RS_PDU_TYPE:
	            cp_nr_dl_tti_csi_rs_pdu(&dst->csi_rs_pdu.csi_rs_pdu_rel15, &src->csi_rs_pdu.csi_rs_pdu_rel15);
	            break;
	        case NFAPI_NR_DL_TTI_SSB_PDU_TYPE:
	            cp_nr_dl_tti_ssb_pdu(&dst->ssb_pdu.ssb_pdu_rel15, &src->ssb_pdu.ssb_pdu_rel15);
	            break;
    }
   // Copy the nUe array
    for (int i = 0; i < dst->dl_tti_request_body.nGroup; ++i) {
        dst->dl_tti_request_body.nUe[i] = src->dl_tti_request_body.nUe[i];
    }

    // Copy the PduIdx array
    for (int i = 0; i < dst->dl_tti_request_body.nPDUs; ++i) {
        for (int j = 0; j < dst->dl_tti_request_body.nUe[i]; ++j) {
            dst->dl_tti_request_body.PduIdx[i][j] = src->dl_tti_request_body.PduIdx[i][j];
        }
    }

    // Copy vendor_extension
    dst->vendor_extension = src->vendor_extension;
}

```