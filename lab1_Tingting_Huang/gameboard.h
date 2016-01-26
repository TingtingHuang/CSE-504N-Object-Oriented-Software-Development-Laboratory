// Tingting Huang, thuanghjz@gmail.com
// Use the name of the header file for the header guard.
#ifndef	GAMEBOARD_H
#define	GAMEBOARD_H

//header file content
int boarddim(ifstream & ifs, unsigned int & m, unsigned int & n);
int readboard(ifstream & ifs, vector<game_piece> & vect, unsigned int m, unsigned int n);
int printboard(const vector<game_piece> & vect, unsigned int m, unsigned int n);
int adjacent(const vector<game_piece> & vect, unsigned int m, unsigned int n);

//guard ending
#endif