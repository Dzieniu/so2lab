#!/usr/bin/perl 

# open(PLIK, "@ARGV[0]");

# for (<PLIK>){
# 	print;
# }
use File::Copy;

opendir(DIR, "@ARGV[0]");

for $_ (readdir DIR){
	if ( -f $_ ){
		$path = "@ARGV[1]/$_";
		print "$path";
		if ( -e $path ){
			move("@ARGV[0]/$_", "@ARGV[1]/$_") or die "Copy failed: $!";
		}	
	}
	
}