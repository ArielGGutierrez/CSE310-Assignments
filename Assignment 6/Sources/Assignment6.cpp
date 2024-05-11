//************************************************************************
// ASU CSE310 Assignment #6 Spring 2022
// Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: This is the main program that reads input from keyboard,
//              it then execute various red-black tree operations which
//              is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get the key of a Student
void getStudentKey(string oneLine, int& id, string& firstName, string& lastName);

//This function used to get all info. of a Student
void getStudentInfo(string oneLine, int& id, string& firstName, string& lastName, double& gpa);

int main()
{
   int id;
   string firstName, lastName;
   double gpa;
   string command, oneLine, token;
   string delimiter = ",";

   int pos = 0;

   //Create a RedBlackTree object
   //----
   RedBlackTree* tree = new RedBlackTree();

   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());

      if(command.compare("quit")==0)
      {
          cout << "\nCommand: quit" << endl;
          delete tree;
          break;
      }

      else if(command.compare("tree_preorder")==0)
      {
          cout << "\nCommand: tree_preorder" << endl;
          tree->treePreorder();
      }

      else if(command.compare("tree_inorder")==0)
      {
          cout << "\nCommand: tree_inorder" << endl;
          tree->treeInorder();
      }

      else if(command.compare("tree_postorder")==0)
      {
          cout << "\nCommand: tree_postorder" << endl;
          tree->treePostorder();
      }

      else if(command.compare("tree_minimum")==0)
      {
          cout << "\nCommand: tree_minimum" << endl;
          tree->treeMinimum();
      }

      else if(command.compare("tree_maximum")==0)
      {
          cout << "\nCommand: tree_maximum" << endl;
          tree->treeMaximum();
      }

      else if(command.compare("tree_predecessor")==0)
      {
          getStudentKey(oneLine, id, firstName, lastName);
          cout << "\nCommand: tree_predecessor" << endl;
          tree->treePredecessor(id, firstName, lastName);
      }

      else if(command.compare("tree_successor")==0)
      {
          getStudentKey(oneLine, id, firstName, lastName);
          cout << "\nCommand: tree_successor" << endl;
          tree->treeSucessor(id, firstName, lastName);
      }

      else if(command.compare("tree_search")==0)
      {
          getStudentKey(oneLine, id, firstName, lastName);
          cout << "\nCommand: tree_search" << endl;
          tree->treeSearch(id, firstName, lastName);
      }

      else if(command.compare("tree_insert")==0)
      {
          getStudentInfo(oneLine, id, firstName, lastName, gpa);

          cout << "\nCommand: tree_insert" << endl;
          cout << left;
          cout << setw(8)  << id
               << setw(12) << firstName
               << setw(12) << lastName
               << setw(10) << fixed << setprecision(2) << gpa;

          tree->treeInsert(id, firstName, lastName, gpa);
          cout << endl;
      }
   } while(true);  //continue until 'quit'
   return 0;
}

//********************************************************************
//This function from one line, extracts the id, firstName and lastName
//information of a Student
void getStudentKey(string oneLine, int& id, string& firstName, string& lastName)
{
    string delimiter = ","; // Separates commands, names, etc.

    /* Get id from input */
    int pos = oneLine.find(delimiter);
    string token = oneLine.substr(0, pos);
    id = stoi(token);
    oneLine.erase(0, pos + delimiter.length());

    /* Get first name from input */
    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    firstName = token;
    oneLine.erase(0, pos + delimiter.length());

    /* Get last name from input */
    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    lastName = token;
    oneLine.erase(0, pos + delimiter.length());
}

//**************************************************************
//This function from one line, get all Student info.
void getStudentInfo(string oneLine, int& id, string& firstName, string& lastName, double& gpa)
{
    string delimiter = ","; // Separates commands, names, etc.
                            
    /* Get id from input */
    int pos = oneLine.find(delimiter);
    string token = oneLine.substr(0, pos);
    id = stoi(token);
    oneLine.erase(0, pos + delimiter.length());

    /* Get first name from input */
    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    firstName = token;
    oneLine.erase(0, pos + delimiter.length());

    /* Get last name from input */
    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    lastName = token;
    oneLine.erase(0, pos + delimiter.length());

    /* Get GPA from input */
    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    gpa = stod(token);
    oneLine.erase(0, pos + delimiter.length());

}
