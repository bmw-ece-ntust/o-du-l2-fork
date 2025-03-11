# HARQ compare with monolithic

Summary: Investigate the encoding and decoding of HARQ acknowledgments in the context of comparing HARQ with monolithic systems.
Status: Done
Tags: Robert Task

```
1712244952.039800 [NR_MAC]   UE 7a79 expected HARQ pid 10 feedback at  264. 7, but is at  274. 7 instead (HARQ feedback is in the past)
1712244953.123094 [NR_MAC]   UE 7a79 expected HARQ pid 6 feedback at  304. 7, but is at  314. 7 instead (HARQ feedback is in the past)
1712244954.216258 [NR_MAC]   UE 7a79 expected HARQ pid 12 feedback at  344. 7, but is at  354. 7 instead (HARQ feedback is in the past)

```

this is when there is no load. You should check whether we encode and decode the HARQ ack/nack properly. That means:

- check in L1 when we have PUCCH 0 for acknack: see patch below
- check what we pack in the UCI.indication
- check what we unpack in the UCI.indication message
- compare if all matches
- Check when the scheduler requests ack, and check if that is the same in the L1 (you can check with the PUCCH0 function, that should work, you can compare with monolithic)

same for UL in second step