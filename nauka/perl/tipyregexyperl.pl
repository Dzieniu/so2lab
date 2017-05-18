#Dzielenie stringa na czesci:

$string= "Ala:miała:kota";

@words = split /:/, $string;

foreach (@words){
	print "$_ \n";	
}

