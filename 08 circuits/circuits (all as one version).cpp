#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

//pretty much had to relearn how to use pointers for this

//gonna comment this one better

//stores data about the circuit boxes
struct box{
    int id; //assigns a unique id to each box
    int circuit; //assigns a unique id to each contiguous graph of boxes; this variable is designed to change as the program runs
    int location[3]; //the coordinates of the box in 3-space
    vector<box*> connections = {}; //every box this box is connected to; useful for going through contiguous graphs
    bool visited = false; //helper variable for iterating through graphs
};

//stores data about possible connections between boxes
struct connection{
    box* endpoints[2]; //the two endpoints of the connection
    long distance; //technically the square of the distance, but it's slightly faster this way probably
};

//custom comparator for comparing distances, i guess
struct comparator{
    bool operator()(connection a, connection b) const{
        if(a.distance < b.distance){
            return true; //is either distance strictly less than the other?
        }
        else if(a.distance == b.distance){
            //if not, it may not be the worst idea in the world to define an inequality between different distances of the same length; don't know what'll happen otherwise
            if(a.endpoints[0]->id < b.endpoints[0]->id){
                return true;
            }
            else if(a.endpoints[0]->id == b.endpoints[0]->id){
                if(a.endpoints[1]->id < b.endpoints[1]->id){
                    return true;
                }
            }
        }
        return false;
    };
};

//helper function for iterating through graphs
void graphHelper(box* node, int id, bool reset){
    if(node->visited == reset){
        node->visited = !reset;
        node->circuit = id;
        for(int j = 0; j < node->connections.size(); j++){
            graphHelper(node->connections.at(j), id, reset);
        }
    }
}

int main(){
    ifstream input("junctionboxes.txt"); //input file
    string current = ""; //current line of input
    vector<box*> boxes = {}; //list of all boxes
    set<connection, comparator> network = {}; //list of all connections, automatically ordered by length (this ordering is incredibly useful)
    int numGraphs = 0; //how many graphs there are; we need to know when this number drops down to 1

    //read in the file
    while(getline(input, current)){
        int i = 0; //iterator variable; yes, a for loop would look more elegant, but this was easier to code
        string number = ""; //holds the current number as a string
        box* newBox = new box; //create a new box and keep it in memory
        newBox->id = boxes.size(); //give the box a unique id
        newBox->circuit = newBox->id; //none of the boxes are connected at first, so this will be fine
        numGraphs++;
        //read in the first number in the line
        while(current[i] != ','){
            number = number + current[i];
            i++;
        }
        newBox->location[0] = stoi(number);
        i++;
        //reset and read in the second number
        number = "";
        while(current[i] != ','){
            number = number + current[i];
            i++;
        }
        newBox->location[1] = stoi(number);
        i++;
        //you get the idea
        number = "";
        while(i < current.length()){
            number = number + current[i];
            i++;
        }
        newBox->location[2] = stoi(number);
        //check the distance to each other existing box
        for(int j = 0; j < boxes.size(); j++){
            connection newEdge;
            newEdge.endpoints[1] = newBox;
            newEdge.endpoints[0] = boxes.at(j);
            newEdge.distance = 0;
            long pDistance;
            for(int d = 0; d < 3; d++){
                pDistance = newEdge.endpoints[1]->location[d] - newEdge.endpoints[0]->location[d];
                newEdge.distance += pow(pDistance, 2);
            }
            network.insert(newEdge);
        }
        //add the box to the list so we can keep track of it
        boxes.push_back(newBox);
    }

    for(connection edge : network){
        //iterate through all possible connections until all boxes form one contiguous network
        if(numGraphs > 1){
            if(edge.endpoints[0]->circuit != edge.endpoints[1]->circuit){
                graphHelper(edge.endpoints[1], edge.endpoints[0]->circuit, false); //set the second graph
                graphHelper(edge.endpoints[1], edge.endpoints[1]->circuit, true); //reset the second graph
                numGraphs--;
            }
            //connect the two boxes
            edge.endpoints[0]->connections.push_back(edge.endpoints[1]);
            edge.endpoints[1]->connections.push_back(edge.endpoints[0]);
            cout << "connected ( ";
            for(int d = 0; d < 3; d++){
                cout << edge.endpoints[0]->location[d] << " ";
            }
            cout << ") with ( ";
            for(int d = 0; d < 3; d++){
                cout << edge.endpoints[1]->location[d] << " ";
            }
            cout << "); distance^2 = " << edge.distance << endl;
            if(numGraphs == 1){
                cout << "final answer: " << edge.endpoints[0]->location[0] * edge.endpoints[1]->location[0] << endl;
                break;
            }
        }
    }

    //cleanup
    input.close(); //close the input file
    while(boxes.size() > 0){
        //delete all our dynamically allocated data
        box* temp = boxes.back();
        boxes.pop_back();
        delete temp;
    }
    return 0;
}