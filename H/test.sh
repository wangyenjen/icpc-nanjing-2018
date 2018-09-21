#!/usr/bin/env bash

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
        timeout 1s prlimit -s-1 "$exe" < "$input" | cmp -s "$output"

        ret0="${PIPESTATUS[0]}" ret1="${PIPESTATUS[1]}"
        [ "$ret0" = "124" ] && { echo "TLE on $input"; continue 2; }
        [ "$ret0" = "0" ] || { echo "RE on $input"; continue 2; }
        [ "$ret1" = "0" ] || { echo "WA on $input"; continue 2; }
    done

    echo "AC"
done
