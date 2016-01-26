//GomokuGame.h
//Tingting Huang, tingtinghuang@wustl.edu
//header guard
#ifndef GOMOKUGAME_H
#define GOMOKUGAME_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "GameBase.h"

using namespace std;

const string black = "B";
const string white = "W";

class GomokuGame : public GameBase {
	//Declare a reference to self
	GomokuGame & self;
	//connecting pieces to win
	int con_;
	//current stone coordinate
	int x_;
	int y_;
	//Store player name
	const string player1 = black;
	const string player2 = white;
	//Store the moves of each player
	vector<string> Wmoves;
	vector<string> Bmoves;
	//check whether the adjacent connecting pieces are the same as the given player name.
	bool checkadj(const string playername);
	friend ostream & operator<<(ostream & out, const GomokuGame & g);
public:
	//Constructor
	GomokuGame(int dim, int connecting);
	//Override virtual print
	virtual void print();
	//return true if one player wins
	virtual bool done();
	//return true for being capable of drawing new charactors and neither player has won
	virtual bool draw();
	//Overloaded prompt method
	virtual void prompt(unsigned int & a, unsigned int & b);
	//Change the game board for each valid move for different players
	virtual int turn();
	//Output player name
	virtual const string player();
	//Lab4: override the save() method
	virtual int save(string s);
};

ostream & operator<<(ostream & out, const GomokuGame & g);

//end guard
#endif