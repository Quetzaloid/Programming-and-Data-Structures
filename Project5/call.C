#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"
#include "dlist.C"

using namespace std;

struct Client
   {
     string Name;
     string status;
     int duration;
   };

int main()
	{
     int numEvents;
     cin>>numEvents;

     int curEvents = 0;
     int tick = 0;
     int inBusy = 0;
     int tStamp;
     cin>>tStamp;

     Dlist<Client> Regular;
     Dlist<Client> Silver;
     Dlist<Client> Gold;
     Dlist<Client> Platinum;

     while (curEvents < numEvents || inBusy >=0)
        {
          cout << "Starting tick #" << tick << endl;

          while (curEvents < numEvents && tStamp == tick)
             {
               Client *curCall = new Client;
               cin>> curCall->Name>> curCall->status>> curCall->duration;
               cout<< "Call from "<< curCall->Name<< " a "<< curCall->status<< " member"<<endl;
               if (curCall->status == "regular")
                  {
                    Regular.insertBack(curCall);
                  }
               else if(curCall->status == "silver")
                  {
                    Silver.insertBack(curCall);
                  }
               else if(curCall->status == "gold")
                  {
                    Gold.insertBack(curCall);
                  }
               else
                  {
                    Platinum.insertBack(curCall);
                  }
					cin>>tStamp;
               curEvents++;
             }

          if (inBusy <= 0)
             {
               if (!Platinum.isEmpty())
                  {
                    Client *ansCall = Platinum.removeFront();
                    cout<< "Answering call from "<< ansCall->Name<<endl;
                    inBusy = ansCall->duration;
                    delete ansCall;
                  }
               else if (!Gold.isEmpty())
                  {
                    Client *ansCall = Gold.removeFront();
                    cout<< "Answering call from "<< ansCall->Name<<endl;
                    inBusy = ansCall->duration;
                    delete ansCall;
                  }
               else if (!Silver.isEmpty())
                  {
                    Client *ansCall = Silver.removeFront();
                    cout<< "Answering call from "<< ansCall->Name<<endl;
                    inBusy = ansCall->duration;
                    delete ansCall;
                  }
               else if (!Regular.isEmpty())
                  {
                    Client *ansCall = Regular.removeFront();
                    cout<< "Answering call from "<< ansCall->Name<<endl;
                    inBusy = ansCall->duration;
                    delete ansCall;
                  }
             }
          tick++;
          inBusy--;
        }
	}
