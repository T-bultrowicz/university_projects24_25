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
    deque <int> cons_min;
    int l = 0, p = 1;
    int res = 1;
    cons_min.push_front(0);
    while(p < events.size()) {
        if(events[p].first - events[l].first < k) {
            while(!cons_min.empty()) {
                if(events[p].second < events[cons_min.front()].second) {
                    cons_min.pop_front();
                } else {
                    break;
                }
            }
            cons_min.push_front(p);
            p++;
        } else {
            res = max(res, events[cons_min.back()].second);
            if(l++ == cons_min.back()) {
                cons_min.pop_back();
            }           
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