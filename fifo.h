#ifndef FIFO_H
#define FIFO_H

struct node
{
	string tiles;
	node *next;
};

class fifo
{
private:
	node *start;
	node *end;
public:
	fifo(){start=NULL;end=NULL;}

	void enque(string str)
	{
		node *newnode = new node();
		newnode->tiles = str;
		newnode->next = NULL;

		if(start == NULL)
			start = newnode;
		else
			end->next = newnode;
		end = newnode;
	}

	string deque()
	{
		node *temp = start;
		string result = start->tiles;

		start = start->next;
		delete temp;

		return result;
};
#endif
	
