//********************************************************************************
// ASU Spring 2022 CSE310 HW#3
// Name: Ariel Gael Gutierrez
// ASU ID: 1218982505
// ASU Email Address: agguti12@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

#include <iostream>
#include <string>
#include "MaxHeap.h"

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
    string firstName, lastName;
	int id, newID;
	int capacity, index = -1;   //1D array capacity and index
	double gpa;
	bool success = false;

    Student* oneStudent;

	//a variable used to represent a MaxHeap object
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the initial capacity
			{
				cout << "\nPlease enter the heap capacity: ";

				cin >> capacity;
				heap1 = new MaxHeap(capacity);

				cin.ignore(20, '\n');	//flush the buffer for above capacity entered

				break;
			}

			//delete the heap, call the destructor explicitly. Re-initialize heap1
			//with default capacity 5
			case 'D':
			{
				/* Delete the heap */
				cout << "\nDelete the heap" << endl;
				delete heap1;

				/* Create new heap with default capacity 5 */
				heap1 = new MaxHeap(5);
				cout << endl;

				break;
			}

			case 'E':	//Extract the root, remove it from the heap
			{
				/* Check if heap is null or empty */
				if (heap1 == nullptr || heap1->getSize() < 1)
				{
					cout << "\nEmpty heap, can NOT extract max\n";
				}

				/* Extract the root */
				else
				{
					cout << "\nBefore extract heap max operation:\n";
					heap1->printHeap();

					heap1->extractHeapMax();

					cout << "\nAfter extract heap max operation:\n";
					heap1->printHeap();
				}

				break;
			}

			case 'F':	//Find a Student
			{
				cout << "\nEnter the student ID you want to search: ";
				cin >> id;
				cin.ignore(20, '\n');	//flush the buffer

				index = heap1->isFound(id); // Index of id if it is already in the heap

				/* id exists, let the user know */
				if (index > -1)
				{
					cout << "\nStudent with id: " << id << " is found\n";
				}

				/* id doesn't exist, let the user know */
				else
				{
					cout << "\nStudent with id: " << id << " is NOT found\n";
				}

				break;
			}

			case 'I':	//Insert a Student
			{
				cout << "\nEnter the student first name: ";
				cin >> firstName;

				cout << "\nEnter the student last name: ";
				cin >> lastName;

				cout << "\nEnter the student id: ";
				cin >> id;
				cout << "\nEnter the student gpa: ";
				cin >> gpa;
				cin.ignore(20, '\n');	//flush the buffer


				if (heap1 == nullptr) break; // Check if the list isn't initialized

				/* Check if a duplicate exists */
				if (heap1->isFound(id) != -1)
				{
					cout << "\nDuplicated Student. Not added\n";
					cout << "\nStudent \"" << firstName << " " << lastName << "\" is NOT added\n";
					break;
				}

				/* 
				   Check if the heap is at max capacity and let the user know that the capacity will be doubled
				   and that the student was added.
				*/
				if (heap1->getSize() == heap1->getCapacity())
				{
					cout << "\nReach the capacity limit, double the capacity now.\n";
					
					heap1->heapInsert(id, firstName, lastName, gpa);
					
					cout << "\nThe new capacity now is " << heap1->getCapacity() << "\n";
					cout << "\nStudent \"" << firstName << " " << lastName << "\" is added\n";
				}

				/* Add the student and let the user know it was added */
				else
				{
					heap1->heapInsert(id, firstName, lastName, gpa);

					cout << "\nStudent \"" << firstName << " " << lastName << "\" is added\n";
				}
				break;
			}

			case 'K':	//increase the ID
			{
				cout << "\nEnter the old student id you want to increase: ";
				cin >> id;
				cout << "\nEnter the new id: ";
				cin >> newID;
				cin.ignore(20, '\n');	//flush the buffer

				/* Check if the new id is smaller than the old one, don't let the user enter id if it is */
				if (newID < id)
				{
					cout << "\nIncrease ID error: new id is smaller than current id\n";
					break;
				}

				index = heap1->isFound(newID); // Index of newID if it is found in the heap

				/* If the id is already in the heap, don't add it */
				if (index >= 0)
				{
					cout << "\nThe new ID you entered already exist, increase ID operation failed\n";
					break;
				}

				index = heap1->isFound(id); // Index of old id if it is in the heap

				/* If the old id isn't in the list, don't add the new id */
				if (index < 0)
				{
					cout << "\nThe old ID you try to increase does not exist\n";
					break;
				}

				/* Temporary student object to house the new id */
				oneStudent = new Student();
				oneStudent->id = newID;

				/* Display to user how heap looks like before replacing the id */
				cout << "\nBefore increase ID operation:\n";
				heap1->printHeap();

				/* Replace the id of the student at the index */
				cout << "\nStudent with old id: " << id << " is increased to new id: " << newID << "\n";
				heap1->heapIncreaseID(index, *oneStudent);

				/* Display to the user how heap looks like after replacing the id */
				cout << "\nAfter increase id operation: \n";
				heap1->printHeap();

				delete oneStudent; // Delete the temporary object

				break;
			}

			case 'M':	//get the maximum node info.
			{
				/* Check of the heap is null or empty */
				if (heap1 == nullptr || heap1->getSize() < 1)
				{
					cout << "Empty heap, can NOT get max node\n";
					break;
				}

				/* Temporary student object to hold student information */
				oneStudent = new Student();
				*oneStudent = heap1->getHeapMax();

				/* Display to the user the maximum heap node */
				cout << "\nThe maximum heap node is:\n";
				cout << left;
				cout << setw(8) << oneStudent->id
					<< setw(12) << oneStudent->firstName
					<< setw(12) << oneStudent->lastName
					<< setw(8) << fixed << setprecision(2) << oneStudent->gpa << endl;

				delete oneStudent; // Delete temporary student object

				break;
			}

			case 'P':	//Print heap contents
			{
				/* Check if heap is null or empty */
				if (heap1 == nullptr || heap1->getSize() < 1)
				{
					cout << "\nEmpty heap, no elements\n";
					break;
				}

				heap1->printHeap(); // Display the heap to the user

				break;
			}

			case 'S':	//HeapSort
			{
				cout << "\nHeap sort. Students will be sorted in increasing order of their IDs" << endl;

				heapSort(heap1); // Perform heapsort

				break;
			}

			case 'Q':	//Quit
			{
				delete heap1;
				break;
			}

			case '?':	//Display Menu
			{
				printMenu();
				break;
			}

			default:
			{
				cout << "Unknown action\n";
				break;
			}
		}
	} while (input1 != 'Q');
	return 0;
}

