#!/usr/bin/env bash

read -p "Enter a number: " num1
read -p "Enter another number: " num2
add=$((num1 + num2))
echo "Addition of numbers: $add" > output.txt
