
#include "classes.h"            

namespace Game {

    Player::Player() {
		Earse_Map (attack);
		Earse_Map (ships);
		Earse_Data(all);
    }

    void Player::Earse_Map (defs mode, int num) {
        for (int y (null); y < map_size; y++) {
            for (int x (null); x < map_size; x++) {
				if (mode == attack)
					Att_Map [y][x] = num;
				else
					Ship_Map [y][x] = num;
			}
		}
    }

	void Player::Earse_Data (defs mode) {
		if (mode == all)
			Again = false;
		Wounded	= null;
		if (mode == all || mode == no_again) {
			for (int i (null); i < coord_num; i++) {
				Y [i] = null;
				X [i] = null;
			}
		}
	}

    void Player::Show_Map (defs mode){
		for (int i(null); i < map_finish; i++) {
			for (int j(null); j < map_finish; j++) {
				if (mode == attack) {
					if ((i>0)&&(j>0) && Att_Map [i][j] == hit)
						cout<<"X   ";
					if ((i>0)&&(j>0) && Att_Map [i][j] == miss)
						cout<<"*   ";
					if ((i>0)&&(j>0) && Att_Map [i][j] == null)
						cout<<".   ";
					if ((i>0)&&(j>0) && Att_Map [i][j] > hit)
						cout<<"[]  ";
				}
				else {
					if ((i>0)&&(j>0) && Ship_Map [i][j] == hit)
						cout<<"X   ";
					if ((i>0)&&(j>0) && Ship_Map [i][j] == miss)
						cout<<"*   ";
					if ((i>0)&&(j>0) && Ship_Map [i][j] == null)
						cout<<".   ";
					if ((i>0)&&(j>0) && Ship_Map [i][j] > hit)
						cout<<"[]  ";
				}
				if ((i==0) && (j==0))
                    cout<<"    ";
                if ((i==0) && (j==1))
                    cout<<"�   ";
                if ((i==0) && (j==2))
                    cout<<"�   ";
                if ((i==0) && (j==3))
                    cout<<"�   ";
                if ((i==0) && (j==4))
                    cout<<"�   ";
                if ((i==0) && (j==5))
                    cout<<"�   ";
                if ((i==0) && (j==6))
                    cout<<"�   ";
                if ((i==0) && (j==7))
                    cout<<"�   ";
                if ((i==0) && (j==8))
                    cout<<"�   ";
                if ((i==0) && (j==9))
                    cout<<"�   ";
                if ((i==0)&&(j==10))
                    cout<<"�  ";
                if ((i==1) && (j==0))
                    cout<<"1   ";
                if ((i==2) && (j==0))
                    cout<<"2   ";
                if ((i==3) && (j==0))
                    cout<<"3   ";
                if ((i==4) && (j==0))
                    cout<<"4   ";
                if ((i==5) && (j==0))
                    cout<<"5   ";
                if ((i==6) && (j==0))
                    cout<<"6   ";
                if ((i==7) && (j==0))
                    cout<<"7   ";
                if ((i==8) && (j==0))
                    cout<<"8   ";
                if ((i==9) && (j==0))
                    cout<<"9   ";
                if ((i==10) && (j==0))
                    cout<<"10  ";
            }
            cout<<"\n\n";
        }
    }

    bool Player::Check_Win() {
		int counter = null;	
		for (int i (null); i<map_finish; i++) {
			for (int j(null); j<map_finish; j++) {
				if (Att_Map [i][j] == hit)
					counter ++;
			}
		}
		return ( counter == all_deck )? true : false;
	}

