#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <cstdlib>
using namespace std;

#define MENU_LIST 4
#define NUM_OF_MODES 2

// DECLARATION
struct Player
{
	int time = 0;
	string user = "";
	string pass = "";
	string mode = "";
};

Player P;

void Leaderboards();
void Login_Menu();
void Main_Menu();
void Personal_Record(Player P);

///////////////////////////////////////////////////////////
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

void Register()
{
	string user, pass = "", pass_confirm = "", user_check;
	char temp, temp_conf;
	bool mark;
	do
	{
		system("cls");
		SET_COLOR(14);
		cout << "\n===========================REGISTER=======================================\n\n";
		SET_COLOR(3);
		cout << "-Enter USER ID: ";
		SET_COLOR(7);
		getline(cin, user);

		// CHECK WHETHER USERNAME HAS EXISTED
		mark = false;
		ifstream Check("Account/" + user + ".txt");
		if (Check)
		{
			mark = true;
			SET_COLOR(4);
			cout << "\t\n!! The username has exsited. Please choose another one !!\n";
			Sleep(1500);
			continue;
		}
		/////////////////////////////////////////////////////////////////////////////
		SET_COLOR(3);
		cout << "-Enter PASSWORD: ";
		SET_COLOR(7);
		pass = "";

		// INPUT PASSWORD
		while (1)
		{
			temp = _getch();
			if (temp == '\r')
			{
				cout << "\n";
				break;
			}
			else if (temp == '\b' && pass.length() > 0)
			{
				pass.pop_back();
				cout << "\b \b";
				continue;
			}
			else if (temp == '\b' && pass.length() == 0)
				continue;

			pass.push_back(temp);
			cout << '*';
		}
		SET_COLOR(3);
		cout << "-Confirm PASSWORD: ";
		SET_COLOR(7);
		pass_confirm = "";

		// CONFIRM PASSWORD
		while (1)
		{
			temp_conf = _getch();
			if (temp_conf == '\r')
			{
				cout << "\n";
				break;
			}
			else if (temp_conf == '\b' && pass_confirm.length() > 0)
			{
				pass_confirm.pop_back();
				cout << "\b \b";
				continue;
			}
			else if (temp_conf == '\b' && pass_confirm.length() == 0)
				continue;

			pass_confirm.push_back(temp_conf);
			cout << '*';
		}

		if (pass_confirm.compare(pass) == 0)
		{
			mark = false;
			// CREATE A FILE FOR EACH ACCOUNT
			string file_path = "Account/" + user + ".txt";
			ofstream F(file_path);
			F << pass << "\n";
			F.close();
			///////////////////////////////////////////////////////
			SET_COLOR(10);
			cout << "\n---> Register successfully!\n";
			Sleep(1000);
			SET_COLOR(7);
			cout << "\nPlease wait a moment.......................................\n";
			Sleep(2000);
			Main_Menu();
		}
		else
		{
			mark = true;
			SET_COLOR(4);
			cout << "\t\n!! Those passwords didn't match. Try again. !!\n";
			Sleep(1500);
		}
	} while (mark);
}

void Login(string &user, string &pass)
{
	char temp;
	string pass_test = "";
	int flag = 0;
	int limit = 0;
	do
	{
		system("cls");
		SET_COLOR(14);
		cout << "\n==============================LOGIN=======================================\n";
		SET_COLOR(3);
		cout << "-USER ID: ";
		SET_COLOR(7);
		getline(cin, user);
		SET_COLOR(3);
		cout << "-PASSWORD: ";
		SET_COLOR(7);
		pass = "";

		// REPRESENT THE PASSWORD WITH THE CHARACTER '*'
		while (1)
		{
			temp = _getch();
			if (temp == '\r') // '\r' is ENTER
			{
				cout << "\n";
				break;
			}
			else if (temp == '\b' && pass.length() > 0) // '\b' is BACKSPACE
			{
				pass.pop_back();
				cout << "\b \b";
				continue;
			}
			else if (temp == '\b' && pass.length() == 0)
				continue;

			pass.push_back(temp);
			cout << '*';
		}

		ifstream Check("Account\\" + user + ".txt");
		if (Check)
		{
			getline(Check, pass_test);
			Check.close();
		}

		if (pass.compare(pass_test) == 0)
		{
			flag = 1;
			SET_COLOR(10);
			cout << "\t--> Login successfully!\n";
			Sleep(1000);
			SET_COLOR(7);
			cout << "\nPlease wait a moment...........................................";
			Sleep(1500);
			break;
		}
		else
		{
			SET_COLOR(4);
			cout << "\n!! The USER ID or PASSWORD is wrong !! Please try again !!\n";
			Sleep(1500);
			limit++;
		}
	} while (limit <= 5);

	if (flag == 1)
		Main_Menu();
	else
	{
		// ASKING USER FOR CREATING NEW ACCOUNT
		SET_COLOR(14);
		cout << "\t\t\n\nYOU DO NOT HAVE AN ACCOUNT ?";
		cout << "\t\t\nPlease create one!\n";
		SET_COLOR(8);
		cout << "[*] Press 1 for YES or 2 for NO";
		while (1)
		{
			char choice = _getch();
			switch (choice)
			{
			case '1':
				Register();
				break;
			case '2':
				Login_Menu();
			default:
				continue;
			}
		}
	}
}

