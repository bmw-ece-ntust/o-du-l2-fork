# Fix ASN.1 compiler issues

Start Date: 2024/10/17
Summary: Updating ASN.1-related folders in OSC to transition from the Nokia compiler to OAI's native ASN.1 struct definition while addressing compilation issues.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2025/02/10
SUM: 🗓️ Days Spent to Complete: 116

Due to issues with the Nokia compiler currently used by OSC, I hope to use OSC's native ASN.1 struct definition and fix the current problems for OSC using the compiler used by OAI

- The compiler originally used by OSC

[https://github.com/nokia/asn1c](https://github.com/nokia/asn1c)

- The compiler planned for a replacement

[https://github.com/mouse07410/asn1c](https://github.com/mouse07410/asn1c)

Therefore, I started updating the ASN.1-related folders in OSC:→ [How to Fix OSC asn1c Issues](How%20to%20Fix%20OSC%20asn1c%20Issues%20176100983143804bb9f3fd6a511b919c.md) 

- RRC → [OSC RRC ASN.1 file](OSC%20RRC%20ASN%201%20file%20121100983143816c86a6e7063521baf1.md)
- F1AP → [OSC F1AP ASN.1 file](OSC%20F1AP%20ASN%201%20file%201211009831438070bb80c050fcf47cdf.md)
- E2AP → [OSC E2AP ASN.1 file](OSC%20E2AP%20ASN%201%20file%2012110098314380ebbef6c4d726bd0894.md)

---

<aside>
💡

From Prof.Rat Information: Mongazon 10:27 PM 

</aside>

Since Laurent has invited me, I will write here how we proceed in LTEBox/ SABox code regarding ASN.1. 1. C code is generated from ASN.1 file(s). If a file depends on the inclusion of another one or multiple ones, all files are provided as input to asn1c. The generated code for the set of thus-selected files is put in a library. In order to allow the thus generated libraries to be linked together, we use the ASN1C_PREFIX=xxxx. We use asn1c from Nokia public github with the following arguments: "-gen-PER -no-gen-OER -fcompound-names -findirect-choice -fno-include-deps". The asn1c from Nokia public github has some lacks which are being filled now, in particular NR-RRC does not compile yet. We are working on it. Important note is that we keep the basic ASN.1 types in a separate library. 2. The libraries built from 1. can be

---

linked together to form a complete ASN.1 implementation for a given protocol stack.

Key points:

- OSC is transitioning from Nokia compiler to OAI's native ASN.1 struct definition
- ASN.1-related folders in OSC (RRC, F1AP, E2AP) are being updated
- Current process involves generating C code from ASN.1 files using specific compiler arguments
- Basic ASN.1 types are kept in a separate library
- NR-RRC compilation issues are being addressed
- Generated libraries can be linked to form a complete ASN.1 implementation for a protocol stack