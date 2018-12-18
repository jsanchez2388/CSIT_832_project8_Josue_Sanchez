//Josue Sanchez
//CSIT-832
//Assignment 8
//Description: This program is an example of a binary sear tree. The tree is populated by random integers.
//If a generated value is already found inside of the tree, the program will notify the user and ignore the value.
//The values in the tree are then printed out in increasing order. The user is then asked to enter a value to
//search for in the tree. The closest value is then displayed. If there are two integers that are closest to the 
//value entered, both will be displayed. 

#include <iostream>
#include "BST.h"
#include <ctime>
#include <cstdlib>

using namespace std;

/*****Function Prototypes*****/
int createRandInt();

int main()
{
	//Arrays to store values to be added to tree
	int treeValues[10];
	srand(time(0));

	//Add random values to array
	for (int i = 0; i < 10; i++)
	{
		treeValues[i] = createRandInt();
	}

	//Create tree
	BST intTree;

	//Create container for values
	container closest;

	//Variables needed for algorithm
	int intInput;

	//Try to output empty tree
	cout << "Binary Search Tree Example:\n\n";
	cout << "Printing tree before adding values.\n";
	cout << "IntTree:\n";
	intTree.printInOrder();

	//Add values to trees
	cout << "\nAdding values to tree.\n\n";
	for (int i = 0; i < 10; i++)
	{
		intTree.addNode(treeValues[i]);
	}
	
	//Balance the tree
	intTree.balanceTree();

	//Print tree
	cout << "Printing tree in by increasing value after adding values.\n";
	cout << "Int Tree:\n";
	intTree.printInOrder();
	cout << endl;

	
	//Ask user to input int
	cout << "\n\nEnter an integer value to search for: ";
	cin >> intInput;
	while (cin.fail())	//Validate Data
	{
		cin.clear(); //Clear input
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore bad input
		cout << "Invalid Entry.\nEnter an integer value to search for: ";
		cin >> intInput;
	}
	cout << "Finding closest values:\nSearch IntTree for " << intInput << endl;
	//Search for closest value and store result
	closest = intTree.closestValue(intInput);

	//Output result
	if (closest.value1 != INT_MAX && closest.value2 != INT_MAX)
	{
		cout << "The closest values are " << closest.value1 << " and "<< closest.value2 << endl;
	}
	else if (closest.value1 != INT_MAX)
	{
		cout << "The closest value is " << closest.value1 << endl;
	}
	else
	{
		cout << "Tree is empty.\n";
	}

	return 0;
}

//Generate random int and return it
int createRandInt()
{
	int random = rand() % 100 + 1;	//Generate number between 1 and 100
	return random;
}
