#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
using namespace std;

#define MENU_LIST 3
#define NumOfModes 2

void SET_COLOR(int color)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
} // Changing color function

void Leaderboard(){
    struct player{
        int time;
        string username;
    }; 

    fstream fso("Player.txt", ios::app | ios::in);
    

    fso.close();
}

void Mode_Menu() {
	int flag = 1;
	int opt = 1;
	while (1) {
		system("cls");
		cout << "\n\n";
        SET_COLOR(11);
		cout << "\t\t\tWHICH MODE DO YOU WANT TO PLAY ?\n\n";
        SET_COLOR(14);
		cout << "\t\t\t\t1. Normal \n";
		cout << "\t\t\t\t2. Difficult ";
        SET_COLOR(7);
		cout << "\n\n[*] Use UP and DOWN arrow keys to select\n";
		cout << "\nYour choice [1-" << MENU_LIST << "]: ";
		SET_COLOR(14);
		cout << opt;

		char ch = _getch();
		if (ch == 13) {
			flag = 0;
			switch (opt)
			{
                case 1:
                    //Basic_Mode();
                    break;
			default:
                    //Difficult_Mode();
		    break;
			}
		}
        
		else if (ch == 80)
			opt++;
		else if (ch == 72)
			opt--;

		if (opt < 1)
			opt = NumOfModes;
		else if (opt > NumOfModes)
			opt = 1;

		if (flag == 0)
			break;
	}
}

void Main_Menu()
{
	int opt = 1;
	int flag = 1;
	while (1)
	{
		system("cls");
		SET_COLOR(14);
		cout << "\t\t\t+-+-+-+-+-+-+-+-+-+ MENU -+-+-+-+-+-+-+-+-+\n";
		SET_COLOR(11);
		cout << "\t\t\t+\t\t1> Start game		  +\n";
		cout << "\t\t\t+\t\t2> Leaderboard		  +\n";
		cout << "\t\t\t+\t\t3> Quit			  +\n";
		SET_COLOR(14);
		cout << "\t\t\t+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+- \n";
		SET_COLOR(7);
		cout << "\n[*] Use UP and DOWN arrow keys to select\n";
		cout << "\nYour choice [1-" << MENU_LIST << "]: ";
		SET_COLOR(14);
		cout << opt;

		char p = _getch();
		if (p == 13)
		{
			flag = 0;
			switch (opt)
			{
			case 1:
				Mode_Menu();
				break;
			case 2:
				Leaderboard();
				break;
           		 case 4:
                		exit(0);
			default:
				break;
			}	
		}
		else if (p == 80)
			opt++;
		else if (p == 72)
			opt--;

		if (opt > MENU_LIST)
			opt = 1;
		else if (opt < 1)
			opt = MENU_LIST;

		if (flag == 0)
			break;
	}
}
