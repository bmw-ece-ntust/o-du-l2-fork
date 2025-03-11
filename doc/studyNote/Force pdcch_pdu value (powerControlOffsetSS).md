# Force pdcch_pdu value (powerControlOffsetSS)

Start Date: 2024/06/03
Summary: Force the value of powerControlOffsetSS in the pdcch_pdu configuration.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: OSC Integration problem

```c
  value->dci_pdu[0].powerControlOffsetSS= 1;
```

[PDCCH PDU](PDCCH%20PDU%201211009831438174be81d186be229c06.md)