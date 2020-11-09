#include "GameEngine.h"

GameEngine::GameEngine()
{
	initPlayer();
	initSet();
	initCards();

	
}

void GameEngine::initPlayer()
{
	players = nullptr;
	howManyPlayers = 0;
	
}

void GameEngine::initSet()
{
	boardSets = nullptr;
	howManySets = 0;
	
}

void GameEngine::initCards()
{
	boardSets = new Set*[2]; //construct 2 decks
	howManySets = 2;

	boardSets[0] = new Set;
	boardSets[1] = new Set;
	int counter = 0;
	
	for(int i=1;i<=2;++i)//RUNS ON DECK
	{
		for(int j =1; j<=4;++j)//SYMBOLS
		{

			for(int w=1; w<=13;++w)//NUMBERS
			{
				cards[counter].setCard(initSymbol(j), w);//CREATE ONE CARD
				boardSets[i-1]->addCard(cards+(counter)); //SAVES CARD IN DECK
				deck.push(cards + (counter));//INSERT NEW CARD INTO DEALER DECK
				++counter;
			}
			
		}

		
	}
	
	deck.shuffle(); //SHUFFLE DEALER DECK
	
}

char GameEngine::initSymbol(int num)
{
	
	switch (num) {
	case 1 :
		return 'H';
	case 2:
		return 'S';
	case 3:
		return 'C';
	case 4:
		return 'D';
	default:
		{
		std::cout << "ERROR YOU BROKE THIS METHOD\n";
			return NULL;
		}
	}
	
}

void GameEngine::printGame()
{
	//std::cout << " FIRST SET:\n";
	//boardSets[0]->printSet();
	//std::cout << "\n\n SECOND SET:\n";
	//boardSets[1]->printSet();

	deck.printStackForDeBugOnly();
	
}
