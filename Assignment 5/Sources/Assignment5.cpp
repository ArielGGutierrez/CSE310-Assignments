// ASU CSE310 Assignment #5 Spring 2022
// Name of Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Student
//   object's hash value.

//   My hash function combines the inputs into a string, turns the characters into
//   integers, sums those up and finally restricts the result into a value from 0
//   to the array size.

//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.

//   Test 1:
//     Performance Ratio:  1.67
//     Biggest LinkedList: 5
//   Test 2:
//     Performance Ratio:  2
//     Biggest LinkedList: 6
//   Test 3:
//     Performance Ratio:  1.75
//     Biggest LinkedList: 7
//   Test 4:
//     Performance Ratio:  2
//     Biggest LinkedList: 12

//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?

//   If I were to change the hash function, it'd be to use a more complicated way of
//   arriving to the keys in the hopes of arriving to a more distributed linked list

********************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include "Hash.h"

using namespace std;

//This function used to get a Student key which is the combination of firstName, lastName and id
void getKey(string oneLine, string& command, string& firstName, string& lastName, int& id);

int main()
{
    int size = 0 ;
    int numOfCommand = 0;
    string firstName, lastName;
    int id;
    double gpa;

    string oneLine;         // Line of user input
    string command;         // Command instruction
    string delimiter = ","; // Separates commands, names, etc.
    int numStudents = 0;    // Number of students in the hash table
 
    cout << "Enter the size of the hash table: ";   
    cin >> size;
    cin.ignore(20, '\n');

    //Instantiate the hash table with the relevant number of slots
    Hash* hashTable = new Hash(size);

    /* 
       Use this do..while loop to repeatedly get one line Student info. and extract tokens
       create one Student object and insert it inside the hashTable until seeing the message
       "InsertionEnd" to terminate
    */
    do
    {
        getline(cin, oneLine); // Get input from user

        if (oneLine.compare("InsertionEnd") == 0) break; // Stop getting input from user if InsertionEnd is inputted
        
        else
        {
            /* Get first name from input */
            int pos = oneLine.find(delimiter);
            string token = oneLine.substr(0, pos);
            firstName = token;
            oneLine.erase(0, pos + delimiter.length());

            /* Get last name from input */
            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            lastName = token;
            oneLine.erase(0, pos + delimiter.length());

            /* Get id from input */
            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            id = stoi(token);
            oneLine.erase(0, pos + delimiter.length());

            /* Get gpa from input */
            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            gpa = stoi(token);
            oneLine.erase(0, pos + delimiter.length());

            hashTable->hashInsert(firstName, lastName, id, gpa); // Insert student into hash table

            numStudents++; // add to student count
        }

    } while(true);

	//cout << "\nEnter number of commands: ";
    cin >> numOfCommand;
    cin.ignore(20, '\n');

    /* Execute the commands inputted */
    for(int i= 0; i < numOfCommand; i++)
    {
        getline(cin, oneLine); // Get command from user

        /* Get command from input */
        int pos = oneLine.find(delimiter);
        string firstToken = oneLine.substr(0, pos);

        /* If user inputted this command, display the hash table */
        if (firstToken.compare("hashDisplay") == 0) hashTable->hashDisplay();

        /* If the user inputted this command, calculate the load factor */
        else if (firstToken.compare("hashLoadFactor") == 0)
        {
            /* calculate ideal/actual load factors and performance comparison */
            float idealFactor = numStudents / size;
            float actualFactor = hashTable->hashLoadFactor();
            float performance = (float)(actualFactor) / idealFactor;

            /* Display calculated values to user */
            cout << "\nThe ideal load factor is: " << fixed << setprecision(2) << idealFactor;
            cout << "\nMy hash table real load factor is: " << fixed << setprecision(2) << actualFactor;
            cout << "\nMy hash table performance ratio is: " << fixed << setprecision(2) << performance << endl;
        }
        
        /* Other commands */
        else
        {
            getKey(oneLine, command, firstName, lastName, id); // Get command, first/last name, and id from input
            
            /* Execute requested commands */
            if      (command.compare("hashSearch") == 0)     hashTable->hashSearch(firstName, lastName, id);
            else if (command.compare("hashDelete") == 0)     hashTable->hashDelete(firstName, lastName, id);
            
            /* Command is invalid */
            else                                             cout<<"Invalid command"<<endl;
        }
    } //end for loop
    return 0;
}

//****************************************************************************************
//Given one line, this function extracts the firstName, lastName, id info. of a Student
//This function is completed and given here as a study guide for extracting tokens
void getKey(string oneLine, string& command, string& firstName, string& lastName, int& id)
{
   string delimiter = ","; // Separates commands, names, etc.

   /* Get command from input */
   int pos = oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   command = token;
   oneLine.erase(0, pos+delimiter.length());

   /* Get first name from input */
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   firstName = token;
   oneLine.erase(0, pos+delimiter.length());

   /* Get last name from input */
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   lastName = token;
   oneLine.erase(0, pos+delimiter.length());

   /* Get id from input */
   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   id = stoi(token);
   oneLine.erase(0, pos+delimiter.length());
}