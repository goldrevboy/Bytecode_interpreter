#!/bin/bash

# Set the compiler and flags
CC=gcc
CFLAGS="-Wall -Wextra -g -std=c99"

# Output executable name
OUTPUT="program.out"

# Compile all files
echo "Compiling all files..."
$CC $CFLAGS -o $OUTPUT *.c
if [ $? -ne 0 ]; then
    echo "Compilation failed. Fix the errors before debugging."
    exit 1
fi

echo "Compilation successful. Running the program under gdb..."
echo "---------------------------------------------"

# Run the program with gdb
gdb -q -batch -ex "run" -ex "backtrace" -ex "info source" --args ./$OUTPUT "$@"

# Explanation of gdb commands:
# - `-q`: Quiet mode
# - `-batch`: Run commands non-interactively
# - `-ex \"run\"`: Start the program
# - `-ex \"backtrace\"`: Print the stack trace if a crash occurs
# - `-ex \"info source\"`: Show the current source file being debugged
# - `--args ./$OUTPUT \"$@\"`: Pass arguments to the program
