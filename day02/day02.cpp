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

#include <map>

using namespace std;

#define vec vector
using ll = long long;
using str = string;

const str INPUT = "input.txt";

void task1() {
    cout << "Task 1: ";
    ifstream infile(INPUT);

    char a, b;
    ll score = 0;
    ll self, opp;
    /*
        0 1 2
      0 1 0 2
      1 2 1 0
      2 0 2 1

        0  1  2
      0 0  2  1
      1 1  0  2
      2 2  1  0
    */

    str line;
    
    while(getline(infile, line)) {
            stringstream stream(line);
            stream >> a >> b;
            opp = (ll) (a-'A');
            self = (ll) (b-'X');
            score += self+1 + 3*((self-opp+4)%3);
    }

    infile.close();


    cout << score << endl;
}

void task2() {
    cout << "Task 2: ";
    ifstream infile(INPUT);

    char a, b;
    ll score = 0;
    ll self, opp;
    /*
        0 1 2
      0 1 0 2
      1 2 1 0
      2 0 2 1

        0  1  2
      0 0  2  1
      1 1  0  2
      2 2  1  0
    */

    str line;
    
    while(getline(infile, line)) {
            stringstream stream(line);
            stream >> a >> b;
            opp = (ll) (a-'A');
            self = (ll) (b-'X');
            score += (self+opp+2)%3 +1 + 3*self;
    }

    infile.close();


    cout << score << endl;
}

int main() {
    task1();
    task2();
}

