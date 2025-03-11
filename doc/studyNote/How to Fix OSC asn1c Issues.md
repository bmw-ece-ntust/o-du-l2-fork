# How to Fix OSC asn1c Issues

Start Date: 2025/01/09
Summary: Replacing the ASN.1 compiler in OSC by switching to a different fork while addressing compilation issues.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: PIN
Finish Date: 2025/02/10
SUM: 🗓️ Days Spent to Complete: 32

## Motivation

Replacing the ASN.1 compiler by switching from Nokia's fork to mouse07410's fork, while reorganizing the folder structure and resolving compilation issues.

💡 [Responding to Nokia’s email about new test file](Responding%20to%20Nokia%E2%80%99s%20email%20about%20new%20test%20file%2013610098314380579e60f368397cf5db.md) 

💡 [Use another(mouse07410) asn.1 compiler (asn1c)](Use%20another(mouse07410)%20asn%201%20compiler%20(asn1c)%2012e1009831438015baa3f32e16b207e0.md)

💡 [Fix ASN.1 compiler issues](Fix%20ASN%201%20compiler%20issues%201221009831438019ae05ee8563d9a476.md) 

When we need to encode the SIB1 data into ASN.1 in OSC and then send it out via nFAPI, the current version of OSC fails to encode searchSpace->searchSpaceType. However, this is a required parameter. The OSC source code also mentions that this is an unresolved issue.

```c
/* Commented due to ASN decode failure in wireshark.
 * Parameters like dci_Format0_0_AndFormat1_0 which are pointer to a structure that 
 * does not have any member parameter lead to decode failure in wireshark. 
 * The issue has been reported to Nokia.
 * The following code will be uncommented once the issue is resolved */
```

## Problem Description

[OSC ASN.1 file status](OSC%20ASN%201%20file%20status%2012110098314380edaf54c79ad7358cca.md) 

The ASN.1 compiler (hereafter referred to as asn1c) currently used by OSC is a version forked and developed by Nokia from an open-source repository. However, multiple tests have confirmed that Nokia's developed asn1c has issues. There are two solutions to address this situation:

- Wait for Nokia's fix (OSC's recommended method)
- **Recompile using the asn1c version currently adopted by OAI (forked and developed by mouse from the same open-source repository, which is the method used in this note)**

Reference Information:

- Nokia asn1c → (Forked form https://github.com/velichkov/asn1c → forked from https://github.com/vlm/asn1c)

[https://github.com/nokia/asn1c](https://github.com/nokia/asn1c)

- mouse07410 asn1c → (forked from https://github.com/vlm/asn1c)

[https://github.com/mouse07410/asn1c](https://github.com/mouse07410/asn1c)

## Experimental Procedure:

To systematically propose a solution, I created a table to record all possible test combinations and their results.

Version numbers used in the environment:

---

- OAI RRC v17.3.0
- OAI F1AP ETSI TS 138 473 **V16.3.1** (2020-11)
    - 5G; NG-RAN; F1 Application Protocol (F1AP) (3GPP TS 38.473 version 16.3.1 Release 16)
- OAI E2AP  v3.01
- OAI E2SM_KPM v3.00

---

- OSC RRC v15.3
- OSC F1AP ETSI TS 138 473 **V17.3.0** (2023-01)
    - 5G; NG-RAN; F1 Application Protocol (F1AP) (3GPP TS 38.473 version 17.3.0 Release 17)
- OSC E2AP  v0300
- OSC E2SM_KPM v3.0

---

The test variables include:

- ASN.1 definition file provided by OSC
- ASN.1 definition file provided by OAI
- asn1c used by OSC (maintained by Nokia)
- asn1c used by OAI (maintained by mouse07410)

Comparison Table:

|  | ASN.1 definition file (OAI) | ASN.1 definition file (OSC) |
| --- | --- | --- |
| asn1c (mouse07410) | ❌ [Use ASN.1 definition file (OAI) with asn1c (mouse07410)](Use%20ASN%201%20definition%20file%20(OAI)%20with%20asn1c%20(mouse0%201761009831438092a5e6fc33541bd1d1.md)  | ✅ [Use ASN.1 definition file (OSC) with asn1c (mouse07410)](Use%20ASN%201%20definition%20file%20(OSC)%20with%20asn1c%20(mouse0%201761009831438038b06dddef537752ed.md)  |
| asn1c (Nokia) | ❌ [Update OSC ASN.1 version -1](Update%20OSC%20ASN%201%20version%20-1%2012110098314381579d9ed08d5956749b.md) | **OSC native environment (experiencing issues)** |

## Solution (Tested Successfully)

✅ [Use ASN.1 definition file (OSC) with asn1c (mouse07410)](Use%20ASN%201%20definition%20file%20(OSC)%20with%20asn1c%20(mouse0%201761009831438038b06dddef537752ed.md) 

Option 2: Await Nokia's update

⏳ [Responding to Nokia’s email about new test file](Responding%20to%20Nokia%E2%80%99s%20email%20about%20new%20test%20file%2013610098314380579e60f368397cf5db.md) 

## Known Issues (Documentation of Problems Encountered Across All Test Cases)

⚠️ [**ASN.1 file build: unknown type name**](ASN%201%20file%20build%20unknown%20type%20name%201221009831438027a679c6b997f60b5b.md) 

⚠️ Initially, I hypothesized that OAI's functionality might be due to its use of CMake.

- [Refactor Development Code for SIB1 ASN.1 in Preparation for New Nokia asn1c Integration](Refactor%20Development%20Code%20for%20SIB1%20ASN%201%20in%20Prepar%2013d1009831438065ad24d2d8167e4721.md)
- [OSC asn1c .cmake File Generation](OSC%20asn1c%20cmake%20File%20Generation%2014d100983143805fb970eb6975364058.md)

After consulting with Robert about implementing CMake in OSC, I discovered that the solution was unrelated to this approach.