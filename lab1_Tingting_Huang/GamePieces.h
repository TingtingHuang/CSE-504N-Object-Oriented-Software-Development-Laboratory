// Tingting Huang, thuanghjz@gmail.com
// Use the name of the header file for the header guard.
#ifndef GAMEPIECES_H
#define GAMEPIECES_H

//content of the hearder file
enum piece_color { Red, Black, White, InvalidColor, NoColor};

string lowercolor(piece_color n);
piece_color colortovalue(string s);

//declare a struct to represent a game piece
struct game_piece {
	// col is a variable of the enumerated type
	// s1 is the string variable to hold the name of the piece
	// s2 is the string variable to represent how the piece should be displayed
	game_piece(piece_color col, string s1, string s2);
	piece_color col_;
	string s1_;
	string s2_;
};

//end of guard
#endif