/*BAGH-CHAAL

This program was written to play with keyboard.

Then later was adjusted to play with mouse..

Moreover Code Redundancy is present here ....

So might not be optimized...

But works nonetheless...

Built as a beginner college project */


#include <graphics.h>
#include <process.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <iostream.h>


//Mouse 
union REGS in,out;
void showmouse()
{
union REGS in ,out;
in.x.ax=1;
int86(0x33,&in,&out);
}


void mouseinfo(int*button,int*xpos,int*ypos)
{
union REGS in ,out;
in.x.ax=3;

int86(0x33,&in,&out);
*xpos=out.x.cx;
*ypos=out.x.dx;
*button=out.x.bx;
}



int xpos,ypos,button;



void draw_line(int,int,int,int);	 //draws a line
void draw_circle(int,int,int,int);    //draws a circle
void draw_goat(int,int);    //draws goat
void draw_tiger(int,int);   //draws tiger
void draw_board(char[],int,int);    //draws Game Board
void check_pos(int,int*);         //converts user input(11,22,43,etc) to actual pos (0-24)
void get_coordinate(int,int*,int*); //gets coordinate for tiger and goat to draw
int num_of_paths(int,int); //Checks whether there exists a path between two coordinates
int goat_win_condition(char[]);     //checks winning condition
void game();             //function for running the game
void displaygoat_win_condition();   //display if goat wins
char* move_goat(int*,char[],int);
char* move_tiger(int,char[],int*);
void displaytiger_win_condition();  //display if tiger wins
int conversion_pos(int);   //converts actual pos to user input


