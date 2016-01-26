Name: Tingting Huang
Lab number: lab1


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

1. warning C4018: '<' : signed/unsigned mismatch: for (int j = 0; j < (m * n); ++j)
solution: for (unsigned int j = 0; j < (m * n); ++j)

2. Always gives error message as cerr << "the board dimensions cannot be extracted from the input file." << endl
solution: because I used getline function before boarddim in main funtion to count the number of lines in the input file,
I need to close and reopen the input file to refresh the getline function.

////////////////////////////////////////////////////////////////////////////
Executable cases:
1. For regular gomoku.txt trails, the command line is:
	H:\My Documents\Visual Studio 2013\Projects\Debug>lab0.exe gomoku.txt
The program prints the game board with "x" and "o" showing at the correct places.
The return code: 0

2. Delete the first row where the dimensions are stored to make badley formated lines.
The program prints an error message: the board dimensions cannot be extracted from the input file.
The return code: -6

3. Add empty lines before and inbetween each game piece line
The program prints the game board with "x" and "o" showing at the correct places, because empty lines have been skipped.
The return code: 0

4. Change the color at (0,0) from "black" to "B"
The program prints the game board without any entry at (0,0), because invalid colors have been skipped.
The return code: 0

5. Change the color at (0,0) from "black" to "Black"
The program prints the game board with "x" and "o" showing at the correct places, because the color names have been converted to lowercases.
The return code: 0

6. Delete all the 5 parameter lines
The program prints an error message: the game pieces cannot be extracted from the input file.
The return code: -7

7. Pass a test file that doesn't exist
The program prints an error message: couldn't open: all.txt
The return code: -5

8. Pass more than 1 test file
The program prints an usage message: usage: lab1.exe <input_file_name>
The return code: -4

EXTRA Credit:
it works with all if conditions!