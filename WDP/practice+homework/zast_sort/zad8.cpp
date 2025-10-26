#include<bits/stdc++.h>
using namespace std;

int rejs(int k, const vector <int> start, const vector <int> end) {
    vector <pair <int, int> > events;
    for(int i = 0; i < start.size(); i++) {
        events.push_back({start[i], 1});
        events.push_back({end[i] + 1, -1});
    }
    sort(events.begin(), events.end());
    for(int i = 1; i < events.size(); i++) {
        events[i].second += events[i - 1].second;
    }
    int l = 0, p = 0;
    int res = -1;
    int turn_down = 0;
    while(p < events.size() && l < events.size()) {
        if(p == l) {
            p++;
        } else if(events[l].second >= k) {
            while(events[l].second - turn_down >= k) {
                if(p == events.size()) {
                    break;
                }
                if(events[p].second < events[p - 1].second) {
                    turn_down++;
                }
                p++;
            }
            p--;
            res = max(res, events[p].first - events[l].first);
            if(events[l + 1].second < events[l].second) {
                turn_down--; 
            }
            l++;
            p++;
        } else {
            l++;
        }
    }
    return res;
}

int main() {
    int a, b;
    if(scanf("%d %d", &a, &b) != 2) {
        return -1;
    }
    vector <int> c, d;
    int acc;
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &acc) != 1) {
            return -1;
        }
        c.push_back(acc);
    }
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &acc) != 1) {
            return -1;
        }
        d.push_back(acc);
    }    
    printf("%d", rejs(b, c, d));
    return 0;
}