//Grid
const int path[25][25]={  {0,1,2,0,0,1,1,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
			  {1,0,1,2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
			  {2,1,0,1,2,0,1,1,1,0,2,0,2,0,2,0,0,0,0,0,0,0,0,0,0},
			  {0,2,1,0,1,0,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
			  {0,0,2,1,0,0,0,0,1,1,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0},
			  {1,0,0,0,0,0,1,2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
			  {1,1,1,0,0,1,0,1,2,0,1,1,1,0,0,0,2,0,2,0,0,0,0,0,0},
			  {0,0,1,0,0,2,1,0,1,2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0},
			  {0,0,1,1,1,0,2,1,0,1,0,0,1,1,1,0,2,0,2,0,0,0,0,0,0},
			  {0,0,0,0,1,0,0,2,1,0,0,0,0,0,1,0,0,0,0,2,0,0,0,0,0},
			  {2,0,2,0,0,1,1,0,0,0,0,1,2,0,0,1,1,0,0,0,2,0,2,0,0},
			  {0,2,0,0,0,0,1,0,0,0,1,0,1,2,0,0,1,0,0,0,0,2,0,0,0},
			  {2,0,2,0,2,0,1,1,1,0,2,1,0,1,2,0,1,1,1,0,2,0,2,0,2},
			  {0,0,0,2,0,0,0,0,1,0,0,2,1,0,1,0,0,0,1,0,0,0,0,2,0},
			  {0,0,2,0,2,0,0,0,1,1,0,0,2,1,0,0,0,0,1,1,0,0,2,0,2},
			  {0,0,0,0,0,2,0,0,0,0,1,0,0,0,0,0,1,2,0,0,1,0,0,0,0},
			  {0,0,0,0,0,0,2,0,2,0,1,1,1,0,0,1,0,1,2,0,1,1,1,0,0},
			  {0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,2,1,0,1,2,0,0,1,0,0},
			  {0,0,0,0,0,0,2,0,2,0,0,0,1,1,1,0,2,1,0,1,0,0,1,1,1},
			  {0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,2,1,0,0,0,0,0,1},
			  {0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,1,1,0,0,0,0,1,2,0,0},
			  {0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,0,1,0,1,2,0},
			  {0,0,0,0,0,0,0,0,0,0,2,0,2,0,2,0,1,1,1,0,2,1,0,1,2},
			  {0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,2,1,0,1},
			  {0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,1,1,0,0,2,1,0}};


void main()
{
   int gd= DETECT, gm,x1=200,y1=220,x=200,y=220;


   char play;

   initgraph(&gd, &gm, "C:\\TC\\BGI");
     sleep(1);


       setbkcolor(BLACK);
   setcolor(7);
   settextstyle(10,0,2);
   outtextxy(200,150,"LOADING.....");
  while(x1<=390)
  {
  setfillstyle(9,7);
   delay(25);
   bar(x,y,x1,y1);
   bar(x,y+2,x1,y1+2);
   bar(x,y+3,x1,y1+3);
   bar(x,y+4,x1,y1+4);
   bar(x,y+5,x1,y1+5);
   bar(x,y+6,x1,y1+6);
   x=x+1,x1=x1+2;
   }
   sleep(1);
   cleardevice();



    setcolor(WHITE);
   settextstyle(0,0,1);

    game();
   while(1)
   {
	clrscr();
	cleardevice();
	game();

   }

}

int conversion_pos(int arr)
{
	int pos,k1,k2;

	if(arr>=0 && arr<=4)
	{
		k1=1;
		k2=arr+1;
	} else if(arr>=5 && arr<=9)
	{
		k1=2;
		k2=arr-4;
	} else if(arr>=10 && arr<=14)
	{
		k1=3;
		k2=arr-9;
	} else if(arr>=15 && arr<=19)
	{
		k1=4;
		k2=arr-14;
	} else if(arr>=20 && arr<=24)
	{
		k1=5;
		k2=arr-19;
	}

	pos = k1*10 + k2;

	return pos;
}

char* move_tiger(int goat_num,char animal_pos[25],int* dead_goat)
{
	int a1,a2,b1,b2,c,c2,c1,loc1,loc2,y,z,tigerSelect,tigerShift;
	while(1)
	{ setcolor(WHITE);
	outtextxy(480,50,"Select tiger:");
	outtextxy(480,70,"(Right Click)");
	//mouse infos 
	while(1)
	   { mouseinfo(&button,&xpos,&ypos);
	 if(xpos>40&&xpos<60&&ypos>40&&ypos<60)if(2==button)
	{
	loc1=11;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>40&&ypos<60)if(2==button)
	{loc1=12;
	break;
	}if(xpos>240&&xpos<260&&ypos>40&&ypos<60)if(2==button)
	{loc1=13;
	break;
	}if(xpos>340&&xpos<360&&ypos>40&&ypos<60)if(2==button)
	{loc1=14;
	break;
	}if(xpos>440&&xpos<460&&ypos>40&&ypos<60)if(2==button)
	{loc1=15;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>140&&ypos<160)if(2==button)
	{loc1=21;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>140&&ypos<160)if(2==button)
	{loc1=22;
	break;
	}if(xpos>240&&xpos<260&&ypos>140&&ypos<160)if(2==button)
	{loc1=23;
	break;
	}if(xpos>340&&xpos<360&&ypos>140&&ypos<160)if(2==button)
	{loc1=24;
	break;
	}if(xpos>440&&xpos<460&&ypos>140&&ypos<160)if(2==button)
	{loc1=25;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>240&&ypos<260)if(2==button)
	{loc1=31;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>240&&ypos<260)if(2==button)
	{loc1=32;
	break;
	}if(xpos>240&&xpos<260&&ypos>240&&ypos<260)if(2==button)
	{loc1=33;
	break;
	}if(xpos>340&&xpos<360&&ypos>240&&ypos<260)if(2==button)
	{loc1=34;
	break;
	}if(xpos>440&&xpos<460&&ypos>240&&ypos<260)if(2==button)
	{loc1=35;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>340&&ypos<360)if(2==button)
	{loc1=41;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>340&&ypos<360)if(2==button)
	{loc1=42;
	break;
	}if(xpos>240&&xpos<260&&ypos>340&&ypos<360)if(2==button)
	{loc1=43;
	break;
	}if(xpos>340&&xpos<360&&ypos>340&&ypos<360)if(2==button)
	{loc1=44;
	break;
	}if(xpos>440&&xpos<460&&ypos>340&&ypos<360)if(2==button)
	{loc1=45;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>440&&ypos<460)if(2==button)
	{loc1=51;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>440&&ypos<460)if(2==button)
	{loc1=52;
	break;
	}if(xpos>240&&xpos<260&&ypos>440&&ypos<460)if(2==button)
	{loc1=53;
	break;
	}if(xpos>340&&xpos<360&&ypos>440&&ypos<460)if(2==button)
	{loc1=54;
	break;
	}if(xpos>440&&xpos<460&&ypos>440&&ypos<460)if(2==button)
	{loc1=55;
	break;
	}
	   if(xpos>617&&xpos<637&&ypos>2&&ypos<22)if(1==button)
	{
	exit(1);

	}
}
	showmouse();
	check_pos(loc1,&tigerSelect);
	if(animal_pos[tigerSelect]=='T')
	{
		{
			outtextxy(480,90,"Place tiger");
			 outtextxy(480,110,"(Left Click)");
				while(1)
	{mouseinfo(&button,&xpos,&ypos);

	 if(xpos>40&&xpos<60&&ypos>40&&ypos<60)if(1==button)
	{
	loc2=11;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>40&&ypos<60)if(1==button)
	{
	loc2=12;
	break;
	}if(xpos>240&&xpos<260&&ypos>40&&ypos<60)if(1==button)
	{loc2=13;
	break;
	}if(xpos>340&&xpos<360&&ypos>40&&ypos<60)if(1==button&1)
	{loc2=14;
	break;
	}if(xpos>440&&xpos<460&&ypos>40&&ypos<60)if(1==button&1)
	{loc2=15;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=21;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=22;
	break;
	}if(xpos>240&&xpos<260&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=23;
	break;
	}if(xpos>340&&xpos<360&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=24;
	break;
	}if(xpos>440&&xpos<460&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=25;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=31;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=32;
	break;
	}if(xpos>240&&xpos<260&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=33;
	break;
	}if(xpos>340&&xpos<360&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=34;
	break;
	}if(xpos>440&&xpos<460&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=35;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=41;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=42;
	break;
	}if(xpos>240&&xpos<260&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=43;
	break;
	}if(xpos>340&&xpos<360&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=44;
	break;
	}if(xpos>440&&xpos<460&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=45;
	break;
	}
		if(xpos>40&&xpos<60&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=51;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=52;
	break;
	}if(xpos>240&&xpos<260&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=53;
	break;
	}if(xpos>340&&xpos<360&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=54;
	break;
	}if(xpos>440&&xpos<460&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=55;
	break;
	}   if(xpos>617&&xpos<637&&ypos>2&&ypos<22)if(1==button)
	{
	exit(1);

	}
	}
	showmouse();

			check_pos(loc2,&tigerShift);


		       z=num_of_paths(loc1,loc2);

			if(z==1)
			{
				if(animal_pos[tigerShift]=='X')
				{


				animal_pos[tigerSelect]='X';
				animal_pos[tigerShift]='T';
				clrscr();
				cleardevice();
				draw_board(animal_pos,goat_num,*dead_goat);
				break;
				}
				else
				{ setcolor(RED);
				outtextxy(480,130,"There's something!!");
				setcolor(WHITE);
				sleep(2);
				clrscr();
				cleardevice();
				draw_board(animal_pos,goat_num,*dead_goat);
				}
			}
			else if(z==2)
			{
				a1=(int)loc1/10;
				a2=(int)loc1%10;
				b1=(int)loc2/10;
				b2=(int)loc2%10;

				if(a1==b1)
				{
					c1=a1;
					if(a2>b2)
					{
						c2=a2-1;
					}
					else
					{
						c2=a2+1;
					}
				}
				else if(a2==b2)
				{
					c2=a2;
					if(a1>b1)
					{
						c1=a1-1;
					}
					else
					{
						c1=a1+1;
					}
				}
				else
				{
					if(a1>b1 && a2>b2)
					{
						c1=a1-1;
						c2=a2-1;
					}
					else if(a1>b1 && a2<b2)
					{
						c1=a1-1;
						c2=a2+1;
					} else if(a1<b1 && a2<b2)
					{
						c1=a1+1;
						c2=a2+1;
					}
					else
					{
						c1=a1+1;
						c2=a2-1;
					}
				}

				c = (c1 * 10) + c2;

				check_pos(c,&y);

				if((animal_pos[y]=='G') && (animal_pos[tigerShift]=='X'))
				{
				animal_pos[y]='X';
				(*dead_goat)++;

				animal_pos[tigerSelect]='X';
				animal_pos[tigerShift]='T';
				clrscr();
				cleardevice();
				draw_board(animal_pos,goat_num,*dead_goat);
				break;
				}
				else
				{ setcolor(RED);
				outtextxy(480,130,"Invalid!!");
				setcolor(WHITE);
				sleep(2);
				clrscr();
				cleardevice();
				draw_board(animal_pos,goat_num,*dead_goat);

				}
			}
			else
			{
			       setcolor(RED);
			       outtextxy(480,130,"Invalid position!!");
			       setcolor(WHITE);
				sleep(2);
				clrscr();
				cleardevice();
				draw_board(animal_pos,goat_num,*dead_goat);
			}

		}
	}
	else
	{ setcolor(RED);
	outtextxy(480,90,"No tiger there!!");
	setcolor(WHITE);
	sleep(2);
	clrscr();
	cleardevice();
	draw_board(animal_pos,goat_num,*dead_goat);
	}
	}

	return animal_pos;
}

char* move_goat(int* goat_num, char animal_pos[25],int dead_goat)
{
int loc,x,z,loc1,loc2,goatSelect,goatShift;


if( (*goat_num) < 20 )
{
	while(1)
	{
	clrscr();
	cleardevice();
	draw_board(animal_pos,*goat_num,dead_goat);
	setcolor(WHITE);
	outtextxy(480,50,"PLACE GOAT:");
	outtextxy(480,70,"(Left click)");

	while(1)
	{mouseinfo(&button,&xpos,&ypos);
	 if(xpos>40&&xpos<60&&ypos>40&&ypos<60)if(1==button&1)
	{loc=11;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>40&&ypos<60)if(1==button&1)
	{loc=12;
	break;
	}if(xpos>240&&xpos<260&&ypos>40&&ypos<60)if(1==button&1)
	{loc=13;
	break;
	}if(xpos>340&&xpos<360&&ypos>40&&ypos<60)if(1==button&1)
	{loc=14;
	break;
	}if(xpos>440&&xpos<460&&ypos>40&&ypos<60)if(1==button&1)
	{loc=15;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>140&&ypos<160)if(1==button&1)
	{loc=21;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>140&&ypos<160)if(1==button&1)
	{loc=22;
	break;
	}if(xpos>240&&xpos<260&&ypos>140&&ypos<160)if(1==button&1)
	{loc=23;
	break;
	}if(xpos>340&&xpos<360&&ypos>140&&ypos<160)if(1==button&1)
	{loc=24;
	break;
	}if(xpos>440&&xpos<460&&ypos>140&&ypos<160)if(1==button&1)
	{loc=25;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>240&&ypos<260)if(1==button&1)
	{loc=31;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>240&&ypos<260)if(1==button&1)
	{loc=32;
	break;
	}if(xpos>240&&xpos<260&&ypos>240&&ypos<260)if(1==button&1)
	{loc=33;
	break;
	}if(xpos>340&&xpos<360&&ypos>240&&ypos<260)if(1==button&1)
	{loc=34;
	break;
	}if(xpos>440&&xpos<460&&ypos>240&&ypos<260)if(1==button&1)
	{loc=35;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>340&&ypos<360)if(1==button&1)
	{loc=41;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>340&&ypos<360)if(1==button&1)
	{loc=42;
	break;
	}if(xpos>240&&xpos<260&&ypos>340&&ypos<360)if(1==button&1)
	{loc=43;
	break;
	}if(xpos>340&&xpos<360&&ypos>340&&ypos<360)if(1==button&1)
	{loc=44;
	break;
	}if(xpos>440&&xpos<460&&ypos>340&&ypos<360)if(1==button&1)
	{loc=45;
	break;
	}
		if(xpos>40&&xpos<60&&ypos>440&&ypos<460)if(1==button&1)
	{loc=51;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>440&&ypos<460)if(1==button&1)
	{loc=52;
	break;
	}if(xpos>240&&xpos<260&&ypos>440&&ypos<460)if(1==button&1)
	{loc=53;
	break;
	}if(xpos>340&&xpos<360&&ypos>440&&ypos<460)if(1==button&1)
	{loc=54;
	break;
	}if(xpos>440&&xpos<460&&ypos>440&&ypos<460)if(1==button&1)
	{loc=55;
	break;
	}    if(xpos>617&&xpos<637&&ypos>2&&ypos<22)if(1==button)
	{
	exit(1);

	}

	}
	   showmouse();
	   check_pos(loc,&x);

	if(animal_pos[x]=='X')
	{   clrscr();
	    cleardevice();
	    animal_pos[x]='G';
	    (*goat_num)++;
	    draw_board(animal_pos,*goat_num,dead_goat);
	    return animal_pos;
	}
	else
	{        setcolor(RED);
		outtextxy(480,90,"There's something!!");
		setcolor(WHITE);
		sleep(2);
	}
 }
}

else
	{
	while(1)
	{
	clrscr();
	cleardevice();
	draw_board(animal_pos,*goat_num,dead_goat);
	setcolor(WHITE);
	outtextxy(480,50,"Select goat:");
	outtextxy(480,70,"(Right Click)");
       while (1)	{ mouseinfo(&button,&xpos,&ypos);
	 if(xpos>40&&xpos<60&&ypos>40&&ypos<60)if(2==button)
	{
	loc1=11;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>40&&ypos<60)if(2==button)
	{loc1=12;
	break;
	}if(xpos>240&&xpos<260&&ypos>40&&ypos<60)if(2==button)
	{loc1=13;
	break;
	}if(xpos>340&&xpos<360&&ypos>40&&ypos<60)if(2==button)
	{loc1=14;
	break;
	}if(xpos>440&&xpos<460&&ypos>40&&ypos<60)if(2==button)
	{loc1=15;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>140&&ypos<160)if(2==button)
	{loc1=21;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>140&&ypos<160)if(2==button)
	{loc1=22;
	break;
	}if(xpos>240&&xpos<260&&ypos>140&&ypos<160)if(2==button)
	{loc1=23;
	break;
	}if(xpos>340&&xpos<360&&ypos>140&&ypos<160)if(2==button)
	{loc1=24;
	break;
	}if(xpos>440&&xpos<460&&ypos>140&&ypos<160)if(2==button)
	{loc1=25;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>240&&ypos<260)if(2==button)
	{loc1=31;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>240&&ypos<260)if(2==button)
	{loc1=32;
	break;
	}if(xpos>240&&xpos<260&&ypos>240&&ypos<260)if(2==button)
	{loc1=33;
	break;
	}if(xpos>340&&xpos<360&&ypos>240&&ypos<260)if(2==button)
	{loc1=34;
	break;
	}if(xpos>440&&xpos<460&&ypos>240&&ypos<260)if(2==button)
	{loc1=35;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>340&&ypos<360)if(2==button)
	{loc1=41;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>340&&ypos<360)if(2==button)
	{loc1=42;
	break;
	}if(xpos>240&&xpos<260&&ypos>340&&ypos<360)if(2==button)
	{loc1=43;
	break;
	}if(xpos>340&&xpos<360&&ypos>340&&ypos<360)if(2==button)
	{loc1=44;
	break;
	}if(xpos>440&&xpos<460&&ypos>340&&ypos<360)if(2==button)
	{loc1=45;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>440&&ypos<460)if(2==button)
	{loc1=51;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>440&&ypos<460)if(2==button)
	{loc1=52;
	break;
	}if(xpos>240&&xpos<260&&ypos>440&&ypos<460)if(2==button)
	{loc1=53;
	break;
	}if(xpos>340&&xpos<360&&ypos>440&&ypos<460)if(2==button)
	{loc1=54;
	break;
	}if(xpos>440&&xpos<460&&ypos>440&&ypos<460)if(2==button)
	{loc1=55;
	break;
	}
	   if(xpos>617&&xpos<637&&ypos>2&&ypos<22)if(1==button)
	{
	exit(1);

	}
	} showmouse();
	check_pos(loc1,&goatSelect);
	if(animal_pos[goatSelect]=='G')
	{
			    setcolor(WHITE);
			outtextxy(480,90,"PLACE GOAT");
			outtextxy(480,110,"(Left Click)");
			while(1)
	{mouseinfo(&button,&xpos,&ypos);

	 if(xpos>40&&xpos<60&&ypos>40&&ypos<60)if(1==button)
	{
	loc2=11;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>40&&ypos<60)if(1==button)
	{
	loc2=12;
	break;
	}if(xpos>240&&xpos<260&&ypos>40&&ypos<60)if(1==button)
	{loc2=13;
	break;
	}if(xpos>340&&xpos<360&&ypos>40&&ypos<60)if(1==button&1)
	{loc2=14;
	break;
	}if(xpos>440&&xpos<460&&ypos>40&&ypos<60)if(1==button&1)
	{loc2=15;

	break;
	}
	if(xpos>40&&xpos<60&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=21;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=22;
	break;
	}if(xpos>240&&xpos<260&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=23;
	break;
	}if(xpos>340&&xpos<360&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=24;
	break;
	}if(xpos>440&&xpos<460&&ypos>140&&ypos<160)if(1==button&1)
	{loc2=25;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=31;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=32;
	break;
	}if(xpos>240&&xpos<260&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=33;
	break;
	}if(xpos>340&&xpos<360&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=34;
	break;
	}if(xpos>440&&xpos<460&&ypos>240&&ypos<260)if(1==button&1)
	{loc2=35;
	break;
	}
	if(xpos>40&&xpos<60&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=41;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=42;
	break;
	}if(xpos>240&&xpos<260&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=43;
	break;
	}if(xpos>340&&xpos<360&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=44;
	break;
	}if(xpos>440&&xpos<460&&ypos>340&&ypos<360)if(1==button&1)
	{loc2=45;
	break;
	}
		if(xpos>40&&xpos<60&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=51;
	break;
	}
	if(xpos>140&&xpos<160&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=52;
	break;
	}if(xpos>240&&xpos<260&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=53;
	break;
	}if(xpos>340&&xpos<360&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=54;
	break;
	}if(xpos>440&&xpos<460&&ypos>440&&ypos<460)if(1==button&1)
	{loc2=55;
	break;
	}
	   if(xpos>617&&xpos<637&&ypos>2&&ypos<22)if(1==button)
	{
	exit(1);

	}
	}
	showmouse();

			check_pos(loc2,&goatShift);
			z=num_of_paths(loc1,loc2);

			if(z==1)
			{
				if(animal_pos[goatShift]=='X')
				{
					animal_pos[goatSelect]='X';
					animal_pos[goatShift]='G';
					clrscr();
					cleardevice();
					draw_board(animal_pos,*goat_num,dead_goat);
					return animal_pos;
				}
				else
				{setcolor(RED);
				outtextxy(480,130,"There's something!!");
				setcolor(WHITE);
				sleep(2);
				cleardevice();
				draw_board(animal_pos,*goat_num,dead_goat);
				}
			}
			else
			{                    setcolor(RED);
				outtextxy(480,130,"Invalid position!!");
				setcolor(WHITE);
				 sleep(2);
				cleardevice();
				draw_board(animal_pos,*goat_num,dead_goat);
			}



	}
	else
	{ setcolor(RED);
	outtextxy(480,110,"No goat there!!");
	setcolor(WHITE);
	sleep(2);
	clrscr();
	cleardevice();
	draw_board(animal_pos,*goat_num,dead_goat);
	}
	}
	}



}

void displaygoat_win_condition()
{
	clrscr();
	cleardevice();
	setbkcolor(BLACK);
	setcolor(3);
	settextstyle(10,0,5);
	outtextxy(getmaxx()/2-280,getmaxy()/2-125,"GOAT WINS!!");
	 sleep(2);


}
void main_menu()
{
setcolor(14);
settextstyle(0,0,5);
	outtextxy(170,50,"BAGH-CHAL");
  setcolor(GREEN);

	rectangle(80,180,350,240);
	settextstyle(0,0,3);
	outtextxy(96,200,"1.New Game");
	rectangle(80,270,450,330);
	settextstyle(0,0,3);
	outtextxy(96,290,"2.Instructions");
	rectangle(80,360,300,420);
	settextstyle(0,0,3);
	outtextxy(96,380,"3.Exit");
	}

void game()
{
   int choose,i,dead_goat=0,goat_num=0;
   char play;
   char* pos;
   char animal_pos[25]={'T','X','X','X','T','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','T','X','X','X','T'};

   while(1)
   {
    clrscr();
     cleardevice();

	  main_menu();

  showmouse();
  while(1)
  { mouseinfo(&button,&xpos,&ypos);
	 if(xpos>80&&xpos<350&&ypos>180&&ypos<240)if(1==button&1)
	{choose=1;
	break;
	} if(xpos>80&&xpos<450&&ypos>270&&ypos<330)if(1==button&1)
	{choose=2;
	break;
	}if(xpos>80&&xpos<300&&ypos>360&&ypos<420)if(1==button&1)
	{choose=3;
	break;
	} }
   settextstyle(0,0,1);
   sleep(1);

   switch(choose)
   {

   case 1:
   setbkcolor(BLUE);
   showmouse();
    while(dead_goat<5)
   {

	pos=move_goat(&goat_num,animal_pos,dead_goat);

	for(i=0;i<25;i++)
	{
		animal_pos[i]=*(pos+i);
	}


	//check goat win
	if(goat_win_condition(animal_pos))
	{
	displaygoat_win_condition();
	getch();
	return;
	}

	//tiger Move

	pos=move_tiger(goat_num,animal_pos,&dead_goat);

	for(i=0;i<25;i++)
	{
		animal_pos[i]=*(pos+i);
	}
   }

   if(dead_goat==5)
   {    clrscr();
	cleardevice();
	settextstyle(10,0,4);
	sleep(1);
	displaytiger_win_condition();
	getch();


	return;



   }
   break;
   case 2:
   {
     clrscr();
     cleardevice();
     settextstyle(7,0,6);
   setcolor(RED);
   outtextxy(100,50,"INSTRUCTIONS");
   settextstyle(0,0,1);
   sleep(1);
 cout<<"\n\n\n\n\n\n\n";
    delay(500);
cout<<"\nThe game is over when either the tigers capture five goats,or the goats have \nblocked the tigers from being able to move.";
delay(500);
cout<<"\nRULES FOR TIGER:";
delay(500);
cout<<"\n1. They can move to an adjacent free position along the lines.";
delay(500);
cout<<"\n2. They can capture goats during any move, and do not need to wait until all\n  goats are placed.";
delay(500);
cout<<"\n3. They can capture only one goat at a time.";
delay(500);
cout<<"\n4. They can jump over a goat in any direction,as long as there is an open space   for the tiger to complete its turn.";
delay(500);
cout<<"\n5. A tiger cannot jump over another tiger.";
delay(500);
cout<<"\nRULES FOR GOAT:";
delay(500);
cout<<"\n1. Goats cannot move until all goats have been positioned on the board.";
delay(500);
cout<<"\n2. They must leave the board when captured.";
delay(500);
cout<<"\n3. They cannot jump over tigers or other goats.";
delay(500);
cout<<"\n INSTRUCTION FOR MOUSE CONTROL";
delay(500);
cout<<"\nRight Click to select the Tiger/Goat\nLeft click to position Goat/Tiger";

sleep(1);
getch();
getch();
 break; }
  case 3:
   exit(1);

		getch();
		break;
   }

   }

}
void displaytiger_win_condition()
{
 clrscr();

	cleardevice();
	setbkcolor(BLACK);
	setcolor(3);

	settextstyle(10,0,5);
	outtextxy(getmaxx()/2-280,getmaxy()/2-125,"TIGER WINS!!!");

	getch();

}
int goat_win_condition(char animal_pos[25])
{
	int i,j,count=0;
	for(i=0;i<=24;i++)
	{
		if(animal_pos[i]=='T')
		{
			for(j=0;j<=24;j++)
			{
				if((path[i][j]==1 && animal_pos[j]=='X') || (path[i][j]==2 && animal_pos[j]=='X'))
				{
					return 0;
				}

			}
			count++;
		}
	}

	return 1;

}
void get_coordinate(int a,int *i,int *j)   //takes a from 0 - 24, provides coordiantes
{
      int rem;
      rem=(int) (a+1)%5;

      switch(rem)
      {
	case 0: *i=450;
		break;
	case 1: *i=50;
		break;
	case 2: *i=150;
		break;
	case 3: *i=250;
		break;
	case 4: *i=350;
		break;
      }

      if(a<=4)
      {
	*j=50;

      } else if(a>4 && a<=9)
      {
	*j=150;

      } else if(a>9 && a<=14)
      {
	*j=250;

      } else if(a>14 && a<=19)
      {
	*j=350;

      } else if(a>19 && a<=24)
      {
	*j=450;

      }
}

void check_pos(int a,int *x) //changes game postion(11,12,32,55,etc) to 0-24
{
      int k1,k2;
      k2=(int) a%10;
      k1=(int) a/10;

      if(k1==1)
	{
		*x=k2-1;

	} else if(k1==2)
	{
		*x=k2+4;

	} else if(k1==3)
	{
		*x=k2+9;
	}else if(k1==4)
	{
		*x=k2+14;
	}else if(k1==5)
	{
		*x=k2+19;
	}

}

int num_of_paths(int m1,int m2) //returns 0 for no path,1 for single step path and 2 for double step path
{
	int a1,b1,a2,b2,x,y;

	a1=(int)m1/10;
	a2=(int)m2/10;
	b1=(int)m1%10;
	b2=(int)m2%10;

	if(a1==1)
	{
		x=b1-1;

	} else if(a1==2)
	{
		x=b1+4;

	} else if(a1==3)
	{
		x=b1+9;
	}else if(a1==4)
	{
		x=b1+14;
	}else if(a1==5)
	{
		x=b1+19;
	}
	if(a2==1)
	{
		y=b2-1;

	} else if(a2==2)
	{
		y=b2+4;

	} else if(a2==3)
	{
		y=b2+9;
	}else if(a2==4)
	{
		y=b2+14;
	}else if(a2==5)
	{
		y=b2+19;
	}

	if(path[x][y]==1)
	{
	return 1;
	}
	else if(path[x][y]==2)
	{
	return 2;
	}
	else
	{
	return 0;
	}
}

void draw_board(char animal_pos[25],int goat_num,int dead_goat)
{
	int i,j,xcoo,ycoo;
setcolor(WHITE);
 rectangle (getmaxx()-22,2,getmaxx()-2,22);
   setfillstyle(1,RED);
line(getmaxx()-17,7,getmaxx()-7,17);
    line(getmaxx()-7,7,getmaxx()-17,17);
    floodfill(629,5,WHITE);
  setcolor(1);
	printf("Goats Left=%d\tGoat Eaten=%d\t",(20-goat_num),dead_goat);
	for(i=0;i<450;i+=100)
	{
		draw_line(50,50+i,450,50+i);
		draw_line(50+i,50,50+i,450);
	}

	draw_line(50,50,450,450);
	draw_line(450,50,50,450);
	draw_line(50,250,250,50);
	draw_line(250,50,450,250);
	draw_line(50,250,250,450);
	draw_line(450,250,250,450);
	for(i=0;i<=24;i++)
	{
		if(animal_pos[i]=='T')
		{
			get_coordinate(i,&xcoo,&ycoo);
			draw_tiger(xcoo,ycoo);
		}
		else if(animal_pos[i]=='G')
		{
			get_coordinate(i,&xcoo,&ycoo);
			draw_goat(xcoo,ycoo);
		}

	}
}

void draw_goat(int x,int y)
{
	int i;
	for(i=1;i<=8;i++)
	draw_circle(x,y,i,GREEN);
}

void draw_tiger(int x,int y)
{       int i;
	for(i=1;i<=17;i++)
	draw_circle(x,y,i,RED);
}

void draw_line(int x1,int y1,int x2,int y2)
{
   float xinc,yinc;
   int dx,dy;
   int steps,j;
   dx=x2-x1;
   dy=y2-y1;
   if(abs(dx)>abs(dy))
   steps=abs(dx);
   else
   steps=abs(dy);
   xinc=dx/steps;
   yinc=dy/steps;
   for(j=0;j<=steps;j++)
   {
	x1=x1+xinc;
	y1=y1+yinc;
	putpixel((int)(x1+0.5),(int)(y1+0.5),55);
   }
}
void draw_circle(int x,int y,int r,int m)
{
	int pk,x1,y1;
	x1=0;
	y1=r;
	pk=1-y1;
	while(x1<=y1)
	{
		putpixel(x1+x,y1+y,m);
		putpixel(y1+x,x1+y,m);
		putpixel(y1+x,-x1+y,m);
		putpixel(x1+x,-y1+y,m);
		putpixel(-x1+x,-y1+y,m);
		putpixel(-y1+x,-x1+y,m);
		putpixel(-y1+x,x1+y,m);
		putpixel(-x1+x,y1+y,m);
		if(pk<0)
		{
			x1=x1+1;
			pk=pk+2*x1+1;

		}
		else
		{
			x1=x1+1;
			y1=y1-1;
			pk=pk+2*x1-2*y1+1;
		}
	}
}
