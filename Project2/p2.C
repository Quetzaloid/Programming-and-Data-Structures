#include <iostream>
#include <cassert>
#include "recursive.h"

using namespace std;


//LIST
static int size_helper(list_t list, int l_size)
	{
     if (list_isEmpty(list) == 1)
        {
          return l_size;
        }
     else
        {
          return size_helper(list_rest(list), l_size+1);
        }
   }

int size(list_t list)
	{
     return size_helper(list, 0);
	}
/////////////////////

static int getNth_helper(list_t list, int n, int l_Nth)
	{
     if (n <= 0)
     	  {
          return l_Nth;
        }
     else
        {
          return getNth_helper(list_rest(list), n-1, list_first(list));
        }
	}

int getNth(list_t list, int n)
	{
     assert(list_isEmpty(list) == 0 && n>=1);
	  return getNth_helper(list, n, list_first(list));
   }
//////////////////

static int sum_helper(list_t list, int l_sum)
   {
     if (list_isEmpty(list) == 1)
        {
          return l_sum;
        }
     else 
        {
          return sum_helper(list_rest(list), l_sum+list_first(list));
        }
	}

int sum(list_t list)
   {
     return sum_helper(list, 0);
   }
/////////////////////

static int product_helper(list_t list, int l_product)
   {
     if (list_isEmpty(list) == 1)
        {
          return l_product;
        }
     else 
        {
          return product_helper(list_rest(list), l_product*list_first(list));
        }
	}

int product(list_t list)
   {
     return product_helper(list, 1);
   }
///////////////////

static int accumulate_helper(list_t list, int (*fn)(int, int), int result)
	{
     if (list_isEmpty(list) == 1)
        {
          return result;
        }
     else 
        {
          return accumulate_helper( list_rest(list), fn, fn(result, list_first(list)));
        }     
   }

int accumulate(list_t list, int (*fn)(int, int), int base)
	{
     return accumulate_helper(list, fn, base);
	}
///////////////////

static list_t reverse_helper(list_t list, list_t Revlist)
	{
     if (list_isEmpty(list) == 1)
        {
          return Revlist;
        }
     else
        {
          return reverse_helper(list_rest(list), list_make(list_first(list), Revlist));
        }
   }

list_t reverse(list_t list)
   {
     return reverse_helper(list, list_make());
   }
///////////////////

static list_t append_helper(list_t Appendix, list_t Applist)
	{
     if (list_isEmpty(Appendix) == 1)
        {
          return Applist;
        }
     else
        {
          return append_helper(list_rest(Appendix), list_make(list_first(Appendix), Applist));
        }
   }

list_t append(list_t first, list_t second)
   {
     return append_helper(reverse(first), second);
   }
//////////////////////

static list_t filter_odd_helper(list_t list, list_t Oddlist)
   {
     if (list_isEmpty(list) == 1)
        {
          return reverse(Oddlist);
        }
     else if (list_first(list) % 2 == 0)
        {
          return filter_odd_helper(list_rest(list), Oddlist);
        }
     else
        {
          return filter_odd_helper(list_rest(list), list_make(list_first(list), Oddlist));
        }
   }

list_t filter_odd(list_t list)
	{
     return filter_odd_helper(list, list_make());
	}
///////////////////////////

static list_t filter_even_helper(list_t list, list_t Evenlist)
   {
     if (list_isEmpty(list) == 1)
        {
          return reverse(Evenlist);
        }
     else if (list_first(list) % 2 == 1)
        {
          return filter_even_helper(list_rest(list), Evenlist);
        }
     else
        {
          return filter_even_helper(list_rest(list), list_make(list_first(list), Evenlist));
        }
   }

list_t filter_even(list_t list)
	{
     return filter_even_helper(list, list_make());
	}
/////////////////////////////

static list_t filter_helper(list_t list, bool (*fn)(int), list_t result)
   {
     if (list_isEmpty(list) == 1)
        {
          return reverse(result);
        }
     else if (fn(list_first(list)) == 0)
        {
          return filter_helper(list_rest(list), fn, result);
        }
     else
        {
          return filter_helper(list_rest(list), fn, list_make(list_first(list), result));
        }
   }

list_t filter(list_t list, bool (*fn)(int))
	{
     return filter_helper(list, fn, list_make());
    }
///////////////////////////

static list_t insert_list_helper(list_t first, list_t second, unsigned int n, list_t Inslist)
	{
     if (list_isEmpty(first)==1 && list_isEmpty(second)==1 && n <= 0)
        {
          return reverse(Inslist);
        }
     else if (list_isEmpty(second)==1 && n <= 0)
        {
          return insert_list_helper(list_rest(first), second, n, list_make(list_first(first), Inslist));
        }
     else if (n<=0)
        {
          return insert_list_helper(first, list_rest(second), n, list_make(list_first(second), Inslist));
        }
     else
        {
          return insert_list_helper(list_rest(first), second, n-1, list_make(list_first(first), Inslist));
        }
	}

