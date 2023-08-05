#!/bin/bash

# File path
ODU_PATH=$(pwd)
file_path1="$ODU_PATH/src/cm/common_def.h"
file_path2="$ODU_PATH/src/cu_stub/cu_f1ap_msg_hdl.h"
file_path3="$ODU_PATH/src/cu_stub/cu_stub_egtp.h"
file_path4="$ODU_PATH/src/cm/rgu.h"

# New values for experiment
new_max_num_ue=3  # New value for max number of UEs
new_lc_each_ue=1  # New value for the number of logical channels for each UE
new_total_lc_traffic=3  # New value for total number of logical channels for traffic
new_total_lc_rlc=3  # New value for total number of logical channels in RLC layer

# Find the line containing the MAX_NUM_UE macro and replace the value
if grep -q -E "^#define[[:space:]]+MAX_NUM_UE[[:space:]]+[0-9]+" "$file_path1"; then
    old_max_num_ue=$(grep -E "^#define[[:space:]]+MAX_NUM_UE[[:space:]]+[0-9]+" "$file_path1" | awk '{print $3}')
    sed -i "s/^#define[[:space:]]\+MAX_NUM_UE[[:space:]]\+[0-9]\+/#define MAX_NUM_UE $new_max_num_ue/" "$file_path1"
    echo "Successfully updated MAX_NUM_UE from $old_max_num_ue to $new_max_num_ue."
else
    echo "MAX_NUM_UE macro not found in the file."
fi

# Find the line containing the MAX_DRB_SET_UE_CONTEXT_SETUP_REQ macro and replace the value
if grep -q -E "^#define[[:space:]]+MAX_DRB_SET_UE_CONTEXT_SETUP_REQ[[:space:]]+[0-9]+" "$file_path2"; then
    old_lc_each_ue=$(grep -E "^#define[[:space:]]+MAX_DRB_SET_UE_CONTEXT_SETUP_REQ[[:space:]]+[0-9]+" "$file_path2" | awk '{print $3}')
    sed -i "s/^#define[[:space:]]\+MAX_DRB_SET_UE_CONTEXT_SETUP_REQ[[:space:]]\+[0-9]\+/#define MAX_DRB_SET_UE_CONTEXT_SETUP_REQ $new_lc_each_ue/" "$file_path2"
    echo "Successfully updated MAX_DRB_SET_UE_CONTEXT_SETUP_REQ from $old_lc_each_ue to $new_lc_each_ue."
else
    echo "MAX_DRB_SET_UE_CONTEXT_SETUP_REQ macro not found in the file."
fi

# Find the line containing the NUM_TUNNEL_TO_PUMP_DATA macro and replace the value
if grep -q -E "^#define[[:space:]]+NUM_TUNNEL_TO_PUMP_DATA[[:space:]]+[0-9]+" "$file_path3"; then
    old_total_lc_traffic=$(grep -E "^#define[[:space:]]+NUM_TUNNEL_TO_PUMP_DATA[[:space:]]+[0-9]+" "$file_path3" | awk '{print $3}')
    sed -i "s/^#define[[:space:]]\+NUM_TUNNEL_TO_PUMP_DATA[[:space:]]\+[0-9]\+/#define NUM_TUNNEL_TO_PUMP_DATA $new_total_lc_traffic/" "$file_path3"
    echo "Successfully updated NUM_TUNNEL_TO_PUMP_DATA from $old_total_lc_traffic to $new_total_lc_traffic."
else
    echo "NUM_TUNNEL_TO_PUMP_DATA macro not found in the file."
fi

# Find the line containing the RGU_MAX_LC macro and replace the value
if grep -q -E "^#define[[:space:]]+RGU_MAX_LC[[:space:]]+[0-9]+" "$file_path4"; then
    old_total_lc_rlc=$(grep -E "^#define[[:space:]]+RGU_MAX_LC[[:space:]]+[0-9]+" "$file_path4" | awk '{print $3}')
    sed -i "s/^#define[[:space:]]\+RGU_MAX_LC[[:space:]]\+[0-9]\+/#define RGU_MAX_LC $new_total_lc_rlc/" "$file_path4"
    echo "Successfully updated RGU_MAX_LC from $old_total_lc_rlc to $new_total_lc_rlc."
else
    echo "RGU_MAX_LC macro not found in the file."
fi