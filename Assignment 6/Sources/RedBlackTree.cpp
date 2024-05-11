//************************************************************************
// ASU CSE310 Assignment #6 Spring 2022
// Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
	root = NULL;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
	/* Delete all of the nodes */
	int numOfNodes = deleteNode(root);
	cout << "The number of nodes deleted: " << numOfNodes << endl;
}

//**************************************************************
//Accessor for the root of the red-black tree
Node* RedBlackTree::getRoot()
{
	return root;
}

//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This should be defined as a recursive function
int RedBlackTree::deleteNode(Node *node)
{
	/* If the current node is null, return 0 sum */
	if (node == NULL)
	{
		return 0;
	}

	/* Get the sum and delete the node */
	else
	{
		int sumLeft  = deleteNode(node->leftChild);
		int sumRight = deleteNode(node->rightChild);

		delete node;

		return sumLeft + sumRight + 1;
	}
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
void RedBlackTree::insertNode(Node *node)
{
	Node* temp = root;   // Temporary node to find the parent node
	Node* parent = NULL; // Parent of the node to be inserted

	/* Find the parent of the node (y) */
	while (temp != NULL)
	{
		parent = temp;

		string tempKey = to_string(temp->id) + temp->firstName + temp->lastName;

		if (compareNodes(node, tempKey) < 0)
		{
			temp = temp->leftChild;
		}

		else temp = temp->rightChild;
	}

	node->parent = parent; // Set the node's parent

	/* Create the key value for the parent if it exists */
	string parentKey;
	if (parent != NULL) parentKey = to_string(parent->id) + parent->firstName + parent->lastName;

	/* If there's no parent, make the node the root */
	if (parent == NULL)
	{
		root = node;
	}

	/* Check if the root is the left child of the parent */
	else if (compareNodes(node, parentKey) < 0)
	{
		parent->leftChild = node;
	}

	/* Make the root the right child of the parent */
	else parent->rightChild = node;
}

//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.
void RedBlackTree::fixUp(Node *z)
{
	Node* uncle = NULL; // Z node's uncle

	/* Fix the tree if z isn't the node and it's parent is RED colored */
	while (z != NULL && z != root && z->parent->color.compare("RED") == 0)
	{
		/* Check if z's parent is the left child of z's grandparent */
		if (z->parent == z->parent->parent->leftChild)
		{
			uncle = z->parent->parent->rightChild;

			/*
			   Case 1:
			   Z's uncle is RED
			*/
			if (uncle != NULL && uncle->color.compare("RED") == 0)
			{
				/* Fix the issue */
				z->parent->color = "BLACK";
				uncle->color = "BLACK";
				z->parent->parent->color = "RED";

				z = z->parent->parent; // Move z up to keep fixing the rest of the tree
			}

			/* Only check and do case 2 followed by case 3 */
			else
			{
				/*
				   Case 2:
				   Z's uncle is BLACK
				   Z is the right child of it's parent
				*/
				if (z == z->parent->rightChild)
				{
					z = z->parent;
					leftRotate(z);
				}

				/*
				   Case 3:
				   Z's uncle is BLACK
				   Z is the left child of it's parent
				*/
				z->parent->color = "BLACK";
				z->parent->parent->color = "RED";
				rightRotate(z->parent->parent);
			}
		}

		else
		{
			uncle = z->parent->parent->leftChild;

			/*
			   Case 1:
			   Z's uncle is RED
			*/
			if (uncle != NULL && uncle->color.compare("RED") == 0)
			{
				/* Fix the issue */
				z->parent->color = "BLACK";
				uncle->color = "BLACK";
				z->parent->parent->color = "RED";

				z = z->parent->parent; // Move z up to keep fixing the rest of the tree
			}

			/* Only check and do case 2 followed by case 3 */
			else
			{
				/*
				   Case 2:
				   Z's uncle is BLACK
				   Z is the right child of it's parent
				*/
				if (z == z->parent->leftChild)
				{
					z = z->parent;
					rightRotate(z);
				}

				/*
				   Case 3:
				   Z's uncle is BLACK
				   Z is the left child of it's parent
				*/
				z->parent->color = "BLACK";
				z->parent->parent->color = "RED";
				leftRotate(z->parent->parent);
			}
		}
	}

	root->color = "BLACK"; // Always set the root node to BLACK
}

//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::preOrderTraversal(Node *node)
{
	/* Only do this if node isn't null */
	if (node != NULL)
	{
		print(node);
		preOrderTraversal(node->leftChild);
		preOrderTraversal(node->rightChild);
	}
	
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::inOrderTraversal(Node *node)
{
	/* Only do this if node isn't null */
	if (node != NULL)
	{
		inOrderTraversal(node->leftChild);
		print(node);
		inOrderTraversal(node->rightChild);
	}
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::postOrderTraversal(Node *node)
{
	/* Only do this if node isn't null */
	if (node != NULL)
	{
		postOrderTraversal(node->leftChild);
		postOrderTraversal(node->rightChild);
		print(node);
	}
}

//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function
Node* RedBlackTree::findMinimumNode(Node *node)
{
	/* If there is no subtree, there is no minimum */
	if (node == NULL)
    {
		cout << "Tree is empty, no MINIMUM." << endl;
		return node;
	}

    else
    {
		/* 
		   Keep finding the leftmost child of the 
		   subtree starting at node
		*/
		if (node->leftChild != NULL)
		{
			return findMinimumNode(node->leftChild);
		}

		return node; // Return the minimum node
	}
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function
Node* RedBlackTree::findMaximumNode(Node *node)
{
	/* If there is no subtree, there is no maximum */
	if (node == NULL)
    {
		cout << "Tree is empty, no MAXIMUM." << endl;
		return node;
	}

    else
    {
		/*
		   Keep finding the rightmost child of the
		   subtree starting at node
		*/
		if (node->rightChild != NULL)
		{
			return findMaximumNode(node->rightChild);
		}

		return node; // Return the maximum node
	}
}

//**************************************************************
//This function search the tree for a given key of a Student
//Note: key is the combination of id, firstName and lastName
//It returns a pointer points to the node if founded; otherwise it returns NULL
Node* RedBlackTree::treeSearch(int id, string firstName, string lastName)
{
	Node* tempNode = root; // Temporary node to iterate through the tree

	string k = to_string(id) + firstName + lastName; // Key of the node to search

	/* Iterate through the tree until the node is found (or not found) */
	while (tempNode != NULL && compareNodes(tempNode, k) != 0)
	{
		/* If the key is less than the current node, check the left child */
		if (compareNodes(tempNode, k) > 0)
		{
			tempNode = tempNode->leftChild;
		}

		else tempNode = tempNode->rightChild; // Check the right child
	}

	/* If the node is found, let the user know */
	if (tempNode != NULL)
	{
		cout << left;
		cout << setw(8) << id
			<< setw(12) << firstName
			<< setw(12) << lastName
			<< " is FOUND." << endl;
	}

	/* If the node wasn't found, let the user know */
	else
	{
		cout << left;
		cout << setw(8) << id
			<< setw(12) << firstName
			<< setw(12) << lastName
			<< " is NOT FOUND." << endl;
	}

	return tempNode;
}

//****************************************************
//This function left-rotate the BST rooted at 'node'
void RedBlackTree::leftRotate(Node *node)
{
	Node* right = node->rightChild; // Original right child of the node

	node->rightChild = right->leftChild;

	/* Check if the right child of the node has a left child */
	if (right->leftChild != NULL)
	{
		right->leftChild->parent = node;
	}

	right->parent = node->parent;

	/* Check if the parent of the node is the root */
	if (node->parent == NULL)
	{
		root = right;
	}

	/* Check if the node is the left child of its parent */
	else if (node == node->parent->leftChild)
	{
		node->parent->leftChild = right;
	}

	/* Node is right child of its parent */
	else node->parent->rightChild = right;

	right->leftChild = node;
	node->parent = right;
}

//***************************************************
//This function right-rotate the BST rooted at 'node'
void RedBlackTree::rightRotate(Node *node) 
{
	Node* left = node->leftChild; // Original left child of the node

	node->leftChild = left->rightChild;

	/* Check if the left child of the node has a right child */
	if (left->rightChild != NULL)
	{
		left->rightChild->parent = node;
	}

	left->parent = node->parent;
	
	/* Check if the parent of the node is the root */
	if (node->parent == NULL)
	{
		root = left;
	}

	/* Check if the node is the right child of its parent */
	else if (node == node->parent->rightChild)
	{
		node->parent->rightChild = left;
	}

	/* Node is right child of its parent */
	else node->parent->leftChild = left;

	left->rightChild = node;
	node->parent = left;
}

//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen and also
//return a pointer that points to the predecessor
Node* RedBlackTree::findPredecessorNode(Node *node)
{
	Node* predecessor = NULL; // Predecessor node

	/* If the node has a left child, the predecessor is the max node of the left subtree */
	if (node->leftChild != NULL)
	{
		predecessor = findMaximumNode(node->leftChild);
	}

	/* If the node doesn't have a left child, the predecessor is likely one of its parents */
	else
	{
		predecessor = node->parent;

		while (predecessor != NULL && node == predecessor->leftChild)
		{
			node = predecessor;
			predecessor = predecessor->parent;
		}
	}

	/* Let the user know that the predecessor was found */
	if (predecessor != NULL && predecessor != node)
	{
		cout << left;
		cout << "Its Predecessor is: " << endl;
		print(predecessor);
	}
    
	/* Let the user know that a predecessor wasn't found */
	else
	{
		cout << left;
		cout << "Its Predecessor does NOT EXIST" << endl;
	}

	return predecessor;
}

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen and also return
//a pointer that points to the successor node
Node* RedBlackTree::findSuccessorNode(Node *node)
{
	Node* successor = NULL; // Successor node

	/* If the node has a right child, the successor is the min node of the right subtree */
	if (node->rightChild != NULL)
	{
		successor = findMinimumNode(node->rightChild);
	}

	/* If the node doesn't have a right child, the sucessor is likely one of its parents */
	else
	{
		successor = node->parent;

		while (successor != NULL && node == successor->rightChild)
		{
			node = successor;
			successor = successor->parent;
		}
	}

	/* Let the user know that the successor was found */
	if (successor != NULL && successor != node)
	{
		cout << left;
		cout << "Its Successor is: " << endl;
		print(successor);
	}

	/* Let the user know that a successor wasn't found */
	else
	{
		cout << "Its Successor does NOT EXIST" << endl;
	}

	return successor;
}

//****************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print 'Tree is empty' message on screen.
void RedBlackTree::treeMinimum()
{
	/* If there's no root, there's no minimum */
	if (root == NULL)
	{
		cout << "Tree is empty. No Minimum." << endl;
	}

	/* Find the minimum */
	else
	{
		Node* minimum = findMinimumNode(root);
		cout << "The MINIMUM is:" << endl;
		print(minimum);
	}
}

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print 'Tree is empty' message on screen.
void RedBlackTree::treeMaximum()
{
	/* If there's no root, there's no maximum */
	if (root == NULL)
	{
		cout << "Tree is empty. No Maximum." << endl;
	}

	/* Find the maximum */
	else
	{
		Node* maximum = findMaximumNode(root);
		cout << "The MAXIMUM is:" << endl;
		print(maximum);
	}
}

//****************************************************************************
//This function print out the pre-order traversal of the entire red-black tree
void RedBlackTree::treePreorder()
{
	preOrderTraversal(root);
}

//***************************************************************************
//This function print out the in-order traversal of the entire red-black tree
void RedBlackTree::treeInorder()
{
	inOrderTraversal(root);
}

//*****************************************************************************
//This function print out the post-order traversal of the entire red-black tree
void RedBlackTree::treePostorder()
{
	postOrderTraversal(root);
}

//******************************************************************
//Given a Student key, this function first check whether the
//student is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message
void RedBlackTree::treePredecessor(int id, string firstName, string lastName)
{
	/* If there's no root, there's no predecessor */
	if (root == NULL)
	{
		cout << "Tree is empty. No Predecessor." << endl;
	}
	
	/* Find the predecessor of the node matching the user's description */
	else
    {
		Node* node = treeSearch(id, firstName, lastName); // Search for a matching node

		/* Find the predecessor of the node */
		if (node != NULL)
		{
			findPredecessorNode(node);
		}
	}
}

//******************************************************************
//Given a Student key, this function first check whether the
//student is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message
void RedBlackTree::treeSucessor(int id, string firstName, string lastName)
{
	/* If there's no root, there's no successor */
	if (root == NULL)
	{
		cout << "Tree is empty. No Successor." << endl;
	}

	/* Find the successor of the node matching the user's description */
	else
    {
		Node* node = treeSearch(id, firstName, lastName); // Search for a matching node

		/* Find the predecessor of the node */
		if (node != NULL)
		{
			findSuccessorNode(node);
		}
	}
}

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'
void RedBlackTree::treeInsert(int id, string firstName, string lastName, double gpa)
{
	/* Create a new node */
	Node* newNode = new Node();
	newNode->id = id;
	newNode->firstName = firstName;
	newNode->lastName = lastName;
	newNode->gpa = gpa;
	newNode->color = "RED";
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	/* Insert the new node */
	insertNode(newNode);
	fixUp(newNode);

}

//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
	cout << left;
	cout << setw(8)  << node->id
		 << setw(12) << node->firstName
		 << setw(12) << node->lastName
		 << setw(10) << fixed << setprecision(2) << node->gpa;
	cout << right << setw(7) << node->color << endl;
}

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of id + firstName + lastName
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number
int RedBlackTree::compareNodes(Node *node1, string key2)
{
	string nodeKey = to_string(node1->id) + node1->firstName + node1->lastName; // Create the key of node1

	return nodeKey.compare(key2); // Return the comparison of node1 and another key
}
