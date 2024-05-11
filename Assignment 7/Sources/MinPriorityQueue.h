//***************************************************************************************
// ASU CSE310 Spring 2022 Assignment #7
// Name of Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: City represent a vertex of the graph which is a departure City
//              Class MinPriorityQueue represents a Min-heap that contains City objects.
//              The key of each City is its d value. Note: for min-heap, the underline
//              data structure is a one dimensional array of City objects.
//***************************************************************************************

#include "ArrivalCityList.h"

#pragma once

using namespace std;

//City represent a vertex of the graph which is a departure City
struct City
{
	string cityName;
    double d;
    struct City* pi;
    ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains City objects.
//The key of each City is its d value. Note: for min-heap, the underline
//data structure is a one dimensional array of City objects.
class MinPriorityQueue
{
    private:
        struct City* cityArr;	//a City array
        int capacity, size;

	public:
        MinPriorityQueue(int capacity);
        ~MinPriorityQueue();

        City* getCityArr();
        int getSize();
        int getCapacity();
        int isFound(string cityName);
        bool decreaseKey(int index, City oneCitywithNewD);
        bool insert(City oneCity);
        void heapify(int index);
        City getHeapMin();
        void extractHeapMin();
        int leftChild(int parentIndex);
        int rightChild(int parentIndex);
        int parent(int childIndex);
        void printHeap();
};

/* Constructor to dynamically allocate memory for a heap with the specified capacity */
MinPriorityQueue::MinPriorityQueue(int capacity)
{
	cityArr = new City[capacity];
	this->capacity = capacity;
	this->size = 0;
}

/*
   Destructor
   Before termination, the destructor is called to free the associated memory occupied by the heap.
   and prints the number of nodes deleted by it.
*/
MinPriorityQueue::~MinPriorityQueue()
{
	delete[] cityArr;
}

/* This is the accessor for the instance variable cityArr. */
City* MinPriorityQueue::getCityArr()
{
	return cityArr;
}

/* This is the accessor for the instance variable size. */
int MinPriorityQueue::getSize()
{
	return size;
}

/* 	This is the accessor for the instance variable capacity. */
int MinPriorityQueue::getCapacity()
{
	return capacity;
}

/* 
   Given a cityName, this method returns the city object's index inside the cityArr if it finds a
   city with the specific name; otherwise it should return -1.
*/
int MinPriorityQueue::isFound(string cityName)
{
	/* Iterate through the array looking for a match */
	for (int i = 0; i < size; i++)
	{
		/* Match found, return the index */
		if (cityArr[i].cityName.compare(cityName) == 0)
		{
			return i;
		}
	}

	return -1; // Match not found, return -1
}

/*
   Given an index and a city object called oneCitywithNewD, this function decreases the distance of
   a city object at the specified index to the new distance as inside the oneCitywithNewD. The 
   function returns true if the operation is successful and false otherwise.
*/
bool MinPriorityQueue::decreaseKey(int index, City oneCitywithNewD)
{
	/* Check if the new distance is larger than the old one, if it isn't don't change it */
	if (cityArr[index].d < oneCitywithNewD.d)
	{
		return false;
	}

	cityArr[index].d = oneCitywithNewD.d; // Change the city distance to the new distance

	/* Bubble up the city based on if their new distance is smaller than their parent's distance */
	while (index > 0 && cityArr[parent(index)].d > cityArr[index].d)
	{
		/* Swap two students */
		City tempCity = cityArr[index];
		cityArr[index] = cityArr[parent(index)];
		cityArr[parent(index)] = tempCity;

		index = parent(index); // Check the new index
	}

	return true; // Operation successful
}

/*
   Given the information of a City object, namely its distance this function create a new City 
   object and inserts it inside the heap. If successful, it should update the size and return true;
   otherwise return false.
*/
bool MinPriorityQueue::insert(City oneCity)
{
	/* Check if heap has reached capacity */
	if (size + 1 > capacity)
	{
		/* Create a new heap that is double the capacity of the current heap */
		City* newCityArr = new City[2 * capacity];

		/* Copy the elements of the old heap to the new heap */
		for (int i = 0; i < size; i++)
		{
			newCityArr[i] = cityArr[i];
		}

		/* Delete the elements of the old heap and set it to the new heap */
		delete[] cityArr;
		cityArr = newCityArr;

		capacity = capacity * 2; // Double the capacity of the old heap
	}

	size++; // Increase the size by 1

	cityArr[size - 1] = oneCity; // Place the new element at the end of the heap

	/* Use decreaseKey to change the d of the last element to the new id */
	bool success = decreaseKey(size - 1, oneCity);

	return success; // Return true if the decreaseKey function was successful
}

/*
   As we learned in class, before we call this heapify( ) function, we assume that the binary tree
   rooted at left and right child of the node at index are already min heaps, but node at index might
   be bigger than its children, thus violating the min-heap property. heapify( ) lets the node at
   index "float down" in the min-heap so that the subtree rooted at index obeys the min-heap property.
*/
void MinPriorityQueue::heapify(int index)
{
	/* Indices used later */
	int smallest;
	int left = leftChild(index);
	int right = rightChild(index);

	/* If the left child distnce is smaller than the parent distnce, set it's index as the smallest index */
	if (left < size && cityArr[left].d < cityArr[index].d)
	{
		smallest = left;
	}

	/* If the parent index has a distance smaller than the left child, set that index to be the smallest one */
	else
	{
		smallest = index;
	}

	/* If the right child has a distane smaller than the prevously computed smallest index, set that to be the smallest */
	if (right < size && cityArr[right].d < cityArr[smallest].d)
	{
		smallest = right;
	}

	/* Recursive case for if the smallest index isn't the same as the parent index */
	if (smallest != index)
	{
		/* Swap index and largest child */
		City tempCity = cityArr[index];
		cityArr[index] = cityArr[smallest];
		cityArr[smallest] = tempCity;

		heapify(smallest);
	}
}

/*
   This is the accessor for the root of the heap, it returns the smallest city object (also root)
   of the min-heap. Note: this function only get the root information, it does NOT remove it.
*/
City MinPriorityQueue::getHeapMin()
{
	return cityArr[0];
}

/*
   This function extracts the root of the heap. Basically we replace the root by the last node of the
   heap, then call heapify( ) to "float-down" the newly added root, we then decrease the size of the
   heap by 1. 
*/
void MinPriorityQueue::extractHeapMin()
{
	/* Check if the heap is empty */
	if (size < 1)
	{
		return;
	}

	/* Swap the first and last element */
	City tempCity = cityArr[0];
	cityArr[0] = cityArr[size - 1];
	cityArr[size - 1] = tempCity;

	size--; // Decrease the size

	heapify(0); // Ensure that heap property is maintained
}

/* Given a parent node's index, this function returns its left child's index inside the 1D array. */
int MinPriorityQueue::leftChild(int parentIndex)
{
	return ((parentIndex + 1) * 2) - 1;
}

// Given a parent node's index, this function returns its right child's index inside the 1D array.
int MinPriorityQueue::rightChild(int parentIndex)
{
	return (parentIndex + 1) * 2;
}

/* Given a node's index, this function returns its parent node's index inside the 1D array. */
int MinPriorityQueue::parent(int childIndex)
{
	return (childIndex - 1) / 2;
}

/* Print all of the elements in the heap */
void MinPriorityQueue::printHeap()
{
	/* Check if the heap is empty */
	if (size < 1)
	{
		cout << "\nEmpty heap, no elements\n";
	}

	/* Print all of the elements in the heap */
	else
	{
		/* Print all elements in the heap */
		for (int i = 0; i < size; i++)
		{
			/* Print the name and distance */
			cout << left;
			cout << setw(15) << cityArr[i].cityName
				 << setw(12) << fixed << setprecision(2) << cityArr[i].d;

			/* Check if the element has a parent */
			if (cityArr[i].pi != NULL)
			{
				cout << setw(15) << cityArr[i].pi->cityName;
			}

			/* Let the user know tht the elment doesn't have  parent */
			else
			{
				cout << setw(15) << "No Parent";
			}
			
			cityArr[i].arrCityList->printArrCityList(); // Print the ArrivalCityList of each city

			cout << endl; // Newline
		}
	}
}