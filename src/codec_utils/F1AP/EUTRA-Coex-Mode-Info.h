/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "F1AP-IEs"
 * 	found in "/root/svaidhya/ASN1_file/F1.asn1"
 * 	`asn1c -pdu=all -fno-include-deps -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/F1AP/`
 */

#ifndef	_EUTRA_Coex_Mode_Info_H_
#define	_EUTRA_Coex_Mode_Info_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum EUTRA_Coex_Mode_Info_PR {
	EUTRA_Coex_Mode_Info_PR_NOTHING,	/* No components present */
	EUTRA_Coex_Mode_Info_PR_fDD,
	EUTRA_Coex_Mode_Info_PR_tDD
	/* Extensions may appear below */
	
} EUTRA_Coex_Mode_Info_PR;

/* Forward declarations */
struct EUTRA_Coex_FDD_Info;
struct EUTRA_Coex_TDD_Info;

/* EUTRA-Coex-Mode-Info */
typedef struct EUTRA_Coex_Mode_Info {
	EUTRA_Coex_Mode_Info_PR present;
	union EUTRA_Coex_Mode_Info_u {
		struct EUTRA_Coex_FDD_Info	*fDD;
		struct EUTRA_Coex_TDD_Info	*tDD;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} EUTRA_Coex_Mode_Info_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EUTRA_Coex_Mode_Info;
extern asn_CHOICE_specifics_t asn_SPC_EUTRA_Coex_Mode_Info_specs_1;
extern asn_TYPE_member_t asn_MBR_EUTRA_Coex_Mode_Info_1[2];
extern asn_per_constraints_t asn_PER_type_EUTRA_Coex_Mode_Info_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _EUTRA_Coex_Mode_Info_H_ */
#include <asn_internal.h>
