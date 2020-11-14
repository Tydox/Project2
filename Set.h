#ifndef _SET
#define _SET
#include "card.h"
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
	bool isValidSet() const;
	bool isEmpty() const;
	bool isSameValueSeries() const;
	bool isSequential() const;
	void printSet() const;
	
};



#endif


