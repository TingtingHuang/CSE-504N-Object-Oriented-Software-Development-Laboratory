// lab1.cpp : Defines the entry point for the console application.
// Tingting Huang, thuanghjz@gmail.com
// 

#include "stdafx.h"
#include "enumeration.h"
#include "GamePieces.h"
#include "gameboard.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <locale>

using namespace std;

sucAndFail succ = success; //enumeration label of value 0
sucAndFail fail1 = failure1; //enumeration label of value -1
sucAndFail fial2 = failure2; //enumeration label of value -2
arrayindices zero = programName; //enumeration label of index 0
arrayindices one = arg1; //enumeration label of index 0


int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		int result = usage(argv[zero]);
		return result; //return -4
	}
	else
	{
		//take the first program argument as the input
		ifstream ifs;
		ifs.open(argv[one]); //open the file
		if (ifs.is_open())
		{
			unsigned int m; //horizontal extent
			unsigned int n; //vertical extent
			int numofline = 0;
			string testline;
			while (getline(ifs, testline))
			{
				++numofline; //count the number of lines in the input file
			}
			ifs.close(); //close the file to refresh getline function
			ifs.open(argv[one]); //open the file
			if (ifs.is_open())
			{
				int r;
				for (int i = 1; i <= numofline; ++i)
				{
					r = boarddim(ifs, m, n);
					if (r == -1)
					{
						r = boarddim(ifs, m, n); //call boarddim again for reading without extraction
					}
					else
					{
						break; //end the loop when there is successful extraction or no reading
					}
				}
				//If the extraction is not successful, return the error message, else continue
				if (r != 0)
				{
					cerr << "the board dimensions cannot be extracted from the input file." << endl;
					return noextraction; //return -6
				}
				else
				{
					//create empty game board
					vector<game_piece> vect;
					for (unsigned int j = 0; j < (m * n); ++j)
					{
						piece_color nocol = NoColor;
						vect.push_back(game_piece(nocol, " ", " "));
					}
					int r2 = readboard(ifs, vect, m, n); //pass the game pieces in the input file to the vector
					
					if (r2 != 0)
					{
						cerr << "the game pieces cannot be extracted from the input file." << endl;
						return nogamepiece; //return -7
					}
					else
					{
						int r3 = printboard(vect, m, n);
						int extracredit = adjacent(vect, m, n);
						return r3;
					}
				}
				ifs.close(); //close the file
			}
			else
			{
				//print the error message if the file is not open
				cerr << "couldn't open: " << argv[1] << endl;
				return openfail; //return -5
			}
		}
		else
		{
			//print the error message if the file is not open
			cerr << "couldn't open: " << argv[1] << endl;
			return openfail; //return -5
		}
		
	}
}

