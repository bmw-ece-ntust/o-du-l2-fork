/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2AP-IEs"
 * 	found in "/root/svaidhya/ASN1_file/E2APV0300.asn1"
 * 	`asn1c -fno-include-deps -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/E2AP/`
 */

#ifndef	_AMFName_H_
#define	_AMFName_H_


#include <asn_application.h>

/* Including external dependencies */
#include <PrintableString.h>

#ifdef __cplusplus
extern "C" {
#endif

/* AMFName */
typedef PrintableString_t	 AMFName_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_AMFName_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_AMFName;
asn_struct_free_f AMFName_free;
asn_struct_print_f AMFName_print;
asn_constr_check_f AMFName_constraint;
xer_type_decoder_f AMFName_decode_xer;
xer_type_encoder_f AMFName_encode_xer;
per_type_decoder_f AMFName_decode_uper;
per_type_encoder_f AMFName_encode_uper;
per_type_decoder_f AMFName_decode_aper;
per_type_encoder_f AMFName_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _AMFName_H_ */
#include <asn_internal.h>
