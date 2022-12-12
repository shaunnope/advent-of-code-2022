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

vec<ll> parse_row(str line, pair<pair<size_t,size_t>, pair<size_t,size_t>>& targets, ll row_num, ll init){
    vec<ll> row;
    row.push_back(init);
    for(char c: line){
        if(c == 'S'){
            targets.first = pair<size_t,size_t>({row_num, row.size()});
            row.push_back(0);
        } else if(c == 'E'){
            targets.second = pair<size_t,size_t>({row_num, row.size()});
            row.push_back(25);
        }
        else row.push_back(c-'a');
    }
    row.push_back(init);
    return row;
}

pair<vec<vec<ll>>, pair<pair<size_t,size_t>, pair<size_t,size_t>>> parse_grid(str input, ll init){
    vec<vec<ll>> grid;
    pair<pair<size_t,size_t>, pair<size_t,size_t>> targets;

    ifstream infile(input);
    str line;
    ll row_num = 1;
    while(getline(infile, line)){
        grid.push_back(parse_row(line, targets, row_num, init));
        row_num++;
    }
    infile.close();

    grid.emplace(grid.begin(), vec<ll>(grid[0].size(), init));
    grid.push_back(vec<ll>(grid[0].size(), init));

    return {grid, targets};
}

ll get_shortest_path_length(vec<vec<ll>>& grid, pair<pair<size_t,size_t>, pair<size_t,size_t>> targets){
    pair<size_t,size_t> start = targets.first;
    pair<size_t,size_t> end = targets.second;

    queue<pair<pair<size_t,size_t>, ll>> q;
    q.push({start, 0});
    vec<vec<ll>> dists(grid.size(), vec<ll>(grid[0].size(), -1));
    ll dist = 0;
    while(!q.empty()){
        pair<pair<size_t,size_t>, ll> curr = q.front();
        if(curr.first == end) return curr.second;

        size_t i = curr.first.first;
        size_t j = curr.first.second;
        ll dist = curr.second;
        q.pop();
        

        if(dists[i][j] > -1) continue;
        dists[i][j] = dist;

        if(grid[i-1][j] <= grid[i][j]+1) q.push({{i-1,j},dist+1});
        if(grid[i+1][j] <= grid[i][j]+1) q.push({{i+1,j},dist+1});
        if(grid[i][j-1] <= grid[i][j]+1) q.push({{i,j-1},dist+1});
        if(grid[i][j+1] <= grid[i][j]+1) q.push({{i,j+1},dist+1});

    }
    
    return 0;
}

ll get_closest_start(vec<vec<ll>>& grid, pair<pair<size_t,size_t>, pair<size_t,size_t>> targets){
    pair<size_t,size_t> start = targets.first;
    pair<size_t,size_t> end = targets.second;
    queue<pair<pair<size_t,size_t>, ll>> q;
    q.push({end, 0});
    vec<vec<ll>> dists(grid.size(), vec<ll>(grid[0].size(), -1));
    ll dist = 0;
    while(!q.empty()){
        pair<pair<size_t,size_t>, ll> curr = q.front();
        size_t i = curr.first.first;
        size_t j = curr.first.second;
        ll dist = curr.second;

        if(grid[i][j] == 0) return curr.second;
        q.pop();
        

        if(dists[i][j] > -1) continue;
        dists[i][j] = dist;

        if(grid[i][j] <= grid[i-1][j]+1) q.push({{i-1,j},dist+1});
        if(grid[i][j] <= grid[i+1][j]+1) q.push({{i+1,j},dist+1});
        if(grid[i][j] <= grid[i][j-1]+1) q.push({{i,j-1},dist+1});
        if(grid[i][j] <= grid[i][j+1]+1) q.push({{i,j+1},dist+1});

    }
    
    return 0;
}


void task1(str input) {
    cout << input << " - Task 1: " << endl; 
    
    vec<vec<ll>> grid;
    pair<pair<ll,ll>, pair<ll,ll>> targets;

    auto& output = parse_grid(input, 50);
    grid = output.first;
    targets = output.second;
    ll sum = get_shortest_path_length(grid, targets);

    cout << sum << endl;

}

void task2(str input) {
    cout << input << " - Task 2: " << endl; 

    vec<vec<ll>> grid;
    pair<pair<ll,ll>, pair<ll,ll>> targets;

    auto& output = parse_grid(input, -10);
    grid = output.first;
    targets = output.second;
    ll sum = get_closest_start(grid, targets);

    cout << sum << endl;

}

int main() {
    task1(TEST);
    task2(TEST);
    task1(INPUT);
    task2(INPUT);
}

