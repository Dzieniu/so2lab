#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include <ncurses.h>
#include <string.h>

struct pole{
	int status, index; // status: 0 - zwykle pole; 1- pionek; 2 - plapka; 3 - zablokowany pionek
};

struct pionek {
	int x, y, index;
	bool wolny;
	char znak;
};

#define winx 50
#define winy 20
#define ilosc 5
#define iloscPlap 30

struct pionek pionki[ilosc];
struct pole plansza[winx][winy];
int zablokowane = 0;
bool koniec = false;
pthread_t watki[ilosc];
pthread_t rysowanieWatek;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void rysuj()
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_WHITE); // kolor planszy
	init_pair(2, COLOR_WHITE, COLOR_GREEN); // kolor pionka
	init_pair(3, COLOR_WHITE, COLOR_RED); // kolor plapki
	init_pair(4, COLOR_RED,COLOR_BLUE); // kolor zablokowanego pionka
	int i,j;
	for(i=0; i<winy; i++)
	{
		for(j=0; j<winx; j++)
		{
			char a;
			if(plansza[j][i].status==0) // zwykle pole
			{
				attrset(COLOR_PAIR(1));
				a=' ';
				move(i+1, j+1);
				addch(a);
				attroff(COLOR_PAIR(1));
			}
			else if(plansza[j][i].status==1) // pionek
			{
				attrset(COLOR_PAIR(2));
				a = pionki[plansza[j][i].index].znak;
				move(i+1, j+1);
				addch(a);
				attroff(COLOR_PAIR(2));
			}
			else if(plansza[j][i].status==2) // plapka
			{
				attrset(COLOR_PAIR(3));
				a='X';
			  	move(i+1, j+1);
			    addch(a);
			    attroff(COLOR_PAIR(3));

			}
			else if(plansza[j][i].status==3) // zablokowany pionek
			{
				attrset(COLOR_PAIR(4));
				a = pionki[plansza[j][i].index].znak;
				move(i+1, j+1);
			    addch(a);
			    attroff(COLOR_PAIR(4));
			}
		}
	}
	attroff(COLOR_PAIR(1));
	refresh();
}

void umiescPlapki()
{
	bool k = false;
	do
	{
		k = false;
		int x = rand()%winx;
		int y = rand()%winy;
		if(plansza[x][y].status == 0 && (x != 0 || y != 0))
		{
			plansza[x][y].status = 2;
			k = true;
		}
	}while(k == false);
}

void umiesc(struct pionek* p, int i)
{
	bool k = false;
	do
	{
		k = false;
		p->x=rand()%winx;
		p->y=rand()%winy;
		int x = p->x;
		int y = p->y;
		if(plansza[x][y].status == 0)
		{
			plansza[x][y].status = 1;
			p->wolny = true;
			p->znak = '0' + i;
			p->index = i;
			plansza[x][y].index = i;
			k = true;
		}
	}while(k==false);
}

void* rysunek(void* arg){
	while(!koniec)
		rysuj();
}

