
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
                    cout<<"А   ";
                if ((i==0) && (j==2))
                    cout<<"Б   ";
                if ((i==0) && (j==3))
                    cout<<"В   ";
                if ((i==0) && (j==4))
                    cout<<"Г   ";
                if ((i==0) && (j==5))
                    cout<<"Д   ";
                if ((i==0) && (j==6))
                    cout<<"Е   ";
                if ((i==0) && (j==7))
                    cout<<"Ж   ";
                if ((i==0) && (j==8))
                    cout<<"З   ";
                if ((i==0) && (j==9))
                    cout<<"К   ";
                if ((i==0)&&(j==10))
                    cout<<"Л  ";
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
		while(true) { // чотирьохпалyбний;
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
                Ship_Map[y][x]=41;		// ідентифікатор палуби корабля (унікальний для корабля);
                Ship_Map[y][x+1]=41;	// ідентифікатор палуби корабля (унікальний для корабля);
                Ship_Map[y][x+2]=41;	// ідентифікатор палуби корабля (унікальний для корабля);
                Ship_Map[y][x+3]=41;	// ідентифікатор палуби корабля (унікальний для корабля);
                break;
            }
            else {
                Ship_Map[y][x]=41;		// ідентифікатор палуби корабля (унікальний для корабля);
                Ship_Map[y+1][x]=41;	// ідентифікатор палуби корабля (унікальний для корабля);
                Ship_Map[y+2][x]=41;	// ідентифікатор палуби корабля (унікальний для корабля);
                Ship_Map[y+3][x]=41;	// ідентифікатор палуби корабля (унікальний для корабля);
                break;
            }
		}
		ship_num ++;
		for (int times = 1; times <= 2; times ++) { // трьохпалyбні (2 шт.);
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
                        Ship_Map[y][x]=30+times;	// ідентифікатор палуби корабля (унікальний для корабля);
                        Ship_Map[y][x+1]=30+times;	// ідентифікатор палуби корабля (унікальний для корабля);
                        Ship_Map[y][x+2]=30+times;	// ідентифікатор палуби корабля (унікальний для корабля);
                        break;
                }
                else {
                        Ship_Map[y][x]=30+times;	// ідентифікатор палуби корабля (унікальний для корабля);
                        Ship_Map[y+1][x]=30+times;	// ідентифікатор палуби корабля (унікальний для корабля);
                        Ship_Map[y+2][x]=30+times;	// ідентифікатор палуби корабля (унікальний для корабля);
                        break;
                }
            }
            ship_num ++;
		}
		for (int times = 1; times <= 3; times ++) { // двохпалyбні (3 шт.);
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
                        Ship_Map[y][x]= 20+times;	// ідентифікатор палуби корабля (унікальний для корабля);
                        Ship_Map[y][x+1]= 20+times; // ідентифікатор палуби корабля (унікальний для корабля);
                        break;
                }
                else {
                        Ship_Map[y][x]= 20+times;	// ідентифікатор палуби корабля (унікальний для корабля);
                        Ship_Map[y+1][x]= 20+times; // ідентифікатор палуби корабля (унікальний для корабля);
                        break;
                }
            }
            ship_num ++;
		}
        for (int times = 1; times <= 4; times ++) { // однопалyбні (4 шт.);
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
            Ship_Map[y][x] = 10+times;	// ідентифікатор палуби корабля (унікальний для корабля);
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
			while (true) { // (алгоритм попадання в першy палyбy)
				y = rand()%10+1;
				x = rand()%10+1;
				stop = null;
				for (int i=-1; i<=1; i++) {	////////////// В ДАНОМУ АЛГОРИТМІ НЕМАЄ ПОТРЕБИ// 
					for (int j=-1; j<=1;j++)
						if (Att_Map [y+i][x+j] == hit)
							stop++;
				}
				if(stop != null)
					continue;/////////////////////////////////////////////////////////////////
				if (Att_Map [y][x] != null)			// якщо в ячейці 2 або 4 (вже був постріл по цих координатах;
					continue; 
				else if (pl.Ship_Map[y][x] == null) {// сценарій непотрапляння (якщо на карті користyвача немає корабля - місце позначається на карті;             
					Att_Map[y][x] = miss;			 // компютера цифрою (2))
					Again = false;
					break;
				}
				else if (pl.Ship_Map[y][x] != null) {// сценарій потрапляння (якщо на карті користyвача є корабель - місце позначається на карті;                          
					Att_Map[y][x] = hit;			// компютера цифрою (4))
					Y[1] = y;
					X[1] = x;
					Wounded = pl.Ship_Map[y][x];
					pl.Ship_Map[y][x] *= del;
					Again = true;
					break;
				}
			}
		}// (закінчився алгоритм попадання в першy палyбy)
		else if ((Wounded) && (Y[2] == null) && (X[2] == null)) {// ( алгоритм попадання в дрyгy палyбy)
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
		else if ((Y[2] != null ) && (X[2] != null)) { // (алгоритм попадання в третю та четвертy (за наявності) палyби)
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
		X[0] = x;                    // занесення даних пострілу у відповідні поля гравця;
		Y[0] = y;                    // кінець потрапляння в 3 - 4 палуби;
    }

	void Player::Move_Man (Player& check, int y , int x) {
		if (check.Ship_Map[y][x] == null) {// сценарій непотрапляння (якщо на карті компютера немає корабля - місце позначається на карті;
            Att_Map[y][x] = miss;      // користyвача цифрою (2))
            X[0] = x;
            Y[0] = y;
            Again = false;
        }
        else if (check.Ship_Map [y] [x] != null) {// сценарій потрапляння (якщо на карті користyвача є корабель - місце позначається на карті;
            Att_Map [y][x] = hit;          // компютера цифрою (4))
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
		if (sizeof (T) == 1) {	// (якщо чар) приведення введених символів до 1251 таблиці з 886 таблиці; 
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

	int Player::Transl (char letter) {//транслітератор (цифри - букви)
		int number = 0;
		switch (letter) {
			case 'А':
			case 'а':
			number=1;
		break;
			case 'Б':
			case 'б':
			number=2;
		break;
			case 'В':
			case 'в':
			number=3;
		break;
			case 'Г':
			case 'г':
			number=4;
		break;
			case 'Д':
			case 'д':
			number=5;
		break;
			case 'Е':
			case 'е':
			number=6;
		break;
			case 'Ж':
			case 'ж':
			number=7;
		break;
			case 'З':
			case 'з':
			number=8;
		break;
			case 'К':
			case 'к':
			number=9;
		break;
			case 'Л':
			case 'л':
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
            cout<<"          === МОРСЬКИЙ БIЙ ===\n";
			cout << "  Координати необхiдно вводити кирилецею.\n";
			User.Show_Map(ships);
            cout<<"      [1] ГРА          [2] ВИХIД   ";
            if (!User.Input (ans, 1, 2))
				continue;
		} while (ans != 1 && ans != 2);
		if (ans == 2)
			return false;
		do {
			system ("cls");
            cout<<"    На Вашiй картi кораблi позначенi \"[]\":\n\n";
			
			User.Earse_Map(ships);
			User.Put_Ships();
			User.Show_Map(ships);
            cout<<"    [1] ПРОДОВЖИТИ  [...] ЗМIНА КАРТИ   ";
            if (!User.Input (ans, 1, 1))
				continue;
        } while (ans != 1);
		User.Earse_Map (attack);
		PC.Earse_Map (attack);
		PC.Earse_Map (ships);
		PC.Put_Ships();
		do {
			system ("cls");
			cout<<"    Пострiл мимо - \"*\", попадання - \"X\":\n\n";
			PC.Show_Map (attack);
			cout<<"    [1] ПОЧАТИ ПЕРШИМ  [2] ПЕРЕДАТИ ХIД   ";
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
        cout<<"Черга супротивника здiйснювати пострiл.\n\n";
		PC.Show_Map(attack);
		cout << " . . .";
        system("pause >> void");
        system ("cls");
        PC.Move_AI (User);
		cout<<"Супротивник вистрiлив по координатах: "<<Letters [PC.Get_X()]<<" "<<PC.Get_Y()<<"\n";
		if (PC.Get_Again()) 
			not_kill = PC.Check_Ship(User);
        if (!PC.Get_Again())
			cout<<"Промазав!\n";
		else if (not_kill && PC.Get_Again())
			cout<<"Поранив!\n";
		else {
			cout<<"Вбив!\n";
			PC.Round_Fire (User);
			PC.Earse_Data (no_again);
		}      
        PC.Show_Map(attack);
		cout << " . . .";
        system("pause >> void");
        system ("cls");
		if (PC.Check_Win()) {
            cout<<"Cупротивник перемiг!\n\n";
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
                cout<<"По цим координатам Ви вже стрiляли.\n\n";
            else if ((User.Get_Y(0) != null) && (User.Get_X(0) != null)) {
                cout << "Ваш останнiй пострiл бyв " << Letters[User.Get_X(0)] << " " << User.Get_Y(0) <<", резyльтат:\n";
                if (User.Get_Att_Map (User.Get_Y(0), User.Get_X(0)) == miss)
                    cout<<"Промазав!\n";
                if ((User.Get_Att_Map (User.Get_Y(0), User.Get_X(0)) == hit) && (User.Get_Wounded() == null))
                    cout<<"Вбив!\n";
                if ((User.Get_Att_Map (User.Get_Y(0), User.Get_X(0)) == hit) && (User.Get_Wounded() != null))
                    cout<<"Поранив!\n";
            }
            else
                cout<<"Ваша черга здiйснювати пострiл.\n\n";
			User.Show_Map(attack);
            cout<<"Введiть лiтерy пострiлу: ";
			if (!User.Input (letter, CHAR_MIN, CHAR_MAX) || !(User.Transl(letter)))
                continue;
            system ("cls");
            cout<<"Введена лiтера пострiлу: " << letter << "\n\n";
            User.Show_Map(attack);
            cout<<"Введiть цифрy пострiлу: ";
			if (!User.Input (y, map_start, map_finish))
                continue;
            x = User.Transl(letter);  // захист від неправильних даних та повторним попаданням;
        }while (User.Get_Att_Map (y, x) != null || (x == null && y == null));
		User.Move_Man (PC, y, x);
        system ("cls");
        cout<<"Бyв здiйснений пострiл по координатах: "<< Letters[x] <<" "<< y <<"\n";
		if (User.Get_Again())
			not_kill = User.Check_Ship(PC);
		if (!User.Get_Again())
			cout<<"Промазав!\n";
		else if (not_kill && User.Get_Again())
			cout<<"Поранив!\n";
		else {
			cout<<"Вбив!\n";
			User.Round_Fire (PC);
			User.Earse_Data (wounded);
		}      
		User.Show_Map(attack);
		if (User.Check_Win()) {
			cout<<"Ви перемогли!\n\n";
			User.Show_Map(attack);
			cout << " . . .";
			system("pause >> void");
			User.Earse_Data (all);
			PC.Earse_Data (all);
			User.Earse_Map(ships);
		}
		cout << " . . .";
		system("pause >> void");
    } // (закінчився алгоритм пострілy користyвача);

    Marine_Battle::~Marine_Battle (){
    }

}
