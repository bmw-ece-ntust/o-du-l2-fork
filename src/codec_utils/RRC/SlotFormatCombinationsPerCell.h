/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "/root/svaidhya/ASN1_file/rrc_15_3.asn1"
 * 	`asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/RRC/`
 */

#ifndef	_SlotFormatCombinationsPerCell_H_
#define	_SlotFormatCombinationsPerCell_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ServCellIndexRrc.h"
#include "SubcarrierSpacing.h"
#include <NativeInteger.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SlotFormatCombination;

/* SlotFormatCombinationsPerCell */
typedef struct SlotFormatCombinationsPerCell {
	ServCellIndexRrc_t	 servingCellId;
	SubcarrierSpacing_t	 subcarrierSpacing;
	SubcarrierSpacing_t	*subcarrierSpacing2;	/* OPTIONAL */
	struct SlotFormatCombinationsPerCell__slotFormatCombinations {
		A_SEQUENCE_OF(struct SlotFormatCombination) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *slotFormatCombinations;
	long	*positionInDCI;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SlotFormatCombinationsPerCell_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SlotFormatCombinationsPerCell;
extern asn_SEQUENCE_specifics_t asn_SPC_SlotFormatCombinationsPerCell_specs_1;
extern asn_TYPE_member_t asn_MBR_SlotFormatCombinationsPerCell_1[5];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SlotFormatCombination.h"

#endif	/* _SlotFormatCombinationsPerCell_H_ */
#include <asn_internal.h>
