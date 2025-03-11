# Responding to Nokia’s email about new test file

Start Date: 2024/11/06
Summary: Work involves addressing issues with the ASN.1 compiler related to differences in generated files and resolving constraints in NGAP specifications.
Status: padding
Assign: Ming 咚咚 [銘鴻]
Tags: mail

[ASN.1 Compiler Issues: A Solution](https://gamma.app/docs/ASN1-Compiler-Issues-A-Solution-rh06y6e47owondi)

[newWA.tar](newWA.tar)

[Starus trace](Responding%20to%20Nokia%E2%80%99s%20email%20about%20new%20test%20file%2013610098314380579e60f368397cf5db.md) 

## Main Steps:

```bash
Hello

This version should be the right one.

Copy and extract the attached file, it contains:

- justTest.sh // The shell script to be executed.
- SearchSpace.c.old // The Nokia asn1c generated file.
- SearchSpace.c.new // The corrected version.

Go into the RRC directory:

*cd RRC*

And execute the shell script:

*./justTest.sh*

And you should have a difference with the three files as with Mouse version.

You may also compare RRC/APER (Nokia version) with the RRC/APER (Mouse version) they should be the identical.

Best regards,

Erick Bizouarn
```

## Action Items:

- [x]  Extract "newWA.tar"
- [x]  Run `./justTest.sh` in RRC directory
- [x]  Compare files with Mouse version
- [x]  Check RRC/APER versions match
- [x]  Report results to Erick

[patchVoidSequence.tar](patchVoidSequence.tar)

Hello

The attached file contains the asn1c file:

asn1c-s1ap/libasn1compiler/asn1c_C.c

Can you extract the file and regenerate the asn1c code generator and test it with the previous examples. ?

Please send me the results.

Best regards,

Erick Bizouarn

## My progress

```bash
hpe@hpe-ProLiant-DL380-Gen10:~/Nokia-Test/asn1c-s1ap/libasn1compiler$ gcc -o asn1c_C asn1c_C.c
asn1c_C.c:5:10: fatal error: asn1c_internal.h: No such file or directory
    5 | #include "asn1c_internal.h"
      |          ^~~~~~~~~~~~~~~~~~
compilation terminated.
```

- patch file

```bash
hpe@hpe-ProLiant-DL380-Gen10:~/asn1c$ git diff
diff --git a/libasn1compiler/asn1c_C.c b/libasn1compiler/asn1c_C.c
index fad5fbd3..69925c26 100644
--- a/libasn1compiler/asn1c_C.c
+++ b/libasn1compiler/asn1c_C.c
@@ -439,6 +439,7 @@ asn1c_lang_C_type_SEQUENCE_def(arg_t *arg, asn1c_ioc_table_and_objset_t *opt_ioc
        /*
         * Fetch every inner tag from the tag to elements map.
         */
+
        if(_fill_tag2el_map(arg, &tag2el, &tag2el_count, -1, FTE_ALLTAGS)) {
                if(tag2el) free(tag2el);
                return -1;
@@ -526,6 +527,12 @@ asn1c_lang_C_type_SEQUENCE_def(arg_t *arg, asn1c_ioc_table_and_objset_t *opt_ioc
                        aoms_count = 0;
                }
        } else {
+               TQ_FOR(v, &(expr->members), next) {
+                  if(v->expr_type == A1TC_EXTENSIBLE) {
+                       first_extension = 0;
+                       break;
+                   }
+                }
                elements = 0;
                roms_count = 0;
                aoms_count = 0;
```

[regenerateASN1C.patch](regenerateASN1C.patch)

- When I rebuild ASN1C

```bash
Build
Build the libraries and the compiler:

make
Ensure asn1c is still behaving well after compiling on your platform:

make check
```

```bash
make  check-TESTS
make[3]: Entering directory '/home/hpe/asn1c/tests/tests-asn1c-compiler'
make[4]: Entering directory '/home/hpe/asn1c/tests/tests-asn1c-compiler'
FAIL: check-parsing.sh
============================================================================
Testsuite summary for asn1c 0.9.29
============================================================================
# TOTAL: 1
# PASS:  0
# SKIP:  0
# XFAIL: 0
# FAIL:  1
# XPASS: 0
# ERROR: 0
============================================================================
See tests/tests-asn1c-compiler/test-suite.log
Please report to vlm@lionet.info
============================================================================
make[4]: *** [Makefile:548: test-suite.log] Error 1
make[4]: Leaving directory '/home/hpe/asn1c/tests/tests-asn1c-compiler'
make[3]: *** [Makefile:656: check-TESTS] Error 2
make[3]: Leaving directory '/home/hpe/asn1c/tests/tests-asn1c-compiler'
make[2]: *** [Makefile:729: check-am] Error 2
make[2]: Leaving directory '/home/hpe/asn1c/tests/tests-asn1c-compiler'
make[1]: *** [Makefile:388: check-recursive] Error 1
make[1]: Leaving directory '/home/hpe/asn1c/tests'
make: *** [Makefile:494: check-recursive] Error 1
```

[justTest.log](justTest%201.log)

[APER.tar](APER%201.tar)

[test-suite.log](test-suite.log)

[regenerateASN1C.patch](regenerateASN1C%201.patch)

- I’m still encountering three differences in my tests. I’ve attached all relevant logs and files for your reference. (justTest.log and APER.tar)
- Do I need to apply your patch and then rebuild & reinstall the Nokia ASN1C? (regenerateASN1C.patch)
- I encountered issues installing Nokia ASN1C successfully. (test-suite.log)
    - Which branch should I select?
- I used my originally installed Nokia ASN1C and ran `./justTest.sh` after applying `newWA.tar`, but I’m still seeing three differences. (justTest.log)
- I’d like to clarify the setup (as the files have been updated multiple times, and it’s a bit confusing): If I prepare an empty directory and extract all the tar files you provided in the order you sent them, do I just need to run `./justTest.sh`?
- I’d like to confirm how the script operates: `justTest.sh` uses the currently installed `asn1c` (in my case, Nokia ASN1C is the default, while `mouse` requires a specified path) to compile the ASN.1 files, placing the output in the `APER` directory, and then compares it with **NokiaAPER** provided in your tar file, is that correct?
    - Based on this setup, I’m curious why this process would result in any differences. Unless I replace the script to use `mouse ASN1C`, it seems like the script's current operation wouldn’t be consistent with my understanding (i.e., it should yield no differences).

---

## Reply from Nokia

Hello

My answers in red.

- I’m still encountering three differences in my tests. I’ve attached all relevant logs and files for your reference. (justTest.log and APER.tar)

That is normal, it should  have the same behavior as the Mouse version. The question is “are the Nokia generated aper files (with the correction) in the APER directory the same as the ones generated by the Mouse version ?”. If they are identical then the correction is valid.

- Do I need to apply your patch and then rebuild & reinstall the Nokia ASN1C? (regenerateASN1C.patch)

Yes.

- I encountered issues installing Nokia ASN1C successfully. (test-suite.log)
    - Which branch should I select?

For this test you can use your current branch, the issues during the installation is due to the test step, wrong reference files (it is in the TODO list).

But the asn1c binary should have been generated and should be valid, so just have to do a make install or a sudo make install if you want to make it globally visible.

- I used my originally installed Nokia ASN1C and ran `./justTest.sh` after applying `newWA.tar`, but I’m still seeing three differences. (justTest.log)

That is normal, if you look at the justTest.sh the new version (with the correction ) of SearchSpace.c is copied from the Src directory after the asn1c generation, so it differs from the original version. As above to see if it is correct, the test is to compare the APER generated files to the Mouse version generated ones. If they are identical it means that the correction is valid.

- I’d like to clarify the setup (as the files have been updated multiple times, and it’s a bit confusing): If I prepare an empty directory and extract all the tar files you provided in the order you sent them, do I just need to run `./justTest.sh`?

As the justTest script copy the corrected version it should not be necessary.

- I’d like to confirm how the script operates: `justTest.sh` uses the currently installed `asn1c` (in my case, Nokia ASN1C is the default, while `mouse` requires a specified path) to compile the ASN.1 files, placing the output in the `APER` directory, and then compares it with **NokiaAPER** provided in your tar file, is that correct?

Yes but as NokiaAPER contains wrong encoding for three files, the right result should be three differences.

- Based on this setup, I’m curious why this process would result in any differences. Unless I replace the script to use `mouse ASN1C`, it seems like the script's current operation wouldn’t be consistent with my understanding (i.e., it should yield no differences).

The issue is probably due to a void SEQUENCE with extension:

```jsx
VoidSequence ::= SEQUENCE {

…

}
```

The Nokia version did not encode the extension bit, so there is a missing bit in the encoding.

Best regards,

Erick Bizouarn

---

## Action items

Based on the reply from Nokia, here are the action items:

1. Apply the patch (regenerateASN1C.patch) and rebuild & reinstall Nokia ASN1C
2. After rebuilding, run 'make install' or 'sudo make install' to make the asn1c binary globally visible
3. Run './justTest.sh' and compare the APER generated files with the Mouse version generated ones
4. Verify if the three differences in the test results are due to the void SEQUENCE with extension issue mentioned by Nokia
5. If the APER files generated by Nokia ASN1C (with the correction) are identical to those generated by the Mouse version, confirm that the correction is valid

These steps should help address the current issues and verify the corrections made to the Nokia ASN1C implementation.

---

## My reply context

Hi,

Thank you for the explanation; it has helped clarify things further.

After apply patch and re-extracting all files and running [justTest.sh](http://justtest.sh/), I observed three diffs, consistent with what you described. Additionally, I replaced justTest with mouse asn1c, and as expected, I still see the same three diffs, with behavior matching your description.

At the end of your message, you mentioned a “miss bit” issue, so I wanted to confirm if this is the main problem we are currently addressing. Are you currently working on a solution, or is there already a fix available (perhaps via the patch file you previously shared, which seems to address the ASN1C parser)?

If this resolves the issue, I will proceed by recompiling and replacing the files in the OSC project folder to conduct further testing.

Thank you for your guidance.

Best regards,

Ming

---

## Nokia reply

<aside>
💡

</aside>

```bash
Hello
We will integrate this correction with other corrections in a new version later this week. I will send you a message when it will be available.
Best regards,
Erick Bizouarn

Hello
When doing some tests with other ASN.1 files, we encountered another issue so delaying the release of a new version.
Sorry for the delay.
Best regards,
Erick Bizouarn
```

<aside>
💡

Hello

Thank you for the update. I completely understand that unexpected issues can arise during testing.

Would it be possible to share more details about the issue encountered with the ASN.1 files?

I’d also appreciate it if you could let me know the current progress and provide an estimated timeline for resolving the issue and releasing the new version.

Please feel free to let me know if there’s anything I can do to support.

Looking forward to your reply.

</aside>

```bash
Hello
Description of the issue with NGAP:items
In the spec NGAP they are using the CONTAINING constraint (used only with BIT STRING and OCTET STRING) without defining the encoding/decoding scheme.
like in the following type definition:

PDUSessionResourceModifyItemModCfm ::= SEQUENCE {

              pDUSessionID                                                                                                    PDUSessionID,

              pDUSessionResourceModifyConfirmTransfer                            OCTET STRING (CONTAINING PDUSessionResourceModifyConfirmTransfer),

              iE-Extensions                 ProtocolExtensionContainer { {PDUSessionResourceModifyItemModCfm-ExtIEs} }  OPTIONAL,

              ...

}
and it works well.
But when it is used into class instance:
BroadcastSessionSetupRequestIEs NGAP-PROTOCOL-IES ::= {

              { ID id-MBS-SessionID                                                                                      CRITICALITY reject       TYPE MBS-SessionID                                                                                                                    PRESENCE mandatory              }|

              { ID id-S-NSSAI                                                                                                                 CRITICALITY reject       TYPE S-NSSAI                                                                                                                                               PRESENCE mandatory        }|

              { ID id-MBS-ServiceArea                                                                                                CRITICALITY reject       TYPE MBS-ServiceArea                                                                                                                              PRESENCE mandatory        }|

              { ID id-MBSSessionSetupRequestTransfer                     CRITICALITY reject       TYPE OCTET STRING (CONTAINING MBSSessionSetupOrModRequestTransfer)                   PRESENCE mandatory        },

              ...

}
The generated code for PER constraint for the member MBSSessionSetupRequestTransfer is missing and there is an error at compile time during the link step.
Best regards,
Erick Bizouarn
```

---

```jsx
Dear Erick,
Thank you for explaining the issue with the CONTAINING constraint in NGAP.
May I ask if there is a deadline for resolving this? If there’s anything I can do to assist or help expedite the process, please let me know.
Best regards,
```

```markdown
Dear Erick,
I hope this email finds you well.
I wanted to follow up on the status of the ASN.1 compiler updates. Has there been any progress regarding the issues with the NGAP specifications and the resolution of the CONTAINING constraint problem? Additionally, could you please provide an estimated timeline for the release of the updated version?
Please let me know if there’s anything further I can assist with to help expedite the process.
Looking forward to your response.
Best regards,
Ming
```

```markdown
Dear Erick,  

Happy New Year! I hope you had a wonderful start to 2025.  

I wanted to check in on the status of the ASN.1 compiler updates. Specifically, has there been any progress in addressing the issues related to the NGAP specifications and resolving the CONTAINING constraint problem? It would also be greatly appreciated if you could provide an estimated timeline for the release of the updated version.  

Please let me know if there’s anything I can do to assist in moving things along.  

Looking forward to hearing from you.  

Best regards,  
Ming  
```

![image.png](image%2091.png)

## Starus trace

| 11/13 | ✅ | Inquired about progress and received a reply that there would be an update that week |
| --- | --- | --- |
| 11/20 | ✅ | Inquired about progress again and asked why there was no update |
| 11/20 | ✅ | Get the delay notify |
| 11/26 | ⏳ | the asn1c issue with NGAP (MBSSessionSetupRequestTransfer) |
| 12/3 | ⏳ | Ask for deadline |
| 12/17 | ⏳ | check the status of ASN.1 complier. |
| 1/2 | ⏳ | check the status of ASN.1 complier. |
| 1/7 | ⏳ | check the status of ASN.1 complier. Erick on sick leave.. |
| 1/15 | ⏳ | check the status of ASN.1 complier. (add mailto:abdulwahid.w@nokia.com) |

[SIB1 ASN.1 Code Modification and Repository Commit Clarification](SIB1%20ASN%201%20Code%20Modification%20and%20Repository%20Commit%20151100983143803b8c19dd90a19b6a3f.md) 

[OSC F1AP ASN.1 file](OSC%20F1AP%20ASN%201%20file%201211009831438070bb80c050fcf47cdf.md) 

[Tracking OAI 5G nFAPI Uplink Issues with Robert](Tracking%20OAI%205G%20nFAPI%20Uplink%20Issues%20with%20Robert%20178100983143807b9552db131c8a9dfc.md)