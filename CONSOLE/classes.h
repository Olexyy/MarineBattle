
#ifndef CLASSES_H               
#define CLASSES_H               
#include <iostream>             
#include <random>               
#include <ctime>				
using namespace std;            
namespace Game {
	enum defs {null , map_start, miss, coord_num, hit, del = 10, map_finish, map_size, all_deck = 20, attack, ships, all, no_again, wounded}; 
    
	const char  Letters [map_size]={'!','À','Á','Â','Ã','Ä','Å','Æ','Ç','Ê','Ë','!'};   
   
	class Player {								
        int     Ship_Map[map_size][map_size];	
		int		Att_Map[map_size][map_size];			    
		bool	Again;							
		int		X [coord_num];					
		int		Y [coord_num];					
		int		Wounded;						
    public:										
        Player     ();							
        void    Earse_Map (defs, int = null);	
		void    Earse_Data (defs);				
        void    Show_Map (defs);				
        bool    Check_Win();					
		void    Put_Ships();					
        bool    Check_Ship (Player &);			
        void    Round_Fire (Player &);			
		void    Move_AI (Player&);				
		void	Move_Man (Player&, int,int);	
		bool	Get_Again ();					
		int		Get_X (int = null);				
		int		Get_Y (int = null);				
		int		Get_Att_Map (int, int);			
		int		Get_Wounded ();					
		int     Transl (char);					
		template<typename T>					
		bool    Input (T&, int, int);			
        ~Player    ();							
    };
    class Marine_Battle {					    
		Player	PC;								
		Player	User;							
		bool	PC_first;						
    public:                                     
                Marine_Battle ();				
		void    Gameplay ();					
		bool	Intro();						
		void    Attack_Auto();					
        void    Attack_Manual();				
				~Marine_Battle ();				
    };                                          
}
#endif // CLASSES_H
