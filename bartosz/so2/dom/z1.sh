#!/usr/bin/env bash

if [ $# -ne 1 ]; then
  echo "Usage : $0 <dir>"
  exit 1
fi

if [ ! -d $1 ]; then
  echo "Katalog $1 nie istnieje"
  exit 1
fi

echo "Pliki male w $1 :"
find $1 -maxdepth 1 -size -50 -printf "%f %sB\n"
ilemalych=`find $1 -maxdepth 1 -size -50 -printf "%f %sB\n" | wc -l`
echo "Jest $ilemalych malych plikow."

echo "Pliki srednie w $1 :"
find $1 -maxdepth 1 -size 50 -size +50 -size -1M -printf "%f %sB\n"
ilesrednich=`find $1 -maxdepth 1 -size 50 -size +50 -size -1M -printf "%f %s\n" | wc -l`
echo "Jest $ilesrednich srednich plikow."

echo "Pliki duze w $1 :"
find $1 -maxdepth 1 -size 1M -size +1M -printf "%f %sB\n"
ileduzych=`find $1 -maxdepth 1 -size 1M -size +1M -printf "%f %sB\n" | wc -l`
echo "Jest $ileduzych duzych plikow."
