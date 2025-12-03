#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

long joltageHelper(string bank, int startingIndex, int digit){
    int place = 0;
    int index = -1;
    for(int i = startingIndex; i < bank.length() - digit; i++){
        if(static_cast<int>(bank[i]) - 48 > place){
            place = static_cast<int>(bank[i]) - 48; //again, there's a good reason i'm subtracting 48 here
            index = i;
        }
    }

    if(digit == 0){
        return place;
    }
    else{
        return pow(10, digit) * place + joltageHelper(bank, index + 1, digit - 1); //recursivity!!! programmers think that's cool, right
    }
}

int main(){
    ifstream batteries("powerbank.txt");
    string bank;
    long power = 0;

    while(getline(batteries, bank)){
        long reading = joltageHelper(bank, 0, 11);
        cout << reading << endl;
        power += reading;
    }
    cout << "total power: " << power << endl;

    batteries.close();
    return 0;
}
