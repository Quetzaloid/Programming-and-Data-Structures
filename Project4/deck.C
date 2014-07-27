#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "deck.h"

using namespace std;

Deck::Deck()
	{
     reset();
   }

void Deck::reset()
	{
     next=0;

     for(int i=0; i<DeckSize; i++)
        {
          deck[i].suit = (Suit)(i/13);
          deck[i].spot = (Spot)(i%13);
        }
	}

void Deck::shuffle(int n)
	{
     next=0;
          
     Card tempDeck[DeckSize];
     int partiNum = min(n, DeckSize-n);

     for(int i=0; i<partiNum; i++)
        {
          tempDeck[2*i] = deck[n+i];
          tempDeck[2*i+1] = deck[i];
        }
     
     int locusPara = (n>(DeckSize-n))?1:2;

     for(int i=0; i<DeckSize-2*partiNum; i++)
        {
          tempDeck[2*partiNum+i] = deck[locusPara*partiNum+i];
        }
     
     for(int i=0; i<DeckSize; i++)
        {
          deck[i] = tempDeck[i];
        }
	}

Card Deck::deal()
   {
     DeckEmpty NoCard;

     if(next<=51)
       {
		   next++;
         return deck[next-1];
       }
     else
       {
         throw NoCard;
       }
   }

int Deck::cardsLeft()
   {
     return 52-next;
   }
