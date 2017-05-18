#!/bin/sh

if [ $# -lt 2 ]; then               # check argv length
    echo "Usage: $0 DIRA DIRB"      # print usage info
    exit 1                          # exit
fi

# $1 # katalog
# $2 # miejsca na kopie

# bez kopiowania katalogow
# kopiowanie plikow i dowiazan
# dowiazania po skopiowaniu maja wskazywac na obiekty skopiowane a jezeli nie byly kopiowane to na oryginalne


dira=$(greadlink -f $1)
dirb=$(greadlink -f $2)

for i in `ls $dira`; do
    if [ -L "$dira/$i" -o -f "$dira/$i" ]; then
        echo "Copy $i"
        gcp -d "$dira/$i" "$dirb/$i"
    fi;
done;

# cd $dirb

for i in `ls $dirb`; do
    echo
    if [ -L "$dirb/$i" ]; then
        echo "Link file $i => "
        # echo "readlink = $(greadlink -f $dirb/$i)"
        full=$(greadlink -f $dirb/$i)
        echo "full = $full"
        if echo $full | grep "^$dira"; then
            echo "inside"
            nd=${full/$dira/$dirb}

            rm "$dirb/$i"
            if [ -f "$nd" ]; then
                ln -s "$nd" "$dirb/$i"
            else
                orig=$(greadlink -f $dira/$i)
                ln -s "$orig" "$dirb/$i"
            fi;
        else
            echo "outside"
            if [ $full -a -f $full  ]; then
                echo "copied"
            else
                echo "missing - replace with original"
                rm "$dirb/$i"
                orig=$(greadlink -f $dira/$i)
                ln -s $orig "$dirb/$i"
            fi;
        fi;

    fi;
done;
