/*
 * gerp.cpp
 *
 * Driver for gerp
 *
 * COMP15 
 * Spring 2018
 * Project 2
 * Maxwell Kaye
 * 
 */
#include "FSTree.h"
#include "DirNode.h"
#include "LinkedList.h"
#include "HashString.h"
#include "HashTable.h"

#include <iostream>
#include <fstream>
#include <cctype> 	// for isalnum function
#include <cstring> 	// for strcmp
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;

void traverse(DirNode*, string, LinkedList<string>&);
string modify_string(string);
void inquire(Hash<HashString>&, Hash<HashString>&);

int main(int argc, char *argv[])
{
	// make sure the provide exactly one command line argument
	if (argc != 2)
	{
		cout << "Usage:  gerp directory" << endl
		<< "\t\twhere: directory is a valid directory";
		return 0;
	}
	// instantiate an FSTree object using paramaterized constructor
	FSTree tree(argv[1]);

	// useful string, stores the current path from the root
	string path = "";

	// stores all of the paths
	LinkedList<string> paths;

	// traverse tree and create a list of paths with helper function
	traverse(tree.get_root(), path, paths);

	// make a HashTable to store all of the words in all of the files
	Hash<HashString> big_table;
	// make another one to store insenstive words
	Hash<HashString> insensitive_table;

	// Now that paths is loaded with every file to search for text,
	// loop through the LinkedList, examining each file
	for (int index = 0; index < paths.get_length(); index++)
	{
		path = paths.get_value_at(index);
		paths.delete_value_at(index);
		index++;

		// open file
		ifstream infile;
		infile.open(path);

		if (!infile.is_open())
		{
			cerr << "File failed to open.\n";
		}	// checks if the file opened

		string full_line;
		string dirty_word;
		string clean_word;
		// For each word in the file, make it into a HashString object
		// and include its path as an attribute of the HashString. Insert
		// that HashString object into the HashTable
		int line_num = 0;
		while (!infile.eof())
		{
			// get full lines and parse them into words
			getline(infile, full_line);
			line_num++;
			stringstream ss(full_line);
			string temp;
			while (ss >> dirty_word)
			{
				clean_word = modify_string(dirty_word);
				HashString hs(clean_word, full_line, path, line_num);
				big_table.insert(hs);

				// now insert the same word case insenstively into
				// the other hash table
				for (int i = 0; i < clean_word.length(); i++)
				{
					clean_word[i] = tolower(clean_word[i]);
				}
				HashString hsi(clean_word, full_line, path, line_num);
				insensitive_table.insert(hsi);
			}
		}

		infile.close();
	}

	// now allow the user to search for words in the file
	inquire(big_table, insensitive_table);


	return 0;
}


// Function traverse
// Inputs: 	pointer to a DirNode object, the root
//			string, the path
// Outputs: none
// Does: helper function to traverse the FSTree and print
void traverse(DirNode* root, string path, LinkedList<string>& paths)
{
	path = path + root->get_name() + "/";

	// basecase (empty)
	if (root->is_empty())
	{
		return;
	}
	// if there are files or directories, recurse through directories and print files
	else
	{
		// loops through each subdirectory, calls traverse, prints
		for (int i = 0; i < root->num_subdirs(); i++)
		{
			DirNode* child = root->get_subdir(i);
			traverse(child, path, paths);
		}
		// prints each file in the current directory
		for (int i = 0; i < root->num_files(); i++)
		{
			string file = root->get_file(i);
			paths.insert(path + file);
		}
	}
}


// Function modify_string
// Inputs: 	string, the string possibly containing nonalphanumerics
// Outputs: string, a clean string with no alphanumerics
// Does: removes nonalphanumeric characters from the inputted string
string modify_string(string s)
{
	string pure_string = "";

	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		// the ASCI value for ! is 33
		if (isalnum(s[i]) || s[i] == 33)
			pure_string += s[i];
	}

	return pure_string;
}
// Function inquire
// Inputs: reference to HashTable<HashString>, big_table
// Outputs: none
// Does: accepts the user's query, searches the hash table for the query
void inquire(Hash<HashString>& ht, Hash<HashString>& hti)
{
	// now retrieve
	string path;
	string line;
	string query;
	int line_num = 0;
	bool found = false;
	bool insensitive = false;

	while(true)
	{
		cout << endl << "Query? ";
		cin >> query;
		if (query == "@insensitive" || query == "@i")
		{
			cin >> query;
			for (int i = 0; i < query.length(); i++)
			{
				query[i] = tolower(query[i]);
			}
			insensitive = true;
		}
		
		else if (query == "@q" || query == "@quit")
		{
			cout << "Goodbye! Thank you and have a nice day.\n";
		}

		HashString query_hs;
		query_hs.set_word(query);

		if (insensitive)
		{
			hti.retrieve(query_hs, found);
		}
		else
		{
			ht.retrieve(query_hs, found);
		}

		if (!found)
		{
			cout << endl << query
			<< " Not Found. Try with @insensitive or @i.\n";
		}
		else
		{
			// now get all of the hashstring data ONLY FOR THE CORRECT WORD
			// (since certain HashStrings will contain multiple words 
			// with the same hash values)
			if (query_hs.get_word() == query)
			{
				path = query_hs.get_path();
				line = query_hs.get_line();
				line_num = query_hs.get_line_num();
				cout << endl << path << ":" << line_num << ": " << line;

				for (int i = 0; i < query_hs.list_length(); i++)
				{
					query_hs = query_hs.get_next();

					if (query_hs.get_word() == query)
					{
						path = query_hs.get_path();
						line = query_hs.get_line();
						line_num = query_hs.get_line_num();
						cout << endl << path << ":" 
						<< line_num << ": " << line;
					}
				}
			}
		}
	}
}

