#!/bin/bash

# ODU PATH
ODU_PATH=$(pwd)

# set the output file path
OUTPUT_FILE=$ODU_PATH/LCtpt.csv
touch $OUTPUT_FILE

# Define the regular expression patterns for LC Id and DL Tpt
ue_id_pattern="UE ID: ([0-9]+)"
lc_id_pattern="LC ID: ([0-9]+)"
tpt_pattern="DL Tpt : ([0-9]+\.[0-9]+)"
num_lc_per_ue=1
second=0

# run the odu command and continuously monitor its output
while IFS= read -r line; do
    # check if the line contains "DL Tpt"
    if [[ $line == *"DL Throughput Per UE"* ]]; then
        second=$((second+1))
    fi
    if [[ $line == *"Tput per DRB"* ]]; then
        # extract the DL Tpt value from the line
        ue_id=$(echo "$line" | grep -oE "$ue_id_pattern" | sed 's/UE ID: //')
        lc_id=$(echo "$line" | grep -oE "$lc_id_pattern" | sed 's/LC ID: //')
        dl_tpt=$(echo "$line" | grep -oE "$tpt_pattern" | sed 's/DL Tpt : //')
        drb=$((($ue_id - 1)*$num_lc_per_ue+($lc_id-3)))
        # output the DL Tpt value to the console
        echo "Second: $second --> UE id: $ue_id, LC id: $lc_id, drb: $drb, DL Tpt: $dl_tpt"

        # append the DL Tpt value to the csv file
        echo "$second,$ue_id,$lc_id,$drb,$dl_tpt" >> $OUTPUT_FILE
    fi
done < "$ODU_PATH/log-du.txt"