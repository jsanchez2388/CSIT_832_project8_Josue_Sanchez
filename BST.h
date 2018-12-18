#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

//Structure for BST Node using template
typedef int Object;

struct container
{
	Object value1;
	Object value2;
};

struct Node
{
	Object value = NULL;
	Node *left, *right;
};

//Binary Search Tree class declaration using template

class BST
{
private:
	Node* root;

	/******Private Member Functions******/
	void addNodePrivate(Object, Node*);
	void printInOrderPrivate(Node*) const;
	void findValue(Object, Node*, Object&, Object&, Object&);
	void deleteTree(Node*);
	void storeTreeValues(Node*, vector<Node*>&);
	Node* buildTree(vector<Node*>&, int, int);
public:
	BST();	//Constructor
	~BST();	//Destructor

	/******Public Member Functions******/
	void addNode(Object);
	void printInOrder() const;
	Node* createNode(Object);
	container closestValue(Object v);
	void balanceTree();
};

void BST::addNodePrivate(Object v, Node* r)
{
	if (root == nullptr)	//If tree is empty
	{
		root = createNode(v); //Create a new node and point root to it
	}
	else if (v < r->value)	//If tree not empty, and value passed is less than value of node
	{
		if (r->left != nullptr)	//If there is a left node 
		{
			addNodePrivate(v, r->left);	//Recursive call to function, passing same value and left pointer 
		}
		else
		{
			r->left = createNode(v);	//If there is not a left node, create one
		}
	}
	else if (v > r->value)	//If tree not empty, and value pass is greater than value of node
	{
		if (r->right != nullptr)	//If there is a right node
		{
			addNodePrivate(v, r->right);	//Recurvise vall to function, passing same value and right pointer
		}
		else
		{
			r->right = createNode(v);	//If there is not a right node, create one
		}
	}
	else	//If value passed is equal to value of node, cout that value already exists.
	{
		cout << v << " has already been added to the tree.\n";
	}
}


void BST::printInOrderPrivate(Node* r) const
{
	if (r != nullptr)	//If node not null
	{
		if (r->left != nullptr)	//If left node not null
		{
			printInOrderPrivate(r->left);	//Recursive call to print out left node
		}
		cout << r->value << " ";	//print out node value
		if (r->right != nullptr)	//If right node not null
		{
			printInOrderPrivate(r->right);	//Recursive call to print out left node
		}
	}
	else	//If node is null, tree is empty
	{
		cout << "Tree is empty.\n";
	}
}

inline
BST::BST()
{
	root = nullptr; //set root of tree to null
}

inline
BST::~BST()
{
	deleteTree(root);	//Call function to deallocate memory
}

inline
void BST::addNode(Object v)
{
	addNodePrivate(v, root);	//Call private function to add node
}

inline
void BST::printInOrder() const
{
	printInOrderPrivate(root); //Call private function to print note
}

inline
Node* BST::createNode(Object v)
{
	//Create new node, set value and return it
	Node* r = new Node;
	r->value = v;
	r->left = nullptr;
	r->right = nullptr;
	return r;
}

container BST::closestValue(Object v)
{
	Object minDiff = INT_MAX;	//Initialize value
	Object minVal1 = INT_MAX;	//Initialize value
	Object minVal2 = INT_MAX;	//Initialize value
	findValue(v, root, minDiff, minVal1, minVal2);	//Call funtion to find closest value
	container temp;
	temp.value1 = minVal1;
	temp.value2 = minVal2;
	return temp;	//Return value in tree closes to value entered
}

void BST::findValue(Object v, Node* r, Object &min, Object &minValue1, Object &minValue2)
{
	if (r == nullptr)
	{
		return;
	}
	if (r->value == v)	//If value equals node value
	{
		minValue1 = v;	//Set value and return
		return;
	}
	if (min == abs(r->value - v)) //If absolute value is equal to current min difference
	{
		minValue2 = r->value;	//Store value to second 
		return;
	}
	if (min > abs(r->value - v))	//If stored min difference is larger than new difference
	{
		min = abs(r->value - v);	//Store difference
		minValue1 = r->value;	//Store value
	}
	if (v < r->value)	//if stored min difference is less than new difference
	{
		findValue(v, r->left, min, minValue1, minValue2);	//Continue searching through left node
	}
	else	//If store min difference is greater than new difference
	{
		findValue(v, r->right, min, minValue1, minValue2);	//Continue searching through right node
	}
}

void BST::deleteTree(Node* r)
{
	if (r == nullptr)	//If tree is empty just return
	{
		return;
	}
	deleteTree(r->left);	//Recursive call to delete left node 
	deleteTree(r->right);	//Recursive call to delete right node
	delete r;	//Delete node
}

inline void BST::storeTreeValues(Node * r, vector<Node*> &n)
{
	if (r == nullptr)
		return;

	// Store tree nodes in vector
	storeTreeValues(r->left, n);
	n.push_back(r);
	storeTreeValues(r->right, n);
}

inline void BST::balanceTree()
{
	vector<Node*>nodes;	//temp vector to hold tree nodes
	storeTreeValues(root, nodes);	//Call funtion to store nodes
	root = buildTree(nodes, 0, (nodes.size() - 1));	//Call funtion to rebuild tree and store middle node to root
	//Deallocate memory
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes.pop_back();
	}
}

inline Node* BST::buildTree(vector<Node*>& n, int s, int e)
{
	if (s > e)
		return nullptr;

	//Get the middle element and make it root 
	int mid = (s + e) / 2;
	Node* r = n[mid];

	// Using index, construct left and right subtress 
	r->left = buildTree(n, s, mid - 1);
	r->right = buildTree(n, mid + 1, e);
	
	return r;
}
