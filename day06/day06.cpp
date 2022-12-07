#include <iostream>
#include <fstream> // File IO
#include <sstream> // String IO
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

#include <map> // sorted kv pairs
#include <bitset>
#include <numeric>


using namespace std;

#define vec vector
using ll = long long;
using str = string;

const str INPUT = "input.txt";
const str TEST = "test.txt";

ll find_start(stringstream& input, int n){
    if(n>26){
        return -1;
    }

    char c;
    ll pos;
    queue<char> buf;
    int counts[26];
    int cum;

    fill(counts, counts+26, 1);

    for(int i=0;i<n;i++){
        input >> c;
        buf.push(c);
        counts[c-'a']++;
    }
    pos = n;

    while(c != '\n'){
        cum = accumulate(counts, counts+26, 1, multiplies<int>());
        if(cum == pow(2,n)){
            return pos;
        }

        input >> c;
        pos++;
        buf.push(c);
        counts[c-'a']++;
        counts[buf.front()-'a']--;
        buf.pop();
    }
    return 0;
}


void task1(str input) {
    cout << input << " - Task 1: " << endl; 

    ifstream infile(input);
    str line;

    while(getline(infile, line)){
        stringstream lstream(line);
        cout << find_start(lstream, 4) << endl;
    }
    
    infile.close();

    cout << endl;

}

void task2(str input) {
    cout << input << " - Task 2: " << endl; 

    ifstream infile(input);
    str line;

    while(getline(infile, line)){
        stringstream lstream(line);
        cout << find_start(lstream, 14) << endl;
    }
    
    infile.close();

    cout << endl;

}

int main() {
    task1(TEST);
    task2(TEST);
    task1(INPUT);
    task2(INPUT);
}

