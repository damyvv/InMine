#!/bin/bash

RED='\033[0;31m' # Red
BB='\033[0;34m'  # Blue
NC='\033[0m'     # No Color
BG='\033[0;32m'  # Green

error() { >&2 echo -e "${RED}$1${NC}"; }
showinfo() { echo -e "${BG}$1${NC}"; }
workingprocess() { echo -e "${BB}$1${NC}"; }
alert() { echo -e "${RED}$1${NC}"; }

showinfo "Starting cmake..."
mkdir -p build
cd build
cmake ..
showinfo "Building the project..."
make -j8

if [ $? -ne 0 ]; then
  error "Error: there are compile errors!"
  exit 3
fi

workingprocess "Build successful! All done"
