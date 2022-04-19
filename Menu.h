#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <sstream>
using namespace std;

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
void Game();
///////////////////////////////////////////////////////////

string Convert_Time(int time)
{
	int h, m, s;
	string res;

	h = time / 3600;
	m = time % 3600 / 60;
	s = time - 3600*h - 60*m;

	res = to_string(h);
	res.append("h ");
	res.append(to_string(m));
	res.append("m ");
	res.append(to_string(s));
	res.append("s");

	return res; 
}

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

void Register(string &user, string &pass)
{
	string pass_confirm = "", user_check;
	pass = ""; 
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
		cin >> user;

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
			if (temp == 27)
				Login_Menu();
			else if (temp == '\r')
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
			if (temp == 27)
				exit(0);
			else if (temp_conf == '\r')
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
			cout << (char)7;
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
		cin >> user;
		SET_COLOR(3);
		cout << "-PASSWORD: ";
		SET_COLOR(7);
		pass = "";

		// REPRESENT THE PASSWORD WITH THE CHARACTER '*'
		while (1)
		{
			temp = _getch();
			if (temp == 27) // the ASCII code of ESC is 27
				Login_Menu();
			else if (temp == '\r') // '\r' is ENTER
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
			cout << (char)7;
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
				Register(P.user,P.pass);
				break;
			case '2':
				Login_Menu();
			default:
				continue;
			}
		}
	}
}

void Main_Menu()
{
	char opt;
	do
	{
		system("cls");
		SET_COLOR(14);
		cout << "\t\t\t+-+-+-+-+-+-+-+-+-+ MENU -+-+-+-+-+-+-+-+-+\n";
		SET_COLOR(11);
		cout << "\t\t\t+\t\t1> Start game		  +\n";
		cout << "\t\t\t+\t\t2> Leaderboards		  +\n";
		cout << "\t\t\t+\t\t3> Personal record	  +\n";
		cout << "\t\t\t+\t\t4> Quit			  +\n";
		SET_COLOR(14);
		cout << "\t\t\t+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+- \n";
		SET_COLOR(7);
		cout << "\n[*] Please press the corresponding number to select";

		opt = _getch();
		switch (opt)
		{
		case '1':
			Game();
			break;
		case '2':
			Leaderboards();
			break;
		case '3':
			Personal_Record(P);
			break;
		case '4':
			exit(0);
			break;
		case 27:
			Login_Menu();
		default:
			continue;
		}
	} while (1);
}

void Login_Menu()
{
	char func;
	do
	{
		system("cls");
		SET_COLOR(14);
		cout << "\t\t\t+-+-+-+-+-+-+-+-+-+-+-LOGIN MENU-+-+-+-+-+-+-+-+-\n";
		SET_COLOR(11);
		cout << "\t\t\t+\t\t1> Register			+\n";
		cout << "\t\t\t+\t\t2> Login			+\n";
		cout << "\t\t\t+\t\t3> Quit				+\n";
		SET_COLOR(14);
		cout << "\t\t\t+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-\n";
		SET_COLOR(7);
		cout << "\n[*] Please press the corresponding number to select";

		func = _getch();
		switch (func)
		{
		case '1':
			Register(P.user,P.pass);
			break;
		case '2':
			Login(P.user, P.pass);
			break;
		case '3':
		case 27:
			exit(0);
			break;
		default:
			continue;
		}
	} while (1);
}

void Save_Record(Player P, int timer, int m)
{
	ofstream Read("Account\\" + P.user + ".txt", ios::app);
	ofstream Print("LDB.txt", ios::app);
	P.time = timer;

	if (m == 1)
		P.mode = "Normal";
	else if( m == 2 )
		P.mode = "Difficult";
	else return;
	// WRITE INFORMATION INTO FILE
	Read.flush();
	Read << P.time << "-" << P.mode << "\n";

	Print.flush();
	Print << P.user << "-" << P.time << "-" << P.mode << "\n"; 

	Read.close();
	Print.close();
}

void Personal_Record(Player P)
{
	system("cls");
	SET_COLOR(14);
	cout <<"\n\n";
	cout << left << setw(20) << "BEST TIME";
	cout << left << setw(20) << "MODE";
	cout << "\n-----------------------------------------------------------------\n";


	ifstream F("Account\\" + P.user + ".txt");
	int numLines = 0;
	string s;
	// COUNT THE NUMBER OF LINES OF FILE FROM THE PASSWORD LINE
	while (getline(F,s))
	{
		numLines++;
	}
	numLines--; // the fisrt line is PASSWORD

	// MOVE THE POSITION POINTER TO THE BEGINNING OF THE FIRST LINE STORES TIME
	F.clear();
	F.seekg(0, ios::beg);
	F.seekg(P.pass.length() + 1, ios::cur);
	/////////////////////////////////////////////////////////////////////
	
	string temp1, temp2;
	int cnt1 = 0, cnt2 = 0;
	Player exchange;

	Player *Norm = new Player[numLines];
	Player *Diff = new Player[numLines];

	// GET THE TIME AND MODE FROM FILE
	
	for (int i = 0; i < numLines; i++)
	{
		getline(F, temp1, '-');
		getline(F, temp2);

		if (temp2 == "Normal")
		{
			Norm[cnt1].time = stoi(temp1);
			Norm[cnt1].mode = "Normal";
			cnt1++;
		}
		else if (temp2 == "Difficult")
		{
			Diff[cnt2].time = stoi(temp1);
			Diff[cnt2].mode = "Difficult";
			cnt2++;
		}
	}
	// SORT TO GET THE SHORTEST TIME
	if (cnt1 > 0)
	{
		if (cnt1 > 1)
		{
			for (int i = 0; i < cnt1 - 1; i++)
			{
				for (int j = i + 1; j < cnt1; j++)
				{
					if (Norm[i].time > Norm[j].time)
					{
						Player temp = Norm[i];
						Norm[i] = Norm[j];
						Norm[j] = exchange;
					}
				}
			}
		}
		SET_COLOR(7);
		string cvt = Convert_Time(Norm[0].time);
		cout << left << setw(20) << cvt;
		cout << left << setw(20) << Norm[0].mode;
		cout << "\n";
	}

	if (cnt2 > 0)
	{
		if (cnt2 > 1)
		{
			for (int i = 0; i < cnt2 - 1; i++)
			{
				for (int j = i + 1; j < cnt2; j++)
				{
					if (Diff[i].time > Diff[j].time)
					{
						exchange = Diff[i];
						Diff[i] = Diff[j];
						Diff[j] = exchange;
					}
				}
			}
		}
		SET_COLOR(7);
		string cvt = Convert_Time(Diff[0].time);
		cout << left << setw(20) << cvt;
		cout << left << setw(20) << Diff[0].mode;
		cout << "\n";
	}
	////////////////////////////////////////////////////
	F.close();
	getch();
	delete[] Norm;
	delete[] Diff;
	Main_Menu();
}

