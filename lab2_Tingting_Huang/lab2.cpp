// lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TicTacToeGame.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 1)
	{
		int result = usage(argv[success]);
		return result; //return -4
	}
	else
	{
		Game g;
		int playresult = g.play();
		return playresult;
	}
}

