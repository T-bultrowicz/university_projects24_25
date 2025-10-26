#include<bits/stdc++.h>
using namespace std;

int _T___SIZE;
constexpr size_t _GOLDEN_RATIO = 2654435761u;
struct Hashprocedure {
    size_t operator()(const vector<int>& t) const {
        size_t res = _T___SIZE;
        for(int i = 0; i < (int) _T___SIZE ;i++) {
            res ^= hash<int>{}(t[i]) + 0x9e3779b9 + (res << 6) + (res >> 2);
        }
        return res;
    }
};

int equalPairs(vector<vector<int>>& grid) {
    _T___SIZE = grid.size();
    int res = 0;
    unordered_map<vector<int>, int ,Hashprocedure> map;
    vector<int> check;
    for(auto a : grid) {
        auto x = map.find(a);
        if(x != map.end()) {
            x->second++;
        } else {
            map.insert({a,1});
        }
    }
    for(int i = 0; i < _T___SIZE; i++) {
        check.clear();
        for(int j = 0; j < _T___SIZE; j++) {
            check.push_back(grid[j][i]);
        }
        auto x = map.find(check);
        if(x != map.end()) {
            res += x->second;
        }
    }
    return res;
}

int main() {
    _T___SIZE = 117;
}