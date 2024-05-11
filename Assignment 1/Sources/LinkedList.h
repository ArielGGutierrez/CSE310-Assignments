// ASU CSE310 Spring 2022 Assignment #1
// Name: Ariel Gael Gutierrez
// ASU ID: 1218982505
// ASU Email Address: agguti12@asu.edu
// Description: This code creates a linked list of Student structures.

#include <iostream>
#include <iomanip>          //used to control the format of the output
#include <string>

using namespace std;

//Student represents a student information
struct Student
{
    string firstName, lastName;
    int id;
    double gpa;
    struct Student* next;
};

//class LinkedList will contains a linked list of Students. This is class definition
class LinkedList
{
    private:
        struct Student* head;

    public:
        LinkedList();
        ~LinkedList();
        bool findStudent(int studentId);
        bool addStudent(string firstName, string lastName, int studentId, double gpa);
        bool removeById(int studentId);
        bool removeByName(string firstName, string lastName);
        bool changeStudentName(int studentId, string newFullName);
        bool updateStudentGpa(int studentId, double newGpa);
        void printStudentListByLastName(string oneLastName);
        void printStudentList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = NULL; // Set the head to null
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    int StudentCount = 0;        // Counts the number of students deleted
    struct Student* temp = head; // Temporary pointer to iterate through the list

    /* Iterates through the list deleting stuff */
    while (temp != NULL)
    {
        /* More than one left on the list */
        if (temp->next != NULL)
        {
            head = temp->next;
            free(temp);
            temp = head;
        }

        /* Last one on the list */
        else
        {
            free(head);
            head = NULL;
            temp = NULL;
        }

        StudentCount++;
    }

    cout << "The number of deleted student is: " << StudentCount; // Let the user know how many students were removed
}

//A function to identify if the parameterized Student is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::findStudent(int studentId)
{
    struct Student* temp = head; // Temporary pointer to iterate through the list

    /* Iterate through the list */
    while (temp != NULL)
    {
        /* If the id in the list is the same as the one inputted, return true */
        if (temp->id == studentId)
        {
            return true;
        }
        
        temp = temp->next;  // Keep iterating through the list
    }
    return false;  // No id's matched, return false
}

//This function creates a new node and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Students by their names, i.e.
//first by last name, then by first name. Note: each Student has a unique id, but
//may have the same first and last name with another Student. In case two Students have same names
//they should be inserted according to the increasing order of their IDs.
//Return true if it is successfully inserted and false in case of failures.
bool LinkedList::addStudent(string firstName, string lastName, int studentId, double gpa)
{
    //----
    struct Student* node = new Student(); // New student node
    if (node == NULL) return false;       // Check if there is enough memory for the new ndoe

    /* Fill the new node with information */
    node->firstName = firstName;
    node->lastName = lastName;
    node->id = studentId;
    node->gpa = gpa;
    node->next = NULL;

    /* If the list is empty, add it to the beginning of the list */
    if (head == NULL)
    {
        head = node;
        return true;
    }

    struct Student* befTemp = head; // Temporary pointer pointing before temp pointer
    struct Student* temp    = head; // Temporary pointer to iterate through the list

    /* Iterate through the list */
    while (temp != NULL)
    {
        /* If any of the conditions match up, place the new node in between befTemp and temp */
        if ((lastName.compare(temp->lastName) < 0) ||
            (lastName.compare(temp->lastName) == 0 && firstName.compare(temp->firstName) < 0) ||
            (lastName.compare(temp->lastName) == 0 && firstName.compare(temp->firstName) == 0 && studentId < temp->id))
        {
            /* Handles when node needs to be placed at the beginning of the list */
            if (temp == head)
            {
                node->next = head;
                head = node;
            }

            /* Place the node in the right spot */
            else
            {
                node->next = temp;
                befTemp->next = node;
            }

            return true; // Node was placed, no need to keep going
        }

        /* Keep iterating */
        befTemp = temp;
        temp = temp->next;
    }

    /* Handles when the node needs to be placed at the end of the list */
    befTemp->next = node;
    return true;
}

