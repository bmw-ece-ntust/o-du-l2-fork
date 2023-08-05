#!/bin/bash

ODU_PATH=$(pwd)

sudo ifconfig lo:ODU "192.168.130.81"
sudo ifconfig lo:CU_STUB "192.168.130.82"

# Run odu
cd $ODU_PATH/bin
cd odu

# Debug Mode
# sudo gdb ./odu

# Normal Mode
sudo ./odu