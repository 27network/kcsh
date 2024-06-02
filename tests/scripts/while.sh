input=""

read -p "Enter q to quit: " input

while [ "$input" != "q" ] || [ "$input" != "Q" ]
do
	echo "You entered $input. Press q to quit:"
	read input
done
echo "Program Terminated..."
