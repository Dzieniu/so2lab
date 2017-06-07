#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include <ncurses.h>
#include <string.h>


//wymiary pola rysowalnego
#define windowX 60
#define windowY 20

struct pole{
	int index, status // status: 0 - zwykle pole; 1- pionek; 2 - plapka; 3 - zablokowany pionek, index- nr pola
};

void rysuj(){
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE); // kolor planszy
	int i,j; 
	for(i=0;i<windowY;i++){
		char a;
		for(j=0;j<windowX;j++){
			attrset(COLOR_PAIR(1));
			a='s';
			move(i+1, j+1);
			addch(a);
			attroff(COLOR_PAIR(1));
		}
	}
}


int main(void){
	initscr(); //ncurses - startuje tryb rysowania
	rysuj();

	refresh();
	sleep(5);
	endwin(); //ncurses- konczy tryb rysowania

}