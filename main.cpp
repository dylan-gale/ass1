#include <iostream>
#include "bfs.h"
#include <fstream>
#include <cmath>
using namespace std;

//hash function that will treat the string of tiles as a ternary number
//and convert it to binary for the sake of hashing already visited nodes.
int Hash(string tiles)
{
	int num = 0;
	for( int i =0; i < tiles.length() ;i++)
	{
		cout << i << endl;
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
	//bfs test(puzzle);
	string big = "xBBBBBBWWWWWW";
	//YES
	//YES
	//YES
	//WE CAN USE THIS HASH FUNCTION STILL BY SIMPLY CHECKING IF THE VALUE
	//HASHED TO STORES ZERO OR NOT, INSTEAD OF STORING THE DUMB FUCKING 
	//STIRNGS THERE GOD DAMNIT I AM SUCH A FUCKING IDIOT.
	int table[Hash(big)] = {0};	
	cout << pow(3, big.length()) - Hash(big) << endl;
	int tsize = pow(3, big.length());
	int tabl2[tsize] = {0};
	//ALRIGHT SO WHEN YOU SET THIS UP, TAKE THE INPUT STRING, INITIALIZE THE
	//VISITED ARRAY TO BE AN INT ARRAY OF SIZE POW(3,INIT.LENGTH()) AND WE 
	//GOOD
	//
	return 0;
}
