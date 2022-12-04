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

#include <bitset>


using namespace std;

#define vec vector
using ll = long long;
using str = string;

int main() {
    ifstream infile("input.txt");
    
    ll a[2], b[2];
    str A,B;

    ll com, hypA, hypB;

    ll score = 0;

    str line;
    
    while(getline(infile, line)) {
        com = line.find(",");
        hypA = line.find("-");
        hypB = line.find("-", com);
        a[0] = stoll(line.substr(0, hypA));
        a[1] = stoll(line.substr(hypA+1, com-hypA));
        b[0] = stoll(line.substr(com+1,hypB-com));
        b[1] = stoll(line.substr(hypB+1));

        if(a[0] <= b[0] && a[1] >= b[1]){score++;}
        else if (b[0] <= a[0] && b[1] >= a[1]){score++;}
            
    }

    infile.close();

    cout << score << endl;
}

