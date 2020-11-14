#include "GameEngine.h"


#include <iostream>
#include <ostream>

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
	//boardSets = new Set*[2]; //construct 2 decks
	//howManySets = 2;

	//boardSets[0] = new Set;
	//boardSets[1] = new Set;
	int counter = 0;
	
	for(int i=1;i<=2;++i)//RUNS ON DECK
	{
		for(int j =1; j<=4;++j)//SYMBOLS
		{

			for(int w=1; w<=13;++w)//NUMBERS
			{
				cards[counter].setCard(initSymbol(j), w);//CREATE ONE CARD
				//boardSets[i-1]->addCard(cards+(counter)); //SAVES CARD IN DECK
				deck.push(cards + (counter));//INSERT NEW CARD INTO DEALER DECK
				++counter;
			}	
		}
		
	}

	initPlayer();
	initSet();
	
	deck.shuffle(); //SHUFFLE DEALER DECK
	
}

char GameEngine::initSymbol(int num) const
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

void GameEngine::printGame() const
{
	//std::cout << " FIRST SET:\n";
	//boardSets[0]->printSet();
	//std::cout << "\n\n SECOND SET:\n";
	//boardSets[1]->printSet();

	deck.printStackForDeBugOnly();
	
}

void GameEngine::createSet()
{

	++howManySets; //ADD 1 TO SET COUNT
	Set** newSet = new Set*[howManySets]; //CREATE A NEW SET

	int i=0;
	for(; i<howManySets; ++i)
	{
	newSet[i] = boardSets[i]; //COPY POINTER
	}

	newSet[i]=new Set(); //CREATE EMPTY SET

	delete[] boardSets; //DELETE OLD SET

	boardSets=newSet; //COPY NEW SET INTO BOARD SET


	
}

void GameEngine::cardToSet(Card** cardBackup,bool endTurn,int backupCounter,Player* player)
{
	/*if(cardBackup==nullptr)
	{
		std::cout << "ERROR NO BACKUP CARD WAS CREATED!!!!!\n";
		return;
	}*/
	
	
	//user data
	int setIndexSrc=0;
	int setIndexDst=0;
	int cardNum=0;
	char cardSym='\0';
	Card* tmpCard=nullptr;

	do
	{
		if (endTurn == false)
		{
			std::cout << "Enter Set Number to add a Card:\n";
			std::cin >> setIndexDst;
		}
		if (isSetValid(setIndexDst))
			continue;

		std::cout << "Enter a Card Number:\n";
		std::cin >> cardNum;

		std::cout << "Enter a Card Symbol[H-Heart,D-Diamond,C-Club,S-Spades]:\n";
		std::cin >> cardSym;

		if (player != nullptr)
		{
			tmpCard = player->extractCard(cardSym, cardNum);
			
		}
		else
		{
			std::cout << "Enter from which Set to remove a card:\n";
			std::cin >> setIndexSrc;

			if (!isSetValid(setIndexSrc))
				continue;

			tmpCard = boardSets[setIndexSrc]->extractCard(cardNum, cardSym);
		}
	}
	while(tmpCard==nullptr);

	if (endTurn == false)
	{
		boardSets[setIndexDst]->addCard(tmpCard); //EXTRACT CARD THEN ADD TO SET
		cardBackup[backupCounter]->setCard(cardBackup[backupCounter]->getSign(),cardBackup[backupCounter]->getValue());
	}
	else
	{
		trash.push(tmpCard);
	}


//	tmpCard=nullptr;//CHECK IF I NEED TO DELETE THE TMPCARD VARIABLE OR NOT
	
	
}

bool GameEngine::isSetValid(int i) const
{
	if(i-1>howManySets)
		{
				std::cout << "ERROR, SET DOES NOT EXIST!\nTRY AGAIN\n";
			return false;
		}
	else
	return true;
}

void GameEngine::endTurn(Set** backupSet,Card** cardBackup,int cardCounter ,Player* player)
{

	int isNotValid=0;
	
	for (int i = 0; i < howManySets; ++i)
	{
		if (!(boardSets[i]->isValidSet()))
		{
			isNotValid = 1;
			break;
		}
	}


	switch (isNotValid)
	{
	case 0://VALID
		{
			cardToSet(nullptr,true,0,player);
			delete[] backupSet;
			delete[] cardBackup;
			break;
		}

	case 1://NOT VALID
		{

			delete[] boardSets;
			boardSets=backupSet;

			for(int i=0;i<cardCounter;++i)
			{

				player->setCard(cardBackup[i]);
			}
			delete[] cardBackup;
			
		}

	}
	
	
}

bool GameEngine::turn(Player* player)
{
	Set** backupSet(boardSets); //COPY BACKUP SETS
	Card**  backupCard = new Card*[14]; //MAX CARDS TO PUT IN SETS
	int backupCardCounter=0;

	Card* tempCardDeck = deck.pop();
	
	std::cout
	<< "Select an Option:\n"
	<< "1)Forfeit - QUIT \n"
	<< "2)Take card from Top Deck - The Card is:[";
	 tempCardDeck->printCard();
	std::cout << "]\n"
	<< "3)Extract a new card from the Trash\n";

	char userOpt='0';

	std::cin >> userOpt;

	switch (userOpt)
	{
	case '1':
		{

		userForfeit(player);
		deck.push(tempCardDeck);
		if (howManyPlayers == 1)
		{
			std::cout << " THE WINNER IS:" << players[0]->getName() << std::endl;
			return false;
		}
		else
			return true;
		}

	case '2':
		{
			player->setCard(tempCardDeck);
			break;
		}

	case '3':
		{
			player->setCard(trash.pop());
			deck.push(tempCardDeck);
			break;
		}
		default:
		{
			std::cout << "WRONG INPUT - TRY AGAIN!\n";
			break;
		}
	}

	

	userOpt='1';
	
	while (userOpt != '0')
	{
		std::cout << "what would you like to do?\n1) Create new set\n2)ADD CARD FROM HAND TO EXISTING SET\n3)Allocate between existing sets\n0)End turn\n";
		std::cin >> userOpt;

		switch (userOpt)
		{
		case '1':
		{
			createSet();
			break;
		}
		case '2':
		{
			cardToSet(backupCard, false, backupCardCounter, player);
			break;
		}
		case '3':
		{
			cardToSet(backupCard, false, backupCardCounter);
			break;
		}
			case '0':
		{
			endTurn(backupSet, backupCard, backupCardCounter, player);
				return !isWinner(player);
			//break;
		}
		default:
		{
			std::cout << "WRONG INPUT - TRY AGAIN!\n";
			break;
		}

		}

	}

	
}

void GameEngine::userForfeit(Player* player)
{
	int flag=player->getNumberOfCards();

	for(int i =0; i<flag;++i)
	{
		deck.push(player->extractCard());
	}

	deck.shuffle();

	delete player;
	--howManyPlayers;

	Player** newPlayers = new Player*[howManyPlayers];
	for(int j=0; j<howManyPlayers;++j)
	{
		newPlayers[j]=players[j];
	}
	delete[] players;
	players=newPlayers;

	
	
}

bool GameEngine::isWinner(Player* player)
{

	if(player->getNumberOfCards()==0)
		return true;
	else
		return false;
}
