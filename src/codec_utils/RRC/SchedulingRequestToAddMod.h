/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "/root/svaidhya/ASN1_file/rrc_15_3.asn1"
 * 	`asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/RRC/`
 */

#ifndef	_SchedulingRequestToAddMod_H_
#define	_SchedulingRequestToAddMod_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SchedulingRequestId.h"
#include <NativeEnumerated.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SchedulingRequestToAddMod__sr_ProhibitTimer {
	SchedulingRequestToAddMod__sr_ProhibitTimer_ms1	= 0,
	SchedulingRequestToAddMod__sr_ProhibitTimer_ms2	= 1,
	SchedulingRequestToAddMod__sr_ProhibitTimer_ms4	= 2,
	SchedulingRequestToAddMod__sr_ProhibitTimer_ms8	= 3,
	SchedulingRequestToAddMod__sr_ProhibitTimer_ms16	= 4,
	SchedulingRequestToAddMod__sr_ProhibitTimer_ms32	= 5,
	SchedulingRequestToAddMod__sr_ProhibitTimer_ms64	= 6,
	SchedulingRequestToAddMod__sr_ProhibitTimer_ms128	= 7
} e_SchedulingRequestToAddMod__sr_ProhibitTimer;
typedef enum SchedulingRequestToAddMod__sr_TransMax {
	SchedulingRequestToAddMod__sr_TransMax_n4	= 0,
	SchedulingRequestToAddMod__sr_TransMax_n8	= 1,
	SchedulingRequestToAddMod__sr_TransMax_n16	= 2,
	SchedulingRequestToAddMod__sr_TransMax_n32	= 3,
	SchedulingRequestToAddMod__sr_TransMax_n64	= 4,
	SchedulingRequestToAddMod__sr_TransMax_spare3	= 5,
	SchedulingRequestToAddMod__sr_TransMax_spare2	= 6,
	SchedulingRequestToAddMod__sr_TransMax_spare1	= 7
} e_SchedulingRequestToAddMod__sr_TransMax;

/* SchedulingRequestToAddMod */
typedef struct SchedulingRequestToAddMod {
	SchedulingRequestId_t	 schedulingRequestId;
	long	*sr_ProhibitTimer;	/* OPTIONAL */
	long	 sr_TransMax;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SchedulingRequestToAddMod_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_sr_ProhibitTimer_3;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_sr_TransMax_12;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_SchedulingRequestToAddMod;
extern asn_SEQUENCE_specifics_t asn_SPC_SchedulingRequestToAddMod_specs_1;
extern asn_TYPE_member_t asn_MBR_SchedulingRequestToAddMod_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _SchedulingRequestToAddMod_H_ */
#include <asn_internal.h>
