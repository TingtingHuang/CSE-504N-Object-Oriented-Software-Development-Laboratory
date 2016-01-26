//functions for the main
// Tingting Huang, thuanghjz@gmail.com

#include "stdafx.h"
#include "enumeration.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <locale>

using namespace std;

//parse an input file containing text strings and whitespaces
int parsing(vector<string> & vect, char * filename)
{
	//load the text file named as filename in C-style string.
	ifstream ifs;
	ifs.open(filename); //open the file
	if (ifs.is_open())
	{
		string line;
		string word; //hold a line and word from input.
		while (getline(ifs, line)) //read each line from the input
		{
			istringstream content(line); //bind content to the line read from the input
			while (content >> word) //read each word in the line
			{
				vect.push_back(word); //store each word in the vector string
			}
		}
		ifs.close(); //close the file
		return success; //return 0
	}
	else
	{
		//print the error message if the file is not open
		cerr << "couldn't open: " << filename << endl;
		return failure1; //return -1
	}
}

//tells the user the correct usage for having the wrong number of command line arguments
int usage(char * name)
{
	cout << "usage: " << name << " <input_file_name>" << endl;
	return usagefail; //return -4
}

//takes a reference to a C++ style string and modifies all the alphabetic characters in it to lowercase
int lowercase(string & s)
{
	int i = 0;
	//loop through each character in the string, if the character is uppercase, replace it with its lowercase
	while (s[i]) {
		if (isupper(s[i]))
			s[i] = tolower(s[i]);
		++i;
	}
	return success;
}