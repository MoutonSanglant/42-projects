#!/bin/bash

source $1

PROGRAM_FN=`nm -u $2`

for fn in ${AUTHORIZED_FN[@]}; do
	echo fn: $fn
done

for fn in ${PROGRAM_FN[@]}; do
	if [[ $fn =~ ^_{1}[a-zA-Z0-9]*$ ]]; then
		echo fn: $fn
	fi
done
