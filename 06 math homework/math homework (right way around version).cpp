#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
    ifstream homework("problemsheet.txt");
    string current = "";

    vector<vector<char>> problems = {}; //nested vector! waow

    while(getline(homework, current)){
        problems.push_back({}); //we stay silly :3
        string temp = "";
        for(int i = 0; i < current.length(); i++){
            problems.back().push_back(current[i]);
        }
    }

    long calculator = 0;
    vector<int> numbers = {};
    string temp = "";
    for(int i = problems.front().size() - 1; i >= 0; i--){
        for(int j = 0; j < problems.size(); j++){
            if(problems.at(j).at(i) == '+'){
                //push and add; reset
                numbers.push_back(stoi(temp));
                temp = "";
                long entry = 0;
                for(int n = 0; n < numbers.size(); n++){
                    entry += numbers.at(n);
                    cout << numbers.at(n) << " + ";
                }
                cout << "\b\b" << "= " << entry << endl;
                calculator += entry;
                while(numbers.empty() == 0){
                    numbers.pop_back();
                }
            }
            else if(problems.at(j).at(i) == '*'){
                //push and multiply; reset
                numbers.push_back(stoi(temp));
                temp = "";
                long entry = 1;
                for(int n = 0; n < numbers.size(); n++){
                    entry *= numbers.at(n);
                    cout << numbers.at(n) << " * ";
                }
                cout << "\b\b" << "= " << entry << endl;
                calculator += entry;
                while(numbers.empty() == 0){
                    numbers.pop_back();
                }
            }
            else if(problems.at(j).at(i) != ' '){
                temp = temp + problems.at(j).at(i);
            }
        }
        if(temp != ""){
            numbers.push_back(stoi(temp));
            temp = "";
        }
    }

    cout << "checksum = " << calculator << endl;

    homework.close();
    return 0;
}