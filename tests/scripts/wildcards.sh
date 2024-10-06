#!/bin/bash

# Array of test commands
tests=(
    "'*'"
    '"*"'
    '*'
	"Make*"
    "'Make'*"
    "'Make*'"
    '"Make*"'
    'Make*file'
    "'Make'*\"file\""
    "'file*'"
    '"file*"'
    '*file*'
    'Make*/'
    'Make/*'
    "'Make/'*"
    "'Make/'*"
)

# Loop through each test and execute
for TEST in "${tests[@]}"; do
    echo -n "$TEST -> "
    bash -c "echo $TEST"
done

