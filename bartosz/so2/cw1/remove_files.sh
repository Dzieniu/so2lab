#!/bin/bash
if [ "$#" != "1" ]
then
  echo "podaj argumenty"
  exit 1
fi

if [ ! -d $1 ]
then
  echo "katalog nie istnieje"
  exit 1
fi

for i in `ls $1`
do
  if [ ! -x $1/$i ] && [ -f $1/$i ]
  then
    rm $1/$i
  fi
done