    void Player::Put_Ships() {
		int x = null, y = null, random = null, again = null, ship_num = null;
		while(true) { // �����������y����;
            x = rand()%10+1;
            y = rand()%10+1;
            random = rand()%100;
            again = null;
            if (random%2 == null){
                for (int i=-1;i<=1;i++) {
                    for (int j=-1;j<=4;j++) {
                        if ((Ship_Map[y+i][x+j]!=0)||(x+j>10))
                            again++;
                    }
                }
            }
            else {
                for (int i=-1;i<=4;i++) {
                    for (int j=-1;j<=1;j++) {
                        if ((Ship_Map[y+i][x+j]!=0)||(y+i>10))
                            again++;
                    }
                }
            }
            if (again != null)
                continue;
            if (random%2 == null) {
                Ship_Map[y][x]=41;		// ������������� ������ ������� (��������� ��� �������);
                Ship_Map[y][x+1]=41;	// ������������� ������ ������� (��������� ��� �������);
                Ship_Map[y][x+2]=41;	// ������������� ������ ������� (��������� ��� �������);
                Ship_Map[y][x+3]=41;	// ������������� ������ ������� (��������� ��� �������);
                break;
            }
            else {
                Ship_Map[y][x]=41;		// ������������� ������ ������� (��������� ��� �������);
                Ship_Map[y+1][x]=41;	// ������������� ������ ������� (��������� ��� �������);
                Ship_Map[y+2][x]=41;	// ������������� ������ ������� (��������� ��� �������);
                Ship_Map[y+3][x]=41;	// ������������� ������ ������� (��������� ��� �������);
                break;
            }
		}
		ship_num ++;
		for (int times = 1; times <= 2; times ++) { // ��������y�� (2 ��.);
            while(true) {
            x = rand()%10+1;
            y = rand()%10+1;
            random = rand()%100;
            again = null;
                if (random%2 == null) {
                    for (int i=-1;i<=1;i++) {
                        for (int j=-1;j<=3;j++) {
                            if ((Ship_Map[y+i][x+j]!=0)||(x+j>10))
                                again++;
                        }
                    }
                }
                else {
                    for (int i=-1;i<=3;i++) {
                        for (int j=-1;j<=1;j++) {
                            if ((Ship_Map[y+i][x+j]!=0)||(y+i>10))
                                again++;
                        }
                    }
                }
                if (again != null)
                        continue;
                if (random%2 == null) {
                        Ship_Map[y][x]=30+times;	// ������������� ������ ������� (��������� ��� �������);
                        Ship_Map[y][x+1]=30+times;	// ������������� ������ ������� (��������� ��� �������);
                        Ship_Map[y][x+2]=30+times;	// ������������� ������ ������� (��������� ��� �������);
                        break;
                }
                else {
                        Ship_Map[y][x]=30+times;	// ������������� ������ ������� (��������� ��� �������);
                        Ship_Map[y+1][x]=30+times;	// ������������� ������ ������� (��������� ��� �������);
                        Ship_Map[y+2][x]=30+times;	// ������������� ������ ������� (��������� ��� �������);
                        break;
                }
            }
            ship_num ++;
		}
		for (int times = 1; times <= 3; times ++) { // �������y�� (3 ��.);
            while(true) {
            x = rand()%10+1;
            y = rand()%10+1;
            random = rand()%100;
            again = null;
                if (random%2 == null) {
                    for (int i=-1;i<=1;i++)
                    {
                        for (int j=-1;j<=2;j++)
                        {
                            if ((Ship_Map[y+i][x+j]!=0)||(x+j>10))
                                again++;
                        }
                    }
                }
                else {
                    for (int i=-1;i<=2;i++)
                    {
                        for (int j=-1;j<=1;j++)
                        {
                            if ((Ship_Map[y+i][x+j]!=0)||(y+i>10))
                                again++;
                        }
                    }
                }
                if (again != null)
                        continue;
                if (random%2 == null) {
                        Ship_Map[y][x]= 20+times;	// ������������� ������ ������� (��������� ��� �������);
                        Ship_Map[y][x+1]= 20+times; // ������������� ������ ������� (��������� ��� �������);
                        break;
                }
                else {
                        Ship_Map[y][x]= 20+times;	// ������������� ������ ������� (��������� ��� �������);
                        Ship_Map[y+1][x]= 20+times; // ������������� ������ ������� (��������� ��� �������);
                        break;
                }
            }
            ship_num ++;
		}
        for (int times = 1; times <= 4; times ++) { // �������y�� (4 ��.);
            while(true) {
            x = rand()%10+1;
            y = rand()%10+1;
            again = null;
            for (int i=-1;i<=1;i++) {
                for (int j=-1;j<=1;j++) {
                    if (Ship_Map[y+i][x+j]!=0)
                        again++;
                    }
                }
            if (again != null)
                continue;
            Ship_Map[y][x] = 10+times;	// ������������� ������ ������� (��������� ��� �������);
            break;
            }
        ship_num ++;
		}
    }

    bool Player::Check_Ship (Player & pl) {
		for (int i (map_start); i<map_finish; i++) {
			for (int j (map_start); j<map_finish; j++) {
				if (pl.Ship_Map [i][j] == Wounded)
					return true;
			}
		}
        return false;
    }

    void Player::Round_Fire (Player & pl) {
        for (int i (map_start); i<map_finish; i++) {
			for (int j (map_start); j<map_finish; j++) {
				if (pl.Ship_Map [i][j] == (Wounded * del)) {
					for (int y (-1); y <=1; y++) {
						for (int x (-1); x <=1; x++) {
							if (Att_Map [i+y][j+x] == null)
								Att_Map [i+y][j+x] = miss;
						}
					}
				}
			}
		}
    }

