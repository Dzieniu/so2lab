#!/bin/sh

# Wyświetlić zawartość zadanego pliku tekstowego, modyfikując go
# tak aby każde zdanie bylo w osobnej(jednej) linii
# puste linie beda wyswietlone jako puste.
# Zdanie = co najmniej 2 wyrazy + .!? na koncu


gawk 'BEGIN { RS="[.!?]"; previous=""} 
{

gsub(/\n/, " "); 
gsub(/^\s+\s+/, "\n"); 
if (NF>1) 
	{ print  previous "" $0 "" RT; previous=""} 
else 
	{previous=previous "" $0 "" RT}

}' $1
