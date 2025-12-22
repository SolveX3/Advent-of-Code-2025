#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
    ifstream homework("problemsheet.txt");
    string current = "";

    vector<vector<string>> problems = {}; //nested vector! waow

    while(getline(homework, current)){
        problems.push_back({}); //we stay silly :3
        string temp = "";
        for(int i = 0; i < current.length(); i++){
            if(current[i] == ' '){
                if(temp != ""){
                    problems.back().push_back(temp);
                    temp = "";
                }
            }
            else{
                temp = temp + current[i];
            }
        }
        if(temp != ""){
            problems.back().push_back(temp);
            temp = "";
        }
    }

    long calculator = 0;
    for(int i = 0; i < problems.back().size(); i++){
        if(problems.back().at(i) == "*"){
            long entry = 1;
            for(int j = 0; j < problems.size() - 1; j++){
                entry *= stol(problems.at(j).at(i));
                cout << stol(problems.at(j).at(i)) << " * ";
            }
            calculator += entry;
            cout << "\b\b" << "= " << entry << endl;
        }
        else{
            long entry = 0; //i know this doesn't need to be long, but maybe it'll make it easier on the computer
            for(int j = 0; j < problems.size() - 1; j++){
                entry += stol(problems.at(j).at(i));
                cout << stol(problems.at(j).at(i)) << " + ";
            }
            calculator += entry;
            cout << "\b\b= " << entry << endl; //this doesn't work the way i'd like; instead of backspacing twice and replacing the desired characters, it just prints 'b' twice
        }
    }

    cout << "checksum = " << calculator << endl;

    homework.close();
    return 0;
}