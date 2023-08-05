#!/bin/bash

ODU_PATH=$(pwd)

sudo ifconfig lo:ODU "192.168.130.81"
sudo ifconfig lo:CU_STUB "192.168.130.82"

# Build odu & cu stub
cd $ODU_PATH/build/odu
sudo -E make clean_odu odu MACHINE=BIT64 MODE=FDD