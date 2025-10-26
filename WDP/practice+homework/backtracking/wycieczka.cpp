#include<bits/stdc++.h>
using namespace std;

void r_trip(int city, vector<int>& b_v, vector<vector<int>>& unl, const vector<vector<int>>& d, int cd, int& mind) {
    int n = d.size();
    if(city == n - 1) {
        mind = min(mind, cd);
        return;
    }
    for(int i = n - 1; i > 0; i--) {
        if(!b_v[i]) {
            if(i < n - 1) {
                for(int j : unl[i]) {
                    b_v[j]--;
                }
                b_v[i]++;
            }
            r_trip(i, b_v, unl, d, cd + d[city][i], mind);
            if(i < n - 1) {
                for(int j : unl[i]) {
                    b_v[j]++;
                }
                b_v[i]--;
            }
        }
    }
    return;
}

int wycieczka(const vector<vector<int>>& dist, const vector<pair<int,int>> assertions) {
    vector<int>blocked_v(dist.size(), 0);
    vector<vector<int>> unlocks(dist.size() - 1);
    int min_dist = INT_MAX;
    blocked_v[dist.size() - 1] = dist.size() - 2;
    for(int i = 0; i < assertions.size(); i++) {
        if(assertions[i].first != dist.size() - 1 && assertions[i].second != dist.size() - 1) {
            unlocks[assertions[i].first].push_back(assertions[i].second);
            blocked_v[assertions[i].second]++;
        }
    }
    for(int i = 0; i < dist.size() - 1; i++) {
        unlocks[i].push_back(dist.size() - 1);
    }
    r_trip(0, blocked_v, unlocks, dist, 0, min_dist);
    return min_dist;
}

int main() {
    int n, l, a, b;
    scanf("%d %d", &n, &l);
    vector<pair<int,int>> assertions;
    vector<vector<int>> dist;
    for(int i = 0; i < l; i++) {
        scanf("%d %d", &a, &b);
        assertions.push_back(make_pair(--a,--b));
    }
    dist.resize(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &a);
            dist[i].push_back(a);
        }
    }
    printf("%d", wycieczka(dist, assertions));
    return 0;
}