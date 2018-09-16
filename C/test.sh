#!/bin/sh

for input in inputs/*
do
    ./validator < "$input" || { echo "$input is invalid"; exit 1; }
done

for exe in extras/*
do
    test -x "$exe" || continue

    echo -n "Testing $exe: "

    for input in inputs/*
    do
        output=$(echo "$input" | sed 's-inputs/-outputs/-')
        prlimit -s-1 "$exe" < "$input" | cmp -s "$output" || { echo "WA on $input"; continue 2; }
    done

    echo "AC"
done
