#!/usr/bin/perl 
#plik 6 - core_filter - odnaleźć definicje funkcji

#!/usr/bin/perl 
use strict;
use warnings;

my $filename = "$ARGV[0]";

open(my $fh, '<', $filename);

LINE: while ( my $row = <$fh>){
	#my @words = split /-/, $row;
	my $currentrow = $row;	
	next LINE if (!($currentrow =~ s/^(?!\s+#).*def.*$//));
	print "$row ";
}