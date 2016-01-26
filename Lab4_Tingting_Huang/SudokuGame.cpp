//SudokuGame.cpp
//Tingting Huang, tingtinghuang@wustl.edu

#include "stdafx.h"
#include "GameBase.h"
#include "SudokuGame.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

ostream & operator<<(ostream & out, const SudokuGame & g)
{
	for (unsigned int j = 0; j < g.dim_; ++j)    //This loops on the rows.
	{
		out << g.dim_ - 1 - j << "||";
		for (unsigned int i = 0; i < g.dim_; ++i) //This loops on the columns
		{
			if (i == 2 || i == 5 || i == 8)
			{
				out << setw(g.longeststr) << g.board[i][g.dim_ - 1 - j] << "||";
			}
			else{
				out << setw(g.longeststr) << g.board[i][g.dim_ - 1 - j] << "|";
			}
		}
		out << endl;
		if (j == 2 || j == 5 || j == 8)
		{
			out << "=||=|=|=||=|=|=||=|=|=||" << endl;
		}
		else
		{
			out << "-||-|-|-||-|-|-||-|-|-||" << endl;
		}
	}
	vector<int> r(g.dim_);
	iota(begin(r), end(r), 0);
	out << "#||";
	for (rsize_t i = 0; i < r.size(); ++i)
	{
		if (i == 2 || i == 5 || i == 8)
		{
			out << setw(g.longeststr) << r[i] << "||";
		}
		else
		{
			out << setw(g.longeststr) << r[i] << "|";
		}
		
	}
	out << endl;
	return out;
}

/////////////////////////////////////////////////////////////////////
//SudokuGame Class
//Constructor for SudokuGame
SudokuGame::SudokuGame() : self(*this), GameBase(9){
	longeststr = 1;
	//Initialize the game with 'sudoku0'
	//Then load the saved game file if it exists
	//open the sudoku0 file
	ifstream init("sudoku0");
	if (init.is_open())
	{
		int n = this->dim_;
		int j = 0;
		string numbers;
		while (getline(init, numbers))
		{
			int i0, i1, i2, i3, i4, i5, i6, i7, i8;
			istringstream content(numbers);
			//take in all 9 numbers from a row
			if (content >> i0 >> i1 >> i2 >> i3 >> i4 >> i5 >> i6 >> i7 >> i8)
			{
				int intline[] = { i0, i1, i2, i3, i4, i5, i6, i7, i8 };
				for (int i = 0; i<n; i++) //This loops on the columns
				{
					//ignore 0'ss
					if (intline[i] != 0)
					{
						//initialize the board and store the position
						this->board[i][j] = to_string(intline[i]);
						int pos = i * 10 + j;
						this->inipos.push_back(pos);
					}
				}
			}
			j += 1; //loop through rows
		}
		init.close();
		//check the file is closed
		if (init.is_open())
		{
			//if the file is not closed, output an error message
			cerr << "fail to close initial game file" << endl;
		}
	}
	else
	{
		cerr << "fail to open initial game file" << endl;
	}
	//open the saved game file
	ifstream data("Sudoku");
	if (data.is_open())
	{
		string line;
		getline(data, line);
		if (line == "Sudoku")
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
		cerr << "New Sudoku Game Starts" << endl;
	}
}

//override print function
void SudokuGame::print() { cout << *this; }

//Override done method
//insert the non-empty game pieces in the same row, same column, or the same sub-grid into a separate set
//Since the game pieces are restricted from 1 to 9, if all 9 digits are used, the size of the set should be 9
bool SudokuGame::done()
{
	int n = this->dim_;
	//check each row
	bool row = false;
	int rowpass = 0;
	set<string> rowset;
	for (int i = 0; i < n; ++i)
	{
		rowset.clear(); //clear the contents of the rowset for each row
		for (int j = 0; j < n; ++j)
		{
			if (this->board[i][j] != " ")
			{
				rowset.insert(this->board[i][j]);
			}
		}
		//check the size of rowset
		if (rowset.size() == 9)
		{
			rowpass += 1;
		}
	}
	//check whether each row has passed the test
	if (rowpass == 9)
	{
		row = true;
	}
	//check each column
	bool column = false;
	int colpass = 0;
	set<string> colset;
	for (int i = 0; i < n; ++i)
	{
		colset.clear(); //clear the contents of the colset for each column
		for (int j = 0; j < n; ++j)
		{
			if (this->board[j][i] != " ")
			{
				colset.insert(this->board[j][i]);
			}
		}
		//check the size of rowset
		if (colset.size() == 9)
		{
			colpass += 1;
		}
	}
	//check whether each column has passed the test
	if (colpass == 9)
	{
		column = true;
	}
	//check each sub-grid
	bool subgrid = false;
	int subpass = 0;
	set<string> subset;
	//loop through 9 sub-grids
	for (int i = 0; i < n; i += 3)
	{
		for (int j = 0; j < n; j += 3)
		{
			//loop through 9 game pieces in each sub-grids
			subset.clear();
			for (int x = i; x < (i + 3); ++x)
			{
				for (int y = j; y < (j + 3); ++y)
				{
					if (this->board[x][y] != " ")
					{
						subset.insert(this->board[x][y]);
					}
				}
			}
			//check the size of subset
			if (subset.size() == 9)
			{
				subpass += 1;
			}
		}
	}
	//check whether all sub-grids pass the test
	if (subpass == 9)
	{
		subgrid = true;
	}
	return row && column && subgrid;
}

