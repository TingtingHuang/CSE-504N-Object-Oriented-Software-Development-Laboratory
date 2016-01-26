//TicTacToeGame.h
//Tingting Huang, tingtinghuang@wustl.edu
//header guard
#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "GameBase.h"

using namespace std;

const string first = "X";
const string second = "O";
class TicTacToeGame : public GameBase {
	//Declare a reference to self
	TicTacToeGame & self;
	//Player name
	const string player1 = first;
	const string player2 = second;
	//Store the moves of each player
	vector<string> Omoves;
	vector<string> Xmoves;
	friend ostream & operator<<(ostream & out, const TicTacToeGame & g);
public:
	//Constructor
	TicTacToeGame(int dim);
	//Override virtual print
	virtual void print();
	//return true if one player wins
	virtual bool done();
	//return true for being capable of drawing new charactors and neither player has won
	virtual bool draw();
	//Change the game board for each valid move for different players
	virtual int turn();
	//Output player name
	virtual const string player();
	//Lab4: override the save() method
	virtual int save(string s);
};


ostream & operator<<(ostream & out, const TicTacToeGame & g);
//End of the header guard
#endif