	void Player::Move_AI (Player & pl) {
		int y = null, x = null, stop = null;
		if (Wounded == null) {
			while (true) { // (�������� ��������� � ����y ���y�y)
				y = rand()%10+1;
				x = rand()%10+1;
				stop = null;
				for (int i=-1; i<=1; i++) {	////////////// � ������ �������̲ ����� �������// 
					for (int j=-1; j<=1;j++)
						if (Att_Map [y+i][x+j] == hit)
							stop++;
				}
				if(stop != null)
					continue;/////////////////////////////////////////////////////////////////
				if (Att_Map [y][x] != null)			// ���� � ������ 2 ��� 4 (��� ��� ������ �� ��� �����������;
					continue; 
				else if (pl.Ship_Map[y][x] == null) {// ������� ������������� (���� �� ���� ������y���� ���� ������� - ���� ����������� �� ����;             
					Att_Map[y][x] = miss;			 // ��������� ������ (2))
					Again = false;
					break;
				}
				else if (pl.Ship_Map[y][x] != null) {// ������� ����������� (���� �� ���� ������y���� � �������� - ���� ����������� �� ����;                          
					Att_Map[y][x] = hit;			// ��������� ������ (4))
					Y[1] = y;
					X[1] = x;
					Wounded = pl.Ship_Map[y][x];
					pl.Ship_Map[y][x] *= del;
					Again = true;
					break;
				}
			}
		}// (��������� �������� ��������� � ����y ���y�y)
		else if ((Wounded) && (Y[2] == null) && (X[2] == null)) {// ( �������� ��������� � ��y�y ���y�y)
			if ((X[1]+1 < map_finish) && (Att_Map [Y[1]][X[1]+1] == null)) {
				y = Y[1];
				x = X[1]+1;
			}
			else if ((Y[1]+1 < map_finish) && (Att_Map[Y[1]+1][X[1]] == null)) {
				y = Y[1]+1;
				x = X[1];
			}
			else if ((X[1]-1 >= map_start) && (Att_Map[Y[1]][X[1]-1] == null)) { 
				y = Y[1];
				x = X[1]-1;
			}
			else if ((Y[1]-1 >= map_start) && (Att_Map[Y[1]-1][X[1]] == null)) {
				y = Y[1]-1;
				x = X[1];
			}
			if (pl.Ship_Map[y][x] == null) {
				Att_Map[y][x] = miss;
				Again = false;
			}
			else if (pl.Ship_Map[y][x] != null) {
				Att_Map[y][x] = hit;
				Y[2] = y;
				X[2] = x;
				pl.Ship_Map[y][x] *= del;
				Again = true;
			}
		}
		else if ((Y[2] != null ) && (X[2] != null)) { // (�������� ��������� � ����� �� �������y (�� ��������) ���y��)
			if (Y[1] == Y[2]) {
				 if ((X[1]+2 <= 10) && (Att_Map[Y[1]][X[1]+2] == null) && (Att_Map[Y[1]][X[1]+1] != miss)) {
					y = Y[1];
					x = X[1]+2;
				}
				else if ((X[1]+3 <= 10) && (Att_Map[Y[1]][X[1]+3] == null) && (Att_Map[Y[1]][X[1]+1] != miss) && (Att_Map[Y[1]][X[1]+2] != miss)) {
					y = Y[1];
					x = X[1]+3;
				}
				else if ((Att_Map[Y[1]][X[1]-1] == null)) {
					y = Y[1];
					x = X[1]-1;
				}
				else if ((Att_Map[Y[1]][X[1]-2] == null)) {
					y = Y[1];
					x = X[1]-2;
				}
				else if ((Att_Map[Y[1]][X[1]-3] == null)) {
					y=Y[1];
					x=X[1]-3;
				}
			}
			else if (X[1] == X[2]) {
				if ((Y[1]+2<=10) && (Att_Map[Y[1]+2][X[1]] == null) && (Att_Map[Y[1]+1][X[1]] != miss)) {
					y=Y[1]+2;
					x=X[1];
				}
				else if ((Y[1]+3<=10) && (Att_Map[Y[1]+3][X[1]] == null) && (Att_Map[Y[1]+1][X[1]] != miss) && (Att_Map[Y[1]+2][X[1]] != miss)) {
					y = Y[1]+3;
					x = X[1];
				}
				else if ((Att_Map[Y[1]-1][X[1]] == null)) {
					y=Y[1]-1;
					x=X[1];
				}
				else if ((Att_Map[Y[1]-2][X[1]] == null)) {
					y=Y[1]-2;
					x=X[1];
				}
				else if ((Att_Map[Y[1]-3][X[1]] == null)) {
					y=Y[1]-3;
					x=X[1];
				}
			}
			if (pl.Ship_Map[y][x] == null) {
				Att_Map[y][x] = miss;
				Again = false;
			}
			else if (pl.Ship_Map[y][x]!=0) {
				Att_Map[y][x] = hit;
				pl.Ship_Map[y][x] *= del;
				Again = true;
			}
		}
		X[0] = x;                    // ��������� ����� ������� � ������� ���� ������;
		Y[0] = y;                    // ����� ����������� � 3 - 4 ������;
    }

