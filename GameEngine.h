#ifndef _GAME_ENGINE
#define _GAME_ENGINE
#include "card.h"
#include "CashierStack.h"
#include "Player.h"
#include "Set.h"

//class Player;
//class Set;

class GameEngine
{

private:

	Set** boardSets;
	int howManySets;

	Player** players;
	int howManyPlayers;

	Card cards[104];
	CashierStack deck;
	CashierStack trash;
	
public:

	GameEngine();

	void initPlayer();
	void initSet();
	void initCards();
	char initSymbol(int num);

	void printGame();
	
};



#endif
