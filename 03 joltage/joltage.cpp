#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream batteries("powerbank.txt");
    string bank;
    int power = 0;

    while(getline(batteries, bank)){
        int tens = 0;
        int tensIndex = -1;
        for(int i = 0; i < bank.length(); i++){
            if(static_cast<int>(bank[i]) - 48 > tens){
                tens = static_cast<int>(bank[i]) - 48; //casting char to int returns the ASCII value of the char, so we subtract 48 to get its numerical value
                tensIndex = i;
            }
        }
        if(tensIndex == bank.length() - 1){
            int actualTens = 0;
            for(int i = 0; i < bank.length() - 1; i++){
                if(static_cast<int>(bank[i]) - 48 > actualTens){
                    actualTens = static_cast<int>(bank[i]) - 48;
                }
            }
            cout << 10 * actualTens + tens << endl;
            power += 10 * actualTens + tens;
        }
        else{
            int ones = 0;
            for(int i = tensIndex + 1; i < bank.length(); i++){
                if(static_cast<int>(bank[i]) - 48 > ones){
                    ones = static_cast<int>(bank[i]) - 48;
                }
            }
            cout << 10 * tens + ones << endl;
            power += 10 * tens + ones;
        }
    }
    cout << "total power: " << power << endl;

    batteries.close();
    return 0;
}