	void Player::Move_Man (Player& check, int y , int x) {
		if (check.Ship_Map[y][x] == null) {// ������� ������������� (���� �� ���� ��������� ���� ������� - ���� ����������� �� ����;
            Att_Map[y][x] = miss;      // ������y���� ������ (2))
            X[0] = x;
            Y[0] = y;
            Again = false;
        }
        else if (check.Ship_Map [y] [x] != null) {// ������� ����������� (���� �� ���� ������y���� � �������� - ���� ����������� �� ����;
            Att_Map [y][x] = hit;          // ��������� ������ (4))
            Wounded = check.Ship_Map [y] [x];
            check.Ship_Map [y][x] *= del;
            Again = true;
            X[0] = x;
            Y[0] = y;
        }
	}

	bool Player::Get_Again () {
		return Again;
	}

	int	Player::Get_X (int ind) {
		return X[ind];
	}

	int	Player::Get_Y (int ind) {
		return Y[ind];
	}

	int Player::Get_Att_Map (int y , int x) {
		return Att_Map [y][x];
	}

	int Player::Get_Wounded () {
		return Wounded;
	}

	template <typename T>
	bool Player::Input (T &ans, int min, int max) {
		if (!(cin >> ans) || ans < min || ans > max) {
			cin.clear();
			while (cin.get() != '\n');
			ans = 0;
			return 0;
		}
		while (cin.get() != '\n');
		if (sizeof (T) == 1) {	// (���� ���) ���������� �������� ������� �� 1251 ������� � 886 �������; 
			if ((ans >= -128) && (ans <= -81))
				ans += 64;
			else if ((ans >= -32) && (ans <= -17))
				ans += 16;
			else if ((ans >= 128) && (ans <= 175))
				ans += 64;
			else if ((ans >= 224) && (ans <= 239))
				ans += 16;
		}
		return 1;
	}
	template bool Player::Input (int&, int, int);
	template bool Player::Input (char&, int, int);

	int Player::Transl (char letter) {//������������� (����� - �����)
		int number = 0;
		switch (letter) {
			case '�':
			case '�':
			number=1;
		break;
			case '�':
			case '�':
			number=2;
		break;
			case '�':
			case '�':
			number=3;
		break;
			case '�':
			case '�':
			number=4;
		break;
			case '�':
			case '�':
			number=5;
		break;
			case '�':
			case '�':
			number=6;
		break;
			case '�':
			case '�':
			number=7;
		break;
			case '�':
			case '�':
			number=8;
		break;
			case '�':
			case '�':
			number=9;
		break;
			case '�':
			case '�':
			number=10;
		break;
            default:
        break;
		}
			return number;
	}

	Player::~Player() {
    }

    Marine_Battle::Marine_Battle (){
		PC_first = false;
        Gameplay ();
    }

    void Marine_Battle::Gameplay() {		
		srand (time(NULL));         
		setlocale(LC_ALL,"Ukrainian");
        while (Intro ()) {	
            while (!PC.Check_Win() && !User.Check_Win()) {
                do {
					if (!PC_first) {
						PC_first = true;
						break;
                    }
                    Attack_Auto ();
				} while (PC.Get_Again());
				do {
					if (PC.Check_Win())
						break;
					Attack_Manual ();
				} while (User.Get_Again());
			}	
		}
    } 

