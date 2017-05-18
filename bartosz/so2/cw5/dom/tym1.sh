#!/bin/sh

if [ $# -lt 1 ]; then               # check argv length
    echo "Usage: $0 FILE"           # print usage info
    exit 1                          # exit
fi

# Dla zadanego pliku tekstowego wylistowac tresc w postaci
# 1. Pierwsze zdanie
# 2. Drugie zdanie
# 3. ...

gawk 'BEGIN { RS="[.?!]"; OFS="" } /\w/ { gsub(/\n/, " "); gsub(/\s+$/, ""); gsub(/^\s+/, "");  print NR, ". ", $0, RT }' $1
