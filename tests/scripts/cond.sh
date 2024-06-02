#!/usr/bin/env bash

# Checking if a number is positive or negative
read -p "Enter a number:" num

if [ $num -gt 0 ]; then
echo "The number is positive."
else
	echo "The number is negative or zero."
fi
