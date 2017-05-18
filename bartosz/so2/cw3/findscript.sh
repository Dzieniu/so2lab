#!/bin/sh

# w zadanym drzewie katalogow znalexc pliki regularne
# do których właściciel ma prawo x, grupa ma prawo r i w
# i w inni nie maja prawa r i jeszcze plik musi byc nowszy niz 5 minut


if [ '$#' == "1" ]; then
  echo 'Podaj jeden argument, katalog'
  exit 1
fi

if [ ! -d $1 ]; then
  echo "Podaj argumenty"
  exit 1
fi

find $1 -type f -perm -u=x,g=rw ! -perm -o=r -mmin -5 -print
