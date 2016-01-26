// Tingting Huang, thuanghjz@gmail.com
// the source file for game pieces


#include "stdafx.h"
#include "enumeration.h"
#include "GamePieces.h"
#include <iostream>
#include <string>

using namespace std;

//input a value of piece_color enumerator value, output a string containing a color
string lowercolor(piece_color n)
{
	string enumstr[] = { "red", "black", "white", "invalidcolor", "nocolor" };
	return enumstr[n];
}

//takes a C++ style string, converts and returns the element of the enumerated type
piece_color colortovalue(string s)
{
	lowercase(s);
	if (s == "red"){
		return piece_color::Red;
	} 
	else if (s == "black")
	{
		return piece_color::Black;
	}
	else if (s == "white")
	{
		return piece_color::White;
	}
	else if (s == " ")
	{
		return piece_color::NoColor;
	}
	else
	{
		return piece_color::InvalidColor;
	}
}

//define a struct to represent a game piece.
game_piece::game_piece(piece_color col, string s1, string s2)
: col_(col), s1_(s1), s2_(s2) {}