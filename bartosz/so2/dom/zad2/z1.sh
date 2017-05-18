#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage : $0 lista"
  exit 1
fi

if [[ ! -r $1 ]]; then
  echo "Plik $1 nie istnieje lub nie jest odczytywalny."
  exit 1
fi

while read LINE
do
  if [ -e $LINE ]; then
    rm -f $LINE

  else
    touch $LINE

    if [ $? -ne 0 ]; then
      echo "Operacja nie powiodla sie."
      exit 1
    fi
  fi

done < $1
