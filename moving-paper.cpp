#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

int main(){
    ifstream floorMap("floorplan.txt");
    int count = 0;

    LinkedList layout;
    string row;
    while(getline(floorMap, row)){
        layout.AddRow(row);
    }
    layout.PrintList();
    cout << endl;
    layout.ToTop();
    do{
        string currentRow = layout.GetCurrent();
        for(int i = 0; i < currentRow.length(); i++){
            if(currentRow[i] == '@'){
                int neighbors = 0;
                if(i > 0 && currentRow[i - 1] == '@'){
                    //west
                    neighbors++;
                }
                if(i < currentRow.length() - 1 && currentRow[i + 1] == '@'){
                    //east
                    neighbors++;
                }
                if(layout.GetPrev() == nullptr){
                    layout.ToTop();
                }
                else{
                    string previousRow = layout.GetCurrent();
                    if(previousRow[i] == '@'){
                        //north
                        neighbors++;
                    }
                    if(i > 0 && previousRow[i - 1] == '@'){
                        //northwest
                        neighbors++;
                    }
                    if(i < previousRow.length() - 1 && previousRow[i + 1] == '@'){
                        //northeast
                        neighbors++;
                    }
                    layout.GetNext(); //remind me to rewrite the linked list code from scratch next time
                }
                if(layout.GetNext() == nullptr){
                    layout.ToBottom();
                }
                else{
                    string nextRow = layout.GetCurrent();
                    if(nextRow[i] == '@'){
                        //south
                        neighbors++;
                    }
                    if(i > 0 && nextRow[i - 1] == '@'){
                        //southwest
                        neighbors++;
                    }
                    if(i < nextRow.length() - 1 && nextRow[i + 1] == '@'){
                        //southeast
                        neighbors++;
                    }
                    layout.GetPrev();
                }
                cout << neighbors;
                if(neighbors < 4){
                    count++;
                }
            }
            else{
                cout << " ";
            }
        }
        cout << endl;
    } while(layout.GetNext() != nullptr); //extremely rare sighting of a do while loop. take a photo

    cout << "movable rolls of paper: " << count << endl;

    layout.EmptyList();
    floorMap.close();
    return 0;
}