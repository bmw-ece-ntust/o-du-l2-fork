/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "/root/svaidhya/ASN1_file/rrc_15_3.asn1"
 * 	`asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/RRC/`
 */

#ifndef	_TDD_UL_DL_Pattern_H_
#define	_TDD_UL_DL_Pattern_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity {
	TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity_ms0p5	= 0,
	TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity_ms0p625	= 1,
	TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity_ms1	= 2,
	TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity_ms1p25	= 3,
	TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity_ms2	= 4,
	TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity_ms2p5	= 5,
	TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity_ms5	= 6,
	TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity_ms10	= 7
} e_TDD_UL_DL_Pattern__dl_UL_TransmissionPeriodicity;
typedef enum TDD_UL_DL_Pattern__ext1__dl_UL_TransmissionPeriodicity_v1530 {
	TDD_UL_DL_Pattern__ext1__dl_UL_TransmissionPeriodicity_v1530_ms3	= 0,
	TDD_UL_DL_Pattern__ext1__dl_UL_TransmissionPeriodicity_v1530_ms4	= 1
} e_TDD_UL_DL_Pattern__ext1__dl_UL_TransmissionPeriodicity_v1530;

/* TDD-UL-DL-Pattern */
typedef struct TDD_UL_DL_Pattern {
	long	 dl_UL_TransmissionPeriodicity;
	long	 nrofDownlinkSlots;
	long	 nrofDownlinkSymbols;
	long	 nrofUplinkSlots;
	long	 nrofUplinkSymbols;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct TDD_UL_DL_Pattern__ext1 {
		long	*dl_UL_TransmissionPeriodicity_v1530;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext1;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TDD_UL_DL_Pattern_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_dl_UL_TransmissionPeriodicity_2;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_dl_UL_TransmissionPeriodicity_v1530_17;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_TDD_UL_DL_Pattern;
extern asn_SEQUENCE_specifics_t asn_SPC_TDD_UL_DL_Pattern_specs_1;
extern asn_TYPE_member_t asn_MBR_TDD_UL_DL_Pattern_1[6];

#ifdef __cplusplus
}
#endif

#endif	/* _TDD_UL_DL_Pattern_H_ */
#include <asn_internal.h>
