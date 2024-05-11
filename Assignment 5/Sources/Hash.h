// ASU CSE310 Assignment #5 (Spring 2022)
// Name of Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay

#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

class Hash
{
   private:
      LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
      int m;                     //slots number of the hash table
	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string firstName, string lastName, int id);
      bool hashInsert(string firstName, string lastName, int id, double gpa);
      bool hashDelete(string firstName, string lastName, int id);
      int hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
  };

/* Constructor */
Hash::Hash(int size)
{
    /* Create new hash table from requested size */
    hashTable = new LinkedList[size];
    m = size;
}

/* Destructor */
Hash::~Hash()
{
    delete[] hashTable;
}

/*
   This function searches for a key inside the hash table and
   return true if it is found and false otherwise
   Note: key is the combination of firstName, lastName and id
*/
bool Hash::hashSearch(string firstName, string lastName, int id)
{
   bool found = false;

   /* Turn id into a string */
   string strId = to_string(id);

   string key = lastName + firstName + strId; // Combine last/first names and id into string

   int index = hashFunction(key); // Find the index that the student should be in

   found = hashTable[index].searchStudent(id); // Look for the student in the linkelist

   /* Tell the user that the student was found */
   if (found == true)
   {
       cout << "\n" << left
           << setw(12) << firstName
           << setw(12) << lastName
           << setw(8) << id
           << " is found inside the hash table." << endl;
       return true;
   }

   /* Tell the user that the student wasn't found */
   else
   {
       cout << "\n" << left
           << setw(12) << firstName
           << setw(12) << lastName
           << setw(8) << id
           << " is NOT found inside the hash table." << endl;
       return false;
   }
}

/*
   hashInsert inserts a Student with the relevant info. into the hashTable.
   it returns true if the data is inserted successfully and false otherwise
*/
bool Hash::hashInsert(string firstName, string lastName, int id, double gpa)
{
    /* Turn id into a string */
    string strId = to_string(id);

    string key = lastName + firstName + strId; // Combine last/first names and id into string

    int index = hashFunction(key); // Find the index that the student should be in

    bool success = hashTable[index].insertStudent(firstName, lastName, id, gpa); // Insert the student

    return success; // Tell the user if the operation was successful
}

/*
   hashDelete deletes a Student with the relevant key from the hashTable.
   it returns true if it is deleted successfully and false otherwise
   Note: key is the combination of firstName, lastName and id
*/
bool Hash::hashDelete(string firstName, string lastName, int id)
{
    /* Turn id into a string */
    string strId = to_string(id);

    string key = lastName + firstName + strId; // Combine last/first names and id into string

    int index = hashFunction(key); // Find the index that the student should be in

    /* Delete the object, and let the user know that the operation was successful */
    if (hashTable[index].deleteStudent(id))
    {
        cout << "\n";
        cout << setw(12) << firstName
            << setw(12) << lastName
            << setw(8) << id
            << " is deleted from hash table." << endl;
        return true;
    }

    /* Let the user know that the operation wasn't successful */
    else
    {
        cout << "\n";
        cout << setw(12) << firstName
            << setw(12) << lastName
            << setw(8) << id
            << " is NOT deleted from hash table." << endl;
        return false;
    }

}

/*
   This function computes your hash table real load factor
   it is the longest linked list size
*/
int Hash::hashLoadFactor()
{
    int largest = 0; // Largest linked list size

    /* Find the largest linkedlist in all of the elements */
    for (int i = 0; i < m; i++)
    {
        if (hashTable[i].getSize() > largest)
        {
            largest = hashTable[i].getSize();
        }
    }

    return largest; // Return the value
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
    /* Display the hash table to the user */
    for (int i = 0; i < m; i++)
    {
        /* Let the user know that the current linkedlist is empty */
        if (hashTable[i].getSize() < 1)
        {
            cout << "\nHashTable[" << i << "] is empty, size = 0\n";
        }

        /* Print the current linkedlist */
        else
        {
            cout << "\nHashTable[" << i << "], size = " << hashTable[i].getSize() << endl;
            hashTable[i].displayList();
        }
    }
}

/*
   This is the hash function you need to design. Given a
   string key, the function should return the slot number
   where we will hash the key to
*/
int Hash::hashFunction(string key)
{
    int sum = 0;              // Sum of all the characters in the key
    int keySize = key.size(); // Size of the key string

    /* Compute the sum */
    for (int i = 0; i < keySize; i++)
    {
        sum += (int)(key.at(i));
    }

    int index = sum % m; // Limit the sum to a value between 0 and m

    return index; // Return the index
}