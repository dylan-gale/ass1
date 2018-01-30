#include <iostream>
#include "bfs.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
	string txt = argv[1];
       	ifstream file(txt, ios::in);
	
	string puzzle;
	if(file)getline(file, puzzle);file.close();
	bfs test(puzzle);
	
		

	return 0;
}
