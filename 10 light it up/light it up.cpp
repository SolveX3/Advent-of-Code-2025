#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct machine{
    vector<bool> lights;
    vector<vector<int>> buttons;
    vector<int> joltage;
}; //define a struct for the machines

int main(){
    //preparation
    ifstream input("brokenmachines.txt");
    vector<machine> machines = {};
    string current = "";

    //read in the file
    while(getline(input, current)){
        machine newMachine; //create a new machine
        int i = 1; //indexes the current string; start at 1 because 0 will always be '['
        while(current[i] != ']'){
            if(current[i] == '#'){
                newMachine.lights.push_back(true);
            }
            else if(current[i] == '.'){
                newMachine.lights.push_back(false);
            }
            i++; //go forward
        }
        i += 2; //go forward to to skip the bracket and the space
        while(current[i] != '{'){
            //should start this loop at '(' every time
            i++;
            vector<int> newButton = {}; //create a new button
            int value = 0; //reads in the current number
            while(current[i] != ')'){
                if(current[i] == ','){
                    //enter the current number
                    newButton.push_back(value);
                    value = 0;
                }
                else{
                    value *= 10;
                    value += static_cast<int>(current[i]) - 48; //yeah, yeah, i know it looks awkward
                }
                i++;
            }
            newButton.push_back(value);
            newMachine.buttons.push_back(newButton);
            i += 2;
        }
        //at this point, we will be at the joltage section, which can be processed similarly:
        i++;
        int newJoltage = 0;
        while(current[i] != '}'){
            if(current[i] == ','){
                //enter the current number
                newMachine.joltage.push_back(newJoltage);
                newJoltage = 0;
            }
            else{
                newJoltage *= 10;
                newJoltage += static_cast<int>(current[i]) - 48; //yeah, yeah, i know it looks awkward
            }
            i++;
        }
        newMachine.joltage.push_back(newJoltage);
        machines.push_back(newMachine);
    }

    int answer = 0;
    for(int i = 0; i < machines.size(); i++){
        //initialize the loop
        int max = 10000000; //just need some arbitrary large value; this is probably best for spotting errors
        vector<bool> lights = {}; //current state of lights
        for(int j = 0; j < machines.at(i).lights.size(); j++){
            lights.push_back(false); //all lights are off
        }
        for(int n = 0; n < pow(2, machines.at(i).buttons.size()); n++){
            for(int j = 0; j < lights.size(); j++){
                lights.at(j) = false; //reinitialize
            }
            int buttonCount = 0; //how many buttons are pressed
            //convert to binary
            //ints are naturally stored as raw binary, right?
            for(int j = 0; j < machines.at(i).buttons.size(); j++){
                if((n & static_cast<int>(pow(2, j))) != 0){
                    //that's how this works, right?
                    //maybe i'm weird and watch too much Retro Game Mechanics Explained
                    //if this works, this is gonna be the most cursed thing i've ever done with a computer
                    for(int k = 0; k < machines.at(i).buttons.at(j).size(); k++){
                        int wire = machines.at(i).buttons.at(j).at(k); //because it's a wire going from the button to the light i guess
                        lights.at(wire) = !lights.at(wire); //toggle
                    }
                    buttonCount++;
                }
            }
            if(machines.at(i).lights == lights && buttonCount < max){
                //cout << "new best solution found: " << n << endl;
                max = buttonCount;
            }
        }
        cout << "machine " << i + 1 << " activated in " << max << " button presses" << endl;
        answer += max;
    }

    cout << "total button presses: " << answer << endl;
    return 0;
}