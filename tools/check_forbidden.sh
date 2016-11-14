#!/bin/bash

# Defined in ${PROJECT}.cfg file
AUTHORIZED_FN=

# Collected with `nm -u` command
PROGRAM_FN=

# Set to 1 when a forbidden function is found
FORBIDDEN=0

# Check if the file exists
if ! [[ -f $1 ]]; then
	printf "\033[1;33m$0: File '$1' not found !\033[1;0m\n"
	exit 1
else
	# Collect file's undefined symbols (exit if not a valid object file)
	PROGRAM_FN=`nm -u $1 2>/dev/null`
	if ! [[ "$?" == "0" ]]; then
		printf "\033[1;33m$0: File '$1' is not a valid object file !\033[1;0m\n"
		exit 2
	fi
fi

if [[ "$2" == "" ]]; then
	echo "..."
else
	# Check if the file exists
	if ! [[ -f $2 ]]; then
		printf "\033[1;33m$0: File '$2' not found !\033[1;0m\n"
		exit 1
	else
		source $2 2>/dev/null
		if ! [[ "$?" == "0" ]]; then
			printf "\033[1;33m$0: File '$2' is not a valid source file.\033[1;0m\n"
			exit 2
		fi
	fi
fi
if [[ "$AUTHORIZED_FN" == "" ]]; then
	printf "\033[1;33m$0: No 'functions' found in '$2'.\033[1;0m\n"
	exit 3
fi

# Look for a valid match
function is_forbidden
{
	for auth_fn in ${AUTHORIZED_FN[@]}; do
		if [[ "$1" == "_$auth_fn" ]]; then
			return
		fi
	done
	FORBIDDEN=1
	printf "\033[1;31mForbidden function found: $fn\033[1;0m\n"
}

for fn in ${PROGRAM_FN[@]}; do
	if [[ $fn =~ ^_{1}[a-zA-Z0-9]*$ ]]; then
		is_forbidden $fn
	fi
done

if [[ "$FORBIDDEN" == "0" ]]; then
	printf "\033[1;32mNo forbidden functions found\033[1;0m\n"
fi
