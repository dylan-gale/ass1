#include <iostream>
#include <string>
#include "Q.h"
#include "priQ.h"
#include <cmath>
#include <fstream>
using namespace std;

int h(string);
bool goal(string);
node *child_gen(node*,int,int);
string retile(string, int);
int Hash(string);
node *bfs(string);
node *ucs(string);
node *gs(string);
node *astar(string);
node *dfs(string);
int main(int argc, char *argv[])
{
	node *goal_state;
	
	if(argc < 3)
	{
		cerr << "Usage: " << argv[0] << " [-cost] <BFS|DFS|UCS|GS|ASTAR> <input.txt>\n";	
		return 1;
	}
	else if(string(argv[1]) == "BFS")
	{
		goal_state = bfs(argv[2]); 
		cout << "Final Results for BFS:\n";
	}
	else if(string(argv[1]) == "UCS")
	{
		goal_state = ucs(argv[2]);
		cout << "Finals Results for UCS:\n";
	}
	else if(string(argv[1]) == "GS")
	{
		goal_state = gs(argv[2]);
		cout << "Final Results for GS:\n";
	}
	else if(string(argv[1]) == "ASTAR")
	{
		goal_state = astar(argv[2]);
		cout << "Final Results for ASTAR:\n";
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
	if(xpos == string::npos)xpos = state.find('X');
	string l = state.substr(0, xpos); 
	string r = state.substr(xpos + 1);
//	cout << "["<<l<<"]["<<r<<"]\n";
	for(int b=0; b < l.length(); b++)
		if(l[b] != 'B') return false;
	for(int w=0; w < r.length(); w++)
		if(r[w] != 'W') return false;
	return true;
}

int h(string state)
{
	//because we can't assume that the input will be odd
	//we must account for situations where there is one
	//more black than white, or vice versa, so here, in
	//order to count tiles out of place I decided to count 
	//how many B's there are, from which I could determine 
	//the final goal state and compare. still counting B's 
	//I'll instead use that number for control flow
	int i=0, bees=0, counter=0;
	for(int j=0; j<state.length();j++)
	{
		if(state[j] == 'B') bees++;
	}
	for(;i<bees;i++)
	{
		if(state[i] != 'B') counter++;
	}
	if(state[i] != 'x' && state[i]!= 'X') counter++;
	for(++i;i<state.length();i++)
	{
		if(state[i] != 'W') counter++;
	}
	return counter;
}

node *child_gen(node *mom, int move, int cost)
{
	node *child = new node;
	child->state = retile(mom->state, move);
	/*child->state = mom->state;
	int xpos = child->state.find('x');
	if(xpos == string::npos)xpos = child->state.find('X');
	child->state[move] = child->state[move] + child->state[xpos];
	child->state[xpos] = child->state[move] - child->state[xpos];
	child->state[move] = child->state[move] - child->state[xpos];*/
	child->parent = mom;
	child->action = move;
	child->cost = cost;
	child->next = NULL;
	return child;
}

/*reminder that whenever we go to handle -cost, if we can relay that from main to here
 * its as simple as taking abs(i-xpos)
 */
string retile(string str, int i)
{
	int xpos = str.find('x');
	if(xpos == string::npos)xpos = str.find('X');
	str[i] = str[i] + str[xpos];
	str[xpos] = str[i] - str[xpos];
	str[i] = str[i] - str[xpos];
	return str;
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
	node *root = new node; root->cost = 0; root->action = -1;
	node *failure = new node; failure->state = "FAILURE";
	ifstream file(filename, ios::in);
	if(file)getline(file, root->state);file.close();

	int tiles_size = root->state.length();

	if(goal(root->state)) return root;
	
	Q frontier;
	frontier.nQ(root);

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
			if(n->state[i] == 'x' || n->state[i] == 'X') continue;
			node *child = child_gen(n, i, 0);
			int hash = Hash(child->state);
			if(!(visited[hash] || in_frontier[hash])) 
			{
			cout << "Move "<<i<<": " << child->state<< '\t'<< h(child->state) <<endl;
				if(goal(child->state)) return child;
				frontier.nQ(child);
				in_frontier[hash] = true;
			}
		}
	}while(!frontier.is_empty());

}

