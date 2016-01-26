Name: Tingting Huang
Lab number: lab2


////////////////////////////////////////////////////////////////////////////
Design Process:
Problem 6
lowercase function in "CommonFunction.cpp"

Problem 7
In "GamePieces.h", enumeration piece_color as Red, Black, White, InvalidColor, 
and NoColor

Problem 8
In "GamePieces.cpp", function lowercolor takes in a piece_color value, and 
returns a string of the name of the color all in lowercase.

Problem 9
In "GamePieces.cpp", function colortovalue takes in a string of a color that 
can have mixed lower or upper cases, and returns its corresponding value in 
the enumeration.

Problem 10
In "GamePieces.h" and "GamePieces.cpp", declare and define a struct game_piece 
with variables of the enumerated type, and two strings

Problem 11
In "gameboard.cpp", function boarddim reads the dimensions of a game board, 
and returns 0 for success, -1 for being able to read, but not to extract, -2 
for not being able to read

Problem 12
In "gameboard.cpp", function readboard reads game pieces from an input file 
stream. While the getline function works properly, the content of each line 
is passed to a string stream. If five values are not successfully extracted, 
continue to next line. If the colorvalue is invalid as 3, or the coordinates
fall outside of the board, continue to next line. After checking each line is 
ell-formed, update the game piece in the vector at corresponding index.
Reutn 0 for success, -3 or odd number of well-formed extraction.

Problem 13
Create a pointer to pointer to string to mimic the 2 dimensional array. 
Since the indicate numbers of rows are flipped, I used (m-1-i) to flip the rows.

////////////////////////////////////////////////////////////////////////////
Error/warning Messages:

1. error C2758: 'Game::self' : a member of reference type must be initialized
Solution: initialize as Game():self(*this)

2. error LNK1169: one or more multiply defined symbols found
Solution: in TicTacToeGame.h, define constant variables as 
	const char first = 'X';
	const char second = 'O';

////////////////////////////////////////////////////////////////////////////
Executable cases:
1. If invalid but not quit moves are inputed:
the program will continue to show "please type quit to end the game or a string
 representating a valid coordinate separated by comma" until a valid move
is inputed.

2. If the user quit the program any time:
The program will quit, and output "number turns were played. User quited"
The return code: -5

3. If any user wins the game:
The program will stop, and output "'X' or 'O' wins the game"
return code: 0

4. If no one wins but the board is filled:
The program will stop, and output "number turns were played. No winning moves remain"
return code: -4
