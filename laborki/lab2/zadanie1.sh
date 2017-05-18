#!/bin/bash
# <Konrad><Dzien>
# Napisz skrypt, który dla wszystkich plików z jakiegoś katalogu (parametr wywołania skryptu)
# utworzy dowiązania symboliczne w drugim kataogu ( parametr wywołania skryptu), jeśli
# odpowiednie dowiązania symboliczne jeszcze nie istnieją

zmienna="dowiazanie"
licznik=0

for plik in `ls $1`
do

	if [ -f "$plik" ]
	then

		for plik2 in `ls $2`
		do
			if [ -h $2/$plik2 ]		
			then

				if [ `readlink $2/$plik2` == "$1/$plik" ]
				then
					licznik=1
					break
				fi
			fi
		done

		if [ $licznik == 0 ]
		then
			echo `ln -s $1/$plik $2/$plik.$zmienna`
			licznik=0
		fi
	licznik=0
	fi
done