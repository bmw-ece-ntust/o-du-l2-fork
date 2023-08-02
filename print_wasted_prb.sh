#!/bin/bash

# set the output file path
OUTPUT_FILE=/home/ubuntu/Multi-UE-per-TTI-SCH/waste.csv
touch $OUTPUT_FILE

# ODU PATH
ODU_PATH=/home/ubuntu/Multi-UE-per-TTI-SCH

# Define the regular expression patterns for wasted PRBs
prb_pattern="The amount of wasted PRBs is ([0-9]+)"
slot_pattern="in slot ([0-9]+)"

# run the odu command and continuously monitor its output
while IFS= read -r line; do
  # check if the line contains "DL Tpt"
  if [[ $line == *"The amount of wasted PRBs is"* ]]; then
    # extract the remaining PRBs from the line
    prbs=$(echo "$line" | grep -oE "$prb_pattern" | sed 's/The amount of wasted PRBs is //')
    slot=$(echo "$line" | grep -oE "$slot_pattern" | sed 's/in slot //')

    echo "Slot: $slot -> Wasted PRBs: $prbs"

    # append the PRBs value to the csv file
    echo "$slot,$prbs" >> $OUTPUT_FILE
  fi
done < "$ODU_PATH/log-du.txt"