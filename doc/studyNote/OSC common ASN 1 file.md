# OSC common  ASN.1 file

Start Date: 2024/10/16
Summary: Development and documentation of an ASN.1 file for OSC common, including project timelines and associated source code files.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2025/01/09
SUM: 🗓️ Days Spent to Complete: 85

```jsx
-rw-rw-r-- 1 hpe hpe 15175  七  22 22:21 asn_application.c
-rw-rw-r-- 1 hpe hpe  6168  七  22 22:21 asn_application.h
-rw-rw-r-- 1 hpe hpe  3444  七  22 22:21 asn_codecs.h
-rw-rw-r-- 1 hpe hpe  1095  七  22 22:21 asn_internal.c
-rw-rw-r-- 1 hpe hpe  5619  七  22 22:21 asn_internal.h
-rw-rw-r-- 1 hpe hpe  3915  七  22 22:21 asn_system.h
-rw-rw-r-- 1 hpe hpe  7784  七  22 22:21 ber_decoder.c
-rw-rw-r-- 1 hpe hpe  2243  七  22 22:21 ber_decoder.h
-rw-rw-r-- 1 hpe hpe  3446  七  22 22:21 ber_tlv_length.c
-rw-rw-r-- 1 hpe hpe  1544  七  22 22:21 ber_tlv_length.h
-rw-rw-r-- 1 hpe hpe  3188  七  22 22:21 ber_tlv_tag.c
-rw-rw-r-- 1 hpe hpe  1835  七  22 22:21 ber_tlv_tag.h
-rw-rw-r-- 1 hpe hpe  1851  七  22 22:21 constr_TYPE.c
-rw-rw-r-- 1 hpe hpe 10253  七  22 22:21 constr_TYPE.h
-rw-rw-r-- 1 hpe hpe  5320  七  22 22:21 der_encoder.c
-rw-rw-r-- 1 hpe hpe  2312  七  22 22:21 der_encoder.h
-rw-rw-r-- 1 hpe hpe 65964  七  22 22:21 OCTET_STRING.c
-rw-rw-r-- 1 hpe hpe  3583  七  22 22:21 OCTET_STRING.h
-rw-rw-r-- 1 hpe hpe  4702  七  22 22:21 odu_common_codec.c
-rw-rw-r-- 1 hpe hpe  2161  七  22 22:21 odu_common_codec.h
-rw-rw-r-- 1 hpe hpe  5064  七  22 22:21 per_decoder.c
-rw-rw-r-- 1 hpe hpe  3004  七  22 22:21 per_decoder.h
-rw-rw-r-- 1 hpe hpe  6543  七  22 22:21 per_encoder.c
-rw-rw-r-- 1 hpe hpe  3293  七  22 22:21 per_encoder.h
-rw-rw-r-- 1 hpe hpe 11743  七  22 22:21 per_support.c
-rw-rw-r-- 1 hpe hpe  4267  七  22 22:21 per_support.h
-rw-rw-r-- 1 hpe hpe  8869  七  22 22:21 xer_decoder.c
-rw-rw-r-- 1 hpe hpe  3599  七  22 22:21 xer_decoder.h
-rw-rw-r-- 1 hpe hpe  7083  七  22 22:21 xer_encoder.c
-rw-rw-r-- 1 hpe hpe  3017  七  22 22:21 xer_encoder.h
```

```bash
ANY_aper.c             asn_SET_OF.h            constr_SEQUENCE_OF_aper.c  Makefile.am.libasncodec    OPEN_TYPE_aper.c
ANY.c                  asn_system.h            constr_SEQUENCE_OF.c       NativeEnumerated_aper.c    OPEN_TYPE.c
ANY.h                  ber_tlv_length.c        constr_SEQUENCE_OF.h       NativeEnumerated.c         OPEN_TYPE.h
ANY_uper.c             ber_tlv_length.h        constr_SEQUENCE_OF_uper.c  NativeEnumerated.h         OPEN_TYPE_uper.c
ANY_xer.c              ber_tlv_tag.c           constr_SEQUENCE_OF_xer.c   NativeEnumerated_uper.c    OPEN_TYPE_xer.c
aper_decoder.c         ber_tlv_tag.h           constr_SEQUENCE_print.c    NativeEnumerated_xer.c     per_decoder.c
aper_decoder.h         BIT_STRING.c            constr_SEQUENCE_rfill.c    NativeInteger_aper.c       per_decoder.h
aper_encoder.c         BIT_STRING.h            constr_SEQUENCE_uper.c     NativeInteger.c            per_encoder.c
aper_encoder.h         BIT_STRING_print.c      constr_SEQUENCE_xer.c      NativeInteger.h            per_encoder.h
aper_opentype.c        BIT_STRING_rfill.c      constr_SET_OF_aper.c       NativeInteger_print.c      per_opentype.c
aper_opentype.h        BIT_STRING_uper.c       constr_SET_OF.c            NativeInteger_rfill.c      per_opentype.h
aper_support.c         BIT_STRING_xer.c        constr_SET_OF.h            NativeInteger_uper.c       per_support.c
aper_support.h         BOOLEAN_aper.c          constr_SET_OF_print.c      NativeInteger_xer.c        per_support.h
asn_application.c      BOOLEAN.c               constr_SET_OF_rfill.c      NULL.c                     PrintableString.c
asn_application.h      BOOLEAN.h               constr_SET_OF_uper.c       NULL.h                     PrintableString.h
asn_bit_data.c         BOOLEAN_print.c         constr_SET_OF_xer.c        ObjectDescriptor.c         uper_decoder.c
asn_bit_data.h         BOOLEAN_rfill.c         constr_TYPE.c              ObjectDescriptor.h         uper_decoder.h
asn_codecs.h           BOOLEAN_uper.c          constr_TYPE.h              OBJECT_IDENTIFIER.c        uper_encoder.c
asn_codecs_prim.c      BOOLEAN_xer.c           ENUMERATED_aper.c          OBJECT_IDENTIFIER.h        uper_encoder.h
asn_codecs_prim.h      constraints.c           ENUMERATED.c               OBJECT_IDENTIFIER_print.c  uper_opentype.c
asn_codecs_prim_xer.c  constraints.h           ENUMERATED.h               OBJECT_IDENTIFIER_rfill.c  uper_opentype.h
asn_config.h           constr_CHOICE_aper.c    ENUMERATED_uper.c          OBJECT_IDENTIFIER_xer.c    uper_support.c
asn_constant.h         constr_CHOICE.c         GraphicString.c            OCTET_STRING_aper.c        uper_support.h
asn_internal.c         constr_CHOICE.h         GraphicString.h            OCTET_STRING.c             xer_decoder.c
asn_internal.h         constr_CHOICE_print.c   INTEGER_aper.c             OCTET_STRING.h             xer_decoder.h
asn_ioc.h              constr_CHOICE_rfill.c   INTEGER.c                  OCTET_STRING_print.c       xer_encoder.c
asn_random_fill.c      constr_CHOICE_uper.c    INTEGER.h                  OCTET_STRING_rfill.c       xer_encoder.h
asn_random_fill.h      constr_CHOICE_xer.c     INTEGER_print.c            OCTET_STRING_uper.c        xer_support.c
asn_SEQUENCE_OF.c      constr_SEQUENCE_aper.c  INTEGER_rfill.c            OCTET_STRING_xer.c         xer_support.h
asn_SEQUENCE_OF.h      constr_SEQUENCE.c       INTEGER_uper.c             odu_common_codec.c
asn_SET_OF.c           constr_SEQUENCE.h       INTEGER_xer.c              odu_common_codec.h
```