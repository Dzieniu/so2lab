#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Usage : $0 plik gdzie"
  exit 1
fi

if [ ! -e $1 ]; then
  echo "Plik $1 nie istnieje"
  exit 1
fi

if [ ! -d $2 ]; then
  echo "Katalog $2 nie istnieje"
  exit 1
fi

find $2 -samefile $1 2>/dev/null
