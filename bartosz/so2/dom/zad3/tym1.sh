#!/bin/sh

if [ $# -lt 2 ]; then               # check argv length
    echo "Usage: $0 DIR N"          # print usage info
    exit 1                          # exit
fi

# W zadanym drzewie katalogow znalezc podkatalogi zawierajace minimum N
# podkatalogow oraz majace ustawione atrybuty dostepu tak, ze wlasciciel
# nie ma prawa odczytu lub wykonania, natomiast grupa lub inni maja prawo
# odczytu

n=`expr $2 + 2`

find $1 -type d -links +$n \( \( ! -perm -u+r \) -or \( ! -perm -u+x \) \) \( -perm -g+r -or -perm -o+r \) -print
