/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "/root/svaidhya/ASN1_file/rrc_15_3.asn1"
 * 	`asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/RRC/`
 */

#ifndef	_Phy_ParametersFR1_H_
#define	_Phy_ParametersFR1_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Phy_ParametersFR1__pdcchMonitoringSingleOccasion {
	Phy_ParametersFR1__pdcchMonitoringSingleOccasion_supported	= 0
} e_Phy_ParametersFR1__pdcchMonitoringSingleOccasion;
typedef enum Phy_ParametersFR1__scs_60kHz {
	Phy_ParametersFR1__scs_60kHz_supported	= 0
} e_Phy_ParametersFR1__scs_60kHz;
typedef enum Phy_ParametersFR1__pdsch_256QAM_FR1 {
	Phy_ParametersFR1__pdsch_256QAM_FR1_supported	= 0
} e_Phy_ParametersFR1__pdsch_256QAM_FR1;
typedef enum Phy_ParametersFR1__pdsch_RE_MappingFR1_PerSymbol {
	Phy_ParametersFR1__pdsch_RE_MappingFR1_PerSymbol_n10	= 0,
	Phy_ParametersFR1__pdsch_RE_MappingFR1_PerSymbol_n20	= 1
} e_Phy_ParametersFR1__pdsch_RE_MappingFR1_PerSymbol;

/* Phy-ParametersFR1 */
typedef struct Phy_ParametersFR1 {
	long	*pdcchMonitoringSingleOccasion;	/* OPTIONAL */
	long	*scs_60kHz;	/* OPTIONAL */
	long	*pdsch_256QAM_FR1;	/* OPTIONAL */
	long	*pdsch_RE_MappingFR1_PerSymbol;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Phy_ParametersFR1_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_pdcchMonitoringSingleOccasion_2;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_scs_60kHz_4;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_pdsch_256QAM_FR1_6;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_pdsch_RE_MappingFR1_PerSymbol_8;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_Phy_ParametersFR1;
extern asn_SEQUENCE_specifics_t asn_SPC_Phy_ParametersFR1_specs_1;
extern asn_TYPE_member_t asn_MBR_Phy_ParametersFR1_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _Phy_ParametersFR1_H_ */
#include <asn_internal.h>
