# Assuming the file name is data.txt
file="log-du.txt"

# Use grep to find the line containing the relevant information
line=$(grep "JOJO processing time Measurement" "$file")

# Use awk to extract the processing time
processing_time=$(echo "$line" | awk '{print $NF}')

# ODU PATH
ODU_PATH=$(pwd)

# set the output file path
OUTPUT_FILE=$ODU_PATH/processing_time.csv
touch $OUTPUT_FILE

# Define the regular expression patterns for processing time
sec_pattern="([0-9]+\.[0-9]+) sec"

# run the odu command and continuously monitor its output
while IFS= read -r line; do
    # check if the line contains "processing time"
    if [[ $line == *"JOJO processing time Measurement : Processing Time of whole scheduling:"* ]]; then
        # extract the processing time value from the line
        processing_time=$(echo "$line" | grep -oE "$sec_pattern" | sed 's/ sec//')

        # Print the processing time
        # echo "Processing Time of whole scheduling: $processing_time sec"

        # append the DL Tpt value to the csv file
        echo "$processing_time" >> $OUTPUT_FILE
    fi
done < "$ODU_PATH/log-du.txt"