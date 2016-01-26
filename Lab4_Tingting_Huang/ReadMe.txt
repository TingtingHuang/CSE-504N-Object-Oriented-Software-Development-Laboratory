Name: Tingting Huang
Lab number: lab4


////////////////////////////////////////////////////////////////////////////
Design Process:
Part II:
Problem 3-8:
Followed the instructions. 
Caught any exceptions, including bad_alloc, to handle badly formed command in
Lab.cpp

Part III:
Problem 9-11:
For TicTacToe:
Save:
If the player chooses to quit and save, the program will save the game name as
the first line, and save the all non-empty game pieces in the form of
"horizontal coordinate_vertical coordinate_game piece" in separate lines. For
an example, an "X" in (2,2) should be saved as 2 2 X
If the player chooses to quit without saving, the program will overwrite and 
save "NODATA" as the first line.
Also, whenever a game is completed, the program will overwrite and save "NEW"
as the first line.
Load:
After opening the game file, the program will check the first line. If the first
line is the same as the game name, then the program will continue to read the \
following coordinates and pieces and update the board. Otherwise, the normal 
constructor will be called to create an empty board

For Gomoku:
Save:
The only difference is that after saving the game name in the first line, the 
program will save the "board dimension with buffer_connecting pieces" in the 
second line. Example, for 3x3 board with connecting pieces as 3, the saved 
second line will be 5 3
Load:
The only difference from TicTacToe is that, besides checking the game name in 
the first line, the program will check whether the newly given dimensions and 
connecting pieces are the same with the saved game file. If they are same, load 
the file as before; otherwise, start a new game.

Part IV:
For Sudoku:
1.Sudoku game class is derived from the game base class. 
2.Define the << operator to print the game as the example given in the instruction.
3.For constructor, initialize the board with the numbers from "sudoku0", and 
record the positions of the initial pieces in a vector of integers in the form of 
10*horizontal coordinate+vertical coordinate, such that each position on the board
correspond to a distinct value.Later, the constructor will try to open the game file
to check whether to load or not as discussed in Part III.
4.Override the prompt() to take in three unsigned int. Make sure they are in the
valid range in turn(), and the new coordinate doesn't appear in the initial positions.
Otherwise, the program will ask the player to input the correct numbers until they 
are in the right form. 
5.For done(), the idea is to push the game pieces in the same row, column, or
sub-grid into an empty set of string.Since there is no duplicate element when 
inserting the game pieces into the set, and the game pieces are restricted from 
1 to 9 by prompt() shown as strings, the check of each rule will pass if the size
of the set is 9. done() will return true if all rules are passed.
6. draw() always returns false.
7.Similar to TicTacToe, save the file with the game name in the first line,
and the non-empty pieces in separate lines. "NODATA" for no saving. "NEW" for
completed game.

Part V:
Conceptual understanding of the five features:
Copy constructor will copy an existing object to a newly created object, and 
move constructor creats by passing r-value
Copy assignment operator will match an existing object to the same values as
the l-value, and move-assignment operator changes the existing variables by 
passing r-value reference.
Destructor will destroy the object from memory.

For my design ideas, the default copy constructors and destructors are sufficient
for all my game classes

////////////////////////////////////////////////////////////////////////////
Error/warning Messages:

1. error C2259: 'GameBase': cannot instantiate abstract class
Solution: After checking the Ouput view, the problem was found when I tried 
to store the address of game object to the shared smart pointer with
make_shared<GameBase>. Instead, declare a separate shared pointer initialized
with the new game object, and assign it to the protected variable.


////////////////////////////////////////////////////////////////////////////
Test cases:
For all three games:
1. If invalid coordinates (outside of board/bad format) but not quit moves are inputed:
the program will continue to ask the player to give inputs until a valid move
is inputed.

2. If the game piece at the given coordinates is not empty for TicTacToe and 
Gomoku, or the given coordinates is at the initial pieces for Sudoku, or the 
given game piece is not from 1 to 9 for Sudoku:
the program will continue to ask the player to give inputs until a valid move
is inputed.

3. If the user quit the program any time for all three games:
The program will ask the player to save or not. If the user chooses to save, 
the program will save the current board to a game file with the same game 
name
return code: -5

4. If the user quit the program any time for all three games:
The program will ask the player to save or not. If the user chooses not to save, 
the program will not save the game and quit. Overwrite the saved game file with
"NODATA"
return code: -5

5. For TicTacToe and Gomoku, If any user wins the game in a row, column, or 
any diagonal direction:
The program will stop, and output "'player name' wins the game". Overwrite 
the saved game file with "NEW"
return code: 0

6. For TicTacToe and Gomoku, If no one wins and there is no more possible winning 
moves for the next player:
The program will stop, and output "number turns were played. No winning moves remain"
Overwrite saved game file with "NEW"
return code: -4

7. For Sudoku, If the player wins:
The program will stop, and output "you wins the game." Overwrite the game file 
with "NEW"

8. For Sudoku, if the player doen't win, but the board is full:
The program will output "All cells are filled, please prompt additional inputs" and
continue the game

9. For Gomoku, with negative dimensions: Lab4.exe Gomoku -1:
The program will output "Please input a positive dimension and the user message
return code: -8

10.For Gomoku, with negative connecting pieces: Lab4.exe Gomoku 3 -3:
Output "Please input a positive dimension and a positive number of connecting pieces 
and the user message
return code: -9

11. Badly formed command lines: without a game name
The program will output "usage: Lab3.exe <TicTacToe or Gomoku with additional commands>"
return code:-12

12.Badly formed command lines: with wrong game name
The program will output "usage: Lab3.exe <TicTacToe or Gomoku with additional commands>"
return code:-12



////////////////////////////////////////////////////////////////////////////
Extra Credit:

Ultimate TicTacToe is a derived class of TicTacToe

move prompt, board to public in GameBase for access from UltTTT

overload all virtual methods 

UltTTT is constructed with a vector of 9 dynamiclly allocated TicTacToe games, call this->games
the 9 game results for each sub-game is stored in vector of strings this->gameresult.
if one player wins in a sub-game, the result at corresponding position is the player name
if a sub-game is draw, the result is "draw"
otherwise, it is empty

To play:
1. input valid coordinates (0-2) to choose the position of sub-game
Example: (0,0) for lowerleft corner, and (2,2) for the upperright corner
If i) invalid coordinates
   ii) sub-game with valid coordinates is either done or draw, 
the program will ask the user to input again.
if quit, then the whole game quits, goes to step 3)

2. in the given sub-game, input valid coordinates for game pieces (1 to 3) just like TicTacToe
If i) invalid coordinates
   ii) this sub-game is either done or draw, 
the program will ask the user to input again.
if quit, then the whole game quits, goes to step 3)
If valid coordinates are provided, do:
   i)change the game piece in this sub-game to the player name according to the total number of turns played
   ii) update the private variable this->index for the index of this->games with the formular, index = x*3+y
	if the sub-game at the updated index is not done or draw, do nothing
	otherwise, change the updated index to 9, which will loop back to step 1)

3. when quit
if save game, do:
   i)save the game name to the first line
   ii) save the game results in the second line
   iii) save the nonempty game pieces in the format of 
	"sub-game_index horizontal_coor vertical_coor game_piece"
	such as 1 1 1 X in sub-game (0,1) with "X" at position (1,1)
if not save, do:
   overwrite with single line of "NODATA"
if game is completed, do:
   overwrite with single line of "NEW"

4. when initiate:
copy both the whole gameboard and the gameresult to continue.


