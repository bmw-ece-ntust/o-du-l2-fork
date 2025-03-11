# How to design DCI and SIB1

Start Date: 2024/05/22
Summary: Designing DCI and SIB1 for efficient transmission and decoding in network communication.
Status: Done
Assign: Ming 咚咚 [銘鴻]

# What is MIB

[Information about Master Information Block (MIB)](https://www.notion.so/Information-about-Master-Information-Block-MIB-12110098314381a1b249d754acba2094?pvs=21) 

# What is CORESET0, SS, DCI, SIB1

[Information about **CORESET** ](https://www.notion.so/Information-about-CORESET-12110098314381ff98a6cb9b8698f6ba?pvs=21) 

[Information about DCI](https://www.notion.so/Information-about-DCI-12110098314381398780dcb31c5e48c6?pvs=21) 

SIB1 is carried by a PDSCH like any other user data 

Then, why we need a special algorithm for transmitting and decoding a PDSCH carrying SIB1

| CORESET | network defines a specific physical resources for transmitting DCI  |
| --- | --- |
| Search Space (SS) | network defines a specific set of candidate physical resources that UE has to monitor (Search Space) to find scheduling information |

# MIB → CORESET0

| pdcch-ConfigSIB1- ControlResourceSetZero | pdcch-ConfigSIB1- searchSpaceZero |
| --- | --- |
| Table 13-1 ~ 13-10 | Table 13-11 ~ 13-14 |

![Untitled](Untitled%2090.png)

# Status

[Mapping OSC and OAI MIB SIB configuration](Mapping%20OSC%20and%20OAI%20MIB%20SIB%20configuration%201211009831438153ab27d58fee15a2d4.md) 

[https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=Rut-183sEZWMflkd3cW0&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download](https://viewer.diagrams.net/?border=0&tags={}&highlight=0000ff&edit=_blank&layers=1&nav=1&page-id=Rut-183sEZWMflkd3cW0&title=nFAPI.drawio#Uhttps://drive.google.com/uc?id=1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts&export=download)