//Pomysly czerpane z:
//https://pl.wikibooks.org/wiki/POSIX_Threads/Podstawowe_operacje

#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include <ncurses.h>
#include <string.h>


//wymiary pola rysowalnego
#define windowX 60
#define windowY 20
#define pulapki 100
#define iloscPionkow 5


struct pole{
	int status, index; // status: 0 - zwykle pole; 1- pionek; 2 - plapka; 3 - zablokowany pionek, index- nr pola
};

struct pionek{
	int x,y,index;
	bool zablokowany;
}; 

struct pole plansza[windowX][windowY];
struct pionek pionki[iloscPionkow];

//watki
pthread_t rysowanieWatek;
pthread_t pionkiWatki[iloscPionkow];
// void inicjujplansze(){
// 	for(int i=0;i<windowY;i++){
// 		for(int j=0;j<windowX;j++){
// 			plansza[i][j].status=0;
// 		}
// 	}
// }

void losujpulapki(){
	
	for(int k=0;k<pulapki;k++){
			int x =rand()%windowX;
			int y =rand()%windowY;
			if(plansza[x][y].status==0 && (x != 0 || y != 0)){
				plansza[x][y].status=2;
			}
		}
};

void umiescPionki(){
	for(int i=0;i<iloscPionkow;i++){

			int wspx =rand()%windowX;
			int wspy =rand()%windowY;

		if(plansza[wspx][wspy].status==0 && (wspx != 0 || wspy != 0)){
			pionki[i].x=wspx;
			pionki[i].y=wspy;
			plansza[wspx][wspy].status=1;
		}
	}
}



void tworzobraz(){
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE); // kolor planszy
	init_pair(2, COLOR_RED, COLOR_RED); // kolor pulapki
	init_pair(3, COLOR_GREEN, COLOR_GREEN); // kolor pionka
	init_pair(4, COLOR_BLUE, COLOR_BLUE); // kolor pionka
	int i,j; 
	for(i=0;i<windowY;i++){
		char a;
		for(j=0;j<windowX;j++){ //wszystko ncurses
			if(plansza[j][i].status==2){
				attrset(COLOR_PAIR(2));
				a='x';
				move(i+1, j+1); //kursor przesuwa
				addch(a);
				attroff(COLOR_PAIR(2));

			}else if(plansza[j][i].status==0) {
				attrset(COLOR_PAIR(1));
				a='s';
				move(i+1, j+1); //kursor przesuwa
				addch(a);
				attroff(COLOR_PAIR(1));
			}else if(plansza[j][i].status==1) {
				attrset(COLOR_PAIR(3));
				a='s';
				move(i+1, j+1); //kursor przesuwa
				addch(a);
				attroff(COLOR_PAIR(3));
			}
			else if(plansza[j][i].status==3) {
				attrset(COLOR_PAIR(4));
				a='s';
				move(i+1, j+1); //kursor przesuwa
				addch(a);
				attroff(COLOR_PAIR(4));
			}
		}
	}
	attroff(COLOR_PAIR(1));
	refresh();
};

// bool koniec=false;

void* rysuj(void* arg){
	while(true){
		tworzobraz();
	}
};

void* ruchPionka(void* arg){
	struct pionek* p = (struct pionek*)arg; //przekazany argument z watku,czyli pojedynczy pionek
	while(true){
		usleep(1000000);//czas ruchu pionka
		int kierunek = rand()%4; // kierunek ruchu, 0-gora, 1-prawo, 2-dol, 3-lewo
		//koordynaty pionka przed ruchem

		int x = p->x;
		int y = p->y;


		//ruch pionka
		if(kierunek==0){
			if (p->zablokowany!=true)//jak wolny to go, jak zablokowany to nothing happens
			{
				if(plansza[x][y-1].status == 2){ //if pulapka
					p->zablokowany=true;
					plansza[x][y-1].status = 3; // nowy status pola planszy - zablkoowany pionek
					plansza[x][y].status = 0;		// nowy status pola planszy - pustep pole
					//nowe koordynaty pionka
					p->x = x;								
		  		p->y = y-1;
				}else{//if nie pulapka
					plansza[x][y-1].status = 1; // nowy status pola planszy - pionek
			  	plansza[x][y].status = 0;		// nowy status pola planszy - pustep pole
			  	p->x = x;								
		  		p->y = y-1;
				}
			}
		}else if(kierunek==1){
			if (p->zablokowany!=true)//jak wolny to go, jak zablokowany to nothing happens
			{
				if(plansza[x+1][y].status == 2){ //if pulapka
					p->zablokowany=true;
					plansza[x+1][y].status = 3; // nowy status pola planszy - zablkoowany pionek
					plansza[x][y].status = 0;		// nowy status pola planszy - pustep pole
					//nowe koordynaty pionka
					p->x = x+1;								
		  		p->y = y;
				}else{//if nie pulapka
					plansza[x+1][y].status = 1; // nowy status pola planszy - pionek
	  			plansza[x][y].status = 0;		// nowy status pola planszy - pustep pole
			  	p->x = x+1;								
		  		p->y = y;
				}
			}
		}
			else if(kierunek==2){
				if (p->zablokowany!=true)//jak wolny to go, jak zablokowany to nothing happens
			{
				if(plansza[x][y+1].status == 2){ //if pulapka
					p->zablokowany=true;
					plansza[x][y+1].status = 3; // nowy status pola planszy - zablkoowany pionek
					plansza[x][y].status = 0;		// nowy status pola planszy - pustep pole
					//nowe koordynaty pionka
					p->x = x;								
		  		p->y = y+1;
				}else{//if nie pulapka
					plansza[x][y+1].status = 1; // nowy status pola planszy - pionek
	  			plansza[x][y].status = 0;		// nowy status pola planszy - pustep pole
			  	p->x = x;								
		  		p->y = y+1;
				}
			}
			}
			else if(kierunek==3){
				if (p->zablokowany!=true)//jak wolny to go, jak zablokowany to nothing happens
			{
				if(plansza[x-1][y].status == 2){ //if pulapka
					p->zablokowany=true;
					plansza[x-1][y].status = 3; // nowy status pola planszy - zablkoowany pionek
					plansza[x][y].status = 0;		// nowy status pola planszy - pustep pole
					//nowe koordynaty pionka
					p->x = x-1;								
		  		p->y = y;
				}else{//if nie pulapka
					plansza[x-1][y].status = 1; // nowy status pola planszy - pionek
	  			plansza[x][y].status = 0;		// nowy status pola planszy - pustep pole
			  	p->x = x-1;								
		  		p->y = y;
				}
			}
		}
	}

}


int main(void){
	srand(time(NULL)); // jakis zarodek bez tego przy kolejnym uruchomieniu programu sa te same liczby, co za patologia
	initscr(); //ncurses - startuje tryb rysowania

	losujpulapki();
	umiescPionki();
	//--------------------------watki tworzenie--------------
	pthread_create(&rysowanieWatek,NULL, rysuj, NULL); // 1. id watku, 2. atrybuty, szczegoly watku, 3. funkcja wykonywana w watku, 4. argumenty przekazywane do funkcji
	for(int i=0; i<iloscPionkow;i++){
		pthread_create(&pionkiWatki[i],NULL,ruchPionka,&pionki[i]);
	}
	//------------------koniec tworzenia watkow
	tworzobraz();


	refresh();
	sleep(51);//czeka tyle sekund na zakonczenie ncurses
	endwin(); //ncurses- konczy tryb rysowania

}