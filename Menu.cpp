void Mode_Menu() {
	int flag = 1;
	int opt = 1;
	while (1) {
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
		if (ch == 13) {
			flag = 0;
			switch (opt)
			{
                case 1:
                    Basic_Mode();
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
