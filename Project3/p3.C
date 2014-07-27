#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "world_type.h"
#include "simulation.h"

using namespace std;

int main()
	{
     world_t world;

	  string argcLine;    
	  getline(cin, argcLine);
    
     istringstream iStream;
	  iStream.str(argcLine);
     string Argc[4];
     int n=0;
     bool ifVerbose = 0;
     
     while (iStream>>Argc[n] && n<=4)
        { 
          n++; 
        }
     if (Argc[n-1]=="v" || Argc[n-1]=="verbose")
        {
          ifVerbose = 1;
          if (n<=3)
             {
					 cout<<"Error: Missing arguments!"<<endl
						  <<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
					 exit(1);
             }
		  }
     else if (n<=2)
        {
		    cout<<"Error: Missing arguments!"<<endl
		        <<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
		    exit(1);
        }

     int rounds = atoi(Argc[2].c_str());
     if (rounds < 0)
        {
          cout<<"Error: Number of simulation rounds is negative!"<<endl;
          exit(1);
        }

     initWorld(world, Argc[0], Argc[1]); 
	  cout<<"Initial state"<<endl;
	  printGrid(world.grid);
     
     for (int i=1; i<=rounds; i++)
         {
           cout<<"Round"<<" "<<i<<endl;
           for(int j=0; j<world.numCreatures; j++)
              {
                simulateCreature(world.creatures[j], world.grid, ifVerbose);
              }
           if (ifVerbose == 0)
              {
                printGrid(world.grid);
              }
         }

     return 0;   
	}






