/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "/root/svaidhya/ASN1_file/rrc_15_3.asn1"
 * 	`asn1c -pdu=all -fcompound-names -gen-UPER -no-gen-BER -no-gen-JER -no-gen-OER -gen-APER -no-gen-example -findirect-choice -D /root/svaidhya/28March_ASN1_l2/l2/src/codec_utils/RRC/`
 */

#include "UE-CapabilityRequestFilterNR.h"

static const ber_tlv_tag_t asn_DEF_nonCriticalExtension_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SEQUENCE_specifics_t asn_SPC_nonCriticalExtension_specs_3 = {
	sizeof(struct UE_CapabilityRequestFilterNR__nonCriticalExtension),
	offsetof(struct UE_CapabilityRequestFilterNR__nonCriticalExtension, _asn_ctx),
	0,	/* No top level tags */
	0,	/* No tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nonCriticalExtension_3 = {
	"nonCriticalExtension",
	"nonCriticalExtension",
	&asn_OP_SEQUENCE,
	asn_DEF_nonCriticalExtension_tags_3,
	sizeof(asn_DEF_nonCriticalExtension_tags_3)
		/sizeof(asn_DEF_nonCriticalExtension_tags_3[0]) - 1, /* 1 */
	asn_DEF_nonCriticalExtension_tags_3,	/* Same as above */
	sizeof(asn_DEF_nonCriticalExtension_tags_3)
		/sizeof(asn_DEF_nonCriticalExtension_tags_3[0]), /* 2 */
	{
#if !defined(ASN_DISABLE_OER_SUPPORT)
		0,
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */
#if !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT)
		0,
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT) */
#if !defined(ASN_DISABLE_JER_SUPPORT)
		0,
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */
		SEQUENCE_constraint
	},
	0, 0,	/* No members */
	&asn_SPC_nonCriticalExtension_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UE_CapabilityRequestFilterNR_1[] = {
	{ ATF_POINTER, 2, offsetof(struct UE_CapabilityRequestFilterNR, frequencyBandListr),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FreqBandList,
		0,
		{
#if !defined(ASN_DISABLE_OER_SUPPORT)
			0,
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */
#if !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT)
			0,
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT) */
#if !defined(ASN_DISABLE_JER_SUPPORT)
			0,
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */
			0
		},
		0, 0, /* No default value */
		"frequencyBandListr"
		},
	{ ATF_POINTER, 1, offsetof(struct UE_CapabilityRequestFilterNR, nonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_nonCriticalExtension_3,
		0,
		{
#if !defined(ASN_DISABLE_OER_SUPPORT)
			0,
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */
#if !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT)
			0,
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT) */
#if !defined(ASN_DISABLE_JER_SUPPORT)
			0,
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */
			0
		},
		0, 0, /* No default value */
		"nonCriticalExtension"
		},
};
static const int asn_MAP_UE_CapabilityRequestFilterNR_oms_1[] = { 0, 1 };
static const ber_tlv_tag_t asn_DEF_UE_CapabilityRequestFilterNR_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_UE_CapabilityRequestFilterNR_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* frequencyBandListr */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* nonCriticalExtension */
};
static asn_SEQUENCE_specifics_t asn_SPC_UE_CapabilityRequestFilterNR_specs_1 = {
	sizeof(struct UE_CapabilityRequestFilterNR),
	offsetof(struct UE_CapabilityRequestFilterNR, _asn_ctx),
	asn_MAP_UE_CapabilityRequestFilterNR_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_UE_CapabilityRequestFilterNR_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_UE_CapabilityRequestFilterNR = {
	"UE-CapabilityRequestFilterNR",
	"UE-CapabilityRequestFilterNR",
	&asn_OP_SEQUENCE,
	asn_DEF_UE_CapabilityRequestFilterNR_tags_1,
	sizeof(asn_DEF_UE_CapabilityRequestFilterNR_tags_1)
		/sizeof(asn_DEF_UE_CapabilityRequestFilterNR_tags_1[0]), /* 1 */
	asn_DEF_UE_CapabilityRequestFilterNR_tags_1,	/* Same as above */
	sizeof(asn_DEF_UE_CapabilityRequestFilterNR_tags_1)
		/sizeof(asn_DEF_UE_CapabilityRequestFilterNR_tags_1[0]), /* 1 */
	{
#if !defined(ASN_DISABLE_OER_SUPPORT)
		0,
#endif  /* !defined(ASN_DISABLE_OER_SUPPORT) */
#if !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT)
		0,
#endif  /* !defined(ASN_DISABLE_UPER_SUPPORT) || !defined(ASN_DISABLE_APER_SUPPORT) */
#if !defined(ASN_DISABLE_JER_SUPPORT)
		0,
#endif  /* !defined(ASN_DISABLE_JER_SUPPORT) */
		SEQUENCE_constraint
	},
	asn_MBR_UE_CapabilityRequestFilterNR_1,
	2,	/* Elements count */
	&asn_SPC_UE_CapabilityRequestFilterNR_specs_1	/* Additional specs */
};

