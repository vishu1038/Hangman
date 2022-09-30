#include<stdio.h>
#include "format.h"
#define MAX 15 

void hang() //function to print the title
{
	drawRect();
	SetColor(45);
	gotoxy(30,2);printf("** HANGMAN **");
    gotoxy(30,3);printf(" GUESS or DIE\n");
    gotoxy(0,5);
    SetColor(17);
    int i;
	for(i = 1; i < 78; i++){
        gotoxy(i, 5);
        printf("%c",205);
    }
    
}

int check(char d[27],char alpha) //function to check if char already used
{
	int i,c=0;
	for(i=0;i<27;i++)
	{
		if(d[i]==alpha)
			c++;
	}
	if(c)
		return 1;
	else 
		return 0;
}

int playagain() //function to restart the game
{
	gotoxy(24,19);printf("Want to  Play Again(Y/N):");
	char ch=getche();
	if(ch=='Y' || ch =='y' )
		return 1;
	else 
		return 0;
}

void showHangman(int choice) //function to display different stages of hangman graphic  
{
	switch(choice)
    {
    	case 0:
		 	gotoxy(60,11);printf("||===== ");
			gotoxy(60,12);printf("||    | ");
			gotoxy(60,13);printf("||   %cO/",'\\');
			gotoxy(60,14);printf("||    | ");
			gotoxy(60,15);printf("||   / %c",'\\');
			gotoxy(60,16);printf("||      ");
			break;
     	case 1: 
			gotoxy(60,11);printf("||===== ");
			gotoxy(60,12);printf("||    | ");
			gotoxy(60,13);printf("||   %cO/",'\\');
			gotoxy(60,14);printf("||    | ");
			gotoxy(60,15);printf("||     %c",'\\');
			gotoxy(60,16);printf("||      ");
			break;
	    case 2:     
			gotoxy(60,11);printf("||===== ");
			gotoxy(60,12);printf("||    | ");
			gotoxy(60,13);printf("||   %cO/",'\\');
			gotoxy(60,14);printf("||    | ");
			gotoxy(60,15);printf("||      ");
			gotoxy(60,16);printf("||      ");
			break;
	    case 3:     
			gotoxy(60,11);printf("||===== ");
			gotoxy(60,12);printf("||    | ");
			gotoxy(60,13);printf("||   %cO/",'\\');
			gotoxy(60,14);printf("||      ");
			gotoxy(60,15);printf("||      ");
			gotoxy(60,16);printf("||      ");
			break;
	    case 4:
			gotoxy(60,11);printf("||===== ");
			gotoxy(60,12);printf("||    | ");
			gotoxy(60,13);printf("||   %cO ",'\\');
			gotoxy(60,14);printf("||      ");
			gotoxy(60,15);printf("||      ");
			gotoxy(60,16);printf("||      ");
			break;
	    case 5:
			gotoxy(60,11);printf("||===== ");
			gotoxy(60,12);printf("||    | ");
			gotoxy(60,13);printf("||    O ");
			gotoxy(60,14);printf("||      ");
			gotoxy(60,15);printf("||      ");
			gotoxy(60,16);printf("||      ");
			break;
		case 6:  
			gotoxy(60,11);printf("||===== ");
			gotoxy(60,12);printf("||    | ");
			gotoxy(60,13);printf("||      ");
			gotoxy(60,14);printf("||      ");
			gotoxy(60,15);printf("||      ");
			gotoxy(60,16);printf("||      ");
			break;
	}
}

int Randoms(int lower, int upper,int count) //function to select a random number
{ 
	int i; 
	for (i = 0; i < count; i++) 
	{ 
		int num = (rand() % (upper - lower + 1)) + lower; 
	return(num);
	} 
} 

void word(char a[]) //function to select a random word from file
{
	FILE *fp;
    fp = fopen("hangman-words.txt", "r");
	int lower = 1, upper = 213, count = 1; 
	srand(time(0)); 
    int n = Randoms(lower, upper, count); 
    char buf[MAX];
    int i;
    for (i = 0; i < n; i++)
    {
        fgets(buf, MAX, fp);
    }
    strcpy(a,buf);
}

void game() //main game function
{
	ngame:
	start();
	system("cls");
	int i,j,c,count=0,ans=0,flag,don=0;
	char a[MAX],done[]="                           ";
	word(a);
	char b[MAX],alpha;
	char d='_';
	system("cls");
	c=strlen(a)-1;
	hang();
	gotoxy(4,8);
	SetColor(45);
	for(j=0;j<c;j++)
		{
			printf("%c ",d);
			b[j]=d;
		}
	while (count<7)
 	{
 		flag=0;
	   	again:SetColor(28);
		gotoxy(4,13);printf("Enter your guess(character):");
	   	SetColor(45);
		alpha=getche();
		SetColor(28);
		if(check(done,alpha))
		{
			gotoxy(4,12);printf("You have already enterred this character.");
			gotoxy(32,13);printf(" ");
			goto again;
		}
		else
		{
			done[don]=alpha;
			don++;
		}
		for(i=0;i<c;i++)
		{
			if (alpha==a[i])
		  	{	
				b[i]=a[i];
		   		flag=1;
				ans++;
			}
		}
		SetColor(17);
		system("cls");
		hang();
		gotoxy(4,8);
		SetColor(45);
		for(i=0;i<c;i++)
			printf("%c ",b[i]);
		if(flag==0)
		{
			count++;
			SetColorAndBackground(31,28);
			gotoxy(50,8);printf("%c is a wrong guess",alpha);
			gotoxy(50,9);printf(" (You have %d more guesses)",7-count);
			SetColorAndBackground(17,15);
			showHangman(7-count);
		}
		else
		{
			SetColorAndBackground(31,34);
			gotoxy(50,8);printf("You are correct!!");
	   		gotoxy(40,9);printf("( You have %d more letters to go)",c-ans);
	   		SetColorAndBackground(17,15);
	   		showHangman(7-count);
		}
		if(ans==c)
			break;
 	}
 	if(ans==c) 
	{
 		system("cls");
 		hang();
 		SetColorAndBackground(31,34);
 		gotoxy(24,12);printf("You Won!!");
 		SetColorAndBackground(17,15);
 		if(playagain())
 			goto ngame;
 		else
 			exit(0);
	}
 	else {
 		system("cls");
 		hang();
 		showHangman(0);
 		SetColorAndBackground(31,28);
		gotoxy(4,11);printf("You lose.");
		gotoxy(4,12);printf("**SORRY YOU ARE HANGED**");
		SetColorAndBackground(17,15);
		if(playagain())
 			goto ngame;
 		else
 			exit(0);
	}
}

void main()
{
	ClearConsoleToColors(17,15);
    SetConsoleTitle("HANGMAN : GUESS OR DIE"); //inbult  function to set console title
	game();
}
