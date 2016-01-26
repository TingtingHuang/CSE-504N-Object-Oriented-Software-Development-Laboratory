// Tingting Huang, thuanghjz@gmail.com
// the source file for a game board


#include "stdafx.h"
#include "enumeration.h"
#include "GamePieces.h"
#include "gameboard.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//function boarddim reads in the dimensions of a game board from an input file stream with m as the horizontal dimension, and n as the vertical dimension
int boarddim(ifstream & file, unsigned int & m, unsigned int & n)
{
	string line;
	if (getline(file, line)) //read the first line 
	{
		istringstream content(line); //bind content to the first line
		if (content >> m >> n)
		{
			return success; //return 0, since the function successfully extracts the dimensions
		}
		else
		{
			return failure1; //return -1, since the function can read a line but cannot extract dimensions
		}
	}
	else 
	{
		return failure2; //return -2, since the function cannot read a line
	}
}

//function readboard reads game pieces from an input file stream
int readboard(ifstream & ifs, vector<game_piece> & vect, unsigned int m, unsigned int n)
{
	string line;
	int linenum = 0;
	while (getline(ifs, line)) //read each line from the input file stream
	{
		istringstream content(line); //bind content to the first line
		string color;
		string name;
		string display;
		unsigned int a; //horizontal coordinate
		unsigned int b; //vertical coordinate

		if (content >> color >> name >> display >> a >> b)
		{
			//check whether the game piece is well formed
			piece_color value = colortovalue(color);
			if ((value == 3) || (a >= m || b >= n))//if the game piece color is invalid or the coordinates are outside of the board, continue to next line
			{
				continue; 
			}
			
			//after checking the validity of the line, update the vetor of game piece
			int index = m * b + a; //find the index into the vector of game pieces
			vect[index] = game_piece(value, name, display);
			++linenum;

		}
		else //if the function is not able to extract five values, continue to next line
		{
			continue;
		}
	}
	//check the number of well formed piece
	if (linenum != 0)
	{
		return success;
	}
	else
	{
		return failure3; //return -3 for failing to find any well formed piece definitions
	}
}

//function printboard for printing out the pieces
int printboard(const vector<game_piece> & vect, unsigned int m, unsigned int n)
{
	if (vect.size() == (m * n))
	{
		string **matrix = new string *[n];

		for (unsigned int i = 0; i < n; ++i)
		{
			matrix[i] = new string[m];
		}
		for (unsigned int i = 0; i < m; ++i)
		{
			for (unsigned int j = 0; j < n; ++j)
			{
				int index = m * j + (m - 1 - i); //using the same formular to find index in vector with flipped rows
				matrix[i][j] = vect[index].s2_;

				cout << "|" << matrix[i][j] << "|";
			}
			cout << endl;

		}

		return success;
	}
	else
	{
		return unmatch; //return -8
	}

}

//Extra credit
int adjacent(const vector<game_piece> & vect, unsigned int m, unsigned int n)
{
	//Initiate a pointer to pointer to mimic 2 dimensional array
	string **matrix = new string *[n];
	for (unsigned int i = 0; i < n; ++i)
	{
		matrix[i] = new string[m];
	}
	
	for (unsigned int i = 0; i < m; ++i)
	{
		for (unsigned int j = 0; j < n; ++j)
		{
			int index = m * j + i; //using the same formular to find index in vector
			if (vect[index].s1_ != " ")
			{
				string color = lowercolor(vect[index].col_);
				cout << i << "," << j << " " << color << " " << vect[index].s1_ << ": ";
				if (i == 0 && j != 0)
				{
					for (unsigned int a = i; a <= (i + 1); ++a)
					{
						for (unsigned int b = (j - 1); b <= (j + 1); ++b)
						{
							if (a != i || b != j)
							{
								int surindex = m * b + a; //using the same formular to find index of surrounding spaces including itself
								int valid = m * n - 1;
								if ((0 <= surindex) && (surindex <= valid)) // make sure there is a color in the surrounding space and the space exits
								{
									if (vect[surindex].s1_ != " ")
									{
										string surcolor = lowercolor(vect[surindex].col_);
										cout << a << "," << b << " " << surcolor << " " << vect[surindex].s1_ << "; ";
									}
								}
							}
						}
					}
				}
				else if (j == 0 && i != 0)
				{
					for (unsigned int a = (i - 1); a <= (i + 1); ++a)
					{
						for (unsigned int b = j; b <= (j + 1); ++b)
						{
							if (a != i || b != j)
							{
								int surindex = m * b + a; //using the same formular to find index of surrounding spaces including itself
								int valid = m * n - 1;
								if ((0 <= surindex) && (surindex <= valid)) // make sure there is a color in the surrounding space and the space exits
								{
									if (vect[surindex].s1_ != " ")
									{
										string surcolor = lowercolor(vect[surindex].col_);
										cout << a << "," << b << " " << surcolor << " " << vect[surindex].s1_ << "; ";
									}
								}
							}
						}
					}
				}
				else if ((i == 0) && (j == 0))
				{
					
					for (unsigned int a = i; a <= (i + 1); ++a)
					{
						for (unsigned int b = j; b <= (j + 1); ++b)
						{
							
							if (a != i || b != j)
							{
								int surindex = m * b + a; //using the same formular to find index of surrounding spaces including itself
								int valid = m * n - 1;
								if ((0 <= surindex) && (surindex <= valid)) // make sure there is a color in the surrounding space and the space exits
								{
									if (vect[surindex].s1_ != " ")
									{
										string surcolor = lowercolor(vect[surindex].col_);
										cout << a << "," << b << " " << surcolor << " " << vect[surindex].s1_ << "; ";
									}
								}
							}
						}
					}
				}
				else
				{
					for (unsigned int a = (i - 1); a <= (i + 1); ++a)
					{
						for (unsigned int b = (j - 1); b <= (j + 1); ++b)
						{
							if (a <= (m - 1) && b <= (n - 1))
							{
								if (a != i || b != j)
								{
									int surindex = m * b + a; //using the same formular to find index of surrounding spaces including itself
									int valid = m * n - 1;
									if ((0 <= surindex) && (surindex <= valid)) // make sure there is a color in the surrounding space and the space exits
									{
										if (vect[surindex].s1_ != " ")
										{
											string surcolor = lowercolor(vect[surindex].col_);
											cout << a << "," << b << " " << surcolor << " " << vect[surindex].s1_ << "; ";
										}
									}
								}
							}
						}
					}
				}
				
				cout << endl;
			}
		}
	}
	return success;
}