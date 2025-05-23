/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "/root/svaidhya/ASN1_file/rrc_15_3.asn1"
 * 	`asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/RRC/`
 */

#ifndef	_SRS_CarrierSwitching_H_
#define	_SRS_CarrierSwitching_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <NativeEnumerated.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_CHOICE.h>
#include "ServCellIndexRrc.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SRS_CarrierSwitching__srs_SwitchFromCarrier {
	SRS_CarrierSwitching__srs_SwitchFromCarrier_sUL	= 0,
	SRS_CarrierSwitching__srs_SwitchFromCarrier_nUL	= 1
} e_SRS_CarrierSwitching__srs_SwitchFromCarrier;
typedef enum SRS_CarrierSwitching__srs_TPC_PDCCH_Group_PR {
	SRS_CarrierSwitching__srs_TPC_PDCCH_Group_PR_NOTHING,	/* No components present */
	SRS_CarrierSwitching__srs_TPC_PDCCH_Group_PR_typeA,
	SRS_CarrierSwitching__srs_TPC_PDCCH_Group_PR_typeB
} SRS_CarrierSwitching__srs_TPC_PDCCH_Group_PR;

/* Forward declarations */
struct SRS_TPC_PDCCH_Config;

/* SRS-CarrierSwitching */
typedef struct SRS_CarrierSwitching {
	long	*srs_SwitchFromServCellIndex;	/* OPTIONAL */
	long	 srs_SwitchFromCarrier;
	struct SRS_CarrierSwitching__srs_TPC_PDCCH_Group {
		SRS_CarrierSwitching__srs_TPC_PDCCH_Group_PR present;
		union SRS_CarrierSwitching__srs_TPC_PDCCH_Group_u {
			struct SRS_CarrierSwitching__srs_TPC_PDCCH_Group__typeA {
				A_SEQUENCE_OF(struct SRS_TPC_PDCCH_Config) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *typeA;
			struct SRS_TPC_PDCCH_Config	*typeB;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *srs_TPC_PDCCH_Group;
	struct SRS_CarrierSwitching__monitoringCells {
		A_SEQUENCE_OF(ServCellIndexRrc_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *monitoringCells;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SRS_CarrierSwitching_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_srs_SwitchFromCarrier_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_SRS_CarrierSwitching;
extern asn_SEQUENCE_specifics_t asn_SPC_SRS_CarrierSwitching_specs_1;
extern asn_TYPE_member_t asn_MBR_SRS_CarrierSwitching_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SRS-TPC-PDCCH-Config.h"

#endif	/* _SRS_CarrierSwitching_H_ */
#include <asn_internal.h>
