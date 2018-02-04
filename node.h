#ifndef NODE_H
#define NODE_H
using namespace std;
struct node
{
	string state;
	node *parent;
	int action;
	int cost;
	node *next;
};

#endif
