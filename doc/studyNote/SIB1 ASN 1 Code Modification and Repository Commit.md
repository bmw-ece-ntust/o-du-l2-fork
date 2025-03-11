# SIB1 ASN.1 Code Modification and Repository Commit Clarification

Start Date: 2024/12/03
Summary: SIB1 ASN.1 code modifications were made, along with clarifications on repository commits and responses to inquiries from lab partners regarding the issue fix.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: mail
Finish Date: 2024/12/06
SUM: 🗓️ Days Spent to Complete: 3

<aside>
💡

This note tracks my responses to emails and Slack messages from our lab partners (OAI, OSC, VIAVI, etc.).

</aside>

SIB1 ASN.1 Code Modification and Repository Commit Clarification

Original context

```jsx
Ankit Barve
  晚上 9:07
Hi Ming, Priyanka has few questions regarding ASN.1 issue fix for SIB1, could you please respond to her?? (已編輯) 

Ming_NTUST_銘鴻
  凌晨 1:17
oh okay, sorry for the delay in replying due to delays. I have contacted Priyanka and provided a detailed reply. If she has any more advanced questions, I will be happy to assist.

Ankit Barve
  凌晨 2:03
Thanks a lot Ming.
```

```jsx
pborla
  下午 5:05
Hi Ming

Ming_NTUST_銘鴻
  下午 5:11
Hi

pborla
  下午 5:18
I need a little help. I'd want to know how you fixed the SIB1 problem. There are several commits accessible under Match SIB1 in the NTUST-OSC-DU-nFAPI repository, which I was looking over.  So can you please tell me which commit has the exact SIB1 related changes.

Ming_NTUST_銘鴻
  凌晨 1:14
Yes, you have caught the point.
1:14
all change commits are included in the same branch. If you want to check, you can check the commits with [SIB1] related prefix near this commit. I have clearly distinguished each detailed change.
The most important thing is this change. You can browse it before and after this commit. （a1c5f5fe6cf494887b86b79fe7b59d75eb28f34）
https://github.com/dong881/NTUST-OSC-DU-nFAPI/commit/9a1c5f5fe6cf494887b86b79fe7b59d75eb28f34

pborla
  凌晨 1:44
Could you tell me how you made the changes to the ASN file? Have you made any modifications to the asn1 file or have you made them directly in the codec folder?

Ming_NTUST_銘鴻
  下午 1:17
Yes, my process is to directly use OAI's ASN1.C definition file and use mouse asn1c to recompile code_utlis RRC. Then, because the variable names do not match the original OSC declaration, I replaced them one by one with the variable names declared by OSC according to the compiler failed log. , many parts have different declaration order of variable names, so you can see which one should be replaced. I know this description seems too general. If you still can't understand clearly, I will find corresponding examples between today and tomorrow. The commit is for your reference, but all changes are in the branch, so the answers can be found in the commit inside.
```

**Summary Highlights:**

- Ankit Barve requested assistance from me regarding Priyanka's questions on the ASN.1 issue fix for SIB1.
- I responded to Priyanka with a detailed explanation and offered further assistance if needed.
- Pborla inquired about the specific commit related to the SIB1 issue in the NTUST-OSC-DU-nFAPI repository.
- I clarified that all changes are included in the same branch, with commits marked by the [SIB1] prefix.
- Pborla asked for details on changes made to the ASN file or directly in the codec folder.
- I explained my process of using OAI's ASN1.C definition file, recompiling with asn1c, and aligning variable names with OSC declarations.

**Next Step Action Items:**

- [x]  Provide specific examples to Pborla regarding the changes made in the ASN file.
- [x]  Ensure all changes and explanations are clear and accessible in the repository branch.

Regarding the changes made in the ASN file.

```jsx
commit 5a2cfb425bac8b517f6a2df3cba4d4ac9f450034
Author: dong881 <joe888joejoe@gmail.com>
Date:   Fri Jul 5 16:32:58 2024 +0800

    [Match SIB1] Delete the old source code and revise it with a new approach using macros.

commit 061faf1f6afdf300d8838858dcef6a3b469b91ab
Author: dong881 <joe888joejoe@gmail.com>
Date:   Fri Jul 5 16:29:26 2024 +0800

    [Match SIB1] Streamline C code macro

commit bedda0d63c831a51d0e688725139dcab25135617
Author: dong881 <joe888joejoe@gmail.com>
Date:   Fri Jul 5 16:25:34 2024 +0800

    [Match SIB1] Fix the issue where the PLMN in SIB1 cannot be decoded.(E2AP and F1AP change name)

commit 3f63ee8f7586761ba31b261715ad639d0566d930
Author: dong881 <joe888joejoe@gmail.com>
Date:   Tue Jul 2 17:31:00 2024 +0800

    [Match SIB1] Because of the version update, a substantial modification of the original makefile and OSC source code's variable names is required to ensure successful compilation.

commit 9a1c5f5fe6cf494887b86b79fe7b59d75eb28f34
Author: dong881 <joe888joejoe@gmail.com>
Date:   Fri Jun 28 17:34:48 2024 +0800

    [Match SIB1] Upgrade ASN.1 RRC version 15_3->17.3.0 (and change Folder name)

commit 45539ae5324a7aff42994582e26fe6da5568723f
Author: dong881 <joe888joejoe@gmail.com>
Date:   Fri Jun 28 17:11:28 2024 +0800

    [Match SIB1] Add searchSpaceType (based on the comparison with OAI SIB1)
```

I believe the most important changes are limited to these specific commits: from restoring the search space-related features that were originally commented out by OSC, to recompiling asn1c, and addressing the error caused by mismatched variable names.

As for the other [Match SIB1] changes, most of them involve parameter adjustments made to align OSC DU High with OAI Layer1.

Aside from the series of consecutive commits I’ve highlighted above, there is one more issue worth mentioning. After fixing the errors caused by mismatched variable names, I encountered another issue where PLMN could not be properly encoded/decoded. To address this, I revised the encoding method for OSC PLMN.

Please refer to commit acf6e35 for details.

```
commit acf6e359f8b3a1a2552492c1e0a23733e17beb1a
Author: dong881 <joe888joejoe@gmail.com>
Date:   Fri Jul 5 16:22:01 2024 +0800

    [Match SIB1] Fix issue with PLMN decoding in SIB1
```

Regarding fixing the errors caused by mismatched variable names, I believe it would be easier to understand with an example of the actual changes I made:
in commit `3f63ee8f7586761ba31b261715ad639d0566d930`:

```diff
switch(longDrxCycleLength)
{
  case 10:
-   return DRX_ConfigRrc__drx_LongCycleStartOffset_PR_ms10;
+   return DRX_Config__drx_LongCycleStartOffset_PR_ms10;
  case 20:
-   return DRX_ConfigRrc__drx_LongCycleStartOffset_PR_ms20;
+   return DRX_Config__drx_LongCycleStartOffset_PR_ms20;
}
```

→ [List of SIB1 ASN.1 Code Modifications](List%20of%20SIB1%20ASN%201%20Code%20Modifications%2015710098314380c485bacb030c3c5444.md)