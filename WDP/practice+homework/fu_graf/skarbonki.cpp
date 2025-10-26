#include<bits/stdc++.h>
#include"find_union.h"
using namespace std;

int skarbonki(int s, int tab[]) {
    vector<find_union> skr;
    unordered_set <int> res;
    for(int i = 0; i < s; i++) {
        skr.push_back(create_find_union(i));
    }
    for(int i = 0; i < s; i++) {
        unite(skr[i], skr[tab[i]]);
    }
    for(int i = 0; i < s; i++) {
        res.insert(find(skr[i]));
    }
    for(int i = 0; i < s; i++) {
        delete skr[i];
    }
    return res.size();
}


int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    int tab[a];
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &tab[i]) != 1) {
            return -1;
        }
    }
    printf("%d", skarbonki(a, tab));
    return 0;
}