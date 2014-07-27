#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "hand.h"

using namespace std;

Hand::Hand()
   {
     discardAll();
   }

void Hand::discardAll()
   {
     curValue.count=0;
     curValue.soft=0;
   }

void Hand::addCard(Card c)
   {
     if (c.spot<=8)
        {
          curValue.count += (c.spot+2);
        }
     else if (c.spot<=11)
        {
          curValue.count += 10;
        }
     else
        {
		    if (curValue.soft==1)
			    {
		         curValue.count += 1; 
			    }
			 else
			    {
               curValue.count += 11;
               curValue.soft=1;
			    }
        }

	  if (curValue.count>21 && curValue.soft==1)
	     {
	       curValue.count -= 10;
			 curValue.soft=0;
	     }
	}

HandValue Hand::handValue() const
   {
     return curValue;
   }

