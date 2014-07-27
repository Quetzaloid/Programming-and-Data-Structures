#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include"deck.h"
#include"card.h"
#include"hand.h"
#include"rand.h"
#include"player.h"

using namespace std;


void driver(unsigned int bankroll, int hands, Player *STplayer);
void shuffle(Deck &deck, Player *player);

///////////////////////////////main program
int main(int argc, char *argv[])
   {
     int bankroll = atoi(argv[1]);
     int hands = atoi(argv[2]);
     string player = argv[3];
     
     if (player == "simple")
        {
	       driver(bankroll, hands, get_Simple());
        }
     else if (player == "counting")
        {
	       driver(bankroll, hands, get_Counting());
        }
	  return 0;
   }

void driver(unsigned int bankroll, int hands, Player *STplayer)
   {
     Deck myDeck;
     Hand dealer, player;
     int minBet = 5;
     int thishand = 0;
    
     shuffle(myDeck, STplayer);
     
     while( bankroll>=minBet && (thishand+1)<=hands )
        {
		    thishand++;
          cout << "Hand " << thishand << " bankroll " << bankroll << endl;
          player.discardAll();
          dealer.discardAll();
          
          if (myDeck.cardsLeft()<20)
             {
               shuffle(myDeck, STplayer);
             }

          int wager=STplayer->bet(bankroll,minBet);
          cout << "Player bets " << wager << endl;

          Card pCard;
          Card dCard; 
			 Card holeCard;
          /////1st card
          pCard=myDeck.deal();
          player.addCard(pCard);
          cout<< "Player dealt "<< SpotNames[pCard.spot]<< " of "<< SuitNames[pCard.suit]<<endl;
          STplayer->expose(pCard);
          /////2nd card
          dCard=myDeck.deal();
          dealer.addCard(dCard);
          cout<< "Dealer dealt "<< SpotNames[dCard.spot]<< " of "<< SuitNames[dCard.suit]<<endl;
          STplayer->expose(dCard);
          /////3rd card
          pCard=myDeck.deal();
          player.addCard(pCard);
          cout<< "Player dealt "<< SpotNames[pCard.spot]<< " of "<< SuitNames[pCard.suit]<<endl;
          STplayer->expose(pCard);
          /////4th card
          holeCard=myDeck.deal();
          dealer.addCard(holeCard);

          if(player.handValue().count==21)
            {
              cout << "Player dealt natural 21\n";
              bankroll=bankroll+wager*3/2;
            }
          else 
            {
              while(STplayer->draw(dCard, player)==1)
                 { 
                   Card plusCard=myDeck.deal();
                   player.addCard(plusCard);
                   cout<< "Player dealt " << SpotNames[plusCard.spot] << " of " << SuitNames[plusCard.suit] <<endl;
                   STplayer->expose(plusCard);
                 }
              cout << "Player's total is " << player.handValue().count << endl;
              if (player.handValue().count>21)
                 {
                   cout << "Player busts\n";
                   bankroll=bankroll-wager;
                 }
              else
                 {
                   cout<< "Dealer's hole card is " << SpotNames[holeCard.spot] << " of " << SuitNames[holeCard.suit] << endl;
                   STplayer->expose(holeCard);
                   while(dealer.handValue().count<17)
                      { 
                        Card plusCard=myDeck.deal();
                        dealer.addCard(plusCard);
                        cout<< "Dealer dealt " << SpotNames[plusCard.spot] << " of " << SuitNames[plusCard.suit] <<endl;
                        STplayer->expose(plusCard);
                      }
                   cout << "Dealer's total is " << dealer.handValue().count << endl;
                   if (dealer.handValue().count>21)
                      {
                        cout << "Dealer busts\n";
                        bankroll=bankroll+wager;
                      }
                   else
                      {
                        if (player.handValue().count>dealer.handValue().count)
                           {
                             cout << "Player wins\n";
                             bankroll=bankroll+wager;
                           }
                        else if(player.handValue().count<dealer.handValue().count)
                           {
                             cout << "Dealer wins\n";
                             bankroll=bankroll-wager;
                           }
                        else
                           {
                             cout << "Push\n";
                           }
                      }                 
                 }   
            }
        }
     cout<< "Player has "<< bankroll<< " after "<< thishand<< " hands\n";
   }

void shuffle(Deck &deck, Player *player)
	{  
     cout<<"Shuffling the deck\n";   
     for(int i=0; i<7; i++)
        {
          int n=get_cut();
          deck.shuffle(n);
          cout <<"cut at "<< n << endl;
        }
     player->shuffled();
	}