//Removes the specified student from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeById(int studentId)
 {
    struct Student* befTemp = head; // Temporary pointer pointing before temp pointer
    struct Student* temp    = head; // Temporary pointer to iterate through the list

    /* Iterate through the list */
    while (temp != NULL)
    {
        /* If the ids match, remove the student */
        if (temp->id == studentId)
        {
            /* Handles if the student is at the beginning of the list */
            if (temp == head)
            {
                head = temp->next;
            }

            /* Remove the node from the list */
            else
            {
                befTemp->next = temp->next;
            }

            free(temp);  // Free the memory from the removed pointer
            return true; // No need to keep iterating
        }

        /* Keep iterating through the list */
        befTemp = temp;
        temp = temp->next;
    }

    return false; // No ids match
 }

//Removes the given Student from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Students with
//the same first and last name should be removed from the list.
bool LinkedList::removeByName(string firstName, string lastName)
{
    struct Student* befTemp = head; // Temporary pointer pointing before temp pointer
    struct Student* temp    = head; // Temporary pointer to iterate through the list

    bool removed = false; // Boolean that checks if at least 1 node has been removed

    /* Iterate through the list */
    while (temp != NULL)
    {
        /* If the first and last names match up, remove the node. */
        if (temp->firstName.compare(firstName) == 0 && temp->lastName.compare(lastName) == 0)
        {
            /* Handles when the node is in the beginning of the list */
            if (temp == head)
            {
                befTemp = head->next;
                head = head->next;

                free(temp);
                temp = befTemp;
            }

            /* Remove the node and free its memory */
            else
            {
                befTemp->next = temp->next;

                free(temp);
                temp = befTemp->next;
            }

            removed = true;  // If 1 node was deleted, set removed to true
        }

        /* Only continue iterating through the list if the current node wasn't removed */
        else
        {
            befTemp = temp;
            temp = temp->next;
        }
    }
    return removed; // Let the user know that at least one node was removed.
}

//Modifies the data of the given Student. Return true if it modifies successfully and
//false otherwise. Note: after changing a Student name, the linked list must still be
//in correct alphabetical order.
bool LinkedList::changeStudentName(int studentId, string newFullName)
{
    string firstName = newFullName.substr(0, newFullName.find(" "));                            // Get the first name of the full name
    string lastName  = newFullName.substr(newFullName.find(" ") + 1, newFullName.length() - 1); // Get the last name of full name
    double gpa;                                                                                 // Temporary variable to store the gpa 
    struct Student* temp = head;                                                                // Temporary pointer to iterate through the list

    /* Iterate through the list */
    while (temp != NULL)
    {
        /* If the list exists, change the name */
        if (temp->id == studentId)
        {
            /* Instead of spending time resorting the list, remove the student and add them again with the new name */
            gpa = temp->gpa;
            removeById(studentId);
            addStudent(firstName, lastName, studentId, gpa);
            return true;
        }
        
        temp = temp->next; // Keep iterating through the list
    }
    return false; // No ids matched
}

bool LinkedList::updateStudentGpa(int studentId, double newGpa)
{
    struct Student* temp = head; // Temporary pointer to iterate through the list

    /* Iterate through the list */
    while (temp != NULL)
    {
        /* If an id matches, change the gpa and return */
        if (temp->id == studentId)
        {
            temp->gpa = newGpa;
            return true;
        }
        
        temp = temp->next; // Keep iterating through the list
    }
    return false; // No ids match
}

//Prints all students in the list with the same last name.
void LinkedList::printStudentListByLastName(string oneLastName)
{
    /* If the list is empty, let the user know */
    if(head == NULL)
    {
		cout << "The list is empty\n";
		return;
	}

    struct Student* temp = head; // Temporary pointer to iterate through the list

    /* Iterate through the list */
    while (temp != NULL)
    {
        /* If the last names match, print out the information */
        if (temp->lastName.compare(oneLastName) == 0)
        {
            cout << left << setw(12) << temp->firstName
                 << left << setw(12) << temp->lastName
                 << right << setw(8) << temp->id
                 << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
        }

        temp = temp->next; // Keep iterating through the list
    }

}

//Prints all students in the linked list starting from the head node.
void LinkedList::printStudentList()
{
    /* If the list is empty, let the user know */
    if(head == NULL)
    {
		cout << "The list is empty\n";
		return;
	}

    struct Student* temp = head; // Temporary pointer to iterate through the list

    /* Iterate through the list, printing out each member */
    while (temp != NULL)
    {
        cout << left << setw(12) << temp->firstName
             << left << setw(12) << temp->lastName
             << right << setw(8) << temp->id
             << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
        
        temp = temp->next; // Keep iterating through the list
    }
}