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

//Implementations

bool initWorld(world_t &world, const string &speciesFile, const string &creaturesFile)
	{
     initSpecies(world, speciesFile);
     initGrid   (world, creaturesFile);
     return true;
    }
// MODIFIES: world
//
// EFFECTS: Initialize "world" given the species summary file
//          "speciesFile" and the world description file
//          "creaturesFile". This initializes all the components of
//          "world". Returns true if initialization is successful.

void initSpecies(world_t &world, const string &speciesFile)
	{
     ifstream iFile;

     iFile.open(speciesFile.c_str());
     if (!iFile)
        {
          cout<<"Error: Cannot open file "<<speciesFile<<"!"<<endl;
          exit(1);
        }
     
	   string temp;
     iFile>>temp;
     int n=0;
     world.numSpecies = 0;
     
     while (iFile>>temp)
        {
          world.numSpecies++;
          if (world.numSpecies > MAXSPECIES)
				 {
               cout<<"Error: Too many species!"<<endl
				       <<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
				   exit(1);
				 }
          world.species[n]=getSpecies(temp);
          n++;
        }
 	  iFile.close();
	}
   //Initialize the species components of "world" given the species summary file "speciesFile".

void initGrid(world_t &world, const string &creaturesFile)
	{
     ifstream iFile;

     iFile.open(creaturesFile.c_str()); 
	  if (!iFile)
        {
          cout<<"Error: Cannot open file "<<creaturesFile<<"!"<<endl;
          exit(1);
        }

     iFile>>world.grid.height>>world.grid.width;
     if (world.grid.height > MAXHEIGHT || world.grid.height < 0 )
        {
          cout<<"Error: The grid height is illegal!"<<endl;
          exit(1);
        }
     else if (world.grid.width > MAXWIDTH || world.grid.width < 0 )
        {
          cout<<"Error: The grid width is illegal!"<<endl;
          exit(1);
        }
     for(int i=0; i<MAXHEIGHT; i++)
        {
          for(int j=0; j<MAXHEIGHT; j++)
             {
               world.grid.squares[i][j] = NULL;
             }
        }

     string temp1, temp2;
	  int temp3, temp4;
     int m=0;
     world.numCreatures = 0;
     
     while (iFile>>temp1>>temp2>>temp3>>temp4)
        {
          world.numCreatures++;
          if (world.numCreatures > MAXCREATURES)
				 {
               cout<<"Error: Too many creatures!"<<endl
				       <<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
				   exit(1);
				 }
          if ( temp3>=world.grid.height || temp4>=world.grid.width || temp3<0 || temp4<0)
             {
               cout<<"Error: Creature ("<<temp1<<" "<<temp2<<" "<<temp3<<" "<<temp4<<") is out of bound!"<<endl
                   <<"The grid size is "<<world.grid.height<<"-by-"<<world.grid.width<<"."<<endl;
               exit(1);
             } 
          
          bool ifFind = 0;
          for(int i=0; i<world.numSpecies; i++)
             {
               if (temp1 == world.species[i].name)
                  {
                    world.creatures[m].location.r = temp3;
                    world.creatures[m].location.c = temp4;
                    if (world.grid.squares[temp3][temp4] != NULL)
                       {
                         cout<<"Error: Creature ("<<temp1<<" "<<temp2<<" "<<temp3<<" "<<temp4<<") overlaps with creature ("
                             <<world.creatures[m-1].species->name<<" "<<directName[world.creatures[m-1].direction]<<" "
                             <<world.creatures[m].location.r<<" "<<world.creatures[m].location.c<<")!"<<endl;
                         exit(1);
                       }

                    if (temp2 == "east")
					        {
                         world.creatures[m].direction = EAST;
					        }
                    else if (temp2 == "south")
					        {
                         world.creatures[m].direction = SOUTH;
					        }
                    else if (temp2 == "west")
					        {
                         world.creatures[m].direction = WEST;
					        }
                    else if (temp2 == "north")
					        {
                         world.creatures[m].direction = NORTH;
					        }
                    else
                       {
                         cout<<"Error: Direction "<<temp2<<" is not recognized!"<<endl;
                         exit(1);
                       }

                    ifFind = 1;

                    world.creatures[m].species = &world.species[i];
                    world.creatures[m].programID = 1;

                    world.grid.squares[temp3][temp4] = &world.creatures[m];
                  }
             }
          if (ifFind == 0)
             {
               cout<<"Error: Species "<<temp1<<" not found!"<<endl;
               exit(1);
             }
          m++;        
        }
 	  iFile.close();
	}
   // EFFECTS: Returns the species with its property in "speciesName"file.