node *ucs(string filename)
{
	node *root = new node; root->cost = 0; root->action = -1;
	node *failure = new node; failure->state = "FAILURE";

	ifstream file(filename, ios::in);
	if(file)getline(file, root->state);file.close();
	
	int g_n = 0;
	root->cost = g_n;
	if(goal(root->state)) return root;
	
	priQ frontier;
	frontier.add(root);

	int tiles_size = root->state.length();
	int vtsize = pow(3,tiles_size);
	bool visited[vtsize] = {0};
	bool in_frontier[vtsize] = {0};

	do
	{
		if(frontier.is_empty()) return failure;
		node *n = frontier.get_min();
		int hash = Hash(n->state);
		visited[hash] = true;

		for(int i =0; i < tiles_size; i++)
		{
			if(n->state[i] == 'x' || n->state[i] == 'X') continue;
			node *child = child_gen(n, i, g_n);
			int hash = Hash(child->state);
			if(!(visited[hash] || in_frontier[hash])) 
			{
			cout << "Move "<<i<<": " << child->state<<'\n';
				g_n++;
				if(goal(child->state)) return child;
				frontier.add(child);
				in_frontier[hash] = true;
			}
		}
	}while(!frontier.is_empty());
}

node *gs(string filename)
{
	node *root = new node; root->cost = 0; root->action = -1;
	node *failure = new node; failure->state = "FAILURE";

	ifstream file(filename, ios::in);
	if(file)getline(file, root->state);file.close();
	
	root->cost = h(root->state);
	if(goal(root->state)) return root;
	
	priQ frontier;
	frontier.add(root);

	int tiles_size = root->state.length();
	int vtsize = pow(3,tiles_size);
	bool visited[vtsize] = {0};
	bool in_frontier[vtsize] = {0};

	do
	{
		if(frontier.is_empty()) return failure;
		node *n = frontier.get_min();
		int hash = Hash(n->state);
		visited[hash] = true;

		for(int i =0; i < tiles_size; i++)
		{
			if(n->state[i] == 'x' || n->state[i] == 'X') continue;
			node *child = child_gen(n, i, 0);
			child->cost = h(child->state);
			int hash = Hash(child->state);
			if(!(visited[hash] || in_frontier[hash] || child->cost >= n->cost)) 
			{
			cout << "Move "<<i<<": " << child->state<<'\n';
				if(goal(child->state)) return child;
				frontier.add(child);
				in_frontier[hash] = true;
			}
		}
	}while(!frontier.is_empty());
}

node *astar(string filename)
{
	node *root = new node; root->cost = 0; root->action = -1;
	node *failure = new node; failure->state = "FAILURE";

	ifstream file(filename, ios::in);
	if(file)getline(file, root->state);file.close();
	
	int g_n = 0;
	root->cost = g_n;
	if(goal(root->state)) return root;
	
	priQ frontier;
	frontier.add(root);

	int tiles_size = root->state.length();
	int vtsize = pow(3,tiles_size);
	bool visited[vtsize] = {0};
	bool in_frontier[vtsize] = {0};

	do
	{
		if(frontier.is_empty()) return failure;
		node *n = frontier.get_min();
		int hash = Hash(n->state);
		visited[hash] = true;

		for(int i =0; i < tiles_size; i++)
		{
			if(n->state[i] == 'x' || n->state[i] == 'X') continue;
			node *child = child_gen(n, i, g_n);
			child->cost = h(child->state);
			int hash = Hash(child->state);
			if(!(visited[hash] || in_frontier[hash])) 
			{
			cout << "Move "<<i<<": " << child->state<<'\n';
				g_n++;
				if(goal(child->state)) return child;
				frontier.add(child);
				in_frontier[hash] = true;
			}
		}
	}while(!frontier.is_empty());

}
