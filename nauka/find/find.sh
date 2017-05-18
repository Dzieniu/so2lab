#!/bin/bash

#1
#find $1 -user $2 -type f -perm -u+x

#2
#find $1 -name .git -mtime +30 -type d -exec dirname {} ';' 

#3
#me=`whoami`
#find . $1 -type f  -user $me -print -exec stat -c "użytkownik: %U grupa: %G uprawnienia: %A" {} ';'





# %U - username of owner, %G - group name of owner %A- uprawnienia do plików
#wyswietla katalog pliku
#find . $1 -type f -exec dirname {} ';' 