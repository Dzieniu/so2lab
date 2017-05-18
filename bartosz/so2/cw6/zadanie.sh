#!/bin/sh

# w zadanym drzewie katalogow
# znalezc pliki regularne
# ktorych liczba okreslajaca wielkosc plikow
# w kb jest kawalkiem nazwy pliku

if [ $# -lt 1 ]; then               # check argv length
    echo "Usage: $0 DIR"            # print usage info
    exit 1                          # exit
fi

dir=$1
gfind "$1" -type f -printf "%p %f %k\n" | awk '{
    name = $2;
    size = $3;
    isSizeInName = "";
    regexp = "(" size ")";

    if (name ~ regexp){
      isSizeInName = "tak"
    } else {
      isSizeInName = "nie"
    }

    print "size: " size "kb; name " $1 ";\n zawiera sie: " isSizeInName "\n";
}'
