# Check rx_nr_prach all of input value different

Start Date: 2024/06/06
Summary: Check the input values for rx_nr_prach to ensure they are all different.
Status: Done
Assign: Ming 咚咚 [銘鴻]

```c
  LOG_I(PHY,"nb_rx:%d\n",nb_rx);
  LOG_I(PHY,"rootSequenceIndex:%d\n",rootSequenceIndex);
  LOG_I(PHY,"numrootSequenceIndex:%d\n",numrootSequenceIndex);
  LOG_I(PHY,"NCS:%d\n",NCS);
  LOG_I(PHY,"prach_sequence_length:%d\n",prach_sequence_length);
  LOG_I(PHY,"msg1_frequencystart:%d\n",msg1_frequencystart);
  LOG_I(PHY,"restricted_set:%d\n",restricted_set);
```

| **N_ZC** | 139 |
| --- | --- |
| **NCS** | 34 |
| **NCS2** | 62 |