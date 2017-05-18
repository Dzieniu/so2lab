#!/usr/bin/env bash

if [ $# -ne 2 ]; then
  echo "Usage : $0 <dir> <usr>"
  exit 1
fi

if [ ! -d $1 ]; then
  echo "Katalog $1 nie istnieje"
  exit 1
fi

uid=`id -u $2 2>/dev/null`

if [ $? -ne 0 ]; then
  echo "Uzytkownik $2 nie istnieje"
  exit 1
fi

ileplikow=`find $1 -maxdepth 1 -uid $uid | wc -l`
echo "Uzytkownik $2 ma $ileplikow plikow w katalogu $1"

wynik=`find $1 -maxdepth 1 -type f -uid $uid`
calyrozm=0
rozm=0
for line in $wynik;
do
  rozm=`stat -c "%s" $line`
  calyrozm=$(($calyrozm + $rozm))
done
echo "Zajmuja one $calyrozm bajtow"