void Leaderboards()
{
	Player exchange;
	system("cls");
	SET_COLOR(14);
	cout << "\n\n";
	cout << left << setw(20) << "USERNAME";
	cout << left << setw(20) << "TIME";
	cout << left << setw(20) << "MODE";
	cout << "\n-----------------------------------------------------------------\n";

	ifstream Print("LDB.txt");
	int numLines = 0;
	string s;
	// COUNT THE NUMBER OF LINES OF FILE FROM THE PASSWORD LINE
	while (getline(Print,s))
	{
		numLines++;
	}
	// MOVE THE POSITION POINTER TO THE BEGINNING OF THE FILE
	Print.clear();
	Print.seekg(0, ios::beg);
	/////////////////////////////////////////////////////////////////////

	string temp1, temp2, temp3;
	int cnt1 = 0, cnt2 = 0;

	Player *Norm = new Player[numLines];
	Player *Diff = new Player[numLines];

	// GET THE TIME AND MODE FROM FILE
	for (int i = 0; i < numLines; i++)
	{
		getline(Print, temp3,'-');
		getline(Print, temp1, '-');
		getline(Print, temp2);

		if (temp2 == "Normal")
		{
			Norm[cnt1].time = stoi(temp1);
			Norm[cnt1].mode = temp2;
			Norm[cnt1].user = temp3;
			cnt1++;
		}
		else if(temp2 == "Difficult")
		{
			Diff[cnt2].time = stoi(temp1);
			Diff[cnt2].mode = temp2;
			Diff[cnt2].user = temp3;
			cnt2++;
		}
	}
	// SORT TO GET THE SHORTEST TIME
	if (cnt1 > 0)
	{
		for (int i = 0; i < cnt1 - 1; i++)
		{
			if (Norm[i].time == 0)
				break;

			for (int j = i + 1; j < cnt1; j++)
			{
				if (Norm[i].time > Norm[j].time)
				{
					exchange = Norm[i];
					Norm[i] = Norm[j];
					Norm[j] = exchange;
				}
			}
		}
		SET_COLOR(7);
		int lim = 0; 
		for (int i = 0; i < cnt1; i++)
		{
			string cvt = Convert_Time(Norm[i].time);
			cout << left << setw(20) << Norm[i].user;
			cout << left << setw(20) << cvt;
			cout << left << setw(20) << Norm[i].mode;
			cout << "\n";

			lim++;
			if(lim > 10) break; // Print 10 best player of Normal mode
		}
	}
	cout << "\n-----------------------------------------------------------------\n\n";

	if (cnt2 > 0)
	{
		for (int i = 0; i < cnt2 - 1; i++)
		{
			if (Diff[i].time == 0)
				break;

			for (int j = i + 1; j < cnt2; j++)
			{
				if (Diff[i].time > Diff[j].time)
				{
					exchange = Diff[i];
					Diff[i] = Diff[j];
					Diff[j] = exchange;
				}
			}
		}
		SET_COLOR(7);
		int lim = 0;
		for (int i = 0; i < cnt2; i++)
		{
			string cvt = Convert_Time(Diff[0].time);
			cout << left << setw(20) << Diff[0].user;
			cout << left << setw(20) << cvt;
			cout << left << setw(20) << Diff[0].mode;
			cout << "\n";

			lim++;
			if(lim>10) break;
		}
		
	}
	////////////////////////////////////////////////////
	Print.close();
	delete[] Norm;
	delete[] Diff;
	_getch();
	Main_Menu();
}

void Ending_Screen(){
    system("cls");
    SET_COLOR(14);
    string draw;
    ifstream read("Ending_Screen.txt");
    while (!read.eof())
    {
        getline(read,draw);
        cout << draw << "\n";
        Sleep(200);
    }
    read.close();
    cout <<"\n\n\n";
    Sleep(2000);
	Game();
}

void Starting_Screen()
{
	string draw;

	ifstream S1("Starting_Screen\\St1.txt");
	SET_COLOR(13);
	while (!S1.eof())
    {
        getline(S1,draw);
        cout << draw << "\n";
        Sleep(200);
    }
	S1.close();

	ifstream S2("Starting_Screen\\St2.txt");
	SET_COLOR(14);
	while (!S2.eof())
    {
        getline(S2,draw);
        cout << draw << "\n";
        Sleep(200);
    }
	S2.close();

	Sleep(1000);
	SET_COLOR(7);
	cout << "\n\nPlease wait a moment.................................................";
	Sleep(2500);
}
