//********************************************************************
// ASU CSE310 Spring 2022 Assignment #7
// Name of Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: This assignment finds the shortest path from a graph of cities
//********************************************************************

#include "ArrivalCityList.h"
#include "MinPriorityQueue.h"
#include "Graph.h"

using namespace std;

void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance);

int main()
{
    int count;       //a variable for number of nodes
    string oneLine, sourceCityName;
    cin >> count;
    cin.ignore(20, '\n');       //will be used in Linux testing

    //For each line of the file, we will create a ArrivalCityList for a
    //specific departure city (which is a linked list). It represents all its
    //reachable arrival cities with distance info.
    //Here we use an array of City to store them
    City* cityArr = new City[count];

    //Initialize cityArr. Set each node's d value to be very large 30000
    //initialize each arrival city list
    for(int i = 0; i < count; i++)
    {
        /* Takes care of some of initialize_single_source */
        cityArr[i].d = 30000;
        cityArr[i].pi = NULL;
    }

    //get input line by line
    for(int i = 0; i< count; i++)
    {
        getline(cin, oneLine);

        /* Create variables to store the city name and arrival city list */
        string depCityName;
        ArrivalCityList* arrCityList = new ArrivalCityList();

        getCityInfo(oneLine, depCityName, arrCityList); // Extract the relevant info. from the input

        /* Store the info. into the city array */
        cityArr[i].cityName = depCityName;
        cityArr[i].arrCityList = arrCityList;
    }

    cout << "Enter source city name: " << endl;
    getline(cin, sourceCityName);

    //create a MinPriorityQueue which capacity is double the count
    MinPriorityQueue* cityHeap = new MinPriorityQueue(count*2);

    //insert each City objects one by one inside cityHeap
    for (int i = 0; i < count; i++)
    {
        cityHeap->insert(cityArr[i]);
    }

    //create a Graph object by using its constructor
    Graph* graph = new Graph(count, cityHeap);

    //print the graph adjacency list before running Dijkstra algorithm
    cout << "\nPrint the graph before Dijkstra algorithm" << endl;
    graph->printGraph();

   //Run Dijkstra algorithm on the graph
    graph->dijkstra(sourceCityName);

   //print the Dijkstra shortest path result
   cout << "\nPrint the Dijkstra algorithm running result" << endl;
   graph->printDijkstraPath(sourceCityName);
}

//**************************************************************
//This function from one line, gets all city info.
void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList)
{
    string delimiter = ","; // Separates commands, names, etc.

    /* Get depCityName from input */
    int pos = oneLine.find(delimiter);
    string token = oneLine.substr(0, pos);
    depCityName = token;
    oneLine.erase(0, pos + delimiter.length());

    /* Get arrCityList from the input */
    while (!oneLine.empty())
    {
        /* Find the next substring with new arrCityList node info. */
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);

        /* If there is info. extract what is needed */
        if (token.length() > 1)
        {
            /* Create variables to store the city name and the distance */
            string arrCityName;
            double distance;

            getArrCityInfo(token, arrCityName, distance); // Get the required name and distance from the inpust

            arrCityList->addArrCity(arrCityName, distance); // Store the info. into the ArrivalCityList
        }

        oneLine.erase(0, pos + delimiter.length()); // Erase the current substring from the input
    }
}

//****************************************************************************
//Given one arrival city info. format of, such as New York(611.20), this function
//extract arrival city name 'New York' and distance 611.20 out.
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance)
{
    /* Delimiters */
    string delimiter1 = "(";
    string delimiter2 = ")";

    /* Get city name from the input */
    int pos = oneArrCityInfo.find(delimiter1);
    string token = oneArrCityInfo.substr(0, pos);
    arrCityName = token;
    oneArrCityInfo.erase(0, pos + delimiter1.length());

    /* Get the distance from the input */
    pos = oneArrCityInfo.find(delimiter2);
    token = oneArrCityInfo.substr(0, pos);
    distance = stod(token);
    oneArrCityInfo.erase(0, pos + delimiter2.length());
}
