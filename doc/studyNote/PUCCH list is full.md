# PUCCH list is full

Summary: Investigating an issue related to the PUCCH list being full in the NR transport layer implementation.
Status: Done

ok I found a problem with it, though:

```
Assertion (found) failed!
In nr_fill_pucch() /home/richie/w/nfapi-fixes/openair1/PHY/NR_TRANSPORT/pucch_rx.c:84
PUCCH list is full

```

it should not be full but freed, maybe there is something that is not called or so

[5:11](https://openairinterface.slack.com/archives/D06MS6VMKQS/p1712589089549309)

maybe have a look

However, the problem is that `init_nr_transport`() allocated only one PUCCH structure. see patch:

[Allow to use multiple PUCCH at once (c971677d) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/c971677dce45e585bc94d0671598425ff1b67a54)