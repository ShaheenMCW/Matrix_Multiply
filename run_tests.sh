#!/bin/bash

gcc -o matrix_driver driver.c -lm

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running tests..."

    ./matrix_driver

    if [ $? -eq 0 ]; then
        echo "Tests completed successfully."
    else
        echo "Error occurred during test execution."
    fi
else
    echo "Compilation failed. Please check the code."
fi
