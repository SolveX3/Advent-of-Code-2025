#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList(){
    head = nullptr;
    tail = nullptr;
    curPos = nullptr;
    length = 0;
}
LinkedList::~LinkedList(){
    EmptyList();
}
void LinkedList::AddRow(string contents){
    ToBottom();
    Node* newRow = new Node(contents);
    if(tail == nullptr){
        head = newRow;
    }
    else{
        newRow->SetPrev(tail);
        tail->SetNext(newRow);
    }
    tail = newRow;
    length++;
}
string LinkedList::GetCurrent(){
    return curPos->GetRow();
}
void LinkedList::ToTop(){
    curPos = head;
}
void LinkedList::ToBottom(){
    curPos = tail;
}
void LinkedList::EmptyList(){
    ToTop();
    while(curPos != nullptr){
        Node* temp = curPos->Next();
        delete curPos;
        curPos = temp;
    }
    length = 0;
    head = nullptr;
    tail = nullptr;
    ToTop();
}
void LinkedList::PrintList(){
    ToTop();
    while(curPos != nullptr){
        cout << curPos->GetRow() << endl;
        GetNext();
    }
    ToTop();
}
Node* LinkedList::GetNext(){
    curPos = curPos->Next();
    return curPos;
}
Node* LinkedList::GetPrev(){
    curPos = curPos->Prev();
    return curPos;
}
Node* LinkedList::GetCurrentNode(){
    //i give up
    return curPos;
}
int LinkedList::GetLength(){
    return length;
}

#endif
