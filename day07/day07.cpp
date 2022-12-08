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


using namespace std;

#define vec vector
using ll = long long;
using str = string;

const str INPUT = "input.txt";
const str TEST = "test.txt";

ll parse_line(str line, vec<str>& path, set<vec<str>>& hist, map<vec<str>,ll>& dir_sizes){

    vec<str> current;
    str dir;

    switch(line[0]) {
        case '$': // command
            if(line.substr(2,3) == "cd "){
                str item = line.substr(5);
                if(item == ".."){ // finished processing directory
                    current = path;
                    path.pop_back();
                    dir_sizes[path] += dir_sizes[current];
                } else {
                    path.push_back(item);
                }
                
            }
            break;

        case 'd': // directory
            dir = line.substr(4);
            path.push_back(dir);
            current = path;

            dir_sizes.insert({current, 0});
            path.pop_back();

            break;
            
        default: // file
            str item;
            ll size;
            stringstream lstream(line);
            lstream >> size >> item;
            path.push_back(item);

            current = path;
            path.pop_back();

            size_t hist_length = hist.size();
            hist.insert(current);
            if(hist.size() > hist_length && size <= 100000){
                return size;
            }
            break;
    }

    return 0;
}


void task1(str input) {
    cout << input << " - Task 1: " << endl; 

    ifstream infile(input);
    str line;

    map<vec<str>, ll> dir_sizes;

    /**
     * store current path
     * if in new directory, track files recorded
     * else, skip to next command
     * 
     */
    vec<str> path = {};
    set<vec<str>> hist = {}; 
    ll res = 0;

    while(getline(infile, line)){
       res += parse_line(line, path, hist, dir_sizes);
    }
    
    infile.close();

    cout << res << endl;

}

void task2(str input) {
    cout << input << " - Task 2: " << endl; 

    ifstream infile(input);
    str line;

    // while(getline(infile, line)){
    //     stringstream lstream(line);
    //     cout << find_start(lstream, 14) << endl;
    // }
    
    // infile.close();

    // cout << endl;

}


int main() {
    task1(TEST);
    // task2(TEST);
    task1(INPUT);
    // task2(INPUT);
}

