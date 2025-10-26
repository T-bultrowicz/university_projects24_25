#include<bits/stdc++.h>
using namespace std;


//T: O(E^2), M: O(E + V)
vector <vector <int>> przetworz(const vector<vector <bool>>& g) {
    vector <vector <int>> res(g.size());
    for(int i = 0; i < g.size(); i++) {
        for(int j = 0; j < g.size(); j++) {
            if(g[i][j]) {
                res[j].push_back(i);
            }
        }
    }
    return res;
}

pair<int,int> deep_f_search(const vector <vector<int>>& g, int v, int& res, vector<bool>& visited) {
    if(!g[v].size()) {
        visited[v] = true;
        return {0, v};
    }
    bool dominated = true;
    int comparator;
    pair <int,int> most = {-1,-1};
    for(int i = 0; i < g[v].size(); i++) {
        auto a = deep_f_search(g, g[v][i], res, visited);
        if(!i) comparator = a.second;
        if(comparator != a.second) dominated = false;
        if(++a.first > most.first) most = a;
    }
    if(dominated && most.first > 1 && !visited[v]) res++;
    visited[v] = true;
    return most;
}

//T: O(E + V), M: O(E + V)
int zdominowani(const vector<vector <bool>>& g) {
    auto nowy_g = przetworz(g);
    int ilosc_zdominowanych = 0;
    vector <bool> visited(nowy_g.size(), false);
    for(int i = 0; i < nowy_g.size(); i++) {
        if(!visited[i]) {
            deep_f_search(nowy_g, i, ilosc_zdominowanych, visited);
        }
    }
    return ilosc_zdominowanych;
}

int main() {
    int n, d;
    if(scanf("%d", &n) != 1) {
        return -1;
    }
    vector <vector <bool>> g;
    g.resize(n);
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < n; i++) {
            if(scanf("%d", &d) != 1) {
                return -1;
            }
            g[j].push_back((bool) d);
        }
    }
    printf("%d", zdominowani(g));
    return 0;
}