#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
    ifstream input("beamsplitters.txt");

    vector<string> board = {};
    int count = 0;

    //read in file
    string line = "";
    while(getline(input, line)){
        board.push_back(line);
    }

    for(int i = 1; i < board.size(); i++){
        for(int j = 0; j < board.front().length(); j++){
            if(board.at(i-1)[j] == 'S' || board.at(i-1)[j] == '|'){
                if(board.at(i)[j] == '.'){
                    board.at(i)[j] = '|'; //drop the beam
                }
                else if(board.at(i)[j] == '^'){ //split the beam
                    count++;
                    //just to be safe
                    if(j > 0){
                        board.at(i)[j-1] = '|';
                    }
                    if(j < board.at(i).length() - 1){
                        board.at(i)[j+1] = '|';
                    }
                }
            }
        }
    }

    //read out board
    for(int i = 0; i < board.size(); i++){
        cout << board.at(i) << endl;
    }
    cout << "total splits: " << count << endl;

    input.close();
    return 0;
}