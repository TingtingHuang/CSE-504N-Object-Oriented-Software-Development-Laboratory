//SudokuGame.h
//Tingting Huang, tingtinghuang@wustl.edu
//header guard
#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "GameBase.h"

using namespace std;

class SudokuGame : public GameBase {
	//Declare a reference to self
	SudokuGame & self;
	////Lab4: create the method to convert int to string for presenting on the board
	//string inttostr(int i);
	//Store the moves of the player
	vector<string> moves;
	//Store the inital position than cannot be changed
	vector<int> inipos;
	friend ostream & operator<<(ostream & out, const SudokuGame & g);
public:
	//Constructor
	SudokuGame();
	//Override virtual print
	virtual void print();
	//return true if the player wins
	virtual bool done();
	//Override virtual draw
	virtual bool draw();
	//Override virtual turn
	virtual int turn();
	//Override virtual player
	virtual const string player();
	//Lab4: override the save() method
	virtual int save(string s);
	//provide a new prompt method
	virtual int prompt(unsigned int & i, unsigned int & j, unsigned int & k);
	//new method to count the number of turns played
	virtual int turnNumPlayed();
};

ostream & operator<<(ostream & out, const SudokuGame & g);

//end guard
#endif