species_t getSpecies(const string speciesName)
	{
     species_t species;
     ifstream iFile;

     if (!iFile)
        {
          cout<<"Error: Cannot open file "<<speciesName<<"!"<<endl;
          exit(1);
        }

     species.name = speciesName;
     species.programSize = 0;
     int n=0;

     iFile.open(speciesName.c_str());
     string line;    
	  getline(iFile, line);

	  while (line.length() != 0)
	     {
          species.programSize++;
          if (species.programSize > MAXPROGRAM)
             {
               cout<<"Error: Too many instructions for species "<<speciesName<<"!"<<endl
                   <<"Maximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
               exit(1);
             }
          istringstream iStream;
			 string foo;
			 int addr=0;
			 iStream.str(line);
			 iStream >> foo >> addr;

          if (foo == "hop")
             {
               species.program[n].op = HOP;
             }
          else if (foo == "left")
             {
               species.program[n].op = LEFT;
             }
          else if (foo == "right")
             {
               species.program[n].op = RIGHT;
             }
          else if (foo == "infect")
             {
               species.program[n].op = INFECT;
             }
          else if (foo == "ifempty")
             {
               species.program[n].op = IFEMPTY;
               species.program[n].address = addr;
             }
          else if (foo == "ifenemy")
             {
               species.program[n].op = IFENEMY;
               species.program[n].address = addr;
             }
          else if (foo == "ifsame")
             {
               species.program[n].op = IFSAME;
               species.program[n].address = addr;
             }
          else if (foo == "ifwall")
             {
               species.program[n].op = IFWALL;
               species.program[n].address = addr;
             }
          else if (foo == "go")
             {
               species.program[n].op = GO;
               species.program[n].address = addr;
             }
          else
             {
               cout<<"Error: Instruction "<<foo<<" is not recognized!"<<endl;
               exit(1);
             }
            
		    n++;
		    getline(iFile, line);
		  }  
     iFile.close(); 

	 return species;
   }
	// EFFECTS: Returns the specie with its program in "nameFile"..


void simulateCreature(creature_t &creature, grid_t &grid, bool verbose)
	{
     cout<<"Creature ("<<creature.species->name<<" "<<directName[creature.direction]<<" "
         <<creature.location.r<<" "<<creature.location.c<<") takes action:";
     if (verbose == 1)
        {
          cout<<endl;
        }
     
     instruction_t curInst;
     
     do
     {
        curInst = getInstruction(creature);
        
        if (verbose == 1)
           {
				 if (curInst.op <= 3)
					 {
						cout<<"Instruction "<<creature.programID<<": "
						    <<opName[curInst.op]<<endl;
					 }
				 else
					 {
						cout<<"Instruction "<<creature.programID<<": "
							 <<opName[curInst.op]<<" "<<curInst.address<<endl;
					 }
           }
		  point_t targetLocus = adjacentPoint(creature.location, creature.direction);

		  switch (curInst.op)
		  {
		    case 0:
		        if (getCreature(grid, targetLocus)==NULL && ifBounded(grid, targetLocus)==1)
		           {
		             grid.squares[targetLocus.r][targetLocus.c] = getCreature(grid, creature.location);
		             grid.squares[creature.location.r][creature.location.c] = NULL;
		             creature.location = targetLocus;
		           }
		        creature.programID++;
		        break;
		    case 1:
		        creature.direction = leftFrom(creature.direction);
		        creature.programID++;
		        break;
		    case 2:
		        creature.direction = rightFrom(creature.direction);
		        creature.programID++;
		        break;
		    case 3:
		        if (getCreature(grid, targetLocus)!=NULL && getCreature(grid, targetLocus)->species != creature.species)
		           {
		             getCreature(grid, targetLocus)->species = creature.species;
		             getCreature(grid, targetLocus)->programID = 1;
		           }
		        creature.programID++;
		        break;
		    case 4:
		        if (getCreature(grid, targetLocus)==NULL && ifBounded(grid, targetLocus)==1) 
		           {
		             creature.programID = curInst.address;
		           }                 
		        else
		           {
		             creature.programID++;
		           }
		        break;
		    case 5:
		        if (ifBounded(grid, targetLocus)==1 && getCreature(grid, targetLocus)!=NULL && getCreature(grid, targetLocus)->species != creature.species)
		           {
		             creature.programID = curInst.address;
		           }
		        else
		           {
		             creature.programID++;
		           }
		        break;
		    case 6:          
		        if (getCreature(grid, targetLocus)!=NULL && getCreature(grid, targetLocus)->species == creature.species)
		           {
		             creature.programID = curInst.address;
		           }
		        else
		           {
		             creature.programID++;
		           }
		        break;
		    case 7:
		        if (ifBounded(grid, targetLocus)==0)
		           {
		             creature.programID = curInst.address;
		           }
		        else
		           {
		             creature.programID++;
		           }
		        break;
		    case 8:
		        creature.programID = curInst.address;
		        break;
		    default:
		        exit(1);          
		  }
     }while(curInst.op >= 4);
  
     if (verbose == 1)
        {
          printGrid(grid);
        }
     else
        {
          cout<<" "<<opName[curInst.op]<<endl;
        }
   }
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS: Simulate one turn of "creature" and update the creature,
//          the infected creature, and the grid if necessary.
//          The creature programID is always updated. The function
//          also prints to the stdout the procedure. If verbose is
//          true, it prints more information.