void* ruch(void* arg){
	    struct pionek* p = (struct pionek*)arg;

		while(ilosc > zablokowane)
		{
			usleep(100*1000);
			int x = p->x;
			int y = p->y;
			int kierunek = rand()%4; // 0-gora 1-prawo 2-dol 3-lewo
			if(kierunek == 0) // gora
			{
				pthread_mutex_lock(&mutex);
				if((y-1>=0) && (plansza[x][y-1].status != 1) && p->wolny)
				{
					if(plansza[x][y-1].status == 2)
		        	{
		        		p->x = x;
			        	p->y = y-1;
		        		p->wolny = false;
		        		plansza[x][y-1].index = p->index;
		        		plansza[x][y-1].status = 3;
		        		plansza[x][y].status = 0;
		        		plansza[x][y].index = -1;
		        		zablokowane++;
		        	}
		        	else if(plansza[x][y-1].status == 3)
		        	{
		        		p->wolny = false;
		        		pionki[plansza[x][y-1].index].wolny = true;
		        		pionki[plansza[x][y-1].index].x = 0;
		        		pionki[plansza[x][y-1].index].y = 0;
		        		p->x = x;
			        	p->y = y-1;
			        	plansza[0][0].index = plansza[x][y-1].index;
		        		plansza[x][y-1].index = p->index;
		        		plansza[x][y].index = -1;
		        		plansza[0][0].status = 1;
		        		plansza[x][y].status = 0;
		        	}
		        	else
		        	{
						plansza[x][y-1].status = 1;
			        	plansza[x][y].status = 0;
			        	p->x = x;
			        	p->y = y-1;
			        	plansza[x][y].index = -1;
			        	plansza[x][y-1].index = p->index;
		        	}
				}
				pthread_mutex_unlock(&mutex);
			}
			else if(kierunek == 1) // prawo
			{
				pthread_mutex_lock(&mutex);
		        if((x+1<winx) && plansza[x+1][y].status != 1 && p->wolny)
		        {
		        	if(plansza[x+1][y].status == 2)
		        	{
		        		p->x = x+1;
			        	p->y = y;
		        		p->wolny = false;
		        		plansza[x+1][y].index = p->index;
		        		plansza[x+1][y].status = 3;
		        		plansza[x][y].status = 0;
		        		plansza[x][y].index = -1;
		        		zablokowane++;
		        	}
		        	else if(plansza[x+1][y].status == 3)
		        	{
		        		p->wolny = false;
		        		pionki[plansza[x+1][y].index].wolny = true;
		        		pionki[plansza[x+1][y].index].x = 0;
		        		pionki[plansza[x+1][y].index].y = 0;
		        		p->x = x+1;
			        	p->y = y;
			        	plansza[0][0].index = plansza[x+1][y].index;
		        		plansza[x+1][y].index = p->index;
		        		plansza[x][y].index = -1;
		        		plansza[0][0].status = 1;
		        		plansza[x][y].status = 0;
		        	}
		        	else
		        	{
			        	plansza[x+1][y].status = 1;
			        	plansza[x][y].status = 0;
			        	p->x = x+1;
			        	p->y = y;
			        	plansza[x][y].index = -1;
			        	plansza[x+1][y].index = p->index;
		        	}
		        }
				pthread_mutex_unlock(&mutex);
			}
			else if(kierunek==2) // dol
			{
				pthread_mutex_lock(&mutex);
				if((y+1<winy) && (plansza[x][y+1].status != 1) && p->wolny)
				{
					if(plansza[x][y+1].status == 2)
		        	{
		        		p->x = x;
			        	p->y = y+1;
		        		p->wolny = false;
		        		plansza[x][y+1].index = p->index;
		        		plansza[x][y+1].status = 3;
		        		plansza[x][y].status = 0;
		        		plansza[x][y].index = -1;
		        		zablokowane++;
		        	}
		        	else if(plansza[x][y+1].status == 3)
		        	{
		        		p->wolny = false;
		        		pionki[plansza[x][y+1].index].wolny = true;
		        		pionki[plansza[x][y+1].index].x = 0;
		        		pionki[plansza[x][y+1].index].y = 0;
		        		p->x = x;
			        	p->y = y+1;
			        	plansza[0][0].index = plansza[x][y+1].index;
		        		plansza[x][y+1].index = p->index;
		        		plansza[x][y].index = -1;
		        		plansza[0][0].status = 1;
		        		plansza[x][y].status = 0;
		        	}
		        	else
		        	{
						plansza[x][y+1].status = 1;
			        	plansza[x][y].status = 0;
			        	p->x = x;
			        	p->y = y+1;
			        	plansza[x][y].index = -1;
			        	plansza[x][y+1].index = p->index;
			        }
				}
				pthread_mutex_unlock(&mutex);
			}
			else if(kierunek == 3) // lewo
			{
				pthread_mutex_lock(&mutex);
		        if((x-1>=0) && plansza[x-1][y].status != 1 && p->wolny)
		        {
		        	if(plansza[x-1][y].status == 2)
		        	{
		        		p->x = x-1;
			        	p->y = y;
		        		p->wolny = false;
		        		plansza[x-1][y].index = p->index;
		        		plansza[x-1][y].status = 3;
		        		plansza[x][y].status = 0;
		        		plansza[x][y].index = -1;
		        		zablokowane++;
		        	}
		        	else if(plansza[x-1][y].status == 3)
		        	{
		        		p->wolny = false;
		        		pionki[plansza[x-1][y].index].wolny = true;
		        		pionki[plansza[x-1][y].index].x = 0;
		        		pionki[plansza[x-1][y].index].y = 0;
		        		p->x = x-1;
			        	p->y = y;
			        	plansza[0][0].index = plansza[x-1][y].index;
		        		plansza[x-1][y].index = p->index;
		        		plansza[x][y].index = -1;
		        		plansza[0][0].status = 1;
		        		plansza[x][y].status = 0;
		        	}
		        	else
		        	{
			        	plansza[x-1][y].status = 1;
			        	plansza[x][y].status = 0;
			        	p->x = x-1;
			        	p->y = y;
			        	plansza[x][y].index = -1;
			        	plansza[x-1][y].index = p->index;
		        	}
		        }
				pthread_mutex_unlock(&mutex);
			}
		}
		usleep(500*100);
		koniec = true;
		return NULL;
}

int main(void) {
	initscr();
	curs_set(0);
	srand(time(NULL));
	int i,row, col;
	char tekst[] = "Wszystkie pionki zostaly zablokowane";
	char tekst1[] = "KONIEC";
	for(i=0; i<iloscPlap; i++)
	{
		umiescPlapki();
	}
	for(i=0;i<ilosc;i++)
	{
		umiesc(&pionki[i], i);
	}
	pthread_create(&rysowanieWatek, NULL, rysunek, NULL);
	for(i=0;i<ilosc;i++)
	{
		pthread_create(&watki[i], NULL, ruch, &pionki[i]);
	}
	pthread_join(rysowanieWatek, NULL);
	for (i=0; i < ilosc; i++)
	{
        pthread_join(watki[i], NULL);
	}
	refresh();
	getmaxyx(stdscr,row,col);
	mvprintw(row/2,(col-strlen(tekst))/2,"%s",tekst);
	mvprintw(row/2+1,(col-strlen(tekst1))/2,"%s",tekst1);
    refresh();
    sleep(5);
	endwin();
	pthread_mutex_destroy(&mutex);
	return EXIT_SUCCESS;
}