#!/bin/bash

# set the output file path
OUTPUT_FILE=/home/ubuntu/Multiple-UE-Per-TTI-SCH/UEtpt.csv
touch $OUTPUT_FILE

# ODU PATH
ODU_PATH=/home/ubuntu/Multiple-UE-Per-TTI-SCH

# Define the regular expression patterns for UE Id and DL Tpt
data_size_pattern="Data size ([0-9]+)"
ue_id_pattern="UE id ([0-9]+)"
slot_pattern="in this slot ([0-9]+)"

# run the odu command and continuously monitor its output
while IFS= read -r line; do
    # check if the line contains "DL Tpt"
    if [[ $line == *"JOJO  -->  Data size"* ]]; then
        # extract the DL Tpt value from the line
        slot=$(echo "$line" | grep -oE "$slot_pattern" | sed 's/in this slot //')
        ue_id=$(echo "$line" | grep -oE "$ue_id_pattern" | sed 's/UE id //')
        dl_tpt=$(echo "$line" | grep -oE "$data_size_pattern" | sed 's/Data size //')

        # output the DL Tpt value to the console
        echo "Slot: $slot -> UE id: $ue_id DL Tpt: $dl_tpt"

        # append the DL Tpt value to the csv file
        echo "$slot,$ue_id,$dl_tpt" >> $OUTPUT_FILE
    fi
done < "$ODU_PATH/log-du.txt"