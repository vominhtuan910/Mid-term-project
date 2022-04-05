#include "Menu.h"

void Register(){
    string user, pass = "", pass_confirm = "";
	char temp, temp_conf;
	system("cls");
	SET_COLOR(14);
	cout << "\n===========================REGISTER=======================================\n\n";
	SET_COLOR(3);
	cout << "-USER ID: ";
	SET_COLOR(7);
	getline(cin, user);
	SET_COLOR(3);
	cout << "-PASSWORD: ";
	SET_COLOR(7);

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
		ofstream F;
		F.open("Account.txt", ios::app);
		F<<user<<"|"<<pass<<"\n";
		F.close();
		SET_COLOR(10);
		cout << "\n---> Register successfully!\n";
		SET_COLOR(7);
		Sleep(1000);
		cout << "\nPlease wait a moment.......................................\n";
		Sleep(2000);
		Main_Menu();
	}
	else
	{
		SET_COLOR(4);
		cout << "\t\n!! Those passwords didn't match. Try again. !!\n";
		SET_COLOR(7);
	}
}

void Login(){
    ifstream Check("Account.txt", ios::in);
	string user, pass = "";
	char temp;
	string user_test, pass_test;
	int flag = 0;
	int limit = 0;

	system("cls");
	SET_COLOR(14);
	cout << "\n==============================LOGIN=======================================\n";
	SET_COLOR(3);
	cout << "-Enter USER ID: ";
	SET_COLOR(7);
	getline(cin, user);
	SET_COLOR(3);
	cout << "-Enter PASSWORD: ";
	SET_COLOR(7);

	while (1)
	{
		temp = _getch();
		if (temp == '\r') // '\r' is ENTER
		{
			cout << "\n";
			break;
		}
		else if (temp == '\b' && pass.length() > 0)  // '\b' is BACKSPACE
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

	while (!Check.eof())
	{
		getline(Check, user_test, '|');
		getline(Check, pass_test, '\n');
		if (user_test.compare(user) == 0 && pass_test.compare(pass) == 0)
		{
			SET_COLOR(10);
			cout << "\t--> Login successfully!\n";
			flag = 1;
			break;
		}
	}

	if (flag == 1)
	{
		Sleep(1000);
		SET_COLOR(7);
		cout << "\nPlease wait a moment...........................................";
		Sleep(2000);
		Main_Menu();
	}
	else
	{
		SET_COLOR(4);
		cout << "\n!! The USER ID or PASSWORD is wrong !! Please try again !!\n";
		Sleep(1000);
	}
	Check.close();
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
				Login();
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