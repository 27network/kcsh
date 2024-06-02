#!/usr/bin/env bash

count=0
for file in *.txt
do
	echo "$file"
	count=$((count+1))
done

echo "Total number of files in the current directory: $count"
