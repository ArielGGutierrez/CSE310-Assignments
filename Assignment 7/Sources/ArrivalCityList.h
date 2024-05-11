//********************************************************************
// ASU CSE310 Spring 2022 Assignment #7
// Name of Author: Ariel Gael Gutierrez
// ASU ID: 1218982505
// Description: Linked List that acts as adjacency nodes for a given
//              vertex
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

#pragma once

using namespace std;

//struct ArrCity represents an arrival city information with
//distance from a specific departure city
struct ArrCity
{
    string arrCityName;
    double distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
class ArrivalCityList
{
    private:
        struct ArrCity* head;

    public:
        ArrivalCityList();
        ~ArrivalCityList();
        ArrCity* getHead();
        ArrCity* findArrCity(string oneCity);
        bool addArrCity(string oneCity, double distance);
        void printArrCityList();
};

/* ArrivalCityList Constructor */
ArrivalCityList::ArrivalCityList()
{
    head = NULL;
}

/* ArrivalCityList Destructor */
ArrivalCityList::~ArrivalCityList()
{
    ArrCity* temp = head; // Temporary pointer to scroll through the list

    /* Delete every element in the list */
    while (head != NULL)
    {
        head = head->next;
        delete temp;
        temp = head;
    }
}

/* Accessor method for the head of the linked list */
ArrCity* ArrivalCityList::getHead()
{
    return head;
}

/* This method returns the node which matches a given name */
ArrCity* ArrivalCityList::findArrCity(string oneCity)
{
    ArrCity* temp = head; // Temporary pointer to scroll through the list

    /* Iterate through the list to find the matching node */
    while (temp != NULL)
    {
        /* Matching node found, return it */
        if (temp->arrCityName.compare(oneCity) == 0)
        {
            return temp;
        }

        temp = temp->next; // Iterate
    }

    return NULL; // Matching node not found, return null
}

/* Insertion method for the ArrivalCityList */
bool ArrivalCityList::addArrCity(string oneCity, double distance)
{
    ArrCity* befTemp = head; // Temporary pointer placed before temp
    ArrCity* temp = head;    // Temporary pointer to scroll through the lsit

    /* Create a new ArrCity node */
    ArrCity* newCity = new ArrCity();
    newCity->arrCityName = oneCity;
    newCity->distance = distance;
    newCity->next = NULL;

    /* Place the node at the beginning if there is no list */
    if (head == NULL)
    {
        head = newCity;
        return true;
    }

    /* Iterate through the list to find the right spot */
    while (temp != NULL)
    {
        /* Alphabetical spot found */
        if (oneCity.compare(temp->arrCityName) <= 0)
        {
            /* Handles when node needs to be placed at the beginning of the list */
            if (temp == head)
            {
                newCity->next = head;
                head = newCity;
            }
            
            /* Place the node between befTemp and temp */
            else
            {
                befTemp->next = newCity;
                newCity->next = temp;
            }

            return true; // Node is placed, no need to keep iterting
        }

        /* Keep iterating */
        befTemp = temp;
        temp = temp->next;
    }

    /* Handles when the node needs to be placed at the end of the list */
    befTemp->next = newCity;
    return true;
}

/* Printing method for ArrivalCityList */
void ArrivalCityList::printArrCityList()
{
    ArrCity* temp = head; // Temporary pointer to scroll through the list

    /* There is no list, let user know */
    if (head == NULL)
    {
        cout << "Arrival city list is empty";
        return;
    }

    /* Scroll through the list and print each node */
    while (temp != NULL)
    {
        cout << temp->arrCityName << "(" << temp->distance << ")" << ",";

        temp = temp->next;
    }
}