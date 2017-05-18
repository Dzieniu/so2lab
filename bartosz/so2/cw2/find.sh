#!/bin/bash
if [ "$#" != "2" ]
then
  echo "podaj argumenty"
  exit 1
fi

if [ ! -d $1 ]
then
  if [ ! -d $2 ]; then
    echo "któryś z katalogów nie istnieje"
    exit 1
  fi
  echo "któryś z katalogów nie istnieje"
  exit 1
fi

for i in `ls $1`
do
  if [ -h $1/$i ]
  then
    if [ -f $2/$i ]; then
      if [ ! -h $2/$i ]; then

        if [ `readlink -f $1/$i` == `readlink -f $2/$i` ]; then
          echo "dla $1/$i TAK"
        fi

      fi
    fi
  fi
done
