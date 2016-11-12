using System;

namespace Marine.Battle
{
    enum defs { attack, ships, all, no_again, wounded, horizontal, vertical};

    class Player
    {
        public const int all_decks = 20;

        public const int map_size = 12;

        public const int map_finish = 11;

        public const int buffer_size = 10;

        public const int hit = 4;

        public const int coord_num = 3;

        public const int miss = 2;

        public const int map_start = 1;

        public const int empty = 0;

        public const int earsed = 100;

        private int [,] Ship_Map ;

        private int [,] Att_Map ;

        private int [] X;

        private int [] Y;

        private bool Again;

        private int	Wounded;

        private char [,] Buffer;

        public Player()
        {
            this.Ship_Map = new int [map_size, map_size];
            this.Att_Map = new int [map_size, map_size];
            this.X = new int [coord_num];
            this.Y = new int [coord_num];
            Earse_Map (defs.attack);
            Earse_Map (defs.ships);
            Earse_Data (defs.all);
            this.Wounded = empty;
            this.Buffer = new char [buffer_size, buffer_size];
        }

        public void Clarify_Map(Player opponent)
        {
            for (int y = empty; y < map_size; y++)
                for (int x = empty; x < map_size; x++) 
                    if (this.Att_Map [y, x] == empty)
                        this.Att_Map [y, x] = opponent.Ship_Map [y, x];
        }

        public void Earse_Map (defs mode, int num = empty)
        {
            for (int y = empty; y < map_size; y++)
                for (int x = empty; x < map_size; x++)
                {
                    if (mode == defs.attack)
                        this.Att_Map [y, x] = empty;    
                    else
                        this.Ship_Map[y, x] = empty;
                }
        }

        public void Earse_Data (defs mode)
        {
            if (mode == defs.all)
                this.Again = false;
            this.Wounded = empty;
            if (mode == defs.all || mode == defs.no_again)
            {
                for (int i = empty; i < coord_num; i++) 
                {
                    this.Y [i] = empty;
                    this.X [i] = empty;
                }
            }
        }

        public void Map_To_Buffer (defs mode)
        {
            for (int i = map_start; i < map_finish; i++)
            {
                for (int j = map_start; j < map_finish; j++)
                {
                    if (mode == defs.attack)
                    {
                        if (this.Att_Map [i, j] >= hit)
                           this.Buffer [i-1, j-1] = 'X';
                        if (this.Att_Map [i, j] == miss)
                           this.Buffer [i-1, j-1] = '*';
                        if (this.Att_Map [i, j] == empty)
                           this.Buffer [i-1, j-1] = ' ';
                    }
                    else
                    {
                        if (this.Ship_Map [i, j] >= hit)
                           this.Buffer [i-1, j-1] = 'X';
                        if (this.Ship_Map [i, j] == miss)
                           this.Buffer [i-1, j-1] = '*';
                        if (this.Ship_Map [i, j] == empty)
                           this.Buffer [i-1, j-1] = ' ';
                    }
                }
            }
        }

        public bool Check_Win()
        {
            int counter = empty;
            for (int i = empty; i < map_finish; i++)
            {
                for (int j = empty; j < map_finish; j++)
                {
                    if (Att_Map [i, j] == hit)
                        counter ++;
                }
            }
            return (counter == all_decks)? true : false;
        }

