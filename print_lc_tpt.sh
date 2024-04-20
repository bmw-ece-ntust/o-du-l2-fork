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
LC_setup_pattern="JOJO --> UE ID:([0-9]+) LC ID:([0-9]+) is with 5QI: [0-9]+, priority level: [0-9]+, PDU session ID: [0-9]+, MFBR: ([0-9]+), GFBR: ([0-9]+), avg. win: ([0-9]+)"

second=0
# Declare associative arrays to store MFBR and GFBR values for each UE ID and LC ID
declare -A mfbr_array
declare -A gfbr_array

echo "time,ueId,lcId,tpt,gfbr,mfbr" >> $OUTPUT_FILE

# run the odu command and continuously monitor its output
while IFS= read -r line; do
    # check if the line contains "DL Tpt"
    if [[ $line == *"DRB throughput display"* ]]; then
        second=$(bc <<< "$second + 1")
    fi
    # check if the line contains "()"
    if [[ $line =~ $LC_setup_pattern ]]; then
        ue_id_jojo="${BASH_REMATCH[1]}"
        lc_id_jojo="${BASH_REMATCH[2]}"
        mfbr_jojo="${BASH_REMATCH[3]}"
        gfbr_jojo="${BASH_REMATCH[4]}"
        avgWin_jojo="${BASH_REMATCH[5]}"

        # calculate mfbr and gfbr as throughput
        mfbr_jojo_calculated=$(echo "scale=2; $mfbr_jojo * 8 / 1000" | bc)
        gfbr_jojo_calculated=$(echo "scale=2; $gfbr_jojo * 8 / 1000" | bc)

        # output the JOJO values to the console
        echo "JOJO --> UE id: $ue_id_jojo, LC id: $lc_id_jojo, MFBR: $mfbr_jojo, GFBR: $gfbr_jojo"

        # store the values in the associative array
        mfbr_array["$ue_id_jojo,$lc_id_jojo"]=$mfbr_jojo_calculated
        gfbr_array["$ue_id_jojo,$lc_id_jojo"]=$gfbr_jojo_calculated
    fi
    if [[ $line == *"Tput per DRB"* ]]; then
        # extract the DL Tpt value from the line
        ue_id=$(echo "$line" | grep -oE "$ue_id_pattern" | sed 's/UE ID: //')
        lc_id=$(echo "$line" | grep -oE "$lc_id_pattern" | sed 's/LC ID: //')
        dl_tpt=$(echo "$line" | grep -oE "$tpt_pattern" | sed 's/DL Tpt : //')

        # output the DL Tpt value to the console
        echo "Second: $second --> UE id: $ue_id, LC id: $lc_id, DL Tpt: $dl_tpt, GFBR: ${gfbr_array["$ue_id,$lc_id"]}, MFBR: ${mfbr_array["$ue_id,$lc_id"]}"

        # append the DL Tpt value to the csv file
        echo "$second,$ue_id,$lc_id,$dl_tpt,${gfbr_array["$ue_id,$lc_id"]},${mfbr_array["$ue_id,$lc_id"]}" >> $OUTPUT_FILE
    fi
done < "$ODU_PATH/log-du.txt"
