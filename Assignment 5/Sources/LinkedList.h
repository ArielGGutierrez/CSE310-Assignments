// ASU CSE310 Assignment #5 (Spring 2022)
// Name of Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: A simple linked list that implements a list of Student objects. A user can
//              perform searching, insertion or deletion on the linked list.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Student
{
   string firstName, lastName;
   int id;
   double gpa;
   struct Student* next;
};

class LinkedList
{
	private:
   struct Student* head;
   int size;      //a variable represents number of Students inside the list
    public:
   LinkedList();
   ~LinkedList();
   Student* getHead();
   int getSize();
   bool searchStudent(int stuID);
   bool insertStudent(string firstName, string lastName, int id, double gpa);
   bool deleteStudent(int stuID);
   void displayList();
};

/* Constructor */
LinkedList::LinkedList()
{
    /* Create a new linkedlist */
    size = 0;
    head = NULL;
}

/* Destructor */
LinkedList::~LinkedList()
{
    Student* temp = head; // Temporary pointer

    /* Delete each element in the linked list */
    while (head != NULL)
    {
        head = head->next;
        delete temp;
        temp = head;
    }
}

/* Get head from linkedlist */
Student* LinkedList::getHead()
{
    return head;
}

/* Return number of Students inside the Linked list */
int LinkedList::getSize()
{
    return size;
}

/*
   This function does a linear search on the Student list with the given student ID
   it returns true if the corresponding student is found, otherwise it returns false.
*/
bool LinkedList::searchStudent(int stuID)
{
    Student* temp = head; // Temporary pointer

    /* Iterate through the list trying to find a matching student */
    while (temp != NULL)
    {
        /* A match was found */
        if (stuID == temp->id)
        {
            return true;
        }

        temp = temp->next;
    }

    return false; // A match wasn't found
}

/*
   Insert the parameter Student at the head of the linked list.
   return true if it is inserted successfully and false otherwise
*/
bool LinkedList::insertStudent(string firstName, string lastName, int id, double gpa)
{
    Student* student = new Student(); // New student

    /* Fill the new student with the appropriate attributes */
    student->firstName = firstName;
    student->lastName = lastName;
    student->id = id;
    student->gpa = gpa;

    /* Place new student at the beginning of the list */
    student->next = head;
    head = student;

    size++; // Increase the size counter of the linkedlist

    return true;
}

//Delete the Student with the given student ID from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteStudent(int stuID)
{
    Student* befTemp = head; // Temporary pointer
    Student* temp = head;    // Temporary pointer

    /* Iterate through the list to find and delete a matching student */
    while (temp != NULL)
    {
        /* If there is a match, delete the student */
        if (stuID == temp->id)
        {
            /* Case 1: Student is head */
            if (temp == head)
            {
                head = head->next;
            }

            /* Case 2: Anywhere else */
            else
            {
                befTemp->next = temp->next;
            }

            /* Delete student and decrease size counter */
            delete temp;
            size--;

            return true;
        }

        befTemp = temp;
        temp = temp->next;
    }

    return false; // Match wasn't found
}

/* This function displays the content of the linked list. */
void LinkedList::displayList()
{
   struct Student *temp = head; // Temporary pointer

   if (head == NULL) return; // Check if linkedlist is empty
   
   /* Print the linkedlist */
   while(temp != NULL)
   {
       cout << left    << setw(12) << temp->firstName
           << left    << setw(12) << temp->lastName
           << right   << setw(8)  << temp->id
           << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
       temp = temp->next;
   }
}