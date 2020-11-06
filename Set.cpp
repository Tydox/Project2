﻿#include "Set.h"

Set::Set()
{
	howManyCards=0; //init to 0
	cards = nullptr; // init to null pointer
	
}

Set::Set(Set& s)
{
	howManyCards = s.howManyCards; //copy nums of cards

	cards = new Card*[howManyCards]; //create a new card set

	for(int i=0; i<howManyCards;++i) //copy cards pointers from s to our array
	{
		cards[i] = s.cards[i];
	}
	
}

Set::~Set()
{
	howManyCards=0; //reset value of cards to 0
	delete[] cards; //delete the array only but not the data of pointers
	
}

void Set::addCard(Card* c)
{
	if(c==nullptr)//END CONDITION
	{
		std::cout << "GIVEN CARD IS NULL\n";
		return;
	}

	++howManyCards; //INCREASE CARD SIZE BY 1

	Card** newCards = new Card*[howManyCards]; //NEW ARRAY TO COPY

	for(int i=0; i<howManyCards-1;++i) //copy cards pointers from s to our array
	{
		newCards[i] = cards[i];
	}

	newCards[howManyCards]= c; //IMPORT POINTER TO LAST ARRAY POSITION - CHECK WARNINGS
	delete[] cards;//EMPTY ORIGINAL ARRAY

	cards=newCards;//SAVE THE NEW ARRAY IN THE ORIGINAL VALUE
	
	
}

Card* Set::extractCard(int int_val, char char_c)
{

	int cardIndex = -1; //IF VAL is -1 NO CARD WAS FOUND - END CONDITION MET

	for (int j = 0; j < howManyCards; ++j) //FIND MATCHING CARD IN THE CARDS ARRAY
	{
		if (cards[j]->getValue() == int_val && cards[j]->getSign() == char_c)
		{
			cardIndex = j;
			break;
		}
	}

	Card* removedCard = cards[cardIndex]; //KEEP THE POINTER OF THE REMOVED CARD

	--howManyCards;//REDUCE SIZE BY -1
	Card** newCards = new Card*[howManyCards]; //CREATE A NEW ARRAY IN NEW SIZE

	for(int i=0; i<howManyCards; ++i) //COPY CARD POINTERS
	{
		if(i!=cardIndex)
		{
			newCards[i]=cards[i];
		}
	}

	delete [] cards;

	cards=newCards;
	
	if(cardIndex==-1)
		return nullptr; //RETURN FALSE END CONDITION
	else
		return removedCard; //RETURN TRUE CARD THAT WAS FOUND
}

bool Set::isValidSet()
{
	if(isSameValueSeries()||isSequential())
		return true;
	else	
		return false;
}

bool Set::isEmpty()
{
	if(cards==nullptr)
	{
		std::cout << "Cards Array not initialized\n"; //4DEBUG
		return false;
	}

	if(howManyCards>0) //if we have any cards return yay
		return true;
	else
		return false;
}

bool Set::isSameValueSeries()
{
	if (howManyCards > 4 || howManyCards < 3) //END CONDITION
		return false;


	//SHAPE FLAG
	int h = 0; //heart
	int s = 0; //spade
	int c = 0; //club
	int d = 0; //diamond


	for (int i = 0; i < howManyCards; ++i) //CAN ONLY RUN WHEN THE NUMBER OF CARDS IS EITHER 3 OR 4
	{
		if (cards[i]->getValue() != cards[i + 1]->getValue())
			return false;

		switch (cards[i]->getSign())
		{
		case 'H':
			++h;
			break;
		case 'S':
			++s;
			break;
		case 'C':
			++c;
			break;
		case 'D':
			++d;
			break;
		}

	}

	if (h > 1 || s > 1 || c > 1 || d > 1) //IF ONE OF THE FLAGS IS OVER 1 THEN A SYMBOL IS DUPED
		return false;
	else
		return true;
}

bool Set::isSequential() //CAN WE CHANGE THE ORDER OF THE DECK
{	
	if(howManyCards<3) //END CONDITION
		return false;
	
	//Card** minSorted = new Card*[howManyCards];

	Card* tmp;
	
	for(int i=0; i<howManyCards;++i)//SORT SET BY ORDER SMALL->BIG
	{
		for(int j=i+1;j<howManyCards;++j)
		{
			if(cards[i]->getValue() > cards[j]->getValue())
			{
				tmp=cards[i];
				cards[i]=cards[j];
				cards[j]=tmp;
				
			}
		}
	}

	
	for(int i=0;i<howManyCards-1;++i) //CHECK IF THE SET INCREASES BY INCREMENT OF 1 && SYMBOL ELSE RETURN FALSE
	{
		if(((cards[i+1]->getValue()-cards[i]->getValue())!=1) && (cards[i+1]->getSign()!=cards[i]->getSign()))
			return false;
	}

	return true;
	
}

void Set::printSet()
{

	if(isEmpty()) //END CONDITION
		std::cout << "Empty Serial\n";


	for(int i=0; i<howManyCards;++i)
	{
		cards[i]->printCard();

		if(i!=howManyCards-1) // MAKES SURE WE DONT HAVE , ON THE LAST PRINT
		std::cout <<","; //CHECK IF , IS NEEDED BECAUSE UNSURE OF PRINTCARD METHOD
	}
	
}
