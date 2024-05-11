//************************************************************************
// ASU CSE310 Assignment #6 Spring 2022
// Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: Red black tree header file. It defines the Node and the
//              red black tree functionalities.
//************************************************************************
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

//Node represents one node of the RBT which is a Student
struct Node
{
   int id;
   string firstName, lastName;
   double gpa;
   Node *parent;
   Node *leftChild;
   Node *rightChild;
   string color;
};

class RedBlackTree
{
    private:
        Node *root;
    public:
        RedBlackTree();
        ~RedBlackTree();
        Node* getRoot();
        int deleteNode(Node *node);
        void insertNode(Node *node);
        void fixUp(Node *node);

        void preOrderTraversal(Node *node);
        void inOrderTraversal(Node *node);
        void postOrderTraversal(Node *node);

        Node* findMinimumNode(Node *node);
        Node* findMaximumNode(Node *node);
        Node* treeSearch(int id, string firstName, string lastName);
        void leftRotate(Node *node);
        void rightRotate(Node *node);
        Node* findPredecessorNode(Node *node);
        Node* findSuccessorNode(Node *node);

        void treeMinimum();
        void treeMaximum();
        void treePreorder();
        void treeInorder();
        void treePostorder();
        void treePredecessor(int id, string firstName, string lastName);
        void treeSucessor(int id, string firstName, string lastName);
        void treeInsert(int id, string firstName, string lastName, double gpa);

        void print(Node *node);
        int compareNodes(Node *node, string key);
};
#endif
