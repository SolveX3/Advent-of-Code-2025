#ifndef NODE_CPP
#define NODE_CPP

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//construct an empty node
Node::Node(){
    row = "";
    prev = nullptr;
    next = nullptr;
}
//construct a node describing the given row
Node::Node(string data){
    row = data;
    prev = nullptr;
    next = nullptr;
}
//delete the node
Node::~Node(){
    //if there were any pointers here, this is where we'd deallocate them
}
//set the previous node
void Node::SetPrev(Node* newRow){
    prev = newRow;
}
//set the next node
void Node::SetNext(Node* newRow){
    next = newRow;
}
//set the row contents
void Node::SetRow(string contents){
    row = contents;
}
//get the previous node
Node* Node::Prev(){
    return prev;
}
//get the next node
Node* Node::Next(){
    return next;
}
//get the row contents
string Node::GetRow(){
    return row;
}

#endif