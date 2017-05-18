#!/bin/bash

#<Konrad><Dzien>
#Napisz skrypt który bedzie pełnił funkcję programu czyszczącego katalog użytkownika ze śmieci
#a) program powinien zliczyć wszystkie puste pliki i katalogi w zadanym miejscu (parametr wywołania skrytpu) należące 
#do danego użytkownika (parametr wywołania skryptu)
#b) program powinien zgłosić pliki i katalogi których zawartość nie była zmieniana od roku
#c) program powinien zaraportować wszystkie pliki których zadany użytkownik nie jest oficjalnym właścicielem (nie uwzględniami
#grupy użytkownika)
#d) program powinien zgłosić wszystkie pliki których wskazany użytkownik nie może przeczytać

if [ ! -d $1 ]; then
  echo "Parametr nie jest katalogiem"
  exit 1
fi

#a) 
echo "Wszystkie puste pliki i katalogi należące do użytkownika $2"
find $1 -user $2 -empty | wc -l

#b)
echo "pliki i katalogi nie zmieniane od roku"
find $1 -mtime +356 -print

#c)
echo "pliki których użytkownik $2 nie jest oficjalnym właścicielem"
find $1 ! -user $2 

#d)
echo "pliki których użytkownik $2 nie może przeczytać"
find $1 -user $2 ! -perm /u+r,g+r,o+r