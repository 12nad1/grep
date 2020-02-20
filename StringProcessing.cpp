// StringProcessing.cpp
// Maxwell Kaye
// Apr 17, 2018
// Implementation for String Processing

#include <iostream>
#include <cctype> 	// for isalnum function
#include <cstring> 	// for strcmp
#include <string>
using namespace std;

int main()
{
	bool done = false;
	while (!done)	// loops until the user quits the program
	{
		// the full word, with non alphanumeric characters
		string full_name = "";
		cin >> full_name;

		// the word without alphanumeric characters
		string pure_name = "";

		// builds pure_name
		int len = full_name.length();
		for (int i = 0; i < len; i++)
		{
			// the ASCI value for ! is 33
			if (isalnum(full_name[i]) || full_name[i] == 33)
			{
				pure_name += full_name[i];
			}
		}

		cout << pure_name << endl << endl;
	}
	return 0;
}