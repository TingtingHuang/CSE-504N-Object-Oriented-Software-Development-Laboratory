//TicTacToeGame.cpp
//Tingting Huang, tingtinghuang@wustl.edu

#include "stdafx.h"
#include "GameBase.h"
#include "TicTacToeGame.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ostream & operator<<(ostream & out, const TicTacToeGame & g)
{
	for (unsigned int j = 0; j < g.dim_; ++j) //This loops on the columns
	{
		out << g.dim_ - 1 - j << " ";
		for (unsigned int i = 0; i < g.dim_; ++i)    //This loops on the rows.
		{
			out << setw(g.longeststr) << g.board[i][g.dim_ - 1 - j] << " ";
		}
		out << endl;
	}
	vector<int> r(g.dim_);
	iota(begin(r), end(r), 0);
	out << "  ";
	for (rsize_t i = 0; i < r.size(); ++i)
	{
		out << setw(g.longeststr) << r[i] << " ";
	}
	out << endl;
	return out;
}

/////////////////////////////////////////////////////////////////////
//TicTacToeGame Class
//Constructor for TicTacToeGame
TicTacToeGame::TicTacToeGame(int dim) : self(*this), GameBase(dim){
	longeststr = 1;
	//Load the saved game if the first line of game file is the game name
	//Otherwise, stay empty
	ifstream data("TicTacToe");
	if (data.is_open())
	{
		string line;
		getline(data, line);
		if (line == "TicTacToe")
		{
			while (getline(data, line))
			{
				int i;
				int j;
				string player;
				istringstream content(line);
				content >> i >> j >> player;
				this->board[i][j] = player;
			}
		}
		data.close();
		//check the file is closed
		if (data.is_open())
		{
			//if the file is not closed, output an error message
			cerr << "fail to close game data while loading" << endl;
		}
	}
	//if the file is not open, output an error message
	else
	{
		cerr << "New TicTacToe Game Starts" << endl;
	}
}

//override print function
void TicTacToeGame::print() { cout << *this; }

//Output player name
const string TicTacToeGame::player()
{
	int num = this->turnNumPlayed();
	if (num % 2 == 1)
	{
		return this->player1;
	}
	else
	{
		return this->player2;
	}
}

//Virtual done method
bool TicTacToeGame::done() {
	bool result = false;
	//check the rows, columns and two diagnals
	for (int i = 1; i < 4; ++i)    //This loops on the rows 1 to 3.
	{
		bool samerowX = (board[i][1] == first) && (board[i][2] == first) && (board[i][3] == first);
		bool samerowO = (board[i][1] == second) && (board[i][2] == second) && (board[i][3] == second);
		if (samerowX || samerowO)
		{
			result = true;

		}
	}
	for (int j = 1; j < 4; ++j) //This loops on the columns 1 to 3.
	{
		bool samecolX = (board[1][j] == first) && (board[2][j] == first) && (board[3][j] == first);
		bool samecolO = (board[1][j] == second) && (board[2][j] == second) && (board[3][j] == second);
		if (samecolX || samecolO)
		{
			result = true;

		}
	}
	string lowerleft, upperleft, lowerright, upperright, middle;
	lowerleft = board[3][1];
	upperleft = board[1][1];
	lowerright = board[3][3];
	upperright = board[1][3];
	middle = board[2][2];

	bool samediaX1 = (lowerleft == first) && (middle == first) && (upperright == first);
	bool samediaO1 = (lowerleft == second) && (middle == second) && (upperright == second);
	if (samediaX1 || samediaO1)
	{
		result = true;

	}

	bool samediaX2 = (lowerright == first) && (middle == first) && (upperleft == first);
	bool samediaO2 = (lowerright == second) && (middle == second) && (upperleft == second);
	if (samediaX2 || samediaO2)
	{
		result = true;

	}
	return result;
}

