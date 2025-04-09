#!/bin/bash

# Compile all .cpp files into a single executable
g++ -std=c++17 -w -Wall -Wextra -o interpreter *.cpp

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    
    # Run with argument (file) or without (interactive)
    if [ $# -eq 1 ]; then
        ./interpreter "$1"
    else
        ./interpreter
    fi
else
    echo "Compilation failed."
fi
