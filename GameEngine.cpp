#include "GameEngine.h"


#include <iostream>
#include <ostream>

GameEngine::GameEngine()
{
	initPlayer();
	initSet();
	initCards();
}

GameEngine::~GameEngine()
{
	
	delete[] boardSets;
	delete[] players;
	//delete[] cards;
	
	
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

	/*initPlayer();
	initSet();*/
	
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

	//deck.printStackForDeBugOnly();
	
}

void GameEngine::createSet()
{

	++howManySets; //ADD 1 TO SET COUNT
	Set** newSet = new Set*[howManySets]; //CREATE A NEW SET

	int i=0;
	if (howManySets - 1 > 0) {
		for (; i < howManySets-1; ++i)
		{
			newSet[i] = boardSets[i]; //COPY POINTER
		}
	}
	newSet[i] = new Set(); //CREATE EMPTY SET

	delete[] boardSets; //DELETE OLD SET

	boardSets=newSet; //COPY NEW SET INTO BOARD SET


	
}

void GameEngine::cardToSet(bool endTurn, Card** cardBackup, int backupCounter, Player* player)
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
		if (endTurn != true)//EXIT LOOP IF END TURN
		{

			std::cout << "Enter Set Number to add a Card:\n"; //NUMBER OF END SET DESTINATION
			std::cin >> setIndexDst;

			if (isSetNotValid(setIndexDst))//IF SET INDEX IS TOO BIG RESTART
				continue;
			std::cout << "Enter a Card Number:\n";
		}
		else std::cout << "Enter a Card Number to remove:\n";

		std::cin >> cardNum;

			std::cout << "Enter a Card Symbol[H-Heart,D-Diamond,C-Club,S-Spades]:\n";
			std::cin >> cardSym; //TO VERIFY IF THE CHAR IS CORRECT WILL HAPPEN IN EXTRACTCARD

			if (player != nullptr)//EXTRACT ONLY IS PASSED A PLAYER
			{
				tmpCard = player->extractCard(cardSym, cardNum);
				
			}
			else
			{
				std::cout << "Enter from which Set to remove a card:\n";
				std::cin >> setIndexSrc;

				if (isSetNotValid(setIndexSrc))//IF SET INDEX IS TOO BIG RESTART
					continue;

				tmpCard = boardSets[setIndexSrc]->extractCard(cardNum, cardSym);
			}
		
	}
	while(tmpCard==nullptr);//ENDS LOOP WHEN A CARD IS EXTRACTED

	if (endTurn == false)
	{
		boardSets[setIndexDst]->addCard(tmpCard); //EXTRACT CARD THEN ADD TO SET
		if (backupCounter > -1 && cardBackup!=nullptr && player!=nullptr) {
			cardBackup[backupCounter]->setCard(tmpCard->getSign(),tmpCard->getValue());
		}
	}
	else
	{
		//Card* tmp = player->extractCard();
		//if (tmp != nullptr) {
			trash.push(tmpCard);
		//}
	}


//	tmpCard=nullptr;//CHECK IF I NEED TO DELETE THE TMPCARD VARIABLE OR NOT
	
	
}

bool GameEngine::isSetNotValid(int i) const
{
	if(i-1>howManySets)
		{
			std::cout << "ERROR, SET DOES NOT EXIST!\nTRY AGAIN\n";
			return true;
		}
	else
	return false;
}

void GameEngine::endTurn(Set** backupSet,Card** cardBackup,int cardCounter, int oldsetnum,Player* player)
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
			cardToSet(true,nullptr,0,player);
			delete[] backupSet;
			delete[] cardBackup;
			break;
		}

	case 1://NOT VALID
		{

			delete[] boardSets;//DELETE OLD SET
			boardSets=backupSet;//ROLLBACK
			howManySets = oldsetnum;
			std::cout << "BOARD SET ARE NOT VALID, INITIATING ROLLBACK!\n";
			
			for(int i=0;i<cardCounter;++i)
			{
				player->setCard(cardBackup[i]);
			}
			
			for (int i = 0; i < cardCounter; ++i)//delete card
				delete cardBackup[i];
			delete[] cardBackup;//DELETE PTR CARDS
			
			cardToSet(true, nullptr, 0, player);
		}

	}
	
	
}