        private void Ship_Mapper (int decks_count, int ship_count)
        {
            Random rand = new Random();
            int x, y, direction, again;
            for (int times = 1; times <= ship_count; times ++)
            {
                while(true)
                {
                    x = rand.Next(1, 11);
                    y = rand.Next(1, 11);
                direction = rand.Next(1, 11);
                again = empty;
                    if (direction%2 == empty)
                    {
                        for (int i = -1; i <= 1; i++)
                        {
                            for (int j = -1; j <= decks_count; j++)
                            {
                                if ((x+j > 10) || (this.Ship_Map[y+i, x+j] != empty))
                                    again++;
                            }
                        }
                    }
                    else {
                        for (int i = -1; i <= decks_count; i++)
                        {
                            for (int j = -1; j <= 1; j++)
                            {
                                if ((y+i > 10) || (this.Ship_Map[y+i, x+j] != empty))
                                    again++;
                            }
                        }
                    }
                    if (again != empty)
                            continue;
                    if (direction%2 == empty)
                    {
                        for (int i = empty; i < decks_count; i++)
                            this.Ship_Map[y, x+i] = decks_count * 10 + times;
                        break;
                    }
                    else
                    {
                        for (int i = empty; i < decks_count; i++)
                            this.Ship_Map[y+i, x] = decks_count * 10 + times;
                        break;
                    }
                }
            }
        }

        public void Put_Ships()
        {
            this.Ship_Mapper (4, 1);
            this.Ship_Mapper (3, 2);
            this.Ship_Mapper (2, 3);
            this.Ship_Mapper (1, 4);
        }

        public bool Check_Ship (Player opponent)
        {
            for (int i = map_start; i < map_finish; i++)
            {
                for (int j = map_start; j < map_finish; j++)
                {
                    if (opponent.Ship_Map [i, j] == this.Wounded)
                        return true;
                }
            }
            return false;
        }

        public void Round_Fire (Player opponent)
        {
            for (int i = map_start; i < map_finish; i++)
            {
                for (int j = map_start; j < map_finish; j++)
                {
                    if (opponent.Ship_Map [i, j] == (Wounded * earsed))
                    {
                        for (int y = -1; y <= 1; y++)
                        {
                            for (int x = -1; x <= 1; x++)
                            {
                                if (this.Att_Map [i+y, j+x] == empty)
                                    this.Att_Map [i+y, j+x] = miss;
                            }
                        }
                    }
                }
            }
        }

