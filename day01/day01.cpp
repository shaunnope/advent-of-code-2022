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

const str INPUT = "input.txt";

void task1() {
    ifstream infile(INPUT);

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

void task2() {
    ifstream infile(INPUT);

    vec<ll> heap;

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
            heap.push_back(current);
            current = 0;
        }
    }

    infile.close();
    sort(heap.begin(), heap.end(), greater<ll>());

    cout << heap[0]+heap[1]+heap[2] << endl;
}

int main() {
    task1();
    task2();

}



