#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"
#include "dlist.C"

using namespace std;

bool isInt(string str);
bool rpnHelper(string str, Dlist<int> &stack);

int main()
	{
     Dlist<int> stack;
     
     string str;
     cin>>str;

     while (str != "q")
        {
          if (isInt(str))
             {
               int *opInt = new int;
               *opInt = atoi(str.c_str());
               stack.insertFront(opInt);
             }
          else if (str == "c")
             {
				   while(!stack.isEmpty())
					  {
						 int *op = stack.removeFront();
						 delete op;
					  }
             }
          else if (str == "a")
             {
					Dlist<int> holder = stack;

					while (!holder.isEmpty())
						{
                    int *item = holder.removeFront();
						  cout << *item << ' ';
						}
					cout<<endl;             
             }
          else if (str=="n" || str=="d" || str=="p" || 
                   str=="+" || str=="-" || str=="*" || str=="/" || str=="r")
             {
               if ( !rpnHelper(str, stack) )
                  {
                    cout<<"Not enough operands\n";
                  }
             }
          else
             {
               cout << "Bad input\n";
             }
			 cin>>str;
        }
     return 0;     
   }

bool isInt(string str)
   { 
     if (str == "-")
        {
          return false;
        }
     if ((str.at(0)>'9' || str.at(0)<'0') && (str.at(0)!='-'))
        { 
          return false; 
        } 
     for(int i=1;i<str.size();i++) 
        {   
          if (str.at(i)>'9' || str.at(i)<'0')
             { 
               return false; 
             } 
        } 
     return true; 
   }

bool rpnHelper(string str, Dlist<int> &stack)
	{
	  if (stack.isEmpty())
		  {
		    return false;
		  }

     int *argA = stack.removeFront();

     if (str == "n")
        {
          *argA = -(*argA);
          stack.insertFront(argA);
        }
     else if (str == "d")
        {
          int *cloneA = new int;
          *cloneA = *argA;
          stack.insertFront(argA);
          stack.insertFront(cloneA);
        }
     else if (str == "p")
        {
          cout<<*argA<<endl;
          stack.insertFront(argA);
        }
     else
        {
			 if (stack.isEmpty())
				 {
				   stack.insertFront(argA);
				   return false;
				 }
          int *argB = stack.removeFront();

          if (str == "+")
             {
               *argB += *argA;
               stack.insertFront(argB);
               delete argA;
             }
          else if (str == "-")
             {
               *argB -= *argA;
               stack.insertFront(argB);
               delete argA;
             }
          else if (str == "*")
             {
               *argB *= *argA;
               stack.insertFront(argB);
               delete argA;
             }
          else if (str == "/")
             {
               if (*argA == 0)
                  {
                    cout << "Divide by zero\n";
                    stack.insertFront(argB);
                    stack.insertFront(argA);
                  }
               else
                  {
				        *argB /= *argA;
				        stack.insertFront(argB);
				        delete argA;
                  }
             }
          else if (str == "r")
             {
               stack.insertFront(argA);
               stack.insertFront(argB);
             }
        }
     return true;
    }
