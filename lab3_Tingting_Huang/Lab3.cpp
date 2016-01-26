// lab3.cpp : Defines the entry point for the console application.
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
		//create a smart pointer to the result of the static method in GameBase
		shared_ptr<GameBase> pointer(GameBase::check(argc, argv));
		//if the smart pointer points to 0, return the usage message
		if (pointer == nullptr)
		{
			int result = usage(argv[success]);
			return result;
		}
		//otherwise, the game can be played following the rules in the extra arguments
		else
		{
			int playresult = pointer->play();
			return playresult;
		}
	}
	catch (sucAndFail result)
	{
		return result;
	}
	
}
