#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

const int NUM_CONNECTIONS = 1000;
const int NUM_GRAPHS = 3;
//pretty much had to relearn how to use pointers for this

struct box{
    int id;
    int location[3];
    vector<box*> connections = {};
    bool visited = false;
};

struct connection{
    box* endpoints[2];
    long distance; //technically the square of the distance, but it'll be faster this way
};

struct comparator{
    bool operator()(connection a, connection b) const{
        if(a.distance < b.distance){
            return true;
        }
        else if(a.distance == b.distance){
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

void graphHelper(box* node, int* counter){
    if(node->visited == false){
        (*counter)++;
        node->visited = true;
        for(int j = 0; j < node->connections.size(); j++){
            graphHelper(node->connections.at(j), counter);
        }
    }
}

int main(){
    ifstream input("junctionboxes.txt");
    string current = "";
    vector<box*> boxes = {};
    set<connection, comparator> network = {};

    while(getline(input, current)){
        int i = 0;
        string number = "";
        box* newBox = new box;
        newBox->id = boxes.size();
        while(current[i] != ','){
            number = number + current[i];
            i++;
        }
        newBox->location[0] = stoi(number);
        i++;
        number = "";
        while(current[i] != ','){
            number = number + current[i];
            i++;
        }
        newBox->location[1] = stoi(number);
        i++;
        number = "";
        while(i < current.length()){
            number = number + current[i];
            i++;
        }
        newBox->location[2] = stoi(number);
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
        boxes.push_back(newBox);
    }

    int count = 0;
    for(connection edge : network){
        if(count < NUM_CONNECTIONS){
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
            count++;
        }
    }

    vector<int> graphs = {};

    for(int i = 0; i < boxes.size(); i++){
        int graphSize = 0;
        graphHelper(boxes.at(i), &graphSize);
        if(graphSize > 0){
            cout << "located graph of size " << graphSize << endl;
            graphs.push_back(graphSize);
        }
    }

    sort(graphs.rbegin(), graphs.rend());

    int answer = 1;
    cout << "largest connected graphs are of size";
    for(int i = 0; i < NUM_GRAPHS; i++){
        cout << " " << graphs.at(i);
        answer *= graphs.at(i);
    }
    cout << endl << "final answer: " << answer << endl;

    input.close();
    while(boxes.size() > 0){
        box* temp = boxes.back();
        boxes.pop_back();
        delete temp;
    }
    return 0;
}