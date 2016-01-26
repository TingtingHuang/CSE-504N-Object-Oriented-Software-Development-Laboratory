//GomokuGame.cpp
//Tingting Huang, tingtinghuang@wustl.edu

#include "stdafx.h"
#include "GameBase.h"
#include "GomokuGame.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

ostream & operator<<(ostream & out, const GomokuGame & g)
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
	out << "X ";
	for (rsize_t i = 0; i < r.size(); ++i)
	{
		out << setw(g.longeststr) << r[i] << " ";
	}
	out << endl;
	return out;
}

/////////////////////////////////////////////////////////////////////
//GomokuGame Class
//Constructor for GomokuGame
GomokuGame::GomokuGame(int dim, int connecting) : self(*this), GameBase(dim), con_(connecting){
	longeststr = 1;
	//Load the saved game if the first line of game file is the game name
	//and the dimension & connecting pieces are the same
	//Otherwise, stay empty
	ifstream data("Gomoku");
	if (data.is_open())
	{
		string line1;
		getline(data, line1);
		string line2;
		getline(data, line2);
		int i;
		int j;
		istringstream content1(line2);
		content1 >> i >> j;
		if (line1 == "Gomoku" && i == this->dim_ && j == this->con_)
		{
			string line;
			while (getline(data, line))
			{
				int x;
				int y;
				string player;
				istringstream content(line);
				content >> x >> y >> player;
				this->board[x][y] = player;
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
		cerr << "New Gomoku Game Starts" << endl;
	}
}

//override print function
void GomokuGame::print() { cout << *this; }

//Output player name
const string GomokuGame::player()
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

//check whether the adjacent connecting pieces are the same as the given player name
bool GomokuGame::checkadj(const string playername)
{
	//check the same row
	bool samerow = false;
	int countrow = 1;
	for (unsigned int j = this->y_ + 1; j > 0 && j < (this->dim_ - 1); j += 1)
	{
		if (this->board[this->x_][j] == playername)
		{
			++countrow;
		}
		else
		{
			break;
		}
	}
	for (unsigned int j = this->y_ - 1; j > 0 && j < (this->dim_ - 1); j -= 1)
	{
		if (this->board[this->x_][j] == playername)
		{
			++countrow;
		}
		else
		{
			break;
		}
	}
	if (countrow >= this->con_)
	{
		samerow = true;
	}
	//check the same column
	bool samecolumn = false;
	int countcolumn = 1;
	for (unsigned int i = this->x_ + 1; i > 0 && i < (this->dim_ - 1); i += 1)
	{
		if (this->board[i][this->y_] == playername)
		{
			++countcolumn;
		}
		else
		{
			break;
		}
	}
	for (unsigned int i = this->x_ - 1; i > 0 && i < (this->dim_ - 1); i -= 1)
	{
		if (this->board[i][this->y_] == playername)
		{
			++countcolumn;
		}
		else
		{
			break;
		}
	}
	if (countcolumn >= this->con_)
	{
		samecolumn = true;
	}
	//check the first diagonal
	bool diagonal1 = false;
	int countdia1 = 1;
	for (unsigned int i = this->x_ + 1, j = this->y_ + 1; i > 0 && i < (this->dim_ - 1) && j > 0 && j < (this->dim_ - 1); i += 1, j += 1)
	{
		if (this->board[i][j] == playername)
		{
			++countdia1;
		}
		else
		{
			break;
		}
	}
	for (unsigned int i = this->x_ - 1, j = this->y_ - 1; i > 0 && i < (this->dim_ - 1) && j > 0 && j < (this->dim_ - 1); i -= 1, j -= 1)
	{
		if (this->board[i][j] == playername)
		{
			++countdia1;
		}
		else
		{
			break;
		}
	}
	if (countdia1 >= this->con_)
	{
		diagonal1 = true;
	}
	//check the second diagonal
	bool diagonal2 = false;
	int countdia2 = 1;
	for (unsigned int i = this->x_ - 1, j = this->y_ + 1; i > 0 && i < (this->dim_ - 1) && j > 0 && j < (this->dim_ - 1); i += -1, j += 1)
	{
		if (this->board[i][j] == playername)
		{
			++countdia2;
		}
		else
		{
			break;
		}
	}
	for (unsigned int i = this->x_ + 1, j = this->y_ - 1; i > 0 && i < (this->dim_ - 1) && j > 0 && j < (this->dim_ - 1); i -= -1, j -= 1)
	{
		if (this->board[i][j] == playername)
		{
			++countdia2;
		}
		else
		{
			break;
		}
	}
	if (countdia2 >= this->con_)
	{
		diagonal2 = true;
	}
	//if any of the previous checks is true, return true.
	return samerow || samecolumn || diagonal1 || diagonal2;
}

//Override done method
bool GomokuGame::done()
{
	if (this->board[this->x_][this->y_] == this->player1)
	{
		return this->checkadj(this->player1);
	}
	else if (this->board[this->x_][this->y_] == this->player2)
	{
		return this->checkadj(this->player2);
	}
	else
	{
		return false;
	}
}

//Override draw method
bool GomokuGame::draw()
{
	//copy the current board and check each remaining empty square for the next player to see whethere it is possible to win
	vector<vector<string>> boardcopy = this->board;
	int copyx_ = this->x_;
	int copyy_ = this->y_;
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
					this->x_ = i;
					this->y_ = j;
					bool check = this->done();
					if (check)
					{
						++possiblemove;
					}
				}
				else
				{
					board[i][j] = this->player2;
					this->x_ = i;
					this->y_ = j;
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
	this->x_ = copyx_;
	this->y_ = copyy_;
	if (possiblemove > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//Overloaded prompt method
void GomokuGame::prompt(unsigned int & i, unsigned int & j)
{
	string s = "please type 'quit' to end the game or a string representating a valid coordinate separated by comma";
	cout << s << endl;
	string input;
	cin >> input;
	//replace any comma in the input with empty spaces
	replace(input.begin(), input.end(), ',', ' ');
	if (input == "quit")
	{
		throw quitprompt;
	}
	else
	{
		istringstream content(input);
		if (content >> i >> j)
		{
			throw success;
		}
		else
		{
			throw invalidcoor;
		}
	}
}

//Override turn method
int GomokuGame::turn()
{
	//odd turn number for player B, and even turn number for player W
	int num = this->turnNumPlayed() + 1; //number of turns for the next player
	//update the true turn number played
	this->turns = this->turnNumPlayed();
	unsigned int x;
	unsigned int y;
	try
	{
		this->prompt(x, y);
	}
	catch (sucAndFail promptresult)
	{
		//test whether the coordinates is a valid move
		while (x > (this->dim_ - 2) || x < 1 || y >(this->dim_ - 2) || y < 1 || board[x][y] != " " || promptresult == quitprompt)
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
				try
				{
					this->prompt(x, y);
				}
				catch (sucAndFail result)
				{
					promptresult = result;
				}
			}
		}
	}
	//update current coordinate
	this->x_ = x;
	this->y_ = y;
	//convert valid coordinate to string separated by comma
	string xcoor, ycoor, coor;
	xcoor = to_string(x);
	ycoor = to_string(y);
	coor = xcoor + ", " + ycoor;
	if (num % 2 == 1)
	{
		board[x][y] = black;
		this->Bmoves.push_back(coor);
		cout << self << endl;
		cout << endl;
		cout << "Player " << black << ": ";
		for (size_t s = 0; s < this->Bmoves.size(); ++s)
		{
			cout << this->Bmoves[s] << "; ";
		}
		cout << endl;
	}
	else
	{
		board[x][y] = white;
		this->Wmoves.push_back(coor);
		cout << self << endl;
		cout << endl;
		cout << "Player " << white << ": ";
		for (size_t s = 0; s < this->Wmoves.size(); ++s)
		{
			cout << this->Wmoves[s] << "; ";
		}
		cout << endl;
	}
	return success;
}

//Lab4: Save the current game
int GomokuGame::save(string s)
{
	if (s == "yes")
	{
		ofstream data("Gomoku");
		//chech if the file is open
		if (data.is_open())
		{
			data << "Gomoku" << endl;
			int n = this->dim_;
			int c = this->con_;
			//input the dimension and connecting pieces as the second line
			data << n << " " << c << endl;
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
		ofstream data("Gomoku");
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
		ofstream data("Gomoku");
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