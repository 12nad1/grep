// FSTreeTraversal.cpp
// Maxwell Kaye
// Apr 16, 2018
// Implementation for FSTree Traversal

#include <iostream>
#include <fstream>
#include "FSTree.h"
#include "DirNode.h"
using namespace std;

void traverse(DirNode*, string);

int main(int argc, char *argv[])
{
	// make sure the provide exactly one command line argument
	if (argc != 2)
	{
		cout << "Please enter 1 command line argument\n";
		return 0;
	}
	string directory = argv[1];

	// stores the path from the root
	string path = "";

	// instantiate an FSTree object using paramaterized constructor
	FSTree tree(directory);

	// traverse tree and print with helper function
	traverse(tree.get_root(), path);

	return 0;
}


// Function Traverse
// Inputs: 	pointer to a DirNode object, the root
//			string, the path
// Outputs: none
// Does: helper function to traverse the FSTree and print
void traverse(DirNode* root, string path)
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
			traverse(child, path);
		}
		// prints each file in the current directory
		for (int i = 0; i < root->num_files(); i++)
		{
			string file = root->get_file(i);
			cout << path << file << endl;
		}
	}
}