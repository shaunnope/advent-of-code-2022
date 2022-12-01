#include <iostream>
#include <fstream> // File IO
#include <sstream> // String IO
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>


using namespace std;

#define vec vector
using ll = long long;
using str = string;

int main() {
    ifstream infile("0101_input.txt");

    ll max = 0;
    ll current = 0;
    ll item = 0;
    str line;
    
    while(getline(infile, line)) {
        if(line.size() > 1){
            stringstream stream(line);
            stream >> item;
            current += item;

        } else {
            if(current > max){
                max = current;
            }
            current = 0;
        }
    }

    infile.close();


    cout << max << endl;
}

