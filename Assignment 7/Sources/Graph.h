//********************************************************************
// ASU CSE310 Spring 2022 Assignment #7
// Name of Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: Graph represents the graph of connections between each city
//********************************************************************

#include "ArrivalCityList.h"
#include "MinPriorityQueue.h"

#pragma once

using namespace std;

class Graph
{
    private:
        int numOfNode;                 //number of nodes in the graph
        MinPriorityQueue* cityHeap;    //adjacency list. Which is a min-heap of departure City objects

    public:
        Graph(int numOfNode, MinPriorityQueue* cityHeap);
        ~Graph();

        void printGraph();
        void initialize_single_source(string sourceCityName);
        void relax(City* u, City* v);
        void dijkstra(string sourceCityName);
        void printDijkstraPath(string sourceCityName);
        void printPath(string sourceCityName, City* aCity);
};

/* Graph Constructor */
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
}

/* Graph Destructor */
Graph::~Graph()
{
   delete [] cityHeap;
   cityHeap = NULL;
   numOfNode = 0;
}

/* Method to print the contents of the minHep of the graph */
void Graph::printGraph()
{
    /* Print header representing what each column means */
    cout << left;
    cout << endl << "Heap size = " << cityHeap->getSize() << endl << endl;
    cout << setw(15) << "City Name"
         << setw(12) << "d Value"
         << setw(15) << "PI"
         << "Arrival City List" << endl;

    cityHeap->printHeap(); // Print the heap
}

/* Initializes the graph to prepare it for Dijkstra's algorithm */
void Graph::initialize_single_source(string sourceCityName)
{
    int sourceIndex = cityHeap->isFound(sourceCityName); // Find the spot of the source city in the heap

    /* Create a new city object with the appropriate distance */
    City* tempCity = new City();
    tempCity->d = 0;

    /* Decrease the distance of the city object in the heap so that it bubbles up */
    cityHeap->decreaseKey(sourceIndex, *tempCity);

    delete tempCity; // Memory cleanup
}

/* This method changes the distance and parent of v (adjacent to u) if the new path is shorter */
void Graph::relax(City* u, City* v)
{
    double distance = u->d + v->d; // Calculate the new distance

    /*
       Parameter v is a temporary city that holds the name of the city and the distance
       it is from u.  However, we need to change the distance and parent pointer for the
       matching city in the heap.  These lines find where this "vNode" is
    */
    int index = cityHeap->isFound(v->cityName);
    City* vNode = &cityHeap->getCityArr()[index];

    /* If the new distance is shorter than the previous distance */
    if (vNode->d > distance)
    {
        vNode->pi = u; // Set the new parent to be u

        /* Temporary city pointer containing the new distance */
        City* newDist = new City();
        newDist->d = distance;

        /* Decrease the distance of the city object in the heap so that it bubbles up */
        cityHeap->decreaseKey(index, *newDist);

        delete newDist; // Memory cleanup
    }
}

/* This method runs Dijkstra's shortest path algorithm on the cities starting from a source city */
void Graph::dijkstra(string sourceCityName)
{
    initialize_single_source(sourceCityName); // Initialization

    City* cityArray = cityHeap->getCityArr(); // Get the city array in the heap

    /* Perform this until the heap is empty */
    while (cityHeap->getSize() > 0)
    {
        /*
           Normally, extracted city objects need to be put in an external list,
           but due to the way that extractHeapMin() is implemented, these objects
           end up still in the array, but not in the heap.  Thus, they can be accessed
           wth the right index.
        */
        cityHeap->extractHeapMin();
        City* u = &cityArray[cityHeap->getSize()];

        ArrCity* temp = u->arrCityList->getHead(); // Get u's adjacency list

        /* Iterate through u's adjacency list */
        while (temp != NULL)
        {
            /* Elements in u's adjacency list to check MUST still be found in the heap */
            if (cityHeap->isFound(temp->arrCityName) > -1)
            {
                /* Create a temporary city pointer to house the distance from the adjacent node */
                City* v = new City();
                v->cityName = temp->arrCityName;
                v->d = temp->distance;
                v->pi = NULL;

                relax(u, v); // Perform the relax method

                delete v; // Memory cleanup
            }

            temp = temp->next; // Keep iterating through the adjacency list
        }
    }
}

/* This method prints out the results of running the Dijkstra algorithm */
void Graph::printDijkstraPath(string sourceCityName)
{
    City* cityArr = cityHeap->getCityArr(); // Get the city array with ll of the cities

    /* Print the headers the let the user know what each column stands for */
    cout << endl << "Source City: " << sourceCityName << endl
         << endl << "Arrival City  Shortest Dist. Shortest Path  " << endl;

    /* Print each element in the array */
    for (int i = numOfNode - 1; i >= 0; i--)
    {
        /* Print the name of the city and the distance it's shortest path is from the source city */
        cout << left;
        cout << setw(15) << cityArr[i].cityName
             << setw(15) << fixed << setprecision(2) << cityArr[i].d;

        printPath(sourceCityName, &cityArr[i]); // Print the shortest path for each city from the source city

        cout << endl; // Newline
    }
}

/* This recursive method prints out the path to get from a source city to a specified city */
void Graph::printPath(string sourceCityName, City* aCity)
{
    /* Base case: We've reached the source */
    if (aCity->cityName.compare(sourceCityName) == 0)
    {
        cout << sourceCityName;
    }

    /* Recursive case, we haven't reached the source */
    else
    {
        printPath(sourceCityName, aCity->pi); // Iterate backwards until the source is reached
        cout << "->" << aCity->cityName;      // Print the current city
    }
}