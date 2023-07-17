#!/bin/bash

# set the output file path
OUTPUT_FILE=/home/ubuntu/slice_enable_scheduler/overall.csv
touch $OUTPUT_FILE

# ODU PATH
ODU_PATH=/home/ubuntu/slice_enable_scheduler

# Define the regular expression patterns for UE Id and DL Tpt
slot_pattern="is scheduled in slot ([0-9]+)"
data_size_pattern="Total data size ([0-9]+)"

# run the odu command and continuously monitor its output
while IFS= read -r line; do
    # check if the line contains "DL Tpt"
    if [[ $line == *"JOJO  -->  Total data size"* ]]; then
        # extract the DL Tpt value from the line
        slot=$(echo "$line" | grep -oE "$slot_pattern" | sed 's/is scheduled in slot //')
        dl_tpt=$(echo "$line" | grep -oE "$data_size_pattern" | sed 's/Total data size //')

        # output the DL Tpt value to the console
        echo "Slot: $slot -> DL Tpt: $dl_tpt"

        # append the DL Tpt value to the csv file
        echo "$slot,$dl_tpt" >> $OUTPUT_FILE
    fi
done < "$ODU_PATH/log-du.txt"