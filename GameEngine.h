#ifndef _GAME_ENGINE
#define _GAME_ENGINE

#include "card.h"
#include "cashierStack.h"
#include "Player.h"
#include "Set.h"

class GameEngine
{

private:

	Set** boardBackup;
	int backupSetNum;
	
	
	Set** boardSets;
	int howManySets;

	Player** players;
	int howManyPlayers;

	Card cards[104];
	CashierStack deck;
	CashierStack trash;
	
public:

	GameEngine();
	~GameEngine();
	
	
	void initPlayer();
	void initSet();
	void initCards();
	char initSymbol(int num) const;

	void createSet();
	
	void cardToSet(bool endTurn=false, Card** cardBackup=nullptr,int backupCounter=-1,Player* player=nullptr); //IF PLAYER == NULL, SET TO SET, if PLAYER!=NULL PLAYER HAND TO SET
	bool isSetNotValid(int i) const;
	void endTurn(Card** cardBackup , int cardCounter,int oldsetnum,Player* player=nullptr);

	bool turn(Player* player);
	void userForfeit(Player* player);
	bool isWinner(Player* player) const;

	int findPlayer(Player* player) const;
	void startGame();

	void printSet(Player* player) const;

};



#endif
