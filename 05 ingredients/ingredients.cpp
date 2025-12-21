#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct range{
    long lowerBound;
    long upperBound;
};

int main(){
    ifstream inputData("ingredientranges.txt");

    //i don't feel like implementing linked lists again
    vector<range> ranges = {};
    int count = 0;
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
        cout << "loading range " << currentRange.lowerBound << "-" << currentRange.upperBound << endl;
        ranges.push_back(currentRange);
    } while(current != "");

    while(getline(inputData, current)){
        long number = stol(current);
        bool fresh = false;
        for(int i = 0; i < ranges.size(); i++){
            if(number >= ranges.at(i).lowerBound && number <= ranges.at(i).upperBound){
                cout << number << " is fresh" << endl;
                fresh = true;
                count++;
                break;
            }
        }
        if(fresh == false){
            cout << number << " is spoiled" << endl;
        }
    }

    cout << "there are " << count << " fresh ingredients in total" << endl;

    inputData.close();
    return 0;
}