bool GameEngine::turn(Player* player)
{
	Set** backupSet(boardSets); //COPY BACKUP SETS
	Card**  backupCard = new Card*[14]; //MAX CARDS TO PUT IN SETS
	for(int y=0;y<14;++y)
	backupCard[y] = new Card;
	int oldSetNum = howManySets;
	
	int backupCardCounter=0;

	Card* tempCardDeck = deck.pop();
	trash.push(tempCardDeck);
	tempCardDeck = deck.pop();
	char userOpt='9';
	
	while (userOpt != '0')
	{
		std::cout
			<< "\nSelect an Option:\n"
			<< "1)Forfeit - QUIT \n"
			<< "2)Take card from Top Deck - The Card is:[";
		tempCardDeck->printCard();
		std::cout
			<< "]\n"
			<< "3)Extract a new card from the Trash";
		trash.printStackForDeBugOnly();
		

		std::cin >> userOpt;

		switch (userOpt)
		{
		case '1':
		{

			
			tempCardDeck = nullptr; //ASK MAAYAN
			this->userForfeit(player);

			if (howManyPlayers == 1)
			{
				std::cout << "\nTHE WINNER IS:\t" << players[0]->getName() << std::endl;
				return false; //SIGNAL TO END GAME
			}
			else
				return true;
		}

		case '2':
		{
			player->setCard(tempCardDeck);
			tempCardDeck = nullptr;//ASK MAAYAN
			userOpt = '0';
				break;
		}

		case '3':
		{
			deck.push(tempCardDeck);
			tempCardDeck = nullptr;//ASK MAAYAN
			player->setCard(trash.pop());
			userOpt = '0';
				break;
		}
		default:
		{
			std::cout << "WRONG INPUT - TRY AGAIN!\n";
				//userOpt='-1';
			break;
		}
		}

	}

	userOpt='1';
	
	while (userOpt != '0')
	{
		std::cout << "what would you like to do?\n1) Create new set\n2)ADD CARD FROM HAND TO EXISTING SET\n3)Allocate between existing sets\n0)End turn\n";

		printSet(player);

		if (userOpt != '0') {
			std::cin >> userOpt;
		}
		
		switch (userOpt)
		{
		case '1'://Create new set
		{
			createSet(); 
				break;
		}
		case '2'://move card from hand to set
		{
			if (player->getNumberOfCards() == 1)
			{
				std::cout << "Last card, initiating end turn!\n";
				userOpt = '0';
				break;
			}
			cardToSet(false, backupCard, backupCardCounter, player);
			++backupCardCounter;
			
			break;
		}
		case '3'://move card from set to set
		{
			cardToSet(false); 
				break;
		}
		case '0'://end turn
		{	
			endTurn(backupSet, backupCard, backupCardCounter,oldSetNum, player);
			if (isWinner(player))
				return false;
			else 
				return true;
			
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

	int playerIndex = findPlayer(player);
	delete player;
	--howManyPlayers;

	int w = 0;
	
	Player** newPlayers = new Player*[howManyPlayers];

	for (int j = 0; j < howManyPlayers+1; ++j)//COPY OLD ARRAY TO NEW ARRAY
	{
		if (j != playerIndex) {
			newPlayers[w] = players[j];
			++w;
		}
	}
	
	delete[] players; //DELETE OLD ARRAY
	players=newPlayers; //UPDATING POINTER ARRAY

	
	
}

bool GameEngine::isWinner(Player* player) const
{

	if(player->getNumberOfCards()==0)
		return true;
	else
		return false;
}

int GameEngine::findPlayer(Player* player) const
{
	int i = 0;

	for(;i<howManyPlayers;++i)
	{
		if(strcmp(players[i]->getName(),player->getName())==0)
		{
			return i;
		}
		
	}
	return -1;
}

void GameEngine::startGame()
{
	 //CREATE GAME INIT=CARDS,PLAYER,SETS
	//GameEngine newGame;

	do
	{
		std::cout << "Enter The Amount of Players[2 minimum]:\n";
		std::cin >> howManyPlayers;
		if (howManyPlayers < 2)
		{
			std::cout << "ERROR - MINIMUM PLAYER REQUIERMENTS NOT MET!\n\n";
		}
	} while (howManyPlayers < 2);
	
	
	
	players = new Player * [howManyPlayers];
	
	char tmpName[1001]={'\0'};
	
	for(int i=0; i< howManyPlayers;++i)//SET PLAYERS NAME
	{
		players[i] = new Player;
		
		std::cout << "Enter Player ["<<i<<"] Name:\n";
		fseek(stdin, 0, SEEK_END);

		std::cin.clear();
		std::cin.getline(tmpName,1000);

		players[i]->setName(tmpName);

		for(int j=0; j<14;++j)//GIVE PLAYERS 14 CARDS EACH
		{
			players[i]->setCard(deck.pop());

			
		}
	}

	bool gameStatus = true;
	int playersOld = howManyPlayers;
	while(gameStatus)//RUN UNTIL GAME OVER
	{
		for (int i = 0; i < howManyPlayers; ++i)//PLAYER TURNS
		{
			std::cout << "It's " << players[i]->getName() << " turn!\n";
			players[i]->printHand();
			
			gameStatus = this->turn(players[i]);

			
			
			if (!gameStatus)
				break;

			if(howManyPlayers<playersOld)
			{
				--i;
			}
		}
	}

	std::cout << "GAME OVER\nTHANKS FOR PLAYING.\n";


	
}

void GameEngine::printSet(Player* player)
{
	std::cout << "\nCards:\n";
	player->printHand();
	
	
	std::cout << "\nSET:\n";
	for (int i = 0; i < howManySets; ++i)
	{
		std::cout << "Set[" << i << "]: ";
		boardSets[i]->printSet();
	}
	std::cout << "\n---------------------\nOption:";
}

//void GameEngine::test(GameEngine g)
//{
//	this->printSet();
//	g.printSet();
//}
