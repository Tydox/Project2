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
	char initSymbol(int num) const;

	void printGame() const;


	void createSet();
	
	void cardToSet(bool endTurn=false, Card** cardBackup=nullptr,int backupCounter=-1,Player* player=nullptr); //IF PLAYER == NULL, SET TO SET, if PLAYER!=NULL PLAYER HAND TO SET
	bool isSetNotValid(int i) const;
	void endTurn(Set** backupSet,Card** cardBackup , int cardCounter,Player* player=nullptr);
	bool turn(Player* player);
	void userForfeit(Player* player);
	bool isWinner(Player* player) const;

	int findPlayer(Player* player) const;
	void startGame();
};



#endif
