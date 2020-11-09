

#ifndef _PLAYER
#define _PLAYER

#include "Set.h"
#include "card.h"
#include <cstring>
#include <iostream>


class Player
{
private:
	int numInHand;
	char* name;
	Card** hand;


public:
	Player(); //default constructor

	Player(char* name); //default constructor
	~Player();//destructor

	void setName(char* Name);
	void setCard(Card* card);

	Card* extractCard();
	Card* extractCard(char char_c = '\0', int int_val = 0);
	
	Card* removeCard(char char_c, int int_val);

	char* getName();
	int getNumberOfCards();
	void printHand();
	bool isEmpty();
	
	
};

#endif
