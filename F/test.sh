#!/usr/bin/env bash

tmpfile=$(mktemp)
TL=3
for exe in extras/*; do
  test -x "$exe" || continue
  echo -n "Testing $exe: "
  for input in inputs/*; do
    output=outputs/${input:7}
    timeout $TL "$exe" < "$input" > "$tmpfile"
    if [ $? -ne 0 ]; then
      echo "TLE/RE on $input"
      continue 2
    fi
    cmp -s "$tmpfile" "$output" || {
      echo "WA on $input"
      continue 2
    }
  done
  echo "AC"
done
rm $tmpfile
