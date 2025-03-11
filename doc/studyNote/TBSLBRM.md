# TBSLBRM

Start Date: 2024/10/09
Summary: The project involves implementing and coding the TB-SLBRM (Transport Block Size for Resource Management) for NR (New Radio) communication systems.
Status: Reject
Assign: Ming 咚咚 [銘鴻]

```c
  unsigned int G = nr_get_G(nb_rb, nb_symb_sch, nb_re_dmrs, length_dmrs, harq->unav_res, mod_order, rel15->nrOfLayers);
  LOG_I(PHY,"dlsch coding A %d  Kr %d G %d (nb_rb %d, nb_symb_sch %d, nb_re_dmrs %d, length_dmrs %d, mod_order %d)\n",
        A,impp->K,G, nb_rb,nb_symb_sch,nb_re_dmrs,length_dmrs,(int)mod_order);
  // nrLDPC_encoder output is in "d"
  // let's make this interface happy!
  uint8_t tmp[8][68 * 384]__attribute__((aligned(32)));
  uint8_t *d[impp->n_segments];
  for (int rr=impp->macro_num*8, i=0; rr < impp->n_segments && rr < (impp->macro_num+1)*8; rr++,i++ )
    d[rr] = tmp[i];
  ldpc_interface.LDPCencoder(harq->c, d, impp);
  // Compute where to place in output buffer that is concatenation of all segments
  uint32_t r_offset=0;
  for (int i=0; i < impp->macro_num*8; i++ )
     r_offset+=nr_get_E(G, impp->n_segments, mod_order, rel15->nrOfLayers, i);
  for (int rr=impp->macro_num*8; rr < impp->n_segments && rr < (impp->macro_num+1)*8; rr++ ) {
    if (impp->F>0) {
      // writing into positions d[r][k-2Zc] as in clause 5.3.2 step 2) in 38.212
      memset(&d[rr][impp->K - impp->F - 2 * impp->Zc], NR_NULL, impp->F);
    }

#ifdef DEBUG_DLSCH_CODING
    LOG_D(PHY,"rvidx in encoding = %d\n", rel15->rvIndex[0]);
#endif
    uint32_t E = nr_get_E(G, impp->n_segments, mod_order, rel15->nrOfLayers, rr);
    //#ifdef DEBUG_DLSCH_CODING
    LOG_D(NR_PHY,
          "Rate Matching, Code segment %d/%d (coded bits (G) %u, E %d, Filler bits %d, Filler offset %d mod_order %d, nb_rb "
          "%d,nrOfLayer %d)...\n",
          rr,
          impp->n_segments,
          G,
          E,
          impp->F,
          impp->K - impp->F - 2 * impp->Zc,
          mod_order,
          nb_rb,
          rel15->nrOfLayers);

    uint32_t Tbslbrm = rel15->maintenance_parms_v3.tbSizeLbrmBytes;
```

```c
  int bw_tbslbrm = current_DL_BWP ? mac->sc_info.dl_bw_tbslbrm : dlsch_pdu->BWPSize;
  dlsch_pdu->tbslbrm = nr_compute_tbslbrm(dlsch_pdu->mcs_table, bw_tbslbrm, 1);
```