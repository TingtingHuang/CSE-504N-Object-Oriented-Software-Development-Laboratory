//UltTTT.cpp
//Tingting Huang, tingtinghuang@wustl.edu

#include "stdafx.h"
#include "GameBase.h"
#include "TicTacToeGame.h"
#include "UltTTT.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

//ostream & operator<<(ostream & out, const UltTTT & g)
//{
//	/*for (size_t s = 0; s < g.games.size(); ++s)
//	{
//		out << g.games[s] << endl;
//	}*/
//	out << g.games[0]->print() << endl;
//	return out;
//}

ostream & operator<<(ostream & out, const UltTTT & g)
{
	for (int x = (g.rownum - 1); x >= 0; --x)    //This loops on the rows of ultimate game
	{
		out << "Ultimate row " << x << ":" << endl;
		for (int j = (g.dim_ - 1); j >= 0; --j) //this loops through the rows of sub-games that on the same row of the ultimate game
		{
			for (size_t k = x; k < g.games.size(); k += 3) //This loops on the sub-games on the same row of ultimate game
			{
				out << j << "_";
				for (unsigned int i = 0; i < g.dim_; ++i)    //This loops on the columns of each sub-game
				{
					out << setw(g.longeststr) << g.games[k]->board[i][j] << "_";
				}
				out << "||";
			}
			out << endl;
		}
		vector<int> r(g.dim_);
		iota(begin(r), end(r), 0);
		for (unsigned int z = 0; z < g.rownum; ++z)
		{
			out << "__";
			for (rsize_t i = 0; i < r.size(); ++i)
			{
				out << setw(g.longeststr) << r[i] << "_";
			}
			out << "||";
		}
		out << endl;
	}

	return out;
}
/////////////////////////////////////////////////////////////////////
//UltTTT Class
//Constructor
UltTTT::UltTTT(int dim) : self(*this), TicTacToeGame(dim)
{
	//initialize index to 9 to ask the user to input the sub-game position first
	this->index = 9;
	//initialize the vector of sub-game objects, and the vector of game result
	for (unsigned int i = 0; i < this->totalnum; ++i)
	{
		//push each sub-game
		TicTacToeGame * game = new TicTacToeGame(dim);
		games.push_back(game);
		//push empty for all gameresult
		gameresult.push_back(" ");
	}
	//Load the saved game if the first line of game file is the game name
	//Otherwise, stay empty
	ifstream data("UltimateTicTacToe");
	if (data.is_open())
	{
		string line;
		string results;
		getline(data, line);
		if (line == "UltimateTicTacToe")
		{
			//get the second line for game results
			getline(data, results);
			string i0, i1, i2, i3, i4, i5, i6, i7, i8;
			istringstream content(results);
			//take in all 9 game results from a row
			if (content >> i0 >> i1 >> i2 >> i3 >> i4 >> i5 >> i6 >> i7 >> i8)
			{
				string resline[] = { i0, i1, i2, i3, i4, i5, i6, i7, i8 };
				for (int i = 0; i<9; i++) //This loops on the columns
				{
					this->gameresult[i] = resline[i];
				}
			}
			while (getline(data, line))
			{
				int k;
				int i;
				int j;
				string player;
				istringstream content2(line);
				content2 >> k >> i >> j >> player;
				this->games[k]->board[i][j] = player;
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
		cerr << "New Ultimate TicTacToe Game Starts" << endl;
	}
}

//override print function
void UltTTT::print() { cout << *this; }

//count the total turn number
int UltTTT::totalturnNumPlayed()
{
	int total = 0;
	for (size_t s = 0; s < games.size(); ++s)
	{
		int subtotal = games[s]->turnNumPlayed();
		total += subtotal;
	}
	return total;
}

//Output player name
const string UltTTT::player()
{
	int num = this->totalturnNumPlayed();
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
bool UltTTT::done()
{
	//check whether the same player wins the 3 games in each row
	bool rowpass = false;
	for (unsigned int j = 0; j < this->rownum; ++j)//loop through rows
	{
		int rowwinnum = 0;
		for (unsigned int i = j; i < this->totalnum; i+=3)//loop through sub-games in each row
		{
			bool sub = false;
			sub = games[i]->done(); //check whether each sub-game has a winning player
			bool subdraw = false;
			subdraw = games[i]->draw();
			if (sub == true)
			{
				const string name = this->player();
				this->gameresult[i] = name; //store the winning player name
				rowwinnum += 1;
			}
			//if the sub-game is draw, insert "draw" to result
			else if (subdraw == true)
			{
				this->gameresult[i] = "draw";
			}
		}
		if (rowwinnum == 3)
		{
			//check whether the same player wins this row
			if (gameresult[j] == gameresult[j + 3] && gameresult[j] == gameresult[j + 6] && gameresult[j+6] == gameresult[j + 3])
			{
				rowpass = true;
				break;
			}
		}
	}
	return rowpass;
}

//draw() method
bool UltTTT::draw()
{
	int nonempty = 0;
	for (size_t s = 0; s < gameresult.size(); ++s)
	{
		//if the gameresult is empty, game haven't been finished yet
		if (gameresult[s] == " ")
		{
			return false;
			break;
		}
		//if the gameresult is not empty, count the total number of nonempty results
		else
		{
			nonempty += 1;
		}
	}
	//if the total number of nonempty results is 9, and the done for the whole game is false, return true
	bool totaldone = this->done();
	if (nonempty == 9 && totaldone == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//prompt sub-game position
int UltTTT::subgame(unsigned int & i, unsigned int & j)
{
	string s = "please type 'quit' to end the game or a string representating a valid coordinate (0-2) separated by comma to choose the sub-game position";
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
			if (j < this->rownum && j >= 0)
			{
				if (i < this->rownum && i >= 0)
				{
					//map the sub-game position to distinct 0-8 for the games index
					int nextind = i * 3 + j;
					//check whether it is done or draw
					bool subdone = this->games[nextind]->done();
					bool subdraw = this->games[nextind]->draw();
					if (subdone == false && subdraw == false)
					{
						return (i * 3 + j);
					}
					else
					{
						throw invalidcoor;
					}
					
				}
				else
				{
					throw invalidcoor;
				}
			}
			else
			{
				throw invalidcoor;
			}		
		}
		else
		{
			throw invalidcoor;
		}
	}
	else {
		throw quitprompt;
	}
}

//turn method
int UltTTT::turn()
{
	//odd turn number for player X, and even turn number for player O
	int num = this->totalturnNumPlayed() + 1; //number of turns for the next player
	//update the true turn number played
	this->turns = this->totalturnNumPlayed();
	//if index is 9, ask the player to choose the position of sub-game
	if (this->index > 8)
	{
		unsigned int i;
		unsigned int j;
		int subgamepos = this->index;
		try{
			subgamepos = this->subgame(i, j);
		}
		catch (sucAndFail subgameresult)
		{
			while (subgameresult == quitprompt || subgameresult == invalidcoor)
			{
				if (subgameresult == quitprompt)
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
						subgamepos = this->subgame(i,j);
						if (subgamepos < 9 && subgamepos >= 0)
						{
							subgameresult = success;
						}
					}
					catch (sucAndFail result)
					{
						subgameresult = result;
					}
				}
			}
		}	
		//update index
		this->index = subgamepos;
	}
	//after updating the index, update the board at corresponding sub-game by prompt()
	unsigned int x;
	unsigned int y;
	int promptresult = this->prompt(x, y);
	//test whether the coordinates is a valid move
	while (x > 3 || x < 1 || y > 3 || y < 1 || games[index]->board[x][y] != " " || promptresult == quitprompt)
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
	string xcoor, ycoor, gameindex, coor;
	xcoor = to_string(x);
	ycoor = to_string(y);
	gameindex = to_string(this->index);
	coor = gameindex + ", " + xcoor + ", " + ycoor;
	if (num % 2 == 1)
	{
		games[index]->board[x][y] = first;
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
		games[index]->board[x][y] = second;
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
	//update index
	this->index = ((x-1) * 3 + (y-1));
	//test whether the chosen sub-game is either done or draw
	bool subdone = this->games[this->index]->done();
	bool subdraw = this->games[this->index]->draw();
	if (subdone == true || subdraw == true)
	{
		this->index = 9;
	}
	return success;
}

//Extra: Save the current game
int UltTTT::save(string s)
{

	if (s == "yes")
	{
		ofstream data("UltimateTicTacToe");
		//chech if the file is open
		if (data.is_open())
		{
			data << "UltimateTicTacToe" << endl;
			//push the gameresult to the second line
			for (size_t s = 0; s < this->gameresult.size(); ++s)
			{
				data << gameresult[s] << " ";
			}
			data << endl;
			int n = this->dim_;
			for (size_t k = 0; k < games.size(); ++k) //loop through each sub-game
			{
				for (int i = 0; i < n; i++)    //This loops on the columns.
				{
					for (int j = 0; j < n; j++) //This loops on the rows
					{
						//store the coordinate the game piece of non-empty cell
						if (this->games[k]->board[i][j] != " ")
						{
							data << k << " " << i << " " << j << " " << this->games[k]->board[i][j] << endl;
						}
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
		ofstream data("UltimateTicTacToe");
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
		ofstream data("UltimateTicTacToe");
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