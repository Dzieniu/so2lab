#!/usr/bin/perl 

use File::Find;

$dir = @ARGV[0];
$time = 300; #5 minut
find(\&search, $dir);

sub search{

	$last = (time() - (stat($_))[9]) ;
	if(-l $_ && $last>$time && -r $_ && -f $_){
		print "$_ - $last\n";
	}
}