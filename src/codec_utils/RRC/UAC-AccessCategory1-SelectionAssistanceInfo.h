/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "/root/svaidhya/ASN1_file/rrc_15_3.asn1"
 * 	`asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/RRC/`
 */

#ifndef	_UAC_AccessCategory1_SelectionAssistanceInfo_H_
#define	_UAC_AccessCategory1_SelectionAssistanceInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UAC_AccessCategory1_SelectionAssistanceInfo {
	UAC_AccessCategory1_SelectionAssistanceInfo_a	= 0,
	UAC_AccessCategory1_SelectionAssistanceInfo_b	= 1,
	UAC_AccessCategory1_SelectionAssistanceInfo_c	= 2
} e_UAC_AccessCategory1_SelectionAssistanceInfo;

/* UAC-AccessCategory1-SelectionAssistanceInfo */
typedef long	 UAC_AccessCategory1_SelectionAssistanceInfo_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_UAC_AccessCategory1_SelectionAssistanceInfo_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_UAC_AccessCategory1_SelectionAssistanceInfo;
extern const asn_INTEGER_specifics_t asn_SPC_UAC_AccessCategory1_SelectionAssistanceInfo_specs_1;
asn_struct_free_f UAC_AccessCategory1_SelectionAssistanceInfo_free;
asn_struct_print_f UAC_AccessCategory1_SelectionAssistanceInfo_print;
asn_constr_check_f UAC_AccessCategory1_SelectionAssistanceInfo_constraint;
xer_type_decoder_f UAC_AccessCategory1_SelectionAssistanceInfo_decode_xer;
xer_type_encoder_f UAC_AccessCategory1_SelectionAssistanceInfo_encode_xer;
per_type_decoder_f UAC_AccessCategory1_SelectionAssistanceInfo_decode_uper;
per_type_encoder_f UAC_AccessCategory1_SelectionAssistanceInfo_encode_uper;
per_type_decoder_f UAC_AccessCategory1_SelectionAssistanceInfo_decode_aper;
per_type_encoder_f UAC_AccessCategory1_SelectionAssistanceInfo_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _UAC_AccessCategory1_SelectionAssistanceInfo_H_ */
#include <asn_internal.h>
