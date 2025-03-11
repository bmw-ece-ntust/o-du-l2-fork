# Error decoding PBCH!

Start Date: 2024/06/04
Summary: Error handling and debugging of PBCH decoding processes in a research project related to wireless communication.
Status: Done
Assign: Ming 咚咚 [銘鴻]

# Solution

```c
#define SLOT_DURATION 1400  // in microseconds
void handle_nr_slot_ind(uint16_t sfn, uint16_t slot)
{
    /* uses a usleep to wait for approximately the same time period (300 us) */
    static struct timespec last_execution = {0};
    struct timespec current_execution;
    clock_gettime(CLOCK_REALTIME, &current_execution);
    // Calculate elapsed time since last execution
    long elapsed_time = (current_execution.tv_sec - last_execution.tv_sec) * 1000000; // Convert seconds to microseconds
    elapsed_time += (current_execution.tv_nsec - last_execution.tv_nsec) / 1000; // Convert nanoseconds to microseconds
    if (elapsed_time < SLOT_DURATION) 
        usleep(SLOT_DURATION - elapsed_time);
    // Update last_execution time
    last_execution = current_execution;
```

Change SLOT_DURATION from 300 to 1400 OAI will get every 2 frame `DL_TTI` and `TX_Data`

<aside>
💡 Maybe PHY generate timing PBCH bits need more info we don’t give it.

</aside>

![Untitled](Untitled%2063.png)

```c
int nr_generate_pbch(nfapi_nr_dl_tti_ssb_pdu *ssb_pdu,
                     uint8_t *interleaver,
                     c16_t *txdataF,
                     int16_t amp,
                     uint8_t ssb_start_symbol,
                     uint8_t n_hf,
                     int sfn,
                     nfapi_nr_config_request_scf_t *config,
                     NR_DL_FRAME_PARMS *frame_parms) {
  int k,l,m;
  //int16_t a;
  int16_t mod_pbch_e[NR_POLAR_PBCH_E];
  uint8_t idx=0;
  uint16_t M;
  uint8_t nushift;
  uint32_t unscrambling_mask;
  LOG_D(PHY, "PBCH generation started\n");
  ///Payload generation
  NR_gNB_PBCH m_pbch;
  NR_gNB_PBCH *pbch = &m_pbch;
  memset((void *)pbch, 0, sizeof(NR_gNB_PBCH));
  pbch->pbch_a=0;
  uint8_t ssb_index = ssb_pdu->ssb_pdu_rel15.SsbBlockIndex;
  uint8_t *pbch_pdu = (uint8_t*)&ssb_pdu->ssb_pdu_rel15.bchPayload;
  LOG_I(PHY,"[nr_generate_pbch] pbch_pdu:%lx\n",*pbch_pdu);
  uint8_t Lmax = frame_parms->Lmax;
  for (int i=0; i<NR_PBCH_PDU_BITS; i++)
    pbch->pbch_a |= ((pbch_pdu[i>>3]>>(7-(i&7)))&1)<<i;
  LOG_I(PHY,"[nr_generate_pbch] pbch->pbch_a:%lx\n",pbch->pbch_a);
```

## Error  in decode MIB BCH payload

```c
 六  04 22:57:00 [32m[NR_RRC]   SIB1 decoded
 六  04 22:57:00 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
 六  04 22:57:00 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
 六  04 22:57:00 [0m[PHY]    ------  Decode MIB: frame.slot 46.0 ------  
 六  04 22:57:00 [0m[PHY]   result[0]:0
 六  04 22:57:00 [0m[PHY]   result[1]:0
 六  04 22:57:00 [0m[PHY]   result[2]:0
 六  04 22:57:00 [0m[PHY]   xtra_byte:0
 六  04 22:57:00 [0m[1;31m[PHY]   [UE 0] frame 46, nr_slot_rx 0, Error decoding PBCH!
```

```c
juin 04 16:56:00 [32m[NR_RRC]   SIB1 decoded
juin 04 16:56:00 [0m[NR_MAC]   NR band duplex spacing is 0 KHz (nr_bandtable[40].band = 78)
juin 04 16:56:00 [0m[NR_MAC]   NR band 78, duplex mode TDD, duplex spacing = 0 KHz
juin 04 16:56:00 [0m[PHY]    ------  Decode MIB: frame.slot 106.0 ------  
juin 04 16:56:00 [0m[PHY]   result[0]:d
juin 04 16:56:00 [0m[PHY]   result[1]:6
juin 04 16:56:00 [0m[PHY]   result[2]:6
juin 04 16:56:00 [0m[PHY]   xtra_byte:5
```

## error in **nr_rx_pbch**

## OSC

