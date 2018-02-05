#ifndef Q_H
#define Q_H
#include "node.h"
using namespace std;

class Q
{
	private :
		node *h;
		bool empty;
		node *t;
	public:
		Q(){h = NULL; t=NULL;empty = true;}
/*
	}*/
		void nQ(node *n)
		{
			if(t == NULL)
			{
				t = n;
				empty = false;
			}
			else 
				n->next = h;
			h = n;
		}


		node *dQ()
		{
			if(t ==NULL)
			{
				node *failure = new node();
				failure->state="FAILURE";
				return failure;
			}
			node *temp = t;

			node *result = new node();
			result->state = temp->state;
			result->parent = temp->parent;
			result->action = temp->action;
			result->cost = temp->cost;

			t = h;
			while(t->next != temp)
			{
				if(t->next == NULL)
				{
					t = NULL;
					empty = true;
					break;
				}
				else
					t = t->next;
			}
			//delete temp;
			return result;
		}

		bool is_empty(){return empty;}
};
#endif
