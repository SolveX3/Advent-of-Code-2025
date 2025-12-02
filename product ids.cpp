#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

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
        if(upperBoundStr.length() % 2 == 1){
            //bring the upper bound down to an even number of digits (all 9's)
            int target = upperBoundStr.length() - 1;
            upperBoundStr = "";
            for(int i = 1; i <= target; i++){
                upperBoundStr = upperBoundStr + "9";
            }
        }
        if(lowerBoundStr.length() % 2 == 1){
            int target = lowerBoundStr.length();
            lowerBoundStr = "1";
            for(int i = 1; i <= target; i++){
                lowerBoundStr = lowerBoundStr + "0";
            }
        }
        cout << "checking range [" << lowerBoundStr << ", " << upperBoundStr << "]" << endl;
        long lowerBound = stol(lowerBoundStr); //ran my code the first time and got told the very first input was "out of range" for stoi()
        long upperBound = stol(upperBoundStr);
        while(lowerBound <= upperBound){
            long leftHalf = floor(lowerBound / (pow(10, lowerBoundStr.length()/2)));
            string id = to_string(leftHalf) + to_string(leftHalf);
            if(stol(id) >= lowerBound && stol(id) <= upperBound){
                cout << id << endl;
                total += stol(id);
            }
            lowerBound = stol(to_string(leftHalf + 1) + to_string(leftHalf + 1));
            lowerBoundStr = to_string(lowerBound);
        }
        i++;
    }
    cout << "sum of invalid IDs: " << total << endl;
    products.close(); //think i forgot to do this yesterday. oopsie whoopsie
    return 0;
}