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

enum indices { program_name, game_name, expected_args, expected_dim, expected_con };
enum sucAndFail { success = 0, usagefail = -1, quitprompt = -2, quitturn = -3, drawfail = -4, quitplay = -5, invalidcoor = -6, gamestop = -7, nonposdim = -8, nonposboth = -9, nullsharedpt = -10, nonnullsharedpt = -11, badcommand = -12, badalloc = -13, failopensave = -14, failclosesave = -15, sameinitial = -16 };
int usage(char * name);

//Declare the base class
class GameBase {
protected:
	//Declare a reference to self
	GameBase & self;
	//Declare game dimension
	unsigned int dim_;
	
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
	//Lab4: Declare pure virtural method to save the game file
	virtual int save(string s) = 0;
	//Ask the user to input valid form of coordinates or quit the game
	int prompt(unsigned int & i, unsigned int & j);
	//Lab4: add a shared smart pointer to the game base
	static shared_ptr<GameBase> sharedpt;
	//save the number of turns played
	int turns;
public:
	//common method
	int turnNumPlayed();
	//method used to record the whole game
	int play();
	static void check(int argc, char* argv[]);
	//Lab4: static instance method to return a shared smart pointer to the game base
	static shared_ptr<GameBase> instance();
	//Declare vector of vector of string for the game board
	vector<vector<string>> board;
};

//End of the header guard
#endif