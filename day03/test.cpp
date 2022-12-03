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

void run(int i){
    typedef size_t len_t, pos_t;

    bitset<32> bits;
    bits.set(pos_t(i), true);
    cout << log2(bits.to_ulong()) << " " << 31 - bits.to_string().find("1") << endl;
}

int main() {
    ifstream infile("input.txt");
    
    char a, b;
    str A, B;
    ll counts[53];
    ll errors[53];
    ll half;
    ll pos;


    str line;
    
    for(int i=0; i<32;i++){
        run(i);
    }

}

