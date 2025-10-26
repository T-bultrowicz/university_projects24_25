#include<bits/stdc++.h>
using namespace std;

int proximity(const vector<vector <int>>& g, int s, int k) {
    vector<bool> visited;
    queue<pair <int,int>> to_visit;
    for(auto a : g) {
        visited.push_back(false);
    }
    for(int i = 0; i < s; i++) {
        to_visit.push({i, 0});
        visited[i] = true;
    }
    int count = -s;
    while(!to_visit.empty()) {
        auto a = to_visit.front();
        to_visit.pop();
        if(++count == k) {
            return a.second;
        }
        for(int b : g[a.first]) {
            if(!visited[b]) {
                to_visit.push({b, a.second + 1});
                visited[b] = true;
            }
        }
    }
    return -1;
}


int main() {
    int n, m, s, k;
    if(scanf("%d %d %d %d", &n, &m, &s, &k) != 4) {
        return -1;
    }
    vector <vector <int>> graph;
    int a, b;
    graph.resize(n);
    for(int i = 0; i < m; i++) {
        if(scanf("%d %d", &a, &b) != 2) {
            return -1;
        }
        graph[--a].push_back(--b);
        graph[b].push_back(a);
    }
    printf("%d", proximity(graph, s, k));  
    return 0;
}