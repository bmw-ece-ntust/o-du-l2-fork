#!/bin/bash

# ODU PATH
ODU_PATH=$(pwd)

# set the output file path
OUTPUT_FILE=$ODU_PATH/overall-prb.csv
touch $OUTPUT_FILE

# Define the regular expression patterns for overall PRB usage
prb_usage_pattern="PRBUsage: ([0-9]+\.[0-9]+)"
second=0

# run the odu command and continuously monitor its output
while IFS= read -r line; do
  if [[ $line == *"DL Throughput Per UE"* ]]; then
    second=$(bc <<< "$second + 0.5")
  # check if the line contains "PRBUsage"
  elif [[ $line == *"KPM: overall performance"* ]]; then
    prb_usage=$(echo "$line" | grep -oE "$prb_usage_pattern" | sed 's/PRBUsage: //')
    # output the PRBUsage value to the console
    echo "Second: $second -> PRBUsage: $prb_usage"
    # append the PRBUsage value to the csv file
    echo "$second,$prb_usage" >> $OUTPUT_FILE
  fi
done < "$ODU_PATH/log-du.txt"