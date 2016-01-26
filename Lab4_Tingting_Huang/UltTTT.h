//UltTTT.h
//Tingting Huang, tingtinghuang@wustl.edu
//header guard
#ifndef ULTTTT_H
#define ULTTTT_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "GameBase.h"
#include "TicTacToeGame.h"

using namespace std;

class UltTTT : public TicTacToeGame {
	//Declare a reference to self
	UltTTT & self;
	//Player name
	const string player1 = first;
	const string player2 = second;
	//Store the moves of each player
	vector<string> Omoves;
	vector<string> Xmoves;
	friend ostream & operator<<(ostream & out, const UltTTT & g);
	//Extra: vector of 9 TicTacToe games
	vector<TicTacToeGame*> games;
	//Extra: declare the number of game in a row
	unsigned int rownum = this->dim_ - 2;
	//Extra: declare the number of total games
	unsigned int totalnum = rownum * rownum;
	//Extra:count total turn number of 9 sub-games
	int totalturnNumPlayed();
	//Extra: declare the result of each sub-game using the player's name
	vector<const string> gameresult;
	//Extra: choose sub-game, return the index of the sub-game 
	int subgame(unsigned int & a, unsigned int & b);
    //Extra: store the index for sub-game for next turn, initialized at 9
	int index;

public:
	//Constructor
	UltTTT(int dim);
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


ostream & operator<<(ostream & out, const UltTTT & g);

//End of the header guard
#endif