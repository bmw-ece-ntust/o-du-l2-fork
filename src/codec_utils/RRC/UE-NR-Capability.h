/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "/root/svaidhya/ASN1_file/rrc_15_3.asn1"
 * 	`asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/RRC/`
 */

#ifndef	_UE_NR_Capability_H_
#define	_UE_NR_Capability_H_


#include <asn_application.h>

/* Including external dependencies */
#include "AccessStratumRelease.h"
#include "PDCP-Parameters.h"
#include "Phy-Parameters.h"
#include "RF-Parameters.h"
#include <OCTET_STRING.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RLC_Parameters;
struct MAC_Parameters;
struct MeasAndMobParameters;
struct UE_NR_CapabilityAddXDD_Mode;
struct UE_NR_CapabilityAddFRX_Mode;
struct FeatureSets;
struct FeatureSetCombination;

/* UE-NR-Capability */
typedef struct UE_NR_Capability {
	AccessStratumRelease_t	 accessStratumRelease;
	PDCP_Parameters_t	 pdcp_Parameters;
	struct RLC_Parameters	*rlc_Parameters;	/* OPTIONAL */
	struct MAC_Parameters	*mac_Parameters;	/* OPTIONAL */
	Phy_Parameters_t	 phy_Parameters;
	RF_Parameters_t	 rf_Parameters;
	struct MeasAndMobParameters	*measAndMobParameters;	/* OPTIONAL */
	struct UE_NR_CapabilityAddXDD_Mode	*fdd_Add_UE_NR_Capabilities;	/* OPTIONAL */
	struct UE_NR_CapabilityAddXDD_Mode	*tdd_Add_UE_NR_Capabilities;	/* OPTIONAL */
	struct UE_NR_CapabilityAddFRX_Mode	*fr1_Add_UE_NR_Capabilities;	/* OPTIONAL */
	struct UE_NR_CapabilityAddFRX_Mode	*fr2_Add_UE_NR_Capabilities;	/* OPTIONAL */
	struct FeatureSets	*featureSets;	/* OPTIONAL */
	struct UE_NR_Capability__featureSetCombinations {
		A_SEQUENCE_OF(struct FeatureSetCombination) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *featureSetCombinations;
	OCTET_STRING_t	*lateNonCriticalExtension;	/* OPTIONAL */
	struct UE_NR_Capability__nonCriticalExtension {
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *nonCriticalExtension;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UE_NR_Capability_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UE_NR_Capability;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "RLC-Parameters.h"
#include "MAC-Parameters.h"
#include "MeasAndMobParameters.h"
#include "UE-NR-CapabilityAddXDD-Mode.h"
#include "UE-NR-CapabilityAddFRX-Mode.h"
#include "FeatureSets.h"
#include "FeatureSetCombination.h"

#endif	/* _UE_NR_Capability_H_ */
#include <asn_internal.h>
