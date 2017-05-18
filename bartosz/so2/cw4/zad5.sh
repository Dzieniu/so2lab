#!/bin/sh

# W zadanym drzewie katalogów znaleźć 5
# najczęściej występujących nazw plików regularnych

find $1 (
  while read c 
  do
    echo "$c"
  done
)