list_t insert_list(list_t first, list_t second, unsigned int n)
	{
     assert(n<= size(first));
     return insert_list_helper(first, second, n, list_make());
   }
///////////////////////////

static list_t removeNth_helper(list_t list, unsigned int n, list_t Remolist)
   {
     if (list_isEmpty(list)==1)
        {
          return reverse(Remolist);
        }
     else if (n == 1)
        {
          return removeNth_helper(list_rest(list), n-1, Remolist);
        }
     else
        {
          return removeNth_helper(list_rest(list), n-1, list_make(list_first(list), Remolist));
        }
   }

list_t removeNth(list_t list, unsigned int n)
	{
     assert(n<= size(list));
     return removeNth_helper(list, n, list_make());
   }
/////////////////////////////

static list_t chop_helper(list_t Revlist, unsigned int n, list_t Choplist)
	{
     if (list_isEmpty(Revlist)==1 && n<=0)
        {
          return Choplist;
        } 
     else if (n<=0)
        {
			 return chop_helper(list_rest(Revlist), n, list_make(list_first(Revlist), Choplist));
        }
     else
        {
			 return chop_helper(list_rest(Revlist), n-1, Choplist);
        }
   }

list_t chop(list_t list, unsigned int n)
	{
     assert(n<= size(list));
     return chop_helper(reverse(list), n, list_make());
   }
/////////////////////////////////


//TREE
int tree_sum(tree_t tree)
	{
     if (tree_isEmpty(tree) == 1)
		  {
		    return 0;
		  }
     else
        {
          return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
        }
	}
//////////////////////////

bool tree_search(tree_t tree, int key)
   {
     if (tree_isEmpty(tree) == 1)
		  {
		    return 0;
		  }  
     else if (tree_elt(tree) == key)
        {
          return 1;
        }
     else
        {
          return tree_search(tree_left(tree), key) | tree_search(tree_right(tree), key);
        }  
   }
////////////////////////////

static int depth_helper(tree_t tree, int t_depth)
   {
     if (tree_isEmpty(tree) == 1)
		  {
		    return t_depth;
		  }
     else
        {
		    t_depth++;
          return max( depth_helper(tree_left(tree), t_depth), depth_helper(tree_right(tree), t_depth));
        }  
   }

int depth(tree_t tree)
   {
     return depth_helper(tree, 0);
   }
///////////////////////////

static int tree_min_helper(tree_t tree, int t_min)
	{
     if (tree_isEmpty(tree) == 1)
		  {
		    return t_min;
		  }
     else 
        {
          t_min = min(t_min, tree_elt(tree));
          return min(tree_min_helper(tree_left(tree), t_min), tree_min_helper(tree_right(tree), t_min));
        }
	}

int tree_min(tree_t tree)
	{
     assert(tree_isEmpty(tree) == 0);
     return tree_min_helper(tree, tree_elt(tree));
   }
/////////////////////////////

list_t traversal(tree_t tree)
	{
		if (tree_isEmpty(tree))
			{
			  return list_make();
			}
		else
			{
			  return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
			}
	}
////////////////////////////

bool tree_hasPathSum(tree_t tree, int sum)
   {
     if (tree_isEmpty(tree) == 1)
		  {
		    if (sum == 0)
             {
               return 1;
             }
          else
             {
               return 0;
             }
		  }
     else
        {
          sum -= tree_elt(tree);
          return tree_hasPathSum(tree_left(tree), sum) | tree_hasPathSum(tree_right(tree), sum);
        }  
   }
////////////////////////////

tree_t mirror(tree_t tree)
	{
		if (tree_isEmpty(tree))
			{
			  return tree;
			}
		else
			{
			  return tree_make(tree_elt(tree),mirror(tree_right(tree)), mirror(tree_left(tree)));
			}
   }
///////////////////////////

bool covered_by(tree_t A, tree_t B)
   {
     if (tree_isEmpty(A) == 1)
        {
          return 1;
        }
     else if (tree_isEmpty(B) == 1)
        {
          return 0;
        }
     else if (tree_elt(A) != tree_elt(B))
        {
          return 0;
        }
     else
        {
          return covered_by(tree_left(A), tree_left(B)) & covered_by(tree_right(A), tree_right(B));
        }
   }
//////////////////////////

bool contained_by(tree_t A, tree_t B)
	{
     if (covered_by(A, B) == 1)
        {
          return 1;
        }
     else if (tree_isEmpty(B) == 1)
        {
          return 0;
        }
     else
        {
          return contained_by(A, tree_left(B)) | contained_by(A, tree_right(B));
        }
   }
//////////////////////////

tree_t insert_tree(int elt, tree_t tree)
	{
     if (tree_isEmpty(tree) == 1)
        {
          return tree_make(elt, tree_make(), tree_make());
        }
     else if (elt < tree_elt(tree))
        {
          return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
        }
     else
        {
          return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
        }
	}

//////////////////End
//////////////////Syoung