void Mode_Menu()
{
	int flag = 1;
	int opt = 1;
	while (1)
	{
		system("cls");
		cout << "\n\n";
		SET_COLOR(11);
		cout << "\t\t\tWHICH MODE DO YOU WANT TO PLAY ?\n\n";
		SET_COLOR(14);
		cout << "\t\t\t\t1. Standard \n";
		cout << "\t\t\t\t2. Difficult ";
		SET_COLOR(7);
		cout << "\n\n[*] Use UP and DOWN arrow keys to select\n";
		cout << "\nYour choice [1-" << MENU_LIST << "]: ";
		SET_COLOR(14);
		cout << opt;

		char ch = _getch();
		if (ch == 13)
		{
			flag = 0;
			switch (opt)
			{
			case 1:
				// Basic_Mode();
				break;
			default:
				// Difficult_Mode();
				break;
			}
		}

		else if (ch == 80)
			opt++;
		else if (ch == 72)
			opt--;

		if (opt < 1)
			opt = NUM_OF_MODES;
		else if (opt > NUM_OF_MODES)
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
		cout << "\t\t\t+\t\t2> Leaderboards		  +\n";
		cout << "\t\t\t+\t\t3> Personal record	  +\n";
		cout << "\t\t\t+\t\t4> Exit			  +\n";
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
				Leaderboards();
				break;
			case 3:
				Personal_Record(P);
			default:
				exit(0);
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

void Login_Menu()
{
	int func = 1;
	int flag = 1;
	while (1)
	{
		system("cls");
		SET_COLOR(14);
		cout << "\t\t\t+-+-+-+-+-+-+-+-+-+-+-LOGIN MENU-+-+-+-+-+-+-+-+-\n";
		SET_COLOR(11);
		cout << "\t\t\t+\t\t1> Register			+\n";
		cout << "\t\t\t+\t\t2> Login			+\n";
		cout << "\t\t\t+\t\t3> Exit				+\n";
		SET_COLOR(14);
		cout << "\t\t\t+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-\n";
		SET_COLOR(7);
		cout << "\n[*] Use UP and DOWN arrow keys to select\n";
		cout << "\nYour choice [1 - 3]: ";
		SET_COLOR(11);
		cout << func;

		char p = _getch();
		if (p == 13)
		{
			flag = 0;
			switch (func)
			{
			case 1:
				Register();
				break;
			case 2:
				Login(P.user, P.pass);
				break;
			case 3:
				exit(0);
			default:
				cout << "\n\t!!! Invalid choice !!!\n";
			}
		}
		else if (p == 80)
		{
			func++;
		}
		else if (p == 72)
		{
			func--;
		}

		if (func > 3)
			func = 1;
		else if (func < 1)
			func = 3;

		if (flag == 0)
			break;
	}
}

void Save_Record(Player p)
{
	ofstream Read("Account\\" + p.user + ".txt", ios::app);
	
	// WRITE INFORMATION INTO FILE
	Read << p.time << "-" << p.mode << "\n";
	Read.close();
}

void Personal_Record(Player P)
{
	ifstream F("Account\\" + P.user + ".txt");
	int numLines = 0;
	getline(F, P.pass);

	// COUNT THE NUMBER OF LINES OF FILE FROM THE PASSWORD LINE
	char c;
	F.get(c);
	while (!F.eof())
	{
		if(c=='\n')
			numLines++;
		F.get(c);
	}

	// MOVE THE POSITION POINTER TO THE BEGINNING OF THE FILE
	F.clear();
	F.seekg(0,ios::beg);
	F.seekg(P.pass.length()+1,ios::cur);
	/////////////////////////////////////////////////////////////////////

	string temp;
	Player *Record = new Player[numLines];

	for(int i = 0; i < numLines; i++)
	{
		getline(F,temp,'-');
		getline(F, Record[i].mode);
		Record[i].time = stoi(temp);
	}

	// SORT TO GET THE SHORTEST TIME
	for (int i = 0; i < numLines-1; i++)
	{
		for (int j = i+1; j < numLines; j++)
		{
			if(Record[i].time < Record[j].time)
			{
				Player temp = Record[i];
				Record[i] = Record [j];
				Record[j] = temp; 
			}
		}
		
	}
	system("cls");
	cout << Record[0].time << "-" << Record[0].mode << endl;
	delete [] Record;
	F.close();
	system("pause");
}

void Leaderboards()
{
	
}