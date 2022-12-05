#include <iostream>
#include <fstream> // File IO
#include <sstream> // String IO
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

#include <map> // sorted kv pairs
#include <bitset>


using namespace std;

#define vec vector
using ll = long long;
using str = string;

const str INPUT = "input.txt";

vec<deque<char>> parse(ifstream& input){
    vec<deque<char>> stacks;
    ll pos;

    str line;
    // init stacks
    getline(input, line);
    stacks.push_back({});

    for(int i=1; i<line.size(); i+=4){
        if(line[i] != ' '){
            stacks.push_back({line[i]});
        } else {
            stacks.push_back({});
        }
    }
    getline(input, line);

    while(line.find("1") == -1) {
        for(int i=1; i<line.size(); i+=4){
            if(line[i] != ' '){
                stacks[(i+3)/4].push_front(line[i]);
            }
        }
        getline(input, line);
    }

    getline(input, line);
   
    return stacks;

}

void task1() {
    cout << "Task 1: \n"; 

    ifstream infile(INPUT);
    
    vec<deque<char>> stacks = parse(infile);
    for(deque<char> stk : stacks){
        for(char item : stk){
            cout << item;
        }
        cout << endl;
    }

    str line, tmp;
    ll num, from, to;

    while(getline(infile, line)){
        stringstream op(line);
        op >> tmp >> num >> tmp >> from >> tmp >> to;

        for(int i=0; i<num; i++){
            stacks[to].push_back(stacks[from].back());
            stacks[from].pop_back();
        }
    }
    infile.close();

    cout << endl;
    for(deque<char> stk : stacks){
        if(stk.size() == 0){continue;}
        cout << stk.back();
    }
    cout << endl;

}

void task2() {
    cout << "Task 2: \n"; 

    ifstream infile(INPUT);
    
    vec<deque<char>> stacks = parse(infile);

    str line, tmp;
    ll num, from, to;

    vec<char> ts = {};

    while(getline(infile, line)){
        stringstream op(line);
        op >> tmp >> num >> tmp >> from >> tmp >> to;

        for(int i=0; i<num; i++){
            ts.push_back(stacks[from].back());
            stacks[from].pop_back();
        }
        for(int i=0; i<num; i++){
            stacks[to].push_back(ts.back());
            ts.pop_back();
        }
    }
    infile.close();

    cout << endl;
    for(deque<char> stk : stacks){
        if(stk.size() == 0){continue;}
        cout << stk.back();
    }
    cout << endl;
}

int main() {
    task1();
    task2();
}

