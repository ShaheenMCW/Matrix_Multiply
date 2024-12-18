#!/bin/bash

# Compile the C program
gcc -o matrix_driver driver.c -lm

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running tests..."

    # Run the C program and capture the output
    ./matrix_driver

    # Check if the execution was successful
    if [ $? -eq 0 ]; then
        echo "Tests completed successfully."
    else
        echo "Error occurred during test execution."
    fi
else
    echo "Compilation failed. Please check the code."
fi
