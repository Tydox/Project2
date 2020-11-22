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

	void setName(char* name);
	void setCard(Card* card);

	
	Card* extractCard(char char_c = '\0', int int_val = 0);
	
	Card* removeCard(char char_c, int int_val);

	char* getName() const;
	int getNumberOfCards() const;
	void printHand() const;
	bool isEmpty() const;
	
	
};

#endif