        public void Move_AI (Player opponent)
        {
            Random rand = new Random();
            int y , x , again;
            y = x = again = empty;
            if (this.Wounded == empty)
            {   // перша палуба                                  
                while (true)
                {
                    y = rand.Next (1, 11);
                    x = rand.Next (1, 11);
                    again = empty;
                    for (int i = -1; i <= 1; i++)
                    {	                                           
                        for (int j = -1; j <= 1; j++)
                            if (this.Att_Map[y+i, x+j] == hit)
                                again++;
                    }
                    if(again != empty)
                        continue;
                    if (this.Att_Map [y, x] != empty)			
                        continue;
                    else if (opponent.Ship_Map[y, x] == empty)
                    {                                               
                        this.Att_Map[y, x] = miss;			    
                        this.Again = false;
                        break;
                    }
                    else if (opponent.Ship_Map[y, x] != empty)
                    {                                               
                        this.Att_Map[y, x] = hit;			   
                        this.Y[1] = y;
                        this.X[1] = x;
                        this.Wounded = opponent.Ship_Map[y, x];
                        opponent.Ship_Map[y, x] *= earsed;
                        this.Again = true;
                        break;
                    }
                }
            }                                               
            else if ((this.Wounded > empty) && (this.Y[2] == empty) && (this.X[2] == empty))
            {     // друга палуба               
                if ((this.X[1]+1 < map_finish) && (this.Att_Map [Y[1], X[1]+1] == empty))
                {
                    y = this.Y[1];
                    x = this.X[1]+1;
                }
                else if ((this.Y[1]+1 < map_finish) && (this.Att_Map[Y[1]+1, X[1]] == empty))
                {
                    y = this.Y[1]+1;
                    x = this.X[1];
                }
                else if ((this.X[1]-1 >= map_start) && (this.Att_Map[Y[1], X[1]-1] == empty))
                {
                    y = this.Y[1];
                    x = this.X[1]-1;
                }
                else if ((this.Y[1]-1 >= map_start) && (this.Att_Map[Y[1]-1, X[1]] == empty))
                {
                    y = this.Y[1]-1;
                    x = this.X[1];
                }
                if (opponent.Ship_Map[y, x] == empty)
                {
                    this.Att_Map[y, x] = miss;
                    this.Again = false;
                }
                else if (opponent.Ship_Map[y, x] != empty) {
                    this.Att_Map[y, x] = hit;
                    this.Y[2] = y;
                    this.X[2] = x;
                    opponent.Ship_Map[y, x] *= earsed;
                    this.Again = true;
                }
            }
            else if ((this.Y[2] != empty ) && (this.X[2] != empty))
            { // 3-4 палуби
                if (this.Y[1] == this.Y[2])
                {
                    if ((this.X[1]+2 <= 10) && (this.Att_Map[Y[1], X[1]+2] == empty) && (this.Att_Map[Y[1], X[1]+1] != miss))
                    {
                        y = this.Y[1];
                        x = this.X[1]+2;
                    }
                    else if ((this.X[1]+3 <= 10) && (this.Att_Map[Y[1], X[1]+3] == empty) && (this.Att_Map[Y[1], X[1]+1] != miss) && (this.Att_Map[Y[1], X[1]+2] != miss))
                    {
                        y = this.Y[1];
                        x = this.X[1]+3;
                    }
                    else if ((this.Att_Map[Y[1], X[1]-1] == empty))
                    {
                        y = this.Y[1];
                        x = this.X[1]-1;
                    }
                    else if ((this.Att_Map[Y[1], X[1]-2] == empty))
                    {
                        y = this.Y[1];
                        x = this.X[1]-2;
                    }
                    else if ((this.Att_Map[Y[1], X[1]-3] == empty))
                    {
                        y = this.Y[1];
                        x = this.X[1]-3;
                    }
                }
                else if (this.X[1] == this.X[2]) {
                    if ((this.Y[1]+2 <= 10) && (this.Att_Map[Y[1]+2, X[1]] == empty) && (this.Att_Map[Y[1]+1, X[1]] != miss))
                    {
                        y = this.Y[1]+2;
                        x = this.X[1];
                    }
                    else if ((this.Y[1]+3 <= 10) && (this.Att_Map[Y[1]+3, X[1]] == empty) && (this.Att_Map[Y[1]+1, X[1]] != miss) && (this.Att_Map[Y[1]+2, X[1]] != miss))
                    {
                        y = this.Y[1]+3;
                        x = this.X[1];
                    }
                    else if ((this.Att_Map[Y[1]-1, X[1]] == empty))
                    {
                        y = this.Y[1]-1;
                        x = this.X[1];
                    }
                    else if ((this.Att_Map[Y[1]-2, X[1]] == empty))
                    {
                        y = this.Y[1]-2;
                        x = this.X[1];
                    }
                    else if ((this.Att_Map[Y[1]-3, X[1]] == empty))
                    {
                        y = this.Y[1]-3;
                        x = this.X[1];
                    }
                }
                if (opponent.Ship_Map[y, x] == empty)
                {
                    this.Att_Map[y, x] = miss;
                    this.Again = false;
                }
                else if (opponent.Ship_Map[y, x] != empty)
                {
                    this.Att_Map[y, x] = hit;
                    opponent.Ship_Map[y, x] *= earsed;
                    this.Again = true;
                }
            }
            this.X[0] = x;                          
            this.Y[0] = y;                         
        }

        public void Move_Manual (Player opponent, int y , int x)
        {
            if (opponent.Ship_Map[y, x] == empty)
            {                                   
                this.Att_Map[y, x] = miss; 
                this.X[0] = x;
                this.Y[0] = y;
                this.Again = false;
            }
            else if (opponent.Ship_Map [y, x] != empty)
            {                                   
                this.Att_Map [y, x] = hit;
                this.Wounded = opponent.Ship_Map [y, x];
                opponent.Ship_Map [y, x] *= earsed;
                this.Again = true;
                this.X[0] = x;
                this.Y[0] = y;
            }
        }