//Virtual draw method
bool TicTacToeGame::draw() {
	//copy the current board and check each remaining empty square for the next player to see whethere it is possible to win
	vector<vector<string>> boardcopy = this->board;
	int turnNum = this->turnNumPlayed() + 1;
	int possiblemove = 0;
	for (unsigned int i = 1; i < this->dim_ - 1; ++i)    //this loops on the rows.
	{
		for (unsigned int j = 1; j < this->dim_ - 1; ++j) //this loops on the columns
		{
			if (boardcopy[i][j] == " ")
			{
				if (turnNum % 2 == 1)
				{
					board[i][j] = this->player1;
					bool check = this->done();
					if (check)
					{
						++possiblemove;
					}
				}
				else
				{
					board[i][j] = this->player2;
					bool check = this->done();
					if (check)
					{
						++possiblemove;
					}
				}
			}
		}
	}
	//restore the game board
	this->board = boardcopy;
	if (possiblemove > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//Virtual turn method
int TicTacToeGame::turn()
{
	//odd turn number for player X, and even turn number for player O
	int num = this->turnNumPlayed() + 1; //number of turns for the next player
	//update the true turn number played
	this->turns = this->turnNumPlayed();
	unsigned int x;
	unsigned int y;
	int promptresult = this->prompt(x, y);
	//test whether the coordinates is a valid move
	while (x > 3 || x < 1 || y > 3 || y < 1 || board[x][y] != " " || promptresult == quitprompt)
	{
		if (promptresult == quitprompt)
		{
			//ask the user to input 'yes' or 'no' ONLY
			string message = "please type 'yes' to save current game, or 'no' to start new for next run";
			cout << message << endl;
			string choice;
			cin >> choice;
			while (choice != "yes" && choice != "no")
			{
				cout << message << endl;
				cin >> choice;
			}
			this->save(choice);
			return quitturn;
			break;
		}
		else
		{
			promptresult = this->prompt(x, y);
		}
	}
	//convert valid coordinate to string separated by comma
	string xcoor, ycoor, coor;
	xcoor = to_string(x);
	ycoor = to_string(y);
	coor = xcoor + ", " + ycoor;
	if (num % 2 == 1)
	{
		cout << x << y << endl;
		board[x][y] = first;
		//update length of the longest game piece
		if (first.length() > this->longeststr)
		{
			this->longeststr = first.length();
		}
		this->Xmoves.push_back(coor);
		cout << self << endl;
		cout << endl;
		cout << "Player " << first << ": ";
		for (size_t s = 0; s < this->Xmoves.size(); ++s)
		{
			cout << this->Xmoves[s] << "; ";
		}
		cout << endl;
	}
	else
	{
		board[x][y] = second;
		//update length of the longest game piece
		if (first.length() > this->longeststr)
		{
			this->longeststr = first.length();
		}
		this->Omoves.push_back(coor);
		cout << self << endl;
		cout << endl;
		cout << "Player " << second << ": ";
		for (size_t s = 0; s < this->Omoves.size(); ++s)
		{
			cout << this->Omoves[s] << "; ";
		}
		cout << endl;
	}
	return success;
}

//Lab4: Save the current game
int TicTacToeGame::save(string s)
{
	
	if (s == "yes")
	{
		ofstream data("TicTacToe");
		//chech if the file is open
		if (data.is_open())
		{
			data << "TicTacToe" << endl;
			int n = this->dim_;
			for (int i = 0; i < n; i++)    //This loops on the rows.
			{
				for (int j = 0; j < n; j++) //This loops on the columns
				{
					//store the coordinate the game piece of non-empty cell
					if (this->board[i][j] != " ")
					{
						data << i << " " << j << " " << this->board[i][j] << endl;
					}
				}
			}
			data.close();
			//check the file is closed
			if (data.is_open())
			{
				//if the file is not closed, output an error message
				cerr << "fail to close current saved game data" << endl;
				return failclosesave;
			}
			else{
				return success;
			}
		}
		//if the file is not open, output an error message
		else
		{
			cerr << "fail to open game data while saving" << endl;
			return failopensave;
		}
	}
	else if (s == "no")
	{
		ofstream data("TicTacToe");
		//chech if the file is open
		if (data.is_open())
		{
			data << "NODATA" << endl;
			data.close();
			//check the file is closed
			if (data.is_open())
			{
				//if the file is not closed, output an error message
				cerr << "fail to close current UN-saved game data" << endl;
				return failclosesave;
			}
			else{
				return success;
			}
		}
		//if the file is not open, output an error message
		else
		{
			cerr << "fail to open game data without saving" << endl;
			return failopensave;
		}
	}
	//Indicate new game for next turn when current game is completed
	else
	{
		ofstream data("TicTacToe");
		//chech if the file is open
		if (data.is_open())
		{
			data << "NEW" << endl;
			data.close();
			//check the file is closed
			if (data.is_open())
			{
				//if the file is not closed, output an error message
				cerr << "fail to close new game data" << endl;
				return failclosesave;
			}
			else{
				return success;
			}
		}
		//if the file is not open, output an error message
		else
		{
			cerr << "fail to open completed game data" << endl;
			return failopensave;
		}
	}
}