#!/usr/bin/env bash

read -p "Enter file extension: " extension
case $extension in
	".txt"|"log")
	echo "It's a text file or a log file!"
	;;
	".csv"|".xlsx")
	echo "It's a spreadsheet file!"
	;;
esac