//draw always returns false, since there is no condition for draw in sudoku
bool SudokuGame::draw()
{
	return false;
}

//player will always return 'you'
const string SudokuGame::player()
{
	const string s = "you";
	return s;
}

//newprompt will ask the user to input 3 unsigned int as the coordinates and the game piece value
int SudokuGame::prompt(unsigned int & i, unsigned int & j, unsigned int & k)
{
	string s = "please type 'quit' to end the game or a string representating a valid coordinate (0-8) and an integer from 1-9 for the game piece, separated by comma. Example: 1,1,9 means insert 9 to the position (1,1)";
	cout << s << endl;
	string input;
	cin >> input;
	//replace any comma in the input with empty spaces
	replace(input.begin(), input.end(), ',', ' ');
	if (input == "quit")
	{
		return quitprompt;
	}
	else
	{
		istringstream content(input);
		if (content >> i >> j >> k)
		{
			//check whether the new position is at the initial position
			int newpos = i * 10 + j;
			vector<int>::iterator itr;
			itr = find(inipos.begin(), inipos.end(), newpos);
			if (itr != inipos.end())
			{
				return sameinitial;
			}
			//new position cannot be found in the initial positions
			else
			{
				return success;
			}
		}
		else
		{
			return invalidcoor;
		}
	}
}

//new method to count the number of turns played without the buffer region
//Common method:
int SudokuGame::turnNumPlayed()
{
	//count non-empty game pieces
	int countnonempty = 0;
	for (unsigned int i = 0; i < this->dim_; i++)    //This loops on the rows
	{
		for (unsigned int j = 0; j < this->dim_; j++) //This loops on the columns
		{
			if (board[(this->dim_ - 1) - i][j] != " ")
			{
				countnonempty += 1;
			}
		}
	}
	return countnonempty;
}

//insert or overwrite the game pieces other than the initial pieces based on user's requests
int SudokuGame::turn()
{
	//update the true turn number played
	this->turns = this->turnNumPlayed()-this->inipos.size();
	//inform the player if no more empty space existing
	int n = this->dim_;
	int nsqr = n*n;
	string s = "All cells are filled, please prompt additional inputs";
	if (this->turnNumPlayed() == nsqr)
	{
		cout << s << endl;
	}
	unsigned int x;
	unsigned int y;
	unsigned int z;
	int promptresult = this->prompt(x, y, z);
	//test whether the coordinates is a valid move
	while (x > 8 || x < 0 || y > 8 || y < 0 || z < 1 || z > 9 || promptresult == quitprompt || promptresult == sameinitial)
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
		else if (promptresult == sameinitial)
		{
			promptresult = this->prompt(x, y, z);
		}
		else
		{
			promptresult = this->prompt(x, y, z);
		}
	}
	//convert valid coordinate to string separated by comma
	string value;
	value = to_string(z);
	//update board
	board[x][y] = value;
	//update length of the longest game piece
	if (value.length() > this->longeststr)
	{
		this->longeststr = value.length();
	}
	cout << self << endl;
	cout << endl;
	return success;
}

//Lab4: Save the current game
int SudokuGame::save(string s)
{

	if (s == "yes")
	{
		ofstream data("Sudoku");
		//chech if the file is open
		if (data.is_open())
		{
			data << "Sudoku" << endl;
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
		ofstream data("Sudoku");
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
		ofstream data("Sudoku");
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