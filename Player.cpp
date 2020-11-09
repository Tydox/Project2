#include "Player.h"

Player::Player() //INIT WHEN NO NAME IS GIVEN
{
		name = nullptr;
		numInHand = NULL;
		hand = nullptr;
}

Player::Player(char* Name)//INIT WITH GIVEN NAME
{
	setName(Name);
	numInHand = 0;
	hand = nullptr;
}

Player::~Player()
{
	delete[] name; //DO I NEED TO USE DELETE[]
	delete[] hand;
}

void Player::setName(char* Name) //XX
{
	if (name == NULL)
	{
		std::cout << "ERROR NO NAME IS GIVEN\nNOTHING TO DO\n";
		return;
	}
	
	name = new char[strlen(Name) + 1]; //ALLOCATED MEM
	strcpy_s(name, strlen(Name)+1, Name); //COPY NAME //CHECK IF WORKING!!!!!!!
}

void Player::setCard(Card* card) //XX
{
	if (card == nullptr)//END CONDITION
	{
		std::cout << "GIVEN CARD IS NULL\n";
		return;
	}

	++numInHand; //INCREASE CARD SIZE BY 1

	Card** newCards = new Card*[numInHand]; //NEW ARRAY TO COPY

	for (int i = 0; i < numInHand - 1; ++i) //copy cards pointers from s to our array
	{
		newCards[i] = hand[i];
	}

	newCards[numInHand-1] = card; //IMPORT POINTER TO LAST ARRAY POSITION - CHECK WARNINGS
	delete[] hand;//EMPTY ORIGINAL ARRAY
	
	hand = newCards;//SAVE THE NEW ARRAY IN THE ORIGINAL VALUE
}

Card* Player::extractCard(char char_c, int int_val)
{
	//CONTINUE ONLY IF NUM && SYMBOL ARE CORRECT
	if (char_c == '\0' || (char_c != 'C' && char_c != 'H' && char_c != 'D' && char_c != 'S'))//END CONDITION
	{
		std::cout << "ERROR NO CHAR WAS ENTERED\nNothing TO DO\n";
		return nullptr;
	}
	if (int_val == 0 || !(int_val>0 && int_val <14))//END CONDITION
	{
		std::cout << "ERROR NO CARD NUMBER WAS ENTERED\nNothing TO DO\n";
		return nullptr;
	}

	
	return removeCard(char_c,int_val);//VALUES ARE VALID THUS CONTINUING TO REMOVE
}

Card* Player::extractCard()
{
	return removeCard('R', 0); //R - REMOVE, 0 - FIRST CARD 
}

Card* Player::removeCard(char char_c, int int_val)
{

	int cardIndex = -1; //IF VAL is -1 NO CARD WAS FOUND - END CONDITION MET

	if (char_c == 'R' && int_val == 0) //FIRST CARD REMOVAL - SPECIAL CASE
		cardIndex = 0;
	else
	{
		for (int j = 0; j < numInHand; ++j) //FIND MATCHING CARD IN THE hand ARRAY
		{
			if (hand[j]->getValue() == int_val && hand[j]->getSign() == char_c)
			{
				cardIndex = j;
				break;
			}
		}
	}
	
	if (cardIndex == -1)
	{
		std::cout << "NO CARD WAS FOUND\n";
		return nullptr; //RETURN FALSE END CONDITION
	}

	Card* removedCard = hand[cardIndex]; //KEEP THE POINTER OF THE REMOVED CARD

	--numInHand;//REDUCE SIZE BY -1
	Card** newhand = new Card * [numInHand]; //CREATE A NEW ARRAY IN NEW SIZE

	int w = 0;
	for (int i = 0; i < numInHand; ++i) //COPY CARD POINTERS
	{
		if (i != cardIndex)
		{
			newhand[w++] = hand[i];
		}
	}

	delete[] hand; //DELETE OLD

	hand = newhand; //REPLACE OLD DELETED ARRAY WITH NEW ARRAY

	return removedCard; //RETURN TRUE CARD THAT WAS FOUND
	
}

char* Player::getName()
{
	return name;
}

int Player::getNumberOfCards()
{
	return numInHand;
}

void Player::printHand()
{
	if (isEmpty()) //END CONDITION
	{
		std::cout << "HAND IS EMPTY\n";
		return;
	}

	for (int i = 0; i < numInHand; ++i)
	{
		hand[i]->printCard();

		if (i != numInHand - 1) // MAKES SURE WE DONT HAVE , ON THE LAST PRINT
			std::cout << ","; //CHECK IF , IS NEEDED BECAUSE UNSURE OF PRINTCARD METHOD
	}
}


bool Player::isEmpty()
{
	if (hand == nullptr)
	{
		std::cout << "Cards Array not initialized\n"; //4DEBUG
		return false;
	}

	if (numInHand > 0) //if we have any cards return yay
		return true;
	else
		return false;
}
