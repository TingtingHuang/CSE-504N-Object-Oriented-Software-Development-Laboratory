//GameBase.cpp
//Tingting Huang, tingtinghuang@wustl.edu

#include "stdafx.h"
#include "GameBase.h"
#include "TicTacToeGame.h"
#include "GomokuGame.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <memory>

using namespace std;

int usage(char * name)
{
	cout << "usage: " << name << " <TicTacToe or Gomoku with additional commands>" << endl;
	return usagefail;
}

/////////////////////////////////////////////////////////////////////////
//GameBase Class
//Constructor for the gamebase board
GameBase::GameBase(int dim) :self(*this), dim_(dim){
	int n = dim_;
	board.resize(n);
	for (int i = 0; i < n; ++i)
	{
		board[i].resize(n);
	}
	for (int i = 0; i<n; i++)    //This loops on the rows.
	{
		for (int j = 0; j<n; j++) //This loops on the columns
		{
			board[n - 1 - i][j] = " "; //invert the row coordinate by n-1-i
		}
	}
}

//Common method:
int GameBase::turnNumPlayed()
{
	//count non-empty game pieces
	int countnonempty = 0;
	for (unsigned int i = 1; i < (this->dim_ - 1); i++)    //This loops on the rows
	{
		for (unsigned int j = 1; j < (this->dim_ - 1); j++) //This loops on the columns
		{
			if (board[(this->dim_ - 1) - i][j] != " ")
			{
				countnonempty += 1;
			}
		}
	}
	return countnonempty;
}

//Move prompt method to the GameBase
int GameBase::prompt(unsigned int & i, unsigned int & j)
{
	string s = "please type 'quit' to end the game or a string representating a valid coordinate separated by comma";
	cout << s << endl;
	string input;
	cin >> input;
	//replace any comma in the input with empty spaces
	replace(input.begin(), input.end(), ',', ' ');

	if (input != "quit")
	{
		istringstream content(input);
		if (content >> i >> j)
		{
			return success;
		}
		else
		{
			return invalidcoor;
		}
	}
	else {
		return quitprompt;
	}
}

//Move play to GameBase
int GameBase::play()
{
	print();
	bool gameplay = true;
	while (gameplay)
	{
		int turnresult = this->turn();
		bool doneresult = this->done();
		bool drawresult = this->draw();
		if (doneresult == true)
		{
			const string playername = this->player();
			cout << playername << " wins the game." << endl;
			gameplay = false;
			return success;
		}
		else if (drawresult == true)
		{
			int num = this->turnNumPlayed();
			cout << num << " turns were played. No winning moves remain" << endl;
			gameplay = false;
			return drawfail;
		}
		else if (turnresult == quitturn)
		{
			int num = this->turnNumPlayed();
			cout << num << " turns were played. User quited" << endl;
			gameplay = false;
			return quitplay;
		}
	}
	return gamestop;
}

//Static method
GameBase* GameBase::check(int argc, char* argv[]){
	string s1 = "TicTacToe";
	string s2 = "Gomoku";
	if (argc == 2 && argv[1] == s1)
	{
		GameBase * p = new TicTacToeGame(5);
		return p;
	}
	else if (argc == 2 && argv[1] == s2)
	{
		GameBase * p = new GomokuGame(21,5);
		return p;
	}
	else if (argc == 3 && argv[1] == s2)
	{
		int i = stoi(argv[2]);
		if (i > 0)
		{
			GameBase * p = new GomokuGame(i + 2, 1);
			return p;
		}
		else
		{
			cerr << "Please inpout a positive dimension" << endl;
			throw nonposdim;
		}
	}
	else if (argc == 4 && argv[1] == s2)
	{
		int i = stoi(argv[2]);
		int j = stoi(argv[3]);
		if (i > 0 && j > 0)
		{
			GameBase * p = new GomokuGame(i + 2, j);
			return p;
		}
		else
		{
			cerr << "Please input a positive dimension and a positive number of connecting pieces" << endl;
			throw nonposboth;
		}
	}
	else
	{
		GameBase * singular = nullptr;
		return singular;
	}
}
