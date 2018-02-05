#ifndef PRIQ_H
#define PRIQ_H
#include "node.h"
using namespace std;

class priQ
{
private: 
	node *h;
	bool empty;
public:
	priQ(){h = NULL;empty = true;}

	bool is_empty(){return empty;}

	void add(node *n)
	{
		empty = false;
		node *temp;
		if(h == NULL || n->cost < h->cost)
		{
			n->next = h;
			h = n;
		}
		else
		{
			temp = h;
			while(h->next != NULL && temp->next->cost <= n->cost)
			{
				temp = temp->next;
				if(temp->next == NULL) break;
			}
			n->next = temp->next;
			temp->next = n;
		}
	}

	node *get_min()
	{
		node *temp;
		if(h == NULL)
		{
			empty = true;
			cout << "it's all fucked\n";
			return NULL;
		}
		else
		{
			temp = h;
			h = h->next;
		}
		return temp;
	}


};
#endif
