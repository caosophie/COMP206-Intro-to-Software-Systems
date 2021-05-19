#!/bin/bash

# Check for correct number of arguments
if [[ "$#" -ne 2 ]]; then
	echo "Usage fixformat.sh <dirname> <opfile>"
	exit 1
# Check if first argument is a valid directory
elif [[ ! -d "$1" ]]; then
	echo "Error $1 is not a valid directory" >&2
	exit 1
fi

list_labs="$(find $1 -iname "lab-*.csv")"
echo "User Email,Name (Original Name),Lab,Total Duration (Minutes)" > $2


for file in $list_labs; do
	basename=$(basename $file) # basename is something like lab-A
	IFS=$'\n' # ignore white spaces

	col="$(sed -n '2p' $file | sed 's/,/ /g' | awk '{print NF}')" # get the number of columns
	lab="$(echo $basename | awk -F [-.] '{print toupper($2)}')" # get the lab letter and make it capital

	# for files with format Name, Email, Duration, Guest
	if [[ $col == 5 ]]; then
		for line in $(cat $file | sed 1d $file); do # skip the first line and get the parameters
			firstname="$(echo $line | sed 's/,/ /g' | awk '{print $1}')"
			lastname="$(echo $line | sed 's/,/ /g' | awk '{print $2}')"
			email="$(echo $line | sed 's/,/ /g' | awk '{print $3}')"
			time="$(echo $line | sed 's/,/ /g' | awk '{print $4}')"
			echo "$email,$firstname $lastname,$lab,$time" >> "$2"
			
		done
	else
		for line in $(cat $file | sed 1d $file); do
			firstname="$(echo $line | sed 's/,/ /g' |  awk '{print $1}')"
			lastname="$(echo $line | sed 's/,/ /g' |  awk '{print $2}')"
			email="$(echo $line | sed 's/,/ /g' | awk '{print $3}')"
			time="$(echo $line | sed 's/,/ /g' | awk '{print $10}')"
			echo "$email,$firstname $lastname,$lab,$time" >> "$2"
		done
	fi

done

exit 0
