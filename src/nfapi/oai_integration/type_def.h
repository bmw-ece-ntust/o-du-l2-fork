/*
 * Licensed to the small cell integration team
 * Created by Yu-Hsin (Brandon) Chuang at 2023/12/05
 * Follow the OAI definition.
 */

#ifndef __TYPE_DEF_H__
#define __TYPE_DEF_H__

#include <stdint.h>
#include "nfapi_interface.h"
#include "nfapi_vnf_interface.h"

typedef struct {
  uint8_t   enabled;
  uint32_t  rx_port;
  uint32_t  tx_port;
  char      tx_addr[80];
} udp_data;

typedef struct {
  uint16_t  index;
  uint16_t  id;
  uint8_t   rfs[2];
  uint8_t   excluded_rfs[2];

  udp_data  udp;

  char      local_addr[80];
  int       local_port;

  char      *remote_addr;
  int       remote_port;

  uint8_t   duplex_mode;
  uint16_t  dl_channel_bw_support;
  uint16_t  ul_channel_bw_support;
  uint8_t   num_dl_layers_supported;
  uint8_t   num_ul_layers_supported;
  uint16_t  release_supported;
  uint8_t   nmm_modes_supported;

  uint8_t   dl_ues_per_subframe;
  uint8_t   ul_ues_per_subframe;

  uint8_t   first_subframe_ind;

  // timing information recevied from the vnf
  uint8_t   timing_window;
  uint8_t   timing_info_mode;
  uint8_t   timing_info_period;
} phy_info;

typedef struct {
  uint16_t  index;
  uint16_t  band;
  int16_t   max_transmit_power;
  int16_t   min_transmit_power;
  uint8_t   num_antennas_supported;
  uint32_t  min_downlink_frequency;
  uint32_t  max_downlink_frequency;
  uint32_t  max_uplink_frequency;
  uint32_t  min_uplink_frequency;
} rf_info;

typedef struct {

  int       release;
  phy_info  phys[2];
  rf_info   rfs[2];

  uint8_t   sync_mode;
  uint8_t   location_mode;
  uint8_t   location_coordinates[6];
  uint32_t  dl_config_timing;
  uint32_t  ul_config_timing;
  uint32_t  tx_timing;
  uint32_t  hi_dci0_timing;

  uint16_t  max_phys;
  uint16_t  max_total_bw;
  uint16_t  max_total_dl_layers;
  uint16_t  max_total_ul_layers;
  uint8_t   shared_bands;
  uint8_t   shared_pa;
  int16_t   max_total_power;
  uint8_t   oui;

  uint8_t   wireshark_test_mode;

} pnf_info;

typedef struct mac mac_t;
typedef struct mac{

  void *user_data;

  void (*dl_config_req)(mac_t *mac, nfapi_dl_config_request_t *req);
  void (*ul_config_req)(mac_t *mac, nfapi_ul_config_request_t *req);
  void (*hi_dci0_req)(mac_t *mac, nfapi_hi_dci0_request_t *req);
  void (*tx_req)(mac_t *mac, nfapi_tx_request_t *req);
} mac_t;

typedef struct {

  int     local_port;
  char    local_addr[80];

  unsigned timing_window;
  unsigned periodic_timing_enabled;
  unsigned aperiodic_timing_enabled;
  unsigned periodic_timing_period;

  // This is not really the right place if we have multiple PHY,
  // should be part of the phy struct
  udp_data udp;
  uint8_t thread_started;
  nfapi_vnf_p7_config_t *config;
  mac_t *mac;
} vnf_p7_info;

typedef struct {
  uint8_t wireshark_test_mode;
  pnf_info pnfs[2];
  vnf_p7_info p7_vnfs[2];
} vnf_info;

typedef struct vnf_cfg{
	vnf_info *vnf;
	nfapi_vnf_config_t *config;
}vnf_cfg_t;

#endif //__TYPE_DEF_H__
/* End of file */