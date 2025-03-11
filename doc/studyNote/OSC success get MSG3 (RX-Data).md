# OSC success get MSG3 (RX-Data)

Start Date: 2024/09/04
Summary: Successfully resolved the issue of OSC DU High receiving MSG3 from OAI Layer 1, enabling proper handling of RX data and CRC indications.
Status: Done
Assign: Ming 咚咚 [銘鴻]

## OSC get RACH indication

|  | **sfn** | slot |
| --- | --- | --- |
| UE send | 183 | 19 |
| **VNF current Timing Info** | 184 | 8 |
| **VNF DL TTI Timing Info** | 184 | 10 |

![image.png](image%2061.png)

## current crush issues is page message

- OSC log will stop here

![image.png](image%2062.png)

![mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/lwr_mac_fsm.c](image%2063.png)

mwnl-odu-at-oai-based-on-scf/l2/src/5gnrmac/lwr_mac_fsm.c

## After remove page message relate source code

OSC DU High could successfully get MSG3 from OAI Layer 1 → RX_data

<aside>
⛔

It will still in for-loop

</aside>

![image.png](image%2064.png)

<aside>
📌

Problem define

- The problem is OSC don’t handle this case → **LC ID = 52 (MAC_LCID_CCCH_48BIT)**
</aside>

![image.png](image%2065.png)

# MSG3: RX Data

```
[NTUST] header.message_id:133[nr_rx_data] value->pdu: 
34 1f 56 56 c9 83 a6 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 00 
[unpackRxData] rxDataPdu: 
34 1f 56 56 c9 83 a6 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 00 
 
```

because case **`MAC_LCID_CCCH_48BIT`:** 52(`0x32`) are not handle in `OSC`, so next step, I should trace `OAI` souse code. 

# From `OAI` source code comment

```c
//  For both UL-SCH except:
//   - UL-SCH: fixed-size MAC CE(known by LCID)
//   - UL-SCH: padding
//   - UL-SCH: MSG3 48-bits
//  |0|1|2|3|4|5|6|7|  bit-wise
//  |R|F|   LCID    |
//  |       L       |
//  |0|1|2|3|4|5|6|7|  bit-wise
//  |R|F|   LCID    |
//  |       L       |
//  |       L       |
//
//  For:
//   - UL-SCH: fixed-size MAC CE(known by LCID)
//   - UL-SCH: padding, for single/multiple 1-oct padding CE(s)
//   - UL-SCH: MSG3 48-bits
//  |0|1|2|3|4|5|6|7|  bit-wise
//  |R|R|   LCID    |
//
//  LCID: The Logical Channel ID field identifies the logical channel instance of the corresponding MAC SDU or the type of the corresponding MAC CE or padding as described in Tables 6.2.1-1 and 6.2.1-2 for the DL-SCH and UL-SCH respectively. There is one LCID field per MAC subheader. The LCID field size is 6 bits;
//  L: The Length field indicates the length of the corresponding MAC SDU or variable-sized MAC CE in bytes. There is one L field per MAC subheader except for subheaders corresponding to fixed-sized MAC CEs and padding. The size of the L field is indicated by the F field;
//  F: length of L is 0:8 or 1:16 bits wide
//  R: Reserved bit, set to zero.
```

# In `OAI` case,

`UL_SCH_LCID_CCCH (0x32)` and `UL_SCH_LCID_CCCH1 (0x0)` are in same case!

```jsx
      case UL_SCH_LCID_CCCH:
      case UL_SCH_LCID_CCCH1:
        // fixed length
        mac_subheader_len = 1;

        if ( rx_lcid == UL_SCH_LCID_CCCH1 ) {
          // RRCResumeRequest1 message includes the full I-RNTI and has a size of 8 bytes
          mac_len = 8;

          // Check if it is a valid CCCH1 message, we get all 00's messages very often
          if (pdu_len < mac_subheader_len + mac_len) {
              LOG_E(NR_MAC, "pdu_len %d is invalid (prior to cast of size %d)\n",
                    pdu_len, mac_subheader_len + mac_len);
              return 0;
        }
          int i = 0;
          for(i=0; i<(mac_subheader_len+mac_len); i++) {
            if(pduP[i] != 0) {
              break;
            }
          }
          if (i == (mac_subheader_len+mac_len)) {
            LOG_D(NR_MAC, "%s() Invalid CCCH1 message!, pdu_len: %d\n", __func__, pdu_len);
            done = 1;
            break;
          }
        } else {
          // fixed length of 6 bytes
          mac_len = 6;
        }

        LOG_D(MAC, "[RAPROC] Received SDU for CCCH length %d for UE %04x\n", mac_len, UE->rnti);

        prepare_initial_ul_rrc_message(RC.nrmac[module_idP], UE);
        mac_rlc_data_ind(module_idP,
                         UE->rnti,
                         module_idP,
                         frameP,
                         ENB_FLAG_YES,
                         MBMS_FLAG_NO,
                         0,
                         (char *) (pduP + mac_subheader_len),
                         mac_len,
                         1,
                         NULL);
        break;
```

<aside>
💡

SUCCESS! OSC DU High could get RX_data and CRC

</aside>

After change `OSC` handle case, it start  **RRC Setup Request!!**

- and also could get CRC and RX_data message now!
    - **header.message_id:134 (NFAPI_NR_PHY_MSG_TYPE_RX_DATA_INDICATION)**
    - **header.message_id:133 (NFAPI_NR_PHY_MSG_TYPE_CRC_INDICATION)**

![image.png](image%2066.png)

![image.png](image%2067.png)

![image.png](image%2068.png)

![image.png](image%2069.png)

![image.png](image%2070.png)

```
 九  05 16:19:53 unpackRxData...
 九  05 16:19:53 [unpackRxData] rxDataPdu: 34 15 1f 2e 5b c3 e6 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 3f 00 
 九  05 16:19:53 
 九  05 16:19:53 INFO   -->  MAC : PDU Length = 28
 九  05 16:19:53 INFO   -->  MAC : UE ID = 1
 九  05 16:19:53 INFO   -->  MAC : LC ID = 52, pduLen = 28
 九  05 16:19:53 INFO   -->  MAC : LC ID = 63, pduLen = 21S
 九  05 16:19:53 unpackRxData Finish
```

52 and 63

```bash
#define MAC_LCID_CCCH_48BIT        52
#define MAC_LCID_PADDING           63
```

Do nothing

![image.png](image%2071.png)