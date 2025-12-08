#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

class LinkedList{
    private:
        Node* head; //first item in the list
        Node* tail; //last item in the list
        Node* curPos; //selected item
        int length; //number of rows
    public:
        LinkedList(); //constructor
        ~LinkedList(); //destructor
        void AddRow(string); //add a new row at the end
        string GetCurrent(); //get the current row
        void ToTop(); //return to top
        void ToBottom(); //go to bottom, in case that's necessary
        void EmptyList(); //delete all rows
        void PrintList(); //print out list
        Node* GetNext(); //select & return next row
        Node* GetPrev(); //select & return previous row
        Node* GetCurrentNode(); //select & return current row
        int GetLength(); //get length. don't think i need this, but
};

#endif