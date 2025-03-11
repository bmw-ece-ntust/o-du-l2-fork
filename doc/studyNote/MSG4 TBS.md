# MSG4 TBS

Start Date: 2024/10/10
Summary: MSG4 TBS involves calculating the number of resource blocks and transport block size for a communication system.
Status: Reject
Assign: Ming 咚咚 [銘鴻]

## How to **CalcNumPrb**

```jsx
   pdsch->pdschFreqAlloc.numPrb = schCalcNumPrb(tbSize, mcs, pdschNumSymbols);
```

[TODO] I will check function work in detail

[Compute TBS and PRB](Compute%20TBS%20and%20PRB%20121100983143819aa2b2c12155d157f8.md) 

## How to compute TBS

```c
    dlsch_pdu->TBS = nr_compute_tbs(dlsch_pdu->qamModOrder,
                                    R,
                                    dlsch_pdu->number_rbs,
                                    dlsch_pdu->number_symbols,
                                    nb_re_dmrs * get_num_dmrs(dlsch_pdu->dlDmrsSymbPos),
                                    nb_rb_oh,
                                    0,
                                    1);
```

[TODO] I will check function work in detail

[Compute TBS and PRB](Compute%20TBS%20and%20PRB%20121100983143819aa2b2c12155d157f8.md) 

## Why we need 116 Byte in MSG4

I know and I will write it down when i have time…

[TODO]