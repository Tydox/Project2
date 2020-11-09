

#ifndef _PLAYER
#define _PLAYER

#include "card.h"
#include <cstring>
#include <iostream>
#include "Set.h"

class Player
{
private:
	int numInHand;
	char* name;
	Card** hand;


public:
	 Player(char* name); //default constructor
	~Player();//destructor

	void setName(char* Name);
	void setCard(Card* card);
	Card* extractCard(char char_c, int int_val);
	char* getName();
	int getNumberOfCards();
	void printHand();


};

#endif
