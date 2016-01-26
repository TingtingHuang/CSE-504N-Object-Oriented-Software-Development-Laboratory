//TicTacToaGame.h
//Tingting Huang, tingtinghuang@wustl.edu
//header guard
#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

const char first = 'X';
const char second = 'O';
enum sucAndFail { success = 0, usagefail = -1, quitprompt = -2, quitturn = -3, drawfail = -4, quitplay = -5 };
int usage(char * name);

//Declare the class of the game
class Game {
	//Declare a reference to self
	Game & self;
	//Declare vector of vector of char for the game board
	vector<vector<char>> board;
	//Store the moves of each player
	vector<string> Omoves;
	vector<string> Xmoves;
	friend ostream & operator<<(ostream & out, const Game & g);

	
public:
	//Constructor for the game board
	Game() :self(*this){
		//Initialize the game board 5*5
		const int n = 5;
		board.resize(n);
		for (int i = 0; i < n; ++i)
		{
			board[i].resize(n);
		}
		for (int i = 0; i<5; i++)    //This loops on the rows.
		{
			for (int j = 0; j<5; j++) //This loops on the columns
			{
				board[4 - i][j] = ' '; //invert the row coordinate by 4-i
			}
		}
	}

	//return true is one play wins
	bool done() {
		bool result = false;
		//check the rows, columns and two diagnals
		for (int i = 1; i < 4; ++i)    //This loops on the rows 1 to 3.
		{
			bool samerowX = (board[i][1] == first) && (board[i][2] == first) && (board[i][3] == first);
			bool samerowO = (board[i][1] == second) && (board[i][2] == second) && (board[i][3] == second);
			if(samerowX || samerowO)
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
		char lowerleft, upperleft, lowerright, upperright, middle;
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

	//count the non-empty valid square on the game board as the number of turns played
	int turnNumPlayed()
	{
		int countnonempty = 0;
		for (int i = 1; i<4; i++)    //This loops on the rows from 1 to 3.
		{
			for (int j = 1; j<4; j++) //This loops on the columns from 1 to 3
			{
				if (board[4 - i][j] != ' ')
				{
					countnonempty += 1;
				}
			}
		}
		return countnonempty;
	}

	//return true for being capable of drawing new charactors and neither player has won
	bool draw() {
		bool doneresult = this->done();
		int countnonempty = this->turnNumPlayed();
		if (countnonempty != 9 || doneresult)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	//Ask the user to input valid form of coordinates or quit the game
	int prompt(unsigned int & i, unsigned int & j)
	{
		bool invalid = true;
		string s = "please type quit to end the game or a string representating a valid coordinate separated by comma";
		string input;
		cin >> input;
		//replace any comma in the input with empty spaces
		replace(input.begin(), input.end(), ',', ' ');
		
		if (invalid)
		{
			
			if (input != "quit")
			{
				cout << s << endl;
				istringstream content(input);
				if (content >> i >> j)
				{
					invalid = false;
					return success;
				}
			}
			else if (input == "quit")
			{
				return quitprompt;
			}
		}
	}

	//Change the game board for each valid move for different players
	int turn()
	{
		//odd turn number for player X, and even turn number for player O
		int num = this->turnNumPlayed() + 1; //number of turns for the next player
		
		unsigned int x;
		unsigned int y;
		int promptresult = this->prompt(x, y);
		//test whether the coordinates is a valid move
		while (x > 3 || x < 1 || y > 3 || y < 1 || board[x][y] != ' ' || promptresult == quitprompt)
		{
			if (promptresult == quitprompt)
			{
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
			board[x][y] = first;
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

	//method used to record the whole game
	int play()
	{
		cout << self << endl;
		bool gameplay = true;
		while (gameplay)
		{
			int turnresult = this->turn();
			bool doneresult = this->done();
			bool drawresult = this->draw();
			if (doneresult == true)
			{
				int num = this->turnNumPlayed();
				if (num % 2 == 1)
				{
					cout << "'X' wins the game." << endl;
					gameplay = false;
					return success;
				}
				else
				{
					cout << "'O' wins the game." << endl;
					gameplay = false;
					return success;
				}
			}
			if (drawresult == true)
			{
				int num = this->turnNumPlayed();
				cout << num << " turns were played. No winning moves remain" << endl;
				gameplay = false;
				return drawfail;
			}
			if (turnresult == quitturn)
			{
				int num = this->turnNumPlayed();
				cout << num << " turns were played. User quited" << endl;
				gameplay = false;
				return quitplay;
			}
		}
	}
};


ostream & operator<<(ostream & out, const Game & g);

//End of the header guard
#endif