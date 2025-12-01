#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream combination("fakepassword.txt");
    string rotation;
    int dial = 50;
    int count = 0;
    while(getline(combination, rotation)){
        char direction = rotation[0];
        string distanceStr = "";
        for(int i = 1; i < rotation.length(); i++){
            distanceStr = distanceStr + rotation[i];
        }
        int distance = stoi(distanceStr);
        if(direction == 'L'){
            cout << "rotate left " << distance << " notches; new position ";
            dial -= distance;
        }
        else if(direction == 'R'){
            cout << "rotate right " << distance << " notches; new position ";
            dial += distance;
        }
        dial = dial % 100;
        if(dial < 0){
            //why is this a thing, C++
            dial += 100;
            //i know it doesn't matter, but the output is more elegant this way
        }
        cout << dial << endl;
        if(dial == 0){
            count++;
        }
    }
    cout << "true password: " << count << endl;
    return 0;
}
