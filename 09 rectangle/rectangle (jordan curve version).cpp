#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//so apparently you can't have a vector of arrays
struct point{
    int x;
    int y;
};

struct edge{
    point a;
    point b;
};

int main(){
    ifstream tiles("tiledfloor.txt");
    vector<point> cornerList = {};
    vector<edge> edgeList = {};
    string current = "";

    //read in the file
    while(getline(tiles, current)){
        string number = "";
        int i = 0;
        point newTile;
        //read in each number on the line
        while(current[i] != ','){
            number = number + current[i];
            i++;
        }
        newTile.x = stoi(number);
        number = "";
        i++;
        while(i < current.length()){
            number = number + current[i];
            i++;
        }
        newTile.y = stoi(number);
        cornerList.push_back(newTile);
    }

    //list all the edges
    for(int i = 0; i < cornerList.size(); i++){
        edge newEdge;
        newEdge.a = cornerList.at(i);
        if(i == cornerList.size() - 1){
            newEdge.b = cornerList.at(0);
        }
        else{
            newEdge.b = cornerList.at(i + 1);
        }
        edgeList.push_back(newEdge);
    }

    //find all rectangles
    long answer = 0;
    for(int i = 0; i < cornerList.size() - 1; i++){
        for(int j = i + 1; j < cornerList.size(); j++){
            bool valid = true;
            for(int k = 0; k < cornerList.size(); k++){
                if(cornerList.at(k).x > cornerList.at(i).x && cornerList.at(k).x < cornerList.at(j).x){
                    if(cornerList.at(k).y > cornerList.at(i).y && cornerList.at(k).y < cornerList.at(j).y){
                        valid = false;
                        break;
                    }
                    if(cornerList.at(k).y > cornerList.at(j).y && cornerList.at(k).y < cornerList.at(i).y){
                        valid = false;
                        break;
                    }
                }
                if(cornerList.at(k).x > cornerList.at(j).x && cornerList.at(k).x < cornerList.at(i).x){
                    if(cornerList.at(k).y > cornerList.at(i).y && cornerList.at(k).y < cornerList.at(j).y){
                        valid = false;
                        break;
                    }
                    if(cornerList.at(k).y > cornerList.at(j).y && cornerList.at(k).y < cornerList.at(i).y){
                        valid = false;
                        break;
                    }
                }
            }
            for(int k = 0; k < edgeList.size(); k++){
                if(!valid){
                    break; //it's not impossible that this is the messiest code i've ever written
                }
                //yippee! more casework!
                edge currentEdge = edgeList.at(k);
                int coords[4] = {currentEdge.a.x, currentEdge.a.y, currentEdge.b.x, currentEdge.b.y};
                //making things less unwieldy
                //should've done this sooner, but for a minor project like this? probably too late by now
                if(coords[1] == coords[3] && coords[1] > min(cornerList.at(i).y, cornerList.at(j).y) && coords[1] < max(cornerList.at(i).y, cornerList.at(j).y)){
                    //horizontal edge
                    if(min(coords[0], coords[2]) <= min(cornerList.at(i).x, cornerList.at(j).x) && max(coords[0], coords[2]) >= max(cornerList.at(i).x, cornerList.at(j).x)){
                        valid = false;
                        break;
                    }
                }
                if(coords[0] == coords[2] && coords[0] > min(cornerList.at(i).x, cornerList.at(j).x) && coords[0] < max(cornerList.at(i).x, cornerList.at(j).x)){
                    //vertical edge
                    if(min(coords[1], coords[3]) <= min(cornerList.at(i).y, cornerList.at(j).y) && max(coords[1], coords[3]) >= max(cornerList.at(i).y, cornerList.at(j).y)){
                        valid = false;
                        break;
                    }
                }
            }
            if(valid){
                long xDist = abs(cornerList.at(j).x - cornerList.at(i).x) + 1;
                long yDist = abs(cornerList.at(j).y - cornerList.at(i).y) + 1;
                long area = xDist * yDist;
                cout << "rectangle from (" << cornerList.at(i).x << ", " << cornerList.at(i).y << ") to (" << cornerList.at(j).x << ", " << cornerList.at(j).y << ") has area " << area << endl;
                if(area > answer){
                    answer = area;
                }
            }
        }
    }
    cout << "largest rectangle: " << answer << endl;

    tiles.close();
    return 0;
}