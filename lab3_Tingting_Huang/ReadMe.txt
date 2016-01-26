Name: Tingting Huang
Lab number: lab3


////////////////////////////////////////////////////////////////////////////
Design Process:
Problem 5
Move the common variables from TicTacToeGame to the protected part of G
ameBase

Problem 6
Change the displaying type of game piece from char to string 

Problem 7
Add a protected variable for the length of the longest game piece. Since the
length of game piece of both TicTacToe and Gomoku is known as 1, this 
variable is initialized as 1 in the constructor of each derived class, and 
is updated in turn() method whenever a new game piece is added to the game 
board.

Problem 8
Using setw manipulator to make sure that each column printed has the same 
length as the longest game piece.

Problem 9-15
Follow the instructions
Note: for Problem 12, draw method is fullfilled by replacing all the 
remaining emtpy square step by step with the next player name, and call 
done() to count the number of possible winning moves. If there is no 
possible winning move, the draw method will return true to end the game.
Make sure to copy the original board before replacing, and restore the 
board to continue the game.

Problem 16
The static method "check" will check the number of argument, argv[1] name, 
and any additional arguments for the extra credit part. 

Problem 17
Using shared_ptr as a pointer to the result of the static method

Problem 19
Similarly, create a public inheritated GomokuGame class with additional 
private varibles to store current game piece coordinates and the number of 
connecting piece to win for the extra credit

Problem 20
GomokuGame is initialized as 21x21 board with the buffer and 5 connecting 
pieces to win

Problem 21
Instead of printing 1 to 19 as shown in the instruction, mine prints 0 to 20
with the buffer

Problem 22
As instruction

Problem 23
Create a new method called "checkadj" to check whether the adjacent 
connecting pieces are the same as the given game piece, which is composed 
of 4 parts:
1. check the same row: starting at the current game piece, count the 
connecting pieces with the same color to the right and left directions. If
the count number is greater or equal to the number of connecting pieces to
win, then the boolean of the same row check is changed to true.
2. check the same column: similarly, check the connecting pieces to the up
and down directions
3. lower left to upper right diagonal: changing the horizontal and vertical
coordinates together by 1 to both directions
4. upper left to lower right diagonal: changing the horizontal coordinate by
-1 and the vertical coordinate by 1.
This done() method will call checkadj() to match the game piece at current
coordinate. If any of the checkadj() return true, one player must win the game.

Problem 24
Similarly to TicTacToeGame Problem 12 with additional copying and restoring
the current coordinates.

Problem 25
Provide a virtual prompt() method. Instead of returning int as TicTacToe,
returns void and throw the enumeration of three possible cases: quit,
invalid coordinate, and valid coordinate.

Problem 26
Similar to TicTacToe, catch what is thrown by prompt(), and update the board,
as well as the length of the longest game piece

////////////////////////////////////////////////////////////////////////////
Error/warning Messages:

1. error C2248:'GameBase::play':cannot access protected member declared in 
class 'GameBase'
Solution: make the play method in GameBase public, and make TicTacToeGame as
 	 a puclib derived class of GameBase.

2. warning C4715: 'GameBase::check' : not all control paths return a value
Solution: list all possible cases in if/ else if, ended with an else for 
	 returning null pointer. 


////////////////////////////////////////////////////////////////////////////
Test cases:
1. If invalid coordinates but not quit moves are inputed:
the program will continue to show "please type quit to end the game or a string
 representating a valid coordinate separated by comma" until a valid move
is inputed.

2. If the game piece at the given coordinates is not empty:
the program will continue to show "please type quit to end the game or a string
 representating a valid coordinate separated by comma" until a valid move
is inputed.

3. If the user quit the program any time:
The program will quit, and output "number turns were played. User quited"
return code: -5

4. If any user wins the game in a row, column, or any diagonal direction:
The program will stop, and output "'player name' wins the game"
return code: 0

5. If no one wins and there is no more possible winning moves for the next player:
The program will stop, and output "number turns were played. No winning moves remain"
return code: -4

6. Badly formed command lines: without a game name
The program will output "usage: Lab3.exe <TicTacToe or Gomoku with additional commands>"
return code:-1

7.Badly formed command lines: with wrong game name
The program will output "usage: Lab3.exe <TicTacToe or Gomoku with additional commands>"
return code:-1



////////////////////////////////////////////////////////////////////////////
Extra Credit:
Problem 32
The actual size of game board is the dimension of playing board +2 with buffer.

Problem 33
modified in done() in Problem 23

Problem 34
List all possible cases in the static method in GameBase. If non-positive extra 
number is in the command, outputs an error message and throws a non-zero 
enumeration type, which will be cought in the main function for return.

Test Cases:
1. Badly formed command lines: one extra command with non-positive dimension
The program will output an error message "Please inpout a positive dimension"
return code:-8

2. Badly formed command lines: two extra command with either one being non-positive
The program will output an error message "Please input a positive dimension and a positive number of connecting pieces"
return code:-9

3. No additional arguments after Gomoku:
functions properly as before with 19x19 playing board and 5 connecting pieces to win

4. One additional positive argument:
Gomoku playing board has the dimension as the additional argument,
and the first player would always win, because the connecting pieces is 1 as default.

5. Two additional positive argument:
Gomoku playing board has the dimension as the first additional argument,
and connecting pieces is the second additional argument.
