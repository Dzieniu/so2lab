#!/usr/bin/env bash

if [ $# -ne 1 ]; then
  echo "Usage : $0 <dir>"
  exit 1
fi

if [ ! -d $1 ]; then
  echo "Katalog $1 nie istnieje"
  exit 1
fi

wynik=`find $1 -maxdepth 1 -type f`
for line in $wynik;
do
  rozm=`stat -c "%s" $line`
  rozm=$(($rozm / 1024))
  mv $line $line.$rozm
done

ls -X $1