```
 六  04 21:55:21 [0mextract_rbs (nushift 0): rx_offset=8072, symbol 1
 六  04 21:55:21 rxF.r [0]= 0 rxF.i [0]= 0
 六  04 21:55:21 pbch extract rxF  0 0 addr 0x7e7304635880
 六  04 21:55:21 rxF.r [1]= 0 rxF.i [1]= 0
 六  04 21:55:21 pbch extract rxF  0 0 addr 0x7e7304635884
 六  04 21:55:21 rxF.r [2]= 0 rxF.i [2]= 0
 六  04 21:55:21 pbch extract rxF  0 0 addr 0x7e7304635888
 六  04 21:55:21 rxF.r [3]= 0 rxF.i [3]= 0
 六  04 21:55:21 pbch extract rxF  0 0 addr 0x7e730463588c
 六  04 21:55:21 rxF.r [4]= 0 rxF.i [4]= 0
 六  04 21:55:21 pbch extract rxF  0 0 addr 0x7e7304635890
 六  04 21:55:21 rxF.r [5]= 0 rxF.i [5]= 0
 六  04 21:55:21 pbch extract rxF  0 0 addr 0x7e7304635894
 六  04 21:55:21 rxF.r [6]= 0 rxF.i [6]= 0
 六  04 21:55:21 pbch extract rxF  0 0 addr 0x7e7304635898
 六  04 21:55:21 rxF.r [7]= 0 rxF.i [7]= 0
 六  04 21:55:21 pbch extract rxF  0 0 addr 0x7e730463589c
 六  04 21:55:21 rxF ext[0] = (0,0) rxF [1929]= (0,0)
 六  04 21:55:21 rxF ext[1] = (0,0) rxF [1930]= (0,0)
 六  04 21:55:21 rxF ext[2] = (0,0) rxF [1931]= (0,0)
 六  04 21:55:21 rxF ext[3] = (0,0) rxF [1933]= (0,0)
 六  04 21:55:21 rxF ext[4] = (0,0) rxF [1934]= (0,0)
 六  04 21:55:21 rxF ext[5] = (0,0) rxF [1935]= (0,0)
 六  04 21:55:21 rxF ext[6] = (0,0) rxF [1937]= (0,0)
 六  04 21:55:21 rxF ext[7] = (0,0) rxF [1938]= (0,0)
 六  04 21:55:21 rxF ext[8] = (0,0) rxF [1939]= (0,0)
 六  04 21:55:21 rxF ext[9] = (0,0) rxF [1941]= (0,0)
```

## OAI

```
juin 04 15:55:33 [0mextract_rbs (nushift 0): rx_offset=8072, symbol 1
juin 04 15:55:33 rxF.r [0]= 201 rxF.i [0]= -313
juin 04 15:55:33 pbch extract rxF  201 -313 addr 0x7b9cb45068a0
juin 04 15:55:33 rxF.r [1]= 218 rxF.i [1]= -299
juin 04 15:55:33 pbch extract rxF  218 -299 addr 0x7b9cb45068a4
juin 04 15:55:33 rxF.r [2]= 231 rxF.i [2]= -282
juin 04 15:55:33 pbch extract rxF  231 -282 addr 0x7b9cb45068a8
juin 04 15:55:33 rxF.r [3]= -283 rxF.i [3]= 238
juin 04 15:55:33 pbch extract rxF  -283 238 addr 0x7b9cb45068ac
juin 04 15:55:33 rxF.r [4]= 238 rxF.i [4]= -281
juin 04 15:55:33 pbch extract rxF  238 -281 addr 0x7b9cb45068b0
juin 04 15:55:33 rxF.r [5]= -275 rxF.i [5]= 241
juin 04 15:55:33 pbch extract rxF  -275 241 addr 0x7b9cb45068b4
juin 04 15:55:33 rxF.r [6]= -271 rxF.i [6]= 241
juin 04 15:55:33 pbch extract rxF  -271 241 addr 0x7b9cb45068b8
juin 04 15:55:33 rxF.r [7]= 247 rxF.i [7]= 233
juin 04 15:55:33 pbch extract rxF  247 233 addr 0x7b9cb45068bc
juin 04 15:55:33 rxF ext[0] = (332,-153) rxF [1929]= (332,-153)
juin 04 15:55:33 rxF ext[1] = (-152,-337) rxF [1930]= (-152,-337)
juin 04 15:55:33 rxF ext[2] = (331,-155) rxF [1931]= (331,-155)
juin 04 15:55:33 rxF ext[3] = (-154,-335) rxF [1933]= (-154,-335)
juin 04 15:55:33 rxF ext[4] = (-155,-337) rxF [1934]= (-155,-337)
juin 04 15:55:33 rxF ext[5] = (329,-159) rxF [1935]= (329,-159)
juin 04 15:55:33 rxF ext[6] = (-160,-334) rxF [1937]= (-160,-334)
```