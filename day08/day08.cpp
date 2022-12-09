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

vec<vec<int>> get_grid(str input){

    ifstream infile(input);

    vec<vec<int>> grid;
    str line;

    while(getline(infile, line)){
        vec<int> row = {};
        for(char tree : line){
            row.push_back(tree - '0');
        }
        grid.push_back(row);
    }
    infile.close();

    return grid;
}

vec<vec<pair<int,int>>> init_dp(vec<vec<int>> grid){
    size_t n = grid.size();
    size_t m = grid[0].size();

    vec<pair<int,int>> row(m, {0,0});
    vec<vec<pair<int,int>>> dp(n, row);

    for(int i=0; i<n; i++){
        dp[i][0].first = grid[i][0];
        dp[i][m-1].first = grid[i][m-1];
    }
    for(int j=0; j<m; j++){
        dp[0][j].second = grid[0][j];
        dp[n-1][j].second = grid[n-1][j];
    }

    return dp;
}

bitset<10000> get_visibility(vec<vec<int>> grid){

    ll n = grid.size();
    ll m = grid[0].size();

    bitset<10000> visibility;

    vec<vec<pair<int,int>>> dp = init_dp(grid);

    for(int i=1; i<n-1; i++){
        for(int j=1; j<m-1; j++){
            if (grid[i][j] > dp[i-1][j].second || grid[i][j] > dp[i][j-1].first) {
                visibility.set(i*n+j, true);
            }
            dp[i][j].second = max(dp[i-1][j].second, grid[i][j]);
            dp[i][j].first = max(dp[i][j-1].first, grid[i][j]);
        }
    }

    for(int i=n-2; i>0; i--){
        for(int j=m-2; j>0; j--){
            if (grid[i][j] > dp[i+1][j].second || grid[i][j] > dp[i][j+1].first) {
                visibility.set(i*n+j, true);
            }
            dp[i][j].second = max(dp[i+1][j].second, grid[i][j]);
            dp[i][j].first = max(dp[i][j+1].first, grid[i][j]);
        }
    }

    return visibility;
}

ll get_max(vec<vec<int>> grid){

    ll n = grid.size();
    ll m = grid[0].size();

    vec<vec<ll>> row(m, {0,0,0,0}); // udlr
    vec<vec<vec<ll>>> scores(n, row); 
    
    vec<vec<vec<ll>>> equality(n, row); 
    ll score;
    ll max_score = 0;

    for(int i=1; i<n-1; i++){
        for(int j=1; j<m-1; j++){
            scores[i][j][0] = (grid[i][j] > grid[i-1][j]) ? equality[i-1][j][0] + 1 : 1; // up
            scores[i][j][2] = (grid[i][j] > grid[i][j-1]) ? equality[i][j-1][2] + 1 : 1; // left

            equality[i][j][0] = (grid[i][j] >= grid[i-1][j]) ? equality[i-1][j][0] + 1 : 1; // up
            equality[i][j][2] = (grid[i][j] >= grid[i][j-1]) ? equality[i][j-1][2] + 1 : 1; // left
        }
    }

    for(int i=n-2; i>0; i--){
        // cout << endl;
        for(int j=m-2; j>0; j--){
            scores[i][j][1] = (grid[i][j] > grid[i+1][j]) ? equality[i+1][j][1] + 1 : 1; // down
            scores[i][j][3] = (grid[i][j] > grid[i][j+1]) ? equality[i][j+1][3] + 1 : 1; // right

            equality[i][j][1] = (grid[i][j] >= grid[i+1][j]) ? equality[i+1][j][1] + 1 : 1; // up
            equality[i][j][3] = (grid[i][j] >= grid[i][j+1]) ? equality[i][j+1][3] + 1 : 1; // left

            score = 1;

            for(int k=0; k<4;k++){
                score *= scores[i][j][k];
            }
            max_score = max(score, max_score);

            // cout << score << " ";
        }
        
    }
    // cout << endl;

    return max_score;
}


void task1(str input) {
    cout << input << " - Task 1: "; 

    vec<vec<int>> grid = get_grid(input);
    bitset<10000> visibility = get_visibility(grid);

    ll n = grid.size();
    ll m = grid[0].size();
    
    ll res = visibility.count()+2*(n+m-2);
    cout << res  << endl;
}

void task2(str input) {
    cout << input << " - Task 2: "; 

    vec<vec<int>> grid = get_grid(input);

    ll res = get_max(grid);
    cout << res << endl;

}


int main() {
    task1(TEST);
    task2(TEST);
    task1(INPUT);
    task2(INPUT);
}

