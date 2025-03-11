# Check Trigger_scheduler and UE spec releate

Start Date: 2024/04/18
Summary: Review and implement the Trigger_scheduler and UE specifications related to scheduling for efficient data transmission.
Status: Done
Assign: 陳奕全

![Untitled](Untitled%20112.png)

![Untitled](Untitled%20113.png)

```c

// Pass every two frame
    if (sched_pdsch->rbSize <= 0)
      continue;
      
      
```

<aside>
👀 oai_nfapi_tx_data_req will be trigger every two SFN and contain SIB1.

</aside>