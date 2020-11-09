#include "Player.h"

Player::~Player()
{
	delete name; //DO I NEED TO USE DELETE[]
	delete[] hand;
}

void Player::setName(char* Name) //XX
{
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
