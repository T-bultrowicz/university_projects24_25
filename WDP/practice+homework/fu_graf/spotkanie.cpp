#include<bits/stdc++.h>
using namespace std;

pair<int,int> spotkanie(const vector <vector <int>>& amp) {
    int min_dis = INT_MAX;
    pair<int,int> bst_pair = {-1, -1};
    vector <vector <pair <int,int>>> dis;
    queue<pair <pair <int,int>, int>> to_vis;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    dis.resize(amp.size());
    for(int i = 0;i < amp.size(); i++) {
        for(int j = 0; j < amp[0].size(); j++) {
            dis[i].push_back({-1, -1});
        }
    }
    //start first search
    to_vis.push({{0, 0}, 0});
    while(!to_vis.empty()) {
        auto q = to_vis.front();
        dis[q.first.first][q.first.second].first = q.second;
        for(int i = 0; i < 4; i++) {
            if(q.first.first + dx[i] >=0 && q.first.second + dy[i] >= 0 &&
                q.first.first + dx[i] < amp.size() && q.first.second + dy[i] < amp[0].size()) {
                    if(dis[q.first.first + dx[i]][q.first.second + dy[i]].first == -1 &&
                        amp[q.first.first + dx[i]][q.first.second + dy[i]] < amp[q.first.first][q.first.second]) {
                            to_vis.push({{q.first.first + dx[i], q.first.second + dy[i]}, q.second + 1});
                    }
            }
        }
        to_vis.pop();
    }
    //start second search
    to_vis.push({{0, amp[0].size() - 1}, 0});
    while(!to_vis.empty()) {
        auto q = to_vis.front();
        dis[q.first.first][q.first.second].second = q.second;
        if(dis[q.first.first][q.first.second].first != -1) {
            if(dis[q.first.first][q.first.second].first + q.second < min_dis) {
                min_dis = dis[q.first.first][q.first.second].first + q.second;
                bst_pair = {q.first.first, q.first.second};
            }
        }
        for(int i = 0; i < 4; i++) {
            if(q.first.first + dx[i] >=0 && q.first.second + dy[i] >= 0 &&
                q.first.first + dx[i] < amp.size() && q.first.second + dy[i] < amp[0].size()) {
                    if(dis[q.first.first + dx[i]][q.first.second + dy[i]].second == -1 &&
                        amp[q.first.first + dx[i]][q.first.second + dy[i]] < amp[q.first.first][q.first.second]) {
                            to_vis.push({{q.first.first + dx[i], q.first.second + dy[i]}, q.second + 1});
                    }
            }
        }
        to_vis.pop();        
    }
    return bst_pair;
}

int main() {
    int a, b, c;
    if(scanf("%d %d", &a, &b) != 2) {
        return -1;
    }
    vector <vector <int>> amp;
    amp.resize(a);
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            if(scanf("%d", &c) != 1) {
                return -1;
            }
            amp[i].push_back(c);
        }
    }
    auto ab = spotkanie(amp);
    printf("%d %d", ab.first, ab.second);
    return 0;
}