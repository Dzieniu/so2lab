#!/bin/bash

if [ $# -ne 3 ]; then
  echo "Usage : $0 katalog rozszerzenie wynik"
  exit 1
fi

if [ ! -d $1 ]; then
  echo "Katalog $1 nie istnieje"
  exit 1
fi

if [ -e $3 ]; then
  echo "Plik wynikowy $3 juz istnieje"
  exit 1
fi

touch $3

if [ $? -ne 0 ]; then
  echo "Nie udalo sie utworzyc pliku wynikowego"
  exit 1
fi

for plik in "$1/*.$2"
do
  echo $plik >> $3
  cat $plik >> $3
done
