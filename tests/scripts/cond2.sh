#!/usr/bin/env bash

read -p "Enter your age:" age
read -p "Enter marks obtained:" marks

if [ $age -gt 25 ] && [ $marks -gt 800 ]; then
echo "Congratulations! You are eligible for a scholarship."
elif [ $age -gt 25 ] || [ $marks -gt 800 ]; then
echo "Submit administrative reference for the scholarship."
elif [ $age -lt 25 ] && [ $marks -lt 800 ]; then
echo "Sorry, you are not eligible for the scholarship."
fi
