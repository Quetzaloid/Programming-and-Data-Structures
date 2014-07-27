#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "player.h"

using namespace std;

//////////////////////////////For simple player
class Simple:public Player {
   public:
     int  bet(unsigned int bankroll, unsigned int minimum);
     bool draw(Card dealer,const Hand &player);
     void expose(Card c);
     void shuffled();
   } ;

int Simple::bet(unsigned int bankroll, unsigned int minimum)
   {
     return minimum;
   }

bool Simple::draw(Card dealer,const Hand &player)
   {
     switch (player.handValue().soft)
     {
       case 0:
           if (player.handValue().count<=11)
              {
                return 1;
              }
           else if (player.handValue().count==12)
              {
		          if (dealer.spot==FOUR || dealer.spot==FIVE || dealer.spot==SIX)
		             {
		               return 0;
		             }
		          return 1;
              }
           else if (player.handValue().count>=13 && player.handValue().count<=16)
              {
                if (dealer.spot<=4)
                   {
                     return 0;
                   }
                return 1;
              }
           return 0;
           break;
       case 1:
           if (player.handValue().count<=17)
		        {
		          return 1;
		        }
		     else if (player.handValue().count==18)
		        {
		          if(dealer.spot==TWO || dealer.spot==SEVEN || dealer.spot==EIGHT)
		            {
		              return 0;
		            }
		          return 1;
		        }
		     return 0;
           break;
       default:
           return 0;
     }     
     return 0;
	}

void Simple::expose(Card c)
	{
   }

void Simple::shuffled()
   {
   }

//////////////////////////////For counting player
class Counting:public Simple {
     int count;
   public:
     int  bet(unsigned int bankroll, unsigned int minimum);
     void expose(Card c);
     void shuffled();
   } ;

int Counting::bet(unsigned int bankroll, unsigned int minimum)
   {
     if (count>=2 && bankroll>=2*minimum)
        {
          return 2*minimum;
        }
     return minimum; 
   }

void Counting::expose(Card c)
	{
     if (c.spot>=8)
        {
          count--;
        }
     else if (c.spot<=4)
        {
          count++;
        }
     else
        {
        }
   }

void Counting::shuffled()
   {
     count = 0;
   }


///////////////////
static Simple   simplePlayer;
Player *get_Simple()
   {
     return &simplePlayer;
   }

static Counting countingPlayer;
Player *get_Counting()
   {
     return &countingPlayer;
   }
