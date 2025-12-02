#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

//for this problem, i've noted that none of the IDs are longer than 10 digits, and that no range of IDs contains IDs of more than two different lengths

string substring(string input, int start, int end){
    //returns a substring. start and end are 0-indexed. saw this function on the w3schools docs, but it doesn't seem to work
    string output = "";
    for(int i = start; i <= end; i++){
        output = output + input[i];
    }
    return output;
}

long searchHelper(long lowerBound, long upperBound){
    //assumes lowerBound and upperBound have the same number of digits
    long counter = 0;
    int length = to_string(lowerBound).length();
    if(length % 2 == 0){
        string repeater = substring(to_string(lowerBound), 0, length / 2 - 1);
        string maxRepeater = substring(to_string(upperBound), 0, length / 2 - 1);
        while(stol(repeater) <= stol(maxRepeater)){
            long target = stol(repeater + repeater);
            if(target >= lowerBound && target <= upperBound){
                cout << target << endl;
                counter += target;
            }
            repeater = to_string(stol(repeater) + 1);
        }
    }
    if(length % 3 == 0){
        string repeater = substring(to_string(lowerBound), 0, length / 3 - 1);
        string maxRepeater = substring(to_string(upperBound), 0, length / 3 - 1);
        while(stol(repeater) <= stol(maxRepeater)){
            long target = stol(repeater + repeater + repeater);
            if(target >= lowerBound && target <= upperBound){
                cout << target << endl;
                counter += target;
            }
            repeater = to_string(stol(repeater) + 1);
        }
    }
    if(length % 5 == 0){
        string repeater = substring(to_string(lowerBound), 0, length / 5 - 1);
        string maxRepeater = substring(to_string(upperBound), 0, length / 5 - 1);
        while(stol(repeater) <= stol(maxRepeater)){
            long target = stol(repeater + repeater + repeater + repeater + repeater);
            if(target >= lowerBound && target <= upperBound){
                cout << target << endl;
                counter += target;
            }
            repeater = to_string(stol(repeater) + 1);
        }
    }
    if(length == 7){
        string repeater = substring(to_string(lowerBound), 0, 0); //since it's gonna be length 1 anyway
        string maxRepeater = substring(to_string(upperBound), 0, 0);
        while(stol(repeater) <= stol(maxRepeater)){
            long target = 0;
            for(int i = 0; i < 7; i++){
                target *= 10;
                target += stol(repeater);
            }
            if(target >= lowerBound && target <= upperBound){
                cout << target << endl;
                counter += target;
            }
            repeater = to_string(stol(repeater) + 1);
        }
    }
    if(length == 6 || length == 10){
        string repeater = substring(to_string(lowerBound), 0, 0); //since it's gonna be length 1 anyway
        string maxRepeater = substring(to_string(upperBound), 0, 0);
        while(stol(repeater) <= stol(maxRepeater)){
            long target = 0;
            for(int i = 0; i < length; i++){
                target *= 10;
                target += stol(repeater);
            }
            if(target >= lowerBound && target <= upperBound){
                cout << "overcounted " << target << endl;
                counter -= target;
            }
            repeater = to_string(stol(repeater) + 1);
        }
    }

    return counter;
}

int main(){
    ifstream products("productrange.txt");
    string input;
    getline(products, input); //the file is only one line long

    int i = 0;
    long total = 0;
    while (i < input.length()){
        string lowerBoundStr = "";
        string upperBoundStr = "";
        bool halfway = false;
        while(i < input.length() && input[i] != ','){
            if(input[i] == '-'){
                halfway = true;
            }
            else if(halfway){
                upperBoundStr = upperBoundStr + input[i];
            }
            else{
                lowerBoundStr = lowerBoundStr + input[i];
            }
            i++;
        }
        cout << "checking range [" << lowerBoundStr << ", " << upperBoundStr << "]" << endl;
        bool doublePass = (lowerBoundStr.length() != upperBoundStr.length());
        long lowerBound = stol(lowerBoundStr); //ran my code the first time and got told the very first input was "out of range" for stoi()
        long upperBound = stol(upperBoundStr);
        if(doublePass){
            total += searchHelper(lowerBound, pow(10, lowerBoundStr.length()) - 1);
            total += searchHelper(pow(10, upperBoundStr.length() - 1), upperBound);
        }
        else{
            total += searchHelper(lowerBound, upperBound);
        }
        //while(lowerBound <= upperBound){
            //string repeater = "";
            //none of the IDs seem to have more than 10 digits
            //divide into 2, 3, 5
            //but this won't actually work because we'll overcount, say, 111111
            //so check for repeaters of length 1 if needed (only for n=6,10)
        //}
        i++;
    }
    cout << "sum of invalid IDs: " << total << endl;
    products.close(); //think i forgot to do this yesterday. oopsie whoopsie
    return 0;
}