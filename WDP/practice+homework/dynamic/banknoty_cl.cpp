#include<bits/stdc++.h>
using namespace std;

int banknot(int kwota, const vector<int> &nom) {
    if(!kwota) return 0;
    vector<int> dist(kwota, 0);
    queue<int>to_s;
    to_s.push(0);
    while(!to_s.empty()) {
        int l = to_s.front();
        to_s.pop();
        for(int i = nom.size() - 1; i >= 0; i--) {
            if(l + nom[i] == kwota) {
                return dist[l] + 1;
            } else if(l + nom[i] < kwota && dist[l + nom[i]] == 0) {
                dist[l + nom[i]] = dist[l] + 1;
                to_s.push(l + nom[i]);
            }
        }
    }
    return -1;
}

int main() {
    int n, d, a;
    vector<int> bnkt;
    scanf("%d %d", &n, &d);
    for(int i = 0; i < d; i++) {
        scanf("%d", &a);
        bnkt.push_back(a);
    }
    printf("%d", banknot(n, bnkt));
    return 0;
}