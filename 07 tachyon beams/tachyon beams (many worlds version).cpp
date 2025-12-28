#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
    ifstream input("beamsplitters.txt");

    vector<vector<long>> board = {};
    long count = 0;

    //read in file
    string line = "";
    while(getline(input, line)){
        board.push_back({});
        for(int i = 0; i < line.length(); i++){
            if(line[i] == '^'){
                board.back().push_back(-1);
            }
            else if(line[i] == '.'){
                board.back().push_back(0);
            }
            else if(line[i] == 'S'){
                board.back().push_back(1);
            }
        }
    }

    for(int i = 1; i < board.size(); i++){
        for(int j = 0; j < board.front().size(); j++){
            if(board.at(i-1).at(j) >= 0){
                if(board.at(i).at(j) != -1){
                    board.at(i).at(j) += board.at(i-1).at(j); //drop the beam
                }
                else{ //split the beam
                    //just to be safe
                    if(j > 0){
                        board.at(i).at(j-1) += board.at(i-1).at(j);
                    }
                    if(j < board.at(i).size() - 1){
                        board.at(i).at(j+1) += board.at(i-1).at(j);
                    }
                }
            }
        }
        for(int j = 0; j < board.front().size(); j++){
            cout.width(3);
            if(board.at(i).at(j) == -1){
                cout << "  ^ ";
            }
            else{
                cout << board.at(i).at(j) << " ";
            }
        }
        cout << endl;
    }

    for(int i = 0; i < board.back().size(); i++){
        if(board.back().at(i) != -1){
            count += board.back().at(i);
        }
    }

    cout << "total timelines: " << count << endl;

    input.close();
    return 0;
}