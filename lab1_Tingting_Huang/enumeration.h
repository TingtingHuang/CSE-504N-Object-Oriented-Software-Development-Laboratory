// Tingting Huang, thuanghjz@gmail.com
// Use the name of the header file for the header guard.
#ifndef ENUMERATION_H
#define	ENUMERATION_H

// Content of the header file. 
#include <string>
#include <vector>
using namespace std;
enum arrayindices { programName = 0, arg1 = 1 };
enum sucAndFail { success = 0, failure1 = -1, failure2 = -2, failure3 = -3, usagefail = -4, openfail = -5, noextraction = -6, nogamepiece = -7, unmatch = -8};
int parsing(vector<string> & vect, char * filename);
int usage(char * name);
int lowercase(string & str);

// End of the hearder guard
#endif