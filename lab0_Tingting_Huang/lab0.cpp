// lab0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "enumeration.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

sucAndFail succ = success; //enumeration label of value 0
sucAndFail fail = failure; //enumeration label of value -1
arrayindices zero = programName; //enumeration label of index 0
arrayindices one = arg1; //enumeration label of index 0

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
		return succ; //return 0
	}
	else
	{
		//print the error message if the file is not open
		cerr << "couldn't open: " << filename << endl; 
		return fail; //return -1
	}
}

//tells the user the correct usage for having the wrong number of command line arguments
int usage(char * name)
{
	cout << "usage: " << name << " <input_file_name>" << endl;
	return fail;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		int result = usage(argv[zero]);
		return result;
	}
	else
	{
		char * filename = argv[one]; //take the first program argument as the input filename 
		vector<string> vect;
		int k = parsing(vect, filename);
		if (k != 0)
		{
			return k;
		}
		else
		{
			vector<int> ints; //Declare a vector of integers
			//test whether each string in the vector of string contains only numeric digit characters
			for (size_t s = 0; s < vect.size(); ++s)
			{
				string str = vect[s]; //each string in the vector of strings
				bool alldigit; //set the boolean for testing numeric string
				for (unsigned int j = 0; j < str.length(); j++)
				{
					if (!isdigit(str[j]))
					{
						alldigit = false;
						break; //if the first non numeric digit appears in the string, goto the next string
					}
					else
						alldigit = true; //the boolean is true for numeric string
				}
				
				if (alldigit)
				{
					istringstream ss(str); //wrap the numeric string in an input string stream
					int num;
					ss >> num; //convert to an integer
					ints.push_back(num); //push the integer back into the vector os integers
				}
				else
				{
					cout << str << endl; //print non-numeric string
				}
			}
			for (size_t t = 0; t < ints.size(); t++)
			{
				cout << ints[t] << endl; //print out each integer
			}
			return succ;
		}
	}
}



