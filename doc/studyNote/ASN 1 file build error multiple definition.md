# ASN.1 file build error: multiple definition

Start Date: 2024/10/17
Summary: Resolving a build error in ASN.1 files caused by multiple definitions in different compiler environments.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: ASN.1
Finish Date: 2024/10/17
SUM: 🗓️ Days Spent to Complete: 0

Using the same file but different compilers, the results can vary significantly. The ASN.1 compiler used by OSC (created by Nokia) has lower support, so it seems OSC still needs to create a COMMON folder to store functions that Nokia's compiler needs to include. On the other hand, the ASN.1 compiler used by OAI has sufficient functionality, thus including the COMMON features:

```
-e Compiling [31m[1m /home/hpe/o-du-l2/src/phy_stub//phy_stub_ex_ms.c [m
-e Compiling [31m[1m /home/hpe/o-du-l2/src/phy_stub//phy_stub_msg_hdl.c [m
-e Compiling [31m[1m /home/hpe/o-du-l2/src/phy_stub//phy_stub_thread_hdl.c [m
-e Creating Archive [31m[1m /home/hpe/o-du-l2/build/odu/lib/odu/libphystub.a [m
make[1]: Leaving directory '/home/hpe/o-du-l2/build/odu'
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/ANY_aper.o: in function `ANY_fromType_aper':
/home/hpe/o-du-l2/src/codec_utils/RRC/ANY_aper.c:20: multiple definition of `ANY_fromType_aper'; /home/hpe/o-du-l2/build/odu/obj/odu/ANY.o:/home/hpe/o-du-l2/src/codec_utils/common/ANY.c:116: first defined here
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/ANY_aper.o: in function `ANY_new_fromType_aper':
/home/hpe/o-du-l2/src/codec_utils/RRC/ANY_aper.c:51: multiple definition of `ANY_new_fromType_aper'; /home/hpe/o-du-l2/build/odu/obj/odu/ANY.o:/home/hpe/o-du-l2/src/codec_utils/common/ANY.c:171: first defined here
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/ANY_aper.o: in function `ANY_to_type_aper':
/home/hpe/o-du-l2/src/codec_utils/RRC/ANY_aper.c:75: multiple definition of `ANY_to_type_aper'; /home/hpe/o-du-l2/build/odu/obj/odu/ANY.o:/home/hpe/o-du-l2/src/codec_utils/common/ANY.c:222: first defined here
/usr/bin/ld: /home/hpe/o-du-l2/build/odu/obj/odu/ANY_aper.o: in function `ANY_decode_aper':
```

## Solution:

- Remove the multiple definition file from the `COMMON` folder: `src/codec_utils/common/ANY.c`