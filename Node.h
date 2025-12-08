#ifndef NODE_H
#define NODE_H

//returning to my CS221 work for this one
//probably a good idea

#include <iostream>
#include <string>
using namespace std;

class Node{
    private:
        string row; //the contents of the row
        Node* prev; //the row above this one
        Node* next; //the row below this one
    public:
        Node(); //constructor
        Node(string); //useful constructor
        ~Node(); //destructor
        void SetNext(Node*); //set next node
        void SetPrev(Node*); //set previous node
        string GetRow(); //get row contents
        void SetRow(string); //set row contents
        Node* Prev(); //get previous node
        Node* Next(); //get next node
};

#endif