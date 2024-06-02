#!/usr/bin/env bash

# trap.sh - tests the trap command
# trap command is used to catch signals and execute commands when they are received.

trap 'echo "You hit Ctrl-C!"' INT

echo "This is a test script."
while true
do
	sleep 1
done