//************************************************************
//The function displays the menu
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a student by ID\n";
	cout << "I\t\tInsert a student\n";
	cout << "K\t\tIncrease the ID\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}

//***************************************************************************
//Given a max heap, this function sorts all elements in increasing order of
//their IDs. Note: we explicitly separate the HeapSort algorithm with
//its underline MaxHeap data structure. You can put the sorted elements inside
//another array, then print them out.
void heapSort(MaxHeap* oneMaxHeap)
{
	int size = oneMaxHeap->getSize(); // Get the size of the heap before it is destroyed

	/* Keep extracting the maximum node until the heap is empty */
	for (int i = 0; i < size; i++)
	{
		oneMaxHeap->extractHeapMax();
	}

	Student* stuArr = oneMaxHeap->getStuArr(); // Get the student array from the heap

	/* 
	   Even though the heap is empty, the array still has all the students inside it.
	   The students objects are sorted, so iterate through the array and display the
	   objects.
	*/
	for (int index = 0; index < size; index++)
	{
		//print out format is given as below
		cout << left << setw(8) << stuArr[index].id
			<< setw(12) << stuArr[index].firstName
			<< setw(12) << stuArr[index].lastName
			<< setw(8) << fixed << setprecision(2) << stuArr[index].gpa << endl;
	}
}