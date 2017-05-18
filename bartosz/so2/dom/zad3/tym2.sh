#!/bin/sh

if [ $# -lt 2 ]; then               # check argv length
    echo "Usage: $0 DIRA DIRB DIRC" # print usage info
    exit 1                          # exit
fi

# dwa drzewa katalogow -> nowe drzewo zwierajace wszystkie pliki i wszystkie katalogi i dowiazania ktore wystepuja w pierwszym i drugim drzewie


echo "A"
gfind $1 -ls
echo "B"
gfind $2 -ls
echo "C"
gfind $3 -ls

for i in `gfind $1 -type d -printf "%P\n"`; do
    # echo "i = $i"
    for j in `gfind $2 -type d -path "$2/$i"`; do
        echo "$j"
        mkdir -p "$3/$i"
    done;
done

for t in f l; do
    for i in `gfind $1 -type $t -printf "%P\n"`; do
        # echo "i = $i"
        for j in `gfind $2 -type $t -path "$2/$i"`; do
            echo "$j"
            touch "$3/$i"
        done;
    done
done;
