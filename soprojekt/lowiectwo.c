#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include <ncurses.h>
#include <string.h>


//wymiary pola rysowalnego
#define windowX 60
#define windowY 20
#define pulapki 20
#define iloscPionkow 5


struct pole{
	int status, index; // status: 0 - zwykle pole; 1- pionek; 2 - plapka; 3 - zablokowany pionek, index- nr pola
};

struct pionek{
	int x,y,index;
}; 

struct pole plansza[windowX][windowY];
struct pionek pionki[iloscPionkow];

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



void rysuj(){
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE); // kolor planszy
	init_pair(2, COLOR_RED, COLOR_RED); // kolor pulapki
	init_pair(3, COLOR_GREEN, COLOR_GREEN); // kolor pionka
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
		}
	}
	attroff(COLOR_PAIR(1));
	refresh();
};


int main(void){
srand(time(NULL)); // jakis zarodek bez tego przy kolejnym uruchomieniu programu sa te same liczby, co za patologia
	initscr(); //ncurses - startuje tryb rysowania
	losujpulapki();
	umiescPionki();
	rysuj();


	refresh();
	sleep(51);
	endwin(); //ncurses- konczy tryb rysowania

}