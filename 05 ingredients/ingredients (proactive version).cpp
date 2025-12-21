#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct range{
    long lowerBound;
    long upperBound;
};

bool inRange(long number, range r){
    if(number >= r.lowerBound && number <= r.upperBound){
        return true;
    }
    return false;
}

int main(){
    ifstream inputData("ingredientranges.txt");

    //i don't feel like implementing linked lists again
    vector<range> ranges = {};
    long count = 0;
    string current = "";

    do{
        getline(inputData, current);
        if(current == ""){
            break;
        }
        //cout << current.length() << endl;
        int index = 0;
        string loadNumber = "";
        while(current[index] != '-'){
            loadNumber = loadNumber + current[index];
            index++;
        }
        index++;
        range currentRange;
        currentRange.lowerBound = stol(loadNumber);
        loadNumber = "";
        for(int i = index; i < current.length(); i++){
            loadNumber = loadNumber + current[i];
        }
        currentRange.upperBound = stol(loadNumber);
        cout << "adding range " << currentRange.lowerBound << "-" << currentRange.upperBound << endl;

        for(int i = 0; i < ranges.size(); i++){
            if(inRange(currentRange.lowerBound, ranges.at(i))){
                if(currentRange.upperBound > ranges.at(i).upperBound){
                    ranges.at(i).upperBound = currentRange.lowerBound - 1;
                }
                else{
                    currentRange.lowerBound = -1;
                    currentRange.upperBound = -2;
                    break;
                }
            }
            else if(inRange(currentRange.upperBound, ranges.at(i))){
                ranges.at(i).lowerBound = currentRange.upperBound + 1;
            }
            else if(inRange(ranges.at(i).lowerBound, currentRange) && inRange(ranges.at(i).upperBound, currentRange)){
                ranges.at(i).lowerBound = -1;
                ranges.at(i).upperBound = -2;
            }
        }
        ranges.push_back(currentRange);
        
    } while(current != "");

    cout << "sorting list..." << endl;
    for(int i = 0; i < ranges.size() - 1; i++){
        //sort the list
        for(int j = 0; j < ranges.size() - i - 1; j++){
            if(ranges.at(j).lowerBound > ranges.at(j+1).lowerBound){
                range temp = ranges.at(j+1);
                ranges.at(j+1) = ranges.at(j);
                ranges.at(j) = temp;
            }
        }
    }

    for(int i = 0; i < ranges.size(); i++){
        long magnitude = ranges.at(i).upperBound - ranges.at(i).lowerBound + 1;
        cout << "current range: " << ranges.at(i).lowerBound << "-" << ranges.at(i).upperBound << " (contains " << magnitude << " ids)" << endl;
        count += magnitude;
    }

    cout << "there are " << count << " total slots for fresh ingredients" << endl;

    inputData.close();
    return 0;
}