// lab4.cpp : Defines the entry point for the console application.
//Tingting Huang, tingtinghuang@wustl.edu

#include "stdafx.h"
#include "GameBase.h"
#include "TicTacToeGame.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <memory>
using namespace std;

int main(int argc, char * argv[])
{
	try{
		//call the static method, check, in GameBase
		GameBase::check(argc, argv);
		//calls the static instance() to obtain a shared pointer to the object
		shared_ptr<GameBase> pointer(GameBase::instance());
		//After instance() is processed, the smart pointer cannot be nullptr. Therefore, the game can be played following the rules
		int playresult = pointer->play();
		return playresult;
	}
	//catch the non-zero values for each distinct failure case that has been thrown by check() or instance().
	catch (sucAndFail value)
	{
		usage(argv[program_name]);
		return value;
	}
	//give an error message if bad_alloc is caught
	catch (bad_alloc& bad)
	{
		cerr << "bad_alloc caught: " << bad.what() << endl;
		return badalloc;
	}
}

