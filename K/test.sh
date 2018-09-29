#!/usr/bin/env bash

tmpfile=$(mktemp)
TL=3
for exe in extras/*; do
  test -x "$exe" || continue
  echo -n "Testing $exe: "
  for input in inputs/*; do
    output=outputs/${input:7}
    timeout $TL "$exe" < "$input" > "$tmpfile" 2> /dev/null
    RES=$?
    if [ $RES -ne 0 ]; then
      if [ $RES -eq 124 ]; then
        echo "TLE on $input"
      else
        echo "RE on $input"
      fi
      continue 2
    fi
    if ! [ $(./checker "$input" "$tmpfile") == "AC" ]; then
      echo "WA on $input"
      continue 2
    fi
  done
  echo "AC"
done
rm $tmpfile


