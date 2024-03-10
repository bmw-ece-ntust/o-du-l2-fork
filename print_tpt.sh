#!/bin/bash

# ODU PATH
ODU_PATH=$(pwd)

# set the output file path
OUTPUT_FILE=$ODU_PATH/UEtpt.csv
touch $OUTPUT_FILE

# Define the regular expression patterns for UE Id and DL Tpt
ue_id_pattern="UE Id : ([0-9]+)"
dl_tpt_pattern="DL Tpt : ([0-9]+\.[0-9]+)"
second=0

# run the odu command and continuously monitor its output
while IFS= read -r line; do
  if [[ $line == *"DL Throughput Per UE"* ]]; then
    second=$((second+1))
  fi
  
  # check if the line contains "DL Tpt"
  if [[ $line == *"   DL Tpt : "* ]]; then
    # extract the DL Tpt value from the line
    ue_id=$(echo "$line" | grep -oE "$ue_id_pattern" | sed 's/UE Id : //')
    dl_tpt=$(echo "$line" | grep -oE "$dl_tpt_pattern" | sed 's/DL Tpt : //')

    # output the DL Tpt value to the console
    echo "Second: $second UE id: $ue_id -> DL Tpt: $dl_tpt"

    # append the DL Tpt value to the csv file
    echo "$second,$ue_id,$dl_tpt" >> $OUTPUT_FILE
  fi
done < "$ODU_PATH/log-du.txt"