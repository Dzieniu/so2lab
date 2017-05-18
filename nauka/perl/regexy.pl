#!/usr/bin/perl 
use strict;
use warnings;

my $filename = "$ARGV[0]";

open(my $fh, '<', $filename);

LINE: while ( my $row = <$fh>){
	chomp $row;
	my @words = split /-/, $row;
	foreach (@words){
		my $currentword = $_;
		next LINE if (!($currentword =~ s/^[1-9]{3}$//));
		
	}
	print "$row \n"
}