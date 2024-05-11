//********************************************************************************
// ASU Spring 2022 CSE310 HW#3
// Your Name: Ariel Gael Gutierrez
// ASU ID: 1218982505
// ASU Email address: agguti12@asu.edu
// Description: This class contains an array of student structure
//              which contains the student's first and last names,
//              as well as id and gpa.  The array is kept as a maxheap
//              by the MaxHeap structure.
//********************************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Each Student will have a unique id
struct Student
{
	int id;
	string firstName, lastName;
    double gpa;
};

//class MaxHeap represents a max heap that contains Student objects. The underline data structure
//is a one dimensional array of Student.
class MaxHeap
{
	private:
	struct Student* stuArr;	//an array of Student
	int capacity, size;

	public:
	MaxHeap(int capacity);
	~MaxHeap();

	Student* getStuArr();
	int getSize();
	int getCapacity();
	int isFound(int stuId);
	bool heapIncreaseID(int index, Student oneStudentwithNewID);
	bool heapInsert(int id, string firstName, string lastName, double gpa);
	void heapify(int index);
	Student getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
	stuArr = new Student[capacity];
	this->capacity = capacity;
	this->size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	int studentNum = size;
	delete[] stuArr;
	cout << "\nThe number of deleted Students is: " << studentNum;
}

// This is the accessor for the instance variable stuArr.
Student* MaxHeap:: getStuArr()
{
	return stuArr;
}

// This is the accessor for the instance variable size.
int MaxHeap::getSize()
{
	return size;
}

// 	This is the accessor for the instance variable capacity.
int MaxHeap::getCapacity()
{
	return capacity;
}

// Given a stuId, this method returns the Student object's index inside the stuArr if it find a
// Student with the specific stuId; otherwise it should return -1.
int MaxHeap::isFound(int stuId)
{
	for (int i = 0; i < size; i++)
	{
		if (stuArr[i].id == stuId)
		{
			return i;
		}
	}

	return -1;
}

// Given an index and a Student object called oneStudentwithNewID, this function increases the
// Student object at index's id to the new id as inside the oneStudentwithNewID. The function
// returns true if the operation is successful and false otherwise.
bool MaxHeap::heapIncreaseID(int index, Student oneStudentwithNewID)
{
	/* Check if the new id is smaller than the old one, if it isn't don't change it */
	if (stuArr[index].id > oneStudentwithNewID.id)
	{
		return false;
	}
	
	stuArr[index].id = oneStudentwithNewID.id; // Change the student id to the new id

	/* Bubble up the student based on if their new id is bigger than their parent's id */
	while (index > 0 && stuArr[parent(index)].id < stuArr[index].id)
	{
		/* Swap two students */
		Student tempStudent = stuArr[index];
		stuArr[index] = stuArr[parent(index)];
		stuArr[parent(index)] = tempStudent;

		index = parent(index); // Check the new index
	}

	return true;
}

// Given the information of a Student object, namely its id, firstName, lastName and gpa, this
// function create a new Student object and inserts it inside the heap. If successful, it should
// update the size and return true; otherwise return false.
bool MaxHeap::heapInsert(int id, string firstName, string lastName, double gpa)
{
	/* Check if heap has reached capacity */
	if (size + 1 > capacity)
	{
		/* Create a new heap that is double the capacity of the current heap */
		Student* newStuArr = new Student[2 * capacity];

		/* Copy the elements of the old heap to the new heap */
		for (int i = 0; i < size; i++)
		{
			newStuArr[i] = stuArr[i];
		}

		/* Delete the elements of the old heap and set it to the new heap */
		delete[] stuArr;
		stuArr = newStuArr;

		capacity = capacity * 2; // Double the capacity of the old heap
	}

	size++; // Increase the size by 1

	/* Set the properties of the last element in the list */
	stuArr[size - 1].id = -10000;
	stuArr[size - 1].firstName = firstName;
	stuArr[size - 1].lastName = lastName;
	stuArr[size - 1].gpa = gpa;

	/* Create a new temporary student with the id from the parameters */
	Student* newStudent = new Student();
	newStudent->id = id;

	/* Use heapIncreaseID to change the id of the last element to the new id */
	bool success = heapIncreaseID(size - 1, *newStudent);

	delete newStudent; // Delete the temporary student object

	return success; // Return true if the heapIncreaseID function was successful
}

// As we learned in class, before we call this heapify( ) function, we assume that the binary tree
// rooted at left and right child of the node at index are already max heaps, but node at index might
// be samller than its children, thus violating the max-heap property. heapify( ) lets the node at
// index "float down" in the max-heap so that the subtree rooted at index obeys the max-hea property.
void MaxHeap::heapify(int index)
{
	/* Indices used later */
	int largest;
	int left = leftChild(index);
	int right = rightChild(index);

	/* If the left child id is bigger than the parent id, set it's index as the largest index */
	if (left < size && stuArr[left].id > stuArr[index].id)
	{
		largest = left;
	}

	/* If the parent index has an id higher than the left child, set that index to be the largest one */
	else
	{
		largest = index;
	}

	/* If the right child has an id higher than the prevously computed largest index, set that to be the largest */
	if (right < size && stuArr[right].id > stuArr[largest].id)
	{
		largest = right;
	}

	/* Recursive case for if the largest index isn't the same as the parent index */
	if (largest != index)
	{
		/* Swap index and largest child */
		Student tempStudent = stuArr[index];
		stuArr[index] = stuArr[largest];
		stuArr[largest] = tempStudent;

		heapify(largest);
	}
}

// 	This is the accessor for the root of the heap, it returns the largest Student object (also root)
// of the max-heap. Note: this function only get the root information, it does NOT remove it.
Student MaxHeap::getHeapMax()
{
	return stuArr[0];
}

// This function extracts the root of the heap. Basically we replace the root by the last node of the
// heap, then call heapify( ) to "float-down" the newly added root, we then decrease the size of the
// heap by 1. 
void MaxHeap::extractHeapMax()
{
	/* Check if the heap is empty */
	if (size < 1)
	{
		return;
	}

	/* Swap the first and last element */
	Student tempStudent = stuArr[0];
	stuArr[0] = stuArr[size - 1];
	stuArr[size - 1] = tempStudent;

	size--; // Decrease the size

	heapify(0); // Ensure that heap property is maintained
}

// Given a parent node's index, this function returns its left child's index inside the 1D array.
int MaxHeap::leftChild(int parentIndex)
{
	return ((parentIndex + 1) * 2) - 1;
}

// Given a parent node's index, this function returns its right child's index inside the 1D array.
int MaxHeap::rightChild(int parentIndex)
{
	return (parentIndex + 1) * 2;
}

// Given a node's index, this function returns its parent node's index inside the 1D array.
int MaxHeap::parent(int childIndex)
{
	return (childIndex - 1) / 2;
}

// Print all of the elements in the heap
void MaxHeap::printHeap()
{
	/* Check if the heap is empty */
	if (size < 1)
	{
		cout << "\nEmpty heap, no elements\n";
	}
	
	/* Print all of the elements in the heap */
	else
	{
		/* Let the user know what the capacity and size of the heap are */
		cout << "\nHeap capacity = " << capacity << "\n";
		cout << "\nHeap size = " << size << "\n\n";

		/* Print all elements in the heap */
		for (int i = 0; i < size; i++)
		{
			cout << left;
			cout << setw(8) << stuArr[i].id
				<< setw(12) << stuArr[i].firstName
				<< setw(12) << stuArr[i].lastName
				<< setw(8) << fixed << setprecision(2) << stuArr[i].gpa << endl;
		}
	}
}