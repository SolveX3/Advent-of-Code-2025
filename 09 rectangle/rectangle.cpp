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

int main(){
    ifstream tiles("tiledfloor.txt");
    vector<point> cornerList = {};
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

    //find all rectangles
    long answer = 0;
    for(int i = 0; i < cornerList.size() - 1; i++){
        for(int j = i + 1; j < cornerList.size(); j++){
            long xDist = abs(cornerList.at(j).x - cornerList.at(i).x) + 1;
            long yDist = abs(cornerList.at(j).y - cornerList.at(i).y) + 1;
            long area = xDist * yDist;
            cout << "rectangle from (" << cornerList.at(i).x << ", " << cornerList.at(i).y << ") to (" << cornerList.at(j).x << ", " << cornerList.at(j).y << ") has area " << area << endl;
            if(area > answer){
                answer = area;
            }
        }
    }
    cout << "largest rectangle: " << answer << endl;

    tiles.close();
    return 0;
}