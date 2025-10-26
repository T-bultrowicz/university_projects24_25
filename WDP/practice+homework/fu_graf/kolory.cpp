#include<bits/stdc++.h>
#include"find_union.h"
using namespace std;

int kolory(const vector<pair <int,int>>& towers) {
    vector <pair <pair <int, int>, int> > tow;
    vector <find_union> fu;
    unordered_set <int> res;
    for(int i = 0; i < towers.size(); i++) {
        tow.push_back({towers[i], i});
        fu.push_back(create_find_union(i));      
    }
    sort(tow.begin(), tow.end());
    for(int i = 0; i < towers.size() - 1; i++) {
        if(tow[i].first.first == tow[i + 1].first.first) {
            unite(fu[tow[i].second], fu[tow[i + 1].second]);
        }
    }
    for(int i = 0; i < towers.size(); i++) {
        swap(tow[i].first.first, tow[i].first.second);
    }
    sort(tow.begin(), tow.end());
    for(int i = 0; i < towers.size() - 1; i++) {
        if(tow[i].first.first == tow[i + 1].first.first) {
            unite(fu[tow[i].second], fu[tow[i + 1].second]);
        }
    }
    for(int i = 0; i < towers.size(); i++) {
        res.insert(find(fu[i]));
    }
    for(int i = 0; i < towers.size(); i++) {
        delete fu[i];
    }
    return res.size();
}


int main() {
    int il_w;
    if(scanf("%d", &il_w) != 1) {
        return -1;
    }
    vector < pair<int,int>> towers;
    towers.resize(il_w);
    for(int i = 0; i < il_w; i++) {
        if(scanf("%d %d", &(towers[i].first), &(towers[i].second)) != 2) {
            return -1;
        }
    }
    printf("\n\n%d", kolory(towers));
    return 0;
}