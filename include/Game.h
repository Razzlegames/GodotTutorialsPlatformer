#ifndef GAME_H_
#define GAME_H_

#include "Time.h"

typedef enum GameStates_
{
	PAUSED
}GameStates;

class Game
{
public:
	Time time;
	/** Number of hearts collected */
	int heart_count;
	
	Game()
	{
		heart_count = 0;		
	}
};


#endif /*GAME_H_*/