	bool Marine_Battle::Intro() {
		int ans;
		do {
			system ("cls");
            cout<<"          === �������� �I� ===\n";
			cout << "  ���������� �����i��� ������� ���������.\n";
			User.Show_Map(ships);
            cout<<"      [1] ���          [2] ���I�   ";
            if (!User.Input (ans, 1, 2))
				continue;
		} while (ans != 1 && ans != 2);
		if (ans == 2)
			return false;
		do {
			system ("cls");
            cout<<"    �� ���i� ����i ������i ��������i \"[]\":\n\n";
			
			User.Earse_Map(ships);
			User.Put_Ships();
			User.Show_Map(ships);
            cout<<"    [1] ����������  [...] ��I�� �����   ";
            if (!User.Input (ans, 1, 1))
				continue;
        } while (ans != 1);
		User.Earse_Map (attack);
		PC.Earse_Map (attack);
		PC.Earse_Map (ships);
		PC.Put_Ships();
		do {
			system ("cls");
			cout<<"    �����i� ���� - \"*\", ��������� - \"X\":\n\n";
			PC.Show_Map (attack);
			cout<<"    [1] ������ ������  [2] �������� �I�   ";
            if (!PC.Input (ans, 1, 2))
				continue;
		} while ((ans != 1) && (ans!= 2));
		if (ans == 1)
			PC_first = false;
		else
			PC_first = true;
		return true;
	}

	void Marine_Battle::Attack_Auto() {
		bool not_kill = null;
        system ("cls");
        cout<<"����� ������������ ��i�������� �����i�.\n\n";
		PC.Show_Map(attack);
		cout << " . . .";
        system("pause >> void");
        system ("cls");
        PC.Move_AI (User);
		cout<<"����������� �����i��� �� �����������: "<<Letters [PC.Get_X()]<<" "<<PC.Get_Y()<<"\n";
		if (PC.Get_Again()) 
			not_kill = PC.Check_Ship(User);
        if (!PC.Get_Again())
			cout<<"��������!\n";
		else if (not_kill && PC.Get_Again())
			cout<<"�������!\n";
		else {
			cout<<"����!\n";
			PC.Round_Fire (User);
			PC.Earse_Data (no_again);
		}      
        PC.Show_Map(attack);
		cout << " . . .";
        system("pause >> void");
        system ("cls");
		if (PC.Check_Win()) {
            cout<<"C���������� �����i�!\n\n";
            PC.Show_Map(attack);
            cout << " . . .";
            system("pause >> void");
			PC.Earse_Data (all);
			User.Earse_Data (all);
			User.Earse_Map(ships);
        }
	}

    void Marine_Battle::Attack_Manual() {
        int y = null, x = null, not_kill = null;
        char letter;
        do {
            system ("cls");
            if (User.Get_Att_Map (y, x) != null)
                cout<<"�� ��� ����������� �� ��� ���i����.\n\n";
            else if ((User.Get_Y(0) != null) && (User.Get_X(0) != null)) {
                cout << "��� ������i� �����i� �y� " << Letters[User.Get_X(0)] << " " << User.Get_Y(0) <<", ���y�����:\n";
                if (User.Get_Att_Map (User.Get_Y(0), User.Get_X(0)) == miss)
                    cout<<"��������!\n";
                if ((User.Get_Att_Map (User.Get_Y(0), User.Get_X(0)) == hit) && (User.Get_Wounded() == null))
                    cout<<"����!\n";
                if ((User.Get_Att_Map (User.Get_Y(0), User.Get_X(0)) == hit) && (User.Get_Wounded() != null))
                    cout<<"�������!\n";
            }
            else
                cout<<"���� ����� ��i�������� �����i�.\n\n";
			User.Show_Map(attack);
            cout<<"����i�� �i���y �����i��: ";
			if (!User.Input (letter, CHAR_MIN, CHAR_MAX) || !(User.Transl(letter)))
                continue;
            system ("cls");
            cout<<"������� �i���� �����i��: " << letter << "\n\n";
            User.Show_Map(attack);
            cout<<"����i�� ����y �����i��: ";
			if (!User.Input (y, map_start, map_finish))
                continue;
            x = User.Transl(letter);  // ������ �� ������������ ����� �� ��������� ����������;
        }while (User.Get_Att_Map (y, x) != null || (x == null && y == null));
		User.Move_Man (PC, y, x);
        system ("cls");
        cout<<"�y� ��i������� �����i� �� �����������: "<< Letters[x] <<" "<< y <<"\n";
		if (User.Get_Again())
			not_kill = User.Check_Ship(PC);
		if (!User.Get_Again())
			cout<<"��������!\n";
		else if (not_kill && User.Get_Again())
			cout<<"�������!\n";
		else {
			cout<<"����!\n";
			User.Round_Fire (PC);
			User.Earse_Data (wounded);
		}      
		User.Show_Map(attack);
		if (User.Check_Win()) {
			cout<<"�� ���������!\n\n";
			User.Show_Map(attack);
			cout << " . . .";
			system("pause >> void");
			User.Earse_Data (all);
			PC.Earse_Data (all);
			User.Earse_Map(ships);
		}
		cout << " . . .";
		system("pause >> void");
    } // (��������� �������� ������y ������y����);

    Marine_Battle::~Marine_Battle (){
    }

}
