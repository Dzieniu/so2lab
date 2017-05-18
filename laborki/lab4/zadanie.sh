#!/bin/bash
# <Konrad><Dzien>
#Skrócona treść: znaleźć ścieżki, których wszystkie elementy to palindromy


is=0
isnt=0

find $1 | (
  while read c 
  do

 #do podzielenia ścieżki nie użyłem cut tylko zmiennej tablicowej i polecenia read
 # korzystałem z tego : https://ss64.com/bash/read.html
 # a konkretniej z tej linii: " The characters in the value of the IFS variable are used to split the line into words. "
  		IFS="/" read -a tab <<< "$c"

  		for word in "${tab[@]}"
  		do
	  		if [[ $(rev <<< $word) == "$word" ]]
	  		then
	   			is=0 #niepotrzebna zmienna, nic nie wnosi, ale musiałem tu coś wpisać bo bez tego else nie zadziała
			else
				isnt=1 #jeśli jakieś słowo nie jest polindromem, ustawiamy tu 1, żeby w późniejszym ifie nie wypisywać ścieżki tylko przejść do następnej
			fi  		
  		done

# Przez tego ifa na labolatorium pokazywało źle wyniki, ponieważ był umieszony na końcu powyższej pętli
		if [ $isnt == 1 ]
		then
			isnt=0
			continue
		fi
		echo "$c"
		echo "$c" >> ścieżki

  done
)
