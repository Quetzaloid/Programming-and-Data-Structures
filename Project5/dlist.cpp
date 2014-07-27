#ifndef __DLIST_C__
#define __DLIST_C__

#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"

using namespace std;

template <typename T>
bool Dlist<T>::isEmpty()
   {
     return !first;
   }

template <class T>
void Dlist<T>::insertFront(T *op)
   {
     node *InsF = new node;
     InsF->prev = NULL;
     InsF->next = NULL;
     InsF->op = op;

     if (isEmpty())
        {        
          first = last = InsF;
        }
     else
        {
          first->prev = InsF;
		    InsF->next = first;
		    first = InsF;
        }
   }

template <class T>
void Dlist<T>::insertBack(T *op)
   {
     node *InsB = new node;
     InsB->prev = NULL;
     InsB->next = NULL;
     InsB->op = op;

     if (isEmpty())
        {        
          first = last = InsB;
        }
     else
        {
          last->next = InsB;
		    InsB->prev = last;
		    last = InsB;
        }
   }

template <class T>
T *Dlist<T>::removeFront()
   {
     if (isEmpty())
        {
          emptyList e;
          throw e;
        }
     node *victim = first;
     T *result = NULL;
     first = victim->next;
     if (first)
        {
          first->prev = NULL;
        }
     else
        {
          last = NULL;
        }
     result = victim->op;
     delete victim;
     return result;
   }

template <class T>
T *Dlist<T>::removeBack()
   {
     if (isEmpty())
        {
          emptyList e;
          throw e;
        }
     node *victim = last;
     T *result = NULL;
     last = victim->prev;
     if (last)
        {
          last->next = NULL;
        }
     else
        {
          first = NULL;
        }
     result = victim->op;
     delete victim;
     return result;
   }

template <class T>
Dlist<T>::Dlist()
        :first(0), last(0)
   {
   }

template <class T>
Dlist<T>::Dlist(const Dlist &l)
        :first(0), last(0)
   {
     copyAll(l);
   }

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l)
   {
     if(this != &l)
       {
         removeAll();
         copyAll(l);
       }
     return *this;
   }

template <class T>
Dlist<T>::~Dlist()
   {
     removeAll();
   }

template <class T>
void Dlist<T>::removeAll()
   {
     while(!isEmpty())
       {
         T *op = removeFront();
         delete op;
       }
   }

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l)
   {
    	node *curNode = l.first;
    
    	while (curNode)
    	  {
    		 insertBack((curNode->op));
    		 curNode = curNode->next;
    	  }
   }

#endif /* __DLIST_C__ */

