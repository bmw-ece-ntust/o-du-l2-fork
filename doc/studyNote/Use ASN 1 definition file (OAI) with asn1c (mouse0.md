# Use ASN.1 definition file (OAI) with asn1c (mouse07410)

Start Date: 2025/01/09
Summary: Testing confirms the necessity of using OSC's modified ASN.1 definition files for proper implementation in OSC's project source code.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Finish Date: 2025/01/09
SUM: 🗓️ Days Spent to Complete: 0

Conclusion: Testing confirms that OSC's definition files must be used

The test environment was validated following OAI's current usage method. Although the files compiled by asn1c can be successfully compiled through gcc, they cannot be used in OSC's source code such as du_app. The main reason is that OSC modified the asn1 definition files, resulting in different compiled file names compared to the original version. Since OSC's source code is written based on these modified file names, files compiled using the standard-compliant OAI asn1c definition files cannot be correctly referenced.

For example, OSC adds suffixes (xxxE2) to many variable names in the E2AP definition file. Based on my analysis, this is to avoid naming conflicts with identical variable names in protocols such as F1AP and RRC.

![image.png](image%2099.png)

The left image shows the definition files provided by OAI and the specification, while the right image shows OSC's modified version.

Another example (in RRC):

OSC will arbitrarily modify the .asn1 file (therefore, if you want to use it in the OSC project's du_app, you must use their modified .asn1 file)

![image.png](image%2046.png)

The left side shows the .asn1 file provided by OAI and the spec, while the right side shows the one provided by OSC

Based on this comparison, it is confirmed that OSC's provided asn1 definition files must be used for correct implementation in OSC's project source code.