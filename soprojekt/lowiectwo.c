#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include <ncurses.h>
#include <string.h>


//wymiary pola rysowalnego
#define windowX 60
#define windowY 20
#define pulapki 20

struct pole{
	int status, index; // status: 0 - zwykle pole; 1- pionek; 2 - plapka; 3 - zablokowany pionek, index- nr pola
};

struct pole plansza[windowX][windowY];

// void inicjujplansze(){
// 	for(int i=0;i<windowY;i++){
// 		for(int j=0;j<windowX;j++){
// 			plansza[i][j].status=0;
// 		}
// 	}
// }

void losujpulapki(){
	srand(time(NULL)); // jakis zarodek bez tego przy kolejnym uruchomieniu programu sa te same liczby, co za patologia
	for(int k=0;k<pulapki;k++){
			int x =rand()%windowX;
			int y =rand()%windowY;
			if(plansza[x][y].status==0 && (x != 0 || y != 0)){
				plansza[x][y].status=2;
			}
		}
};



void rysuj(){
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE); // kolor planszy
	init_pair(2, COLOR_RED, COLOR_RED); // kolor pulapki
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

			}else{
				attrset(COLOR_PAIR(1));
				a='s';
				move(i+1, j+1); //kursor przesuwa
				addch(a);
				attroff(COLOR_PAIR(1));
			}
		}
	}
	attroff(COLOR_PAIR(1));
	refresh();
};


int main(void){
	initscr(); //ncurses - startuje tryb rysowania
	losujpulapki();
	rysuj();


	refresh();
	sleep(51);
	endwin(); //ncurses- konczy tryb rysowania

}