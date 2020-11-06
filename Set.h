#ifndef _SET
#define _SET
#include "Card.h"
#include <iostream>

class Set
{
	private:
	int howManyCards;
	Card** cards;

	public:
	Set(); //constructor default
	Set(Set& s); //copy constructor
	~Set(); //destructor
	
	void addCard(Card* c); //add a new card to set
	Card* extractCard(int int_val, char char_c);
	bool isValidSet();
	bool isEmpty();
	bool isSameValueSeries();
	bool isSequential();
	void printSet();
	
};



#endif