        public bool Get_Again ()
        {
            return this.Again;
        }

        public int Get_X (int index = empty)
        {
            return this.X[index];
        }

        public int Get_Y (int index = empty)
        {
            return this.Y[index];
        }

        public int Get_Att_Map (int y , int x)
        {
            return this.Att_Map [y, x];
        }

        public int Get_Wounded ()
        {
            return this.Wounded;
        }

        public char[,] Get_Buffer()
        {
            return this.Buffer;
        }
    };

    class MBCore
    {
        private Player PC;

        private Player User;

        public MBCore ()
        {
            PC = new Player();
            User = new Player();
        }

        public delegate void Send_Map_Delegate(char[,] Map, String Whose, String What);

        public event Send_Map_Delegate Send_Map;

        public delegate void Send_Results_Delegate(String Whose, String Result);

        public event Send_Results_Delegate Send_Results;

        public void Generate_Map_Handler(String Whose)
        {
            if (Whose.Equals ("User"))
            {
                this.User.Earse_Map(defs.attack);
                this.User.Earse_Map(defs.ships);
                this.User.Put_Ships();
            }
            else
            {
                this.PC.Earse_Map(defs.attack);
                this.PC.Earse_Map(defs.ships);
                this.PC.Put_Ships();
            }
         }

        public void Request_Map_Handler(String Whose, String What)
        {
             if (Whose.Equals ("User") && What.Equals ("Attack"))
             {
                 this.User.Map_To_Buffer(defs.attack);
                 this.Send_Map(this.User.Get_Buffer(), "User", "Attack");
             }
             else if(Whose.Equals ("User") && What.Equals ("Ships"))
             {
                 this.User.Map_To_Buffer(defs.ships);
                 this.Send_Map(this.User.Get_Buffer(), "User", "Ships");
             }
             else if (Whose.Equals ("PC") && What.Equals ("Attack"))
             {
                 this.PC.Map_To_Buffer(defs.attack);
                 this.Send_Map(this.PC.Get_Buffer(), "PC", "Attack");
             }
             else
             {
                 this.PC.Map_To_Buffer(defs.ships);
                 this.Send_Map(this.PC.Get_Buffer(), "PC", "Ships");
             }
        }

        public void PC_Move_Handler()
        {
            bool not_kill = false;
            this.PC.Move_AI (this.User);
            if (this.PC.Get_Again() == true)
                not_kill = this.PC.Check_Ship(this.User);        
            if (this.PC.Get_Again() == false)
                this.Send_Results("PC", "Miss");
            else if (not_kill == true && this.PC.Get_Again() == true) 
                this.Send_Results("PC", "Wound");
            else {
                this.PC.Round_Fire (this.User);
                this.PC.Earse_Data (defs.no_again);
                if (this.PC.Check_Win() == true)
                {
                    this.PC.Clarify_Map(this.User);
                    this.Send_Results("PC", "Win");
                }
                else
                    this.Send_Results("PC", "Kill");
            }
        }

        public void User_Move_Handler(int y, int x)
        {
            bool not_kill = false;
            if (this.User.Get_Att_Map(y,x) > Player.empty)
            {
                this.Send_Results("User", "Already");
                return;
            }
            this.User.Move_Manual (this.PC, y, x);
            if (this.User.Get_Again() == true)
                not_kill = this.User.Check_Ship(this.PC);
            if (this.User.Get_Again() == false)
                this.Send_Results("User", "Miss");
            else if (not_kill == true && this.User.Get_Again() == true)
                this.Send_Results("User", "Wound");
            else
            {
                User.Round_Fire (this.PC);
                User.Earse_Data (defs.wounded);
                if (this.User.Check_Win() == true)
                {
                    this.User.Clarify_Map(this.PC);
                    this.Send_Results("User", "Win");
                }
                else
                    this.Send_Results("User", "Kill");
            }
        }
    };
}
