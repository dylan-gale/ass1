#include <iostream>
#include <string>
#include "Q.h"
#include <cmath>
#include <fstream>
using namespace std;

bool goal(string);
node *child_gen(node*,int,int);
int Hash(string);
node *bfs(string);
int main(int argc, char *argv[])
{
	node *goal_state;
	if(argv[1][0] == 'B')
	{
		goal_state = bfs(argv[2]); 
		cout << "Final Results for BFS:\n";
	}


	while(goal_state->action != -1)
	{
		goal_state->parent->next = goal_state;
		goal_state = goal_state->parent;
	}
	cout << goal_state->state << endl;
	int iter = 0;
	while(!goal(goal_state->state))
	{
		goal_state = goal_state->next;
		cout << "Step "<< iter++ <<": Move "<< goal_state->action
		       	<< ": " << goal_state->state << endl;
	}
			

	return 0;
}

bool goal(string state)
{
	int xpos = state.find('x');
	string l = state.substr(0, xpos); 
	string r = state.substr(xpos + 1);
//	cout << "["<<l<<"]["<<r<<"]\n";
	for(int b=0; b < l.length(); b++)
		if(l[b] != 'B') return false;
	for(int w=0; w < r.length(); w++)
		if(r[w] != 'W') return false;
	return true;
}

node *child_gen(node *mom, int move, int cost)
{
	node *child = new node();
	child->state = mom->state;
	int xpos = child->state.find('x');
	child->state[move] = child->state[move] + child->state[xpos];
	child->state[xpos] = child->state[move] - child->state[xpos];
	child->state[move] = child->state[move] - child->state[xpos];
	child->parent = mom;
	child->action = move;
	child->cost = cost;
	child->next = NULL;
	return child;
}

int Hash(string str)
{
	int num =0;
	for( int i =0; i < str.length(); i++)
	{
		if(str[i] == 'B') num += 1 * pow(3,i);
		else if(str[i] =='W') num += 2 * pow(3,i);
	}
	return num;
}

node *bfs(string filename)
{
	node *root = new node(); root->cost = 0; root->action = -1;
	node *failure = new node(); failure->state = "FAILURE";
	ifstream file(filename, ios::in);
	if(file)getline(file, root->state);file.close();

	int tiles_size = root->state.length();

	if(goal(root->state)) return root;
	
	Q frontier;
	frontier.nQ(*root);

	int vtsize = pow(3,tiles_size);
	bool visited[vtsize] = {0};
	bool in_frontier[vtsize] = {0};
	
	do
	{
		if(frontier.is_empty()) return failure;
		node *n = frontier.dQ();
		int hash = Hash(n->state);
		visited[hash] = true;

		for(int i =0; i < tiles_size; i++)
		{
			if(n->state[i] == 'x') continue;
			node *child = child_gen(n, i, 0);
			int hash = Hash(child->state);
			if(!(visited[hash] || in_frontier[hash])) 
			{
			cout << "Move "<<i<<": " << child->state<<endl;
				if(goal(child->state)) return child;
		        	frontier.nQ(*child);
				in_frontier[hash] = true;
			}
		}
	}while(!frontier.is_empty());

}

