#!/bin/bash
#<Konrad><Dzień>
#Oblicz całkowitą sumę wielkości pojedyńczego pliku lub katalogu z całą jego zawartością
#w bajtach (jedno zmyślne wykonanie komendy awk)

find $1 -ls | awk ' {

	if(NR>1){
		sum += $7
	}
	} 
END {print sum}' 