#include <iostream>
#include "bfs.h"
#include <fstream>
#include <cmath>
using namespace std;

//hash function that will treat the string of tiles as a ternary number
//and convert it to binary for the sake of hashing already visited nodes.
int hash(string tiles)
{
	int num = 0;
	for( int i =0; i < sizeof(tiles);i++)
	{
		if(tiles[i] == 'B') num += 1 * pow(3,i);
		else if(tiles[i] == 'W') num += 2 * pow(3,i);	
	}
	return num;
}



int main(int argc, char *argv[])
{
	string txt = argv[1];
       	ifstream file(txt, ios::in);
	
	string puzzle;
	if(file)getline(file, puzzle);file.close();
	bfs test(puzzle);
	
		

	return 0;
}
