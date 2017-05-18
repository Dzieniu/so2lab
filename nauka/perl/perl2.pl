#!/usr/bin/perl 
#<Konrad><Dzien>
#Wyszukaj pliki w danym katalogu oraz wszystkich jego podkatalogach, które
#są dowiązaniem symbolicznym do pliku zwykłego, który można przeczytać, a czas
#modyfikacji nie jest większy niż pare minut

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