//TicIacToeGame.cpp
//Tingting Huang, tingtinghuang@wustl.edu

#include "stdafx.h"
#include "TicTacToeGame.h"
#include <iostream>

using namespace std;

int usage(char * name)
{
	cout << "usage: " << name << " <input_file_name>" << endl;
	return usagefail;
}

ostream & operator<<(ostream & out, const Game & g)
{
	for (int i = 0; i < 5; ++i)    //This loops on the rows.
	{
		out << 4 - i << ' ';
		for (int j = 0; j < 5; ++j) //This loops on the columns
		{
			out << g.board[4-i][j] << ' '; 
		}
		out << endl;
	}
	out << "  0 1 2 3 4" << endl;
	return out;
}