bool ifBounded(const grid_t &grid, point_t location)
	{
     if (location.r>=grid.height || location.c>=grid.width || location.r<0 || location.c<0)
        {
          return false;
        }
     else
        {
          return true;
        }
   }
   // Check if the given location is out of bound.

void printGrid(const grid_t &grid)
	{
     for(int i=0; i<grid.height; i++)
     	  {
          for(int j=0; j<grid.width; j++)
             {
              if (grid.squares[i][j] == NULL)
                 {
                   cout<<"____ ";
                 }
              else
                 {
                   cout<<abbrName(grid.squares[i][j]->species->name)<<"_"
                       <<directShortName[grid.squares[i][j]->direction]<<" ";
                 }
              if (j == grid.width-1)
                 {
                   cout<<endl; 
                 }
             }
        }
	}
// MODIFIES: cout.
//
// EFFECTS: print a grid representation of the creature world.

string abbrName(const string speciesName)
	{
     char abbr[3];

     abbr[0]=speciesName[0];
     abbr[1]=speciesName[1];
	  abbr[2]='\0';

     return abbr;
	}
   // An array of strings representing the species short name.

point_t adjacentPoint(point_t pt, direction_t dir)
	{
     switch (dir)
     {
       case 0:
           pt.c++;
           break;
       case 1:
           pt.r++;
           break;
       case 2:
           pt.c--;
           break;
       case 3:
           pt.r--;
           break;
       default:
           exit(1);
     }
     return pt;
	}
// EFFECTS: Returns a point that results from moving one square
//          in the direction "dir" from the point "pt".


direction_t leftFrom(direction_t dir)
   {
     switch (dir)
     {
       case 0:
           return NORTH;
           break;
       case 1:
           return EAST;
           break;
       case 2:
           return SOUTH;
           break;
       case 3:
           return WEST;
           break;
       default:
           exit(1);
     }
   }
// EFFECTS: Returns the direction that results from turning
//          left from the given direction "dir".


direction_t rightFrom(direction_t dir)
   {
     switch (dir)
     {
       case 0:
           return SOUTH;
           break;
       case 1:
           return WEST;
           break;
       case 2:
           return NORTH;
           break;
       case 3:
           return EAST;
           break;
       default:
           exit(1);
     }
   }
// EFFECTS: Returns the direction that results from turning
//          right from the given direction "dir".


instruction_t getInstruction(const creature_t &creature)
	{
     return creature.species->program[creature.programID-1];
	}
// EFFECTS: Returns the current instruction of "creature".


creature_t *getCreature(const grid_t &grid, point_t location)
	{
     return grid.squares[location.r][location.c];
   }
// REQUIRES: location is inside the grid.
//
// EFFECTS: Returns a pointer to the creature at "location" in "grid".









