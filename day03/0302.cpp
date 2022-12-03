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

    bitset<53> counts[3];
    bitset<53> badge;
    typedef size_t len_t, pos_t;

    ll badges[53];
    ll pos;
    ll score = 0;
    int mem = 0;

    fill(badges, badges+53, 0);

    str line;
    
    while(getline(infile, line)) {
        counts[mem].reset();
        stringstream stream(line);

        // process member
        for(int i=0; i<line.size(); i++){
            stream >> a;
            pos = (ll) (a-'A')+1;
            if(pos > 26){
                pos = (ll) (a-'a')+1;
            } else{
                pos += 26;
            }
            counts[mem].set(pos_t(pos), true);
        }

        if(mem == 2){
            pos = 52 - (counts[0] & counts[1] & counts[2]).to_string().find("1");
            cout << counts[0] << " " << counts[1] << " " << counts[2] << " " << pos << endl;
            badges[pos] += 1;
        }

        mem = (mem+1)%3;
    }

    infile.close();

    for(int i=1; i<53; i++){
        score += i*badges[i];
    }

    cout << score << endl;
}

