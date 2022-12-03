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
    
    char a;

    bitset<56> counts;
    typedef size_t len_t, pos_t;

    ll errors[53];
    ll half;
    ll pos;
    ll score = 0;

    fill(errors, errors+53, 0);

    str line;
    
    while(getline(infile, line)) {
        counts.reset();
        half = line.size()/2;
        stringstream stream(line);

        // process first half
        for(int i=0; i<half; i++){
            stream >> a;
            pos = (ll) (a-'A')+1;
            if(pos > 26){
                pos = (ll) (a-'a')+1;
            } else{
                pos += 26;
            }
            counts.set(pos_t(pos), true);
        }

        // process second half
        for(int i=0; i<half; i++){
            stream >> a;
            pos = (ll) (a-'A')+1;
            if(pos > 26){
                pos = (ll) (a-'a')+1;
            } else {
                pos += 26;
            }
            if(counts[pos]){
                errors[pos] += 1;
                break;
            }
        }
            
    }

    infile.close();

    for(int i=1; i<53; i++){
        score += i*errors[i];
    }

    cout << score << endl;
}

