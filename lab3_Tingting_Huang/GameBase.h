//GameBase.h
//Tingting Huang, tingtinghuang@wustl.edu
//header guard
#ifndef GAMEBASE_H
#define GAMEBASE_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <memory>

using namespace std;


enum sucAndFail { success = 0, usagefail = -1, quitprompt = -2, quitturn = -3, drawfail = -4, quitplay = -5, invalidcoor = -6, gamestop = -7, nonposdim = -8, nonposboth = -9 };
int usage(char * name);

//Declare the base class
class GameBase {
protected:
	//Declare a reference to self
	GameBase & self;
	//Declare game dimension
	unsigned int dim_;
	//Declare vector of vector of string for the game board
	vector<vector<string>> board;
	//Constructor
	GameBase(int dim);
	//Declare a integer variable for the longest display string length
	unsigned int longeststr;
	//player name
	virtual const string player() = 0;
	//Declare pure virtual methods
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;
	//common method
	int turnNumPlayed();
	//Ask the user to input valid form of coordinates or quit the game
	int prompt(unsigned int & i, unsigned int & j);
public:
	//method used to record the whole game
	int play();
	static GameBase* check(int argc, char* argv[]);
};

//End of the header guard
#endif