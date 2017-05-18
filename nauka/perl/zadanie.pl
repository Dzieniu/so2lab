#!/usr/bin/perl 
#<Konrad><Dzień>
#Napisz skrypt, który przeniesie wsyzstkie pliki zwyczajne z danego katalogu źródłowego
# do wskazanego katalogu docelowego ( parametr wywołania skryptu). 
#Jeśli docelowym miejscu istnieje już plik o tejs amej nazwie, pomiajmy przenoszenie

use File::Copy;

opendir(DIR, "@ARGV[0]");

for $_ (readdir DIR){
	if ( -f $_ ){
		$path = "@ARGV[1]/$_";
		if (! -e $path ){
			move("@ARGV[0]/$_", "@ARGV[1]/$_");
		}	
	}
	
}